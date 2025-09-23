#include <stdio.h>

#define SIZE 6

int main() {
    int plays[SIZE] = {120, 150, 80, 200, 300, 250};
    int somaMax = 0;
    int i;
    int dia1 = 0, dia2 = 0;

    // Percorre os pares consecutivos
    for (i = 0; i < SIZE - 1; i++) {
        int soma = plays[i] + plays[i + 1];
        if (soma > somaMax) {
            somaMax = soma;
            dia1 = i;
            dia2 = i + 1;
        }
    }

    printf("Maior soma de reproduções consecutivas: %d (dias %d e %d)\n",
           somaMax, dia1, dia2);

    return 0;
}