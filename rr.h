#ifndef RR_H
#define RR_H
#include <vector>
#include <fstream>
#include "Proceso.h"

using namespace std;

double ejecutarRR(vector<Actividad> lista, int quantum, ofstream &reporte) {
    int n = lista.size();
    
    int reloj = lista[0].ti;
    for(int i = 1; i < n; i++) {
        if(lista[i].ti < reloj) reloj = lista[i].ti;
    }

    vector<int> cola;
    vector<bool> en_cola(n, false);
    vector<bool> completado(n, false);
    int completados = 0;
    double sumaT = 0, sumaE = 0, sumaI = 0;

    auto meter_llegadas = [&]() {
        for (int i = 0; i < n; i++) {
            if (!en_cola[i] && !completado[i] && lista[i].ti <= reloj) {
                cola.push_back(i);
                en_cola[i] = true;
            }
        }
    };

    meter_llegadas();

    reporte << "RESULTADOS DE ROUND ROBIN(Q=" << quantum << ") ---\n";
    reporte << "ID\tti\tt\ttf\tT\tE\tI\n";

    while (completados < n) {
        if (cola.empty()) {
            reloj++;
            meter_llegadas();
            continue;
        }

        int actual = cola[0];
        cola.erase(cola.begin());

        int ejecucion = lista[actual].t_restante;
        if (ejecucion > quantum) {
            ejecucion = quantum;
        }

        for(int t = 0; t < ejecucion; t++) {
            reloj++;
            meter_llegadas();
        }

        lista[actual].t_restante -= ejecucion;

        if (lista[actual].t_restante > 0) {
            cola.push_back(actual);
        } else {
            lista[actual].tf = reloj;
            lista[actual].T = lista[actual].tf - lista[actual].ti;
            lista[actual].E = (long long)lista[actual].T * lista[actual].t;
            lista[actual].I = (double)lista[actual].t / lista[actual].T;

            sumaT += lista[actual].T;
            sumaE += lista[actual].E;
            sumaI += lista[actual].I;

            reporte << lista[actual].id << "\t" << lista[actual].ti << "\t" << lista[actual].t << "\t"
                    << lista[actual].tf << "\t" << lista[actual].T << "\t" << lista[actual].E << "\t" << lista[actual].I << "\n";
            
            completado[actual] = true;
            completados++;
        }
    }

    double promT = sumaT / n;
    reporte << "\nPROMEDIOS RR -> T: " << promT << " | E: " << sumaE/n << " | I: " << sumaI/n << "\n\n";
    return promT;
}

#endif
