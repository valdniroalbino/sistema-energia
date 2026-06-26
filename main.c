#include <stdio.h>
#include "grafo.h"
#include "io.h"

int main(void){
    Grafo *g = criarGrafo();

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
                carregaRede(g, "rede_electrica.txt");
                break;
            case 2:
                mostrarGrafo(g);
                break;
            case 0:
                libertarGrafo(g);
                printf("A sair...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }

    }while(opcao != 0);

    return 0;
}