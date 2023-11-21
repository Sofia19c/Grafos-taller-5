#include <iostream>
#include <fstream>
#include <sstream>

#include "Grafo.h"

void cargarDatosVuelo(string nombreArchivo, Grafo<Aeropuerto, Vuelo>& grafo);
void cargarDatosAeropuertos(string nombreArchivo, Grafo<Aeropuerto, Vuelo>& grafo);
void mostrarRutaCorta(const Grafo<Aeropuerto, Vuelo>& grafo);
void mostrarRutaRapida(Grafo<Aeropuerto, Vuelo>& grafo);


int main() {
    Grafo<Aeropuerto, Vuelo> grafo;

    cargarDatosAeropuertos("aeropuertos.csv",grafo);
    cargarDatosVuelo("vuelos.csv", grafo);

    int opcion;
    do {
        cout << "Seleccione una opcion:" << endl;
        cout << "1. Ruta mas corta en distancia" << endl;
        cout << "2. Ruta mas rapida" << endl;
        cout << "0- Salir" <<endl;
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            mostrarRutaCorta(grafo);
            break;

        case 2:
            mostrarRutaRapida(grafo);
            cout << "Ruta mas rapida" << endl;
            break;

        case 0:
            cout<< "Saliendo..."<<endl;
            break;    
        
        default:
            cout << "Opcion invalida. Intente de nuevo" << endl;
            break;
        }
    } while (opcion != 0);

    return 0;
}

void cargarDatosAeropuertos(string nombreArchivo, Grafo<Aeropuerto, Vuelo>& grafo){
    ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            istringstream ss(linea);
            string ciudad, codigo_aeropuerto, slatitud, slongitud;

            getline(ss, ciudad, ',');
            getline(ss, codigo_aeropuerto, ',');
            getline(ss, slatitud, ',');
            getline(ss, slongitud, ',');

            float latitud = stof(slatitud);
            float longitud = stof(slongitud);

            grafo.agregarVertice(ciudad, codigo_aeropuerto, latitud, longitud);
        }
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << std::endl;
    }
}

void cargarDatosVuelo(string nombreArchivo, Grafo<Aeropuerto, Vuelo>& grafo){
    ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        string linea;
        int contador = 0;
        while (getline(archivo, linea)) {
            contador++;
            istringstream ss(linea);
            string codAeropuertoI, codAeropuertoJ, stiempoProm, sprecio, scantVuelos;

            getline(ss, codAeropuertoI, ',');
            getline(ss, codAeropuertoJ, ',');
            getline(ss, stiempoProm, ',');
            getline(ss, sprecio, ',');
            getline(ss, scantVuelos, ',');

            if (contador < 10)
            {
                //cout<<"que imprimes "<<codAeropuertoI<<" "<<codAeropuertoJ<<" "<<stiempoProm<<endl;
            }
            
            
            float tiempoProm = stof(stiempoProm);
            float precio = stof(sprecio);
            int cantVuelos = stoi(scantVuelos);

            
            if (contador < 10)
            {
                //cout<<"que impreso "<<codAeropuertoI<<" "<<codAeropuertoJ<<" "<<tiempoProm<<endl;
            }

            grafo.agregarArista(codAeropuertoI, codAeropuertoJ, tiempoProm, precio, cantVuelos);
        }
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << std::endl;
    }
}


void mostrarRutaCorta(const Grafo<Aeropuerto, Vuelo>& grafo) {
    std::string origen, destino;
    std::cout << "Ingrese el aeropuerto de origen: ";
    std::cin >> origen;
    std::cout << "Ingrese el aeropuerto de destino: ";
    std::cin >> destino;

    grafo.ruta_corta_distancia(origen, destino);
}

void mostrarRutaRapida(Grafo<Aeropuerto, Vuelo>& grafo){
    pair<vector<int>, float> camino = grafo.caminoMasRapido("ABI", "DFW");

    cout<<"Costo del camino: "<<camino.second<<endl;

    for (int i = 0; i < camino.first.size(); i++)
    {
        cout<<" ";
        cout<<camino.first[i];
    }
    
}