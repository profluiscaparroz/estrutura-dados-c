#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>

// Função para converter a imagem para tons de cinza
void aplicar_filtro_cinza(JSAMPLE *imagem, int largura, int altura) {
    for (int i = 0; i < largura * altura; i++) {
        // Pegando os valores RGB do pixel
        unsigned char r = imagem[i * 3];     // Vermelho
        unsigned char g = imagem[i * 3 + 1]; // Verde
        unsigned char b = imagem[i * 3 + 2]; // Azul

        // Calculando a média (fórmula para tons de cinza)
        unsigned char cinza = (r + g + b) / 3;

        // Aplicando o tom de cinza ao pixel
        imagem[i * 3] = imagem[i * 3 + 1] = imagem[i * 3 + 2] = cinza;
    }
}

// Função para ler uma imagem JPEG
JSAMPLE *ler_imagem_jpeg(const char *arquivo, int *largura, int *altura) {
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    FILE *arquivo_jpeg = fopen(arquivo, "rb");
    if (!arquivo_jpeg) {
        printf("Erro ao abrir arquivo %s\n", arquivo);
        return NULL;
    }

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, arquivo_jpeg);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);

    *largura = cinfo.output_width;
    *altura = cinfo.output_height;
    int canais = cinfo.output_components; // Normalmente 3 para RGB

    // Criando matriz para armazenar pixels
    JSAMPLE *imagem = (JSAMPLE *)malloc((*largura) * (*altura) * canais);
    JSAMPROW linha[1];

    // Lendo linha por linha da imagem
    while (cinfo.output_scanline < cinfo.output_height) {
        linha[0] = &imagem[cinfo.output_scanline * (*largura) * canais];
        jpeg_read_scanlines(&cinfo, linha, 1);
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(arquivo_jpeg);

    return imagem;
}

// Função para salvar uma imagem JPEG
void salvar_imagem_jpeg(const char *arquivo, JSAMPLE *imagem, int largura, int altura) {
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;

    FILE *arquivo_saida = fopen(arquivo, "wb");
    if (!arquivo_saida) {
        printf("Erro ao salvar arquivo %s\n", arquivo);
        return;
    }

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, arquivo_saida);

    cinfo.image_width = largura;
    cinfo.image_height = altura;
    cinfo.input_components = 3;  // RGB tem 3 componentes
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, 100, TRUE);
    jpeg_start_compress(&cinfo, TRUE);

    JSAMPROW linha[1];
    while (cinfo.next_scanline < cinfo.image_height) {
        linha[0] = &imagem[cinfo.next_scanline * largura * 3];
        jpeg_write_scanlines(&cinfo, linha, 1);
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
    fclose(arquivo_saida);
}

int main() {
    const char *arquivo_entrada = "CAMINHO DA IMAGEM JPG";
    const char *arquivo_saida = "CAMINHO DA IMAGEM JPG (nome diferente).jpg";

    int largura, altura;

    // Lendo a imagem
    JSAMPLE *imagem = ler_imagem_jpeg(arquivo_entrada, &largura, &altura);
    if (!imagem) return 1;

    // Aplicando filtro de cinza
    aplicar_filtro_cinza(imagem, largura, altura);

    // Salvando a imagem modificada
    salvar_imagem_jpeg(arquivo_saida, imagem, largura, altura);

    // Liberando memória
    free(imagem);

    printf("Imagem convertida para tons de cinza e salva como %s\n", arquivo_saida);
    return 0;
}
