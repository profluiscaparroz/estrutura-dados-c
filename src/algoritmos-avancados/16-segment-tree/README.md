# Segment Tree (Árvore de Segmentos)

## 📚 Definição Formal

Uma **Segment Tree** (Árvore de Segmentos) é uma estrutura de dados em árvore usada para armazenar informações sobre intervalos ou segmentos de um array. Permite consultas e atualizações de intervalos em tempo O(log n).

**Definição Formal**: Para um array A[0..n-1], a Segment Tree é uma árvore binária completa onde:
- Cada folha representa um elemento de A
- Cada nó interno representa a agregação (soma, mínimo, máximo, etc.) dos seus filhos
- O nó raiz representa o intervalo [0, n-1]

## 🎓 Fundamentação Teórica

### Origem e Aplicações

- Amplamente usada em **programação competitiva** desde os anos 2000
- Fundamental para problemas de **Range Minimum Query (RMQ)**
- Base para estruturas mais complexas como Segment Tree com Lazy Propagation

### Estrutura da Árvore

Para um array de tamanho n:
- **Altura**: ⌈log₂(n)⌉
- **Número de nós**: 2 × 2^⌈log₂(n)⌉ - 1 ≤ 4n
- **Representação**: Array de tamanho 4n (para simplificar)

### Mapeamento de Índices

Para nó no índice i:
- Filho esquerdo: 2i + 1
- Filho direito: 2i + 2
- Pai: (i - 1) / 2

## 📊 Análise de Complexidade

| Operação | Complexidade |
|----------|--------------|
| Construção | O(n) |
| Point Update | O(log n) |
| Range Query | O(log n) |
| Range Update (Lazy) | O(log n) |
| Espaço | O(n) |

## 🔧 Implementação

### Estrutura de Dados

```c
typedef struct {
    int *tree;    // Array que representa a árvore
    int *lazy;    // Array para lazy propagation (opcional)
    int n;        // Tamanho do array original
} SegmentTree;
```

### Construção

```c
void build(SegmentTree *st, int arr[], int node, int start, int end) {
    if (start == end) {
        // Folha: armazena elemento do array
        st->tree[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        
        // Construir subárvores recursivamente
        build(st, arr, 2*node + 1, start, mid);
        build(st, arr, 2*node + 2, mid + 1, end);
        
        // Combinar resultados (exemplo: soma)
        st->tree[node] = st->tree[2*node + 1] + st->tree[2*node + 2];
    }
}

SegmentTree* create_segment_tree(int arr[], int n) {
    SegmentTree *st = malloc(sizeof(SegmentTree));
    st->n = n;
    st->tree = calloc(4 * n, sizeof(int));
    st->lazy = calloc(4 * n, sizeof(int));
    
    build(st, arr, 0, 0, n - 1);
    return st;
}
```

### Range Query

```c
int query(SegmentTree *st, int node, int start, int end, 
          int l, int r) {
    // Caso 1: Fora do intervalo
    if (r < start || end < l) {
        return 0;  // Elemento neutro (0 para soma, INF para min, etc.)
    }
    
    // Caso 2: Completamente dentro do intervalo
    if (l <= start && end <= r) {
        return st->tree[node];
    }
    
    // Caso 3: Parcialmente dentro
    int mid = (start + end) / 2;
    int left_result = query(st, 2*node + 1, start, mid, l, r);
    int right_result = query(st, 2*node + 2, mid + 1, end, l, r);
    
    return left_result + right_result;  // Combinar
}

// Interface
int range_query(SegmentTree *st, int l, int r) {
    return query(st, 0, 0, st->n - 1, l, r);
}
```

### Point Update

```c
void update(SegmentTree *st, int node, int start, int end, 
            int idx, int val) {
    if (start == end) {
        // Folha: atualizar valor
        st->tree[node] = val;
    } else {
        int mid = (start + end) / 2;
        
        if (idx <= mid) {
            update(st, 2*node + 1, start, mid, idx, val);
        } else {
            update(st, 2*node + 2, mid + 1, end, idx, val);
        }
        
        // Recalcular nó interno
        st->tree[node] = st->tree[2*node + 1] + st->tree[2*node + 2];
    }
}
```

## 📐 Lazy Propagation

Para atualizações em intervalos eficientes:

### Conceito

- Adiar atualizações até serem necessárias
- Armazenar pendências no array `lazy`
- Propagar ao visitar nós

### Implementação

