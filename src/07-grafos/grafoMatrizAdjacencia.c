#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF INT_MAX

// Estrutura do grafo usando matriz de adjacência
typedef struct {
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} GraphMatrix;

// Inicializar grafo
void initGraph(GraphMatrix* graph, int vertices) {
    graph->numVertices = vertices;
    
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjMatrix[i][j] = 0; // Para não ponderado
        }
    }
}

// Inicializar grafo ponderado
void initWeightedGraph(GraphMatrix* graph, int vertices) {
    graph->numVertices = vertices;
    
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (i == j) {
                graph->adjMatrix[i][j] = 0; // Distância de um vértice para ele mesmo
            } else {
                graph->adjMatrix[i][j] = INF; // Sem conexão direta
            }
        }
    }
}

// Adicionar aresta (não direcionado)
void addEdgeMatrix(GraphMatrix* graph, int src, int dest, int weight) {
    graph->adjMatrix[src][dest] = weight;
    graph->adjMatrix[dest][src] = weight; // Para não direcionado
}

// Adicionar aresta direcionada
void addDirectedEdgeMatrix(GraphMatrix* graph, int src, int dest, int weight) {
    graph->adjMatrix[src][dest] = weight;
}

// Verificar se existe aresta
int hasEdge(GraphMatrix* graph, int src, int dest) {
    return graph->adjMatrix[src][dest] != 0 && graph->adjMatrix[src][dest] != INF;
}

// Imprimir matriz
void printMatrix(GraphMatrix* graph) {
    printf("Matriz de Adjacência:\n");
    printf("   ");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("%4d", i);
    }
    printf("\n");
    
    for (int i = 0; i < graph->numVertices; i++) {
        printf("%2d ", i);
        for (int j = 0; j < graph->numVertices; j++) {
            if (graph->adjMatrix[i][j] == INF) {
                printf(" INF");
            } else {
                printf("%4d", graph->adjMatrix[i][j]);
            }
        }
        printf("\n");
    }
}

// Estrutura para fila
typedef struct Queue {
    int items[MAX_VERTICES];
    int front;
    int rear;
} Queue;

