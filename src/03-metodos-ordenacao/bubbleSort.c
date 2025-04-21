#include <stdio.h>

// Função para realizar o Bubble Sort
void bubbleSort(int arr[], int n) {
    int i, j, temp;

    // Loop externo para controlar o número de passagens
    for (i = 0; i < n - 1; i++) {
        // Loop interno para comparar elementos adjacentes
        for (j = 0; j < n - i - 1; j++) {
            // Se o elemento atual for maior que o próximo, troca os dois
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Função para imprimir o array
void imprimirArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    // Exemplo de array para ordenar
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array original: \n");
    imprimirArray(arr, n);

    // Chama a função de ordenação Bubble Sort
    bubbleSort(arr, n);

    printf("Array ordenado: \n");
    imprimirArray(arr, n);

    return 0;
}