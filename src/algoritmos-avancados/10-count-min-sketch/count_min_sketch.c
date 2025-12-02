/**
 * ============================================================================
 * COUNT-MIN SKETCH
 * ============================================================================
 * 
 * O Count-Min Sketch é uma estrutura de dados probabilística que permite
 * estimar a frequência de elementos em um fluxo de dados usando espaço
 * sublinear.
 * 
 * Características:
 * - Espaço: O(ε⁻¹ log δ⁻¹) onde ε é o erro e δ é a probabilidade de falha
 * - Tempo de atualização: O(log δ⁻¹)
 * - Nunca subestima a frequência (pode superestimar)
 * 
 * Aplicações:
 * - Análise de tráfego de rede
 * - Contagem de palavras em streams
 * - Detecção de heavy hitters
 * - Sistemas de recomendação
 * 
 * Pré-requisito: Bloom Filter (09-bloomfilter)
 * 
 * Autor: Estrutura de Dados em C
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

// ==================== ESTRUTURA COUNT-MIN SKETCH ====================

typedef struct {
    int **counters;      // Matriz de contadores
    int width;           // Largura (número de colunas)
    int depth;           // Profundidade (número de linhas/hashes)
    unsigned int *seeds; // Seeds para funções hash
} CountMinSketch;

// ==================== FUNÇÕES HASH ====================

/**
 * Função hash baseada em multiplicação
 */
unsigned int hash_function(int item, int seed, int width) {
    unsigned int hash = seed;
    unsigned int val = (unsigned int)item;
    
    // MurmurHash simplificado
    val *= 0xcc9e2d51;
    val = (val >> 15) | (val << 17);
    val *= 0x1b873593;
    
    hash ^= val;
    hash = (hash >> 13) | (hash << 19);
    hash = hash * 5 + 0xe6546b64;
    
    return hash % width;
}

/**
 * Hash para strings
 */
unsigned int hash_string(const char *str, int seed, int width) {
    unsigned int hash = seed;
    
    while (*str) {
        hash ^= (unsigned int)*str++;
        hash *= 0x5bd1e995;
        hash ^= hash >> 15;
    }
    
    return hash % width;
}

// ==================== CRIAÇÃO E DESTRUIÇÃO ====================

/**
 * Criar Count-Min Sketch
 * 
 * @param epsilon: erro relativo desejado (ex: 0.01 para 1%)
 * @param delta: probabilidade de falha (ex: 0.01 para 1%)
 */
CountMinSketch* cms_create(double epsilon, double delta) {
    CountMinSketch *cms = (CountMinSketch *)malloc(sizeof(CountMinSketch));
    
    // Calcular dimensões ótimas
    cms->width = (int)ceil(2.718281828 / epsilon);  // e/ε
    cms->depth = (int)ceil(log(1.0 / delta));       // ln(1/δ)
    
    printf("  [CMS criado: width=%d, depth=%d]\n", cms->width, cms->depth);
    
    // Alocar matriz de contadores
    cms->counters = (int **)malloc(cms->depth * sizeof(int *));
    for (int i = 0; i < cms->depth; i++) {
        cms->counters[i] = (int *)calloc(cms->width, sizeof(int));
    }
    
    // Gerar seeds aleatórias
    cms->seeds = (unsigned int *)malloc(cms->depth * sizeof(unsigned int));
    for (int i = 0; i < cms->depth; i++) {
        cms->seeds[i] = rand();
    }
    
    return cms;
}

/**
 * Criar com dimensões específicas
 */
CountMinSketch* cms_create_simple(int width, int depth) {
    CountMinSketch *cms = (CountMinSketch *)malloc(sizeof(CountMinSketch));
    
    cms->width = width;
    cms->depth = depth;
    
    cms->counters = (int **)malloc(depth * sizeof(int *));
    for (int i = 0; i < depth; i++) {
        cms->counters[i] = (int *)calloc(width, sizeof(int));
    }
    
    cms->seeds = (unsigned int *)malloc(depth * sizeof(unsigned int));
    for (int i = 0; i < depth; i++) {
        cms->seeds[i] = (i + 1) * 0x5bd1e995;
    }
    
    return cms;
}

void cms_free(CountMinSketch *cms) {
    for (int i = 0; i < cms->depth; i++) {
        free(cms->counters[i]);
    }
    free(cms->counters);
    free(cms->seeds);
    free(cms);
}

// ==================== OPERAÇÕES PRINCIPAIS ====================

/**
 * Adicionar um elemento (incrementar contagem)
 */
void cms_add(CountMinSketch *cms, int item) {
    for (int i = 0; i < cms->depth; i++) {
        int j = hash_function(item, cms->seeds[i], cms->width);
        cms->counters[i][j]++;
    }
}

/**
 * Adicionar com contagem específica
 */
void cms_add_count(CountMinSketch *cms, int item, int count) {
    for (int i = 0; i < cms->depth; i++) {
        int j = hash_function(item, cms->seeds[i], cms->width);
        cms->counters[i][j] += count;
    }
}

/**
 * Estimar frequência de um elemento
 * Retorna o mínimo entre todas as linhas (minimiza superestimação)
 */
