/*
 * ==========================================
 * EXEMPLOS DE MANIPULAÇÃO DE STRINGS COM VETORES
 * ==========================================
 * 
 * Este arquivo demonstra como trabalhar com strings usando apenas
 * vetores (arrays) em C, sem usar a biblioteca string.h
 * 
 * Conteúdo:
 * 1. Funções básicas de string (strlen, strcpy, etc.)
 * 2. Vetores de strings
 * 3. Processamento de texto
 * 4. Exemplos práticos
 */

#include <stdio.h>
#include <stdlib.h>

// ==========================================
// FUNÇÕES BÁSICAS DE STRING (SEM string.h)
// ==========================================

/**
 * Calcula o comprimento de uma string
 * @param str: ponteiro para a string
 * @return: número de caracteres (sem contar '\0')
 */
int meu_strlen(char *str) {
    int comprimento = 0;
    while (str[comprimento] != '\0') {
        comprimento++;
    }
    return comprimento;
}

/**
 * Copia uma string para outra
 * @param destino: string de destino
 * @param origem: string de origem
 */
void meu_strcpy(char *destino, char *origem) {
    int i = 0;
    while (origem[i] != '\0') {
        destino[i] = origem[i];
        i++;
    }
    destino[i] = '\0'; // Adiciona o terminador
}

/**
 * Concatena duas strings
 * @param destino: string que receberá a concatenação
 * @param origem: string a ser adicionada
 */
void meu_strcat(char *destino, char *origem) {
    int i = 0, j = 0;
    
    // Encontra o final da string de destino
    while (destino[i] != '\0') {
        i++;
    }
    
    // Adiciona a string origem ao final
    while (origem[j] != '\0') {
        destino[i] = origem[j];
        i++;
        j++;
    }
    destino[i] = '\0'; // Adiciona o terminador
}

/**
 * Compara duas strings
 * @param str1: primeira string
 * @param str2: segunda string
 * @return: 0 se iguais, negativo se str1 < str2, positivo se str1 > str2
 */
int meu_strcmp(char *str1, char *str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        i++;
    }
    return str1[i] - str2[i]; // Tratamento para strings de tamanhos diferentes
}

/**
 * Busca um caractere em uma string
 * @param str: string onde buscar
 * @param c: caractere a ser buscado
 * @return: ponteiro para a primeira ocorrência ou NULL se não encontrado
 */
char* meu_strchr(char *str, char c) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c) {
            return &str[i];
        }
    }
    return NULL; // Não encontrado
}

// ==========================================
// FUNÇÕES AVANÇADAS DE PROCESSAMENTO
// ==========================================

/**
 * Converte string para maiúsculas
 * @param str: string a ser convertida
 */
void para_maiuscula(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 'a' + 'A';
        }
    }
}

/**
 * Converte string para minúsculas
 * @param str: string a ser convertida
 */
void para_minuscula(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] - 'A' + 'a';
        }
    }
}

/**
 * Inverte uma string
 * @param str: string a ser invertida
 */
void inverter_string(char *str) {
    int comprimento = meu_strlen(str);
    for (int i = 0; i < comprimento / 2; i++) {
        char temp = str[i];
        str[i] = str[comprimento - 1 - i];
        str[comprimento - 1 - i] = temp;
    }
}

/**
 * Conta o número de palavras em uma string
 * @param str: string a ser analisada
 * @return: número de palavras
 */
int contar_palavras(char *str) {
    int palavras = 0;
    int em_palavra = 0;
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n') {
            if (!em_palavra) {
                palavras++;
                em_palavra = 1;
            }
        } else {
            em_palavra = 0;
        }
    }
    
    return palavras;
}

/**
 * Remove espaços no início e fim da string
 * @param str: string a ser processada
 */
void trim_string(char *str) {
    int inicio = 0, fim = meu_strlen(str) - 1;
    
    // Remove espaços do início
    while (str[inicio] == ' ' || str[inicio] == '\t' || str[inicio] == '\n') {
        inicio++;
    }
    
    // Remove espaços do fim
    while (fim >= inicio && (str[fim] == ' ' || str[fim] == '\t' || str[fim] == '\n')) {
        fim--;
    }
    
    // Move a string limpa para o início
    int j = 0;
    for (int i = inicio; i <= fim; i++) {
        str[j++] = str[i];
    }
    str[j] = '\0';
}

// ==========================================
// FUNÇÕES PARA VETORES DE STRINGS
// ==========================================

/**
 * Exibe um vetor de strings
 * @param strings: vetor de strings
 * @param quantidade: número de strings no vetor
 */
void exibir_strings(char strings[][50], int quantidade) {
    printf("\n=== LISTA DE STRINGS ===\n");
    for (int i = 0; i < quantidade; i++) {
        printf("%d: %s\n", i + 1, strings[i]);
    }
    printf("\n");
}

/**
 * Ordena um vetor de strings (ordenação por bolha)
 * @param strings: vetor de strings
 * @param quantidade: número de strings no vetor
 */
void ordenar_strings(char strings[][50], int quantidade) {
    for (int i = 0; i < quantidade - 1; i++) {
        for (int j = 0; j < quantidade - 1 - i; j++) {
            if (meu_strcmp(strings[j], strings[j + 1]) > 0) {
                // Troca as strings
                char temp[50];
                meu_strcpy(temp, strings[j]);
                meu_strcpy(strings[j], strings[j + 1]);
                meu_strcpy(strings[j + 1], temp);
            }
        }
    }
}

/**
 * Busca uma string em um vetor de strings
 * @param strings: vetor de strings
 * @param quantidade: número de strings no vetor
 * @param busca: string a ser buscada
 * @return: índice da string encontrada ou -1 se não encontrada
 */
