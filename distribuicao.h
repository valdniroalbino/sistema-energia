#ifndef DISTRIBUICAO_H
#define DISTRIBUICAO_H

#include "grafo.h"




#define MAX 1000

/* Funções de gestão da distribuição */
void reiniciarFluxos(Grafo *g);

void distribuirCargaBFS(Grafo *g, char origem[]);

void distribuirCargaDFS(Grafo *g, char origem[]);


#endif