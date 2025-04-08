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

    printf("Endereço de mat         : %p\n", (void*)mat);
    printf("Endereços dos vetores:\n");
    
    for (int i = 0; i < linhas; i++) {
        printf("  mat[%d] -> %p\n", i, (void*)mat[i]);
        for (int j = 0; j < colunas; j++) {
            printf("    mat[%d][%d] = %d @ %p\n", i, j, mat[i][j], (void*)&mat[i][j]);
        }
    }

    // Libera a memória
    for (int i = 0; i < linhas; i++) {
        free(mat[i]);
    }
    free(mat);
    return 0;
}
// Exibe o endereço de cada elemento da matriz alocada dinamicamente
// e o endereço do vetor que contém os ponteiros para as linhas da matriz.
// A matriz é alocada dinamicamente e os endereços são exibidos em formato hexadecimal.
// O código também libera a memória alocada após o uso.
// O resultado mostra os endereços de cada linha e de cada elemento da matriz.
// O endereço de mat é o endereço do vetor que contém os ponteiros para as linhas da matriz.