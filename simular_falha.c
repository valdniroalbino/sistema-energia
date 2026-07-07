#include <stdio.h>
#include <string.h>
#include "simular_falha.h"
#include "validar_conexao.h"

void simularfalhaSubestacao(Grafo *g, char nome[]){
    int index = -1;

    for (int i = 0; i < g->n_verti; i++)
    {
        if(strcmp(g->vertices[i].nome, nome)==0){
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        printf("Subestacao nao encontrada!\n");
        return;
    }
    if (g->vertices[index].tipo!=1)
    {
        printf("O vertice informado nao e subestacao.\n");
        return;
    }
    
    printf("Falha na subestacao %s!\n",nome);

    for (int i = 0; i < g->n_arest; i++)
    {
        if (g->arestas[i].origem==index || g->arestas[i].destino==index)
        {
            g->arestas[i].capacidade=0;
            g->arestas[i].fluxo=0;
        }
        
    }
    grafoConexao(g);
    printf("Fluxos devem ser calculados pelo modulo de distribuicao.\n");
    
    
}