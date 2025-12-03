# Bloom Filter

## 📚 Definição Formal

Um **Bloom Filter** é uma estrutura de dados probabilística, space-efficient, usada para testar se um elemento é membro de um conjunto. Pode retornar **falsos positivos** (indicar que elemento está presente quando não está), mas **nunca falsos negativos**.

**Definição Formal**: Um Bloom Filter consiste em:
- Um bit array B de m bits, inicialmente todos 0
- k funções hash independentes h₁, h₂, ..., hₖ : U → {0, 1, ..., m-1}

## 🎓 Fundamentação Teórica

### Origem Histórica

- **Burton Howard Bloom (1970)**: Artigo seminal "Space/Time Trade-offs in Hash Coding with Allowable Errors"
- **Motivação original**: Verificação de hifenização em processadores de texto

### Propriedades Fundamentais

1. **Sem falsos negativos**: Se elemento está no conjunto, sempre retorna "possivelmente presente"
2. **Falsos positivos possíveis**: Pode indicar presença de elemento ausente
3. **Não permite deleção**: Na versão básica (ver Counting Bloom Filter)
4. **Espaço constante**: Tamanho independe do número de elementos armazenados

## 📊 Análise de Complexidade

| Operação | Complexidade |
|----------|--------------|
| Inserção | O(k) |
| Consulta | O(k) |
| Espaço | O(m) bits |

Onde k = número de funções hash, m = tamanho do bit array

### Taxa de Falso Positivo

Após inserir n elementos, a probabilidade de falso positivo é aproximadamente:

```
p ≈ (1 - e^(-kn/m))^k
```

### Parâmetros Ótimos

Para minimizar falsos positivos dado n elementos:

**Número ótimo de bits por elemento**:
```
m/n = -ln(p) / (ln(2))²  ≈ -1.44 × log₂(p)
```

**Número ótimo de funções hash**:
```
k = (m/n) × ln(2) ≈ 0.693 × (m/n)
```

### Tabela de Referência

| Taxa FP | Bits/elemento | k ótimo |
|---------|---------------|---------|
| 1% | 9.6 | 7 |
| 0.1% | 14.4 | 10 |
| 0.01% | 19.2 | 13 |
| 0.001% | 24.0 | 17 |

## 🔧 Implementação

### Estrutura de Dados

```c
typedef struct {
    uint8_t *bits;       // Bit array
    size_t size;         // Tamanho em bits
    size_t num_hashes;   // Número de funções hash
    size_t count;        // Elementos inseridos
} BloomFilter;
```

### Operações Fundamentais

```c
// Inserção
void bloom_add(BloomFilter *bf, const void *item, size_t len) {
    for (size_t i = 0; i < bf->num_hashes; i++) {
        size_t hash = hash_function(item, len, i);
        size_t index = hash % bf->size;
        bf->bits[index / 8] |= (1 << (index % 8));
    }
    bf->count++;
}

// Consulta
bool bloom_check(BloomFilter *bf, const void *item, size_t len) {
    for (size_t i = 0; i < bf->num_hashes; i++) {
        size_t hash = hash_function(item, len, i);
        size_t index = hash % bf->size;
        if (!(bf->bits[index / 8] & (1 << (index % 8)))) {
            return false;  // Definitivamente não está
        }
    }
    return true;  // Possivelmente está (pode ser FP)
}
```

### Técnica de Double Hashing

Usar apenas 2 funções hash para simular k:

```c
// h_i(x) = h_a(x) + i × h_b(x)
size_t hash_i(const void *item, size_t len, size_t i, size_t m) {
    size_t h1 = hash_a(item, len);
    size_t h2 = hash_b(item, len);
    return (h1 + i * h2) % m;
}
```

**Teorema** (Kirsch & Mitzenmacher, 2006): Double hashing tem mesma taxa de FP assintótica que k funções verdadeiramente independentes.

## 📐 Variantes

### 1. Counting Bloom Filter

Substitui bits por contadores, permitindo deleção:

```c
typedef struct {
    uint8_t *counters;  // 4 bits por contador (valores 0-15)
    size_t size;
    size_t num_hashes;
} CountingBloomFilter;

void cbf_remove(CountingBloomFilter *cbf, const void *item, size_t len) {
    for (size_t i = 0; i < cbf->num_hashes; i++) {
        size_t index = hash_function(item, len, i) % cbf->size;
        if (cbf->counters[index] > 0) {
            cbf->counters[index]--;
        }
    }
}
```

