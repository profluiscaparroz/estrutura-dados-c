#include <stdio.h>
#include <stdlib.h>

/**
 * Função que imprime uma matriz alocada dinamicamente
 * @param mat: ponteiro para a matriz a ser impressa
 * @param linhas: número de linhas da matriz
 * @param colunas: número de colunas da matriz
 */
void imprimir_matriz_dinamica(int **mat, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

/**
 * Exemplo de alocação dinâmica de matriz usando ponteiros duplos
 * Cria uma matriz 2x3 onde cada elemento é a soma dos índices i+j
 * Demonstra alocação, manipulação e liberação de memória para matrizes dinâmicas
 */
int exemploPonteiro() {
    
    int linhas = 2, colunas = 3;
    // Aloca dinamicamente um array de ponteiros (as linhas da matriz)
    int **mat = malloc(linhas * sizeof(int *));
    for (int i = 0; i < linhas; i++) {
        // Para cada linha, aloca um array de inteiros (as colunas)
        mat[i] = malloc(colunas * sizeof(int));
        for (int j = 0; j < colunas; j++) {
            // Inicializa cada elemento com a soma dos índices
            mat[i][j] = i + j;
        }
    }

    // Imprime a matriz criada
    imprimir_matriz_dinamica(mat, linhas, colunas);

    // Libera a memória alocada (primeiro as linhas, depois o array de ponteiros)
    for (int i = 0; i < linhas; i++) free(mat[i]);
    free(mat);
    return 0;
}

/**
 * Função que demonstra a soma de duas matrizes 2x2
 * A soma de matrizes é realizada somando os elementos correspondentes
 * de cada matriz (mesma posição i,j)
 */
int Soma() {
    // Declaração e inicialização das matrizes 2x2
    int matriz1[2][2] = {
        {1, 2},
        {3, 4}
    };
    int matriz2[2][2] = {
        {5, 6},
        {7, 8}
    };
    int soma[2][2];

    // Somando as matrizes - para cada posição (i,j), soma os elementos correspondentes
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            soma[i][j] = matriz1[i][j] + matriz2[i][j];
        }
    }

    // Imprimindo o resultado
    printf("Resultado da soma das matrizes:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", soma[i][j]);
        }
        printf("\n");
    }

    return 0;
}

/**
 * Função que demonstra a multiplicação de matrizes
 * Multiplica uma matriz A(2x3) por uma matriz B(3x2), resultando em C(2x2)
 * Na multiplicação, cada elemento C[i][j] é o produto escalar da linha i de A 
 * pela coluna j de B
 */
int Multiplicacao() {
    // Matrizes A (2x3) e B (3x2)
    int A[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    int B[3][2] = {
        {7, 8},
        {9, 10},
        {11, 12}
    };
    // Matriz resultado C (2x2) inicializada com zeros
    int C[2][2] = {0};

    // Multiplicação de matrizes usando três loops aninhados
    for (int i = 0; i < 2; i++) {        // Percorre as linhas de A
        for (int j = 0; j < 2; j++) {    // Percorre as colunas de B
            for (int k = 0; k < 3; k++) { // Percorre as colunas de A / linhas de B
                C[i][j] += A[i][k] * B[k][j]; // Acumula o produto dos elementos
            }
        }
    }

    // Imprimindo o resultado
    printf("Resultado da multiplicação das matrizes:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}

/**
 * Função que demonstra a transposição de uma matriz
 * Na transposição, as linhas da matriz original se tornam colunas
 * e as colunas se tornam linhas, ou seja, o elemento na posição [i][j]
 * vai para a posição [j][i]
 */
int Transposicao() {
    // Matriz original 2x3
    int matriz[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    // A transposta será 3x2 (dimensões invertidas)
    int transposta[3][2];

    // Calculando a transposta - inverte índices i e j
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            transposta[j][i] = matriz[i][j];
        }
    }

    // Imprimindo a matriz transposta
    printf("Matriz transposta:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", transposta[i][j]);
        }
        printf("\n");
    }

    return 0;
}

/**
 * Função principal que chama as funções de exemplo
 * para demonstrar as diferentes operações com matrizes
 */
int main() {
    Soma();
    Multiplicacao();
    Transposicao();

    return 0;
}