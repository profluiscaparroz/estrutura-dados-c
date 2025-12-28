# Tabelas Hash (Hash Tables)

## 📋 Visão Geral

Este diretório contém implementação completa de tabela hash em C, uma das estruturas de dados mais importantes e amplamente utilizadas para busca, inserção e remoção em tempo constante médio.

## 📚 Arquivos Incluídos

- **hash_table.c** - Implementação completa da tabela hash
- **hash/** - Diretório com implementações de funções hash
- **hash_test** - Binário executável para testes
- **Makefile** - Automação de compilação e testes

## 🎯 O que é uma Tabela Hash?

Uma **tabela hash** (ou hash map) é uma estrutura de dados que mapeia chaves a valores usando uma **função hash** para computar um índice em um array onde o valor é armazenado.

### Conceitos Fundamentais

**Função Hash**: `h(key) → index`
- Transforma chave em índice do array
- Deve ser determinística
- Distribuição uniforme ideal

**Colisões**: Quando duas chaves mapeiam para o mesmo índice
- **Chaining**: Lista encadeada em cada posição
- **Open Addressing**: Procurar próxima posição livre

## 📊 Complexidade das Operações

### Caso Médio (Boa função hash)

| Operação | Chaining | Open Addressing |
|----------|----------|-----------------|
| **Busca** | O(1) | O(1) |
| **Inserção** | O(1) | O(1) |
| **Remoção** | O(1) | O(1) |
| **Espaço** | O(n) | O(n) |

### Pior Caso (Todas colisões)

| Operação | Chaining | Open Addressing |
|----------|----------|-----------------|
| **Busca** | O(n) | O(n) |
| **Inserção** | O(n) | O(n) |
| **Remoção** | O(n) | O(n) |

**Nota**: Pior caso é raro com boa função hash e load factor adequado.

## 💡 Estrutura de Dados

### Com Chaining

```c
typedef struct Entry {
    char *key;
    int value;
    struct Entry *next;  // Para colisões
} Entry;

typedef struct {
    Entry **buckets;     // Array de ponteiros
    int size;            // Tamanho da tabela
    int count;           // Número de elementos
} HashTable;
```

### Com Open Addressing

```c
typedef struct {
    char *key;
    int value;
    int is_occupied;
    int is_deleted;      // Para lazy deletion
} Entry;

typedef struct {
    Entry *entries;
    int size;
    int count;
} HashTable;
```

## 🔧 Implementação Básica (Chaining)

### 1. Criar Tabela

```c
HashTable* create_hash_table(int size) {
    HashTable *table = (HashTable*)malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->buckets = (Entry**)calloc(size, sizeof(Entry*));
    return table;
}
```

### 2. Função Hash

```c
// Hash simples (djb2)
unsigned long hash(const char *str) {
    unsigned long hash = 5381;
    int c;
    
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }
    
    return hash;
}

// Obter índice
int get_index(HashTable *table, const char *key) {
    return hash(key) % table->size;
}
```

### 3. Inserir

```c
void insert(HashTable *table, const char *key, int value) {
    int index = get_index(table, key);
    
    // Verificar se chave já existe
    Entry *entry = table->buckets[index];
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            entry->value = value;  // Atualizar
            return;
        }
        entry = entry->next;
    }
    
    // Criar nova entrada
    Entry *new_entry = (Entry*)malloc(sizeof(Entry));
    new_entry->key = strdup(key);
    new_entry->value = value;
    new_entry->next = table->buckets[index];
    table->buckets[index] = new_entry;
    table->count++;
    
    // Verificar load factor e redimensionar se necessário
    if ((float)table->count / table->size > 0.75) {
        resize_table(table);
    }
}
```

### 4. Buscar

```c
int search(HashTable *table, const char *key, int *value) {
    int index = get_index(table, key);
    Entry *entry = table->buckets[index];
    
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            *value = entry->value;
            return 1;  // Encontrado
        }
        entry = entry->next;
    }
    
    return 0;  // Não encontrado
}
```

### 5. Remover

```c
int delete(HashTable *table, const char *key) {
    int index = get_index(table, key);
    Entry *entry = table->buckets[index];
    Entry *prev = NULL;
    
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            if (prev == NULL) {
                table->buckets[index] = entry->next;
            } else {
                prev->next = entry->next;
            }
            
            free(entry->key);
            free(entry);
            table->count--;
            return 1;
        }
        prev = entry;
        entry = entry->next;
    }
    
    return 0;  // Não encontrado
}
```

## 🔍 Funções Hash Comuns

### 1. DJB2 (Daniel J. Bernstein)
```c
unsigned long djb2(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}
```

### 2. FNV-1a (Fowler-Noll-Vo)
```c
unsigned long fnv1a(const char *str) {
    unsigned long hash = 2166136261u;
    while (*str) {
        hash ^= (unsigned char)(*str++);
        hash *= 16777619;
    }
    return hash;
}
```

### 3. MurmurHash (Para uso geral)
Mais complexa, excelente distribuição.

### 4. CRC32 (Para checksums)
Boa para detecção de erros.

## ⚖️ Load Factor

**Load Factor** = `count / size`

- **< 0.5**: Baixa ocupação, desperdício de espaço
- **0.5 - 0.75**: Ideal para chaining
- **> 0.75**: Muitas colisões, considerar redimensionamento
- **Open Addressing**: Manter < 0.7 para performance

### Redimensionamento

```c
void resize_table(HashTable *table) {
    int old_size = table->size;
    int new_size = old_size * 2;
    Entry **old_buckets = table->buckets;
    
    // Criar nova tabela
    table->size = new_size;
    table->count = 0;
    table->buckets = (Entry**)calloc(new_size, sizeof(Entry*));
    
    // Reinserir elementos
    for (int i = 0; i < old_size; i++) {
        Entry *entry = old_buckets[i];
        while (entry != NULL) {
            insert(table, entry->key, entry->value);
            Entry *temp = entry;
            entry = entry->next;
            free(temp->key);
            free(temp);
        }
    }
    
    free(old_buckets);
}
```

## 🔧 Compilação

### Usando Makefile

```bash
make              # Compilar
make test         # Executar testes
make clean        # Limpar
```

### Manual

```bash
gcc -Wall -Wextra -std=c99 -o hash hash_table.c
./hash
```

## 📖 Técnicas de Resolução de Colisões

### 1. Chaining (Encadeamento)

**Vantagens:**
- Simples de implementar
- Nunca fica "cheia"
- Remoção fácil

**Desvantagens:**
- Uso extra de memória para ponteiros
- Cache locality ruim

### 2. Open Addressing

#### Linear Probing
```c
// Se h(k) ocupado, tenta h(k)+1, h(k)+2, ...
index = (hash(key) + i) % size;
```

**Vantagens:** Cache locality excelente  
**Desvantagens:** Clustering primário

#### Quadratic Probing
```c
// Tenta h(k)+1², h(k)+2², h(k)+3², ...
index = (hash(key) + i*i) % size;
```

**Vantagens:** Reduz clustering primário  
**Desvantagens:** Clustering secundário

#### Double Hashing
```c
// Usa segunda função hash
index = (h1(key) + i * h2(key)) % size;
```

**Vantagens:** Melhor distribuição  
**Desvantagens:** Duas funções hash

## 💡 Aplicações Práticas

### 1. Cache/Memoization
```c
// Armazenar resultados de computações caras
int fibonacci_cached(int n, HashTable *cache) {
    int result;
    if (search(cache, &n, &result)) {
        return result;
    }
    // Computar e armazenar
}
```

### 2. Contagem de Frequências
```c
void count_words(const char *text, HashTable *counts) {
    // Tokenizar e contar
    char *word = strtok(text, " ");
    while (word != NULL) {
        int count;
        if (search(counts, word, &count)) {
            insert(counts, word, count + 1);
        } else {
            insert(counts, word, 1);
        }
        word = strtok(NULL, " ");
    }
}
```

### 3. Dicionários
```c
// Mapeamento palavra → tradução
insert(dict, "hello", "olá");
insert(dict, "world", "mundo");
```

### 4. Conjuntos (Sets)
```c
// Apenas chaves, sem valores
// Verificar pertencimento em O(1)
```

### 5. Índices de Banco de Dados
Busca rápida por chave primária.

## ⚠️ Cuidados Importantes

1. **Função Hash de Qualidade**: Evitar muitas colisões
2. **Load Factor**: Redimensionar quando necessário
3. **Vazamento de Memória**: Liberar chaves e valores
4. **Thread Safety**: Usar locks para acesso concorrente
5. **Tamanho Inicial**: Escolher primo ou potência de 2

## 📚 Recursos Adicionais

- [Hash Table - Wikipedia](https://en.wikipedia.org/wiki/Hash_table)
- [Hash Functions](https://en.wikipedia.org/wiki/Hash_function)
- [Perfect Hashing](https://en.wikipedia.org/wiki/Perfect_hash_function)
- [Cuckoo Hashing](https://en.wikipedia.org/wiki/Cuckoo_hashing)

---

**Repositório**: https://github.com/profluiscaparroz/estrutura-dados-c
