#include <stdio.h>

// Função para realizar o Bubble Sort
void bubbleSort(int arr[], int n) {
    int i, j, temp;

    // Loop externo para controlar o número de passagens
    for (i = 0; i < n - 1; i++) {
        // Loop interno para comparar elementos adjacentes
        for (j = 0; j < n - i - 1; j++) {
            // Se o elemento atual for maior que o próximo, troca os dois
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Função para imprimir o array
void imprimirArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


/**
* Algoritmo Bubble Sort
*
* Esta função implementa o algoritmo Bubble Sort, que é uma técnica de ordenação simples que percorre a lista repetidamente, 
* compara os elementos adjacentes e os troca se estiverem na ordem errada.
* O processo é repetido até que a lista seja ordenada.
*
* Características:
* - Complexidade Temporal:
* - Melhor Caso: O(n) (quando o array já está ordenado)
* - Caso Médio: O(n^2)
* - Pior Caso: O(n^2)
* - Complexidade Espacial: O(1) (ordenação no local)
* - Estável: Sim (não altera a ordem relativa dos elementos iguais)
*
* Como funciona:
* 1. Comece no início do array.
* 2. Compare cada par de elementos adjacentes.
* 3. Troque os elementos se estiverem na ordem errada.

* 4. Repita o processo para todos os elementos, reduzindo o intervalo de comparação
* após cada passagem, à medida que os elementos maiores "surgem" para suas posições
* corretas no final da matriz.
*
* Este algoritmo é adequado para conjuntos de dados pequenos ou para fins educacionais
* mas é ineficiente para conjuntos de dados grandes em comparação com algoritmos de classificação mais avançados
* como Quick Sort ou Merge Sort.
*/
int main() {
    // Exemplo de array para ordenar
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array original: \n");
    imprimirArray(arr, n);

    // Chama a função de ordenação Bubble Sort
    bubbleSort(arr, n);

    printf("Array ordenado: \n");
    imprimirArray(arr, n);

    return 0;
}