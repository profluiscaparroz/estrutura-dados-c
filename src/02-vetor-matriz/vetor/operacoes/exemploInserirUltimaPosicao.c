#include <stdio.h>

int insereValorVetorNaUltimaPosicao(int vetor[], int tamanho, int valor) {
    if (tamanho < 1) {
        return 0;
    }

    vetor[tamanho - 1] = valor;

    return 1;
}