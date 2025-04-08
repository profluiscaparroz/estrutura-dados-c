#include <stdio.h>

// Função para encontrar a maior soma de dois dias consecutivos
// Parâmetros:
// - reproducoes: vetor de inteiros representando reproduções diárias
// - tamanho: tamanho do vetor
// Retorna:
// - A maior soma de dois dias consecutivos
// - -1 se o vetor tiver menos de dois elementos
int encontrar_maior_soma_consecutiva(int reproducoes[], int tamanho) {
    if (tamanho < 2) { // Verifica se o vetor possui pelo menos dois elementos
        printf("Lista deve ter pelo menos dois dias.\n");
        return -1; // Retorna -1 indicando erro
    }

    // Inicializa a maior soma com a soma dos dois primeiros elementos
    int maior_soma = reproducoes[0] + reproducoes[1];

    // Percorre o vetor a partir do segundo elemento até o penúltimo
    for (int i = 1; i < tamanho - 1; i++) {
        int soma_atual = reproducoes[i] + reproducoes[i + 1]; // Soma dois elementos consecutivos
        if (soma_atual > maior_soma) { // Verifica se a soma atual é maior que a maior soma
            maior_soma = soma_atual; // Atualiza a maior soma
        }
    }

    return maior_soma; // Retorna a maior soma encontrada
}

int main() {
    // Declaração e inicialização do vetor de reproduções diárias
    int reproducoes[] = {120, 150, 80, 200, 300, 250};
    int tamanho = sizeof(reproducoes) / sizeof(reproducoes[0]); // Calcula o tamanho do vetor

    // Chama a função para encontrar a maior soma de dois dias consecutivos
    int resultado = encontrar_maior_soma_consecutiva(reproducoes, tamanho);

    // Exibe o resultado
    printf("Maior soma de dois dias consecutivos: %d\n", resultado);

    return 0; // Retorna 0 indicando que o programa foi executado com sucesso
}