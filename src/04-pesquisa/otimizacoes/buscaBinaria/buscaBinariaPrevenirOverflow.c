#include <stdio.h>

// Função para realizar a busca binária com prevenção de overflow
int buscaBinaria(int arr[], int tamanho, int chave) {
    int inicio = 0;
    int fim = tamanho - 1;

    while (inicio <= fim) {
        // Prevenção de overflow ao calcular o meio
        int meio = inicio + (fim - inicio) / 2;

        if (arr[meio] == chave) {
            return meio; // Retorna o índice do elemento encontrado
        } else if (arr[meio] < chave) {
            inicio = meio + 1; // Ajusta o início para a metade superior
        } else {
            fim = meio - 1; // Ajusta o fim para a metade inferior
        }
    }

    return -1; // Retorna -1 se o elemento não for encontrado
}

int main() {
    /*
    Busca Binária com Prevenção de Overflow:
    O cálculo tradicional do índice do meio em uma busca binária é feito como (inicio + fim) / 2.
    No entanto, quando os valores de 'inicio' e 'fim' são muito grandes, a soma pode causar um overflow.
    Para evitar isso, utilizamos a fórmula alternativa:
        meio = inicio + (fim - inicio) / 2;
    Essa abordagem garante que a subtração (fim - inicio) seja calculada antes de somar com 'inicio',
    evitando assim o risco de overflow.
    */

    int arr[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    int tamanho = sizeof(arr) / sizeof(arr[0]);
    int chave = 17;

    int resultado = buscaBinaria(arr, tamanho, chave);

    if (resultado != -1) {
        printf("Elemento encontrado no índice: %d\n", resultado);
    } else {
        printf("Elemento não encontrado no array.\n");
    }

    return 0;
}