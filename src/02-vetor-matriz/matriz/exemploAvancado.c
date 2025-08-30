#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Função para alocar matriz dinâmica
int** alocar_matriz(int linhas, int colunas) {
    int **matriz = malloc(linhas * sizeof(int*));
    for (int i = 0; i < linhas; i++) {
        matriz[i] = malloc(colunas * sizeof(int));
    }
    return matriz;
}

// Função para liberar matriz dinâmica
void liberar_matriz(int **matriz, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

// Função para imprimir matriz
void imprimir_matriz(int **matriz, int linhas, int colunas, const char* nome) {
    printf("\n%s (%dx%d):\n", nome, linhas, colunas);
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%4d ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Demonstração de representação em memória
void demonstracao_memoria_matriz() {
    printf("=== REPRESENTAÇÃO EM MEMÓRIA - ROW MAJOR ===\n");
    
    int matriz[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    printf("Matriz 3x4:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%2d ", matriz[i][j]);
        }
        printf("\n");
    }
    
    printf("\nEndereços em memória (Row-Major Order):\n");
    int *ptr = (int*)matriz;
    for (int i = 0; i < 12; i++) {
        int linha = i / 4;
        int coluna = i % 4;
        printf("matriz[%d][%d] = %2d @ %p (offset: %2d)\n", 
               linha, coluna, ptr[i], (void*)&ptr[i], i);
    }
    
    printf("\nCálculo de endereço: base + (linha × num_colunas + coluna) × sizeof(int)\n");
    printf("Exemplo matriz[2][1]: %p + (2×4 + 1)×4 = %p\n", 
           (void*)matriz, (void*)&matriz[2][1]);
    printf("\n");
}

// Multiplicação de matrizes com análise de complexidade
int** multiplicar_matrizes(int **A, int **B, int m, int n, int p) {
    printf("=== MULTIPLICAÇÃO DE MATRIZES ===\n");
    printf("Multiplicando matriz %dx%d por matriz %dx%d\n", m, n, n, p);
    printf("Complexidade: O(%d × %d × %d) = O(%d) operações\n\n", m, n, p, m*n*p);
    
    int **C = alocar_matriz(m, p);
    int operacoes = 0;
    
    clock_t inicio = clock();
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
                operacoes++;
            }
        }
    }
    
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000;
    
    printf("Operações realizadas: %d\n", operacoes);
    printf("Tempo de execução: %.3f ms\n\n", tempo);
    
    return C;
}

// Transposição de matriz
int** transpor_matriz(int **matriz, int linhas, int colunas) {
    printf("=== TRANSPOSIÇÃO DE MATRIZ ===\n");
    printf("Transpondo matriz %dx%d para %dx%d\n", linhas, colunas, colunas, linhas);
    
    int **transposta = alocar_matriz(colunas, linhas);
    
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            transposta[j][i] = matriz[i][j];
        }
    }
    
    printf("Complexidade: O(%d × %d) = O(%d)\n\n", linhas, colunas, linhas*colunas);
    return transposta;
}

// Matriz esparsa (muitos zeros)
void demonstracao_matriz_esparsa() {
    printf("=== MATRIZ ESPARSA ===\n");
    
    // Matriz 10x10 com poucos elementos não-zero
    int **matriz = alocar_matriz(10, 10);
    
    // Inicializar com zeros
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            matriz[i][j] = 0;
        }
    }
    
    // Adicionar alguns elementos não-zero
    matriz[0][0] = 5;
    matriz[2][3] = 8;
    matriz[4][7] = 3;
    matriz[6][1] = 9;
    matriz[8][9] = 2;
    
    printf("Matriz 10x10 com apenas 5 elementos não-zero:\n");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%2d ", matriz[i][j]);
        }
        printf("\n");
    }
    
    // Contagem de elementos zero e não-zero
    int zeros = 0, nao_zeros = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (matriz[i][j] == 0) zeros++;
            else nao_zeros++;
        }
    }
    
    printf("\nEstatísticas:\n");
    printf("Elementos zero: %d (%.1f%%)\n", zeros, (float)zeros/100*100);
    printf("Elementos não-zero: %d (%.1f%%)\n", nao_zeros, (float)nao_zeros/100*100);
    printf("Desperdício de memória: %d inteiros armazenando zero\n\n", zeros);
    
    liberar_matriz(matriz, 10);
}

