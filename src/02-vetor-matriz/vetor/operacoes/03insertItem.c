#include <stdio.h>
#include <stdlib.h>

// Função para inserir um item em um vetor, utilizando ponteiros para manipular o tamanho do vetor
int inserirItem(int *vetor, int *tamanho, int posicao, int item) {
    // Verifica se a posição é válida
    if (posicao < 0 || posicao > *tamanho) {
        return -1; // Retorna -1 se a posição for inválida
    }
    // Realoca o vetor para acomodar o novo item
    vetor = (int *)realloc(vetor, (*tamanho + 1) * sizeof(int));
    // Desloca os elementos para abrir espaço para o novo item
    for (int i = *tamanho; i > posicao; i--) {
        vetor[i] = vetor[i - 1];
    }
    vetor[posicao] = item; // Insere o novo item na posição desejada
    (*tamanho)++; // Incrementa o tamanho do vetor
    return posicao; // Retorna a posição do item inserido
}

// Função para inserir um item em um vetor, sem utilizar ponteiros para o tamanho
int inserirItemSemPonteiros(int vetor[], int tamanho, int posicao, int item) {
    // Verifica se a posição é válida
    if (posicao < 0 || posicao > tamanho) {
        return -1; // Retorna -1 se a posição for inválida
    }
    // Desloca os elementos para abrir espaço para o novo item
    for (int i = tamanho; i > posicao; i--) {
        vetor[i] = vetor[i - 1];
    }
    vetor[posicao] = item; // Insere o novo item na posição desejada
    return posicao; // Retorna a posição do item inserido
}

int main() {
    // Declaração e inicialização do vetor
    int *vetor = (int *)malloc(5 * sizeof(int));
    vetor[0] = 1;
    vetor[1] = 2;
    vetor[2] = 4;
    vetor[3] = 5;
    int tamanho = 4; // Tamanho inicial do vetor
    int posicao = 2; // Posição para inserir o novo item
    int item = 3; // Item a ser inserido

    // Chama a função inserirItem e armazena a posição do item inserido
    int posicaoInserida = inserirItem(vetor, &tamanho, posicao, item);

    // Verifica se o item foi inserido
    if (posicaoInserida != -1) {
        printf("O item %d foi inserido na posicao %d\n", item, posicaoInserida);
        // Imprime o vetor atualizado
        for (int i = 0; i < tamanho; i++) {
            printf("%d ", vetor[i]);
        }
    } else {
        printf("Posicao invalida para insercao\n");
    }

    free(vetor); // Libera a memória alocada para o vetor

    return 0; // Retorna 0 indicando que o programa foi executado com sucesso
}
// Output: O item 3 foi inserido na posicao 2