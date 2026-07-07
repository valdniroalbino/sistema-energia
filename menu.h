#ifndef MENU_H
#define MENU_H

#include "grafo.h"

void mostrarCabecalho(void);
void mostrarMenu(void);
void mostrarSubmenuCarga(void);
void mostrarSubmenuFalha(void);
int mostrarCentrais(Grafo *g);
int mostrarSubestacoes(Grafo *g);
void opcaoVertice(Grafo *g, int tipo, int escolha, char nome[]);

#endif