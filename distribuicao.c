#include <stdio.h>
#include <stdlib.h>

#include "distribuicao.h"


#define MAX 1000



/* ==========================
        ESTRUTURA DA FILA
   ========================== */


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



void inserirFila(Fila *f, int valor)
{
    if(f->fim < MAX)
    {
        f->dados[f->fim] = valor;
        f->fim++;
    }
}



int removerFila(Fila *f)
{
    return f->dados[f->inicio++];
}




/* ==========================
        RESET DOS FLUXOS
   ========================== */


void reiniciarFluxos(Grafo *g)
{

    for(int i = 0; i < g->n_arest; i++)
    {
        g->arestas[i].fluxo = 0;
    }

}



/* ==========================
        CALCULO DO FLUXO
   ========================== */


static float calcularFluxo(Aresta *a, float *energia)
{

    float disponivel;


    /*
       capacidade ainda disponível
    */

    disponivel = a->capacidade - a->fluxo;



    if(disponivel <= 0)
        return 0;



    /*
       não pode enviar mais energia
       do que a central possui
    */

    if(disponivel > *energia)
        disponivel = *energia;



    a->fluxo += disponivel;


    *energia -= disponivel;



    return disponivel;

}




/* ==========================
             BFS
   ========================== */


static void bfsDistribuir(Grafo *g, int inicio, float *energia)
{

    int visitado[MAX] = {0};


    Fila fila;


    iniciarFila(&fila);



    inserirFila(&fila, inicio);


    visitado[inicio] = 1;




    while(!filaVazia(&fila))
    {


        if(*energia <= 0)
            return;



        int atual = removerFila(&fila);



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


            inserirFila(&fila, vizinho);



            /*
              Distribuição apenas para subestações
            */


            if(g->vertices[vizinho].tipo == SUBESTACAO)
            {

                float enviado =
                calcularFluxo(
                    &g->arestas[i],
                    energia
                );


                printf("\nBFS: %s -> %s",
                g->vertices[atual].nome,
                g->vertices[vizinho].nome);


                printf("\nEnergia enviada: %.2f MW\n",
                enviado);

            }

        }

    }

}




/* ==========================
        DISTRIBUIÇÃO BFS
   ========================== */


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



    printf("\n========== DISTRIBUICAO BFS ==========\n");



    bfsDistribuir(
        g,
        inicio,
        &energia
    );



    printf("\nEnergia restante na central: %.2f MW\n",
    energia);

}





/* ==========================
             DFS
   ========================== */


static void dfsDistribuir(
        Grafo *g,
        int atual,
        int visitado[],
        float *energia)
{


    if(*energia <= 0)
        return;



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



        visitado[vizinho] = 1;



        if(g->vertices[vizinho].tipo == SUBESTACAO)
        {

            float enviado =
            calcularFluxo(
                &g->arestas[i],
                energia
            );


            printf("\nDFS: %s -> %s",
            g->vertices[atual].nome,
            g->vertices[vizinho].nome);


            printf("\nEnergia enviada: %.2f MW\n",
            enviado);

        }



        dfsDistribuir(
            g,
            vizinho,
            visitado,
            energia
        );


    }

}




/* ==========================
        DISTRIBUIÇÃO DFS
   ========================== */


void distribuirCargaDFS(Grafo *g, char origem[])
{

    int inicio =
    procuraVertice(g, origem);



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



    float energia =
    g->vertices[inicio].pot;



    int visitado[MAX] = {0};



    printf("\n========== DISTRIBUICAO DFS ==========\n");



    dfsDistribuir(
        g,
        inicio,
        visitado,
        &energia
    );



    printf("\nEnergia restante na central: %.2f MW\n",
    energia);

}




/* ==========================
      RELATORIO DA CARGA
   ========================== */


void mostrarEstadoCarga(Grafo *g)
{

    printf("\n========== ESTADO DA DISTRIBUICAO ==========\n");



    for(int i = 0; i < g->n_verti; i++)
    {


        if(g->vertices[i].tipo != SUBESTACAO)
            continue;



        float recebido = 0;



        for(int j = 0; j < g->n_arest; j++)
        {

            if(g->arestas[j].destino == i ||
               g->arestas[j].origem == i)
            {

                recebido += g->arestas[j].fluxo;

            }

        }



        printf("\nSubestacao: %s",
        g->vertices[i].nome);


        printf("\nEnergia recebida: %.2f MW",
        recebido);



        if(recebido > 0)
        {
            printf("\nEstado: ALIMENTADA\n");
        }
        else
        {
            printf("\nEstado: SEM ENERGIA\n");
        }


    }

}