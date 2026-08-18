#include <stdio.h>

int primeiroDiaMeta(int v[], int n, int meta) {
    int left = 0, right = n - 1;
    int resposta = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (v[mid] >= meta) {
            resposta = mid;      // possível resposta
            right = mid - 1;     // tenta achar um índice menor
        } else {
            left = mid + 1;
        }
    }

    // converter para índice baseado em 1
    if (resposta != -1)
        return resposta + 1;

    return -1;
}

int main() {
    int vendas[] = {100, 120, 150, 150, 180, 200};
    int n = sizeof(vendas) / sizeof(vendas[0]);
    int meta = 150;

    int resultado = primeiroDiaMeta(vendas, n, meta);

    printf("%d\n", resultado);

    return 0;
}