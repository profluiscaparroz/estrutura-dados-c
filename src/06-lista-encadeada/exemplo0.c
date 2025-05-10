#include <stdio.h> // Biblioteca padrão para entrada e saída
#define MAX 100 // Define o tamanho máximo da lista como 100

// Estrutura para representar uma lista encadeada
typedef struct {
    int data[MAX]; // Array para armazenar os valores dos nós
    int next[MAX]; // Array para armazenar os índices do próximo nó
    int head; // Índice do primeiro nó da lista (cabeça da lista)
    int free; // Índice do próximo nó livre disponível
} LinkedList;

// Função para inicializar a lista encadeada
void initializeList(LinkedList *list) {
    list->head = -1; // Define a cabeça da lista como vazia (-1)
    list->free = 0; // Define o primeiro nó livre como o índice 0
    for (int i = 0; i < MAX - 1; i++) { // Inicializa os índices livres
        list->next[i] = i + 1; // Cada nó aponta para o próximo índice
    }
    list->next[MAX - 1] = -1; // O último nó livre aponta para -1 (fim da lista livre)
}

// Função para alocar um novo nó na lista
int allocateNode(LinkedList *list) {
    if (list->free == -1) return -1; // Retorna -1 se não houver nós livres
    int newNode = list->free; // Obtém o índice do próximo nó livre
    list->free = list->next[newNode]; // Atualiza o índice do próximo nó livre
    return newNode; // Retorna o índice do nó alocado
}

// Função para liberar um nó e devolvê-lo à lista de nós livres
void freeNode(LinkedList *list, int node) {
    list->next[node] = list->free; // O nó liberado aponta para o início da lista livre
    list->free = node; // Atualiza o índice do próximo nó livre
}

// Função para inserir um valor no início da lista
void insertAtBeginning(LinkedList *list, int value) {
    int newNode = allocateNode(list); // Aloca um novo nó
    if (newNode == -1) { // Verifica se a lista está cheia
        printf("List is full\n"); // Exibe uma mensagem de erro
        return; // Sai da função
    }
    list->data[newNode] = value; // Armazena o valor no novo nó
    list->next[newNode] = list->head; // O novo nó aponta para o antigo primeiro nó
    list->head = newNode; // Atualiza a cabeça da lista para o novo nó
}

// Função para exibir os elementos da lista
void displayList(LinkedList *list) {
    int current = list->head; // Começa pelo primeiro nó da lista
    while (current != -1) { // Percorre a lista até o final
        printf("%d -> ", list->data[current]); // Exibe o valor do nó atual
        current = list->next[current]; // Move para o próximo nó
    }
    printf("NULL\n"); // Indica o final da lista
}

int main() {
    LinkedList list; // Declara uma lista encadeada
    initializeList(&list); // Inicializa a lista

    insertAtBeginning(&list, 10); // Insere o valor 10 no início da lista
    insertAtBeginning(&list, 20); // Insere o valor 20 no início da lista
    insertAtBeginning(&list, 30); // Insere o valor 30 no início da lista

    displayList(&list); // Exibe os elementos da lista

    return 0; // Retorna 0 indicando que o programa foi executado com sucesso
}