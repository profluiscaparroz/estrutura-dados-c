#include <stdio.h>
#include <stdlib.h>

// Estrutura para um nó da lista duplamente circular
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// Função para criar um novo nó
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = newNode->prev = newNode; // Nó aponta para si mesmo
    return newNode;
}

// Função para inserir um nó no final da lista
void insertEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node* tail = (*head)->prev;

    tail->next = newNode;
    newNode->prev = tail;
    newNode->next = *head;
    (*head)->prev = newNode;
}

// Função para exibir a lista
void displayList(Node* head) {
    if (head == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    Node* temp = head;
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

// Função para liberar a memória da lista
void freeList(Node** head) {
    if (*head == NULL) return;

    Node* current = *head;
    Node* nextNode;

    do {
        nextNode = current->next;
        free(current);
        current = nextNode;
    } while (current != *head);

    *head = NULL;
}

int main() {
    Node* head = NULL;

    // Inserindo elementos na lista
    insertEnd(&head, 10);
    insertEnd(&head, 20);
    insertEnd(&head, 30);

    // Exibindo a lista
    printf("Lista duplamente circular: ");
    displayList(head);

    // Liberando a memória
    freeList(&head);

    return 0;
}