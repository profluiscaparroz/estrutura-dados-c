# Algoritmos Avançados

## 📋 Visão Geral

Este diretório contém implementações de algoritmos e estruturas de dados avançadas, representando técnicas de ponta utilizadas em sistemas de produção modernos, bancos de dados, sistemas distribuídos e aplicações de alta performance.

## 📁 Estrutura do Diretório

### Algoritmos Fundamentais
- **01-algoritmo-recursao** - Técnicas avançadas de recursão
- **02-algoritmo-divisao-conquista** - Paradigma dividir para conquistar

### Estruturas de Dados Avançadas para Busca
- **03-consistent-hashing** - Hashing consistente para sistemas distribuídos
- **04-hash-table-avancada** - Implementações avançadas de tabelas hash
- **05-arvore-binaria-busca-avancada** - BST com técnicas otimizadas
- **06-trie** - Árvore de prefixos para strings
- **07-suffix-array** - Arrays de sufixos para busca de padrões
- **08-tabela-lcp** - Tabela Longest Common Prefix

### Árvores Balanceadas
- **12-treap** - Tree + Heap híbrido
- **13-splay-tree** - Árvore auto-ajustável
- **14-avl-tree** - Árvore AVL (balanceamento rigoroso)
- **15-skip-list** - Lista com múltiplos níveis
- **20-b-tree** - Árvore B para sistemas de arquivos

### Estruturas de Dados Especializadas
- **16-segment-tree** - Árvore de segmentos para range queries
- **17-fenwick-tree** - Binary Indexed Tree
- **18-disjoint-set-union** - Union-Find com otimizações
- **19-kd-tree** - K-dimensional tree para dados espaciais

### Estruturas Probabilísticas
- **09-bloomfilter** - Filtro probabilístico de pertencimento
- **10-count-min-sketch** - Estimativa de frequências
- **11-hyperloglog** - Contagem de cardinalidade

## 🎯 Resumo de Cada Estrutura

### 01-02: Paradigmas de Algoritmos

**Recursão e Divisão-Conquista**
- Técnicas fundamentais para resolver problemas complexos
- Base para muitos algoritmos eficientes

### 03-04: Hashing Avançado

**Consistent Hashing**
- Distribuição de dados em sistemas distribuídos
- Minimiza redistribuição quando nós são adicionados/removidos
- Aplicação: Load balancers, caches distribuídos

**Hash Tables Avançadas**
- Cuckoo hashing, Robin Hood hashing
- Otimizações para casos específicos

### 05-06-07-08: Processamento de Strings

**Trie (Árvore de Prefixos)**
- Busca de palavras: O(m) onde m = comprimento
- Autocompletar, spell checkers
- Dicionários eficientes

**Suffix Array + LCP**
- Busca de padrões: O(m log n)
- Análise de DNA, compressão de dados
- Menor uso de memória que suffix tree

### 09-10-11: Estruturas Probabilísticas

**Bloom Filter**
- Teste de pertencimento com falsos positivos (sem falsos negativos)
- Espaço: muito menor que hash table
- Aplicação: Caches, databases, redes

**Count-Min Sketch**
- Estimativa de frequências com erro limitado
- Streaming data, network monitoring

**HyperLogLog**
- Contagem de elementos únicos (cardinalidade)
- Erro < 2% com poucos bytes
- Aplicação: Analytics, big data

### 12-15-20: Árvores Balanceadas

**Comparação de Árvores Balanceadas:**

| Estrutura | Balanceamento | Inserção | Busca | Uso Principal |
|-----------|---------------|----------|-------|---------------|
| **AVL** | Rigoroso | O(log n) | O(log n) | Buscas frequentes |
| **Treap** | Probabilístico | O(log n)* | O(log n)* | Simplicidade |
| **Splay** | Amortizado | O(log n)* | O(log n)* | Dados com localidade |
| **Skip List** | Probabilístico | O(log n)* | O(log n)* | Concorrência |
| **B-Tree** | Altura mínima | O(log n) | O(log n) | Discos, DBs |

\* Esperado

### 16-17-18-19: Estruturas Especializadas

**Segment Tree**
- Range queries: O(log n)
- Range updates: O(log n)
- Aplicação: Geometria computacional, intervalos

**Fenwick Tree (BIT)**
- Prefix sums: O(log n)
- Update: O(log n)
- Mais simples que segment tree, menos geral

**Disjoint Set (Union-Find)**
- Union: O(α(n)) ≈ O(1)
- Find: O(α(n)) ≈ O(1)
- Aplicação: Kruskal, componentes conexos

