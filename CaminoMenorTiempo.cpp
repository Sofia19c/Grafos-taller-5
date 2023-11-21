#include "CaminoMenorTiempo.h"
#include <iostream>

pair<vector<int>, float> calculoCaminoMasRapido (Grafo<Aeropuerto,Vuelo> *grafo, int nodoOrigen, int nodoDestino){
    pair<vector<float>, vector<int>> tabla = dijkstra(grafo, nodoOrigen);

    /*for (int i = 0; i < tabla.first.size(); i++)
    {
        cout<<tabla.first[i]<<"-"<<tabla.second[i]<<endl;
    } */
    

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
    
    //cout<<"Este es el nodo origen"<<nodoOrigen<<endl;
    for(int i = 0; i < 10 ; i++){  //TO BE listaAeropuertos.size()-1
        int siguiente = distanciaMinima (dist, visitados);
        cout<<"uwu"<<siguiente<<endl;
        if(siguiente != -1){
            //cout<<"if"<<endl;
            visitados[siguiente] = true;
            vector<pair<int,Vuelo>> adyacentes = aeropuertosAdyacentes(listaVuelos, listaAeropuertos, siguiente);
            for(int j = 0; j < adyacentes.size(); j++){
                cout<<"impreso"<<adyacentes[j].first<<endl;
                if(dist[siguiente] + adyacentes[j].second.getTiempoProm() < dist[obtenerDestino(listaAeropuertos, adyacentes[j].second)]){
                    cout<<"tiempo arista"<<adyacentes[j].second.getTiempoProm()<<"tiempo predesesor"<<dist[siguiente]<<endl;

                    dist[adyacentes[j].first] = dist[siguiente] + adyacentes[j].second.getTiempoProm();

                    predecesor[adyacentes[j].first] = siguiente;
                }
            }
        }
    }
        
    //3. Se comprueba si utilizando como punto intermedio el ultimo vertice fijado se llega a nuevos vertices o se encuentra un camino mas corto a los que ya hemos accedido
    //4. Con la informacion anterior , se actualizan , si procede las distancias minimas desde el inicial a cada uno de estos
    //5. Volvemos al paso 2 hasta que todos los vertices esten fijados
    return make_pair(dist, predecesor);
}

vector<pair<int,Vuelo>> aeropuertosAdyacentes (vector<Arista<Vuelo>> listaVuelos , vector<Vertice<Aeropuerto>> listaAeropuertos, int verticeActual){
    
    vector<pair<int,Vuelo>> aeropuertos;

    for (int i = 0; i < listaVuelos.size(); i++)
    {
        if (listaVuelos[i].getDato().getAeropuertoI() ==  listaAeropuertos[verticeActual].getDato().getCodigoAeropuerto())
        {
            //cout<<"aeropuerto"<<listaVuelos[i].getDato().getAeropuertoI()<<endl;
            string aeropuertoDestino = listaVuelos[i].getDato().getAeropuertoJ();

            for (int j = 0; j < listaAeropuertos.size(); j++)
            {
                if(listaAeropuertos[j].getDato().getCodigoAeropuerto() == aeropuertoDestino){
                    aeropuertos.push_back(make_pair(j, listaVuelos[i].getDato()));
                }
            }
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