/**
 * Bucket Sort - Algoritmo de Ordenação por Baldes
 * 
 * Complexidade:
 * - Tempo: O(n + k) no caso médio, O(n²) no pior caso
 * - Espaço: O(n + k)
 * - Estável: Depende do algoritmo usado nos baldes
 * - In-place: Não
 * 
 * Funcionamento:
 * Distribui os elementos em vários "baldes" (buckets) e ordena
 * cada balde individualmente. Funciona bem quando os dados estão
 * uniformemente distribuídos.
 * 
 * Melhor uso:
 * - Quando os dados estão uniformemente distribuídos
 * - Para números em ponto flutuante no intervalo [0, 1)
 * - Para otimizar ordenação com distribuição conhecida
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Estrutura para representar um nó na lista encadeada de cada balde
 */
typedef struct Node {
    float data;
    struct Node *next;
} Node;

/**
 * Cria um novo nó
 */
Node* criarNo(float valor) {
    Node *novoNo = (Node *)malloc(sizeof(Node));
    if (novoNo == NULL) {
        printf("Erro ao alocar memória!\n");
        return NULL;
    }
    novoNo->data = valor;
    novoNo->next = NULL;
    return novoNo;
}

/**
 * Insertion Sort para ordenar cada balde (lista encadeada)
 */
void insertionSortLista(Node **head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }
    
    Node *sorted = NULL;
    Node *current = *head;
    
    while (current != NULL) {
        Node *next = current->next;
        
        // Insere current na lista ordenada
        if (sorted == NULL || sorted->data >= current->data) {
            current->next = sorted;
            sorted = current;
        } else {
            Node *temp = sorted;
            while (temp->next != NULL && temp->next->data < current->data) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        
        current = next;
    }
    
    *head = sorted;
}

/**
 * Implementação do Bucket Sort para números em ponto flutuante [0, 1)
 * 
 * @param arr Array a ser ordenado
 * @param n Tamanho do array
 */
