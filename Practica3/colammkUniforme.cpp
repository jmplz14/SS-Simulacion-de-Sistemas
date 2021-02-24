#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <iostream>

using namespace std;

#define suceso_llegada 0
#define suceso_salida 1
#define suceso_finsimulacion 3
#define suceso_monitor 4

typedef struct {
	int suceso;
	float tiempo;
	float retraso;
	} suc;
list<suc> lsuc;
suc nodo;
int nada = 0;
list<float> cola;
int m; //numero de servidores
float tparada;
float tlleg;
float tserv;
float valor;
int numRepeticiones;

float total_espera_cola = 0.0; 
float des_espera_cola = 0.0;
float total_estancia_sistema = 0.0;
float des_estancia_sistema = 0.0;
float total_clientes_cola = 0.0;
float des_clientes_cola = 0.0;
float total_clientes_sistema = 0.0;
float des_clientes_sistema = 0.0;
float total_longitud_colas_no_vacias = 0.0;
float des_longitud_colas_no_vacias = 0.0;
float total_porcentaje_ocio = 0.0;
float des_porcentaje_ocio = 0.0;
float total_log_cola = 0.0;
float des_log_cola = 0.0;

int total_maxima_cola = 0;
float reloj;
int libres;
int encola;
int ensistema;
int atendidos;
float acum_cola;
float acum_sistema;
float acum_ocio;
float acum_retraso;
float tultsuc_cola;
float tultsuc_ocio;
float tultsuc_sistema;
float acum_sincola;
float init_sincola;
int maximacola;
bool parar;

bool compare(const suc &s1, const suc &s2)
{ return s1.tiempo < s2.tiempo; }


/* Inserta de forma ordenada un elemento en la lista de sucesos */
void insertar_lsuc(suc n)
{
  lsuc.push_back(n);
  // Mantener ordenada la lista por el tiempo de los sucesos
  lsuc.sort(compare);
}

float generador_uniforme(float media)
{
	float u;
	u = (float) random();
	u = u/(float)(RAND_MAX+1.0); //RAND_MAX es una constante del sistema
	return (media * 2 * u);
}

// Generador de tiempos entre llegadas (exponencial)
float generallegada(float media)
{ return generador_uniforme(media); }

// Generador de tiempos de servicio (exponencial)
float generaservicio(float media)
{ return generador_uniforme(media); }


/* Procedimiento inicializacion */
void inicializacion()
{

lsuc.clear();
cola.clear();
reloj = 0.0;
libres = m;
encola = 0;
ensistema = 0;
atendidos = 0;
acum_cola = 0.0;
acum_sistema = 0.0;
acum_ocio = 0.0;
acum_retraso = 0.0;
tultsuc_cola = reloj;
tultsuc_ocio = reloj;
tultsuc_sistema = reloj;
acum_sincola = 0.0;
init_sincola = reloj;
maximacola = 0;
nodo.suceso = suceso_llegada;
nodo.tiempo = reloj+generallegada(tlleg);
nodo.retraso = nada;
insertar_lsuc(nodo);
nodo.suceso = suceso_finsimulacion;
nodo.tiempo = reloj+tparada;
nodo.retraso = nada;

insertar_lsuc(nodo); //tparada es un par�metro de entrada al programa
//Inicializar el suceso monitor si que quiere trazar alguna medida del rendimiento a lo largo del tiempo, no solo al final
/* 
nodo.suceso = suceso_monitor;
nodo.tiempo = reloj+1.0;
nodo.retraso = nada;
insertar_lsuc(nodo);
*/
 
parar = false;
}

/* Procedimiento temporizacion */
void temporizacion()
{
  nodo = lsuc.front();
  lsuc.pop_front();
  reloj = nodo.tiempo;
//  printf("\n%.3f",reloj);
}


