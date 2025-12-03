# Disjoint Set Union (Union-Find)

## 📚 Definição Formal

**Disjoint Set Union** (DSU), também conhecido como **Union-Find**, é uma estrutura de dados que mantém uma coleção de conjuntos disjuntos (sem interseção) e suporta duas operações principais:
1. **Find**: Determina a qual conjunto um elemento pertence
2. **Union**: Une dois conjuntos em um único

**Definição Formal**: Uma estrutura DSU sobre universo U mantém partição P = {S₁, S₂, ..., Sₖ} onde:
- Sᵢ ∩ Sⱼ = ∅ para i ≠ j
- S₁ ∪ S₂ ∪ ... ∪ Sₖ = U

## 🎓 Fundamentação Teórica

### Origem Histórica

- **Galler & Fisher (1964)**: Primeiro artigo descrevendo Union-Find
- **Tarjan (1975)**: Análise de complexidade com path compression
- **Tarjan & van Leeuwen (1984)**: Prova da complexidade amortizada inversa de Ackermann

### Função de Ackermann e Inversa

A complexidade amortizada é O(α(n)), onde α é a **inversa da função de Ackermann**:

```
A(0, n) = n + 1
A(m, 0) = A(m-1, 1)
A(m, n) = A(m-1, A(m, n-1))
```

**Propriedade**: α(n) ≤ 4 para todo n ≤ 10^80 (número de átomos no universo observável)

**Na prática**: α(n) é efetivamente constante.

## 📊 Análise de Complexidade

| Operação | Sem otimização | Union by Rank | Path Compression | Ambos |
|----------|----------------|---------------|------------------|-------|
| Find | O(n) | O(log n) | O(log n)* | O(α(n))* |
| Union | O(n) | O(log n) | O(log n)* | O(α(n))* |
| Make Set | O(1) | O(1) | O(1) | O(1) |

*Amortizado

### Teorema de Tarjan

**Teorema**: Uma sequência de m operações em n elementos requer tempo O(m × α(n)) com union by rank e path compression.

## 🔧 Implementação

### Estrutura de Dados

```c
typedef struct {
    int *parent;  // parent[i] = pai de i
    int *rank;    // rank[i] = altura máxima da subárvore
    int n;        // Número de elementos
    int num_sets; // Número de conjuntos
} DSU;

DSU* create_dsu(int n) {
    DSU *dsu = malloc(sizeof(DSU));
    dsu->parent = malloc(n * sizeof(int));
    dsu->rank = calloc(n, sizeof(int));
    dsu->n = n;
    dsu->num_sets = n;
    
    // Inicialmente, cada elemento é seu próprio conjunto
    for (int i = 0; i < n; i++) {
        dsu->parent[i] = i;
    }
    
    return dsu;
}
```

### Find com Path Compression

```c
int find(DSU *dsu, int x) {
    if (dsu->parent[x] != x) {
        dsu->parent[x] = find(dsu, dsu->parent[x]);  // Path compression
    }
    return dsu->parent[x];
}
```

**Alternativa iterativa**:

```c
int find_iterative(DSU *dsu, int x) {
    int root = x;
    
    // Encontrar raiz
    while (dsu->parent[root] != root) {
        root = dsu->parent[root];
    }
    
    // Comprimir caminho
    while (dsu->parent[x] != root) {
        int next = dsu->parent[x];
        dsu->parent[x] = root;
        x = next;
    }
    
    return root;
}
```

### Union by Rank

```c
bool union_sets(DSU *dsu, int x, int y) {
    int root_x = find(dsu, x);
    int root_y = find(dsu, y);
    
    if (root_x == root_y) {
        return false;  // Já no mesmo conjunto
    }
    
    // Anexar árvore menor à maior
    if (dsu->rank[root_x] < dsu->rank[root_y]) {
        dsu->parent[root_x] = root_y;
    } else if (dsu->rank[root_x] > dsu->rank[root_y]) {
        dsu->parent[root_y] = root_x;
    } else {
        dsu->parent[root_y] = root_x;
        dsu->rank[root_x]++;
    }
    
    dsu->num_sets--;
    return true;
}
```

### Union by Size

Alternativa a union by rank:

```c
typedef struct {
    int *parent;
    int *size;  // Tamanho do conjunto
    int n;
} DSU_Size;

void union_by_size(DSU_Size *dsu, int x, int y) {
    int root_x = find(dsu, x);
    int root_y = find(dsu, y);
    
    if (root_x == root_y) return;
    
    // Anexar conjunto menor ao maior
    if (dsu->size[root_x] < dsu->size[root_y]) {
        int temp = root_x;
        root_x = root_y;
        root_y = temp;
    }
    
    dsu->parent[root_y] = root_x;
    dsu->size[root_x] += dsu->size[root_y];
}
```