// Otimização de acesso por cache (comparação linha vs coluna)
void demonstracao_cache_matriz() {
    printf("=== OTIMIZAÇÃO DE CACHE EM MATRIZES ===\n");
    
    const int SIZE = 1000;
    int **matriz = alocar_matriz(SIZE, SIZE);
    
    // Preenchimento
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matriz[i][j] = i + j;
        }
    }
    
    // Acesso por linhas (cache-friendly)
    clock_t inicio = clock();
    long soma_linhas = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            soma_linhas += matriz[i][j];
        }
    }
    clock_t fim = clock();
    double tempo_linhas = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000;
    
    // Acesso por colunas (cache-unfriendly)
    inicio = clock();
    long soma_colunas = 0;
    for (int j = 0; j < SIZE; j++) {
        for (int i = 0; i < SIZE; i++) {
            soma_colunas += matriz[i][j];
        }
    }
    fim = clock();
    double tempo_colunas = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000;
    
    printf("Matriz %dx%d:\n", SIZE, SIZE);
    printf("Acesso por linhas: %.2f ms (soma: %ld)\n", tempo_linhas, soma_linhas);
    printf("Acesso por colunas: %.2f ms (soma: %ld)\n", tempo_colunas, soma_colunas);
    printf("Diferença: %.2fx mais lento acessar por colunas\n", tempo_colunas/tempo_linhas);
    printf("Motivo: Cache misses devido ao padrão de acesso não-sequencial\n\n");
    
    liberar_matriz(matriz, SIZE);
}

// Rotação de matriz 90 graus
int** rotacionar_90_graus(int **matriz, int n) {
    printf("=== ROTAÇÃO DE MATRIZ 90° ===\n");
    printf("Rotacionando matriz %dx%d no sentido horário\n", n, n);
    
    int **rotacionada = alocar_matriz(n, n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            rotacionada[j][n-1-i] = matriz[i][j];
        }
    }
    
    printf("Fórmula: rotacionada[j][n-1-i] = original[i][j]\n\n");
    return rotacionada;
}

// Busca em matriz ordenada (Busca em escada)
int busca_matriz_ordenada(int **matriz, int linhas, int colunas, int target) {
    printf("=== BUSCA EM MATRIZ ORDENADA ===\n");
    printf("Procurando valor %d na matriz %dx%d\n", target, linhas, colunas);
    printf("Matriz ordenada por linhas e colunas\n");
    
    int i = 0, j = colunas - 1;  // Começar do canto superior direito
    int passos = 0;
    
    while (i < linhas && j >= 0) {
        passos++;
        printf("Passo %d: verificando posição [%d][%d] = %d\n", passos, i, j, matriz[i][j]);
        
        if (matriz[i][j] == target) {
            printf("Encontrado na posição [%d][%d] em %d passos!\n", i, j, passos);
            printf("Complexidade: O(linhas + colunas) = O(%d)\n\n", linhas + colunas);
            return 1;
        }
        else if (matriz[i][j] > target) {
            j--;  // Mover para a esquerda
        }
        else {
            i++;  // Mover para baixo
        }
    }
    
    printf("Valor não encontrado após %d passos\n\n", passos);
    return 0;
}

int main() {
    printf("***** EXEMPLOS AVANÇADOS DE MATRIZES *****\n\n");
    
    // 1. Demonstração de memória
    demonstracao_memoria_matriz();
    
    // 2. Multiplicação de matrizes
    int **A = alocar_matriz(3, 3);
    int **B = alocar_matriz(3, 3);
    
    // Preenchendo matrizes A e B
    int valores_A[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int valores_B[3][3] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            A[i][j] = valores_A[i][j];
            B[i][j] = valores_B[i][j];
        }
    }
    
    imprimir_matriz(A, 3, 3, "Matriz A");
    imprimir_matriz(B, 3, 3, "Matriz B");
    
    int **C = multiplicar_matrizes(A, B, 3, 3, 3);
    imprimir_matriz(C, 3, 3, "Resultado A × B");
    
    // 3. Transposição
    int **A_transposta = transpor_matriz(A, 3, 3);
    imprimir_matriz(A_transposta, 3, 3, "A Transposta");
    
    // 4. Rotação
    int **A_rotacionada = rotacionar_90_graus(A, 3);
    imprimir_matriz(A_rotacionada, 3, 3, "A Rotacionada 90°");
    
    // 5. Matriz esparsa
    demonstracao_matriz_esparsa();
    
    // 6. Otimização de cache
    demonstracao_cache_matriz();
    
    // 7. Busca em matriz ordenada
    int **matriz_ordenada = alocar_matriz(4, 4);
    int valores_ordenados[4][4] = {
        {1,  4,  7,  11},
        {2,  5,  8,  12},
        {3,  6,  9,  16},
        {10, 13, 14, 17}
    };
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matriz_ordenada[i][j] = valores_ordenados[i][j];
        }
    }
    
    imprimir_matriz(matriz_ordenada, 4, 4, "Matriz Ordenada");
    busca_matriz_ordenada(matriz_ordenada, 4, 4, 6);
    busca_matriz_ordenada(matriz_ordenada, 4, 4, 15);
    
    // Liberação de memória
    liberar_matriz(A, 3);
    liberar_matriz(B, 3);
    liberar_matriz(C, 3);
    liberar_matriz(A_transposta, 3);
    liberar_matriz(A_rotacionada, 3);
    liberar_matriz(matriz_ordenada, 4);
    
    printf("Todas as matrizes foram liberadas da memória!\n");
    
    return 0;
}