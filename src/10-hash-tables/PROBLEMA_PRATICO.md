# Problema Prático: Sistema de Cache de Aplicação Web

## 📋 Descrição do Problema

Uma aplicação web precisa implementar cache para:
- Armazenar respostas de consultas ao banco de dados
- Acesso muito rápido (< 1ms)
- Invalidar cache quando dados mudam
- Limitar tamanho (política LRU - Least Recently Used)
- Estatísticas de hit/miss rate

**Por que usar Hash Table?**
- Inserção O(1) em média
- Busca O(1) em média
- Remoção O(1) em média
- Ideal para chave-valor
- Muito mais rápido que BST para acesso direto

## 🔴 Problema: Array com Busca Linear

```c
#include <stdio.h>
#include <string.h>

#define MAX_CACHE 1000

typedef struct {
    char chave[100];
    char valor[500];
    int valido;
} EntradaCache;

// PROBLEMA: Array linear - busca O(n)
EntradaCache cache[MAX_CACHE];
int total = 0;

// PROBLEMA: Busca linear muito lenta - O(n)
char* buscar(const char *chave) {
    for (int i = 0; i < total; i++) {
        if (cache[i].valido && strcmp(cache[i].chave, chave) == 0) {
            return cache[i].valor;
        }
    }
    return NULL;
}

// PROBLEMA: Sempre adiciona no final, sem verificar duplicata
void inserir(const char *chave, const char *valor) {
    if (total < MAX_CACHE) {
        strcpy(cache[total].chave, chave);
        strcpy(cache[total].valor, valor);
        cache[total].valido = 1;
        total++;
    }
}

int main() {
    inserir("user:123", "{name: 'João', age: 30}");
    inserir("user:456", "{name: 'Maria', age: 25}");
    
    // Busca lenta O(n)
    char *resultado = buscar("user:123");
    
    return 0;
}
```

### Problemas Identificados:
1. ❌ Busca O(n) - inaceitável para cache
2. ❌ Não detecta duplicatas
3. ❌ Sem política de remoção (LRU)
4. ❌ Tamanho fixo desperdiça memória
5. ❌ Sem estatísticas de performance

## ✅ Solução: Hash Table com Chaining + LRU

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define TABLE_SIZE 100
#define MAX_KEY_SIZE 100
#define MAX_VALUE_SIZE 500

// ============= ESTRUTURAS =============

// Nó da lista duplamente encadeada (para LRU)
typedef struct NoLRU {
    char chave[MAX_KEY_SIZE];
    struct NoLRU *anterior;
    struct NoLRU *proximo;
} NoLRU;

// Entrada da hash table (chaining)
typedef struct EntradaHash {
    char chave[MAX_KEY_SIZE];
    char valor[MAX_VALUE_SIZE];
    time_t timestamp;
    int acessos;
    NoLRU *noLRU;  // Ponteiro para nó na lista LRU
    struct EntradaHash *proxima;  // Chaining
} EntradaHash;

// Cache com hash table + lista LRU
typedef struct {
    EntradaHash *tabela[TABLE_SIZE];
    NoLRU *lruInicio;  // Mais recente
    NoLRU *lruFim;     // Menos recente
    int tamanho;
    int capacidadeMaxima;
    int hits;
    int misses;
} Cache;

// ============= FUNÇÃO HASH =============

// DJB2 Hash Function
unsigned long hash(const char *str) {
    unsigned long hash = 5381;
    int c;
    
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    
    return hash % TABLE_SIZE;
}

// ============= OPERAÇÕES DA LISTA LRU =============

NoLRU* criarNoLRU(const char *chave) {
    NoLRU *no = (NoLRU*)malloc(sizeof(NoLRU));
    strcpy(no->chave, chave);
    no->anterior = NULL;
    no->proximo = NULL;
    return no;
}

// Mover nó para o início (mais recente)
void moverParaInicio(Cache *cache, NoLRU *no) {
    if (no == cache->lruInicio) return;  // Já está no início
    
    // Remover da posição atual
    if (no->anterior) {
        no->anterior->proximo = no->proximo;
    }
    if (no->proximo) {
        no->proximo->anterior = no->anterior;
    }
    if (no == cache->lruFim) {
        cache->lruFim = no->anterior;
    }
    
    // Inserir no início
    no->proximo = cache->lruInicio;
    no->anterior = NULL;
    
    if (cache->lruInicio) {
        cache->lruInicio->anterior = no;
    }
    cache->lruInicio = no;
    
    if (cache->lruFim == NULL) {
        cache->lruFim = no;
    }
}

// Adicionar nó no início
void adicionarNoInicio(Cache *cache, NoLRU *no) {
    no->proximo = cache->lruInicio;
    no->anterior = NULL;
    
    if (cache->lruInicio) {
        cache->lruInicio->anterior = no;
    }
    cache->lruInicio = no;
    
    if (cache->lruFim == NULL) {
        cache->lruFim = no;
    }
}

