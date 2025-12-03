# Skip List

## 📚 Definição Formal

Uma **Skip List** é uma estrutura de dados probabilística que permite busca, inserção e deleção em tempo O(log n) esperado. Consiste em múltiplas camadas de listas ligadas ordenadas, onde camadas superiores servem como "atalhos" para acelerar a navegação.

**Definição Formal**: Uma Skip List é uma sequência de listas L₀, L₁, ..., Lₕ onde:
- L₀ contém todos os elementos em ordem
- Cada Lᵢ₊₁ é um subconjunto de Lᵢ
- Cada elemento em Lᵢ aparece em Lᵢ₊₁ com probabilidade p (tipicamente 1/2)

## 🎓 Fundamentação Teórica

### Origem Histórica

- **William Pugh (1990)**: Artigo "Skip Lists: A Probabilistic Alternative to Balanced Trees"
- **Motivação**: Estrutura mais simples que árvores balanceadas com mesma complexidade esperada
- **Inspiração**: "Express lanes" em rodovias

### Análise Probabilística

**Teorema**: Com probabilidade p = 1/2:
- Altura esperada: O(log n)
- Número esperado de elementos por nível i: n/2ⁱ
- Espaço esperado: O(n)

**Prova (altura)**:
- Probabilidade de elemento atingir nível k: (1/2)^k
- Probabilidade de altura > c log n: n × (1/2)^(c log n) = n^(1-c)
- Para c = 2: probabilidade < 1/n (muito improvável)

## 📊 Análise de Complexidade

| Operação | Esperado | Pior Caso |
|----------|----------|-----------|
| Busca | O(log n) | O(n) |
| Inserção | O(log n) | O(n) |
| Deleção | O(log n) | O(n) |
| Espaço | O(n) | O(n log n) |

**Número esperado de comparações**: (1/p) × log_(1/p)(n) ≈ 2 log₂ n para p = 1/2

### Escolha de p

| p | Comparações/busca | Espaço/elemento |
|---|-------------------|-----------------|
| 1/2 | 2 log₂ n | 2 ponteiros |
| 1/4 | 4/3 log₂ n | 4/3 ponteiros |
| 1/e | log₂ n | e/(e-1) ≈ 1.58 ponteiros |

**Trade-off**: p menor = menos níveis, mais busca horizontal

## 🔧 Estrutura de Dados

```c
#define MAX_LEVEL 32  // log₂(2³²) = 32

typedef struct SkipNode {
    int key;
    void *value;
    struct SkipNode **forward;  // Array de ponteiros
    int level;
} SkipNode;

typedef struct {
    SkipNode *header;
    int level;     // Nível atual da lista
    int max_level;
    float p;       // Probabilidade de promoção
    size_t size;
} SkipList;
```

## 🔄 Operações Fundamentais

### Geração de Nível Aleatório

```c
int random_level(float p, int max_level) {
    int level = 1;
    while ((float)rand() / RAND_MAX < p && level < max_level) {
        level++;
    }
    return level;
}
```

### Busca

```c
SkipNode* skip_search(SkipList *list, int key) {
    SkipNode *current = list->header;
    
    // Começar do nível mais alto
    for (int i = list->level - 1; i >= 0; i--) {
        // Avançar enquanto próximo elemento for menor
        while (current->forward[i] && current->forward[i]->key < key) {
            current = current->forward[i];
        }
    }
    
    // Mover para o próximo no nível 0
    current = current->forward[0];
    
    if (current && current->key == key) {
        return current;
    }
    return NULL;
}
```

### Inserção

```c
void skip_insert(SkipList *list, int key, void *value) {
    SkipNode *update[MAX_LEVEL];
    SkipNode *current = list->header;
    
    // Encontrar posição de inserção em cada nível
    for (int i = list->level - 1; i >= 0; i--) {
        while (current->forward[i] && current->forward[i]->key < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }
    
    current = current->forward[0];
    
    // Atualizar se chave existe
    if (current && current->key == key) {
        current->value = value;
        return;
    }
    
    // Gerar nível para novo nó
    int new_level = random_level(list->p, list->max_level);
    
    // Atualizar nível da lista se necessário
    if (new_level > list->level) {
        for (int i = list->level; i < new_level; i++) {
            update[i] = list->header;
        }
        list->level = new_level;
    }
    
    // Criar e inserir novo nó
    SkipNode *new_node = create_node(key, value, new_level);
    for (int i = 0; i < new_level; i++) {
        new_node->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = new_node;
    }
    
    list->size++;
}
```

### Deleção

