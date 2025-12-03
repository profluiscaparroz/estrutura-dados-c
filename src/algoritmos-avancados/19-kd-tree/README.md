# K-D Tree (K-Dimensional Tree)

## 📚 Definição Formal

Uma **K-D Tree** (K-Dimensional Tree) é uma estrutura de dados de particionamento espacial para organizar pontos em um espaço k-dimensional. É uma árvore binária de busca onde cada nó representa um hiperplano que divide o espaço em dois semi-espaços.

**Definição Formal**: Uma K-D Tree para um conjunto P de pontos em ℝᵏ é uma árvore binária onde:
- Cada nó interno representa um hiperplano perpendicular a uma das k dimensões
- Nós em profundidade d dividem pelo eixo (d mod k)
- A subárvore esquerda contém pontos menores na dimensão de corte
- A subárvore direita contém pontos maiores ou iguais

## 🎓 Fundamentação Teórica

### Origem Histórica

- **Jon Louis Bentley (1975)**: Artigo "Multidimensional Binary Search Trees Used for Associative Searching"
- **Stanford University**: Desenvolvida durante seu doutorado
- **Aplicação original**: Busca associativa em bancos de dados multidimensionais

### Particionamento do Espaço

A K-D Tree divide recursivamente o espaço:

```
      ┌─────────────────────┐
      │           │         │
      │     A     │    B    │
      │           │         │
      ├───────────┤─────────┤
      │     C     │    D    │
      │           │         │
      └─────────────────────┘
```

Cada divisão é perpendicular a um eixo, alternando entre dimensões.

## 📊 Análise de Complexidade

| Operação | Caso Médio | Pior Caso |
|----------|------------|-----------|
| Construção | O(n log n) | O(n log n) |
| Inserção | O(log n) | O(n) |
| Busca exata | O(log n) | O(n) |
| Nearest Neighbor | O(log n) | O(n) |
| Range Search | O(√n + k) | O(n) |

Onde k = número de pontos reportados

### Espaço

- **Espaço**: O(n)
- **Altura esperada**: O(log n)
- **Altura pior caso**: O(n) (sem balanceamento)

## 🔧 Implementação

### Estrutura de Dados

```c
#define K 2  // Número de dimensões

typedef struct KDNode {
    int point[K];  // Coordenadas do ponto
    struct KDNode *left;
    struct KDNode *right;
} KDNode;

typedef struct {
    KDNode *root;
    int size;
} KDTree;
```

### Construção

```c
int compare_dim;  // Variável global para comparação

int compare_points(const void *a, const void *b) {
    int *p1 = *(int**)a;
    int *p2 = *(int**)b;
    return p1[compare_dim] - p2[compare_dim];
}

KDNode* build_tree(int **points, int n, int depth) {
    if (n <= 0) return NULL;
    
    // Escolher dimensão de corte
    int dim = depth % K;
    
    // Ordenar por dimensão atual e pegar mediana
    compare_dim = dim;
    qsort(points, n, sizeof(int*), compare_points);
    
    int mid = n / 2;
    
    // Criar nó com mediana
    KDNode *node = malloc(sizeof(KDNode));
    memcpy(node->point, points[mid], K * sizeof(int));
    
    // Construir subárvores recursivamente
    node->left = build_tree(points, mid, depth + 1);
    node->right = build_tree(points + mid + 1, n - mid - 1, depth + 1);
    
    return node;
}
```

### Inserção

```c
KDNode* insert(KDNode *root, int point[], int depth) {
    if (root == NULL) {
        KDNode *node = malloc(sizeof(KDNode));
        memcpy(node->point, point, K * sizeof(int));
        node->left = node->right = NULL;
        return node;
    }
    
    int dim = depth % K;
    
    if (point[dim] < root->point[dim]) {
        root->left = insert(root->left, point, depth + 1);
    } else {
        root->right = insert(root->right, point, depth + 1);
    }
    
    return root;
}
```

### Busca Exata

```c
bool search(KDNode *root, int point[], int depth) {
    if (root == NULL) return false;
    
    // Verificar se ponto atual é o procurado
    bool match = true;
    for (int i = 0; i < K; i++) {
        if (root->point[i] != point[i]) {
            match = false;
            break;
        }
    }
    if (match) return true;
    
    int dim = depth % K;
    
    if (point[dim] < root->point[dim]) {
        return search(root->left, point, depth + 1);
    }
    return search(root->right, point, depth + 1);
}
```

### Nearest Neighbor Search

