#include "../include/ordenador.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/sort.h"

int shuffleVector(int *V, int tam, int numShuffle) {
  int p1 = 0, p2 = 0, temp;
  for (int t = 0; t < numShuffle; t++) {
    /* Gera dois índices distintos no intervalo [0..size-1] */
    while (p1 == p2) {
      p1 = (int)(drand48() * tam);
      p2 = (int)(drand48() * tam);
    }
    /* Realiza a troca para introduzir uma quebra */
    temp = V[p1];
    V[p1] = V[p2];
    V[p2] = temp;
    p1 = p2 = 0;
  }
  return 0;
}

int determinaQuebras(int *V, int tam) {
  int quebras = 0;
  // Para cada vez que um número for maior que seu sucessor, aumenta 1 quebra.
  for (int i = 0; i < tam - 1; i++) {
    if (V[i] > V[i + 1]) {
      quebras++;
    }
  }
  return quebras;
}

void ordenadorUniversal(int *V, int tam, int minTamParticao, int limiarQuebras, int numeroQuebras, Stat *s) {
  // Se o número de quebras for menor que a limiar determinada (Vetor quase ordenado), usa o insertionSort.
  if (numeroQuebras < limiarQuebras) {
    insertionSort(V, 0, tam - 1, s);
  } else {
    // Se o tamanho do vetor for maior que a limiar de partições, usa o quickSort.
    if (tam > minTamParticao) {
      quickSort(V, minTamParticao, 0, tam - 1, s);

      // Caso contrário, usa o insertionSort.
    } else {
      insertionSort(V, 0, tam - 1, s);
    }
  }
}

int determinaLimiarParticao(int *V, int tam, double limiarCusto, double a, double b, double c) {
  int contador = 0;
  int indiceLimParticao = 0;  // Indice onde está a melhor limiar de partição.
  int numMPS = 5;             // Número de limiares de partição em uma iteração.
  int minMPS = 2;             // Limite inferior de um intervalo de partições para uma iteração.
  int maxMPS = tam;           // Limite superior de um intervalo de partições para uma iteração.

  float diffCusto = limiarCusto + 1;     // Diferença de custo entre os limites de uma iteração.
  int passoMPS = (maxMPS - minMPS) / 5;  // Intervalo entre os 6 números de partição usados em uma iteração.

  Stat s = {0};               // Estrutura que armazena as estatísticas de uma execução de algoritmo de ordenação.
  CostStat ps[10] = {0};      // Vetor que guarda todos os valores de limiar e custos de diferentes valores de partição em uma iteração.

  // Roda iterações até que o custo de um intervalo seja menor que a limiar de custo 
  // passada na entrada, ou que o intervalo tenha menos de 5 valores.
  while ((diffCusto > limiarCusto) && (numMPS >= 5)) {
    // Imprime o número da iteração.
    printf("iter %d\n", contador);

    // Zera o numMPS antes de todas as iterações.
    numMPS = 0;

    // Para cada tamanho t de partição, roda o loop, até que chegue no limite superior do intervalo.
    for (int t = minMPS; t <= maxMPS; t += passoMPS) {
      // É usada uma cópia do vetor V, para manter o mesmo vetor para todas os testes.
      int *Vcopia = malloc(tam * sizeof(int));
      if (Vcopia == NULL) {
        printf("Erro de alocação de memória (Vcopia)\n");   //Verificação de alocação.
        return 1;
      }
      memcpy(Vcopia, V, tam * sizeof(int));

      // O ordenador é chamado, e logo após as estatísticas são registradas no vetor ps e impressas na tela.
      ordenadorUniversal(Vcopia, tam, t, 1, 1, &s);
      registraEstatisticas(a, b, c, numMPS, t, s, ps);
      imprimeEstatisticas(numMPS, &s, ps);

      numMPS++;

      // Resetamos o struct s, para que o próximo algoritmo tenha suas
      // estatísticas registradas nele (Como registramos o custo no vetor ps,
      // podemos reutilizar o mesmo s para todos testes).
      resetCounter(&s);

      // Libera a memória da cópia do vetor.
      free(Vcopia);
    }

    // Cria variáveis para os índice que vão representar a nova faixa de partições.
    int newMin = 0, newMax = 0;

    // Atribui o índice do vetor ps que contém o menor custo ao limiar de partição.
    indiceLimParticao = indiceMenorCusto(ps, numMPS);

    // Calcula a nova faixa de partições baseado no índice do vetor ps: "limParticao".
    calculaNovaFaixa(indiceLimParticao, ps, &minMPS, &maxMPS, &passoMPS, &newMax, &newMin, numMPS);

    // Diferença de custo entre as partições limites da nova faixa.
    diffCusto = fabs(getCusto(ps, newMin) - getCusto(ps, newMax));

    // Imprime as conclusões da iteração, contendo o número de partições na
    // faixa, o limiar de partição que obteve o melhor desempenho e o diffCusto.
    printf("nummps %d limParticao %d mpsdiff %.6f\n\n", numMPS, getMPS(ps, indiceLimParticao), diffCusto);

    contador++;
  }
  // Retorna o limiar de partição calculado pelo algorítmo.
  return getMPS(ps, indiceLimParticao);
}

