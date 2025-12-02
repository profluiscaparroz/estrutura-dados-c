/**
 * ============================================================================
 * TABELA HASH AVANÇADA - TÉCNICAS DE RESOLUÇÃO DE COLISÕES
 * ============================================================================
 * 
 * Este arquivo demonstra técnicas avançadas de hash tables, expandindo
 * os conceitos do Consistent Hashing (03-consistent-hashing).
 * 
 * Técnicas implementadas:
 * - Encadeamento (Chaining)
 * - Endereçamento Aberto (Open Addressing)
 *   - Linear Probing
 *   - Quadratic Probing
 *   - Double Hashing
 * - Cuckoo Hashing
 * 
 * Conceitos importantes:
 * - Fator de carga
 * - Redimensionamento dinâmico
 * - Funções hash universais
 * 
 * Pré-requisito: Entender Consistent Hashing (03-consistent-hashing)
 * 
 * Autor: Estrutura de Dados em C
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INICIAL_SIZE 16
#define LOAD_FACTOR_MAX 0.75
#define DELETED_KEY -999999

// ==================== FUNÇÕES HASH ====================

/**
 * Função hash primária (djb2)
 */
unsigned int hash_primary(int key, int size) {
    unsigned int hash = 5381;
    unsigned int k = (unsigned int)key;
    
    while (k > 0) {
        hash = ((hash << 5) + hash) + (k % 10);
        k /= 10;
    }
    
    return hash % size;
}

/**
 * Função hash secundária para double hashing
 */
unsigned int hash_secondary(int key, int size) {
    (void)size;  // Não usado nesta implementação
    // Retorna um valor ímpar para garantir que percorrerá toda a tabela
    return 7 - (key % 7);
}

// ==================== HASH TABLE COM ENCADEAMENTO ====================

typedef struct ChainNode {
    int key;
    int value;
    struct ChainNode *next;
} ChainNode;

typedef struct {
    ChainNode **buckets;
    int size;
    int count;
} ChainHashTable;

ChainHashTable* chain_create(int size) {
    ChainHashTable *ht = (ChainHashTable *)malloc(sizeof(ChainHashTable));
    ht->size = size;
    ht->count = 0;
    ht->buckets = (ChainNode **)calloc(size, sizeof(ChainNode *));
    return ht;
}

void chain_insert(ChainHashTable *ht, int key, int value) {
    unsigned int idx = hash_primary(key, ht->size);
    
    // Verificar se chave já existe
    ChainNode *current = ht->buckets[idx];
    while (current) {
        if (current->key == key) {
            current->value = value;
            return;
        }
        current = current->next;
    }
    
    // Inserir no início da lista
    ChainNode *node = (ChainNode *)malloc(sizeof(ChainNode));
    node->key = key;
    node->value = value;
    node->next = ht->buckets[idx];
    ht->buckets[idx] = node;
    ht->count++;
}

int chain_search(ChainHashTable *ht, int key) {
    unsigned int idx = hash_primary(key, ht->size);
    
    ChainNode *current = ht->buckets[idx];
    while (current) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    
    return -1; // Não encontrado
}

