#include <stdio.h>

// Função para realizar a busca ternária
// Parâmetros:
// - arr: array ordenado onde será realizada a busca
// - esquerda: índice inicial do intervalo de busca
// - direita: índice final do intervalo de busca
// - alvo: elemento a ser buscado
// Retorna:
// - O índice do elemento encontrado ou -1 se o elemento não estiver no array
int buscaTernaria(int arr[], int esquerda, int direita, int alvo) {
    while (esquerda <= direita) {
        // Divide o intervalo em três partes
        int terco1 = esquerda + (direita - esquerda) / 3; // Primeiro ponto de divisão
        int terco2 = direita - (direita - esquerda) / 3;  // Segundo ponto de divisão

        // Verifica se o elemento está em um dos pontos de divisão
        if (arr[terco1] == alvo) {
            return terco1; // Retorna o índice do primeiro terço
        }
        if (arr[terco2] == alvo) {
            return terco2; // Retorna o índice do segundo terço
        }

        // Decide em qual dos três intervalos continuar a busca
        if (alvo < arr[terco1]) {
            // O elemento está no primeiro terço
            direita = terco1 - 1;
        } else if (alvo > arr[terco2]) {
            // O elemento está no terceiro terço
            esquerda = terco2 + 1;
        } else {
            // O elemento está no intervalo entre os dois terços
            esquerda = terco1 + 1;
            direita = terco2 - 1;
        }
    }

    return -1; // Retorna -1 se o elemento não for encontrado
}

int main() {
    // Array ordenado para realizar a busca
    int arr[] = {1, 3, 7, 15, 31, 63, 127, 255, 511, 1023};
    int tamanho = sizeof(arr) / sizeof(arr[0]); // Calcula o tamanho do array
    int alvo = 127; // Elemento a ser buscado

    // Chama a função de busca ternária
    int resultado = buscaTernaria(arr, 0, tamanho - 1, alvo);

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

A Busca Ternária é uma extensão da Busca Binária. Em vez de dividir o intervalo de busca em duas partes, ela divide o intervalo em três partes iguais. Isso reduz o número de elementos a serem verificados em cada iteração, tornando-a eficiente em alguns casos.

Passos da abordagem:
1. **Divisão do intervalo:**
   - O intervalo de busca é dividido em três partes usando dois pontos de divisão:
     - `terco1`: Um terço do intervalo.
     - `terco2`: Dois terços do intervalo.
   - Esses pontos são calculados como:
     - `terco1 = esquerda + (direita - esquerda) / 3`
     - `terco2 = direita - (direita - esquerda) / 3`

2. **Verificação dos pontos de divisão:**
   - Verifica se o elemento buscado está em `terco1` ou `terco2`.

3. **Redução do intervalo:**
   - Se o elemento for menor que `arr[terco1]`, a busca continua no primeiro terço.
   - Se o elemento for maior que `arr[terco2]`, a busca continua no terceiro terço.
   - Caso contrário, a busca continua no intervalo entre `terco1` e `terco2`.

4. **Repetição:**
   - O processo é repetido até que o intervalo de busca seja reduzido a zero ou o elemento seja encontrado.

**Complexidade de Tempo:**
- Melhor caso: **O(1)**, se o elemento for encontrado em uma das divisões iniciais.
- Pior caso: **O(log3(n))**, onde `n` é o tamanho do array. Isso ocorre porque o intervalo é reduzido em um terço a cada iteração.

**Vantagens:**
- Divide o intervalo em três partes, reduzindo o número de comparações em alguns casos.

**Desvantagens:**
- A constante de tempo associada à divisão em três partes pode torná-la menos eficiente que a Busca Binária em muitos casos.

**Exemplo no código:**
Dado o array `{1, 3, 7, 15, 31, 63, 127, 255, 511, 1023}` e o alvo `127`:
- A busca ternária divide o intervalo em três partes:
  - Primeiro terço: `[1, 3, 7]`
  - Segundo terço: `[15, 31, 63]`
  - Terceiro terço: `[127, 255, 511, 1023]`
- O elemento `127` é encontrado no terceiro terço, no índice `6`.

Essa abordagem é útil em cenários onde a divisão em três partes pode ser mais vantajosa que a divisão em duas partes, mas geralmente a Busca Binária é mais prática devido à sua simplicidade e eficiência.
*/