#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um nó da fila
typedef struct No {
    int dado;
    struct No* proximo;
} No;

// Estrutura para representar a fila
typedef struct Fila {
    No* frente;
    No* tras;
} Fila;

// Função para criar uma fila vazia
Fila* criarFila() {
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    fila->frente = NULL;
    fila->tras = NULL;
    return fila;
}

// Função para verificar se a fila está vazia
int estaVazia(Fila* fila) {
    return fila->frente == NULL;
}

// Função para enfileirar (inserir) um elemento na fila
void enfileirar(Fila* fila, int valor) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->dado = valor;
    novoNo->proximo = NULL;

    if (fila->tras == NULL) {
        // Se a fila estiver vazia, o novo nó será tanto a frente quanto o final
        fila->frente = novoNo;
        fila->tras = novoNo;
    } else {
        // Caso contrário, adiciona o novo nó ao final da fila
        fila->tras->proximo = novoNo;
        fila->tras = novoNo;
    }
}

// Função para desenfileirar (remover) um elemento da fila
int desenfileirar(Fila* fila) {
    if (estaVazia(fila)) {
        printf("A fila está vazia. Não é possível desenfileirar.\n");
        exit(EXIT_FAILURE);
    }

    No* temp = fila->frente;
    int valor = temp->dado;

    fila->frente = fila->frente->proximo;

    if (fila->frente == NULL) {
        // Se a fila ficou vazia, atualiza o ponteiro tras
        fila->tras = NULL;
    }

    free(temp);
    return valor;
}

// Função para liberar a memória alocada para a fila
void liberarFila(Fila* fila) {
    while (!estaVazia(fila)) {
        desenfileirar(fila);
    }
    free(fila);
}

// Função principal para demonstrar o uso da fila
int main() {
    Fila* fila = criarFila();

    // Enfileirando elementos
    enfileirar(fila, 10);
    enfileirar(fila, 20);
    enfileirar(fila, 30);

    printf("Desenfileirando: %d\n", desenfileirar(fila));
    printf("Desenfileirando: %d\n", desenfileirar(fila));

    // Enfileirando mais elementos
    enfileirar(fila, 40);
    enfileirar(fila, 50);

    printf("Desenfileirando: %d\n", desenfileirar(fila));
    printf("Desenfileirando: %d\n", desenfileirar(fila));
    printf("Desenfileirando: %d\n", desenfileirar(fila));

    liberarFila(fila);
    return 0;
}