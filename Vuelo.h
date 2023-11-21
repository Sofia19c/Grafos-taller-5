#ifndef GRAFOS_VUELO_H
#define GRAFOS_VUELO_H


#include <string>

using namespace std;
class Vuelo {
protected:
    string aeropuertoI;
    string aeropuertoJ;
    float tiempoProm;
    float precio;
    int cantVuelos;

public:
    //Constructor
    Vuelo();
    Vuelo(string &aeropuertoI, string &aeropuertoJ, float tiempoProm, float precio, int cantVuelos);

    //Getters y Setters
    const string &getAeropuertoI() const;
    void setAeropuertoI(const string &aeropuertoI);
    const string &getAeropuertoJ() const;
    void setAeropuertoJ(const string &aeropuertoJ);
    float getTiempoProm() const;
    void setTiempoProm(float tiempoProm);
    float getPrecio() const;
    void setPrecio(float precio);
    int getCantVuelos() const;
    void setCantVuelos(int cantVuelos);

};


#endif //GRAFOS_VUELO_H
