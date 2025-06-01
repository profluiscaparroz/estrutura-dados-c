#include<stdio.h>

#define V 4

void addEdge(int mat[V][V], int i, int j) {
    mat[i][j] = 1;
    mat[j][i] = 1; // Since the graph is undirected
}

void displayMatrix(int mat[V][V]) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
}

int main() {
    // Create a graph with 4 vertices and no edges
    // Note that all values are initialized as 0
    int mat[V][V] = {0};

    // Now add edges one by one
    addEdge(mat, 0, 1);
    addEdge(mat, 0, 2);
    addEdge(mat, 1, 2);
    addEdge(mat, 2, 3);

    /* Alternatively, we can also create using the below
       code if we know all edges in advance

    int mat[V][V] = {
        {0, 1, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {0, 0, 1, 0}
    }; */

    printf("Adjacency Matrix Representation\n");
    displayMatrix(mat);

    return 0;
}