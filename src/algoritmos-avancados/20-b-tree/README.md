# B-Tree

## 📚 Definição Formal

Uma **B-Tree** de ordem m é uma árvore de busca balanceada auto-balanceada que mantém dados ordenados e permite buscas, inserções e deleções em tempo logarítmico. Projetada para sistemas que leem e escrevem blocos grandes de dados, como sistemas de arquivos e bancos de dados.

**Definição Formal**: Uma B-Tree de ordem m é uma árvore que satisfaz:
1. Todo nó tem no máximo m filhos
2. Todo nó interno (exceto raiz) tem no mínimo ⌈m/2⌉ filhos
3. A raiz tem no mínimo 2 filhos (se não for folha)
4. Todas as folhas estão no mesmo nível
5. Um nó com k filhos contém k-1 chaves

## 🎓 Fundamentação Teórica

### Origem Histórica

- **Rudolf Bayer & Edward McCreight (1972)**: Artigo "Organization and Maintenance of Large Ordered Indices" na *Acta Informatica*
- **Boeing Scientific Research Labs**: Desenvolvida para otimizar acesso a disco
- **Nome**: Origem do "B" nunca foi oficialmente explicada (teorias: Bayer, Boeing, Balanced, Broad)

### Motivação

**Problema**: Em sistemas com discos, o tempo de acesso é dominado pelo tempo de seek/latência.

**Solução**: Maximizar dados por nó = minimizar acessos ao disco

```
Tempo de acesso ao disco:
- Seek time: ~10ms
- Latency: ~5ms
- Transfer: ~0.01ms/KB

Para 1 milhão de registros:
- Árvore binária: log₂(10⁶) ≈ 20 acessos ao disco
- B-Tree (ordem 100): log₁₀₀(10⁶) ≈ 3 acessos ao disco
```

## 📊 Análise de Complexidade

| Operação | Complexidade | Acessos ao disco |
|----------|--------------|------------------|
| Busca | O(log n) | O(logₘ n) |
| Inserção | O(log n) | O(logₘ n) |
| Deleção | O(log n) | O(logₘ n) |
| Range query | O(log n + k) | O(logₘ n + k/m) |

### Altura

Para n chaves e ordem m:
```
h ≤ logₘ/₂((n+1)/2)
```

**Exemplo**: n = 10⁹, m = 1000
```
h ≤ log₅₀₀(5×10⁸) ≈ 3.2
```

Apenas **4 acessos ao disco** para bilhões de registros!

## 🔧 Estrutura de Dados

```c
#define MAX_KEYS 1000  // Ordem m = 1001
#define MIN_KEYS (MAX_KEYS / 2)

typedef struct BTreeNode {
    int keys[MAX_KEYS];
    struct BTreeNode *children[MAX_KEYS + 1];
    int num_keys;
    bool is_leaf;
} BTreeNode;

typedef struct {
    BTreeNode *root;
    int order;
} BTree;
```

## 🔄 Operações Fundamentais

### Busca

```c
BTreeNode* search(BTreeNode *node, int key, int *idx) {
    int i = 0;
    
    // Encontrar posição da chave ou primeiro maior
    while (i < node->num_keys && key > node->keys[i]) {
        i++;
    }
    
    // Chave encontrada
    if (i < node->num_keys && key == node->keys[i]) {
        *idx = i;
        return node;
    }
    
    // Chave não encontrada e é folha
    if (node->is_leaf) {
        return NULL;
    }
    
    // Recursão no filho apropriado
    return search(node->children[i], key, idx);
}
```

### Inserção