void calculaNovaFaixa(int indiceLimParticao, CostStat *ps, int *minMPS, int *maxMPS, int *passoMPS, int *newMax, int *newMin, int numMPS) {
  // Se a posição da partição de menor custo, no vetor ps, for 0, escolhe o intervalo [0,2].
  if (indiceLimParticao == 0) {
    *newMin = 0;
    *newMax = 2;

    // Se a posição da partição de menor custo, no vetor ps, for 5, escolhe o intervalo [3,5].
  } else if (indiceLimParticao == numMPS - 1) {
    *newMin = numMPS - 3;
    *newMax = numMPS - 1;

    // C.C, escolhe o intervalo [limParticao-1 , limParticao+1].
  } else {
    *newMin = indiceLimParticao - 1;
    *newMax = indiceLimParticao + 1;
  }

  // Atribui os valores da partição às variáveis.
  *minMPS = getMPS(ps, *newMin);
  *maxMPS = getMPS(ps, *newMax);
  *passoMPS = (int)(*maxMPS - *minMPS) / 5;

  // Medida de proteção, para que haja um passoMPS válido caso o resultado da divisão dê 0.
  if (*passoMPS == 0) (*passoMPS)++;
}

int determinaLimiarQuebra(int *V, int tam, int seed, double limiarCusto, int minTamParticao, double a, double b, double c) {
  int contador = 0;
  int indiceLimQuebras = 0;
  int numMQS = 5;        // Número de limiares de quebra em uma iteração.
  int minMQS = 1;        // Limite superior de um intervalo de partições para uma iteração.
  int maxMQS = tam / 2;  // Limite inferior de um intervalo de partições para uma iteração.

  float diffCusto = limiarCusto + 1;     // Diferença de custo entre os limites de uma iteração.
  int passoMQS = (maxMQS - minMQS) / 5;  // Intervalo entre os 6 números de limiar usados em uma iteração.

  Stat s = {0};                     // Estrutura que armazena as estatísticas de uma execução de um algoritmo de ordenação.
  CostStat QuickPs[10] = {0};       // Vetor que guarda todos os valores de limiar e custos das execuções do quickSort.
  CostStat InsertPs[10] = {0};      // Vetor que guarda todos os valores de limiar e custos das execuções do quickSort.

  // Roda iterações até que o custo de um intervalo seja menor que a limiar de
  // custo passada na entrada, ou que o intervalo tenha menos de 5 valores
  while ((diffCusto > limiarCusto) && (numMQS >= 5)) {
    // Imprime o número da iteração.
    printf("iter %d\n", contador);

    // Zera o numMQS antes de todas as iterações.
    numMQS = 0;

    // Para cada tamanho t de partição, roda o loop, até que chegue no limite superior do intervalo.
    for (int t = minMQS; t <= maxMQS; t += passoMQS) {
      // São usadas duas cópias do vetor ordenado, uma para cada algoritmo.
      int *Vcopia = malloc(tam * sizeof(int));
      if (Vcopia == NULL) {
        printf("Erro de alocação de memória (Vcopia)\n");   //Verificação de alocação.
        return 1;
      }
      int *Vcopia2 = malloc(tam * sizeof(int));
      if (Vcopia2 == NULL) {
        printf("Erro de alocação de memória (Vcopia2)\n");  //Verificação de alocação.
        return 1;
      }
      memcpy(Vcopia, V, tam * sizeof(int));
      memcpy(Vcopia2, V, tam * sizeof(int));

      // Embaralhamento dos vetores segundo a limiar (Feito duas vezes para manter o embaralhamento idêntico).
      srand48(seed);
      shuffleVector(Vcopia, tam, t);

      srand48(seed);
      shuffleVector(Vcopia2, tam, t);

      quickSort(Vcopia, minTamParticao, 0, tam - 1, &s);
      registraEstatisticas(a, b, c, numMQS, t, s, QuickPs);
      printf("qs lq %d cost %.9lf cmp %d move %d calls %d\n", getMPS(QuickPs, numMQS), getCusto(QuickPs, numMQS), s.cmp, s.move, s.calls);

      resetCounter(&s);  // Reseta os stats para o outro algoritmo.

      insertionSort(Vcopia2, 0, tam - 1, &s);
      registraEstatisticas(a, b, c, numMQS, t, s, InsertPs);
      printf("in lq %d cost %.9lf cmp %d move %d calls %d\n", getMPS(InsertPs, numMQS), getCusto(InsertPs, numMQS), s.cmp, s.move, s.calls);

      numMQS++;
      resetCounter(&s);

      // Libera as memórias da cópias do vetor.
      free(Vcopia);
      free(Vcopia2);
    }

    // Cria variáveis para os índice que vão representar a nova faixa de limiares.
    int newMin = 0, newMax = 0;

    // Atribui o índice do vetor ps que contém a menor diferença entre o custo dos dois algoritmos diferentes.
    indiceLimQuebras = indiceMenorDiferenca(InsertPs, QuickPs, numMQS);

    // Calcula a nova faixa de partições baseado no índice do vetor ps: "indiceLimQuebras".
    calculaNovaFaixa(indiceLimQuebras, InsertPs, &minMQS, &maxMQS, &passoMQS, &newMax, &newMin, numMQS);

    // Diferença de custo entre as limiares limites da nova faixa.
    diffCusto = fabs(getCusto(InsertPs, newMax) - getCusto(InsertPs, newMin));

    // Imprime as conclusões da iteração, contendo o número de limiares na
    // faixa, o limiar de quebras que obteve o melhor desempenho e o diffCusto.
    printf("numlq %d limQuebras %d lqdiff %.6f", numMQS, getMPS(InsertPs, indiceLimQuebras), diffCusto);
    contador++;

    // Controla a quebra de linhas.
    if ((diffCusto > limiarCusto) && (numMQS >= 5)) {
      printf("\n\n");
    }
  }
  // Retorna o limiar de quebras.
  return getMPS(InsertPs, indiceLimQuebras);
}
