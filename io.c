#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"
#include "grafo.h"

#define MAX_LINE 100
int procuraVertice(Grafo *g, char nome[]){
	for(int i=0; i < g->n_verti; i++){
		if(strcmp(g->vertices[i].nome, nome) == 0)
			return 1;
	}

	return 0;
}

int existeLigacao(Grafo *g, int origem, int destino){
	for(int i=0; i < g->n_arest; i++){
		if(g->arestas[i].origem == origem && g->arestas[i].destino == destino)
			return 1;
	}
	
	return 0;
}

int carregaRede(Grafo *g, const char *file){
	FILE *fp = fopen(file, "r");
	
	if(fp == NULL){
		printf("Nao foi possivel abrir o ficheiro.\n");
		return 0;
	}
	
	char line[MAX_LINE];
	while(fgets(line, sizeof(line), fp)){
		char tipo[20];
		
		sscanf(line, "%s", tipo);
		
		//centrais
		if(strcmp(line, "CENTRAL") == 0){
			char nome[50];
			float pot;
			
			if(sscanf(line, "CENTRAL %s %f", nome, &pot) != 2){
				printf("Erro de formato: %s", line);
				continue;
			}
		
			if(pot <= 0){
				printf("Erro: potencia da central %s invalida!\n", nome);
				continue;
			}
		
			if(procuraVertice(g, nome) != -1){
				printf("Erro: vertice %s duplicado.\n", nome);
				continue;
			}
			
			//addVertice(g, nome, 0, pot);->josemar
		}
		
		//subestações
		else if(strcmp(tipo, "SUBESTACAO") == 0){
			char nome[50];
			float pot;
			
			if(sscanf(tipo, "SUBESTACAO %s %f", nome, &pot) != 2){
				printf("Erro de formato: %s", line);
				continue;
			}
		
			if(pot <= 0){
				printf("Erro: carga da subestacao %s invalida!\n", nome);
				continue;
			}
		
			if(procuraVertice(g, nome) != -1){
				printf("Erro: vertice %s duplicado.\n", nome);
				continue;
			}
			
			//addVertice(g, nome, 1, pot);->josemar
		}
		
		//ligacoes
		else if(strcmp(tipo, "LIGACAO") == 0){
			char origem[50], destino[50];
			float capacidade;
			
			if(sscanf(line, "LIGACAO %s %s %f", origem, destino, &capacidade) != 3){
				printf("Erro: de formato: %s", line);
				continue;
			}
			
			if(capacidade <= 0){
				printf("Erro: capacidade invalida!\n");
				continue;
			}
			
			int ori = procuraVertice(g, origem);
			int des = procuraVertice(g, destino);
			
			if(ori == -1){
				printf("Erro: origem %s inexistente.\n", origem);
				continue;
			}
			
			if(des == -1){
				printf("Erro: destino %s inexistente.\n", destino);
				continue;
			}
			
			if(existeLigacao(g, ori, des)){
				printf("Erro: ligacao duplicada %s -> %s", origem, destino);
				continue;
			}
			
			//addAresta(g, ori, des, capacidade)->josemar
		}
		
		else{
			printf("Erro: Comando invalido -> %s", line);
		}
		
	}
	
	fclose(fp);
	printf("\nRede carregada com sucesso!\n");
	printf("Vertices %d.\n", g->n_verti);
	printf("Ligacoes: %d.\n", g->n_arest);
	
	return 1;
}