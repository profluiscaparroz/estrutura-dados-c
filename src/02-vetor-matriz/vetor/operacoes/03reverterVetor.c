#include <stdlib.h>
#include <stdio.h>

// Função para reverter um vetor
void reverterVetor(int *vetor, int tamanho) {
    // Itera sobre metade do vetor
    for (int i = 0; i < tamanho / 2; i++) {
        // Troca os elementos simétricos em relação ao centro do vetor
        int temp = vetor[i];
        vetor[i] = vetor[tamanho - i - 1];
        vetor[tamanho - i - 1] = temp;
    }
}

void reverterVetorSemPonteiros(int vetor[], int tamanho) {
    // Itera sobre metade do vetor
    for (int i = 0; i < tamanho / 2; i++) {
        // Troca os elementos simétricos em relação ao centro do vetor
        int temp = vetor[i];
        vetor[i] = vetor[tamanho - i - 1];
        vetor[tamanho - i - 1] = temp;
    }
}

void reverterVetorComAuxiliar(int vetor[], int tamanhoVetor) {
    int* vetorAuxiliar = (int*)malloc(tamanhoVetor * sizeof(int));
    if(vetorAuxiliar == NULL) {
        printf("Erro de alocacao de memoria\n");
        return;
    }
    for (int i = 0; i < tamanhoVetor; i++) {
        vetorAuxiliar[i] = vetor[tamanhoVetor - i - 1];
    }
}

int main() {
    // Declaração e inicialização do vetor
    int vetor[] = {1, 2, 3, 4, 5};
    int tamanho = 5; // Tamanho do vetor

    // Chama a função reverterVetor
    reverterVetor(vetor, tamanho);

    // Imprime o vetor revertido
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }

    return 0; // Retorna 0 indicando que o programa foi executado com sucesso
}
// Output: 5 4 3 2 1