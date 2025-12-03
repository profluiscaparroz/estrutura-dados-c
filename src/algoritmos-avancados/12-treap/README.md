# Treap

## 📚 Definição Formal

Um **Treap** (Tree + Heap) é uma estrutura de dados que combina as propriedades de uma Árvore Binária de Busca (BST) e um Heap. Cada nó contém:
- Uma **chave** que satisfaz a propriedade BST (ordem in-order)
- Uma **prioridade** aleatória que satisfaz a propriedade heap (min-heap ou max-heap)

**Definição Formal**: Um Treap é uma árvore binária onde:
1. As chaves satisfazem a propriedade BST: `left.key < node.key < right.key`
2. As prioridades satisfazem a propriedade heap: `node.priority ≤ parent.priority` (min-heap)

## 🎓 Fundamentação Teórica

### Origem Histórica

- **Seidel & Aragon (1996)**: Artigo "Randomized Search Trees" no *Algorithmica*
- **Motivação**: Árvore balanceada com análise probabilística simples
- **Nome**: Combinação de "tree" e "heap"

### Propriedade Fundamental

**Teorema**: Se as prioridades são valores aleatórios independentes uniformes, o Treap resultante tem a mesma distribuição que uma BST construída por inserções em ordem aleatória.

**Corolário**: A altura esperada é O(log n).

### Unicidade

**Teorema**: Para qualquer conjunto de pares (chave, prioridade) com chaves e prioridades distintas, existe exatamente um Treap.

## 📊 Análise de Complexidade

| Operação | Esperado | Pior Caso |
|----------|----------|-----------|
| Busca | O(log n) | O(n) |
| Inserção | O(log n) | O(n) |
| Deleção | O(log n) | O(n) |
| Split | O(log n) | O(n) |
| Merge | O(log n) | O(n) |

**Nota**: O pior caso O(n) tem probabilidade exponencialmente pequena.

### Análise Detalhada

**Altura esperada**: 2 ln n ≈ 1.39 log₂ n

**Número esperado de rotações por inserção/deleção**: ≤ 2

## 🔧 Estrutura de Dados

```c
typedef struct TreapNode {
    int key;
    int priority;  // Valor aleatório
    struct TreapNode *left;
    struct TreapNode *right;
} TreapNode;

typedef struct {
    TreapNode *root;
    size_t size;
} Treap;
```

## 🔄 Operações Fundamentais

### Rotações

As rotações mantêm a propriedade BST enquanto restauram a propriedade heap:

```c
// Rotação à direita
TreapNode* rotate_right(TreapNode *y) {
    TreapNode *x = y->left;
    TreapNode *T2 = x->right;
    
    x->right = y;
    y->left = T2;
    
    return x;  // Nova raiz
}

// Rotação à esquerda
TreapNode* rotate_left(TreapNode *x) {
    TreapNode *y = x->right;
    TreapNode *T2 = y->left;
    
    y->left = x;
    x->right = T2;
    
    return y;  // Nova raiz
}
```

### Inserção

```c
TreapNode* treap_insert(TreapNode *root, int key) {
    if (root == NULL) {
        TreapNode *node = malloc(sizeof(TreapNode));
        node->key = key;
        node->priority = rand();  // Prioridade aleatória
        node->left = node->right = NULL;
        return node;
    }
    
    if (key < root->key) {
        root->left = treap_insert(root->left, key);
        
        // Restaurar propriedade heap
        if (root->left->priority < root->priority) {
            root = rotate_right(root);
        }
    } else if (key > root->key) {
        root->right = treap_insert(root->right, key);
        
        if (root->right->priority < root->priority) {
            root = rotate_left(root);
        }
    }
    // key == root->key: chave duplicada (ignorar ou atualizar)
    
    return root;
}
```

### Deleção

```c
TreapNode* treap_delete(TreapNode *root, int key) {
    if (root == NULL) return NULL;
    
    if (key < root->key) {
        root->left = treap_delete(root->left, key);
    } else if (key > root->key) {
        root->right = treap_delete(root->right, key);
    } else {
        // Nó encontrado - rotacionar até ser folha
        if (root->left == NULL) {
            TreapNode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreapNode *temp = root->left;
            free(root);
            return temp;
        }
        
        // Rotacionar na direção do filho com menor prioridade
        if (root->left->priority < root->right->priority) {
            root = rotate_right(root);
            root->right = treap_delete(root->right, key);
        } else {
            root = rotate_left(root);
            root->left = treap_delete(root->left, key);
        }
    }
    
    return root;
}
```

