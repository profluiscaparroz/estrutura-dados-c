/**
 * Counting Sort - Algoritmo de Ordenação por Contagem
 * 
 * Complexidade:
 * - Tempo: O(n + k) onde k é o range dos valores
 * - Espaço: O(n + k)
 * - Estável: Sim
 * - In-place: Não
 * 
 * Funcionamento:
 * Conta a frequência de cada elemento e usa essas contagens
 * para determinar a posição de cada elemento no array ordenado.
 * 
 * Melhor uso:
 * - Quando o range de valores (k) é pequeno comparado com n
 * - Para inteiros não-negativos
 * - Quando estabilidade é necessária
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Encontra o valor máximo no array
 */
int encontrarMaximo(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

/**
 * Implementação do Counting Sort
 * 
 * @param arr Array a ser ordenado
 * @param n Tamanho do array
 */
void countingSort(int arr[], int n) {
    // Encontra o valor máximo para determinar o tamanho do array de contagem
    int max = encontrarMaximo(arr, n);
    
    // Aloca e inicializa array de contagem
    int *count = (int *)calloc(max + 1, sizeof(int));
    if (count == NULL) {
        printf("Erro ao alocar memória!\n");
        return;
    }
    
    // Conta a frequência de cada elemento
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }
    
    // Modifica count[i] para conter a posição real do elemento
    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }
    
    // Constrói o array de saída
    int *output = (int *)malloc(n * sizeof(int));
    if (output == NULL) {
        printf("Erro ao alocar memória!\n");
        free(count);
        return;
    }
    
    // Percorre o array original de trás para frente para manter estabilidade
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
    
    // Copia o array ordenado de volta para o array original
    memcpy(arr, output, n * sizeof(int));
    
    // Libera memória
    free(count);
    free(output);
}

/**
 * Função auxiliar para imprimir array
 */
void imprimirArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/**
 * Função principal com exemplos de uso
 */
int main() {
    printf("=== Counting Sort - Ordenação por Contagem ===\n\n");
    
    // Exemplo 1: Array pequeno
    printf("Exemplo 1: Array pequeno\n");
    int arr1[] = {4, 2, 2, 8, 3, 3, 1};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    
    printf("Array original: ");
    imprimirArray(arr1, n1);
    
    countingSort(arr1, n1);
    
    printf("Array ordenado: ");
    imprimirArray(arr1, n1);
    printf("\n");
    
    // Exemplo 2: Array com valores repetidos
    printf("Exemplo 2: Array com muitos valores repetidos\n");
    int arr2[] = {1, 4, 1, 2, 7, 5, 2};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    
    printf("Array original: ");
    imprimirArray(arr2, n2);
    
    countingSort(arr2, n2);
    
    printf("Array ordenado: ");
    imprimirArray(arr2, n2);
    printf("\n");
    
    // Exemplo 3: Entrada do usuário
    printf("Exemplo 3: Entrada do usuário\n");
    int n;
    printf("Digite a quantidade de elementos: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Entrada inválida!\n");
        return 1;
    }
    
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }
    
    printf("Digite %d números inteiros não-negativos separados por espaço:\n", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1 || arr[i] < 0) {
            printf("Entrada inválida!\n");
            free(arr);
            return 1;
        }
    }
    
    printf("Array original: ");
    imprimirArray(arr, n);
    
    countingSort(arr, n);
    
    printf("Array ordenado: ");
    imprimirArray(arr, n);
    
    free(arr);
    
    return 0;
}
