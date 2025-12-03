# HyperLogLog

## 📚 Definição Formal

**HyperLogLog** (HLL) é um algoritmo probabilístico para estimativa de **cardinalidade** (contagem de elementos distintos) em grandes conjuntos de dados, utilizando espaço sublinear. É uma melhoria do algoritmo LogLog de Durand e Flajolet.

**Definição Formal**: O HyperLogLog usa:
- m = 2^b registradores (buckets), onde b ∈ {4, 5, ..., 16}
- Uma função hash h: U → {0, 1}^L (tipicamente L = 64 bits)
- Cada registrador armazena o máximo número de zeros consecutivos + 1

## 🎓 Fundamentação Teórica

### Origem Histórica

- **Flajolet, Fusy, Gandouet, & Meunier (2007)**: Artigo seminal "HyperLogLog: the analysis of a near-optimal cardinality estimation algorithm"
- **Evolução**: Linear Counting → LogLog → SuperLogLog → HyperLogLog

### Insight Fundamental

**Observação-chave**: Em uma sequência de n bits aleatórios uniformes, o padrão 0^k1 (k zeros seguidos de um 1) aparece com probabilidade 2^(-k-1).

Se observamos k zeros iniciais, estimamos que vimos aproximadamente 2^k valores distintos.

### Estimador Base

Para um registrador com máximo de zeros observado = M:

```
E[cardinalidade] ≈ 2^M × constante_de_correção
```

## 📊 Análise de Complexidade

| Operação | Complexidade |
|----------|--------------|
| Add | O(1) |
| Estimate | O(m) |
| Merge | O(m) |
| Espaço | O(m) ≈ O(1/ε²) |

### Precisão

Com m = 2^b registradores:
- Erro padrão relativo: σ ≈ 1.04 / √m

| Registradores (m) | Bits (b) | Espaço | Erro padrão |
|-------------------|----------|--------|-------------|
| 16 | 4 | 48 bytes | 26% |
| 64 | 6 | 192 bytes | 13% |
| 256 | 8 | 768 bytes | 6.5% |
| 1024 | 10 | 3 KB | 3.25% |
| 4096 | 12 | 12 KB | 1.625% |
| 16384 | 14 | 48 KB | 0.81% |
| 65536 | 16 | 192 KB | 0.40% |

## 🔧 Implementação

### Estrutura de Dados

```c
typedef struct {
    uint8_t *registers;  // Array de m registradores
    uint8_t b;           // log2(m)
    uint32_t m;          // Número de registradores
    double alpha_m;      // Constante de correção
} HyperLogLog;
```

### Constantes de Correção

```c
double alpha(uint32_t m) {
    switch(m) {
        case 16:  return 0.673;
        case 32:  return 0.697;
        case 64:  return 0.709;
        default:  return 0.7213 / (1 + 1.079 / m);
    }
}
```

### Operações Fundamentais

```c
// Adicionar elemento
void hll_add(HyperLogLog *hll, const void *item, size_t len) {
    uint64_t hash = hash64(item, len);
    
    // Primeiros b bits determinam o registrador
    uint32_t idx = hash >> (64 - hll->b);
    
    // Contar zeros nos bits restantes
    uint64_t w = hash << hll->b;
    uint8_t rho = (w == 0) ? (64 - hll->b) + 1 : __builtin_clzll(w) + 1;
    
    // Atualizar máximo
    if (rho > hll->registers[idx]) {
        hll->registers[idx] = rho;
    }
}

// Estimar cardinalidade
double hll_estimate(HyperLogLog *hll) {
    // Média harmônica dos 2^M[j]
    double sum = 0.0;
    int zeros = 0;
    
    for (uint32_t j = 0; j < hll->m; j++) {
        sum += pow(2.0, -hll->registers[j]);
        if (hll->registers[j] == 0) zeros++;
    }
    
    double E = hll->alpha_m * hll->m * hll->m / sum;
    
    // Correções para small/large range
    if (E <= 2.5 * hll->m && zeros > 0) {
        // Small range correction (Linear Counting)
        E = hll->m * log((double)hll->m / zeros);
    } else if (E > (1.0/30.0) * pow(2, 64)) {
        // Large range correction
        E = -pow(2, 64) * log(1 - E / pow(2, 64));
    }
    
    return E;
}

// Merge dois HLLs
void hll_merge(HyperLogLog *dst, HyperLogLog *src) {
    for (uint32_t i = 0; i < dst->m; i++) {
        if (src->registers[i] > dst->registers[i]) {
            dst->registers[i] = src->registers[i];
        }
    }
}
```

## 📐 Variantes e Otimizações

### 1. HyperLogLog++ (Google, 2013)

