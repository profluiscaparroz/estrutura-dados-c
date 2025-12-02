/**
 * ============================================================================
 * SUFFIX ARRAY - ARRAY DE SUFIXOS
 * ============================================================================
 * 
 * Este arquivo implementa o Suffix Array, uma estrutura de dados fundamental
 * para processamento de strings e busca de padrões.
 * 
 * O Suffix Array é uma alternativa mais eficiente em memória à Suffix Tree,
 * e é amplamente usado em:
 * - Bioinformática (alinhamento de DNA/RNA)
 * - Compressão de dados
 * - Busca de padrões em texto
 * - Detecção de plágio
 * 
 * Conceitos abordados:
 * - Construção do Suffix Array
 * - Busca binária em sufixos
 * - Aplicações práticas
 * 
 * Pré-requisito: Trie (06-trie)
 * Próximo: Tabela LCP (08-tabela-lcp)
 * 
 * Autor: Estrutura de Dados em C
 * ============================================================================
 */

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ==================== ESTRUTURA DO SUFFIX ARRAY ====================

typedef struct {
    int *suffix_array;  // Array de índices dos sufixos ordenados
    char *text;         // Texto original
    int length;         // Tamanho do texto
} SuffixArray;

// Estrutura auxiliar para ordenação
typedef struct {
    int index;
    int rank[2];
} Suffix;

// ==================== FUNÇÕES DE COMPARAÇÃO ====================

/**
 * Comparador para qsort
 */
int compare_suffix(const void *a, const void *b) {
    Suffix *s1 = (Suffix *)a;
    Suffix *s2 = (Suffix *)b;
    
    if (s1->rank[0] != s2->rank[0]) {
        return s1->rank[0] - s2->rank[0];
    }
    return s1->rank[1] - s2->rank[1];
}

// ==================== CONSTRUÇÃO DO SUFFIX ARRAY ====================

/**
 * Construção do Suffix Array usando algoritmo O(n log²n)
 * 
 * Ideia: Ordenar sufixos por prefixos de tamanho 1, 2, 4, 8, ...
 * A cada iteração, usamos a ordenação anterior para construir a nova
 */
SuffixArray* suffix_array_create(const char *text) {
    int n = strlen(text);
    
    SuffixArray *sa = (SuffixArray *)malloc(sizeof(SuffixArray));
    sa->text = strdup(text);
    sa->length = n;
    sa->suffix_array = (int *)malloc(n * sizeof(int));
    
    Suffix *suffixes = (Suffix *)malloc(n * sizeof(Suffix));
    
    // Passo 1: Ordenar por primeiro caractere
    for (int i = 0; i < n; i++) {
        suffixes[i].index = i;
        suffixes[i].rank[0] = text[i] - 'a';
        suffixes[i].rank[1] = (i + 1 < n) ? (text[i + 1] - 'a') : -1;
    }
    
    qsort(suffixes, n, sizeof(Suffix), compare_suffix);
    
    // Array de índices para ranks
    int *indices = (int *)malloc(n * sizeof(int));
    
    // Passo 2: Ordenar por prefixos de tamanho 2, 4, 8, ...
    for (int k = 4; k < 2 * n; k *= 2) {
        // Atribuir ranks baseado na ordenação anterior
        int rank = 0;
        int prev_rank = suffixes[0].rank[0];
        suffixes[0].rank[0] = rank;
        indices[suffixes[0].index] = 0;
        
        for (int i = 1; i < n; i++) {
            if (suffixes[i].rank[0] == prev_rank &&
                suffixes[i].rank[1] == suffixes[i-1].rank[1]) {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = rank;
            } else {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = ++rank;
            }
            indices[suffixes[i].index] = i;
        }
        
        // Calcular segundo rank baseado no próximo prefixo
        for (int i = 0; i < n; i++) {
            int next_index = suffixes[i].index + k/2;
            suffixes[i].rank[1] = (next_index < n) ? 
                                  suffixes[indices[next_index]].rank[0] : -1;
        }
        
        qsort(suffixes, n, sizeof(Suffix), compare_suffix);
    }
    
    // Construir o suffix array final
    for (int i = 0; i < n; i++) {
        sa->suffix_array[i] = suffixes[i].index;
    }
    
    free(suffixes);
    free(indices);
    
    return sa;
}

/**
 * Construção simples do Suffix Array (O(n² log n))
 * Mais simples de entender, menos eficiente
 */
