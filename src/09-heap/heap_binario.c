/*
 * ====================================================================
 * IMPLEMENTAÇÃO DE HEAP BINÁRIO MÍNIMO (Min Heap)
 * ====================================================================
 * 
 * Descrição:
 * Um heap binário é uma árvore binária completa que satisfaz a propriedade
 * de heap: em um min-heap, o valor de cada nó é menor ou igual aos valores
 * de seus filhos. Implementado usando array para eficiência.
 * 
 * Propriedades:
 * - Árvore binária completa (preenchida da esquerda para direita)
 * - Propriedade de heap: parent ≤ children (min-heap)
 * - Implementação usando array: parent(i) = (i-1)/2, children = 2i+1, 2i+2
 * 
 * Complexidade das operações:
 * - Inserção: O(log n)
 * - Extração do mínimo: O(log n)
 * - Busca do mínimo: O(1)
 * - Construção: O(n)
 * 
 * Aplicações:
 * - Priority Queue (Fila de Prioridade)
 * - Algoritmo de Dijkstra
 * - Heap Sort
 * - Algoritmos de grafos
 * 
 * Autor: Estrutura de Dados em C
 * Data: 2024
 * ====================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/**
 * Estrutura do Min Heap
 * @param data: array para armazenar os elementos
 * @param size: número atual de elementos no heap
 * @param capacity: capacidade máxima do heap
 */
typedef struct {
    int* data;
    int size;
    int capacity;
} MinHeap;

/**
 * Cria um novo heap com capacidade especificada
 * @param capacity: capacidade máxima do heap
 * @return: ponteiro para o heap criado
 */
MinHeap* create_heap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (heap == NULL) {
        printf("Erro: Falha na alocação de memória para o heap\n");
        exit(1);
    }
    
    heap->data = (int*)malloc(capacity * sizeof(int));
    if (heap->data == NULL) {
        printf("Erro: Falha na alocação de memória para os dados\n");
        free(heap);
        exit(1);
    }
    
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// ============ FUNÇÕES AUXILIARES PARA NAVEGAÇÃO NO HEAP ============

/**
 * Retorna o índice do pai de um nó
 * @param i: índice do nó filho
 * @return: índice do pai
 */
int parent(int i) { 
    return (i - 1) / 2; 
}

/**
 * Retorna o índice do filho esquerdo
 * @param i: índice do nó pai
 * @return: índice do filho esquerdo
 */
int left_child(int i) { 
    return 2 * i + 1; 
}

/**
 * Retorna o índice do filho direito
 * @param i: índice do nó pai
 * @return: índice do filho direito
 */
int right_child(int i) { 
    return 2 * i + 2; 
}

/**
 * Troca dois elementos no array
 * @param a: ponteiro para o primeiro elemento
 * @param b: ponteiro para o segundo elemento
 */
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Restaura a propriedade de heap subindo um elemento (usado após inserção)
 * @param heap: ponteiro para o heap
 * @param i: índice do elemento a ser movido para cima
 */
void heapify_up(MinHeap* heap, int i) {
    // Continua subindo enquanto o elemento for menor que seu pai
    while (i != 0 && heap->data[parent(i)] > heap->data[i]) {
        swap(&heap->data[i], &heap->data[parent(i)]);
        i = parent(i);
    }
}

/**
 * Restaura a propriedade de heap descendo um elemento (usado após extração)
 * @param heap: ponteiro para o heap
 * @param i: índice do elemento a ser movido para baixo
 */
void heapify_down(MinHeap* heap, int i) {
    int smallest = i;
    int left = left_child(i);
    int right = right_child(i);
    
    // Encontrar o menor entre pai, filho esquerdo e filho direito
    if (left < heap->size && heap->data[left] < heap->data[smallest]) {
        smallest = left;
    }
    
    if (right < heap->size && heap->data[right] < heap->data[smallest]) {
        smallest = right;
    }
    
    // Se o menor não é o pai, trocar e continuar heapify
    if (smallest != i) {
        swap(&heap->data[i], &heap->data[smallest]);
        heapify_down(heap, smallest);
    }
}

