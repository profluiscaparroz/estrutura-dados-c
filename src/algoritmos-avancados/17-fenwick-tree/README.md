# Fenwick Tree (Binary Indexed Tree)

## 📚 Definição Formal

Uma **Fenwick Tree** (também conhecida como **Binary Indexed Tree** ou **BIT**) é uma estrutura de dados que permite calcular **somas de prefixos** e realizar **atualizações de ponto** em tempo O(log n), usando espaço O(n).

**Definição Formal**: Para um array A[1..n], a Fenwick Tree T[1..n] armazena:
```
T[i] = Σ A[j]  para j ∈ (i - lowbit(i), i]
```

Onde `lowbit(i) = i & (-i)` é o bit menos significativo de i.

## 🎓 Fundamentação Teórica

### Origem Histórica

- **Peter Fenwick (1994)**: Artigo "A New Data Structure for Cumulative Frequency Tables" no *Software: Practice and Experience*
- **Motivação original**: Compressão aritmética e codificação de dados
- **Redescoberta**: Conhecida como Binary Indexed Tree na comunidade de programação competitiva

### Insight Fundamental

A representação binária de índices determina quais elementos cada posição da BIT cobre:

```
Índice 1  (0001): cobre [1, 1]     - 1 elemento
Índice 2  (0010): cobre [1, 2]     - 2 elementos
Índice 3  (0011): cobre [3, 3]     - 1 elemento
Índice 4  (0100): cobre [1, 4]     - 4 elementos
Índice 5  (0101): cobre [5, 5]     - 1 elemento
Índice 6  (0110): cobre [5, 6]     - 2 elementos
Índice 7  (0111): cobre [7, 7]     - 1 elemento
Índice 8  (1000): cobre [1, 8]     - 8 elementos
```

### Operação lowbit

```c
int lowbit(int x) {
    return x & (-x);  // Isola o bit menos significativo
}
```

**Exemplos**:
- lowbit(6) = lowbit(110₂) = 2 = 10₂
- lowbit(12) = lowbit(1100₂) = 4 = 100₂
- lowbit(8) = lowbit(1000₂) = 8 = 1000₂

## 📊 Análise de Complexidade

| Operação | Complexidade |
|----------|--------------|
| Construção | O(n) ou O(n log n) |
| Point Update | O(log n) |
| Prefix Sum | O(log n) |
| Range Sum | O(log n) |
| Espaço | O(n) |

### Comparação com Segment Tree

| Aspecto | Fenwick Tree | Segment Tree |
|---------|--------------|--------------|
| Espaço | n + 1 | 4n |
| Constante | Menor | Maior |
| Código | Simples | Mais complexo |
| Flexibilidade | Menor | Maior |
| Range Update | Requer 2 BITs | Lazy propagation |

## 🔧 Implementação

### Estrutura de Dados

```c
typedef struct {
    int *tree;
    int n;
} FenwickTree;

FenwickTree* create_fenwick(int n) {
    FenwickTree *ft = malloc(sizeof(FenwickTree));
    ft->n = n;
    ft->tree = calloc(n + 1, sizeof(int));  // 1-indexed
    return ft;
}
```

### Point Update

Adiciona `delta` ao elemento no índice `i`:

```c
void update(FenwickTree *ft, int i, int delta) {
    for (; i <= ft->n; i += i & (-i)) {
        ft->tree[i] += delta;
    }
}
```

**Visualização para update(5, delta)**:
```
5 (101) → 6 (110) → 8 (1000) → ...
```

### Prefix Sum

Retorna soma de A[1..i]:

```c
int prefix_sum(FenwickTree *ft, int i) {
    int sum = 0;
    for (; i > 0; i -= i & (-i)) {
        sum += ft->tree[i];
    }
    return sum;
}
```

**Visualização para prefix_sum(7)**:
```
7 (111) → 6 (110) → 4 (100) → 0
```

### Range Sum

Retorna soma de A[l..r]:

```c
int range_sum(FenwickTree *ft, int l, int r) {
    return prefix_sum(ft, r) - prefix_sum(ft, l - 1);
}
```

### Construção Eficiente O(n)

```c
void build(FenwickTree *ft, int arr[], int n) {
    for (int i = 1; i <= n; i++) {
        ft->tree[i] += arr[i - 1];  // arr é 0-indexed
        int j = i + (i & (-i));
        if (j <= n) {
            ft->tree[j] += ft->tree[i];
        }
    }
}
```

## 📐 Extensões

### 1. Range Update, Point Query

Usando difference array:

```c
typedef struct {
    FenwickTree *ft;
} RangeUpdateBIT;

// Adiciona val a todos elementos em [l, r]
void range_update(RangeUpdateBIT *rb, int l, int r, int val) {
    update(rb->ft, l, val);
    update(rb->ft, r + 1, -val);
}

// Retorna valor no índice i
int point_query(RangeUpdateBIT *rb, int i) {
    return prefix_sum(rb->ft, i);
}
```

