#include "Grafo.h"
#include "CaminoMenorTiempo.h"

#include <iostream>
#include <utility>
#include <unordered_map>
#include <queue>
#include <limits>
#include <algorithm>
#include <cmath>


template<typename T, typename O>
Grafo<T, O>::Grafo() {}

/*
template<typename T, typename O>
Grafo<T, O>::Grafo(vector<T> listaVertices, vector<O> listaAristas) {
    this->listaVertices = listaVertices;
    this->listaAristas = listaAristas;
}
*/


template<typename T, typename O>
void Grafo<T, O>::agregarVertice(string ciudad, string codigo_aeropuerto, float latitud, float longitud) {

    Vertice<T> vertice(move(ciudad), move(codigo_aeropuerto), latitud, longitud);

    bool existe = false;
    for(auto it = listaVertices.begin(); it!=listaVertices.end();it++){
        if(it ->getDato().getCodigoAeropuerto() == vertice.getDato().getCodigoAeropuerto()){
            existe = true;
            cout<<"El aeropuerto ya existe"<<endl;
            break;
        }
    }
    if(!existe){
        listaVertices.push_back(vertice);

    }
}

template<typename T, typename O>
void Grafo<T, O>::eliminarVertice(std::string id) {
    for(auto it = listaVertices.begin(); it!=listaVertices.end();it++){
        if(it ->getDato().getCodigoAeropuerto() == id){
            listaVertices.erase(it);
            cout<<"Se elimino el aeropuerto"<<endl;
            break;
        }
    }
}

template<typename T, typename O>
void Grafo<T, O>::agregarArista(string aeropuertoI,string aeropuertoJ, float tiempoProm, float precio, int cantVuelos) {
    Arista<O> arista(aeropuertoI, aeropuertoJ, tiempoProm, precio, cantVuelos);

    bool encontrado = false;
    bool existeI = false;
    bool existeJ = false;

    for(auto it = listaAristas.begin(); it != listaAristas.end();it++){
        if(it->getDato().getAeropuertoI()==arista.getDato().getAeropuertoI() &&
                it->getDato().getAeropuertoJ()==arista.getDato().getAeropuertoJ()){
            encontrado = true;
            cout<<"Este vuelo ya existe"<<endl;
            break;
        }
    }

    if(!encontrado){
        for(auto it = listaVertices.begin(); it != listaVertices.end(); it++){
            if(it->getDato().getCodigoAeropuerto() == aeropuertoI){
                existeI = true;
            }
            if(it->getDato().getCodigoAeropuerto() == aeropuertoJ){
                existeJ = true;
            }
        }
        if(!existeI){
            cout<<"El aeropuerto de salida no existe"<<endl;
        }else if(!existeJ){
            cout<<"El aeropuerto de llegada no existe"<<endl;
        }else{
            listaAristas.push_back(arista);
        }
    }
}

template<typename T, typename O>
void Grafo<T, O>::eliminarArista(string idI, string idJ) {

    for(auto it = listaAristas.begin(); it != listaAristas.end();it++){
        if(it->getDato().getAeropuertoI()==idI && it->getDato().getAeropuertoJ()==idJ){
            listaAristas.erase(it);
            cout<<"Se elimino el vuelo"<<endl;
            break;
        }
    }
}


// Método ruta_corta_distancia para encontrar la ruta más corta en términos de distancia
template <typename T, typename O>
void Grafo<T, O>::ruta_corta_distancia(const string &origen, const string &destino) const {
    // Lógica para encontrar el camino más corto basado en la distancia geográfica
    unordered_map<string, vector<Aeropuerto>> aeropuertos;

    // Encontrar todos los aeropuertos relacionados con el origen
    for (const auto &vertice : listaVertices) {
        if (vertice.getDato().getCiudad() == origen) {
            aeropuertos[origen].push_back(vertice.getDato());
        }
    }

    // Encontrar todos los aeropuertos relacionados con el destino
    for (const auto &vertice : listaVertices) {
        if (vertice.getDato().getCiudad() == destino) {
            aeropuertos[destino].push_back(vertice.getDato());
        }
    }

    // Encontrar la combinación más corta entre los aeropuertos de origen y destino
    double menorDistancia = std::numeric_limits<double>::max();
    Aeropuerto mejorOrigen;
    Aeropuerto mejorDestino;

    for (const auto &orig : aeropuertos[origen]) {
        for (const auto &dest : aeropuertos[destino]) {
            double distancia = calcularDistancia(orig.getLatitud(), orig.getLongitud(), dest.getLatitud(), dest.getLongitud());
            if (distancia < menorDistancia) {
                menorDistancia = distancia;
                mejorOrigen = orig;
                mejorDestino = dest;
            }
        }
    }

    // Imprimir la ruta más corta encontrada
    std::cout << "El camino más corto en términos de distancia es: " << mejorOrigen.getCodigoAeropuerto()
              << " -> " << mejorDestino.getCodigoAeropuerto() << std::endl;
}

template <typename T, typename O>
double Grafo<T, O>::calcularDistancia(int x1, int y1, int x2, int y2) const {
    double distancia = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    return distancia;
}

template<typename T, typename O>
vector<Arista<O>> Grafo<T,O>::obtenerAristas(){
    return this->listaAristas;
}

template<typename T, typename O>
vector<Vertice<T>> Grafo<T,O>::obtenerVertices(){
    return this->listaVertices;
}


pair<vector<int>, float> Grafo<Aeropuerto, Vuelo>::caminoMasRapido (int nodoOrigen, int nodoDestino){
    return calculoCaminoMasRapido(this, nodoOrigen, nodoDestino);
}

template class Grafo<Aeropuerto,Vuelo>;