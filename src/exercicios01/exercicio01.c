#include <stdio.h>

#define MAX 1000

int primeiroRepetido(int arr[], int n) {
    int visto[MAX] = {0}; // inicializa tudo com 0

    for (int i = 0; i < n; i++) {
        if (visto[arr[i]] == 1) {
            return arr[i];
        }
        visto[arr[i]] = 1;
    }

    return -1;
}

int main() {
    int arr[] = {10, 5, 3, 4, 3, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    int resultado = primeiroRepetido(arr, n);

    printf("%d\n", resultado);

    return 0;
}