#include <stdio.h>
#include <stdlib.h>

// Função para ordenar o vetor usando Bubble Sort
void bubbleSort(int *arr, int n) {
    int temp;
    int trocou;
    for (int i = 0; i < n - 1; i++) {
        trocou = 0; // Indica se houve troca na iteração
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) { // Se o elemento for maior que o próximo, troca
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                trocou = 1;
            }
        }
        if (!trocou) break; // Se nenhuma troca ocorreu, o vetor já está ordenado
    }
}

// Função de busca binária em um vetor ordenado
int buscaBinaria(int *arr, int esq, int dir, int chave) {
    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;
        
        if (arr[meio] == chave)
            return meio; // Retorna o índice do elemento encontrado
        
        if (arr[meio] < chave)
            esq = meio + 1; // Busca na metade direita
        else
            dir = meio - 1; // Busca na metade esquerda
    }
    return -1; // Retorna -1 se o elemento não for encontrado
}

int main() {
    int n;

    // Solicita ao usuário o tamanho do vetor
    printf("Digite o número de elementos: ");
    scanf("%d", &n);

    // Aloca dinamicamente memória para o vetor
    int *vetor = (int *)malloc(n * sizeof(int));
    if (vetor == NULL) {
        printf("Erro de alocação de memória!\n");
        return 1;
    }

    // Recebendo os elementos do usuário
    printf("Digite %d números:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &vetor[i]);
    }

    // Ordena o vetor
    bubbleSort(vetor, n);
    
    // Exibe o vetor ordenado
    printf("Vetor ordenado: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    // Solicita um número para buscar
    int chave;
    printf("Digite um número para buscar no vetor: ");
    scanf("%d", &chave);

    // Busca binária no vetor ordenado
    int resultado = buscaBinaria(vetor, 0, n - 1, chave);
    
    if (resultado != -1)
        printf("Número %d encontrado na posição %d.\n", chave, resultado);
    else
        printf("Número %d não encontrado no vetor.\n", chave);

    // Libera a memória alocada
    free(vetor);

    return 0;
}
