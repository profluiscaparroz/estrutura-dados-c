#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void exec1(){
    int numbers[] = {1, 2, 3, 4, 5};
    int size = 5;

    printf("Vetor de trás para frente:\n");
    for (int i = size - 1; i >= 0; i--) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
}

void exec2(){
    int numbers[10];
    int size = 10;

    srand(time(NULL)); // inicializa gerador de números aleatórios

    printf("Números maiores que 5:\n");
    for (int i = 0; i < size; i++) {
        numbers[i] = rand() % 10; // gera números de 0 a 9
        if (numbers[i] > 5) {
            printf("%d ", numbers[i]);
        }
    }
    printf("\n");
}

void exec3(){
    char surname[] = "caparroz"; // seu sobrenome
    int i = 0;

    printf("Letras alternadas:\n");
    while (surname[i] != '\0') {
        if (i % 2 == 0) { // índices pares
            printf("%c", surname[i]);
        }
        i++;
    }
    printf("\n");
}

void exec4(){
    int ages[] = {12, 25, 30, 17, 19, 40};
    int size = 6;

    printf("Idades ímpares:\n");
    for (int i = 0; i < size; i++) {
        if (ages[i] % 2 != 0) { // verifica se é ímpar
            printf("%d ", ages[i]);
        }
    }
    printf("\n");
}   

int main() {
    int choice;

    printf("Escolha o exercício (1-4):\n");
    printf("1. Imprimir vetor de trás para frente\n");
    printf("2. Números aleatórios maiores que 5\n");
    printf("3. Letras alternadas do sobrenome\n");
    printf("4. Idades ímpares\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            exec1();
            break;
        case 2:
            exec2();
            break;
        case 3:
            exec3();
            break;
        case 4:
            exec4();
            break;
        default:
            printf("Escolha inválida.\n");
    }

    return 0;
}