#ifndef PROCESO_H
#define PROCESO_H
#include <string>

using namespace std;

struct Actividad {
    string id;
    int ti;
    int t;
    int t_restante;
    int tf;
    int T;
    long long E;
    double I;
};

#endif
