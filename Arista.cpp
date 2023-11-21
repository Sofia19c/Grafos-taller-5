#include "Arista.h"

template<typename T>
T Arista<T>::getDato() const {
    return dato;
}

template<typename T>
void Arista<T>::setDato(T dato) {
    this->dato = dato;
}

template<typename T>
Arista<T>::Arista(string &aeropuertoI, string &aeropuertoJ, float tiempoProm, float precio, int cantVuelos) {
    Vuelo vuelo(aeropuertoI, aeropuertoJ, tiempoProm, precio, cantVuelos);
    dato = vuelo;

}

template class Arista<Vuelo>;