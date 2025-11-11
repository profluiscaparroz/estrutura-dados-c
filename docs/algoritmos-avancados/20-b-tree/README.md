# Aula de Ciência da Computação: B-Tree – História, Funcionamento e Aplicações

## Introdução

A **B-Tree** é uma estrutura de dados de árvore balanceada e auto-organizável, projetada especificamente para sistemas que leem e escrevem grandes blocos de dados, como bancos de dados e sistemas de arquivos. Foi inventada por Rudolf Bayer e Edward M. McCreight em 1970 na Boeing Research Labs e revolucionou o armazenamento e recuperação de dados em sistemas de disco.

---

## 1. História e Motivação

A B-Tree foi introduzida por Rudolf Bayer e Edward McCreight no artigo **"Organization and Maintenance of Large Ordered Indexes"**, publicado na Acta Informatica em 1972. Eles trabalhavam em sistemas de banco de dados e perceberam que estruturas tradicionais como BST e AVL eram ineficientes para armazenamento em disco.

Antes da B-Tree:

* **Árvores Binárias (BST, AVL)**: Cada nó armazena apenas uma chave, causando muitos acessos a disco (cada acesso = operação cara).
* **ISAM (Indexed Sequential Access Method)**: Índices estáticos que requeriam reorganização periódica.
* **Arquivos Sequenciais**: Inserções e buscas custavam O(n).

A B-Tree foi projetada considerando:
* **Minimizar acessos a disco**: Nós grandes com múltiplas chaves por nó
* **Balanceamento automático**: Mantém altura O(log n)
* **Operações eficientes**: Inserção, remoção e busca em O(log n) acessos a disco

Segundo Bayer e McCreight (1972), "uma B-tree de ordem m é especialmente útil quando os dados residem em armazenamento externo".

---

## 2. O que era feito antes da B-Tree?

Antes da B-Tree, sistemas de banco de dados usavam:

* **Índices Binários**: Árvores binárias armazenadas em disco
  - Problema: Cada nó = 1 acesso a disco
  - Para árvore com 1 milhão de chaves: ~20 acessos a disco
  
* **Arquivos Sequenciais Indexados**:
  - Índice principal + arquivo de dados
  - Reorganização completa necessária periodicamente
  
* **Hash Tables em Disco**:
  - Bons para busca exata, ruins para range queries
  - Problemas com colisões e crescimento dinâmico

A B-Tree trouxe balanceamento automático com nós grandes, reduzindo drasticamente acessos a disco.

---

## 3. Como funciona a B-Tree?

Uma B-Tree de ordem m (também chamada de grau mínimo t) possui propriedades:

### Propriedades

1. Cada nó contém no máximo 2t-1 chaves
2. Cada nó (exceto raiz) contém no mínimo t-1 chaves
3. Todos os nós folha estão no mesmo nível
4. Um nó com k chaves tem k+1 filhos
5. Chaves em cada nó são ordenadas

### Estrutura

```
Exemplo de B-Tree de ordem t=3 (máximo 5 chaves por nó):

                [10, 20, 30]
               /    |    |    \
        [5,8]  [12,15] [25,28] [35,40,50]
```

### Operações

**Busca**: Similar a BST, mas navega por múltiplas chaves em cada nó - O(log n)

**Inserção**: 
1. Busca posição correta (folha)
2. Insere chave
3. Se nó fica cheio, divide (split) em dois
4. Propaga split para cima se necessário

**Remoção**: Mais complexa, pode envolver fusão de nós ou redistribuição de chaves.

---

## 4. Vantagens da B-Tree

* **Otimizada para Disco**: Minimiza acessos a disco - crucial para performance.
* **Balanceamento Garantido**: Sempre balanceada, altura O(log n).
* **Alta Taxa de Ocupação**: Nós utilizam bem o espaço.
* **Suporta Range Queries**: Eficiente para consultas de intervalo.
* **Inserções e Remoções Dinâmicas**: Sem necessidade de reorganização global.

---

## 5. Desvantagens da B-Tree

* **Complexidade de Implementação**: Operações de split e merge são complexas.
* **Overhead de Espaço**: Nós podem ter espaço não utilizado.
* **Cache Performance**: Pode ter problemas de cache em comparação com estruturas contíguas.
* **Não Ideal para Memória**: Em memória RAM pura, outras estruturas podem ser mais rápidas.

---

## 6. Aplicações Práticas

