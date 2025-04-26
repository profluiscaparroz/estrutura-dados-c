#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um nó da pilha
typedef struct Node {
    int data; // Dado armazenado no nó
    struct Node* next; // Ponteiro para o próximo nó
} Node;

// Estrutura para representar a pilha
typedef struct Stack {
    Node* top; // Ponteiro para o topo da pilha
} Stack;

// Função para inicializar a pilha
void initializeStack(Stack* stack) {
    stack->top = NULL; // Inicializa o topo como NULL
}

// Função para verificar se a pilha está vazia
int isEmpty(Stack* stack) {
    return stack->top == NULL;
}

// Função para empilhar (push) um elemento na pilha
void push(Stack* stack, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // Aloca memória para o novo nó
    if (newNode == NULL) {
        printf("Erro: Memória insuficiente.\n");
        exit(1);
    }
    newNode->data = value; // Atribui o valor ao nó
    newNode->next = stack->top; // Aponta o próximo nó para o topo atual
    stack->top = newNode; // Atualiza o topo da pilha
}

// Função para desempilhar (pop) um elemento da pilha
int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Erro: Pilha vazia.\n");
        exit(1);
    }
    Node* temp = stack->top; // Armazena o nó do topo
    int poppedValue = temp->data; // Armazena o valor do nó
    stack->top = temp->next; // Atualiza o topo para o próximo nó
    free(temp); // Libera a memória do nó removido
    return poppedValue; // Retorna o valor removido
}

// Função para visualizar o elemento no topo da pilha
int peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Erro: Pilha vazia.\n");
        exit(1);
    }
    return stack->top->data; // Retorna o valor do topo
}

// Função principal
int main() {
    // Explicação sobre pilhas:
    // Pilhas são estruturas de dados do tipo LIFO (Last In, First Out), ou seja,
    // o último elemento inserido é o primeiro a ser removido. Operações básicas
    // incluem empilhar (push), desempilhar (pop) e visualizar o topo (peek).

    Stack stack; // Declara uma pilha
    initializeStack(&stack); // Inicializa a pilha

    // Exemplo de uso da pilha
    push(&stack, 10); // Empilha o valor 10
    push(&stack, 20); // Empilha o valor 20
    push(&stack, 30); // Empilha o valor 30

    printf("Topo da pilha: %d\n", peek(&stack)); // Exibe o topo da pilha

    printf("Desempilhando: %d\n", pop(&stack)); // Remove o topo da pilha
    printf("Desempilhando: %d\n", pop(&stack)); // Remove o próximo topo

    printf("Topo da pilha após desempilhar: %d\n", peek(&stack)); // Exibe o novo topo

    return 0;
}