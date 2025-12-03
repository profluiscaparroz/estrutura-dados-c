# Tabela LCP (Longest Common Prefix)

## 📚 Definição Formal

A **Tabela LCP** (Longest Common Prefix Array) é uma estrutura de dados auxiliar ao Suffix Array que armazena os comprimentos dos prefixos comuns mais longos entre sufixos adjacentes na ordem lexicográfica.

**Definição Formal**: Para um Suffix Array SA de uma string S de tamanho n, o LCP Array é definido como:

```
LCP[i] = lcp(S[SA[i-1]..], S[SA[i]..])  para i ∈ {1, ..., n-1}
```

Onde `lcp(x, y)` retorna o comprimento do maior prefixo comum entre as strings x e y.

Por convenção, `LCP[0] = 0` ou é indefinido.

## 🎓 Fundamentação Teórica

### Motivação

O LCP Array complementa o Suffix Array, permitindo:
1. Emular operações de Suffix Tree
2. Acelerar busca de padrões
3. Encontrar substrings repetidas
4. Resolver problemas de substring comum

### Relação com Suffix Tree

O LCP Array contém exatamente a informação das arestas internas de uma Suffix Tree:
- `LCP[i]` = profundidade do LCA (Lowest Common Ancestor) entre folhas SA[i-1] e SA[i]

## 📊 Análise de Complexidade

### Construção

| Algoritmo | Tempo | Espaço |
|-----------|-------|--------|
| Naive | O(n²) | O(n) |
| Kasai et al. | O(n) | O(n) |
| Φ-Algorithm | O(n) | O(n) |
| PLCP | O(n) | O(n) |

### Operações com LCP

| Operação | Sem LCP | Com LCP + RMQ |
|----------|---------|---------------|
| LCP de dois sufixos | O(n) | O(1) |
| Busca de padrão | O(m log n) | O(m + log n) |
| Substring repetida | O(n²) | O(n) |

## 🔧 Algoritmo de Kasai (Construção Linear)

### Insight Fundamental

**Observação-chave**: Se `lcp(S[i..], S[j..]) = h`, então `lcp(S[i+1..], S[j+1..]) ≥ h - 1`

Isso significa que ao calcular LCP na ordem do texto (não do SA), o valor do LCP anterior fornece um lower bound.

### Algoritmo

```
KASAI_LCP(S, SA)
    n = |S|
    rank = [0] * n
    
    // Construir array de ranks (inverso do SA)
    for i in 0..n-1:
        rank[SA[i]] = i
    
    LCP = [0] * n
    h = 0
    
    for i in 0..n-1:
        if rank[i] > 0:
            j = SA[rank[i] - 1]  // Sufixo anterior lexicograficamente
            while i + h < n and j + h < n and S[i + h] = S[j + h]:
                h = h + 1
            LCP[rank[i]] = h
            if h > 0:
                h = h - 1  // Diminui no máximo 1
    
    return LCP
```

### Prova de Complexidade O(n)

- `h` aumenta no máximo n vezes no total (cada comparação positiva)
- `h` diminui no máximo n vezes (uma vez por iteração)
- Total de operações: O(n)

## 🔍 Aplicações

### 1. Substring Mais Longa Repetida

```
LONGEST_REPEATED_SUBSTRING(S, SA, LCP)
    max_len = MAX(LCP)
    pos = ARGMAX(LCP)
    return S[SA[pos] : SA[pos] + max_len]
```

**Complexidade**: O(n)

### 2. Contagem de Substrings Distintas

```
COUNT_DISTINCT(S, SA, LCP)
    n = |S|
    // Total de substrings - repetições
    return n * (n + 1) / 2 - SUM(LCP)
```

### 3. LCP de Dois Sufixos Quaisquer

Com pré-processamento RMQ (Range Minimum Query):

```
LCP_QUERY(SA, LCP, i, j)
    // LCP entre S[i..] e S[j..]
    ri = rank[i]
    rj = rank[j]
    if ri > rj:
        SWAP(ri, rj)
    return RMQ(LCP, ri + 1, rj)
```

**Pré-processamento**: O(n) para Sparse Table
**Consulta**: O(1)

### 4. Longest Common Substring de K Strings

Para encontrar a substring comum mais longa presente em pelo menos k das n strings:

1. Concatenar: S = S₁ + '#₁' + S₂ + '#₂' + ... + Sₙ + '#ₙ'
2. Construir SA e LCP
3. Usar janela deslizante no LCP para encontrar intervalos com k strings distintas

**Complexidade**: O(N) onde N = soma dos tamanhos

### 5. Número de Substrings Distintas em Janela

Para cada posição, contar substrings distintas que começam naquela janela:
- Usar LCP Array com estrutura de dados para range queries

## 📐 Range Minimum Query (RMQ)

### Sparse Table para RMQ

Pré-computar mínimos para intervalos de tamanho 2^k:

```
BUILD_SPARSE_TABLE(LCP)
    n = |LCP|
    log_n = LOG2(n) + 1
    
    // sparse[i][j] = mínimo no intervalo [i, i + 2^j - 1]
    sparse = [[0] * log_n for _ in range(n)]
    
    // Base: intervalos de tamanho 1
    for i in 0..n-1:
        sparse[i][0] = LCP[i]
    
    // Intervalos maiores
    for j in 1..log_n-1:
        for i in 0..(n - 2^j):
            sparse[i][j] = MIN(sparse[i][j-1], sparse[i + 2^(j-1)][j-1])
    
    return sparse

RMQ(sparse, l, r)
    len = r - l + 1
    k = LOG2(len)
    return MIN(sparse[l][k], sparse[r - 2^k + 1][k])
```

**Pré-processamento**: O(n log n)
**Consulta**: O(1)

### Algoritmo de Farach-Colton-Bender

Para LCP Arrays especificamente:
- LCP Array tem propriedade ±1 (valores adjacentes diferem em no máximo 1)
- Permite RMQ em O(n) espaço e O(1) consulta

## 🔄 Estruturas Relacionadas

### PLCP Array (Permuted LCP)

```
PLCP[i] = LCP[rank[i]]
```

Armazena LCP na ordem do texto, facilitando certas aplicações.

### Φ-Function

```
Φ[i] = SA[rank[i] - 1]  se rank[i] > 0
     = -1               caso contrário
```

Predecessor no Suffix Array, usado em algoritmos de construção.

## 📖 Referências Bibliográficas

1. **Kasai, T., Lee, G., Arimura, H., Arikawa, S., & Park, K.** (2001). Linear-Time Longest-Common-Prefix Computation in Suffix Arrays and Its Applications. *CPM*, 181-192.

2. **Manzini, G.** (2004). Two Space Saving Tricks for Linear Time LCP Array Computation. *SWAT*, 372-383.

3. **Fischer, J., & Heun, V.** (2007). A New Succinct Representation of RMQ-Information and Improvements in the Enhanced Suffix Array. *ESCAPE*, 459-470.

4. **Bender, M. A., & Farach-Colton, M.** (2000). The LCA Problem Revisited. *LATIN*, 88-94.

5. **Kärkkäinen, J., Manzini, G., & Puglisi, S. J.** (2009). Permuted Longest-Common-Prefix Array. *CPM*, 181-192.

## 🔗 Navegação

← **[07-suffix-array](../07-suffix-array/)**: Suffix Array

→ **[09-bloomfilter](../09-bloomfilter/)**: Bloom Filter

---

*Este material faz parte do curso de Estrutura de Dados em C.*
