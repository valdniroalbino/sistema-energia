#include <stdio.h>
#include "grafo.h"
#include "io.h"
#include "distribuicao.h"
#include "simular_falha.h"
#include "simular_falha_central.h"
#include "validar_conexao.h"

int main(void) {
    Grafo *g = criarGrafo();
    int opcao;

    do {
        printf("\n===== Sistema de Rede Electrica =====\n");
        printf("1. Carregar rede do ficheiro\n");
        printf("2. Mostrar grafo carregado\n");
        printf("3. Equilibrar carga\n");
        printf("4. Simular falha\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                carregaRede(g, "rede_electrica.txt");
                break;
            case 2:
                mostrarGrafo(g);
                break;
            case 3:
                char nome[50];
                int sub;
                printf("\n--- Equilibrar Carga ---\n");
                printf("1. BFS\n");
                printf("2. DFS\n");
                printf("Opcao: ");
                scanf("%d", &sub);

                printf("Nome da central: ");
                scanf("%s", nome);

                if(sub == 1)
                    distribuirCargaBFS(g, nome);
                else if(sub == 2)
                    distribuirCargaDFS(g, nome);
                else
                    printf("Opcao invalida.\n");
                break;
            case 4:
                char nome[50];
                int sub;
                printf("\n--- Simular Falha ---\n");
                printf("1. Falha de subestacao\n");
                printf("2. Falha de central\n");
                printf("Opcao: ");
                scanf("%d", &sub);

                printf("Nome: ");
                scanf("%s", nome);

                if(sub == 1)
                    simularfalhaSubestacao(g, nome);
                else if(sub == 2)
                    simularFalhaCentral(g, nome);
                else
                    printf("Opcao invalida.\n");
                break;
            case 0:
                libertarGrafo(g);
                printf("A sair...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }

    } while(opcao != 0);

    return 0;
}