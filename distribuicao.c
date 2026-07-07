#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "distribuicao.h"

#define MAX 1000

EstadoCarga carga[MAX];


/* Fila */

typedef struct {

    int dados[MAX];
    int inicio;
    int fim;

} Fila;


void iniciarFila(Fila *f)
{
    f->inicio = 0;
    f->fim = 0;
}


int filaVazia(Fila *f)
{
    return f->inicio == f->fim;
}


void inserirFila(Fila *f, int v)
{
    if(f->fim < MAX)
        f->dados[f->fim++] = v;
}


int removerFila(Fila *f)
{
    return f->dados[f->inicio++];
}


/* Reset ou reiniciar  */

void reiniciarFluxos(Grafo *g)
{

    for(int i = 0; i < g->n_arest; i++)
        g->arestas[i].fluxo = 0;


    for(int i = 0; i < g->n_verti; i++)
    {
        carga[i].recebido = 0;
        carga[i].estado = 0;
    }

}


/* Processar consumidor */

static void processarConsumidor(Grafo *g, int vizinho, int aresta, float *energia)
{

    float necessidade = g->vertices[vizinho].pot;

    float enviar = necessidade;


    // Limite pela energia disponível

    if(enviar > *energia)
        enviar = *energia;


    // Limite pela capacidade da ligação

    if(enviar > g->arestas[aresta].capacidade)
        enviar = g->arestas[aresta].capacidade;



    // Atualizar fluxo

    g->arestas[aresta].fluxo += enviar;



    // Atualizar energia disponível

    *energia -= enviar;



    // Atualizar consumidor

    carga[vizinho].recebido += enviar;



    if(enviar == 0)

        carga[vizinho].estado = 0;


    else if(enviar < necessidade)

        carga[vizinho].estado = 1;


    else

        carga[vizinho].estado = 2;



    printf("\nConsumidor: %s", g->vertices[vizinho].nome);
    printf("\nNecessita : %.2f MW", necessidade);
    printf("\nRecebeu   : %.2f MW", enviar);
    printf("\nEnergia restante: %.2f MW\n", *energia);

}


/* Bfs interno */

static void bfsDistribuir(Grafo *g, int inicio, float *energia)
{

    int visitado[MAX] = {0};


    Fila f;

    iniciarFila(&f);


    inserirFila(&f, inicio);

    visitado[inicio] = 1;



    while(!filaVazia(&f))
    {

        int atual = removerFila(&f);



        for(int i = 0; i < g->n_arest; i++)
        {

            int vizinho = -1;



            if(g->arestas[i].origem == atual)

                vizinho = g->arestas[i].destino;


            else if(g->arestas[i].destino == atual)

                vizinho = g->arestas[i].origem;



            if(vizinho == -1)

                continue;



            if(visitado[vizinho])

                continue;



            visitado[vizinho] = 1;


            inserirFila(&f, vizinho);



            if(g->vertices[vizinho].tipo == CONSUMIDOR)

            {
                processarConsumidor(g, vizinho, i, energia);
            }

        }

    }

}



/* Distribuicao Bfs*/

void distribuirCargaBFS(Grafo *g, char origem[])
{

    int inicio = procuraVertice(g, origem);



    if(inicio == -1)
    {
        printf("Central inexistente.\n");
        return;
    }



    if(g->vertices[inicio].tipo != CENTRAL)
    {
        printf("O vertice indicado nao e uma central.\n");
        return;
    }



    reiniciarFluxos(g);



    float energia = g->vertices[inicio].pot;



    printf("\n======= DISTRIBUICAO BFS =======\n");



    bfsDistribuir(g, inicio, &energia);



    printf("\nEnergia restante na central: %.2f MW\n", energia);

}



/* Dfs interno */

static void dfsDistribuir(Grafo *g, int atual, int visitado[], float *energia)
{

    visitado[atual] = 1;



    for(int i = 0; i < g->n_arest; i++)
    {

        int vizinho = -1;



        if(g->arestas[i].origem == atual)

            vizinho = g->arestas[i].destino;


        else if(g->arestas[i].destino == atual)

            vizinho = g->arestas[i].origem;



        if(vizinho == -1)

            continue;



        if(visitado[vizinho])

            continue;



        if(g->vertices[vizinho].tipo == CONSUMIDOR)

        {
            processarConsumidor(g, vizinho, i, energia);
        }



        dfsDistribuir(g, vizinho, visitado, energia);

    }

}



/* Distribuicao Dfs*/

void distribuirCargaDFS(Grafo *g, char origem[])
{

    int inicio = procuraVertice(g, origem);



    if(inicio == -1)
    {
        printf("Central inexistente.\n");
        return;
    }



    if(g->vertices[inicio].tipo != CENTRAL)
    {
        printf("O vertice indicado nao e uma central.\n");
        return;
    }



    reiniciarFluxos(g);



    float energia = g->vertices[inicio].pot;



    int visitado[MAX] = {0};



    printf("\n======= DISTRIBUICAO DFS =======\n");



    dfsDistribuir(g, inicio, visitado, &energia);



    printf("\nEnergia restante na central: %.2f MW\n", energia);

}



/* Relatorio */

void mostrarEstadoCarga(Grafo *g)
{

    printf("\n========== ESTADO DA DISTRIBUICAO ==========\n");



    for(int i = 0; i < g->n_verti; i++)
    {

        if(g->vertices[i].tipo != CONSUMIDOR)

            continue;



        printf("\n%s", g->vertices[i].nome);

        printf("\nRecebido : %.2f MW", carga[i].recebido);



        if(carga[i].estado == 2)

            printf("\nEstado   : TOTALMENTE ALIMENTADO\n");


        else if(carga[i].estado == 1)

            printf("\nEstado   : PARCIALMENTE ALIMENTADO\n");


        else

            printf("\nEstado   : SEM ENERGIA\n");

    }

}