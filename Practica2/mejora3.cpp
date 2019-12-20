#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "iostream"
#include <algorithm>

using namespace std;

double uniforme() //Genera un número uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C. Lo utiliza el generador de demanda
{
    int t = random();
    double f = ((double)RAND_MAX + 1.0);
    return (double)t / f;
}

float *construye_prop_a(int n) //Construye la tabla de búsqueda de
                               //tamaño n para la distribución de
                               //la demanda del apartado (a).
{
    int i;
    float *temp;
    if ((temp = (float *)malloc(n * sizeof(float))) == NULL)
    {
        fputs("Error reservando memoria para generador uniforme\n", stderr);
        exit(1);
    }
    temp[0] = 1.0 / n;
    for (i = 1; i < n; i++)
        temp[i] = temp[i - 1] + 1.0 / n;

    return temp;
}

float *construye_prop_b(int n) //Construye la tabla de búsqueda de
                               //tamaño n para la distribución de
                               //la demanda del apartado (b).
{
    int i, max;
    float *temp;
    if ((temp = (float *)malloc(n * sizeof(float))) == NULL)
    {
        fputs("Error reservando memoria para generador proporcional\n", stderr);
        exit(1);
    }
    max = (n / 2) * (n + 1);
    temp[0] = n * 1.0 / max;

    return temp;
}

float *construye_prop_c(int n) //Construye la tabla de búsqueda de
                               //tamaño n para la distribución de
                               //la demanda del apartado (c).
{
    int i, max;
    float *temp;
    if ((temp = (float *)malloc(n * sizeof(float))) == NULL)
    {
        fputs("Error reservando memoria para generador triangular\n", stderr);
        exit(1);
    }
    max = n * n / 4;
    temp[0] = 0.0;
    for (i = 1; i < (n / 2); i++)
        temp[i] = temp[i - 1] + (float)i / max;
    for (i = (n / 2); i < n; i++)
        temp[i] = temp[i - 1] + (float)(n - i) / max;


    return temp;
}

int genera_demanda(float *tabla, int tama) // Genera un valor de la
                                           // distribución de la demanda codificada en tabla, por el
                                           // método de tablas de búsqueda.
                                           // tama es el tamaño de la tabla, 100 en nuestro caso particular
{
    int i;
    double u = uniforme();
    i = 0;
    while ((i < tama) && (u >= tabla[i]))
        i++;


    
    return i;
}

int genera_demanda_a(float *tabla, int tama) 
{
    int i;
    double u = uniforme();
    float tam_intervalo  = 1.0 / tama;
    
    float division = u/ tam_intervalo;
    return (int)division;
    

    
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    //Inicializa el generador de números pseudoaleatorios

    double x, y, z, ganancia, gananciaesperada, desviaciont;
    int veces, opcion;

    if (argc != 6)
    {
        system("clear");
        cout << "Error: Numero incorrecto de parametros.\n";
        cout << "El uso correcto del programa es:\n";
        cout << "<ganancia por unidad> <perdida por unidad> <gastos de devolución> <numero repeticiones> <distribución de probabilidad>\n"
             << endl;
        exit(1);
    }
    else
    {
        opcion = atoi(argv[5]);
        if (opcion >= 0 && opcion <= 2)
        {
            x = atoi(argv[1]);
            y = atoi(argv[2]);
            z = atoi(argv[3]);
            veces = atoi(argv[4]);
        }
        else
        {
            cout << "Error: La distribución de probabilidad tiene que ser 0, 1 o 2.\n";
            cout << "El uso correcto del programa es:\n";
            exit(1);
        }
    }
    float *tablademanda;
    
    if (opcion == 0)
    {
        tablademanda = construye_prop_a(100);
    }
    else if (opcion == 1)
    {
        tablademanda = construye_prop_b(100);
    }
    else
    {
        tablademanda = construye_prop_c(100);
    }

    unsigned t0, t1;
    
    t0=clock();

    /*cout << "s:"
         << "ganacia:"
         << "desviación" << endl;*/
    for (int s = 1; s < 100; s++)
    {
        double sum = 0.0, sum2 = 0.0;
        for (int i = 0; i < veces; i++)
        {
            int demanda;
            if(opcion == 0){
                demanda = genera_demanda_a(tablademanda, 100);
            }else
                demanda = genera_demanda(tablademanda,100);
            
            

            if (s > demanda)
                ganancia = demanda * x - min(z, (s - demanda) * y);
            else
                ganancia = s * x;
            sum += ganancia;
            sum2 += ganancia * ganancia;
        }
        gananciaesperada = sum / veces;
        desviaciont = sqrt((sum2 - veces * gananciaesperada * gananciaesperada) / (veces - 1));
        //cout << s << ":" << gananciaesperada << ":" << desviaciont << endl;
    }

    t1 = clock();
    cout << veces << ":" << double(t1-t0)/CLOCKS_PER_SEC << endl;
    free(tablademanda);
}
//El programa principal debe también incluir lo siguiente:
