#ifndef MENU_H
#define MENU_H

#include "grafo.h"
//Exibe o cabecalho do programa com o nome da RNT
void mostrarCabecalho(void);
//Exibe o menu principal com as opcoes disponiveis
void mostrarMenu(void);
//Exibe o submenu de equilibrar carga (BFS ou DFS)
void mostrarSubmenuCarga(void);
//Exibe o submenu de simulacao de falha (subestacao ou central)
void mostrarSubmenuFalha(void);
//Lista as centrais disponiveis e retorna o total
int mostrarCentrais(Grafo *g);
//Lista as subestacoes disponiveis e retorna o total
int mostrarSubestacoes(Grafo *g);
//Converte a escolha numerica do utilizador no nome do vertice correspondente
void opcaoVertice(Grafo *g, int tipo, int escolha, char nome[]);
//Antes de qualuqer opcao, o usuario deve carregar a rede. 
int redeCarregada(Grafo *g) ;
//Aguarda que o utilizador prima uma tecla para continuar
void pausa(void);
/* Le uma opcao do utilizador de forma segura contra letras e caracteres invalidos */
int lerOpcao(void);

#endif