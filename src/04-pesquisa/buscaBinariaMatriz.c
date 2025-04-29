#include <stdio.h>
#include <stdbool.h>

// Função para realizar a busca binária em uma matriz ordenada
bool buscaBinariaMatriz(int matriz[][3], int linhas, int colunas, int alvo) {
    int inicio = 0;
    int fim = linhas * colunas - 1;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;

        // Converter o índice linear para índices de linha e coluna
        int linha = meio / colunas;
        int coluna = meio % colunas;

        if (matriz[linha][coluna] == alvo) {
            return true; // Elemento encontrado
        } else if (matriz[linha][coluna] < alvo) {
            inicio = meio + 1; // Ajustar o início
        } else {
            fim = meio - 1; // Ajustar o fim
        }
    }

    return false; // Elemento não encontrado
}

int main() {
    /*
    Busca binária em uma matriz:
    A busca binária é um algoritmo eficiente para encontrar um elemento em uma coleção ordenada.
    Neste exemplo, aplicamos a busca binária em uma matriz 2D que é tratada como uma lista linear.
    A matriz deve ser ordenada em ordem crescente, e os índices são convertidos de linear para 2D
    durante o processo de busca. O algoritmo tem complexidade O(log(n*m)), onde n é o número de linhas
    e m é o número de colunas.
    */

    int matriz[3][3] = {
        {1, 3, 5},
        {7, 9, 11},
        {13, 15, 17}
    };

    int alvo = 9;

    if (buscaBinariaMatriz(matriz, 3, 3, alvo)) {
        printf("Elemento %d encontrado na matriz.\n", alvo);
    } else {
        printf("Elemento %d nao encontrado na matriz.\n", alvo);
    }

    return 0;
}