* **Sistemas de Banco de Dados**: MySQL, PostgreSQL, Oracle usam B-Trees (ou B+ Trees) para índices.
* **Sistemas de Arquivos**: NTFS, ext4, HFS+ usam B-Trees.
* **Bancos de Dados NoSQL**: MongoDB usa B-Trees para índices.
* **SSDs e Armazenamento Flash**: Variações de B-Trees para otimizar escritas.
* **Sistemas de Arquivos Distribuídos**: GFS, HDFS usam estruturas baseadas em B-Trees.

---

## Onde a B-Tree é usada no dia a dia?

1. **Bancos de Dados Relacionais**: Todo índice em MySQL, PostgreSQL é uma B+ Tree.
2. **Sistemas de Arquivos**: Windows NTFS, macOS HFS+, Linux ext4.
3. **MongoDB**: Índices implementados com B-Trees.
4. **SQLite**: Usa B-Trees para tabelas e índices.
5. **Sistemas de Backup**: Para indexar grandes volumes de dados em fitas ou discos.

---

## Como podemos melhorar a B-Tree para uso prático?

### 1. **B+ Tree**
* Variante onde dados ficam apenas nas folhas
* Folhas são ligadas como linked list
* Melhora range queries e varreduras sequenciais
* Usada na maioria dos bancos de dados reais

### 2. **B* Tree**
* Mantém nós mais cheios (mínimo 2/3 ao invés de 1/2)
* Reduz número de splits
* Melhora utilização de espaço

### 3. **Bulk Loading**
* Construção eficiente de B-Trees a partir de dados ordenados
* Útil para carga inicial de dados

### 4. **Concurrent B-Trees**
* Técnicas de lock-free ou latch coupling
* Permite múltiplas threads acessando simultaneamente

### 5. **Flash-Optimized B-Trees**
* Adaptadas para características de SSDs
* Reduzem escritas para aumentar vida útil do dispositivo

---

# Implementação Simplificada da B-Tree em Python

```python
class BTreeNode:
    def __init__(self, leaf=False):
        self.keys = []
        self.children = []
        self.leaf = leaf
    
    def search(self, k):
        i = 0
        while i < len(self.keys) and k > self.keys[i]:
            i += 1
        
        if i < len(self.keys) and k == self.keys[i]:
            return True
        elif self.leaf:
            return False
        else:
            return self.children[i].search(k)

class BTree:
    def __init__(self, t):
        self.root = BTreeNode(leaf=True)
        self.t = t  # Grau mínimo
    
    def search(self, k):
        return self.root.search(k)
    
    def insert(self, k):
        root = self.root
        if len(root.keys) == (2 * self.t) - 1:
            new_root = BTreeNode()
            new_root.children.append(self.root)
            self.split_child(new_root, 0)
            self.root = new_root
            self.insert_non_full(new_root, k)
        else:
            self.insert_non_full(root, k)
    
    def insert_non_full(self, node, k):
        if node.leaf:
            node.keys.append(k)
            node.keys.sort()
        else:
            i = len(node.keys) - 1
            while i >= 0 and k < node.keys[i]:
                i -= 1
            i += 1
            if len(node.children[i].keys) == (2 * self.t) - 1:
                self.split_child(node, i)
                if k > node.keys[i]:
                    i += 1
            self.insert_non_full(node.children[i], k)
    
    def split_child(self, parent, i):
        t = self.t
        full_child = parent.children[i]
        new_child = BTreeNode(leaf=full_child.leaf)
        
        mid_key = full_child.keys[t - 1]
        new_child.keys = full_child.keys[t:]
        full_child.keys = full_child.keys[:t - 1]
        
        if not full_child.leaf:
            new_child.children = full_child.children[t:]
            full_child.children = full_child.children[:t]
        
        parent.keys.insert(i, mid_key)
        parent.children.insert(i + 1, new_child)

# Exemplo de uso
if __name__ == "__main__":
    btree = BTree(t=3)  # B-Tree de ordem 3
    
    keys = [10, 20, 5, 6, 12, 30, 7, 17]
    for key in keys:
        btree.insert(key)
        print(f"Inserido: {key}")
    
    print(f"\nBuscar 6: {btree.search(6)}")
    print(f"Buscar 15: {btree.search(15)}")
```

---

# Implementação Simplificada da B-Tree em C

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define T 3  // Grau mínimo da B-Tree (ordem = 2*T - 1 = 5)

typedef struct BTreeNode {
    int keys[2 * T - 1];
    struct BTreeNode *children[2 * T];
    int n;  // Número atual de chaves
    bool leaf;
} BTreeNode;

typedef struct BTree {
    BTreeNode *root;
} BTree;

BTreeNode* createNode(bool leaf) {
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    node->n = 0;
    node->leaf = leaf;
    for (int i = 0; i < 2 * T; i++) {
        node->children[i] = NULL;
    }
    return node;
}

