#include <stdio.h>
#include <string.h>

#define TAMANHO 5  // Definição de tamanho do vetor

int main() {
    // 1. Declaração e Inicialização de um vetor
    int numeros[TAMANHO] = {10, 20, 30, 40, 50};  
    
    // 2. Acesso aos elementos do vetor
    printf("Acessando elementos do vetor:\n");
    for (int i = 0; i < TAMANHO; i++) {
        printf("Elemento %d: %d\n", i, numeros[i]);
    }
    printf("\n");

    // 3. Modificando elementos do vetor
    numeros[2] = 99;  // Alterando o terceiro elemento (índice 2)
    printf("Após modificação:\n");
    for (int i = 0; i < TAMANHO; i++) {
        printf("Elemento %d: %d\n", i, numeros[i]);
    }
    printf("\n");

    // 4. Preenchendo um vetor com valores do usuário
    int entrada[TAMANHO];
    printf("Digite %d números:\n", TAMANHO);
    for (int i = 0; i < TAMANHO; i++) {
        printf("Número %d: ", i);
        scanf("%d", &entrada[i]);
    }

    // 5. Calculando a soma dos elementos do vetor
    int soma = 0;
    for (int i = 0; i < TAMANHO; i++) {
        soma += entrada[i];
    }
    printf("\nSoma dos números digitados: %d\n\n", soma);

    // 6. Encontrando o maior e o menor número do vetor
    int maior = entrada[0];
    int menor = entrada[0];

    for (int i = 1; i < TAMANHO; i++) {
        if (entrada[i] > maior) {
            maior = entrada[i];
        }
        if (entrada[i] < menor) {
            menor = entrada[i];
        }
    }

    printf("Maior número: %d\n", maior);
    printf("Menor número: %d\n\n", menor);

    // 7. Criando e imprimindo um vetor de caracteres (string)
    char nome[] = "Linguagem C";
    printf("Vetor de caracteres (string): %s\n", nome);
    
    // Demonstrando que strings são arrays de caracteres
    printf("Caracteres individuais da string:\n");
    for (int i = 0; nome[i] != '\0'; i++) {
        printf("nome[%d] = '%c'\n", i, nome[i]);
    }
    printf("Terminador: nome[%d] = '\\0'\n\n", (int)strlen(nome));

    // 8. Vetor bidimensional (Matriz)
    int matriz[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    printf("Matriz 2x3:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    
    printf("\n=== Para mais exemplos de strings com vetores ===\n");
    printf("Execute: ./exemploStringVetores\n");
    printf("Veja também: README.md (seção Strings como Vetores)\n");

    return 0;
}
