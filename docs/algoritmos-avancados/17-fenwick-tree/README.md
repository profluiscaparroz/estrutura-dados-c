# Aula de Ciência da Computação: Fenwick Tree (Binary Indexed Tree) – História, Funcionamento e Aplicações

## Introdução

A **Fenwick Tree**, também conhecida como **Binary Indexed Tree (BIT)**, é uma estrutura de dados que permite calcular somas de prefixos e realizar atualizações de elementos em tempo logarítmico O(log n), usando apenas O(n) espaço. Foi inventada por Peter M. Fenwick em 1994 como uma alternativa mais simples e eficiente em espaço à Segment Tree para problemas específicos de consulta de intervalo.

---

## 1. História e Motivação

A Fenwick Tree foi introduzida por Peter M. Fenwick no artigo **"A New Data Structure for Cumulative Frequency Tables"**, publicado no Software: Practice and Experience em 1994. Fenwick trabalhava com problemas de compressão de dados e estatísticas, onde era necessário calcular frequências acumuladas repetidamente.

Antes da Fenwick Tree, as principais abordagens eram:

* **Array de Prefixos**: Calcular e armazenar somas de prefixos em O(n) tempo e espaço, mas atualizações requerem O(n).
* **Segment Tree**: Oferece O(log n) para consultas e atualizações, mas usa O(4n) espaço e tem implementação mais complexa.
* **Recalculo Naive**: Para cada consulta, somar elementos no intervalo – O(n) por consulta.

A Fenwick Tree surgiu como uma solução elegante que combina:
* Uso de espaço O(n) (metade da Segment Tree)
* Operações em O(log n)
* Implementação extremamente simples (poucas linhas de código)

Segundo Fenwick (1994), "esta estrutura permite atualizações e consultas de frequências acumuladas em tempo logarítmico, usando uma quantidade linear de espaço".

---

## 2. O que era feito antes da Fenwick Tree?

Antes da Fenwick Tree, para problemas de soma de prefixos:

* **Array de Soma Acumulada**: 
  - Pré-computar somas: `prefix[i] = sum(arr[0..i])`
  - Consulta em O(1): `sum(L, R) = prefix[R] - prefix[L-1]`
  - Atualização em O(n): recalcular todo o array de prefixo
  
* **Segment Tree**: 
  - Consulta e atualização em O(log n)
  - Usa 4n espaço
  - Implementação mais complexa

* **Square Root Decomposition**: 
  - Dividir array em blocos de √n
  - Consulta e atualização em O(√n)
  - Mais simples que Segment Tree, mas menos eficiente

A Fenwick Tree trouxe o melhor dos mundos: simplicidade, eficiência de espaço e desempenho logarítmico.

---

## 3. Como funciona a Fenwick Tree?

A Fenwick Tree usa uma representação baseada em array onde cada posição armazena a soma de um intervalo de elementos, determinado pela representação binária do índice.

### Conceito Chave: Least Significant Bit (LSB)

Para um índice `i`, definimos:
* `LSB(i)` = menor bit significativo de `i` em binário
* Cada posição `i` armazena a soma dos últimos `LSB(i)` elementos

Por exemplo:
* `tree[12]` (1100₂) armazena soma de 4 elementos: arr[9..12]
* `tree[10]` (1010₂) armazena soma de 2 elementos: arr[9..10]
* `tree[9]` (1001₂) armazena soma de 1 elemento: arr[9]

### Operações

**1. Atualização (add delta ao índice i)**:
```
while (i <= n):
    tree[i] += delta
    i += LSB(i)
```

**2. Consulta de Soma de Prefixo (sum até índice i)**:
```
result = 0
while (i > 0):
    result += tree[i]
    i -= LSB(i)
```

**3. Consulta de Intervalo (sum de L a R)**:
```
return prefixSum(R) - prefixSum(L-1)
```

### Cálculo de LSB

LSB pode ser calculado eficientemente usando operação bit-a-bit:
```
LSB(i) = i & (-i)
```

---

## 4. Vantagens da Fenwick Tree

* **Simplicidade Extrema**: Implementação com menos de 20 linhas de código.
* **Eficiência de Espaço**: Usa exatamente O(n) espaço, metade da Segment Tree.
* **Performance**: Constantes menores que Segment Tree, mais rápida na prática.
* **Cache-Friendly**: Melhor localidade de cache por usar array contíguo.
* **Fácil de Entender**: Baseada em manipulação de bits simples.

---

## 5. Desvantagens da Fenwick Tree