void llegada()
{
acum_sistema += (reloj - tultsuc_sistema) * ensistema;
tultsuc_sistema = reloj;
ensistema ++;
nodo.suceso = suceso_llegada;
nodo.tiempo = reloj+generallegada(tlleg);
nodo.retraso = nada;
insertar_lsuc(nodo);
if (libres > 0)
     {
      acum_ocio += (reloj - tultsuc_ocio) * libres;
      tultsuc_ocio = reloj;
      libres --;
      nodo.suceso = suceso_salida;
      nodo.tiempo = reloj+generaservicio(tserv);
      nodo.retraso = nada;
      insertar_lsuc(nodo);
     }
else {
      if (encola == 0) acum_sincola += reloj - init_sincola;
      acum_cola += (reloj - tultsuc_cola) * encola;
      tultsuc_cola = reloj;
      encola ++;
      if (encola > maximacola) maximacola = encola;
      cola.push_back(reloj);
      }
}

void salida()
{
acum_sistema += (reloj - tultsuc_sistema) * ensistema;
tultsuc_sistema = reloj;
ensistema --;
atendidos ++;
acum_retraso += nodo.retraso;
if (encola > 0)
     {
      acum_cola += (reloj - tultsuc_cola) * encola;
      tultsuc_cola = reloj;
      encola --;
      if (encola == 0) init_sincola = reloj;
      valor = cola.front();
      cola.pop_front();
      nodo.suceso = suceso_salida;
      nodo.tiempo = reloj+generaservicio(tserv);
      nodo.retraso = reloj-valor;
      insertar_lsuc(nodo);
     }
else {
      acum_ocio += (reloj - tultsuc_ocio) * libres;
      tultsuc_ocio = reloj;
      libres ++;
     }
}

void fin()
{
parar = true; //para detener la simulaci�n
              //habr� que hacer las �ltimas actualizaciones de algunas variables
float retrasomedio = acum_retraso/atendidos;
total_espera_cola += retrasomedio;
des_espera_cola += pow(retrasomedio, 2);
//printf("\nTiempo medio de espera en cola = %.3f",retrasomedio);
float estanciamedia = retrasomedio + tserv;
total_estancia_sistema += estanciamedia;
des_estancia_sistema += pow(estanciamedia, 2);
//printf("\nTiempo medio de estancia en el sistema = %.3f",estanciamedia);
acum_cola += (reloj - tultsuc_cola) * encola;

//printf("\nTiempo medio de espera en cola bis = %.3f",acum_cola/atendidos);
//printf("\nTiempo medio de estancia en el sistema bis= %.3f",acum_cola/atendidos+tserv);


float encolamedio = acum_cola/reloj;
total_clientes_cola += encolamedio;
des_clientes_cola += pow(encolamedio, 2);
//printf("\nNumero medio de personas en cola = %.3f",encolamedio);
acum_sistema += (reloj - tultsuc_sistema) * ensistema;
float ensistemamedio = acum_sistema/reloj;
total_clientes_sistema += ensistemamedio;
des_clientes_sistema += pow(ensistemamedio, 2);
//printf("\nNumero medio de personas en el sistema = %.3f",ensistemamedio);
if (encola == 0) acum_sincola += reloj - init_sincola;
float colasnovaciasmedio = acum_cola/(reloj - acum_sincola);
total_longitud_colas_no_vacias += colasnovaciasmedio;
des_longitud_colas_no_vacias += pow(colasnovaciasmedio, 2);
//printf("\nLongitud media de colas no vacias = %.3f",colasnovaciasmedio);
acum_ocio += (reloj - tultsuc_ocio) * libres;
float porcentajemedioocio = 100*acum_ocio/(m*reloj);
total_porcentaje_ocio += porcentajemedioocio;
des_porcentaje_ocio += pow(porcentajemedioocio, 2);
//printf("\nporcentaje medio de tiempo de ocio por servidor = %.3f",porcentajemedioocio);
//printf("\nLongitud m�xima de la cola = %d",maximacola);
//printf("\n");
total_maxima_cola = maximacola > total_maxima_cola? maximacola : total_maxima_cola;
total_log_cola += maximacola;
des_log_cola += pow(maximacola, 2);
}

//Si se desea monitorizar, por ejemplo el n�mero medio de clientes en sistema a lo largo del tiempo se puede usar el suceso monitor siguiente, que habr� que inicializar
void monitor()
{
nodo.suceso = suceso_monitor;
nodo.tiempo = reloj+100.0;
nodo.retraso = nada;
insertar_lsuc(nodo);
cout<<"tiempo y media en sistema "<<reloj<<" "<<(acum_sistema+(reloj - tultsuc_sistema) * ensistema)/reloj<<endl;
//printf("\n %.3f, %3f","tiempo y media en sistema",reloj,(acum_sistema+(reloj - tultsuc_sistema) * ensistema)/reloj);
}

