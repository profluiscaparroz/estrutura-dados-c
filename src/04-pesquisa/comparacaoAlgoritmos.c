#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/**
 * Programa de Comparação Completa de Algoritmos de Busca
 * 
 * Este programa implementa e compara diferentes algoritmos de busca:
 * 1. Busca Linear
 * 2. Busca Linear com Sentinela
 * 3. Busca Binária Iterativa
 * 4. Busca Binária Recursiva
 * 5. Busca Interpolada
 * 6. Busca Exponencial + Binária
 * 
 * Inclui medição de performance e análise comparativa.
 */

// Estrutura para armazenar resultados de benchmark
typedef struct {
    char nome[50];
    int encontrado;
    int posicao;
    double tempo;
    int comparacoes;
} ResultadoBusca;

// Variável global para contar comparações
int contador_comparacoes = 0;

// ============= IMPLEMENTAÇÕES DOS ALGORITMOS =============

// 1. Busca Linear
int buscaLinear(int array[], int tamanho, int elemento) {
    contador_comparacoes = 0;
    for (int i = 0; i < tamanho; i++) {
        contador_comparacoes++;
        if (array[i] == elemento) {
            return i;
        }
    }
    return -1;
}

// 2. Busca Linear com Sentinela
int buscaLinearSentinela(int array[], int tamanho, int elemento) {
    contador_comparacoes = 0;
    if (tamanho == 0) return -1;
    
    int backup = array[tamanho - 1];
    array[tamanho - 1] = elemento;
    
    int i = 0;
    while (array[i] != elemento) {
        i++;
        contador_comparacoes++;
    }
    contador_comparacoes++; // Comparação final
    
    array[tamanho - 1] = backup;
    
    return (i < tamanho - 1 || backup == elemento) ? i : -1;
}

// 3. Busca Binária Iterativa
int buscaBinariaIterativa(int array[], int tamanho, int elemento) {
    contador_comparacoes = 0;
    int esquerda = 0;
    int direita = tamanho - 1;
    
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        contador_comparacoes++;
        
        if (array[meio] == elemento) {
            return meio;
        }
        
        contador_comparacoes++;
        if (array[meio] < elemento) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    
    return -1;
}

// 4. Busca Binária Recursiva
int buscaBinariaRecursivaAux(int array[], int esquerda, int direita, int elemento) {
    if (esquerda > direita) {
        return -1;
    }
    
    int meio = esquerda + (direita - esquerda) / 2;
    contador_comparacoes++;
    
    if (array[meio] == elemento) {
        return meio;
    }
    
    contador_comparacoes++;
    if (array[meio] > elemento) {
        return buscaBinariaRecursivaAux(array, esquerda, meio - 1, elemento);
    }
    
    return buscaBinariaRecursivaAux(array, meio + 1, direita, elemento);
}

int buscaBinariaRecursiva(int array[], int tamanho, int elemento) {
    contador_comparacoes = 0;
    return buscaBinariaRecursivaAux(array, 0, tamanho - 1, elemento);
}

// 5. Busca Interpolada
int buscaInterpolada(int array[], int tamanho, int elemento) {
    contador_comparacoes = 0;
    int esquerda = 0;
    int direita = tamanho - 1;
    
    while (esquerda <= direita && elemento >= array[esquerda] && elemento <= array[direita]) {
        contador_comparacoes += 2; // Comparações de limites
        
        if (esquerda == direita) {
            contador_comparacoes++;
            return (array[esquerda] == elemento) ? esquerda : -1;
        }
        
        if (array[direita] == array[esquerda]) {
            contador_comparacoes++;
            return (array[esquerda] == elemento) ? esquerda : -1;
        }
        
        // Fórmula de interpolação
        int pos = esquerda + ((double)(elemento - array[esquerda]) * 
                              (direita - esquerda)) / (array[direita] - array[esquerda]);
        
        // Garantir que pos está dentro dos limites
        if (pos < esquerda) pos = esquerda;
        if (pos > direita) pos = direita;
        
        contador_comparacoes++;
        if (array[pos] == elemento) {
            return pos;
        }
        
        contador_comparacoes++;
        if (array[pos] < elemento) {
            esquerda = pos + 1;
        } else {
            direita = pos - 1;
        }
    }
    
    return -1;
}

