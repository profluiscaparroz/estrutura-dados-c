#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 5 // Número de vértices no grafo

// Função para encontrar o vértice com a menor distância que ainda não foi processado
int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

// Função para imprimir o resultado
void printSolution(int dist[]) {
    printf("Vértice \t Distância da origem\n");
    for (int i = 0; i < V; i++) {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}

// Implementação do algoritmo de Dijkstra
void dijkstra(int graph[V][V], int src) {
    int dist[V]; // Array para armazenar as distâncias mínimas
    bool sptSet[V]; // sptSet[i] será verdadeiro se o vértice i já foi processado

    // Inicializa todas as distâncias como INFINITO e sptSet[] como falso
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    // A distância do vértice de origem para ele mesmo é sempre 0
    dist[src] = 0;

    // Encontra o caminho mais curto para todos os vértices
    for (int count = 0; count < V - 1; count++) {
        // Escolhe o vértice de menor distância que ainda não foi processado
        int u = minDistance(dist, sptSet);

        // Marca o vértice como processado
        sptSet[u] = true;

        // Atualiza o valor da distância dos vértices adjacentes do vértice escolhido
        for (int v = 0; v < V; v++) {
            // Atualiza dist[v] se não estiver em sptSet, existe uma aresta de u para v,
            // e o peso total do caminho de src para v através de u é menor que o valor atual de dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Imprime o array de distâncias
    printSolution(dist);
}

int main() {
    // Exemplo de grafo representado por uma matriz de adjacência
    int graph[V][V] = {
        {0, 10, 0, 0, 5},
        {0, 0, 1, 0, 2},
        {0, 0, 0, 4, 0},
        {7, 0, 6, 0, 0},
        {0, 3, 9, 2, 0}
    };

    // Executa o algoritmo de Dijkstra a partir do vértice 0
    dijkstra(graph, 0);

    return 0;
}