Queue* createQueue() {
    Queue* q = malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

bool isEmpty(Queue* q) {
    return q->rear == -1;
}

void enqueue(Queue* q, int value) {
    if (q->rear == MAX_VERTICES - 1) {
        printf("Fila cheia\n");
    } else {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(Queue* q) {
    int item;
    if (isEmpty(q)) {
        printf("Fila vazia\n");
        item = -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
    }
    return item;
}

// BFS usando matriz de adjacência
void BFS(GraphMatrix* graph, int startVertex) {
    bool visited[MAX_VERTICES] = {false};
    
    Queue* q = createQueue();
    
    visited[startVertex] = true;
    enqueue(q, startVertex);
    
    printf("BFS iniciando do vértice %d: ", startVertex);
    
    while (!isEmpty(q)) {
        int currentVertex = dequeue(q);
        printf("%d ", currentVertex);
        
        for (int i = 0; i < graph->numVertices; i++) {
            if (hasEdge(graph, currentVertex, i) && !visited[i]) {
                visited[i] = true;
                enqueue(q, i);
            }
        }
    }
    printf("\n");
    
    free(q);
}

// DFS recursivo
void DFS_recursive(GraphMatrix* graph, int vertex, bool visited[]) {
    visited[vertex] = true;
    printf("%d ", vertex);
    
    for (int i = 0; i < graph->numVertices; i++) {
        if (hasEdge(graph, vertex, i) && !visited[i]) {
            DFS_recursive(graph, i, visited);
        }
    }
}

void DFS(GraphMatrix* graph, int startVertex) {
    bool visited[MAX_VERTICES] = {false};
    printf("DFS iniciando do vértice %d: ", startVertex);
    DFS_recursive(graph, startVertex, visited);
    printf("\n");
}

// Encontrar vértice com menor distância para Dijkstra
int minDistance(int dist[], bool sptSet[], int V) {
    int min = INF, min_index;
    
    for (int v = 0; v < V; v++) {
        if (sptSet[v] == false && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    
    return min_index;
}

// Imprimir caminho do algoritmo de Dijkstra
void printPath(int parent[], int j) {
    if (parent[j] == -1) {
        printf("%d", j);
        return;
    }
    
    printPath(parent, parent[j]);
    printf(" -> %d", j);
}

// Algoritmo de Dijkstra
void dijkstra(GraphMatrix* graph, int src) {
    int dist[MAX_VERTICES];
    bool sptSet[MAX_VERTICES];
    int parent[MAX_VERTICES];
    
    // Inicializar distâncias e conjunto SPT
    for (int i = 0; i < graph->numVertices; i++) {
        dist[i] = INF;
        sptSet[i] = false;
        parent[i] = -1;
    }
    
    dist[src] = 0;
    
    // Encontrar caminho mais curto para todos os vértices
    for (int count = 0; count < graph->numVertices - 1; count++) {
        int u = minDistance(dist, sptSet, graph->numVertices);
        sptSet[u] = true;
        
        for (int v = 0; v < graph->numVertices; v++) {
            if (!sptSet[v] && graph->adjMatrix[u][v] != INF && 
                dist[u] != INF && dist[u] + graph->adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + graph->adjMatrix[u][v];
                parent[v] = u;
            }
        }
    }
    
    // Imprimir resultados
    printf("\nAlgoritmo de Dijkstra a partir do vértice %d:\n", src);
    printf("Vértice\tDistância\tCaminho\n");
    
    for (int i = 0; i < graph->numVertices; i++) {
        printf("%d\t", i);
        if (dist[i] == INF) {
            printf("INF\t\tInacessível");
        } else {
            printf("%d\t\t", dist[i]);
            printPath(parent, i);
        }
        printf("\n");
    }
}

// Algoritmo de Floyd-Warshall para todos os caminhos mínimos
void floydWarshall(GraphMatrix* graph) {
    int dist[MAX_VERTICES][MAX_VERTICES];
    int V = graph->numVertices;
    
    // Inicializar matriz de distâncias
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = graph->adjMatrix[i][j];
        }
    }
    
    // Aplicar algoritmo de Floyd-Warshall
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && 
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    
    // Imprimir matriz de distâncias mínimas
    printf("\nMatriz de todas as distâncias mínimas (Floyd-Warshall):\n");
    printf("     ");
    for (int i = 0; i < V; i++) {
        printf("%4d ", i);
    }
    printf("\n");
    
    for (int i = 0; i < V; i++) {
        printf("%2d: ", i);
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF) {
                printf(" INF ");
            } else {
                printf("%4d ", dist[i][j]);
            }
        }
        printf("\n");
    }
}

// Detectar ciclo negativo usando Bellman-Ford
bool bellmanFord(GraphMatrix* graph, int src) {
    int dist[MAX_VERTICES];
    int V = graph->numVertices;
    
    // Inicializar distâncias
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
    }
    dist[src] = 0;
    
    // Relaxar todas as arestas V-1 vezes
    for (int i = 0; i < V - 1; i++) {
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                if (graph->adjMatrix[u][v] != INF && dist[u] != INF &&
                    dist[u] + graph->adjMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph->adjMatrix[u][v];
                }
            }
        }
    }
    
    // Verificar ciclos negativos
    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) {
            if (graph->adjMatrix[u][v] != INF && dist[u] != INF &&
                dist[u] + graph->adjMatrix[u][v] < dist[v]) {
                printf("Grafo contém ciclo negativo\n");
                return false;
            }
        }
    }
    
    printf("Bellman-Ford a partir do vértice %d:\n", src);
    for (int i = 0; i < V; i++) {
        printf("Distância para vértice %d: ", i);
        if (dist[i] == INF) {
            printf("INF\n");
        } else {
            printf("%d\n", dist[i]);
        }
    }
    
    return true;
}

