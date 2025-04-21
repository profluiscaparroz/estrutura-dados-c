#include <stdio.h>

// Função para realizar o algoritmo de ordenação por inserção (Insertion Sort)
void insertionSort(int arr[], int n) {
    // Percorre o array a partir do segundo elemento
    for (int i = 1; i < n; i++) {
        int key = arr[i]; // Elemento atual a ser inserido na posição correta
        int j = i - 1;

        // Move os elementos maiores que 'key' uma posição à frente
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        // Insere o elemento na posição correta
        arr[j + 1] = key;
    }
}

// Função para imprimir o array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/**
 * Algoritmo InsertSort:
 * 
 * O InsertSort é um algoritmo de ordenação que funciona de maneira semelhante 
 * à forma como organizamos cartas em um jogo. Ele constrói a lista ordenada 
 * gradualmente, um elemento por vez, movendo cada elemento para sua posição 
 * correta em relação aos elementos já ordenados.
 * 
 * Passos do algoritmo:
 * 1. Percorre o array a partir do segundo elemento (índice 1).
 * 2. Para cada elemento, compara-o com os elementos anteriores (da direita para a esquerda).
 * 3. Move os elementos maiores que o elemento atual uma posição para a direita.
 * 4. Insere o elemento atual na posição correta.
 * 
 * Complexidade:
 * - Melhor caso (array já ordenado): O(n)
 * - Pior caso (array em ordem inversa): O(n^2)
 * - Caso médio: O(n^2)
 * 
 * Este algoritmo é eficiente para listas pequenas ou quase ordenadas, mas 
 * não é recomendado para listas grandes devido à sua complexidade quadrática 
 * no pior caso.
 * 
 * Vantagens:
 * - Simples de implementar.
 * - Estável (não altera a ordem relativa de elementos iguais).
 * 
 * Desvantagens:
 * - Ineficiente para grandes conjuntos de dados.
 */
// Função principal
int main() {
    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array original:\n");
    printArray(arr, n);

    insertionSort(arr, n);

    printf("Array ordenado:\n");
    printArray(arr, n);

    return 0;
}