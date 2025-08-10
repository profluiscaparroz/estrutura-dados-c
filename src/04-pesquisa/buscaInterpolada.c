#include <stdio.h>
#include <stdlib.h>

/**
 * Busca Interpolada (Interpolation Search)
 * 
 * A busca interpolada é uma melhoria da busca binária para dados uniformemente distribuídos.
 * Em vez de sempre dividir o array pela metade, ela calcula uma posição aproximada 
 * baseada na distribuição dos valores.
 * 
 * Complexidade:
 * - Melhor caso: O(1)
 * - Caso médio: O(log log n) para dados uniformemente distribuídos
 * - Pior caso: O(n) para dados mal distribuídos
 * 
 * Pré-requisito: Array ordenado e dados uniformemente distribuídos
 */

// Implementação da busca interpolada
int buscaInterpolada(int array[], int tamanho, int elemento) {
    int esquerda = 0;
    int direita = tamanho - 1;
    
    // Verificação de limites
    while (esquerda <= direita && elemento >= array[esquerda] && elemento <= array[direita]) {
        
        // Se há apenas um elemento
        if (esquerda == direita) {
            return (array[esquerda] == elemento) ? esquerda : -1;
        }
        
        // Evitar divisão por zero
        if (array[direita] == array[esquerda]) {
            return (array[esquerda] == elemento) ? esquerda : -1;
        }
        
        // Fórmula de interpolação
        // pos = left + [(x - arr[left]) * (right - left)] / [arr[right] - arr[left]]
        int pos = esquerda + ((double)(elemento - array[esquerda]) * 
                              (direita - esquerda)) / (array[direita] - array[esquerda]);
        
        // Verificar se a posição calculada está dentro dos limites
        if (pos < esquerda || pos > direita) {
            break;
        }
        
        // Elemento encontrado
        if (array[pos] == elemento) {
            return pos;
        }
        
        // Ajustar os limites da busca
        if (array[pos] < elemento) {
            esquerda = pos + 1;
        } else {
            direita = pos - 1;
        }
    }
    
    return -1; // Elemento não encontrado
}

// Versão otimizada com proteção contra overflow
int buscaInterpoladaSegura(int array[], int tamanho, int elemento) {
    int esquerda = 0;
    int direita = tamanho - 1;
    
    while (esquerda <= direita && elemento >= array[esquerda] && elemento <= array[direita]) {
        
        if (esquerda == direita) {
            return (array[esquerda] == elemento) ? esquerda : -1;
        }
        
        if (array[direita] == array[esquerda]) {
            return (array[esquerda] == elemento) ? esquerda : -1;
        }
        
        // Usar aritmética de ponto flutuante para evitar overflow
        double ratio = (double)(elemento - array[esquerda]) / (array[direita] - array[esquerda]);
        int pos = esquerda + (int)(ratio * (direita - esquerda));
        
        // Garantir que pos está dentro dos limites
        if (pos < esquerda) pos = esquerda;
        if (pos > direita) pos = direita;
        
        if (array[pos] == elemento) {
            return pos;
        }
        
        if (array[pos] < elemento) {
            esquerda = pos + 1;
        } else {
            direita = pos - 1;
        }
    }
    
    return -1;
}

// Função para gerar array com distribuição uniforme
int* gerarArrayUniforme(int tamanho, int inicio, int fim) {
    int* array = (int*)malloc(tamanho * sizeof(int));
    if (array == NULL) {
        printf("Erro na alocação de memória\n");
        return NULL;
    }
    
    double incremento = (double)(fim - inicio) / (tamanho - 1);
    
    for (int i = 0; i < tamanho; i++) {
        array[i] = inicio + (int)(i * incremento);
    }
    
    return array;
}

