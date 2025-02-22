#include <stdio.h>

void exemploVariavelEstatica() {
    // Variável local persistente entre chamadas
    static int contador = 0;
    contador++;

    printf("Chamada %d: Valor do contador = %d\n", contador, contador);
}

int main(void) {
    exemploVariavelEstatica();
    exemploVariavelEstatica();
    exemploVariavelEstatica();
    exemploVariavelEstatica();
    exemploVariavelEstatica();
    return 0;
}