```c
void push_down(SegmentTree *st, int node, int start, int end) {
    if (st->lazy[node] != 0) {
        int mid = (start + end) / 2;
        
        // Propagar para filhos
        st->tree[2*node + 1] += st->lazy[node] * (mid - start + 1);
        st->tree[2*node + 2] += st->lazy[node] * (end - mid);
        
        st->lazy[2*node + 1] += st->lazy[node];
        st->lazy[2*node + 2] += st->lazy[node];
        
        st->lazy[node] = 0;
    }
}

void range_update(SegmentTree *st, int node, int start, int end,
                  int l, int r, int val) {
    if (r < start || end < l) return;
    
    if (l <= start && end <= r) {
        // Atualização lazy
        st->tree[node] += val * (end - start + 1);
        st->lazy[node] += val;
        return;
    }
    
    push_down(st, node, start, end);
    
    int mid = (start + end) / 2;
    range_update(st, 2*node + 1, start, mid, l, r, val);
    range_update(st, 2*node + 2, mid + 1, end, l, r, val);
    
    st->tree[node] = st->tree[2*node + 1] + st->tree[2*node + 2];
}
```

## 🔄 Tipos de Consultas

### 1. Range Sum Query (RSQ)

```c
// Combinar: soma
tree[node] = tree[left] + tree[right];
// Neutro: 0
```

### 2. Range Minimum Query (RMQ)

```c
// Combinar: mínimo
tree[node] = min(tree[left], tree[right]);
// Neutro: INT_MAX
```

### 3. Range Maximum Query

```c
// Combinar: máximo
tree[node] = max(tree[left], tree[right]);
// Neutro: INT_MIN
```

### 4. Range GCD Query

```c
// Combinar: GCD
tree[node] = gcd(tree[left], tree[right]);
// Neutro: 0
```

### 5. Range Count Query

Contar elementos satisfazendo condição:
```c
// Combinar: soma de contagens
tree[node] = tree[left] + tree[right];
```

## 📐 Variantes

### 1. Segment Tree 2D

Para matrizes:
```c
// Query: O(log n × log m)
// Espaço: O(n × m)
```

### 2. Persistent Segment Tree

Mantém versões anteriores:
- Cada atualização cria O(log n) novos nós
- Permite consultas em versões passadas
- Espaço: O(n + q log n) para q operações

### 3. Merge Sort Tree

Armazena arrays ordenados nos nós:
- Query de k-ésimo menor em range
- Espaço: O(n log n)

### 4. Segment Tree com Beats

Para operações de clamp (min/max):
- Mantém estatísticas adicionais
- Operações como "set all in range to min(x, val)"

## 🎯 Aplicações Práticas

### 1. Problemas de Range Query

- Soma de intervalo com atualizações
- Mínimo/máximo de intervalo
- GCD de intervalo

### 2. Geometria Computacional

- Área de união de retângulos
- Interseção de segmentos de linha

### 3. Inversão de Arrays

- Contar inversões durante merge sort
- Rank queries

### 4. Compressão de Coordenadas

Combinar com coordenadas comprimidas para espaços grandes.

### 5. Competitive Programming

**Problemas clássicos**:
- SPOJ HORRIBLE: Range update, range query
- Codeforces: Diversos problemas de range query

## 🔄 Comparação com Outras Estruturas

| Estrutura | Build | Point Update | Range Query | Range Update |
|-----------|-------|--------------|-------------|--------------|
| Array | O(n) | O(1) | O(n) | O(n) |
| Prefix Sum | O(n) | O(n) | O(1) | O(n) |
| Segment Tree | O(n) | O(log n) | O(log n) | O(n log n)* |
| Segment Tree (Lazy) | O(n) | O(log n) | O(log n) | O(log n) |
| Fenwick Tree | O(n) | O(log n) | O(log n) | O(log n)** |
| Sqrt Decomposition | O(n) | O(1) | O(√n) | O(√n) |

*Sem lazy propagation
**Com técnica de difference array

## 📖 Referências Bibliográficas

1. **Bentley, J. L.** (1977). Solutions to Klee's Rectangle Problems. Unpublished manuscript.

2. **de Berg, M., et al.** (2008). *Computational Geometry: Algorithms and Applications* (3rd ed.). Springer.

3. **Halim, S., & Halim, F.** (2013). *Competitive Programming* (3rd ed.). Capítulo sobre Segment Trees.

4. **CP-Algorithms**. Segment Tree. https://cp-algorithms.com/data_structures/segment_tree.html

5. **Eppstein, D.** (2011). ICS 161: Design and Analysis of Algorithms. UC Irvine.

## 🔗 Navegação

← **[15-skip-list](../15-skip-list/)**: Skip List

→ **[17-fenwick-tree](../17-fenwick-tree/)**: Fenwick Tree

---

*Este material faz parte do curso de Estrutura de Dados em C.*
