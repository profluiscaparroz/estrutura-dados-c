# Splay Tree

## 📚 Definição Formal

Uma **Splay Tree** é uma árvore binária de busca auto-ajustante que move nós acessados para a raiz através de uma operação chamada "splaying". Diferente de outras árvores balanceadas, não mantém informação de balanceamento nos nós, mas garante tempo amortizado O(log n) para todas as operações.

**Definição Formal**: Uma Splay Tree é uma BST com a propriedade de que cada operação de busca, inserção ou deleção é seguida por uma operação de splay que move o nó acessado para a raiz.

## 🎓 Fundamentação Teórica

### Origem Histórica

- **Sleator & Tarjan (1985)**: Artigo "Self-Adjusting Binary Search Trees" em *JACM*
- **Motivação**: Estrutura simples com boa performance amortizada
- **Insight**: Localidade temporal - elementos acessados recentemente são mais prováveis de serem acessados novamente

### Propriedade de Auto-Ajuste

A operação de splay usa **rotações** para mover um nó até a raiz, considerando três casos:
1. **Zig**: Pai é a raiz
2. **Zig-Zig**: Nó e pai são ambos filhos esquerdos (ou direitos)
3. **Zig-Zag**: Nó e pai são filhos em lados opostos

### Teorema do Acesso (Access Lemma)

**Teorema (Sleator-Tarjan)**: O custo amortizado de fazer splay em um nó x é no máximo:

```
3(r(raiz) - r(x)) + 1
```

Onde r(x) = log(tamanho da subárvore de x).

**Corolário**: O tempo amortizado por operação é O(log n).

## 📊 Análise de Complexidade

| Operação | Amortizado | Pior Caso |
|----------|------------|-----------|
| Busca | O(log n) | O(n) |
| Inserção | O(log n) | O(n) |
| Deleção | O(log n) | O(n) |
| Split | O(log n) | O(n) |
| Merge (Join) | O(log n) | O(n) |

### Propriedades Avançadas

**Teorema do Working Set**: Se um elemento foi acessado t operações atrás, o custo de acessá-lo novamente é O(log t + 1).

**Teorema da Entropia Estática**: Se elemento i é acessado com frequência pᵢ, o custo amortizado é O(Σ pᵢ log(1/pᵢ)) = O(entropia).

**Conjectura da Otimalidade Dinâmica**: Splay Trees são competitivos com qualquer BST online.

## 🔄 Operação de Splay

### Casos de Splay

```
Caso ZIG (pai é raiz):
        p              x
       / \            / \
      x   C    →     A   p
     / \                / \
    A   B              B   C

Caso ZIG-ZIG (mesmo lado):
          g              x
         / \            / \
        p   D          A   p
       / \      →         / \
      x   C              B   g
     / \                    / \
    A   B                  C   D

Caso ZIG-ZAG (lados opostos):
          g              x
         / \            / \
        p   D          p   g
       / \      →     / \ / \
      A   x          A  B C  D
         / \
        B   C
```

### Implementação do Splay

```c
typedef struct SplayNode {
    int key;
    struct SplayNode *left, *right, *parent;
} SplayNode;

SplayNode* rotate_left(SplayNode *x) {
    SplayNode *y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    return y;
}

SplayNode* rotate_right(SplayNode *x) {
    SplayNode *y = x->left;
    x->left = y->right;
    if (y->right) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
    return y;
}

void splay(SplayNode **root, SplayNode *x) {
    while (x->parent) {
        if (!x->parent->parent) {
            // Zig
            if (x == x->parent->left)
                rotate_right(x->parent);
            else
                rotate_left(x->parent);
        } else if (x == x->parent->left && 
                   x->parent == x->parent->parent->left) {
            // Zig-Zig esquerda
            rotate_right(x->parent->parent);
            rotate_right(x->parent);
        } else if (x == x->parent->right && 
                   x->parent == x->parent->parent->right) {
            // Zig-Zig direita
            rotate_left(x->parent->parent);
            rotate_left(x->parent);
        } else if (x == x->parent->right && 
                   x->parent == x->parent->parent->left) {
            // Zig-Zag esquerda-direita
            rotate_left(x->parent);
            rotate_right(x->parent);
        } else {
            // Zig-Zag direita-esquerda
            rotate_right(x->parent);
            rotate_left(x->parent);
        }
    }
    *root = x;
}
```

### Operações com Splay