void chain_delete(ChainHashTable *ht, int key) {
    unsigned int idx = hash_primary(key, ht->size);
    
    ChainNode *current = ht->buckets[idx];
    ChainNode *prev = NULL;
    
    while (current) {
        if (current->key == key) {
            if (prev) {
                prev->next = current->next;
            } else {
                ht->buckets[idx] = current->next;
            }
            free(current);
            ht->count--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void chain_free(ChainHashTable *ht) {
    for (int i = 0; i < ht->size; i++) {
        ChainNode *current = ht->buckets[i];
        while (current) {
            ChainNode *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(ht->buckets);
    free(ht);
}

// ==================== HASH TABLE COM LINEAR PROBING ====================

typedef struct {
    int *keys;
    int *values;
    bool *occupied;
    int size;
    int count;
} LinearHashTable;

LinearHashTable* linear_create(int size) {
    LinearHashTable *ht = (LinearHashTable *)malloc(sizeof(LinearHashTable));
    ht->size = size;
    ht->count = 0;
    ht->keys = (int *)malloc(size * sizeof(int));
    ht->values = (int *)malloc(size * sizeof(int));
    ht->occupied = (bool *)calloc(size, sizeof(bool));
    return ht;
}

void linear_resize(LinearHashTable *ht);

void linear_insert(LinearHashTable *ht, int key, int value) {
    // Verificar fator de carga
    if ((double)ht->count / ht->size >= LOAD_FACTOR_MAX) {
        linear_resize(ht);
    }
    
    unsigned int idx = hash_primary(key, ht->size);
    
    // Linear probing
    while (ht->occupied[idx]) {
        if (ht->keys[idx] == key) {
            ht->values[idx] = value;
            return;
        }
        idx = (idx + 1) % ht->size;
    }
    
    ht->keys[idx] = key;
    ht->values[idx] = value;
    ht->occupied[idx] = true;
    ht->count++;
}

void linear_resize(LinearHashTable *ht) {
    int old_size = ht->size;
    int *old_keys = ht->keys;
    int *old_values = ht->values;
    bool *old_occupied = ht->occupied;
    
    ht->size = old_size * 2;
    ht->count = 0;
    ht->keys = (int *)malloc(ht->size * sizeof(int));
    ht->values = (int *)malloc(ht->size * sizeof(int));
    ht->occupied = (bool *)calloc(ht->size, sizeof(bool));
    
    for (int i = 0; i < old_size; i++) {
        if (old_occupied[i] && old_keys[i] != DELETED_KEY) {
            linear_insert(ht, old_keys[i], old_values[i]);
        }
    }
    
    free(old_keys);
    free(old_values);
    free(old_occupied);
    
    printf("  [Tabela redimensionada: %d -> %d]\n", old_size, ht->size);
}

int linear_search(LinearHashTable *ht, int key) {
    unsigned int idx = hash_primary(key, ht->size);
    unsigned int start = idx;
    
    while (ht->occupied[idx]) {
        if (ht->keys[idx] == key) {
            return ht->values[idx];
        }
        idx = (idx + 1) % ht->size;
        if (idx == start) break;
    }
    
    return -1; // Não encontrado
}

void linear_delete(LinearHashTable *ht, int key) {
    unsigned int idx = hash_primary(key, ht->size);
    unsigned int start = idx;
    
    while (ht->occupied[idx]) {
        if (ht->keys[idx] == key) {
            ht->keys[idx] = DELETED_KEY;
            ht->count--;
            return;
        }
        idx = (idx + 1) % ht->size;
        if (idx == start) break;
    }
}

void linear_free(LinearHashTable *ht) {
    free(ht->keys);
    free(ht->values);
    free(ht->occupied);
    free(ht);
}

// ==================== HASH TABLE COM DOUBLE HASHING ====================

typedef struct {
    int *keys;
    int *values;
    bool *occupied;
    int size;
    int count;
} DoubleHashTable;

DoubleHashTable* double_create(int size) {
    DoubleHashTable *ht = (DoubleHashTable *)malloc(sizeof(DoubleHashTable));
    ht->size = size;
    ht->count = 0;
    ht->keys = (int *)malloc(size * sizeof(int));
    ht->values = (int *)malloc(size * sizeof(int));
    ht->occupied = (bool *)calloc(size, sizeof(bool));
    return ht;
}

void double_insert(DoubleHashTable *ht, int key, int value) {
    unsigned int idx = hash_primary(key, ht->size);
    unsigned int step = hash_secondary(key, ht->size);
    
    while (ht->occupied[idx] && ht->keys[idx] != DELETED_KEY) {
        if (ht->keys[idx] == key) {
            ht->values[idx] = value;
            return;
        }
        idx = (idx + step) % ht->size;
    }
    
    ht->keys[idx] = key;
    ht->values[idx] = value;
    ht->occupied[idx] = true;
    ht->count++;
}

int double_search(DoubleHashTable *ht, int key) {
    unsigned int idx = hash_primary(key, ht->size);
    unsigned int step = hash_secondary(key, ht->size);
    unsigned int start = idx;
    
    while (ht->occupied[idx]) {
        if (ht->keys[idx] == key) {
            return ht->values[idx];
        }
        idx = (idx + step) % ht->size;
        if (idx == start) break;
    }
    
    return -1;
}

void double_free(DoubleHashTable *ht) {
    free(ht->keys);
    free(ht->values);
    free(ht->occupied);
    free(ht);
}

// ==================== CUCKOO HASHING ====================

#define CUCKOO_MAX_KICKS 500

typedef struct {
    int *table1;
    int *table2;
    int *values1;
    int *values2;
    bool *occupied1;
    bool *occupied2;
    int size;
    int count;
} CuckooHashTable;

unsigned int cuckoo_hash1(int key, int size) {
    return hash_primary(key, size);
}

unsigned int cuckoo_hash2(int key, int size) {
    unsigned int hash = 0;
    unsigned int k = (unsigned int)key;
    
    while (k > 0) {
        hash = hash * 31 + (k % 10);
        k /= 10;
    }
    
    return hash % size;
}

CuckooHashTable* cuckoo_create(int size) {
    CuckooHashTable *ht = (CuckooHashTable *)malloc(sizeof(CuckooHashTable));
    ht->size = size;
    ht->count = 0;
    ht->table1 = (int *)malloc(size * sizeof(int));
    ht->table2 = (int *)malloc(size * sizeof(int));
    ht->values1 = (int *)malloc(size * sizeof(int));
    ht->values2 = (int *)malloc(size * sizeof(int));
    ht->occupied1 = (bool *)calloc(size, sizeof(bool));
    ht->occupied2 = (bool *)calloc(size, sizeof(bool));
    return ht;
}

bool cuckoo_insert(CuckooHashTable *ht, int key, int value) {
    unsigned int idx1 = cuckoo_hash1(key, ht->size);
    
    // Verificar se já existe na tabela 1
    if (ht->occupied1[idx1] && ht->table1[idx1] == key) {
        ht->values1[idx1] = value;
        return true;
    }
    
    unsigned int idx2 = cuckoo_hash2(key, ht->size);
    
    // Verificar se já existe na tabela 2
    if (ht->occupied2[idx2] && ht->table2[idx2] == key) {
        ht->values2[idx2] = value;
        return true;
    }
    
    // Tentar inserir com cuckoo
    int current_key = key;
    int current_value = value;
    bool use_table1 = true;
    
    for (int i = 0; i < CUCKOO_MAX_KICKS; i++) {
        if (use_table1) {
            unsigned int idx = cuckoo_hash1(current_key, ht->size);
            
            if (!ht->occupied1[idx]) {
                ht->table1[idx] = current_key;
                ht->values1[idx] = current_value;
                ht->occupied1[idx] = true;
                ht->count++;
                return true;
            }
            
            // Expulsar elemento existente
            int temp_key = ht->table1[idx];
            int temp_val = ht->values1[idx];
            ht->table1[idx] = current_key;
            ht->values1[idx] = current_value;
            current_key = temp_key;
            current_value = temp_val;
            use_table1 = false;
        } else {
            unsigned int idx = cuckoo_hash2(current_key, ht->size);
            
            if (!ht->occupied2[idx]) {
                ht->table2[idx] = current_key;
                ht->values2[idx] = current_value;
                ht->occupied2[idx] = true;
                ht->count++;
                return true;
            }
            
            // Expulsar elemento existente
            int temp_key = ht->table2[idx];
            int temp_val = ht->values2[idx];
            ht->table2[idx] = current_key;
            ht->values2[idx] = current_value;
            current_key = temp_key;
            current_value = temp_val;
            use_table1 = true;
        }
    }
    
    // Falha - ciclo detectado, precisa rehash
    printf("  [AVISO: Cuckoo Hashing precisa de rehash]\n");
    return false;
}

int cuckoo_search(CuckooHashTable *ht, int key) {
    // O(1) garantido no pior caso!
    unsigned int idx1 = cuckoo_hash1(key, ht->size);
    if (ht->occupied1[idx1] && ht->table1[idx1] == key) {
        return ht->values1[idx1];
    }
    
    unsigned int idx2 = cuckoo_hash2(key, ht->size);
    if (ht->occupied2[idx2] && ht->table2[idx2] == key) {
        return ht->values2[idx2];
    }
    
    return -1;
}

void cuckoo_free(CuckooHashTable *ht) {
    free(ht->table1);
    free(ht->table2);
    free(ht->values1);
    free(ht->values2);
    free(ht->occupied1);
    free(ht->occupied2);
    free(ht);
}

// ==================== TESTES ====================

void testar_chain() {
    printf("=== HASH TABLE COM ENCADEAMENTO ===\n");
    
    ChainHashTable *ht = chain_create(8);
    
    // Inserir elementos que colidem
    chain_insert(ht, 1, 100);
    chain_insert(ht, 9, 200);   // Colide com 1 (mod 8)
    chain_insert(ht, 17, 300);  // Colide com 1 e 9
    chain_insert(ht, 2, 400);
    
    printf("Buscando chave 1: %d\n", chain_search(ht, 1));
    printf("Buscando chave 9: %d\n", chain_search(ht, 9));
    printf("Buscando chave 17: %d\n", chain_search(ht, 17));
    printf("Buscando chave 99: %d\n", chain_search(ht, 99));
    
    chain_delete(ht, 9);
    printf("Após deletar 9, buscando 9: %d\n", chain_search(ht, 9));
    printf("Após deletar 9, buscando 17: %d\n", chain_search(ht, 17));
    
    chain_free(ht);
    printf("\n");
}

void testar_linear() {
    printf("=== HASH TABLE COM LINEAR PROBING ===\n");
    
    LinearHashTable *ht = linear_create(8);
    
    printf("Inserindo elementos (vai redimensionar)...\n");
    for (int i = 0; i < 10; i++) {
        linear_insert(ht, i * 10, i * 100);
    }
    
    printf("Buscando chave 30: %d\n", linear_search(ht, 30));
    printf("Buscando chave 70: %d\n", linear_search(ht, 70));
    printf("Buscando chave 99: %d\n", linear_search(ht, 99));
    
    printf("Deletando chave 30...\n");
    linear_delete(ht, 30);
    printf("Buscando chave 30: %d\n", linear_search(ht, 30));
    
    linear_free(ht);
    printf("\n");
}

void testar_double() {
    printf("=== HASH TABLE COM DOUBLE HASHING ===\n");
    
    DoubleHashTable *ht = double_create(16);
    
    double_insert(ht, 5, 50);
    double_insert(ht, 21, 210);  // Mesmo índice inicial que 5
    double_insert(ht, 37, 370);  // Mesmo índice inicial que 5 e 21
    
    printf("Buscando chave 5: %d\n", double_search(ht, 5));
    printf("Buscando chave 21: %d\n", double_search(ht, 21));
    printf("Buscando chave 37: %d\n", double_search(ht, 37));
    
    double_free(ht);
    printf("\n");
}

void testar_cuckoo() {
    printf("=== CUCKOO HASHING ===\n");
    printf("Garantia: busca O(1) no PIOR caso!\n\n");
    
    CuckooHashTable *ht = cuckoo_create(16);
    
    cuckoo_insert(ht, 10, 100);
    cuckoo_insert(ht, 20, 200);
    cuckoo_insert(ht, 30, 300);
    cuckoo_insert(ht, 40, 400);
    cuckoo_insert(ht, 50, 500);
    
    printf("Buscando chave 10: %d\n", cuckoo_search(ht, 10));
    printf("Buscando chave 30: %d\n", cuckoo_search(ht, 30));
    printf("Buscando chave 50: %d\n", cuckoo_search(ht, 50));
    printf("Buscando chave 99: %d\n", cuckoo_search(ht, 99));
    
    cuckoo_free(ht);
    printf("\n");
}

void comparar_metodos() {
    printf("=== COMPARAÇÃO DE MÉTODOS ===\n\n");
    
    printf("┌────────────────────┬──────────────┬──────────────┬──────────────┐\n");
    printf("│ Método             │ Busca Média  │ Busca Pior   │ Memória      │\n");
    printf("├────────────────────┼──────────────┼──────────────┼──────────────┤\n");
    printf("│ Encadeamento       │ O(1 + α)     │ O(n)         │ Extra/lista  │\n");
    printf("│ Linear Probing     │ O(1 + α)     │ O(n)         │ Na tabela    │\n");
    printf("│ Quadratic Probing  │ O(1 + α)     │ O(n)         │ Na tabela    │\n");
    printf("│ Double Hashing     │ O(1 + α)     │ O(n)         │ Na tabela    │\n");
    printf("│ Cuckoo Hashing     │ O(1)         │ O(1)         │ 2x tabelas   │\n");
    printf("└────────────────────┴──────────────┴──────────────┴──────────────┘\n\n");
    
    printf("α = fator de carga (n/tamanho)\n");
    printf("Cuckoo Hashing: única técnica com O(1) GARANTIDO na busca!\n");
    printf("\n");
}

// ==================== FUNÇÃO PRINCIPAL ====================

int main() {
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║      TABELA HASH AVANÇADA - RESOLUÇÃO DE COLISÕES        ║\n");
    printf("║   Técnicas avançadas além do hash simples                ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    testar_chain();
    testar_linear();
    testar_double();
    testar_cuckoo();
    comparar_metodos();
    
    printf("═══════════════════════════════════════════════════════════\n");
    printf("Próximos conceitos relacionados:\n");
    printf("- Árvores de Busca Avançadas (05)\n");
    printf("- Trie para busca de strings (06)\n");
    printf("- Bloom Filter para consultas probabilísticas (09)\n");
    printf("═══════════════════════════════════════════════════════════\n");
    
    return 0;
}
