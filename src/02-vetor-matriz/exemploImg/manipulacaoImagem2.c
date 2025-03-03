#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>
#include <math.h>

// Definição de alguns filtros (Matrizes de convolução)
const int blurKernel[3][3] = {
    {1, 2, 1},
    {2, 4, 2},
    {1, 2, 1}
};

const int sharpenKernel[3][3] = {
    { 0, -1,  0},
    {-1,  5, -1},
    { 0, -1,  0}
};

const int edgeKernel[3][3] = {
    {-1, -1, -1},
    {-1,  8, -1},
    {-1, -1, -1}
};

// Função para carregar a imagem JPEG
unsigned char* load_jpeg(const char* filename, int* width, int* height, int* channels) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Erro ao abrir a imagem!\n");
        return NULL;
    }

    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, file);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);

    *width = cinfo.output_width;
    *height = cinfo.output_height;
    *channels = cinfo.output_components;
    int row_stride = (*width) * (*channels);

    unsigned char* data = (unsigned char*)malloc((*width) * (*height) * (*channels));
    unsigned char* buffer_array[1];

    while (cinfo.output_scanline < cinfo.output_height) {
        buffer_array[0] = data + (cinfo.output_scanline) * row_stride;
        jpeg_read_scanlines(&cinfo, buffer_array, 1);
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(file);

    return data;
}

// Função para salvar uma imagem JPEG
void save_jpeg(const char* filename, unsigned char* data, int width, int height, int channels, int quality) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        printf("Erro ao salvar a imagem!\n");
        return;
    }

    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, file);

    cinfo.image_width = width;
    cinfo.image_height = height;
    cinfo.input_components = channels;
    cinfo.in_color_space = JCS_RGB;
    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, quality, TRUE);
    jpeg_start_compress(&cinfo, TRUE);

    int row_stride = width * channels;
    unsigned char* buffer_array[1];

    while (cinfo.next_scanline < cinfo.image_height) {
        buffer_array[0] = data + cinfo.next_scanline * row_stride;
        jpeg_write_scanlines(&cinfo, buffer_array, 1);
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
    fclose(file);
}

// Função para aplicar um filtro de convolução
void apply_filter(unsigned char* image, unsigned char* output, int width, int height, int channels, const int kernel[3][3], int kernel_div) {
    int offset = 1; // Para considerar os vizinhos na matriz 3x3

    for (int y = offset; y < height - offset; y++) {
        for (int x = offset; x < width - offset; x++) {
            int r = 0, g = 0, b = 0;

            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    int pixelX = (x + kx);
                    int pixelY = (y + ky);
                    int index = (pixelY * width + pixelX) * channels;

                    r += image[index] * kernel[ky + 1][kx + 1];
                    g += image[index + 1] * kernel[ky + 1][kx + 1];
                    b += image[index + 2] * kernel[ky + 1][kx + 1];
                }
            }

            // Normaliza os valores
            int index = (y * width + x) * channels;
            output[index] = (unsigned char) fmin(fmax(r / kernel_div, 0), 255);
            output[index + 1] = (unsigned char) fmin(fmax(g / kernel_div, 0), 255);
            output[index + 2] = (unsigned char) fmin(fmax(b / kernel_div, 0), 255);
        }
    }
}

int main() {
    const char* input_file = "entrada.jpg";
    const char* blur_file = "blur.jpg";
    const char* sharpen_file = "sharpen.jpg";
    const char* edge_file = "edges.jpg";

    int width, height, channels;
    unsigned char* image = load_jpeg(input_file, &width, &height, &channels);
    if (!image) return 1;

    unsigned char* blur_image = (unsigned char*)malloc(width * height * channels);
    unsigned char* sharpen_image = (unsigned char*)malloc(width * height * channels);
    unsigned char* edge_image = (unsigned char*)malloc(width * height * channels);

    // Aplicando os filtros
    apply_filter(image, blur_image, width, height, channels, blurKernel, 16);
    apply_filter(image, sharpen_image, width, height, channels, sharpenKernel, 1);
    apply_filter(image, edge_image, width, height, channels, edgeKernel, 1);

    // Salvando as imagens filtradas
    save_jpeg(blur_file, blur_image, width, height, channels, 90);
    save_jpeg(sharpen_file, sharpen_image, width, height, channels, 90);
    save_jpeg(edge_file, edge_image, width, height, channels, 90);

    // Liberar memória
    free(image);
    free(blur_image);
    free(sharpen_image);
    free(edge_image);

    printf("Imagens geradas com sucesso!\n");
    return 0;
}