Melhorias sobre HLL original:
- **Bias Correction**: Correção empírica para estimativas pequenas
- **Sparse Representation**: Economia de espaço para cardinalidades pequenas
- **64-bit Hash**: Evita problemas com hash de 32 bits

```c
typedef struct {
    // Modo sparse: lista de pares (índice, valor)
    uint32_t *sparse_data;
    size_t sparse_size;
    
    // Modo denso: array tradicional
    uint8_t *registers;
    
    bool is_sparse;
    uint32_t m;
} HyperLogLogPlusPlus;
```

### 2. Streaming HLL

Para processamento de streams:
- Sliding window HLL
- Time-decayed HLL

### 3. HLL com Set Operations

```c
// União: merge
double hll_union_cardinality(HyperLogLog *a, HyperLogLog *b) {
    HyperLogLog merged = hll_clone(a);
    hll_merge(&merged, b);
    return hll_estimate(&merged);
}

// Interseção (estimativa via inclusão-exclusão)
double hll_intersection_cardinality(HyperLogLog *a, HyperLogLog *b) {
    double card_a = hll_estimate(a);
    double card_b = hll_estimate(b);
    double card_union = hll_union_cardinality(a, b);
    return card_a + card_b - card_union;
}
```

## 🎯 Aplicações Práticas

### 1. Analytics em Tempo Real

**Contagem de Usuários Únicos**:
- Visitantes únicos por página
- DAU/MAU (Daily/Monthly Active Users)
- Unique IPs

**Exemplo**: Redis implementa HLL nativamente

```redis
PFADD visitors user123 user456 user789
PFCOUNT visitors  # Retorna estimativa
PFMERGE all_visitors page1_visitors page2_visitors
```

### 2. Bancos de Dados

**PostgreSQL, ClickHouse, Presto**:
- `COUNT(DISTINCT column)` aproximado
- Reduz tempo de query de horas para segundos

### 3. Detecção de DDoS

**Network Monitoring**:
- Contar IPs únicos por minuto
- Detectar spikes de cardinalidade

### 4. Deduplicação

**Estimativa de Dedup Ratio**:
- Antes de deduplicar, estimar economia
- Decisão de custo-benefício

### 5. Análise de Grafos

**Reachability Queries**:
- HLL por vértice para estimar alcançabilidade
- Diâmetro aproximado de grafos

## 🔄 Comparação com Alternativas

| Método | Espaço | Erro | Operações |
|--------|--------|------|-----------|
| HashMap (exato) | O(n) | 0 | Add, Count |
| Bitmap | O(max_value) | 0 | Add, Count |
| Linear Counting | O(n/8) | ~1% | Add, Count |
| LogLog | O(log log n) | ~5% | Add, Count |
| HyperLogLog | O(log log n) | ~1-2% | Add, Count, Merge |
| HLL++ | O(log log n) | ~0.5% | Add, Count, Merge |

### Quando Usar Cada Um

| Cenário | Recomendação |
|---------|--------------|
| Cardinalidade exata | HashMap/Set |
| Espaço crítico, baixa cardinalidade | Linear Counting |
| Uso geral | HyperLogLog |
| Alta precisão | HyperLogLog++ |
| Operações de conjunto | MinHash |

## ⚠️ Limitações

1. **Estimativa, não exata**: Não adequado quando precisão exata é necessária
2. **Apenas cardinalidade**: Não suporta queries de membership
3. **Merge apenas monotônico**: Não pode "remover" elementos
4. **Erro sistemático para valores pequenos**: Requer correções

## 📖 Referências Bibliográficas

1. **Flajolet, P., Fusy, É., Gandouet, O., & Meunier, F.** (2007). HyperLogLog: the analysis of a near-optimal cardinality estimation algorithm. *DMTCS Proceedings*, 137-156.

2. **Heule, S., Nunkesser, M., & Hall, A.** (2013). HyperLogLog in Practice: Algorithmic Engineering of a State of The Art Cardinality Estimation Algorithm. *EDBT*, 683-692.

3. **Durand, M., & Flajolet, P.** (2003). Loglog Counting of Large Cardinalities. *ESA*, 605-617.

4. **Flajolet, P., & Martin, G. N.** (1985). Probabilistic Counting Algorithms for Data Base Applications. *JCSS*, 31(2), 182-209.

5. **Ertl, O.** (2017). New cardinality estimation algorithms for HyperLogLog sketches. *arXiv:1702.01284*.

## 🔗 Navegação

← **[10-count-min-sketch](../10-count-min-sketch/)**: Count-Min Sketch

→ **[12-treap](../12-treap/)**: Treap

---

*Este material faz parte do curso de Estrutura de Dados em C.*
