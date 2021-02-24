/*
 * FILE: evolutivo.c
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

#include "evolutivo.h"
#include "utils.h"
#include "funcoes.h"

/* TORNEIOS */

void binary_tournament(pchrom pop, struct info d, pchrom parents) {
    int i, x1, x2;

    for (i = 0; i < d.popsize; i++) {
        x1 = random_l_h(0, d.popsize - 1);
        do
            x2 = random_l_h(0, d.popsize - 1);
        while (x1 == x2);

        // Problema de maximizacao
        if ((pop + x1)->fitness < (pop + x2)->fitness) {
            atribuicao(parents + i, *(pop + x2), d);
        } else {
            atribuicao(parents + i, *(pop + x1), d);
        }
    }
}

// Seleccao por torneio de tamanho t_size
void sized_tournament(pchrom pop, struct info d, pchrom parents) {
    int i, j, max;

    int *xvect = malloc(sizeof(int) * d.t_size);
    if (!xvect) return;

    for (i = 0; i < d.popsize; i++) {
        for (j = 0; j < d.t_size; j++) {
            //Deveria se já foi escolhido
            xvect[j] = random_l_h(0, d.popsize - 1);
        }

        max = xvect[0];
        for (j = 1; j < d.t_size; j++) {
            // Problema de maximizacao: só sai um pai
            if ((pop + xvect[j])->fitness > (pop + max)->fitness)
                max = xvect[j];
        }

        atribuicao(parents + i, *(pop + max), d);
    }

    free(xvect);
}

// Operadores geneticos
void genetic_operators(pchrom parents, struct info d, pchrom offspring, int **dist, Algoritmo algo) {

    switch (algo)
    {
        case EvolutivoBase:
        case Penalizado:
            crossover(parents, d, offspring);
            mutation_binary(d, offspring);
            break;
        case MutacaoTroca:
            crossover(parents, d, offspring);
            mutation(d, offspring);
            break;
        case Recombinacao2Pontos:
            recombination(parents, d, offspring, dist);
            mutation(d, offspring);
            break;
        case RecombinacaoUniforme:
        case TorneioTernario:
        case Hibrido:
            recombination_uniform(parents, d, offspring, dist);
            mutation(d, offspring);
            break;
        default:
            exit(EXIT_FAILURE);
            break;
    }
}

/* RECOMBINACOES */
void crossover(pchrom parents, struct info d, pchrom offspring)
{
    int i;

    for (i = 0; i < d.popsize; i += 2) {
        if (rand_01() < d.pr) {
            // Recombinar
            cx_order((parents + i)->sol, (parents + i + 1)->sol, (offspring + i)->sol, (offspring + i + 1)->sol, d);
        } else {
            // Sem recombinacao
            atribuicao(offspring + i, *(parents + i), d);
            atribuicao(offspring + i + 1, *(parents + i + 1), d);
        }

        (offspring + i)->fitness = (offspring + i + 1)->fitness = 0;
    }
}

// Chama a funcao cx_order que implementa a recombinacao por ordem (com probabilidade pr)
void recombination(pchrom parents, struct info d, pchrom offspring, int **dist) {
    int i;

    for (i = 0; i < d.popsize; i += 2) {
        if (rand_01() < d.pr) {
            // Recombinar
            cx_order2((parents + i)->sol, (parents + i + 1)->sol, (offspring + i)->sol, (offspring + i + 1)->sol, d);
        } else {
            // Sem recombinacao
            atribuicao(offspring + i, *(parents + i), d);
            atribuicao(offspring + i + 1, *(parents + i + 1), d);
        }

        (offspring + i)->fitness = (offspring + i + 1)->fitness = 0;
    }

}

void recombination_uniform(pchrom parents, struct info d, pchrom offspring, int **dist) {
    int i;

    for (i = 0; i < d.popsize; i += 2) {
        if (flip() < d.pr) {
            // Recombinar
            cx_order((parents + i)->sol, (parents + i + 1)->sol, (offspring + i)->sol, (offspring + i + 1)->sol, d);
        } else {
            // Sem recombinacao
            atribuicao(offspring + i, *(parents + i), d);
            atribuicao(offspring + i + 1, *(parents + i + 1), d);
        }

        (offspring + i)->fitness = (offspring + i + 1)->fitness = 0;
    }

}

