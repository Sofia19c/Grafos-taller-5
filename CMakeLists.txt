cmake_minimum_required(VERSION 3.23)
project(Grafos)

set(CMAKE_CXX_STANDARD 14)

add_executable(Grafos main.cpp Grafo.cpp Grafo.h Vertice.cpp Vertice.h Arista.cpp Arista.h Vuelo.cpp Vuelo.h Aeropuerto.cpp Aeropuerto.h)

