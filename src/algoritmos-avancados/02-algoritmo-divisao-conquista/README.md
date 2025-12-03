# Algoritmos de Divisão e Conquista

## 📚 Definição Formal

**Divisão e Conquista** (Divide and Conquer) é um paradigma algorítmico que resolve problemas através de três etapas fundamentais:

1. **DIVIDIR** (Divide): Particionar o problema em subproblemas menores e independentes
2. **CONQUISTAR** (Conquer): Resolver recursivamente cada subproblema
3. **COMBINAR** (Combine): Mesclar as soluções dos subproblemas para obter a solução final

Formalmente, para um problema de tamanho `n`:

```
T(n) = aT(n/b) + D(n) + C(n)
```

Onde:
- `a` = número de subproblemas
- `n/b` = tamanho de cada subproblema
- `D(n)` = custo de dividir
- `C(n)` = custo de combinar

## 🎓 Fundamentação Teórica

### Origem Histórica

O paradigma de Divisão e Conquista tem raízes antigas na estratégia militar ("divide et impera") e foi formalizado na computação por:

- **John von Neumann (1945)**: Merge Sort - primeira aplicação formal
- **C.A.R. Hoare (1961)**: Quick Sort - particionamento eficiente
- **Karatsuba (1962)**: Multiplicação rápida de inteiros

### Teorema Mestre (Master Theorem)

Para recorrências da forma `T(n) = aT(n/b) + f(n)`, onde `a ≥ 1` e `b > 1`:

**Caso 1**: Se `f(n) = O(n^c)` onde `c < log_b(a)`:
```
T(n) = Θ(n^(log_b a))
```

**Caso 2**: Se `f(n) = Θ(n^c log^k n)` onde `c = log_b(a)`:
```
T(n) = Θ(n^c log^(k+1) n)
```

**Caso 3**: Se `f(n) = Ω(n^c)` onde `c > log_b(a)` e condição de regularidade:
```
T(n) = Θ(f(n))
```

## 📊 Algoritmos Clássicos

### 1. Merge Sort

**Recorrência**: `T(n) = 2T(n/2) + Θ(n)`

**Pelo Teorema Mestre**:
- a = 2, b = 2, f(n) = Θ(n)
- log_b(a) = log_2(2) = 1
- f(n) = Θ(n^1) → Caso 2
- **Complexidade**: Θ(n log n)

```
MERGE-SORT(A, p, r)
    if p < r
        q = ⌊(p + r)/2⌋           // DIVIDIR
        MERGE-SORT(A, p, q)        // CONQUISTAR
        MERGE-SORT(A, q+1, r)      // CONQUISTAR
        MERGE(A, p, q, r)          // COMBINAR
```

**Propriedades**:
- Estável: Sim
- In-place: Não (requer O(n) espaço adicional)
- Cache-friendly: Não (acesso não-local na fase de merge)

### 2. Quick Sort

**Recorrência**:
- Caso médio: `T(n) = 2T(n/2) + Θ(n)` → O(n log n)
- Pior caso: `T(n) = T(n-1) + Θ(n)` → O(n²)

```
QUICKSORT(A, p, r)
    if p < r
        q = PARTITION(A, p, r)     // DIVIDIR + COMBINAR
        QUICKSORT(A, p, q-1)       // CONQUISTAR
        QUICKSORT(A, q+1, r)       // CONQUISTAR
```

**Análise Probabilística** (Sedgewick & Flajolet, 1996):
- Número médio de comparações: **1.39 n log₂ n**
- Quick Sort é ~39% mais comparações que o ótimo teórico

### 3. Busca Binária

**Recorrência**: `T(n) = T(n/2) + Θ(1)` → O(log n)

```
BINARY-SEARCH(A, p, r, x)
    if p > r
        return NIL
    q = ⌊(p + r)/2⌋               // DIVIDIR
    if A[q] = x
        return q
    else if x < A[q]
        return BINARY-SEARCH(A, p, q-1, x)  // CONQUISTAR
    else
        return BINARY-SEARCH(A, q+1, r, x)  // CONQUISTAR
```

### 4. Multiplicação de Karatsuba

**Problema**: Multiplicar dois números de n dígitos

**Método Tradicional**: O(n²)

**Método Karatsuba**:
Para x = 10^m × a + b e y = 10^m × c + d:

```
xy = 10^(2m) × ac + 10^m × (ad + bc) + bd
   = 10^(2m) × ac + 10^m × ((a+b)(c+d) - ac - bd) + bd
```

