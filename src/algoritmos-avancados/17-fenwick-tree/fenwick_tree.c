#include <stdio.h>
#include <stdlib.h>

// Estrutura da Fenwick Tree
typedef struct {
    int *tree;
    int n;
} FenwickTree;

// Função para criar uma Fenwick Tree
FenwickTree* createFenwickTree(int n) {
    FenwickTree *ft = (FenwickTree *)malloc(sizeof(FenwickTree));
    ft->n = n;
    ft->tree = (int *)calloc(n + 1, sizeof(int));  // 1-indexed, inicializado com 0
    return ft;
}

// Função para atualizar (adicionar delta ao índice i)
void update(FenwickTree *ft, int i, int delta) {
    while (i <= ft->n) {
        ft->tree[i] += delta;
        i += i & (-i);  // Adiciona LSB (Least Significant Bit)
    }
}

// Função para calcular soma de prefixo (1 a i)
int prefixSum(FenwickTree *ft, int i) {
    int result = 0;
    while (i > 0) {
        result += ft->tree[i];
        i -= i & (-i);  // Remove LSB
    }
    return result;
}

// Função para calcular soma de intervalo (L a R)
int rangeSum(FenwickTree *ft, int L, int R) {
    return prefixSum(ft, R) - prefixSum(ft, L - 1);
}

// Função para liberar memória
void freeFenwickTree(FenwickTree *ft) {
    free(ft->tree);
    free(ft);
}

// Função para exibir array
void displayArray(int arr[], int n) {
    printf("[");
    for (int i = 1; i <= n; i++) {
        printf("%d", arr[i]);
        if (i < n) printf(", ");
    }
    printf("]\n");
}

// Exemplo de uso
int main() {
    // Array 1-indexed: arr[1..6] = {1, 3, 5, 7, 9, 11}
    int n = 6;
    int arr[7] = {0, 1, 3, 5, 7, 9, 11};  // índice 0 não usado
    
    FenwickTree *ft = createFenwickTree(n);
    
    // Construir a Fenwick Tree
    printf("Construindo Fenwick Tree com array: ");
    displayArray(arr, n);
    
    for (int i = 1; i <= n; i++) {
        update(ft, i, arr[i]);
    }
    
    printf("\n=== Consultas de Soma ===\n");
    printf("Soma [1, 3]: %d\n", rangeSum(ft, 1, 3));  // 1 + 3 + 5 = 9
    printf("Soma [2, 5]: %d\n", rangeSum(ft, 2, 5));  // 3 + 5 + 7 + 9 = 24
    printf("Soma [1, 6]: %d\n", rangeSum(ft, 1, 6));  // Soma total = 36
    
    printf("\n=== Atualização ===\n");
    printf("Adicionando 5 ao índice 3 (arr[3] = 5 + 5 = 10)\n");
    update(ft, 3, 5);
    
    printf("\n=== Consultas Após Atualização ===\n");
    printf("Soma [1, 3]: %d\n", rangeSum(ft, 1, 3));  // 1 + 3 + 10 = 14
    printf("Soma [2, 5]: %d\n", rangeSum(ft, 2, 5));  // 3 + 10 + 7 + 9 = 29
    printf("Soma [1, 6]: %d\n", rangeSum(ft, 1, 6));  // Soma total = 41
    
    printf("\n=== Mais Atualizações ===\n");
    printf("Subtraindo 2 do índice 5 (arr[5] = 9 - 2 = 7)\n");
    update(ft, 5, -2);
    
    printf("Soma [1, 6]: %d\n", rangeSum(ft, 1, 6));  // Soma total = 39
    printf("Soma [4, 6]: %d\n", rangeSum(ft, 4, 6));  // 7 + 7 + 11 = 25
    
    freeFenwickTree(ft);
    
    return 0;
}
