#include <stdio.h>

// Função para realizar o Selection Sort
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        // Encontra o índice do menor elemento no subarray não ordenado
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        // Troca o menor elemento encontrado com o primeiro elemento do subarray não ordenado
        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

// Função para imprimir o array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/*
O algoritmo Selection Sort é um método de ordenação simples e intuitivo. 
Ele funciona dividindo o array em duas partes: a parte ordenada (no início do array) 
e a parte não ordenada (o restante do array). A cada iteração, o menor elemento da 
parte não ordenada é selecionado e trocado com o primeiro elemento da parte não 
ordenada, expandindo assim a parte ordenada.

Passos do algoritmo:
    1. Percorra o array e encontre o menor elemento na parte não ordenada.
    2. Troque esse menor elemento com o primeiro elemento da parte não ordenada.
    3. Repita o processo para o restante do array, excluindo a parte já ordenada.
    4. Continue até que todo o array esteja ordenado.

Características:
    Complexidade de tempo: O Selection Sort tem complexidade de tempo O(n²) no pior, melhor e caso médio, pois sempre percorre o array restante para encontrar o menor elemento.
    Espaço adicional: É um algoritmo in-place, ou seja, não requer espaço adicional significativo além do array original.
    Estabilidade: Não é estável, pois pode trocar elementos iguais de posições diferentes.

Exemplo:
    Dado o array {64, 25, 12, 22, 11}, o Selection Sort funciona assim:

    1. Encontra o menor elemento (11) e troca com o primeiro (64): {11, 25, 12, 22, 64}
    2. Encontra o próximo menor (12) e troca com o segundo (25): {11, 12, 25, 22, 64}
    3. Encontra o próximo menor (22) e troca com o terceiro (25): {11, 12, 22, 25, 64}
    4. O array já está ordenado: {11, 12, 22, 25, 64}

*/
int main() {
    // Exemplo de uso do Selection Sort
    int arr[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array original:\n");
    printArray(arr, n);

    // Ordena o array usando Selection Sort
    selectionSort(arr, n);

    printf("Array ordenado:\n");
    printArray(arr, n);

    return 0;
}