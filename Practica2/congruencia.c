#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
long long int aritmeticaEntera(int a ,long long x, int c, int m)
{
    return (a*x*c)%m;
}

long long int aritmeticaRealCaseraFloat(int a ,long long x, int c, int m){
    float fx = (float) x;
    fx = (a * fx + c) / m;
    fx = (fx - (int)fx) * m;
    return (long long int)fx;
}

long long int aritmeticaRealCaseraDouble(int a ,long long x, int c, int m){
    double fx = (double) x;
    fx = (a * fx + c) / m;
    fx = (fx - (int)fx) * m;
    return (long long int)fx;
}

long long int aritmeticaRealArtesanalCorregida(int a ,long long x, int c, int m){
    double fx = (double) x;
    fx = (a * fx + c) / m;
    fx = (fx - (int)fx) * m;
    fx = (int)(fx+0.5);
    return (long long int)fx;
}

long long int aritmeticaRealFmod(int a ,long long x, int c, int m){
    double fx = (double) x;
    fx = fmod((a*fx+c),m);
    
    return (long long int)fx;
}

int main(int argc, char *argv[])
{
    int opcion,numVeces;
    long long x0 = 6;
    int a1 = 2061, a2 = 2060, c = 4321, m = 1e4;

    if (argc != 3)
    {
        printf("\nSolo tenemos un argumento\n");
        printf("<tipo aritmética> <numero de repeticiones>");
        exit(1);
    }
    else
    {
        opcion = atoi(argv[1]);
        numVeces = atoi(argv[2]);

        if (opcion > 4 || opcion < 0)
        {
            printf("Tendra 5 posibles valores:\n");
            printf("0: Aritmética entera\n");
            printf("1: Aritmética real casera float\n");
            printf("2: Aritmética real casera double\n");            
            printf("3: Aritmética real casera corregida\n");
            printf("4: Aritmética real con fmod\n");
            exit(1);
        }
    }

    int i = 0;
    long long int valor = x0;
    bool repetido = false;
    bool *repes;

    if ((repes = (bool *)malloc(m * sizeof(bool))) == NULL)
    {
        fputs("Error reservando memoria para generador triangular\n", stderr);
        exit(1);
    }

    while(i < numVeces && repetido == false){
    
        if(opcion == 0){
            valor = aritmeticaEntera(a2,valor,c,m);
        }else if (opcion == 1)
        {
            valor = aritmeticaRealCaseraFloat(a2,valor,c,m);
        }else if (opcion == 2)
        {
            valor = aritmeticaRealCaseraDouble(a2,valor,c,m);
        }else if (opcion == 3)
        {
            valor = aritmeticaRealArtesanalCorregida(a2,valor,c,m);
        }else if (opcion == 4)
        {
            valor = aritmeticaRealFmod(a2,valor,c,m);
        }
        
        printf("%lld\n",valor);

        if (repes[valor] == false){
            repes[valor] = true;
            i++;
        }else{
            repetido = true;
        }
        
    }
    
    if(repetido == true){
        printf("Se repitio en la posicion %d \n", i + 1);
    }else
    {
        printf("No se repitio nunca\n");
    }
    
    free(repes);
    return 0;
}