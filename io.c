#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"
#include "grafo.h"

#define MAX_LINE 100
#define MAX_POT 1000

int carregaRede(Grafo *g, const char *file)
{
    FILE *fp = fopen(file, "r");

    if (fp == NULL)
    {
        printf("  [ERRO] Nao foi possivel abrir o ficheiro.\n");
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
                printf("  [ERRO] Formato invalido: %s", line);
                continue;
            }

            if (pot <= 0)
            {
                printf("Erro: Potencia da central %s invalida!\n", nome);
                continue;
            }
            if (pot > MAX_POT)
            {
                printf("  [ERRO] Potencia da central %s excede o limite!\n", nome);
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

            if (pot > MAX_POT)
            {
                printf("  [ERRO] Carga da subestacao %s excede o limite!\n", nome);
                continue;
            }

            if (procuraVertice(g, nome) != -1)
            {
                printf("  [ERRO] Vertice %s duplicado.\n", nome);
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
                printf("  [ERRO] Formato invalido: %s", line);
                continue;
            }

            if (capacidade <= 0)
            {
                printf("  [ERRO] Capacidade invalida!\n");
                continue;
            }
            if (strcmp(origem, destino)==0)
            {
                printf("Erro: Ligacao %s invalida(Liga a si mesma)!\n", origem);
                continue;
            }
            

            if (procuraVertice(g, origem) == -1)
            {
                printf("  [ERRO] Origem %s inexistente.\n", origem);
                continue;
            }

            if (procuraVertice(g, destino) == -1)
            {
                printf("  [ERRO] Destino %s inexistente.\n", destino);
                continue;
            }

			int o = procuraVertice(g, origem);
            int d = procuraVertice(g, destino);

            if(g->vertices[o].tipo == 0 && capacidade > g->vertices[o].pot)
            {
                printf("  [ERRO] Capacidade da ligacao excede a potencia da central!\n");
                continue;
            }
            {

            }

         if (existeLigacao(g, o, d))
            {
                printf("  [ERRO] Ligacao duplicada %s -> %s\n", origem, destino);
                continue;
            }

            adicionarAresta(g, origem, destino, capacidade);
        }

    
        else
        {
            printf("  [ERRO] Comando invalido -> %s", line);

        }
    }

    fclose(fp);

    printf("\n  [OK] Rede carregada com sucesso!\n");
    printf("  Vertices: %d | Ligacoes: %d\n\n", g->n_verti, g->n_arest);

    return 1;
}