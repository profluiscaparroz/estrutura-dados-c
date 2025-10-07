#include <stdio.h>

int main() {
    int matriz[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    printf("Enderecos dos elementos da matriz:\n\n");

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            printf("&matriz[%d][%d] = %p  (valor = %d)\n", 
                   i, j, (void*)&matriz[i][j], matriz[i][j]);
        }
        printf("\n");
    }

    return 0;
}
