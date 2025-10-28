#include <stdio.h>
#include <stdlib.h>


// Estrutura do nó da lista encadeada
typedef struct No {
    int valor;
    struct No *proximo;
} No;

// Estrutura da fila
typedef struct {
    No *frente; // Ponteiro para o primeiro elemento
    No *tras;   // Ponteiro para o último elemento
} Fila;

// Inicializa a fila
void inicializarFila(Fila *fila) {
    fila->frente = NULL;
    fila->tras = NULL;
}

// Verifica se a fila está vazia
int estaVazia(Fila *fila) {
    return fila->frente == NULL;
}
// Adiciona um elemento à fila
void enfileirar(Fila *fila, int valor) {
    No *novoNo = (No *)malloc(sizeof(No));
    if (!novoNo) {
        printf("Erro: Falha na alocação de memória!\n");
        return;
    }
    novoNo->valor = valor;
    novoNo->proximo = NULL;
    if (estaVazia(fila)) {
        fila->frente = novoNo; // Define o início da fila
    } else {
        fila->tras->proximo = novoNo; // Liga o último nó ao novo nó
    }
    fila->tras = novoNo; // Atualiza o ponteiro do último nó
    printf("Enfileirado: %d\n", valor);
}

// Remove um elemento da fila
int desenfileirar(Fila *fila) {
    if (estaVazia(fila)) {
        printf("Erro: Fila vazia!\n");
        return -1;
    }
    No *temp = fila->frente;
    int valor = temp->valor;
    fila->frente = fila->frente->proximo; // Move o ponteiro da frente
    if (fila->frente == NULL) {
        fila->tras = NULL; // Se a fila ficar vazia, atualiza o ponteiro do último nó
    }
    free(temp); // Libera a memória do nó removido
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
    No *atual = fila->frente;
    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
    printf("\n");
}

int main() {
    Fila fila;
    inicializarFila(&fila);

    enfileirar(&fila, 10);
    enfileirar(&fila, 20);
    enfileirar(&fila, 30);
    exibirFila(&fila);

    desenfileirar(&fila);
    exibirFila(&fila);

    desenfileirar(&fila);
    desenfileirar(&fila);
    desenfileirar(&fila); // Tentativa de desenfileirar de uma fila vazia

    return 0;
}