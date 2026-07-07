#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "io.h"
#include "distribuicao.h"
#include "simular_falha.h"
#include "simular_falha_central.h"
#include "validar_conexao.h"
#include "menu.h"

int main(void){
    /* Criar o grafo vazio no inicio do programa */
    Grafo *g = criarGrafo();
    int opcao;
    int sub;
    int escolha;
    int total;
    char nome[50];

    //mostrarCabecalho();

    do{
        /* Limpar o ecra e mostrar o cabecalho e menu a cada iteracao */
        system("clear");
        mostrarCabecalho();
        mostrarMenu();
        opcao = lerOpcao();

        switch(opcao){
            case 1:
            /* Se ja existe uma rede carregada, libertar antes de carregar de novo */
                if(g->n_verti > 0) {
                    libertarGrafo(g);
                    g = criarGrafo();
                }
                carregaRede(g, "rede_electrica.txt");
                pausa();
                break;
            case 2:
            /* Verificar se a rede foi carregada antes de mostrar */

                if(!redeCarregada(g)) break;
                mostrarGrafo(g);
                pausa();
    
                break;
            case 3:
            /* Verificar se a rede foi carregada antes de equilibrar */
                if(!redeCarregada(g)) break;
                mostrarSubmenuCarga();
                sub = lerOpcao();
                /* Mostrar centrais e obter escolha do utilizador */
                total = mostrarCentrais(g);
                printf("  Escolha a central: ");
                escolha = lerOpcao();
                if(escolha < 1 || escolha > total) {
                    printf("  Opcao invalida.\n");
                    pausa();
                    break;
                }
                /* Converter escolha numerica no nome da central */
                opcaoVertice(g, CENTRAL, escolha, nome);
                if(sub == 1)
                    distribuirCargaBFS(g, nome);
                else if(sub == 2)
                    distribuirCargaDFS(g, nome);
                else
                    printf("  Opcao invalida.\n");
                pausa();
                break;
            case 4:
            /* Verificar se a rede foi carregada antes de simular */
                if(!redeCarregada(g)) break;
                mostrarSubmenuFalha();
                sub = lerOpcao();
                if(sub == 1){
                    /* Simular falha de subestacao */
                    total = mostrarSubestacoes(g);
                    printf("  Escolha a subestacao: ");
                    escolha = lerOpcao();
                    if(escolha < 1 || escolha > total) {
                        printf("  Opcao invalida.\n");
                        pausa();
                        break;
                    }
                    opcaoVertice(g, SUBESTACAO, escolha, nome);
                    simularfalhaSubestacao(g, nome);
                }else if(sub == 2){
                    /* Simular falha de central */
                    total = mostrarCentrais(g);
                    printf("  Escolha a central: ");
                    escolha = lerOpcao();
                    if(escolha < 1 || escolha > total) {
                        printf("  Opcao invalida.\n");
                        pausa();
                        break;
                    }
                    opcaoVertice(g, CENTRAL, escolha, nome);
                    simularFalhaCentral(g, nome);
                }else{
                    printf("  Opcao invalida.\n");
                }
                pausa();
                break;
            case 0:
            /* Libertar memoria e terminar o programa com uma mensagem*/
                libertarGrafo(g);
                printf("\n  Obrigado por usar o Sistema de Gestao da RNT.\n  Boa continuacao!\n");
                break;
            default:
               printf("  Opcao invalida.\n");
                pausa();
            
        }

    }while(opcao != 0);

    return 0;
}