# Filas (Queues)

## 📋 Visão Geral

Este diretório contém implementações completas e variações de filas (queues) em C, incluindo filas simples, circulares, com prioridade, e implementações avançadas.

## 📚 Implementações Incluídas

### Implementações Básicas

**exemploFilas.c** - Implementação básica de fila com array estático

**Conceitos:**
- Operações FIFO (First In, First Out)
- Enqueue (enfileirar)
- Dequeue (desenfileirar)
- Front e Rear

### Filas com Alocação Dinâmica

**exemploFilasAlocacaoDinamica.c** - Fila com crescimento dinâmico

**Vantagens:**
- Tamanho flexível
- Melhor uso de memória
- Sem limite pré-definido

### Fila Circular

**exemploFilaCircular.c** - Implementação eficiente usando buffer circular

**Conceitos:**
- Reutilização de espaço
- Índices circulares (módulo)
- Evita realocação frequente
- O(1) para enqueue e dequeue

**Vantagem principal**: Elimina desperdício de espaço da fila linear.

### Fila com Lista Encadeada

**exemploFilaListaEncadeada.c** - Fila usando lista encadeada

**Vantagens:**
- Tamanho ilimitado (apenas pela memória)
- Sem realocação
- Eficiente para filas dinâmicas

**Estrutura:**
```c
typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
    int size;
} Queue;
```

### Fila Dupla (Deque)

**exemploFilaDupla.c** - Double-ended queue (deque)

**Conceitos:**
- Inserção e remoção em ambas as extremidades
- Mais flexível que fila simples
- Pode funcionar como pilha ou fila

**Operações:**
- `push_front()` - Inserir no início
- `push_back()` - Inserir no fim
- `pop_front()` - Remover do início
- `pop_back()` - Remover do fim

### Fila com Prioridade

**exemploListaPrioridade.c** - Priority queue (fila de prioridade)

**Conceitos:**
- Elementos ordenados por prioridade
- Elemento de maior prioridade sai primeiro
- Implementação comum: heap binário

**Aplicações:**
- Algoritmos de grafo (Dijkstra, A*)
- Escalonamento de processos
- Event-driven simulation

### Filas Especializadas

**exemploFilaAssincrona.c** - Fila thread-safe para programação concorrente

**Conceitos:**
- Mutex e locks
- Sincronização entre threads
- Producer-consumer pattern

**exemploFilasGenericas.c** - Fila genérica usando `void*`

**Conceitos:**
- Type-agnostic data structures
- Ponteiros genéricos
- Callback functions

## 🔧 Compilação

### Básica
```bash
gcc -Wall -Wextra -std=c99 -o fila exemploFilas.c
./fila
```

### Com Threading (para fila assíncrona)
```bash
gcc -Wall -Wextra -std=c99 -pthread -o async exemploFilaAssincrona.c
./async
```

### Todas as implementações
```bash
gcc -Wall -Wextra -std=c99 -o circular exemploFilaCircular.c
gcc -Wall -Wextra -std=c99 -o dupla exemploFilaDupla.c
gcc -Wall -Wextra -std=c99 -o prioridade exemploListaPrioridade.c
gcc -Wall -Wextra -std=c99 -o encadeada exemploFilaListaEncadeada.c
```

## 📖 Operações Fundamentais

### Fila Simples

```c
typedef struct {
    int items[MAX_SIZE];
    int front;
    int rear;
    int size;
} Queue;

// Inicializar
void init_queue(Queue* q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

// Enfileirar (enqueue)
int enqueue(Queue* q, int value) {
    if (q->size == MAX_SIZE) {
        return 0;  // Fila cheia
    }
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->items[q->rear] = value;
    q->size++;
    return 1;
}

// Desenfileirar (dequeue)
int dequeue(Queue* q, int* value) {
    if (q->size == 0) {
        return 0;  // Fila vazia
    }
    *value = q->items[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    q->size--;
    return 1;
}

// Ver primeiro elemento (peek)
int peek(Queue* q, int* value) {
    if (q->size == 0) {
        return 0;
    }
    *value = q->items[q->front];
    return 1;
}

// Verificar se está vazia
int is_empty(Queue* q) {
    return q->size == 0;
}

// Verificar se está cheia
int is_full(Queue* q) {
    return q->size == MAX_SIZE;
}
```

