#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um nó da pilha
typedef struct Node {
    void *data;             // Ponteiro genérico para armazenar dados
    struct Node *next;      // Ponteiro para o próximo nó
} Node;

// Estrutura para representar a pilha
typedef struct Stack {
    Node *top;              // Ponteiro para o topo da pilha
} Stack;

// Função para inicializar a pilha
Stack* criaPilha() {
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

// Função para empilhar um elemento na pilha
void push(Stack *stack, void *data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

// Função para desempilhar um elemento da pilha
void* pop(Stack *stack) {
    if (stack->top == NULL) {
        return NULL; // Retorna NULL se a pilha estiver vazia
    }
    Node *temp = stack->top;
    void *data = temp->data;
    stack->top = temp->next;
    free(temp);
    return data;
}

// Função para verificar se a pilha está vazia
int isEmpty(Stack *stack) {
    return stack->top == NULL;
}

// Função para liberar a memória da pilha
void freeStack(Stack *stack) {
    while (!isEmpty(stack)) {
        pop(stack);
    }
    free(stack);
}

// Função principal com explicação sobre pilhas
int main() {
    /*
        Pilha é uma estrutura de dados do tipo LIFO (Last In, First Out),
        onde o último elemento inserido é o primeiro a ser removido.
        Operações principais:
        - push: adiciona um elemento no topo da pilha.
        - pop: remove o elemento do topo da pilha.
        - isEmpty: verifica se a pilha está vazia.
    */

    // Criando uma pilha genérica
    Stack *stack = criaPilha();

    // Exemplo de uso com inteiros
    int a = 10, b = 20, c = 30;
    push(stack, &a);
    push(stack, &b);
    push(stack, &c);

    // Desempilhando os elementos
    while (!isEmpty(stack)) {
        int *value = (int*)pop(stack);
        printf("Desempilhado: %d\n", *value);
    }

    // Liberando a memória da pilha
    freeStack(stack);

    return 0;
}