#include <stdio.h>
#include <string.h>

// Função para copiar uma string
void copiarString(char *destino, const char *origem) {
  // Copia a string de origem para destino
  strcpy(destino, origem);
}

// Função para concatenar strings
void concatenarString(char *destino, const char *origem) {
  // Concatena a string de origem ao final da string destino
  strcat(destino, origem);
}

// Função para comparar duas strings
int compararString(const char *str1, const char *str2) {
  // Compara as duas strings lexicograficamente
  return strcmp(str1, str2);
}

// Função para calcular o tamanho de uma string
size_t tamanhoString(const char *str) {
  // Retorna o comprimento da string
  return strlen(str);
}

// Função para buscar a primeira ocorrência de um caractere em uma string
char *buscarCaractere(const char *str, char c) {
  // Retorna um ponteiro para a primeira ocorrência do caractere c em str
  return strchr(str, c);
}

// Função para buscar a primeira ocorrência de uma substring em uma string
char *buscarSubstring(const char *str, const char *substr) {
  // Retorna um ponteiro para a primeira ocorrência da substring substr em str
  return strstr(str, substr);
}

// Função para dividir uma string em tokens com base em delimitadores
void tokenizarString(char *str, const char *delimitadores) {
  char *token = strtok(str, delimitadores); // Primeira chamada
  while (token != NULL) {
    printf("%s\n", token);               // Imprime o token atual
    token = strtok(NULL, delimitadores); // Próxima chamada
  }
}

// Função para preencher uma área de memória com um byte específico
void preencherMemoria(char *buffer, char c, size_t tamanho) {
  // Preenche o buffer com o caractere c
  memset(buffer, c, tamanho);
}

// Função para comparar duas áreas de memória
int compararMemoria(const void *ptr1, const void *ptr2, size_t tamanho) {
  // Compara as áreas de memória ptr1 e ptr2
  return memcmp(ptr1, ptr2, tamanho);
}

// Função para copiar uma quantidade específica de bytes de uma área de memória
// para outra
void copiarMemoria(void *destino, const void *origem, size_t tamanho) {
  // Copia tamanho bytes de origem para destino
  memcpy(destino, origem, tamanho);
}

// Função para mover uma quantidade específica de bytes de uma área de memória
// para outra
void moverMemoria(void *destino, const void *origem, size_t tamanho) {
  // Move tamanho bytes de origem para destino
  memmove(destino, origem, tamanho);
}

// Função para buscar um byte específico em uma área de memória
void *buscarMemoria(const void *ptr, int c, size_t tamanho) {
  // Retorna um ponteiro para a primeira ocorrência de c em ptr
  return memchr(ptr, c, tamanho);
}

int mainie() {
  // Exemplo de uso das funções

  // Usando a função copiarString
  char destino[20];
  copiarString(destino, "Olá");
  printf("Cópia: %s\n", destino);

  // Usando a função concatenarString
  concatenarString(destino, " mundo");
  printf("Concatenação: %s\n", destino);

  // Usando a função compararString
  int cmp = compararString("abc", "abc");
  printf("Comparação: %d\n", cmp);

  // Usando a função tamanhoString
  size_t len = tamanhoString(destino);
  printf("Tamanho: %zu\n", len);

  // Usando a função buscarCaractere
  char *ptr = buscarCaractere(destino, 'W');
  printf("Buscar caractere: %s\n", ptr);

  // Usando a função buscarSubstring
  ptr = buscarSubstring(destino, "World");
  printf("Buscar substring: %s\n", ptr);

  // Usando a função tokenizarString
  char frase[] = "Hello, World!";
  printf("Tokens:\n");
  tokenizarString(frase, " ,!");

  // Usando a função preencherMemoria
  char buffer[10];
  preencherMemoria(buffer, 'A', 10);
  printf("Preencher memória: ");
  for (int i = 0; i < 10; i++) {
    printf("%c", buffer[i]);
  }
  printf("\n");

  // Usando a função compararMemoria
  int resultadoMemcmp = compararMemoria("abc", "abd", 3);
  printf("Comparar memória: %d\n", resultadoMemcmp);

  // Usando a função copiarMemoria
  char origem[10] = "123456789";
  copiarMemoria(destino, origem, 10);
  printf("Copiar memória: %s\n", destino);

  // Usando a função moverMemoria
  moverMemoria(destino + 1, destino, 9);
  printf("Mover memória: %s\n", destino);

  // Usando a função buscarMemoria
  ptr = buscarMemoria(destino, '2', 10);
  printf("Buscar memória: %s\n", ptr);

  return 0;
}