```c
void insert(BTree *tree, int key) {
    BTreeNode *root = tree->root;
    
    // Caso especial: raiz está cheia
    if (root->num_keys == MAX_KEYS) {
        BTreeNode *new_root = create_node(false);
        new_root->children[0] = root;
        tree->root = new_root;
        
        split_child(new_root, 0);
        insert_non_full(new_root, key);
    } else {
        insert_non_full(root, key);
    }
}

void insert_non_full(BTreeNode *node, int key) {
    int i = node->num_keys - 1;
    
    if (node->is_leaf) {
        // Deslocar chaves e inserir
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->num_keys++;
    } else {
        // Encontrar filho apropriado
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        
        // Dividir filho se necessário
        if (node->children[i]->num_keys == MAX_KEYS) {
            split_child(node, i);
            if (key > node->keys[i]) {
                i++;
            }
        }
        insert_non_full(node->children[i], key);
    }
}

void split_child(BTreeNode *parent, int idx) {
    BTreeNode *full_child = parent->children[idx];
    BTreeNode *new_child = create_node(full_child->is_leaf);
    
    int mid = MAX_KEYS / 2;
    
    // Mover metade das chaves para novo nó
    new_child->num_keys = MAX_KEYS - mid - 1;
    for (int j = 0; j < new_child->num_keys; j++) {
        new_child->keys[j] = full_child->keys[mid + 1 + j];
    }
    
    // Mover filhos se não for folha
    if (!full_child->is_leaf) {
        for (int j = 0; j <= new_child->num_keys; j++) {
            new_child->children[j] = full_child->children[mid + 1 + j];
        }
    }
    
    full_child->num_keys = mid;
    
    // Inserir chave mediana no pai
    for (int j = parent->num_keys; j > idx; j--) {
        parent->children[j + 1] = parent->children[j];
    }
    parent->children[idx + 1] = new_child;
    
    for (int j = parent->num_keys - 1; j >= idx; j--) {
        parent->keys[j + 1] = parent->keys[j];
    }
    parent->keys[idx] = full_child->keys[mid];
    parent->num_keys++;
}
```

### Deleção

A deleção em B-Tree é mais complexa, envolvendo:
1. **Caso 1**: Chave em folha → remover diretamente
2. **Caso 2**: Chave em nó interno → substituir por predecessor/sucessor
3. **Caso 3**: Underflow → emprestar de irmão ou merge

## 📐 Variantes

### B+ Tree

Variante mais comum em bancos de dados:
- **Diferenças**:
  - Dados apenas nas folhas
  - Folhas conectadas em lista ligada
  - Chaves internas são apenas índices
- **Vantagens**:
  - Range queries eficientes
  - Todos os dados no mesmo nível
  - Mais chaves por nó interno

### B* Tree

- Nós preenchidos até 2/3 (ao invés de 1/2)
- Redistribuição antes de split
- Melhor utilização de espaço

### Blink Tree

- Otimizada para concorrência
- Usa latches e link pointers
- Permite travessia sem lock na raiz

## 🎯 Aplicações Práticas

### 1. Bancos de Dados

**MySQL (InnoDB)**:
- Índice clustered em B+ Tree
- Índices secundários apontam para chave primária

**PostgreSQL**:
- B-Tree é índice default
- GiST, GIN para outros tipos

**SQLite**:
- Usa B-Tree para tabelas e índices
- Variante com células de tamanho variável

### 2. Sistemas de Arquivos

**NTFS, HFS+, ext4**:
- Metadados em B-Tree
- Localização de arquivos/diretórios

**Btrfs, ZFS**:
- Copy-on-write B-Trees
- Suporta snapshots eficientes

### 3. Bancos NoSQL

**MongoDB**:
- Índices em B-Tree

**CouchDB, LevelDB**:
- LSM-Trees (relacionadas)

## 🔒 Concorrência

### Latch Crabbing

Protocolo para acesso concorrente:

```c
// Busca
void search_concurrent(BTree *tree, int key) {
    lock(tree->root);
    BTreeNode *node = tree->root;
    
    while (!node->is_leaf) {
        BTreeNode *child = find_child(node, key);
        lock(child);
        unlock(node);  // "Crab" para próximo nó
        node = child;
    }
    
    // ... buscar na folha
    unlock(node);
}
```

### B-Link Tree

Adiciona ponteiros de link para evitar locks na raiz:

```c
typedef struct BLinkNode {
    // ... campos padrão
    struct BLinkNode *right_link;  // Ponteiro para irmão direito
    int high_key;                   // Maior chave no irmão
} BLinkNode;
```

## 📖 Referências Bibliográficas

1. **Bayer, R., & McCreight, E.** (1972). Organization and Maintenance of Large Ordered Indices. *Acta Informatica*, 1(3), 173-189.

2. **Comer, D.** (1979). The Ubiquitous B-Tree. *ACM Computing Surveys*, 11(2), 121-137.

3. **Cormen, T. H., et al.** (2009). *Introduction to Algorithms* (3rd ed.). MIT Press. Capítulo 18.

4. **Graefe, G.** (2011). Modern B-Tree Techniques. *Foundations and Trends in Databases*, 3(4), 203-402.

5. **Lehman, P. L., & Yao, S. B.** (1981). Efficient Locking for Concurrent Operations on B-Trees. *ACM TODS*, 6(4), 650-670.

## 🔗 Navegação

← **[19-kd-tree](../19-kd-tree/)**: K-D Tree

---

*Este material faz parte do curso de Estrutura de Dados em C.*
