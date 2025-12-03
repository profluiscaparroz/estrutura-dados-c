# Suffix Array

## 📚 Definição Formal

Um **Suffix Array** (Array de Sufixos) é uma estrutura de dados que consiste em um array ordenado de todos os sufixos de uma string. Formalmente, para uma string S de tamanho n, o suffix array SA é uma permutação de {0, 1, ..., n-1} tal que:

```
S[SA[0]..n-1] < S[SA[1]..n-1] < ... < S[SA[n-1]..n-1]
```

Onde < denota ordem lexicográfica.

## 🎓 Fundamentação Teórica

### Origem Histórica

- **Manber & Myers (1990)**: Introduziram o Suffix Array como alternativa space-efficient à Suffix Tree
- **Motivação**: Suffix Tree usa O(n) palavras de memória (20-40 bytes/caractere), enquanto Suffix Array usa O(n) inteiros (4-8 bytes/caractere)

### Relação com Suffix Tree

Todo problema resolvível com Suffix Tree pode ser resolvido com Suffix Array + LCP Array:

```
Suffix Tree ↔ Suffix Array + LCP Array
```

**Conversão**:
- Suffix Tree → Suffix Array: Travessia DFS das folhas em ordem lexicográfica
- Suffix Array + LCP → Suffix Tree: Algoritmo de Kasai et al. (2001)

## 📊 Análise de Complexidade

### Construção

| Algoritmo | Tempo | Espaço | Ano |
|-----------|-------|--------|-----|
| Naive (ordenação) | O(n² log n) | O(n) | - |
| Manber-Myers | O(n log n) | O(n) | 1990 |
| Larsson-Sadakane | O(n log n) | O(n) | 1999 |
| KS (Kärkkäinen-Sanders) | O(n) | O(n) | 2003 |
| SA-IS (Induced Sorting) | O(n) | O(n) | 2009 |
| DivSufSort | O(n log n) | O(n) | - |

### Operações

| Operação | Complexidade | Com LCP |
|----------|--------------|---------|
| Busca de padrão | O(m log n) | O(m + log n) |
| Contagem de ocorrências | O(m log n) | O(m + log n) |
| Substring mais longa repetida | O(n) | O(n) |
| LCP entre sufixos | O(1) | Com RMQ |

Onde m = tamanho do padrão, n = tamanho do texto

## 🔧 Construção do Suffix Array

### Algoritmo Naive

```
NAIVE_SUFFIX_ARRAY(S)
    n = |S|
    suffixes = [(i, S[i:]) for i in 0..n-1]
    SORT(suffixes, by second element)
    return [i for (i, _) in suffixes]
```

**Complexidade**: O(n² log n) - cada comparação custa O(n)

### Algoritmo Prefix Doubling (Manber-Myers)

**Ideia**: Ordenar sufixos por prefixos de tamanho 1, 2, 4, 8, ... até 2^k ≥ n

```
PREFIX_DOUBLING(S)
    n = |S|
    rank = [ord(S[i]) for i in 0..n-1]
    k = 1
    while k < n:
        // Ordenar por (rank[i], rank[i+k])
        suffixes = [(rank[i], rank[i+k] if i+k < n else -1, i) for i in 0..n-1]
        SORT(suffixes)
        // Atualizar ranks
        rank[suffixes[0][2]] = 0
        for i in 1..n-1:
            if suffixes[i][0:2] = suffixes[i-1][0:2]:
                rank[suffixes[i][2]] = rank[suffixes[i-1][2]]
            else:
                rank[suffixes[i][2]] = i
        k = 2 * k
    return [s[2] for s in suffixes]
```

**Complexidade**: O(n log n) com radix sort, O(n log² n) com comparison sort

### Algoritmo SA-IS (Induced Sorting)

**Estado da arte** para construção em tempo linear O(n):

1. Classificar sufixos como S-type ou L-type
2. Encontrar sufixos LMS (leftmost S-type)
3. Induzir ordenação dos demais sufixos

**Vantagens**:
- Tempo linear garantido
- Cache-efficient
- Baixo overhead de espaço

## 🔍 Busca de Padrões

### Busca Binária

