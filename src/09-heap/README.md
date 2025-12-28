# Heap Binário (Binary Heap)

## 📋 Visão Geral

Este diretório contém implementação completa de heap binário em C, uma estrutura de dados fundamental para implementação de filas de prioridade e algoritmos de ordenação eficientes.

## 📚 Arquivos Incluídos

- **heap_binario.c** - Implementação completa do heap binário
- **heap_test** - Binário executável para testes
- **Makefile** - Automação de compilação e testes

## 🎯 O que é um Heap?

Um **heap binário** é uma árvore binária completa que satisfaz a propriedade de heap:
- **Max-Heap**: Valor de cada nó é ≥ valores dos filhos
- **Min-Heap**: Valor de cada nó é ≤ valores dos filhos

### Características Principais

1. **Árvore Binária Completa**: Todos os níveis preenchidos, exceto possivelmente o último (preenchido da esquerda para direita)
2. **Representação em Array**: Eficiente, sem necessidade de ponteiros
3. **Relações Pai-Filho**: 
   - Pai de índice `i`: `(i-1)/2`
   - Filho esquerdo: `2*i + 1`
   - Filho direito: `2*i + 2`

## 📊 Complexidade das Operações

| Operação | Complexidade | Descrição |
|----------|-------------|-----------|
| **Inserção (push)** | O(log n) | Insere e reorganiza heap |
| **Remoção do topo (pop)** | O(log n) | Remove raiz e reorganiza |
| **Ver topo (peek)** | O(1) | Acessa elemento máximo/mínimo |
| **Heapify** | O(n) | Construir heap de array |
| **Heap Sort** | O(n log n) | Ordenação usando heap |
| **Busca** | O(n) | Heap não é otimizado para busca |
| **Espaço** | O(n) | Array contíguo |

## 💡 Estrutura de Dados

```c
typedef struct {
    int *data;          // Array de elementos
    int size;           // Número atual de elementos
    int capacity;       // Capacidade máxima
    int is_max_heap;    // 1 para max-heap, 0 para min-heap
} Heap;
```

## 🔧 Operações Fundamentais

### 1. Criar Heap

```c
Heap* create_heap(int capacity, int is_max_heap) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->data = (int*)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    heap->is_max_heap = is_max_heap;
    return heap;
}
```

### 2. Inserir Elemento (Heapify Up)

```c
void push(Heap* heap, int value) {
    if (heap->size == heap->capacity) {
        // Redimensionar se necessário
        resize_heap(heap);
    }
    
    // Inserir no final
    heap->data[heap->size] = value;
    heap->size++;
    
    // Heapify up (subir elemento até posição correta)
    heapify_up(heap, heap->size - 1);
}

void heapify_up(Heap* heap, int index) {
    if (index == 0) return;
    
    int parent = (index - 1) / 2;
    
    if (heap->is_max_heap) {
        if (heap->data[index] > heap->data[parent]) {
            swap(&heap->data[index], &heap->data[parent]);
            heapify_up(heap, parent);
        }
    } else {
        if (heap->data[index] < heap->data[parent]) {
            swap(&heap->data[index], &heap->data[parent]);
            heapify_up(heap, parent);
        }
    }
}
```

### 3. Remover Topo (Heapify Down)

```c
int pop(Heap* heap) {
    if (heap->size == 0) {
        return -1;  // Erro: heap vazio
    }
    
    int root = heap->data[0];
    
    // Mover último elemento para raiz
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    
    // Heapify down (descer elemento até posição correta)
    heapify_down(heap, 0);
    
    return root;
}

void heapify_down(Heap* heap, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int extreme = index;  // max para max-heap, min para min-heap
    
    // Encontrar o extremo entre pai e filhos
    if (heap->is_max_heap) {
        if (left < heap->size && heap->data[left] > heap->data[extreme]) {
            extreme = left;
        }
        if (right < heap->size && heap->data[right] > heap->data[extreme]) {
            extreme = right;
        }
    } else {
        if (left < heap->size && heap->data[left] < heap->data[extreme]) {
            extreme = left;
        }
        if (right < heap->size && heap->data[right] < heap->data[extreme]) {
            extreme = right;
        }
    }
    
    // Se extremo não é o pai, trocar e continuar
    if (extreme != index) {
        swap(&heap->data[index], &heap->data[extreme]);
        heapify_down(heap, extreme);
    }
}
```

