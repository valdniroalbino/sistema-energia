#ifndef DISTRIBUICAO_H
#define DISTRIBUICAO_H

#include "grafo.h"


#define MAX 1000


void reiniciarFluxos(Grafo *g);

void distribuirCargaBFS(Grafo *g, char origem[]);

void distribuirCargaDFS(Grafo *g, char origem[]);


/* Relatório da distribuição */
void mostrarEstadoCarga(Grafo *g);


#endif