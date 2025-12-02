/**
 * ============================================================================
 * ALGORITMOS DE DIVISÃO E CONQUISTA
 * ============================================================================
 * 
 * Este arquivo demonstra o paradigma de Divisão e Conquista, uma técnica
 * fundamental que serve como base para muitos algoritmos avançados.
 * 
 * O paradigma consiste em três etapas:
 * 1. DIVIDIR: Dividir o problema em subproblemas menores
 * 2. CONQUISTAR: Resolver os subproblemas recursivamente
 * 3. COMBINAR: Combinar as soluções dos subproblemas
 * 
 * Algoritmos implementados:
 * - Merge Sort
 * - Quick Sort
 * - Busca do Máximo e Mínimo
 * - Contagem de Inversões
 * - Multiplicação de Karatsuba
 * 
 * Pré-requisito: Entender recursão (01-algoritmo-recursao)
 * 
 * Autor: Estrutura de Dados em C
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

// ==================== MERGE SORT ====================

/**
 * Função auxiliar para mesclar dois subarrays ordenados
 */
void merge(int arr[], int esq, int meio, int dir) {
    int n1 = meio - esq + 1;
    int n2 = dir - meio;
    
    // Arrays temporários
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));
    
    // Copiar dados
    for (int i = 0; i < n1; i++)
        L[i] = arr[esq + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[meio + 1 + j];
    
    // Mesclar de volta
    int i = 0, j = 0, k = esq;
    
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
    
    // Copiar elementos restantes
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

/**
 * Merge Sort - Algoritmo de ordenação por divisão e conquista
 * 
 * Complexidade:
 * - Tempo: O(n log n) em todos os casos
 * - Espaço: O(n) para arrays temporários
 * - Estável: Sim
 */
void mergeSort(int arr[], int esq, int dir) {
    if (esq < dir) {
        // DIVIDIR: encontrar ponto médio
        int meio = esq + (dir - esq) / 2;
        
        // CONQUISTAR: ordenar cada metade
        mergeSort(arr, esq, meio);
        mergeSort(arr, meio + 1, dir);
        
        // COMBINAR: mesclar as metades ordenadas
        merge(arr, esq, meio, dir);
    }
}

// ==================== QUICK SORT ====================

/**
 * Função de partição para Quick Sort
 * Escolhe o último elemento como pivô
 */
int particionar(int arr[], int baixo, int alto) {
    int pivo = arr[alto];
    int i = baixo - 1;
    
    for (int j = baixo; j < alto; j++) {
        if (arr[j] < pivo) {
            i++;
            // Trocar arr[i] e arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    // Colocar pivô na posição correta
    int temp = arr[i + 1];
    arr[i + 1] = arr[alto];
    arr[alto] = temp;
    
    return i + 1;
}

/**
 * Quick Sort - Algoritmo de ordenação por divisão e conquista
 * 
 * Complexidade:
 * - Tempo: O(n log n) caso médio, O(n²) pior caso
 * - Espaço: O(log n) para pilha de recursão
 * - Estável: Não (esta implementação)
 * - In-place: Sim
 */
void quickSort(int arr[], int baixo, int alto) {
    if (baixo < alto) {
        // DIVIDIR: particionar ao redor do pivô
        int pi = particionar(arr, baixo, alto);
        
        // CONQUISTAR: ordenar partições
        quickSort(arr, baixo, pi - 1);
        quickSort(arr, pi + 1, alto);
        
        // COMBINAR: não é necessário (in-place)
    }
}

// ==================== MÁXIMO E MÍNIMO ====================

typedef struct {
    int max;
    int min;
} MinMax;

/**
 * Encontrar máximo e mínimo usando divisão e conquista
 * 
 * Comparações: 3n/2 - 2 (melhor que 2n - 2 do método ingênuo)
 */
MinMax encontrarMinMax(int arr[], int baixo, int alto) {
    MinMax resultado, esq, dir;
    
    // Caso base: um elemento
    if (baixo == alto) {
        resultado.min = arr[baixo];
        resultado.max = arr[baixo];
        return resultado;
    }
    
    // Caso base: dois elementos
    if (alto == baixo + 1) {
        if (arr[baixo] < arr[alto]) {
            resultado.min = arr[baixo];
            resultado.max = arr[alto];
        } else {
            resultado.min = arr[alto];
            resultado.max = arr[baixo];
        }
        return resultado;
    }
    
    // DIVIDIR
    int meio = (baixo + alto) / 2;
    
    // CONQUISTAR
    esq = encontrarMinMax(arr, baixo, meio);
    dir = encontrarMinMax(arr, meio + 1, alto);
    
    // COMBINAR
    resultado.min = (esq.min < dir.min) ? esq.min : dir.min;
    resultado.max = (esq.max > dir.max) ? esq.max : dir.max;
    
    return resultado;
}

// ==================== CONTAGEM DE INVERSÕES ====================

/**
 * Merge que conta inversões
 */
long mergeContarInversoes(int arr[], int temp[], int esq, int meio, int dir) {
    int i = esq, j = meio, k = esq;
    long inversoes = 0;
    
    while (i <= meio - 1 && j <= dir) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            // Todos elementos restantes no lado esquerdo formam inversões
            inversoes += (meio - i);
        }
    }
    
    while (i <= meio - 1)
        temp[k++] = arr[i++];
    
    while (j <= dir)
        temp[k++] = arr[j++];
    
    for (i = esq; i <= dir; i++)
        arr[i] = temp[i];
    
    return inversoes;
}

/**
 * Contar inversões em um array
 * Uma inversão é um par (i, j) onde i < j mas arr[i] > arr[j]
 * 
 * Usando modificação do Merge Sort
 * Complexidade: O(n log n)
 */
long contarInversoes(int arr[], int temp[], int esq, int dir) {
    long inversoes = 0;
    
    if (esq < dir) {
        int meio = (esq + dir) / 2;
        
        // CONQUISTAR e contar inversões em cada metade
        inversoes += contarInversoes(arr, temp, esq, meio);
        inversoes += contarInversoes(arr, temp, meio + 1, dir);
        
        // COMBINAR e contar inversões entre metades
        inversoes += mergeContarInversoes(arr, temp, esq, meio + 1, dir);
    }
    
    return inversoes;
}

// ==================== MULTIPLICAÇÃO DE KARATSUBA ====================

/**
 * Número de dígitos de um número
 */
int numDigitos(long n) {
    int digitos = 0;
    while (n > 0) {
        digitos++;
        n /= 10;
    }
    return digitos;
}

/**
 * Potência de 10
 */
long potencia10(int n) {
    long resultado = 1;
    for (int i = 0; i < n; i++) {
        resultado *= 10;
    }
    return resultado;
}

/**
 * Multiplicação de Karatsuba
 * 
 * Ideia: xy = 10^n * ac + 10^(n/2) * ((a+b)(c+d) - ac - bd) + bd
 * onde x = 10^(n/2) * a + b  e  y = 10^(n/2) * c + d
 * 
 * Complexidade: O(n^1.585) vs O(n²) do método tradicional
 */
long karatsuba(long x, long y) {
    // Caso base
    if (x < 10 || y < 10) {
        return x * y;
    }
    
    int n = numDigitos(x);
    int m = numDigitos(y);
    int max_n = (n > m) ? n : m;
    int meio = max_n / 2;
    
    long divisor = potencia10(meio);
    
    // Dividir x em a e b
    long a = x / divisor;
    long b = x % divisor;
    
    // Dividir y em c e d
    long c = y / divisor;
    long d = y % divisor;
    
    // Três multiplicações recursivas
    long ac = karatsuba(a, c);
    long bd = karatsuba(b, d);
    long ad_bc = karatsuba(a + b, c + d) - ac - bd;
    
    // Combinar
    return ac * potencia10(2 * meio) + ad_bc * potencia10(meio) + bd;
}

// ==================== EXPONENCIAÇÃO RÁPIDA ====================

/**
 * Exponenciação rápida (Binary Exponentiation)
 * Complexidade: O(log n)
 */
long exponenciacao_rapida(long base, int exp) {
    if (exp == 0) return 1;
    
    long metade = exponenciacao_rapida(base, exp / 2);
    
    if (exp % 2 == 0) {
        return metade * metade;
    } else {
        return base * metade * metade;
    }
}

// ==================== PONTO MAIS PRÓXIMO ====================

typedef struct {
    int x;
    int y;
} Ponto;

/**
 * Distância entre dois pontos (ao quadrado para evitar raiz)
 */
long distanciaQuad(Ponto p1, Ponto p2) {
    long dx = p1.x - p2.x;
    long dy = p1.y - p2.y;
    return dx * dx + dy * dy;
}

// ==================== FUNÇÕES DE UTILIDADE ====================

void imprimirArray(int arr[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
}

void copiarArray(int origem[], int destino[], int n) {
    for (int i = 0; i < n; i++) {
        destino[i] = origem[i];
    }
}

// ==================== TESTES ====================

void testar_merge_sort() {
    printf("=== TESTE MERGE SORT ===\n");
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Array original: ");
    imprimirArray(arr, n);
    
    mergeSort(arr, 0, n - 1);
    
    printf("Array ordenado: ");
    imprimirArray(arr, n);
    printf("\n");
}

void testar_quick_sort() {
    printf("=== TESTE QUICK SORT ===\n");
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Array original: ");
    imprimirArray(arr, n);
    
    quickSort(arr, 0, n - 1);
    
    printf("Array ordenado: ");
    imprimirArray(arr, n);
    printf("\n");
}

void testar_min_max() {
    printf("=== TESTE MÁXIMO E MÍNIMO ===\n");
    int arr[] = {1000, 11, 445, 1, 330, 3000};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Array: ");
    imprimirArray(arr, n);
    
    MinMax resultado = encontrarMinMax(arr, 0, n - 1);
    
    printf("Mínimo: %d\n", resultado.min);
    printf("Máximo: %d\n", resultado.max);
    printf("\n");
}

void testar_inversoes() {
    printf("=== TESTE CONTAGEM DE INVERSÕES ===\n");
    int arr[] = {1, 20, 6, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int *temp = (int *)malloc(n * sizeof(int));
    
    printf("Array: ");
    imprimirArray(arr, n);
    
    long inv = contarInversoes(arr, temp, 0, n - 1);
    
    printf("Número de inversões: %ld\n", inv);
    printf("Inversões: (20,6), (20,4), (20,5), (6,4), (6,5), (4,5)? Não, (4,5) não é.\n");
    printf("Correto: (20,6), (20,4), (20,5), (6,4), (6,5) = 5 inversões\n");
    
    free(temp);
    printf("\n");
}

void testar_karatsuba() {
    printf("=== TESTE MULTIPLICAÇÃO DE KARATSUBA ===\n");
    
    long x = 1234, y = 5678;
    long resultado = karatsuba(x, y);
    long esperado = x * y;
    
    printf("%ld x %ld = %ld\n", x, y, resultado);
    printf("Verificação: %ld (esperado: %ld)\n", resultado, esperado);
    
    x = 12345678; y = 87654321;
    resultado = karatsuba(x, y);
    esperado = x * y;
    
    printf("%ld x %ld = %ld\n", x, y, resultado);
    printf("Verificação: %s\n", resultado == esperado ? "CORRETO" : "INCORRETO");
    printf("\n");
}

void testar_exponenciacao() {
    printf("=== TESTE EXPONENCIAÇÃO RÁPIDA ===\n");
    printf("2^10 = %ld\n", exponenciacao_rapida(2, 10));
    printf("3^5 = %ld\n", exponenciacao_rapida(3, 5));
    printf("5^4 = %ld\n", exponenciacao_rapida(5, 4));
    printf("\n");
}

void comparar_performance() {
    printf("=== COMPARAÇÃO DE PERFORMANCE ===\n");
    
    int tamanhos[] = {1000, 5000, 10000};
    int num_tamanhos = 3;
    
    for (int t = 0; t < num_tamanhos; t++) {
        int n = tamanhos[t];
        int *arr1 = (int *)malloc(n * sizeof(int));
        int *arr2 = (int *)malloc(n * sizeof(int));
        
        // Gerar array aleatório
        srand(42);
        for (int i = 0; i < n; i++) {
            arr1[i] = rand() % 10000;
            arr2[i] = arr1[i];
        }
        
        // Testar Merge Sort
        clock_t inicio = clock();
        mergeSort(arr1, 0, n - 1);
        clock_t fim = clock();
        double tempo_merge = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000;
        
        // Restaurar e testar Quick Sort
        copiarArray(arr2, arr1, n);
        inicio = clock();
        quickSort(arr1, 0, n - 1);
        fim = clock();
        double tempo_quick = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000;
        
        printf("n = %d: Merge Sort = %.3fms, Quick Sort = %.3fms\n", 
               n, tempo_merge, tempo_quick);
        
        free(arr1);
        free(arr2);
    }
    printf("\n");
}

// ==================== FUNÇÃO PRINCIPAL ====================

int main() {
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║         ALGORITMOS DE DIVISÃO E CONQUISTA                ║\n");
    printf("║   Dividir → Conquistar → Combinar                        ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    testar_merge_sort();
    testar_quick_sort();
    testar_min_max();
    testar_inversoes();
    testar_karatsuba();
    testar_exponenciacao();
    comparar_performance();
    
    printf("═══════════════════════════════════════════════════════════\n");
    printf("Divisão e Conquista é a base para:\n");
    printf("- Consistent Hashing (próximo tópico)\n");
    printf("- Árvores de segmento\n");
    printf("- FFT (Fast Fourier Transform)\n");
    printf("- Algoritmos paralelos\n");
    printf("═══════════════════════════════════════════════════════════\n");
    
    return 0;
}