```c
typedef struct {
    KDNode *best;
    double best_dist;
} NNResult;

double distance(int p1[], int p2[]) {
    double dist = 0;
    for (int i = 0; i < K; i++) {
        double d = p1[i] - p2[i];
        dist += d * d;
    }
    return sqrt(dist);
}

void nearest_neighbor(KDNode *root, int target[], int depth, NNResult *result) {
    if (root == NULL) return;
    
    double d = distance(root->point, target);
    
    if (d < result->best_dist) {
        result->best_dist = d;
        result->best = root;
    }
    
    int dim = depth % K;
    double diff = target[dim] - root->point[dim];
    
    // Visitar lado mais provável primeiro
    KDNode *first = diff < 0 ? root->left : root->right;
    KDNode *second = diff < 0 ? root->right : root->left;
    
    nearest_neighbor(first, target, depth + 1, result);
    
    // Verificar se precisa visitar outro lado
    if (fabs(diff) < result->best_dist) {
        nearest_neighbor(second, target, depth + 1, result);
    }
}

KDNode* find_nearest(KDTree *tree, int target[]) {
    NNResult result = {NULL, INFINITY};
    nearest_neighbor(tree->root, target, 0, &result);
    return result.best;
}
```

### Range Search

```c
void range_search(KDNode *root, int min[], int max[], int depth,
                  int **results, int *count) {
    if (root == NULL) return;
    
    // Verificar se ponto está no range
    bool in_range = true;
    for (int i = 0; i < K; i++) {
        if (root->point[i] < min[i] || root->point[i] > max[i]) {
            in_range = false;
            break;
        }
    }
    
    if (in_range) {
        results[*count] = root->point;
        (*count)++;
    }
    
    int dim = depth % K;
    
    // Visitar subárvores se podem conter pontos no range
    if (min[dim] <= root->point[dim]) {
        range_search(root->left, min, max, depth + 1, results, count);
    }
    if (max[dim] >= root->point[dim]) {
        range_search(root->right, min, max, depth + 1, results, count);
    }
}
```

## 📐 Variantes

### 1. Ball Tree

Usa hiperesferas ao invés de hiperplanos:
- Melhor para alta dimensionalidade
- Métricas de distância arbitrárias

### 2. R-Tree

Para retângulos mínimos delimitadores:
- Usado em bancos de dados espaciais (PostGIS)
- Melhor para objetos não-pontiformes

### 3. VP-Tree (Vantage-Point Tree)

Particionamento baseado em distância:
- Bom para espaços métricos
- Não requer coordenadas

### 4. Cover Tree

Para k-NN aproximado em alta dimensão:
- Complexidade O(c^k log n)
- c = constante de expansão

## 🎯 Aplicações Práticas

### 1. Computação Gráfica

- **Ray Tracing**: Aceleração de interseção ray-object
- **Collision Detection**: Broad phase detection

### 2. Machine Learning

- **K-Nearest Neighbors (KNN)**: Classificação
- **Clustering**: K-means acelerado

### 3. Sistemas de Informação Geográfica (GIS)

- Busca de pontos em região
- Nearest neighbor queries

### 4. Processamento de Nuvem de Pontos

- **LiDAR**: Processamento de scans 3D
- **Reconstrução 3D**: Matching de pontos

### 5. Computação Científica

- **N-body Simulation**: Barnes-Hut algorithm
- **Interpolação Espacial**: Kriging

## ⚠️ Limitações

### Curse of Dimensionality

Para k alto (k > 20):
- Número de células cresce exponencialmente
- Busca degenera para O(n)
- Considerar alternativas: LSH, Random Projections

### Desbalanceamento

Inserções podem desbalancear a árvore:
- Soluções: Reconstrução periódica, Relaxed K-D Trees

## 🔄 Comparação

| Estrutura | Build | NN Query | Range Query | Dimensões |
|-----------|-------|----------|-------------|-----------|
| K-D Tree | O(n log n) | O(log n)* | O(√n + k) | Baixas |
| Ball Tree | O(n log n) | O(log n) | - | Médias |
| R-Tree | O(n log n) | O(log n) | O(log n + k) | Baixas |
| Brute Force | O(1) | O(n) | O(n) | Qualquer |

*Para k pequeno

## 📖 Referências Bibliográficas

1. **Bentley, J. L.** (1975). Multidimensional Binary Search Trees Used for Associative Searching. *Communications of the ACM*, 18(9), 509-517.

2. **Friedman, J. H., Bentley, J. L., & Finkel, R. A.** (1977). An Algorithm for Finding Best Matches in Logarithmic Expected Time. *ACM TOMS*, 3(3), 209-226.

3. **de Berg, M., et al.** (2008). *Computational Geometry: Algorithms and Applications* (3rd ed.). Springer. Capítulo 5.

4. **Samet, H.** (2006). *Foundations of Multidimensional and Metric Data Structures*. Morgan Kaufmann.

5. **Muja, M., & Lowe, D. G.** (2014). Scalable Nearest Neighbor Algorithms for High Dimensional Data. *IEEE TPAMI*, 36(11), 2227-2240.

## 🔗 Navegação

← **[18-disjoint-set-union](../18-disjoint-set-union/)**: Disjoint Set Union

→ **[20-b-tree](../20-b-tree/)**: B-Tree

---

*Este material faz parte do curso de Estrutura de Dados em C.*
