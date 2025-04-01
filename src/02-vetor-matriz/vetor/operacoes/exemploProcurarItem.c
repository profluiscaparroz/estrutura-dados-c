#include <stdio.h>

// Função para inserir um valor na última posição de um vetor
// Parâmetros:
// - vetor: vetor de inteiros
// - tamanho: tamanho atual do vetor
// - valor: valor a ser inserido na última posição
// Retorna:
// - 1 se a operação foi bem-sucedida
// - 0 se o tamanho do vetor for inválido (menor que 1)
int insereValorVetorNaUltimaPosicao(int vetor[], int tamanho, int valor) {
    if (tamanho < 1) { // Verifica se o tamanho do vetor é válido
        return 0; // Retorna 0 se o tamanho for inválido
    }

    vetor[tamanho - 1] = valor; // Insere o valor na última posição do vetor

    return 1; // Retorna 1 indicando sucesso
}

int main() {
    // Declaração e inicialização do vetor
    int vetor[] = {1, 2, 3, 4, 5};
    int tamanho = sizeof(vetor) / sizeof(vetor[0]); // Calcula o tamanho do vetor
    int valor = 6; // Valor a ser inserido na última posição

    // Exibe o vetor antes da inserção
    printf("Vetor antes de inserir o valor %d na última posição: ", valor);
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    // Chama a função para inserir o valor na última posição
    if (insereValorVetorNaUltimaPosicao(vetor, tamanho, valor)) {
        tamanho++; // Incrementa o tamanho do vetor (simulação, mas não afeta o vetor real)
        printf("Vetor depois de inserir o valor %d na última posição: ", valor);
        for (int i = 0; i < tamanho; i++) {
            printf("%d ", vetor[i]);
        }
        printf("\n");
    } else {
        // Mensagem de erro caso a inserção não seja possível
        printf("Não foi possível inserir o valor %d na última posição.\n", valor);
    }

    return 0; // Retorna 0 indicando que o programa foi executado com sucesso
}