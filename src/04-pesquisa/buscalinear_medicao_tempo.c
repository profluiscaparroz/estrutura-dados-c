#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função de busca linear
int buscaLinear(int arr[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x) {
            return i; // Retorna o índice do elemento encontrado
        }
    }
    return -1; // Retorna -1 se o elemento não for encontrado
}

int main() {
    // Tamanho do array
    int n = 100000;
    int *arr = malloc(n * sizeof(int)); // Alocação dinâmica para o array

    // Preenchendo o array com valores de 1 a n
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    // Elemento a ser buscado
    int x = 99999;

    // Medindo o tempo de execução
    clock_t inicio, fim;
    double tempoGasto;

    inicio = clock(); // Marca o início do tempo
    int resultado = buscaLinear(arr, n, x);
    fim = clock(); // Marca o fim do tempo

    // Calcula o tempo gasto em segundos
    tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    // Exibindo o resultado
    if (resultado != -1) {
        printf("Elemento encontrado no índice: %d\n", resultado);
    } else {
        printf("Elemento não encontrado.\n");
    }

    printf("Tempo de execução: %.6f segundos\n", tempoGasto);

    // Liberando a memória alocada
    free(arr);

    return 0;
}
