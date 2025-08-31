/*
 * ====================================================================
 * IMPLEMENTAÇÃO DE TABELA HASH COM ENCADEAMENTO (Hash Table with Chaining)
 * ====================================================================
 * 
 * Descrição:
 * Uma tabela hash é uma estrutura de dados que mapeia chaves para valores
 * usando uma função de hash. Esta implementação usa encadeamento para
 * resolver colisões, onde cada posição da tabela aponta para uma lista
 * ligada contendo todos os elementos que mapeiam para esse índice.
 * 
 * Complexidade das operações (caso médio):
 * - Inserção: O(1)
 * - Busca: O(1)
 * - Remoção: O(1)
 * - Pior caso: O(n) quando muitas colisões ocorrem
 * 
 * Características desta implementação:
 * - Resolve colisões usando encadeamento (chaining)
 * - Suporta chaves string e valores inteiros
 * - Função hash baseada em multiplicação e módulo
 * - Redimensionamento automático não implementado (versão básica)
 * 
 * Vantagens do encadeamento:
 * - Simples de implementar
 * - Nunca fica "cheio" (pode crescer dinamicamente)
 * - Performance degrada graciosamente
 * 
 * Aplicações:
 * - Implementação de dicionários/mapas
 * - Cache de dados
 * - Indexação de bancos de dados
 * - Compiladores (tabela de símbolos)
 * 
 * Autor: Estrutura de Dados em C
 * Data: 2024
 * ====================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 101  // Número primo para melhor distribuição hash

/**
 * Estrutura para um item da tabela hash
 * Cada item representa um par chave-valor em uma lista ligada
 * @param key: string chave para identificação
 * @param value: valor inteiro associado à chave
 * @param next: ponteiro para o próximo item (para resolver colisões)
 */
typedef struct HashItem {
    char* key;
    int value;
    struct HashItem* next;
} HashItem;

/**
 * Estrutura da tabela hash
 * @param items: array de ponteiros para as listas de itens
 * @param size: tamanho da tabela (número de slots)
 * @param count: número total de elementos na tabela
 */
typedef struct HashTable {
    HashItem** items;
    int size;
    int count;
} HashTable;

/**
 * Função hash usando o método da multiplicação com constante 31
 * A constante 31 é escolhida por ser prima e produzir boa distribuição
 * @param key: string chave para calcular o hash
 * @return: índice da tabela hash (0 a TABLE_SIZE-1)
 */
unsigned int hash_function(const char* key) {
    unsigned int hash = 0;
    // Percorre cada caractere da string
    for (int i = 0; key[i] != '\0'; i++) {
        // Formula: hash = (hash * 31 + char) % TABLE_SIZE
        hash = (hash * 31 + key[i]) % TABLE_SIZE;
    }
    return hash;
}

/**
 * Cria uma nova tabela hash vazia
 * @return: ponteiro para a tabela hash criada
 */
HashTable* create_hash_table() {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (table == NULL) {
        printf("Erro: Falha na alocação de memória para a tabela\n");
        exit(1);
    }
    
    // Alocar array de ponteiros e inicializar com NULL
    table->items = (HashItem**)calloc(TABLE_SIZE, sizeof(HashItem*));
    if (table->items == NULL) {
        printf("Erro: Falha na alocação de memória para os itens\n");
        free(table);
        exit(1);
    }
    
    table->size = TABLE_SIZE;
    table->count = 0;
    return table;
}

/**
 * Cria um novo item para a tabela hash
 * @param key: string chave (será copiada)
 * @param value: valor inteiro associado
 * @return: ponteiro para o item criado
 */
HashItem* create_item(const char* key, int value) {
    HashItem* item = (HashItem*)malloc(sizeof(HashItem));
    if (item == NULL) {
        printf("Erro: Falha na alocação de memória para o item\n");
        exit(1);
    }
    
    // Alocar e copiar a chave
    item->key = (char*)malloc(strlen(key) + 1);
    if (item->key == NULL) {
        printf("Erro: Falha na alocação de memória para a chave\n");
        free(item);
        exit(1);
    }
    
    strcpy(item->key, key);
    item->value = value;
    item->next = NULL;
    return item;
}

