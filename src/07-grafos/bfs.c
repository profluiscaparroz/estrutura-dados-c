#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

typedef struct {
    int front, rear;
    int items[MAX_VERTICES];
} Queue;

Queue* create_queue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

bool is_empty(Queue* queue) {
    return queue->front == -1;
}

void enqueue(Queue* queue, int value) {
    if (queue->rear == MAX_VERTICES - 1) {
        printf("Queue is full\n");
        return;
    }
    
    if (queue->front == -1) {
        queue->front = 0;
    }
    queue->rear++;
    queue->items[queue->rear] = value;
}

int dequeue(Queue* queue) {
    if (is_empty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    
    int item = queue->items[queue->front];
    queue->front++;
    
    if (queue->front > queue->rear) {
        queue->front = queue->rear = -1;
    }
    
    return item;
}

void bfs(int graph[][MAX_VERTICES], int vertices, int start_vertex) {
    bool visited[MAX_VERTICES] = {false};
    Queue* queue = create_queue();
    
    visited[start_vertex] = true;
    enqueue(queue, start_vertex);
    
    printf("BFS traversal starting from vertex %d: ", start_vertex);
    
    while (!is_empty(queue)) {
        int current_vertex = dequeue(queue);
        printf("%d ", current_vertex);
        
        for (int i = 0; i < vertices; i++) {
            if (graph[current_vertex][i] == 1 && !visited[i]) {
                visited[i] = true;
                enqueue(queue, i);
            }
        }
    }
    
    printf("\n");
    free(queue);
}

int main() {
    int vertices = 5;
    int graph[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 1, 0},
        {1, 1, 0, 1, 1},
        {0, 1, 1, 0, 1},
        {0, 0, 1, 1, 0}
    };
    
    bfs(graph, vertices, 0);
    
    return 0;
}