/*
 * FILE: initDados.h
 * NOME: Ma Fatima Gomes Rodrigues
 * NR: 2019112924
 *
 * NOME: Vasco Daniel Matos Pereira
 * NR: 2019134744
 *
 * CREATED ON 15/01/2021
 */

#ifndef __INITDADOS_H__
#define __INITDADOS_H__

typedef struct {
    int nElementos;
    int nSubConjuntos; // vert
    int **matriz;
} init;

char* obtemFicheiroLeitura(char* nomeFicheiro);
void imprimeDados(init* dados);
init* initDadosFicheiro(char* nomeFicheiro);

#endif //__INITDADOS_H__