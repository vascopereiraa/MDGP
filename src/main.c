/*
 * FILE: main.c
 * NOME: Ma Fatima Gomes Rodrigues
 * NR: 2019112924
 *
 * NOME: Vasco Daniel Matos Pereira
 * NR: 2019134744
 *
 * CREATED ON 11/12/2020
 */

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "initDados.h"
#include "evolutivo.h"
#include "pesquisaLocal.h"
#include "funcoes.h"

#define DEFAULT_RUNS 50

int main (int argc, char** argv) {

    if(argc < 3)
        exit(1);

    init_rand();
    init* dados = initDadosFicheiro(argv[1]);

    int m = dados->nElementos;
    int g = dados->nSubConjuntos;
    int** dist = dados->matriz;

    // Local
    int* solucao, *best, nIteracoes, custo, bestCusto = 0;
    int nDescidas = 0;

    // Evolutivo
    int runs = atoi(argv[2]);
    struct info parameters;
    parameters.m = m;
    parameters.g = g;
    parameters.numGenerations = 2100;
    parameters.popsize = 100;
    parameters.pm_swap = 0.01;
    parameters.pr = 0.7;
    parameters.t_size = 3;
    pchrom pop = NULL, parents = NULL;
    chrom best_run, best_ever;
    int gen_actual;

    best_run.sol = calloc(m,sizeof(int));
    best_ever.sol = calloc(m,sizeof(int));

    float mbf = 0.0;
    int i, k;
    Algoritmo algo = Penalizado;
    int hibrido = 0;

    switch (algo) {
        case TrepaColinas:
        case TrepaColinasViz2:
        case TrepaColinasViz3:
        case TrepaColinasProb:
        case TrepaColinasProbViz2:
        case TrepaColinasProbViz3:
        case Recristalizacao:
        case RecristalizacaoViz2:
        case RecristalizacaoViz3:
        case Tabu:
            solucao = malloc(sizeof(int) * dados->nElementos);
            best = malloc(sizeof(int) * dados->nElementos);
            nIteracoes = (int) strtol(argv[2], NULL, 10);
            if(solucao == NULL || best == NULL) {
                fprintf(stderr, "[ERRO] Nao foi possivel alocar memoria!\n");
                exit(1);
            }

            for(i = 0; i < DEFAULT_RUNS; ++i) {

                // Obter solucao inicial
                gera_sol_inicial(solucao, dados->nElementos, dados->nSubConjuntos);

                switch (algo) {
                    case TrepaColinas:
                        custo = trepaColinas(solucao, dados, &nIteracoes);
                        break;
                    case TrepaColinasViz2:
                        custo = trepaColinasViz2(solucao, dados, &nIteracoes);
                        break;
                    case TrepaColinasViz3:
                        custo = trepaColinasViz2(solucao, dados, &nIteracoes);
                        break;
                    case TrepaColinasProb:
                        custo = trepaColinas_prob(solucao, dados, &nIteracoes);
                        break;
                    case TrepaColinasProbViz2:
                        custo = trepaColinas_probViz2(solucao, dados, &nIteracoes);
                        break;
                    case TrepaColinasProbViz3:
                        custo = trepaColinas_probViz2(solucao, dados, &nIteracoes);
                        break;
                    case Recristalizacao:
                        custo = simulated_annealing(solucao, dados, &nIteracoes);
                        break;
                    case RecristalizacaoViz2:
                        custo = simulated_annealingViz2(solucao, dados, &nIteracoes);
                        break;
                    case RecristalizacaoViz3:
                        custo = simulated_annealingViz3(solucao, dados, &nIteracoes);
                        break;
                    case Tabu:
                        custo = pesquisaTabu(solucao, dados, &nIteracoes, nDescidas, 1);
                        break;
                    default:
                        exit(EXIT_FAILURE);
                        break;
                }

                printf("Repeticao %d: ", i + 1);
                escreve_sol(solucao, dados->nElementos, dados->nSubConjuntos);
                printf("Custo Final: %2d\n\n", custo);

                mbf += (float) custo;
                if (i == 0 || bestCusto < custo) {
                    bestCusto = custo;
                    copia(best, solucao, dados->nElementos);
                }
            }

            printf("\nMBF: %f\n", mbf / (float) i);
            printf("\nMelhor solucao encontrada");
            escreve_sol(best, dados->nElementos, dados->nSubConjuntos);
            printf("Custo final: %2d\n", bestCusto);

            // Apaga dados em memória
            for(int j = 0; j < dados->nElementos; ++j)
                free(dados->matriz[j]);
            free(dados->matriz);
            free(dados);
            free(best);
            free(solucao);

            break;
        case Hibrido:
            hibrido = 1;
        case EvolutivoBase:
        case Penalizado:
        case MutacaoTroca:
        case Recombinacao2Pontos:
        case RecombinacaoUniforme:
        case TorneioTernario:
            for(k = 0 ; k < DEFAULT_RUNS; ++k) {

                pop = init_pop(parameters, dist);

                gen_actual = 1;

                atribuicao(&best_run, pop[0], parameters);

                // Inicializar a melhor solucao encontrada
                get_best(pop, parameters, &best_run);

                // Reservar espaco para os pais
                parents = init_parents(parameters);

                // Loop pricipal da Evolucao
                while (gen_actual <= parameters.numGenerations)
                {
                    switch(algo)
                    {
                        case EvolutivoBase:
                            // Torneio binario para encontrar os progenitores (ficam armazenados no vector parents)
                            binary_tournament(pop, parameters, parents);

                            // Aplicar operadores geneticos aos pais (os descendentes ficam armazenados no vector pop)
                            genetic_operators(parents, parameters, pop, dist, algo);

                            // Reavaliar a qualidade da populacao
                            evaluate(pop, parameters, dist);
                            break;
                        case Penalizado:
                            // Torneio binario para encontrar os progenitores (ficam armazenados no vector parents)
                            binary_tournament(pop, parameters, parents);

                            // Aplicar operadores geneticos aos pais (os descendentes ficam armazenados no vector pop)
                            genetic_operators(parents, parameters, pop, dist, algo);

                            //Algoritmo Penalizado
                            evaluate_penalizado(pop, parameters, dist);
                            break;
                        case MutacaoTroca:
                            // Torneio binario para encontrar os progenitores (ficam armazenados no vector parents)
                            binary_tournament(pop, parameters, parents);

                            // Aplicar operadores geneticos aos pais (os descendentes ficam armazenados no vector pop)
                            genetic_operators(parents, parameters, pop, dist, algo);

                            // Reavaliar a qualidade da populacao
                            evaluate(pop, parameters, dist);
                            break;
                        case Recombinacao2Pontos:
                            // Torneio binario para encontrar os progenitores (ficam armazenados no vector parents)
                            binary_tournament(pop, parameters, parents);

                            // Aplicar operadores geneticos aos pais (os descendentes ficam armazenados no vector pop)
                            genetic_operators(parents, parameters, pop, dist, algo);

                            // Reavaliar a qualidade da populacao
                            evaluate(pop, parameters, dist);
                            break;
                        case RecombinacaoUniforme:
                            // Torneio binario para encontrar os progenitores (ficam armazenados no vector parents)
                            binary_tournament(pop, parameters, parents);

                            // Aplicar operadores geneticos aos pais (os descendentes ficam armazenados no vector pop)
                            genetic_operators(parents, parameters, pop, dist, algo);

                            // Reavaliar a qualidade da populacao
                            evaluate(pop, parameters, dist);
                            break;
                        case Hibrido:
                        case TorneioTernario:
                            // Torneio trenario
                            sized_tournament(pop, parameters, parents);

                            // Aplicar operadores geneticos aos pais (os descendentes ficam armazenados no vector pop)
                            genetic_operators(parents, parameters, pop, dist, algo);

                            // Reavaliar a qualidade da populacao
                            evaluate(pop, parameters, dist);
                            break;
                        default:
                            exit(EXIT_FAILURE);
                            break;
                    }

                    // Actualizar a melhor solucao encontrada
                    get_best(pop, parameters, &best_run);

                    gen_actual++;
                }

                if(hibrido == 1)
                    best_run.fitness = trepaColinas(best_run.sol, dados, &runs);

                // Escreve resultados da repeticao que terminou
                printf("\nRepeticao %d:",k);
                escreve_sol(best_run.sol, m, g);
                printf("Custo: %2d\n", best_run.fitness);

                mbf += best_run.fitness;
                if (k == 0 || best_ever.fitness < best_run.fitness)
                {
                    atribuicao(&best_ever,best_run,parameters);
                }

                // Libertar memoria
                // Populacao
                for (i=0; i<parameters.popsize; i++)
                    free(pop[i].sol);
                free(pop);

                // Pais
                for (i=0; i<parameters.popsize; i++)
                    free(parents[i].sol);
                free(parents);
            }

            // Escreve resultados globais
            printf("\n\nMBF: %f\n", mbf/k);
            printf("\nMelhor solucao encontrada");
            escreve_sol(best_ever.sol, m, g);
            printf("Custo final: %2d\n", best_ever.fitness);

            free(best_run.sol);
            free(best_ever.sol);
            break;
        default:
            exit(EXIT_FAILURE);
            break;
    }

    return EXIT_SUCCESS;
}