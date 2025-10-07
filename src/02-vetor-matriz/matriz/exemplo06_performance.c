#include <stdio.h>
#include <time.h>

int main() {
    int matriz[1000][1000];
    long long soma = 0;

    // Inicializar a matriz
    for (int i = 0; i < 1000; i++)
        for (int j = 0; j < 1000; j++)
            matriz[i][j] = i + j;

    clock_t inicio, fim;
    double tempo;

    // Método 1: percorrer por linhas (cache-friendly)
    soma = 0;
    inicio = clock();
    for (int i = 0; i < 1000; i++)
        for (int j = 0; j < 1000; j++)
            soma += matriz[i][j];
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Metodo 1 (linhas): soma = %lld, tempo = %.6f s\n", soma, tempo);

    // Método 2: percorrer por colunas (cache miss)
    soma = 0;
    inicio = clock();
    for (int j = 0; j < 1000; j++)
        for (int i = 0; i < 1000; i++)
            soma += matriz[i][j];
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Metodo 2 (colunas): soma = %lld, tempo = %.6f s\n", soma, tempo);

    return 0;
}
