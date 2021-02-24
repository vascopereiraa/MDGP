/*
 * FILE: pesquisaLocal.c
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
#include <math.h>

#include "pesquisaLocal.h"
#include "initDados.h"
#include "utils.h"
#include "funcoes.h"

// Trepa-Colinas com vizinhança 1
int trepaColinas(int* solucao, init* dadosFicheiro, int* nIteracoes) {
    int *nova_sol, custo, custo_viz;
    int nElementos = dadosFicheiro->nElementos;
    int nSubConj = dadosFicheiro->nSubConjuntos;

    nova_sol = malloc(sizeof(int) * nElementos);

    if(nova_sol == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }

    // Avalia solucao inicial
    custo = calcula_fit(solucao, dadosFicheiro->matriz, nElementos, nSubConj);

    for (int i = 0; i < *nIteracoes; ++i) {
        // Gera vizinho (troca um vertice de cada grupo)
        gera_vizinho(solucao, nova_sol, &nElementos);

        // Avalia vizinho
        custo_viz = calcula_fit(nova_sol, dadosFicheiro->matriz, nElementos, nSubConj);

        // Aceita vizinho se o custo aumentar (problema de maximizacao)
        if (custo_viz > custo) {
            copia(solucao, nova_sol, nElementos);
            custo = custo_viz;
        }
    }

    free(nova_sol);

    return custo;

}

// Trepa-Colinas com vizinhança 2
int trepaColinasViz2(int* solucao, init* dadosFicheiro, int* nIteracoes) {
    int *nova_sol, custo, custo_viz, *nova_sol2, custo_viz2;
    int nElementos = dadosFicheiro->nElementos;
    int nSubConj = dadosFicheiro->nSubConjuntos;

    nova_sol = malloc(sizeof(int) * nElementos);
    nova_sol2= malloc(sizeof(int) * nElementos);

    if(nova_sol == NULL || nova_sol2 == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }

    // Avalia solucao inicial
    custo = calcula_fit(solucao, dadosFicheiro->matriz, nElementos, nSubConj);

    for (int i = 0; i < *nIteracoes; ++i)
    {
        // Gera vizinho (troca um vertice de cada grupo)
        gera_vizinho(solucao, nova_sol, &nElementos);

        // Gera vizinho 2 (troca dois vertices de cada grupo)
        gera_vizinho2(solucao, nova_sol2, &nElementos);

        // Avalia vizinho
        custo_viz = calcula_fit(nova_sol, dadosFicheiro->matriz, nElementos, nSubConj);
        custo_viz2 = calcula_fit(nova_sol2, dadosFicheiro->matriz, nElementos, nSubConj);

        // Aceita vizinho se o custo aumentar (problema de maximizacao)
        // Aceita vizinhos com o mesmo custo
        if(custo_viz >= custo){
            copia(solucao, nova_sol, nElementos);
            custo = custo_viz;
        }
        if (custo_viz2 >= custo)
        {
            copia(solucao, nova_sol2, nElementos);
            custo = custo_viz2;
        }
    }

    free(nova_sol);
    free(nova_sol2);

    return custo;
}

// Trepa-Colinas com vizinhança 3
int trepaColinasViz3(int* solucao, init* dadosFicheiro, int* nIteracoes) {
    int *nova_sol, custo, custo_viz, *nova_sol2, custo_viz2, *nova_sol3, custo_viz3;
    int nElementos = dadosFicheiro->nElementos;
    int nSubConj = dadosFicheiro->nSubConjuntos;

    nova_sol = malloc(sizeof(int) * nElementos);
    nova_sol2= malloc(sizeof(int) * nElementos);
    nova_sol3= malloc(sizeof(int) * nElementos);

    if(nova_sol == NULL || nova_sol2 == NULL || nova_sol3 == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }

    // Avalia solucao inicial
    custo = calcula_fit(solucao, dadosFicheiro->matriz, nElementos, nSubConj);

    for (int i = 0; i < *nIteracoes; ++i)
    {
        // Gera vizinho (troca um vertice de cada grupo)
        gera_vizinho(solucao, nova_sol, &nElementos);

        // Gera vizinho 2 (troca dois vertices de cada grupo)
        gera_vizinho2(solucao, nova_sol2, &nElementos);

        gera_vizinho3(solucao, nova_sol3, &nElementos);

        // Avalia vizinho
        custo_viz = calcula_fit(nova_sol, dadosFicheiro->matriz, nElementos, nSubConj);
        custo_viz2 = calcula_fit(nova_sol2, dadosFicheiro->matriz, nElementos, nSubConj);
        custo_viz3 = calcula_fit(nova_sol3, dadosFicheiro->matriz, nElementos, nSubConj);

        // Aceita vizinho se o custo aumentar (problema de maximizacao)
        // Aceita vizinhos com o mesmo custo
        if(custo_viz >= custo){
            copia(solucao, nova_sol, nElementos);
            custo = custo_viz;
        }
        if (custo_viz2 >= custo)
        {
            copia(solucao, nova_sol2, nElementos);
            custo = custo_viz2;
        }
        if (custo_viz3 >= custo)
        {
            copia(solucao, nova_sol3, nElementos);
            custo = custo_viz3;
        }
    }

    free(nova_sol);
    free(nova_sol2);
    free(nova_sol3);

    return custo;
}

int trepaColinas_prob(int * solucao, init* dadosFicheiro, int* nIteracoes){

    int *nova_sol, *best_sol, custo, custo_best, custo_viz, i;
    double r;
    int nElementos = dadosFicheiro->nElementos;
    int nSubConj = dadosFicheiro->nSubConjuntos;
    nova_sol = malloc(sizeof(int)*nElementos);
    best_sol = malloc(sizeof(int)*nElementos);

    // Avalia solucao inicial
    custo = calcula_fit(solucao, dadosFicheiro->matriz, nElementos, nSubConj);

    copia(best_sol, solucao, nElementos);
    custo_best = custo;

    for(i=0; i < *nIteracoes; i++)
    {
        // Gera vizinho (troca um vertice em cada grupo)
        gera_vizinho(solucao, nova_sol, &nElementos);

        // Avalia vizinho
        custo_viz = calcula_fit(nova_sol,dadosFicheiro->matriz, nElementos, nSubConj);
        // Aceita vizinho se o custo aumentar (problema de maximizacao)
        if (custo_viz > custo)
        {
            copia(solucao, nova_sol, nElementos);
            custo = custo_viz;
        }
        else
        {
            r = rand_01();
            if(r < PROB)
            {
                copia(solucao, nova_sol, nElementos);
                custo = custo_viz;
            }
        }
        if (custo_best < custo)
        {
            copia(best_sol, solucao, nElementos);
            custo_best = custo;
        }
    }

    copia(solucao, best_sol, nElementos);
    custo = custo_best;

    free(nova_sol);
    free(best_sol);
    return custo;
}

int trepaColinas_probViz2(int * solucao, init* dadosFicheiro, int* nIteracoes){

    int *nova_sol, *best_sol, custo, custo_best, custo_viz, i;
    double r;
    int *nova_sol2, custo_viz2;
    int nElementos = dadosFicheiro->nElementos;
    int nSubConj = dadosFicheiro->nSubConjuntos;
    nova_sol = malloc(sizeof(int)*nElementos);
    nova_sol2 = malloc(sizeof(int)*nElementos);
    best_sol = malloc(sizeof(int)*nElementos);

    // Avalia solucao inicial
    custo = calcula_fit(solucao, dadosFicheiro->matriz, nElementos, nSubConj);

    copia(best_sol, solucao, nElementos);
    custo_best = custo;

    for(i=0; i < *nIteracoes; i++)
    {
        // Gera vizinho (troca um vertice em cada grupo)
        gera_vizinho(solucao, nova_sol, &nElementos);
        gera_vizinho2(solucao, nova_sol2, &nElementos);

        // Avalia vizinho
        custo_viz = calcula_fit(nova_sol,dadosFicheiro->matriz, nElementos, nSubConj);
        custo_viz2 = calcula_fit(nova_sol2,dadosFicheiro->matriz, nElementos, nSubConj);

        // Aceita vizinho se o custo aumentar (problema de maximizacao)
        if (custo_viz > custo && custo_viz > custo_viz2)
        {
            copia(solucao, nova_sol, nElementos);
            custo = custo_viz;
        }
        else {
            if (custo_viz2 > custo && custo_viz2 > custo_viz) {
                copia(solucao, nova_sol2, nElementos);
                custo = custo_viz2;
            }
            else
            {
                r = rand_01();
                if (r < PROB) {
                    copia(solucao, nova_sol, nElementos);
                    custo = custo_viz;
                }
            }
        }
        if (custo_best < custo)
        {
            copia(best_sol, solucao, nElementos);
            custo_best = custo;
        }
    }

    copia(solucao, best_sol, nElementos);
    custo = custo_best;

    free(nova_sol);
    free(nova_sol2);
    free(best_sol);
    return custo;
}

int trepaColinas_probViz3(int * solucao, init* dadosFicheiro, int* nIteracoes){

    int *nova_sol, *best_sol, custo, custo_best, custo_viz, i;
    double r;
    int *nova_sol2, custo_viz2;
    int *nova_sol3, custo_viz3;
    int nElementos = dadosFicheiro->nElementos;
    int nSubConj = dadosFicheiro->nSubConjuntos;
    nova_sol = malloc(sizeof(int)*nElementos);
    nova_sol2 = malloc(sizeof(int)*nElementos);
    nova_sol3 = malloc(sizeof(int)*nElementos);
    best_sol = malloc(sizeof(int)*nElementos);

    // Avalia solucao inicial
    custo = calcula_fit(solucao, dadosFicheiro->matriz, nElementos, nSubConj);

    copia(best_sol, solucao, nElementos);
    custo_best = custo;

    for(i=0; i < *nIteracoes; i++)
    {
        // Gera vizinho (troca um vertice em cada grupo)
        gera_vizinho(solucao, nova_sol, &nElementos);
        gera_vizinho2(solucao, nova_sol2, &nElementos);
        gera_vizinho3(solucao, nova_sol3, &nElementos);

        // Avalia vizinho
        custo_viz = calcula_fit(nova_sol,dadosFicheiro->matriz, nElementos, nSubConj);
        custo_viz2 = calcula_fit(nova_sol2,dadosFicheiro->matriz, nElementos, nSubConj);
        custo_viz3 = calcula_fit(nova_sol3,dadosFicheiro->matriz, nElementos, nSubConj);
        // Aceita vizinho se o custo aumentar (problema de maximizacao)
        if (custo_viz > custo && custo_viz > custo_viz2 && custo_viz > custo_viz3)
        {
            copia(solucao, nova_sol, nElementos);
            custo = custo_viz;
        }
        else {
            if (custo_viz2 > custo && custo_viz2 > custo_viz && custo_viz2 > custo_viz3) {
                copia(solucao, nova_sol2, nElementos);
                custo = custo_viz2;
            } else {
                if(custo_viz3 > custo && custo_viz3 > custo_viz && custo_viz3 > custo_viz2) {
                    copia(solucao, nova_sol3, nElementos);
                    custo = custo_viz3;
                }
                else
                {
                    r = rand_01();
                    if (r < PROB) {
                        copia(solucao, nova_sol, nElementos);
                        custo = custo_viz;
                    }
                }
            }
        }
        if (custo_best < custo)
        {
            copia(best_sol, solucao, nElementos);
            custo_best = custo;
        }
    }

    copia(solucao, best_sol, nElementos);
    custo = custo_best;

    free(nova_sol);
    free(nova_sol2);
    free(nova_sol3);
    free(best_sol);
    return custo;
}

int simulated_annealing(int* solucao, init* dadosFicheiro, int* nIteracoes){

    int *nova_sol, custo, custo_viz, i;
    float temp, erro, probAceitar, max = TMAX, min = TMIN;
    int nElementos = dadosFicheiro->nElementos;
    int nSubConj = dadosFicheiro->nSubConjuntos;

    nova_sol = malloc(sizeof(int)*nElementos);
    if(nova_sol == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }

    // Avalia solucao inicial
    custo = calcula_fit(solucao, dadosFicheiro->matriz, nElementos, nSubConj);

    temp = max;
    while(temp >  min)
    {
        temp -= (max - min) / (float) *nIteracoes; // Descer

        //Gera vizinho 2 (troca dois vertices de cada grupo)
        gera_vizinho2(solucao, nova_sol, &nElementos);

        // Avalia vizinho
        custo_viz = calcula_fit(nova_sol, dadosFicheiro->matriz, nElementos, nSubConj);

        if(custo_viz <= custo)
        {
            copia(solucao, nova_sol, nElementos);
            custo = custo_viz;
        }
        else {
            erro = (float) (custo - custo_viz);
            probAceitar = (float) exp(erro / temp);
            if(rand_01() < erro) {
                copia(solucao, nova_sol, nElementos);
                custo = custo_viz;
            }
        }
    }
    free(nova_sol);
    return custo;
}

int simulated_annealingViz2(int * solucao, init* dadosFicheiro, int* nIteracoes){

    int *nova_sol, *nova_sol2, custo, custo_viz, custo_viz2, i;
    float temp, erro, probAceitar, max = TMAX, min = TMIN;
    int nElementos = dadosFicheiro->nElementos;
    int nSubConj = dadosFicheiro->nSubConjuntos;

    nova_sol = malloc(sizeof(int)*nElementos);
    nova_sol2 = malloc(sizeof(int)*nElementos);
    if(nova_sol == NULL || nova_sol2 == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }

    // Avalia solucao inicial
    custo = calcula_fit(solucao, dadosFicheiro->matriz, nElementos, nSubConj);

    temp = max;
    while(temp >  min)
    {
        temp -= (max - min) / (float) *nIteracoes; // Descer

        // Gera vizinho
        gera_vizinho2(solucao, nova_sol, &nElementos);
        gera_vizinho2(solucao, nova_sol2, &nElementos);

        // Avalia vizinho
        custo_viz = calcula_fit(nova_sol, dadosFicheiro->matriz, nElementos, nSubConj);
        custo_viz2 = calcula_fit(nova_sol2, dadosFicheiro->matriz, nElementos, nSubConj);

        if(custo_viz <= custo && custo_viz <= custo_viz2)
        {
            copia(solucao, nova_sol, nElementos);
            custo = custo_viz;
        }
        if (custo_viz2 <= custo && custo_viz2 <= custo_viz) {
            copia(solucao, nova_sol2, nElementos);
            custo = custo_viz2;
        }
        else {
            erro = (float) (custo - custo_viz);
            probAceitar = (float) exp(erro / temp);
            if(rand_01() < erro) {
                copia(solucao, nova_sol, nElementos);
                custo = custo_viz;
            }
        }
    }

    free(nova_sol);
    free(nova_sol2);
    return custo;
}

int simulated_annealingViz3(int * solucao, init* dadosFicheiro, int* nIteracoes){

    int *nova_sol, *nova_sol2, *nova_sol3, custo, custo_viz, custo_viz2, custo_viz3, i;
    float temp, erro, probAceitar, max = TMAX, min = TMIN;
    int nElementos = dadosFicheiro->nElementos;
    int nSubConj = dadosFicheiro->nSubConjuntos;

    nova_sol = malloc(sizeof(int)*nElementos);
    nova_sol2 = malloc(sizeof(int)*nElementos);
    nova_sol3 = malloc(sizeof(int)*nElementos);
    if(nova_sol == NULL || nova_sol2 == NULL || nova_sol3 == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }

    // Avalia solucao inicial
    custo = calcula_fit(solucao, dadosFicheiro->matriz, nElementos, nSubConj);

    temp = max;
    while(temp >  min)
    {
        temp -= (max - min) / (float) *nIteracoes; // Descer

        // Gera vizinho
        gera_vizinho2(solucao, nova_sol, &nElementos);
        gera_vizinho2(solucao, nova_sol2, &nElementos);
        gera_vizinho2(solucao, nova_sol3, &nElementos);

        // Avalia vizinho
        custo_viz = calcula_fit(nova_sol, dadosFicheiro->matriz, nElementos, nSubConj);
        custo_viz2 = calcula_fit(nova_sol2, dadosFicheiro->matriz, nElementos, nSubConj);
        custo_viz3 = calcula_fit(nova_sol3, dadosFicheiro->matriz, nElementos, nSubConj);

        if(custo_viz <= custo && custo_viz <= custo_viz2 && custo_viz <= custo_viz3)
        {
            copia(solucao, nova_sol, nElementos);
            custo = custo_viz;
        }
        if (custo_viz2 <= custo && custo_viz2 <= custo_viz && custo_viz2 <= custo_viz3) {
            copia(solucao, nova_sol2, nElementos);
            custo = custo_viz2;
        }
        if (custo_viz3 <= custo && custo_viz3 <= custo_viz && custo_viz3 <= custo_viz2) {
            copia(solucao, nova_sol2, nElementos);
            custo = custo_viz2;
        }
        else {
            erro = (float) (custo - custo_viz);
            probAceitar = (float) exp(erro / temp);
            if(rand_01() < erro) {
                copia(solucao, nova_sol, nElementos);
                custo = custo_viz;
            }
        }
    }

    free(nova_sol);
    free(nova_sol2);
    free(nova_sol3);
    return custo;
}

int pesquisaTabu(int * solucao, init* dadosFicheiro, int* nIteracoes, int nDescidas, int MudaIteracoes){
    int *nova_sol, custo, custo_viz, custoGlobal=0,tabidx=0, i;
    int inc = 1;
    int nElementos = dadosFicheiro->nElementos;
    int nSubConj = dadosFicheiro->nSubConjuntos;

    nova_sol = malloc(sizeof(int)*nElementos);
    if(nova_sol == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }

    // Avalia solucao inicial
    custo = calcula_fit(solucao, dadosFicheiro->matriz, nElementos, nSubConj);

    for(i=0; i < *nIteracoes; ) {
        // Gera vizinho
        gera_vizinho(solucao, nova_sol, &nElementos);

        // Avalia vizinho
        custo_viz = calcula_fit(nova_sol, dadosFicheiro->matriz, nElementos, nSubConj);

        // Aceita vizinho se o custo aumentar (problema de maximizacao)
        if (custo_viz > custo) {
            tabidx = 0;
            custo = custo_viz;
            if (custo > custoGlobal) {
                custoGlobal = custo_viz;
                copia(solucao, nova_sol, nElementos);
            }
            inc = 1;
        } else {
            if (nDescidas > tabidx) {
                if (MudaIteracoes == 0)
                    inc = 1;
                else
                    inc = 0;

                custo = custo_viz;
                tabidx++;
            } else
                inc = 1;
        }
        if (custoGlobal > custo)
            custo = custoGlobal;

        if (inc == 1)
            i++;
    }
    free(nova_sol);

    return custo;
}

/* Funcoes auxiliares aos algoritmos de Pesquisa Local */

