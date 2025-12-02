/**
 * ============================================================================
 * TABELA LCP (LONGEST COMMON PREFIX)
 * ============================================================================
 * 
 * Este arquivo implementa a Tabela LCP, uma estrutura complementar ao 
 * Suffix Array que armazena o tamanho do prefixo comum mais longo entre
 * sufixos adjacentes.
 * 
 * A combinação Suffix Array + LCP Array permite:
 * - Encontrar a substring repetida mais longa em O(n)
 * - Contar substrings distintas em O(n)
 * - Busca de padrões mais eficiente
 * - Comparação de strings mais rápida
 * 
 * Algoritmo implementado: Kasai et al. O(n)
 * 
 * Pré-requisito: Suffix Array (07-suffix-array)
 * 
 * Autor: Estrutura de Dados em C
 * ============================================================================
 */

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ==================== ESTRUTURAS ====================

typedef struct {
    int *suffix_array;  // Array de sufixos ordenados
    int *lcp_array;     // Array de LCP
    int *rank_array;    // Posição de cada sufixo no SA
    char *text;
    int length;
} SuffixLCP;

// ==================== CONSTRUÇÃO DO SUFFIX ARRAY ====================

/**
 * Construção simples do Suffix Array (para clareza)
 */
void build_suffix_array(SuffixLCP *slcp) {
    int n = slcp->length;
    
    // Array de índices e ponteiros para sufixos
    int *indices = (int *)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        indices[i] = i;
    }
    
    // Bubble sort simples (para demonstração)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(slcp->text + indices[j], slcp->text + indices[j + 1]) > 0) {
                int temp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = temp;
            }
        }
    }
    
    // Copiar para suffix_array
    for (int i = 0; i < n; i++) {
        slcp->suffix_array[i] = indices[i];
    }
    
    // Construir rank_array (inverso do suffix_array)
    for (int i = 0; i < n; i++) {
        slcp->rank_array[slcp->suffix_array[i]] = i;
    }
    
    free(indices);
}

// ==================== ALGORITMO DE KASAI ====================

/**
 * Construção do LCP Array usando algoritmo de Kasai
 * Complexidade: O(n)
 * 
 * Ideia principal: Se LCP[i] = k, então LCP[i+1] >= k-1
 * Isso permite calcular todos os LCPs em tempo linear
 */
void build_lcp_kasai(SuffixLCP *slcp) {
    int n = slcp->length;
    int k = 0;
    
    slcp->lcp_array[0] = 0;  // Primeiro elemento não tem predecessor
    
    for (int i = 0; i < n; i++) {
        // Posição do sufixo i no suffix array
        int pos = slcp->rank_array[i];
        
        // Primeiro sufixo não tem LCP
        if (pos == 0) {
            k = 0;
            continue;
        }
        
        // Sufixo anterior no suffix array
        int j = slcp->suffix_array[pos - 1];
        
        // Calcular LCP comparando caracteres
        while (i + k < n && j + k < n && 
               slcp->text[i + k] == slcp->text[j + k]) {
            k++;
        }
        
        slcp->lcp_array[pos] = k;
        
        // Decrementar k para próxima iteração
        if (k > 0) k--;
    }
}

// ==================== CRIAÇÃO E DESTRUIÇÃO ====================

SuffixLCP* suffix_lcp_create(const char *text) {
    int n = strlen(text);
    
    SuffixLCP *slcp = (SuffixLCP *)malloc(sizeof(SuffixLCP));
    slcp->text = strdup(text);
    slcp->length = n;
    slcp->suffix_array = (int *)malloc(n * sizeof(int));
    slcp->lcp_array = (int *)malloc(n * sizeof(int));
    slcp->rank_array = (int *)malloc(n * sizeof(int));
    
    build_suffix_array(slcp);
    build_lcp_kasai(slcp);
    
    return slcp;
}

void suffix_lcp_free(SuffixLCP *slcp) {
    free(slcp->suffix_array);
    free(slcp->lcp_array);
    free(slcp->rank_array);
    free(slcp->text);
    free(slcp);
}

// ==================== OPERAÇÕES COM LCP ====================

/**
 * Encontrar a substring repetida mais longa
 * O LCP máximo indica onde ela está
 */
int longest_repeated_substring(SuffixLCP *slcp, int *start_pos) {
    int max_lcp = 0;
    int max_idx = 0;
    
    for (int i = 1; i < slcp->length; i++) {
        if (slcp->lcp_array[i] > max_lcp) {
            max_lcp = slcp->lcp_array[i];
            max_idx = i;
        }
    }
    
    if (max_lcp > 0) {
        *start_pos = slcp->suffix_array[max_idx];
    } else {
        *start_pos = -1;
    }
    
    return max_lcp;
}