// Verificar se o grafo é bipartido
bool isBipartite(GraphMatrix* graph) {
    int color[MAX_VERTICES];
    
    // Inicializar cores (-1 significa não colorido)
    for (int i = 0; i < graph->numVertices; i++) {
        color[i] = -1;
    }
    
    // Usar BFS para colorir o grafo
    for (int src = 0; src < graph->numVertices; src++) {
        if (color[src] == -1) {
            Queue* q = createQueue();
            color[src] = 0;
            enqueue(q, src);
            
            while (!isEmpty(q)) {
                int u = dequeue(q);
                
                for (int v = 0; v < graph->numVertices; v++) {
                    if (hasEdge(graph, u, v)) {
                        if (color[v] == -1) {
                            color[v] = 1 - color[u];
                            enqueue(q, v);
                        } else if (color[v] == color[u]) {
                            free(q);
                            return false;
                        }
                    }
                }
            }
            free(q);
        }
    }
    
    return true;
}

int main() {
    printf("=== Demonstração Completa de Grafo com Matriz de Adjacência ===\n\n");
    
    // Teste 1: Grafo simples não direcionado
    printf("1. Grafo não direcionado simples:\n");
    GraphMatrix graph;
    initGraph(&graph, 5);
    
    addEdgeMatrix(&graph, 0, 1, 1);
    addEdgeMatrix(&graph, 0, 4, 1);
    addEdgeMatrix(&graph, 1, 2, 1);
    addEdgeMatrix(&graph, 1, 3, 1);
    addEdgeMatrix(&graph, 1, 4, 1);
    addEdgeMatrix(&graph, 2, 3, 1);
    
    printMatrix(&graph);
    
    printf("\n2. Algoritmos de busca:\n");
    BFS(&graph, 0);
    DFS(&graph, 0);
    
    printf("\n3. Teste de grafo bipartido:\n");
    printf("O grafo é bipartido? %s\n", isBipartite(&graph) ? "Sim" : "Não");
    
    // Teste 2: Grafo ponderado para algoritmos de caminho mínimo
    printf("\n4. Grafo ponderado para algoritmos de caminho mínimo:\n");
    GraphMatrix weightedGraph;
    initWeightedGraph(&weightedGraph, 5);
    
    addDirectedEdgeMatrix(&weightedGraph, 0, 1, 4);
    addDirectedEdgeMatrix(&weightedGraph, 0, 2, 2);
    addDirectedEdgeMatrix(&weightedGraph, 1, 2, 1);
    addDirectedEdgeMatrix(&weightedGraph, 1, 3, 5);
    addDirectedEdgeMatrix(&weightedGraph, 2, 3, 8);
    addDirectedEdgeMatrix(&weightedGraph, 2, 4, 10);
    addDirectedEdgeMatrix(&weightedGraph, 3, 4, 2);
    
    printf("Matriz do grafo ponderado:\n");
    printMatrix(&weightedGraph);
    
    // Dijkstra
    dijkstra(&weightedGraph, 0);
    
    // Floyd-Warshall
    floydWarshall(&weightedGraph);
    
    // Teste 3: Bellman-Ford com peso negativo
    printf("\n5. Teste Bellman-Ford com peso negativo:\n");
    GraphMatrix negativeGraph;
    initWeightedGraph(&negativeGraph, 4);
    
    addDirectedEdgeMatrix(&negativeGraph, 0, 1, 1);
    addDirectedEdgeMatrix(&negativeGraph, 1, 2, -3);
    addDirectedEdgeMatrix(&negativeGraph, 2, 3, 2);
    addDirectedEdgeMatrix(&negativeGraph, 3, 1, 1);
    
    bellmanFord(&negativeGraph, 0);
    
    return 0;
}