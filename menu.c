#include <stdio.h>
#include <string.h>
#include "menu.h"

void mostrarCabecalho(void){
    printf("\n");
    printf("╔══════════════════════════════════════════╗\n");
    printf("║     RNT - Rede Nacional de Transporte    ║\n");
    printf("║        Sistema de Gestao de Energia      ║\n");
    printf("╚══════════════════════════════════════════╝\n");
}

void mostrarMenu(void){
    printf("\n");
    printf("  [1] Carregar rede do ficheiro\n");
    printf("  [2] Mostrar estado da rede\n");
    printf("  [3] Equilibrar carga\n");
    printf("  [4] Simular falha\n");
    printf("  [0] Sair\n");
    printf("\n  --------------------------------------\n");
    printf("\n  Opcao: ");
}

void mostrarSubmenuCarga(void){
    printf("\n");
    printf("  -- Equilibrar Carga --\n");
    printf("  [1] BFS\n");
    printf("  [2] DFS\n");
    printf("  Opcao: ");
}

void mostrarSubmenuFalha(void){
    printf("\n");
    printf("  -- Simular Falha --\n");
    printf("  [1] Falha de subestacao\n");
    printf("  [2] Falha de central\n");
    printf("  Opcao: ");
}

/* Percorre os vertices e lista apenas as centrais com potencia disponivel
   Retorna o total de centrais encontradas */
int mostrarCentrais(Grafo *g){
    int contador = 0;
    printf("\n  Centrais disponiveis:\n");
    for(int i = 0; i < g->n_verti; i++) {
        /* Filtra centrais com potencia maior que zero */
        if(g->vertices[i].tipo == CENTRAL && g->vertices[i].pot > 0) {
            contador++;
            printf("  [%d] %s (%.2f MW)\n", contador, g->vertices[i].nome, g->vertices[i].pot);
        }
    }
    printf("\n");
    return contador;
}

/* Percorre os vertices e lista apenas as subestacoes
   Retorna o total de subestacoes encontradas */
int mostrarSubestacoes(Grafo *g){
    int contador = 0;
    printf("\n  Subestacoes disponiveis:\n");
    for(int i = 0; i < g->n_verti; i++){
        if(g->vertices[i].tipo == SUBESTACAO) {
            contador++;
            printf("  [%d] %s (%.2f MW)\n", contador, g->vertices[i].nome, g->vertices[i].pot);
        }
    }
    printf("\n");
    return contador;
}

/* Converte a escolha numerica do utilizador no nome do vertice correspondente
   Percorre os vertices do tipo indicado e copia o nome quando encontra a posicao certa */
void opcaoVertice(Grafo *g, int tipo, int escolha, char nome[]){
    int contador = 0;
    for(int i = 0; i < g->n_verti; i++){
        if(g->vertices[i].tipo == tipo){
            contador++;
            /* Quando o contador corresponde a escolha, copia o nome e termina */
            if(contador == escolha) {
                strcpy(nome, g->vertices[i].nome);
                return;
            }
        }
    }
}

/* Verifica se a rede foi carregada antes de executar qualquer operacao
   Retorna 1 se a rede tem vertices, 0 caso contrario */
int redeCarregada(Grafo *g){
    if(g->n_verti == 0) {
        printf("\n  [AVISO] Carregue a rede primeiro. (opcao 1)\n");
        return 0;
    }
    return 1;
}

/* Aguarda que o utilizador prima uma tecla antes de voltar ao menu
   O primeiro getchar limpa o Enter que ficou no buffer do scanf */
void pausa(void){
    printf("\n  Prima qualquer tecla para continuar...");
    getchar();
    getchar();
}
