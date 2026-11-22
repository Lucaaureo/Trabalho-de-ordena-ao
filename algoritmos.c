#include <stdlib.h>   /* malloc e free (usados no Merge Sort) */
#include "algoritmos.h"

/* ---------- BUBBLE SORT: compara vizinhos e troca ---------- */
void bubble_sort(int v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int trocou = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            if (v[j] > v[j + 1]) {
                int aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
                trocou = 1;
            }
        }
        if (!trocou) break;   /* passada sem trocas: já está ordenado */
    }
}

/* ---------- INSERTION SORT: insere cada elemento na parte ordenada ---------- */
void insertion_sort(int v[], int n) {
    for (int i = 1; i < n; i++) {
        int chave = v[i];
        int j = i - 1;
        while (j >= 0 && v[j] > chave) {   /* desloca os maiores para a direita */
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = chave;
    }
}

/* ---------- SELECTION SORT: escolhe o menor e coloca na posição i ---------- */
void selection_sort(int v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (v[j] < v[min]) min = j;
        }
        if (min != i) {
            int aux = v[i];
            v[i] = v[min];
            v[min] = aux;
        }
    }
}

/* ---------- SHELL SORT: insertion sort com intervalos (gaps) decrescentes ---------- */
/* Gaps usados: n/2, n/4, ..., 1 (sequência original de Shell) */
void shell_sort(int v[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int chave = v[i];
            int j = i;
            while (j >= gap && v[j - gap] > chave) {
                v[j] = v[j - gap];
                j -= gap;
            }
            v[j] = chave;
        }
    }
}

/* ---------- QUICK SORT: particiona em torno de um pivô (elemento do meio) ---------- */
static void quick_rec(int v[], int low, int high) {
    int i = low, j = high;
    int pivo = v[low + (high - low) / 2];

    while (i <= j) {
        while (v[i] < pivo) i++;   /* acha elemento >= pivô à esquerda */
        while (v[j] > pivo) j--;   /* acha elemento <= pivô à direita */
        if (i <= j) {
            int aux = v[i];
            v[i] = v[j];
            v[j] = aux;
            i++;
            j--;
        }
    }
    if (low < j)  quick_rec(v, low, j);
    if (i < high) quick_rec(v, i, high);
}

void quick_sort(int v[], int n) {
    if (n > 1) quick_rec(v, 0, n - 1);
}

/* ---------- HEAP SORT: monta um max-heap e extrai o maior repetidamente ---------- */
static void peneirar(int v[], int n, int i) {
    while (1) {
        int maior = i;
        int esq = 2 * i + 1;
        int dir = 2 * i + 2;

        if (esq < n && v[esq] > v[maior]) maior = esq;
        if (dir < n && v[dir] > v[maior]) maior = dir;
        if (maior == i) break;

        int aux = v[i];
        v[i] = v[maior];
        v[maior] = aux;
        i = maior;
    }
}

void heap_sort(int v[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {   /* constrói o heap */
        peneirar(v, n, i);
    }
    for (int fim = n - 1; fim > 0; fim--) {  /* move o maior para o final */
        int aux = v[0];
        v[0] = v[fim];
        v[fim] = aux;
        peneirar(v, fim, 0);
    }
}

/* ---------- MERGE SORT: divide, ordena as metades e intercala ---------- */
static void merge_rec(int v[], int aux[], int ini, int fim) {
    if (ini >= fim) return;

    int meio = ini + (fim - ini) / 2;
    merge_rec(v, aux, ini, meio);
    merge_rec(v, aux, meio + 1, fim);

    int i = ini, j = meio + 1, k = ini;
    while (i <= meio && j <= fim) {
        if (v[i] <= v[j]) aux[k++] = v[i++];
        else              aux[k++] = v[j++];
    }
    while (i <= meio) aux[k++] = v[i++];
    while (j <= fim)  aux[k++] = v[j++];

    for (k = ini; k <= fim; k++) v[k] = aux[k];
}

void merge_sort(int v[], int n) {
    if (n < 2) return;
    int *aux = malloc(n * sizeof(int));   /* vetor auxiliar para intercalar */
    if (aux == NULL) return;
    merge_rec(v, aux, 0, n - 1);
    free(aux);
}