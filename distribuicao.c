#include <stdio.h>
#include <stdlib.h>

#include "distribuicao.h"


//Fila Bfs

typedef struct
{
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


//Reiniciar fluxos

void reiniciarFluxos(Grafo *g)
{
    for(int i = 0; i < g->n_arest; i++)
    {
        g->arestas[i].fluxo = 0;
    }
}



//Bfs

static void bfsDistribuir(Grafo *g, int inicio, float *energia)
{

    int visitado[MAX] = {0};


    Fila f;

    iniciarFila(&f);


    inserirFila(&f, inicio);

    visitado[inicio] = 1;



    while(!filaVazia(&f))
    {

        if(*energia <= 0)
            break;


        int atual = removerFila(&f);



        for(int i = 0; i < g->n_arest; i++)
        {

            int vizinho = -1;



            if(g->arestas[i].origem == atual)
            {
                vizinho = g->arestas[i].destino;
            }
            else if(g->arestas[i].destino == atual)
            {
                vizinho = g->arestas[i].origem;
            }



            if(vizinho == -1)
                continue;



            if(visitado[vizinho])
                continue;



            visitado[vizinho] = 1;

            inserirFila(&f, vizinho);



            // A energia é distribuída apenas para subestações
           

            if(g->vertices[vizinho].tipo == SUBESTACAO)
            {

                float enviar = g->arestas[i].capacidade;


                if(enviar > *energia)
                    enviar = *energia;



                // Acumula o fluxo existente

                g->arestas[i].fluxo += enviar;



                // Retira energia da central

                *energia -= enviar;

            }

        }

    }

}


//Distribuicao Bfs

void distribuirCargaBFS(Grafo *g, char origem[])
{

    int inicio = procuraVertice(g, origem);



    if(inicio == -1)
    {
        printf("  [ERRO] Central inexistente.\n");
        return;
    }



    if(g->vertices[inicio].tipo != CENTRAL)
    {
        printf("  [ERRO] O vertice indicado nao e uma central.\n");
        return;
    }



    reiniciarFluxos(g);



    float energia = g->vertices[inicio].pot;



    printf("\n  ======= DISTRIBUICAO BFS =======\n");



    bfsDistribuir(g, inicio, &energia);



    printf("  Energia restante na central: %.2f MW\n", energia);
}


//Dfs

static void dfsDistribuir(Grafo *g, int atual, int visitado[], float *energia)
{

    if(*energia <= 0)
        return;



    visitado[atual] = 1;



    for(int i = 0; i < g->n_arest; i++)
    {

        int vizinho = -1;



        if(g->arestas[i].origem == atual)
        {
            vizinho = g->arestas[i].destino;
        }
        else if(g->arestas[i].destino == atual)
        {
            vizinho = g->arestas[i].origem;
        }



        if(vizinho == -1)
            continue;



        if(visitado[vizinho])
            continue;



        // Apenas subestações recebem energia
        

        if(g->vertices[vizinho].tipo == SUBESTACAO)
        {

            float enviar = g->arestas[i].capacidade;



            if(enviar > *energia)
                enviar = *energia;



            // Acumula fluxo

            g->arestas[i].fluxo += enviar;



            *energia -= enviar;

        }



        dfsDistribuir(g, vizinho, visitado, energia);

    }

}



//Distribuicao Dfs

void distribuirCargaDFS(Grafo *g, char origem[])
{

    int inicio = procuraVertice(g, origem);



    if(inicio == -1)
    {
        printf("  [ERRO] Central inexistente.\n");
        return;
    }



    if(g->vertices[inicio].tipo != CENTRAL)
    {
        printf("  [ERRO] O vertice indicado nao e uma central.\n");
        return;
    }



    reiniciarFluxos(g);



    float energia = g->vertices[inicio].pot;



    int visitado[MAX] = {0};



    printf("\n  ======= DISTRIBUICAO DFS =======\n");



    dfsDistribuir(g, inicio, visitado, &energia);



    printf("  Energia restante na central: %.2f MW\n", energia);

}


