/**
 * Radix Sort - Algoritmo de Ordenação por Dígitos
 * 
 * Complexidade:
 * - Tempo: O(d * (n + k)) onde d é o número de dígitos e k é a base
 * - Espaço: O(n + k)
 * - Estável: Sim
 * - In-place: Não
 * 
 * Funcionamento:
 * Ordena os números dígito por dígito, começando do dígito menos
 * significativo (unidades) até o mais significativo. Usa counting sort
 * como sub-rotina estável para cada dígito.
 * 
 * Melhor uso:
 * - Para inteiros com número fixo de dígitos
 * - Quando o número de dígitos é pequeno
 * - Números com base fixa (decimal, binário, etc)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Função auxiliar para encontrar o valor máximo
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
 * Counting Sort usado como sub-rotina para Radix Sort
 * Ordena o array baseado no dígito representado por exp (1, 10, 100, ...)
 * 
 * @param arr Array a ser ordenado
 * @param n Tamanho do array
 * @param exp Posição do dígito (1 = unidades, 10 = dezenas, etc)
 */
void countingSortPorDigito(int arr[], int n, int exp) {
    int *output = (int *)malloc(n * sizeof(int));
    int count[10] = {0};  // Base 10 (dígitos de 0 a 9)
    
    if (output == NULL) {
        printf("Erro ao alocar memória!\n");
        return;
    }
    
    // Conta a ocorrência de cada dígito
    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }
    
    // Modifica count[i] para conter a posição real
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    
    // Constrói o array de saída (percorre de trás para manter estabilidade)
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }
    
    // Copia o array ordenado de volta para o original
    memcpy(arr, output, n * sizeof(int));
    
    free(output);
}

/**
 * Implementação principal do Radix Sort
 * 
 * @param arr Array a ser ordenado
 * @param n Tamanho do array
 */
void radixSort(int arr[], int n) {
    // Encontra o valor máximo para determinar o número de dígitos
    int max = encontrarMaximo(arr, n);
    
    // Executa counting sort para cada dígito
    // exp é 10^i onde i é a posição do dígito (0 = unidades, 1 = dezenas, etc)
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSortPorDigito(arr, n, exp);
    }
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
 * Função para demonstrar o processo passo a passo
 */
void radixSortComPassos(int arr[], int n) {
    int max = encontrarMaximo(arr, n);
    int passo = 1;
    
    printf("Array inicial: ");
    imprimirArray(arr, n);
    printf("\n");
    
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSortPorDigito(arr, n, exp);
        printf("Após ordenar pelo dígito das ");
        if (exp == 1) printf("unidades");
        else if (exp == 10) printf("dezenas");
        else if (exp == 100) printf("centenas");
        else printf("10^%d", passo);
        printf(": ");
        imprimirArray(arr, n);
        passo++;
    }
}

/**
 * Função principal com exemplos de uso
 */
int main() {
    printf("=== Radix Sort - Ordenação por Dígitos ===\n\n");
    
    // Exemplo 1: Array simples
    printf("Exemplo 1: Array simples\n");
    int arr1[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    
    printf("Array original: ");
    imprimirArray(arr1, n1);
    
    radixSort(arr1, n1);
    
    printf("Array ordenado: ");
    imprimirArray(arr1, n1);
    printf("\n");
    
    // Exemplo 2: Demonstração passo a passo
    printf("Exemplo 2: Demonstração passo a passo\n");
    int arr2[] = {329, 457, 657, 839, 436, 720, 355};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    
    radixSortComPassos(arr2, n2);
    printf("\n");
    
    // Exemplo 3: Array com números pequenos
    printf("Exemplo 3: Array com números de 1 dígito\n");
    int arr3[] = {7, 3, 9, 1, 5, 2, 8, 4, 6};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    
    printf("Array original: ");
    imprimirArray(arr3, n3);
    
    radixSort(arr3, n3);
    
    printf("Array ordenado: ");
    imprimirArray(arr3, n3);
    printf("\n");
    
    // Exemplo 4: Entrada do usuário
    printf("Exemplo 4: Entrada do usuário\n");
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
    
    radixSort(arr, n);
    
    printf("Array ordenado: ");
    imprimirArray(arr, n);
    
    free(arr);
    
    return 0;
}