// Função para imprimir array
void imprimirArray(int array[], int tamanho) {
    printf("Array: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// Comparação entre busca binária e interpolada
int buscaBinaria(int array[], int tamanho, int elemento) {
    int esquerda = 0;
    int direita = tamanho - 1;
    
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        
        if (array[meio] == elemento) {
            return meio;
        }
        
        if (array[meio] < elemento) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    
    return -1;
}

int main() {
    printf("=== Demonstração da Busca Interpolada ===\n\n");
    
    // Teste 1: Array pequeno com distribuição uniforme
    printf("Teste 1: Array pequeno com distribuição uniforme\n");
    int array1[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int tamanho1 = sizeof(array1) / sizeof(array1[0]);
    
    imprimirArray(array1, tamanho1);
    
    int buscar1 = 70;
    printf("Buscando elemento: %d\n", buscar1);
    
    int resultado_interpolada = buscaInterpolada(array1, tamanho1, buscar1);
    int resultado_binaria = buscaBinaria(array1, tamanho1, buscar1);
    
    printf("Busca Interpolada: %s na posição %d\n", 
           resultado_interpolada != -1 ? "Encontrado" : "Não encontrado", resultado_interpolada);
    printf("Busca Binária: %s na posição %d\n", 
           resultado_binaria != -1 ? "Encontrado" : "Não encontrado", resultado_binaria);
    
    printf("\n");
    
    // Teste 2: Array grande gerado automaticamente
    printf("Teste 2: Array grande com distribuição uniforme\n");
    int tamanho2 = 20;
    int* array2 = gerarArrayUniforme(tamanho2, 100, 300);
    
    if (array2 != NULL) {
        imprimirArray(array2, tamanho2);
        
        int buscar2 = 200;
        printf("Buscando elemento: %d\n", buscar2);
        
        resultado_interpolada = buscaInterpoladaSegura(array2, tamanho2, buscar2);
        resultado_binaria = buscaBinaria(array2, tamanho2, buscar2);
        
        printf("Busca Interpolada Segura: %s na posição %d\n", 
               resultado_interpolada != -1 ? "Encontrado" : "Não encontrado", resultado_interpolada);
        printf("Busca Binária: %s na posição %d\n", 
               resultado_binaria != -1 ? "Encontrado" : "Não encontrado", resultado_binaria);
        
        free(array2);
    }
    
    printf("\n");
    
    // Teste 3: Busca de elementos não existentes
    printf("Teste 3: Busca de elementos não existentes\n");
    int buscar3 = 35;
    printf("Buscando elemento inexistente: %d\n", buscar3);
    
    resultado_interpolada = buscaInterpolada(array1, tamanho1, buscar3);
    resultado_binaria = buscaBinaria(array1, tamanho1, buscar3);
    
    printf("Busca Interpolada: %s\n", 
           resultado_interpolada != -1 ? "Encontrado" : "Não encontrado");
    printf("Busca Binária: %s\n", 
           resultado_binaria != -1 ? "Encontrado" : "Não encontrado");
    
    printf("\n");
    
    // Teste 4: Array com distribuição não uniforme (pior caso para interpolação)
    printf("Teste 4: Array com distribuição não uniforme\n");
    int array3[] = {1, 2, 3, 4, 5, 1000, 2000, 3000, 4000, 5000};
    int tamanho3 = sizeof(array3) / sizeof(array3[0]);
    
    imprimirArray(array3, tamanho3);
    
    int buscar4 = 1000;
    printf("Buscando elemento: %d\n", buscar4);
    
    resultado_interpolada = buscaInterpolada(array3, tamanho3, buscar4);
    resultado_binaria = buscaBinaria(array3, tamanho3, buscar4);
    
    printf("Busca Interpolada: %s na posição %d\n", 
           resultado_interpolada != -1 ? "Encontrado" : "Não encontrado", resultado_interpolada);
    printf("Busca Binária: %s na posição %d\n", 
           resultado_binaria != -1 ? "Encontrado" : "Não encontrado", resultado_binaria);
    
    printf("\n=== Análise ===\n");
    printf("A busca interpolada é mais eficiente que a busca binária quando:\n");
    printf("1. Os dados estão uniformemente distribuídos\n");
    printf("2. O array é grande\n");
    printf("3. A distribuição dos valores é previsível\n\n");
    printf("Para arrays pequenos ou com distribuição irregular,\n");
    printf("a busca binária pode ser mais adequada.\n");
    
    return 0;
}