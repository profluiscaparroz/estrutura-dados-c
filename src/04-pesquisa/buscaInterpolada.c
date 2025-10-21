#include <stdio.h>

/// @brief Pesquisa Interpolada é parecida com a busca binária, mas em vez de dividir o array ao meio,
/// ela tenta prever a posição do elemento com base no valor do elemento buscado em relação aos valores
/// nos extremos do array. Isso pode levar a uma busca mais rápida em arrays uniformemente distribuídos.
/// @param vetor 
/// @param tamanho 
/// @param x 
/// @return 
int pesquisaInterpolada(int vetor[], int tamanho, int x){
    int inicio = 0;
    int fim = tamanho - 1;

    while (inicio <= fim && x >= vetor[inicio] && x <= vetor[fim]) {
        // Evita divisão por zero
        if (vetor[fim] == vetor[inicio]) {
            break;
        }

        // Calcula a posição usando a fórmula de interpolação
        int pos = inicio + ((double)(x - vetor[inicio]) * (fim - inicio)) / (vetor[fim] - vetor[inicio]);

        // Verifica se o elemento foi encontrado
        if (vetor[pos] == x) {
            return pos; // Elemento encontrado
        }

        // Ajusta os limites da busca
        if (vetor[pos] < x) {
            inicio = pos + 1;
        } else {
            fim = pos - 1;
        }
    }
    return -1; // Elemento não encontrado
    
}

int main() {
    int vetor[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int tamanho = sizeof(vetor) / sizeof(vetor[0]);
    int elementoBuscado = 70;

    int resultado = pesquisaInterpolada(vetor, tamanho, elementoBuscado);

    if (resultado != -1) {
        printf("Elemento %d encontrado na posição %d.\n", elementoBuscado, resultado);
    } else {
        printf("Elemento %d não encontrado no array.\n", elementoBuscado);
    }

    return 0;
}