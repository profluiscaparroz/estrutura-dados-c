# Bubble Sort

Ideia
- Percorre o array várias vezes, trocando vizinhos fora de ordem.
- Após cada passagem, o maior elemento "borbulha" para o final.

Complexidade
- Tempo: O(n^2) no pior e médio; O(n) no melhor (já ordenado com otimização).
- Espaço: O(1).

Código em C
```c
#include <stdio.h>
#include <stdbool.h>

void bubble_sort(int arr[], int n) {
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Troca os elementos
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        // Se não houve troca, o array já está ordenado
        if (!swapped) break;
    }
}

void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Array original: ");
    print_array(arr, n);
    
    bubble_sort(arr, n);
    
    printf("Array ordenado: ");
    print_array(arr, n);
    
    return 0;
}
```

Quando usar
- Didático; raramente apropriado em produção devido a O(n^2).