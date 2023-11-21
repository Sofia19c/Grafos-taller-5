#ifndef GRAFOS_ARISTA_H
#define GRAFOS_ARISTA_H

#include <string>
#include "Vuelo.h"

using namespace std;
template <typename T>
class Arista {
protected:
    T dato;
public:
    //Constructor
    Arista(string &aeropuertoI, string &aeropuertoJ, float tiempoProm, float precio, int cantVuelos);

    //Getters y setters
    T getDato() const;
    void setDato(T dato);
};


#endif //GRAFOS_ARISTA_H
