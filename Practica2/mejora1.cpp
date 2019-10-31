#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "iostream"
#include <algorithm> 
#include <ctime>
using namespace std;

struct posicion {
  int numero;
  float valor;
} ;

double uniforme() //Genera un número uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C. Lo utiliza el generador de demanda
{
    int t = random();
    double f = ((double)RAND_MAX + 1.0);
    return (double)t / f;
}

posicion *construye_prop_a(int n) //Construye la tabla de búsqueda de
                               //tamaño n para la distribución de
                               //la demanda del apartado (a).
{
    int i;
    posicion *temp;
    if ((temp = (posicion *)malloc(n * sizeof(posicion))) == NULL)
    {
        fputs("Error reservando memoria para generador uniforme\n", stderr);
        exit(1);
    }
    temp[0].valor = 1.0 / n;
    temp[0].numero = 0;
    for (i = 1; i < n; i++){
        temp[i].valor = temp[i - 1].valor + 1.0 / n;
        temp[i].numero = i;
    }
    return temp;
}

posicion *construye_prop_b(int n) //Construye la tabla de búsqueda de
                               //tamaño n para la distribución de
                               //la demanda del apartado (b).
{
    int i, max;
    posicion *temp;
    if ((temp = (posicion *)malloc(n * sizeof(posicion))) == NULL)
    {
        fputs("Error reservando memoria para generador proporcional\n", stderr);
        exit(1);
    }
    max = (n / 2) * (n + 1);
    temp[0].valor = n * 1.0 / max;
    temp[0].numero = 0;
    for (i = 1; i < n; i++){
        temp[i].valor = temp[i - 1].valor + (float)(n - i) / max;
        temp[i].numero = i;
    }

    return temp;

}

posicion *construye_prop_c(int n) //Construye la tabla de búsqueda de
                               //tamaño n para la distribución de
                               //la demanda del apartado (c).
{
    int i, j, k, max, medio = n/2;
    posicion *temp;
    
    if ((temp = (posicion *)malloc(n * sizeof(posicion))) == NULL)
    {
        fputs("Error reservando memoria para generador triangular\n", stderr);
        exit(1);
    }
    max = n * n / 4;

    int val_medio = n / 2;
	
	
	temp[0].numero = medio;
	temp[0].valor = (float)val_medio / max;

	j = 1;
	for (i=1 ;i < medio;i++)
	{

		
        temp[j].numero = medio - i;
        temp[j+1].numero = medio + i;
		
        temp[j].valor = temp[j-1].valor + (float)temp[j].numero / max;
        j++;
        temp[j].valor = temp[j-1].valor + (float)temp[j-1].numero / max;
        j++;
        
				
	}

    for (int j = 0; j<n; j++)
        cout << temp[j].valor << endl;
    return temp;
}

int genera_demanda(posicion *tabla, int tama) // Genera un valor de la
                                           // distribución de la demanda codificada en tabla, por el
                                           // método de tablas de búsqueda.
                                           // tama es el tamaño de la tabla, 100 en nuestro caso particular
{
    int i;
    double u = uniforme();
    i = 0;
    while ((i < tama) && (u >= tabla[i].valor))
        i++;
    return tabla[i].numero;
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
        cout << "<ganancia por unidad> <perdida por unidad> <gastos de devolución> <numero repeticiones> <distribución de probabilidad>\n" << endl;
        exit(1);
    }
    else
    {
        opcion = atoi(argv[5]);
        if(opcion >= 0 && opcion <= 2)
        {
            x = atoi(argv[1]);
            y = atoi(argv[2]);
            z = atoi(argv[3]);
            veces = atoi(argv[4]);
        }else
        {   
            cout << "Error: La distribución de probabilidad tiene que ser 0, 1 o 2.\n";
            cout << "El uso correcto del programa es:\n";
            exit(1);
        }
        
        
        

    }
    posicion *tablademanda;
    if(opcion == 0){
        tablademanda = construye_prop_a(100);
    }else if (opcion == 1){
        tablademanda = construye_prop_b(100);
    }else{     
        tablademanda = construye_prop_c(100);
    }
        
            
    
    
    unsigned t0, t1;
 
    t0=clock();
    
    cout << "s:" << "ganacia:" << "desviación" << endl;
    for (int s = 1; s < 100; s++)
    {
        double sum = 0.0, sum2 = 0.0;
        for (int i = 0; i < veces; i++)
        {
            int demanda = genera_demanda(tablademanda, 100);

            if (s > demanda)
                ganancia = demanda * x - min(z,(s-demanda) * y);
            else
                ganancia = s * x;
            sum += ganancia;
            sum2 += ganancia * ganancia;
        }
        gananciaesperada = sum / veces;
        desviaciont = sqrt((sum2 - veces * gananciaesperada * gananciaesperada) / (veces - 1));
        cout << s << ":" << gananciaesperada << ":" << desviaciont << endl;
    }
    t1 = clock();
    cout << "Tiempo de Ejecución:" << double(t1-t0)/CLOCKS_PER_SEC << endl;
    free(tablademanda);
}
//El programa principal debe también incluir lo siguiente:
