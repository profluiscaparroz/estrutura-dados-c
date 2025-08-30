# Grafos em C

## 📋 Visão Geral

Grafos são estruturas de dados não-lineares compostas por vértices (nós) conectados por arestas. São fundamentais para modelar relações complexas entre entidades e resolver problemas em diversas áreas como redes de computadores, transporte, redes sociais e algoritmos de otimização.

## 📚 Conceitos Fundamentais

### O que é um Grafo?

Um grafo G é definido como G = (V, E), onde:
- **V**: Conjunto de vértices (nós)
- **E**: Conjunto de arestas que conectam os vértices

### Tipos de Grafos

#### 1. **Grafo Direcionado (Dígrafo)**
- Arestas têm direção específica
- Representam relações assimétricas
- Exemplo: Páginas web com links

#### 2. **Grafo Não-Direcionado**
- Arestas são bidirecionais
- Representam relações simétricas
- Exemplo: Rede de amizades

#### 3. **Grafo Ponderado**
- Arestas possuem pesos/custos
- Usado para otimização de caminhos
- Exemplo: Rotas com distâncias

#### 4. **Grafo Simples**
- Sem laços ou arestas múltiplas
- No máximo uma aresta entre dois vértices

## 🗂️ Estrutura dos Arquivos

```
grafos/
├── grafoMatrizAdjacencia.c       # Implementação com matriz de adjacência
├── grafoListaAdjacencia.c        # Implementação com lista de adjacência
├── exemploGrafoSimplesMatriz.c   # Exemplo básico com matriz
├── exemploGrafoSimplesListaAdj.c # Exemplo básico com lista
├── exemplosGrafos.c              # Exemplos diversos e algoritmos
└── test_grafo_lista             # Executável de teste
```

## 🏗️ Representações de Grafos

### 1. Matriz de Adjacência

#### Estrutura
```c
typedef struct {
    int** matrix;      // Matriz de adjacência
    int numVertices;   // Número de vértices
    bool isDirected;   // Se é direcionado
} GraphMatrix;
```

#### Características
- **Espaço**: O(V²)
- **Verificar aresta**: O(1)
- **Adicionar aresta**: O(1)
- **Iterar adjacentes**: O(V)

#### Quando Usar
- ✅ Grafos densos (muitas arestas)
- ✅ Consultas frequentes de adjacência
- ✅ Operações com matrizes
- ❌ Grafos esparsos (poucas arestas)

### 2. Lista de Adjacência

#### Estrutura
```c
typedef struct Node {
    int vertex;        // Vértice de destino
    int weight;        // Peso da aresta (opcional)
    struct Node* next; // Próximo nó na lista
} AdjNode;

typedef struct {
    AdjNode** array;   // Array de listas
    int numVertices;   // Número de vértices
    bool isDirected;   // Se é direcionado
} GraphList;
```

#### Características
- **Espaço**: O(V + E)
- **Verificar aresta**: O(grau do vértice)
- **Adicionar aresta**: O(1)
- **Iterar adjacentes**: O(grau do vértice)

#### Quando Usar
- ✅ Grafos esparsos (poucas arestas)
- ✅ Economia de memória
- ✅ Algoritmos de travessia
- ❌ Consultas frequentes de adjacência

## ⚙️ Operações Fundamentais

### Operações Básicas
```c
// Criação e inicialização
GraphMatrix* createGraphMatrix(int vertices, bool directed);
GraphList* createGraphList(int vertices, bool directed);

// Manipulação de arestas
void addEdge(Graph* graph, int src, int dest, int weight);
void removeEdge(Graph* graph, int src, int dest);
bool hasEdge(Graph* graph, int src, int dest);

// Consultas
int getNumVertices(Graph* graph);
int getNumEdges(Graph* graph);
int getDegree(Graph* graph, int vertex);

// Liberação de memória
void destroyGraph(Graph* graph);
```

### Algoritmos de Travessia

#### 1. Busca em Profundidade (DFS)
```c
void DFS(Graph* graph, int startVertex, bool visited[]) {
    visited[startVertex] = true;
    printf("%d ", startVertex);
    
    // Para cada vértice adjacente
    for (int i = 0; i < graph->numVertices; i++) {
        if (hasEdge(graph, startVertex, i) && !visited[i]) {
            DFS(graph, i, visited);
        }
    }
}
```

#### 2. Busca em Largura (BFS)
```c
void BFS(Graph* graph, int startVertex) {
    bool* visited = calloc(graph->numVertices, sizeof(bool));
    Queue* queue = createQueue();
    
    visited[startVertex] = true;
    enqueue(queue, startVertex);
    
    while (!isEmpty(queue)) {
        int current = dequeue(queue);
        printf("%d ", current);
        
        // Para cada vértice adjacente
        for (int i = 0; i < graph->numVertices; i++) {
            if (hasEdge(graph, current, i) && !visited[i]) {
                visited[i] = true;
                enqueue(queue, i);
            }
        }
    }
    
    free(visited);
    destroyQueue(queue);
}
```

