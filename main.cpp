#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Actividad {
    string id;
    int ti;
    int t;
    int tf;
    int T;
    long long E;
    double I;
};

int main() {
    ifstream archivoEntrada("programa.csv");
    
    if (!archivoEntrada.is_open()) {
        cout << "Fallo: No se encuentra programa.csv" << endl;
        return 1;
    }

    vector<Actividad> lista;
    string linea;

    getline(archivoEntrada, linea);

    while (getline(archivoEntrada, linea)) {
        if (linea.length() < 3) continue;

        Actividad act;
        int pos1 = linea.find(',');
        int pos2 = linea.rfind(',');

        act.id = linea.substr(0, pos1);
        act.ti = stoi(linea.substr(pos1 + 1, pos2 - pos1 - 1));
        act.t = stoi(linea.substr(pos2 + 1));

        lista.push_back(act);
    }
    archivoEntrada.close();

    //ordenamiento por orden de llegada ( ti )
    for (int i = 0; i < lista.size() - 1; i++) {
        for (int j = 0; j < lista.size() - i - 1; j++) {
            if (lista[j].ti > lista[j+1].ti) {
                Actividad temporal = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temporal;
            }
        }
    }

    ofstream reporte("resultados.txt");

    int reloj = 0;
    double sumaT = 0, sumaE = 0, sumaI = 0;

    reporte << "RESULTADOS FIFO\n";
    reporte << "ID\tti\tt\ttf\tT\tE\tI\n";

    for (int i = 0; i < lista.size(); i++) {
        if (reloj < lista[i].ti) {
            reloj = lista[i].ti;
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

    reporte << "\nPROMEDIOS:\n";
    reporte << "T: " << sumaT / lista.size() << "\n";
    reporte << "E: " << sumaE / lista.size() << "\n";
    reporte << "I: " << sumaI / lista.size() << "\n";

    reporte.close();
    cout << "Calculos hechos, estan en el txt." << endl;

    return 0;
}
