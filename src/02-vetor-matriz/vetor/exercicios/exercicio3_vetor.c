#include <stdio.h>

#define CATEGORIAS 3

int main() {
    // Notas dos funcionários
    int A[CATEGORIAS] = {8, 7, 9};   // Funcionário A
    int B[CATEGORIAS] = {6, 7, 10};  // Funcionário B

    int pointsA = 0, pointsB = 0;

    for (int i = 0; i < CATEGORIAS; i++) {
        if (A[i] > B[i]) {
            pointsA++;
        } else if (B[i] > A[i]) {
            pointsB++;
        }
    }

    printf("Pontuação final:\n");
    printf("Funcionário A: %d ponto(s)\n", pointsA);
    printf("Funcionário B: %d ponto(s)\n", pointsB);

    return 0;
}