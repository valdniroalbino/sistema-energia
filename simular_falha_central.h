#ifndef SIMULAR_FALHA_CENTRAL_H
#define SIMULAR_FALHA_CENTRAL_H


#include "grafo.h"


/*
Simula a falha de uma central e redistribui
a carga através das restantes centrais disponíveis
*/

void simularFalhaCentral(Grafo *g, char central[]);


#endif