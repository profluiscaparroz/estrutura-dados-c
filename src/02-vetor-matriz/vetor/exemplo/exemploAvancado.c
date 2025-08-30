#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para demonstrar análise de complexidade temporal
void demonstracao_complexidade() {
    printf("=== DEMONSTRAÇÃO DE COMPLEXIDADE TEMPORAL ===\n\n");
    
    int vetor[1000];
    clock_t inicio, fim;
    
    // Preenchendo o vetor
    for (int i = 0; i < 1000; i++) {
        vetor[i] = i;
    }
    
    // 1. Acesso por índice - O(1)
    inicio = clock();
    int elemento = vetor[500];  // Acesso direto
    fim = clock();
    printf("1. Acesso por índice (O(1)): %d\n", elemento);
    printf("   Tempo: %f microssegundos\n\n", ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000000);
    
    // 2. Busca linear - O(n)
    inicio = clock();
    int encontrado = -1;
    for (int i = 0; i < 1000; i++) {
        if (vetor[i] == 500) {
            encontrado = i;
            break;
        }
    }
    fim = clock();
    printf("2. Busca linear (O(n)): encontrado na posição %d\n", encontrado);
    printf("   Tempo: %f microssegundos\n\n", ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000000);
}

// Função para demonstrar inserção no início - O(n)
void insercao_inicio(int vetor[], int *tamanho, int valor) {
    printf("=== INSERÇÃO NO INÍCIO DO VETOR ===\n");
    printf("Vetor antes da inserção: ");
    for (int i = 0; i < *tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
    
    // Desloca todos os elementos uma posição para a direita
    for (int i = *tamanho; i > 0; i--) {
        vetor[i] = vetor[i-1];
    }
    
    // Insere o novo valor no início
    vetor[0] = valor;
    (*tamanho)++;
    
    printf("Inserindo %d no início...\n", valor);
    printf("Vetor após inserção: ");
    for (int i = 0; i < *tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\nComplexidade: O(n) - todos os elementos foram deslocados\n\n");
}

// Função para demonstrar gerenciamento de memória dinâmica
void demonstracao_memoria_dinamica() {
    printf("=== ALOCAÇÃO DINÂMICA DE VETORES ===\n");
    
    int tamanho;
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &tamanho);
    
    // Alocação dinâmica
    int *vetor = malloc(tamanho * sizeof(int));
    if (vetor == NULL) {
        printf("Erro na alocação de memória!\n");
        return;
    }
    
    printf("Vetor alocado dinamicamente com %d elementos\n", tamanho);
    printf("Endereço base: %p\n", (void*)vetor);
    
    // Preenchimento
    for (int i = 0; i < tamanho; i++) {
        vetor[i] = i * i;
        printf("vetor[%d] = %d (endereço: %p)\n", i, vetor[i], (void*)&vetor[i]);
    }
    
    // Redimensionamento
    printf("\nRedimensionando vetor para %d elementos...\n", tamanho * 2);
    vetor = realloc(vetor, tamanho * 2 * sizeof(int));
    if (vetor == NULL) {
        printf("Erro no redimensionamento!\n");
        return;
    }
    
    // Preenchendo novos elementos
    for (int i = tamanho; i < tamanho * 2; i++) {
        vetor[i] = i * i;
    }
    
    printf("Novo endereço base: %p\n", (void*)vetor);
    printf("Todos os elementos:\n");
    for (int i = 0; i < tamanho * 2; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
    
    // Liberação da memória
    free(vetor);
    printf("Memória liberada com sucesso!\n\n");
}

// Algoritmo de Kadane para maior subarray contíguo
int kadane_algorithm(int arr[], int n) {
    printf("=== ALGORITMO DE KADANE (MAIOR SUBARRAY) ===\n");
    printf("Vetor: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    int max_atual = arr[0];
    int max_global = arr[0];
    int inicio = 0, fim = 0, inicio_temp = 0;
    
    printf("\nProcessamento passo a passo:\n");
    printf("i=0: max_atual=%d, max_global=%d\n", max_atual, max_global);
    
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_atual + arr[i]) {
            max_atual = arr[i];
            inicio_temp = i;
        } else {
            max_atual = max_atual + arr[i];
        }
        
        if (max_atual > max_global) {
            max_global = max_atual;
            inicio = inicio_temp;
            fim = i;
        }
        
        printf("i=%d: max_atual=%d, max_global=%d\n", i, max_atual, max_global);
    }
    
    printf("\nMaior subarray: ");
    for (int i = inicio; i <= fim; i++) {
        printf("%d ", arr[i]);
    }
    printf("\nSoma máxima: %d\n\n", max_global);
    
    return max_global;
}

// Demonstração de diferentes formas de passagem de parâmetros
void exemplo_passagem_parametros(int arr[], int *arr_ptr, int tamanho) {
    printf("=== PASSAGEM DE VETORES COMO PARÂMETROS ===\n");
    printf("Dentro da função:\n");
    printf("sizeof(arr): %lu bytes\n", sizeof(arr));  // Sempre sizeof(int*)
    printf("sizeof(arr_ptr): %lu bytes\n", sizeof(arr_ptr));  // Sempre sizeof(int*)
    printf("Endereço recebido: %p\n", (void*)arr);
    
    // Modificando o vetor (afeta o original)
    for (int i = 0; i < tamanho; i++) {
        arr[i] *= 2;
    }
    printf("Valores multiplicados por 2\n\n");
}

// Análise de localidade de cache
void demonstracao_cache_locality() {
    printf("=== LOCALIDADE DE CACHE ===\n");
    const int TAMANHO = 1000000;
    int *vetor = malloc(TAMANHO * sizeof(int));
    
    // Preenchimento inicial
    for (int i = 0; i < TAMANHO; i++) {
        vetor[i] = i;
    }
    
    clock_t inicio, fim;
    
    // Acesso sequencial (cache-friendly)
    inicio = clock();
    long soma_sequencial = 0;
    for (int i = 0; i < TAMANHO; i++) {
        soma_sequencial += vetor[i];
    }
    fim = clock();
    double tempo_sequencial = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000;
    
    // Acesso aleatório (cache-unfriendly)
    inicio = clock();
    long soma_aleatoria = 0;
    for (int i = 0; i < TAMANHO; i += 16) {  // Saltando 16 posições
        soma_aleatoria += vetor[i];
    }
    fim = clock();
    double tempo_aleatorio = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000;
    
    printf("Acesso sequencial: %.2f ms (soma: %ld)\n", tempo_sequencial, soma_sequencial);
    printf("Acesso com saltos: %.2f ms (soma parcial: %ld)\n", tempo_aleatorio, soma_aleatoria);
    printf("Diferença de performance: %.2fx mais rápido\n\n", tempo_aleatorio/tempo_sequencial);
    
    free(vetor);
}

int main() {
    printf("***** EXEMPLOS AVANÇADOS DE VETORES *****\n\n");
    
    // 1. Demonstração de complexidade
    demonstracao_complexidade();
    
    // 2. Inserção no início
    int vetor_teste[10] = {1, 2, 3, 4, 5};
    int tamanho = 5;
    insercao_inicio(vetor_teste, &tamanho, 0);
    
    // 3. Memória dinâmica
    demonstracao_memoria_dinamica();
    
    // 4. Algoritmo de Kadane
    int arr_kadane[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int n = sizeof(arr_kadane) / sizeof(arr_kadane[0]);
    kadane_algorithm(arr_kadane, n);
    
    // 5. Passagem de parâmetros
    int arr_param[] = {1, 2, 3, 4, 5};
    int tamanho_param = 5;
    printf("Antes da função: ");
    for (int i = 0; i < tamanho_param; i++) {
        printf("%d ", arr_param[i]);
    }
    printf("\n");
    
    exemplo_passagem_parametros(arr_param, arr_param, tamanho_param);
    
    printf("Depois da função: ");
    for (int i = 0; i < tamanho_param; i++) {
        printf("%d ", arr_param[i]);
    }
    printf("\n\n");
    
    // 6. Localidade de cache
    demonstracao_cache_locality();
    
    return 0;
}