/**
 * ============================================================================
 * HYPERLOGLOG - ESTIMATIVA DE CARDINALIDADE
 * ============================================================================
 * 
 * HyperLogLog é um algoritmo probabilístico para estimar a cardinalidade
 * (número de elementos distintos) de um conjunto usando espaço muito pequeno.
 * 
 * Características:
 * - Erro padrão: 1.04/√m onde m é o número de registros
 * - Espaço: O(m) = O(1/ε²) onde ε é o erro relativo
 * - Com 12KB de memória, erro de ~0.81% para bilhões de elementos!
 * 
 * Aplicações:
 * - Contagem de usuários únicos
 * - Análise de logs
 * - Detecção de ataques DDoS
 * - Estatísticas de banco de dados
 * 
 * Pré-requisito: Count-Min Sketch (10-count-min-sketch)
 * 
 * Autor: Estrutura de Dados em C
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

// ==================== CONSTANTES ====================

#define HLL_BITS 14         // Número de bits para índice (m = 2^14 = 16384)
#define HLL_REGISTERS 16384 // Número de registros (2^14)

// ==================== ESTRUTURA HYPERLOGLOG ====================

typedef struct {
    uint8_t *registers;   // Array de registros
    int num_registers;    // Número de registros (m = 2^p)
    int precision;        // Número de bits de precisão (p)
    double alpha;         // Constante de correção
} HyperLogLog;

// ==================== FUNÇÕES HASH ====================

/**
 * Função hash de 64 bits (baseada em MurmurHash3)
 */
uint64_t hash64(const void *key, int len) {
    const uint8_t *data = (const uint8_t *)key;
    const int nblocks = len / 8;
    
    uint64_t h1 = 0;
    uint64_t c1 = 0x87c37b91114253d5ULL;
    uint64_t c2 = 0x4cf5ad432745937fULL;
    
    const uint64_t *blocks = (const uint64_t *)(data);
    
    for (int i = 0; i < nblocks; i++) {
        uint64_t k1 = blocks[i];
        
        k1 *= c1;
        k1 = (k1 << 31) | (k1 >> 33);
        k1 *= c2;
        
        h1 ^= k1;
        h1 = (h1 << 27) | (h1 >> 37);
        h1 = h1 * 5 + 0x52dce729;
    }
    
    const uint8_t *tail = (const uint8_t *)(data + nblocks * 8);
    uint64_t k1 = 0;
    
    switch (len & 7) {
        case 7: k1 ^= (uint64_t)(tail[6]) << 48; /* fall through */
        case 6: k1 ^= (uint64_t)(tail[5]) << 40; /* fall through */
        case 5: k1 ^= (uint64_t)(tail[4]) << 32; /* fall through */
        case 4: k1 ^= (uint64_t)(tail[3]) << 24; /* fall through */
        case 3: k1 ^= (uint64_t)(tail[2]) << 16; /* fall through */
        case 2: k1 ^= (uint64_t)(tail[1]) << 8; /* fall through */
        case 1: k1 ^= (uint64_t)(tail[0]);
                k1 *= c1;
                k1 = (k1 << 31) | (k1 >> 33);
                k1 *= c2;
                h1 ^= k1;
    }
    
    h1 ^= len;
    h1 ^= h1 >> 33;
    h1 *= 0xff51afd7ed558ccdULL;
    h1 ^= h1 >> 33;
    h1 *= 0xc4ceb9fe1a85ec53ULL;
    h1 ^= h1 >> 33;
    
    return h1;
}

/**
 * Hash para inteiros
 */
uint64_t hash_int(int value) {
    return hash64(&value, sizeof(int));
}

/**
 * Hash para strings
 */
uint64_t hash_string(const char *str) {
    return hash64(str, strlen(str));
}

// ==================== FUNÇÕES AUXILIARES ====================

/**
 * Contar zeros à direita + 1 (posição do primeiro bit 1)
 */
int count_leading_zeros(uint64_t hash, int bits_usados) {
    // Ignorar os primeiros 'bits_usados' bits
    hash = hash >> bits_usados;
    
    if (hash == 0) return 64 - bits_usados + 1;
    
    int count = 1;
    while ((hash & 1) == 0 && count <= 64 - bits_usados) {
        count++;
        hash >>= 1;
    }
    return count;
}

/**
 * Calcular constante alpha baseada no número de registros
 */
double calculate_alpha(int m) {
    if (m == 16) return 0.673;
    if (m == 32) return 0.697;
    if (m == 64) return 0.709;
    // Para m >= 128
    return 0.7213 / (1.0 + 1.079 / m);
}

// ==================== CRIAÇÃO E DESTRUIÇÃO ====================

HyperLogLog* hll_create(int precision) {
    if (precision < 4 || precision > 18) {
        precision = 14;  // Valor padrão
    }
    
    HyperLogLog *hll = (HyperLogLog *)malloc(sizeof(HyperLogLog));
    hll->precision = precision;
    hll->num_registers = 1 << precision;  // 2^precision
    hll->registers = (uint8_t *)calloc(hll->num_registers, sizeof(uint8_t));
    hll->alpha = calculate_alpha(hll->num_registers);
    
    return hll;
}

