#include <stdio.h>
#include <immintrin.h> // Biblioteca para intrínsecos SIMD

// Função para busca binária vetorial (SIMD)
int buscaBinariaVetorial(int *vetor, int tamanho, int chave) {
    // Inicializa os limites inferior e superior
    int inicio = 0;
    int fim = tamanho - 1;

    // Enquanto houver elementos no intervalo
    while (inicio <= fim) {
        // Calcula o índice do meio
        int meio = (inicio + fim) / 2;

        // Carrega 4 elementos do vetor a partir do índice do meio usando SIMD
        __m128i valores = _mm_loadu_si128((__m128i *)&vetor[meio]);

        // Cria um vetor SIMD com a chave a ser buscada
        __m128i chaveSimd = _mm_set1_epi32(chave);

        // Compara os valores carregados com a chave
        __m128i comparacao = _mm_cmpeq_epi32(valores, chaveSimd);

        // Move os resultados da comparação para um inteiro
        int mascara = _mm_movemask_epi8(comparacao);

        // Verifica se a chave foi encontrada
        if (mascara != 0) {
            // Retorna o índice do primeiro elemento encontrado
            for (int i = 0; i < 4; i++) {
                if (vetor[meio + i] == chave) {
                    return meio + i;
                }
            }
        }

        // Ajusta os limites com base na comparação
        if (vetor[meio] < chave) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    // Retorna -1 se a chave não for encontrada
    return -1;
}

int main() {
    // Vetor ordenado para busca
    int vetor[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int tamanho = sizeof(vetor) / sizeof(vetor[0]);
    int chave = 7;

    // Explicação da abordagem Busca Binária Vetorial (SIMD):
    // 1. A busca binária tradicional divide o vetor em duas partes e verifica o elemento do meio.
    // 2. Na abordagem vetorial (SIMD), carregamos múltiplos elementos do vetor de uma só vez.
    // 3. Usamos instruções SIMD para comparar esses elementos simultaneamente com a chave.
    // 4. Isso pode acelerar a busca em vetores grandes, aproveitando o paralelismo de hardware.

    // Chama a função de busca binária vetorial
    int resultado = buscaBinariaVetorial(vetor, tamanho, chave);

    // Exibe o resultado
    if (resultado != -1) {
        printf("Chave %d encontrada no índice %d.\n", chave, resultado);
    } else {
        printf("Chave %d não encontrada.\n", chave);
    }

    return 0;
}