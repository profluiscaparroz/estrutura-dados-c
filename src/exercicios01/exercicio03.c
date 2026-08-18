#include <stdio.h>
#include <stdlib.h>

// ------------------------------
// Função auxiliar: busca binária
// ------------------------------
int buscaBinaria(int v[], int n, int alvo) {
    int left = 0, right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (v[mid] == alvo)
            return mid;
        else if (v[mid] < alvo)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

// comparação para qsort
int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// -------------------------------------------------
// 1. Matriz 3x3 → vetor → ordena → busca binária
// -------------------------------------------------
void exemploMatrizParaVetor() {
    int matriz[3][3] = {
        {9, 2, 7},
        {4, 6, 1},
        {8, 3, 5}
    };

    int vetor[9];
    int k = 0;

    // converter matriz em vetor
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            vetor[k++] = matriz[i][j];

    // ordenar
    qsort(vetor, 9, sizeof(int), cmp);

    int alvo = 6;
    int pos = buscaBinaria(vetor, 9, alvo);

    printf("Exemplo 1 - Matriz -> Vetor:\n");
    printf("Posição do %d: %d\n\n", alvo, pos);
}

// --------------------------------------------
// 2. Busca binária usando RA como vetor
// --------------------------------------------
void exemploRA() {
    int ra[] = {1, 2, 3, 4, 5, 6}; // RA exemplo ordenado
    int n = 6;

    int alvo = 4;

    int pos = buscaBinaria(ra, n, alvo);

    printf("Exemplo 2 - RA:\n");
    printf("Posição do %d: %d\n\n", alvo, pos);
}

// ------------------------------------------------------
// 3. Busca binária em vetor desordenado (erro demonstrado)
// ------------------------------------------------------
void exemploDesordenado() {
    int v[] = {10, 3, 7, 1, 9, 5};
    int n = 6;

    int alvo = 1;

    int left = 0, right = n - 1;

    printf("Exemplo 3 - Vetor desordenado:\n");

    while (left <= right) {
        int mid = (left + right) / 2;

        printf("left=%d mid=%d right=%d valor=%d\n", left, mid, right, v[mid]);

        if (v[mid] == alvo) {
            printf("Encontrado na posição %d\n\n", mid);
            return;
        } else if (v[mid] < alvo) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    printf("Resultado: -1 (valor existe, mas não foi encontrado)\n\n");
}

// ------------------------------
// MAIN
// ------------------------------
int main() {
    exemploMatrizParaVetor();
    exemploRA();
    exemploDesordenado();

    return 0;
}