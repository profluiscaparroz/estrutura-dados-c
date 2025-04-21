#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <stdio.h>
#include <stdlib.h>


void aplicar_grayscale(unsigned char *img, int width, int height, int channels) {
    for (int i = 0; i < width * height * channels; i += channels) {
        unsigned char r = img[i];
        unsigned char g = img[i + 1];
        unsigned char b = img[i + 2];
        unsigned char gray = 0.3 * r + 0.59 * g + 0.11 * b;
        img[i] = img[i + 1] = img[i + 2] = gray;
    }
}

void aplicar_negativo(unsigned char *img, int width, int height, int channels) {
    for (int i = 0; i < width * height * channels; i += channels) {
        img[i] = 255 - img[i];
        img[i + 1] = 255 - img[i + 1];
        img[i + 2] = 255 - img[i + 2];
    }
}

void aplicar_sepia(unsigned char *img, int width, int height, int channels) {
    for (int i = 0; i < width * height * channels; i += channels) {
        unsigned char r = img[i];
        unsigned char g = img[i + 1];
        unsigned char b = img[i + 2];

        int tr = 0.393 * r + 0.769 * g + 0.189 * b;
        int tg = 0.349 * r + 0.686 * g + 0.168 * b;
        int tb = 0.272 * r + 0.534 * g + 0.131 * b;

        img[i]     = (tr > 255) ? 255 : tr;
        img[i + 1] = (tg > 255) ? 255 : tg;
        img[i + 2] = (tb > 255) ? 255 : tb;
    }
}

void espelhar_horizontal(unsigned char *img, int width, int height, int channels) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width / 2; x++) {
            int idx1 = (y * width + x) * channels;
            int idx2 = (y * width + (width - 1 - x)) * channels;
            for (int c = 0; c < channels; c++) {
                unsigned char tmp = img[idx1 + c];
                img[idx1 + c] = img[idx2 + c];
                img[idx2 + c] = tmp;
            }
        }
    }
}

void salvar_imagem(const char *nome, unsigned char *img, int width, int height, int channels) {
    stbi_write_png(nome, width, height, channels, img, width * channels);
    printf("Imagem salva como %s\n", nome);
}

void copiar_imagem(unsigned char *src, unsigned char *dest, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        dest[i] = src[i];
    }
}

void ajustar_brilho(unsigned char *img, int width, int height, int channels, int brilho) {
    for (int i = 0; i < width * height * channels; i++) {
        int valor = img[i] + brilho;
        img[i] = (valor > 255) ? 255 : (valor < 0) ? 0 : valor;
    }
}

void ajustar_contraste(unsigned char *img, int width, int height, int channels, float fator) {
    for (int i = 0; i < width * height * channels; i++) {
        float pixel = img[i] / 255.0;
        pixel -= 0.5;
        pixel *= fator;
        pixel += 0.5;
        pixel *= 255;

        int valor = (int)pixel;
        img[i] = (valor > 255) ? 255 : (valor < 0) ? 0 : valor;
    }
}

void aplicar_blur(unsigned char *img, int width, int height, int channels) {
    unsigned char *copy = malloc(width * height * channels);
    copiar_imagem(img, copy, width * height * channels);

    int kernel[3][3] = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    int kernel_size = 3;
    int kernel_sum = 9;

    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            for (int c = 0; c < channels; c++) {
                int soma = 0;
                for (int ky = 0; ky < kernel_size; ky++) {
                    for (int kx = 0; kx < kernel_size; kx++) {
                        int ix = (x + kx - 1);
                        int iy = (y + ky - 1);
                        soma += copy[(iy * width + ix) * channels + c] * kernel[ky][kx];
                    }
                }
                img[(y * width + x) * channels + c] = soma / kernel_sum;
            }
        }
    }

    free(copy);
}


int main() {
    int width, height, channels;
    unsigned char *img = stbi_load("lena.jpg", &width, &height, &channels, 0);
    if (img == NULL) {
        printf("Erro ao carregar imagem.\n");
        return 1;
    }

    int tamanho = width * height * channels;
    unsigned char *backup = malloc(tamanho); // para restaurar sempre antes de aplicar outro filtro
    copiar_imagem(img, backup, tamanho);

    int opcao;
    do {
        printf("\nEscolha uma operação:\n");
        printf("1 - Grayscale\n");
        printf("2 - Negativo\n");
        printf("3 - Sépia\n");
        printf("4 - Espelhar Horizontalmente\n");
        printf("5 - Ajustar brilho\n");
        printf("6 - Ajustar contraste\n");
        printf("7 - Desfoque (blur)\n");

        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        // Restaurar a imagem original antes de aplicar novo filtro
        copiar_imagem(backup, img, tamanho);

        switch (opcao) {
            case 1:
                aplicar_grayscale(img, width, height, channels);
                salvar_imagem("grayscale.png", img, width, height, channels);
                break;
            case 2:
                aplicar_negativo(img, width, height, channels);
                salvar_imagem("negativo.png", img, width, height, channels);
                break;
            case 3:
                aplicar_sepia(img, width, height, channels);
                salvar_imagem("sepia.png", img, width, height, channels);
                break;
            case 4:
                espelhar_horizontal(img, width, height, channels);
                salvar_imagem("espelhada.png", img, width, height, channels);
                break;
            case 5: {
                int brilho;
                printf("Digite o valor de brilho (-100 a 100): ");
                scanf("%d", &brilho);
                ajustar_brilho(img, width, height, channels, brilho);
                salvar_imagem("brilho.png", img, width, height, channels);
                break;
            }
            case 6: {
                float fator;
                printf("Digite o fator de contraste (ex: 1.2 para aumentar, 0.8 para reduzir): ");
                scanf("%f", &fator);
                ajustar_contraste(img, width, height, channels, fator);
                salvar_imagem("contraste.png", img, width, height, channels);
                break;
            }
            case 7:
                aplicar_blur(img, width, height, channels);
                salvar_imagem("blur.png", img, width, height, channels);
                break;                
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    free(img);
    free(backup);
    return 0;
}
// Compilar com: gcc main.c -o exemploImg -lm
// Executar com: ./exemploImg