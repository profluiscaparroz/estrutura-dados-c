#include <stdio.h>

// Função para realizar a busca linear com otimização de Loop Unrolling
int buscaLinearLoopUnrolling(int arr[], int tamanho, int chave) {
    int i;

    // Percorre o array em blocos de 4 elementos
    for (i = 0; i <= tamanho - 4; i += 4) {
        // Verifica 4 elementos por iteração
        if (arr[i] == chave) return i;
        if (arr[i + 1] == chave) return i + 1;
        if (arr[i + 2] == chave) return i + 2;
        if (arr[i + 3] == chave) return i + 3;
    }

    // Verifica os elementos restantes (caso o tamanho do array não seja múltiplo de 4)
    for (; i < tamanho; i++) {
        if (arr[i] == chave) return i;
    }

    // Retorna -1 se o elemento não for encontrado
    return -1;
}

int main() {
    /*
    O que é Loop Unrolling (Desenrolamento de Laço)?
    ------------------------------------------------
    Loop Unrolling é uma técnica de otimização que consiste em "desenrolar" um laço,
    ou seja, executar várias iterações do laço em uma única iteração. Isso reduz o
    número de verificações de condição e incrementos do contador, melhorando o desempenho.
    No entanto, essa técnica pode aumentar o tamanho do código e deve ser usada com cuidado.
    */

    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int tamanho = sizeof(arr) / sizeof(arr[0]);
    int chave = 70;

    // Chama a função de busca linear com Loop Unrolling
    int resultado = buscaLinearLoopUnrolling(arr, tamanho, chave);

    if (resultado != -1) {
        printf("Elemento encontrado no índice: %d\n", resultado);
    } else {
        printf("Elemento não encontrado.\n");
    }

    return 0;
}