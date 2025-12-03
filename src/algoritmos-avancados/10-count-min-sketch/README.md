# Count-Min Sketch

## 📚 Definição Formal

O **Count-Min Sketch** (CM Sketch) é uma estrutura de dados probabilística sublinear que permite estimar a frequência de elementos em um stream de dados. Introduz apenas superestimação (nunca subestima), tornando-o útil para aplicações onde upper bounds são aceitáveis.

**Definição Formal**: Um Count-Min Sketch consiste em:
- Uma matriz de contadores C[d][w] de d linhas e w colunas
- d funções hash independentes h₁, h₂, ..., hₐ : U → {0, 1, ..., w-1}

## 🎓 Fundamentação Teórica

### Origem Histórica

- **Cormode & Muthukrishnan (2005)**: Artigo "An Improved Data Stream Summary: The Count-Min Sketch and its Applications"
- **Motivação**: Processamento de streams de dados em tempo real com memória limitada

### Propriedades Fundamentais

1. **Sublinear Space**: Espaço O(d × w) independente do número de elementos
2. **Streaming Model**: Processa elementos one-pass
3. **Merge-able**: Sketches podem ser combinados (adição elemento a elemento)
4. **Upper Bound**: Sempre retorna ≥ frequência real

## 📊 Análise de Complexidade

| Operação | Complexidade |
|----------|--------------|
| Update (inserção/incremento) | O(d) |
| Query (estimativa) | O(d) |
| Espaço | O(d × w) |

### Garantia de Erro

Com probabilidade ≥ 1 - δ, para qualquer elemento x:

```
f̂(x) ≤ f(x) + ε × ‖f‖₁
```

Onde:
- f̂(x) = frequência estimada
- f(x) = frequência real
- ε = parâmetro de erro
- ‖f‖₁ = soma de todas frequências (total de elementos)
- δ = probabilidade de falha

### Parâmetros Ótimos

```
w = ⌈e/ε⌉      (largura)
d = ⌈ln(1/δ)⌉  (profundidade)
```

Onde e ≈ 2.718 é a constante de Euler.

**Exemplo**:
- ε = 0.001 (erro de 0.1%)
- δ = 0.01 (99% de confiança)
- w = 2719, d = 5
- Espaço: ~54KB com contadores de 4 bytes

## 🔧 Implementação

### Estrutura de Dados

```c
typedef struct {
    int **counts;      // Matriz d × w
    size_t width;      // w
    size_t depth;      // d
    size_t total;      // Total de elementos inseridos
} CountMinSketch;
```

### Operações Fundamentais

```c
// Inicialização
CountMinSketch* cms_create(double epsilon, double delta) {
    CountMinSketch *cms = malloc(sizeof(CountMinSketch));
    cms->width = (size_t)ceil(M_E / epsilon);
    cms->depth = (size_t)ceil(log(1.0 / delta));
    cms->counts = calloc(cms->depth, sizeof(int*));
    for (size_t i = 0; i < cms->depth; i++) {
        cms->counts[i] = calloc(cms->width, sizeof(int));
    }
    cms->total = 0;
    return cms;
}

// Update (adicionar elemento com contagem c)
void cms_update(CountMinSketch *cms, const void *item, size_t len, int c) {
    for (size_t i = 0; i < cms->depth; i++) {
        size_t j = hash(item, len, i) % cms->width;
        cms->counts[i][j] += c;
    }
    cms->total += c;
}

// Query (estimar frequência)
int cms_estimate(CountMinSketch *cms, const void *item, size_t len) {
    int min_count = INT_MAX;
    for (size_t i = 0; i < cms->depth; i++) {
        size_t j = hash(item, len, i) % cms->width;
        if (cms->counts[i][j] < min_count) {
            min_count = cms->counts[i][j];
        }
    }
    return min_count;
}
```

### Merge de Sketches

```c
void cms_merge(CountMinSketch *dst, CountMinSketch *src) {
    for (size_t i = 0; i < dst->depth; i++) {
        for (size_t j = 0; j < dst->width; j++) {
            dst->counts[i][j] += src->counts[i][j];
        }
    }
    dst->total += src->total;
}
```

## 📐 Variantes e Otimizações

### 1. Conservative Update

Reduz superestimação incrementando apenas o mínimo:

```c
void cms_conservative_update(CountMinSketch *cms, const void *item, 
                              size_t len, int c) {
    int min_count = cms_estimate(cms, item, len);
    for (size_t i = 0; i < cms->depth; i++) {
        size_t j = hash(item, len, i) % cms->width;
        cms->counts[i][j] = MAX(cms->counts[i][j], min_count + c);
    }
    cms->total += c;
}
```