void bucketSort(float arr[], int n) {
    if (n <= 0) {
        return;
    }
    
    // Cria n baldes vazios
    Node **buckets = (Node **)calloc(n, sizeof(Node *));
    if (buckets == NULL) {
        printf("Erro ao alocar memória!\n");
        return;
    }
    
    // Distribui os elementos nos baldes
    for (int i = 0; i < n; i++) {
        int bucketIndex = (int)(n * arr[i]);  // Índice do balde
        
        // Garante que o índice está dentro do range
        if (bucketIndex >= n) {
            bucketIndex = n - 1;
        }
        
        // Cria um novo nó e adiciona ao balde
        Node *novoNo = criarNo(arr[i]);
        if (novoNo == NULL) {
            // Libera memória em caso de erro
            for (int j = 0; j < n; j++) {
                Node *current = buckets[j];
                while (current != NULL) {
                    Node *temp = current;
                    current = current->next;
                    free(temp);
                }
            }
            free(buckets);
            return;
        }
        
        // Adiciona no início do balde
        novoNo->next = buckets[bucketIndex];
        buckets[bucketIndex] = novoNo;
    }
    
    // Ordena cada balde individualmente
    for (int i = 0; i < n; i++) {
        insertionSortLista(&buckets[i]);
    }
    
    // Concatena os baldes ordenados de volta no array original
    int index = 0;
    for (int i = 0; i < n; i++) {
        Node *current = buckets[i];
        while (current != NULL) {
            arr[index++] = current->data;
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    
    free(buckets);
}

/**
 * Bucket Sort para inteiros com range definido
 * 
 * @param arr Array a ser ordenado
 * @param n Tamanho do array
 * @param numBuckets Número de baldes
 * @param maxValue Valor máximo esperado
 */
void bucketSortInteiros(int arr[], int n, int numBuckets, int maxValue) {
    if (n <= 0 || numBuckets <= 0 || maxValue <= 0) {
        return;
    }
    
    // Cria os baldes
    int **buckets = (int **)malloc(numBuckets * sizeof(int *));
    int *bucketSizes = (int *)calloc(numBuckets, sizeof(int));
    int *bucketCapacities = (int *)malloc(numBuckets * sizeof(int));
    
    if (buckets == NULL || bucketSizes == NULL || bucketCapacities == NULL) {
        printf("Erro ao alocar memória!\n");
        return;
    }
    
    // Inicializa os baldes
    for (int i = 0; i < numBuckets; i++) {
        bucketCapacities[i] = 10;  // Capacidade inicial
        buckets[i] = (int *)malloc(bucketCapacities[i] * sizeof(int));
    }
    
    // Distribui elementos nos baldes
    for (int i = 0; i < n; i++) {
        int bucketIndex = (arr[i] * numBuckets) / (maxValue + 1);
        
        // Garante que está no range
        if (bucketIndex >= numBuckets) {
            bucketIndex = numBuckets - 1;
        }
        
        // Expande o balde se necessário
        if (bucketSizes[bucketIndex] >= bucketCapacities[bucketIndex]) {
            bucketCapacities[bucketIndex] *= 2;
            buckets[bucketIndex] = (int *)realloc(buckets[bucketIndex], 
                                                   bucketCapacities[bucketIndex] * sizeof(int));
        }
        
        buckets[bucketIndex][bucketSizes[bucketIndex]++] = arr[i];
    }
    
    // Ordena cada balde (usando insertion sort simples)
    for (int i = 0; i < numBuckets; i++) {
        for (int j = 1; j < bucketSizes[i]; j++) {
            int key = buckets[i][j];
            int k = j - 1;
            while (k >= 0 && buckets[i][k] > key) {
                buckets[i][k + 1] = buckets[i][k];
                k--;
            }
            buckets[i][k + 1] = key;
        }
    }
    
    // Concatena os baldes de volta
    int index = 0;
    for (int i = 0; i < numBuckets; i++) {
        for (int j = 0; j < bucketSizes[i]; j++) {
            arr[index++] = buckets[i][j];
        }
        free(buckets[i]);
    }
    
    free(buckets);
    free(bucketSizes);
    free(bucketCapacities);
}

/**
 * Função auxiliar para imprimir array de floats
 */
void imprimirArrayFloat(float arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%.3f ", arr[i]);
    }
    printf("\n");
}

/**
 * Função auxiliar para imprimir array de inteiros
 */
void imprimirArrayInt(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/**
 * Função principal com exemplos de uso
 */
int main() {
    printf("=== Bucket Sort - Ordenação por Baldes ===\n\n");
    
    // Exemplo 1: Números em ponto flutuante [0, 1)
    printf("Exemplo 1: Números float no intervalo [0, 1)\n");
    float arr1[] = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    
    printf("Array original: ");
    imprimirArrayFloat(arr1, n1);
    
    bucketSort(arr1, n1);
    
    printf("Array ordenado: ");
    imprimirArrayFloat(arr1, n1);
    printf("\n");
    
    // Exemplo 2: Inteiros com range definido
    printf("Exemplo 2: Inteiros com range 0-100\n");
    int arr2[] = {42, 32, 33, 52, 37, 47, 51, 29, 12, 95};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    
    printf("Array original: ");
    imprimirArrayInt(arr2, n2);
    
    bucketSortInteiros(arr2, n2, 10, 100);  // 10 baldes, max 100
    
    printf("Array ordenado: ");
    imprimirArrayInt(arr2, n2);
    printf("\n");
    
    // Exemplo 3: Mais números float
    printf("Exemplo 3: Mais números float uniformemente distribuídos\n");
    float arr3[] = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    
    printf("Array original: ");
    imprimirArrayFloat(arr3, n3);
    
    bucketSort(arr3, n3);
    
    printf("Array ordenado: ");
    imprimirArrayFloat(arr3, n3);
    
    return 0;
}
