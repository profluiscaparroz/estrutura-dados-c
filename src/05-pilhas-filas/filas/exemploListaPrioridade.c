#include <stdio.h>
#include <stdlib.h>

// Estrutura de um nó da lista duplamente ligada
typedef struct No {
    int prioridade; // Prioridade do elemento
    int dado;       // Valor do elemento
    struct No* prox; // Ponteiro para o próximo nó
    struct No* ant;  // Ponteiro para o nó anterior
} No;

// Estrutura da fila de prioridade
typedef struct FilaPrioridade {
    No* inicio; // Ponteiro para o início da fila
    No* fim;    // Ponteiro para o final da fila
} FilaPrioridade;

// Função para criar uma nova fila de prioridade
FilaPrioridade* criarFila() {
    FilaPrioridade* fila = (FilaPrioridade*)malloc(sizeof(FilaPrioridade));
    fila->inicio = NULL;
    fila->fim = NULL;
    return fila;
}

// Função para criar um novo nó
No* criarNo(int dado, int prioridade) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->dado = dado;
    novoNo->prioridade = prioridade;
    novoNo->prox = NULL;
    novoNo->ant = NULL;
    return novoNo;
}

// Função para inserir um elemento na fila de prioridade
void inserir(FilaPrioridade* fila, int dado, int prioridade) {
    No* novoNo = criarNo(dado, prioridade);

    // Se a fila estiver vazia
    if (fila->inicio == NULL) {
        fila->inicio = novoNo;
        fila->fim = novoNo;
        return;
    }

    No* atual = fila->inicio;

    // Encontrar a posição correta para inserir com base na prioridade
    while (atual != NULL && atual->prioridade >= prioridade) {
        atual = atual->prox;
    }

    // Inserir no início
    if (atual == fila->inicio) {
        novoNo->prox = fila->inicio;
        fila->inicio->ant = novoNo;
        fila->inicio = novoNo;
    }
    // Inserir no final
    else if (atual == NULL) {
        novoNo->ant = fila->fim;
        fila->fim->prox = novoNo;
        fila->fim = novoNo;
    }
    // Inserir no meio
    else {
        novoNo->prox = atual;
        novoNo->ant = atual->ant;
        atual->ant->prox = novoNo;
        atual->ant = novoNo;
    }
}

// Função para remover o elemento de maior prioridade
int remover(FilaPrioridade* fila) {
    if (fila->inicio == NULL) {
        printf("Fila vazia!\n");
        return -1;
    }

    No* temp = fila->inicio;
    int dado = temp->dado;

    // Atualizar o início da fila
    fila->inicio = fila->inicio->prox;
    if (fila->inicio != NULL) {
        fila->inicio->ant = NULL;
    } else {
        fila->fim = NULL;
    }

    free(temp);
    return dado;
}

// Função para exibir os elementos da fila
void exibir(FilaPrioridade* fila) {
    No* atual = fila->inicio;
    while (atual != NULL) {
        printf("Dado: %d, Prioridade: %d\n", atual->dado, atual->prioridade);
        atual = atual->prox;
    }
}

// Função principal para demonstrar o uso da fila de prioridade
int main() {
    FilaPrioridade* fila = criarFila();

    inserir(fila, 10, 2);
    inserir(fila, 20, 1);
    inserir(fila, 30, 3);

    printf("Elementos na fila:\n");
    exibir(fila);

    printf("\nRemovendo elemento de maior prioridade: %d\n", remover(fila));

    printf("\nElementos na fila após remoção:\n");
    exibir(fila);

    return 0;
}

/*
Uma lista duplamente ligada é uma estrutura de dados onde cada nó contém três partes:
1. Um ponteiro para o nó anterior.
2. Um valor ou dado armazenado no nó.
3. Um ponteiro para o próximo nó.

Essa estrutura permite a navegação em ambas as direções (para frente e para trás),
o que a torna mais flexível do que uma lista simplesmente ligada. No entanto, ela
ocupa mais memória devido aos ponteiros adicionais.
*/