#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * Programa de exemplo para busca de palavras em strings SEM usar funções da string.h
 * 
 * Este arquivo demonstra como implementar funções de busca de strings
 * sem utilizar as funções padrão da biblioteca string.h do C.
 * Todas as operações são implementadas manualmente para fins educacionais.
 * 
 * Operações implementadas:
 * 1. Cálculo manual do comprimento de string
 * 2. Busca manual de substring
 * 3. Busca manual de caractere
 * 4. Comparação case-insensitive manual
 * 5. Contagem manual de ocorrências
 */

// Função para calcular o comprimento de uma string (equivalente a strlen)
// Parâmetros:
// - str: string para calcular o comprimento
// Retorna:
// - Número de caracteres na string (sem contar o '\0')
int meuStrlen(const char* str) {
    if (str == NULL) {
        return 0;
    }
    
    int comprimento = 0;
    while (str[comprimento] != '\0') {
        comprimento++;
    }
    return comprimento;
}

// Função para comparar duas strings (equivalente a strcmp)
// Parâmetros:
// - str1: primeira string
// - str2: segunda string
// Retorna:
// - 0 se as strings são iguais
// - valor negativo se str1 < str2
// - valor positivo se str1 > str2
int meuStrcmp(const char* str1, const char* str2) {
    if (str1 == NULL || str2 == NULL) {
        return (str1 == str2) ? 0 : (str1 == NULL ? -1 : 1);
    }
    
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        i++;
    }
    
    // Uma das strings terminou
    return str1[i] - str2[i];
}

// Função para copiar uma string (equivalente a strcpy)
// Parâmetros:
// - destino: string de destino
// - origem: string de origem
void meuStrcpy(char* destino, const char* origem) {
    if (destino == NULL || origem == NULL) {
        return;
    }
    
    int i = 0;
    while (origem[i] != '\0') {
        destino[i] = origem[i];
        i++;
    }
    destino[i] = '\0';
}

// Função para converter caractere para minúscula
// Parâmetros:
// - c: caractere a ser convertido
// Retorna:
// - Caractere em minúscula
char paraMinuscula(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }
    return c;
}

// Função para verificar se um caractere é alfanumérico
// Parâmetros:
// - c: caractere a ser verificado
// Retorna:
// - 1 se é alfanumérico, 0 caso contrário
int ehAlfanumerico(char c) {
    return (c >= 'a' && c <= 'z') || 
           (c >= 'A' && c <= 'Z') || 
           (c >= '0' && c <= '9');
}

// Função para buscar uma substring em uma string (equivalente a strstr)
// Parâmetros:
// - texto: string onde será feita a busca
// - palavra: substring a ser procurada
// Retorna:
// - Ponteiro para a primeira ocorrência da palavra no texto
// - NULL se a palavra não for encontrada
char* procurarSubstringManual(const char* texto, const char* palavra) {
    if (texto == NULL || palavra == NULL) {
        return NULL;
    }
    
    int len_texto = meuStrlen(texto);
    int len_palavra = meuStrlen(palavra);
    
    // Palavra vazia sempre é encontrada no início
    if (len_palavra == 0) {
        return (char*)texto;
    }
    
    // Se a palavra é maior que o texto, não pode ser encontrada
    if (len_palavra > len_texto) {
        return NULL;
    }
    
    // Busca a palavra no texto
    for (int i = 0; i <= len_texto - len_palavra; i++) {
        int encontrou = 1;
        
        // Compara caractere por caractere
        for (int j = 0; j < len_palavra; j++) {
            if (texto[i + j] != palavra[j]) {
                encontrou = 0;
                break;
            }
        }
        
        if (encontrou) {
            return (char*)(texto + i);
        }
    }
    
    return NULL; // Não encontrada
}

// Função para buscar um caractere em uma string (equivalente a strchr)
// Parâmetros:
// - texto: string onde será feita a busca
// - caractere: caractere a ser procurado
// Retorna:
// - Ponteiro para a primeira ocorrência do caractere no texto
// - NULL se o caractere não for encontrado
char* procurarCaractereManual(const char* texto, char caractere) {
    if (texto == NULL) {
        return NULL;
    }
    
    int i = 0;
    while (texto[i] != '\0') {
        if (texto[i] == caractere) {
            return (char*)(texto + i);
        }
        i++;
    }
    
    return NULL; // Não encontrado
}

