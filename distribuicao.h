#ifndef DISTRIBUICAO_H
#define DISTRIBUICAO_H

#include "grafo.h"

typedef struct estadoCarga{
    float recebido;
    int estado;
}EstadoCarga;

/*
estado

0 -> sem energia
1 -> parcialmente alimentado
2 -> totalmente alimentado
*/

void reiniciarFluxos(Grafo *g);

void distribuirCargaBFS(Grafo *g, char origem[]);

void distribuirCargaDFS(Grafo *g, char origem[]);

void mostrarEstadoCarga(Grafo *g);

#endif