void cx_order(int p1[], int p2[], int d1[], int d2[], struct info d) {
    int i, aceites;
    int *tab1, *tab2, *conj;
    double prob = 0.5;
    double r;

    tab1 = (int *) calloc(d.m, sizeof(int));
    if (!tab1) {
        printf("Erro na alocacao de memoria");
        exit(1);
    }

    tab2 = (int *) calloc(d.m, sizeof(int));
    if (!tab2) {
        printf("Erro na alocacao de memoria");
        exit(1);
    }

    conj = (int *) calloc(d.g, sizeof(int));
    if (!conj) {
        printf("Erro na alocacao de memoria");
        exit(1);
    }

    // Primeiro descendente
    i = 0;
    aceites = 0;
    while (1) {
        // Verificar
        if (aceites >= d.m)
            break;

        // Ultimo
        if (i >= d.m) {
            i = 0;
            continue;
        }

        r = rand_01();
        if (r < prob) {
            // Verifica se ja ultrapassa do limite
            if (conj[p1[i]] >= (d.m / d.g) || tab1[i] == 1) {
                if (conj[p2[i]] >= (d.m / d.g) || tab2[i] == 1) {
                    // Ultimo: Proteccao
                    if (i == d.m - 1)
                        i = 0;
                    else
                        i++;
                    continue;
                } else {
                    d1[aceites] = p2[i];
                    tab2[i] = 1;
                }
            } else {
                d1[aceites] = p1[i];
                tab1[i] = 1;
            }
        } else {
            // Verifica se ja ultrapassa do limite
            if (conj[p2[i]] >= (d.m / d.g) || tab2[i] == 1) {
                if (conj[p1[i]] >= (d.m / d.g) || tab1[i] == 1) {
                    // Ultimo: Proteccao
                    if (i == d.m - 1)
                        i = 0;
                    else
                        i++;
                    continue;
                } else {
                    d1[aceites] = p1[i];
                    tab1[i] = 1;
                }
            } else {
                d1[aceites] = p2[i];
                tab2[i] = 1;
            }
        }

        conj[d1[aceites]]++;

        aceites++;
        i++;
    }

    // Liberta memória
    free(conj);
    free(tab1);
    free(tab2);
}

// Recombinacao por ordem
void cx_order2(int p1[], int p2[], int d1[], int d2[], struct info d) {
    int i, aceites;
    int *tab1, *tab2, *conj;
    double prob = 0.5;
    double r;

    tab1 = (int *) calloc(d.m, sizeof(int));
    if (!tab1) {
        printf("Erro na alocacao de memoria");
        exit(1);
    }

    tab2 = (int *) calloc(d.m, sizeof(int));
    if (!tab2) {
        printf("Erro na alocacao de memoria");
        exit(1);
    }

    conj = (int *) calloc(d.g, sizeof(int));
    if (!conj) {
        printf("Erro na alocacao de memoria");
        exit(1);
    }

    // Primeiro descendente
    i = 0;
    aceites = 0;
    while (1) {
        // Verificar
        if (aceites >= d.m)
            break;

        // Ultimo
        if (i >= d.m) {
            i = 0;
            continue;
        }

        r = rand_01();
        if (r < prob) {
            // Verifica se ja ultrapassa do limite
            if (conj[p1[i]] >= (d.m / d.g) || tab1[i] == 1) {
                if (conj[p2[i]] >= (d.m / d.g) || tab2[i] == 1) {
                    // Ultimo: Proteccao
                    if (i == d.m - 1)
                        i = 0;
                    else
                        i++;
                    continue;
                } else {
                    d1[aceites] = p2[i];
                    tab2[i] = 1;
                }
            } else {
                d1[aceites] = p1[i];
                tab1[i] = 1;
            }
        } else {
            // Verifica se ja ultrapassa do limite
            if (conj[p2[i]] >= (d.m / d.g) || tab2[i] == 1) {
                if (conj[p1[i]] >= (d.m / d.g) || tab1[i] == 1) {
                    // Ultimo: Proteccao
                    if (i == d.m - 1)
                        i = 0;
                    else
                        i++;
                    continue;
                } else {
                    d1[aceites] = p1[i];
                    tab1[i] = 1;
                }
            } else {
                d1[aceites] = p2[i];
                tab2[i] = 1;
            }
        }

        conj[d1[aceites]]++;

        aceites++;
        i++;
    }



    // Segundo descendente
    i = 0;
    aceites = 0;
    while (i < d.m) {
        // Proteccao
        if (aceites >= d.m)
            break;

        // Restantes para o descendente 2
        if (tab1[i] == 0) {
            d2[aceites++] = p1[i];
        }
        if (tab2[i] == 0) {
            d2[aceites++] = p2[i];
        }
        i++;
    }


    // Liberta memória
    free(conj);
    free(tab1);
    free(tab2);
}