// Função para busca case-insensitive (sem distinção entre maiúsculas/minúsculas)
// Parâmetros:
// - texto: string onde será feita a busca
// - palavra: palavra a ser procurada
// Retorna:
// - Posição da primeira ocorrência (índice baseado em 0)
// - -1 se a palavra não for encontrada
int procurarCaseInsensitiveManual(const char* texto, const char* palavra) {
    if (texto == NULL || palavra == NULL) {
        return -1;
    }
    
    int len_texto = meuStrlen(texto);
    int len_palavra = meuStrlen(palavra);
    
    // Palavra vazia sempre é encontrada no início
    if (len_palavra == 0) {
        return 0;
    }
    
    // Se a palavra é maior que o texto, não pode ser encontrada
    if (len_palavra > len_texto) {
        return -1;
    }
    
    // Busca a palavra no texto
    for (int i = 0; i <= len_texto - len_palavra; i++) {
        int encontrou = 1;
        
        // Compara caractere por caractere (case-insensitive)
        for (int j = 0; j < len_palavra; j++) {
            if (paraMinuscula(texto[i + j]) != paraMinuscula(palavra[j])) {
                encontrou = 0;
                break;
            }
        }
        
        if (encontrou) {
            return i;
        }
    }
    
    return -1; // Não encontrada
}

// Função para contar quantas vezes uma palavra aparece no texto
// Parâmetros:
// - texto: string onde será feita a busca
// - palavra: palavra a ser contada
// Retorna:
// - Número de ocorrências da palavra no texto
int contarOcorrenciasManual(const char* texto, const char* palavra) {
    if (texto == NULL || palavra == NULL) {
        return 0;
    }
    
    int contador = 0;
    int len_palavra = meuStrlen(palavra);
    const char* ptr = texto;
    
    // Busca sucessivas ocorrências
    while ((ptr = procurarSubstringManual(ptr, palavra)) != NULL) {
        contador++;
        ptr += len_palavra; // Move o ponteiro para além da palavra encontrada
    }
    
    return contador;
}

// Função para verificar se uma palavra está presente como palavra completa
// Parâmetros:
// - texto: string onde será feita a busca
// - palavra: palavra a ser procurada
// Retorna:
// - 1 se a palavra foi encontrada como palavra completa
// - 0 se não foi encontrada ou está dentro de outra palavra
int procurarPalavraCompletaManual(const char* texto, const char* palavra) {
    if (texto == NULL || palavra == NULL) {
        return 0;
    }
    
    int len_palavra = meuStrlen(palavra);
    const char* ptr = texto;
    
    // Busca todas as ocorrências da substring
    while ((ptr = procurarSubstringManual(ptr, palavra)) != NULL) {
        // Verifica se é o início do texto ou se o caractere anterior não é alfanumérico
        int inicio_valido = (ptr == texto) || !ehAlfanumerico(*(ptr - 1));
        
        // Verifica se é o fim do texto ou se o caractere seguinte não é alfanumérico
        int fim_valido = (*(ptr + len_palavra) == '\0') || !ehAlfanumerico(*(ptr + len_palavra));
        
        if (inicio_valido && fim_valido) {
            return 1; // Encontrou como palavra completa
        }
        
        ptr += 1; // Move para a próxima posição
    }
    
    return 0; // Não encontrou como palavra completa
}

// Função para buscar a última ocorrência de um caractere (equivalente a strrchr)
// Parâmetros:
// - texto: string onde será feita a busca
// - caractere: caractere a ser procurado
// Retorna:
// - Ponteiro para a última ocorrência do caractere no texto
// - NULL se o caractere não for encontrado
char* procurarUltimoCaractere(const char* texto, char caractere) {
    if (texto == NULL) {
        return NULL;
    }
    
    char* ultima_ocorrencia = NULL;
    int i = 0;
    
    while (texto[i] != '\0') {
        if (texto[i] == caractere) {
            ultima_ocorrencia = (char*)(texto + i);
        }
        i++;
    }
    
    return ultima_ocorrencia;
}

