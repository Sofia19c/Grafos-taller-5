#ifndef GRAFOS_GRAFO_H
#define GRAFOS_GRAFO_H

#include "Arista.h"
#include "Vertice.h"
#include "Aeropuerto.h"
#include "Vuelo.h"

#include <string>
#include <vector>



using namespace std;

template <typename T, typename O> class Grafo {
protected:
  std::vector<Vertice<T>> listaVertices;
  vector<Arista<O>> listaAristas;

public:
  // Constructr
  Grafo();
  Grafo(vector<T> listaVertices, vector<O> listaAristas);

  // Funciones vertice y arista
  void agregarVertice(string ciudad, string codigo_aeropuerto, float latitud,
                      float longitud);
  void eliminarVertice(string id);

  void agregarArista(string aeropuertoI, string aeropuertoJ, float tiempoProm,
                     float precio, int cantVuelos);
  void eliminarArista(string idI, string idJ);

  vector<Vertice<T>> obtenerVertices() { return listaVertices; }

  void ruta_corta_distancia(const string &origen, const string &destino) const;
   
  double calcularDistancia(int x1, int y1, int x2, int y2) const;

  vector<Arista<O>> obtenerAristas();
  vector<Vertice<T>> obtenerVertices();


};

#endif // GRAFOS_GRAFO_H