SuffixArray* suffix_array_create_simple(const char *text) {
    int n = strlen(text);
    
    SuffixArray *sa = (SuffixArray *)malloc(sizeof(SuffixArray));
    sa->text = strdup(text);
    sa->length = n;
    sa->suffix_array = (int *)malloc(n * sizeof(int));
    
    // Array de sufixos (ponteiros para posições no texto)
    char **suffixes = (char **)malloc(n * sizeof(char *));
    int *positions = (int *)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        suffixes[i] = sa->text + i;
        positions[i] = i;
    }
    
    // Bubble sort dos sufixos (simples para demonstração)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(suffixes[j], suffixes[j + 1]) > 0) {
                char *temp_s = suffixes[j];
                suffixes[j] = suffixes[j + 1];
                suffixes[j + 1] = temp_s;
                
                int temp_p = positions[j];
                positions[j] = positions[j + 1];
                positions[j + 1] = temp_p;
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        sa->suffix_array[i] = positions[i];
    }
    
    free(suffixes);
    free(positions);
    
    return sa;
}

// ==================== OPERAÇÕES DE BUSCA ====================

/**
 * Comparar padrão com sufixo
 */
int compare_pattern(const char *text, int suffix_pos, const char *pattern, int pattern_len) {
    return strncmp(text + suffix_pos, pattern, pattern_len);
}

/**
 * Busca binária para encontrar a primeira ocorrência
 */
