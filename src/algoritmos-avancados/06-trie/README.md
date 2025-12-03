# Trie (Árvore de Prefixos)

## 📚 Definição Formal

Uma **Trie** (pronuncia-se "try", do inglês "re**trie**val") é uma estrutura de dados em árvore usada para armazenar um conjunto dinâmico de strings, onde as chaves são geralmente strings. Também conhecida como **Árvore de Prefixos** ou **Radix Tree** (quando compactada).

**Definição Formal**: Uma Trie sobre alfabeto Σ é uma árvore enraizada onde:
- Cada aresta é rotulada com um símbolo de Σ
- Para cada nó, arestas para filhos têm rótulos distintos
- Uma chave é representada pelo caminho da raiz ao nó marcado como final

## 🎓 Fundamentação Teórica

### Origem Histórica

- **Edward Fredkin (1960)**: Introduziu o termo "Trie"
- **René de la Briandais (1959)**: Estrutura similar para armazenamento de strings
- Derivado de "retrieval", mas pronunciado diferente para distinguir de "tree"

### Propriedades Fundamentais

1. **Prefixo Comum**: Strings com prefixo comum compartilham caminho
2. **Busca por Prefixo**: O(m) onde m é o comprimento do prefixo
3. **Ordenação Lexicográfica**: Travessia DFS produz strings ordenadas
4. **Sem Colisões**: Diferente de hash tables

## 📊 Análise de Complexidade

Seja:
- n = número de strings armazenadas
- m = comprimento da string consultada
- |Σ| = tamanho do alfabeto

| Operação | Complexidade Tempo | Complexidade Espaço |
|----------|-------------------|---------------------|
| Inserção | O(m) | O(m × |Σ|) |
| Busca Exata | O(m) | O(1) |
| Busca por Prefixo | O(m + k) | O(1) |
| Deleção | O(m) | O(1) |
| Autocompletar | O(m + k) | O(k) |

Onde k = número de matches encontrados

### Análise de Espaço

**Trie Padrão**:
- Pior caso: O(n × m × |Σ|)
- Cada nó tem |Σ| ponteiros

**Trie Compacta (Patricia Tree)**:
- O(n) nós no máximo
- Significativa economia para strings longas

## 🔧 Estrutura de Dados

### Trie Padrão (Array de Filhos)

```c
#define ALPHABET_SIZE 26

typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
    int frequency;  // Opcional: contagem de ocorrências
} TrieNode;
```

**Trade-offs**:
- ✅ Acesso O(1) aos filhos
- ❌ Espaço desperdiçado para nós esparsos

### Trie com HashMap

```c
typedef struct TrieNode {
    HashMap *children;  // char → TrieNode*
    bool isEndOfWord;
} TrieNode;
```

**Trade-offs**:
- ✅ Economiza espaço para alfabetos grandes
- ❌ Overhead de hash para cada nó

### Trie com Lista de Filhos

```c
typedef struct TrieNode {
    char character;
    struct TrieNode *sibling;  // Próximo filho do pai
    struct TrieNode *child;    // Primeiro filho
    bool isEndOfWord;
} TrieNode;
```

**Trade-offs**:
- ✅ Mínimo uso de memória
- ❌ Busca O(|Σ|) para encontrar filho

## 🔄 Operações Fundamentais

### Inserção

```
INSERT(root, word)
    node = root
    for cada caractere c em word:
        index = c - 'a'
        if node.children[index] = NIL:
            node.children[index] = CREATE_NODE()
        node = node.children[index]
    node.isEndOfWord = true
```

### Busca Exata

```
SEARCH(root, word)
    node = root
    for cada caractere c em word:
        index = c - 'a'
        if node.children[index] = NIL:
            return false
        node = node.children[index]
    return node.isEndOfWord
```

### Autocompletar

```
AUTOCOMPLETE(root, prefix)
    // 1. Navegar até nó do prefixo
    node = FIND_PREFIX_NODE(root, prefix)
    if node = NIL:
        return []
    
    // 2. DFS para coletar todas palavras
    results = []
    DFS_COLLECT(node, prefix, results)
    return results

DFS_COLLECT(node, current, results)
    if node.isEndOfWord:
        results.append(current)
    for cada filho (char, child) de node:
        DFS_COLLECT(child, current + char, results)
```