void gera_vizinho(int a[], int b[], int* nElementos) {

    int p1, p2;

    // Copia a solucao atual para a solucao vizinha
    copia(b,a, *nElementos);

    // Encontra aleatoriamente uma posicao com valor 1
    do
        p1 = random_l_h(0, *nElementos - 1);
    while (b[p1] != 0);

    // Encontra aleatoriamente uma posicao com valor 0
    do
        p2 = random_l_h(0, *nElementos - 1);
    while (b[p2] != 1);

    // Troca
    troca(b, p1, p2);
}

void gera_vizinho2(int a[], int b[], int* nElementos) {

    int p1, p2, p3, p4;

    // Copia a solucao atual para a solucao vizinha
    copia(b, a, *nElementos);

    // Encontra aleatoriamente uma posicao com valor 0
    do
        p1 = random_l_h(0, *nElementos - 1);
    while (b[p1] != 0);

    // Encontra aleatoriamente uma posicao com valor 1
    do
        p2 = random_l_h(0, *nElementos - 1);
    while (b[p2] != 1);

    // Troca
    troca(b, p1, p2);

    //Encontra uma nova poiscao com valor 0, que nao seja igual a p1
    do
        p3 = random_l_h(0, *nElementos - 1);
    while (b[p3] != 0 || p3 == p1);

    // Encontra aleatoriamente uma posicao com valor 1, que nao seja igual a p2
    do
        p4 = random_l_h(0, *nElementos - 1);
    while (b[p4] != 1 || p4 == p2);

    // Troca
    troca(b, p3, p4);
}

