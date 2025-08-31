# Busca Binária

Pré-requisito
- Array deve estar ordenado.

Complexidade
- Tempo: O(log n); Espaço: O(1) (versão iterativa).

Código em C (iterativo)
```c
#include <stdio.h>

int busca_binaria(int arr[], int n, int x) {
    int left = 0, right = n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2; // Evita overflow
        
        if (arr[mid] == x) {
            return mid; // Elemento encontrado
        }
        
        if (arr[mid] < x) {
            left = mid + 1; // Busca na metade direita
        } else {
            right = mid - 1; // Busca na metade esquerda
        }
    }
    
    return -1; // Elemento não encontrado
}

int main() {
    int arr[] = {2, 3, 4, 10, 14, 20, 40};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 10;
    
    int result = busca_binaria(arr, n, x);
    
    if (result == -1) {
        printf("Elemento %d não encontrado no array\n", x);
    } else {
        printf("Elemento %d encontrado no índice %d\n", x, result);
    }
    
    return 0;
}
```

Observações
- Cuidado com overflow na média (use l + (r - l)/2).