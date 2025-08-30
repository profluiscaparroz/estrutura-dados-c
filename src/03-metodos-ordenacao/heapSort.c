#include <stdio.h>

// Função para trocar dois elementos
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função para manter a propriedade de heap máximo
void heapify(int arr[], int n, int i) {
    int largest = i;     // Inicializa largest como raiz
    int left = 2 * i + 1; // Filho esquerdo
    int right = 2 * i + 2; // Filho direito

    // Se o filho esquerdo é maior que a raiz
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Se o filho direito é maior que o maior até agora
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Se o maior não é a raiz
    if (largest != i) {
        swap(&arr[i], &arr[largest]);

        // Recursivamente heapify a subárvore afetada
        heapify(arr, n, largest);
    }
}

// Função principal do Heap Sort
void heapSort(int arr[], int n) {
    // Constrói heap (reorganiza array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extrai um elemento do heap por vez
    for (int i = n - 1; i > 0; i--) {
        // Move a raiz atual (maior elemento) para o final
        swap(&arr[0], &arr[i]);

        // Chama heapify na heap reduzida
        heapify(arr, i, 0);
    }
}

// Função para imprimir o array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Função para imprimir o heap como árvore (visualização simples)
void printHeap(int arr[], int n) {
    printf("Representação do Heap:\n");
    int level = 0;
    int elements_in_level = 1;
    int current_level_count = 0;
    
    for (int i = 0; i < n; i++) {
        if (current_level_count == 0) {
            printf("Nível %d: ", level);
        }
        
        printf("%d ", arr[i]);
        current_level_count++;
        
        if (current_level_count == elements_in_level) {
            printf("\n");
            level++;
            elements_in_level *= 2;
            current_level_count = 0;
        }
    }
    if (current_level_count > 0) {
        printf("\n");
    }
}

// Demonstração passo a passo do algoritmo
void heapSortDemonstracao(int arr[], int n) {
    printf("=== DEMONSTRAÇÃO PASSO A PASSO DO HEAP SORT ===\n");
    printf("Array original: ");
    printArray(arr, n);
    printf("\n");

    // Fase 1: Construção do heap
    printf("FASE 1: Construindo heap máximo\n");
    for (int i = n / 2 - 1; i >= 0; i--) {
        printf("Heapify a partir do índice %d:\n", i);
        heapify(arr, n, i);
        printArray(arr, n);
    }
    
    printf("\nHeap máximo construído:\n");
    printHeap(arr, n);
    printf("\n");

    // Fase 2: Ordenação
    printf("FASE 2: Extraindo elementos do heap\n");
    for (int i = n - 1; i > 0; i--) {
        printf("Trocando raiz (%d) com último elemento (%d):\n", arr[0], arr[i]);
        swap(&arr[0], &arr[i]);
        printArray(arr, n);
        
        printf("Heapify da heap reduzida (tamanho %d):\n", i);
        heapify(arr, i, 0);
        printArray(arr, n);
        printf("\n");
    }
    
    printf("Array final ordenado: ");
    printArray(arr, n);
}

// Função de teste com diferentes casos
void testarHeapSort() {
    // Caso 1: Array padrão
    int arr1[] = {12, 11, 13, 5, 6, 7};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    
    printf("=== TESTE 1: Array Padrão ===\n");
    printf("Array original: ");
    printArray(arr1, n1);
    heapSort(arr1, n1);
    printf("Array ordenado: ");
    printArray(arr1, n1);
    printf("\n");

    // Caso 2: Array já ordenado
    int arr2[] = {1, 2, 3, 4, 5, 6};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    
    printf("=== TESTE 2: Array Já Ordenado ===\n");
    printf("Array original: ");
    printArray(arr2, n2);
    heapSort(arr2, n2);
    printf("Array ordenado: ");
    printArray(arr2, n2);
    printf("\n");

    // Caso 3: Array em ordem reversa
    int arr3[] = {6, 5, 4, 3, 2, 1};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    
    printf("=== TESTE 3: Array em Ordem Reversa ===\n");
    printf("Array original: ");
    printArray(arr3, n3);
    heapSort(arr3, n3);
    printf("Array ordenado: ");
    printArray(arr3, n3);
    printf("\n");

    // Caso 4: Array com duplicatas
    int arr4[] = {4, 10, 3, 5, 1, 3, 10, 4};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    
    printf("=== TESTE 4: Array com Duplicatas ===\n");
    printf("Array original: ");
    printArray(arr4, n4);
    heapSort(arr4, n4);
    printf("Array ordenado: ");
    printArray(arr4, n4);
    printf("\n");
}

int main() {
    printf("=====================================================\n");
    printf("              ALGORITMO HEAP SORT                   \n");
    printf("=====================================================\n\n");

    // Executa testes básicos
    testarHeapSort();

    // Demonstração detalhada
    printf("\n=====================================================\n");
    printf("            DEMONSTRAÇÃO DETALHADA                  \n");
    printf("=====================================================\n\n");
    
    int arr_demo[] = {4, 10, 3, 5, 1};
    int n_demo = sizeof(arr_demo) / sizeof(arr_demo[0]);
    heapSortDemonstracao(arr_demo, n_demo);

    return 0;
}

/**
 * Algoritmo Heap Sort
 * 
 * O Heap Sort é um algoritmo de ordenação por comparação baseado na estrutura
 * de dados heap. Utiliza um heap binário máximo para ordenar elementos.
 * 
 * Como funciona:
 * 1. Constrói um heap máximo a partir do array
 * 2. Repetidamente extrai o máximo (raiz) e o coloca no final
 * 3. Reconstrói o heap com os elementos restantes
 * 
 * Características:
 * - Complexidade de tempo: O(n log n) em todos os casos
 * - Complexidade de espaço: O(1) - algoritmo in-place
 * - Não é estável (pode alterar ordem de elementos iguais)
 * - Performance consistente independente da entrada
 * 
 * Vantagens:
 * - Garantia de O(n log n) no pior caso
 * - Uso mínimo de memória adicional
 * - Simples de implementar
 * 
 * Desvantagens:
 * - Não é estável
 * - Constantes maiores que Quick Sort
 * - Não se beneficia de dados parcialmente ordenados
 * 
 * Conceitos importantes:
 * - Heap: Árvore binária completa onde cada nó pai é maior (ou menor) que seus filhos
 * - Heapify: Operação para manter a propriedade de heap
 * - Heap máximo: Pai sempre maior que filhos (usado para ordenação crescente)
 * 
 * Aplicações:
 * - Quando garantia de O(n log n) é necessária
 * - Sistemas com restrições de memória
 * - Priority queues e algoritmos de grafos
 */