/* Procedimiento suceso */
void suceso()
{
 switch(nodo.suceso)
                {
                 case suceso_llegada: llegada(); break;
                 case suceso_salida: salida(); break;
                 case suceso_finsimulacion: fin(); break;
		 case suceso_monitor: monitor(); break;
                }
}

float desviacion(float des, float media){
  float dev = des - (numRepeticiones * pow(media, 2));
  dev /= (numRepeticiones - 1);
  dev = sqrt(dev);
  return dev;
}

void mostrarMediasYDesviacion(){

  float media_espera_cola = total_espera_cola/numRepeticiones;
  float dev_espera_cola = desviacion(des_espera_cola, media_espera_cola);
  printf("\nTiempo medio de espera en cola: = %.3f",media_espera_cola);
  printf("\nDesviación de espera en cola: = %.3f",dev_espera_cola);

  float media_estancia_sistema = total_estancia_sistema/numRepeticiones;
  float dev_estancia_sistema = desviacion(des_estancia_sistema, media_estancia_sistema);
  printf("\nTiempo medio de estancia en el sistema: = %.3f",media_estancia_sistema);
  printf("\nDesviación de estancia en el sistema: = %.3f",dev_estancia_sistema);

  float media_clientes_cola = total_clientes_cola/numRepeticiones;
  float dev_clientes_cola = desviacion(des_clientes_cola, media_clientes_cola);
  printf("\nNúmero medio de clientes en cola: = %.3f",media_clientes_cola);
  printf("\nDesviación de clientes en cola: = %.3f",dev_clientes_cola);

  float media_clientes_sistema = total_clientes_sistema/numRepeticiones;
  float dev_clientes_sistema = desviacion(des_clientes_sistema, media_clientes_cola);
  printf("\nNúmero medio de clientes en el sistema = %.3f",media_clientes_sistema);
  printf("\nDesviación de clientes en el sistema = %.3f",dev_clientes_sistema);

  float media_longitud_colas_no_vacias = total_longitud_colas_no_vacias/numRepeticiones;
  float dev_longitud_colas_no_vacias = desviacion(des_longitud_colas_no_vacias,media_longitud_colas_no_vacias);
  printf("\nLongitud media de colas no vacías = %.3f",media_longitud_colas_no_vacias);
  printf("\nDesviación de longuitud colas no vacías = %.3f",dev_longitud_colas_no_vacias);

  float media_porcentaje_ocio = (float)total_porcentaje_ocio/numRepeticiones;
  float dev_porcentaje_ocio = desviacion(des_porcentaje_ocio, media_porcentaje_ocio);
  printf("\nMedia Porcentaje de tiempo de ocio del servidor: = %.3f",media_porcentaje_ocio);
  printf("\nDesviación Porcentaje de tiempo de ocio del servidor: = %.3f",dev_porcentaje_ocio);

  float media_cola_max = total_log_cola/numRepeticiones;
  float dev_log_cola = desviacion(des_log_cola, media_cola_max);
  printf("\nMedia longitud cola maxima: = %.3f",media_cola_max);
  printf("\nDesviación longitud cola maxima: = %.3f\n\n",dev_log_cola);

  
  
}


int main(int argc, char *argv[])
{
  
  int i;

  if (argc != 6)
    {
     printf("\n\nFormato Argumentos -> <numero_servidores> <tiempo de parada> <tlleg> <tserv> <numRepeticiones> \n\n");
     exit(1);
    }
  sscanf(argv[1],"%d",&m);
  sscanf(argv[2],"%f",&tparada);
  sscanf(argv[3],"%f",&tlleg);
  sscanf(argv[4],"%f",&tserv);
  sscanf(argv[5],"%d",&numRepeticiones);
  srandom(time(NULL));    
    for (int i = 0; i < numRepeticiones; i++){
      inicializacion();
      while (!parar)
	   {
	    temporizacion();
	    suceso();
	   }
      cout << "Ejecutado la simulación " << i + 1 << endl;
    }
    
    mostrarMediasYDesviacion();
}