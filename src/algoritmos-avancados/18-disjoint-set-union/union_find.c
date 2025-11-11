#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Estrutura do Union-Find
typedef struct {
    int *parent;
    int *rank;
    int n;
    int count;  // Número de componentes conectados
} UnionFind;

// Criar Union-Find
UnionFind* createUnionFind(int n) {
    UnionFind *uf = (UnionFind *)malloc(sizeof(UnionFind));
    uf->n = n;
    uf->count = n;
    uf->parent = (int *)malloc(sizeof(int) * n);
    uf->rank = (int *)calloc(n, sizeof(int));
    
    for (int i = 0; i < n; i++) {
        uf->parent[i] = i;
    }
    
    return uf;
}

// Find com path compression
int find(UnionFind *uf, int x) {
    if (uf->parent[x] != x) {
        uf->parent[x] = find(uf, uf->parent[x]);  // Path compression
    }
    return uf->parent[x];
}

// Union com union by rank
bool unionSets(UnionFind *uf, int x, int y) {
    int root_x = find(uf, x);
    int root_y = find(uf, y);
    
    if (root_x == root_y) {
        return false;  // Já estão no mesmo conjunto
    }
    
    // Union by rank
    if (uf->rank[root_x] < uf->rank[root_y]) {
        uf->parent[root_x] = root_y;
    } else if (uf->rank[root_x] > uf->rank[root_y]) {
        uf->parent[root_y] = root_x;
    } else {
        uf->parent[root_y] = root_x;
        uf->rank[root_x]++;
    }
    
    uf->count--;
    return true;
}

// Verificar se estão conectados
bool connected(UnionFind *uf, int x, int y) {
    return find(uf, x) == find(uf, y);
}

// Obter número de componentes
int getCount(UnionFind *uf) {
    return uf->count;
}

// Liberar memória
void freeUnionFind(UnionFind *uf) {
    free(uf->parent);
    free(uf->rank);
    free(uf);
}

// Exemplo de uso
int main() {
    int n = 6;
    UnionFind *uf = createUnionFind(n);
    
    printf("=== Union-Find com %d elementos ===\n\n", n);
    printf("Componentes iniciais: %d\n", getCount(uf));
    
    printf("\nUnindo 0-1...\n");
    unionSets(uf, 0, 1);
    printf("Componentes: %d\n", getCount(uf));
    
    printf("\nUnindo 2-3...\n");
    unionSets(uf, 2, 3);
    printf("Componentes: %d\n", getCount(uf));
    
    printf("\nUnindo 0-2...\n");
    unionSets(uf, 0, 2);
    printf("Componentes: %d\n", getCount(uf));
    
    printf("\nUnindo 4-5...\n");
    unionSets(uf, 4, 5);
    printf("Componentes: %d\n", getCount(uf));
    
    printf("\n=== Consultas de Conectividade ===\n");
    printf("0 e 3 conectados? %s\n", connected(uf, 0, 3) ? "Sim" : "Não");
    printf("1 e 2 conectados? %s\n", connected(uf, 1, 2) ? "Sim" : "Não");
    printf("0 e 4 conectados? %s\n", connected(uf, 0, 4) ? "Sim" : "Não");
    printf("4 e 5 conectados? %s\n", connected(uf, 4, 5) ? "Sim" : "Não");
    
    freeUnionFind(uf);
    
    return 0;
}
