#include <stdio.h>
#include <math.h>
#include <time.h> // Biblioteca para medir o tempo

int main() {
    clock_t inicio = clock(); // Marca o tempo inicial

    double x = 25; 
    double a = 2;  
    double epsilon = 0.00001; 

    // ESTRUTURA DE DADOS: Um array para guardar o histórico completo
    double historico_chutes[100]; 
    int total_iteracoes = 0;

    // 1. Processamento focado e isolado na memória (sem pausas de I/O)
    while (fabs(a * a - x) > epsilon && total_iteracoes < 100) {
        a = (a + x / a) / 2.0; 
        historico_chutes[total_iteracoes] = a; // Salvando na estrutura de dados
        total_iteracoes++;
    }

    clock_t fim = clock(); // Marca o tempo final
    double tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC; //

    // 2. Exibição organizada dos dados estruturados apenas no final
    printf("--- RELATORIO DA ESTRUTURA DE DADOS ---\n");
    for (int i = 0; i < total_iteracoes; i++) {
        printf("Historico da posicao [%d] = %.5f\n", i, historico_chutes[i]);
    }

    printf("\n[Versao Melhorada] Tempo decorrido: %.6f segundos\n", tempo_gasto);
    return 0;
}