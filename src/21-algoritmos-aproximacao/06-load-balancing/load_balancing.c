/* Load Balancing - List Scheduling e LPT */
#include <stdio.h>
#include <stdlib.h>

int compare_desc(const void* a, const void* b) {
    return *(int*)b - *(int*)a;
}

int list_scheduling(int tasks[], int n, int m, int assignment[]) {
    int loads[10] = {0};
    
    for (int i = 0; i < n; i++) {
        int min_idx = 0;
        for (int j = 1; j < m; j++) {
            if (loads[j] < loads[min_idx]) min_idx = j;
        }
        loads[min_idx] += tasks[i];
        assignment[i] = min_idx;
    }
    
    int max_load = 0;
    for (int i = 0; i < m; i++) {
        if (loads[i] > max_load) max_load = loads[i];
    }
    return max_load;
}

int lpt(int tasks[], int n, int m, int assignment[]) {
    int sorted[100];
    for (int i = 0; i < n; i++) sorted[i] = tasks[i];
    qsort(sorted, n, sizeof(int), compare_desc);
    return list_scheduling(sorted, n, m, assignment);
}

int main() {
    printf("LOAD BALANCING\n\n");
    
    int tasks[] = {7, 5, 4, 4, 3, 3, 2};
    int n = 7, m = 3;
    int assignment[100];
    
    int greedy = list_scheduling(tasks, n, m, assignment);
    printf("List Scheduling: makespan = %d\n", greedy);
    
    int lpt_result = lpt(tasks, n, m, assignment);
    printf("LPT: makespan = %d\n", lpt_result);
    
    printf("\nLPT é melhor: fator 4/3 vs 2\n");
    
    return 0;
}
