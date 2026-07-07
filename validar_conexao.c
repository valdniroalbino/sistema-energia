#include <stdio.h>
#include <stdlib.h>
#include "validar_conexao.h"

/*pesquisa por profundidade
essa funcao percorre o grafo para verificar se todos os vertices estao conectados*/
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
            if(!visitado[origem])
                dfs(g, origem, visitado);
        }   
    }
}
/*usa a pesquisa por profundidade 
para verificar se a rede permanece conectada apos alteracoes*/

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
            printf("  [ERRO] A rede ficou desconexa.\n");
            return 0;
        }
        
    }
    free(visitado);
    printf("  [OK] Rede valida. Todos os nos estao conectados.\n");
    return 1;
    
}