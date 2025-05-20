#include <stdio.h>
#include <stdlib.h>

// Estrutura para um nó da lista duplamente encadeada
typedef struct Node {
    int dado; // Dado armazenado no nó
    struct Node* anterior; // Ponteiro para o nó anterior
    struct Node* proximo; // Ponteiro para o próximo nó
} Node;

// Função para criar um novo nó
Node* criarNo(int dado) {
    Node* novoNo = (Node*)malloc(sizeof(Node)); // Aloca memória para o nó
    novoNo->dado = dado; // Atribui o dado ao nó
    novoNo->anterior = NULL; // Inicializa o ponteiro para o nó anterior como NULL
    novoNo->proximo = NULL; // Inicializa o ponteiro para o próximo nó como NULL
    return novoNo; // Retorna o novo nó
}

// Função para inserir um nó no início da lista
void inserirInicio(Node** head, int dado) {
    Node* novoNo = criarNo(dado); // Cria um novo nó
    novoNo->proximo = *head; // Faz o próximo do novo nó apontar para o antigo primeiro nó
    if (*head != NULL) {
        (*head)->anterior = novoNo; // Atualiza o ponteiro anterior do antigo primeiro nó
    }
    *head = novoNo; // Atualiza o ponteiro da cabeça para o novo nó
}

// Função para inserir um nó no final da lista
void inserirFim(Node** head, int dado) {
    Node* novoNo = criarNo(dado); // Cria um novo nó
    if (*head == NULL) {
        *head = novoNo; // Se a lista estiver vazia, o novo nó será a cabeça
        return;
    }
    Node* temp = *head; // Ponteiro temporário para percorrer a lista
    while (temp->proximo != NULL) {
        temp = temp->proximo; // Avança até o último nó
    }
    temp->proximo = novoNo; // Faz o próximo do último nó apontar para o novo nó
    novoNo->anterior = temp; // Faz o anterior do novo nó apontar para o último nó
}

// Função para imprimir a lista do início ao fim
void imprimirLista(Node* head) {
    Node* temp = head; // Ponteiro temporário para percorrer a lista
    printf("Lista (início ao fim): ");
    while (temp != NULL) {
        printf("%d ", temp->dado); // Imprime o dado do nó atual
        temp = temp->proximo; // Avança para o próximo nó
    }
    printf("\n");
}

// Função para imprimir a lista do fim ao início
void imprimirListaReversa(Node* head) {
    if (head == NULL) return; // Se a lista estiver vazia, não faz nada
    Node* temp = head;
    while (temp->proximo != NULL) {
        temp = temp->proximo; // Avança até o último nó
    }
    printf("Lista (fim ao início): ");
    while (temp != NULL) {
        printf("%d ", temp->dado); // Imprime o dado do nó atual
        temp = temp->anterior; // Retrocede para o nó anterior
    }
    printf("\n");
}

// Função principal para testar a lista duplamente encadeada
int main() {
    Node* head = NULL; // Inicializa a lista como vazia

    // Testando as funções
    inserirInicio(&head, 10);
    inserirInicio(&head, 20);
    inserirFim(&head, 30);
    inserirFim(&head, 40);

    imprimirLista(head); // Imprime a lista do início ao fim
    imprimirListaReversa(head); // Imprime a lista do fim ao início

    return 0;
}