**KD-Tree**
- Busca espacial: O(log n) médio
- K-nearest neighbors
- Aplicação: Gráficos, machine learning

## 📊 Comparação: Quando Usar Cada Estrutura

### Para Buscas em Strings

| Operação | Trie | Suffix Array | Hash Table |
|----------|------|--------------|------------|
| Busca exata | O(m) | O(m log n) | O(1)* |
| Busca prefixo | O(m + k) | O(m log n + k) | N/A |
| Busca substring | O(m + k) | O(m log n + k) | N/A |
| Espaço | Alto | Médio | Médio |

### Para Range Queries

| Estrutura | Query | Update | Espaço | Complexidade |
|-----------|-------|--------|--------|--------------|
| **Array** | O(n) | O(1) | O(n) | Simples |
| **Segment Tree** | O(log n) | O(log n) | O(n) | Média |
| **Fenwick Tree** | O(log n) | O(log n) | O(n) | Média |
| **Sparse Table** | O(1) | N/A | O(n log n) | Somente leitura |

### Para Estruturas Probabilísticas

| Estrutura | Operação | Espaço | Erro | Uso |
|-----------|----------|--------|------|-----|
| **Bloom Filter** | Pertencimento | Muito baixo | Falsos positivos | Cache, DB |
| **Count-Min** | Frequência | Baixo | Over-estimation | Streams |
| **HyperLogLog** | Cardinalidade | Muito baixo | ~2% | Analytics |

## 🔧 Compilação

Cada subdiretório possui suas próprias instruções de compilação. Geralmente:

```bash
# Navegar para o diretório específico
cd 14-avl-tree

# Compilar
make
# ou
gcc -Wall -Wextra -std=c99 -O3 -o avl avl_tree.c

# Executar
./avl
```

## 💡 Escolhendo a Estrutura Certa

### Perguntas-Chave

1. **Que operações são mais frequentes?**
   - Busca → AVL, B-Tree
   - Inserção/Remoção → Splay Tree, Treap
   - Range queries → Segment Tree

2. **Qual o padrão de acesso?**
   - Localidade temporal → Splay Tree
   - Aleatório → AVL
   - Sequencial → Skip List

3. **Restrições de memória?**
   - Baixa memória → Bloom Filter, HyperLogLog
   - Streaming data → Count-Min Sketch

4. **Precisão necessária?**
   - Exata → Estruturas determinísticas
   - Aproximada → Estruturas probabilísticas

5. **Dados persistentes (disco)?**
   - Sim → B-Tree, B+ Tree
   - Não → AVL, Treap

## 🚀 Casos de Uso Reais

### Google/Facebook/Amazon
- **Consistent Hashing**: Distribuição de dados
- **Bloom Filters**: Cache layers
- **HyperLogLog**: Analytics de usuários únicos

### Banco de Dados
- **B-Trees**: Índices (MySQL, PostgreSQL)
- **Skip Lists**: Redis (sorted sets)
- **Tries**: Autocomplete

### Sistemas de Arquivos
- **B-Trees**: Ext4, NTFS
- **KD-Trees**: Organizações espaciais

### Compiladores
- **Tries**: Tabela de símbolos
- **Union-Find**: Análise de fluxo

### Machine Learning
- **KD-Trees**: K-NN, clustering
- **Count-Min Sketch**: Feature counting

## 📖 Recursos de Aprendizado

### Livros
- "Introduction to Algorithms" (CLRS)
- "Advanced Data Structures" (Brass)
- "The Algorithm Design Manual" (Skiena)

### Online
- [CP-Algorithms](https://cp-algorithms.com/)
- [GeeksforGeeks](https://www.geeksforgeeks.org/)
- [Visualgo](https://visualgo.net/)

### Papers
- Cada diretório contém referências específicas

## ⚠️ Nota sobre Complexidade

Complexidades listadas assumem:
- Implementação correta
- Distribuição razoável de dados
- Operações balanceadas

Em casos específicos, comportamento pode variar.

## 🎓 Níveis de Dificuldade

**Iniciante:**
- 01-02: Recursão e Divisão-Conquista
- 14: AVL Tree
- 18: Union-Find

**Intermediário:**
- 06: Trie
- 09: Bloom Filter
- 16-17: Segment/Fenwick Tree

**Avançado:**
- 03: Consistent Hashing
- 07-08: Suffix Array + LCP
- 10-11: Count-Min Sketch, HyperLogLog
- 12-13: Treap, Splay Tree
- 19: KD-Tree
- 20: B-Tree

---

**Repositório**: https://github.com/profluiscaparroz/estrutura-dados-c
