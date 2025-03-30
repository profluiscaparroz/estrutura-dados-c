#include <stdlib.h>
#include <stdio.h>

// Função para deletar um item de um vetor, utilizando ponteiros para manipular o tamanho do vetor
int deletarItem(int *vetor, int *tamanho, int item) {
    int posicao = -1; // Variável para armazenar a posição do item a ser removido
    // Busca pelo item no vetor
    for (int i = 0; i < *tamanho; i++) {
        if (vetor[i] == item) { // Verifica se o item atual é o que deve ser removido
            posicao = i; // Armazena a posição do item
            break; // Interrompe o laço ao encontrar o item
        }
    }
    // Se o item foi encontrado
    if (posicao != -1) {
        // Desloca os elementos subsequentes para preencher o espaço do item removido
        for (int i = posicao; i < *tamanho - 1; i++) {
            vetor[i] = vetor[i + 1];
        }
        (*tamanho)--; // Decrementa o tamanho do vetor
    }
    return posicao; // Retorna a posição do item removido ou -1 se não encontrado
}

// Função para deletar um item de um vetor, sem utilizar ponteiros para o tamanho
int deletarItemSemPonteiros(int vetor[], int tamanho, int item) {
    int posicao = -1; // Variável para armazenar a posição do item a ser removido
    // Busca pelo item no vetor
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i] == item) { // Verifica se o item atual é o que deve ser removido
            posicao = i; // Armazena a posição do item
            break; // Interrompe o laço ao encontrar o item
        }
    }
    // Se o item foi encontrado
    if (posicao != -1) {
        // Desloca os elementos subsequentes para preencher o espaço do item removido
        for (int i = posicao; i < tamanho - 1; i++) {
            vetor[i] = vetor[i + 1];
        }
    }
    return posicao; // Retorna a posição do item removido ou -1 se não encontrado
}

int main() {
    // Declaração e inicialização do vetor
    int vetor[] = {1, 2, 3, 4, 5};
    int tamanho = 5; // Tamanho inicial do vetor
    int item = 3; // Item a ser removido

    // Chama a função deletarItem e armazena a posição do item removido
    int posicao = deletarItem(vetor, &tamanho, item);

    // Verifica se o item foi encontrado e removido
    if (posicao != -1) {
        printf("O item %d foi deletado da posicao %d\n", item, posicao);
        // Imprime o vetor atualizado
        for (int i = 0; i < tamanho; i++) {
            printf("%d ", vetor[i]);
        }
        printf("\n");
    } else {
        // Mensagem caso o item não seja encontrado
        printf("O item %d nao foi encontrado\n", item);
    }
    return 0; // Retorna 0 indicando que o programa foi executado com sucesso
}