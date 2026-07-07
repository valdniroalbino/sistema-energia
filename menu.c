#include <stdio.h>
#include <string.h>
#include "menu.h"

void mostrarCabecalho(void) {
    printf("\n");
    printf("╔══════════════════════════════════════════╗\n");
    printf("║     RNT - Rede Nacional de Transporte    ║\n");
    printf("║        Sistema de Gestao de Energia      ║\n");
    printf("╚══════════════════════════════════════════╝\n");
}

void mostrarMenu(void) {
    printf("\n");
    printf("  [1] Carregar rede do ficheiro\n");
    printf("  [2] Mostrar estado da rede\n");
    printf("  [3] Equilibrar carga\n");
    printf("  [4] Simular falha\n");
    printf("  [0] Sair\n");
    printf("\n  Opcao: ");
}

void mostrarSubmenuCarga(void) {
    printf("\n");
    printf("  -- Equilibrar Carga --\n");
    printf("  [1] BFS\n");
    printf("  [2] DFS\n");
    printf("  Opcao: ");
}

void mostrarSubmenuFalha(void) {
    printf("\n");
    printf("  -- Simular Falha --\n");
    printf("  [1] Falha de subestacao\n");
    printf("  [2] Falha de central\n");
    printf("  Opcao: ");
}

int mostrarCentrais(Grafo *g) {
    int contador = 0;
    printf("\n  Centrais disponiveis:\n");
    for(int i = 0; i < g->n_verti; i++) {
        if(g->vertices[i].tipo == CENTRAL) {
            contador++;
            printf("  [%d] %s (%.2f MW)\n", contador, g->vertices[i].nome, g->vertices[i].pot);
        }
    }
    printf("\n");
    return contador;
}

int mostrarSubestacoes(Grafo *g) {
    int contador = 0;
    printf("\n  Subestacoes disponiveis:\n");
    for(int i = 0; i < g->n_verti; i++) {
        if(g->vertices[i].tipo == SUBESTACAO) {
            contador++;
            printf("  [%d] %s (%.2f MW)\n", contador, g->vertices[i].nome, g->vertices[i].pot);
        }
    }
    printf("\n");
    return contador;
}

void opcaoVertice(Grafo *g, int tipo, int escolha, char nome[]) {
    int contador = 0;
    for(int i = 0; i < g->n_verti; i++) {
        if(g->vertices[i].tipo == tipo) {
            contador++;
            if(contador == escolha) {
                strcpy(nome, g->vertices[i].nome);
                return;
            }
        }
    }
}