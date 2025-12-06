/* Knapsack Greedy */
#include <stdio.h>
#include <stdlib.h>

typedef struct { int value, weight; double ratio; int id; } Item;

int compare(const void* a, const void* b) {
    double diff = ((Item*)b)->ratio - ((Item*)a)->ratio;
    return (diff > 0) - (diff < 0);
}

int knapsack_greedy(Item items[], int n, int capacity) {
    for (int i = 0; i < n; i++)
        items[i].ratio = (double)items[i].value / items[i].weight;
    
    qsort(items, n, sizeof(Item), compare);
    
    int total_value = 0, total_weight = 0;
    
    printf("Ordem gulosa (v/w):\n");
    for (int i = 0; i < n; i++) {
        if (total_weight + items[i].weight <= capacity) {
            printf("  Item %d: v=%d, w=%d, ratio=%.2f\n", 
                   items[i].id, items[i].value, items[i].weight, items[i].ratio);
            total_value += items[i].value;
            total_weight += items[i].weight;
        }
    }
    
    return total_value;
}

int main() {
    printf("KNAPSACK GREEDY\n\n");
    
    Item items[] = {
        {60, 10, 0, 0},
        {100, 20, 0, 1},
        {120, 30, 0, 2}
    };
    int n = 3, capacity = 50;
    
    int value = knapsack_greedy(items, n, capacity);
    printf("\nValor total: %d\n", value);
    printf("Capacidade: %d\n", capacity);
    
    return 0;
}