void hll_free(HyperLogLog *hll) {
    free(hll->registers);
    free(hll);
}

// ==================== OPERAÇÕES PRINCIPAIS ====================

/**
 * Adicionar um inteiro ao HyperLogLog
 */
void hll_add_int(HyperLogLog *hll, int value) {
    uint64_t hash = hash_int(value);
    
    // Usar primeiros p bits como índice
    int idx = hash & ((1 << hll->precision) - 1);
    
    // Contar zeros no restante
    int rank = count_leading_zeros(hash, hll->precision);
    
    // Atualizar registro com o máximo
    if (rank > hll->registers[idx]) {
        hll->registers[idx] = rank;
    }
}

/**
 * Adicionar uma string ao HyperLogLog
 */
void hll_add_string(HyperLogLog *hll, const char *str) {
    uint64_t hash = hash_string(str);
    
    int idx = hash & ((1 << hll->precision) - 1);
    int rank = count_leading_zeros(hash, hll->precision);
    
    if (rank > hll->registers[idx]) {
        hll->registers[idx] = rank;
    }
}

/**
 * Estimar cardinalidade
 */
double hll_estimate(HyperLogLog *hll) {
    int m = hll->num_registers;
    
    // Calcular média harmônica
    double sum = 0.0;
    int zeros = 0;
    
    for (int i = 0; i < m; i++) {
        sum += 1.0 / (1ULL << hll->registers[i]);
        if (hll->registers[i] == 0) zeros++;
    }
    
    double estimate = hll->alpha * m * m / sum;
    
    // Correção para valores pequenos
    if (estimate <= 2.5 * m && zeros > 0) {
        // LinearCounting
        estimate = m * log((double)m / zeros);
    }
    // Correção para valores muito grandes
    else if (estimate > (1.0 / 30.0) * pow(2, 32)) {
        estimate = -pow(2, 32) * log(1.0 - estimate / pow(2, 32));
    }
    
    return estimate;
}

/**
 * Merge de dois HyperLogLogs
 */
HyperLogLog* hll_merge(HyperLogLog *hll1, HyperLogLog *hll2) {
    if (hll1->precision != hll2->precision) {
        return NULL;
    }
    
    HyperLogLog *result = hll_create(hll1->precision);
    
    for (int i = 0; i < result->num_registers; i++) {
        result->registers[i] = (hll1->registers[i] > hll2->registers[i]) ?
                               hll1->registers[i] : hll2->registers[i];
    }
    
    return result;
}

/**
 * Limpar HyperLogLog
 */
void hll_clear(HyperLogLog *hll) {
    memset(hll->registers, 0, hll->num_registers * sizeof(uint8_t));
}

// ==================== ESTATÍSTICAS ====================

void hll_stats(HyperLogLog *hll) {
    int zeros = 0;
    int max_val = 0;
    int sum = 0;
    
    for (int i = 0; i < hll->num_registers; i++) {
        if (hll->registers[i] == 0) zeros++;
        if (hll->registers[i] > max_val) max_val = hll->registers[i];
        sum += hll->registers[i];
    }
    
    printf("Estatísticas HyperLogLog:\n");
    printf("  Número de registros: %d\n", hll->num_registers);
    printf("  Registros zerados: %d (%.2f%%)\n", zeros, 100.0 * zeros / hll->num_registers);
    printf("  Valor máximo: %d\n", max_val);
    printf("  Valor médio: %.2f\n", (double)sum / hll->num_registers);
    printf("  Memória usada: %d bytes\n", hll->num_registers);
}

// ==================== TESTES ====================

void testar_basico() {
    printf("=== TESTE BÁSICO HYPERLOGLOG ===\n\n");
    
    HyperLogLog *hll = hll_create(10);  // 2^10 = 1024 registros
    
    printf("Adicionando elementos: 1, 2, 3, 4, 5\n");
    hll_add_int(hll, 1);
    hll_add_int(hll, 2);
    hll_add_int(hll, 3);
    hll_add_int(hll, 4);
    hll_add_int(hll, 5);
    
    printf("Cardinalidade estimada: %.0f (esperado: 5)\n\n", hll_estimate(hll));
    
    printf("Adicionando elementos duplicados: 1, 2, 3, 1, 2, 1\n");
    hll_add_int(hll, 1);
    hll_add_int(hll, 2);
    hll_add_int(hll, 3);
    hll_add_int(hll, 1);
    hll_add_int(hll, 2);
    hll_add_int(hll, 1);
    
    printf("Cardinalidade estimada: %.0f (esperado: ainda 5)\n\n", hll_estimate(hll));
    
    hll_free(hll);
}

