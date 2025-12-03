# AVL Tree

## 📚 Definição Formal

Uma **AVL Tree** é uma árvore binária de busca auto-balanceada onde a diferença de altura (fator de balanceamento) entre as subárvores esquerda e direita de qualquer nó é no máximo 1.

**Definição Formal**: Uma AVL Tree é uma BST onde para todo nó v:
```
|altura(v.esquerda) - altura(v.direita)| ≤ 1
```

O **fator de balanceamento** é definido como:
```
bf(v) = altura(v.esquerda) - altura(v.direita)
```

Para uma AVL Tree válida: bf(v) ∈ {-1, 0, +1}

## 🎓 Fundamentação Teórica

### Origem Histórica

- **Adelson-Velsky e Landis (1962)**: Artigo "An algorithm for the organization of information" (em russo)
- **Primeira estrutura de dados auto-balanceada** inventada
- **Nome**: Iniciais dos inventores (A-V-L)

### Altura Máxima

**Teorema**: Uma AVL Tree com n nós tem altura h satisfazendo:

```
log₂(n + 1) ≤ h < 1.4405 × log₂(n + 2) - 0.328
```

**Prova** (via Números de Fibonacci):
- N(h) = número mínimo de nós em AVL de altura h
- N(0) = 1, N(1) = 2
- N(h) = N(h-1) + N(h-2) + 1 = Fₕ₊₂ - 1
- Portanto: h < 1.44 log₂(n)

### Comparação de Alturas

| Estrutura | Altura Máxima | Altura para n=10⁶ |
|-----------|---------------|-------------------|
| BST (pior) | n - 1 | 999,999 |
| AVL | 1.44 log n | ~29 |
| Red-Black | 2 log n | ~40 |
| BST (random) | 2 ln n | ~28 |

## 📊 Análise de Complexidade

| Operação | Complexidade |
|----------|--------------|
| Busca | O(log n) |
| Inserção | O(log n) |
| Deleção | O(log n) |
| Mínimo/Máximo | O(log n) |
| Sucessor/Predecessor | O(log n) |

**Número de rotações**:
- Inserção: No máximo 2 rotações (O(1))
- Deleção: Até O(log n) rotações

## 🔄 Rotações

### Rotação Simples à Direita (Right Rotation)

Corrige desbalanceamento Left-Left (LL):

```
        y                x
       / \              / \
      x   T3    →      T1   y
     / \                   / \
    T1  T2                T2  T3
```

```c
AVLNode* rotate_right(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;
    
    x->right = y;
    y->left = T2;
    
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));
    
    return x;
}
```

### Rotação Simples à Esquerda (Left Rotation)

Corrige desbalanceamento Right-Right (RR):

```
      x                  y
     / \                / \
    T1   y      →      x   T3
        / \           / \
       T2  T3        T1  T2
```

### Rotação Dupla Left-Right (LR)

Corrige desbalanceamento Left-Right:

```
        z                  z                  y
       / \                / \                / \
      x   T4    →        y   T4    →        x   z
     / \                / \                / \ / \
    T1   y             x   T3             T1 T2 T3 T4
        / \           / \
       T2  T3        T1  T2
```

### Rotação Dupla Right-Left (RL)

Corrige desbalanceamento Right-Left:

```
      z                  z                      y
     / \                / \                    / \
    T1   x    →        T1   y      →          z   x
        / \                / \               / \ / \
       y   T4             T2   x            T1 T2 T3 T4
      / \                     / \
     T2  T3                  T3  T4
```

## 🔧 Implementação

### Estrutura de Dados

```c
typedef struct AVLNode {
    int key;
    int height;
    struct AVLNode *left;
    struct AVLNode *right;
} AVLNode;
```

### Inserção

```c
AVLNode* avl_insert(AVLNode *node, int key) {
    // 1. Inserção BST padrão
    if (node == NULL) {
        return create_node(key);
    }
    
    if (key < node->key)
        node->left = avl_insert(node->left, key);
    else if (key > node->key)
        node->right = avl_insert(node->right, key);
    else
        return node;  // Duplicatas não permitidas
    
    // 2. Atualizar altura
    node->height = 1 + max(height(node->left), height(node->right));
    
    // 3. Calcular fator de balanceamento
    int balance = balance_factor(node);
    
    // 4. Rebalancear se necessário
    
    // Caso Left-Left
    if (balance > 1 && key < node->left->key)
        return rotate_right(node);
    
    // Caso Right-Right
    if (balance < -1 && key > node->right->key)
        return rotate_left(node);
    
    // Caso Left-Right
    if (balance > 1 && key > node->left->key) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    
    // Caso Right-Left
    if (balance < -1 && key < node->right->key) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    
    return node;
}
```