// Função de demonstração das operações manuais
void demonstrarBuscasManual() {
    printf("=== DEMONSTRAÇÃO DE BUSCAS SEM STRING.H ===\n\n");
    
    const char* texto = "Programacao em C e uma linguagem de programacao poderosa. "
                       "A programacao estruturada facilita o desenvolvimento.";
    
    printf("Texto de exemplo:\n\"%s\"\n\n", texto);
    
    // 1. Busca simples de substring
    printf("1. BUSCA MANUAL DE SUBSTRING:\n");
    const char* palavra1 = "programacao";
    char* resultado1 = procurarSubstringManual(texto, palavra1);
    
    if (resultado1 != NULL) {
        printf("   Palavra \"%s\" encontrada na posição: %ld\n", palavra1, resultado1 - texto);
        printf("   Contexto: \"%.20s...\"\n", resultado1);
    } else {
        printf("   Palavra \"%s\" não encontrada\n", palavra1);
    }
    
    // 2. Busca de caractere
    printf("\n2. BUSCA MANUAL DE CARACTERE:\n");
    char caractere = 'C';
    char* resultado2 = procurarCaractereManual(texto, caractere);
    
    if (resultado2 != NULL) {
        printf("   Caractere '%c' encontrado na posição: %ld\n", caractere, resultado2 - texto);
    } else {
        printf("   Caractere '%c' não encontrado\n", caractere);
    }
    
    // 3. Busca case-insensitive
    printf("\n3. BUSCA MANUAL CASE-INSENSITIVE:\n");
    const char* palavra2 = "LINGUAGEM";
    int posicao = procurarCaseInsensitiveManual(texto, palavra2);
    
    if (posicao != -1) {
        printf("   Palavra \"%s\" encontrada na posição: %d (ignorando maiúsculas/minúsculas)\n", 
               palavra2, posicao);
    } else {
        printf("   Palavra \"%s\" não encontrada\n", palavra2);
    }
    
    // 4. Contagem de ocorrências
    printf("\n4. CONTAGEM MANUAL DE OCORRÊNCIAS:\n");
    const char* palavra3 = "programacao";
    int contador = contarOcorrenciasManual(texto, palavra3);
    printf("   A palavra \"%s\" aparece %d vez(es) no texto\n", palavra3, contador);
    
    // 5. Busca de palavra completa
    printf("\n5. BUSCA MANUAL DE PALAVRA COMPLETA:\n");
    const char* palavra4 = "em";
    int completa = procurarPalavraCompletaManual(texto, palavra4);
    
    if (completa) {
        printf("   Palavra \"%s\" encontrada como palavra completa\n", palavra4);
    } else {
        printf("   Palavra \"%s\" não encontrada como palavra completa\n", palavra4);
    }
    
    // 6. Busca da última ocorrência
    printf("\n6. BUSCA DA ÚLTIMA OCORRÊNCIA:\n");
    char* ultima = procurarUltimoCaractere(texto, 'a');
    if (ultima != NULL) {
        printf("   Última ocorrência de 'a' na posição: %ld\n", ultima - texto);
    } else {
        printf("   Caractere 'a' não encontrado\n");
    }
    
    // 7. Demonstração das funções auxiliares
    printf("\n7. FUNÇÕES AUXILIARES IMPLEMENTADAS:\n");
    printf("   Comprimento do texto: %d caracteres\n", meuStrlen(texto));
    
    const char* teste1 = "teste";
    const char* teste2 = "TESTE";
    printf("   Comparação \"%s\" vs \"%s\": %d\n", teste1, teste2, meuStrcmp(teste1, teste2));
}

int main() {
    printf("=== EXEMPLOS DE BUSCA DE PALAVRAS SEM STRING.H ===\n\n");
    
    // Demonstração principal
    demonstrarBuscasManual();
    
    printf("\n=== EXEMPLO INTERATIVO ===\n");
    
    // Exemplo interativo simples
    char texto_usuario[500];
    char palavra_busca[100];
    
    printf("Digite um texto (máximo 499 caracteres): ");
    if (fgets(texto_usuario, sizeof(texto_usuario), stdin) != NULL) {
        // Remove a quebra de linha se existir
        int len = meuStrlen(texto_usuario);
        if (len > 0 && texto_usuario[len-1] == '\n') {
            texto_usuario[len-1] = '\0';
        }
        
        printf("Digite uma palavra para buscar: ");
        if (fgets(palavra_busca, sizeof(palavra_busca), stdin) != NULL) {
            // Remove a quebra de linha se existir
            len = meuStrlen(palavra_busca);
            if (len > 0 && palavra_busca[len-1] == '\n') {
                palavra_busca[len-1] = '\0';
            }
            
            printf("\n=== RESULTADOS DA BUSCA MANUAL ===\n");
            
            // Busca simples
            char* resultado = procurarSubstringManual(texto_usuario, palavra_busca);
            if (resultado != NULL) {
                printf("✅ Palavra \"%s\" encontrada na posição %ld\n", 
                       palavra_busca, resultado - texto_usuario);
            } else {
                printf("❌ Palavra \"%s\" não encontrada\n", palavra_busca);
            }
            
            // Busca case-insensitive
            int posicao_ci = procurarCaseInsensitiveManual(texto_usuario, palavra_busca);
            if (posicao_ci != -1) {
                printf("🔍 Busca case-insensitive: encontrada na posição %d\n", posicao_ci);
            } else {
                printf("🔍 Busca case-insensitive: não encontrada\n");
            }
            
            // Contagem
            int contador = contarOcorrenciasManual(texto_usuario, palavra_busca);
            printf("📊 Total de ocorrências: %d\n", contador);
            
            // Busca como palavra completa
            int completa = procurarPalavraCompletaManual(texto_usuario, palavra_busca);
            if (completa) {
                printf("🎯 Encontrada como palavra completa\n");
            } else {
                printf("⚠️  Não encontrada como palavra completa\n");
            }
        }
    }
    
    printf("\n=== CONCEITOS IMPORTANTES ===\n");
    printf("1. Implementação manual de strlen(), strcmp(), strcpy()\n");
    printf("2. Algoritmo de busca de substring O(n*m) - força bruta\n");
    printf("3. Manipulação direta de ponteiros e índices\n");
    printf("4. Verificação manual de limites e casos especiais\n");
    printf("5. Conversão manual de maiúsculas/minúsculas\n");
    printf("6. Importância das funções da biblioteca padrão para eficiência\n");
    
    return 0;
}