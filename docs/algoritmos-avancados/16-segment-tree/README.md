# Aula de Ciência da Computação: Segment Tree (Árvore de Segmentos) – História, Funcionamento e Aplicações

## Introdução

A **Segment Tree** (Árvore de Segmentos) é uma estrutura de dados hierárquica utilizada para realizar consultas de intervalo e atualizações em tempo logarítmico. É especialmente útil quando precisamos responder repetidamente a consultas sobre intervalos de um array, como soma, mínimo, máximo ou outras operações associativas, com a possibilidade de atualizar elementos individuais de forma eficiente.

---

## 1. História e Motivação

A Segment Tree foi introduzida na década de 1970 como uma solução para problemas de geometria computacional e processamento de consultas de intervalo. O conceito foi formalizado e popularizado por pesquisadores como Jon Louis Bentley, que trabalharam em estruturas de dados para geometria computacional e consultas espaciais.

Antes da Segment Tree, as principais abordagens para problemas de consulta de intervalo eram:

* **Arrays simples**: Consultas de intervalo (ex: soma de elementos de i a j) requerem O(n) no pior caso, tornando-se impraticáveis para grandes volumes de dados com muitas consultas.
* **Pré-computação total**: Armazenar todas as possíveis consultas de intervalo requer O(n²) espaço, inviável para arrays grandes.
* **Estruturas especializadas**: Como Binary Indexed Tree (Fenwick Tree), mas com limitações em tipos de operações suportadas.

A Segment Tree surgiu como uma solução elegante que equilibra tempo e espaço: O(n) espaço e O(log n) para consultas e atualizações.

Segundo Cormen et al. (Introduction to Algorithms, 2009), "estruturas de árvore de segmentos são fundamentais para resolver eficientemente problemas de consulta de intervalo dinâmicos".

---

## 2. O que era feito antes da Segment Tree?

Antes da Segment Tree, as soluções para consultas de intervalo tinham trade-offs significativos:

* **Abordagem Ingênua**: Para cada consulta de soma no intervalo [L, R], percorrer todos os elementos – O(n) por consulta.
* **Tabela de Pré-computação**: Criar uma matriz onde `table[i][j]` armazena o resultado do intervalo [i, j]. Requer O(n²) espaço e tempo de pré-processamento.
* **Square Root Decomposition**: Dividir o array em blocos de tamanho √n, reduzindo consultas para O(√n), mas ainda subótimo.

A Segment Tree trouxe uma solução com O(log n) para ambas consultas e atualizações, mantendo O(n) espaço, tornando-se o padrão para problemas de consulta de intervalo dinâmico.

---

## 3. Como funciona a Segment Tree?

Uma Segment Tree é uma árvore binária onde:

* **Folhas**: Representam elementos individuais do array original.
* **Nós internos**: Representam a fusão (merge) de intervalos de seus filhos.

### Estrutura

Para um array de tamanho `n`:
* A árvore tem altura O(log n).
* Cada nó representa um intervalo [L, R] e armazena informação agregada sobre esse intervalo (ex: soma, mínimo, máximo).
* Filhos esquerdo e direito representam metades do intervalo do pai.

### Construção

A construção é feita recursivamente:
1. Para uma folha (intervalo de um único elemento), o valor é o próprio elemento.
2. Para um nó interno, o valor é a combinação dos valores dos filhos.

Complexidade: O(n)

### Consulta de Intervalo

Para consultar um intervalo [L, R]:
1. Se o intervalo do nó está completamente dentro de [L, R], retornar o valor armazenado.
2. Se o intervalo do nó não intersecta [L, R], retornar valor neutro (0 para soma, ∞ para mínimo).
3. Caso contrário, recursivamente consultar os filhos e combinar resultados.

Complexidade: O(log n)

### Atualização

Para atualizar um elemento no índice `i`:
1. Atualizar a folha correspondente.
2. Propagar a mudança para cima, atualizando todos os ancestrais.