// 6. Busca Exponencial + Binária
int buscaExponencial(int array[], int tamanho, int elemento) {
    contador_comparacoes = 0;
    
    // Se o elemento está na primeira posição
    contador_comparacoes++;
    if (array[0] == elemento) {
        return 0;
    }
    
    // Encontrar o intervalo onde o elemento pode estar
    int bound = 1;
    while (bound < tamanho && array[bound] < elemento) {
        contador_comparacoes += 2;
        bound *= 2;
    }
    
    // Busca binária no intervalo [bound/2, min(bound, tamanho-1)]
    int esquerda = bound / 2;
    int direita = (bound < tamanho) ? bound : tamanho - 1;
    
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        contador_comparacoes++;
        
        if (array[meio] == elemento) {
            return meio;
        }
        
        contador_comparacoes++;
        if (array[meio] < elemento) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    
    return -1;
}

// ============= FUNÇÕES AUXILIARES =============

// Função para medir tempo de execução
double medirTempo(clock_t inicio, clock_t fim) {
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000; // Em milissegundos
}

// Gerar array ordenado
int* gerarArrayOrdenado(int tamanho, int inicio, int incremento) {
    int* array = (int*)malloc(tamanho * sizeof(int));
    if (array == NULL) {
        printf("Erro na alocação de memória\n");
        return NULL;
    }
    
    for (int i = 0; i < tamanho; i++) {
        array[i] = inicio + i * incremento;
    }
    
    return array;
}

// Executar e medir um algoritmo de busca
ResultadoBusca executarBusca(const char* nome, int (*algoritmo)(int[], int, int), 
                            int array[], int tamanho, int elemento) {
    ResultadoBusca resultado;
    strcpy(resultado.nome, nome);
    
    clock_t inicio = clock();
    resultado.posicao = algoritmo(array, tamanho, elemento);
    clock_t fim = clock();
    
    resultado.encontrado = (resultado.posicao != -1);
    resultado.tempo = medirTempo(inicio, fim);
    resultado.comparacoes = contador_comparacoes;
    
    return resultado;
}

// Imprimir resultados de forma organizada
void imprimirResultados(ResultadoBusca resultados[], int numResultados) {
    printf("\n=== RESULTADOS DA BUSCA ===\n");
    printf("%-25s %-12s %-10s %-15s %-12s\n", 
           "Algoritmo", "Encontrado", "Posição", "Tempo (ms)", "Comparações");
    printf("%-25s %-12s %-10s %-15s %-12s\n", 
           "-------------------------", "----------", "--------", "-------------", "----------");
    
    for (int i = 0; i < numResultados; i++) {
        printf("%-25s %-12s %-10d %-15.6f %-12d\n",
               resultados[i].nome,
               resultados[i].encontrado ? "Sim" : "Não",
               resultados[i].posicao,
               resultados[i].tempo,
               resultados[i].comparacoes);
    }
}

// Análise comparativa
void analisarResultados(ResultadoBusca resultados[], int numResultados) {
    printf("\n=== ANÁLISE COMPARATIVA ===\n");
    
    // Encontrar o mais rápido
    int maisRapido = 0;
    for (int i = 1; i < numResultados; i++) {
        if (resultados[i].tempo < resultados[maisRapido].tempo) {
            maisRapido = i;
        }
    }
    
    // Encontrar o com menos comparações
    int menosComparacoes = 0;
    for (int i = 1; i < numResultados; i++) {
        if (resultados[i].comparacoes < resultados[menosComparacoes].comparacoes) {
            menosComparacoes = i;
        }
    }
    
    printf("Algoritmo mais rápido: %s (%.6f ms)\n", 
           resultados[maisRapido].nome, resultados[maisRapido].tempo);
    printf("Algoritmo com menos comparações: %s (%d comparações)\n", 
           resultados[menosComparacoes].nome, resultados[menosComparacoes].comparacoes);
}

