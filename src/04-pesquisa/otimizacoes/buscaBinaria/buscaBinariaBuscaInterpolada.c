#include <stdio.h>

// Função para realizar a busca binária interpolada
// Essa função retorna o índice do elemento encontrado ou -1 caso o elemento não esteja presente
int buscaBinariaInterpolada(int arr[], int tamanho, int chave) {
    int inicio = 0, fim = tamanho - 1;

    while (inicio <= fim && chave >= arr[inicio] && chave <= arr[fim]) {
        // Caso o array esteja ordenado e o elemento esteja fora do intervalo
        if (inicio == fim) {
            if (arr[inicio] == chave) return inicio;
            return -1;
        }

        // Fórmula para calcular a posição interpolada
        int pos = inicio + ((double)(fim - inicio) / (arr[fim] - arr[inicio])) * (chave - arr[inicio]);

        // Verifica se o elemento foi encontrado
        if (arr[pos] == chave) {
            return pos;
        }

        // Ajusta os limites de busca
        if (arr[pos] < chave) {
            inicio = pos + 1; // Busca na metade superior
        } else {
            fim = pos - 1; // Busca na metade inferior
        }
    }

    return -1; // Elemento não encontrado
}

int main() {
    /*
    A busca binária interpolada é uma otimização da busca binária tradicional.
    Enquanto a busca binária divide o intervalo de busca sempre ao meio, a busca interpolada
    tenta estimar a posição do elemento com base na sua relação com os valores extremos do intervalo.
    Isso é feito utilizando uma fórmula de interpolação linear.

    Essa abordagem é mais eficiente em arrays ordenados e uniformemente distribuídos,
    pois reduz o número de iterações necessárias para encontrar o elemento.
    No entanto, em casos onde os dados não são uniformemente distribuídos, o desempenho pode ser similar
    ou até pior do que a busca binária tradicional.
    */

    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int tamanho = sizeof(arr) / sizeof(arr[0]);
    int chave = 70;

    int resultado = buscaBinariaInterpolada(arr, tamanho, chave);

    if (resultado != -1) {
        printf("Elemento encontrado no índice: %d\n", resultado);
    } else {
        printf("Elemento não encontrado.\n");
    }

    return 0;
}