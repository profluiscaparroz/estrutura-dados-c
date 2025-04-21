#include <stdio.h>

int buscaBinaria(int arr[], int tamanho, int chave) {
    int inicio = 0, fim = tamanho - 1;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;

        if (arr[meio] == chave) {
            return meio; // Elemento encontrado
        }

        if (arr[meio] < chave) {
            inicio = meio + 1; // Buscar na metade direita
        } else {
            fim = meio - 1; // Buscar na metade esquerda
        }
    }

    return -1; // Elemento não encontrado
}

/**
 * Implementação do algoritmo de busca binária.
 *
 * A busca binária é um método eficiente para encontrar um elemento em um array ordenado.
 * O algoritmo funciona dividindo repetidamente o intervalo de busca pela metade até que
 * o elemento seja encontrado ou o intervalo se torne vazio.
 *
 * Passos do algoritmo:
 * 1. Inicialize dois ponteiros, `inicio` e `fim`, representando os limites do intervalo de busca.
 * 2. Enquanto `inicio` for menor ou igual a `fim`:
 *    a. Calcule o índice do meio do intervalo: `meio = (inicio + fim) / 2`.
 *    b. Compare o elemento no índice `meio` com o valor alvo:
 *       - Se forem iguais, o elemento foi encontrado e o índice é retornado.
 *       - Se o valor alvo for menor, ajuste o limite superior: `fim = meio - 1`.
 *       - Se o valor alvo for maior, ajuste o limite inferior: `inicio = meio + 1`.
 * 3. Se o intervalo se tornar vazio, o elemento não está presente no array.
 *
 * Complexidade:
 * - Melhor caso: O(1), quando o elemento está no meio do array na primeira iteração.
 * - Caso médio e pior caso: O(log n), onde n é o número de elementos no array.
 *
 * Observação:
 * O array deve estar ordenado para que a busca binária funcione corretamente.
 */
int main() {
    int arr[] = {2, 3, 4, 10, 40};
    int tamanho = sizeof(arr) / sizeof(arr[0]);
    int chave = 10;

    int resultado = buscaBinaria(arr, tamanho, chave);

    if (resultado != -1) {
        printf("Elemento encontrado no índice: %d\n", resultado);
    } else {
        printf("Elemento não encontrado no array.\n");
    }

    return 0;
}