#ifndef ORDENADOR_H
#define ORDENADOR_H

#include "./estatisticas.h"
#include "./sort.h"

// Função que gera numShuffle quebras em um vetor ordenado.
int shuffleVector(int *V, int tam, int numShuffle);

// Função que determina o número de quebras em um vetor (V[i] > V[i+1])
int determinaQuebras(int *V, int tam);

// Função que primeiro escolhe qual vai ser o algoritmo utilizado, e depois ordena o vetor.
void ordenadorUniversal(int *V, int tam, int minTamParticao, int limiarQuebras, int numeroQuebras, Stat *s);

// Função que determina a limiar do tamanho mínimo de partição para que seja melhor utilizar o quickSort comparado ao insertionSort.
int determinaLimiarParticao(int *V, int tam, double limiarCusto, double a, double b, double c);

// Função auxiliar da determinaLimiarParticao. Calcula as faixas seguintes a primeira, "refinando" o número ideal para a limiar.
void calculaNovaFaixa(int indiceLimParticao, CostStat *ps, int *minMPS, int *maxMPS, int *passoMPS, int *newMax, int *newMin, int numMPS);

// Função que determina a limiar do número máximo de quebras para que seja melhor utilizar o insertionSort comparado ao quickSort.
int determinaLimiarQuebra(int *V, int tam, int seed, double limiarCusto, int minTamParticao, double a, double b, double c);

#endif
