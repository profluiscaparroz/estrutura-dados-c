#include <stdio.h>
#include <math.h>

int main() {
    double x = 25; // Valor para o qual queremos a raiz quadrada
    double a = 2;  // Chute inicial
    double epsilon = 0.00001; // Tolerância para o quão próximo o resultado deve ser
    double novo_chute;

    // Itera até que o quadrado do chute esteja "perto o suficiente" de x
    while (fabs(a * a - x) > epsilon) {
        novo_chute = (a + x / a) / 2.0; // Calcula o novo chute
        printf("Nome chute: %.5f\n", novo_chute);
        a = novo_chute; // Atualiza o chute
    }

    // Exibe o resultado
    printf("A raiz quadrada aproximada de %.2f eh %.5f\n", x, a);

    return 0;
}
