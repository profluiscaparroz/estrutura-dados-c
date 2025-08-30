#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Implementações básicas de algoritmos de ordenação
void quickSort(int arr[], int low, int high);
void mergeSort(int arr[], int left, int right);

// Algoritmos de busca
int buscaLinear(int arr[], int n, int chave);
int buscaBinaria(int arr[], int n, int chave);
int buscaInterpolada(int arr[], int n, int chave);

// Funções auxiliares
void swap(int *a, int *b);
int partition(int arr[], int low, int high);
void merge(int arr[], int left, int mid, int right);
void imprimirArray(int arr[], int n);
int* copiarArray(int original[], int n);

// ===== IMPLEMENTAÇÕES DE ORDENAÇÃO =====

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

// ===== IMPLEMENTAÇÕES DE BUSCA =====

int buscaLinear(int arr[], int n, int chave) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == chave) {
            return i;
        }
    }
    return -1;
}

int buscaBinaria(int arr[], int n, int chave) {
    int left = 0, right = n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == chave) {
            return mid;
        }
        
        if (arr[mid] < chave) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int buscaInterpolada(int arr[], int n, int chave) {
    int low = 0, high = n - 1;
    
    while (low <= high && chave >= arr[low] && chave <= arr[high]) {
        if (low == high) {
            return (arr[low] == chave) ? low : -1;
        }
        
        // Calcula posição usando interpolação
        int pos = low + ((double)(chave - arr[low]) / (arr[high] - arr[low])) * (high - low);
        
        if (arr[pos] == chave) {
            return pos;
        }
        
        if (arr[pos] < chave) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }
    return -1;
}

// ===== FUNÇÕES AUXILIARES =====

void imprimirArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int* copiarArray(int original[], int n) {
    int* copia = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        copia[i] = original[i];
    }
    return copia;
}

double medirTempo(clock_t inicio, clock_t fim) {
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

// ===== DEMONSTRAÇÕES =====

void demonstrarOrdenacaoEBusca() {
    printf("=== DEMONSTRAÇÃO: ORDENAÇÃO + BUSCA ===\n\n");
    
    int dados[] = {64, 34, 25, 12, 22, 11, 90, 5, 77, 30};
    int n = sizeof(dados) / sizeof(dados[0]);
    int chave = 30;
    
    printf("Array original: ");
    imprimirArray(dados, n);
    printf("Procurando por: %d\n\n", chave);
    
    // Busca linear no array desordenado
    clock_t inicio = clock();
    int posLinear = buscaLinear(dados, n, chave);
    clock_t fim = clock();
    
    printf("1. BUSCA LINEAR (array desordenado):\n");
    printf("   Resultado: %s na posição %d\n", 
           posLinear != -1 ? "Encontrado" : "Não encontrado", posLinear);
    printf("   Tempo: %.6f segundos\n\n", medirTempo(inicio, fim));
    
    // Ordena com QuickSort e busca binária
    int* dadosOrdenados = copiarArray(dados, n);
    
    inicio = clock();
    quickSort(dadosOrdenados, 0, n - 1);
    fim = clock();
    
    printf("2. ORDENAÇÃO COM QUICK SORT:\n");
    printf("   Array ordenado: ");
    imprimirArray(dadosOrdenados, n);
    printf("   Tempo de ordenação: %.6f segundos\n\n", medirTempo(inicio, fim));
    
    // Busca binária no array ordenado
    inicio = clock();
    int posBinaria = buscaBinaria(dadosOrdenados, n, chave);
    fim = clock();
    
    printf("3. BUSCA BINÁRIA (array ordenado):\n");
    printf("   Resultado: %s na posição %d\n", 
           posBinaria != -1 ? "Encontrado" : "Não encontrado", posBinaria);
    printf("   Tempo: %.6f segundos\n\n", medirTempo(inicio, fim));
    
    // Busca interpolada no array ordenado
    inicio = clock();
    int posInterpolada = buscaInterpolada(dadosOrdenados, n, chave);
    fim = clock();
    
    printf("4. BUSCA INTERPOLADA (array ordenado):\n");
    printf("   Resultado: %s na posição %d\n", 
           posInterpolada != -1 ? "Encontrado" : "Não encontrado", posInterpolada);
    printf("   Tempo: %.6f segundos\n\n", medirTempo(inicio, fim));
    
    free(dadosOrdenados);
}

void compararEficiencia() {
    printf("=== COMPARAÇÃO DE EFICIÊNCIA ===\n\n");
    
    int tamanhos[] = {100, 1000, 5000};
    int numTamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);
    
    for (int t = 0; t < numTamanhos; t++) {
        int n = tamanhos[t];
        printf("--- Array de tamanho %d ---\n", n);
        
        // Gera array aleatório
        srand(42); // Seed fixo para resultados reproduzíveis
        int* dados = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            dados[i] = rand() % 1000;
        }
        
        int chave = dados[n/2]; // Procura por um elemento que existe
        
        // Busca linear (array desordenado)
        clock_t inicio = clock();
        int posLinear = buscaLinear(dados, n, chave);
        clock_t fim = clock();
        double tempoLinear = medirTempo(inicio, fim);
        
        // Ordena o array
        int* dadosOrdenados = copiarArray(dados, n);
        inicio = clock();
        quickSort(dadosOrdenados, 0, n - 1);
        fim = clock();
        double tempoOrdenacao = medirTempo(inicio, fim);
        
        // Busca binária (array ordenado)
        inicio = clock();
        int posBinaria = buscaBinaria(dadosOrdenados, n, chave);
        fim = clock();
        double tempoBinaria = medirTempo(inicio, fim);
        
        // Tempo total (ordenação + busca binária)
        double tempoTotal = tempoOrdenacao + tempoBinaria;
        
        printf("  Busca Linear:      %.6f s\n", tempoLinear);
        printf("  Ordenação:         %.6f s\n", tempoOrdenacao);
        printf("  Busca Binária:     %.6f s\n", tempoBinaria);
        printf("  Total (Ord+Bin):   %.6f s\n", tempoTotal);
        printf("  Speedup:           %.2fx %s\n\n", 
               tempoLinear / tempoBinaria,
               tempoTotal < tempoLinear ? "(Vale a pena ordenar)" : "(Não vale a pena ordenar)");
        
        free(dados);
        free(dadosOrdenados);
    }
}

