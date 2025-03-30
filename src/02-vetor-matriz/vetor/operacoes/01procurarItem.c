#include <stdlib.h>
#include <stdio.h>

// Função para procurar um item em um vetor
// Parâmetros:
// - vetor: ponteiro para o vetor de inteiros
// - tamanho: número de elementos no vetor
// - item: valor a ser procurado no vetor
// Retorna:
// - A posição do item no vetor, se encontrado
// - -1, se o item não for encontrado
int procurarItem(int *vetor, int tamanho, int item) {
    // Itera sobre os elementos do vetor
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i] == item) { // Verifica se o elemento atual é igual ao item procurado
            return i; // Retorna a posição do item encontrado
        }
    }
    return -1; // Retorna -1 se o item não for encontrado
}

int main() {
    // Declaração e inicialização do vetor
    int vetor[] = {1, 2, 3, 4, 5};
    int tamanho = 5; // Tamanho do vetor
    int item = 3; // Item a ser procurado

    // Chama a função procurarItem e armazena a posição do item
    int posicao = procurarItem(vetor, tamanho, item);

    // Verifica se o item foi encontrado
    if (posicao != -1) {
        // Exibe a posição do item encontrado
        printf("O item %d foi encontrado na posicao %d\n", item, posicao);
    } else {
        // Exibe mensagem caso o item não seja encontrado
        printf("O item %d nao foi encontrado\n", item);
    }

    return 0; // Retorna 0 indicando que o programa foi executado com sucesso
}