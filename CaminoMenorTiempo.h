#pragma once

#include "Grafo.h"
#include <algorithm>
#include <limits>

pair<vector<int>, float> caminoMasRapido (Grafo<Aeropuerto,Vuelo>& grafo, int nodoOrigen, int nodoDestino);

//necesito: necesito los vertices , las aristas y el peso de las aristas
//nodo de origen
pair<vector<float>, vector<int>> dijkstra (Grafo<Aeropuerto,Vuelo>& grafo, int nodoOrigen);

vector<int> aeropuertosAdyacentes (vector<Arista<Vuelo>> listaVuelos , vector<Vertice<Aeropuerto>> listaAeropuertos, int verticeActual);

int distanciaMinima(vector<float> distance, vector<bool> visitados);

int obtenerDestino(vector<Vertice<Aeropuerto>> listaAeropuertos, Vuelo vuelo);