void gera_vizinho3(int a[], int b[], int* nElementos) {

    int p1, p2, p3, p4, p5, p6, i;

    copia(b, a, *nElementos);

    // Encontra aleatoriamente uma posicao com valor 0
    do
        p1 = random_l_h(0, *nElementos - 1);
    while (b[p1] != 0);

    // Encontra aleatoriamente uma posicao com valor 1
    do
        p2 = random_l_h(0, *nElementos - 1);
    while (b[p2] != 1);

    // Troca
    troca(b, p1, p2);

    //Encontra uma nova poiscao com valor 0, que nao seja igual a p1
    do
        p3 = random_l_h(0, *nElementos - 1);
    while (b[p3] != 0 || p3 == p1);

    // Encontra aleatoriamente uma posicao com valor 1, que nao seja igual a p2
    do
        p4 = random_l_h(0, *nElementos - 1);
    while (b[p4] != 1 || p4 == p2);

    // Troca
    troca(b, p3, p4);

    //Encontra uma nova posicao com valor 0, que nao seja igual a p1 e p3
    do
        p5 = random_l_h(0, *nElementos -1);
    while(b[p5] != 0 || p5 == p1 || p5 == p3);

    //Encontra uma nova posicao com valor 1, que nao seja igual a p2 e p4
    do
        p6 = random_l_h(0,*nElementos -1);
    while(b[p6] != 0 || p6 == p2 || p6 == p4);

    // Troca
    troca(b, p5, p6);
}
