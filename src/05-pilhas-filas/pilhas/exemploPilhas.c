#include <stdio.h>
#include <stdlib.h>

#define MAX 100 // Define o tamanho máximo da pilha

// Estrutura para representar a pilha
typedef struct {
    int itens[MAX]; // Array para armazenar os elementos da pilha
    int topo;       // Índice do topo da pilha
} Pilha;

// Função para inicializar a pilha
void inicializarPilha(Pilha *p) {
    p->topo = -1; // Define o topo como -1, indicando que a pilha está vazia
}

// Função para verificar se a pilha está cheia
int estaCheia(Pilha *p) {
    return p->topo == MAX - 1; // Retorna 1 (true) se o topo atingir o limite máximo
}

// Função para verificar se a pilha está vazia
int estaVazia(Pilha *p) {
    return p->topo == -1; // Retorna 1 (true) se o topo for -1
}

// Função para empilhar (push) um elemento
void empilhar(Pilha *p, int valor) {
    if (estaCheia(p)) {
        printf("Erro: Pilha cheia!\n");
        return;
    }
    p->itens[++p->topo] = valor; // Incrementa o topo e adiciona o valor
}

// Função para desempilhar (pop) um elemento
int desempilhar(Pilha *p) {
    if (estaVazia(p)) {
        printf("Erro: Pilha vazia!\n");
        return -1; // Retorna -1 para indicar erro
    }
    return p->itens[p->topo--]; // Retorna o elemento do topo e decrementa o índice
}

// Função para exibir os elementos da pilha
void exibirPilha(Pilha *p) {
    if (estaVazia(p)) {
        printf("Pilha vazia!\n");
        return;
    }
    printf("Elementos da pilha: ");
    for (int i = 0; i <= p->topo; i++) {
        printf("%d ", p->itens[i]);
    }
    printf("\n");
}

// Função principal para demonstrar o uso da pilha
int main() {
    Pilha p;
    inicializarPilha(&p);

    empilhar(&p, 10);
    empilhar(&p, 20);
    empilhar(&p, 30);

    exibirPilha(&p);

    printf("Desempilhando: %d\n", desempilhar(&p));
    printf("Desempilhando: %d\n", desempilhar(&p));

    exibirPilha(&p);

    return 0;
}