### Deleção

```c
AVLNode* avl_delete(AVLNode *node, int key) {
    // 1. Deleção BST padrão
    if (node == NULL) return NULL;
    
    if (key < node->key)
        node->left = avl_delete(node->left, key);
    else if (key > node->key)
        node->right = avl_delete(node->right, key);
    else {
        // Nó com 0 ou 1 filho
        if (node->left == NULL || node->right == NULL) {
            AVLNode *temp = node->left ? node->left : node->right;
            if (temp == NULL) {
                temp = node;
                node = NULL;
            } else {
                *node = *temp;
            }
            free(temp);
        } else {
            // Nó com 2 filhos: substituir pelo sucessor in-order
            AVLNode *temp = find_min(node->right);
            node->key = temp->key;
            node->right = avl_delete(node->right, temp->key);
        }
    }
    
    if (node == NULL) return NULL;
    
    // 2. Atualizar altura
    node->height = 1 + max(height(node->left), height(node->right));
    
    // 3. Rebalancear
    int balance = balance_factor(node);
    
    // Caso Left-Left
    if (balance > 1 && balance_factor(node->left) >= 0)
        return rotate_right(node);
    
    // Caso Left-Right
    if (balance > 1 && balance_factor(node->left) < 0) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    
    // Caso Right-Right
    if (balance < -1 && balance_factor(node->right) <= 0)
        return rotate_left(node);
    
    // Caso Right-Left
    if (balance < -1 && balance_factor(node->right) > 0) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    
    return node;
}
```

## 📐 Propriedades e Teoremas

### Número de Nós

**Número mínimo de nós** em AVL de altura h (relacionado a Fibonacci):

```
N(h) = Fₕ₊₃ - 1

N(0) = 1
N(1) = 2
N(2) = 4
N(3) = 7
N(4) = 12
...
```

### Número de Rotações

**Teorema**: A inserção em AVL requer no máximo 2 rotações.

**Teorema**: A deleção em AVL pode requerer O(log n) rotações.

### Complexidade de Espaço

- **Por nó**: chave + altura + 2 ponteiros
- **Total**: O(n)

## 🎯 Aplicações Práticas

### 1. Bancos de Dados em Memória

- Índices em memória
- Quando operações de leitura dominam
- Garantia de O(log n)

### 2. Dicionários Ordenados

- Implementação de maps/sets ordenados
- Quando range queries são necessárias

### 3. Sistemas de Arquivos

- Gerenciamento de diretórios
- Alocação de blocos

### 4. Jogos

- Detecção de colisão
- Estruturas espaciais 1D

## 🔄 Comparação com Red-Black Tree

| Aspecto | AVL Tree | Red-Black Tree |
|---------|----------|----------------|
| Altura máxima | 1.44 log n | 2 log n |
| Rotações na inserção | ≤ 2 | ≤ 2 |
| Rotações na deleção | O(log n) | ≤ 3 |
| Busca | Mais rápida | Ligeiramente mais lenta |
| Inserção/Deleção | Ligeiramente mais lenta | Mais rápida |
| Memória extra | altura (int) | cor (1 bit) |
| Uso típico | Muitas buscas | Muitas modificações |

### Quando Usar Cada Uma

**AVL Tree**:
- Mais buscas que inserções/deleções
- Altura mínima é importante
- Dados relativamente estáticos

**Red-Black Tree**:
- Muitas inserções/deleções
- Usado em bibliotecas padrão (C++ STL, Java TreeMap)
- Menor overhead de rebalanceamento

## 📖 Referências Bibliográficas

1. **Adelson-Velsky, G. M., & Landis, E. M.** (1962). An algorithm for the organization of information. *Soviet Mathematics Doklady*, 3, 1259-1263.

2. **Knuth, D. E.** (1998). *The Art of Computer Programming, Vol. 3: Sorting and Searching* (2nd ed.). Addison-Wesley. Seção 6.2.3.

3. **Cormen, T. H., et al.** (2009). *Introduction to Algorithms* (3rd ed.). MIT Press. Problema 13-3.

4. **Sedgewick, R., & Wayne, K.** (2011). *Algorithms* (4th ed.). Addison-Wesley.

5. **Pfaff, B.** (2004). Performance Analysis of BSTs in System Software. *SIGMETRICS*, 410-411.

## 🔗 Navegação

← **[13-splay-tree](../13-splay-tree/)**: Splay Tree

→ **[15-skip-list](../15-skip-list/)**: Skip List

---

*Este material faz parte do curso de Estrutura de Dados em C.*