int find_first(SuffixArray *sa, const char *pattern) {
    int pattern_len = strlen(pattern);
    int left = 0, right = sa->length - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = compare_pattern(sa->text, sa->suffix_array[mid], pattern, pattern_len);
        
        if (cmp == 0) {
            result = mid;
            right = mid - 1;  // Continuar buscando à esquerda
        } else if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

/**
 * Busca binária para encontrar a última ocorrência
 */
int find_last(SuffixArray *sa, const char *pattern) {
    int pattern_len = strlen(pattern);
    int left = 0, right = sa->length - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = compare_pattern(sa->text, sa->suffix_array[mid], pattern, pattern_len);
        
        if (cmp == 0) {
            result = mid;
            left = mid + 1;  // Continuar buscando à direita
        } else if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

/**
 * Encontrar todas as ocorrências de um padrão
 * Retorna array de posições no texto original
 */
int* search_pattern(SuffixArray *sa, const char *pattern, int *count) {
    int first = find_first(sa, pattern);
    
    if (first == -1) {
        *count = 0;
        return NULL;
    }
    
    int last = find_last(sa, pattern);
    *count = last - first + 1;
    
    int *positions = (int *)malloc((*count) * sizeof(int));
    for (int i = 0; i < *count; i++) {
        positions[i] = sa->suffix_array[first + i];
    }
    
    return positions;
}

/**
 * Contar ocorrências de um padrão
 */
int count_occurrences(SuffixArray *sa, const char *pattern) {
    int first = find_first(sa, pattern);
    if (first == -1) return 0;
    
    int last = find_last(sa, pattern);
    return last - first + 1;
}

// ==================== SUBSTRING REPETIDA MAIS LONGA ====================

/**
 * Encontrar a substring repetida mais longa
 * Compara sufixos adjacentes no suffix array
 */
int longest_repeated_substring(SuffixArray *sa, int *start_pos) {
    int max_len = 0;
    *start_pos = -1;
    
    for (int i = 1; i < sa->length; i++) {
        // Calcular LCP de sufixos adjacentes
        int pos1 = sa->suffix_array[i - 1];
        int pos2 = sa->suffix_array[i];
        int len = 0;
        
        while (pos1 + len < sa->length && pos2 + len < sa->length &&
               sa->text[pos1 + len] == sa->text[pos2 + len]) {
            len++;
        }
        
        if (len > max_len) {
            max_len = len;
            *start_pos = pos1;
        }
    }
    
    return max_len;
}

// ==================== VISUALIZAÇÃO ====================

void print_suffix_array(SuffixArray *sa) {
    printf("Texto: \"%s\" (tamanho: %d)\n\n", sa->text, sa->length);
    printf("Suffix Array:\n");
    printf("┌───────┬───────┬────────────────────────────────┐\n");
    printf("│ Rank  │ Index │ Sufixo                         │\n");
    printf("├───────┼───────┼────────────────────────────────┤\n");
    
    for (int i = 0; i < sa->length; i++) {
        printf("│ %5d │ %5d │ %-30s │\n", 
               i, sa->suffix_array[i], sa->text + sa->suffix_array[i]);
    }
    printf("└───────┴───────┴────────────────────────────────┘\n");
}

// ==================== LIBERAÇÃO DE MEMÓRIA ====================

void suffix_array_free(SuffixArray *sa) {
    free(sa->suffix_array);
    free(sa->text);
    free(sa);
}

// ==================== TESTES ====================

void testar_construcao() {
    printf("=== CONSTRUÇÃO DO SUFFIX ARRAY ===\n\n");
    
    const char *texto = "banana";
    SuffixArray *sa = suffix_array_create_simple(texto);
    
    print_suffix_array(sa);
    printf("\n");
    
    printf("Explicação:\n");
    printf("- Sufixos ordenados lexicograficamente\n");
    printf("- 'a' < 'ana' < 'anana' < 'banana' < 'na' < 'nana'\n");
    printf("\n");
    
    suffix_array_free(sa);
}

void testar_busca() {
    printf("=== BUSCA DE PADRÕES ===\n\n");
    
    const char *texto = "abracadabra";
    SuffixArray *sa = suffix_array_create(texto);
    
    print_suffix_array(sa);
    printf("\n");
    
    // Buscar padrão "abra"
    const char *padrao = "abra";
    int count;
    int *posicoes = search_pattern(sa, padrao, &count);
    
    printf("Padrão \"%s\" encontrado %d vez(es):\n", padrao, count);
    if (posicoes) {
        for (int i = 0; i < count; i++) {
            printf("  Posição %d: %s\n", posicoes[i], texto + posicoes[i]);
        }
        free(posicoes);
    }
    printf("\n");
    
    // Buscar outro padrão
    padrao = "bra";
    printf("Ocorrências de \"%s\": %d\n", padrao, count_occurrences(sa, padrao));
    
    padrao = "xyz";
    printf("Ocorrências de \"%s\": %d\n", padrao, count_occurrences(sa, padrao));
    
    printf("\n");
    suffix_array_free(sa);
}

void testar_lrs() {
    printf("=== SUBSTRING REPETIDA MAIS LONGA ===\n\n");
    
    const char *texto = "banana";
    SuffixArray *sa = suffix_array_create_simple(texto);
    
    int pos;
    int len = longest_repeated_substring(sa, &pos);
    
    printf("Texto: \"%s\"\n", texto);
    printf("Substring repetida mais longa: ");
    if (len > 0) {
        printf("\"%.*s\" (tamanho %d, posição %d)\n", len, texto + pos, len, pos);
    } else {
        printf("(nenhuma)\n");
    }
    printf("\n");
    
    suffix_array_free(sa);
    
    // Outro exemplo
    texto = "mississippi";
    sa = suffix_array_create(texto);
    
    len = longest_repeated_substring(sa, &pos);
    
    printf("Texto: \"%s\"\n", texto);
    printf("Substring repetida mais longa: ");
    if (len > 0) {
        printf("\"%.*s\" (tamanho %d)\n", len, texto + pos, len);
    }
    printf("\n");
    
    suffix_array_free(sa);
}

void testar_aplicacoes() {
    printf("=== APLICAÇÕES PRÁTICAS ===\n\n");
    
    printf("1. BIOINFORMÁTICA - Busca de sequências genéticas:\n");
    const char *dna = "actgactgactgaactgactg";
    SuffixArray *sa = suffix_array_create(dna);
    
    const char *gene = "actg";
    printf("   DNA: %s\n", dna);
    printf("   Gene \"%s\" aparece %d vezes\n", gene, count_occurrences(sa, gene));
    
    suffix_array_free(sa);
    printf("\n");
    
    printf("2. COMPRESSÃO DE DADOS:\n");
    printf("   Suffix arrays são usados em BWT (Burrows-Wheeler Transform)\n");
    printf("   que é base do algoritmo de compressão bzip2\n\n");
    
    printf("3. DETECÇÃO DE PLÁGIO:\n");
    const char *texto1 = "este é um texto de exemplo para teste";
    sa = suffix_array_create(texto1);
    
    const char *fragmento = "texto de";
    printf("   Documento: \"%s\"\n", texto1);
    printf("   Fragmento \"%s\" encontrado: %s\n", 
           fragmento, count_occurrences(sa, fragmento) > 0 ? "Sim" : "Não");
    
    suffix_array_free(sa);
    printf("\n");
}

// ==================== FUNÇÃO PRINCIPAL ====================

int main() {
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║            SUFFIX ARRAY - ARRAY DE SUFIXOS               ║\n");
    printf("║   Estrutura eficiente para busca em strings              ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    testar_construcao();
    testar_busca();
    testar_lrs();
    testar_aplicacoes();
    
    printf("═══════════════════════════════════════════════════════════\n");
    printf("Complexidades:\n");
    printf("- Construção: O(n log n) ou O(n) com algoritmos avançados\n");
    printf("- Busca: O(m log n) onde m = tamanho do padrão\n");
    printf("- Espaço: O(n) - muito mais eficiente que Suffix Tree!\n");
    printf("\n");
    printf("Próximo: Tabela LCP (08) para otimizar buscas\n");
    printf("═══════════════════════════════════════════════════════════\n");
    
    return 0;
}
