/*
 * FILE: pesquisaLocal.h
 * NOME: Ma Fatima Gomes Rodrigues
 * NR: 2019112924
 *
 * NOME: Vasco Daniel Matos Pereira
 * NR: 2019134744
 *
 * CREATED ON 15/01/2021
 */
 
#ifndef __PESQUISA_LOCAL_H__
#define __PESQUISA_LOCAL_H__

#include "initDados.h"

#define PROB 0.01
#define TMAX 1
#define TMIN 0.00001

// Algortimos de Pesquisa Local
int trepaColinas(int* solucao, init* dadosFicheiro, int* nIteracoes);
int trepaColinasViz2(int* solucao, init* dadosFicheiro, int* nIteracoes);
int trepaColinasViz3(int* solucao, init* dadosFicheiro, int* nIteracoes);
int trepaColinas_prob(int * solucao, init* dadosFicheiro, int* nIteracoes);
int trepaColinas_probViz2(int * solucao, init* dadosFicheiro, int* nIteracoes);
int trepaColinas_probViz3(int * solucao, init* dadosFicheiro, int* nIteracoes);
int simulated_annealing(int * solucao, init* dadosFicheiro, int* nIteracoes);
int simulated_annealingViz2(int * solucao, init* dadosFicheiro, int* nIteracoes);
int simulated_annealingViz3(int * solucao, init* dadosFicheiro, int* nIteracoes);
int pesquisaTabu(int * solucao, init* dadosFicheiro, int* nIteracoes, int nDescidas, int MudaIteracoes);

// Funcoes auxiliares aos algoritmos de Pesquisa Local
void gera_vizinho(int a[], int b[], int* nElementos);
void gera_vizinho2(int a[], int b[], int* nElementos);
void gera_vizinho3(int a[], int b[], int* nElementos);

#endif //__PESQUISA_LOCAL_H__