int cms_estimate(CountMinSketch *cms, int item) {
    int min_count = INT_MAX;
    
    for (int i = 0; i < cms->depth; i++) {
        int j = hash_function(item, cms->seeds[i], cms->width);
        if (cms->counters[i][j] < min_count) {
            min_count = cms->counters[i][j];
        }
    }
    
    return min_count;
}

/**
 * Versão para strings
 */
void cms_add_string(CountMinSketch *cms, const char *str) {
    for (int i = 0; i < cms->depth; i++) {
        int j = hash_string(str, cms->seeds[i], cms->width);
        cms->counters[i][j]++;
    }
}

int cms_estimate_string(CountMinSketch *cms, const char *str) {
    int min_count = INT_MAX;
    
    for (int i = 0; i < cms->depth; i++) {
        int j = hash_string(str, cms->seeds[i], cms->width);
        if (cms->counters[i][j] < min_count) {
            min_count = cms->counters[i][j];
        }
    }
    
    return min_count;
}

// ==================== OPERAÇÕES ADICIONAIS ====================

/**
 * Merge de dois Count-Min Sketches
 */
CountMinSketch* cms_merge(CountMinSketch *cms1, CountMinSketch *cms2) {
    if (cms1->width != cms2->width || cms1->depth != cms2->depth) {
        return NULL;
    }
    
    CountMinSketch *result = cms_create_simple(cms1->width, cms1->depth);
    
    for (int i = 0; i < result->depth; i++) {
        result->seeds[i] = cms1->seeds[i];
        for (int j = 0; j < result->width; j++) {
            result->counters[i][j] = cms1->counters[i][j] + cms2->counters[i][j];
        }
    }
    
    return result;
}

/**
 * Produto interno (estima soma de freq1 * freq2)
 */
long cms_inner_product(CountMinSketch *cms1, CountMinSketch *cms2) {
    if (cms1->width != cms2->width || cms1->depth != cms2->depth) {
        return -1;
    }
    
    long min_sum = LONG_MAX;
    
    for (int i = 0; i < cms1->depth; i++) {
        long sum = 0;
        for (int j = 0; j < cms1->width; j++) {
            sum += (long)cms1->counters[i][j] * cms2->counters[i][j];
        }
        if (sum < min_sum) {
            min_sum = sum;
        }
    }
    
    return min_sum;
}

// ==================== HEAVY HITTERS ====================

/**
 * Identificar heavy hitters (elementos frequentes)
 * threshold: frequência mínima para ser considerado heavy hitter
 */
void cms_find_heavy_hitters(CountMinSketch *cms, int *candidates, int num_candidates, 
                            int threshold, int *heavy_hitters, int *hh_count) {
    *hh_count = 0;
    
    for (int i = 0; i < num_candidates; i++) {
        if (cms_estimate(cms, candidates[i]) >= threshold) {
            heavy_hitters[(*hh_count)++] = candidates[i];
        }
    }
}

// ==================== VISUALIZAÇÃO ====================

void cms_print(CountMinSketch *cms) {
    printf("Count-Min Sketch (%dx%d):\n", cms->depth, cms->width);
    
    for (int i = 0; i < cms->depth; i++) {
        printf("  Linha %d: [", i);
        for (int j = 0; j < cms->width && j < 10; j++) {
            printf("%d", cms->counters[i][j]);
            if (j < cms->width - 1 && j < 9) printf(", ");
        }
        if (cms->width > 10) printf(", ...");
        printf("]\n");
    }
}

// ==================== TESTES ====================

void testar_basico() {
    printf("=== TESTE BÁSICO COUNT-MIN SKETCH ===\n\n");
    
    CountMinSketch *cms = cms_create_simple(10, 4);
    
    // Adicionar elementos
    printf("Adicionando elementos:\n");
    cms_add(cms, 1);
    cms_add(cms, 1);
    cms_add(cms, 1);
    cms_add(cms, 2);
    cms_add(cms, 2);
    cms_add(cms, 3);
    
    printf("  1: 3 vezes\n");
    printf("  2: 2 vezes\n");
    printf("  3: 1 vez\n\n");
    
    printf("Estimativas:\n");
    printf("  Frequência de 1: %d (esperado: 3)\n", cms_estimate(cms, 1));
    printf("  Frequência de 2: %d (esperado: 2)\n", cms_estimate(cms, 2));
    printf("  Frequência de 3: %d (esperado: 1)\n", cms_estimate(cms, 3));
    printf("  Frequência de 4: %d (esperado: 0)\n", cms_estimate(cms, 4));
    
    printf("\nEstado interno:\n");
    cms_print(cms);
    printf("\n");
    
    cms_free(cms);
}

