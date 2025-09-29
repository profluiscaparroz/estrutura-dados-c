#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <stdio.h>
#include <stdlib.h>

// Aplica o filtro grayscale (tons de cinza) na imagem.
// O algoritmo calcula a média ponderada dos valores de vermelho, verde e azul (RGB) de cada pixel,
// usando os pesos 0.3, 0.59 e 0.11, respectivamente. Esses pesos refletem a percepção humana
// das cores, dando mais importância ao verde. O resultado é atribuído a todos os canais RGB,
// transformando o pixel em um tom de cinza.
void aplicar_grayscale(unsigned char *img, int width, int height, int channels) {
    for (int i = 0; i < width * height * channels; i += channels) {
        unsigned char r = img[i];
        unsigned char g = img[i + 1];
        unsigned char b = img[i + 2];
        unsigned char gray = 0.3 * r + 0.59 * g + 0.11 * b;
        img[i] = img[i + 1] = img[i + 2] = gray;
    }
}

// Aplica o filtro negativo na imagem, invertendo as cores.
// O algoritmo subtrai o valor de cada canal RGB de 255, criando o efeito de negativo.
// Isso inverte as cores, pois os valores mais claros se tornam escuros e vice-versa.
// O impacto visual é uma imagem com cores complementares.
void aplicar_negativo(unsigned char *img, int width, int height, int channels) {
    for (int i = 0; i < width * height * channels; i += channels) {
        img[i] = 255 - img[i];
        img[i + 1] = 255 - img[i + 1];
        img[i + 2] = 255 - img[i + 2];
    }
}

// Aplica o filtro sépia na imagem, criando um efeito envelhecido.
// O algoritmo calcula novos valores para os canais RGB usando uma fórmula específica,
// que combina os valores originais de vermelho, verde e azul com pesos diferentes.
// Os valores resultantes são limitados a 255 para evitar estouro. O efeito sépia
// dá à imagem um tom amarelado, simulando fotos antigas.
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

// Espelha a imagem horizontalmente, invertendo os lados esquerdo e direito.
// O algoritmo percorre cada linha da imagem e troca os pixels das extremidades
// opostas, movendo-se em direção ao centro. Isso é feito para cada canal RGB,
// garantindo que as cores sejam preservadas. O resultado é uma imagem espelhada.
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

// Salva a imagem processada em um arquivo PNG.
// A função usa a biblioteca stb_image_write para criar um arquivo PNG com os dados
// da imagem. O nome do arquivo é especificado pelo usuário, e a função também
// imprime uma mensagem confirmando o salvamento. Isso permite visualizar o resultado
// das alterações feitas na imagem.
void salvar_imagem(const char *nome, unsigned char *img, int width, int height, int channels) {
    stbi_write_png(nome, width, height, channels, img, width * channels);
    printf("Imagem salva como %s\n", nome);
}

// Copia os dados de uma imagem para outra, útil para criar backups.
// O algoritmo percorre todos os bytes da imagem de origem e os copia para o destino.
// Isso é usado para restaurar a imagem original antes de aplicar novos filtros,
// garantindo que cada operação comece com os dados originais.
void copiar_imagem(unsigned char *src, unsigned char *dest, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        dest[i] = src[i];
    }
}

// Ajusta o brilho da imagem com base em um valor fornecido pelo usuário.
// O algoritmo soma o valor do brilho a cada canal RGB de cada pixel. Se o resultado
// ultrapassar 255, ele é limitado a 255; se for menor que 0, é ajustado para 0.
// Isso torna a imagem mais clara ou mais escura, dependendo do valor fornecido.
void ajustar_brilho(unsigned char *img, int width, int height, int channels, int brilho) {
    for (int i = 0; i < width * height * channels; i++) {
        int valor = img[i] + brilho;
        img[i] = (valor > 255) ? 255 : (valor < 0) ? 0 : valor;
    }
}

// Ajusta o contraste da imagem com base em um fator fornecido pelo usuário.
// O algoritmo normaliza os valores dos pixels para o intervalo [0, 1], aplica o fator
// de contraste, e depois reverte a normalização para o intervalo [0, 255]. Valores
// maiores que 1 aumentam o contraste, enquanto valores menores que 1 o reduzem.
// Isso realça ou suaviza as diferenças entre as cores.
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

// Aplica um efeito de desfoque (blur) na imagem usando um kernel 3x3.
// O algoritmo percorre cada pixel (exceto as bordas) e calcula a média dos valores
// dos pixels vizinhos, definidos pelo kernel 3x3. Isso suaviza as transições entre
// os pixels, criando um efeito de desfoque. Uma cópia da imagem original é usada
// para evitar que os cálculos afetem os pixels ainda não processados.
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
    unsigned char *img = stbi_load("turing.jpg", &width, &height, &channels, 0);
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