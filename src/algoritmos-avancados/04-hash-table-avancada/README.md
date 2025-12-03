# Tabelas Hash Avançadas

## 📚 Definição Formal

Uma **Tabela Hash** (Hash Table) é uma estrutura de dados que implementa um mapeamento associativo de chaves para valores, utilizando uma **função hash** para computar um índice em um array de buckets ou slots. As técnicas avançadas de hash table visam otimizar a performance, minimizar colisões e garantir complexidade O(1) nas operações.

## 🎓 Fundamentação Teórica

### Base Matemática

Uma função hash `h: U → {0, 1, ..., m-1}` mapeia o universo de chaves U para slots da tabela:

- **m**: tamanho da tabela
- **n**: número de elementos armazenados
- **α = n/m**: fator de carga (load factor)

### Propriedades Desejáveis

1. **Uniformidade Simples (Simple Uniform Hashing)**:
   - Cada chave tem igual probabilidade de ser mapeada para qualquer slot
   - Pr[h(k) = i] = 1/m para todo k e todo i

2. **Independência**:
   - h(k₁) e h(k₂) são independentes para k₁ ≠ k₂

3. **Avalanche Effect**:
   - Pequena mudança na entrada → grande mudança na saída

## 🔧 Funções Hash Avançadas

### 1. Multiplicative Hashing (Método de Knuth)

```
h(k) = ⌊m × (k × A mod 1)⌋
```

Onde A = (√5 - 1)/2 ≈ 0.6180339887 (razão áurea)

**Vantagens**:
- Independente do tamanho m
- Boa distribuição para muitos padrões de dados

### 2. Universal Hashing

Família de funções hash onde a probabilidade de colisão é ≤ 1/m:

```
h_{a,b}(k) = ((a × k + b) mod p) mod m
```

Onde:
- p é um primo maior que o universo U
- a ∈ {1, 2, ..., p-1}, b ∈ {0, 1, ..., p-1}

**Garantia**: Para quaisquer k₁ ≠ k₂:
```
Pr[h_{a,b}(k₁) = h_{a,b}(k₂)] ≤ 1/m
```

### 3. MurmurHash3

```c
uint32_t murmur3_32(const void *key, size_t len, uint32_t seed) {
    const uint32_t c1 = 0xcc9e2d51;
    const uint32_t c2 = 0x1b873593;
    const uint8_t *data = (const uint8_t *)key;
    uint32_t h1 = seed;
    // ... implementação
}
```

**Características**:
- Não criptográfico, muito rápido
- Excelente distribuição
- Usado em sistemas de produção (Redis, Cassandra)

### 4. xxHash

- Mais rápido que MurmurHash
- Qualidade de hash comparável
- Implementação otimizada para SIMD

## 🔄 Tratamento de Colisões Avançado

### 1. Cuckoo Hashing

**Conceito**: Usa duas (ou mais) funções hash e duas tabelas. Cada chave pode estar em uma de duas posições possíveis.

```
Inserir k:
    if T1[h1(k)] está vazio:
        T1[h1(k)] = k
    else if T2[h2(k)] está vazio:
        T2[h2(k)] = k
    else:
        // "Empurrar" elemento existente
        temp = T1[h1(k)]
        T1[h1(k)] = k
        INSERIR(temp)  // Recursivamente
```

**Complexidade**:
- Lookup: O(1) **pior caso** (não amortizado!)
- Insert: O(1) amortizado
- Fator de carga máximo: ~50% para 2 tabelas, maior com mais funções

**Problema**: Ciclos podem ocorrer → rehash necessário

### 2. Robin Hood Hashing

**Conceito**: Open addressing onde elementos "pobres" (longe de sua posição ideal) podem "roubar" posições de elementos "ricos".

```
Inserir k:
    probe = 0
    while true:
        pos = (h(k) + probe) mod m
        if T[pos] está vazio:
            T[pos] = (k, probe)
            return
        if probe > T[pos].probe:
            swap(k, T[pos].key)
            swap(probe, T[pos].probe)
        probe++
```

**Vantagens**:
- Reduz variância no tempo de busca
- Melhor uso de cache que chaining
- Permite fator de carga mais alto (~90%)

### 3. Hopscotch Hashing

**Conceito**: Combina linear probing com buckets virtuais de tamanho fixo H.

**Invariante**: Cada elemento está no máximo H-1 posições de sua posição hash

**Vantagens**:
- Excelente para concorrência
- Cache-friendly
- O(1) lookup com alta probabilidade

### 4. Swiss Table (Abseil/Google)

**Inovações**:
- SIMD para verificar múltiplos slots simultaneamente
- Metadata separado em bytes de controle
- Layout otimizado para cache

