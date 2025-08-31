#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 101  // Número primo para melhor distribuição

// Estrutura para um item da tabela hash
typedef struct HashItem {
    char* key;
    int value;
    struct HashItem* next;
} HashItem;

// Estrutura da tabela hash
typedef struct HashTable {
    HashItem** items;
    int size;
    int count;
} HashTable;

// Função hash simples (método da divisão)
unsigned int hash_function(const char* key) {
    unsigned int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash = (hash * 31 + key[i]) % TABLE_SIZE;
    }
    return hash;
}

// Criar uma nova tabela hash
HashTable* create_hash_table() {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->items = (HashItem**)calloc(TABLE_SIZE, sizeof(HashItem*));
    table->size = TABLE_SIZE;
    table->count = 0;
    return table;
}

// Criar um novo item
HashItem* create_item(const char* key, int value) {
    HashItem* item = (HashItem*)malloc(sizeof(HashItem));
    item->key = (char*)malloc(strlen(key) + 1);
    strcpy(item->key, key);
    item->value = value;
    item->next = NULL;
    return item;
}

// Inserir item na tabela hash
void hash_insert(HashTable* table, const char* key, int value) {
    unsigned int index = hash_function(key);
    HashItem* new_item = create_item(key, value);
    
    // Se não há item nesta posição
    if (table->items[index] == NULL) {
        table->items[index] = new_item;
        table->count++;
        return;
    }
    
    // Verificar se a chave já existe
    HashItem* current = table->items[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            // Atualizar valor existente
            current->value = value;
            free(new_item->key);
            free(new_item);
            return;
        }
        if (current->next == NULL) {
            break;
        }
        current = current->next;
    }
    
    // Adicionar no final da lista (encadeamento)
    current->next = new_item;
    table->count++;
}

// Buscar item na tabela hash
int hash_search(HashTable* table, const char* key, int* found) {
    unsigned int index = hash_function(key);
    HashItem* current = table->items[index];
    
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            *found = 1;
            return current->value;
        }
        current = current->next;
    }
    
    *found = 0;
    return -1;
}

// Remover item da tabela hash
int hash_delete(HashTable* table, const char* key) {
    unsigned int index = hash_function(key);
    HashItem* current = table->items[index];
    HashItem* prev = NULL;
    
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (prev == NULL) {
                // Primeiro item da lista
                table->items[index] = current->next;
            } else {
                prev->next = current->next;
            }
            
            int value = current->value;
            free(current->key);
            free(current);
            table->count--;
            return value;
        }
        prev = current;
        current = current->next;
    }
    
    return -1; // Não encontrado
}

// Destruir tabela hash
void destroy_hash_table(HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        HashItem* current = table->items[i];
        while (current != NULL) {
            HashItem* temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
    free(table->items);
    free(table);
}

// Imprimir tabela hash
void print_hash_table(HashTable* table) {
    printf("Hash Table contents:\n");
    for (int i = 0; i < table->size; i++) {
        if (table->items[i] != NULL) {
            printf("Index %d: ", i);
            HashItem* current = table->items[i];
            while (current != NULL) {
                printf("(%s, %d)", current->key, current->value);
                if (current->next != NULL) {
                    printf(" -> ");
                }
                current = current->next;
            }
            printf("\n");
        }
    }
    printf("Total items: %d\n", table->count);
}

int main() {
    HashTable* table = create_hash_table();
    
    // Inserir alguns items
    hash_insert(table, "apple", 10);
    hash_insert(table, "banana", 20);
    hash_insert(table, "orange", 30);
    hash_insert(table, "grape", 40);
    
    print_hash_table(table);
    
    // Buscar items
    int found;
    int value = hash_search(table, "banana", &found);
    if (found) {
        printf("Encontrado: banana = %d\n", value);
    }
    
    value = hash_search(table, "kiwi", &found);
    if (!found) {
        printf("kiwi não encontrado\n");
    }
    
    // Remover item
    value = hash_delete(table, "orange");
    if (value != -1) {
        printf("Removido: orange = %d\n", value);
    }
    
    printf("\nApós remoção:\n");
    print_hash_table(table);
    
    destroy_hash_table(table);
    return 0;
}