Complexidade: O(log n)

---

## 4. Vantagens da Segment Tree

* **Eficiência**: O(log n) para consultas e atualizações, muito mais rápido que abordagens ingênuas.
* **Versatilidade**: Suporta diversas operações (soma, mínimo, máximo, GCD, produto) desde que sejam associativas.
* **Lazy Propagation**: Pode ser estendida para suportar atualizações de intervalo em O(log n).
* **Estrutura Clara**: Implementação recursiva intuitiva e fácil de entender.
* **Memória Razoável**: O(4n) espaço na implementação array-based, aceitável para a maioria das aplicações.

---

## 5. Desvantagens da Segment Tree

* **Complexidade de Implementação**: Mais complexa que soluções simples ou Fenwick Tree.
* **Overhead de Memória**: Usa mais memória que Fenwick Tree (O(4n) vs O(n)).
* **Não trivial para iniciantes**: Requer entendimento de recursão e árvores.
* **Cache Performance**: Pode ter pior localidade de cache comparada a estruturas contíguas.
* **Overhead Constante**: Constantes ocultas na notação Big-O podem tornar outras estruturas mais rápidas na prática para arrays pequenos.

---

## 6. Aplicações Práticas

Segment Trees são amplamente utilizadas em:

* **Programação Competitiva**: Essencial para resolver problemas de consulta de intervalo eficientemente.
* **Sistemas de Banco de Dados**: Para indexação e consultas de agregação em intervalos.
* **Processamento de Imagens**: Para consultas rápidas sobre regiões de imagens.
* **Sistemas de Consulta Geográfica**: Para consultas espaciais e de intervalo em mapas.
* **Análise de Séries Temporais**: Para consultas sobre janelas de tempo.

---

## Onde a Segment Tree é usada no dia a dia?

1. **Plataformas de programação competitiva**:
   * Codeforces, AtCoder, TopCoder e LeetCode frequentemente têm problemas que requerem Segment Trees.

2. **Sistemas de monitoramento e análise de dados**:
   * Para consultas rápidas sobre métricas agregadas em intervalos de tempo (ex: soma de vendas em um período).

3. **Editores de texto e IDEs**:
   * Para implementar recursos como syntax highlighting e folding de código, que requerem consultas rápidas sobre intervalos de linhas.

4. **Sistemas de processamento de sinais**:
   * Para análise de janelas de dados em tempo real.

5. **Bancos de dados e sistemas OLAP**:
   * Para consultas de agregação eficientes sobre grandes volumes de dados.

---

## Como podemos melhorar a Segment Tree para uso prático?

### 1. **Lazy Propagation**
* Permite atualizações de intervalo em O(log n) ao adiar (lazy) a propagação de mudanças até que seja necessário.
* Essencial para problemas que requerem atualização de múltiplos elementos.

### 2. **Compressão de Coordenadas**
* Quando trabalhamos com valores esparsos, comprimir coordenadas reduz o uso de memória.

### 3. **Segment Tree Iterativa**
* Implementação bottom-up sem recursão, mais rápida e com menor overhead de chamada de função.
* Reduz a profundidade de chamadas de função, melhorando performance.

### 4. **Persistent Segment Tree**
* Mantém versões históricas da árvore, permitindo consultas em diferentes pontos no tempo.
* Útil para problemas com rollback ou versionamento.

### 5. **Dynamic Segment Tree**
* Cria nós sob demanda, economizando memória quando trabalhamos com intervalos muito grandes.

---

# Implementação da Segment Tree em Python

