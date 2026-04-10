#ifndef RR_H
#define RR_H
#include <vector>
#include <fstream>
#include <iomanip>
#include <queue>
#include "Proceso.h"

using namespace std;

void ejecutarRR(vector<Actividad> lista, int Q, ofstream &reporte, double &out_pT, double &out_pE) {
    int n = lista.size(), reloj = 0, completados = 0;
    queue<int> cola_ready;
    vector<bool> en_cola(n, false), completado(n, false);
    double sumaT = 0, sumaI = 0; 
    long long sumaE = 0;

    reporte << "\nALGORITMO ROUND ROBIN (Q=" << Q << ")\n";
    reporte << left << setw(6) << "ID" << "| ti | t  | tf | T  | " << setw(12) << "E" << " | I\n";

    auto revisar_llegadas = [&]() {
        for (int i = 0; i < n; i++) {
            if (!completado[i] && !en_cola[i] && lista[i].ti <= reloj) {
                cola_ready.push(i);
                en_cola[i] = true;
            }
        }
    };

    revisar_llegadas();

    while (completados < n) {
        if (cola_ready.empty()) { reloj++; revisar_llegadas(); continue; }

        int idx = cola_ready.front();
        cola_ready.pop();

        int t_ejec = min(Q, lista[idx].t_restante);
        for(int i = 0; i < t_ejec; i++) { 
            reloj++; 
            revisar_llegadas(); 
        }
        lista[idx].t_restante -= t_ejec;

        if (lista[idx].t_restante == 0) {
            lista[idx].tf = reloj;
            lista[idx].T = lista[idx].tf - lista[idx].ti;
            lista[idx].E = (long long)lista[idx].T * lista[idx].t;
            lista[idx].I = (double)lista[idx].t / lista[idx].T;

            sumaT += lista[idx].T;
            sumaE += lista[idx].E;
            sumaI += lista[idx].I;

            reporte << left << setw(6) << lista[idx].id << "| " << setw(2) << right << lista[idx].ti << " | " << setw(2) << left << lista[idx].t << " | " << setw(2) << lista[idx].tf << " | " << setw(2) << lista[idx].T << " | " << setw(12) << lista[idx].E << "| " << fixed << setprecision(4) << lista[idx].I << "\n";

            completado[idx] = true;
            completados++;
        } else {
            revisar_llegadas();
            cola_ready.push(idx); 
        }
    }

    out_pT = sumaT / n;
    out_pE = (double)sumaE / n;

    reporte << "Promedios -> T: " << out_pT << " | E: " << out_pE << " | I: " << sumaI/n << "\n\n";
}
#endif
