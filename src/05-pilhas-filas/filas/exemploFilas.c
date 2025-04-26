#include <stdio.h>
#include <stdlib.h>

#define MAX 100 // Tamanho máximo da fila

// Estrutura da fila
typedef struct {
    int itens[MAX];
    int frente; // Índice do primeiro elemento
    int tras;   // Índice do último elemento
} Fila;

// Inicializa a fila
void inicializarFila(Fila *fila) {
    fila->frente = -1;
    fila->tras = -1;
}

// Verifica se a fila está cheia
int estaCheia(Fila *fila) {
    return fila->tras == MAX - 1;
}

// Verifica se a fila está vazia
int estaVazia(Fila *fila) {
    return fila->frente == -1 || fila->frente > fila->tras;
}

// Adiciona um elemento à fila
void enfileirar(Fila *fila, int valor) {
    if (estaCheia(fila)) {
        printf("Erro: Fila cheia!\n");
        return;
    }
    if (fila->frente == -1) {
        fila->frente = 0; // Define o início da fila
    }
    fila->tras++;
    fila->itens[fila->tras] = valor; // Adiciona o elemento
    printf("Enfileirado: %d\n", valor);
}

// Remove um elemento da fila
int desenfileirar(Fila *fila) {
    if (estaVazia(fila)) {
        printf("Erro: Fila vazia!\n");
        return -1;
    }
    int valor = fila->itens[fila->frente];
    fila->frente++;
    if (fila->frente > fila->tras) {
        inicializarFila(fila); // Reinicializa a fila se estiver vazia
    }
    printf("Desenfileirado: %d\n", valor);
    return valor;
}

// Exibe os elementos da fila
void exibirFila(Fila *fila) {
    if (estaVazia(fila)) {
        printf("Fila vazia!\n");
        return;
    }
    printf("Fila: ");
    for (int i = fila->frente; i <= fila->tras; i++) {
        printf("%d ", fila->itens[i]);
    }
    printf("\n");
}

// Função principal
int main() {
    Fila fila;
    inicializarFila(&fila);

    // Testando a fila
    enfileirar(&fila, 10);
    enfileirar(&fila, 20);
    enfileirar(&fila, 30);
    exibirFila(&fila);

    desenfileirar(&fila);
    exibirFila(&fila);

    desenfileirar(&fila);
    desenfileirar(&fila);
    desenfileirar(&fila); // Tentativa de remover de uma fila vazia

    return 0;
}