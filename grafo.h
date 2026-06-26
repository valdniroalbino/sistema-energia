#ifndef GRAFO_H
#define GRAFO_H

typedef struct vertice{
	char nome[100];
	int tipo;
	float pot;
}Vertice;

typedef struct aresta{
	int origem, destino;
	float capacidade, fluxo;
}Aresta;

typedef struct grafo{
	struct vertice *vertices;
	struct aresta *arestas;
	int n_verti, n_arest;
}Grafo;

int procuraVertice(Grafo *g, char nome[]);
int existeLigacao(Grafo *g, int origem, int destino);


	Grafo *criarGrafo();
void libertarGrafo(Grafo *g);


		int adicionarVertice(Grafo *g, char nome[], int tipo, float pot);
    int removerVertice(Grafo *g, char nome[]);


      int adicionarAresta(Grafo *g, char origem[], char destino[], float capacidade);
   int removerAresta(Grafo *g, char origem[], char destino[]);

       void mostrarGrafo(Grafo *g);

#endif