void testar_strings() {
    printf("=== TESTE COM STRINGS ===\n\n");
    
    CountMinSketch *cms = cms_create_simple(20, 5);
    
    // Simular contagem de palavras
    const char *palavras[] = {"the", "quick", "brown", "fox", "the", "lazy", "dog", "the"};
    int n = sizeof(palavras) / sizeof(palavras[0]);
    
    printf("Contando palavras:\n");
    for (int i = 0; i < n; i++) {
        printf("  %s\n", palavras[i]);
        cms_add_string(cms, palavras[i]);
    }
    
    printf("\nEstimativas:\n");
    printf("  'the': %d (esperado: 3)\n", cms_estimate_string(cms, "the"));
    printf("  'fox': %d (esperado: 1)\n", cms_estimate_string(cms, "fox"));
    printf("  'cat': %d (esperado: 0)\n", cms_estimate_string(cms, "cat"));
    printf("\n");
    
    cms_free(cms);
}

void testar_precisao() {
    printf("=== TESTE DE PRECISÃO ===\n\n");
    
    // CMS com parâmetros para erro de 1% e 1% de probabilidade de falha
    CountMinSketch *cms = cms_create(0.01, 0.01);
    
    // Simular stream de dados
    int n = 10000;
    int freq_real[100] = {0};
    
    printf("Simulando stream de %d elementos...\n", n);
    
    srand(42);
    for (int i = 0; i < n; i++) {
        // Distribuição Zipf-like
        int item;
        double r = (double)rand() / RAND_MAX;
        if (r < 0.3) item = 0;
        else if (r < 0.5) item = 1;
        else if (r < 0.65) item = 2;
        else item = rand() % 100;
        
        cms_add(cms, item);
        freq_real[item]++;
    }
    
    printf("\nComparação (10 primeiros elementos):\n");
    printf("┌──────┬───────────┬────────────┬──────────┐\n");
    printf("│ Item │ Freq Real │ Estimativa │ Erro     │\n");
    printf("├──────┼───────────┼────────────┼──────────┤\n");
    
    for (int i = 0; i < 10; i++) {
        int est = cms_estimate(cms, i);
        int erro = est - freq_real[i];
        printf("│ %4d │ %9d │ %10d │ %+8d │\n", i, freq_real[i], est, erro);
    }
    printf("└──────┴───────────┴────────────┴──────────┘\n\n");
    
    printf("Nota: CMS nunca subestima, apenas pode superestimar!\n\n");
    
    cms_free(cms);
}

void testar_heavy_hitters() {
    printf("=== HEAVY HITTERS ===\n\n");
    
    CountMinSketch *cms = cms_create_simple(100, 5);
    
    // Stream com alguns elementos frequentes
    printf("Stream: muitos 5's e 10's, poucos outros\n");
    for (int i = 0; i < 100; i++) cms_add(cms, 5);
    for (int i = 0; i < 80; i++) cms_add(cms, 10);
    for (int i = 0; i < 20; i++) cms_add(cms, 15);
    for (int i = 0; i < 5; i++) cms_add(cms, i + 20);
    
    // Candidatos a heavy hitters
    int candidates[] = {5, 10, 15, 20, 21, 22};
    int num_candidates = 6;
    
    int heavy_hitters[10];
    int hh_count;
    
    cms_find_heavy_hitters(cms, candidates, num_candidates, 50, heavy_hitters, &hh_count);
    
    printf("Heavy Hitters (threshold >= 50):\n");
    for (int i = 0; i < hh_count; i++) {
        printf("  Item %d: frequência estimada = %d\n", 
               heavy_hitters[i], cms_estimate(cms, heavy_hitters[i]));
    }
    printf("\n");
    
    cms_free(cms);
}

void comparar_memoria() {
    printf("=== COMPARAÇÃO DE MEMÓRIA ===\n\n");
    
    int n = 1000000;  // 1 milhão de elementos únicos possíveis
    
    printf("Para rastrear %d elementos únicos:\n\n", n);
    
    printf("Array exato:     %lu bytes (%lu MB)\n", 
           (unsigned long)(n * sizeof(int)),
           (unsigned long)(n * sizeof(int) / 1024 / 1024));
    
    // CMS com 1% de erro e 1% de falha
    int width = (int)ceil(2.718281828 / 0.01);
    int depth = (int)ceil(log(1.0 / 0.01));
    
    printf("Count-Min Sketch: %lu bytes (%.2f KB)\n",
           (unsigned long)(width * depth * sizeof(int)),
           (double)(width * depth * sizeof(int)) / 1024);
    
    printf("\nEconomia: %.2fx menos memória!\n\n", 
           (double)(n * sizeof(int)) / (width * depth * sizeof(int)));
}

// ==================== FUNÇÃO PRINCIPAL ====================

int main() {
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║              COUNT-MIN SKETCH                            ║\n");
    printf("║   Estimativa de frequência em espaço sublinear           ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    testar_basico();
    testar_strings();
    testar_precisao();
    testar_heavy_hitters();
    comparar_memoria();
    
    printf("═══════════════════════════════════════════════════════════\n");
    printf("Propriedades do Count-Min Sketch:\n");
    printf("- Nunca subestima a frequência\n");
    printf("- Erro máximo: εN com probabilidade 1-δ\n");
    printf("- Espaço: O(1/ε * log(1/δ))\n");
    printf("\n");
    printf("Próximo: HyperLogLog (11) para contagem de elementos únicos\n");
    printf("═══════════════════════════════════════════════════════════\n");
    
    return 0;
}
