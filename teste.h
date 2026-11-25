#ifndef TESTE_H
#define TESTE_H

/* preenche v com n inteiros pseudoaleatorios de 30 bits (0 a 2^30 - 1) */
void gerar_aleatorio(int v[], int n);

/* retorna 1 se v esta em ordem crescente, 0 caso contrario */
int esta_ordenado(const int v[], int n);

/* imprime os n elementos de v em uma linha */
void imprimir_vetor(const int v[], int n);

/* copia o original, ordena a copia com 'algoritmo' e devolve o tempo em segundos.
   'ok' recebe 1 se ordenou certo, 0 se errou (pode ser NULL). */
double medir_tempo(void (*algoritmo)(int[], int),
                   const int original[], int n, int *ok);

#endif
