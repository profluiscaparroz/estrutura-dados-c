#include <stdio.h>
#include <stdlib.h>

void exemplo(){
    // Método 1: Matriz estática (recomendado quando possível)
    int matriz[3][4];
    // + Memória contígua (mais rápida)
    // + Menos fragmentação
    // + Sintaxe simples
    // - Tamanho fixo em tempo de compilação

    // Método 2: Array de ponteiros (flexível)
    int **matrizPonteiros = malloc(3 * sizeof(int*));
    for (int i = 0; i < 3; i++)
    matrizPonteiros[i] = malloc(4 * sizeof(int));
    // + Tamanho dinâmico
    // + Pode ter linhas de tamanhos diferentes
    // - Memória fragmentada (mais lenta)
    // - Mais complexo de gerenciar
    // - Overhead de ponteiros

    // Método 3: Bloco contíguo (melhor dos dois mundos)
    int *matrizContinuo = malloc(3 * 4 * sizeof(int));
    // Acesso: matriz[i * colunas + j]
    // + Memória contígua (rápida como Método 1)
    // + Tamanho dinâmico (flexível como Método 2)
    // + Apenas uma chamada malloc (eficiente)
    // - Sintaxe menos intuitiva
}

int main() {
    int linhas = 3, colunas = 4;
    int i, j;

    // ----------------------------
    // Método 1: Matriz Estática
    // ----------------------------
    int matriz[3][4];  // memória contígua
    int valor = 1;

    printf("Metodo 1: Matriz Estatica\n");
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            matriz[i][j] = valor++;
            printf("%3d ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // ----------------------------
    // Método 2: Array de Ponteiros
    // ----------------------------
    int **matrizPonteiros = malloc(linhas * sizeof(int*));
    for (i = 0; i < linhas; i++) {
        matrizPonteiros[i] = malloc(colunas * sizeof(int));
    }

    valor = 1;
    printf("Metodo 2: Matriz com Ponteiros\n");
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            matrizPonteiros[i][j] = valor++;
            printf("%3d ", matrizPonteiros[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // ----------------------------
    // Método 3: Bloco Contíguo
    // ----------------------------
    int *matrizContinuo = malloc(linhas * colunas * sizeof(int));

    valor = 1;
    printf("Metodo 3: Matriz em Bloco Contiguo\n");
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            matrizContinuo[i * colunas + j] = valor++;
            printf("%3d ", matrizContinuo[i * colunas + j]);
        }
        printf("\n");
    }
    printf("\n");

    // ----------------------------
    // Liberando memória (Método 2 e 3)
    // ----------------------------
    for (i = 0; i < linhas; i++) {
        free(matrizPonteiros[i]);
    }
    free(matrizPonteiros);

    free(matrizContinuo);

    return 0;
}