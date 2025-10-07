#include <stdio.h>
#include <stdlib.h>

int main() {
    int linhas = 3;
    int **matriz; // Ponteiro para ponteiro

    // 1. Aloca o vetor de ponteiros para as linhas
    matriz = malloc(linhas * sizeof(int *));
    if (matriz == NULL) {
        perror("Erro na alocacao do vetor de ponteiros");
        return 1;
    }

    // 2. Aloca cada linha com um numero de colunas diferente
    matriz[0] = malloc(3 * sizeof(int)); // Linha 0 com 3 colunas
    matriz[1] = malloc(1 * sizeof(int)); // Linha 1 com 1 coluna
    matriz[2] = malloc(2 * sizeof(int)); // Linha 2 com 2 colunas

    // 3. Atribui valores (exemplo)
    matriz[0][0] = 1;
    matriz[0][1] = 4;
    matriz[0][2] = 5;
    matriz[1][0] = 3;
    matriz[2][0] = 6;
    matriz[2][1] = 2;

    // 4. Imprime a matriz irregular
    printf("Matriz irregular:\n");
    printf("matriz[0]: ");
    for (int j = 0; j < 3; j++) {
        printf("%d ", matriz[0][j]);
    }
    printf("\n");
    printf("matriz[1]: ");
    for (int j = 0; j < 1; j++) {
        printf("%d ", matriz[1][j]);
    }
    printf("\n");
    printf("matriz[2]: ");
    for (int j = 0; j < 2; j++) {
        printf("%d ", matriz[2][j]);
    }
    printf("\n");

    // 5. Libera a memoria (importante!)
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}