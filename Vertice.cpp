#include "Vertice.h"

template<typename T>
T Vertice<T>::getDato() const {
    return dato;
}

template<typename T>
void Vertice<T>::setDato(T dato) {
    Vertice::dato = dato;
}

template<typename T>
Vertice<T>::Vertice(string ciudad, string codigo_aeropuerto, float latitud, float longitud) {
    Aeropuerto aeropuerto(ciudad,codigo_aeropuerto,latitud,longitud);
    dato = aeropuerto;
}

template<typename T>
Vertice<T>::Vertice() {}
