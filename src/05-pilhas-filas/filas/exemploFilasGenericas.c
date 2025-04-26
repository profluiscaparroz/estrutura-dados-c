#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para um nó da fila
typedef struct Node {
    void *data;             // Ponteiro genérico para armazenar qualquer tipo de dado
    struct Node *next;      // Ponteiro para o próximo nó
} Node;

// Estrutura para a fila
typedef struct Queue {
    Node *front;            // Ponteiro para o início da fila
    Node *rear;             // Ponteiro para o final da fila
    size_t dataSize;        // Tamanho do tipo de dado armazenado
} Queue;

// Função para inicializar a fila
void initQueue(Queue *q, size_t dataSize) {
    q->front = q->rear = NULL;
    q->dataSize = dataSize;
}

// Função para verificar se a fila está vazia
int isEmpty(Queue *q) {
    return q->front == NULL;
}

// Função para enfileirar um elemento
void enqueue(Queue *q, void *data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Erro ao alocar memória para o nó.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = malloc(q->dataSize);
    if (!newNode->data) {
        fprintf(stderr, "Erro ao alocar memória para os dados.\n");
        free(newNode);
        exit(EXIT_FAILURE);
    }
    memcpy(newNode->data, data, q->dataSize);
    newNode->next = NULL;

    if (q->rear) {
        q->rear->next = newNode;
    }
    q->rear = newNode;

    if (!q->front) {
        q->front = newNode;
    }
}

// Função para desenfileirar um elemento
void dequeue(Queue *q, void *data) {
    if (isEmpty(q)) {
        fprintf(stderr, "Erro: a fila está vazia.\n");
        return;
    }

    Node *temp = q->front;
    memcpy(data, temp->data, q->dataSize);

    q->front = q->front->next;
    if (!q->front) {
        q->rear = NULL;
    }

    free(temp->data);
    free(temp);
}

// Função para liberar a memória da fila
void freeQueue(Queue *q) {
    Node *current = q->front;
    while (current) {
        Node *temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
    q->front = q->rear = NULL;
}

int main() {
    /*
     * Este programa demonstra o uso de uma fila genérica que pode armazenar
     * qualquer tipo de dado usando ponteiros void*. A abordagem utilizada
     * envolve a criação de uma estrutura de fila que armazena o tamanho do
     * tipo de dado, permitindo que os dados sejam copiados para a memória
     * alocada dinamicamente. Isso garante que a fila seja flexível e possa
     * ser usada para diferentes tipos de dados.
     */

    Queue q;
    initQueue(&q, sizeof(int)); // Inicializa a fila para armazenar inteiros

    int value = 10;
    enqueue(&q, &value); // Enfileira o valor 10

    value = 20;
    enqueue(&q, &value); // Enfileira o valor 20

    int dequeuedValue;
    dequeue(&q, &dequeuedValue); // Desenfileira o primeiro valor
    printf("Valor desenfileirado: %d\n", dequeuedValue);

    dequeue(&q, &dequeuedValue); // Desenfileira o próximo valor
    printf("Valor desenfileirado: %d\n", dequeuedValue);

    freeQueue(&q); // Libera a memória da fila

    return 0;
}