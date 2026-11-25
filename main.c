/*
 * Comparacao de algoritmos de ordenacao.
 *
 * Uso:
 *   ordenacao          -> teste completo (10 a 100.000 elementos) -> resultados.csv
 *   ordenacao rapido   -> teste curto (10 a 1.000 elementos)      -> resultados_rapido.csv
 *   ordenacao demo     -> mostra um vetor de 10 elementos antes e depois de cada algoritmo
 *
 * Os vetores sao pseudoaleatorios com semente FIXA (SEMENTE): rodar de novo gera
 * os mesmos vetores. Os tempos medidos, porem, variam de uma execucao para outra.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algoritmos.h"
#include "teste.h"

#define SEMENTE    12345
#define REPETICOES 10
#define QTD_ALG    7

static const char *NOMES[QTD_ALG] = {
    "Bubble", "Insertion", "Selection", "Shell", "Quick", "Heap", "Merge"
};

static void (*const ALGORITMOS[QTD_ALG])(int[], int) = {
    bubble_sort, insertion_sort, selection_sort, shell_sort,
    quick_sort, heap_sort, merge_sort
};

/* Mostra o vetor antes e depois de cada algoritmo (prova visivel de que ordena). */
static int modo_demo(void) {
    enum { N = 10 };
    int original[N], copia[N];
    int tudo_ok = 1;

    srand(SEMENTE);
    gerar_aleatorio(original, N);
    for (int i = 0; i < N; i++) original[i] %= 100;   /* numeros pequenos: mais legiveis */

    printf("Vetor original: ");
    imprimir_vetor(original, N);

    for (int a = 0; a < QTD_ALG; a++) {
        memcpy(copia, original, sizeof(original));
        ALGORITMOS[a](copia, N);
        int ok = esta_ordenado(copia, N);
        if (!ok) tudo_ok = 0;
        printf("%-10s: ", NOMES[a]);
        imprimir_vetor(copia, N);
        printf("            ordenado? %s\n", ok ? "sim" : "NAO");
    }
    return tudo_ok ? 0 : 1;
}

/* Roda os 7 algoritmos, REPETICOES vezes para cada tamanho, e grava o CSV. */
static int modo_teste(const int tamanhos[], int qtd_tam, const char *arquivo_csv) {
    FILE *csv = fopen(arquivo_csv, "w");
    if (csv == NULL) {
        printf("Erro ao criar %s\n", arquivo_csv);
        return 1;
    }
    fprintf(csv, "algoritmo,n,repeticao,tempo_s,ordenado\n");

    srand(SEMENTE);
    printf("Semente do gerador: %d\n", SEMENTE);

    int todos_ok = 1;
    for (int t = 0; t < qtd_tam; t++) {
        int n = tamanhos[t];
        int *original = malloc(n * sizeof(int));
        if (original == NULL) {
            printf("Sem memoria\n");
            fclose(csv);
            return 1;
        }

        double soma[QTD_ALG] = {0};
        int ok_todos[QTD_ALG];
        for (int a = 0; a < QTD_ALG; a++) ok_todos[a] = 1;

        printf("\n=== n = %d ===\n", n);
        fflush(stdout);   /* mostra o titulo ja, pois n grande demora */

        for (int r = 0; r < REPETICOES; r++) {
            gerar_aleatorio(original, n);   /* um vetor por repeticao, igual para os 7 */

            for (int a = 0; a < QTD_ALG; a++) {
                int ok;
                double tempo = medir_tempo(ALGORITMOS[a], original, n, &ok);
                soma[a] += tempo;
                if (!ok) { ok_todos[a] = 0; todos_ok = 0; }
                fprintf(csv, "%s,%d,%d,%.9f,%d\n", NOMES[a], n, r + 1, tempo, ok);
            }
        }

        for (int a = 0; a < QTD_ALG; a++) {
            printf("%-10s media = %.9f s | ordenou certo? %s\n",
                   NOMES[a], soma[a] / REPETICOES, ok_todos[a] ? "sim" : "NAO");
        }
        free(original);
    }

    fclose(csv);
    printf("\nResultados salvos em %s\n", arquivo_csv);
    return todos_ok ? 0 : 1;
}

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "demo") == 0) {
        return modo_demo();
    }
    if (argc > 1 && strcmp(argv[1], "rapido") == 0) {
        const int tamanhos[] = {10, 100, 1000};
        return modo_teste(tamanhos, 3, "resultados_rapido.csv");
    }
    if (argc > 1) {
        printf("Uso: %s [demo | rapido]\n", argv[0]);
        return 1;
    }
    const int tamanhos[] = {10, 100, 1000, 10000, 100000};
    return modo_teste(tamanhos, 5, "resultados.csv");
}