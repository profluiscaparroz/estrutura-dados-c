#include <stdio.h>

// Função para mesclar dois subarrays em ordem crescente
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1; // Tamanho do subarray esquerdo
    int n2 = right - mid;    // Tamanho do subarray direito

    // Arrays temporários para armazenar os subarrays
    int L[n1], R[n2];

    // Copia os dados para os arrays temporários
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Índices iniciais dos subarrays e do array mesclado
    int i = 0, j = 0, k = left;

    // Mescla os subarrays de volta no array original
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes do subarray esquerdo, se houver
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copia os elementos restantes do subarray direito, se houver
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Função recursiva para dividir o array e ordenar as partes
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; // Calcula o ponto médio

        // Ordena a primeira e a segunda metade
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Mescla as duas metades ordenadas
        merge(arr, left, mid, right);
    }
}

// Função para imprimir o array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Função principal para demonstrar o Merge Sort
int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Array original:\n");
    printArray(arr, size);

    mergeSort(arr, 0, size - 1);

    printf("Array ordenado:\n");
    printArray(arr, size);

    return 0;
}