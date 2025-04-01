#include <stdio.h>

int verificaItemExisteVetor(int vetor[], int tamanho, int item) {
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i] == item) {
            return 1;
        }
    }
    return 0;
}

int verificaItemExisteVetorComPonteiro(int *vetor, int tamanho, int item) {
    for (int i = 0; i < tamanho; i++) {
        if (*(vetor + i) == item) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int vetor[] = {1, 2, 3, 4, 5};
    int tamanho = sizeof(vetor) / sizeof(vetor[0]);
    int item = 3;

    if (verificaItemExisteVetor(vetor, tamanho, item)) {
        printf("O item %d existe no vetor.\n", item);
    } else {
        printf("O item %d não existe no vetor.\n", item);
    }

    if (verificaItemExisteVetorComPonteiro(vetor, tamanho, item)) {
        printf("O item %d existe no vetor (com ponteiro).\n", item);
    } else {
        printf("O item %d não existe no vetor (com ponteiro).\n", item);
    }

    return 0;
}