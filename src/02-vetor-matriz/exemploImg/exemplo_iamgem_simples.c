#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *arquivo = fopen("lena.jpg", "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    char formato[3];
    int largura, altura, maxValor;

    // Lê cabeçalho
    fscanf(arquivo, "%s", formato);       // P3
    fscanf(arquivo, "%d %d", &largura, &altura); // largura e altura
    fscanf(arquivo, "%d", &maxValor);     // valor máximo da cor (255)

    printf("Formato: %s\n", formato);
    printf("Tamanho: %dx%d\n", largura, altura);
    printf("Valor máximo de cor: %d\n\n", maxValor);

    // Aloca memória para os pixels
    int tamanho = largura * altura;
    int *pixels = malloc(tamanho * 3 * sizeof(int)); // R, G, B

    // Lê todos os valores RGB
    for (int i = 0; i < tamanho * 3; i++) {
        fscanf(arquivo, "%d", &pixels[i]);
    }

    fclose(arquivo);

    // Exibe os pixels RGB
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            int idx = (i * largura + j) * 3;
            printf("Pixel (%d,%d): R=%d G=%d B=%d\n", 
                   i, j, pixels[idx], pixels[idx + 1], pixels[idx + 2]);
        }
    }

    free(pixels);
    return 0;
}