**Performance**:
- 2-3x mais rápido que std::unordered_map
- Menor uso de memória

## 📊 Análise de Performance

### Comparação de Métodos

| Método | Lookup (avg) | Lookup (worst) | Insert | Fator carga |
|--------|--------------|----------------|--------|-------------|
| Chaining | O(1 + α) | O(n) | O(1) | Sem limite |
| Linear Probing | O(1/(1-α)) | O(n) | O(1/(1-α)) | < 1 |
| Quadratic Probing | O(1/(1-α)) | O(n) | O(1/(1-α)) | < 0.5* |
| Double Hashing | O(1/(1-α)) | O(n) | O(1/(1-α)) | < 1 |
| Cuckoo | O(1) | O(1) | O(1)** | < 0.5 |
| Robin Hood | O(1) | O(log n) | O(1) | < 0.9 |
| Hopscotch | O(1) | O(H) | O(1) | < 0.9 |

*Requer m primo; **Amortizado

### Fórmulas de Performance

**Linear Probing** (Knuth, 1962):
- Busca bem-sucedida: ½(1 + 1/(1-α))
- Busca mal-sucedida: ½(1 + 1/(1-α)²)

**Chaining**:
- Busca bem-sucedida: 1 + α/2
- Busca mal-sucedida: α

## 🔒 Perfect Hashing

### Minimal Perfect Hash Function (MPHF)

Função hash sem colisões para conjunto estático de chaves:
- n chaves → n slots
- Busca em O(1) garantido
- Espaço: O(n) bits com algoritmos modernos (CHD, PTHash)

### Two-Level Hashing

Construção de Fredman, Komlós, e Szemerédi (1984):

**Nível 1**: Hash para buckets
**Nível 2**: Perfect hash dentro de cada bucket

**Espaço**: O(n)
**Tempo de construção**: O(n) esperado
**Lookup**: O(1) pior caso

## 🔐 Considerações de Segurança

### Hash Flooding Attack

**Problema**: Adversário pode gerar chaves que colidem, degradando O(1) para O(n)

**Soluções**:
1. **Randomização**: Seed aleatório na inicialização
2. **SipHash**: Função hash resistente a ataques, usada em Python 3.4+
3. **Treeification**: Java 8 HashMap converte buckets longos em árvores

### SipHash

```
PRF: {0,1}^64 × {0,1}^* → {0,1}^64
```

**Propriedades**:
- Resistente a ataques de colisão
- Mais lento que MurmurHash, mas seguro
- Default em Python, Ruby, Rust

## 🚀 Otimizações de Implementação

### 1. Power-of-2 Sizing

```c
// Usar AND ao invés de MOD
size_t index = hash & (table_size - 1);  // table_size = 2^k
```

### 2. Cache-Aware Layout

```c
// Separar metadata de valores
struct HashTable {
    uint8_t *control;   // 1 byte por slot
    Entry *entries;     // Valores separados
};
```

### 3. Prefetching

```c
__builtin_prefetch(&table[hash], 0, 1);
```

### 4. SIMD Lookup

```c
// Verificar 16 slots simultaneamente com SSE
__m128i pattern = _mm_set1_epi8(hash_byte);
__m128i matches = _mm_cmpeq_epi8(pattern, control);
int mask = _mm_movemask_epi8(matches);
```

## 📖 Referências Bibliográficas

1. **Pagh, R., & Rodler, F. F.** (2004). Cuckoo Hashing. *Journal of Algorithms*, 51(2), 122-144.

2. **Celis, P., Larson, P. A., & Munro, J. I.** (1985). Robin Hood Hashing. *FOCS*, 281-288.

3. **Herlihy, M., Shavit, N., & Tzafrir, M.** (2008). Hopscotch Hashing. *DISC*, 350-364.

4. **Fredman, M. L., Komlós, J., & Szemerédi, E.** (1984). Storing a Sparse Table with O(1) Worst Case Access Time. *JACM*, 31(3), 538-544.

5. **Aumasson, J. P., & Bernstein, D. J.** (2012). SipHash: A Fast Short-Input PRF. *INDOCRYPT*, 489-508.

6. **Kulukundis, M.** (2017). Designing a Fast, Efficient, Cache-friendly Hash Table. *CppCon*.

## 🔗 Navegação

← **[03-consistent-hashing](../03-consistent-hashing/)**: Consistent Hashing

→ **[05-arvore-binaria-busca-avancada](../05-arvore-binaria-busca-avancada/)**: Árvores Binárias de Busca Avançadas

---

*Este material faz parte do curso de Estrutura de Dados em C.*
