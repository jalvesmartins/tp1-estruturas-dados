#ifndef STATS_H
#define STATS_H

// Estrutura que armazena as estatísticas de uma execução de algoritmo.
typedef struct Stat {
  long int cmp;    // Número de comparações
  long int move;   // Número de movimentos
  long int calls;  // Número de chamadas

} Stat;

// Estrutura que armazena as estatísticas ligadas ao custo de uma execução de algoritmo.
typedef struct CostStat {
  int MPS;       // Armazena o valor da partição / número de quebras.
  double custo;  // Armazena o custo da partição / quebra.

} CostStat;

// Zera todos os valores do Stat s.
void resetCounter(Stat *s);

// Incrementa o número de comparações em um valor = num.
void increaseCmp(Stat *s, int num);

// Incrementa o número de movimentações em um valor = num.
void increaseMove(Stat *s, int num);

// Incrementa o número de chamadas em um valor = num.
void increaseCalls(Stat *s, int num);

// Retorna o valor do MPS na posição do parâmetro índice.
int getMPS(CostStat *ps, int indice);

// Retorna o valor do custo na posição do parâmetro índice.
double getCusto(CostStat *ps, int indice);

// Calcula o custo de uma ordenação, baseado nos parâmetros passados na entrada.
double calculaCusto(double a, double b, double c, Stat *s);

// Retorna o menor valor de custo dos MPS do vetor ps.
int indiceMenorCusto(CostStat *ps, int tam);

// Retorna o indice com a menor diferença de custo entre um ps e o outro.
int indiceMenorDiferenca(CostStat *ps, CostStat *ps2, int tam);

// Imprime a stat no formato desejado.
void imprimeEstatisticas(int indice, Stat *s, CostStat *ps);

// Registra o custo da ordenação no vetor de estatísticas.
void registraEstatisticas(double a, double b, double c, int indice, int t, Stat s, CostStat *ps);

#endif