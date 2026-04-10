#ifndef LIFO_H
#define LIFO_H
#include <vector>
#include <fstream>
#include <iomanip>
#include "Proceso.h"

using namespace std;

void ejecutarLIFO(vector<Actividad> lista, ofstream &reporte, double &out_pT, double &out_pE) {
    int n = lista.size(), reloj = 0, completados = 0;
    vector<bool> hecho(n, false);
    double sumaT = 0, sumaI = 0; 
    long long sumaE = 0;

    reporte << "\nALGORITMO LIFO\n";
    reporte << left << setw(6) << "ID" << "| ti | t  | tf | T  | " << setw(12) << "E" << " | I\n";

    while (completados < n) {
        int seleccionado = -1;

        for (int i = 0; i < n; i++) {
            if (!hecho[i] && lista[i].ti <= reloj) {
                if (seleccionado == -1 || lista[i].ti > lista[seleccionado].ti) {
                    seleccionado = i;
                }
            }
        }

        if (seleccionado == -1) { reloj++; continue; }

        reloj += lista[seleccionado].t;
        lista[seleccionado].tf = reloj;
        lista[seleccionado].T = lista[seleccionado].tf - lista[seleccionado].ti;
        lista[seleccionado].E = (long long)lista[seleccionado].T * lista[seleccionado].t;
        lista[seleccionado].I = (double)lista[seleccionado].t / lista[seleccionado].T;

        sumaT += lista[seleccionado].T;
        sumaE += lista[seleccionado].E;
        sumaI += lista[seleccionado].I;

        reporte << left << setw(6) << lista[seleccionado].id << "| " << setw(2) << right << lista[seleccionado].ti << " | " << setw(2) << left << lista[seleccionado].t << " | " << setw(2) << lista[seleccionado].tf << " | " << setw(2) << lista[seleccionado].T << " | " << setw(12) << lista[seleccionado].E << "| " << fixed << setprecision(4) << lista[seleccionado].I << "\n";

        hecho[seleccionado] = true;
        completados++;
    }

    out_pT = sumaT / n;
    out_pE = (double)sumaE / n;

    reporte << "Promedios -> T: " << out_pT << " | E: " << out_pE << " | I: " << sumaI/n << "\n";
}
#endif
