# Exemplos de Processamento de Imagens

## 📋 Visão Geral

Este diretório contém exemplos de processamento de imagens usando arrays (vetores e matrizes) em C. Demonstra como trabalhar com dados de imagem representados como matrizes de pixels.

## 📚 Arquivos Incluídos

### Exemplos de Código

- **exemplo_iamgem_simples.c** - Exemplo básico de processamento de imagem
- **main.c** - Programa principal com processamento de imagem
- **main_simples.c** - Versão simplificada do programa principal

### Bibliotecas

- **stb_image.h** - Biblioteca para carregar imagens (header-only)
- **stb_image_write.h** - Biblioteca para salvar imagens (header-only)

### Imagens de Teste

- **lena.jpg** - Imagem clássica de teste em processamento de imagens
- **turing.jpg** - Imagem de teste adicional

## 🎯 Conceitos Trabalhados

- Representação de imagens como matrizes de pixels
- Carregamento e salvamento de imagens
- Manipulação de dados de pixels (RGB)
- Processamento básico de imagens
- Uso de bibliotecas header-only

## 🔧 Compilação

### Compilação Básica

```bash
gcc -Wall -Wextra -std=c99 -o processo main.c -lm
./processo
```

### Compilação do Exemplo Simples

```bash
gcc -Wall -Wextra -std=c99 -o simples main_simples.c -lm
./simples
```

**Nota**: A flag `-lm` é necessária para linkar a biblioteca matemática.

## 📖 Estrutura de uma Imagem

Uma imagem colorida é representada como uma matriz 3D:
- **Largura**: Número de pixels horizontalmente
- **Altura**: Número de pixels verticalmente
- **Canais**: Geralmente 3 (RGB) ou 4 (RGBA)

```c
// Exemplo de acesso a um pixel
unsigned char *img = stbi_load("imagem.jpg", &width, &height, &channels, 0);

// Acessar pixel na posição (x, y)
int index = (y * width + x) * channels;
unsigned char r = img[index + 0];  // Red
unsigned char g = img[index + 1];  // Green
unsigned char b = img[index + 2];  // Blue
```

## 💡 Operações Comuns

### Carregar Imagem

```c
int width, height, channels;
unsigned char *img = stbi_load("input.jpg", &width, &height, &channels, 0);
if (img == NULL) {
    printf("Erro ao carregar imagem\n");
    return 1;
}
```

### Salvar Imagem

```c
// Salvar como JPG
stbi_write_jpg("output.jpg", width, height, channels, img, 100);

// Salvar como PNG
stbi_write_png("output.png", width, height, channels, img, width * channels);
```

### Converter para Escala de Cinza

```c
for (int i = 0; i < width * height; i++) {
    int index = i * channels;
    unsigned char r = img[index + 0];
    unsigned char g = img[index + 1];
    unsigned char b = img[index + 2];
    
    // Média ponderada (padrão)
    unsigned char gray = (unsigned char)(0.299 * r + 0.587 * g + 0.114 * b);
    
    img[index + 0] = gray;
    img[index + 1] = gray;
    img[index + 2] = gray;
}
```

### Liberar Memória

```c
stbi_image_free(img);
```

## 🚀 Exemplos de Processamento

1. **Conversão para escala de cinza**
2. **Inversão de cores**
3. **Ajuste de brilho**
4. **Aplicação de filtros**
5. **Detecção de bordas**
6. **Rotação e espelhamento**

## 📚 Sobre stb_image

[stb_image](https://github.com/nothings/stb) é uma biblioteca header-only popular para carregar imagens. Suporta formatos:
- JPEG
- PNG
- BMP
- TGA
- GIF
- PSD
- HDR
- PIC
- PNM

## ⚠️ Observações Importantes

1. **Memória**: Imagens grandes podem consumir muita memória
2. **Formato de Pixels**: Geralmente armazenados como RGB ou RGBA (0-255 por canal)
3. **Coordenadas**: Origem (0,0) geralmente no canto superior esquerdo
4. **Liberação**: Sempre use `stbi_image_free()` para liberar memória

## 🔗 Recursos Adicionais

- [stb Libraries](https://github.com/nothings/stb)
- [Digital Image Processing](https://en.wikipedia.org/wiki/Digital_image_processing)
- [Color Models](https://en.wikipedia.org/wiki/RGB_color_model)

---

**Repositório**: https://github.com/profluiscaparroz/estrutura-dados-c
