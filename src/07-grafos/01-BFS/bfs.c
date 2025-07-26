#include <stdio.h>
#include <stdlib.h> 

// definicao da estrutura do nó da lista de adjacencia 
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Definição da estrutura do grafo
typedef struct Graph {
    int numVertices;
    Node** adjList;
    int* visited;
} Graph;

// Fila para BFS
typedef struct Queue {
    int items[100];
    int front;
    int rear;
} Queue;

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

int isEmpty(Queue* q) {
    return q->front == -1;
}

void enqueue(Queue* q, int value) {
    if (q->rear == 99) {
        printf("Queue is full\n");
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    int item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
        q->front = -1;
        q->rear = -1;
    }
    return item;
}

// Função para criar um novo nó
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjList = (Node**)malloc(vertices * sizeof(Node*));
    graph->visited = (int*)malloc(vertices * sizeof(int));
    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

// Adiciona uma aresta ao grafo
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    // Para grafos não direcionados
    newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = src;
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

// Função para realizar a busca em largura (BFS)
void bfs(Graph* graph, int start) {
    Queue* q = createQueue();
    graph->visited[start] = 1;
    enqueue(q, start);

    while (!isEmpty(q)) {
        int currentVertex = dequeue(q);
        printf("Visitando vértice %d\n", currentVertex);

        Node* temp = graph->adjList[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;
            if (!graph->visited[adjVertex]) {
                graph->visited[adjVertex] = 1;
                enqueue(q, adjVertex);
            }
            temp = temp->next;
        }
    }
    free(q);
}
// Função para imprimir o grafo
void printGraph(Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        Node* temp = graph->adjList[v];
        printf("Vértice %d: ", v);
        while (temp) {
            printf("→ %d ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}
// Função principal
int main() {
    int vertices, edges, src, dest;
    printf("Digite o número de vértices: ");
    scanf("%d", &vertices);
    
    Graph* graph = createGraph(vertices);
    
    printf("Digite o número de arestas: ");
    scanf("%d", &edges);
    
    for (int i = 0; i < edges; i++) {
        printf("Digite a origem e o destino da aresta %d: ", i + 1);
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }
    
    printf("Grafo criado:\n");
    printGraph(graph);
    
    printf("Digite o vértice inicial para BFS: ");
    scanf("%d", &src);
    
    printf("Resultado da BFS a partir do vértice %d:\n", src);
    bfs(graph, src);
    
    // Libera a memória
    for (int i = 0; i < vertices; i++) {
        Node* temp = graph->adjList[i];
        while (temp) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(graph->adjList);
    free(graph->visited);
    free(graph);
    
    return 0;
}