/*
 * FILE: funcoes.h
 * NOME: Ma Fatima Gomes Rodrigues
 * NR: 2019112924
 *
 * NOME: Vasco Daniel Matos Pereira
 * NR: 2019134744
 *
 * CREATED ON 15/01/2021
 */
 
#ifndef __FUNCOES_H__
#define __FUNCOES_H__

#include "initDados.h"
#include "evolutivo.h"

int calcula_fit(int a[], int **mat, int m, int g);
int calcula_fit_penalizado(int a[], int **mat, int m, int g, struct info d);
int calcula_div(int sol[], int **mat, int m, int start, int count);
int flip();
void gera_sol_inicial(int *sol, int m, int g);

#endif // __FUNCOES_H__