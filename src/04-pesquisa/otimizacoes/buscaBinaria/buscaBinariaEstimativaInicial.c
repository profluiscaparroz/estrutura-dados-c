#include <stdio.h>

// Função para realizar a busca binária em um intervalo específico
int buscaBinaria(int arr[], int esquerda, int direita, int alvo) {
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2; // Calcula o índice do meio

        // Verifica se o elemento do meio é o alvo
        if (arr[meio] == alvo) {
            return meio; // Retorna o índice do elemento encontrado
        }

        // Se o elemento do meio for maior que o alvo, busca na metade esquerda
        if (arr[meio] > alvo) {
            direita = meio - 1;
        }
        // Caso contrário, busca na metade direita
        else {
            esquerda = meio + 1;
        }
    }

    return -1; // Retorna -1 se o elemento não for encontrado
}

// Função para realizar a busca binária com estimativa inicial (exponencial)
int buscaBinariaComEstimativa(int arr[], int tamanho, int alvo) {
    // Caso o primeiro elemento seja o alvo
    if (arr[0] == alvo) {
        return 0;
    }

    // Estimativa inicial: encontra o intervalo exponencial onde o alvo pode estar
    int i = 1;
    while (i < tamanho && arr[i] <= alvo) {
        i *= 2; // Dobra o índice a cada iteração
    }

    // Realiza a busca binária no intervalo estimado
    return buscaBinaria(arr, i / 2, (i < tamanho ? i : tamanho - 1), alvo);
}

int main() {
    // Array ordenado para realizar a busca
    int arr[] = {1, 3, 7, 15, 31, 63, 127, 255, 511, 1023};
    int tamanho = sizeof(arr) / sizeof(arr[0]); // Calcula o tamanho do array
    int alvo = 127; // Elemento a ser buscado

    // Chama a função de busca binária com estimativa inicial
    int resultado = buscaBinariaComEstimativa(arr, tamanho, alvo);

    // Exibe o resultado
    if (resultado != -1) {
        printf("Elemento %d encontrado no índice %d.\n", alvo, resultado);
    } else {
        printf("Elemento %d não encontrado.\n", alvo);
    }

    return 0;
}

/*
Contexto e Explicação da Abordagem:

A Busca Binária com Estimativa Inicial (Exponencial) é uma otimização da busca binária tradicional. Ela é útil em cenários onde o tamanho do array é muito grande e o elemento buscado está mais próximo do início do array. A ideia principal é reduzir o intervalo de busca inicial de forma exponencial, antes de aplicar a busca binária.

Passos da abordagem:
1. **Estimativa Inicial (Exponencial):**
   - Começa verificando o primeiro elemento.
   - Dobra o índice (`i *= 2`) a cada iteração até encontrar um valor maior que o alvo ou atingir o final do array.
   - Isso reduz significativamente o intervalo de busca para elementos próximos ao início.

2. **Busca Binária:**
   - Após determinar o intervalo onde o elemento pode estar, aplica a busca binária nesse intervalo.
   - Isso mantém a eficiência da busca binária no intervalo reduzido.

**Complexidade de Tempo:**
- Melhor caso: **O(log k)**, onde `k` é o índice do intervalo onde o elemento está localizado.
- Pior caso: **O(log n)**, onde `n` é o tamanho do array.

**Vantagens:**
- Reduz o número de comparações iniciais para elementos próximos ao início.
- Mantém a eficiência da busca binária.

**Exemplo no código:**
Dado o array `{1, 3, 7, 15, 31, 63, 127, 255, 511, 1023}` e o alvo `127`:
- A estimativa inicial encontra o intervalo `[64, 127]` (índices 4 a 6).
- A busca binária é aplicada nesse intervalo, encontrando o elemento no índice `6`.

Essa abordagem é especialmente útil para arrays muito grandes e pode ser adaptada para outros tipos de dados ordenados.
*/