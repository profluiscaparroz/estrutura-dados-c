#include <stdio.h>

// Função para mesclar dois subarrays em ordem crescente
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1; // Tamanho do subarray esquerdo
    int n2 = right - mid;    // Tamanho do subarray direito

    // Arrays temporários para armazenar os subarrays
    int L[n1], R[n2];

    // Copia os dados para os arrays temporários
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Índices iniciais dos subarrays e do array mesclado
    int i = 0, j = 0, k = left;

    // Mescla os subarrays de volta no array original
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes do subarray esquerdo, se houver
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copia os elementos restantes do subarray direito, se houver
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Função recursiva para dividir o array e ordenar as partes
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; // Calcula o ponto médio

        // Ordena a primeira e a segunda metade
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Mescla as duas metades ordenadas
        merge(arr, left, mid, right);
    }
}

// Função para imprimir o array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

/*
O algoritmo Merge Sort é um dos algoritmos de ordenação mais eficientes, 
baseado no paradigma Dividir e Conquistar (Divide and Conquer). 
Ele divide o problema em subproblemas menores, resolve cada subproblema 
recursivamente e, em seguida, combina as soluções para resolver o problema original. 
Aqui está uma explicação detalhada:

Passos do Merge Sort:
    1. Divisão do Array:
        O array original é dividido recursivamente em duas metades até que cada 
        subarray tenha apenas um elemento (um array com um único elemento já está ordenado).
    2. Conquista (Ordenação e Combinação):
        Após dividir o array em partes menores, o algoritmo começa a combinar os subarrays de forma ordenada.
        A combinação é feita utilizando a técnica de merge, onde dois subarrays ordenados são mesclados em um único array ordenado.
    3. Finalização:
        O processo de mesclagem continua até que todas as divisões sejam combinadas, 
        resultando em um array completamente ordenado.
Características do Merge Sort:
    - É um algoritmo de ordenação estável, o que significa que mantém a ordem relativa dos elementos iguais.
    - Funciona bem com listas grandes e é eficiente para dados que não cabem na memória (pode ser implementado em disco).
    - A complexidade de tempo é O(n log n) no pior caso, melhor caso e caso médio, onde n é o número de elementos no array.
    - A complexidade de espaço é O(n), pois requer espaço adicional para os arrays temporários usados durante a mesclagem.
Complexidade de Tempo:
    Melhor caso, pior caso e caso médio: O(n log n), onde n é o número de elementos no array.
Complexidade de Espaço:
    O Merge Sort requer espaço adicional proporcional ao tamanho do array, 
    pois utiliza arrays temporários para a mesclagem.
Estabilidade:
    O Merge Sort é um algoritmo estável, ou seja, mantém a ordem relativa dos 
    elementos iguais.

Funcionamento com um Exemplo:
    Dado o array [12, 11, 13, 5, 6, 7]:

    1. Divida o array em duas metades: [12, 11, 13] e [5, 6, 7].
    2. Continue dividindo até obter subarrays unitários:
        [12], [11], [13], [5], [6], [7].
    3. Combine os subarrays ordenados:
        [11, 12] (mescla [12] e [11]).
        [11, 12, 13] (mescla [11, 12] e [13]).
        [5, 6] (mescla [5] e [6]).
        [5, 6, 7] (mescla [5, 6] e [7]).
    4. Combine as duas metades ordenadas:
        [5, 6, 7, 11, 12, 13].
*/
// Função principal para demonstrar o Merge Sort
int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Array original:\n");
    printArray(arr, size);

    mergeSort(arr, 0, size - 1);

    printf("Array ordenado:\n");
    printArray(arr, size);

    return 0;
}