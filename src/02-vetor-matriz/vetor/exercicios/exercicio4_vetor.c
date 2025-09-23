#include <stdio.h>

int main() {
    char s[51]; // até 50 caracteres + '\0'
    int i = 0;
    int vogal = 0, consoantes = 0;
    char c;

    printf("Digite uma string (max 50 caracteres, apenas letras minúsculas):\n");
    fgets(s, 51, stdin); // lê a string do usuário

    // Percorre cada caractere da string
    while (s[i] != '\0') {
        c = s[i];

        // Verifica se é letra minúscula
        if (c >= 'a' && c <= 'z') {
            // Verifica se é vogal
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                vogal++;
            } else {
                consoantes++;
            }
        }

        i++;
    }

    printf("%d %d\n", vogal, consoantes);

    return 0;
}
