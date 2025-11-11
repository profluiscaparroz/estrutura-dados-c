# Aula de Ciência da Computação: Disjoint Set Union (Union-Find) – História, Funcionamento e Aplicações

## Introdução

O **Disjoint Set Union (DSU)**, também conhecido como **Union-Find**, é uma estrutura de dados que gerencia uma coleção de conjuntos disjuntos (sem elementos em comum) e suporta eficientemente duas operações principais: unir dois conjuntos e verificar se dois elementos pertencem ao mesmo conjunto. Com otimizações como union by rank e path compression, alcança complexidade quase constante, O(α(n)), onde α é a função inversa de Ackermann.

---

## 1. História e Motivação

A estrutura Union-Find foi desenvolvida na década de 1960, com contribuições significativas de Bernard A. Galler e Michael J. Fischer em 1964, e posteriormente otimizada por Robert Tarjan em 1975, que introduziu a análise da complexidade amortizada usando a função inversa de Ackermann.

Antes do Union-Find, problemas de conectividade eram resolvidos com:

* **Busca Exaustiva**: Para verificar se dois elementos estão conectados, percorrer todos os caminhos possíveis – O(n²) ou pior.
* **Matrizes de Adjacência**: Armazenar conexões explicitamente – O(n²) espaço e atualização cara.
* **Árvores e Grafos Explícitos**: Usar estruturas de grafo completas, mesmo quando só precisamos de conectividade.

O Union-Find surgiu como uma solução especializada e extremamente eficiente para o problema de componentes conectados dinâmicos.

Segundo Tarjan (1975), "o algoritmo union-find com path compression e union by rank tem complexidade amortizada praticamente constante".

---

## 2. O que era feito antes do Union-Find?

Antes do Union-Find, para problemas de conectividade dinâmica:

* **Recomputação Total**: Cada vez que elementos eram unidos, executar BFS/DFS para recalcular componentes – O(n) por operação.
* **Manter Labels Explícitos**: Cada elemento tem um ID de componente, mas unir dois componentes requer atualizar todos os IDs – O(n) por união.
* **Estruturas de Grafo Completas**: Manter representação completa de grafo mesmo quando só importa conectividade.

Union-Find trouxe operações em tempo quase constante, revolucionando algoritmos de grafos como Kruskal's MST.

---

## 3. Como funciona o Union-Find?

Union-Find representa cada conjunto como uma árvore, onde:
* Cada nó aponta para seu pai
* A raiz de cada árvore representa o conjunto
* Elementos no mesmo conjunto têm a mesma raiz

### Operações Básicas

**1. Find(x)**: Encontrar a raiz (representante) do conjunto contendo x
```
while (parent[x] != x):
    x = parent[x]
return x
```

**2. Union(x, y)**: Unir os conjuntos contendo x e y
```
root_x = find(x)
root_y = find(y)
if (root_x != root_y):
    parent[root_x] = root_y
```

### Otimizações

**1. Path Compression (Compressão de Caminho)**
* Durante Find, fazer todos os nós visitados apontarem diretamente para a raiz
* Reduz altura da árvore, acelerando futuras operações

**2. Union by Rank (União por Rank)**
* Manter "rank" (profundidade aproximada) de cada árvore
* Sempre anexar árvore menor à maior
* Mantém árvores balanceadas

Com ambas otimizações: complexidade amortizada O(α(n)) ≈ O(1) na prática.

---

## 4. Vantagens do Union-Find

* **Eficiência Excepcional**: Operações em tempo quase constante O(α(n)).
* **Simplicidade**: Implementação muito simples, menos de 30 linhas.
* **Uso de Memória**: O(n) espaço, mínimo possível.
* **Versátil**: Aplicável a diversos problemas de conectividade.
* **Determinístico**: Não depende de aleatoriedade.

---

## 5. Desvantagens do Union-Find

* **Sem Suporte a Separação**: Não permite "desunir" conjuntos (operação disjoint).
* **Apenas Conectividade**: Não armazena informações sobre caminhos específicos.
* **Dificuldade em Consultas Complexas**: Não suporta naturalmente consultas além de "estão no mesmo conjunto?".
* **Path Compression Impede Persistência**: Difícil criar versões persistentes da estrutura.

