#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

 //Criar o grafo

Grafo *criarGrafo()
{
    Grafo *g = (Grafo *)malloc(sizeof(Grafo));
    if (g == NULL)
    return NULL;

    g->vertices = NULL;
    g->arestas = NULL;
    g->n_verti = 0;
    g->n_arest = 0;

    return g;
}

// Destruir o grafo ou seja, liberação do grafo

void libertarGrafo(Grafo *g)
{
    if (g == NULL) return;

    free(g->vertices);
    free(g->arestas);
    free(g);
}

//Procurar vertice 

int procuraVertice(Grafo *g, char nome[])
{
    for (int i = 0; i < g->n_verti; i++)
    {
        if (strcmp(g->vertices[i].nome, nome) == 0)
            return i;
    }
    return -1;
}

// Verificacao de que existe ligacao 

int existeLigacao(Grafo *g, int origem, int destino)
{
    for (int i = 0; i < g->n_arest; i++)
    {
        if ((g->arestas[i].origem == origem &&
             g->arestas[i].destino == destino) ||
            (g->arestas[i].origem == destino &&
             g->arestas[i].destino == origem))
        {
            return 1;
        }
    }
    return 0;
}

// Adicionar vertices 

int adicionarVertice(Grafo *g, char nome[], int tipo, float pot)
{
    if (procuraVertice(g, nome) != -1)
        return 0;

    g->vertices = realloc(g->vertices, (g->n_verti + 1) * sizeof(Vertice));

    strcpy(g->vertices[g->n_verti].nome, nome);
    g->vertices[g->n_verti].tipo = tipo;
    g->vertices[g->n_verti].pot = pot;

    g->n_verti++;

    return 1;
}


// Adicionar arestas

int adicionarAresta(Grafo *g, char origem[], char destino[], float capacidade)
{
    int o = procuraVertice(g, origem);
    int d = procuraVertice(g, destino);

    if (o == -1 || d == -1)
        return 0;

    if (existeLigacao(g, o, d))
        return 0;

    g->arestas = realloc(g->arestas, (g->n_arest + 1) * sizeof(Aresta));

    g->arestas[g->n_arest].origem = o;
    g->arestas[g->n_arest].destino = d;
    g->arestas[g->n_arest].capacidade = capacidade;
    g->arestas[g->n_arest].fluxo = 0;

    g->n_arest++;

    return 1;
}

// Remover arestas

int removerAresta(Grafo *g, char origem[], char destino[])
{
    int o = procuraVertice(g, origem);
    int d = procuraVertice(g, destino);

    if (o == -1 || d == -1)
        return 0;

    for (int i = 0; i < g->n_arest; i++)
    {
        if ((g->arestas[i].origem == o && g->arestas[i].destino == d) ||
            (g->arestas[i].origem == d && g->arestas[i].destino == o))
        {
            for (int j = i; j < g->n_arest - 1; j++)
                g->arestas[j] = g->arestas[j + 1];

            g->n_arest--;
            return 1;
        }
    }

    return 0;
}

// Remover vertices

int removerVertice(Grafo *g, char nome[])
{
    int pos = procuraVertice(g, nome);

    if (pos == -1)
        return 0;

    // remover arestas ligadas ao vértice
    for (int i = 0; i < g->n_arest; i++)
    {
        if (g->arestas[i].origem == pos || g->arestas[i].destino == pos)
        {
            removerAresta(g,
                          g->vertices[g->arestas[i].origem].nome,
                          g->vertices[g->arestas[i].destino].nome);
            i--;
        }
    }

    // remover vértice
    for (int i = pos; i < g->n_verti - 1; i++)
        g->vertices[i] = g->vertices[i + 1];

    g->n_verti--;

    // ajustar índices das arestas
    for (int i = 0; i < g->n_arest; i++)
    {
        if (g->arestas[i].origem > pos)
            g->arestas[i].origem--;

        if (g->arestas[i].destino > pos)
            g->arestas[i].destino--;
    }

    return 1;
}

// Mostrar o grafo

void mostrarGrafo(Grafo *g)
{
    printf("\n--- VERTICES ---\n");

    for (int i = 0; i < g->n_verti; i++)
    {
        printf("%d - %s | tipo: %d | pot: %.2f\n",
               i,
               g->vertices[i].nome,
               g->vertices[i].tipo,
               g->vertices[i].pot);
    }

    printf("\n--- ARESTAS ---\n");

    for (int i = 0; i < g->n_arest; i++)
    {
        printf("%s <-> %s | cap: %.2f | fluxo: %.2f\n",
               g->vertices[g->arestas[i].origem].nome,
               g->vertices[g->arestas[i].destino].nome,
               g->arestas[i].capacidade,
               g->arestas[i].fluxo);
    }
}