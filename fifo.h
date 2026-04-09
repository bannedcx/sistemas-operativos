#ifndef FIFO_H
#define FIFO_H
#include <vector>
#include <fstream>
#include "Proceso.h"

using namespace std;

double ejecutarFIFO(vector<Actividad> lista, ofstream &reporte) {
    int reloj = 0;
    double sumaT = 0, sumaE = 0, sumaI = 0;

    reporte << "RESULTADOS DE FIFO\n";
    reporte << "ID\tti\tt\ttf\tT\tE\tI\n";

    //procesa exactamente en el orden del archivo
    for (int i = 0; i < lista.size(); i++) {
        if (reloj < lista[i].ti) {
            reloj = lista[i].ti; //se esper a que llegue el proceso
        }

        lista[i].tf = reloj + lista[i].t;
        lista[i].T = lista[i].tf - lista[i].ti;
        lista[i].E = (long long)lista[i].T * lista[i].t;
        lista[i].I = (double)lista[i].t / lista[i].T;

        sumaT += lista[i].T;
        sumaE += lista[i].E;
        sumaI += lista[i].I;

        reporte << lista[i].id << "\t" << lista[i].ti << "\t" << lista[i].t << "\t"
                << lista[i].tf << "\t" << lista[i].T << "\t" << lista[i].E << "\t" << lista[i].I << "\n";

        reloj = lista[i].tf;
    }

    double promT = sumaT / lista.size();
    reporte << "\nPROMEDIOS FIFO -> T: " << promT << " | E: " << sumaE/lista.size() << " | I: " << sumaI/lista.size() << "\n\n";
    return promT;
}

#endif
