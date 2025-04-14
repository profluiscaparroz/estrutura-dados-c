#include <stdio.h>

// Função para encontrar dois números no vetor cuja soma seja igual ao valor alvo
// Parâmetros:
// - precos: vetor de inteiros representando os preços
// - tamanho: tamanho do vetor
// - alvo: valor alvo que a soma de dois elementos deve atingir
void encontrar_pares(int precos[], int tamanho, int alvo) {
    // Percorre o vetor com dois laços aninhados para verificar todas as combinações de pares
    for (int i = 0; i < tamanho; i++) {
        for (int j = i + 1; j < tamanho; j++) { // Começa de i + 1 para evitar pares repetidos
            if (precos[i] + precos[j] == alvo) { // Verifica se a soma dos dois elementos é igual ao alvo
                printf("Índices encontrados: [%d, %d]\n", i, j); // Exibe os índices dos elementos encontrados
                return; // Encerra a função após encontrar o primeiro par
            }
        }
    }
    // Caso nenhum par seja encontrado, exibe uma mensagem
    printf("Nenhum par encontrado.\n");
}


int main() {
    // Declaração e inicialização do vetor de preços
    int precos[] = {10, 20, 35, 50, 75};
    int tamanho = sizeof(precos) / sizeof(precos[0]); // Calcula o tamanho do vetor
    int valor_alvo = 55; // Define o valor alvo para a soma dos pares

    // Chama a função para encontrar pares que somem ao valor alvo
    encontrar_pares(precos, tamanho, valor_alvo);

    return 0; // Retorna 0 indicando que o programa foi executado com sucesso
}