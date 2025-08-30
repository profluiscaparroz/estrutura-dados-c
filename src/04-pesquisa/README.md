# Algoritmos de Pesquisa em C

## 📋 Visão Geral

Os algoritmos de pesquisa são fundamentais em ciência da computação e permitem encontrar elementos específicos em conjuntos de dados. Este módulo apresenta os principais algoritmos de pesquisa implementados em C, desde a busca linear básica até técnicas mais avançadas como busca binária e interpolada.

## 🔍 Algoritmos Implementados

### Busca Linear
- **Arquivo**: `buscaLinear.c`
- **Complexidade**: O(n)
- **Aplicação**: Dados não ordenados
- **Características**: Simples e versátil

### Busca Linear em Matriz
- **Arquivo**: `buscaLinearMatriz.c`
- **Complexidade**: O(m×n)
- **Aplicação**: Matrizes bidimensionais
- **Características**: Busca elemento por elemento

### Busca Binária
- **Arquivo**: `buscaBinaria.c`
- **Complexidade**: O(log n)
- **Aplicação**: Dados ordenados
- **Características**: Eficiente para grandes conjuntos

### Busca Binária em Matriz
- **Arquivo**: `buscaBinariaMatriz.c`
- **Complexidade**: O(log(m×n))
- **Aplicação**: Matrizes ordenadas
- **Características**: Otimizada para estruturas 2D

### Busca Interpolada
- **Arquivo**: `buscaInterpolada.c`
- **Complexidade**: O(log log n) - melhor caso
- **Aplicação**: Dados uniformemente distribuídos
- **Características**: Melhora da busca binária

## 📊 Comparação de Performance

| Algoritmo | Melhor Caso | Caso Médio | Pior Caso | Espaço |
|-----------|-------------|------------|-----------|---------|
| Linear | O(1) | O(n) | O(n) | O(1) |
| Binária | O(1) | O(log n) | O(log n) | O(1) |
| Interpolada | O(1) | O(log log n) | O(n) | O(1) |

## 🛠️ Como Executar

### Compilação
```bash
gcc -o busca_linear buscaLinear.c
gcc -o busca_binaria buscaBinaria.c
gcc -o busca_interpolada buscaInterpolada.c
```

### Execução
```bash
./busca_linear
./busca_binaria
./busca_interpolada
```

## 📚 Conceitos Fundamentais

### Pré-requisitos para Busca Binária
- **Dados ordenados**: Essencial para funcionamento
- **Acesso aleatório**: Necessário para divisão eficiente
- **Elementos comparáveis**: Operadores relacionais definidos

### Quando Usar Cada Algoritmo

#### Busca Linear
- ✅ Dados pequenos (< 100 elementos)
- ✅ Dados não ordenados
- ✅ Busca única ou poucas buscas
- ✅ Implementação simples necessária

#### Busca Binária
- ✅ Dados ordenados
- ✅ Múltiplas buscas no mesmo conjunto
- ✅ Conjuntos grandes (> 1000 elementos)
- ✅ Memória limitada

#### Busca Interpolada
- ✅ Dados uniformemente distribuídos
- ✅ Conjuntos muito grandes
- ✅ Dados numéricos
- ✅ Performance crítica

## 🔧 Otimizações Implementadas

### Busca Binária Otimizada
- Verificação de limites
- Prevenção de overflow em índices
- Tratamento de casos especiais

### Busca em Matriz
- Aproveitamento da estrutura 2D
- Redução do espaço de busca
- Otimização de cache

## 🧮 Análise Matemática

### Busca Binária
A cada iteração, o espaço de busca é dividido pela metade:
```
T(n) = T(n/2) + c
T(n) = O(log₂ n)
```

### Busca Interpolada
Para dados uniformemente distribuídos:
```
T(n) = T(n^(1/2)) + c
T(n) = O(log log n)
```

## 🤔 Questões para Reflexão

1. **Análise**: Por que a busca binária requer dados ordenados? O que acontece se aplicarmos em dados desordenados?

2. **Comparação**: Em que situações a busca linear pode ser mais eficiente que a busca binária?

3. **Implementação**: Como você modificaria a busca binária para encontrar a primeira ocorrência de um elemento repetido?

4. **Otimização**: Qual seria o impacto de usar busca interpolada em dados não uniformemente distribuídos?

5. **Aplicação Prática**: Projete um sistema de busca que combine múltiplos algoritmos baseado no tamanho e características dos dados.

## 📖 Exercícios Práticos

1. **Básico**: Implemente uma versão recursiva da busca binária
2. **Intermediário**: Crie uma busca binária que retorne todas as posições de elementos duplicados
3. **Avançado**: Desenvolva uma busca híbrida que escolha automaticamente entre linear e binária baseado no tamanho dos dados
4. **Desafio**: Implemente busca ternária e compare sua performance com a busca binária

## 📚 Referências

- Cormen, T. H. et al. (2009). *Introduction to Algorithms*. MIT Press.
- Sedgewick, R. (2011). *Algorithms*. Addison-Wesley.
- Knuth, D. E. (1998). *The Art of Computer Programming, Vol. 3*. Addison-Wesley.