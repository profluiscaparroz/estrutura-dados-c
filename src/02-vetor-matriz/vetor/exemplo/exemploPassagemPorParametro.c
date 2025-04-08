#include <stdio.h>
#include <stdlib.h>

// Função para incrementar todos os elementos de um vetor
void incrementar(int vetor[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        vetor[i] += 1; // Incrementa cada elemento
    }
}

// Função para somar uma constante a todos os elementos de uma matriz
void somar_constante(int matriz[][3], int constante) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matriz[i][j] += constante; // Soma a constante a cada elemento
        }
    }
}

// Função para modificar uma matriz dinâmica multiplicando cada elemento por 2
void modificar_matriz(int **matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            matriz[i][j] *= 2; // Multiplica cada elemento por 2
        }
    }
}

// Função para modificar uma matriz dinâmica (usando ponteiros) somando 10 a cada elemento
void modificar_matriz_ponteiro(int *matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            matriz[i * colunas + j] += 10; // Adiciona 10 a cada elemento
        }
    }
}

int main() {
    // Exemplo 1: Passagem de vetor
    int vetor[] = {1, 2, 3, 4, 5};
    int tamanho = sizeof(vetor) / sizeof(vetor[0]);

    printf("Vetor antes de incrementar: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    // Passando o vetor para a função
    incrementar(vetor, tamanho);

    printf("Vetor depois de incrementar: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    // Exemplo 2: Passagem de matriz estática
    int matriz[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    printf("Matriz antes da soma:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    // Passando a matriz para a função
    somar_constante(matriz, 5);

    printf("Matriz depois da soma de 5:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    // Exemplo 3: Matrizes Dinâmicas
    int linhas = 2, colunas = 2;
    
    // Alocando memória para a matriz dinamicamente
    int **matriz_dinamica = (int **)malloc(linhas * sizeof(int *));
    for (int i = 0; i < linhas; i++) {
        matriz_dinamica[i] = (int *)malloc(colunas * sizeof(int));
    }

    // Inicializando a matriz
    matriz_dinamica[0][0] = 1; matriz_dinamica[0][1] = 2;
    matriz_dinamica[1][0] = 3; matriz_dinamica[1][1] = 4;

    printf("Matriz dinâmica antes da modificação:\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d ", matriz_dinamica[i][j]);
        }
        printf("\n");
    }

    // Passando a matriz dinâmica para a função
    modificar_matriz(matriz_dinamica, linhas, colunas);

    printf("Matriz dinâmica depois da modificação:\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d ", matriz_dinamica[i][j]);
        }
        printf("\n");
    }

    // Liberando memória alocada para a matriz dinâmica
    for (int i = 0; i < linhas; i++) {
        free(matriz_dinamica[i]);
    }
    free(matriz_dinamica);

    // Exemplo 4: Matrizes Dinâmicas com Ponteiros
    int *matriz_ponteiro = (int *)malloc(linhas * colunas * sizeof(int));

    // Inicializando a matriz
    matriz_ponteiro[0] = 1; matriz_ponteiro[1] = 2;
    matriz_ponteiro[2] = 3; matriz_ponteiro[3] = 4;

    printf("Matriz com ponteiro antes da modificação:\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d ", matriz_ponteiro[i * colunas + j]);
        }
        printf("\n");
    }

    // Passando a matriz com ponteiro para a função
    modificar_matriz_ponteiro(matriz_ponteiro, linhas, colunas);

    printf("Matriz com ponteiro depois da modificação:\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d ", matriz_ponteiro[i * colunas + j]);
        }
        printf("\n");
    }

    // Liberando memória alocada para a matriz com ponteiro
    free(matriz_ponteiro);

    return 0;
}