* **Limitada a Operações Inversíveis**: Funciona bem para soma (inversível por subtração), mas não para mínimo/máximo.
* **Indexação 1-based**: Tradicionalmente usa índices começando em 1, pode confundir iniciantes.
* **Menos Versátil**: Segment Tree suporta mais tipos de operações.
* **Range Updates Complexas**: Atualizações de intervalo requerem técnicas adicionais (diferença de arrays).
* **Menos Intuitiva**: A lógica de LSB pode ser menos óbvia que árvores explícitas.

---

## 6. Aplicações Práticas

* **Programação Competitiva**: Amplamente usada por sua simplicidade e eficiência.
* **Inversões em Arrays**: Contar inversões em O(n log n).
* **Cálculo de Estatísticas**: Mediana dinâmica, quantis.
* **Compressão de Dados**: Codificação aritmética e tabelas de frequência.
* **Sistemas de Ranking**: Atualização e consulta de scores em tempo real.

---

## Onde a Fenwick Tree é usada no dia a dia?

1. **Plataformas de programação competitiva**:
   * Codeforces, AtCoder, ICPC - problema clássico de consulta de soma de intervalo.

2. **Sistemas de ranking e leaderboards**:
   * Jogos online, sistemas de pontuação onde scores mudam dinamicamente.

3. **Análise de algoritmos de ordenação**:
   * Contar inversões eficientemente durante merge sort.

4. **Processamento de sinais**:
   * Cálculo de somas cumulativas em janelas deslizantes.

5. **Bancos de dados e sistemas de cache**:
   * Estatísticas de agregação incremental.

---

## Como podemos melhorar a Fenwick Tree para uso prático?

### 1. **Fenwick Tree 2D**
* Estender para matrizes 2D para consultas de soma retangular.
* Útil para processamento de imagens e problemas de geometria.

### 2. **Range Updates usando Array de Diferenças**
* Combinar Fenwick Tree com array de diferenças para atualizar intervalos em O(log n).

### 3. **Binary Search na Fenwick Tree**
* Encontrar o menor índice com soma de prefixo ≥ k em O(log n).
* Útil para encontrar k-ésimo menor elemento.

### 4. **Fenwick Tree com Compressão de Coordenadas**
* Para trabalhar com valores esparsos ou muito grandes.

### 5. **Persistent Fenwick Tree**
* Manter versões históricas para consultas temporais.

---

# Implementação da Fenwick Tree em Python

```python
class FenwickTree:
    def __init__(self, n):
        self.n = n
        self.tree = [0] * (n + 1)  # 1-indexed
    
    def update(self, i, delta):
        """Adiciona delta ao elemento no índice i"""
        while i <= self.n:
            self.tree[i] += delta
            i += i & (-i)  # Adiciona LSB
    
    def prefix_sum(self, i):
        """Retorna soma de elementos de 1 a i"""
        result = 0
        while i > 0:
            result += self.tree[i]
            i -= i & (-i)  # Remove LSB
        return result
    
    def range_sum(self, L, R):
        """Retorna soma de elementos de L a R"""
        return self.prefix_sum(R) - self.prefix_sum(L - 1)

# Exemplo de uso
if __name__ == "__main__":
    # Array: [0, 1, 3, 5, 7, 9, 11] (índice 0 não usado, 1-indexed)
    arr = [0, 1, 3, 5, 7, 9, 11]
    n = len(arr) - 1
    
    fenwick = FenwickTree(n)
    
    # Construir a árvore
    for i in range(1, len(arr)):
        fenwick.update(i, arr[i])
    
    print(f"Array: {arr[1:]}")
    print(f"Soma [1, 3]: {fenwick.range_sum(1, 3)}")  # 1 + 3 + 5 = 9
    print(f"Soma [2, 5]: {fenwick.range_sum(2, 5)}")  # 3 + 5 + 7 + 9 = 24
    
    print("\nAtualizando índice 3: adicionando 5")
    fenwick.update(3, 5)  # arr[3] = 5 + 5 = 10
    
    print(f"Soma [1, 3]: {fenwick.range_sum(1, 3)}")  # 1 + 3 + 10 = 14
    print(f"Soma [2, 5]: {fenwick.range_sum(2, 5)}")  # 3 + 10 + 7 + 9 = 29
```

---

# Implementação da Fenwick Tree em C

