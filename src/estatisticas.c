#include "../include/estatisticas.h"

#include <math.h>

#include "stdio.h"

void resetCounter(Stat *s) {
  s->cmp = 0;
  s->move = 0;
  s->calls = 0;
}

void increaseCmp(Stat *s, int num) { s->cmp += num; }

void increaseMove(Stat *s, int num) { s->move += num; }

void increaseCalls(Stat *s, int num) { s->calls += num; }

void imprimeEstatisticas(int indice, Stat *s, CostStat *ps) {
  // Imprime o valor da partição e seu custo, além dos contadores de cada operação.
  printf("mps %d cost %.9lf cmp %ld move %ld calls %ld\n", ps[indice].MPS, ps[indice].custo, s->cmp, s->move, s->calls);
}

void registraEstatisticas(double a, double b, double c, int indice, int t, Stat s, CostStat *ps) {
  // Registra o valor da partição e seu custo no CostStat ps.
  ps[indice].MPS = t;
  ps[indice].custo = calculaCusto(a, b, c, &s);
}

double calculaCusto(double a, double b, double c, Stat *s) { return (a * s->cmp) + (b * s->move) + (c * s->calls); }

int getMPS(CostStat *ps, int indice) { return ps[indice].MPS; }

double getCusto(CostStat *ps, int indice) { return ps[indice].custo; }

int indiceMenorCusto(CostStat *ps, int tam) {
  int min = 0;
  for (int i = 1; i < tam; i++) {
    if (ps[i].custo < ps[min].custo) {
      min = i;
    }
  }
  return min;
}

int indiceMenorDiferenca(CostStat *ps, CostStat *ps2, int tam) {
  int min = 0;
  for (int i = 1; i < tam; i++) {
    if (fabs(ps[i].custo - ps2[i].custo) < fabs(ps[min].custo - ps2[min].custo)) {
      min = i;
    }
  }
  return min;
}
