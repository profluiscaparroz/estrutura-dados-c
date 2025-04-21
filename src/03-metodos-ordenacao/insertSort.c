#include <stdio.h>

// Função para realizar o algoritmo de ordenação por inserção (Insertion Sort)
void insertionSort(int arr[], int n) {
    // Percorre o array a partir do segundo elemento
    for (int i = 1; i < n; i++) {
        int key = arr[i]; // Elemento atual a ser inserido na posição correta
        int j = i - 1;

        // Move os elementos maiores que 'key' uma posição à frente
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        // Insere o elemento na posição correta
        arr[j + 1] = key;
    }
}

// Função para imprimir o array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Função principal
int main() {
    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array original:\n");
    printArray(arr, n);

    insertionSort(arr, n);

    printf("Array ordenado:\n");
    printArray(arr, n);

    return 0;
}