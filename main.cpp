#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include "Proceso.h"
#include "Fifo.h"
#include "Lifo.h"
#include "Rr.h"

using namespace std;
using namespace std::chrono;

int main() {
    int quantum;
    cout << "Ingrese el Quantum para Round Robin: ";
    if (!(cin >> quantum)) { cout << "Quantum invalido.\n"; return 1; }

    ifstream archivo("programa.csv");

    vector<Actividad> lista_original;
    string linea;
    bool primeraLinea = true;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string id_val, ti_val, t_val;

        if (getline(ss, id_val, ',') && getline(ss, ti_val, ',') && getline(ss, t_val)) {
            if (primeraLinea && (ti_val.find_first_not_of("0123456789") != string::npos)) {
                primeraLinea = false;
                continue;
            }
            Actividad act;
            act.id = id_val;
            act.ti = stoi(ti_val);
            act.t = stoi(t_val);
            act.t_restante = act.t;
            lista_original.push_back(act);
        }
        primeraLinea = false;
    }
    archivo.close();

    ofstream reporte("resultados.txt");

    double pt_fifo, pe_fifo;
    double pt_lifo, pe_lifo;
    double pt_rr, pe_rr;

    auto s1 = high_resolution_clock::now();
    ejecutarFIFO(lista_original, reporte, pt_fifo, pe_fifo);
    double ms_fifo = duration_cast<microseconds>(high_resolution_clock::now() - s1).count() / 1000.0;

    auto s2 = high_resolution_clock::now();
    ejecutarLIFO(lista_original, reporte, pt_lifo, pe_lifo);
    double ms_lifo = duration_cast<microseconds>(high_resolution_clock::now() - s2).count() / 1000.0;

    auto s3 = high_resolution_clock::now();
    ejecutarRR(lista_original, quantum, reporte, pt_rr, pe_rr);
    double ms_rr = duration_cast<microseconds>(high_resolution_clock::now() - s3).count() / 1000.0;

    reporte << "\nTIEMPOS DE EJECUCION\n";
    reporte << "FIFO: " << ms_fifo << " ms\n";
    reporte << "LIFO: " << ms_lifo << " ms\n";
    reporte << "Round Robin: " << ms_rr << " ms\n";

    reporte << "\nCOMPARACION DE PROMEDIOS\n";
    reporte << "- FIFO        -> Promedio T: " << pt_fifo << " | Promedio E: " << pe_fifo << "\n";
    reporte << "- LIFO        -> Promedio T: " << pt_lifo << " | Promedio E: " << pe_lifo << "\n";
    reporte << "- ROUND ROBIN -> Promedio T: " << pt_rr   << " | Promedio E: " << pe_rr << "\n";

    double min_pt = min({pt_fifo, pt_lifo, pt_rr});
    string ganador = (min_pt == pt_fifo) ? "FIFO" : (min_pt == pt_lifo) ? "LIFO" : "ROUND ROBIN";

    reporte << "\nEl algoritmo mas optimo es " << ganador << " (menor pT)\n";

    reporte.close();
    cout << "calculos en el txt" << endl;

    return 0;
}
