#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct {
    int numVertices;
    int directed;
    Node* adjList[MAX_VERTICES];
} Graph;

Node* createNode(int v) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices, int directed) {
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->directed = directed;
    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    if (!graph->directed) {
        newNode = createNode(src);
        newNode->next = graph->adjList[dest];
        graph->adjList[dest] = newNode;
    }
}

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

int isBipartite(Graph* graph) {
    int color[MAX_VERTICES];
    for (int i = 0; i < graph->numVertices; i++) color[i] = -1;

    for (int start = 0; start < graph->numVertices; start++) {
        if (color[start] != -1) continue;

        int queue[MAX_VERTICES], front = 0, rear = 0;
        color[start] = 0;
        queue[rear++] = start;

        while (front < rear) {
            int u = queue[front++];

            Node* temp = graph->adjList[u];
            while (temp) {
                int v = temp->vertex;
                if (color[v] == -1) {
                    color[v] = 1 - color[u];
                    queue[rear++] = v;
                } else if (color[v] == color[u]) {
                    return 0;  // conflito de cor
                }
                temp = temp->next;
            }
        }
    }
    return 1;
}

void menu() {
    Graph* graph = NULL;
    int choice, vertices, directed, src, dest;

    while (1) {
        printf("\n===== MENU DO GRAFO =====\n");
        printf("1. Criar Grafo\n");
        printf("2. Adicionar Aresta\n");
        printf("3. Imprimir Grafo\n");
        printf("4. Verificar se é Bipartido\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Número de vértices: ");
                scanf("%d", &vertices);
                printf("Grafo é direcionado? (1 = sim, 0 = não): ");
                scanf("%d", &directed);
                graph = createGraph(vertices, directed);
                printf("Grafo criado com sucesso.\n");
                break;

            case 2:
                if (!graph) {
                    printf("Crie o grafo primeiro!\n");
                    break;
                }
                printf("Origem da aresta: ");
                scanf("%d", &src);
                printf("Destino da aresta: ");
                scanf("%d", &dest);
                if (src >= graph->numVertices || dest >= graph->numVertices) {
                    printf("Vértice inválido.\n");
                    break;
                }
                addEdge(graph, src, dest);
                printf("Aresta adicionada.\n");
                break;

            case 3:
                if (!graph) {
                    printf("Crie o grafo primeiro!\n");
                    break;
                }
                printGraph(graph);
                break;

            case 4:
                if (!graph) {
                    printf("Crie o grafo primeiro!\n");
                    break;
                }
                if (isBipartite(graph)) {
                    printf("O grafo É bipartido.\n");
                } else {
                    printf("O grafo NÃO é bipartido.\n");
                }
                break;

            case 0:
                printf("Encerrando...\n");
                return;

            default:
                printf("Opção inválida.\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
