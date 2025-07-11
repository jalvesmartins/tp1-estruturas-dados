#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/estatisticas.h"
#include "../include/ordenador.h"
#include "../include/sort.h"

int main(int argc, char *argv[]) {
  // Verifica se o arquivo foi passado como parâmetro.
  if (argc < 2) {
    printf("Uso: %s <nome_do_arquivo>\n", argv[0]);
    return 1;
  }

  // Cria o ponteiro para o arquivo.
  FILE *arquivo;

  // Inicializa o as variáveis que armazenam os pesos da calibração, o tamanho do vetor e a limiar de custo.
  double a = 0, b = 0, c = 0, limiarCusto = 0;
  int tam = 0, seed = 0;

  // Abre o arquivo e lança retona em caso de erro.
  arquivo = fopen(argv[1], "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo %s\n", argv[1]);
    return 1;
  }

  // Lê as variáveis abaixo, diretamente do arquivo.
  fscanf(arquivo, "%d %lf %lf %lf %lf %d", &seed, &limiarCusto, &a, &b, &c, &tam);

  if (limiarCusto < 0) {
    printf("Limiar de custo inválida.");            //Verificação dos parâmetros.
    return 1;
  }                               
  if (tam < 0) {
    printf("Tamanho de vetor inválido.");
    return 1;
  }

  // Cria o vetor dinamicamente.
  int *V = (int *)calloc(tam, sizeof(int));
  if (V == NULL) {                      
    printf("Erro de alocação de memória (V)\n");    //Verificação de alocação.
    return 1;
  }

  // Preenche o vetor com os valores da entrada.
  for (int i = 0; i < tam; i++) {
    fscanf(arquivo, "%d", &V[i]);
  }

  // Fecha o arquivo.
  fclose(arquivo);

  // Extrai o número de quebras.
  int numQuebras = determinaQuebras(V, tam);

  // Imprime o tamanho, a seed usada e o número de quebras.
  printf("size %d seed %d breaks %d\n\n", tam, seed, numQuebras);

  // Calcula o tamanho minimo de partição.
  int minTamParticao = determinaLimiarParticao(V, tam, limiarCusto, a, b, c);

  // Ordena o vetor.
  Stat test = {0};
  ordenadorUniversal(V, tam, minTamParticao, numQuebras, numQuebras, &test);

  // Calcula a limiar de quebras.
  determinaLimiarQuebra(V, tam, seed, limiarCusto, minTamParticao, a, b, c);

  // Desaloca a memória do vetor.
  free(V);

  return 0;
}