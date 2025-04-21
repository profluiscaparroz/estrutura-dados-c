#include <stdio.h>

// Função para busca linear em um vetor
int buscaLinearVetor(int vetor[], int tamanho, int elemento) {
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i] == elemento) {
            return i; // Retorna o índice onde o elemento foi encontrado
        }
    }
    return -1; // Retorna -1 se o elemento não foi encontrado
}

// Função para busca linear em uma matriz
int buscaLinearMatriz(int linhas, int colunas, int matriz[linhas][colunas], int elemento, int *linha, int *coluna) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j] == elemento) {
                *linha = i; // Armazena a linha onde o elemento foi encontrado
                *coluna = j; // Armazena a coluna onde o elemento foi encontrado
                return 1; // Retorna 1 se o elemento foi encontrado
            }
        }
    }
    return 0; // Retorna 0 se o elemento não foi encontrado
}


/**
 * Realiza uma busca linear em um array.
 *
 * A busca linear é um algoritmo simples que percorre cada elemento
 * de um array sequencialmente até encontrar o elemento desejado ou
 * até que todos os elementos tenham sido verificados.
 *
 * Complexidade:
 * - Melhor caso: O(1) (quando o elemento procurado está no início do array).
 * - Pior caso: O(n) (quando o elemento procurado está no final ou não está no array).
 *
 * Parâmetros:
 * - array: O array onde a busca será realizada.
 * - tamanho: O número de elementos no array.
 * - chave: O valor a ser procurado no array.
 *
 * Retorno:
 * - O índice do elemento encontrado, se a chave estiver presente no array.
 * - -1, se a chave não for encontrada no array.
 */
int main() {
    // Exemplo de busca linear em vetor
    int vetor[] = {10, 20, 30, 40, 50};
    int tamanhoVetor = sizeof(vetor) / sizeof(vetor[0]);
    int elementoVetor = 30;
    int indice = buscaLinearVetor(vetor, tamanhoVetor, elementoVetor);

    if (indice != -1) {
        printf("Elemento %d encontrado no índice %d do vetor.\n", elementoVetor, indice);
    } else {
        printf("Elemento %d não encontrado no vetor.\n", elementoVetor);
    }

    // Exemplo de busca linear em matriz
    int matriz[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int elementoMatriz = 5;
    int linha, coluna;

    if (buscaLinearMatriz(3, 3, matriz, elementoMatriz, &linha, &coluna)) {
        printf("Elemento %d encontrado na posição [%d][%d] da matriz.\n", elementoMatriz, linha, coluna);
    } else {
        printf("Elemento %d não encontrado na matriz.\n", elementoMatriz);
    }

    return 0;
}