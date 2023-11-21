#ifndef GRAFOS_VERTICE_H
#define GRAFOS_VERTICE_H

#include <string>
#include "Aeropuerto.h"

using namespace std;
template<typename T>
class Vertice {
protected:
    T dato;
public:
    //Constructores
    Vertice();
    Vertice(string ciudad, string codigo_aeropuerto, float latitud, float longitud);


    //Setters y Getter
    T getDato() const;
    void setDato(T dato);


};

#endif //GRAFOS_VERTICE_H
