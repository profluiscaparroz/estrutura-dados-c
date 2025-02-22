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

    return 0;
}