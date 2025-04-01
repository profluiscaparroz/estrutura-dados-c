#include <stdio.h>

int exemploDeletarItemVetor(int vetor[], int tamanho, int posicao) {
    if (posicao < 0 || posicao >= tamanho) {
        return 0;
    }

    for (int i = posicao; i < tamanho - 1; i++) {
        vetor[i] = vetor[i + 1];
    }

    return 1;
}

int exemploDeletarItemVetorComPonteiros(int *vetor, int tamanho, int posicao) {
    if (posicao < 0 || posicao >= tamanho) {
        return 0;
    }

    for (int i = posicao; i < tamanho - 1; i++) {
        *(vetor + i) = *(vetor + i + 1);
    }

    return 1;
}

int main() {
    int vetor[] = {1, 2, 3, 4, 5};
    int tamanho = sizeof(vetor) / sizeof(vetor[0]);
    int posicao = 2;

    printf("Vetor antes de deletar o item na posição %d: ", posicao);
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    if (exemploDeletarItemVetor(vetor, tamanho, posicao)) {
        tamanho--;
        printf("Vetor depois de deletar o item na posição %d: ", posicao);
        for (int i = 0; i < tamanho; i++) {
            printf("%d ", vetor[i]);
        }
        printf("\n");
    } else {
        printf("Não foi possível deletar o item na posição %d.\n", posicao);
    }

    int vetor2[] = {1, 2, 3, 4, 5};
    int tamanho2 = sizeof(vetor2) / sizeof(vetor2[0]);
    int posicao2 = 2;

    printf("Vetor 2 antes de deletar o item na posição %d: ", posicao2);
    for (int i = 0; i < tamanho2; i++) {
        printf("%d ", vetor2[i]);
    }
    printf("\n");

    if (exemploDeletarItemVetorComPonteiros(vetor2, tamanho2, posicao2)) {
        tamanho2--;
        printf("Vetor 2 depois de deletar o item na posição %d: ", posicao2);
        for (int i = 0; i < tamanho2; i++) {
            printf("%d ", vetor2[i]);
        }
        printf("\n");
    } else {
        printf("Não foi possível deletar o item na posição %d.\n", posicao2);
    }

    return 0;
}