```c
// Busca
SplayNode* splay_find(SplayNode **root, int key) {
    SplayNode *curr = *root;
    SplayNode *last = NULL;
    
    while (curr) {
        last = curr;
        if (key < curr->key)
            curr = curr->left;
        else if (key > curr->key)
            curr = curr->right;
        else {
            splay(root, curr);
            return curr;
        }
    }
    
    if (last) splay(root, last);  // Splay no último nó visitado
    return NULL;
}

// Inserção
void splay_insert(SplayNode **root, int key) {
    if (*root == NULL) {
        *root = create_node(key);
        return;
    }
    
    // Buscar posição
    SplayNode *curr = *root;
    SplayNode *parent = NULL;
    
    while (curr) {
        parent = curr;
        if (key < curr->key)
            curr = curr->left;
        else if (key > curr->key)
            curr = curr->right;
        else {
            splay(root, curr);  // Chave existe
            return;
        }
    }
    
    // Inserir
    SplayNode *node = create_node(key);
    node->parent = parent;
    if (key < parent->key)
        parent->left = node;
    else
        parent->right = node;
    
    splay(root, node);
}
```

## 📐 Variantes

### 1. Top-Down Splay

Realiza splay durante a descida na árvore:
- Mais eficiente (uma passagem)
- Implementação mais complexa
- Preferida em produção

### 2. Semi-Splay

Splay parcial - para quando altura é fator menos crítico:
- Move nó apenas metade do caminho
- Ainda O(log n) amortizado
- Menos reestruturação

### 3. Link-Cut Trees

Splay Trees para floresta dinâmica:
- Operações de link e cut
- Usadas em algoritmos de fluxo máximo
- Base para algumas estruturas de dados de grafos

## 🎯 Aplicações Práticas

### 1. Caches

**Propriedade de Working Set**:
- Elementos recém-acessados ficam na raiz
- Acesso a elementos "quentes" é muito rápido
- Natural fit para padrões de localidade

### 2. Garbage Collectors

**Listas de livre**:
- Elementos alocados/liberados recentemente são mais comuns
- Splay tree como alternativa a listas ligadas

### 3. Compressão de Dados

**Move-to-Front Transform**:
- Splay tree como implementação eficiente
- Base para algoritmos como bzip2

### 4. Undo/Redo em Editores

**Operações recentes**:
- Acessadas frequentemente
- Splay tree para histórico de operações

## 🔄 Comparação com Outras Árvores

| Propriedade | Splay Tree | AVL | Red-Black | Treap |
|-------------|------------|-----|-----------|-------|
| Balanceamento | Amortizado | Estrito | Relaxado | Probabilístico |
| Pior caso único | O(n) | O(log n) | O(log n) | O(n) |
| Espaço extra | 0 | 1 int/nó | 1 bit/nó | 1 int/nó |
| Implementação | Simples | Média | Complexa | Simples |
| Localidade temporal | Excelente | Nenhuma | Nenhuma | Nenhuma |

### Quando Usar Splay Tree

✅ Usar quando:
- Padrão de acesso tem localidade temporal
- Simplicidade é valorizada
- Performance amortizada é aceitável
- Working set é pequeno

❌ Evitar quando:
- Garantias de pior caso são necessárias
- Acessos são uniformemente distribuídos
- Tempo real / tempo de resposta garantido

## 📖 Referências Bibliográficas

1. **Sleator, D. D., & Tarjan, R. E.** (1985). Self-Adjusting Binary Search Trees. *Journal of the ACM*, 32(3), 652-686.

2. **Tarjan, R. E.** (1985). Amortized Computational Complexity. *SIAM Journal on Algebraic Discrete Methods*, 6(2), 306-318.

3. **Cole, R.** (2000). On the Dynamic Finger Conjecture for Splay Trees. Part II: The Proof. *SIAM Journal on Computing*, 30(1), 44-85.

4. **Sleator, D. D., & Tarjan, R. E.** (1983). A Data Structure for Dynamic Trees. *JCSS*, 26(3), 362-391.

5. **Demaine, E. D., Harmon, D., Iacono, J., & Pǎtraşcu, M.** (2007). Dynamic Optimality—Almost. *SIAM Journal on Computing*, 37(1), 240-251.

## 🔗 Navegação

← **[12-treap](../12-treap/)**: Treap

→ **[14-avl-tree](../14-avl-tree/)**: AVL Tree

---

*Este material faz parte do curso de Estrutura de Dados em C.*