/**
 * Insere ou atualiza um par chave-valor na tabela hash
 * @param table: ponteiro para a tabela hash
 * @param key: chave string
 * @param value: valor inteiro a ser associado
 */
void hash_insert(HashTable* table, const char* key, int value) {
    unsigned int index = hash_function(key);
    HashItem* new_item = create_item(key, value);
    
    // Caso 1: Slot vazio - inserir diretamente
    if (table->items[index] == NULL) {
        table->items[index] = new_item;
        table->count++;
        printf("✓ Inserido: (\"%s\", %d) no índice %u\n", key, value, index);
        return;
    }
    
    // Caso 2: Slot ocupado - verificar se chave já existe ou adicionar à lista
    HashItem* current = table->items[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            // Chave existe - atualizar valor
            current->value = value;
            free(new_item->key);
            free(new_item);
            printf("✓ Atualizado: (\"%s\", %d) no índice %u\n", key, value, index);
            return;
        }
        if (current->next == NULL) {
            break;
        }
        current = current->next;
    }
    
    // Adicionar no final da lista (colisão resolvida por encadeamento)
    current->next = new_item;
    table->count++;
    printf("✓ Inserido: (\"%s\", %d) no índice %u (colisão resolvida)\n", key, value, index);
}

/**
 * Busca um valor pela chave na tabela hash
 * @param table: ponteiro para a tabela hash
 * @param key: chave a ser buscada
 * @param found: ponteiro para flag indicando se foi encontrado (saída)
 * @return: valor associado à chave ou -1 se não encontrado
 */
int hash_search(HashTable* table, const char* key, int* found) {
    unsigned int index = hash_function(key);
    HashItem* current = table->items[index];
    
    // Percorrer a lista ligada no índice calculado
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            *found = 1;
            return current->value;
        }
        current = current->next;
    }
    
    // Chave não encontrada
    *found = 0;
    return -1;
}

/**
 * Remove um item da tabela hash pela chave
 * @param table: ponteiro para a tabela hash
 * @param key: chave do item a ser removido
 * @return: valor do item removido ou -1 se não encontrado
 */
int hash_delete(HashTable* table, const char* key) {
    unsigned int index = hash_function(key);
    HashItem* current = table->items[index];
    HashItem* prev = NULL;
    
    // Buscar o item na lista ligada
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            // Item encontrado - remover da lista
            if (prev == NULL) {
                // Primeiro item da lista - atualizar ponteiro da tabela
                table->items[index] = current->next;
            } else {
                // Item no meio/fim da lista - atualizar ponteiro anterior
                prev->next = current->next;
            }
            
            // Liberar memória e retornar valor
            int value = current->value;
            free(current->key);
            free(current);
            table->count--;
            
            printf("✓ Removido: (\"%s\", %d) do índice %u\n", key, value, index);
            return value;
        }
        prev = current;
        current = current->next;
    }
    
    printf("✗ Chave \"%s\" não encontrada para remoção\n", key);
    return -1; // Não encontrado
}

/**
 * Libera toda a memória alocada para a tabela hash
 * @param table: ponteiro para a tabela hash a ser destruída
 */
