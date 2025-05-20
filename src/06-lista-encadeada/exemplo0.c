#include <stdio.h> // Biblioteca padrão para entrada e saída
#define MAX 100 // Define o tamanho máximo da lista como 100

// Estrutura para representar uma lista encadeada
typedef struct {
    int dado[MAX]; // Array para armazenar os valores dos nós
    int proximo[MAX]; // Array para armazenar os índices do próximo nó
    int inicio; // Índice do primeiro nó da lista (cabeça da lista)
    int livro; // Índice do próximo nó livre disponível
} LinkedList;

// Função para inicializar a lista encadeada
void inicializarLista(LinkedList *list) {
    list->inicio = -1; // Define a cabeça da lista como vazia (-1)
    list->livro = 0; // Define o primeiro nó livre como o índice 0
    for (int i = 0; i < MAX - 1; i++) { // Inicializa os índices livres
        list->proximo[i] = i + 1; // Cada nó aponta para o próximo índice
    }
    list->proximo[MAX - 1] = -1; // O último nó livre aponta para -1 (fim da lista livre)
}

// Função para alocar um novo nó na lista
int alocarNovoNo(LinkedList *list) {
    if (list->livro == -1) return -1; // Retorna -1 se não houver nós livres
    int novoNo = list->livro; // Obtém o índice do próximo nó livre
    list->livro = list->proximo[novoNo]; // Atualiza o índice do próximo nó livre
    return novoNo; // Retorna o índice do nó alocado
}

// Função para liberar um nó e devolvê-lo à lista de nós livres
void livroNode(LinkedList *list, int node) {
    list->proximo[node] = list->livro; // O nó liberado aponta para o início da lista livre
    list->livro = node; // Atualiza o índice do próximo nó livre
}

// Função para inserir um valor no início da lista
void insereNoInicio(LinkedList *list, int value) {
    int novoNo = alocarNovoNo(list); // Aloca um novo nó
    if (novoNo == -1) { // Verifica se a lista está cheia
        printf("Lista está cheia\n"); // Exibe uma mensagem de erro
        return; // Sai da função
    }
    list->dado[novoNo] = value; // Armazena o valor no novo nó
    list->proximo[novoNo] = list->inicio; // O novo nó aponta para o antigo primeiro nó
    list->inicio = novoNo; // Atualiza a cabeça da lista para o novo nó
}

// Função para exibir os elementos da lista
void exibirItensLista(LinkedList *list) {
    int current = list->inicio; // Começa pelo primeiro nó da lista
    while (current != -1) { // Percorre a lista até o final
        printf("%d -> ", list->dado[current]); // Exibe o valor do nó atual
        current = list->proximo[current]; // Move para o próximo nó
    }
    printf("NULL\n"); // Indica o final da lista
}

int main() {
    LinkedList list; // Declara uma lista encadeada
    inicializarLista(&list); // Inicializa a lista

    insereNoInicio(&list, 10); // Insere o valor 10 no início da lista
    insereNoInicio(&list, 20); // Insere o valor 20 no início da lista
    insereNoInicio(&list, 30); // Insere o valor 30 no início da lista

    exibirItensLista(&list); // Exibe os elementos da lista

    return 0; // Retorna 0 indicando que o programa foi executado com sucesso
}