```c
bool skip_delete(SkipList *list, int key) {
    SkipNode *update[MAX_LEVEL];
    SkipNode *current = list->header;
    
    for (int i = list->level - 1; i >= 0; i--) {
        while (current->forward[i] && current->forward[i]->key < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }
    
    current = current->forward[0];
    
    if (current && current->key == key) {
        // Remover de todos os níveis
        for (int i = 0; i < list->level; i++) {
            if (update[i]->forward[i] != current) break;
            update[i]->forward[i] = current->forward[i];
        }
        
        free(current->forward);
        free(current);
        
        // Diminuir nível se necessário
        while (list->level > 1 && 
               list->header->forward[list->level - 1] == NULL) {
            list->level--;
        }
        
        list->size--;
        return true;
    }
    
    return false;
}
```

## 📐 Variantes

### 1. Deterministic Skip List

Remove aleatoriedade usando contagem:
- Mantém invariante de 1-2 ou 2-3 nós entre promoções
- Complexidade garantida O(log n)

### 2. Concurrent Skip List

Lock-free ou fine-grained locking:
- Cada nível pode ser modificado independentemente
- Usado em Java's ConcurrentSkipListMap

```c
typedef struct ConcurrentSkipNode {
    int key;
    atomic_int marked;  // Para deleção lógica
    struct ConcurrentSkipNode **forward;
    pthread_mutex_t lock;
} ConcurrentSkipNode;
```

### 3. Indexable Skip List

Com contagem de elementos entre nós:
- Suporta acesso por índice O(log n)
- Operações de rank O(log n)

```c
typedef struct IndexableSkipNode {
    int key;
    int *span;  // Distância até próximo nó em cada nível
    struct IndexableSkipNode **forward;
} IndexableSkipNode;
```

### 4. Interval Skip List

Para consultas de intervalo:
- Armazena intervalos ao invés de pontos
- Suporta stabbing queries

## 🎯 Aplicações Práticas

### 1. Redis (ZSET)

**Sorted Sets** implementados com Skip List:
```redis
ZADD myset 1 "one" 2 "two" 3 "three"
ZRANGEBYSCORE myset 1 2  # Range query
ZRANK myset "two"        # Rank query
```

**Por que Skip List em vez de árvore balanceada?**
- Range queries mais simples
- Implementação concorrente mais fácil
- Performance comparável

### 2. LevelDB / RocksDB

**MemTable** implementada com Skip List:
- Write-ahead log + Skip List
- Flush para SSTable quando cheio

### 3. Lucene / Elasticsearch

**Posting Lists** otimizadas:
- Skip pointers para acelerar intersecção
- Trade-off espaço vs velocidade

### 4. MemSQL

**In-memory Indexes**:
- Lock-free Skip Lists
- Alta concorrência

## 🔄 Comparação com Outras Estruturas

| Estrutura | Busca | Insert | Delete | Implementação | Concorrência |
|-----------|-------|--------|--------|---------------|--------------|
| Skip List | O(log n)* | O(log n)* | O(log n)* | Simples | Fácil |
| AVL Tree | O(log n) | O(log n) | O(log n) | Média | Difícil |
| Red-Black | O(log n) | O(log n) | O(log n) | Complexa | Difícil |
| B-Tree | O(log n) | O(log n) | O(log n) | Complexa | Média |

*Esperado

### Vantagens da Skip List

1. **Simplicidade**: Mais fácil de implementar que árvores balanceadas
2. **Range Queries**: Naturalmente eficiente (seguir nível 0)
3. **Concorrência**: Lock-free mais simples
4. **Cache**: Níveis superiores cabem em cache

### Desvantagens

1. **Espaço**: Overhead de ponteiros
2. **Probabilístico**: Sem garantia de pior caso
3. **Reprodutibilidade**: Depende de seed do RNG

## 📖 Referências Bibliográficas

1. **Pugh, W.** (1990). Skip Lists: A Probabilistic Alternative to Balanced Trees. *Communications of the ACM*, 33(6), 668-676.

2. **Pugh, W.** (1990). Concurrent Maintenance of Skip Lists. Technical Report CS-TR-2222, University of Maryland.

3. **Herlihy, M., Lev, Y., Luchangco, V., & Shavit, N.** (2006). A Provably Correct Scalable Concurrent Skip List. *OPODIS*.

4. **Fraser, K.** (2004). Practical Lock-Freedom. PhD Thesis, University of Cambridge.

5. **Dean, B. C., & Jones, Z. H.** (2007). Exploring the Duality between Skip Lists and Binary Search Trees. *ACM Southeast Regional Conference*.

## 🔗 Navegação

← **[14-avl-tree](../14-avl-tree/)**: AVL Tree

→ **[16-segment-tree](../16-segment-tree/)**: Segment Tree

---

*Este material faz parte do curso de Estrutura de Dados em C.*
