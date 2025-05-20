#include <stdio.h>

#define SIZE 100
#define NULL_PTR -1

int dado[SIZE];        // Armazena os dados
int proximo[SIZE];        // Simula os ponteiros
int inicio = NULL_PTR;   // Início da lista
int lista_livre = 0;     // Próximo índice livre

// Inicializa os "ponteiros" livres
void inicia_lista() {
    for (int i = 0; i < SIZE - 1; i++) {
        proximo[i] = i + 1;
    }
    proximo[SIZE - 1] = NULL_PTR;
}

// Insere no início
void insere(int valor) {
    if (lista_livre == NULL_PTR) {
        printf("Lista cheia!\n");
        return;
    }
    int novo_no = lista_livre;
    lista_livre = proximo[lista_livre];

    dado[novo_no] = valor;
    proximo[novo_no] = inicio;
    inicio = novo_no;
}

// Imprime lista
void exibir_lista() {
    int current = inicio;
    while (current != NULL_PTR) {
        printf("%d -> ", dado[current]);
        current = proximo[current];
    }
    printf("NULL\n");
}

int main() {
    inicia_lista();

    insere(10);
    insere(20);
    insere(30);

    exibir_lista();  // Saída esperada: 30 -> 20 -> 10 -> NULL

    return 0;
}