**Recorrência**: `T(n) = 3T(n/2) + Θ(n)`

**Complexidade**: O(n^(log₂3)) ≈ O(n^1.585)

### 5. Algoritmo de Strassen (Multiplicação de Matrizes)

**Problema**: Multiplicar duas matrizes n×n

**Método Tradicional**: O(n³)

**Método Strassen**: Divide cada matriz em 4 submatrizes e usa 7 multiplicações ao invés de 8

**Recorrência**: `T(n) = 7T(n/2) + Θ(n²)`

**Complexidade**: O(n^(log₂7)) ≈ O(n^2.807)

## 📈 Análise Comparativa

| Algoritmo | Recorrência | Complexidade | Espaço |
|-----------|-------------|--------------|--------|
| Merge Sort | T(n) = 2T(n/2) + Θ(n) | Θ(n log n) | O(n) |
| Quick Sort | T(n) = 2T(n/2) + Θ(n) | Θ(n log n)* | O(log n) |
| Busca Binária | T(n) = T(n/2) + Θ(1) | Θ(log n) | O(1) ou O(log n)** |
| Karatsuba | T(n) = 3T(n/2) + Θ(n) | Θ(n^1.585) | O(n) |
| Strassen | T(n) = 7T(n/2) + Θ(n²) | Θ(n^2.807) | O(n²) |
| Max-Min | T(n) = 2T(n/2) + Θ(1) | Θ(n) | O(log n) |

*Caso médio; pior caso é O(n²)
**O(1) iterativo, O(log n) recursivo

## 🎯 Aplicações Práticas

### 1. Ordenação Externa
- Merge Sort é ideal para dados em disco
- Acesso sequencial é eficiente

### 2. Processamento Paralelo
- Subproblemas independentes podem executar em paralelo
- Fork-Join frameworks (Java, OpenMP)

### 3. Geometria Computacional
- Par de pontos mais próximo: O(n log n)
- Envoltória convexa: O(n log n)

### 4. Transformada Rápida de Fourier (FFT)
- Recorrência: T(n) = 2T(n/2) + Θ(n)
- Complexidade: O(n log n)
- Aplicações: processamento de sinais, multiplicação de polinômios

### 5. Algoritmos em Grafos
- Componentes fortemente conexos
- Árvore geradora mínima (algoritmo de Borůvka)

## 🔄 Paradigmas Relacionados

### Divisão e Conquista vs Programação Dinâmica

| Aspecto | Divisão e Conquista | Programação Dinâmica |
|---------|---------------------|----------------------|
| Subproblemas | Independentes | Sobrepostos |
| Abordagem | Top-down | Bottom-up ou Top-down com memo |
| Exemplo | Merge Sort | Fibonacci otimizado |

### Divisão e Conquista vs Decrease and Conquer

| Aspecto | Divisão e Conquista | Decrease and Conquer |
|---------|---------------------|----------------------|
| Divisão | Múltiplos subproblemas | Um subproblema |
| Exemplo | Merge Sort | Busca Binária |

## 🛠️ Técnicas de Otimização

### 1. Escolha do Caso Base
- Usar algoritmos simples para entradas pequenas
- Quick Sort + Insertion Sort para n < 10-20

### 2. Balanceamento de Subproblemas
- Dividir em partes iguais quando possível
- Evitar divisões desbalanceadas (Quick Sort com mediana)

### 3. Eliminação de Cópias
- Reutilizar buffers em Merge Sort
- Implementações in-place quando possível

## 📖 Referências Bibliográficas

1. **Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C.** (2009). *Introduction to Algorithms* (3rd ed.). MIT Press. Capítulo 4: Divide-and-Conquer.

2. **Bentley, J. L.** (1986). *Programming Pearls*. Addison-Wesley. Capítulo 8.

3. **Karatsuba, A., & Ofman, Y.** (1962). Multiplication of multidigit numbers on automata. *Soviet Physics Doklady*, 7, 595-596.

4. **Strassen, V.** (1969). Gaussian elimination is not optimal. *Numerische Mathematik*, 13(4), 354-356.

5. **Sedgewick, R., & Flajolet, P.** (2013). *An Introduction to the Analysis of Algorithms* (2nd ed.). Addison-Wesley.

## 🔗 Navegação

← **[01-algoritmo-recursao](../01-algoritmo-recursao/)**: Fundamentos de Recursão

→ **[03-consistent-hashing](../03-consistent-hashing/)**: Consistent Hashing para Sistemas Distribuídos

---

*Este material faz parte do curso de Estrutura de Dados em C.*
