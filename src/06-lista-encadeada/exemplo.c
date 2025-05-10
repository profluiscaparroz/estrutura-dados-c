#include <stdio.h>

#define SIZE 100
#define NULL_PTR -1

int data[SIZE];        // Armazena os dados
int next[SIZE];        // Simula os ponteiros
int head = NULL_PTR;   // Início da lista
int free_list = 0;     // Próximo índice livre

// Inicializa os "ponteiros" livres
void init_list() {
    for (int i = 0; i < SIZE - 1; i++) {
        next[i] = i + 1;
    }
    next[SIZE - 1] = NULL_PTR;
}

// Insere no início
void insert(int value) {
    if (free_list == NULL_PTR) {
        printf("Lista cheia!\n");
        return;
    }
    int new_node = free_list;
    free_list = next[free_list];

    data[new_node] = value;
    next[new_node] = head;
    head = new_node;
}

// Imprime lista
void print_list() {
    int current = head;
    while (current != NULL_PTR) {
        printf("%d -> ", data[current]);
        current = next[current];
    }
    printf("NULL\n");
}

int main() {
    init_list();

    insert(10);
    insert(20);
    insert(30);

    print_list();  // Saída esperada: 30 -> 20 -> 10 -> NULL

    return 0;
}
