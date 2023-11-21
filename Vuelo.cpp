#include "Vuelo.h"

const string &Vuelo::getAeropuertoI() const {
    return aeropuertoI;
}

void Vuelo::setAeropuertoI(const string &aeropuertoI) {
    Vuelo::aeropuertoI = aeropuertoI;
}

const string &Vuelo::getAeropuertoJ() const {
    return aeropuertoJ;
}

void Vuelo::setAeropuertoJ(const string &aeropuertoJ) {
    Vuelo::aeropuertoJ = aeropuertoJ;
}

float Vuelo::getTiempoProm() const {
    return tiempoProm;
}

void Vuelo::setTiempoProm(float tiempoProm) {
    Vuelo::tiempoProm = tiempoProm;
}

float Vuelo::getPrecio() const {
    return precio;
}

void Vuelo::setPrecio(float precio) {
    Vuelo::precio = precio;
}

int Vuelo::getCantVuelos() const {
    return cantVuelos;
}

void Vuelo::setCantVuelos(int cantVuelos) {
    Vuelo::cantVuelos = cantVuelos;
}


Vuelo::Vuelo() {}

Vuelo::Vuelo(string &aeropuertoI, string &aeropuertoJ, float tiempoProm, float precio, int cantVuelos)
        : aeropuertoI(aeropuertoI), aeropuertoJ(aeropuertoJ), tiempoProm(tiempoProm), precio(precio),
          cantVuelos(cantVuelos) {}
