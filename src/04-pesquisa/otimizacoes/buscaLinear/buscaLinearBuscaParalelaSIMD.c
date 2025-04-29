#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h> // Biblioteca para intrínsecos SIMD

// Função para busca linear paralela usando SIMD
int buscaLinearParalelaSIMD(int *array, int tamanho, int valor) {
    // Define o vetor com o valor a ser buscado
    __m128i valorBuscado = _mm_set1_epi32(valor);

    // Itera pelo array em blocos de 4 elementos (128 bits)
    for (int i = 0; i < tamanho; i += 4) {
        // Carrega 4 inteiros do array em um registrador SIMD
        __m128i bloco = _mm_loadu_si128((__m128i*)&array[i]);

        // Compara os 4 inteiros do bloco com o valor buscado
        __m128i comparacao = _mm_cmpeq_epi32(bloco, valorBuscado);

        // Cria uma máscara com os resultados da comparação
        int mascara = _mm_movemask_epi8(comparacao);

        // Verifica se algum dos 4 valores é igual ao valor buscado
        if (mascara != 0) {
            // Retorna o índice do primeiro valor encontrado
            for (int j = 0; j < 4; j++) {
                if (array[i + j] == valor) {
                    return i + j;
                }
            }
        }
    }

    // Retorna -1 se o valor não for encontrado
    return -1;
}

int main() {
    // Explicação do conceito:
    // A busca paralela com SIMD (Single Instruction, Multiple Data) utiliza instruções vetoriais
    // para processar múltiplos dados simultaneamente. Neste caso, a busca linear é otimizada
    // ao comparar blocos de 4 elementos do array em uma única operação, reduzindo o número
    // de iterações e aumentando a eficiência em relação à busca linear tradicional.

    // Exemplo de uso da função
    int array[] = {10, 20, 30, 40, 50, 60, 70, 80};
    int tamanho = sizeof(array) / sizeof(array[0]);
    int valor = 50;

    // Chama a função de busca
    int indice = buscaLinearParalelaSIMD(array, tamanho, valor);

    // Exibe o resultado
    if (indice != -1) {
        printf("Valor %d encontrado no índice %d.\n", valor, indice);
    } else {
        printf("Valor %d não encontrado.\n", valor);
    }

    return 0;
}