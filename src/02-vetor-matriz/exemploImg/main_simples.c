#include <stdio.h>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" // Biblioteca para carregar imagens
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h" // Biblioteca para salvar imagens

// Função para aumentar o brilho da imagem
// Parâmetros:
// - img: ponteiro para os dados da imagem
// - total_pixels: número total de pixels na imagem
void aumentar_brilho(unsigned char *img, int total_pixels) {
    // Percorre todos os canais (R, G, B) de todos os pixels
    for (int i = 0; i < total_pixels * 3; i++) {
        int novo_valor = img[i] + 3; // Aumenta o brilho adicionando 3 ao valor do canal
        img[i] = (novo_valor > 255) ? 255 : novo_valor; // Garante que o valor não ultrapasse 255
    }
}

int main() {
    int largura, altura, canais;

    // Carrega a imagem original
    // Parâmetros:
    // - "lena.jpg": nome do arquivo da imagem
    // - largura, altura, canais: variáveis para armazenar as dimensões e o número de canais da imagem
    // - 3: força a imagem a ser carregada com 3 canais (R, G, B)
    unsigned char *img = stbi_load("lena.jpg", &largura, &altura, &canais, 3);
    
    // Verifica se a imagem foi carregada com sucesso
    if (img == NULL) {
        printf("Erro ao carregar imagem.\n");
        return 1; // Encerra o programa em caso de erro
    }

    // Exibe informações sobre a imagem carregada
    printf("Imagem carregada: %dx%d, canais: %d\n", largura, altura, canais);
    printf("Imagem carregada com sucesso!\n");
    printf("Dimensões: %d x %d\n", largura, altura);
    printf("Canais: %d\n", canais);

    // Exibe os valores de RGB para os primeiros 10 pixels
    int max = largura * altura; // Calcula o número total de pixels
    for (int i = 0; i < max && i < 10; i++) { // Limita a exibição aos primeiros 10 pixels
        int index = i * 3; // Calcula o índice do pixel no array (cada pixel tem 3 canais: R, G, B)
        unsigned char r = img[index];       // Valor do canal vermelho
        unsigned char g = img[index + 1];   // Valor do canal verde
        unsigned char b = img[index + 2];   // Valor do canal azul
        printf("Pixel %d: R=%d G=%d B=%d\n", i, r, g, b); // Exibe os valores de RGB do pixel
    }

    // Aplica o aumento de brilho na imagem
    aumentar_brilho(img, largura * altura);

    // Salva a imagem modificada em formato PNG
    // Parâmetros:
    // - "saida.png": nome do arquivo de saída
    // - largura, altura: dimensões da imagem
    // - 3: número de canais (R, G, B)
    // - img: ponteiro para os dados da imagem
    // - largura * 3: número de bytes por linha da imagem
    if (stbi_write_png("saida.png", largura, altura, 3, img, largura * 3)) {
        printf("Imagem salva com sucesso como 'saida.png'\n");
    } else {
        printf("Erro ao salvar imagem.\n");
    }

    // Libera a memória alocada para a imagem
    stbi_image_free(img);

    return 0; // Retorna 0 indicando que o programa foi executado com sucesso
}