#ifndef GRAFOS_AEROPUERTO_H
#define GRAFOS_AEROPUERTO_H



#include <string>

using namespace std;
class Aeropuerto {
protected:
    string ciudad;
    string codigo_aeropuerto;
    float latitud;
    float longitud;
public:
    //Constructores
    Aeropuerto();
    Aeropuerto(const string &ciudad, const string &codigoAeropuerto, float latitud, float longitud);

    //Getters y Setters
    const string &getCiudad() const;
    void setCiudad(const string &ciudad);
    const string &getCodigoAeropuerto() const;
    void setCodigoAeropuerto(const string &codigoAeropuerto);
    float getLatitud() const;
    void setLatitud(float latitud);
    float getLongitud() const;
    void setLongitud(float longitud);



};


#endif //GRAFOS_AEROPUERTO_H
