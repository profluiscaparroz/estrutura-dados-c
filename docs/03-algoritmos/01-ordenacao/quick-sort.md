# Quick Sort

Ideia
- Escolhe pivô, particiona, recursão nas partes.

Complexidade
- Tempo: O(n log n) médio; O(n^2) pior (pivôs ruins).
- Espaço: O(log n) para pilha de recursão (em média).

Código em C (partição Lomuto)
```c
#include <stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Escolhe o último elemento como pivô
    int i = low - 1; // Índice do menor elemento
    
    for (int j = low; j <= high - 1; j++) {
        // Se elemento atual é menor ou igual ao pivô
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        
        // Ordena elementos antes e depois da partição
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Array original: ");
    print_array(arr, n);
    
    quick_sort(arr, 0, n - 1);
    
    printf("Array ordenado: ");
    print_array(arr, n);
    
    return 0;
}
```

Dicas
- Use escolha de pivô melhor (mediana de três) e caia para Insertion Sort em subproblemas pequenos.