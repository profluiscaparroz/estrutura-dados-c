# Árvore Binária de Busca Avançada

## 📚 Definição Formal

Uma **Árvore Binária de Busca** (BST - Binary Search Tree) é uma estrutura de dados hierárquica onde cada nó possui no máximo dois filhos, satisfazendo a **propriedade de ordenação**:

Para todo nó `x`:
- Todos os nós na subárvore esquerda têm chaves **menores** que `x.key`
- Todos os nós na subárvore direita têm chaves **maiores** que `x.key`

## 🎓 Fundamentação Teórica

### Propriedade Fundamental

A propriedade BST permite busca eficiente através de decisões binárias:

```
BUSCA(x, k)
    if x = NIL ou k = x.key
        return x
    if k < x.key
        return BUSCA(x.left, k)
    else
        return BUSCA(x.right, k)
```

### Análise de Altura

**Teorema**: Uma BST com n nós tem altura h onde:
- **Mínimo**: h = ⌊log₂(n)⌋ (árvore completa)
- **Máximo**: h = n - 1 (lista degenerada)
- **Esperado** (inserção aleatória): h = O(log n)

**Prova (altura esperada)**: Hibbard (1962) e Knuth (1973) mostraram que para n inserções em ordem aleatória, a altura esperada é aproximadamente 2 ln n ≈ 1.39 log₂ n.

## 📊 Operações e Complexidade

| Operação | Melhor Caso | Caso Médio | Pior Caso |
|----------|-------------|------------|-----------|
| Busca | O(1) | O(log n) | O(n) |
| Inserção | O(1) | O(log n) | O(n) |
| Remoção | O(1) | O(log n) | O(n) |
| Mínimo/Máximo | O(1) | O(log n) | O(n) |
| Sucessor/Predecessor | O(1) | O(log n) | O(n) |
| Travessia | O(n) | O(n) | O(n) |

## 🔄 Travessias

### In-order (Simétrica)

Visita nós em ordem crescente de chaves:

```
IN-ORDER(x)
    if x ≠ NIL
        IN-ORDER(x.left)
        VISIT(x)
        IN-ORDER(x.right)
```

**Aplicação**: Ordenação de elementos

### Pre-order (Pré-fixa)

```
PRE-ORDER(x)
    if x ≠ NIL
        VISIT(x)
        PRE-ORDER(x.left)
        PRE-ORDER(x.right)
```

**Aplicação**: Serialização/cópia de árvore

### Post-order (Pós-fixa)

```
POST-ORDER(x)
    if x ≠ NIL
        POST-ORDER(x.left)
        POST-ORDER(x.right)
        VISIT(x)
```

**Aplicação**: Liberação de memória, cálculo de expressões

### Morris Traversal

Travessia in-order sem recursão ou pilha:

```
MORRIS-INORDER(root)
    current = root
    while current ≠ NIL
        if current.left = NIL
            VISIT(current)
            current = current.right
        else
            predecessor = current.left
            while predecessor.right ≠ NIL and predecessor.right ≠ current
                predecessor = predecessor.right
            if predecessor.right = NIL
                predecessor.right = current
                current = current.left
            else
                predecessor.right = NIL
                VISIT(current)
                current = current.right
```

**Complexidade**: O(n) tempo, O(1) espaço

## 🛠️ Operações Avançadas

### Remoção de Nó

Três casos:
1. **Folha**: Simplesmente remove
2. **Um filho**: Substitui pelo filho
3. **Dois filhos**: Substitui pelo sucessor in-order (ou predecessor)

```
DELETE(T, z)
    if z.left = NIL
        TRANSPLANT(T, z, z.right)
    else if z.right = NIL
        TRANSPLANT(T, z, z.left)
    else
        y = MINIMUM(z.right)  // Sucessor in-order
        if y.parent ≠ z
            TRANSPLANT(T, y, y.right)
            y.right = z.right
            y.right.parent = y
        TRANSPLANT(T, z, y)
        y.left = z.left
        y.left.parent = y
```

### Select (k-ésimo menor)

Com augmentation de tamanho:

```
SELECT(x, k)
    r = SIZE(x.left) + 1
    if k = r
        return x
    if k < r
        return SELECT(x.left, k)
    else
        return SELECT(x.right, k - r)
```

**Complexidade**: O(h)