---

## 6. Aplicações Práticas

* **Algoritmo de Kruskal**: Para encontrar Minimum Spanning Tree (MST).
* **Detecção de Ciclos**: Em grafos não-direcionados.
* **Problemas de Conectividade**: Redes, componentes conectados.
* **Processamento de Imagens**: Segmentação, labeling de componentes.
* **Compiladores**: Análise de equivalência de variáveis.

---

## Onde o Union-Find é usado no dia a dia?

1. **Redes Sociais e Sistemas de Recomendação**:
   * Detectar comunidades e grupos conectados de usuários.

2. **Processamento de Imagens**:
   * Segmentação de regiões, detecção de objetos conectados.

3. **Problemas de Roteamento**:
   * Verificar conectividade de redes, redundância de caminhos.

4. **Jogos e Simulações**:
   * Verificar se terrenos são acessíveis, sistemas de partículas conectadas.

5. **Bioinformática**:
   * Análise de conectividade em redes de proteínas.

---

## Como podemos melhorar o Union-Find para uso prático?

### 1. **Union by Size ao invés de Rank**
* Manter tamanho real do conjunto ao invés de rank aproximado.
* Útil quando precisamos saber o tamanho dos componentes.

### 2. **Rollback (Desfazer União)**
* Manter histórico de uniões para permitir desfazer.
* Útil em backtracking e algoritmos online.

### 3. **Weighted Union-Find**
* Armazenar pesos ou distâncias entre elementos.
* Útil para problemas com relações quantitativas.

### 4. **Persistent Union-Find**
* Técnicas funcionais para manter versões históricas.
* Complexidade aumenta, mas permite consultas temporais.

---

# Implementação do Union-Find em Python

```python
class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n
        self.count = n  # Número de componentes
    
    def find(self, x):
        """Encontra a raiz com path compression"""
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])  # Path compression
        return self.parent[x]
    
    def union(self, x, y):
        """Une dois conjuntos com union by rank"""
        root_x = self.find(x)
        root_y = self.find(y)
        
        if root_x == root_y:
            return False  # Já estão no mesmo conjunto
        
        # Union by rank
        if self.rank[root_x] < self.rank[root_y]:
            self.parent[root_x] = root_y
        elif self.rank[root_x] > self.rank[root_y]:
            self.parent[root_y] = root_x
        else:
            self.parent[root_y] = root_x
            self.rank[root_x] += 1
        
        self.count -= 1
        return True
    
    def connected(self, x, y):
        """Verifica se x e y estão no mesmo conjunto"""
        return self.find(x) == self.find(y)
    
    def get_count(self):
        """Retorna número de componentes conectados"""
        return self.count

# Exemplo de uso
if __name__ == "__main__":
    uf = UnionFind(6)
    
    print(f"Componentes iniciais: {uf.get_count()}")
    
    uf.union(0, 1)
    print(f"Após unir 0-1: {uf.get_count()} componentes")
    
    uf.union(2, 3)
    print(f"Após unir 2-3: {uf.get_count()} componentes")
    
    uf.union(0, 2)
    print(f"Após unir 0-2: {uf.get_count()} componentes")
    
    print(f"\n0 e 3 conectados? {uf.connected(0, 3)}")
    print(f"1 e 4 conectados? {uf.connected(1, 4)}")
```

---

# Implementação do Union-Find em C

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Estrutura do Union-Find
typedef struct {
    int *parent;
    int *rank;
    int n;
    int count;  // Número de componentes conectados
} UnionFind;

// Criar Union-Find
UnionFind* createUnionFind(int n) {
    UnionFind *uf = (UnionFind *)malloc(sizeof(UnionFind));
    uf->n = n;
    uf->count = n;
    uf->parent = (int *)malloc(sizeof(int) * n);
    uf->rank = (int *)calloc(n, sizeof(int));
    
    for (int i = 0; i < n; i++) {
        uf->parent[i] = i;
    }
    
    return uf;
}