### Fila Circular (Mais Eficiente)

```c
// Uso de módulo para índices circulares
q->rear = (q->rear + 1) % MAX_SIZE;
q->front = (q->front + 1) % MAX_SIZE;
```

**Vantagem**: Reutiliza espaços livres no início do array.

### Fila com Lista Encadeada

```c
// Enqueue O(1)
void enqueue(Queue* q, int value) {
    Node* new_node = create_node(value);
    
    if (q->rear == NULL) {
        q->front = q->rear = new_node;
    } else {
        q->rear->next = new_node;
        q->rear = new_node;
    }
    q->size++;
}

// Dequeue O(1)
int dequeue(Queue* q) {
    if (q->front == NULL) {
        return -1;  // Erro
    }
    
    Node* temp = q->front;
    int value = temp->data;
    q->front = q->front->next;
    
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    free(temp);
    q->size--;
    return value;
}
```

## 📊 Análise de Complexidade

### Fila com Array

| Operação | Circular | Linear | Comentário |
|----------|----------|--------|------------|
| Enqueue | O(1) | O(1) | Amortizado se redimensionar |
| Dequeue | O(1) | O(n) | Linear precisa shiftar |
| Peek | O(1) | O(1) | Apenas leitura |
| Espaço | O(n) | O(n) | n = capacidade |

### Fila com Lista Encadeada

| Operação | Complexidade | Comentário |
|----------|-------------|------------|
| Enqueue | O(1) | Inserção no rear |
| Dequeue | O(1) | Remoção do front |
| Peek | O(1) | Acesso ao front |
| Espaço | O(n) | n = número de elementos |

## 💡 Aplicações Práticas

### 1. Sistemas Operacionais
- Fila de processos prontos
- Fila de impressão
- Buffer de I/O

### 2. Algoritmos
- BFS (Breadth-First Search)
- Simulações de eventos
- Cache LRU (Least Recently Used)

### 3. Redes
- Buffers de pacotes
- Roteamento
- QoS (Quality of Service)

### 4. Sistemas em Tempo Real
- Fila de mensagens
- Event handling
- Producer-consumer

## ⚠️ Cuidados Importantes

### 1. Underflow
```c
if (is_empty(queue)) {
    printf("Erro: fila vazia!\n");
    return;
}
```

### 2. Overflow
```c
if (is_full(queue)) {
    printf("Erro: fila cheia!\n");
    return;
}
```

### 3. Vazamento de Memória (Lista Encadeada)
```c
// Sempre liberar nós ao desenfileirar
Node* temp = front;
front = front->next;
free(temp);  // IMPORTANTE!
```

### 4. Thread Safety (Filas Concorrentes)
```c
pthread_mutex_lock(&queue->mutex);
// Operação crítica
pthread_mutex_unlock(&queue->mutex);
```

## 🚀 Otimizações

### Cache Locality
- Preferir array para pequenas filas
- Lista encadeada tem pior locality

### Lock-Free Queues
- Usar atomic operations
- Melhor para alta concorrência

### Ring Buffer
- Fila circular com potência de 2
- Usa AND ao invés de módulo: `(index) & (size - 1)`

## 📚 Recursos Adicionais

- [Queue Data Structure](https://en.wikipedia.org/wiki/Queue_(abstract_data_type))
- [Circular Buffer](https://en.wikipedia.org/wiki/Circular_buffer)
- [Priority Queue](https://en.wikipedia.org/wiki/Priority_queue)
- [Deque](https://en.wikipedia.org/wiki/Double-ended_queue)

---

**Repositório**: https://github.com/profluiscaparroz/estrutura-dados-c