```python
class SegmentTree:
    def __init__(self, arr):
        self.n = len(arr)
        self.tree = [0] * (4 * self.n)
        self.arr = arr
        self.build(0, 0, self.n - 1)
    
    def build(self, node, start, end):
        if start == end:
            self.tree[node] = self.arr[start]
        else:
            mid = (start + end) // 2
            left_child = 2 * node + 1
            right_child = 2 * node + 2
            
            self.build(left_child, start, mid)
            self.build(right_child, mid + 1, end)
            
            self.tree[node] = self.tree[left_child] + self.tree[right_child]
    
    def query(self, node, start, end, L, R):
        # Sem sobreposição
        if R < start or L > end:
            return 0
        
        # Sobreposição total
        if L <= start and end <= R:
            return self.tree[node]
        
        # Sobreposição parcial
        mid = (start + end) // 2
        left_child = 2 * node + 1
        right_child = 2 * node + 2
        
        left_sum = self.query(left_child, start, mid, L, R)
        right_sum = self.query(right_child, mid + 1, end, L, R)
        
        return left_sum + right_sum
    
    def update(self, node, start, end, idx, val):
        if start == end:
            self.arr[idx] = val
            self.tree[node] = val
        else:
            mid = (start + end) // 2
            left_child = 2 * node + 1
            right_child = 2 * node + 2
            
            if idx <= mid:
                self.update(left_child, start, mid, idx, val)
            else:
                self.update(right_child, mid + 1, end, idx, val)
            
            self.tree[node] = self.tree[left_child] + self.tree[right_child]
    
    def range_query(self, L, R):
        return self.query(0, 0, self.n - 1, L, R)
    
    def point_update(self, idx, val):
        self.update(0, 0, self.n - 1, idx, val)

# Exemplo de uso
if __name__ == "__main__":
    arr = [1, 3, 5, 7, 9, 11]
    seg_tree = SegmentTree(arr)
    
    print(f"Array: {arr}")
    print(f"Soma [1, 3]: {seg_tree.range_query(1, 3)}")  # 3 + 5 + 7 = 15
    print(f"Soma [0, 5]: {seg_tree.range_query(0, 5)}")  # Soma total = 36
    
    print("\nAtualizando índice 2 para 10")
    seg_tree.point_update(2, 10)
    
    print(f"Soma [1, 3]: {seg_tree.range_query(1, 3)}")  # 3 + 10 + 7 = 20
    print(f"Soma [0, 5]: {seg_tree.range_query(0, 5)}")  # Soma total = 41
```

---

# Implementação da Segment Tree em C

