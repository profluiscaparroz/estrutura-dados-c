## 📚 **Grafos na Ciência da Computação** — Teoria Formal

### ✅ **Definição Formal**

Na matemática e ciência da computação, um **grafo** é definido como:

$
G = (V, E)
$

Onde:

* $V$ é um conjunto finito de **vértices** (ou *nós*).
* $E \subseteq V \times V$ é um conjunto de **arestas** (ou *ligações*), que conectam pares de vértices.

---

### 🧭 **Tipos de Grafos**

#### 1. **Grafo não direcionado (ou simples)**

As arestas não têm direção:

$
E = \{ \{u, v\} \mid u, v \in V \}
$

#### 2. **Grafo direcionado (ou dígrafo)**

Cada aresta aponta de um vértice para outro:

$
E = \{ (u, v) \mid u, v \in V \}
$

#### 3. **Multigrafo**

Permite múltiplas arestas entre o mesmo par de vértices.

#### 4. **Grafo ponderado**

Cada aresta tem um peso $w(u, v) \in \mathbb{R}$, comum em problemas como caminhos mínimos (e.g., Dijkstra).

---

### 🎓 **Propriedades Importantes**

| Conceito            | Descrição                                                                                   |
| ------------------- | ------------------------------------------------------------------------------------------- |
| **Grau do vértice** | Número de arestas conectadas a ele. Em grafos direcionados: grau de entrada/saída.          |
| **Caminho**         | Sequência de vértices conectados por arestas.                                               |
| **Ciclo**           | Caminho que começa e termina no mesmo vértice.                                              |
| **Conectividade**   | Grafo é conectado se existe um caminho entre qualquer par de vértices.                      |
| **Árvore**          | Grafo acíclico e conectado.                                                                 |
| **Grafo bipartido** | Os vértices podem ser divididos em dois conjuntos disjuntos com arestas só entre conjuntos. |
| **Subgrafo**        | Um grafo formado a partir de subconjuntos de vértices e arestas do grafo original.          |

---

### 🧮 **Representações em Computação**

1. **Matriz de Adjacência**

   * Tamanho $|V| \times |V|$
   * Útil para grafos densos.
   * Teste de adjacência é $O(1)$.

2. **Lista de Adjacência**

   * Lista onde cada vértice aponta para seus vizinhos.
   * Eficiência espacial $O(|V| + |E|)$
   * Ideal para grafos esparsos.

3. **Lista de Arestas**

   * Lista de pares $(u, v)$ ou trios $(u, v, w)$ se ponderado.
   * Boa para algoritmos de ordenação de arestas (e.g., Kruskal).

---

### ⚙️ **Algoritmos Fundamentais**

| Algoritmo                       | Aplicação                                                | Complexidade        |
| ------------------------------- | -------------------------------------------------------- | ------------------- |
| **BFS (Busca em Largura)**      | Conectividade, caminhos mínimos em grafos não ponderados | $O(V + E)$          |
| **DFS (Busca em Profundidade)** | Ciclos, componentes, ordenação topológica                | $O(V + E)$          |
| **Dijkstra**                    | Caminho mínimo com pesos positivos                       | $O((V + E) \log V)$ |
| **Bellman-Ford**                | Caminho mínimo com pesos negativos                       | $O(VE)$             |
| **Floyd-Warshall**              | Todos os caminhos mínimos                                | $O(V^3)$            |
| **Kruskal / Prim**              | Árvore Geradora Mínima (MST)                             | $O(E \log V)$       |
| **Kosaraju / Tarjan**           | Componentes fortemente conexos                           | $O(V + E)$          |

---

### 🔗 **Aplicações na Ciência da Computação**

* **Sistemas Operacionais**: Deadlock (grafo de espera por recursos)
* **Redes**: Roteamento de pacotes, conectividade de redes
* **Compiladores**: Dependência entre tarefas (grafo de dependência)
* **Teoria dos Jogos**: Representação de estratégias e estados
* **Inteligência Artificial**: Busca em grafos para planejamento
* **Web**: PageRank (grafo de links), recomendação

---

### 📏 **Classificação dos Grafos por Complexidade**

| Tipo de grafo | Denso       | Esparso | Cíclico             | Acíclico                    |
| ------------- | ----------- | ------- | ------------------- | --------------------------- |
| Exemplo       | Rede social | Árvore  | Roteamento de redes | DAG (dependências de build) |

---

## 🧠 **Resumo Visual**

```
Grafo (V, E)
├── Direcionado ou Não
├── Ponderado ou Não
├── Representações
│   ├── Matriz de Adjacência
│   ├── Lista de Adjacência
│   └── Lista de Arestas
└── Algoritmos
    ├── BFS / DFS
    ├── Dijkstra / Bellman-Ford
    └── Kruskal / Prim
```

---


