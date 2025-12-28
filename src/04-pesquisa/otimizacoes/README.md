# Otimizações de Algoritmos de Busca

## 📋 Visão Geral

Este diretório contém implementações otimizadas de algoritmos de busca, demonstrando técnicas avançadas para melhorar o desempenho de operações de pesquisa em vetores.

## 📁 Estrutura

### Subdiretórios

- **buscaBinaria/** - Variações e otimizações da busca binária
- **buscaInterpolada/** - Implementação de busca interpolada
- **buscaLinear/** - Otimizações da busca linear

## 🎯 Algoritmos Implementados

### Busca Linear (Linear Search)
- **Complexidade**: O(n)
- **Aplicação**: Vetores não ordenados
- **Otimizações**: Sentinela, SIMD, multithreading, loop unrolling

### Busca Binária (Binary Search)
- **Complexidade**: O(log n)
- **Aplicação**: Vetores ordenados
- **Otimizações**: Branchless, vetorial, prevenção de overflow, busca ternária

### Busca Interpolada (Interpolation Search)
- **Complexidade**: O(log log n) caso médio, O(n) pior caso
- **Aplicação**: Vetores ordenados com distribuição uniforme
- **Vantagem**: Mais rápida que busca binária para dados uniformemente distribuídos

## 📊 Comparação de Desempenho

| Algoritmo | Melhor Caso | Caso Médio | Pior Caso | Espaço | Pré-requisito |
|-----------|------------|------------|-----------|--------|---------------|
| **Linear** | O(1) | O(n) | O(n) | O(1) | Nenhum |
| **Linear com Sentinela** | O(1) | O(n) | O(n) | O(1) | Nenhum |
| **Binária** | O(1) | O(log n) | O(log n) | O(1) | Ordenado |
| **Interpolada** | O(1) | O(log log n) | O(n) | O(1) | Ordenado + Uniforme |
| **Ternária** | O(1) | O(log₃ n) | O(log₃ n) | O(1) | Ordenado |

## 🔧 Compilação

```bash
# Compilar exemplos de busca binária
cd buscaBinaria
gcc -Wall -Wextra -std=c99 -O3 -o binaria *.c

# Compilar exemplos de busca linear
cd ../buscaLinear
gcc -Wall -Wextra -std=c99 -O3 -o linear *.c -pthread

# Compilar busca interpolada
cd ../buscaInterpolada
gcc -Wall -Wextra -std=c99 -O3 -o interpolada *.c
```

## 💡 Quando Usar Cada Algoritmo

### Busca Linear
✅ **Use quando:**
- Vetor não está ordenado
- Vetor é pequeno (n < 100)
- Dados não são acessados frequentemente
- Simplicidade é prioritária

❌ **Evite quando:**
- Vetor é grande e ordenado
- Buscas são frequentes
- Performance é crítica

### Busca Binária
✅ **Use quando:**
- Vetor está ordenado
- Buscas são frequentes
- Tamanho do vetor é moderado a grande
- Inserções/remoções são raras

❌ **Evite quando:**
- Vetor não está ordenado (custo de ordenação pode não compensar)
- Dados têm distribuição uniforme (interpolada pode ser melhor)

### Busca Interpolada
✅ **Use quando:**
- Vetor está ordenado
- Dados têm distribuição aproximadamente uniforme
- Vetor é muito grande
- Buscas são extremamente frequentes

❌ **Evite quando:**
- Distribuição de dados é irregular
- Dados têm clusters ou gaps
- Vetor é pequeno

## 🚀 Técnicas de Otimização

### 1. Sentinela (Sentinel)
Elimina verificação de limites em cada iteração.

```c
int busca_sentinela(int arr[], int n, int x) {
    int ultimo = arr[n-1];
    arr[n-1] = x;
    int i = 0;
    while (arr[i] != x) i++;
    arr[n-1] = ultimo;
    return (i < n-1 || arr[n-1] == x) ? i : -1;
}
```

### 2. Loop Unrolling
Reduz overhead de controle do loop.

```c
for (int i = 0; i < n; i += 4) {
    if (arr[i] == x) return i;
    if (arr[i+1] == x) return i+1;
    if (arr[i+2] == x) return i+2;
    if (arr[i+3] == x) return i+3;
}
```

### 3. Branchless Binary Search
Elimina branches condicionais.

```c
int mid = left + (right - left) / 2;
left = (arr[mid] < x) ? mid + 1 : left;
right = (arr[mid] >= x) ? mid : right;
```

### 4. SIMD (Single Instruction Multiple Data)
Processa múltiplos elementos simultaneamente.

### 5. Prevenção de Overflow
```c
// ERRADO (pode overflow)
int mid = (left + right) / 2;

// CORRETO
int mid = left + (right - left) / 2;
```

## 📖 Conceitos Avançados

### Busca Ternária
Divide o intervalo em três partes ao invés de duas.

**Complexidade**: O(log₃ n)  
**Comparações**: Reduz comparações em ~11% vs binária

### Busca em Domínio Contínuo
Busca binária adaptada para funções contínuas.

**Aplicação**: Encontrar raízes de funções, otimização

### Busca Vetorial
Usa instruções vetoriais (SSE, AVX) para paralelismo.

**Speedup**: 2-8x dependendo do hardware

## ⚠️ Considerações Importantes

### Cache Locality
- Busca linear tem melhor cache locality
- Para vetores pequenos, pode ser mais rápida que binária

### Branch Prediction
- Branches previsíveis melhoram performance
- Branchless pode ser mais lento em CPUs antigas

### Overhead de Paralelização
- Multithreading só compensa para vetores grandes
- Overhead de criação de threads pode superar ganhos

## 📚 Recursos Adicionais

- [Binary Search Variations](https://en.wikipedia.org/wiki/Binary_search_algorithm)
- [Interpolation Search](https://en.wikipedia.org/wiki/Interpolation_search)
- [SIMD Programming](https://en.wikipedia.org/wiki/SIMD)
- [Branch Prediction](https://en.wikipedia.org/wiki/Branch_predictor)

## 🔗 Navegação

Para aprender sobre otimizações de busca:

1. Comece com **buscaLinear/** para entender otimizações básicas
2. Estude **buscaBinaria/** para técnicas avançadas
3. Explore **buscaInterpolada/** para casos especiais

---

**Repositório**: https://github.com/profluiscaparroz/estrutura-dados-c
