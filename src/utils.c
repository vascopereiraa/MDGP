/*
 * FILE: utils.c
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
#include <time.h>

#include "utils.h"

/* RANDOM */

// Inicializa o gerador de numeros aleatorios
void init_rand() {
    srand((unsigned int) time(NULL));
}

// Devolve valor inteiro aleatorio entre min e max
int random_l_h(int min, int max) {
    return rand() % max + min;
}


// Devolve um valor real aleatorio do intervalo [0, 1]
float rand_01() {
    float x = ((float) rand()) / RAND_MAX;
    return x;
}

/* Manipulacao de Dados */

// Escreve solucao
void escreve_sol(int *sol, int m, int g) {
    int i, subc;

    for (subc = 0; subc < g; subc++) {
        printf("\nConjunto %d: ", subc + 1);
        for (i = 0; i < m; i++)
            if (sol[i] == subc)
                printf("%2d  ", i);
    }
    printf("\n");
}

// Obter o valor da distancia entre dois pontos
int obter_distancia(int **dist, int m, int a, int b) {
    int i, j;
    if (a > b) {
        i = b;
        j = a;
    } else {
        i = a;
        j = b;
    }
    return dist[i][j];
}

// Mostra a distancia entre dois pontos
void mostra_distancia(int **dist, int m, int a, int b) {
    printf("%d\n", obter_distancia(dist, m, a, b));
}

// Copia vector b para a (tamanho n)
void copia(int a[], int b[], int n) {
    int i;
    for (i = 0; i < n; i++)
        a[i] = b[i];
}


// Troca de a para b
void troca(int *sol, int a, int b) {
    int aux;
    aux = sol[b];
    sol[b] = sol[a];
    sol[a] = aux;
}