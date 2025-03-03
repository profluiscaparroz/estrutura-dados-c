#include <stdio.h>

int main() {
    // Declaração e inicialização da matriz 2x3
    int matriz[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    // Acessando e imprimindo os elementos
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("Elemento [%d][%d] = %d\n", i, j, matriz[i][j]);
        }
    }

    return 0;
}
