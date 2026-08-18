#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int v[500];

    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }

    int trocas = 0;

    // Bubble Sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                // troca
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;

                trocas++;
            }
        }
    }

    printf("%d\n", trocas);

    return 0;
}