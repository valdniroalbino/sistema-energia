#include <stdio.h>
#include "grafo.h"
#include "io.h"
#include "distribuicao.h"
#include "simular_falha.h"
#include "simular_falha_central.h"
#include "validar_conexao.h"
#include "menu.h"

int main(void) {
    Grafo *g = criarGrafo();
    int opcao;
    int sub;
    int escolha;
    int total;
    char nome[50];

    mostrarCabecalho();

    do {
        mostrarMenu();
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                carregaRede(g, "rede_electrica.txt");
                break;
            case 2:
                mostrarGrafo(g);
                break;
            case 3:
                mostrarSubmenuCarga();
                scanf("%d", &sub);
                total = mostrarCentrais(g);
                printf("  Escolha a central: ");
                scanf("%d", &escolha);
                if(escolha < 1 || escolha > total) {
                    printf("  Opcao invalida.\n");
                    break;
                }
                opcaoVertice(g, CENTRAL, escolha, nome);
                if(sub == 1)
                    distribuirCargaBFS(g, nome);
                else if(sub == 2)
                    distribuirCargaDFS(g, nome);
                else
                    printf("  Opcao invalida.\n");
                break;
            case 4:
                mostrarSubmenuFalha();
                scanf("%d", &sub);
                if(sub == 1) {
                    total = mostrarSubestacoes(g);
                    printf("  Escolha a subestacao: ");
                    scanf("%d", &escolha);
                    if(escolha < 1 || escolha > total) {
                        printf("  Opcao invalida.\n");
                        break;
                    }
                    opcaoVertice(g, SUBESTACAO, escolha, nome);
                    simularfalhaSubestacao(g, nome);
                } else if(sub == 2) {
                    total = mostrarCentrais(g);
                    printf("  Escolha a central: ");
                    scanf("%d", &escolha);
                    if(escolha < 1 || escolha > total) {
                        printf("  Opcao invalida.\n");
                        break;
                    }
                    opcaoVertice(g, CENTRAL, escolha, nome);
                    simularFalhaCentral(g, nome);
                } else {
                    printf("  Opcao invalida.\n");
                }
                break;
            case 0:
                libertarGrafo(g);
                printf("\n  Ate logo!\n\n");
                break;
            default:
                printf("  Opcao invalida.\n");
        }

    } while(opcao != 0);

    return 0;
}