#include <stdio.h>

// Função para realizar a busca linear com sentinela
int buscaLinearSentinela(int arr[], int n, int chave) {
    // Armazena o último elemento do array
    int ultimo = arr[n - 1];
    // Coloca a chave como sentinela no final do array
    arr[n - 1] = chave;

    int i = 0;
    // Realiza a busca até encontrar a chave
    while (arr[i] != chave) {
        i++;
    }

    // Restaura o último elemento do array
    arr[n - 1] = ultimo;

    // Verifica se a chave foi encontrada dentro do array original
    if (i < n - 1 || arr[n - 1] == chave) {
        return i; // Retorna o índice da chave
    }

    return -1; // Retorna -1 se a chave não foi encontrada
}

int main() {
    /*
    O método de Busca Linear com Sentinela (Sentinel Search) é uma otimização da busca linear tradicional.
    Ele utiliza um "sentinela" para evitar a necessidade de verificar os limites do array em cada iteração,
    o que reduz o número de comparações e melhora o desempenho em alguns casos.

    A ideia principal é colocar o elemento a ser buscado (chave) como um sentinela no final do array.
    Isso garante que a busca sempre encontrará o sentinela, eliminando a necessidade de verificar os limites.
    Após a busca, o valor original do último elemento é restaurado para manter a integridade do array.

    Este método é útil em cenários onde a busca linear é aplicada frequentemente e o custo de adicionar
    o sentinela é compensado pela redução no número de comparações.
    */

    int arr[] = {10, 20, 30, 40, 50};
    int n = sizeof(arr) / sizeof(arr[0]);
    int chave = 30;

    int resultado = buscaLinearSentinela(arr, n, chave);

    if (resultado != -1) {
        printf("Elemento encontrado no índice: %d\n", resultado);
    } else {
        printf("Elemento não encontrado.\n");
    }

    return 0;
}