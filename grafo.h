#ifndef GRAFO_H
#define GRAFO_H

typedef struct Aresta{
    int destino;
    int peso;
    struct Aresta *prox;
}Aresta;

typedef struct {
    char nome[100];
    Aresta*lista;
}No;

typedef struct{
    int numNos;
    No *nos;
}Grafo;

typedef Grafo *GRF; //so para adoçar

GRF grafo_criar(int numNos);
void grafo_adicionarAresta(GRF g, int u, int v,int peso);
void grafo_removerAresta(GRF g, int u, int v);
void grafo_imprimir(GRF g);
void grafo_destruir(GRF g);
void grafo_bfs(GRF g, int origem);



#endif