```c
#include <stdio.h>
#include <stdlib.h>

// Estrutura da Fenwick Tree
typedef struct {
    int *tree;
    int n;
} FenwickTree;

// Função para criar uma Fenwick Tree
FenwickTree* createFenwickTree(int n) {
    FenwickTree *ft = (FenwickTree *)malloc(sizeof(FenwickTree));
    ft->n = n;
    ft->tree = (int *)calloc(n + 1, sizeof(int));  // 1-indexed, inicializado com 0
    return ft;
}

// Função para atualizar (adicionar delta ao índice i)
void update(FenwickTree *ft, int i, int delta) {
    while (i <= ft->n) {
        ft->tree[i] += delta;
        i += i & (-i);  // Adiciona LSB (Least Significant Bit)
    }
}

// Função para calcular soma de prefixo (1 a i)
int prefixSum(FenwickTree *ft, int i) {
    int result = 0;
    while (i > 0) {
        result += ft->tree[i];
        i -= i & (-i);  // Remove LSB
    }
    return result;
}

// Função para calcular soma de intervalo (L a R)
int rangeSum(FenwickTree *ft, int L, int R) {
    return prefixSum(ft, R) - prefixSum(ft, L - 1);
}

// Função para liberar memória
void freeFenwickTree(FenwickTree *ft) {
    free(ft->tree);
    free(ft);
}

// Função para exibir array
void displayArray(int arr[], int n) {
    printf("[");
    for (int i = 1; i <= n; i++) {
        printf("%d", arr[i]);
        if (i < n) printf(", ");
    }
    printf("]\n");
}

// Exemplo de uso
int main() {
    // Array 1-indexed: arr[1..6] = {1, 3, 5, 7, 9, 11}
    int n = 6;
    int arr[7] = {0, 1, 3, 5, 7, 9, 11};  // índice 0 não usado
    
    FenwickTree *ft = createFenwickTree(n);
    
    // Construir a Fenwick Tree
    printf("Construindo Fenwick Tree com array: ");
    displayArray(arr, n);
    
    for (int i = 1; i <= n; i++) {
        update(ft, i, arr[i]);
    }
    
    printf("\n=== Consultas de Soma ===\n");
    printf("Soma [1, 3]: %d\n", rangeSum(ft, 1, 3));  // 1 + 3 + 5 = 9
    printf("Soma [2, 5]: %d\n", rangeSum(ft, 2, 5));  // 3 + 5 + 7 + 9 = 24
    printf("Soma [1, 6]: %d\n", rangeSum(ft, 1, 6));  // Soma total = 36
    
    printf("\n=== Atualização ===\n");
    printf("Adicionando 5 ao índice 3 (arr[3] = 5 + 5 = 10)\n");
    update(ft, 3, 5);
    
    printf("\n=== Consultas Após Atualização ===\n");
    printf("Soma [1, 3]: %d\n", rangeSum(ft, 1, 3));  // 1 + 3 + 10 = 14
    printf("Soma [2, 5]: %d\n", rangeSum(ft, 2, 5));  // 3 + 10 + 7 + 9 = 29
    printf("Soma [1, 6]: %d\n", rangeSum(ft, 1, 6));  // Soma total = 41
    
    printf("\n=== Mais Atualizações ===\n");
    printf("Subtraindo 2 do índice 5 (arr[5] = 9 - 2 = 7)\n");
    update(ft, 5, -2);
    
    printf("Soma [1, 6]: %d\n", rangeSum(ft, 1, 6));  // Soma total = 39
    printf("Soma [4, 6]: %d\n", rangeSum(ft, 4, 6));  // 7 + 7 + 11 = 25
    
    freeFenwickTree(ft);
    
    return 0;
}
```

---

## 7. Conclusão

A Fenwick Tree representa uma das estruturas de dados mais elegantes em Ciência da Computação. Sua beleza está na simplicidade: usando apenas manipulação de bits e um array, resolve eficientemente problemas de consulta de intervalo que parecem requerer estruturas muito mais complexas.

Como Peter Fenwick (1994) afirmou: "Esta estrutura fornece uma solução simples e eficiente para o problema de manter tabelas de frequências acumuladas dinâmicas".

Desde sua introdução, a Fenwick Tree tornou-se ferramenta essencial para programadores competitivos e engenheiros de software que lidam com consultas de intervalo, sendo preferida à Segment Tree quando aplicável devido à sua simplicidade e eficiência.

---

## Referências

* Fenwick, P. M. (1994). **A New Data Structure for Cumulative Frequency Tables**. *Software: Practice and Experience*, 24(3), 327-336.

* Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009). *Introduction to Algorithms* (3rd ed.). MIT Press.

* Halim, S., & Halim, F. (2013). *Competitive Programming 3*. Lulu Independent Publishing.

* CP-Algorithms. **Fenwick Tree**. Disponível em: https://cp-algorithms.com/data_structures/fenwick.html

* TopCoder. **Binary Indexed Trees**. Disponível em: https://www.topcoder.com/community/competitive-programming/tutorials/binary-indexed-trees/
