#include <stdio.h>

// Função que conta o número de vogais e consoantes em uma string
void contaVogaisConsoantes(char s[], int *vogais, int *consoantes) {
    *vogais = 0;
    *consoantes = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];
        if (c >= 'a' && c <= 'z') { // Verifica se é uma letra minúscula
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                (*vogais)++;
            } else {
                (*consoantes)++;
            }
        }
    }
}

int main() {
    char s[51]; // String de entrada com tamanho máximo de 50 caracteres
    int vogais, consoantes;

    printf("Digite uma string: ");
    fgets(s, sizeof(s), stdin);

    // Remove o caractere de nova linha, se presente
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '\n') {
            s[i] = '\0';
            break;
        }
    }

    contaVogaisConsoantes(s, &vogais, &consoantes);
    printf("%d %d\n", vogais, consoantes);

    return 0;
}