int buscar_string(char strings[][50], int quantidade, char *busca) {
    for (int i = 0; i < quantidade; i++) {
        if (meu_strcmp(strings[i], busca) == 0) {
            return i;
        }
    }
    return -1; // Não encontrada
}

// ==========================================
// EXEMPLOS PRÁTICOS
// ==========================================

/**
 * Demonstra operações básicas com strings
 */
void exemplo_operacoes_basicas() {
    printf("\n=== OPERAÇÕES BÁSICAS COM STRINGS ===\n");
    
    char str1[100] = "Programacao";
    char str2[100] = " em C";
    char str3[100];
    
    printf("String 1: '%s'\n", str1);
    printf("String 2: '%s'\n", str2);
    
    // Comprimento
    printf("Comprimento de str1: %d\n", meu_strlen(str1));
    
    // Cópia
    meu_strcpy(str3, str1);
    printf("Cópia de str1 em str3: '%s'\n", str3);
    
    // Concatenação
    meu_strcat(str1, str2);
    printf("str1 após concatenação: '%s'\n", str1);
    
    // Comparação
    int cmp = meu_strcmp(str3, "Programacao");
    printf("Comparação de str3 com 'Programacao': %d\n", cmp);
    
    // Busca de caractere
    char *pos = meu_strchr(str1, 'C');
    if (pos != NULL) {
        printf("Caractere 'C' encontrado na posição: %ld\n", pos - str1);
    }
}

/**
 * Demonstra processamento avançado de texto
 */
void exemplo_processamento_texto() {
    printf("\n=== PROCESSAMENTO AVANÇADO DE TEXTO ===\n");
    
    char texto[100] = "  Linguagem C e Vetores  ";
    char copia[100];
    
    meu_strcpy(copia, texto);
    
    printf("Texto original: '%s'\n", texto);
    printf("Número de palavras: %d\n", contar_palavras(texto));
    
    // Trim
    trim_string(texto);
    printf("Após trim: '%s'\n", texto);
    
    // Maiúsculas
    meu_strcpy(copia, texto);
    para_maiuscula(copia);
    printf("Em maiúsculas: '%s'\n", copia);
    
    // Minúsculas
    meu_strcpy(copia, texto);
    para_minuscula(copia);
    printf("Em minúsculas: '%s'\n", copia);
    
    // Inversão
    meu_strcpy(copia, texto);
    inverter_string(copia);
    printf("Invertida: '%s'\n", copia);
}

/**
 * Demonstra manipulação de vetores de strings
 */
void exemplo_vetor_strings() {
    printf("\n=== MANIPULAÇÃO DE VETORES DE STRINGS ===\n");
    
    char nomes[5][50] = {
        "Maria",
        "João",
        "Ana",
        "Carlos",
        "Bruno"
    };
    
    printf("Lista original de nomes:\n");
    exibir_strings(nomes, 5);
    
    // Busca
    char busca[] = "Ana";
    int posicao = buscar_string(nomes, 5, busca);
    if (posicao != -1) {
        printf("'%s' encontrado na posição %d\n", busca, posicao);
    }
    
    // Ordenação
    printf("Após ordenação:\n");
    ordenar_strings(nomes, 5);
    exibir_strings(nomes, 5);
}

/**
 * Sistema simples de cadastro de palavras
 */
void sistema_cadastro_palavras() {
    printf("\n=== SISTEMA DE CADASTRO DE PALAVRAS ===\n");
    
    char palavras[10][50];
    int total = 0;
    char entrada[50];
    
    printf("Digite palavras (digite 'fim' para encerrar):\n");
    
    while (total < 10) {
        printf("Palavra %d: ", total + 1);
        scanf("%s", entrada);
        
        if (meu_strcmp(entrada, "fim") == 0) {
            break;
        }
        
        meu_strcpy(palavras[total], entrada);
        total++;
    }
    
    if (total > 0) {
        printf("\nPalavras cadastradas:\n");
        exibir_strings(palavras, total);
        
        printf("Ordenando palavras...\n");
        ordenar_strings(palavras, total);
        exibir_strings(palavras, total);
        
        // Estatísticas
        int total_chars = 0;
        for (int i = 0; i < total; i++) {
            total_chars += meu_strlen(palavras[i]);
        }
        printf("Estatísticas:\n");
        printf("- Total de palavras: %d\n", total);
        printf("- Total de caracteres: %d\n", total_chars);
        printf("- Média de caracteres por palavra: %.2f\n", 
               total > 0 ? (float)total_chars / total : 0);
    }
}

// ==========================================
// FUNÇÃO PRINCIPAL
// ==========================================

int main() {
    printf("==============================================\n");
    printf("  DEMONSTRAÇÃO: STRINGS COM VETORES EM C\n");
    printf("==============================================\n");
    
    // Exemplos das funcionalidades
    exemplo_operacoes_basicas();
    exemplo_processamento_texto();
    exemplo_vetor_strings();
    
    // Sistema interativo
    char opcao;
    printf("\nDeseja testar o sistema de cadastro? (s/n): ");
    scanf(" %c", &opcao);
    
    if (opcao == 's' || opcao == 'S') {
        sistema_cadastro_palavras();
    }
    
    printf("\n=== CONCEITOS IMPORTANTES ===\n");
    printf("1. Strings são vetores de char terminados com '\\0'\n");
    printf("2. Sempre verificar limites para evitar buffer overflow\n");
    printf("3. Gerenciar memória adequadamente\n");
    printf("4. Implementar validações de entrada\n");
    printf("5. Considerar performance em operações repetitivas\n");
    
    printf("\n=== PROGRAMA FINALIZADO ===\n");
    return 0;
}