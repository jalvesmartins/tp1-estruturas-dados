#include "../include/sort.h"

/* Para os algoritmos abaixo, os valores L e R representam os limites à esquerda
e à direita de um vetor. São importantes na hora da recursão. Além disso, o stat
* s é um ponteiro para a estrutura que armazena as estatísticas de performance
do algoritmo. A descrição de o que cada uma das funções representa está no
arquivo sort.h e na documentação. */

void insertionSort(int *v, int l, int r, Stat *s) {
  increaseCalls(s, 1);
  int j = 0, aux = 0;

  // Primeiro loop, "empurra" os elementos maiores que v[i] para frente, abrindo
  // espaço para v[i].
  for (int i = l + 1; i <= r; i++) {
    increaseMove(s, 1);
    aux = v[i];
    j = i - 1;

    // Verifica se o número v[i] é menor que o seu antecessor, e vai movendo ele
    // até encontrar sua posição correta no subvetor.
    while ((j >= 0) && (v[j] > aux)) {
      increaseCmp(s, 1);
      increaseMove(s, 1);
      v[j + 1] = v[j];
      j--;
    }
    increaseCmp(s, 1);

    // Coloca o v[i] na sua posição correta
    if (i != j) {
      increaseMove(s, 1);
      v[j + 1] = aux;
    }
  }
  return;
}

void quickSort(int *A, int tamParticao, int l, int r, Stat *s) {
  increaseCalls(s, 1);
  // Caso base
  if (l >= r) return;

  int i = 0, j = 0;

  // Primeira partição
  partition(A, l, r, &i, &j, s);

  // Partições recursivas, com verificação para o insertion sort
  if (l < j) {
    if ((j - l) < tamParticao) {
      insertionSort(A, l, j, s);

    } else {
      quickSort(A, tamParticao, l, j, s);
    }
  }

  if (i < r) {
    if ((r - i) < tamParticao) {
      insertionSort(A, i, r, s);

    } else {
      quickSort(A, tamParticao, i, r, s);
    }
  }
}

void partition(int *A, int l, int r, int *i, int *j, Stat *s) {
  increaseCalls(s, 1);
  // Escolhe o pivô, sendo o médio do primeiro, último e elemento do meio.
  *i = l;
  *j = r;
  int pivot = median(A[l], A[r], A[(l + r) / 2]);

  // Anda com i e j ate encontrar os elementos que devem ser trocados, ou seja,
  // A[i] > pivot e A[j] < pivot.
  do {
    while (A[*i] < pivot) {
      increaseCmp(s, 1);
      (*i)++;
    }
    increaseCmp(s, 1);

    while (A[*j] > pivot) {
      increaseCmp(s, 1);
      (*j)--;
    }
    increaseCmp(s, 1);

    // Se eles não se cruzaram ainda, faz a troca e anda +1 posição com i e j.
    if (*i <= *j) {
      swap(&A[*i], &A[*j], s);
      (*i)++;
      (*j)--;
    }

  } while (*i <= *j);
}

int median(int a, int b, int c) {
  if ((a <= b) && (b <= c)) return b;  // a b c
  if ((a <= c) && (c <= b)) return c;  // a c b
  if ((b <= a) && (a <= c)) return a;  // b a c
  if ((b <= c) && (c <= a)) return c;  // b c a
  if ((c <= a) && (a <= b)) return a;  // c a b
  return b;                            // c b a
}

void swap(int *xp, int *yp, Stat *s) {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
  increaseMove(s, 3);
}