BTree* createBTree() {
    BTree *tree = (BTree *)malloc(sizeof(BTree));
    tree->root = createNode(true);
    return tree;
}

bool search(BTreeNode *node, int k) {
    int i = 0;
    while (i < node->n && k > node->keys[i]) {
        i++;
    }
    
    if (i < node->n && k == node->keys[i]) {
        return true;
    }
    
    if (node->leaf) {
        return false;
    }
    
    return search(node->children[i], k);
}

void splitChild(BTreeNode *parent, int i) {
    BTreeNode *fullChild = parent->children[i];
    BTreeNode *newChild = createNode(fullChild->leaf);
    
    newChild->n = T - 1;
    
    for (int j = 0; j < T - 1; j++) {
        newChild->keys[j] = fullChild->keys[j + T];
    }
    
    if (!fullChild->leaf) {
        for (int j = 0; j < T; j++) {
            newChild->children[j] = fullChild->children[j + T];
        }
    }
    
    fullChild->n = T - 1;
    
    for (int j = parent->n; j > i; j--) {
        parent->children[j + 1] = parent->children[j];
    }
    parent->children[i + 1] = newChild;
    
    for (int j = parent->n - 1; j >= i; j--) {
        parent->keys[j + 1] = parent->keys[j];
    }
    parent->keys[i] = fullChild->keys[T - 1];
    parent->n++;
}

void insertNonFull(BTreeNode *node, int k) {
    int i = node->n - 1;
    
    if (node->leaf) {
        while (i >= 0 && k < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = k;
        node->n++;
    } else {
        while (i >= 0 && k < node->keys[i]) {
            i--;
        }
        i++;
        
        if (node->children[i]->n == 2 * T - 1) {
            splitChild(node, i);
            if (k > node->keys[i]) {
                i++;
            }
        }
        insertNonFull(node->children[i], k);
    }
}

void insert(BTree *tree, int k) {
    BTreeNode *root = tree->root;
    
    if (root->n == 2 * T - 1) {
        BTreeNode *newRoot = createNode(false);
        newRoot->children[0] = root;
        tree->root = newRoot;
        splitChild(newRoot, 0);
        insertNonFull(newRoot, k);
    } else {
        insertNonFull(root, k);
    }
}

void traverse(BTreeNode *node) {
    int i;
    for (i = 0; i < node->n; i++) {
        if (!node->leaf) {
            traverse(node->children[i]);
        }
        printf("%d ", node->keys[i]);
    }
    if (!node->leaf) {
        traverse(node->children[i]);
    }
}

int main() {
    BTree *tree = createBTree();
    
    int keys[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int n = sizeof(keys) / sizeof(keys[0]);
    
    printf("=== B-Tree de ordem %d ===\n\n", 2 * T - 1);
    
    printf("Inserindo chaves:\n");
    for (int i = 0; i < n; i++) {
        insert(tree, keys[i]);
        printf("  Inserido: %d\n", keys[i]);
    }
    
    printf("\nPercurso in-order: ");
    traverse(tree->root);
    printf("\n");
    
    printf("\n=== Buscas ===\n");
    printf("Buscar 6: %s\n", search(tree->root, 6) ? "Encontrado" : "Não encontrado");
    printf("Buscar 15: %s\n", search(tree->root, 15) ? "Encontrado" : "Não encontrado");
    printf("Buscar 30: %s\n", search(tree->root, 30) ? "Encontrado" : "Não encontrado");
    
    return 0;
}
```

---

## 7. Conclusão

A B-Tree representa uma das contribuições mais importantes para sistemas de armazenamento de dados. Sua design considerou desde o início as características de hardware (discos), resultando em uma estrutura que permanece relevante décadas depois.

Como Bayer e McCreight (1972) afirmaram: "A B-tree fornece uma solução elegante para o problema de manter grandes índices ordenados em armazenamento secundário".

Praticamente todo sistema de banco de dados moderno usa B-Trees ou variantes (B+ Trees), demonstrando a atemporalidade desta estrutura.

---

## Referências

* Bayer, R., & McCreight, E. (1972). **Organization and Maintenance of Large Ordered Indexes**. *Acta Informatica*, 1(3), 173-189.

* Comer, D. (1979). **The Ubiquitous B-Tree**. *ACM Computing Surveys*, 11(2), 121-137.

* Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009). *Introduction to Algorithms* (3rd ed.). MIT Press.

* Knuth, D. E. (1998). *The Art of Computer Programming, Volume 3: Sorting and Searching* (2nd ed.). Addison-Wesley.
