#include <stdio.h>

int main() {
    // Declaração e inicialização da matriz 2x3
    // Aqui, estamos criando uma matriz com 2 linhas e 3 colunas
    // e inicializando seus elementos com valores específicos.
    int matriz[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    // Acessando e imprimindo os elementos
    // Este loop percorre cada elemento da matriz e o imprime.
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("Elemento [%d][%d] = %d\n", i, j, matriz[i][j]);
        }
    }

    // Exemplo adicional: matriz 3x2 não inicializada
    // Aqui, criamos uma matriz com 3 linhas e 2 colunas sem inicializar os valores.
    int matrizNaoInicializada[3][2];

    // Preenchendo a matriz com valores e imprimindo
    printf("\nPreenchendo e imprimindo matriz 3x2:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            matrizNaoInicializada[i][j] = i + j; // Exemplo de preenchimento
            printf("Elemento [%d][%d] = %d\n", i, j, matrizNaoInicializada[i][j]);
        }
    }

    // Exemplo adicional: matriz 2x2 com valores padrão
    // Aqui, criamos e inicializamos uma matriz 2x2 com valores padrão.
    int matrizPadrao[2][2] = {0}; // Todos os elementos serão inicializados como 0.

    printf("\nImprimindo matriz 2x2 com valores padrão:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("Elemento [%d][%d] = %d\n", i, j, matrizPadrao[i][j]);
        }
    }

    return 0;
}