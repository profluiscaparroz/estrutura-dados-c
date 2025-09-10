#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Programa de exemplo para busca de palavras em strings usando funções da string.h
 * 
 * Este arquivo demonstra diferentes técnicas de busca de palavras/substrings
 * utilizando as funções padrão da biblioteca string.h do C.
 * 
 * Operações implementadas:
 * 1. Busca simples de substring (strstr)
 * 2. Busca de caractere (strchr)
 * 3. Busca case-insensitive
 * 4. Busca de múltiplas ocorrências
 * 5. Busca de palavra completa
 */

// Função para procurar uma substring em uma string usando strstr()
// Parâmetros:
// - texto: string onde será feita a busca
// - palavra: substring a ser procurada
// Retorna:
// - Ponteiro para a primeira ocorrência da palavra no texto
// - NULL se a palavra não for encontrada
char* procurarSubstring(const char* texto, const char* palavra) {
    if (texto == NULL || palavra == NULL) {
        return NULL;
    }
    return strstr(texto, palavra);
}

// Função para procurar um caractere em uma string usando strchr()
// Parâmetros:
// - texto: string onde será feita a busca
// - caractere: caractere a ser procurado
// Retorna:
// - Ponteiro para a primeira ocorrência do caractere no texto
// - NULL se o caractere não for encontrado
char* procurarCaractere(const char* texto, char caractere) {
    if (texto == NULL) {
        return NULL;
    }
    return strchr(texto, caractere);
}

// Função auxiliar para converter string para minúsculas
// Parâmetros:
// - destino: string de destino (deve ter espaço suficiente)
// - origem: string a ser convertida
void paraMinuscula(char* destino, const char* origem) {
    if (destino == NULL || origem == NULL) {
        return;
    }
    
    int i = 0;
    while (origem[i] != '\0') {
        destino[i] = tolower((unsigned char)origem[i]);
        i++;
    }
    destino[i] = '\0';
}

// Função para busca case-insensitive (sem distinção entre maiúsculas/minúsculas)
// Parâmetros:
// - texto: string onde será feita a busca
// - palavra: palavra a ser procurada
// Retorna:
// - Posição da primeira ocorrência (índice baseado em 0)
// - -1 se a palavra não for encontrada
int procurarCaseInsensitive(const char* texto, const char* palavra) {
    if (texto == NULL || palavra == NULL) {
        return -1;
    }
    
    size_t len_texto = strlen(texto);
    size_t len_palavra = strlen(palavra);
    
    // Aloca memória para versões em minúscula
    char* texto_lower = malloc(len_texto + 1);
    char* palavra_lower = malloc(len_palavra + 1);
    
    if (texto_lower == NULL || palavra_lower == NULL) {
        free(texto_lower);
        free(palavra_lower);
        return -1;
    }
    
    // Converte para minúsculas
    paraMinuscula(texto_lower, texto);
    paraMinuscula(palavra_lower, palavra);
    
    // Busca usando strstr
    char* resultado = strstr(texto_lower, palavra_lower);
    int posicao = -1;
    
    if (resultado != NULL) {
        posicao = resultado - texto_lower;
    }
    
    // Libera memória
    free(texto_lower);
    free(palavra_lower);
    
    return posicao;
}

// Função para contar quantas vezes uma palavra aparece no texto
// Parâmetros:
// - texto: string onde será feita a busca
// - palavra: palavra a ser contada
// Retorna:
// - Número de ocorrências da palavra no texto
int contarOcorrencias(const char* texto, const char* palavra) {
    if (texto == NULL || palavra == NULL) {
        return 0;
    }
    
    int contador = 0;
    size_t len_palavra = strlen(palavra);
    const char* ptr = texto;
    
    // Busca sucessivas ocorrências
    while ((ptr = strstr(ptr, palavra)) != NULL) {
        contador++;
        ptr += len_palavra; // Move o ponteiro para além da palavra encontrada
    }
    
    return contador;
}

// Função para verificar se uma palavra está presente como palavra completa
// (não como parte de outra palavra)
// Parâmetros:
// - texto: string onde será feita a busca
// - palavra: palavra a ser procurada
// Retorna:
// - 1 se a palavra foi encontrada como palavra completa
// - 0 se não foi encontrada ou está dentro de outra palavra
int procurarPalavraCompleta(const char* texto, const char* palavra) {
    if (texto == NULL || palavra == NULL) {
        return 0;
    }
    
    size_t len_palavra = strlen(palavra);
    const char* ptr = texto;
    
    // Busca todas as ocorrências da substring
    while ((ptr = strstr(ptr, palavra)) != NULL) {
        // Verifica se é o início do texto ou se o caractere anterior não é alfanumérico
        int inicio_valido = (ptr == texto) || !isalnum((unsigned char)*(ptr - 1));
        
        // Verifica se é o fim do texto ou se o caractere seguinte não é alfanumérico
        int fim_valido = (*(ptr + len_palavra) == '\0') || !isalnum((unsigned char)*(ptr + len_palavra));
        
        if (inicio_valido && fim_valido) {
            return 1; // Encontrou como palavra completa
        }
        
        ptr += 1; // Move para a próxima posição
    }
    
    return 0; // Não encontrou como palavra completa
}

// Função de demonstração das operações
void demonstrarBuscas() {
    printf("=== DEMONSTRAÇÃO DE BUSCAS COM STRING.H ===\n\n");
    
    const char* texto = "Programacao em C e uma linguagem de programacao poderosa. "
                       "A programacao estruturada facilita o desenvolvimento.";
    
    printf("Texto de exemplo:\n\"%s\"\n\n", texto);
    
    // 1. Busca simples de substring
    printf("1. BUSCA SIMPLES DE SUBSTRING:\n");
    const char* palavra1 = "programacao";
    char* resultado1 = procurarSubstring(texto, palavra1);
    
    if (resultado1 != NULL) {
        printf("   Palavra \"%s\" encontrada na posição: %ld\n", palavra1, resultado1 - texto);
        printf("   Contexto: \"%.20s...\"\n", resultado1);
    } else {
        printf("   Palavra \"%s\" não encontrada\n", palavra1);
    }
    
    // 2. Busca de caractere
    printf("\n2. BUSCA DE CARACTERE:\n");
    char caractere = 'C';
    char* resultado2 = procurarCaractere(texto, caractere);
    
    if (resultado2 != NULL) {
        printf("   Caractere '%c' encontrado na posição: %ld\n", caractere, resultado2 - texto);
    } else {
        printf("   Caractere '%c' não encontrado\n", caractere);
    }
    
    // 3. Busca case-insensitive
    printf("\n3. BUSCA CASE-INSENSITIVE:\n");
    const char* palavra2 = "LINGUAGEM";
    int posicao = procurarCaseInsensitive(texto, palavra2);
    
    if (posicao != -1) {
        printf("   Palavra \"%s\" encontrada na posição: %d (ignorando maiúsculas/minúsculas)\n", 
               palavra2, posicao);
    } else {
        printf("   Palavra \"%s\" não encontrada\n", palavra2);
    }
    
    // 4. Contagem de ocorrências
    printf("\n4. CONTAGEM DE OCORRÊNCIAS:\n");
    const char* palavra3 = "programacao";
    int contador = contarOcorrencias(texto, palavra3);
    printf("   A palavra \"%s\" aparece %d vez(es) no texto\n", palavra3, contador);
    
    // 5. Busca de palavra completa
    printf("\n5. BUSCA DE PALAVRA COMPLETA:\n");
    const char* palavra4 = "em";
    int completa = procurarPalavraCompleta(texto, palavra4);
    
    if (completa) {
        printf("   Palavra \"%s\" encontrada como palavra completa\n", palavra4);
    } else {
        printf("   Palavra \"%s\" não encontrada como palavra completa\n", palavra4);
    }
    
    // Teste com palavra que aparece como parte de outra
    const char* palavra5 = "gra"; // parte de "Programacao"
    int completa2 = procurarPalavraCompleta(texto, palavra5);
    
    if (completa2) {
        printf("   Palavra \"%s\" encontrada como palavra completa\n", palavra5);
    } else {
        printf("   Palavra \"%s\" encontrada apenas como parte de outras palavras\n", palavra5);
    }
}

int main() {
    printf("=== EXEMPLOS DE BUSCA DE PALAVRAS USANDO STRING.H ===\n\n");
    
    // Demonstração principal
    demonstrarBuscas();
    
    printf("\n=== EXEMPLO INTERATIVO ===\n");
    
    // Exemplo interativo simples
    char texto_usuario[500];
    char palavra_busca[100];
    
    printf("Digite um texto (máximo 499 caracteres): ");
    if (fgets(texto_usuario, sizeof(texto_usuario), stdin) != NULL) {
        // Remove a quebra de linha se existir
        size_t len = strlen(texto_usuario);
        if (len > 0 && texto_usuario[len-1] == '\n') {
            texto_usuario[len-1] = '\0';
        }
        
        printf("Digite uma palavra para buscar: ");
        if (fgets(palavra_busca, sizeof(palavra_busca), stdin) != NULL) {
            // Remove a quebra de linha se existir
            len = strlen(palavra_busca);
            if (len > 0 && palavra_busca[len-1] == '\n') {
                palavra_busca[len-1] = '\0';
            }
            
            // Busca simples
            char* resultado = procurarSubstring(texto_usuario, palavra_busca);
            if (resultado != NULL) {
                printf("\n✅ Palavra \"%s\" encontrada na posição %ld\n", 
                       palavra_busca, resultado - texto_usuario);
            } else {
                printf("\n❌ Palavra \"%s\" não encontrada\n", palavra_busca);
            }
            
            // Contagem
            int contador = contarOcorrencias(texto_usuario, palavra_busca);
            printf("📊 Total de ocorrências: %d\n", contador);
            
            // Busca como palavra completa
            int completa = procurarPalavraCompleta(texto_usuario, palavra_busca);
            if (completa) {
                printf("🎯 Encontrada como palavra completa\n");
            } else {
                printf("⚠️  Não encontrada como palavra completa (pode estar dentro de outras palavras)\n");
            }
        }
    }
    
    printf("\n=== CONCEITOS IMPORTANTES ===\n");
    printf("1. strstr() - Busca substring em string\n");
    printf("2. strchr() - Busca caractere em string\n");
    printf("3. Busca case-insensitive requer conversão manual\n");
    printf("4. Múltiplas ocorrências podem ser encontradas iterando\n");
    printf("5. Verificação de palavra completa requer análise de contexto\n");
    
    return 0;
}