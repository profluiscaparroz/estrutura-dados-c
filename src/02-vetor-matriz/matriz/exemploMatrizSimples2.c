#include <stdio.h>
#include <stdlib.h>

int main() {
    int linhas = 2, colunas = 3;
    int **mat = malloc(linhas * sizeof(int *));

    for (int i = 0; i < linhas; i++) {
        mat[i] = malloc(colunas * sizeof(int));
        for (int j = 0; j < colunas; j++) {
            mat[i][j] = i + j;
        }
    }

    printf("Endereço de mat: %p\n", (void*)mat);
    for (int i = 0; i < linhas; i++) {
        printf("mat[%d] -> %p\n", i, (void*)mat[i]);
        for (int j = 0; j < colunas; j++) {
            printf("  mat[%d][%d] = %d  @ %p\n", i, j, mat[i][j], (void*)&mat[i][j]);
        }
    }

    // Liberar memória
    for (int i = 0; i < linhas; i++) {
        free(mat[i]);
    }
    free(mat);

    return 0;
}