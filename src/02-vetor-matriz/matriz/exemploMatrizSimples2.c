#include <stdio.h>
#include <stdlib.h>

int main() {
    // Definindo o número de linhas e colunas da matriz
    int linhas = 2, colunas = 3;

    // Alocação dinâmica de memória para uma matriz 2x3
    // Aqui, criamos um array de ponteiros, onde cada ponteiro representará uma linha da matriz.
    int **mat = malloc(linhas * sizeof(int *));

    // Verificando se a alocação foi bem-sucedida
    if (mat == NULL) {
        printf("Erro ao alocar memória para as linhas.\n");
        return 1;
    }

    // Alocando memória para cada linha e inicializando os elementos
    for (int i = 0; i < linhas; i++) {
        mat[i] = malloc(colunas * sizeof(int)); // Alocação para as colunas de cada linha

        // Verificando se a alocação foi bem-sucedida
        if (mat[i] == NULL) {
            printf("Erro ao alocar memória para a linha %d.\n", i);
            return 1;
        }

        // Inicializando os elementos da matriz com valores baseados em i e j
        for (int j = 0; j < colunas; j++) {
            mat[i][j] = i + j; // Exemplo de inicialização: soma dos índices
        }
    }

    // Imprimindo os endereços e valores da matriz
    printf("Endereço de mat (array de ponteiros): %p\n", (void*)mat);
    for (int i = 0; i < linhas; i++) {
        printf("Endereço da linha %d: %p\n", i, (void*)mat[i]);
        for (int j = 0; j < colunas; j++) {
            printf("  mat[%d][%d] = %d  @ %p\n", i, j, mat[i][j], (void*)&mat[i][j]);
        }
    }

    // Liberando a memória alocada para evitar vazamentos
    for (int i = 0; i < linhas; i++) {
        free(mat[i]); // Liberando a memória alocada para cada linha
    }
    free(mat); // Liberando o array de ponteiros

    // Finalizando o programa
    return 0;
}