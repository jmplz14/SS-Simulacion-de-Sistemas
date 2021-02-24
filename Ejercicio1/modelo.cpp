#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "iostream"
#include <algorithm>
#include <limits>

using namespace std;

const int MAX_PROBABLE = 2600, MENOR = 2000, MAYOR = 3000;
const double PRECIO_VENTA = 0.60, PRECIO_COMPRA_AGOSTO = 1 * 0.25, PRECIO_COMPRA_DICIEMBRE = 1.50*0.25;

double uniforme() //Genera un número uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C. Lo utiliza el generador de demanda
{
    int t = random();
    double f = ((double)RAND_MAX + 1.0);
    return (double)t / f;
}
int genera_demanda()
{
    int i;
    double u,x;
    u = uniforme();
    if (u < (MAX_PROBABLE-MENOR)/(MAYOR-MENOR))
        x = MENOR + sqrt((MAYOR-MENOR) * (MAX_PROBABLE - MENOR) * u );
    else
        x = MAYOR -sqrt((MAYOR-MENOR) * (MAYOR-MAX_PROBABLE) * (1-u));
    return (int)x;
    
    
}

int main(int argc, char *argv[])
{
    int numRepes = 100000;
    srand(time(NULL));
    //Inicializa el generador de números pseudoaleatorios
    double mejorGanancia = numeric_limits<double>::min(), mejorDesviacion;
    int mejorValor;
    int mejorDemanda;
    
    for (int i = MENOR; i < MAYOR; i++)
    {
        double sumMedia = 0, sumDesviacion = 0;
        int ganancia,gastos;
        for (int j = 0; j < numRepes; j++){
            int demanda = genera_demanda();
            ganancia = (double) demanda * PRECIO_VENTA; 
            if (demanda <= i)
                gastos = (double) i * PRECIO_COMPRA_AGOSTO;
            else
                gastos = (double)i *PRECIO_COMPRA_AGOSTO + (double)(demanda-i) * PRECIO_COMPRA_DICIEMBRE;
                   
            ganancia -= gastos;
            sumMedia += ganancia;
            sumDesviacion += ganancia * ganancia;


        }
        
        double media = sumMedia / numRepes;
        double desviacion = sqrt((sumDesviacion - numRepes * media * media) / (numRepes - 1));

        cout << "Demanda: " << i << " Kilos comprados:" << i * 0.25 << " Ganancia: " << media << " Desviacion: " << desviacion << endl;

        if(media>mejorGanancia){
            mejorDemanda = i;
            mejorGanancia = media;
            mejorDesviacion = desviacion;
            mejorValor = i;
        }
        

    }

    cout << "-----------------------------------------------------------------------------------------" << endl;
    cout << "Se obtiene la mejor ganancia comprando " << mejorValor * 0.25 << " para una demanda de " << mejorDemanda << endl;
    cout << "La ganancia es de " << mejorGanancia << " con una desviación de " << mejorDesviacion << endl;

    
}
