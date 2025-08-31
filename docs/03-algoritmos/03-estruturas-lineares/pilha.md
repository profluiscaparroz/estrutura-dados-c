# Pilha (Stack)

Conceito
- LIFO: último que entra é o primeiro a sair.
- Operações: push, pop, top.

Implementação com array dinâmico
```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int* data;
    int top;
    int capacity;
} Stack;

Stack* create_stack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->data = (int*)malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

bool is_empty(Stack* stack) {
    return stack->top == -1;
}

bool is_full(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

void push(Stack* stack, int item) {
    if (is_full(stack)) {
        printf("Stack overflow\n");
        return;
    }
    stack->data[++stack->top] = item;
    printf("Pushed %d\n", item);
}

int pop(Stack* stack) {
    if (is_empty(stack)) {
        printf("Stack underflow\n");
        return -1;
    }
    return stack->data[stack->top--];
}

int peek(Stack* stack) {
    if (is_empty(stack)) {
        printf("Stack is empty\n");
        return -1;
    }
    return stack->data[stack->top];
}

void destroy_stack(Stack* stack) {
    free(stack->data);
    free(stack);
}

int main() {
    Stack* stack = create_stack(5);
    
    push(stack, 10);
    push(stack, 20);
    push(stack, 30);
    
    printf("Top element: %d\n", peek(stack));
    printf("Popped: %d\n", pop(stack));
    printf("Top element after pop: %d\n", peek(stack));
    
    destroy_stack(stack);
    return 0;
}
```

Complexidade
- push/pop/top: O(1) amortizado.