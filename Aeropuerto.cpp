#include "Aeropuerto.h"

const string &Aeropuerto::getCiudad() const {
    return ciudad;
}

void Aeropuerto::setCiudad(const string &ciudad) {
    Aeropuerto::ciudad = ciudad;
}

const string &Aeropuerto::getCodigoAeropuerto() const {
    return codigo_aeropuerto;
}

void Aeropuerto::setCodigoAeropuerto(const string &codigoAeropuerto) {
    codigo_aeropuerto = codigoAeropuerto;
}

float Aeropuerto::getLatitud() const {
    return latitud;
}

void Aeropuerto::setLatitud(float latitud) {
    Aeropuerto::latitud = latitud;
}

float Aeropuerto::getLongitud() const {
    return longitud;
}

void Aeropuerto::setLongitud(float longitud) {
    Aeropuerto::longitud = longitud;
}

Aeropuerto::Aeropuerto() {}

Aeropuerto::Aeropuerto(const string &ciudad, const string &codigoAeropuerto, float latitud, float longitud) : ciudad(
        ciudad), codigo_aeropuerto(codigoAeropuerto), latitud(latitud), longitud(longitud) {}



