#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
long long int aritmeticaEntera(int a ,long long x, int c, int m)
{
    return (a*x+c)%m;
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
    int opcion,numVeces, xElegido;
    long long x0 = 14;
    int a, c = 4321, m = 1e4;

    if (argc != 4)
    {
        printf("\nSolo tenemos un argumento\n");
        printf("<tipo aritmética> <numero de repeticiones> <elegir a 0 = 2060 y 1 = 2061>\n");
        exit(1);
    }
    else
    {
        opcion = atoi(argv[1]);
        numVeces = atoi(argv[2]);
        xElegido = atoi(argv[3]);

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
        if (xElegido > 1 || xElegido < 0)
        {
            printf("Tendra 2 posibles valores:\n");
            printf("0: a = 2060\n");
            printf("1: a = 2061\n");
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
    if (xElegido == 0){
        a = 2060;
    }else
    {
        a = 2061;
    }
    

    while(i < numVeces && repetido == false){
    
        if(opcion == 0){
            valor = aritmeticaEntera(a,valor,c,m);
        }else if (opcion == 1)
        {
            valor = aritmeticaRealCaseraFloat(a,valor,c,m);
        }else if (opcion == 2)
        {
            valor = aritmeticaRealCaseraDouble(a,valor,c,m);
        }else if (opcion == 3)
        {
            valor = aritmeticaRealArtesanalCorregida(a,valor,c,m);
        }else if (opcion == 4)
        {
            valor = aritmeticaRealFmod(a,valor,c,m);
        }
        

        if (repes[valor] == false){
            repes[valor] = true;
            i++;
        }else{
            repetido = true;
        }
        
    }
    
    if(repetido == true){
        
        printf("Se repitió en la posición %d \n", i);
        
        
    }else
    {
        printf("No se repitió nunca\n");
    }
    
    free(repes);
    return 0;
}