### Split e Merge

**Split**: Divide treap em dois baseado em uma chave

```c
void treap_split(TreapNode *root, int key, 
                 TreapNode **left, TreapNode **right) {
    if (root == NULL) {
        *left = *right = NULL;
        return;
    }
    
    if (root->key <= key) {
        *left = root;
        treap_split(root->right, key, &((*left)->right), right);
    } else {
        *right = root;
        treap_split(root->left, key, left, &((*right)->left));
    }
}
```

**Merge**: Combina dois treaps (todas chaves de L < todas chaves de R)

```c
TreapNode* treap_merge(TreapNode *left, TreapNode *right) {
    if (left == NULL) return right;
    if (right == NULL) return left;
    
    if (left->priority < right->priority) {
        left->right = treap_merge(left->right, right);
        return left;
    } else {
        right->left = treap_merge(left, right->left);
        return right;
    }
}
```

## 📐 Variantes

### 1. Implicit Treap (Treap com Chave Implícita)

Usa posição no array como chave implícita. Permite:
- Inserção/deleção em posição O(log n)
- Operações em intervalos O(log n)

```c
typedef struct ImplicitTreapNode {
    int value;           // Valor armazenado
    int priority;
    int subtree_size;    // Tamanho da subárvore
    struct ImplicitTreapNode *left, *right;
} ImplicitTreapNode;
```

**Aplicações**:
- Implementar rope (string com edição eficiente)
- Operações em arrays com inserção/deleção

### 2. Treap with Lazy Propagation

Para operações em range:

```c
typedef struct LazyTreapNode {
    int key, priority;
    int value;
    int lazy;           // Operação pendente
    int subtree_min;    // Agregação (mínimo da subárvore)
    struct LazyTreapNode *left, *right;
} LazyTreapNode;
```

### 3. Persistent Treap

Versão funcional (imutável) para versionamento:
- Cada operação cria nova versão
- Versões anteriores permanecem acessíveis
- Espaço: O(log n) por operação

## 🎯 Aplicações Práticas

### 1. Estrutura de Dados para Competições

**Vantagens em programação competitiva**:
- Implementação mais simples que outras árvores balanceadas
- Suporta split/merge naturalmente
- Fácil de adaptar para operações em range

### 2. Implementação de Map/Set

Alternativa a Red-Black Tree:
- Mesma complexidade esperada
- Código mais simples
- Análise probabilística mais direta

### 3. Operações em Intervalos

Com treap implícito:
- Reverter substring
- Mover bloco de texto
- Queries de soma/mínimo/máximo

## 🔄 Comparação com Outras Árvores

| Estrutura | Altura | Inserção | Deleção | Implementação |
|-----------|--------|----------|---------|---------------|
| Treap | O(log n)* | O(log n)* | O(log n)* | Simples |
| AVL | 1.44 log n | O(log n) | O(log n) | Média |
| Red-Black | 2 log n | O(log n) | O(log n) | Complexa |
| Splay | O(log n)** | O(log n)** | O(log n)** | Simples |

*Esperado (probabilístico)
**Amortizado

### Quando Usar Treap

✅ Usar quando:
- Análise probabilística é aceitável
- Split/merge são necessários
- Simplicidade de código é valorizada
- Competições de programação

❌ Evitar quando:
- Garantias determinísticas são necessárias
- Randomização é proibida
- Reprodutibilidade é crítica (use seed fixo)

## 📖 Referências Bibliográficas

1. **Seidel, R., & Aragon, C. R.** (1996). Randomized Search Trees. *Algorithmica*, 16(4-5), 464-497.

2. **Aragon, C. R., & Seidel, R.** (1989). Randomized Search Trees. *FOCS*, 540-545.

3. **Martínez, C., & Roura, S.** (1998). Randomized Binary Search Trees. *JACM*, 45(2), 288-323.

4. **Pugh, W.** (1990). Skip Lists: A Probabilistic Alternative to Balanced Trees. *Communications of the ACM*, 33(6), 668-676.

5. **Motwani, R., & Raghavan, P.** (1995). *Randomized Algorithms*. Cambridge University Press. Capítulo 8.

## 🔗 Navegação

← **[11-hyperloglog](../11-hyperloglog/)**: HyperLogLog

→ **[13-splay-tree](../13-splay-tree/)**: Splay Tree

---

*Este material faz parte do curso de Estrutura de Dados em C.*
