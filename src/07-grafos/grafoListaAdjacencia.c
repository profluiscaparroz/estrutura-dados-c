#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Estrutura para representar um nó da lista de adjacência
typedef struct AdjListNode {
    int dest;
    int weight; // Para grafos ponderados
    struct AdjListNode* next;
} AdjListNode;

// Estrutura para representar uma lista de adjacência
typedef struct AdjList {
    struct AdjListNode* head;
} AdjList;

// Estrutura do grafo
typedef struct Graph {
    int V; // Número de vértices
    struct AdjList* array;
} Graph;

// Criar um novo nó da lista de adjacência
AdjListNode* newAdjListNode(int dest, int weight) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Criar um grafo com V vértices
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    
    // Criar array de listas de adjacência
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));
    
    // Inicializar cada lista como vazia
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
        
    return graph;
}

// Adicionar aresta ao grafo (não direcionado)
void addEdge(Graph* graph, int src, int dest, int weight) {
    // Adicionar aresta de src para dest
    AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    
    // Para grafo não direcionado, adicionar também de dest para src
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Adicionar aresta direcionada
void addDirectedEdge(Graph* graph, int src, int dest, int weight) {
    AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

// Imprimir o grafo
void printGraph(Graph* graph) {
    for (int v = 0; v < graph->V; ++v) {
        AdjListNode* pCrawl = graph->array[v].head;
        printf("Lista de adjacência do vértice %d:\n head", v);
        while (pCrawl) {
            printf(" -> %d(%d)", pCrawl->dest, pCrawl->weight);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

// Liberar memória do grafo
void freeGraph(Graph* graph) {
    for (int v = 0; v < graph->V; v++) {
        AdjListNode* pCrawl = graph->array[v].head;
        while (pCrawl) {
            AdjListNode* temp = pCrawl;
            pCrawl = pCrawl->next;
            free(temp);
        }
    }
    free(graph->array);
    free(graph);
}

// Busca em profundidade (DFS) recursiva
void DFSUtil(Graph* graph, int v, bool visited[]) {
    visited[v] = true;
    printf("%d ", v);
    
    AdjListNode* pCrawl = graph->array[v].head;
    while (pCrawl != NULL) {
        int adjVertex = pCrawl->dest;
        if (!visited[adjVertex])
            DFSUtil(graph, adjVertex, visited);
        pCrawl = pCrawl->next;
    }
}

// Busca em profundidade
void DFS(Graph* graph, int startVertex) {
    bool* visited = (bool*)malloc(graph->V * sizeof(bool));
    for (int i = 0; i < graph->V; i++)
        visited[i] = false;
    
    printf("DFS iniciando do vértice %d: ", startVertex);
    DFSUtil(graph, startVertex, visited);
    printf("\n");
    
    free(visited);
}

// Estrutura para fila (BFS)
typedef struct Queue {
    int* items;
    int front;
    int rear;
    int capacity;
} Queue;

Queue* createQueue(int capacity) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->items = (int*)malloc(capacity * sizeof(int));
    q->front = -1;
    q->rear = -1;
    q->capacity = capacity;
    return q;
}

bool isEmpty(Queue* q) {
    return q->rear == -1;
}

void enqueue(Queue* q, int value) {
    if (q->rear == q->capacity - 1) {
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

void freeQueue(Queue* q) {
    free(q->items);
    free(q);
}

// Busca em largura (BFS)
void BFS(Graph* graph, int startVertex) {
    bool* visited = (bool*)malloc(graph->V * sizeof(bool));
    for (int i = 0; i < graph->V; i++)
        visited[i] = false;
    
    Queue* q = createQueue(graph->V);
    
    visited[startVertex] = true;
    enqueue(q, startVertex);
    
    printf("BFS iniciando do vértice %d: ", startVertex);
    
    while (!isEmpty(q)) {
        int currentVertex = dequeue(q);
        printf("%d ", currentVertex);
        
        AdjListNode* temp = graph->array[currentVertex].head;
        while (temp) {
            int adjVertex = temp->dest;
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                enqueue(q, adjVertex);
            }
            temp = temp->next;
        }
    }
    printf("\n");
    
    free(visited);
    freeQueue(q);
}

// Detectar ciclo usando DFS (para grafo direcionado)
bool isCyclicUtil(Graph* graph, int v, bool visited[], bool recStack[]) {
    visited[v] = true;
    recStack[v] = true;
    
    AdjListNode* temp = graph->array[v].head;
    while (temp) {
        int adjVertex = temp->dest;
        if (!visited[adjVertex] && isCyclicUtil(graph, adjVertex, visited, recStack))
            return true;
        else if (recStack[adjVertex])
            return true;
        temp = temp->next;
    }
    
    recStack[v] = false;
    return false;
}

bool isCyclic(Graph* graph) {
    bool* visited = (bool*)malloc(graph->V * sizeof(bool));
    bool* recStack = (bool*)malloc(graph->V * sizeof(bool));
    
    for (int i = 0; i < graph->V; i++) {
        visited[i] = false;
        recStack[i] = false;
    }
    
    for (int i = 0; i < graph->V; i++) {
        if (!visited[i] && isCyclicUtil(graph, i, visited, recStack)) {
            free(visited);
            free(recStack);
            return true;
        }
    }
    
    free(visited);
    free(recStack);
    return false;
}

// Contar componentes conectados
int countConnectedComponents(Graph* graph) {
    bool* visited = (bool*)malloc(graph->V * sizeof(bool));
    for (int i = 0; i < graph->V; i++)
        visited[i] = false;
    
    int count = 0;
    for (int v = 0; v < graph->V; v++) {
        if (!visited[v]) {
            DFSUtil(graph, v, visited);
            count++;
        }
    }
    
    free(visited);
    return count;
}

// Encontrar grau de um vértice
int getVertexDegree(Graph* graph, int vertex) {
    int degree = 0;
    AdjListNode* temp = graph->array[vertex].head;
    while (temp) {
        degree++;
        temp = temp->next;
    }
    return degree;
}

int main() {
    printf("=== Demonstração Completa de Grafo com Lista de Adjacência ===\n\n");
    
    // Teste 1: Grafo não direcionado
    printf("1. Criando grafo não direcionado com 5 vértices:\n");
    Graph* graph = createGraph(5);
    
    // Adicionar arestas
    addEdge(graph, 0, 1, 2);
    addEdge(graph, 0, 4, 6);
    addEdge(graph, 1, 2, 3);
    addEdge(graph, 1, 3, 8);
    addEdge(graph, 1, 4, 5);
    addEdge(graph, 2, 3, 7);
    
    printGraph(graph);
    
    printf("\n2. Algoritmos de busca:\n");
    BFS(graph, 0);
    DFS(graph, 0);
    
    printf("\n3. Análise do grafo:\n");
    printf("Componentes conectados: %d\n", countConnectedComponents(graph));
    printf("Grau do vértice 1: %d\n", getVertexDegree(graph, 1));
    
    freeGraph(graph);
    
    // Teste 2: Grafo direcionado para detecção de ciclo
    printf("\n4. Teste de detecção de ciclo (grafo direcionado):\n");
    Graph* directedGraph = createGraph(4);
    
    addDirectedEdge(directedGraph, 0, 1, 1);
    addDirectedEdge(directedGraph, 1, 2, 1);
    addDirectedEdge(directedGraph, 2, 3, 1);
    // addDirectedEdge(directedGraph, 3, 1, 1); // Descomente para criar um ciclo
    
    printf("Grafo direcionado:\n");
    printGraph(directedGraph);
    printf("Tem ciclo: %s\n", isCyclic(directedGraph) ? "Sim" : "Não");
    
    // Adicionar uma aresta para criar ciclo
    addDirectedEdge(directedGraph, 3, 1, 1);
    printf("\nApós adicionar aresta 3->1:\n");
    printf("Tem ciclo: %s\n", isCyclic(directedGraph) ? "Sim" : "Não");
    
    freeGraph(directedGraph);
    
    // Teste 3: Grafo desconectado
    printf("\n5. Teste com grafo desconectado:\n");
    Graph* disconnectedGraph = createGraph(6);
    
    addEdge(disconnectedGraph, 0, 1, 1);
    addEdge(disconnectedGraph, 1, 2, 1);
    addEdge(disconnectedGraph, 3, 4, 1);
    // Vértice 5 fica isolado
    
    printf("Grafo desconectado:\n");
    printGraph(disconnectedGraph);
    printf("Componentes conectados: %d\n", countConnectedComponents(disconnectedGraph));
    
    freeGraph(disconnectedGraph);
    
    return 0;
}