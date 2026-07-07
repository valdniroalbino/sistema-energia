#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "distribuicao.h"

#define MAX 1000

EstadoCarga carga[MAX];

/* ===================== FILA ===================== */

typedef struct {
    int dados[MAX];
    int inicio;
    int fim;
} Fila;

void iniciarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
}

int filaVazia(Fila *f) {
    return f->inicio == f->fim;
}

void inserirFila(Fila *f, int v) {
    f->dados[f->fim++] = v;
}

int removerFila(Fila *f) {
    return f->dados[f->inicio++];
}

/* ===================== RESET ===================== */

void reiniciarFluxos(Grafo *g) {

    for (int i = 0; i < g->n_arest; i++)
        g->arestas[i].fluxo = 0;

    for (int i = 0; i < g->n_verti; i++) {
        carga[i].recebido = 0;
        carga[i].estado = 0;
    }
}

/* ===================== BFS ===================== */

void distribuirCargaBFS(Grafo *g, char origem[]) {

    int inicio = procuraVertice(g, origem);

    if (inicio == -1) {
        printf("Central inexistente.\n");
        return;
    }

    if (g->vertices[inicio].tipo != CENTRAL) {
        printf("O vertice indicado nao e uma central.\n");
        return;
    }

    reiniciarFluxos(g);

    float energia = g->vertices[inicio].pot;
    float energiaInicial = energia;

    int visitado[MAX] = {0};
    int consumidores = 0;
    int atendidos = 0;

    Fila f;
    iniciarFila(&f);

    inserirFila(&f, inicio);

    printf("\n======= DISTRIBUICAO BFS =======\n");

    while (!filaVazia(&f)) {

        int atual = removerFila(&f);

        for (int i = 0; i < g->n_arest; i++) {

            int vizinho = -1;

            if (g->arestas[i].origem == atual)
                vizinho = g->arestas[i].destino;
            else if (g->arestas[i].destino == atual)
                vizinho = g->arestas[i].origem;

            if (vizinho == -1)
                continue;

            if (visitado[vizinho])
                continue;

            visitado[vizinho] = 1;
            inserirFila(&f, vizinho);

            if (g->vertices[vizinho].tipo == CONSUMIDOR) {

                consumidores++;

                float necessidade = g->vertices[vizinho].pot;

                float enviar = necessidade;

                if (enviar > energia)
                    enviar = energia;

                if (enviar > g->arestas[i].capacidade)
                    enviar = g->arestas[i].capacidade;

                g->arestas[i].fluxo += enviar;

                energia -= enviar;

                carga[vizinho].recebido += enviar;

                if (enviar == necessidade)
                    carga[vizinho].estado = 2;
                else if (enviar > 0)
                    carga[vizinho].estado = 1;
                else
                    carga[vizinho].estado = 0;

                if (enviar == necessidade)
                    atendidos++;

                printf("\nConsumidor: %s", g->vertices[vizinho].nome);
                printf("\nRecebeu   : %.2f MW", enviar);
                printf("\nRestante  : %.2f MW\n", energia);
            }
        }
    }

    printf("\nEnergia inicial: %.2f MW", energiaInicial);
    printf("\nEnergia final  : %.2f MW", energia);
    printf("\nTaxa de atendimento: %.2f%%\n",
           consumidores > 0 ? (atendidos * 100.0 / consumidores) : 0);
}

/* ===================== DFS ===================== */

static void dfs(Grafo *g, int atual, int visitado[], float *energia) {

    visitado[atual] = 1;

    for (int i = 0; i < g->n_arest; i++) {

        int vizinho = -1;

        if (g->arestas[i].origem == atual)
            vizinho = g->arestas[i].destino;
        else if (g->arestas[i].destino == atual)
            vizinho = g->arestas[i].origem;

        if (vizinho == -1 || visitado[vizinho])
            continue;

        if (g->vertices[vizinho].tipo == CONSUMIDOR) {

            float enviar = g->vertices[vizinho].pot;

            if (enviar > *energia)
                enviar = *energia;

            if (enviar > g->arestas[i].capacidade)
                enviar = g->arestas[i].capacidade;

            g->arestas[i].fluxo += enviar;

            *energia -= enviar;

            carga[vizinho].recebido += enviar;

            if (enviar == g->vertices[vizinho].pot)
                carga[vizinho].estado = 2;
            else if (enviar > 0)
                carga[vizinho].estado = 1;
            else
                carga[vizinho].estado = 0;
        }

        dfs(g, vizinho, visitado, energia);
    }
}

/* ===================== DFS MAIN ===================== */

void distribuirCargaDFS(Grafo *g, char origem[]) {

    int inicio = procuraVertice(g, origem);

    if (inicio == -1)
        return;

    if (g->vertices[inicio].tipo != CENTRAL) {
        printf("O vertice indicado nao e uma central.\n");
        return;
    }

    reiniciarFluxos(g);

    float energia = g->vertices[inicio].pot;

    int visitado[MAX] = {0};

    dfs(g, inicio, visitado, &energia);
}

/* ===================== RELATORIO ===================== */

void mostrarEstadoCarga(Grafo *g) {

    printf("\n========== ESTADO DA DISTRIBUICAO ==========\n");

    for (int i = 0; i < g->n_verti; i++) {

        if (g->vertices[i].tipo != CONSUMIDOR)
            continue;

        printf("\n%s", g->vertices[i].nome);
        printf("\nRecebido : %.2f MW", carga[i].recebido);

        if (carga[i].estado == 2)
            printf("\nEstado   : TOTALMENTE ALIMENTADO\n");
        else if (carga[i].estado == 1)
            printf("\nEstado   : PARCIALMENTE ALIMENTADO\n");
        else
            printf("\nEstado   : SEM ENERGIA\n");
    }
}