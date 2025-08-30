#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Declarações das funções de ordenação
void bubbleSort(int arr[], int n);
void insertionSort(int arr[], int n);
void selectionSort(int arr[], int n);
void quickSort(int arr[], int low, int high);
void mergeSort(int arr[], int left, int right);

// Funções auxiliares para merge sort
void merge(int arr[], int left, int mid, int right);

// Função para trocar elementos (para quickSort)
void swap(int *a, int *b);
int partition(int arr[], int low, int high);

// Implementações dos algoritmos (versões simplificadas para benchmark)

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    free(L);
    free(R);
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Função para gerar arrays de teste
int* gerarArrayAleatorio(int n, int seed) {
    srand(seed);
    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000; // Números de 0 a 999
    }
    return arr;
}

int* gerarArrayOrdenado(int n) {
    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
    return arr;
}

int* gerarArrayReverso(int n) {
    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
    return arr;
}

// Função para copiar array
int* copiarArray(int* original, int n) {
    int* copia = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        copia[i] = original[i];
    }
    return copia;
}

// Função para verificar se array está ordenado
int verificarOrdenacao(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return 0;
        }
    }
    return 1;
}

// Função para medir tempo de execução
double medirTempo(void (*algoritmo)(int[], int), int arr[], int n) {
    clock_t inicio = clock();
    algoritmo(arr, n);
    clock_t fim = clock();
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

double medirTempoQuickSort(int arr[], int n) {
    clock_t inicio = clock();
    quickSort(arr, 0, n - 1);
    clock_t fim = clock();
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

double medirTempoMergeSort(int arr[], int n) {
    clock_t inicio = clock();
    mergeSort(arr, 0, n - 1);
    clock_t fim = clock();
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

// Função principal de benchmark
void executarBenchmark(int* arrayOriginal, int n, const char* tipoArray) {
    printf("\n=== BENCHMARK: %s (n = %d) ===\n", tipoArray, n);
    printf("%-15s %-12s %-12s\n", "Algoritmo", "Tempo (s)", "Ordenado?");
    printf("%-15s %-12s %-12s\n", "-------------", "----------", "---------");
    
    // Bubble Sort
    int* arr = copiarArray(arrayOriginal, n);
    double tempo = medirTempo(bubbleSort, arr, n);
    printf("%-15s %-12.6f %-12s\n", "Bubble Sort", tempo, 
           verificarOrdenacao(arr, n) ? "Sim" : "Não");
    free(arr);
    
    // Insertion Sort
    arr = copiarArray(arrayOriginal, n);
    tempo = medirTempo(insertionSort, arr, n);
    printf("%-15s %-12.6f %-12s\n", "Insertion Sort", tempo, 
           verificarOrdenacao(arr, n) ? "Sim" : "Não");
    free(arr);
    
    // Selection Sort
    arr = copiarArray(arrayOriginal, n);
    tempo = medirTempo(selectionSort, arr, n);
    printf("%-15s %-12.6f %-12s\n", "Selection Sort", tempo, 
           verificarOrdenacao(arr, n) ? "Sim" : "Não");
    free(arr);
    
    // Quick Sort
    arr = copiarArray(arrayOriginal, n);
    tempo = medirTempoQuickSort(arr, n);
    printf("%-15s %-12.6f %-12s\n", "Quick Sort", tempo, 
           verificarOrdenacao(arr, n) ? "Sim" : "Não");
    free(arr);
    
    // Merge Sort
    arr = copiarArray(arrayOriginal, n);
    tempo = medirTempoMergeSort(arr, n);
    printf("%-15s %-12.6f %-12s\n", "Merge Sort", tempo, 
           verificarOrdenacao(arr, n) ? "Sim" : "Não");
    free(arr);
}

int main() {
    printf("=================================================\n");
    printf("         COMPARAÇÃO DE ALGORITMOS DE ORDENAÇÃO  \n");
    printf("=================================================\n");
    
    // Tamanhos de array para teste
    int tamanhos[] = {100, 500, 1000};
    int numTamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);
    
    for (int i = 0; i < numTamanhos; i++) {
        int n = tamanhos[i];
        
        // Teste com array aleatório
        int* arrayAleatorio = gerarArrayAleatorio(n, 42);
        executarBenchmark(arrayAleatorio, n, "Array Aleatório");
        free(arrayAleatorio);
        
        // Teste com array já ordenado
        int* arrayOrdenado = gerarArrayOrdenado(n);
        executarBenchmark(arrayOrdenado, n, "Array Ordenado");
        free(arrayOrdenado);
        
        // Teste com array em ordem reversa
        int* arrayReverso = gerarArrayReverso(n);
        executarBenchmark(arrayReverso, n, "Array Reverso");
        free(arrayReverso);
    }
    
    printf("\n=== RESUMO DAS CARACTERÍSTICAS ===\n");
    printf("Bubble Sort:    O(n²) - Simples, estável, ineficiente para arrays grandes\n");
    printf("Insertion Sort: O(n²) - Eficiente para arrays pequenos e quase ordenados\n");
    printf("Selection Sort: O(n²) - Minimiza número de trocas\n");
    printf("Quick Sort:     O(n log n) avg - Rápido, mas O(n²) no pior caso\n");
    printf("Merge Sort:     O(n log n) - Consistente, estável, usa mais memória\n");
    
    printf("\n=== RECOMENDAÇÕES ===\n");
    printf("Arrays pequenos (n < 50):     Insertion Sort\n");
    printf("Arrays médios (50 < n < 1000): Quick Sort\n");
    printf("Arrays grandes (n > 1000):     Merge Sort ou Quick Sort\n");
    printf("Necessita estabilidade:        Merge Sort ou Insertion Sort\n");
    printf("Memória limitada:              Quick Sort ou algoritmos in-place\n");
    
    return 0;
}

/**
 * Ferramenta de Comparação de Algoritmos de Ordenação
 * 
 * Este programa compara o desempenho de diferentes algoritmos de ordenação
 * em diferentes tipos de arrays e tamanhos.
 * 
 * Funcionalidades:
 * - Benchmark de tempo de execução
 * - Verificação de corretude
 * - Diferentes tipos de dados de entrada
 * - Relatório comparativo
 * 
 * Uso:
 * gcc -O2 -o comparacao comparacao.c
 * ./comparacao
 */