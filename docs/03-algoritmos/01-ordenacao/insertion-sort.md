# Insertion Sort

Ideia
- Constrói uma parte ordenada inserindo cada novo elemento na posição correta.

Complexidade
- Tempo: O(n^2) médio/pior; O(n) no melhor (quase ordenado).
- Espaço: O(1).

Código em C
```c
#include <stdio.h>

void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        // Move elementos maiores que key uma posição à frente
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Array original: ");
    print_array(arr, n);
    
    insertion_sort(arr, n);
    
    printf("Array ordenado: ");
    print_array(arr, n);
    
    return 0;
}
```

Quando usar
- Listas pequenas; dados quase ordenados; como passo em algoritmos híbridos.