#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algoritmos.h"
#include "teste.h"

#define REPETICOES 10
#define QTD_ALG 7
#define QTD_TAM 5

int main(void) {
    srand((unsigned)time(NULL));

    const char *nomes[QTD_ALG] = {"Bubble", "Insertion", "Selection",
                                  "Shell", "Quick", "Heap", "Merge"};
    void (*algoritmos[QTD_ALG])(int[], int) = {bubble_sort, insertion_sort, selection_sort,
                                               shell_sort, quick_sort, heap_sort, merge_sort};
    int tamanhos[QTD_TAM] = {10, 100, 1000, 10000, 100000};

    FILE *csv = fopen("resultados.csv", "w");
    if (csv == NULL) {
        printf("Erro ao criar resultados.csv\n");
        return 1;
    }
    fprintf(csv, "algoritmo,n,repeticao,tempo_s,ordenado\n");

    for (int t = 0; t < QTD_TAM; t++) {
        int n = tamanhos[t];
        int *original = malloc(n * sizeof(int));
        if (original == NULL) { printf("Sem memoria\n"); return 1; }

        double soma[QTD_ALG] = {0};
        int ok_todos[QTD_ALG];
        for (int a = 0; a < QTD_ALG; a++) ok_todos[a] = 1;

        printf("\n=== n = %d ===\n", n);
        fflush(stdout);   /* mostra o título já, pois n grande demora */

        for (int r = 0; r < REPETICOES; r++) {
            gerar_aleatorio(original, n);   /* um vetor por repetição, igual p/ todos */

            for (int a = 0; a < QTD_ALG; a++) {
                int ok;
                double tempo = medir_tempo(algoritmos[a], original, n, &ok);
                soma[a] += tempo;
                if (!ok) ok_todos[a] = 0;
                fprintf(csv, "%s,%d,%d,%.9f,%d\n", nomes[a], n, r + 1, tempo, ok);
            }
        }

        for (int a = 0; a < QTD_ALG; a++) {
            printf("%-10s media = %.9f s | ordenou certo? %s\n",
                   nomes[a], soma[a] / REPETICOES, ok_todos[a] ? "sim" : "NAO");
        }

        free(original);
    }

    fclose(csv);
    printf("\nResultados salvos em resultados.csv\n");
    return 0;
}