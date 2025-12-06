/**
 * Bin Packing - Heurísticas de Aproximação
 * Next Fit, First Fit, First Fit Decreasing
 * 
 * Complexidade FFD: O(n log n)
 * Fator de Aproximação FFD: 11/9 ≈ 1.222
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ITEMS 100
#define CAPACITY 1.0

typedef struct {
    double capacity;
    double used;
    int items[MAX_ITEMS];
    int n_items;
} Bin;

// Função de comparação para qsort (ordem decrescente)
int compare_desc(const void* a, const void* b) {
    double diff = *(double*)b - *(double*)a;
    return (diff > 0) - (diff < 0);
}

// Next Fit: Tenta bin atual, se não couber abre novo
int next_fit(double items[], int n, Bin bins[]) {
    int n_bins = 1;
    bins[0].used = 0;
    bins[0].n_items = 0;
    
    for (int i = 0; i < n; i++) {
        if (bins[n_bins-1].used + items[i] <= CAPACITY) {
            bins[n_bins-1].items[bins[n_bins-1].n_items++] = i;
            bins[n_bins-1].used += items[i];
        } else {
            bins[n_bins].used = items[i];
            bins[n_bins].n_items = 1;
            bins[n_bins].items[0] = i;
            n_bins++;
        }
    }
    return n_bins;
}

// First Fit: Coloca no primeiro bin que cabe
int first_fit(double items[], int n, Bin bins[]) {
    int n_bins = 0;
    
    for (int i = 0; i < n; i++) {
        bool placed = false;
        
        for (int j = 0; j < n_bins; j++) {
            if (bins[j].used + items[i] <= CAPACITY) {
                bins[j].items[bins[j].n_items++] = i;
                bins[j].used += items[i];
                placed = true;
                break;
            }
        }
        
        if (!placed) {
            bins[n_bins].used = items[i];
            bins[n_bins].n_items = 1;
            bins[n_bins].items[0] = i;
            n_bins++;
        }
    }
    return n_bins;
}

// First Fit Decreasing: Ordena decrescente + First Fit
int first_fit_decreasing(double items[], int n, Bin bins[]) {
    double sorted[MAX_ITEMS];
    for (int i = 0; i < n; i++) sorted[i] = items[i];
    
    qsort(sorted, n, sizeof(double), compare_desc);
    return first_fit(sorted, n, bins);
}

void print_bins(Bin bins[], int n_bins) {
    for (int i = 0; i < n_bins; i++) {
        printf("Bin %d (%.2f/%.2f)\n", i+1, bins[i].used, CAPACITY);
    }
}

int main() {
    printf("╔═══════════════════════════════════════╗\n");
    printf("║  BIN PACKING - Heurísticas            ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
    
    double items[] = {0.7, 0.5, 0.3, 0.4, 0.2, 0.6, 0.1, 0.8};
    int n = 8;
    
    printf("Itens: ");
    for (int i = 0; i < n; i++) printf("%.1f ", items[i]);
    printf("\nCapacidade: %.1f\n\n", CAPACITY);
    
    Bin bins[MAX_ITEMS];
    
    // Next Fit
    for (int i = 0; i < MAX_ITEMS; i++) bins[i].n_items = 0;
    int nf = next_fit(items, n, bins);
    printf("=== Next Fit: %d bins ===\n", nf);
    print_bins(bins, nf);
    
    // First Fit
    printf("\n=== First Fit: ");
    for (int i = 0; i < MAX_ITEMS; i++) bins[i].n_items = 0;
    int ff = first_fit(items, n, bins);
    printf("%d bins ===\n", ff);
    print_bins(bins, ff);
    
    // First Fit Decreasing
    printf("\n=== First Fit Decreasing: ");
    for (int i = 0; i < MAX_ITEMS; i++) bins[i].n_items = 0;
    int ffd = first_fit_decreasing(items, n, bins);
    printf("%d bins ===\n", ffd);
    print_bins(bins, ffd);
    
    printf("\nResumo:\n");
    printf("NF: %d bins (fator 2)\n", nf);
    printf("FF: %d bins (fator 1.7)\n", ff);
    printf("FFD: %d bins (fator 1.222)\n", ffd);
    
    return 0;
}
