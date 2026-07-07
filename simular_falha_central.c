#include <stdio.h>
#include <string.h>

#include "simular_falha_central.h"
#include "distribuicao.h"


void simularFalhaCentral(Grafo *g, char central[]){

            int pos = procuraVertice(g, central);


    // Verificar se a central existe

    if(pos == -1){
        printf("  [ERRO] Central inexistente.\n");
        return;
    }


    // Verificar se é realmente uma central

            if(g->vertices[pos].tipo != CENTRAL){
        printf("  [ERRO] O vertice indicado nao e uma central.\n");
        return;
    }



        printf("\n  ===== SIMULACAO DE FALHA =====\n");

        printf("  Central afectada: %s\n", g->vertices[pos].nome);



// Guardar potência original

    float potenciaAnterior = g->vertices[pos].pot;



// Simular falha

        g->vertices[pos].pot = 0;



    printf("  Potencia perdida: %.2f MW\n", potenciaAnterior);



    // Limpar distribuição anterior

    reiniciarFluxos(g);



    int encontrouCentral = 0;



    printf("  Redistribuindo carga pelas centrais disponiveis...\n");



    // Procurar outras centrais

for(int i = 0; i < g->n_verti; i++){

    if(g->vertices[i].tipo == CENTRAL &&
           g->vertices[i].pot > 0 &&
           i != pos)
        {

            encontrouCentral = 1;


            printf("  Nova central de alimentacao: %s\n", g->vertices[i].nome);



            distribuirCargaBFS(g, g->vertices[i].nome);

        }

    }


if(!encontrouCentral){

        printf("  [AVISO] Nao existem outras centrais disponiveis.\n");

        printf("  As subestacoes ficaram sem alimentacao.\n");

    }



    printf("\n  ===== FIM DA SIMULACAO =====\n");


    mostrarEstadoCarga(g);

}