## 📐 Variantes de Trie

### 1. Patricia Tree (Radix Tree)

**Compactação**: Combina cadeias de nós únicos em arestas

```
Trie Normal:          Patricia Tree:
    (root)               (root)
      |                    |
      c                   [car]
      |                   / \
      a                 [s] [t]
     /|\                 |
    r s t               [s]
    |   |
    s   s
```

**Vantagens**:
- Menos nós (O(n) ao invés de O(nm))
- Menos acessos de memória
- Usado em: roteadores IP (longest prefix match)

### 2. Ternary Search Trie (TST)

Cada nó tem três ponteiros: menor, igual, maior

```c
typedef struct TSTNode {
    char character;
    struct TSTNode *lo, *eq, *hi;
    bool isEndOfWord;
} TSTNode;
```

**Vantagens**:
- Menos espaço que Trie padrão
- Mais rápido que BST de strings

### 3. DAWG (Directed Acyclic Word Graph)

Também conhecido como **DAFSA** (Deterministic Acyclic Finite State Automaton)

- Compartilha sufixos comuns também
- Minimal DFA para conjunto de strings
- Usado em: Scrabble solvers, spell checkers

### 4. Suffix Trie

- Insere todos sufixos de uma string
- Base para Suffix Tree
- Tamanho: O(n²) para string de tamanho n

## 🎯 Aplicações Práticas

### 1. Autocompletar e Sugestões

**Google Search, IDEs, Mobile Keyboards**:
- Prefixo → lista de completamentos
- Ordenado por frequência/relevância

### 2. Spell Checking

```
SPELL_CHECK(root, word)
    if SEARCH(root, word):
        return "Correto"
    return FIND_SUGGESTIONS(root, word, maxDistance)
```

**Técnicas**:
- Distância de Levenshtein
- Fuzzy matching com threshold

### 3. Roteamento IP (Longest Prefix Match)

**Roteadores de Internet**:
- Endereço IP → próximo hop
- Radix Tree binária (0/1 por nível)
- O(32) para IPv4, O(128) para IPv6

### 4. Compressão de Texto

**Algoritmo LZW**:
- Dicionário como Trie
- Compressão baseada em strings repetidas

### 5. Word Games

**Boggle, Scrabble**:
- Verificar validade de palavras
- Encontrar todas palavras possíveis

## ⚙️ Otimizações

### 1. Cache de Top-K por Nó

```c
typedef struct TrieNode {
    // ... campos padrão ...
    char *topSuggestions[K];  // Pré-computadas
} TrieNode;
```

### 2. Compressão de Nó

- Bitmap para indicar filhos presentes
- Array compacto apenas com filhos existentes

### 3. Burst Trie

- Buckets de strings em nós folha
- Expande bucket quando muito cheio
- Melhor uso de cache

## 📖 Referências Bibliográficas

1. **Fredkin, E.** (1960). Trie Memory. *Communications of the ACM*, 3(9), 490-499.

2. **Morrison, D. R.** (1968). PATRICIA - Practical Algorithm To Retrieve Information Coded in Alphanumeric. *JACM*, 15(4), 514-534.

3. **Knuth, D. E.** (1998). *The Art of Computer Programming, Vol. 3: Sorting and Searching* (2nd ed.). Addison-Wesley. Seção 6.3.

4. **Bentley, J. L., & Sedgewick, R.** (1997). Fast Algorithms for Sorting and Searching Strings. *SODA*, 360-369.

5. **Heinz, S., Zobel, J., & Williams, H. E.** (2002). Burst Tries: A Fast, Efficient Data Structure for String Keys. *ACM TOIS*, 20(2), 192-223.

## 🔗 Navegação

← **[05-arvore-binaria-busca-avancada](../05-arvore-binaria-busca-avancada/)**: Árvore Binária de Busca Avançada

→ **[07-suffix-array](../07-suffix-array/)**: Suffix Array

---

*Este material faz parte do curso de Estrutura de Dados em C.*
