#include <stdio.h>

int soma(int a, int b) { return a + b; }
int subtrai(int a, int b) { return a - b; }
int multiplica(int a, int b) { return a * b; }
int divide(int a, int b) { return b != 0 ? a / b : 0; }

int main() {
    // Vetor de ponteiros para funções
    int (*operacoes[4])(int, int) = {soma, subtrai, multiplica, divide};

    int a, b, opcao;
    printf("Digite dois numeros: ");
    scanf("%d %d", &a, &b);

    printf("Escolha a operacao:\n");
    printf("0 - Soma\n1 - Subtracao\n2 - Multiplicacao\n3 - Divisao\n");
    scanf("%d", &opcao);

    if (opcao >= 0 && opcao < 4) {
        printf("Resultado: %d\n", operacoes[opcao](a, b));
    } else {
        printf("Opcao invalida!\n");
    }

    return 0;
}
