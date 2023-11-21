#include "CaminoMenorTiempo.h"

pair<vector<int>, float> calculoCaminoMasRapido (Grafo<Aeropuerto,Vuelo> *grafo, int nodoOrigen, int nodoDestino){
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
pair<vector<float>, vector<int>> dijkstra (Grafo<Aeropuerto,Vuelo> *grafo, int nodoOrigen){
    vector<Arista<Vuelo>> listaVuelos = grafo->obtenerAristas();
    vector<Vertice<Aeropuerto>> listaAeropuertos = grafo->obtenerVertices();
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