#ifndef SORT_H
#define SORT_H
#include "./estatisticas.h"

// Insertion sort.
void insertionSort(int *V, int l, int r, Stat *s);

// Quicksort usando a "mediana de 3" e o insertionSort, para evitar os piores casos de tempo de execução.
void quickSort(int *V, int tamParticao, int l, int r, Stat *s); 

void quickSort2(int * A, int l, int r, Stat *s);

// Calcula a partição usada no quicksort, usando a "mediana de 3".
void partition(int *V, int l, int r, int *i, int *j, Stat *s);

// Mediana de 3 inteiros.
int median(int a, int b, int c);

// Troca o valor de 2 chaves.
void swap(int *xp, int *yp, Stat *s);

#endif