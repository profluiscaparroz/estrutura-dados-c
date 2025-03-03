#include <stdio.h>
#include <stdlib.h>

int main() {
    int linhas = 3, colunas = 4;
    
    // Passo 1: Criar um ponteiro para um array de ponteiros
    int **matriz = (int **)malloc(linhas * sizeof(int *));
    
    // Passo 2: Para cada linha, alocar um array de inteiros
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (int *)malloc(colunas * sizeof(int));
    }

    // Passo 3: Preenchendo a matriz
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = i + j;  // Apenas um exemplo de preenchimento
        }
    }

    // Passo 4: Exibindo a matriz
    printf("Matriz:\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    // Passo 5: Liberando memória alocada
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);  // Libera cada linha
    }
    free(matriz);  // Libera o array de ponteiros

    return 0;
}