#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "distribuicao.h"

#define MAX 1000

EstadoCarga carga[MAX];

typedef struct{

    int dados[MAX];
    int inicio;
    int fim;

}Fila;


void iniciarFila(Fila *f){

    f->inicio=0;
    f->fim=0;

}

int filaVazia(Fila *f){

    return f->inicio==f->fim;

}

void inserirFila(Fila *f,int v){

    f->dados[f->fim]=v;
    f->fim++;

}

int removerFila(Fila *f){

    int v=f->dados[f->inicio];
    f->inicio++;

    return v;

}

void reiniciarFluxos(Grafo *g){

    for(int i=0;i<g->n_arest;i++)
        g->arestas[i].fluxo=0;

    for(int i=0;i<g->n_verti;i++){

        carga[i].recebido=0;
        carga[i].estado=0;

    }

}

//Distribuir Carga BFS

void distribuirCargaBFS(Grafo *g,char origem[])
{

    int inicio=procuraVertice(g,origem);

    if(inicio==-1){

        printf("Central inexistente.\n");
        return;

    }

    if(g->vertices[inicio].tipo!=1){

        printf("O vertice indicado nao e uma central.\n");
        return;

    }

    reiniciarFluxos(g);

    float energia=g->vertices[inicio].pot;

    int visitado[MAX]={0};

    Fila f;

    iniciarFila(&f);

    inserirFila(&f,inicio);

    visitado[inicio]=1;

    printf("\n======= DISTRIBUICAO BFS =======\n");

    while(!filaVazia(&f))
    {

        int atual=removerFila(&f);

        printf("\nNo atual: %s\n",g->vertices[atual].nome);

        for(int i=0;i<g->n_arest;i++)
        {

            int vizinho=-1;

            if(g->arestas[i].origem==atual)
                vizinho=g->arestas[i].destino;

            else if(g->arestas[i].destino==atual)
                vizinho=g->arestas[i].origem;

            if(vizinho==-1)
                continue;

            if(visitado[vizinho])
                continue;

            visitado[vizinho]=1;

            inserirFila(&f,vizinho);

            float enviar=0;

            if(g->vertices[vizinho].tipo==3)
            {

                float necessidade=g->vertices[vizinho].pot;

                enviar=necessidade;

                if(enviar>energia)
                    enviar=energia;

                if(enviar>g->arestas[i].capacidade)
                    enviar=g->arestas[i].capacidade;

                g->arestas[i].fluxo=enviar;

                carga[vizinho].recebido=enviar;

                energia-=enviar;

                if(enviar==0)
                    carga[vizinho].estado=0;

                else if(enviar<necessidade)
                    carga[vizinho].estado=1;

                else
                    carga[vizinho].estado=2;

                printf("Consumidor: %s\n",g->vertices[vizinho].nome);

                printf("Necessita : %.2f MW\n",necessidade);

                printf("Recebeu   : %.2f MW\n",enviar);

                printf("Energia restante da central: %.2f MW\n",energia);

            }

            else
            {

                g->arestas[i].fluxo=0;

            }

        }

    }

    printf("\nEnergia restante na central: %.2f MW\n",energia);

}

// Aplicação do DFS
´

static void dfs(Grafo *g,int atual,int visitado[],float *energia)
{

    visitado[atual]=1;

    for(int i=0;i<g->n_arest;i++)
    {

        int vizinho=-1;

        if(g->arestas[i].origem==atual)
            vizinho=g->arestas[i].destino;

        else if(g->arestas[i].destino==atual)
            vizinho=g->arestas[i].origem;

        if(vizinho==-1)
            continue;

        if(visitado[vizinho])
            continue;

        if(g->vertices[vizinho].tipo==3)
        {

            float enviar=g->vertices[vizinho].pot;

            if(enviar>*energia)
                enviar=*energia;

            if(enviar>g->arestas[i].capacidade)
                enviar=g->arestas[i].capacidade;

            *energia-=enviar;

            g->arestas[i].fluxo=enviar;

            carga[vizinho].recebido=enviar;

            if(enviar==0)
                carga[vizinho].estado=0;

            else if(enviar<g->vertices[vizinho].pot)
                carga[vizinho].estado=1;

            else
                carga[vizinho].estado=2;

        }

        dfs(g,vizinho,visitado,energia);

    }

}

void distribuirCargaDFS(Grafo *g,char origem[])
{

    int inicio=procuraVertice(g,origem);

    if(inicio==-1)
        return;

    reiniciarFluxos(g);

    float energia=g->vertices[inicio].pot;

    int visitado[MAX]={0};

    dfs(g,inicio,visitado,&energia);

}

// Mostrar relatório ou informcação de distribuição


void mostrarEstadoCarga(Grafo *g)
{

    printf("\n========== ESTADO DA DISTRIBUICAO ==========\n");

    for(int i=0;i<g->n_verti;i++)
    {

        if(g->vertices[i].tipo!=3)
            continue;

        printf("\n%s\n",g->vertices[i].nome);

        printf("Necessita : %.2f MW\n",g->vertices[i].pot);

        printf("Recebido  : %.2f MW\n",carga[i].recebido);

        if(carga[i].estado==0)
            printf("Estado    : SEM ENERGIA\n");

        else if(carga[i].estado==1)
            printf("Estado    : PARCIALMENTE ALIMENTADO\n");

        else
            printf("Estado    : TOTALMENTE ALIMENTADO");

        printf("\n");

    }

}