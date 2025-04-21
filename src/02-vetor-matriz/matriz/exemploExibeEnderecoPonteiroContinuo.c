#include <stdio.h>
#include <stdlib.h>

int main() {
    int linhas = 2, colunas = 3;

    // Alocação contínua
    int *mat = malloc(linhas * colunas * sizeof(int));
    if (!mat) {
        printf("Erro de alocação\n");
        return 1;
    }

    // Preenche a matriz
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            mat[i * colunas + j] = i + j;
        }
    }

    // Exibe os elementos e os endereços
    printf("Bloco contínuo de memória para a matriz:\n\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            int valor = mat[i * colunas + j];
            int *endereco = &mat[i * colunas + j];
            printf("mat[%d][%d] = %d @ %p\n", i, j, valor, (void*)endereco);
        }
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
// A matriz é alocada de forma contínua, o que significa que todos os elementos estão em um único bloco de memória.