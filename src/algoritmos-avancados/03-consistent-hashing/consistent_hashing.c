#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 10
#define HASH_RING_SIZE 1000

typedef struct {
    char name[50];
    int hash;
} Node;

Node ring[MAX_NODES];
int node_count = 0;

// Função de hash simples (djb2)
unsigned int hash_function(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) 
        hash = ((hash << 5) + hash) + c;
    return hash % HASH_RING_SIZE;
}

// Adiciona um nó ao anel
void add_node(const char *name) {
    if (node_count >= MAX_NODES) {
        printf("Máximo de nós atingido!\n");
        return;
    }
    strcpy(ring[node_count].name, name);
    ring[node_count].hash = hash_function(name);
    printf("Nó '%s' adicionado com hash %d\n", name, ring[node_count].hash);
    node_count++;
}

// Remove um nó do anel
void remove_node(const char *name) {
    for (int i = 0; i < node_count; i++) {
        if (strcmp(ring[i].name, name) == 0) {
            printf("Removendo nó '%s'\n", name);
            // Move os nós restantes para a esquerda
            for (int j = i; j < node_count - 1; j++) {
                ring[j] = ring[j + 1];
            }
            node_count--;
            return;
        }
    }
    printf("Nó '%s' não encontrado\n", name);
}

// Encontra o nó mais próximo no sentido horário
const char* get_node(const char *key) {
    if (node_count == 0) {
        return "Nenhum nó disponível";
    }
    
    int key_hash = hash_function(key);
    int min_diff = HASH_RING_SIZE;
    int chosen = -1;

    // Procura o nó com menor diferença positiva (sentido horário)
    for (int i = 0; i < node_count; i++) {
        int diff = (ring[i].hash >= key_hash)
                   ? ring[i].hash - key_hash
                   : HASH_RING_SIZE + ring[i].hash - key_hash;

        if (diff < min_diff) {
            min_diff = diff;
            chosen = i;
        }
    }

    return ring[chosen].name;
}

// Mostra a distribuição atual do anel
void show_ring() {
    printf("\n=== Estado atual do anel ===\n");
    printf("Número de nós: %d\n", node_count);
    for (int i = 0; i < node_count; i++) {
        printf("Nó: %s (hash: %d)\n", ring[i].name, ring[i].hash);
    }
    printf("================================\n\n");
}

// Testa a distribuição de chaves
void test_key_distribution(const char *keys[], int num_keys) {
    printf("Distribuição de chaves:\n");
    for (int i = 0; i < num_keys; i++) {
        int key_hash = hash_function(keys[i]);
        const char *node = get_node(keys[i]);
        printf("'%s' (hash: %d) -> %s\n", keys[i], key_hash, node);
    }
    printf("\n");
}

// Simula redistribuição quando um nó é removido
void simulate_node_failure(const char *failed_node, const char *keys[], int num_keys) {
    printf("=== Simulando falha do nó '%s' ===\n", failed_node);
    
    // Mostrar distribuição antes
    printf("Antes da falha:\n");
    test_key_distribution(keys, num_keys);
    
    // Remover nó
    remove_node(failed_node);
    
    // Mostrar distribuição depois
    printf("Após a falha:\n");
    test_key_distribution(keys, num_keys);
}

int main() {
    printf("=== Teste do Consistent Hashing ===\n\n");
    
    // Adicionar nós
    add_node("ServidorA");
    add_node("ServidorB");
    add_node("ServidorC");
    
    show_ring();
    
    // Chaves para testar
    const char *chaves[] = {
        "usuario1", "usuario2", "usuario3", "usuario4", 
        "usuario5", "session123", "cache_data", "config"
    };
    int num_chaves = sizeof(chaves) / sizeof(chaves[0]);
    
    // Testar distribuição inicial
    printf("=== Distribuição inicial ===\n");
    test_key_distribution(chaves, num_chaves);
    
    // Adicionar um novo nó
    printf("=== Adicionando ServidorD ===\n");
    add_node("ServidorD");
    printf("Após adicionar ServidorD:\n");
    test_key_distribution(chaves, num_chaves);
    
    // Simular falha de um nó
    simulate_node_failure("ServidorB", chaves, num_chaves);
    
    // Mostrar estado final
    show_ring();
    
    return 0;
}