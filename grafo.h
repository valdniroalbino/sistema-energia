#ifndef GRAFO_H
#define GRAFO_H

/* Tipos de vértices */
#define CENTRAL 0
#define SUBESTACAO 1


/* Estrutura do vértice */
typedef struct vertice
{
    char nome[100];
    int tipo;
    float pot;
} Vertice;

/* Estrutura da aresta */
typedef struct aresta
{
    int origem;
    int destino;
    float capacidade;
    float fluxo;
} Aresta;

/* Estrutura do grafo */
typedef struct grafo
{
    Vertice *vertices;
    Aresta *arestas;
    int n_verti;
    int n_arest;
} Grafo;

/* Funções auxiliares */
int procuraVertice(Grafo *g, char nome[]);
int existeLigacao(Grafo *g, int origem, int destino);

/* Gestão do grafo */
Grafo *criarGrafo();
void libertarGrafo(Grafo *g);

/* Gestão dos vértices */
int adicionarVertice(Grafo *g, char nome[], int tipo, float pot);
int removerVertice(Grafo *g, char nome[]);

/* Gestão das arestas */
int adicionarAresta(Grafo *g, char origem[], char destino[], float capacidade);
int removerAresta(Grafo *g, char origem[], char destino[]);

/* Visualização */
void mostrarGrafo(Grafo *g);

#endif