### Rank (posição de chave)

```
RANK(T, k)
    rank = 0
    x = T.root
    while x ≠ NIL
        if k < x.key
            x = x.left
        else
            rank = rank + SIZE(x.left) + 1
            if k = x.key
                return rank
            x = x.right
    return NIL  // Não encontrado
```

## 🔍 Técnicas de Augmentation

### Order Statistics Tree

Cada nó armazena o tamanho da sua subárvore:

```c
typedef struct Node {
    int key;
    int size;  // Tamanho da subárvore
    struct Node *left, *right, *parent;
} Node;
```

**Manutenção**: Atualizar size em inserções/remoções

### Interval Tree

Armazena intervalos e permite consultas de sobreposição:

```c
typedef struct IntervalNode {
    int low, high;    // Intervalo
    int max;          // Máximo high na subárvore
    struct IntervalNode *left, *right;
} IntervalNode;
```

**Aplicação**: Detecção de conflitos de agenda, geometria computacional

## ⚠️ Problema de Degeneração

### Causa

Inserções em ordem (crescente ou decrescente) criam lista encadeada:

```
Inserir: 1, 2, 3, 4, 5

    1
     \
      2
       \
        3
         \
          4
           \
            5

Altura = n - 1 = O(n)
```

### Soluções

1. **Árvores Auto-Balanceadas**:
   - AVL Tree: Fator de balanceamento ≤ 1
   - Red-Black Tree: Altura ≤ 2 log₂(n+1)
   - Splay Tree: Amortizado O(log n)
   - Treap: Aleatorizado

2. **Randomização**:
   - Shuffle antes de inserir
   - Treap usa prioridades aleatórias

3. **Rebalanceamento**:
   - DSW (Day-Stout-Warren) Algorithm
   - Transforma BST em lista e depois em árvore balanceada
   - O(n) tempo, O(1) espaço

## 📐 Teoremas Importantes

### Teorema 1: Número de BSTs Distintas

O número de BSTs estruturalmente distintas com n nós é dado pelos **Números de Catalan**:

```
Cₙ = (2n)! / ((n+1)! × n!) = C(2n,n) / (n+1)
```

Aproximação: Cₙ ≈ 4ⁿ / (n^(3/2) × √π)

### Teorema 2: Altura Esperada

Para n inserções em ordem uniformemente aleatória:

```
E[altura] ≈ 4.311 × ln(n) ≈ 2.988 × log₂(n)
```

### Teorema 3: IPL (Internal Path Length)

Comprimento médio de caminho interno:

```
E[IPL] = 2n × Hₙ - 2n ≈ 1.39n × log₂(n)
```

Onde Hₙ é o n-ésimo número harmônico.

## 🔄 Comparação com Outras Estruturas

| Estrutura | Busca | Insert | Delete | Ordenado | Espaço |
|-----------|-------|--------|--------|----------|--------|
| BST | O(h) | O(h) | O(h) | Sim | O(n) |
| Hash Table | O(1)* | O(1)* | O(1)* | Não | O(n) |
| Skip List | O(log n)* | O(log n)* | O(log n)* | Sim | O(n log n)* |
| Array Ordenado | O(log n) | O(n) | O(n) | Sim | O(n) |

*Caso médio/esperado

## 📖 Referências Bibliográficas

1. **Cormen, T. H., et al.** (2009). *Introduction to Algorithms* (3rd ed.). MIT Press. Capítulos 12-13.

2. **Knuth, D. E.** (1998). *The Art of Computer Programming, Vol. 3: Sorting and Searching* (2nd ed.). Addison-Wesley. Seção 6.2.

3. **Sedgewick, R., & Wayne, K.** (2011). *Algorithms* (4th ed.). Addison-Wesley. Capítulo 3.

4. **Hibbard, T. N.** (1962). Some Combinatorial Properties of Certain Trees With Applications to Searching and Sorting. *JACM*, 9(1), 13-28.

5. **Devroye, L.** (1986). A Note on the Height of Binary Search Trees. *JACM*, 33(3), 489-498.

## 🔗 Navegação

← **[04-hash-table-avancada](../04-hash-table-avancada/)**: Tabelas Hash Avançadas

→ **[06-trie](../06-trie/)**: Trie (Árvore de Prefixos)

---

*Este material faz parte do curso de Estrutura de Dados em C.*