### 2. Count-Min-Log Sketch

Usa contadores logarítmicos para economizar espaço:
- Contador de 8 bits representa valores até 2^255
- Trade-off: maior erro para valores altos

### 3. Augmented Sketch

Mantém heap dos top-k elementos exatos:

```c
typedef struct {
    CountMinSketch *sketch;
    MinHeap *topk;          // Top-k elementos
    size_t k;
} AugmentedSketch;
```

## 🎯 Aplicações Práticas

### 1. Heavy Hitters (Elementos Frequentes)

Encontrar elementos com frequência > θ × n:

```c
typedef struct {
    char *item;
    int count;
} HeavyHitter;

HeavyHitter* find_heavy_hitters(CountMinSketch *cms, 
                                 double threshold,
                                 size_t *num_hh) {
    // Usar heap para manter candidatos
    // Verificar estimativa vs threshold × total
    ...
}
```

**Aplicação**: Trending topics, popular searches

### 2. Detecção de Anomalias em Rede

**Network Flow Monitoring**:
- Contar pacotes por IP/porta
- Detectar DDoS (IPs com frequência anormal)

### 3. Consultas de Range em Streams

**Dyadic Intervals**:
- Manter múltiplos sketches para diferentes granularidades
- Responder queries como "quantos eventos entre t₁ e t₂"

### 4. Sistemas de Recomendação

**Click-Through Rate Estimation**:
- Estimar CTR para milhões de ads/páginas
- Personalização em tempo real

### 5. Banco de Dados

**Query Optimization**:
- Estimar seletividade de predicados
- Cardinalidade de joins

## 🔄 Comparação com Outras Estruturas

| Estrutura | Operação | Garantia | Espaço |
|-----------|----------|----------|--------|
| HashMap | Exato | Sem erro | O(n) |
| Count-Min Sketch | Frequência | Superestima | O(1/ε × log(1/δ)) |
| Count Sketch | Frequência | Estimativa não-viesada | O(1/ε² × log(1/δ)) |
| HyperLogLog | Cardinalidade | ±1.04/√m | O(m) |
| Bloom Filter | Membership | Falsos positivos | O(n/ln 2) |

### Count-Min vs Count Sketch

| Aspecto | Count-Min Sketch | Count Sketch |
|---------|------------------|--------------|
| Erro | Sempre superestima | Média não-viesada |
| Contadores | Não-negativos | Pode ser negativo |
| Heavy Hitters | ✓ | ✓ (via mediana) |
| Range Queries | ✓ | Mais complexo |
| Point Queries | Min across rows | Mediana |

## ⚠️ Limitações e Considerações

### Limitações

1. **Apenas superestimação**: Não adequado quando subestimação é necessária
2. **Não suporta deleção**: Versão básica (ver Count-Min-Cu com contadores de saturação)
3. **Dependência do total**: Erro proporcional ao ‖f‖₁

### Quando Usar

✅ Usar Count-Min Sketch quando:
- Processando streams de dados
- Upper bounds são aceitáveis
- Memória é limitada
- Heavy hitters são o objetivo

❌ Evitar quando:
- Precisão exata é necessária
- Subestimação seria problemática
- Deleções são frequentes

## 📖 Referências Bibliográficas

1. **Cormode, G., & Muthukrishnan, S.** (2005). An Improved Data Stream Summary: The Count-Min Sketch and its Applications. *Journal of Algorithms*, 55(1), 58-75.

2. **Charikar, M., Chen, K., & Farach-Colton, M.** (2002). Finding Frequent Items in Data Streams. *ICALP*, 693-703.

3. **Goyal, A., Daumé III, H., & Cormode, G.** (2012). Sketch Algorithms for Estimating Point Queries in NLP. *EMNLP*, 1093-1103.

4. **Cormode, G.** (2009). Count-Min Sketch. *Encyclopedia of Database Systems*, 511-516.

5. **Estan, C., & Varghese, G.** (2002). New Directions in Traffic Measurement and Accounting. *SIGCOMM*, 323-336.

## 🔗 Navegação

← **[09-bloomfilter](../09-bloomfilter/)**: Bloom Filter

→ **[11-hyperloglog](../11-hyperloglog/)**: HyperLogLog

---

*Este material faz parte do curso de Estrutura de Dados em C.*
