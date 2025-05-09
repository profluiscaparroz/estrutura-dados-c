#include <stdio.h>

// Função para trocar dois elementos no array
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função para particionar o array em torno de um pivô
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Escolhe o último elemento como pivô
    int i = low - 1;       // Índice do menor elemento

    for (int j = low; j < high; j++) {
        // Se o elemento atual for menor ou igual ao pivô
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]); // Troca os elementos
        }
    }
    swap(&arr[i + 1], &arr[high]); // Coloca o pivô na posição correta
    return i + 1;                  // Retorna o índice do pivô
}

// Função principal do QuickSort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // Encontra o índice do pivô
        int pi = partition(arr, low, high);

        // Ordena os elementos antes e depois do pivô
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Função para imprimir o array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/**
 * Algoritmo QuickSort
 *
 * O QuickSort é um algoritmo de ordenação eficiente que utiliza a técnica de divisão e conquista.
 * Ele seleciona um elemento como pivô e particiona o array em torno desse pivô, de forma que os
 * elementos menores que o pivô fiquem à esquerda e os maiores à direita. O processo é repetido
 * recursivamente para as sublistas resultantes.
 *
 * Complexidade:
 * - Melhor caso: O(n log n)
 * - Caso médio: O(n log n)
 * - Pior caso: O(n^2) (ocorre quando o array já está ordenado ou quase ordenado)
 * - Complexidade espacial: O(log n) (para a pilha de chamadas recursivas)
 *
 * Vantagens:
 * - Rápido para listas grandes.
 * - Ordenação in-place (não requer espaço adicional significativo).
 *
 * Desvantagens:
 * - Não é estável (pode alterar a ordem relativa de elementos iguais).
 */
// Exemplo de uso do algoritmo QuickSort
int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array original: ");
    printArray(arr, n);

    quickSort(arr, 0, n - 1);

    printf("Array ordenado: ");
    printArray(arr, n);

    return 0;
}