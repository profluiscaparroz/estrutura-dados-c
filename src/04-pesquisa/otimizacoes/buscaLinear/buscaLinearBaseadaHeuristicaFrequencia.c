#include <stdio.h>

// Função para realizar a busca linear com otimização baseada em heurística de frequência
void buscaLinearHeuristicaFrequencia(int arr[], int frequencia[], int tamanho, int chave) {
    // Percorre o array para encontrar o elemento
    for (int i = 0; i < tamanho; i++) {
        // Verifica se o elemento atual é igual à chave
        if (arr[i] == chave) {
            // Incrementa a frequência do elemento encontrado
            frequencia[i]++;
            
            // Realiza uma troca para mover o elemento mais acessado para uma posição anterior
            for (int j = i; j > 0 && frequencia[j] > frequencia[j - 1]; j--) {
                // Troca os elementos no array
                int temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;

                // Troca as frequências correspondentes
                int tempFreq = frequencia[j];
                frequencia[j] = frequencia[j - 1];
                frequencia[j - 1] = tempFreq;
            }
            return; // Sai da função após encontrar o elemento
        }
    }
}

int main() {
    // Explicação sobre Otimização Baseada em Heurística de Frequência
    printf("Otimização Baseada em Heurística de Frequência é uma técnica utilizada para melhorar a eficiência de buscas em arrays.\n");
    printf("Ela funciona aumentando a prioridade de elementos mais acessados, movendo-os para posições anteriores no array.\n");
    printf("Isso reduz o tempo médio de busca para elementos frequentemente acessados.\n\n");

    // Exemplo de uso da busca linear com heurística de frequência
    int arr[] = {5, 3, 8, 6, 2};
    int frequencia[] = {0, 0, 0, 0, 0}; // Inicializa as frequências com zero
    int tamanho = sizeof(arr) / sizeof(arr[0]);

    // Realiza algumas buscas
    buscaLinearHeuristicaFrequencia(arr, frequencia, tamanho, 8);
    buscaLinearHeuristicaFrequencia(arr, frequencia, tamanho, 3);
    buscaLinearHeuristicaFrequencia(arr, frequencia, tamanho, 8);

    // Exibe o array atualizado após as buscas
    printf("Array atualizado:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d (frequencia: %d)\n", arr[i], frequencia[i]);
    }

    return 0;
}