#ifndef LIFO_H
#define LIFO_H
#include <vector>
#include <fstream>
#include "Proceso.h"

using namespace std;

double ejecutarLIFO(vector<Actividad> lista, ofstream &reporte) {
    int reloj = 0;
    int completados = 0;
    int n = lista.size();
    vector<bool> hecho(n, false);
    
    double sumaT = 0, sumaE = 0, sumaI = 0;

    reporte << "RESULTADOS DE LIFO\n";
    reporte << "ID\tti\tt\ttf\tT\tE\tI\n";

    while (completados < n) {
        int seleccionado = -1;
        int max_ti = -1;

        for (int i = 0; i < n; i++) {
            if (!hecho[i] && lista[i].ti <= reloj) {
                if (lista[i].ti >= max_ti) {
                    max_ti = lista[i].ti;
                    seleccionado = i;
                }
            }
        }

        if (seleccionado == -1) {
            reloj++;
            continue;
        }

        lista[seleccionado].tf = reloj + lista[seleccionado].t;
        lista[seleccionado].T = lista[seleccionado].tf - lista[seleccionado].ti;
        lista[seleccionado].E = (long long)lista[seleccionado].T * lista[seleccionado].t;
        lista[seleccionado].I = (double)lista[seleccionado].t / lista[seleccionado].T;

        sumaT += lista[seleccionado].T;
        sumaE += lista[seleccionado].E;
        sumaI += lista[seleccionado].I;

        reporte << lista[seleccionado].id << "\t" << lista[seleccionado].ti << "\t" << lista[seleccionado].t << "\t"
                << lista[seleccionado].tf << "\t" << lista[seleccionado].T << "\t" << lista[seleccionado].E << "\t" << lista[seleccionado].I << "\n";

        reloj = lista[seleccionado].tf;
        hecho[seleccionado] = true;
        completados++;
    }

    double promT = sumaT / n;
    reporte << "\nPROMEDIOS LIFO -> T: " << promT << " | E: " << sumaE/n << " | I: " << sumaI/n << "\n\n";
    return promT;
}

#endif
