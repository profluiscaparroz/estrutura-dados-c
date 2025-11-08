#include <stdio.h>
#include <stdlib.h>

// Estrutura de um nó
typedef struct Node {
    int valor;
    struct Node* proximo;
} Node;

// Função para criar um novo nó
Node* criarNo(int valor) {
    Node* novo = (Node*) malloc(sizeof(Node));
    if (novo == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    novo->valor = valor;
    novo->proximo = NULL;
    return novo;
}

// Inserir um nó no final da lista
void inserirFim(Node** inicio, int valor) {
    Node* novo = criarNo(valor);

    if (*inicio == NULL) {
        *inicio = novo; // a lista estava vazia
        return;
    }

    Node* atual = *inicio;
    while (atual->proximo != NULL) {
        atual = atual->proximo;
    }
    atual->proximo = novo;
}

// Imprimir todos os elementos da lista
void imprimirLista(Node* inicio) {
    Node* atual = inicio;
    printf("Lista: ");
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->proximo;
    }
    printf("NULL\n");
}

// Liberar memória da lista
void liberarLista(Node* inicio) {
    Node* atual = inicio;
    Node* prox;
    while (atual != NULL) {
        prox = atual->proximo;
        free(atual);
        atual = prox;
    }
}

int main() {
    Node* lista = NULL; // início da lista

    inserirFim(&lista, 10);
    inserirFim(&lista, 20);
    inserirFim(&lista, 30);

    imprimirLista(lista);

    liberarLista(lista);
    return 0;
}