/**
 * Insere um novo elemento no heap
 * @param heap: ponteiro para o heap
 * @param data: valor a ser inserido
 */
void insert(MinHeap* heap, int data) {
    if (heap->size == heap->capacity) {
        printf("Erro: Heap overflow - capacidade máxima atingida\n");
        return;
    }
    
    // Inserir no final e restaurar propriedade de heap
    heap->data[heap->size] = data;
    heapify_up(heap, heap->size);
    heap->size++;
    
    printf("✓ Inserido: %d\n", data);
}

/**
 * Remove e retorna o elemento mínimo do heap (raiz)
 * @param heap: ponteiro para o heap
 * @return: valor mínimo ou INT_MAX se heap vazio
 */
int extract_min(MinHeap* heap) {
    if (heap->size <= 0) {
        printf("Erro: Heap underflow - heap está vazio\n");
        return INT_MAX;
    }
    
    // Caso especial: apenas um elemento
    if (heap->size == 1) {
        heap->size--;
        return heap->data[0];
    }
    
    // Salvar o mínimo, mover último para raiz e restaurar heap
    int root = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heapify_down(heap, 0);
    
    return root;
}

/**
 * Retorna o elemento mínimo sem removê-lo
 * @param heap: ponteiro para o heap
 * @return: valor mínimo ou INT_MAX se heap vazio
 */
int get_min(MinHeap* heap) {
    if (heap->size <= 0) {
        printf("Erro: Heap está vazio\n");
        return INT_MAX;
    }
    return heap->data[0];
}

/**
 * Imprime todos os elementos do heap
 * @param heap: ponteiro para o heap
 */
void print_heap(MinHeap* heap) {
    printf("Heap (%d elementos): ", heap->size);
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

/**
 * Libera toda a memória alocada para o heap
 * @param heap: ponteiro para o heap a ser destruído
 */
void destroy_heap(MinHeap* heap) {
    if (heap != NULL) {
        free(heap->data);
        free(heap);
    }
}

/**
 * Função principal demonstrando o uso do Min Heap
 * Testa inserção, extração e operações básicas
 */
int main() {
    printf("=== DEMONSTRAÇÃO DE HEAP BINÁRIO MÍNIMO ===\n\n");
    
    // Criar heap com capacidade para 10 elementos
    MinHeap* heap = create_heap(10);
    printf("✓ Heap criado com capacidade para 10 elementos\n\n");
    
    // Inserir elementos
    printf("=== INSERINDO ELEMENTOS ===\n");
    insert(heap, 3);
    insert(heap, 2);
    insert(heap, 15);
    insert(heap, 5);
    insert(heap, 4);
    insert(heap, 45);
    
    printf("\n");
    print_heap(heap);
    
    // Testar acesso ao mínimo
    printf("\n=== OPERAÇÕES DE CONSULTA ===\n");
    printf("Elemento mínimo (sem remover): %d\n", get_min(heap));
    
    // Extrair elementos
    printf("\n=== EXTRAINDO ELEMENTOS ===\n");
    printf("Extraído (mínimo): %d\n", extract_min(heap));
    print_heap(heap);
    
    printf("Extraído (mínimo): %d\n", extract_min(heap));
    print_heap(heap);
    
    printf("Extraído (mínimo): %d\n", extract_min(heap));
    print_heap(heap);
    
    // Inserir mais elementos para demonstrar que o heap continua funcionando
    printf("\n=== INSERINDO MAIS ELEMENTOS ===\n");
    insert(heap, 1);
    insert(heap, 8);
    print_heap(heap);
    
    printf("Novo mínimo: %d\n", get_min(heap));
    
    // Extrair todos os elementos restantes para mostrar ordenação
    printf("\n=== EXTRAINDO TODOS OS ELEMENTOS (ORDENAÇÃO) ===\n");
    printf("Elementos em ordem crescente: ");
    while (heap->size > 0) {
        printf("%d ", extract_min(heap));
    }
    printf("\n");
    
    // Limpeza
    destroy_heap(heap);
    printf("\n✓ Memória liberada com sucesso!\n");
    
    return 0;
}