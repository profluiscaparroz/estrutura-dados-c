#include <stdio.h>

// Função para realizar a busca linear em uma matriz
// Retorna 1 se o elemento for encontrado, caso contrário retorna 0
int buscaLinearMatriz(int matriz[][3], int linhas, int colunas, int elemento) {
    // Percorre todas as linhas da matriz
    for (int i = 0; i < linhas; i++) {
        // Percorre todas as colunas da matriz
        for (int j = 0; j < colunas; j++) {
            // Verifica se o elemento atual é igual ao elemento procurado
            if (matriz[i][j] == elemento) {
                return 1; // Elemento encontrado
            }
        }
    }
    return 0; // Elemento não encontrado
}

int main() {
    // Explicação:
    // Este programa implementa uma busca linear em uma matriz 2D.
    // Ele percorre todos os elementos da matriz para verificar se um determinado valor está presente.
    // Caso o valor seja encontrado, o programa informa que o elemento foi localizado.
    // Caso contrário, informa que o elemento não foi encontrado.

    // Declaração de uma matriz 3x3
    int matriz[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // Elemento a ser buscado
    int elemento = 5;

    // Chamada da função de busca linear
    if (buscaLinearMatriz(matriz, 3, 3, elemento)) {
        printf("Elemento %d encontrado na matriz.\n", elemento);
    } else {
        printf("Elemento %d nao encontrado na matriz.\n", elemento);
    }

    return 0;
}