**Trade-off**: 4x mais espaço para suportar deleções

### 2. Scalable Bloom Filter

Cresce dinamicamente mantendo taxa de FP:

```c
typedef struct {
    BloomFilter **filters;  // Array de filtros
    size_t num_filters;
    double fp_rate;
    double tightening_ratio;  // r < 1, tipicamente 0.5
} ScalableBloomFilter;
```

**Propriedade**: Taxa FP total = Σᵢ p₀ × rⁱ < p₀/(1-r)

### 3. Partitioned Bloom Filter

Divide bit array em k partições (uma por função hash):

**Vantagem**: Melhor localidade de cache
**Desvantagem**: Taxa de FP ligeiramente maior

### 4. Cuckoo Filter

Alternativa moderna que suporta deleção eficiente:

- Armazena fingerprints em hash table com cuckoo hashing
- Suporta deleção
- Melhor espaço para FP < 3%

## 🎯 Aplicações Práticas

### 1. Cache Distribuído

**Problema**: Evitar cache miss para itens inexistentes
**Solução**: Bloom Filter como "gatekeeper"

```
CACHE_LOOKUP(key):
    if not bloom_filter.contains(key):
        return NOT_FOUND  // Evita acesso ao cache/DB
    return actual_cache_lookup(key)
```

### 2. Bancos de Dados

**Google BigTable, Apache Cassandra, LevelDB**:
- Evitar leituras de SSTable que não contêm a chave
- Economia significativa de I/O de disco

### 3. Redes e Segurança

**Detecção de URLs maliciosas (Chrome Safe Browsing)**:
- Lista de URLs maliciosas em Bloom Filter local
- Consulta servidor apenas para positivos

### 4. Deduplicação

**Sistemas de Backup**:
- Verificar rapidamente se chunk já foi armazenado
- Evitar armazenamento duplicado

### 5. Blockchain (Bitcoin)

**SPV (Simplified Payment Verification)**:
- Clientes leves enviam Bloom Filter de seus endereços
- Nós completos filtram transações relevantes

## ⚠️ Considerações de Projeto

### Quando Usar

✅ Usar Bloom Filter quando:
- Falsos positivos são aceitáveis
- Economia de espaço é crítica
- Consultas negativas são comuns
- Dados são inseridos mas não deletados

❌ Evitar quando:
- Falsos positivos são inaceitáveis
- Deleção é necessária (use Counting BF ou Cuckoo Filter)
- Precisão exata é requerida

### Dimensionamento

```python
# Calcular parâmetros ótimos
import math

def bloom_params(n, p):
    """
    n: número esperado de elementos
    p: taxa de falso positivo desejada
    """
    m = -n * math.log(p) / (math.log(2) ** 2)
    k = (m / n) * math.log(2)
    return int(m), int(round(k))

# Exemplo: 1 milhão de elementos, 1% FP
m, k = bloom_params(1_000_000, 0.01)
# m ≈ 9.6 milhões de bits ≈ 1.2 MB
# k ≈ 7 funções hash
```

## 📖 Referências Bibliográficas

1. **Bloom, B. H.** (1970). Space/Time Trade-offs in Hash Coding with Allowable Errors. *Communications of the ACM*, 13(7), 422-426.

2. **Broder, A., & Mitzenmacher, M.** (2004). Network Applications of Bloom Filters: A Survey. *Internet Mathematics*, 1(4), 485-509.

3. **Kirsch, A., & Mitzenmacher, M.** (2006). Less Hashing, Same Performance: Building a Better Bloom Filter. *ESA*, 456-467.

4. **Fan, B., Andersen, D. G., Kaminsky, M., & Mitzenmacher, M.** (2014). Cuckoo Filter: Practically Better Than Bloom. *CoNEXT*, 75-88.

5. **Tarkoma, S., Rothenberg, C. E., & Lagerspetz, E.** (2012). Theory and Practice of Bloom Filters for Distributed Systems. *IEEE Communications Surveys & Tutorials*, 14(1), 131-155.

## 🔗 Navegação

← **[08-tabela-lcp](../08-tabela-lcp/)**: Tabela LCP

→ **[10-count-min-sketch](../10-count-min-sketch/)**: Count-Min Sketch

---

*Este material faz parte do curso de Estrutura de Dados em C.*
