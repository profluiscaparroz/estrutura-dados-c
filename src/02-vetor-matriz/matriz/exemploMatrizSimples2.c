#include <stdio.h>
#include <stdlib.h>

int main() {
    // Definindo o número de linhas e colunas
    int linhas = 2, colunas = 3;

    // Alocação dinâmica de memória para uma matriz 2x3
    // Aqui, alocamos um array de ponteiros para representar as linhas.
    int **mat = malloc(linhas * sizeof(int *));

    // Alocando memória para cada linha e inicializando os elementos
    for (int i = 0; i < linhas; i++) {
        mat[i] = malloc(colunas * sizeof(int)); // Alocação para as colunas
        for (int j = 0; j < colunas; j++) {
            mat[i][j] = i + j; // Exemplo de inicialização
        }
    }

    // Imprimindo os endereços e valores da matriz
    printf("Endereço de mat: %p\n", (void*)mat);
    for (int i = 0; i < linhas; i++) {
        printf("mat[%d] -> %p\n", i, (void*)mat[i]);
        for (int j = 0; j < colunas; j++) {
            printf("  mat[%d][%d] = %d  @ %p\n", i, j, mat[i][j], (void*)&mat[i][j]);
        }
    }

    // Liberando a memória alocada para evitar vazamentos
    for (int i = 0; i < linhas; i++) {
        free(mat[i]); // Liberando cada linha
    }
    free(mat); // Liberando o array de ponteiros

    return 0;
}