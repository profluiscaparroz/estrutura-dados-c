#include <stdio.h>

// Insertion Sort que conta deslocamentos
int insertionSortCount(int v[], int n) {
    int count = 0;

    for (int i = 1; i < n; i++) {
        int key = v[i];
        int j = i - 1;

        while (j >= 0 && v[j] > key) {
            v[j + 1] = v[j]; // deslocamento
            j--;
            count++;
        }

        v[j + 1] = key;
    }

    return count;
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    int tarefas[10000];

    for (int i = 0; i < n; i++) {
        scanf("%d", &tarefas[i]);
    }

    while (q--) {
        int l, r;
        scanf("%d %d", &l, &r);

        // converter para índice 0-based
        l--; 
        r--;

        int tamanho = r - l + 1;
        int sub[10000];

        // copiar subarray
        for (int i = 0; i < tamanho; i++) {
            sub[i] = tarefas[l + i];
        }

        int resultado = insertionSortCount(sub, tamanho);

        printf("%d\n", resultado);
    }

    return 0;
}