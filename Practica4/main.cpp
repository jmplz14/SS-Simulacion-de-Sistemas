#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

const int numeq = 2;

double a11, a12, a21, a22;
double tinicio, tfin, dt;
double estado[numeq];
double oldestado[numeq];
int metodo = 0;

void salida(ofstream& fichero, double t)
{
    fichero << t << "," << estado[0] << "," << estado[1] << endl;
}

void derivacion(double *est, double *f)
{
    f[0] = a11 * est[0] - a12 * est[0] * est[1];
    f[1] = a21 * est[0] * est[1] - a22 * est[1];
}

void one_step_euler(double *inp, double *out, double tt, double hh)
{
    double f[numeq];
    derivacion(inp, f);
    for (int i = 0; i < numeq; i++)
        out[i] = inp[i] + hh * f[i];
}

void one_step_kutta(double *inp, double *out, double tt, double hh)
{

    for (int i = 0; i < numeq; i++)
        out[i] = inp[i];

    double time = tt;
    double f[numeq], k[numeq][4];

    for (int j = 0; j < 4; j++)
    {

        derivacion(out, f);

        for (int i = 0; i < numeq; i++)
            k[i][j] = f[i];

        double incr, time;
        if (j < 2)
            incr = hh / 2;
        else
            incr = hh;
        time = tt + incr;

        for (int i = 0; i < numeq; i++)
            out[i] = inp[i] + k[i][j] * incr;
    }

    for (int i = 0; i < numeq; i++)
        out[i] = inp[i] + hh / 6 * (k[i][0] + 2 * k[i][1] + 2 * k[i][2] + k[i][3]);
}

void one_step(double *inp, double *out, double tt, double hh)
{
    if (metodo == 0)
    {
        one_step_euler(inp, out, tt, hh);
    }
    else
    {
        one_step_kutta(inp, out, tt, hh);
    }
}

void integracion()
{

    ofstream fichero;
    fichero.open("datos.csv");
    double t = tinicio;
    do
    {

        salida(fichero,t);

        oldestado[0] = estado[0];
        oldestado[1] = estado[1];

        one_step(oldestado, estado, t, dt);

        t += dt;

    } while (t <= tfin);
    fichero.close();
}

int main(int argc, char *argv[])
{

    if (argc != 11)
    {
        cout << "Parametros incorrectos, el programa tiene el siguiente formato:" << endl;
        cout << argv[0] << " a11 a12 a21 a22 Tinicio Tfin Poblacionx Poblaciony dt Tipo" << endl;
        exit(1);
    }

    a11 = stod(argv[1]);
    a12 = stod(argv[2]);
    a21 = stod(argv[3]);
    a22 = stod(argv[4]);

    tinicio = stod(argv[5]);
    tfin = stod(argv[6]);

    estado[0] = stod(argv[7]);
    estado[1] = stod(argv[8]);

    dt = stod(argv[9]);

    int metodoIntroducido = stoi(argv[10]);
    if (metodoIntroducido == 1)
        metodo = 1;

    integracion();
}