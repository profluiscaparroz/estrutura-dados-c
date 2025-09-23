#include <stdio.h>

#define SIZE 5

int main() {
    int precos[SIZE] = {10, 20, 35, 50, 75};
    int alvo = 55;
    int i, j;
    int encontrou = 0;

    // Percorre todos os pares de elementos
    for (i = 0; i < SIZE - 1; i++) {
        for (j = i + 1; j < SIZE; j++) {
            if (precos[i] + precos[j] == alvo) {
                printf("Produtos encontrados nos índices [%d, %d]\n", i, j);
                encontrou = 1;
                break; // Sai do loop interno
            }
        }
        if (encontrou) break; // Sai do loop externo também
    }

    if (!encontrou) {
        printf("Nenhum par encontrado que some ao valor alvo.\n");
    }

    return 0;
}
