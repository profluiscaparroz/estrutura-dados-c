#include <stdio.h>
#include <math.h>
#include <time.h> // Biblioteca para medir o tempo

int main() {
    clock_t inicio = clock(); // Marca o tempo inicial

    double x = 25; 
    double a = 2;  
    double epsilon = 0.00001; 
    double novo_chute;

    int iteracoes = 0;
    while (fabs(a * a - x) > epsilon) {
        novo_chute = (a + x / a) / 2.0; 
        
        // ERRO DE PROJETO: Chamar printf a cada iteração 
        // força o processador a esperar o hardware de vídeo/console.
        printf("Iteracao %d: %.5f\n", iteracoes, novo_chute);
        
        a = novo_chute; 
        iteracoes++;
    }

    clock_t fim = clock(); // Marca o tempo final
    double tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC; //

    printf("\n[Versao Piorada] Tempo decorrido: %.6f segundos\n", tempo_gasto);
    return 0;
}