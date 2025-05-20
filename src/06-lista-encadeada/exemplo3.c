#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um nó da lista circular
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Função para criar um novo nó
Node* criarNo(int data) {
    Node* novoNo = (Node*)malloc(sizeof(Node));
    if (!novoNo) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    novoNo->data = data;
    novoNo->next = novoNo; // Aponta para si mesmo, formando um ciclo
    return novoNo;
}

// Função para inserir um nó no final da lista circular
Node* inserirNoFinal(Node* tail, int data) {
    Node* novoNo = criarNo(data);
    if (tail == NULL) {
        // Se a lista estiver vazia, o novo nó será o único elemento
        return novoNo;
    }
    // Ajusta os ponteiros para inserir o novo nó no final
    novoNo->next = tail->next;
    tail->next = novoNo;
    return novoNo; // O novo nó se torna o último nó (tail)
}

// Função para imprimir os elementos da lista circular
void imprimirLista(Node* tail) {
    if (tail == NULL) {
        printf("A lista está vazia.\n");
        return;
    }
    Node* temp = tail->next; // Começa pelo primeiro nó
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != tail->next); // Continua até voltar ao início
    printf("\n");
}

// Função para liberar a memória da lista circular
void liberarLista(Node* tail) {
    if (tail == NULL) return;
    Node* temp = tail->next;
    Node* proxNo;
    do {
        proxNo = temp->next;
        free(temp);
        temp = proxNo;
    } while (temp != tail->next);
}

int main() {
    Node* tail = NULL; // Ponteiro para o último nó da lista

    // Inserindo elementos na lista circular
    tail = inserirNoFinal(tail, 10);
    tail = inserirNoFinal(tail, 20);
    tail = inserirNoFinal(tail, 30);

    // Imprimindo a lista circular
    printf("Elementos da lista circular: ");
    imprimirLista(tail);

    // Liberando a memória alocada
    liberarLista(tail);

    return 0;
}