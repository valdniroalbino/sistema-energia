#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"
#include "grafo.h"

#define MAX_LINE 100

int carregaRede(Grafo *g, const char *file)
{
    FILE *fp = fopen(file, "r");

    if (fp == NULL)
    {
        printf("Nao foi possivel abrir o ficheiro.\n");
        return 0;
    }

    char line[MAX_LINE];

    while (fgets(line, sizeof(line), fp))
    {
        char tipo[20];
        sscanf(line, "%s", tipo);

        // Central
        if (strcmp(tipo, "CENTRAL") == 0)
        {
            char nome[50];
            float pot;

            if (sscanf(line, "CENTRAL %s %f", nome, &pot) != 2)
            {
                printf("Erro de formato: %s", line);
                continue;
            }

            if (pot <= 0)
            {
                printf("Erro: Potencia da central %s invalida!\n", nome);
                continue;
            }

            if (procuraVertice(g, nome) != -1)
            {
                printf("Erro: Vertice %s duplicado.\n", nome);
                continue;
            }

            adicionarVertice(g, nome, 0, pot);
        }

        // Subestação
        else if (strcmp(tipo, "SUBESTACAO") == 0)
        {
            char nome[50];
            float pot;

            if (sscanf(line, "SUBESTACAO %s %f", nome, &pot) != 2)
            {
                printf("Erro de formato: %s", line);
                continue;
            }

            if (pot <= 0)
            {
                printf("Erro: Carga da subestacao %s invalida!\n", nome);
                continue;
            }

            if (procuraVertice(g, nome) != -1)
            {
                printf("Erro: Vertice %s duplicado.\n", nome);
                continue;
            }

            adicionarVertice(g, nome, 1, pot);
        }

        // Ligação
        else if (strcmp(tipo, "LIGACAO") == 0)
        {
            char origem[50], destino[50];
            float capacidade;

            if (sscanf(line, "LIGACAO %s %s %f", origem, destino, &capacidade) != 3)
            {
                printf("Erro de formato: %s", line);
                continue;
            }

            if (capacidade <= 0)
            {
                printf("Erro: Capacidade invalida!\n");
                continue;
            }

            if (procuraVertice(g, origem) == -1)
            {
                printf("Erro: Origem %s inexistente.\n", origem);
                continue;
            }

            if (procuraVertice(g, destino) == -1)
            {
                printf("Erro: Destino %s inexistente.\n", destino);
                continue;
            }

			int o = procuraVertice(g, origem);
             int d = procuraVertice(g, destino);

         if (existeLigacao(g, o, d))
            {
                printf("Erro: Ligacao duplicada %s -> %s\n", origem, destino);
                continue;
            }

            adicionarAresta(g, origem, destino, capacidade);
        }

    
        else
        {
            printf("Erro: Comando invalido -> %s", line);
        }
    }

    fclose(fp);

    printf("\nRede carregada com sucesso!\n");
    printf("Vertices: %d\n", g->n_verti);
    printf("Ligacoes: %d\n", g->n_arest);

    return 1;
}