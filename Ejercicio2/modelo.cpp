#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <iostream>

using namespace std;

#define suceso_llegada 0
#define suceso_fin_A 1
#define suceso_fin_B 2
#define suceso_fin 4


typedef struct
{
    int suceso;
    double tiempo;
} suc;
list<suc> lsuc;
suc nodo;
double mediaTotal = 0.0;
double desviacion = 0.0;
int numSimulacion;
const double TIEMPO_MEDIO_LLEGADA = 1.0, TIEMPO_MEDIO_A = 0.8, TIEMPO_MEDIO_B = 0.86;
const double INICIO = 0.0, FINAL = 480.0;
bool parar;
double reloj, acumSistema;
bool libreA, libreB;
int nodosFinalizados, colaA, colaB;
list<double> llegadas;

bool compare(const suc &s1, const suc &s2)
{
    return s1.tiempo < s2.tiempo;
}

void insertar_lsuc(suc n)
{
    lsuc.push_back(n);
    lsuc.sort(compare);
}

double generador_exponencial(double media)
{
    double u;
    u = (double)random();
    u = u / (double)(RAND_MAX + 1.0);
    return (-media * log(1 - u));
}

void inicializacion()
{

    nodosFinalizados = 0;
    reloj = 0.0;
    acumSistema = 0.0;
    nodo.suceso = suceso_llegada;
    nodo.tiempo = reloj + generador_exponencial(TIEMPO_MEDIO_LLEGADA);
    insertar_lsuc(nodo);
    nodo.suceso = suceso_fin;
    nodo.tiempo = reloj + FINAL;
    insertar_lsuc(nodo);
    colaA = 0;
    colaB = 0;

    libreA = true;
    libreB = true;
    parar = false;
}

void temporizacion()
{
    nodo = lsuc.front();
    lsuc.pop_front();
    reloj = nodo.tiempo;
}

void fin()
{
    parar = true;
    double estanciamedia = acumSistema / nodosFinalizados;
    cout << endl
         << "Simulacion " << numSimulacion << " Tiempo medio de estancia en el sistema " << estanciamedia;
}

void generarInsertarSuceso(int suceso, double tiempo)
{
    nodo.suceso = suceso;
    nodo.tiempo = reloj + generador_exponencial(tiempo);
    insertar_lsuc(nodo);
}
void llegada()
{


    generarInsertarSuceso(suceso_llegada, TIEMPO_MEDIO_LLEGADA);
    llegadas.push_back(reloj);

    if (libreA)
    {
        libreA = false;
        generarInsertarSuceso(suceso_fin_A, TIEMPO_MEDIO_A);
    }
    else
    {
        colaA++;
    }
}

void finA()
{

    if (colaA > 0)
    {
        colaA--;
        generarInsertarSuceso(suceso_fin_A, TIEMPO_MEDIO_A);
    }
    else
    {
        libreA = true;
    }

    if (libreB)
    {
        libreB = false;
        generarInsertarSuceso(suceso_fin_B, TIEMPO_MEDIO_B);
    }
    else
    {
        colaB++;
    }
}

void finB()
{

    if (colaB > 0)
    {
        colaB--;
        generarInsertarSuceso(suceso_fin_B, TIEMPO_MEDIO_B);
    }
    else
    {
        libreB = true;
    }

    nodosFinalizados++;
    double tiempoLlegada = llegadas.front();
    llegadas.pop_front();
    acumSistema += reloj - tiempoLlegada;
}

void suceso()
{
    switch (nodo.suceso)
    {
    case suceso_llegada:
        llegada();
        break;
    case suceso_fin_A:
        finA();
        break;
    case suceso_fin_B:
        finB();
        break;
    case suceso_fin:
        fin();
        break;
    }
}

int main(int argc, char *argv[])
{   
    if (argc != 2)
    {
     printf("\n\nFormato Argumentos -> <nuemeroRepes>\n\n");
     exit(1);
    }
    int numRepes = stoi(argv[1]);
    

    srandom(time(NULL));
    for (numSimulacion = 0; numSimulacion < numRepes; numSimulacion++)
    {
        inicializacion();
        while (!parar)
        {
            temporizacion();
            suceso();

        }
        double media = acumSistema / nodosFinalizados;
        mediaTotal += media;
        desviacion += media * media;
        lsuc.clear();
        llegadas.clear();

    }
    
    mediaTotal = mediaTotal/numRepes;
    double desviacionTotal = sqrt((desviacion - numRepes * mediaTotal * mediaTotal) / (numRepes - 1));
    
    cout << endl <<  "------------------------------------------------------------------";
    cout << endl <<"El tiempo medio de espera es " << mediaTotal;
    cout << endl << "Tenemos una desviación de " << desviacionTotal << endl;
}