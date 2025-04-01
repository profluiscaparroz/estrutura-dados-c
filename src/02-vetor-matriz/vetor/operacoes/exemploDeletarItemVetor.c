#include <stdio.h>

// Função para deletar um item de um vetor usando índices
// Parâmetros:
// - vetor: vetor de inteiros
// - tamanho: tamanho do vetor
// - posicao: posição do item a ser deletado
// Retorna:
// - 1 se a operação foi bem-sucedida
// - 0 se a posição for inválida
int exemploDeletarItemVetor(int vetor[], int tamanho, int posicao) {
    // Verifica se a posição é válida
    if (posicao < 0 || posicao >= tamanho) {
        return 0; // Retorna 0 se a posição for inválida
    }

    // Desloca os elementos subsequentes para preencher o espaço do item deletado
    for (int i = posicao; i < tamanho - 1; i++) {
        vetor[i] = vetor[i + 1];
    }

    return 1; // Retorna 1 indicando sucesso
}

// Função para deletar um item de um vetor usando ponteiros
// Parâmetros:
// - vetor: ponteiro para o vetor de inteiros
// - tamanho: tamanho do vetor
// - posicao: posição do item a ser deletado
// Retorna:
// - 1 se a operação foi bem-sucedida
// - 0 se a posição for inválida
int exemploDeletarItemVetorComPonteiros(int *vetor, int tamanho, int posicao) {
    // Verifica se a posição é válida
    if (posicao < 0 || posicao >= tamanho) {
        return 0; // Retorna 0 se a posição for inválida
    }

    // Desloca os elementos subsequentes para preencher o espaço do item deletado
    for (int i = posicao; i < tamanho - 1; i++) {
        *(vetor + i) = *(vetor + i + 1); // Usa aritmética de ponteiros
    }

    return 1; // Retorna 1 indicando sucesso
}

int main() {
    // Declaração e inicialização do vetor
    int vetor[] = {1, 2, 3, 4, 5};
    int tamanho = sizeof(vetor) / sizeof(vetor[0]); // Calcula o tamanho do vetor
    int posicao = 2; // Posição do item a ser deletado

    // Exibe o vetor antes da exclusão
    printf("Vetor antes de deletar o item na posição %d: ", posicao);
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    // Chama a função para deletar o item usando índices
    if (exemploDeletarItemVetor(vetor, tamanho, posicao)) {
        tamanho--; // Decrementa o tamanho do vetor
        printf("Vetor depois de deletar o item na posição %d: ", posicao);
        for (int i = 0; i < tamanho; i++) {
            printf("%d ", vetor[i]);
        }
        printf("\n");
    } else {
        printf("Não foi possível deletar o item na posição %d.\n", posicao);
    }

    // Declaração e inicialização de outro vetor
    int vetor2[] = {1, 2, 3, 4, 5};
    int tamanho2 = sizeof(vetor2) / sizeof(vetor2[0]); // Calcula o tamanho do vetor
    int posicao2 = 2; // Posição do item a ser deletado

    // Exibe o vetor antes da exclusão
    printf("Vetor 2 antes de deletar o item na posição %d: ", posicao2);
    for (int i = 0; i < tamanho2; i++) {
        printf("%d ", vetor2[i]);
    }
    printf("\n");

    // Chama a função para deletar o item usando ponteiros
    if (exemploDeletarItemVetorComPonteiros(vetor2, tamanho2, posicao2)) {
        tamanho2--; // Decrementa o tamanho do vetor
        printf("Vetor 2 depois de deletar o item na posição %d: ", posicao2);
        for (int i = 0; i < tamanho2; i++) {
            printf("%d ", vetor2[i]);
        }
        printf("\n");
    } else {
        printf("Não foi possível deletar o item na posição %d.\n", posicao2);
    }

    return 0; // Retorna 0 indicando que o programa foi executado com sucesso
}