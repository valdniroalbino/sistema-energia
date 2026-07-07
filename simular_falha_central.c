#include <stdio.h>
#include <string.h>

#include "simular_falha_central.h"
#include "distribuicao.h"


void simularFalhaCentral(Grafo *g, char central[]){

            int pos = procuraVertice(g, central);


    // Verificar se a central existe

    if(pos == -1){
        printf("\nCentral inexistente.\n");
        return;
    }


    // Verificar se é realmente uma central

            if(g->vertices[pos].tipo != CENTRAL){
        printf("\nO vertice indicado nao e uma central.\n");
        return;
    }



        printf("\n===== SIMULACAO DE FALHA =====\n");

        printf("Central afetada: %s\n", g->vertices[pos].nome);



// Guardar potência original

    float potenciaAnterior = g->vertices[pos].pot;



// Simular falha

        g->vertices[pos].pot = 0;



    printf("Potencia perdida: %.2f MW\n", potenciaAnterior);



    // Limpar distribuição anterior

    reiniciarFluxos(g);



    int encontrouCentral = 0;



    printf("\nRedistribuindo carga pelas centrais disponiveis...\n");



    // Procurar outras centrais

for(int i = 0; i < g->n_verti; i++){

    if(g->vertices[i].tipo == CENTRAL &&
           g->vertices[i].pot > 0 &&
           i != pos)
        {

            encontrouCentral = 1;


            printf("\nNova central de alimentacao: %s\n",
                   g->vertices[i].nome);



            distribuirCargaBFS(g, g->vertices[i].nome);

        }

    }


if(!encontrouCentral){

        printf("\nNao existem outras centrais disponiveis.\n");

        printf("Os consumidores ficaram sem alimentacao.\n");

    }



    printf("\n===== FIM DA SIMULACAO =====\n");


    mostrarEstadoCarga(g);

}