### 4. Ver Topo (Peek)

```c
int peek(Heap* heap) {
    if (heap->size == 0) {
        return -1;  // Erro: heap vazio
    }
    return heap->data[0];
}
```

### 5. Construir Heap de Array (Heapify)

```c
Heap* build_heap(int arr[], int n, int is_max_heap) {
    Heap* heap = create_heap(n, is_max_heap);
    
    // Copiar elementos
    for (int i = 0; i < n; i++) {
        heap->data[i] = arr[i];
    }
    heap->size = n;
    
    // Heapify de baixo para cima (mais eficiente que inserções)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify_down(heap, i);
    }
    
    return heap;
}
```

**Complexidade**: O(n) - mais eficiente que n inserções O(n log n)

## 🔧 Compilação

### Usando Makefile

```bash
make              # Compilar
make test         # Compilar e executar testes
make clean        # Limpar arquivos compilados
```

### Manual

```bash
gcc -Wall -Wextra -std=c99 -o heap heap_binario.c
./heap
```

## 📖 Aplicações Práticas

### 1. Fila de Prioridade
Implementação eficiente onde elemento de maior (ou menor) prioridade é sempre acessível em O(1).

```c
// Max-heap para prioridades (maior = mais urgente)
Heap* priority_queue = create_heap(100, 1);
push(priority_queue, 5);   // Prioridade 5
push(priority_queue, 10);  // Prioridade 10 (mais urgente)
int next_task = pop(priority_queue);  // Retorna 10
```

### 2. Heap Sort
Algoritmo de ordenação in-place com O(n log n).

```c
void heap_sort(int arr[], int n) {
    // 1. Construir max-heap
    Heap* heap = build_heap(arr, n, 1);
    
    // 2. Extrair elementos um por um
    for (int i = n - 1; i >= 0; i--) {
        arr[i] = pop(heap);
    }
}
```

### 3. K Maiores/Menores Elementos

```c
// Encontrar k menores elementos usando max-heap de tamanho k
int* k_smallest(int arr[], int n, int k) {
    Heap* heap = create_heap(k, 1);  // Max-heap
    
    for (int i = 0; i < n; i++) {
        if (heap->size < k) {
            push(heap, arr[i]);
        } else if (arr[i] < peek(heap)) {
            pop(heap);
            push(heap, arr[i]);
        }
    }
    
    return heap->data;
}
```

### 4. Algoritmo de Dijkstra
Encontrar caminho mais curto em grafos.

```c
// Min-heap para armazenar (distância, vértice)
```

### 5. Mediana de Stream de Dados

```c
// Usar dois heaps:
// Max-heap para metade inferior
// Min-heap para metade superior
```

## ⚠️ Cuidados Importantes

1. **Índices**: Cuidado com cálculo de pai/filhos
2. **Heap Vazio**: Sempre verificar antes de pop/peek
3. **Capacidade**: Implementar redimensionamento se necessário
4. **Tipo de Heap**: Garantir consistência (max vs min)

## 🚀 Otimizações

### 1. D-ary Heap
Heap com d filhos por nó (ao invés de 2).

**Vantagem**: Menos altura, menos swaps na inserção  
**Desvantagem**: Mais comparações na remoção

### 2. Lazy Deletion
Marcar elemento como deletado ao invés de remover.

### 3. Heap Binomial/Fibonacci
Estruturas mais avançadas para operações de merge eficientes.

## 📊 Visualização

### Exemplo de Max-Heap

```
Array: [90, 70, 80, 40, 50, 60, 30]

Visualização em Árvore:
        90
       /  \
      70   80
     / \   / \
    40 50 60 30
```

**Propriedade**: Cada pai ≥ filhos

## 📚 Recursos Adicionais

- [Binary Heap - Wikipedia](https://en.wikipedia.org/wiki/Binary_heap)
- [Heap Sort Algorithm](https://en.wikipedia.org/wiki/Heapsort)
- [Priority Queue](https://en.wikipedia.org/wiki/Priority_queue)
- [Dijkstra's Algorithm](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)

---

**Repositório**: https://github.com/profluiscaparroz/estrutura-dados-c