/* Mutacoes */

// Chama as funcoes que implementam as operacoes de mutacao (de acordo com as respectivas probabilidades)
void mutation(struct info d, pchrom offspring) {
    int i;

    for (i = 0; i < d.popsize; i++) {
        if (rand_01() < d.pm_swap) {
            mutation_swap(d, (offspring + i)->sol);
        }
    }
}

// Mutacao swap
void mutation_swap(struct info d, int a[]) {
    int x, y, z;

    x = random_l_h(0, d.m - 1);
    do {
        y = random_l_h(0, d.m - 1);
    } while (x == y || a[x] == a[y]);

    z = a[x];
    a[x] = a[y];
    a[y] = z;
}

// Mutacao binaria
void mutation_binary(struct info d, pchrom offspring) {

    int i, j;

    for (i = 0; i < d.popsize; i++)
        for (j = 0; j < d.g; j++)
            if (rand_01() < d.pm_swap)
                offspring[i].sol[j] = !(offspring[i].sol[j]);

}

/* Funcoes auxiliares aos algoritmos evolutivos */

// Criacao da populacao inicial. O vector e alocado dinamicamente
pchrom init_pop(struct info d, int **dist) {
    int i;

    // Linhas
    pchrom p = malloc(sizeof(chrom) * d.popsize);
    if (!p) {
        printf("Erro na alocacao de memoria\n");
        exit(1);
    }

    for (i = 0; i < d.popsize; i++) {
        // Colunas de cada linha
        p[i].sol = (int *) calloc(d.m, sizeof(int));
        if (!p[i].sol) {
            printf("Erro na alocacao de memoria para linha %d\n", i);
            exit(1);
        }

        gera_sol_inicial(p[i].sol, d.m, d.g);

        p[i].fitness = calcula_fit(p[i].sol, dist, d.m, d.g);
    }

    return p;
}

// Criacao dos pais. O vector e alocado dinamicamente
pchrom init_parents(struct info d) {
    int i;
    pchrom parents = malloc(sizeof(chrom) * d.popsize);

    if (!parents) {
        printf("Erro na alocacao de memoria\n");
        exit(1);
    }
    for (i = 0; i < d.popsize; i++) {
        // Colunas de cada linha
        parents[i].sol = (int *) calloc(d.m, sizeof(int));
        if (!parents[i].sol) {
            printf("Erro na alocacao de memoria para linha %d\n", i);
            exit(1);
        }
        // Inicializa
        parents[i].fitness = 0;
    }
    return parents;
}

// Avaliar cada solucao da populacao
void evaluate(pchrom pop, struct info d, int **dist) {
    int i;
    for (i = 0; i < d.popsize; i++)
        pop[i].fitness = calcula_fit(pop[i].sol, dist, d.m, d.g);
}

// Avaliar cada solucao da populacao com penalizacao
void evaluate_penalizado(pchrom pop, struct info d, int ** dist){
    int i;
    for (i = 0; i < d.popsize; i++)
        pop[i].fitness = calcula_fit_penalizado(pop[i].sol, dist, d.m, d.g, d);

}

// Actualiza a melhor solucao encontrada
void get_best(pchrom pop, struct info d, pchrom best) {
    int i;
    for (i = 0; i < d.popsize; i++) {
        if (best->fitness < pop[i].fitness)
            atribuicao(best, pop[i], d);
    }
}

// Igualar uma solucao de uma populacao
void atribuicao(pchrom a, chrom b, struct info d) {
    copia(a->sol, b.sol, d.m);
    a->fitness = b.fitness;
}
