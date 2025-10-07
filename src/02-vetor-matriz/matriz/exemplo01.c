#include <stdio.h>

int main() {
    float aluno1[4] = {7.5, 8.0, 6.0, 9.0};
    float aluno2[4] = {5.0, 6.5, 7.0, 8.0};
    float aluno3[4] = {9.0, 8.5, 9.5, 10.0};

    // Calcular a média do aluno 2
    float media = (aluno2[0] + aluno2[1] + aluno2[2] + aluno2[3]) / 4;
    printf("Media do aluno 2: %.2f\n", media);

    return 0;
}
