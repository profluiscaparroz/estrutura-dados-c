#include <stdio.h>
#include <stdlib.h>

// Definição de um nó da lista encadeada
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Função para criar um novo nó
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Função para imprimir a lista
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Função para liberar a memória da lista
void freeList(Node* head) {
    Node* current = head;
    Node* nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
}

int main() {
    // Criando nós da lista
    Node* head = createNode(10);
    head->next = createNode(20);
    head->next->next = createNode(30);

    // Imprimindo a lista
    printf("Lista encadeada: ");
    printList(head);

    // Liberando a memória
    freeList(head);

    return 0;
}