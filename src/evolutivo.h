/*
 * FILE: evolutivo.h
 * NOME: Ma Fatima Gomes Rodrigues
 * NR: 2019112924
 *
 * NOME: Vasco Daniel Matos Pereira
 * NR: 2019134744
 *
 * CREATED ON 15/01/2021
 */

#ifndef __EVOLUTIVO__
#define __EVOLUTIVO__

#include "utils.h"

struct info {
    int m;
    int g;
    int popsize;
    float pm_swap;
    float pr;
    int t_size;
    int numGenerations;
};

typedef struct individual chrom, *pchrom;
struct individual {
    int* sol; //solucao
    int fitness; // distancia (qualidade)
};

// Torneios
void binary_tournament(pchrom pop, struct info d, pchrom parents);
void sized_tournament(pchrom pop, struct info d, pchrom parents);
void genetic_operators(pchrom parents, struct info d, pchrom offspring, int** dist, Algoritmo algo);

// Recombinacoes
void crossover(pchrom parents, struct info d, pchrom offspring);
void recombination(pchrom parents, struct info d, pchrom offspring, int** dist);
void recombination_uniform(pchrom parents,struct info d, pchrom offspring, int **dist);
void cx_order(int p1[], int p2[], int d1[], int d2[], struct info d);
void cx_order2(int p1[], int p2[], int d1[], int d2[], struct info d);

// Mutacoes
void mutation(struct info d, pchrom offspring);
void mutation_swap(struct info d, int a[]);
void mutation_binary(struct info d, pchrom offspring);

// Funcoes auxiliares aos algoritmos evolutivos
pchrom init_pop(struct info d, int** dist);
pchrom init_parents(struct info d);
void evaluate(pchrom pop, struct info d, int** dist);
void evaluate_penalizado(pchrom pop, struct info d, int ** dist);
void get_best(pchrom pop, struct info d, pchrom best);
void atribuicao(pchrom a, chrom b, struct info d);

#endif // __EVOLUTIVO__