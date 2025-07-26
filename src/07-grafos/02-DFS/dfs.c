#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da lista de adjacência
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Estrutura do grafo
typedef struct Graph {
    int numVertices;
    Node** adjLists;
    int* visited;
} Graph;

// Cria um novo nó
Node* createNode(int v) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Cria o grafo
Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;

    graph->adjLists = malloc(vertices * sizeof(Node*));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

// Adiciona aresta ao grafo (não direcionado)
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Função recursiva de DFS
void dfs(Graph* graph, int vertex) {
    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    Node* temp = graph->adjLists[vertex];
    while (temp != NULL) {
        int adjVertex = temp->vertex;

        if (graph->visited[adjVertex] == 0) {
            dfs(graph, adjVertex);
        }
        temp = temp->next;
    }
}

// Função principal
int main() {
    Graph* graph = createGraph(6);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 5);
    addEdge(graph, 4, 5);

    printf("DFS traversal: ");
    dfs(graph, 0);

    printf("\n");
    return 0;
}
