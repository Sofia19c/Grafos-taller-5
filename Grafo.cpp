#include "Grafo.h"

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


pair<vector<int>, float> caminoMasRapido (Grafo<Aeropuerto,Vuelo>& grafo, int nodoOrigen, int nodoDestino){
    pair<vector<float>, vector<int>> tabla = dijkstra(grafo, nodoOrigen);
    vector<float> dist = tabla.first;
    vector<int> predecesores = tabla.second;
    vector<int> camino;
    bool termino = false;
    int nodoActual = nodoDestino;

    while (!termino)
    {
        camino.push_back(nodoActual);
        nodoActual = predecesores[nodoActual];
        if (nodoActual == -1){
            termino = true;
        }
    }
    reverse(camino.begin(), camino.end());
    return make_pair(camino, dist[nodoDestino]);
}

//necesito: necesito los vertices , las aristas y el peso de las aristas
//nodo de origen
pair<vector<float>, vector<int>> dijkstra (Grafo<Aeropuerto,Vuelo>& grafo, int nodoOrigen){
    vector<Arista<Vuelo>> listaVuelos = grafo.obtenerAristas();
    vector<Vertice<Aeropuerto>> listaAeropuertos = grafo.obtenerVertices();
    vector<float> dist(listaAeropuertos.size(),numeric_limits<float>::infinity());
    vector<bool> visitados(listaAeropuertos.size(), false);
    vector<int> predecesor(listaAeropuertos.size(),-1);
    //1.1 Se asigna un vertice inicial (vertice de origen en este caso el aeropuerto desde donde inicio la ruta) 
    dist[nodoOrigen] = 0;
    //1.2 se calcula cual es el aeropuerto más proximo
    //1.2.1. Escribir todos los vuelos que salen del aeropuerto de origen
    //1.2.1.1. Encuentro el aeropuerto de origen en la lista de vuelo
    //1.2.1.2 Guardo el vuelo
    //1.2.1.3. Repite desde el 1 hasta que no hayan más aeropuertos
    //1.2.2 Encontrar el vuelo de menor tiempo
    //1.2.3 Escoger el aeropuerto con menor tiempo de vuelo
    
    //2. Se fija el vertice no fijado aun que esta a una menor distancia del inicial
    
    for(int i = 0; i < listaAeropuertos.size() - 1; i++){
        int siguiente = distanciaMinima (dist, visitados);
        if(siguiente != -1){
            visitados[siguiente] = true;
            vector<int> adyacentes = aeropuertosAdyacentes(listaVuelos, listaAeropuertos, siguiente);
            for(int j = 0; j < adyacentes.size(); j++){
                if(dist[siguiente] + listaVuelos[adyacentes[j]].getDato().getTiempoProm() < dist[obtenerDestino(listaAeropuertos, listaVuelos[adyacentes[j]].getDato())]){

                    dist[adyacentes[j]] = dist[siguiente] + listaVuelos[adyacentes[j]].getDato().getTiempoProm();

                    predecesor[adyacentes[j]] = siguiente;
                }
            }
        }
    }
        
    //3. Se comprueba si utilizando como punto intermedio el ultimo vertice fijado se llega a nuevos vertices o se encuentra un camino mas corto a los que ya hemos accedido
    //4. Con la informacion anterior , se actualizan , si procede las distancias minimas desde el inicial a cada uno de estos
    //5. Volvemos al paso 2 hasta que todos los vertices esten fijados
    return make_pair(dist, predecesor);
}

vector<int> aeropuertosAdyacentes (vector<Arista<Vuelo>> listaVuelos , vector<Vertice<Aeropuerto>> listaAeropuertos, int verticeActual){
    
    vector<int> aeropuertos;

    for (int i = 0; i < listaVuelos.size(); i++)
    {
        if (listaVuelos[i].getDato().getAeropuertoI() ==  listaAeropuertos[verticeActual].getDato().getCodigoAeropuerto())
        {
            aeropuertos.push_back(i);
        }    
    }
    return aeropuertos;
}

int distanciaMinima(vector<float> distance, vector<bool> visitados){
    int destino = -1;
    float tiempo = numeric_limits<float>::infinity();

    for (int i = 0; i < distance.size(); i++)
    {
        if(visitados[i] == false && distance[i] < tiempo){
            tiempo = distance[i];
            destino = i;
        }
    }
    return destino;
}

int obtenerDestino(vector<Vertice<Aeropuerto>> listaAeropuertos, Vuelo vuelo){
    string codigoAeropuerto = vuelo.getAeropuertoI();

    for ( int i = 0; i < listaAeropuertos.size(); i++)
    {
        if(listaAeropuertos[i].getDato().getCodigoAeropuerto() == codigoAeropuerto){
            return i;
        }
    }
    return -1;
}

template class Grafo<Aeropuerto,Vuelo>;