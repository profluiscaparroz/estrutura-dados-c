#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data; // Dado armazenado no nó
    struct Node* next; // Ponteiro para o próximo nó
    struct Node* prev; // Ponteiro para o nó anterior
} Node;

typedef struct Deque {
    Node* front; // Ponteiro para o início da fila
    Node* rear;  // Ponteiro para o final da fila
} Deque;

// Função para criar um novo nó
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // Aloca memória para o nó
    newNode->data = data; // Define o dado do nó
    newNode->next = NULL; // Inicializa o ponteiro para o próximo como NULL
    newNode->prev = NULL; // Inicializa o ponteiro para o anterior como NULL
    return newNode; // Retorna o nó criado
}

// Função para inicializar a fila duplamente ligada
Deque* createDeque() {
    Deque* deque = (Deque*)malloc(sizeof(Deque)); // Aloca memória para a estrutura da fila
    deque->front = NULL; // Inicializa o início como NULL
    deque->rear = NULL;  // Inicializa o final como NULL
    return deque; // Retorna a fila criada
}

// Função para adicionar um elemento no final da fila
void enqueueRear(Deque* deque, int data) {
    Node* newNode = createNode(data); // Cria um novo nó
    if (deque->rear == NULL) { // Verifica se a fila está vazia
        deque->front = deque->rear = newNode; // Define o novo nó como início e fim
    } else {
        deque->rear->next = newNode; // Atualiza o próximo do nó atual do final
        newNode->prev = deque->rear; // Define o anterior do novo nó como o nó atual do final
        deque->rear = newNode; // Atualiza o final da fila
    }
}

// Função para remover um elemento do início da fila
int dequeueFront(Deque* deque) {
    if (deque->front == NULL) { // Verifica se a fila está vazia
        printf("Fila vazia!\n");
        return -1; // Retorna -1 para indicar erro
    }
    Node* temp = deque->front; // Armazena o nó a ser removido
    int data = temp->data; // Armazena o dado do nó
    deque->front = deque->front->next; // Atualiza o início da fila
    if (deque->front == NULL) { // Verifica se a fila ficou vazia
        deque->rear = NULL; // Atualiza o final para NULL
    } else {
        deque->front->prev = NULL; // Remove a referência ao nó anterior
    }
    free(temp); // Libera a memória do nó removido
    return data; // Retorna o dado removido
}

// Função para exibir os elementos da fila
void displayDeque(Deque* deque) {
    Node* current = deque->front; // Começa pelo início da fila
    printf("Fila: ");
    while (current != NULL) { // Percorre até o final da fila
        printf("%d ", current->data); // Imprime o dado do nó atual
        current = current->next; // Move para o próximo nó
    }
    printf("\n");
}

// Função principal para demonstrar o uso da fila duplamente ligada
int main() {
    Deque* deque = createDeque(); // Cria a fila

    enqueueRear(deque, 10); // Adiciona 10 no final
    enqueueRear(deque, 20); // Adiciona 20 no final
    enqueueRear(deque, 30); // Adiciona 30 no final

    displayDeque(deque); // Exibe a fila

    printf("Removido: %d\n", dequeueFront(deque)); // Remove do início
    displayDeque(deque); // Exibe a fila novamente

    destroyDeque(deque); // Libera a memória alocada para a fila
    return 0; // Finaliza o programa
}