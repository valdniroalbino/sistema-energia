#ifndef DISTRIBUICAO_H
#define DISTRIBUICAO_H

#include "grafo.h"

/* Estrutura que guarda o estado de cada consumidor */
typedef struct estadoCarga
{
    float recebido;
    int estado;
} EstadoCarga;

/*
Estados possíveis:

0 -> sem energia
1 -> parcialmente alimentado
2 -> totalmente alimentado
*/

#define MAX 1000

/* Funções de gestão da distribuição */
void reiniciarFluxos(Grafo *g);

void distribuirCargaBFS(Grafo *g, char origem[]);

void distribuirCargaDFS(Grafo *g, char origem[]);

void mostrarEstadoCarga(Grafo *g);

#endif