```c
#include <stdio.h>
#include <stdlib.h>

// Estrutura da Segment Tree
typedef struct {
    int *tree;
    int *arr;
    int n;
} SegmentTree;

// Função para criar uma Segment Tree
SegmentTree* createSegmentTree(int arr[], int n) {
    SegmentTree *st = (SegmentTree *)malloc(sizeof(SegmentTree));
    st->n = n;
    st->arr = arr;
    st->tree = (int *)malloc(sizeof(int) * (4 * n));
    return st;
}

// Função auxiliar para construir a árvore
void buildHelper(SegmentTree *st, int node, int start, int end) {
    if (start == end) {
        st->tree[node] = st->arr[start];
    } else {
        int mid = (start + end) / 2;
        int left_child = 2 * node + 1;
        int right_child = 2 * node + 2;
        
        buildHelper(st, left_child, start, mid);
        buildHelper(st, right_child, mid + 1, end);
        
        st->tree[node] = st->tree[left_child] + st->tree[right_child];
    }
}

// Função para construir a Segment Tree
void build(SegmentTree *st) {
    buildHelper(st, 0, 0, st->n - 1);
}

// Função auxiliar para consulta de intervalo
int queryHelper(SegmentTree *st, int node, int start, int end, int L, int R) {
    // Sem sobreposição
    if (R < start || L > end) {
        return 0;
    }
    
    // Sobreposição total
    if (L <= start && end <= R) {
        return st->tree[node];
    }
    
    // Sobreposição parcial
    int mid = (start + end) / 2;
    int left_child = 2 * node + 1;
    int right_child = 2 * node + 2;
    
    int left_sum = queryHelper(st, left_child, start, mid, L, R);
    int right_sum = queryHelper(st, right_child, mid + 1, end, L, R);
    
    return left_sum + right_sum;
}

// Função para consultar soma de intervalo
int rangeQuery(SegmentTree *st, int L, int R) {
    return queryHelper(st, 0, 0, st->n - 1, L, R);
}

// Função auxiliar para atualização de ponto
void updateHelper(SegmentTree *st, int node, int start, int end, int idx, int val) {
    if (start == end) {
        st->arr[idx] = val;
        st->tree[node] = val;
    } else {
        int mid = (start + end) / 2;
        int left_child = 2 * node + 1;
        int right_child = 2 * node + 2;
        
        if (idx <= mid) {
            updateHelper(st, left_child, start, mid, idx, val);
        } else {
            updateHelper(st, right_child, mid + 1, end, idx, val);
        }
        
        st->tree[node] = st->tree[left_child] + st->tree[right_child];
    }
}

// Função para atualizar um elemento
void pointUpdate(SegmentTree *st, int idx, int val) {
    updateHelper(st, 0, 0, st->n - 1, idx, val);
}

// Função para exibir o array
void displayArray(int arr[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
}

// Função para liberar memória
void freeSegmentTree(SegmentTree *st) {
    free(st->tree);
    free(st);
}

// Exemplo de uso
int main() {
    int arr[] = {1, 3, 5, 7, 9, 11};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    SegmentTree *st = createSegmentTree(arr, n);
    build(st);
    
    printf("Array inicial: ");
    displayArray(arr, n);
    
    printf("\n=== Consultas de Intervalo ===\n");
    printf("Soma [1, 3]: %d\n", rangeQuery(st, 1, 3));  // 3 + 5 + 7 = 15
    printf("Soma [0, 5]: %d\n", rangeQuery(st, 0, 5));  // Soma total = 36
    printf("Soma [2, 4]: %d\n", rangeQuery(st, 2, 4));  // 5 + 7 + 9 = 21
    
    printf("\n=== Atualização ===\n");
    printf("Atualizando índice 2 para 10\n");
    pointUpdate(st, 2, 10);
    
    printf("Array atualizado: ");
    displayArray(arr, n);
    
    printf("\n=== Consultas Após Atualização ===\n");
    printf("Soma [1, 3]: %d\n", rangeQuery(st, 1, 3));  // 3 + 10 + 7 = 20
    printf("Soma [0, 5]: %d\n", rangeQuery(st, 0, 5));  // Soma total = 41
    printf("Soma [2, 4]: %d\n", rangeQuery(st, 2, 4));  // 10 + 7 + 9 = 26
    
    freeSegmentTree(st);
    
    return 0;
}
```

---

## 7. Conclusão

A Segment Tree é uma das estruturas de dados mais importantes em Ciência da Computação, especialmente para problemas envolvendo consultas de intervalo. Sua elegância está em equilibrar eficiência temporal (O(log n)) com uso razoável de memória (O(n)).

Como afirma Cormen et al. (2009), "a árvore de segmentos fornece uma solução geral e eficiente para uma ampla gama de problemas de consulta de intervalo dinâmico".

Desde sua introdução, tem sido fundamental em áreas que vão desde programação competitiva até sistemas de banco de dados e análise de dados em tempo real.

---

## Referências

* Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009). *Introduction to Algorithms* (3rd ed.). MIT Press.

* Bentley, J. L. (1980). **Multidimensional Divide-and-Conquer**. *Communications of the ACM*, 23(4), 214-229.

* Halim, S., & Halim, F. (2013). *Competitive Programming 3*. Lulu Independent Publishing.

* Skiena, S. S. (2008). *The Algorithm Design Manual* (2nd ed.). Springer.

* CP-Algorithms. **Segment Tree**. Disponível em: https://cp-algorithms.com/data_structures/segment_tree.html
