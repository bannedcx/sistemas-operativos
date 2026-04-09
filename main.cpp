#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>

#include "Proceso.h"
#include "Fifo.h"
#include "Lifo.h"
#include "Rr.h"

using namespace std;

int main() {
    int quantum;
    cout << "Ingrese el Quantum para Round Robin: ";
    cin >> quantum;

    ifstream archivo("programa.csv");

    vector<Actividad> lista_original;
    string linea;
    
    getline(archivo, linea);

    while (getline(archivo, linea)) {
        if (linea.length() < 3) continue;

        Actividad act;
        int pos1 = linea.find(',');
        int pos2 = linea.rfind(',');

        act.id = linea.substr(0, pos1);
        act.ti = stoi(linea.substr(pos1 + 1, pos2 - pos1 - 1));
        act.t = stoi(linea.substr(pos2 + 1));
        act.t_restante = act.t;

        lista_original.push_back(act);
    }
    archivo.close();

    ofstream reporte("resultados.txt");

    vector<Actividad> lista_fifo = lista_original;
    vector<Actividad> lista_lifo = lista_original;
    vector<Actividad> lista_rr = lista_original;
