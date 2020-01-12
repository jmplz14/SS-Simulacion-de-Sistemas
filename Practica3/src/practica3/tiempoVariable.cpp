
#include <iostream>
#include <cmath>
#include <ctime>
#include <algorithm>

using namespace std;

float generaLlegada(float tlleg)
{

    float u = (float)random();
    u = (float)(u / (RAND_MAX + 1.0));
    return -tlleg * log(1 - u);
}

float generaServicio(float tserv)
{

    float u = (float)random();
    u = (float)(u / (RAND_MAX + 1.0));
    return -tserv * log(1 - u);

}

int main(int argc, char *argv[])
{
    
    

    double tlleg, tserv,total_porcent_ocio = 0.0, total_media_encola = 0.0;
    long long int numero_repes,total_a_atender;
    unsigned t0, t1;
    double tiempo_medio = 0;
    //introducir usuario tlleg, total_a_atender y tserv
    if (argc == 5){
        tlleg = atof(argv[1]);
        total_a_atender = atoi(argv[2]);
        tserv = atof(argv[3]);
        numero_repes = atoi(argv[4]);
        
    }else{
        system("clear");
        cout << "Error: Numero incorrecto de parametros.\n";
        cout << "El uso correcto del programa es:\n";
        cout << argv[0] << " <tiempo de llegada> <total clientes a atender> <tiempo de servicio> <numero de repeticiones>\n" << endl;
        exit(1);
    }
    
    srand(time(NULL));

    cout << "Pasada" << ":" << "Media en cola" << ":" << "Porcentaje tiempo de ocio" << "Tiempo" << endl;

    for(int i = 0; i < numero_repes; i++){
        bool servidor_libre = true;

        long long int infinito = 1e30, atendidos = 0, encola = 0;

        double tiempo_llegada, tiempo_salida = infinito, inicio_ocio = 0.0, acum_cola = 0.0, ocio = 0.0, porcent_ocio, media_encola,reloj = 0.0,tultsuc = reloj;
        

        tiempo_llegada = reloj + generaLlegada(tlleg);
        t0=clock();
        while (atendidos < total_a_atender)
        {
            reloj = min(tiempo_llegada,tiempo_salida);
            if (reloj == tiempo_llegada) //si estamos en el instante en que llega alguien
            {
                
                tiempo_llegada = reloj + generaLlegada(tlleg); //determinamos cuando llegará
                                                            //el siguiente cliente
                if (servidor_libre)                            //si el servidor está ocioso
                {
                    servidor_libre = false;                        //deja de estarlo
                    tiempo_salida = reloj + generaServicio(tserv); //determinamos cuando saldrá
                                                                //ese cliente que acaba de llegar
                    ocio += reloj - inicio_ocio;                   //acumulamos el ocio hasta este momento
                }
                else
                {                                            //el servidor está ocupado
                    acum_cola += (reloj - tultsuc) * encola; //acumulamos el número de clientes en
                                                            //cola por el tiempo en que han estado en cola
                    tultsuc = reloj;                         //para saber en qué momento cambió el tamaño de la cola, en
                                                            //este caso aumentó en uno más
                    encola++;                                //hay un cliente más en cola
                }
            }
            if (reloj == tiempo_salida) //si estamos en el instante en que se va alguien
            {
                atendidos++;    //se ha atendido a un cliente más
                if (encola > 0) //si quedan clientes en cola
                {
                    acum_cola += (reloj - tultsuc) * encola;       // acumulamos el número de clientes en
                                                                //cola por el tiempo en que han estado en cola
                    tultsuc = reloj;                               //para saber en qué momento cambió el tamaño de la cola, en
                                                                //este caso disminuyó en uno
                    encola--;                                     //hay un cliente menos en cola

                    tiempo_salida = reloj + generaServicio(tserv); //determinamos cuando saldrá
                                                                //ese cliente que acaba de entrar
                }
                else
                {                             //no quedan clientes en cola
                    servidor_libre = true;    //el servidor se queda ocioso por falta de clientes
                    inicio_ocio = reloj;      //marcamos cuando empieza a estar ocioso
                    tiempo_salida = infinito; //nadie puede salir puesto que nadie hay
                }
            }
            
            
        }
        t1 = clock();

        porcent_ocio = ocio * 100 / reloj; //calculamos el porcentaje de tiempo de ocio del servidor
        
        media_encola = acum_cola / reloj; //calculamos el número medio de clientes en cola
        /*cout << porcent_ocio << endl;
        cout << media_encola << endl;*/
        double tiempo = (double(t1-t0)/CLOCKS_PER_SEC);
        cout << i << ":" << media_encola << ":" << porcent_ocio << tiempo << endl;
        total_media_encola += media_encola;
        total_porcent_ocio += porcent_ocio;
        tiempo_medio += tiempo;
        
    }
    cout << endl << "media clientes en cola:" << total_media_encola /numero_repes<< endl;
    cout << "media porcentaje de ocio:" <<total_porcent_ocio/numero_repes << endl;
    cout << "media tiempo en ejecucion:" << tiempo_medio /numero_repes<< endl;


}