void demonstrarCasosDeUso() {
    printf("=== CASOS DE USO PRÁTICOS ===\n\n");
    
    printf("1. BUSCA ÚNICA em array não ordenado:\n");
    printf("   → Use BUSCA LINEAR\n");
    printf("   → Complexidade: O(n)\n");
    printf("   → Não vale a pena ordenar\n\n");
    
    printf("2. MÚLTIPLAS BUSCAS em array não ordenado:\n");
    printf("   → Ordene primeiro, depois use BUSCA BINÁRIA\n");
    printf("   → Complexidade: O(n log n) + k×O(log n) para k buscas\n");
    printf("   → Vale a pena se k > n/log(n)\n\n");
    
    printf("3. DADOS JÁ ORDENADOS:\n");
    printf("   → Use BUSCA BINÁRIA ou BUSCA INTERPOLADA\n");
    printf("   → Busca Interpolada é melhor para dados uniformemente distribuídos\n\n");
    
    printf("4. INSERÇÕES FREQUENTES:\n");
    printf("   → Considere estruturas como Árvore Binária de Busca\n");
    printf("   → Ou mantenha lista ordenada com Insertion Sort para inserções\n\n");
}

int main() {
    printf("===============================================\n");
    printf("    INTEGRAÇÃO: ORDENAÇÃO E ALGORITMOS DE BUSCA    \n");
    printf("===============================================\n\n");
    
    demonstrarOrdenacaoEBusca();
    compararEficiencia();
    demonstrarCasosDeUso();
    
    printf("===============================================\n");
    printf("                 RESUMO                       \n");
    printf("===============================================\n");
    printf("• Ordenação é útil quando você fará múltiplas buscas\n");
    printf("• Busca linear: O(n) - melhor para buscas únicas\n");
    printf("• Busca binária: O(log n) - requer dados ordenados\n");
    printf("• Busca interpolada: O(log log n) - melhor para dados uniformes\n");
    printf("• Quick Sort + Busca Binária é uma combinação eficiente\n");
    printf("• Merge Sort garante O(n log n) + estabilidade\n");
    
    return 0;
}

/**
 * Integração de Algoritmos de Ordenação e Busca
 * 
 * Este programa demonstra como algoritmos de ordenação e busca trabalham
 * em conjunto para resolver problemas práticos de forma eficiente.
 * 
 * Conceitos demonstrados:
 * 
 * 1. **Trade-off Ordenação vs Busca Linear**:
 *    - Uma busca: use busca linear O(n)
 *    - Múltiplas buscas: ordene O(n log n) + k buscas binárias O(k log n)
 * 
 * 2. **Escolha do Algoritmo de Ordenação**:
 *    - Quick Sort: Rápido em média, boa escolha geral
 *    - Merge Sort: Garantia O(n log n), estável
 *    - Heap Sort: Garantia O(n log n), in-place
 * 
 * 3. **Escolha do Algoritmo de Busca**:
 *    - Linear: Array não ordenado, busca única
 *    - Binária: Array ordenado, busca geral
 *    - Interpolada: Array ordenado com distribuição uniforme
 * 
 * 4. **Aplicações Práticas**:
 *    - Sistemas de banco de dados (índices)
 *    - Sistemas de busca em grandes datasets
 *    - Otimização de consultas repetitivas
 *    - Processamento de logs e análise de dados
 * 
 * A chave é entender quando o custo da ordenação é compensado
 * pela eficiência das buscas subsequentes.
 */