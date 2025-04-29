#include <stdio.h>

/**
 * 
 * Esta implementação de busca binária utiliza uma abordagem "branchless" (sem ramificações explícitas),
 * ou seja, evita o uso de instruções condicionais como `if` ou `else` dentro do loop principal.
 * Isso pode melhorar o desempenho em algumas arquiteturas de CPU modernas, onde ramificações podem
 * causar penalidades devido à predição de ramificações incorreta.
 */

// Função de busca binária sem ramificações
int branchlessBinarySearch(int arr[], int size, int target) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        // Calcula o índice do meio
        int mid = (low + high) / 2;

        // Verifica se o elemento do meio é o alvo
        int isTarget = (arr[mid] == target);
        int isLess = (arr[mid] < target);

        // Atualiza os limites de busca sem ramificações
        low = isLess * (mid + 1) + (!isLess) * low;
        high = (!isTarget && !isLess) * (mid - 1) + isTarget * high;

        // Retorna o índice se o elemento for encontrado
        if (isTarget) {
            return mid;
        }
    }

    // Retorna -1 se o elemento não for encontrado
    return -1;
}

int main() {
    /*
     * Contexto:
     * Este programa demonstra o uso de uma implementação de busca binária otimizada,
     * conhecida como "Branchless Binary Search". A busca binária é um algoritmo eficiente
     * para encontrar um elemento em um array ordenado, reduzindo o espaço de busca pela metade
     * a cada iteração. A abordagem "branchless" elimina ramificações explícitas no código,
     * o que pode melhorar o desempenho em processadores modernos.
     *
     * Abordagem:
     * - O array deve estar previamente ordenado.
     * - A cada iteração, o índice do meio é calculado.
     * - Em vez de usar `if` para decidir se o alvo está à esquerda ou à direita,
     *   utilizamos operações matemáticas para atualizar os limites de busca.
     * - Isso reduz a dependência de predição de ramificações, tornando o código mais previsível
     *   para o processador.
     */

    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 7;

    int result = branchlessBinarySearch(arr, size, target);

    if (result != -1) {
        printf("Elemento %d encontrado no índice %d.\n", target, result);
    } else {
        printf("Elemento %d não encontrado no array.\n", target);
    }

    return 0;
}
// Explicação:
// A função `branchlessBinarySearch` implementa a busca binária sem ramificações explícitas.
// Ela utiliza operações matemáticas para atualizar os limites de busca, evitando o uso de `if`.
// Isso pode melhorar o desempenho em algumas arquiteturas de CPU modernas, onde ramificações
// podem causar penalidades devido à predição de ramificações incorreta.
// A função retorna o índice do elemento encontrado ou -1 se o elemento não estiver presente no array.
// O programa principal demonstra o uso da função com um array de exemplo e um valor alvo.
// A busca binária é uma técnica eficiente para encontrar elementos em arrays ordenados,
// reduzindo o espaço de busca pela metade a cada iteração.
// A abordagem "branchless" elimina ramificações explícitas no código, o que pode melhorar
// o desempenho em processadores modernos. A função retorna o índice do elemento encontrado
// ou -1 se o elemento não estiver presente no array. O programa principal demonstra o uso
// da função com um array de exemplo e um valor alvo.