## 📊 Comparação de Representações

| Operação | Matriz de Adjacência | Lista de Adjacência |
|----------|---------------------|---------------------|
| Espaço | O(V²) | O(V + E) |
| Adicionar vértice | O(V²) | O(1) |
| Adicionar aresta | O(1) | O(1) |
| Remover aresta | O(1) | O(V) |
| Verificar aresta | O(1) | O(V) |
| Listar adjacentes | O(V) | O(grau) |

### Densidade do Grafo
- **Grafo Denso**: E ≈ V² → Matriz é mais eficiente
- **Grafo Esparso**: E << V² → Lista é mais eficiente

## 🚀 Algoritmos Avançados

### 1. Detecção de Ciclos

#### DFS para Grafos Não-Direcionados
```c
bool hasCycleDFS(Graph* graph, int vertex, bool visited[], int parent) {
    visited[vertex] = true;
    
    for (int i = 0; i < graph->numVertices; i++) {
        if (hasEdge(graph, vertex, i)) {
            if (!visited[i]) {
                if (hasCycleDFS(graph, i, visited, vertex)) {
                    return true;
                }
            } else if (i != parent) {
                return true; // Ciclo encontrado
            }
        }
    }
    
    return false;
}
```

### 2. Componentes Conectados
```c
int countConnectedComponents(Graph* graph) {
    bool* visited = calloc(graph->numVertices, sizeof(bool));
    int components = 0;
    
    for (int i = 0; i < graph->numVertices; i++) {
        if (!visited[i]) {
            DFS(graph, i, visited);
            components++;
        }
    }
    
    free(visited);
    return components;
}
```

### 3. Algoritmo de Dijkstra (Caminho Mínimo)
```c
void dijkstra(Graph* graph, int source) {
    int* distance = malloc(graph->numVertices * sizeof(int));
    bool* visited = calloc(graph->numVertices, sizeof(bool));
    
    // Inicializar distâncias
    for (int i = 0; i < graph->numVertices; i++) {
        distance[i] = INT_MAX;
    }
    distance[source] = 0;
    
    for (int count = 0; count < graph->numVertices - 1; count++) {
        // Encontrar vértice não visitado com menor distância
        int minDistance = INT_MAX, minIndex = -1;
        for (int v = 0; v < graph->numVertices; v++) {
            if (!visited[v] && distance[v] < minDistance) {
                minDistance = distance[v];
                minIndex = v;
            }
        }
        
        if (minIndex == -1) break; // Grafo desconectado
        
        visited[minIndex] = true;
        
        // Atualizar distâncias dos vizinhos
        for (int v = 0; v < graph->numVertices; v++) {
            if (!visited[v] && hasEdge(graph, minIndex, v)) {
                int weight = getEdgeWeight(graph, minIndex, v);
                if (distance[minIndex] + weight < distance[v]) {
                    distance[v] = distance[minIndex] + weight;
                }
            }
        }
    }
    
    // Imprimir resultados
    printf("Distâncias mínimas do vértice %d:\n", source);
    for (int i = 0; i < graph->numVertices; i++) {
        printf("Para %d: %d\n", i, distance[i]);
    }
    
    free(distance);
    free(visited);
}
```

## 🎯 Aplicações Práticas

### 1. Redes de Computadores
- **Topologia de Rede**: Modelar conexões entre computadores
- **Roteamento**: Encontrar caminhos ótimos
- **Detecção de Falhas**: Identificar componentes críticos

### 2. Redes Sociais
- **Grafo de Amizades**: Conexões entre usuários
- **Influência**: Algoritmos de PageRank
- **Comunidades**: Detecção de grupos

### 3. Sistemas de Transporte
- **Rotas**: Mapas e navegação GPS
- **Otimização**: Menor custo ou tempo
- **Planejamento**: Transporte público

### 4. Jogos e IA
- **Pathfinding**: Algoritmos A*
- **Estados de Jogo**: Espaço de possibilidades
- **Árvores de Decisão**: Estratégias ótimas

## 🛠️ Como Compilar e Executar

### Compilação Básica
```bash
# Compilar implementação com matriz
gcc -o grafo_matriz grafoMatrizAdjacencia.c

# Compilar implementação com lista
gcc -o grafo_lista grafoListaAdjacencia.c

# Executar exemplos
./grafo_matriz
./grafo_lista
```

### Compilação com Debug
```bash
gcc -g -Wall -Wextra -o debug_grafo grafoListaAdjacencia.c
gdb ./debug_grafo
```

