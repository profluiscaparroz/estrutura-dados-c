#include <stdio.h>

// Função para reverter um vetor de caracteres (string) usando índices
// Parâmetros:
// - texto: vetor de caracteres a ser revertido
// - tamanho: tamanho do vetor (número de caracteres)
// Retorna:
// - 1 se a operação foi bem-sucedida
int exemploReverterTexto(char texto[], int tamanho) {
    // Percorre metade do vetor, trocando os elementos simétricos
    for (int i = 0; i < tamanho / 2; i++) {
        char temp = texto[i]; // Armazena temporariamente o elemento atual
        texto[i] = texto[tamanho - i - 1]; // Substitui pelo elemento simétrico
        texto[tamanho - i - 1] = temp; // Coloca o elemento armazenado na posição simétrica
    }

    return 1; // Retorna 1 indicando sucesso
}

// Função para reverter um vetor de caracteres usando ponteiros
// Parâmetros:
// - vetor: ponteiro para o vetor de caracteres
// - tamanho: tamanho do vetor
// Retorna:
// - 1 se a operação foi bem-sucedida
int exemploReverterVetorComPonteiros(char *vetor, int tamanho) {
    // Percorre metade do vetor, trocando os elementos simétricos
    for (int i = 0; i < tamanho / 2; i++) {
        char temp = *(vetor + i); // Armazena temporariamente o elemento atual
        *(vetor + i) = *(vetor + tamanho - i - 1); // Substitui pelo elemento simétrico
        *(vetor + tamanho - i - 1) = temp; // Coloca o elemento armazenado na posição simétrica
    }

    return 1; // Retorna 1 indicando sucesso
}

// Função para reverter um vetor de caracteres usando dois ponteiros
// Parâmetros:
// - vetor: ponteiro para o vetor de caracteres
// - tamanho: tamanho do vetor
// Retorna:
// - 1 se a operação foi bem-sucedida
int exemploReverterVetorComAuxiliar(char *vetor, int tamanho) {
    char *inicio = vetor; // Ponteiro para o início do vetor
    char *fim = vetor + tamanho - 1; // Ponteiro para o final do vetor

    // Enquanto os ponteiros não se cruzarem
    while (inicio < fim) {
        char temp = *inicio; // Armazena temporariamente o elemento no início
        *inicio = *fim; // Substitui o elemento do início pelo do final
        *fim = temp; // Coloca o elemento armazenado no final

        inicio++; // Move o ponteiro do início para frente
        fim--; // Move o ponteiro do final para trás
    }

    return 1; // Retorna 1 indicando sucesso
}

int main() {
    // Declaração e inicialização de uma string
    char texto[] = "Ola, mundo!";
    int tamanho = sizeof(texto) / sizeof(texto[0]) - 1; // Calcula o tamanho da string (excluindo o terminador '\0')

    printf("Texto antes de reverter: %s\n", texto);

    // Chama a função para reverter o texto usando índices
    if (exemploReverterTexto(texto, tamanho)) {
        printf("Texto depois de reverter: %s\n", texto);
    } else {
        printf("Não foi possível reverter o texto.\n");
    }

    // Declaração e inicialização de outra string
    char texto2[] = "Ola, mundo!";
    int tamanho2 = sizeof(texto2) / sizeof(texto2[0]) - 1; // Calcula o tamanho da string

    printf("Texto 2 antes de reverter: %s\n", texto2);

    // Chama a função para reverter o texto usando ponteiros
    if (exemploReverterVetorComPonteiros(texto2, tamanho2)) {
        printf("Texto 2 depois de reverter: %s\n", texto2);
    } else {
        printf("Não foi possível reverter o texto 2.\n");
    }

    // Declaração e inicialização de mais uma string
    char texto3[] = "Ola, mundo!";
    int tamanho3 = sizeof(texto3) / sizeof(texto3[0]) - 1; // Calcula o tamanho da string

    printf("Texto 3 antes de reverter: %s\n", texto3);

    // Chama a função para reverter o texto usando dois ponteiros
    if (exemploReverterVetorComAuxiliar(texto3, tamanho3)) {
        printf("Texto 3 depois de reverter: %s\n", texto3);
    } else {
        printf("Não foi possível reverter o texto 3.\n");
    }

    return 0; // Retorna 0 indicando que o programa foi executado com sucesso
}