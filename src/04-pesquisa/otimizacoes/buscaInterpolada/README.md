# Busca Interpolada

## 📋 Visão Geral

Este diretório contém implementação do algoritmo de busca interpolada (Interpolation Search), uma variação da busca binária que é mais eficiente para dados uniformemente distribuídos.

## 📚 Arquivo Incluído

### buscaInterpolada.c
Implementação completa da busca interpolada com exemplos de uso.

## 🎯 O que é Busca Interpolada?

A busca interpolada é um algoritmo de busca que melhora a busca binária tentando estimar a posição provável do elemento alvo com base em sua distribuição.

### Analogia
Imagine procurar uma palavra no dicionário:
- Se procura "Zebra", você abre próximo ao fim (não no meio)
- Se procura "Apple", você abre próximo ao início
- Busca interpolada funciona da mesma forma!

## 📊 Complexidade

| Caso | Complexidade |
|------|-------------|
| **Melhor** | O(1) |
| **Médio** (dados uniformes) | O(log log n) |
| **Pior** (dados não-uniformes) | O(n) |
| **Espaço** | O(1) |

## 💡 Algoritmo

### Fórmula de Interpolação

```c
pos = low + ((target - arr[low]) * (high - low)) / (arr[high] - arr[low])
```

**Intuição**: Estima a posição com base na proporção dos valores.

### Pseudocódigo

```
função busca_interpolada(arr, n, target):
    low = 0
    high = n - 1
    
    enquanto low <= high e target >= arr[low] e target <= arr[high]:
        // Caso especial: evitar divisão por zero
        se arr[low] == arr[high]:
            se arr[low] == target:
                retornar low
            senão:
                retornar -1
        
        // Calcular posição interpolada
        pos = low + ((target - arr[low]) * (high - low)) / (arr[high] - arr[low])
        
        se arr[pos] == target:
            retornar pos
        
        se arr[pos] < target:
            low = pos + 1
        senão:
            high = pos - 1
    
    retornar -1  // Não encontrado
```

## 🔧 Implementação em C

```c
int busca_interpolada(int arr[], int n, int target) {
    int low = 0;
    int high = n - 1;
    
    while (low <= high && target >= arr[low] && target <= arr[high]) {
        // Evitar divisão por zero
        if (arr[low] == arr[high]) {
            return (arr[low] == target) ? low : -1;
        }
        
        // Calcular posição interpolada
        int pos = low + (((double)(high - low) / (arr[high] - arr[low])) 
                         * (target - arr[low]));
        
        // Verificar se encontrou
        if (arr[pos] == target) {
            return pos;
        }
        
        // Ajustar intervalo
        if (arr[pos] < target) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }
    
    return -1;  // Não encontrado
}
```

## 📖 Comparação com Busca Binária

### Busca Binária
- Sempre divide no meio: `mid = (low + high) / 2`
- Complexidade: O(log n)
- Funciona bem para qualquer distribuição ordenada
- Previsível e consistente

### Busca Interpolada
- Estima posição: `pos = low + proporção * (high - low)`
- Complexidade: O(log log n) caso médio
- Requer distribuição aproximadamente uniforme
- Performance varia com os dados

## ⚡ Quando Usar

### ✅ Use Busca Interpolada quando:

1. **Dados uniformemente distribuídos**
   - Exemplo: IDs sequenciais, timestamps, preços em centavos
   
2. **Vetor muito grande (n > 10.000)**
   - Ganhos compensam overhead do cálculo
   
3. **Acesso frequente aos dados**
   - Amortiza custo de análise de distribuição

### ❌ Evite quando:

1. **Distribuição irregular**
   - Clusters de valores
   - Grandes gaps
   - Pode degenerar para O(n)

2. **Vetor pequeno (n < 1000)**
   - Overhead não compensa
   - Busca binária simples é suficiente

3. **Dados não-numéricos**
   - Precisa de mapeamento numérico

## 📊 Exemplo de Performance

### Dados Uniformes (melhor caso)

```
Tamanho do vetor: 1.000.000
Distribuição: Uniforme [0, 10.000.000]

Busca Binária:        ~20 comparações
Busca Interpolada:    ~5 comparações

Speedup: 4x
```

### Dados Não-Uniformes (pior caso)

```
Tamanho do vetor: 1.000.000
Distribuição: [1, 2, 3, ..., 1000, 1.000.000]
                (999 valores pequenos, 1 grande)

Busca Binária:        ~20 comparações
Busca Interpolada:    ~999 comparações

Slowdown: 50x
```

## ⚠️ Cuidados Importantes

### 1. Overflow
```c
// CUIDADO: pode causar overflow
int pos = low + ((target - arr[low]) * (high - low)) / (arr[high] - arr[low]);

// MELHOR: usar double para cálculo
int pos = low + (int)(((double)(target - arr[low]) / (arr[high] - arr[low])) 
                      * (high - low));
```

### 2. Divisão por Zero
```c
if (arr[low] == arr[high]) {
    // Tratar caso especial
}
```

### 3. Limites
```c
// Sempre verificar que pos está dentro dos limites
if (pos < low) pos = low;
if (pos > high) pos = high;
```

## 🚀 Otimizações

### Híbrida com Busca Binária
```c
// Usar interpolada para primeiras iterações
// Depois mudar para binária
if (high - low > THRESHOLD) {
    // interpolação
} else {
    // busca binária
}
```

### Análise de Distribuição
```c
// Verificar uniformidade antes de decidir
double uniformidade = analisar_distribuicao(arr, n);
if (uniformidade > 0.8) {
    busca_interpolada(...);
} else {
    busca_binaria(...);
}
```

## 📈 Análise Matemática

### Por que O(log log n)?

Para dados uniformemente distribuídos:
- Cada iteração reduz intervalo exponencialmente
- Redução: `n → √n → √√n → ...`
- Número de iterações: log₂(log₂(n))

### Exemplo
```
n = 1.000.000 = 10⁶

Busca Binária:    log₂(10⁶) ≈ 20 iterações
Busca Interpolada: log₂(log₂(10⁶)) ≈ 4-5 iterações
```

## 🔧 Compilação

```bash
gcc -Wall -Wextra -std=c99 -O3 -o interpolada buscaInterpolada.c
./interpolada
```

## 📚 Aplicações Práticas

1. **Banco de Dados**: Índices de timestamps ou IDs
2. **Sistemas de Arquivos**: Busca em logs ordenados por data
3. **Finanças**: Busca em séries temporais de preços
4. **Telefonia**: Busca em lista de números de telefone

## 📖 Recursos Adicionais

- [Interpolation Search - Wikipedia](https://en.wikipedia.org/wiki/Interpolation_search)
- [Analysis of Interpolation Search](https://www.cs.princeton.edu/~rs/talks/interpolation-search.pdf)
- [Comparison of Search Algorithms](https://en.wikipedia.org/wiki/Search_algorithm)

---

**Repositório**: https://github.com/profluiscaparroz/estrutura-dados-c
