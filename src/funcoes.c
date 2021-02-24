/*
 * FILE: funcoes.c
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

#include "funcoes.h"
#include "utils.h"

int calcula_fit(int a[], int **mat, int m, int g) {
    int *sol;
    int total = 0, conta, invalidos = 0;
    int i, idx = 0, subc;
    int n = m/g;

    // Coloca solucao num vector
    sol = malloc(sizeof(int) * m);
    for (subc = 0; subc < g; subc++) {
        conta = 0;
        for (i = 0; i < m; i++) {
            if (a[i] == subc) {
                sol[idx++] = i;
                conta++;
            }
        }
        //se encontrar uma solucao em que n != m/g, a solucao e considerada invalida
        if (conta != n){
            return 0;
        }
    }

    // qualidade = diversidade(0) + diversidade(1) + ... + diversidade(g)
    for (i = 0; i < g; i++)
        total += calcula_div(sol, mat, m, i * (m / g), m / g);

    free(sol);

    return total;
}

int calcula_fit_penalizado(int a[], int **mat, int m, int g, struct info d) {
    int *sol;
    int total = 0, conta, invalidos = 0, penalizacao = 0, ro = 0;
    int i, idx = 0, subc;
    int n = m/g;

    // Coloca solucao num vector
    sol = malloc(sizeof(int) * m);
    for (subc = 0; subc < g; subc++) {
        conta = 0;
        for (i = 0; i < m; i++) {
            if (a[i] == subc) {
                sol[idx++] = i;
                conta++;
            }
        }
        //se encontrar uma solucao em que n != m/g, a solucao e considerada invalida e e penalizada
        if (conta != n){
            penalizacao = 1;
        }
    }

    if(penalizacao) {
        for (i = 0; i < g; i++) {
            total += calcula_div(sol, mat, m, i * (m / g), m / g);
        }
        free(sol);
        ro = (n * d.g) * d.m;

        return total - ro;
    }

    // qualidade = diversidade(0) + diversidade(1) + ... + diversidade(g)
    for (i = 0; i < g; i++)
        total += calcula_div(sol, mat, m, i * (m / g), m / g);

    free(sol);

    return total;
}

int calcula_div(int sol[], int **mat, int m, int start, int count) {
    int div = 0;
    int i, j;

    for (i = start; i < (start + count); i++)
        for (j = i + 1; j < (start + count); j++)
            div += obter_distancia(mat, m, sol[i], sol[j]);

    return div;
}

// Simula o lancamento de uma moeda
int flip() {
    if ((((float) rand()) / RAND_MAX) < 0.5)
        return 0;

    else
        return 1;
}

// Gera a solucao inicial
void gera_sol_inicial(int *sol, int m, int g) {
    int i, x, subc;

    // Primeiro sub-conjunto: 0
    for (i = 0; i < m; i++)
        sol[i] = 0;

    // Restante sub-conjuntos: 1,2,3... g
    for (subc = 1; subc < g; subc++)
        for (i = 0; i < m / g; i++) {
            do
                x = random_l_h(0, m - 1);
            while (sol[x] != 0);
            sol[x] = subc;
        }
}