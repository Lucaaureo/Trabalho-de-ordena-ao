#ifndef TESTE_H
#define TESTE_H

void gerar_aleatorio(int v[], int n);
int esta_ordenado(const int v[], int n);

/* copia o original, ordena a cópia e devolve o tempo em segundos.
   'ok' recebe 1 se ordenou certo, 0 se errou (pode ser NULL). */
double medir_tempo(void (*algoritmo)(int[], int),
                   const int original[], int n, int *ok);

#endif