void destroy_hash_table(HashTable* table) {
    if (table == NULL) return;
    
    // Liberar todos os itens em cada slot da tabela
    for (int i = 0; i < table->size; i++) {
        HashItem* current = table->items[i];
        while (current != NULL) {
            HashItem* temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
    
    // Liberar a tabela
    free(table->items);
    free(table);
}

/**
 * Imprime o conteúdo completo da tabela hash
 * Mostra a distribuição dos elementos e possíveis colisões
 * @param table: ponteiro para a tabela hash
 */
void print_hash_table(HashTable* table) {
    printf("=== CONTEÚDO DA TABELA HASH ===\n");
    printf("Total de elementos: %d\n", table->count);
    printf("Tamanho da tabela: %d\n", table->size);
    printf("Fator de carga: %.2f\n\n", (float)table->count / table->size);
    
    int occupied_slots = 0;
    int max_chain_length = 0;
    
    for (int i = 0; i < table->size; i++) {
        if (table->items[i] != NULL) {
            occupied_slots++;
            printf("Índice %3d: ", i);
            
            HashItem* current = table->items[i];
            int chain_length = 0;
            
            while (current != NULL) {
                printf("(\"%s\", %d)", current->key, current->value);
                if (current->next != NULL) {
                    printf(" -> ");
                }
                current = current->next;
                chain_length++;
            }
            printf("\n");
            
            if (chain_length > max_chain_length) {
                max_chain_length = chain_length;
            }
        }
    }
    
    printf("\nEstatísticas:\n");
    printf("- Slots ocupados: %d/%d (%.1f%%)\n", 
           occupied_slots, table->size, 
           (float)occupied_slots / table->size * 100);
    printf("- Maior cadeia: %d elementos\n", max_chain_length);
    printf("- Eficiência: %s\n", 
           max_chain_length <= 3 ? "Boa" : "Considere redimensionar");
}

/**
 * Função principal demonstrando o uso da tabela hash
 * Testa inserção, busca, atualização e remoção
 */
int main() {
    printf("=== DEMONSTRAÇÃO DE TABELA HASH COM ENCADEAMENTO ===\n\n");
    
    // Criar tabela hash
    HashTable* table = create_hash_table();
    printf("✓ Tabela hash criada com %d slots\n\n", TABLE_SIZE);
    
    // Inserir vários items para demonstrar funcionalidade
    printf("=== INSERINDO ELEMENTOS ===\n");
    hash_insert(table, "apple", 10);
    hash_insert(table, "banana", 20);
    hash_insert(table, "orange", 30);
    hash_insert(table, "grape", 40);
    hash_insert(table, "kiwi", 50);
    hash_insert(table, "mango", 60);
    
    printf("\n");
    print_hash_table(table);
    
    // Testar busca
    printf("\n=== TESTE DE BUSCA ===\n");
    int found;
    int value;
    
    value = hash_search(table, "banana", &found);
    if (found) {
        printf("✓ Encontrado: \"banana\" = %d\n", value);
    }
    
    value = hash_search(table, "grape", &found);
    if (found) {
        printf("✓ Encontrado: \"grape\" = %d\n", value);
    }
    
    value = hash_search(table, "pineapple", &found);
    if (!found) {
        printf("✗ \"pineapple\" não encontrado na tabela\n");
    }
    
    // Testar atualização
    printf("\n=== TESTE DE ATUALIZAÇÃO ===\n");
    hash_insert(table, "apple", 15); // Atualizar valor existente
    
    // Testar remoção
    printf("\n=== TESTE DE REMOÇÃO ===\n");
    value = hash_delete(table, "orange");
    if (value != -1) {
        printf("Valor removido: %d\n", value);
    }
    
    hash_delete(table, "nonexistent"); // Tentar remover chave inexistente
    
    printf("\n=== ESTADO FINAL DA TABELA ===\n");
    print_hash_table(table);
    
    // Demonstrar colisões inserindo mais elementos
    printf("\n=== TESTANDO COLISÕES ===\n");
    printf("Inserindo mais elementos para demonstrar colisões...\n");
    hash_insert(table, "strawberry", 70);
    hash_insert(table, "blueberry", 80);
    hash_insert(table, "raspberry", 90);
    
    printf("\n");
    print_hash_table(table);
    
    // Limpeza
    destroy_hash_table(table);
    printf("\n✓ Memória liberada com sucesso!\n");
    
    return 0;
}