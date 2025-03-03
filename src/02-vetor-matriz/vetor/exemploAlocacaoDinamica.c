#include <stdio.h>
#include <stdlib.h>

// Função para exibir o vetor
void exibirVetor(int *vetor, int tamanho) {
    printf("Vetor: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

int main() {
    int capacidade = 2; // Capacidade inicial do vetor dinâmico
    int tamanho = 0;    // Quantidade real de elementos
    int *vetor = (int *)malloc(capacidade * sizeof(int)); // Alocação inicial

    if (vetor == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    printf("Digite números inteiros para armazenar no vetor (-1 para parar):\n");
    
    while (1) {
        int num;
        scanf("%d", &num);
        
        if (num == -1) break; // Condição de parada

        // Verifica se o vetor precisa ser expandido
        if (tamanho == capacidade) {
            capacidade *= 2; // Dobra a capacidade
            int *novoVetor = (int *)realloc(vetor, capacidade * sizeof(int));
            if (novoVetor == NULL) {
                printf("Erro ao realocar memória!\n");
                free(vetor);
                return 1;
            }
            vetor = novoVetor;
        }

        vetor[tamanho] = num; // Adiciona o número ao vetor
        tamanho++;

        exibirVetor(vetor, tamanho); // Mostra o vetor atualizado
    }

    printf("Vetor final armazenado:\n");
    exibirVetor(vetor, tamanho);

    free(vetor); // Libera memória alocada
    return 0;
}
