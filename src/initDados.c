/*
 * FILE: initDados.c
 * NOME: Ma Fatima Gomes Rodrigues
 * NR: 2019112924
 *
 * NOME: Vasco Daniel Matos Pereira
 * NR: 2019134744
 *
 * CREATED ON 15/01/2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "initDados.h"

char* obtemFicheiroLeitura(char* nomeFicheiro) {
    unsigned long tam = strlen(nomeFicheiro);

    // Definicao do ficheiro de trabalho
    char* dir = (char*) malloc(sizeof(char) * (13 + tam));
    if(dir == NULL) {
        fprintf(stderr, "[ERRO] Erro ao criar acesso a localizacao do ficheiro\n");
        exit(1);
    }
    strcpy(dir, "../resources/");
    strcat(dir, nomeFicheiro);

    return dir;
}

void imprimeDados(init* dados) {

    printf("Numero de Elementos: %d\n", dados->nElementos);
    printf("Numero de Subconjuntos: %d\n", dados->nSubConjuntos);

    for(int i = 0; i < dados->nElementos; ++i) {
        for (int j = 0; j < dados->nElementos; ++j)
            printf("%d ", dados->matriz[i][j]);
        puts(" ");
    }
}

init* initDadosFicheiro(char* nomeFich) {

    init* dados;
    FILE* fp;
    int ** matriz;
    char buffer[100];

    // Criacao da estrutura de dados de inicializacao
    dados = (init*) malloc(sizeof(init));
    if(dados == NULL) {
        fprintf(stderr, "[ERRO] Nao foi possivel criar a estrutura de armazenamento de dados\n");
        exit(1);
    }

    // Obtem ficheiro do diretorio "../resources"
    char* nomeFicheiro = obtemFicheiroLeitura(nomeFich);

    // Abrir ficheiro para leitura
    fp = fopen(nomeFicheiro, "r");
    if(fp == NULL) {
        fprintf(stderr, "[ERRO] Nao foi possivel aceder ao ficheiro pretendido!\n");
        exit(1);
    }

    // Leitura do ficheiro
    fscanf(fp, "%d", &dados->nElementos);
    fscanf(fp, "%d", &dados->nSubConjuntos);
    fgets(buffer, 100, fp);

    // Criacao da matriz de distancias
    matriz = (int**) malloc(sizeof(int*) * (dados->nElementos));
    if(matriz == NULL) {
        fprintf(stderr, "[ERRO] Nao foi possivel criar a matriz de distancias\n");
        exit(1);
    }

    for(int i = 0; i < dados->nElementos; ++i) {
        // Inicializar as linhas da matriz com os valores a 0
        matriz[i] = (int*) calloc(dados->nElementos, sizeof(int));
        if(matriz[i] == NULL) {
            fprintf(stderr, "[ERRO] Nao foi possivel criar a matriz de distancias\n");
            exit(1);
        }
    }

    dados->matriz = matriz;

    // Preenchimento da matriz de distancias
    int linha, coluna, valor;
    while(fscanf(fp, "%d %d %d", &linha, &coluna, &valor) == 3) {
        dados->matriz[linha][coluna] = valor;
        dados->matriz[coluna][linha] = valor;
    }

    // Apagar dados desnecessario em memoria
    free(nomeFicheiro);

    // Fechar ficheiro
    fclose(fp);

    return dados;
}