# Busca Linear

Ideia
- Verifica elemento por elemento até achar (ou terminar).

Complexidade
- Tempo: O(n); Espaço: O(1).

Código em C
```c
#include <stdio.h>

int busca_linear(int arr[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x) {
            return i; // Retorna o índice se encontrado
        }
    }
    return -1; // Retorna -1 se não encontrado
}

int main() {
    int arr[] = {2, 3, 4, 10, 40};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 10;
    
    int result = busca_linear(arr, n, x);
    
    if (result == -1) {
        printf("Elemento %d não encontrado no array\n", x);
    } else {
        printf("Elemento %d encontrado no índice %d\n", x, result);
    }
    
    return 0;
}
```

Uso
- Coleções pequenas ou não ordenadas quando O(n) é aceitável.