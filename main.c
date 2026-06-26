#include <stdio.h>
#include "grafo.h"
#include "io.h"

int main(void){
    Grafo g;
    g.vertices = NULL;
    g.arestas  = NULL;
    g.n_verti  = 0;
    g.n_arest  = 0;

    int opcao;

    do{
        printf("\n===== Sistema de Rede Electrica =====\n");
        printf("1. Carregar rede do ficheiro\n");
        printf("2. Mostrar grafo carregado\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                carregaRede(&g, "rede_electrica.txt");
                break;
            case 2:
                printf("Vertices: %d | Ligacoes: %d\n", g.n_verti, g.n_arest);
                break;
            case 0:
                printf("A sair...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }

    }while(opcao != 0);

    return 0;
}