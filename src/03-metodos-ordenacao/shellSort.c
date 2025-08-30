#include <stdio.h>

// Declarações das funções
void imprimirArray(int arr[], int n);
void copiarArray(int origem[], int destino[], int n);

// Implementação do Shell Sort
void shellSort(int arr[], int n) {
    // Começa com um gap grande, depois reduz
    for (int gap = n / 2; gap > 0; gap /= 2) {
        printf("Gap atual: %d\n", gap);
        
        // Faz uma ordenação por inserção com gap
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            
            // Desloca elementos do arr[0..i-gap] que são
            // maiores que temp para uma posição à frente
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            
            // Coloca temp na posição correta
            arr[j] = temp;
        }
        
        printf("Array após gap %d: ", gap);
        imprimirArray(arr, n);
    }
}

// Versão otimizada com sequência de gaps de Knuth
void shellSortKnuth(int arr[], int n) {
    // Sequência de Knuth: 1, 4, 13, 40, 121, 364...
    // Formula: h = 3*h + 1
    int gap = 1;
    while (gap < n / 3) {
        gap = gap * 3 + 1;
    }
    
    printf("Usando sequência de gaps de Knuth\n");
    
    while (gap >= 1) {
        printf("Gap atual: %d\n", gap);
        
        // Insertion sort com gap
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;
            
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
        
        printf("Array após gap %d: ", gap);
        imprimirArray(arr, n);
        gap = gap / 3;
    }
}

// Função para imprimir array
void imprimirArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Função para copiar array
void copiarArray(int origem[], int destino[], int n) {
    for (int i = 0; i < n; i++) {
        destino[i] = origem[i];
    }
}

// Demonstração comparativa
void demonstrarShellSort() {
    int original[] = {23, 29, 15, 19, 31, 7, 9, 5, 2};
    int n = sizeof(original) / sizeof(original[0]);
    
    printf("=== DEMONSTRAÇÃO SHELL SORT ===\n");
    printf("Array original: ");
    imprimirArray(original, n);
    printf("\n");
    
    // Teste com Shell Sort padrão
    int arr1[9];
    copiarArray(original, arr1, n);
    printf("MÉTODO 1: Shell Sort com gaps simples (n/2, n/4, n/8...)\n");
    shellSort(arr1, n);
    printf("Resultado final: ");
    imprimirArray(arr1, n);
    printf("\n");
    
    // Teste com Shell Sort de Knuth
    int arr2[9];
    copiarArray(original, arr2, n);
    printf("MÉTODO 2: Shell Sort com sequência de Knuth\n");
    shellSortKnuth(arr2, n);
    printf("Resultado final: ");
    imprimirArray(arr2, n);
    printf("\n");
}

// Função para testar diferentes casos
void testarCasos() {
    printf("=== TESTES COM DIFERENTES TIPOS DE ARRAYS ===\n\n");
    
    // Caso 1: Array pequeno desordenado
    int caso1[] = {5, 2, 8, 1, 9};
    int n1 = sizeof(caso1) / sizeof(caso1[0]);
    printf("CASO 1: Array pequeno desordenado\n");
    printf("Original: ");
    imprimirArray(caso1, n1);
    shellSort(caso1, n1);
    printf("Ordenado: ");
    imprimirArray(caso1, n1);
    printf("\n");
    
    // Caso 2: Array já ordenado
    int caso2[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int n2 = sizeof(caso2) / sizeof(caso2[0]);
    printf("CASO 2: Array já ordenado\n");
    printf("Original: ");
    imprimirArray(caso2, n2);
    shellSort(caso2, n2);
    printf("Ordenado: ");
    imprimirArray(caso2, n2);
    printf("\n");
    
    // Caso 3: Array em ordem reversa
    int caso3[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int n3 = sizeof(caso3) / sizeof(caso3[0]);
    printf("CASO 3: Array em ordem reversa\n");
    printf("Original: ");
    imprimirArray(caso3, n3);
    shellSort(caso3, n3);
    printf("Ordenado: ");
    imprimirArray(caso3, n3);
    printf("\n");
    
    // Caso 4: Array com duplicatas
    int caso4[] = {3, 7, 3, 1, 7, 5, 1, 5};
    int n4 = sizeof(caso4) / sizeof(caso4[0]);
    printf("CASO 4: Array com elementos duplicados\n");
    printf("Original: ");
    imprimirArray(caso4, n4);
    shellSort(caso4, n4);
    printf("Ordenado: ");
    imprimirArray(caso4, n4);
    printf("\n");
}

int main() {
    printf("====================================================\n");
    printf("               ALGORITMO SHELL SORT                \n");
    printf("====================================================\n\n");
    
    demonstrarShellSort();
    testarCasos();
    
    printf("====================================================\n");
    printf("                  INFORMAÇÕES                      \n");
    printf("====================================================\n");
    printf("Shell Sort é uma generalização do Insertion Sort.\n");
    printf("Ele permite a troca de elementos distantes, reduzindo\n");
    printf("o número total de movimentações necessárias.\n\n");
    printf("Características:\n");
    printf("• Complexidade: O(n log n) a O(n²) dependendo da sequência de gaps\n");
    printf("• Espaço: O(1) - algoritmo in-place\n");
    printf("• Estabilidade: Não é estável\n");
    printf("• Adaptativo: Sim, funciona bem com dados parcialmente ordenados\n\n");
    printf("Vantagens:\n");
    printf("• Melhor que algoritmos O(n²) simples\n");
    printf("• Simples de implementar\n");
    printf("• Bom desempenho para arrays médios\n");
    printf("• Não requer memória adicional\n\n");
    printf("Quando usar:\n");
    printf("• Arrays de tamanho médio (1000-5000 elementos)\n");
    printf("• Quando simplicidade de código é importante\n");
    printf("• Como alternativa ao Insertion Sort para arrays maiores\n");
    
    return 0;
}

/**
 * Algoritmo Shell Sort
 * 
 * O Shell Sort, também conhecido como Sort de Diminuição de Incremento,
 * é uma generalização do Insertion Sort. Foi desenvolvido por Donald Shell
 * em 1959.
 * 
 * Ideia Principal:
 * Em vez de comparar elementos adjacentes (gap = 1), o Shell Sort
 * compara elementos separados por um gap maior, que diminui progressivamente
 * até chegar a 1 (Insertion Sort padrão).
 * 
 * Como funciona:
 * 1. Escolhe uma sequência de gaps (h1, h2, ..., hk) onde hk = 1
 * 2. Para cada gap, aplica o Insertion Sort
 * 3. Elementos distantes são movidos rapidamente para posições próximas
 *    da final
 * 4. Quando gap = 1, faz o Insertion Sort final (que será rápido pois
 *    o array já está quase ordenado)
 * 
 * Sequências de gaps comuns:
 * • Shell original: n/2, n/4, n/8, ..., 1
 * • Knuth: 1, 4, 13, 40, 121... (h = 3h + 1)
 * • Sedgewick: 1, 5, 19, 41, 109...
 * • Hibbard: 1, 3, 7, 15, 31... (2^k - 1)
 * 
 * Vantagem sobre Insertion Sort:
 * O Insertion Sort move elementos uma posição por vez. Se um elemento
 * pequeno está no final do array, precisa de muitas trocas para chegar
 * ao início. O Shell Sort move elementos distantes rapidamente.
 */