/* TSP MST-based 2-aproximação */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>

#define MAX_V 20
#define INF DBL_MAX

double dist[MAX_V][MAX_V];
bool visited[MAX_V];
int tour[MAX_V];
int tour_size = 0;

// Prim's MST
void prim_mst(int n, int parent[]) {
    double key[MAX_V];
    bool in_mst[MAX_V] = {false};
    
    for (int i = 0; i < n; i++) key[i] = INF;
    key[0] = 0;
    parent[0] = -1;
    
    for (int count = 0; count < n; count++) {
        double min = INF;
        int u = -1;
        
        for (int v = 0; v < n; v++) {
            if (!in_mst[v] && key[v] < min) {
                min = key[v];
                u = v;
            }
        }
        
        in_mst[u] = true;
        
        for (int v = 0; v < n; v++) {
            if (!in_mst[v] && dist[u][v] < key[v]) {
                parent[v] = u;
                key[v] = dist[u][v];
            }
        }
    }
}

// DFS na MST para construir tour
void dfs_tour(int u, int n, int parent[]) {
    visited[u] = true;
    tour[tour_size++] = u;
    
    for (int v = 0; v < n; v++) {
        if (parent[v] == u && !visited[v]) {
            dfs_tour(v, n, parent);
        }
    }
}

double tsp_mst_approx(int n) {
    int parent[MAX_V];
    prim_mst(n, parent);
    
    for (int i = 0; i < n; i++) visited[i] = false;
    tour_size = 0;
    
    dfs_tour(0, n, parent);
    tour[tour_size++] = 0; // Volta ao início
    
    double total = 0;
    for (int i = 0; i < tour_size - 1; i++) {
        total += dist[tour[i]][tour[i+1]];
    }
    
    return total;
}

int main() {
    printf("TSP MST 2-Aproximação\n\n");
    
    int n = 4;
    // Distâncias métricas
    double d[4][4] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dist[i][j] = d[i][j];
    
    double cost = tsp_mst_approx(n);
    
    printf("Tour: ");
    for (int i = 0; i < tour_size; i++) printf("%d ", tour[i]);
    printf("\nCusto: %.0f\n", cost);
    printf("Garantia: ≤ 2× OPT\n");
    
    return 0;
}