void testar_strings() {
    printf("=== TESTE COM STRINGS ===\n\n");
    
    HyperLogLog *hll = hll_create(12);
    
    const char *palavras[] = {"apple", "banana", "cherry", "date", "elderberry",
                              "fig", "grape", "honeydew", "apple", "banana"};
    int n = sizeof(palavras) / sizeof(palavras[0]);
    
    printf("Adicionando %d strings (com 2 duplicatas):\n", n);
    for (int i = 0; i < n; i++) {
        printf("  %s\n", palavras[i]);
        hll_add_string(hll, palavras[i]);
    }
    
    printf("\nCardinalidade estimada: %.0f (esperado: 8)\n\n", hll_estimate(hll));
    
    hll_free(hll);
}

void testar_precisao() {
    printf("=== TESTE DE PRECISÃO ===\n\n");
    
    int tamanhos[] = {100, 1000, 10000, 100000};
    int num_testes = 4;
    
    printf("┌─────────────┬────────────┬──────────────┬──────────┐\n");
    printf("│ Cardinalidade│ Estimativa │ Erro Absoluto│ Erro %%   │\n");
    printf("│ Real        │            │              │          │\n");
    printf("├─────────────┼────────────┼──────────────┼──────────┤\n");
    
    for (int t = 0; t < num_testes; t++) {
        int n = tamanhos[t];
        HyperLogLog *hll = hll_create(14);
        
        for (int i = 0; i < n; i++) {
            hll_add_int(hll, i);
        }
        
        double est = hll_estimate(hll);
        double erro_abs = fabs(est - n);
        double erro_rel = 100.0 * erro_abs / n;
        
        printf("│ %11d │ %10.0f │ %12.0f │ %7.2f%% │\n", 
               n, est, erro_abs, erro_rel);
        
        hll_free(hll);
    }
    printf("└─────────────┴────────────┴──────────────┴──────────┘\n\n");
    
    printf("Erro teórico: ~1.04/√m = ~0.81%% para m=16384\n\n");
}

void testar_merge() {
    printf("=== TESTE DE MERGE ===\n\n");
    
    HyperLogLog *hll1 = hll_create(12);
    HyperLogLog *hll2 = hll_create(12);
    
    printf("HLL1: elementos 0-999\n");
    for (int i = 0; i < 1000; i++) {
        hll_add_int(hll1, i);
    }
    
    printf("HLL2: elementos 500-1499\n");
    for (int i = 500; i < 1500; i++) {
        hll_add_int(hll2, i);
    }
    
    printf("\nEstimativas individuais:\n");
    printf("  HLL1: %.0f (esperado: 1000)\n", hll_estimate(hll1));
    printf("  HLL2: %.0f (esperado: 1000)\n", hll_estimate(hll2));
    
    HyperLogLog *merged = hll_merge(hll1, hll2);
    
    printf("\nApós merge (união):\n");
    printf("  Merged: %.0f (esperado: 1500 únicos)\n", hll_estimate(merged));
    
    hll_free(hll1);
    hll_free(hll2);
    hll_free(merged);
    printf("\n");
}

void comparar_memoria() {
    printf("=== COMPARAÇÃO DE MEMÓRIA ===\n\n");
    
    long n = 1000000000L;  // 1 bilhão
    
    printf("Para contar até %ld elementos únicos:\n\n", n);
    
    printf("Estrutura exata (HashSet):\n");
    printf("  Memória: ~%ld GB\n", n * 8 / 1024 / 1024 / 1024);
    
    printf("\nHyperLogLog (precisão 14):\n");
    printf("  Memória: %d bytes (~16 KB)\n", HLL_REGISTERS);
    printf("  Erro: ~0.81%%\n");
    
    printf("\nEconomia: ~%.0fx menos memória!\n\n", 
           (double)(n * 8) / HLL_REGISTERS);
}

void testar_estatisticas() {
    printf("=== ESTATÍSTICAS DO HLL ===\n\n");
    
    HyperLogLog *hll = hll_create(10);
    
    printf("Estado inicial:\n");
    hll_stats(hll);
    
    printf("\nApós 1000 elementos:\n");
    for (int i = 0; i < 1000; i++) {
        hll_add_int(hll, i);
    }
    hll_stats(hll);
    
    printf("\nEstimativa: %.0f\n\n", hll_estimate(hll));
    
    hll_free(hll);
}

// ==================== FUNÇÃO PRINCIPAL ====================

int main() {
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║              HYPERLOGLOG                                 ║\n");
    printf("║   Contagem de elementos únicos em espaço constante      ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    testar_basico();
    testar_strings();
    testar_precisao();
    testar_merge();
    testar_estatisticas();
    comparar_memoria();
    
    printf("═══════════════════════════════════════════════════════════\n");
    printf("Propriedades do HyperLogLog:\n");
    printf("- Erro padrão: 1.04/√m\n");
    printf("- Espaço: O(m) ≈ O(1) para precisão fixa\n");
    printf("- Suporta merge (união de conjuntos)\n");
    printf("- Usado por: Redis, BigQuery, Presto, etc.\n");
    printf("\n");
    printf("Próximo: Treap (12) - BST + Heap randomizado\n");
    printf("═══════════════════════════════════════════════════════════\n");
    
    return 0;
}
