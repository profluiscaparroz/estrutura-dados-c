#include <stdio.h>

int insereValorVetorNaUltimaPosicao(int vetor[], int tamanho, int valor) {
    if (tamanho < 1) {
        return 0;
    }

    vetor[tamanho - 1] = valor;

    return 1;
}

int main() {
    int vetor[] = {1, 2, 3, 4, 5};
    int tamanho = sizeof(vetor) / sizeof(vetor[0]);
    int valor = 6;

    printf("Vetor antes de inserir o valor %d na última posição: ", valor);
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    if (insereValorVetorNaUltimaPosicao(vetor, tamanho, valor)) {
        tamanho++;
        printf("Vetor depois de inserir o valor %d na última posição: ", valor);
        for (int i = 0; i < tamanho; i++) {
            printf("%d ", vetor[i]);
        }
        printf("\n");
    } else {
        printf("Não foi possível inserir o valor %d na última posição.\n", valor);
    }

    return 0;
}
// 4: 5, 5: 5