```
SEARCH_PATTERN(SA, S, P)
    n = |S|
    m = |P|
    
    // Encontrar limite inferior
    lo = 0, hi = n - 1
    while lo < hi:
        mid = (lo + hi) / 2
        if S[SA[mid]:SA[mid]+m] < P:
            lo = mid + 1
        else:
            hi = mid
    left = lo
    
    // Encontrar limite superior
    hi = n - 1
    while lo < hi:
        mid = (lo + hi + 1) / 2
        if S[SA[mid]:SA[mid]+m] > P:
            hi = mid - 1
        else:
            lo = mid
    right = lo
    
    if S[SA[left]:SA[left]+m] = P:
        return (left, right)  // Intervalo de matches
    else:
        return NIL
```

**Complexidade**: O(m log n) para m comparações em log n iterações

### Busca com LCP Array

Usando LCP para evitar comparações redundantes:
- Complexidade: O(m + log n)
- Mantém LCP entre padrão e limites atuais

## 📐 Aplicações

### 1. Substring Mais Longa Repetida

```
LONGEST_REPEATED_SUBSTRING(SA, LCP)
    max_lcp = 0
    max_pos = -1
    for i in 1..n-1:
        if LCP[i] > max_lcp:
            max_lcp = LCP[i]
            max_pos = SA[i]
    return S[max_pos : max_pos + max_lcp]
```

**Complexidade**: O(n)

### 2. Contagem de Substrings Distintas

```
COUNT_DISTINCT_SUBSTRINGS(SA, LCP)
    n = |S|
    total = n * (n + 1) / 2  // Total de substrings
    repeated = SUM(LCP)       // Substrings repetidas
    return total - repeated
```

### 3. Longest Common Substring (LCS)

Para duas strings S₁ e S₂:
1. Concatenar: S = S₁ + '#' + S₂
2. Construir SA e LCP
3. Encontrar maior LCP entre sufixos de strings diferentes

**Complexidade**: O(n) onde n = |S₁| + |S₂|

### 4. Alinhamento de Sequências (Bioinformática)

- Busca de genomas
- Detecção de repetições em DNA
- Compressão de sequências biológicas

## 🔄 Estruturas Relacionadas

### Suffix Tree

| Aspecto | Suffix Array | Suffix Tree |
|---------|--------------|-------------|
| Espaço | 4n-8n bytes | 20n-40n bytes |
| Construção | O(n) | O(n) |
| Busca | O(m log n) | O(m) |
| Implementação | Simples | Complexa |
| Cache | Bom | Ruim |

### Enhanced Suffix Array

Suffix Array + estruturas auxiliares para emular Suffix Tree:
- LCP Array
- Child Table
- Suffix Links

Permite todas operações de Suffix Tree em tempo ótimo.

### FM-Index

Estrutura baseada em BWT (Burrows-Wheeler Transform):
- Suporta busca em O(m)
- Comprimido: O(n/log n) bits
- Usado em: BWA, Bowtie (alinhadores de DNA)

## 📖 Referências Bibliográficas

1. **Manber, U., & Myers, G.** (1990). Suffix Arrays: A New Method for On-Line String Searches. *SODA*, 319-327.

2. **Kärkkäinen, J., & Sanders, P.** (2003). Simple Linear Work Suffix Array Construction. *ICALP*, 943-955.

3. **Nong, G., Zhang, S., & Chan, W. H.** (2009). Linear Suffix Array Construction by Almost Pure Induced-Sorting. *DCC*, 193-202.

4. **Kasai, T., et al.** (2001). Linear-Time Longest-Common-Prefix Computation in Suffix Arrays and Its Applications. *CPM*, 181-192.

5. **Abouelhoda, M. I., Kurtz, S., & Ohlebusch, E.** (2004). Replacing Suffix Trees with Enhanced Suffix Arrays. *Journal of Discrete Algorithms*, 2(1), 53-86.

## 🔗 Navegação

← **[06-trie](../06-trie/)**: Trie (Árvore de Prefixos)

→ **[08-tabela-lcp](../08-tabela-lcp/)**: Tabela LCP (Longest Common Prefix)

---

*Este material faz parte do curso de Estrutura de Dados em C.*
