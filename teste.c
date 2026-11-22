#define _POSIX_C_SOURCE 199309L   /* necessário para clock_gettime em Linux/Mac */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "teste.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <time.h>
#endif

/* tempo atual em segundos, com resolução de nanossegundos */
static double agora(void) {
#ifdef _WIN32
    LARGE_INTEGER freq, cont;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&cont);
    return (double)cont.QuadPart / (double)freq.QuadPart;
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec / 1e9;
#endif
}

void gerar_aleatorio(int v[], int n) {
    for (int i = 0; i < n; i++) {
        v[i] = (rand() << 15) | rand();   /* combina duas chamadas: rand() é pequeno no Windows */
    }
}

int esta_ordenado(const int v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (v[i] > v[i + 1]) return 0;
    }
    return 1;
}

double medir_tempo(void (*algoritmo)(int[], int),
                   const int original[], int n, int *ok) {
    int *copia = malloc(n * sizeof(int));
    if (copia == NULL) {
        printf("Erro: sem memoria\n");
        exit(1);
    }
    memcpy(copia, original, n * sizeof(int));   /* cópia fica fora da medição */

    double inicio = agora();
    algoritmo(copia, n);
    double fim = agora();

    if (ok != NULL) *ok = esta_ordenado(copia, n);

    free(copia);
    return fim - inicio;
}
