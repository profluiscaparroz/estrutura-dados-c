#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000
#define NUM_HASHES 5

unsigned char bit_array[SIZE];

// Função hash DJB2
unsigned int djb2(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % SIZE;
}

// Função hash SDBM
unsigned int sdbm(const char *str) {
    unsigned long hash = 0;
    int c;
    while ((c = *str++))
        hash = c + (hash << 6) + (hash << 16) - hash;
    return hash % SIZE;
}

// Função hash FNV-1a
unsigned int fnv1a(const char *str) {
    unsigned long hash = 2166136261;
    int c;
    while ((c = *str++)) {
        hash ^= c;
        hash *= 16777619;
    }
    return hash % SIZE;
}

// Função para adicionar um item ao filtro
void add(const char *item) {
    // Usar múltiplas funções hash
    unsigned int h1 = djb2(item);
    unsigned int h2 = sdbm(item);
    unsigned int h3 = fnv1a(item);
    
    // Gerar NUM_HASHES diferentes valores usando double hashing
    for (int i = 0; i < NUM_HASHES; i++) {
        unsigned int h = (h1 + i * h2 + i * i * h3) % SIZE;
        bit_array[h] = 1;
    }
}

// Função para verificar se um item pode estar no filtro
int contains(const char *item) {
    unsigned int h1 = djb2(item);
    unsigned int h2 = sdbm(item);
    unsigned int h3 = fnv1a(item);
    
    for (int i = 0; i < NUM_HASHES; i++) {
        unsigned int h = (h1 + i * h2 + i * i * h3) % SIZE;
        if (bit_array[h] == 0) {
            return 0; // Definitivamente não está no conjunto
        }
    }
    return 1; // Pode estar no conjunto (ou falso positivo)
}

// Função para limpar o filtro
void clear_filter() {
    memset(bit_array, 0, sizeof(bit_array));
}

// Função para mostrar estatísticas do filtro
void show_stats() {
    int set_bits = 0;
    for (int i = 0; i < SIZE; i++) {
        if (bit_array[i] == 1) {
            set_bits++;
        }
    }
    
    double load_factor = (double)set_bits / SIZE;
    printf("Estatísticas do Bloom Filter:\n");
    printf("- Tamanho total: %d bits\n", SIZE);
    printf("- Bits definidos: %d\n", set_bits);
    printf("- Fator de carga: %.2f%%\n", load_factor * 100);
    printf("- Número de funções hash: %d\n", NUM_HASHES);
}

// Função para estimativa da taxa de falsos positivos
double false_positive_rate() {
    int set_bits = 0;
    for (int i = 0; i < SIZE; i++) {
        if (bit_array[i] == 1) {
            set_bits++;
        }
    }
    
    double load_factor = (double)set_bits / SIZE;
    
    // Fórmula: (1 - e^(-k*n/m))^k
    // onde k = num_hashes, n = elementos inseridos, m = tamanho do array
    // Aproximação usando load_factor
    double prob = 1.0;
    for (int i = 0; i < NUM_HASHES; i++) {
        prob *= load_factor;
    }
    
    return prob;
}

int main() {
    // Limpar o filtro
    clear_filter();
    
    printf("=== Teste do Bloom Filter ===\n\n");
    
    // Adicionar alguns itens
    printf("Adicionando itens ao filtro...\n");
    add("Luis");
    add("Caparroz");
    add("João");
    add("Maria");
    add("Pedro");
    add("Ana");
    add("Carlos");
    
    printf("Itens adicionados: Luis, Caparroz, João, Maria, Pedro, Ana, Carlos\n\n");
    
    // Testar se os itens estão no filtro
    printf("Testando membros:\n");
    printf("Luis está no filtro? %s\n", contains("Luis") ? "Sim" : "Não");
    printf("Caparroz está no filtro? %s\n", contains("Caparroz") ? "Sim" : "Não");
    printf("João está no filtro? %s\n", contains("João") ? "Sim" : "Não");
    printf("Maria está no filtro? %s\n", contains("Maria") ? "Sim" : "Não");
    
    printf("\nTestando não-membros:\n");
    printf("Roberto está no filtro? %s\n", contains("Roberto") ? "Sim (falso positivo)" : "Não");
    printf("Alice está no filtro? %s\n", contains("Alice") ? "Sim (falso positivo)" : "Não");
    printf("Bruno está no filtro? %s\n", contains("Bruno") ? "Sim (falso positivo)" : "Não");
    printf("Fernanda está no filtro? %s\n", contains("Fernanda") ? "Sim (falso positivo)" : "Não");
    
    printf("\n");
    show_stats();
    
    printf("\nTaxa estimada de falsos positivos: %.4f (%.2f%%)\n", 
           false_positive_rate(), false_positive_rate() * 100);
    
    // Teste adicional: adicionar mais itens
    printf("\n=== Adicionando mais itens ===\n");
    add("Ricardo");
    add("Beatriz");
    add("Diego");
    add("Camila");
    add("Eduardo");
    
    printf("Novos itens adicionados: Ricardo, Beatriz, Diego, Camila, Eduardo\n\n");
    
    show_stats();
    printf("Nova taxa estimada de falsos positivos: %.4f (%.2f%%)\n", 
           false_positive_rate(), false_positive_rate() * 100);
    
    return 0;
}