### Makefile Exemplo
```makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: grafo_matriz grafo_lista exemplos

grafo_matriz: grafoMatrizAdjacencia.c
	$(CC) $(CFLAGS) -o $@ $^

grafo_lista: grafoListaAdjacencia.c
	$(CC) $(CFLAGS) -o $@ $^

exemplos: exemplosGrafos.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f grafo_matriz grafo_lista exemplos

.PHONY: all clean
```

## 🧠 Análise de Complexidade

### Algoritmos de Travessia
- **DFS**: O(V + E) - Visita cada vértice e aresta uma vez
- **BFS**: O(V + E) - Mesma complexidade do DFS

### Algoritmos de Caminho Mínimo
- **Dijkstra**: O(V²) com matriz, O((V + E) log V) com heap
- **Floyd-Warshall**: O(V³) para todos os pares
- **Bellman-Ford**: O(VE) para arestas negativas

### Problemas NP
- **Caminho Hamiltoniano**: Visitir todos os vértices uma vez
- **Clique Máximo**: Maior subgrafo completamente conectado
- **Coloração**: Menor número de cores para vértices

## 🤔 Questões para Reflexão

1. **Representação**: Quando você escolheria matriz de adjacência em vez de lista de adjacência para um grafo com 1000 vértices e 5000 arestas?

2. **Algoritmos**: Por que BFS é usado para encontrar o caminho mais curto em grafos não-ponderados, mas não em grafos ponderados?

3. **Complexidade**: Como a complexidade do algoritmo de Dijkstra mudaria se usássemos uma heap binária versus uma heap de Fibonacci?

4. **Aplicação**: Como você modelaria um sistema de recomendação de amigos usando grafos?

5. **Otimização**: Que modificações você faria no DFS para detectar ciclos em grafos direcionados?

## 📋 Exercícios Práticos

### Nível Básico
1. Implemente uma função que calcule o grau de entrada e saída de cada vértice em um grafo direcionado
2. Crie uma função que verifique se um grafo é conectado
3. Desenvolva uma função que encontre todos os vértices alcançáveis a partir de um vértice dado

### Nível Intermediário
4. Implemente o algoritmo de ordenação topológica
5. Crie uma função que encontre o menor caminho entre dois vértices usando BFS
6. Desenvolva um algoritmo para detectar ciclos em grafos direcionados

### Nível Avançado
7. Implemente o algoritmo de Kruskal para árvore geradora mínima
8. Crie uma solução para o problema do caixeiro viajante usando backtracking
9. Desenvolva o algoritmo de Ford-Fulkerson para fluxo máximo

### Desafios
10. Implemente um algoritmo para encontrar pontes em um grafo
11. Crie uma solução para coloração de grafos com número mínimo de cores
12. Desenvolva um algoritmo para encontrar o centro de um grafo

## 🔍 Debugging e Testes

### Casos de Teste Importantes
```c
// Teste de grafo vazio
void testEmptyGraph();

// Teste de grafo com um vértice
void testSingleVertex();

// Teste de grafo completamente conectado
void testCompleteGraph();

// Teste de grafo desconectado
void testDisconnectedGraph();

// Teste de grafo com ciclos
void testCyclicGraph();

// Teste de grafo direcionado vs não-direcionado
void testDirectedVsUndirected();
```

### Problemas Comuns
- **Memory Leaks**: Não liberar listas de adjacência
- **Segmentation Fault**: Acessar vértices inexistentes
- **Ciclos Infinitos**: Loops em grafos cíclicos sem controle
- **Overflow**: Índices fora dos limites

### Ferramentas de Visualização
```bash
# Gerar arquivo DOT para visualização
void exportToDot(Graph* graph, const char* filename) {
    FILE* file = fopen(filename, "w");
    fprintf(file, "digraph G {\n");
    
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            if (hasEdge(graph, i, j)) {
                fprintf(file, "  %d -> %d;\n", i, j);
            }
        }
    }
    
    fprintf(file, "}\n");
    fclose(file);
}

# Visualizar com Graphviz
# dot -Tpng grafo.dot -o grafo.png
```

## 📚 Referências e Recursos

### Livros Fundamentais
- **Cormen, T. H. et al.** *Introduction to Algorithms*. MIT Press.
- **Sedgewick, R.** *Algorithms*. Addison-Wesley.
- **Diestel, R.** *Graph Theory*. Springer.

### Algoritmos Clássicos
- **Dijkstra, E. W.** (1959). "A note on two problems in connexion with graphs"
- **Kruskal, J. B.** (1956). "On the shortest spanning subtree of a graph"
- **Floyd, R. W.** (1962). "Algorithm 97: Shortest path"

### Recursos Online
- **Visualização**: GraphOnline, Graphviz
- **Problemas**: LeetCode, HackerRank, Codeforces
- **Tutoriais**: GeeksforGeeks, CP-Algorithms

### Aplicações Modernas
- **NetworkX** (Python): Análise de redes
- **SNAP** (Stanford): Grandes redes sociais
- **Gephi**: Visualização de grafos complexos