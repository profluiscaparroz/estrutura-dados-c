#include <stdio.h>

int main() {
    int a = 5, b = 10;

    printf("a = %d, b = %d\n", a, b);
    printf("a == b: %d\n", a == b); // Igual a
    printf("a != b: %d\n", a != b); // Diferente de
    printf("a > b: %d\n", a > b);   // Maior que
    printf("a < b: %d\n", a < b);   // Menor que
    printf("a >= b: %d\n", a >= b); // Maior ou igual a
    printf("a <= b: %d\n", a <= b); // Menor ou igual a

    float c = 5.0f, d = 10.0f;
    printf("c = %.2f, d = %.2f\n", c, d);
    printf("c == d: %d\n", c == d); // Igual a
    printf("c != d: %d\n", c != d); // Diferente de
    printf("c > d: %d\n", c > d);   // Maior que
    printf("c < d: %d\n", c < d);   // Menor que

    char e = 'a', f = 'b';
    printf("e = %c, f = %c\n", e, f);
    printf("e == f: %d\n", e == f); // Igual a
    printf("e != f: %d\n", e != f); // Diferente de
    printf("e > f: %d\n", e > f);   // Maior que

    char nome[] = "Jose";
    printf("nome = %s\n", nome);
    printf("nome == \"Jose\": %d\n", strcmp(nome, "Jose") == 0); // Igual a
    printf("nome != \"Jose\": %d\n", strcmp(nome, "Jose") != 0); // Diferente de

    return 0;
}