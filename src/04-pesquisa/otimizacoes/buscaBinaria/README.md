# Otimizações de Busca Binária

## 📋 Visão Geral

Este diretório contém várias implementações otimizadas e variações do algoritmo de busca binária, demonstrando técnicas avançadas para melhorar desempenho e expandir aplicações.

## 📚 Implementações Incluídas

### 1. buscaBinariaBranchlessBinarySearch.c
Implementação sem branches (condicionais) para melhor previsão de CPU.

**Conceito**: Elimina instruções de salto condicional, melhorando pipeline do processador.

**Vantagens:**
- Melhor performance em CPUs modernas
- Não sofre com branch misprediction
- Execução mais previsível

**Técnica:**
```c
int mid = (left + right) >> 1;
left = (arr[mid] < target) ? mid + 1 : left;
right = (arr[mid] >= target) ? mid : right;
```

### 2. buscaBinariaBuscaBinariaVetorial.c
Usa instruções SIMD (SSE/AVX) para processamento vetorial.

**Conceito**: Compara múltiplos elementos simultaneamente usando instruções vetoriais.

**Vantagens:**
- Speedup de 2-8x em hardware compatível
- Aproveita paralelismo do processador
- Eficiente para vetores grandes

### 3. buscaBinariaBuscaInterpolada.c
Combina busca binária com busca interpolada.

**Conceito**: Usa interpolação quando apropriado, fallback para binária caso contrário.

**Vantagens:**
- O(log log n) para dados uniformes
- Robusta para distribuições irregulares
- Melhor que binária pura em muitos casos

### 4. buscaBinariaDominioContinuos.c
Busca binária adaptada para funções contínuas.

**Conceito**: Encontra raízes ou valores em funções matemáticas contínuas.

**Aplicações:**
- Encontrar zeros de funções
- Otimização numérica
- Cálculo de inversas de funções monotônicas

**Exemplo:**
```c
// Encontrar x tal que f(x) = 0
double busca_funcao(double (*f)(double), double a, double b, double epsilon) {
    while (b - a > epsilon) {
        double mid = (a + b) / 2.0;
        if (f(mid) == 0) return mid;
        if (f(a) * f(mid) < 0)
            b = mid;
        else
            a = mid;
    }
    return (a + b) / 2.0;
}
```

### 5. buscaBinariaEstimativaInicial.c
Otimiza com estimativa inteligente do ponto inicial.

**Conceito**: Usa heurísticas para começar a busca mais próximo do alvo.

**Vantagens:**
- Menos iterações em média
- Bom para dados com padrões conhecidos
- Combina conhecimento do domínio

### 6. buscaBinariaPrevenirOverflow.c
Implementação segura que evita overflow aritmético.

**Problema**: `(left + right) / 2` pode causar overflow se left + right > INT_MAX

**Solução:**
```c
// ERRADO - pode overflow
int mid = (left + right) / 2;

// CORRETO - previne overflow
int mid = left + (right - left) / 2;

// ALTERNATIVA - bit shift (apenas para não-negativos)
int mid = (left + right) >>> 1;
```

### 7. buscaBinariaTernaria.c
Busca ternária - divide em 3 partes ao invés de 2.

**Conceito**: Usa dois pontos médios por iteração.

**Complexidade**: O(log₃ n) ≈ 0.63 × O(log₂ n)

**Quando usar:**
- Funções unimodais (um único máximo/mínimo)
- Otimização de funções convexas/côncavas
- Comparações muito caras

**Algoritmo:**
```c
while (right - left > epsilon) {
    int mid1 = left + (right - left) / 3;
    int mid2 = right - (right - left) / 3;
    
    if (f(mid1) < f(mid2))
        left = mid1;
    else
        right = mid2;
}
```

## 🔧 Compilação

### Básico
```bash
gcc -Wall -Wextra -std=c99 -O3 -o binaria buscaBinariaPrevenirOverflow.c
```

### Com SIMD (requer CPU compatível)
```bash
gcc -Wall -Wextra -std=c99 -O3 -mavx2 -o vetorial buscaBinariaBuscaBinariaVetorial.c
```

### Com otimizações máximas
```bash
gcc -Wall -Wextra -std=c99 -O3 -march=native -o binaria_opt *.c
```

## 📊 Análise de Performance

### Comparações por Busca (n = 1.000.000)

| Variante | Comparações | Tempo Relativo |
|----------|-------------|----------------|
| Binária Padrão | ~20 | 1.0x |
| Branchless | ~20 | 0.85x |
| Vetorial (AVX) | ~20 | 0.3x |
| Ternária | ~13 | 1.1x |
| Interpolada (uniforme) | ~5 | 0.6x |

**Nota**: Tempos relativos dependem de hardware e distribuição de dados.

## 💡 Escolhendo a Variante Correta

### Busca Binária Padrão
✅ Casos gerais, código legível, manutenível

### Branchless
✅ Performance crítica, CPUs modernas, dados aleatórios

### Vetorial
✅ Vetores muito grandes, hardware SIMD disponível, múltiplas buscas

### Ternária
✅ Otimização de funções, comparações caras, busca de extremos

### Interpolada Híbrida
✅ Dados aproximadamente uniformes, vetores grandes

### Prevenção Overflow
✅ Sempre use! Custo zero com benefício de segurança

### Domínio Contínuo
✅ Funções matemáticas, análise numérica

## ⚠️ Considerações

### Branch Prediction
- CPUs modernas preveem branches com ~95% acurácia
- Branchless só vale para dados muito aleatórios

### SIMD
- Requer alinhamento de memória
- Pode ser mais lento para vetores pequenos (n < 1000)
- Portabilidade limitada

### Busca Ternária
- Mais comparações por iteração que binária
- Só vale se comparações são O(1) e muito rápidas

### Interpolação
- Péssima para dados não-uniformes
- Pode degenerar para O(n)

## 🚀 Técnicas Avançadas

### Prefetching
```c
__builtin_prefetch(&arr[mid + 32], 0, 1);
```

### Múltiplos Pivôs
```c
// Busca com 4 pivôs
int p1 = left + (right - left) / 5;
int p2 = left + 2 * (right - left) / 5;
int p3 = left + 3 * (right - left) / 5;
int p4 = left + 4 * (right - left) / 5;
```

### Loop Fusion
Combinar múltiplas buscas em um único loop.

## 📚 Recursos

- [Binary Search Variations](https://en.wikipedia.org/wiki/Binary_search_algorithm)
- [Ternary Search](https://en.wikipedia.org/wiki/Ternary_search)
- [SIMD Instructions](https://software.intel.com/sites/landingpage/IntrinsicsGuide/)
- [Branch Prediction](https://en.wikipedia.org/wiki/Branch_predictor)

---

**Repositório**: https://github.com/profluiscaparroz/estrutura-dados-c