// Remover nó da lista LRU
void removerNoLRU(Cache *cache, NoLRU *no) {
    if (no->anterior) {
        no->anterior->proximo = no->proximo;
    } else {
        cache->lruInicio = no->proximo;
    }
    
    if (no->proximo) {
        no->proximo->anterior = no->anterior;
    } else {
        cache->lruFim = no->anterior;
    }
    
    free(no);
}

// ============= OPERAÇÕES DO CACHE =============

void inicializarCache(Cache *cache, int capacidade) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        cache->tabela[i] = NULL;
    }
    cache->lruInicio = NULL;
    cache->lruFim = NULL;
    cache->tamanho = 0;
    cache->capacidadeMaxima = capacidade;
    cache->hits = 0;
    cache->misses = 0;
}

// Buscar entrada na hash table - O(1) médio
EntradaHash* buscarEntrada(Cache *cache, const char *chave) {
    unsigned long idx = hash(chave);
    EntradaHash *entrada = cache->tabela[idx];
    
    while (entrada != NULL) {
        if (strcmp(entrada->chave, chave) == 0) {
            return entrada;
        }
        entrada = entrada->proxima;
    }
    
    return NULL;
}

// Remover entrada menos recente (LRU)
void removerMenosRecente(Cache *cache) {
    if (cache->lruFim == NULL) return;
    
    char chaveRemover[MAX_KEY_SIZE];
    strcpy(chaveRemover, cache->lruFim->chave);
    
    // Encontrar na hash table
    unsigned long idx = hash(chaveRemover);
    EntradaHash *entrada = cache->tabela[idx];
    EntradaHash *anterior = NULL;
    
    while (entrada != NULL) {
        if (strcmp(entrada->chave, chaveRemover) == 0) {
            // Remover da hash table
            if (anterior) {
                anterior->proxima = entrada->proxima;
            } else {
                cache->tabela[idx] = entrada->proxima;
            }
            
            // Remover da lista LRU
            NoLRU *noRemover = entrada->noLRU;
            if (noRemover->anterior) {
                noRemover->anterior->proximo = NULL;
            }
            cache->lruFim = noRemover->anterior;
            
            printf("  🗑️  Cache cheio: removendo '%s' (LRU)\n", chaveRemover);
            
            free(noRemover);
            free(entrada);
            cache->tamanho--;
            break;
        }
        anterior = entrada;
        entrada = entrada->proxima;
    }
}

// Inserir no cache - O(1) médio
bool inserir(Cache *cache, const char *chave, const char *valor) {
    // Verificar se já existe
    EntradaHash *existente = buscarEntrada(cache, chave);
    
    if (existente) {
        // Atualizar valor
        strcpy(existente->valor, valor);
        existente->timestamp = time(NULL);
        existente->acessos++;
        
        // Mover para início da lista LRU
        moverParaInicio(cache, existente->noLRU);
        
        printf("  ♻️  Atualizando cache: '%s'\n", chave);
        return true;
    }
    
    // Verificar capacidade
    if (cache->tamanho >= cache->capacidadeMaxima) {
        removerMenosRecente(cache);
    }
    
    // Criar nova entrada
    EntradaHash *nova = (EntradaHash*)malloc(sizeof(EntradaHash));
    strcpy(nova->chave, chave);
    strcpy(nova->valor, valor);
    nova->timestamp = time(NULL);
    nova->acessos = 0;
    nova->proxima = NULL;
    
    // Criar nó LRU
    nova->noLRU = criarNoLRU(chave);
    adicionarNoInicio(cache, nova->noLRU);
    
    // Inserir na hash table (início da lista de chaining)
    unsigned long idx = hash(chave);
    nova->proxima = cache->tabela[idx];
    cache->tabela[idx] = nova;
    
    cache->tamanho++;
    
    printf("  ✓ Inserido no cache: '%s' -> '%.50s%s'\n", 
           chave, valor, strlen(valor) > 50 ? "..." : "");
    
    return true;
}

// Buscar no cache - O(1) médio
char* buscar(Cache *cache, const char *chave) {
    EntradaHash *entrada = buscarEntrada(cache, chave);
    
    if (entrada) {
        // Cache HIT
        cache->hits++;
        entrada->acessos++;
        entrada->timestamp = time(NULL);
        
        // Mover para início (mais recente)
        moverParaInicio(cache, entrada->noLRU);
        
        printf("  ✅ Cache HIT: '%s'\n", chave);
        return entrada->valor;
    } else {
        // Cache MISS
        cache->misses++;
        printf("  ❌ Cache MISS: '%s'\n", chave);
        return NULL;
    }
}

