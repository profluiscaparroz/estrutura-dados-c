#include <stdio.h>
#include <stdlib.h>

// Função que calcula a soma de todos os múltiplos de 3 ou 5 abaixo de n
int somaMultiplos(int n) {
    int soma = 0;
    for (int i = 1; i < n; i++) {
        if (i % 3 == 0 || i % 5 == 0) {
            soma += i;
        }
    }
    return soma;
}

int main() {
    int n;
    printf("Digite um número inteiro positivo: ");
    scanf("%d", &n);

    if (n < 1 || n > 1000) {
        printf("O número deve estar entre 1 e 1000.\n");
        return 1;
    }

    int resultado = somaMultiplos(n);
    printf("A soma de todos os múltiplos de 3 ou 5 abaixo de %d é: %d\n", n, resultado);

    return 0;
}