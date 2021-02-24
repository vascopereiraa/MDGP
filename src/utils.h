/*
 * FILE: utils.h
 * NOME: Ma Fatima Gomes Rodrigues
 * NR: 2019112924
 *
 * NOME: Vasco Daniel Matos Pereira
 * NR: 2019134744
 *
 * CREATED ON 15/01/2021
 */

#ifndef __UTILS_H__
#define __UTILS_H__

typedef enum {
    // Pesquisa Local
    TrepaColinas,
    TrepaColinasViz2,
    TrepaColinasViz3,
    TrepaColinasProb,
    TrepaColinasProbViz2,
    TrepaColinasProbViz3,
    Recristalizacao,
    RecristalizacaoViz2,
    RecristalizacaoViz3,
    Tabu,

    // Evolutivo
    EvolutivoBase,
    Penalizado,
    MutacaoTroca,
    Recombinacao2Pontos,
    RecombinacaoUniforme,
    TorneioTernario,

    // Hibrido
    Hibrido
} Algoritmo;

// Random
void init_rand();
int random_l_h(int min, int max);
float rand_01();

// Manipulacao de dados
void escreve_sol(int *sol, int m, int g);
int obter_distancia(int **dist, int m, int a, int b);
void mostra_distancia(int **dist, int m, int a, int b);
void copia(int a[], int b[], int n);
void troca(int *sol, int a, int b);

#endif // __UTILS_H__