// Invalidar entrada - O(1) médio
bool invalidar(Cache *cache, const char *chave) {
    unsigned long idx = hash(chave);
    EntradaHash *entrada = cache->tabela[idx];
    EntradaHash *anterior = NULL;
    
    while (entrada != NULL) {
        if (strcmp(entrada->chave, chave) == 0) {
            // Remover da hash table
            if (anterior) {
                anterior->proxima = entrada->proxima;
            } else {
                cache->tabela[idx] = entrada->proxima;
            }
            
            // Remover da lista LRU
            removerNoLRU(cache, entrada->noLRU);
            
            free(entrada);
            cache->tamanho--;
            
            printf("  🗑️  Cache invalidado: '%s'\n", chave);
            return true;
        }
        anterior = entrada;
        entrada = entrada->proxima;
    }
    
    return false;
}

// Exibir estatísticas
void exibirEstatisticas(Cache *cache) {
    int totalAcessos = cache->hits + cache->misses;
    float hitRate = totalAcessos > 0 ? (float)cache->hits / totalAcessos * 100 : 0;
    
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║     ESTATÍSTICAS DO CACHE              ║\n");
    printf("╚════════════════════════════════════════╝\n");
    printf("  📊 Tamanho atual: %d / %d\n", cache->tamanho, cache->capacidadeMaxima);
    printf("  ✅ Hits: %d\n", cache->hits);
    printf("  ❌ Misses: %d\n", cache->misses);
    printf("  📈 Hit Rate: %.1f%%\n", hitRate);
    printf("  🎯 Eficiência: %s\n", 
           hitRate >= 80 ? "Excelente" : 
           hitRate >= 60 ? "Boa" : 
           hitRate >= 40 ? "Regular" : "Ruim");
}

// Listar entradas do cache (ordem LRU)
void listarCache(Cache *cache) {
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║     CONTEÚDO DO CACHE (LRU Order)      ║\n");
    printf("╚════════════════════════════════════════╝\n");
    
    if (cache->tamanho == 0) {
        printf("  (vazio)\n");
        return;
    }
    
    NoLRU *no = cache->lruInicio;
    int pos = 1;
    
    while (no != NULL) {
        EntradaHash *entrada = buscarEntrada(cache, no->chave);
        
        if (entrada) {
            char timestamp[80];
            struct tm *info = localtime(&entrada->timestamp);
            strftime(timestamp, 80, "%H:%M:%S", info);
            
            printf("%d. [%s] %s\n", pos, timestamp, entrada->chave);
            printf("   Valor: %.60s%s\n", 
                   entrada->valor, strlen(entrada->valor) > 60 ? "..." : "");
            printf("   Acessos: %d\n\n", entrada->acessos);
        }
        
        no = no->proximo;
        pos++;
    }
}

// Limpar cache
void limparCache(Cache *cache) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        EntradaHash *entrada = cache->tabela[i];
        while (entrada != NULL) {
            EntradaHash *temp = entrada;
            entrada = entrada->proxima;
            free(temp->noLRU);
            free(temp);
        }
        cache->tabela[i] = NULL;
    }
    
    cache->lruInicio = NULL;
    cache->lruFim = NULL;
    cache->tamanho = 0;
    
    printf("✓ Cache limpo\n");
}

// ============= SIMULAÇÃO DE APLICAÇÃO WEB =============

void simularConsultaBD(Cache *cache, const char *chave, const char *valorBD) {
    printf("\n🔍 Consultando: %s\n", chave);
    
    char *valorCache = buscar(cache, chave);
    
    if (valorCache == NULL) {
        // Cache miss - simular consulta ao BD
        printf("  💾 Consultando banco de dados...\n");
        inserir(cache, chave, valorBD);
    } else {
        printf("  ⚡ Dados do cache: %.50s%s\n", 
               valorCache, strlen(valorCache) > 50 ? "..." : "");
    }
}

// ============= MAIN =============