/**
 * Contar número de substrings distintas
 * 
 * Total de substrings = n*(n+1)/2
 * Substrings duplicadas = soma de todos os LCP
 * Substrings distintas = Total - Duplicadas
 */
long count_distinct_substrings(SuffixLCP *slcp) {
    int n = slcp->length;
    
    // Total de substrings possíveis
    long total = (long)n * (n + 1) / 2;
    
    // Subtrair duplicadas (soma dos LCPs)
    long duplicates = 0;
    for (int i = 1; i < n; i++) {
        duplicates += slcp->lcp_array[i];
    }
    
    return total - duplicates;
}

/**
 * Encontrar todas as ocorrências de um padrão
 * Usando LCP para otimizar comparações
 */
int* search_pattern(SuffixLCP *slcp, const char *pattern, int *count) {
    int n = slcp->length;
    int m = strlen(pattern);
    
    // Busca binária para primeira ocorrência
    int left = 0, right = n - 1;
    int first = -1;
    
    while (left <= right) {
        int mid = (left + right) / 2;
        int cmp = strncmp(slcp->text + slcp->suffix_array[mid], pattern, m);
        
        if (cmp >= 0) {
            if (cmp == 0) first = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    if (first == -1) {
        *count = 0;
        return NULL;
    }
    
    // Busca binária para última ocorrência
    left = first;
    right = n - 1;
    int last = first;
    
    while (left <= right) {
        int mid = (left + right) / 2;
        int cmp = strncmp(slcp->text + slcp->suffix_array[mid], pattern, m);
        
        if (cmp <= 0) {
            if (cmp == 0) last = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    *count = last - first + 1;
    int *result = (int *)malloc((*count) * sizeof(int));
    
    for (int i = 0; i < *count; i++) {
        result[i] = slcp->suffix_array[first + i];
    }
    
    return result;
}

/**
 * LCP de dois sufixos quaisquer usando RMQ
 * (implementação simplificada sem RMQ pré-processado)
 */
int lcp_of_suffixes(SuffixLCP *slcp, int i, int j) {
    if (i == j) return slcp->length - i;
    
    int rank_i = slcp->rank_array[i];
    int rank_j = slcp->rank_array[j];
    
    if (rank_i > rank_j) {
        int temp = rank_i;
        rank_i = rank_j;
        rank_j = temp;
    }
    
    // Mínimo dos LCPs no intervalo [rank_i+1, rank_j]
    int min_lcp = slcp->length;
    for (int k = rank_i + 1; k <= rank_j; k++) {
        if (slcp->lcp_array[k] < min_lcp) {
            min_lcp = slcp->lcp_array[k];
        }
    }
    
    return min_lcp;
}

// ==================== VISUALIZAÇÃO ====================

void print_suffix_lcp(SuffixLCP *slcp) {
    printf("Texto: \"%s\" (tamanho: %d)\n\n", slcp->text, slcp->length);
    
    printf("┌───────┬───────┬───────┬────────────────────────────────┐\n");
    printf("│ Rank  │ SA[i] │ LCP   │ Sufixo                         │\n");
    printf("├───────┼───────┼───────┼────────────────────────────────┤\n");
    
    for (int i = 0; i < slcp->length; i++) {
        printf("│ %5d │ %5d │ %5d │ %-30s │\n",
               i, 
               slcp->suffix_array[i], 
               slcp->lcp_array[i],
               slcp->text + slcp->suffix_array[i]);
    }
    printf("└───────┴───────┴───────┴────────────────────────────────┘\n");
}

// ==================== TESTES ====================

void testar_construcao() {
    printf("=== CONSTRUÇÃO DO LCP ARRAY ===\n\n");
    
    const char *texto = "banana";
    SuffixLCP *slcp = suffix_lcp_create(texto);
    
    print_suffix_lcp(slcp);
    printf("\n");
    
    printf("Interpretação do LCP:\n");
    printf("- LCP[1] = 1: 'a' e 'ana' compartilham 'a'\n");
    printf("- LCP[2] = 3: 'ana' e 'anana' compartilham 'ana'\n");
    printf("- LCP[3] = 0: 'anana' e 'banana' não compartilham prefixo\n");
    printf("- LCP[4] = 0: 'banana' e 'na' não compartilham prefixo\n");
    printf("- LCP[5] = 2: 'na' e 'nana' compartilham 'na'\n");
    printf("\n");
    
    suffix_lcp_free(slcp);
}

void testar_lrs() {
    printf("=== SUBSTRING REPETIDA MAIS LONGA ===\n\n");
    
    const char *texto = "banana";
    SuffixLCP *slcp = suffix_lcp_create(texto);
    
    int pos;
    int len = longest_repeated_substring(slcp, &pos);
    
    printf("Texto: \"%s\"\n", texto);
    printf("Maior LCP: %d\n", len);
    printf("Substring repetida mais longa: \"%.*s\"\n\n", len, texto + pos);
    
    suffix_lcp_free(slcp);
    
    // Outro exemplo
    texto = "mississippi";
    slcp = suffix_lcp_create(texto);
    
    print_suffix_lcp(slcp);
    printf("\n");
    
    len = longest_repeated_substring(slcp, &pos);
    printf("Texto: \"%s\"\n", texto);
    printf("Substring repetida mais longa: \"%.*s\" (tamanho %d)\n\n", len, texto + pos, len);
    
    suffix_lcp_free(slcp);
}

void testar_contagem() {
    printf("=== CONTAGEM DE SUBSTRINGS DISTINTAS ===\n\n");
    
    const char *texto = "banana";
    SuffixLCP *slcp = suffix_lcp_create(texto);
    
    printf("Texto: \"%s\"\n", texto);
    printf("Tamanho: %d\n", slcp->length);
    printf("Total de substrings possíveis: %d * %d / 2 = %d\n", 
           slcp->length, slcp->length + 1, slcp->length * (slcp->length + 1) / 2);
    
    long distintas = count_distinct_substrings(slcp);
    printf("Substrings distintas: %ld\n\n", distintas);
    
    printf("Listando algumas substrings distintas:\n");
    printf("a, an, ana, anan, anana, b, ba, ban, bana, banan, banana, n, na, nan, nana\n\n");
    
    suffix_lcp_free(slcp);
}

void testar_lcp_pares() {
    printf("=== LCP ENTRE PARES DE SUFIXOS ===\n\n");
    
    const char *texto = "banana";
    SuffixLCP *slcp = suffix_lcp_create(texto);
    
    printf("Texto: \"%s\"\n\n", texto);
    
    // Comparar sufixos específicos
    int i = 1, j = 3;
    printf("LCP do sufixo %d (\"%s\") e sufixo %d (\"%s\"): %d\n",
           i, texto + i, j, texto + j, lcp_of_suffixes(slcp, i, j));
    
    i = 0; j = 3;
    printf("LCP do sufixo %d (\"%s\") e sufixo %d (\"%s\"): %d\n",
           i, texto + i, j, texto + j, lcp_of_suffixes(slcp, i, j));
    
    i = 2; j = 4;
    printf("LCP do sufixo %d (\"%s\") e sufixo %d (\"%s\"): %d\n",
           i, texto + i, j, texto + j, lcp_of_suffixes(slcp, i, j));
    
    printf("\n");
    suffix_lcp_free(slcp);
}

void testar_busca() {
    printf("=== BUSCA DE PADRÕES ===\n\n");
    
    const char *texto = "abracadabra";
    SuffixLCP *slcp = suffix_lcp_create(texto);
    
    print_suffix_lcp(slcp);
    printf("\n");
    
    const char *padrao = "abra";
    int count;
    int *posicoes = search_pattern(slcp, padrao, &count);
    
    printf("Padrão \"%s\" encontrado %d vez(es):\n", padrao, count);
    if (posicoes) {
        for (int i = 0; i < count; i++) {
            printf("  Posição %d\n", posicoes[i]);
        }
        free(posicoes);
    }
    printf("\n");
    
    suffix_lcp_free(slcp);
}

// ==================== FUNÇÃO PRINCIPAL ====================

int main() {
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║         TABELA LCP (LONGEST COMMON PREFIX)               ║\n");
    printf("║   Complemento essencial do Suffix Array                  ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    testar_construcao();
    testar_lrs();
    testar_contagem();
    testar_lcp_pares();
    testar_busca();
    
    printf("═══════════════════════════════════════════════════════════\n");
    printf("Complexidades (Algoritmo de Kasai):\n");
    printf("- Construção do LCP: O(n)\n");
    printf("- Substring repetida mais longa: O(n)\n");
    printf("- Contar substrings distintas: O(n)\n");
    printf("- LCP de dois sufixos: O(n) ou O(1) com RMQ\n");
    printf("\n");
    printf("Próximo: Bloom Filter (09) para consultas probabilísticas\n");
    printf("═══════════════════════════════════════════════════════════\n");
    
    return 0;
}