### 2. Range Update, Range Query

Usando duas BITs:

```c
typedef struct {
    FenwickTree *ft1;
    FenwickTree *ft2;
    int n;
} RangeRangeBIT;

void range_update(RangeRangeBIT *rr, int l, int r, int val) {
    // ft1
    update(rr->ft1, l, val);
    update(rr->ft1, r + 1, -val);
    // ft2
    update(rr->ft2, l, val * (l - 1));
    update(rr->ft2, r + 1, -val * r);
}

int prefix_sum_rr(RangeRangeBIT *rr, int i) {
    return prefix_sum(rr->ft1, i) * i - prefix_sum(rr->ft2, i);
}

int range_query(RangeRangeBIT *rr, int l, int r) {
    return prefix_sum_rr(rr, r) - prefix_sum_rr(rr, l - 1);
}
```

### 3. Fenwick Tree 2D

Para matrizes:

```c
typedef struct {
    int **tree;
    int n, m;
} FenwickTree2D;

void update_2d(FenwickTree2D *ft, int x, int y, int delta) {
    for (int i = x; i <= ft->n; i += i & (-i)) {
        for (int j = y; j <= ft->m; j += j & (-j)) {
            ft->tree[i][j] += delta;
        }
    }
}

int prefix_sum_2d(FenwickTree2D *ft, int x, int y) {
    int sum = 0;
    for (int i = x; i > 0; i -= i & (-i)) {
        for (int j = y; j > 0; j -= j & (-j)) {
            sum += ft->tree[i][j];
        }
    }
    return sum;
}
```

**Complexidade**: O(log n × log m)

### 4. Fenwick Tree para Mínimo/Máximo

Requer modificações (apenas funciona para queries de prefixo):

```c
void update_max(FenwickTree *ft, int i, int val) {
    for (; i <= ft->n; i += i & (-i)) {
        ft->tree[i] = max(ft->tree[i], val);
    }
}

int prefix_max(FenwickTree *ft, int i) {
    int result = INT_MIN;
    for (; i > 0; i -= i & (-i)) {
        result = max(result, ft->tree[i]);
    }
    return result;
}
```

**Nota**: Não suporta range queries arbitrárias para min/max.

## 🎯 Aplicações Práticas

### 1. Contagem de Inversões

```c
long long count_inversions(int arr[], int n) {
    // Comprimir coordenadas se necessário
    FenwickTree *ft = create_fenwick(n);
    long long inversions = 0;
    
    for (int i = n - 1; i >= 0; i--) {
        inversions += prefix_sum(ft, arr[i] - 1);
        update(ft, arr[i], 1);
    }
    
    return inversions;
}
```

### 2. K-th Smallest Element

Usando busca binária na BIT de frequências:

```c
int kth_smallest(FenwickTree *ft, int k) {
    int pos = 0;
    int bitMask = 1 << (int)log2(ft->n);
    
    while (bitMask > 0) {
        int t = pos + bitMask;
        if (t <= ft->n && ft->tree[t] < k) {
            k -= ft->tree[t];
            pos = t;
        }
        bitMask >>= 1;
    }
    
    return pos + 1;
}
```

### 3. Somas de Intervalo Online

Queries e updates intercalados em tempo real.

### 4. Estatísticas de Ordem

Contagem de elementos menores/maiores em ranges.

## 🔄 Comparação

### Quando Usar Fenwick Tree

✅ Usar quando:
- Apenas somas de prefixo/range são necessárias
- Memória é limitada
- Código simples é preferido
- Performance máxima é desejada

❌ Usar Segment Tree quando:
- Operações não-associativas são necessárias
- Lazy propagation é requerido
- Queries que não são prefix-based

## 📖 Referências Bibliográficas

1. **Fenwick, P. M.** (1994). A New Data Structure for Cumulative Frequency Tables. *Software: Practice and Experience*, 24(3), 327-336.

2. **Topcoder**. Binary Indexed Trees. Tutorial clássico.

3. **Halim, S., & Halim, F.** (2013). *Competitive Programming* (3rd ed.). Capítulo sobre BIT.

4. **CP-Algorithms**. Fenwick Tree. https://cp-algorithms.com/data_structures/fenwick.html

5. **Ryabko, B. Y.** (1989). A fast on-line code. *Soviet Mathematics Doklady*, 39, 533-537. (Descoberta independente)

## 🔗 Navegação

← **[16-segment-tree](../16-segment-tree/)**: Segment Tree

→ **[18-disjoint-set-union](../18-disjoint-set-union/)**: Disjoint Set Union (Union-Find)

---

*Este material faz parte do curso de Estrutura de Dados em C.*
