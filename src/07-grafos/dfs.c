#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// Implementação recursiva
void dfs_recursive(int graph[][MAX_VERTICES], int vertices, int vertex, bool visited[]) {
    visited[vertex] = true;
    printf("%d ", vertex);
    
    for (int i = 0; i < vertices; i++) {
        if (graph[vertex][i] == 1 && !visited[i]) {
            dfs_recursive(graph, vertices, i, visited);
        }
    }
}

void dfs(int graph[][MAX_VERTICES], int vertices, int start_vertex) {
    bool visited[MAX_VERTICES] = {false};
    
    printf("DFS traversal starting from vertex %d: ", start_vertex);
    dfs_recursive(graph, vertices, start_vertex, visited);
    printf("\n");
}

// Implementação iterativa com pilha
typedef struct {
    int items[MAX_VERTICES];
    int top;
} Stack;

Stack* create_stack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    return stack;
}

bool is_empty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, int value) {
    if (stack->top == MAX_VERTICES - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack->items[++stack->top] = value;
}

int pop(Stack* stack) {
    if (is_empty(stack)) {
        printf("Stack underflow\n");
        return -1;
    }
    return stack->items[stack->top--];
}

void dfs_iterative(int graph[][MAX_VERTICES], int vertices, int start_vertex) {
    bool visited[MAX_VERTICES] = {false};
    Stack* stack = create_stack();
    
    push(stack, start_vertex);
    
    printf("DFS iterative traversal starting from vertex %d: ", start_vertex);
    
    while (!is_empty(stack)) {
        int current_vertex = pop(stack);
        
        if (!visited[current_vertex]) {
            visited[current_vertex] = true;
            printf("%d ", current_vertex);
            
            // Adiciona vizinhos na pilha (em ordem reversa para manter ordem)
            for (int i = vertices - 1; i >= 0; i--) {
                if (graph[current_vertex][i] == 1 && !visited[i]) {
                    push(stack, i);
                }
            }
        }
    }
    
    printf("\n");
    free(stack);
}

int main() {
    int vertices = 5;
    int graph[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 1},
        {0, 1, 1, 0, 1},
        {0, 0, 1, 1, 0}
    };
    
    dfs(graph, vertices, 0);
    dfs_iterative(graph, vertices, 0);
    
    return 0;
}