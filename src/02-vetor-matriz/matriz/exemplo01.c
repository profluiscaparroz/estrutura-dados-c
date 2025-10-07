#include <stdio.h>

void exemploVetor() {
    float aluno1[4] = {7.5, 8.0, 6.0, 9.0};
    float aluno2[4] = {5.0, 6.5, 7.0, 8.0};
    float aluno3[4] = {9.0, 8.5, 9.5, 10.0};

    // Calcular a média do aluno 2
    float media = (aluno2[0] + aluno2[1] + aluno2[2] + aluno2[3]) / 4;
    printf("Media do aluno 2: %.2f\n", media);
}

void exemploMatriz() {
    float notas[3][4] = {
        {7.5, 8.0, 6.0, 9.0},  // Notas do aluno 1
        {5.0, 6.5, 7.0, 8.0},  // Notas do aluno 2
        {9.0, 8.5, 9.5, 10.0}  // Notas do aluno 3
    };

    // Calcular a média do aluno 2
    float media = (notas[1][0] + notas[1][1] + notas[1][2] + notas[1][3]) / 4;
    printf("Media do aluno 2: %.2f\n", media);
}

void pegarTamanhoMatriz(){
    int matriz[3][4] = {0};
    printf("Tamanho da matriz: %zu bytes\n", sizeof(matriz));
    printf("Numero de linhas: %zu\n", sizeof(matriz) / sizeof(matriz[0]));
    printf("Numero de colunas: %zu\n", sizeof(matriz[0]) / sizeof(matriz[0][0]));
}

int main() {

    pegarTamanhoMatriz();
    return 0;
}
