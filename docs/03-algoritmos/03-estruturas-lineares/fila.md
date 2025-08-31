# Fila (Queue)

Conceito
- FIFO: primeiro que entra é o primeiro a sair.

Implementação com buffer circular
```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int* data;
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

Queue* create_queue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->data = (int*)malloc(capacity * sizeof(int));
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

bool is_empty(Queue* queue) {
    return queue->size == 0;
}

bool is_full(Queue* queue) {
    return queue->size == queue->capacity;
}

void enqueue(Queue* queue, int item) {
    if (is_full(queue)) {
        printf("Queue overflow\n");
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear] = item;
    queue->size++;
    printf("Enqueued %d\n", item);
}

int dequeue(Queue* queue) {
    if (is_empty(queue)) {
        printf("Queue underflow\n");
        return -1;
    }
    int item = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return item;
}

int front(Queue* queue) {
    if (is_empty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    return queue->data[queue->front];
}

void destroy_queue(Queue* queue) {
    free(queue->data);
    free(queue);
}

int main() {
    Queue* queue = create_queue(5);
    
    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    
    printf("Front element: %d\n", front(queue));
    printf("Dequeued: %d\n", dequeue(queue));
    printf("Front element after dequeue: %d\n", front(queue));
    
    destroy_queue(queue);
    return 0;
}
```

Complexidade
- push/pop: O(1).