#include <stdio.h>

// Versão otimizada do Bubble Sort com detecção de array já ordenado
void bubbleSortOptimized(int arr[], int n) {
    if (n <= 1) return; // Array vazio ou com um elemento já está ordenado
    
    int i, j, temp;
    int swapped; // Flag para detectar se houve troca

    for (i = 0; i < n - 1; i++) {
        swapped = 0; // Reset da flag a cada passagem
        
        // Loop interno - note que reduzimos o alcance a cada passagem
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Troca os elementos
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1; // Marca que houve troca
            }
        }
        
        // Se nenhuma troca foi feita, o array já está ordenado
        if (swapped == 0) {
            printf("Array ordenado na passagem %d\n", i + 1);
            break;
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

// Função para testar diferentes casos
void testarCaso(int arr[], int n, const char* descricao) {
    printf("\n=== %s ===\n", descricao);
    printf("Array original: ");
    imprimirArray(arr, n);
    
    bubbleSortOptimized(arr, n);
    
    printf("Array ordenado: ");
    imprimirArray(arr, n);
}

int main() {
    // Caso 1: Array desordenado
    int arr1[] = {64, 34, 25, 12, 22, 11, 90};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    
    // Caso 2: Array já ordenado
    int arr2[] = {1, 2, 3, 4, 5, 6, 7};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    
    // Caso 3: Array em ordem reversa
    int arr3[] = {7, 6, 5, 4, 3, 2, 1};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    
    // Caso 4: Array com elementos duplicados
    int arr4[] = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    
    // Caso 5: Array vazio
    int *arr5 = NULL;
    int n5 = 0;
    
    // Caso 6: Array com um elemento
    int arr6[] = {42};
    int n6 = 1;

    testarCaso(arr1, n1, "Array Desordenado");
    testarCaso(arr2, n2, "Array Já Ordenado");
    testarCaso(arr3, n3, "Array em Ordem Reversa");
    testarCaso(arr4, n4, "Array com Duplicados");
    
    printf("\n=== Array Vazio ===\n");
    printf("Testando array vazio...\n");
    bubbleSortOptimized(arr5, n5);
    printf("Teste de array vazio passou!\n");
    
    testarCaso(arr6, n6, "Array com Um Elemento");

    return 0;
}

/**
 * Bubble Sort Otimizado
 * 
 * Esta versão melhorada do Bubble Sort inclui as seguintes otimizações:
 * 
 * 1. **Detecção de Array Ordenado**: Se nenhuma troca for feita em uma 
 *    passagem completa, o algoritmo para, pois o array já está ordenado.
 *    Isso melhora a complexidade do melhor caso de O(n²) para O(n).
 * 
 * 2. **Redução do Alcance**: A cada passagem, o maior elemento já está 
 *    na posição correta, então reduzimos o alcance do loop interno.
 * 
 * 3. **Verificação de Casos Extremos**: Arrays vazios ou com um elemento
 *    são tratados imediatamente.
 * 
 * Complexidade:
 * - Melhor caso: O(n) - array já ordenado
 * - Caso médio: O(n²)
 * - Pior caso: O(n²) - array em ordem reversa
 * - Espaço: O(1) - algoritmo in-place
 * 
 * Vantagens da versão otimizada:
 * - Detecta arrays já ordenados
 * - Para precocemente quando possível
 * - Testa casos extremos adequadamente
 * - Fornece feedback sobre o número de passagens
 */