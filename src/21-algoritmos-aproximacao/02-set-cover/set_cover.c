/* Set Cover - Algoritmo Greedy O(log n)-aproximação */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ELEMENTS 50
#define MAX_SETS 20

int greedy_set_cover(bool sets[][MAX_ELEMENTS], int n_sets, int n_elements, int cover[]) {
    bool covered[MAX_ELEMENTS] = {false};
    int n_covered = 0, n_cover = 0;
    
    while (n_covered < n_elements) {
        int best_set = -1, best_count = 0;
        
        for (int i = 0; i < n_sets; i++) {
            int count = 0;
            for (int j = 0; j < n_elements; j++) {
                if (sets[i][j] && !covered[j]) count++;
            }
            if (count > best_count) {
                best_count = count;
                best_set = i;
            }
        }
        
        cover[n_cover++] = best_set;
        for (int j = 0; j < n_elements; j++) {
            if (sets[best_set][j] && !covered[j]) {
                covered[j] = true;
                n_covered++;
            }
        }
    }
    return n_cover;
}

int main() {
    printf("SET COVER - Greedy O(log n)-aproximação\n\n");
    
    int n_sets = 5, n_elements = 10;
    bool sets[MAX_SETS][MAX_ELEMENTS] = {
        {1,1,0,0,1,0,0,0,0,0}, // S1: {1,2,5}
        {0,1,1,1,0,0,0,0,0,0}, // S2: {2,3,4}
        {0,0,0,1,1,1,0,0,0,0}, // S3: {4,5,6}
        {0,0,0,0,0,1,1,1,0,0}, // S4: {6,7,8}
        {0,0,0,0,0,0,0,1,1,1}  // S5: {8,9,10}
    };
    
    int cover[MAX_SETS];
    int n_cover = greedy_set_cover(sets, n_sets, n_elements, cover);
    
    printf("Cobertura mínima: %d conjuntos\n", n_cover);
    printf("Conjuntos escolhidos: ");
    for (int i = 0; i < n_cover; i++) printf("S%d ", cover[i]+1);
    printf("\n");
    
    return 0;
}