## 📐 Otimizações

### 1. Path Compression

Cada find faz todos os nós visitados apontarem diretamente para a raiz.

### 2. Path Halving

Alternativa mais simples:

```c
int find_halving(DSU *dsu, int x) {
    while (dsu->parent[x] != x) {
        dsu->parent[x] = dsu->parent[dsu->parent[x]];  // Pular um nível
        x = dsu->parent[x];
    }
    return x;
}
```

### 3. Path Splitting

Cada nó aponta para seu avô:

```c
int find_splitting(DSU *dsu, int x) {
    while (dsu->parent[x] != x) {
        int next = dsu->parent[x];
        dsu->parent[x] = dsu->parent[next];
        x = next;
    }
    return x;
}
```

## 🎯 Aplicações Práticas

### 1. Algoritmo de Kruskal (MST)

```c
typedef struct {
    int u, v, weight;
} Edge;

int compare_edges(const void *a, const void *b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

int kruskal(Edge edges[], int num_edges, int num_vertices) {
    qsort(edges, num_edges, sizeof(Edge), compare_edges);
    
    DSU *dsu = create_dsu(num_vertices);
    int mst_weight = 0;
    int edges_added = 0;
    
    for (int i = 0; i < num_edges && edges_added < num_vertices - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        
        if (find(dsu, u) != find(dsu, v)) {
            union_sets(dsu, u, v);
            mst_weight += edges[i].weight;
            edges_added++;
        }
    }
    
    return mst_weight;
}
```

### 2. Detecção de Ciclos em Grafos

```c
bool has_cycle(Edge edges[], int num_edges, int num_vertices) {
    DSU *dsu = create_dsu(num_vertices);
    
    for (int i = 0; i < num_edges; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        
        if (find(dsu, u) == find(dsu, v)) {
            return true;  // Aresta fecha ciclo
        }
        union_sets(dsu, u, v);
    }
    
    return false;
}
```

### 3. Componentes Conectados Dinâmicos

```c
int count_components(DSU *dsu) {
    return dsu->num_sets;
}

bool are_connected(DSU *dsu, int x, int y) {
    return find(dsu, x) == find(dsu, y);
}
```

### 4. Percolação (Física Estatística)

Simulação de percolação em grades:
- Sites se conectam aleatoriamente
- Verificar se topo conecta ao fundo

### 5. Problema de LCA Offline (Tarjan)

Lowest Common Ancestor em árvores.

## 🔄 Extensões

### 1. Weighted Union-Find

Armazenar informação adicional (distância à raiz):

```c
typedef struct {
    int *parent;
    int *dist;  // Distância até o pai
    int n;
} WeightedDSU;

int find_weighted(WeightedDSU *dsu, int x, int *total_dist) {
    if (dsu->parent[x] == x) {
        *total_dist = 0;
        return x;
    }
    
    int root = find_weighted(dsu, dsu->parent[x], total_dist);
    *total_dist += dsu->dist[x];
    
    // Path compression com atualização de distância
    dsu->dist[x] = *total_dist;
    dsu->parent[x] = root;
    
    return root;
}
```

### 2. Rollback (Persistent DSU)

Para algoritmos que precisam desfazer operações:
- Não usar path compression
- Manter stack de operações

### 3. Small-to-Large Merging

Otimização para manter conjuntos explícitos:
```
Sempre anexar conjunto menor ao maior
Total: O(n log n) operações de movimento
```

## 📖 Referências Bibliográficas

1. **Tarjan, R. E.** (1975). Efficiency of a Good But Not Linear Set Union Algorithm. *JACM*, 22(2), 215-225.

2. **Tarjan, R. E., & van Leeuwen, J.** (1984). Worst-case Analysis of Set Union Algorithms. *JACM*, 31(2), 245-281.

3. **Galler, B. A., & Fisher, M. J.** (1964). An Improved Equivalence Algorithm. *Communications of the ACM*, 7(5), 301-303.

4. **Cormen, T. H., et al.** (2009). *Introduction to Algorithms* (3rd ed.). MIT Press. Capítulo 21.

5. **Sedgewick, R., & Wayne, K.** (2011). *Algorithms* (4th ed.). Addison-Wesley.

## 🔗 Navegação

← **[17-fenwick-tree](../17-fenwick-tree/)**: Fenwick Tree

→ **[19-kd-tree](../19-kd-tree/)**: K-D Tree

---

*Este material faz parte do curso de Estrutura de Dados em C.*
