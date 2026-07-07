#include <stdio.h>
#include <stdlib.h>
#include "validar_conexao.h"

//wis, essa funcao percorre o grafo para verificar se todos os vertices estao conectados
void dfs(Grafo *g, int v, int visitado[]){
    visitado[v] = 1;
    for(int i=0; i < g->n_arest; i++){
        if(g->arestas[i].origem == v){
            int destino = g->arestas[i].destino;
            if(!visitado[destino])
                dfs(g, destino, visitado);
        }
        if (g->arestas[i].destino == v)
        {
            int origem = g->arestas[i].origem;
        }   
    }
}

int grafoConexao(Grafo *g){
    if(g->n_verti == 0)
        return 1;
    
    int *visitado = calloc(g->n_verti, sizeof(int));
    dfs(g, 0, visitado);

    for (int i = 0; i < g->n_verti; i++)
    {
        if (!visitado[i])
        {
            free(visitado);
            printf("ERRO: A rede ficou desconexa.\n");
            return 0;
        }
        
    }
    free(visitado);
    printf("Rede válida.\nTodos os nós estão conectados.\n");
    return 1;
    
}