int main() {
    printf("=== COMPARAÇÃO COMPLETA DE ALGORITMOS DE BUSCA ===\n");
    
    // Configuração do teste
    const int TAMANHO = 10000;
    const int INICIO = 10;
    const int INCREMENTO = 5;
    int* array = gerarArrayOrdenado(TAMANHO, INICIO, INCREMENTO);
    
    if (array == NULL) {
        return 1;
    }
    
    // Elemento a ser buscado (garantidamente existe)
    int elemento = array[TAMANHO * 3 / 4]; // 75% do array
    
    printf("Tamanho do array: %d elementos\n", TAMANHO);
    printf("Elemento buscado: %d\n", elemento);
    printf("Posição real: %d\n", TAMANHO * 3 / 4);
    
    // Array para armazenar resultados
    ResultadoBusca resultados[6];
    int numResultados = 0;
    
    // Executar todos os algoritmos
    resultados[numResultados++] = executarBusca("Busca Linear", buscaLinear, array, TAMANHO, elemento);
    resultados[numResultados++] = executarBusca("Linear c/ Sentinela", buscaLinearSentinela, array, TAMANHO, elemento);
    resultados[numResultados++] = executarBusca("Binária Iterativa", buscaBinariaIterativa, array, TAMANHO, elemento);
    resultados[numResultados++] = executarBusca("Binária Recursiva", buscaBinariaRecursiva, array, TAMANHO, elemento);
    resultados[numResultados++] = executarBusca("Busca Interpolada", buscaInterpolada, array, TAMANHO, elemento);
    resultados[numResultados++] = executarBusca("Busca Exponencial", buscaExponencial, array, TAMANHO, elemento);
    
    // Imprimir e analisar resultados
    imprimirResultados(resultados, numResultados);
    analisarResultados(resultados, numResultados);
    
    // Teste com elemento inexistente
    printf("\n=== TESTE COM ELEMENTO INEXISTENTE ===\n");
    int elementoInexistente = -1;
    printf("Buscando elemento inexistente: %d\n", elementoInexistente);
    
    ResultadoBusca resultadosInexistente[6];
    int numResultadosInexistente = 0;
    
    resultadosInexistente[numResultadosInexistente++] = executarBusca("Busca Linear", buscaLinear, array, TAMANHO, elementoInexistente);
    resultadosInexistente[numResultadosInexistente++] = executarBusca("Linear c/ Sentinela", buscaLinearSentinela, array, TAMANHO, elementoInexistente);
    resultadosInexistente[numResultadosInexistente++] = executarBusca("Binária Iterativa", buscaBinariaIterativa, array, TAMANHO, elementoInexistente);
    resultadosInexistente[numResultadosInexistente++] = executarBusca("Binária Recursiva", buscaBinariaRecursiva, array, TAMANHO, elementoInexistente);
    resultadosInexistente[numResultadosInexistente++] = executarBusca("Busca Interpolada", buscaInterpolada, array, TAMANHO, elementoInexistente);
    resultadosInexistente[numResultadosInexistente++] = executarBusca("Busca Exponencial", buscaExponencial, array, TAMANHO, elementoInexistente);
    
    imprimirResultados(resultadosInexistente, numResultadosInexistente);
    
    // Recomendações
    printf("\n=== RECOMENDAÇÕES DE USO ===\n");
    printf("1. Busca Linear: Use para arrays pequenos ou não ordenados\n");
    printf("2. Busca Linear com Sentinela: Otimização da linear para arrays pequenos\n");
    printf("3. Busca Binária: Melhor escolha geral para arrays ordenados\n");
    printf("4. Busca Interpolada: Use para dados uniformemente distribuídos\n");
    printf("5. Busca Exponencial: Use quando não souber o tamanho exato ou para dados próximos ao início\n");
    
    // Limpeza de memória
    free(array);
    
    return 0;
}