// Find com path compression
int find(UnionFind *uf, int x) {
    if (uf->parent[x] != x) {
        uf->parent[x] = find(uf, uf->parent[x]);  // Path compression
    }
    return uf->parent[x];
}

// Union com union by rank
bool unionSets(UnionFind *uf, int x, int y) {
    int root_x = find(uf, x);
    int root_y = find(uf, y);
    
    if (root_x == root_y) {
        return false;  // Já estão no mesmo conjunto
    }
    
    // Union by rank
    if (uf->rank[root_x] < uf->rank[root_y]) {
        uf->parent[root_x] = root_y;
    } else if (uf->rank[root_x] > uf->rank[root_y]) {
        uf->parent[root_y] = root_x;
    } else {
        uf->parent[root_y] = root_x;
        uf->rank[root_x]++;
    }
    
    uf->count--;
    return true;
}

// Verificar se estão conectados
bool connected(UnionFind *uf, int x, int y) {
    return find(uf, x) == find(uf, y);
}

// Obter número de componentes
int getCount(UnionFind *uf) {
    return uf->count;
}

// Liberar memória
void freeUnionFind(UnionFind *uf) {
    free(uf->parent);
    free(uf->rank);
    free(uf);
}

// Exemplo de uso
int main() {
    int n = 6;
    UnionFind *uf = createUnionFind(n);
    
    printf("=== Union-Find com %d elementos ===\n\n", n);
    printf("Componentes iniciais: %d\n", getCount(uf));
    
    printf("\nUnindo 0-1...\n");
    unionSets(uf, 0, 1);
    printf("Componentes: %d\n", getCount(uf));
    
    printf("\nUnindo 2-3...\n");
    unionSets(uf, 2, 3);
    printf("Componentes: %d\n", getCount(uf));
    
    printf("\nUnindo 0-2...\n");
    unionSets(uf, 0, 2);
    printf("Componentes: %d\n", getCount(uf));
    
    printf("\nUnindo 4-5...\n");
    unionSets(uf, 4, 5);
    printf("Componentes: %d\n", getCount(uf));
    
    printf("\n=== Consultas de Conectividade ===\n");
    printf("0 e 3 conectados? %s\n", connected(uf, 0, 3) ? "Sim" : "Não");
    printf("1 e 2 conectados? %s\n", connected(uf, 1, 2) ? "Sim" : "Não");
    printf("0 e 4 conectados? %s\n", connected(uf, 0, 4) ? "Sim" : "Não");
    printf("4 e 5 conectados? %s\n", connected(uf, 4, 5) ? "Sim" : "Não");
    
    freeUnionFind(uf);
    
    return 0;
}
```

---

## 7. Conclusão

O Disjoint Set Union (Union-Find) é uma das estruturas de dados mais elegantes e eficientes em Ciência da Computação. Com apenas duas otimizações simples (path compression e union by rank), alcança complexidade amortizada quase constante, tornando-se fundamental para algoritmos de grafos.

Como Robert Tarjan demonstrou em 1975, "o algoritmo union-find é um exemplo notável de como simples otimizações podem levar a melhorias dramáticas de desempenho".

Sua aplicação vai desde algoritmos clássicos como Kruskal's MST até problemas modernos em redes sociais, processamento de imagens e análise de dados.

---

## Referências

* Galler, B. A., & Fischer, M. J. (1964). **An Improved Equivalence Algorithm**. *Communications of the ACM*, 7(5), 301-303.

* Tarjan, R. E. (1975). **Efficiency of a Good But Not Linear Set Union Algorithm**. *Journal of the ACM*, 22(2), 215-225.

* Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009). *Introduction to Algorithms* (3rd ed.). MIT Press.

* Sedgewick, R., & Wayne, K. (2011). *Algorithms* (4th ed.). Addison-Wesley.

* CP-Algorithms. **Disjoint Set Union**. Disponível em: https://cp-algorithms.com/data_structures/disjoint_set_union.html
