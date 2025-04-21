#include <stdio.h>
#include <stdlib.h>

void imprimir_matriz_dinamica(int **mat, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int exemploPonteiro() {
    
    int linhas = 2, colunas = 3;
    int **mat = malloc(linhas * sizeof(int *));
    for (int i = 0; i < linhas; i++) {
        mat[i] = malloc(colunas * sizeof(int));
        for (int j = 0; j < colunas; j++) {
            mat[i][j] = i + j;
        }
    }

    imprimir_matriz_dinamica(mat, linhas, colunas);

    for (int i = 0; i < linhas; i++) free(mat[i]);
    free(mat);
    return 0;
}

int Soma() {
    // Declaração e inicialização das matrizes 2x2
    int matriz1[2][2] = {
        {1, 2},
        {3, 4}
    };
    int matriz2[2][2] = {
        {5, 6},
        {7, 8}
    };
    int soma[2][2];

    // Somando as matrizes
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            soma[i][j] = matriz1[i][j] + matriz2[i][j];
        }
    }

    // Imprimindo o resultado
    printf("Resultado da soma das matrizes:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", soma[i][j]);
        }
        printf("\n");
    }

    return 0;
}


int Multiplicacao() {
    // Matrizes A (2x3) e B (3x2)
    int A[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    int B[3][2] = {
        {7, 8},
        {9, 10},
        {11, 12}
    };
    int C[2][2] = {0};

    // Multiplicação de matrizes
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 3; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // Imprimindo o resultado
    printf("Resultado da multiplicação das matrizes:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}

int Transposicao() {
    // Matrizes 2x3
    int matriz[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    int transposta[3][2];

    // Calculando a transposta
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            transposta[j][i] = matriz[i][j];
        }
    }

    // Imprimindo a matriz transposta
    printf("Matriz transposta:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", transposta[i][j]);
        }
        printf("\n");
    }

    return 0;
}

int main() {
    Soma();
    Multiplicacao();
    Transposicao();

    return 0;
}