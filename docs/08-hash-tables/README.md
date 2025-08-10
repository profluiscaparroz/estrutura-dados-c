# Tabelas Hash (Hash Tables) em C

## 📚 Introdução às Tabelas Hash

As **tabelas hash** (ou hash tables) são uma das estruturas de dados mais importantes e eficientes da ciência da computação. Elas permitem armazenar e recuperar dados em tempo médio **O(1)**, tornando-as ideais para operações de busca, inserção e remoção extremamente rápidas.

Uma tabela hash funciona usando uma **função de hash** para mapear chaves (keys) para índices em um array, permitindo acesso direto aos dados sem necessidade de busca sequencial.

---

## 🧮 Conceitos Fundamentais

### Função Hash

Uma **função hash** é uma função matemática que mapeia chaves de tamanho arbitrário para valores de tamanho fixo (normalmente índices de um array).

**Propriedades desejáveis:**
- **Determinística**: a mesma chave sempre produz o mesmo valor hash
- **Uniforme**: distribui as chaves uniformemente pelo espaço de hash
- **Eficiente**: cálculo rápido
- **Sensível**: pequenas mudanças na chave resultam em grandes mudanças no hash

### Colisões

**Colisões** ocorrem quando duas chaves diferentes produzem o mesmo valor hash. Existem duas estratégias principais para lidar com colisões:

1. **Encadeamento (Chaining)**: cada posição da tabela aponta para uma lista ligada
2. **Endereçamento Aberto (Open Addressing)**: busca uma nova posição na própria tabela

---

## 💻 Implementações Práticas em C

### 🔗 Hash Table com Encadeamento

```c
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
```

### 🎯 Hash Table com Endereçamento Aberto

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 23
#define DELETED_KEY "__DELETED__"

// Item da tabela hash
typedef struct {
    char* key;
    int value;
    int is_deleted;
} HashEntry;

// Tabela hash
typedef struct {
    HashEntry* entries[TABLE_SIZE];
    int count;
} HashTableOpen;

// Função hash
unsigned int hash_open(const char* key) {
    unsigned int hash = 5381;
    for (int i = 0; key[i] != '\0'; i++) {
        hash = ((hash << 5) + hash) + key[i];
    }
    return hash % TABLE_SIZE;
}

// Inserir com linear probing
void hash_insert_open(HashTableOpen* table, const char* key, int value) {
    if (table->count >= TABLE_SIZE * 0.7) { // Fator de carga máximo
        printf("Tabela quase cheia! Considere redimensionar.\n");
        return;
    }
    
    unsigned int index = hash_open(key);
    unsigned int original_index = index;
    
    do {
        if (table->entries[index] == NULL || table->entries[index]->is_deleted) {
            // Posição livre encontrada
            if (table->entries[index] != NULL && table->entries[index]->is_deleted) {
                free(table->entries[index]->key);
                free(table->entries[index]);
            }
            table->entries[index] = create_entry(key, value);
            table->count++;
            return;
        }
        
        if (strcmp(table->entries[index]->key, key) == 0) {
            // Chave já existe, atualizar valor
            table->entries[index]->value = value;
            table->entries[index]->is_deleted = 0;
            return;
        }
        
        index = (index + 1) % TABLE_SIZE; // Linear probing
    } while (index != original_index);
    
    printf("Tabela cheia!\n");
}
```

---

## 📊 Análise de Performance

### Complexidade Temporal

| Operação | Melhor Caso | Caso Médio | Pior Caso |
|----------|-------------|------------|-----------|
| Busca    | O(1)        | O(1)       | O(n)      |
| Inserção | O(1)        | O(1)       | O(n)      |
| Remoção  | O(1)        | O(1)       | O(n)      |

### Fatores que Afetam a Performance

1. **Qualidade da Função Hash**: Uma boa distribuição reduz colisões
2. **Fator de Carga**: Proporção entre elementos e tamanho da tabela
3. **Estratégia de Resolução de Colisões**: Encadeamento vs. endereçamento aberto
4. **Tamanho da Tabela**: Números primos geralmente oferecem melhor distribuição

---

## 🎯 Aplicações Práticas

- **Caches**: Armazenamento rápido de dados frequentemente acessados
- **Bancos de Dados**: Índices para busca rápida
- **Compiladores**: Tabelas de símbolos
- **Sistemas Operacionais**: Gerenciamento de recursos
- **Criptografia**: Verificação de integridade (hashes criptográficos)
- **Redes**: Roteamento e armazenamento de sessões

---

## 🔧 Considerações de Implementação

### Escolha do Tamanho da Tabela
- Use números primos para melhor distribuição
- Considere redimensionamento dinâmico quando o fator de carga exceder 0.75

### Gerenciamento de Memória
- Libere adequadamente a memória das chaves e valores
- Use técnicas como copy-on-write para otimização

### Tratamento de Colisões
- **Encadeamento**: Melhor para alta densidade de dados
- **Endereçamento Aberto**: Melhor cache locality, mas requer cuidado com deleções

---

As tabelas hash são fundamentais na programação moderna, oferecendo acesso extremamente rápido aos dados. Sua implementação eficiente requer compreensão profunda de funções hash, resolução de colisões e gerenciamento de memória, tornando-as uma ferramenta poderosa para desenvolvedores em C.