int main() {
    Cache cache;
    inicializarCache(&cache, 5);  // Capacidade: 5 entradas
    
    printf("╔════════════════════════════════════════╗\n");
    printf("║   SISTEMA DE CACHE - HASH TABLE + LRU ║\n");
    printf("╚════════════════════════════════════════╝\n");
    
    printf("\nCapacidade do cache: %d entradas\n", cache.capacidadeMaxima);
    
    // Simular requisições
    printf("\n" "═══════════════════════════════════════════\n");
    printf("SIMULAÇÃO DE REQUISIÇÕES\n");
    printf("═══════════════════════════════════════════\n");
    
    simularConsultaBD(&cache, "user:123", "{id:123, name:'João', age:30}");
    simularConsultaBD(&cache, "user:456", "{id:456, name:'Maria', age:25}");
    simularConsultaBD(&cache, "product:789", "{id:789, name:'Notebook', price:3500}");
    simularConsultaBD(&cache, "user:123", "{id:123, name:'João', age:30}");  // HIT
    simularConsultaBD(&cache, "order:111", "{id:111, total:150.50}");
    simularConsultaBD(&cache, "user:456", "{id:456, name:'Maria', age:25}");  // HIT
    simularConsultaBD(&cache, "product:999", "{id:999, name:'Mouse', price:50}");
    
    listarCache(&cache);
    exibirEstatisticas(&cache);
    
    // Adicionar mais entradas (exceder capacidade)
    printf("\n\n" "═══════════════════════════════════════════\n");
    printf("ADICIONANDO MAIS ENTRADAS (Exceder capacidade)\n");
    printf("═══════════════════════════════════════════\n");
    
    simularConsultaBD(&cache, "category:10", "{id:10, name:'Eletrônicos'}");
    simularConsultaBD(&cache, "category:20", "{id:20, name:'Livros'}");
    
    listarCache(&cache);
    
    // Invalidar cache quando dados mudam
    printf("\n" "═══════════════════════════════════════════\n");
    printf("INVALIDAÇÃO DE CACHE (Dados atualizados no BD)\n");
    printf("═══════════════════════════════════════════\n");
    
    invalidar(&cache, "user:123");
    simularConsultaBD(&cache, "user:123", "{id:123, name:'João Silva', age:31}");  // Novo valor
    
    exibirEstatisticas(&cache);
    
    // Limpar cache
    printf("\n" "═══════════════════════════════════════════\n");
    limparCache(&cache);
    exibirEstatisticas(&cache);
    
    return 0;
}
```

## 📊 Análise de Complexidade

| Operação | Array | BST Balanceada | Hash Table (Chaining) |
|----------|-------|----------------|----------------------|
| Buscar | O(n) | O(log n) | **O(1)** médio ✅ |
| Inserir | O(1)* | O(log n) | **O(1)** médio ✅ |
| Remover | O(n) | O(log n) | **O(1)** médio ✅ |
| Espaço | O(n) | O(n) | O(n + m)** |

*No final, O(n) se precisa manter ordem  
**m = tamanho da tabela

## 🎯 Conceitos de Hash Table Aplicados

- ✅ **Função hash DJB2** - Distribuição uniforme
- ✅ **Chaining** - Resolve colisões com listas encadeadas
- ✅ **O(1) médio** - Busca, inserção e remoção constantes
- ✅ **LRU Policy** - Remove menos recente quando cheio
- ✅ **Lista dupla para LRU** - Move para início em O(1)
- ✅ **Estatísticas** - Hit rate para avaliar eficiência

## 💡 Aplicações de Hash Tables

| Aplicação | Por quê? |
|-----------|----------|
| Cache | Acesso O(1) muito rápido |
| Dicionários | Chave-valor, busca rápida |
| Conjuntos (Sets) | Verificar pertencimento O(1) |
| Contagem de frequência | Incrementar contador O(1) |
| Detecção de duplicatas | Verificar existência O(1) |
| Memoization | Cache de resultados de funções |
| Bancos de dados | Índices hash |

## 📝 Como Compilar e Executar

```bash
# Compilar
gcc PROBLEMA_PRATICO.c -o cache -Wall

# Executar
./cache
```

## 📚 Lições Aprendidas

1. **Hash O(1) >> BST O(log n)** - Para acesso direto por chave
2. **Chaining resolve colisões** - Simples e eficaz
3. **Boa função hash é crítica** - Evita colisões
4. **LRU com lista dupla** - Mover para início em O(1)
5. **Trade-off memória x velocidade** - Mais buckets = menos colisões
6. **Hit rate importa** - Cache só vale a pena se > 60% hits

## 🔍 Técnicas de Resolução de Colisões

| Técnica | Complexidade | Vantagens | Desvantagens |
|---------|--------------|-----------|--------------|
| **Chaining** | O(1) médio | Simples, não precisa redimensionar | Usa ponteiros (overhead) |
| **Linear Probing** | O(1) médio | Cache-friendly, sem ponteiros | Clustering primário |
| **Quadratic Probing** | O(1) médio | Reduz clustering | Pode não encontrar slot |
| **Double Hashing** | O(1) médio | Melhor distribuição | Mais complexo |

## 🔧 Otimizações Avançadas

1. **Rehashing** - Redimensionar quando load factor > 0.7
2. **Robin Hood Hashing** - Balanceia distâncias de probe
3. **Cuckoo Hashing** - Garante O(1) pior caso para busca
4. **Perfect Hashing** - Sem colisões (chaves conhecidas)
5. **Hash consistente** - Para sistemas distribuídos
6. **Bloom Filter** - Teste probabilístico de pertencimento
