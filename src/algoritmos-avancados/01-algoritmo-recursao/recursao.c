/**
 * ============================================================================
 * ALGORITMOS RECURSIVOS - FUNDAMENTOS
 * ============================================================================
 * 
 * Este arquivo demonstra os conceitos fundamentais de recursão em C,
 * servindo como base para entender algoritmos avançados que utilizam
 * técnicas recursivas.
 * 
 * Conceitos abordados:
 * - Caso base e caso recursivo
 * - Recursão direta e indireta
 * - Recursão de cauda (tail recursion)
 * - Memoização básica
 * 
 * A recursão é fundamental para entender:
 * - Algoritmos de divisão e conquista
 * - Travessia de árvores e grafos
 * - Backtracking
 * - Programação dinâmica
 * 
 * Autor: Estrutura de Dados em C
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==================== FATORIAL ====================

/**
 * Fatorial recursivo simples
 * Complexidade: O(n) tempo, O(n) espaço (pilha)
 */
long fatorial(int n) {
    // Caso base
    if (n <= 1) {
        return 1;
    }
    // Caso recursivo
    return n * fatorial(n - 1);
}

/**
 * Fatorial com recursão de cauda (tail recursion)
 * Compiladores podem otimizar para iteração
 * Complexidade: O(n) tempo, O(1) espaço (com otimização)
 */
long fatorial_tail(int n, long acumulador) {
    if (n <= 1) {
        return acumulador;
    }
    return fatorial_tail(n - 1, n * acumulador);
}

// ==================== FIBONACCI ====================

/**
 * Fibonacci recursivo ingênuo
 * Complexidade: O(2^n) tempo - MUITO INEFICIENTE!
 * Demonstra problema de recálculo
 */
long fibonacci_ingenuo(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci_ingenuo(n - 1) + fibonacci_ingenuo(n - 2);
}

// Cache para memoização (inicializado com -1 para indicar não calculado)
static long memo[100];
static int memo_initialized = 0;

/**
 * Inicializar cache de memoização
 */
void init_memo() {
    for (int i = 0; i < 100; i++) {
        memo[i] = -1;
    }
    memo_initialized = 1;
}

/**
 * Fibonacci com memoização
 * Complexidade: O(n) tempo, O(n) espaço
 */
long fibonacci_memo(int n) {
    if (!memo_initialized) {
        init_memo();
    }
    
    if (n <= 1) {
        return n;
    }
    
    // Verificar se já calculamos
    if (memo[n] != -1) {
        return memo[n];
    }
    
    // Calcular e armazenar
    memo[n] = fibonacci_memo(n - 1) + fibonacci_memo(n - 2);
    return memo[n];
}

// ==================== SOMA DE ARRAY ====================

/**
 * Soma de array usando recursão
 * Demonstra divisão do problema
 */
int soma_array(int arr[], int n) {
    // Caso base
    if (n <= 0) {
        return 0;
    }
    // Soma o último elemento com a soma do resto
    return arr[n - 1] + soma_array(arr, n - 1);
}

/**
 * Soma de array usando divisão (divide and conquer style)
 */
int soma_array_divisao(int arr[], int inicio, int fim) {
    // Caso base: um elemento
    if (inicio == fim) {
        return arr[inicio];
    }
    
    // Dividir ao meio
    int meio = (inicio + fim) / 2;
    
    // Conquistar: somar cada metade
    int soma_esq = soma_array_divisao(arr, inicio, meio);
    int soma_dir = soma_array_divisao(arr, meio + 1, fim);
    
    // Combinar
    return soma_esq + soma_dir;
}

// ==================== BUSCA BINÁRIA RECURSIVA ====================

/**
 * Busca binária recursiva
 * Pré-requisito: array ordenado
 * Complexidade: O(log n) tempo
 */
int busca_binaria(int arr[], int inicio, int fim, int chave) {
    // Caso base: não encontrado
    if (inicio > fim) {
        return -1;
    }
    
    int meio = inicio + (fim - inicio) / 2;
    
    // Caso base: encontrado
    if (arr[meio] == chave) {
        return meio;
    }
    
    // Caso recursivo: buscar na metade apropriada
    if (chave < arr[meio]) {
        return busca_binaria(arr, inicio, meio - 1, chave);
    } else {
        return busca_binaria(arr, meio + 1, fim, chave);
    }
}

// ==================== TORRE DE HANOI ====================

int movimentos_hanoi = 0;

/**
 * Torre de Hanoi
 * Demonstra recursão com múltiplas chamadas
 * Complexidade: O(2^n) movimentos
 */
void torre_hanoi(int n, char origem, char destino, char auxiliar) {
    if (n == 1) {
        printf("Mover disco 1 de %c para %c\n", origem, destino);
        movimentos_hanoi++;
        return;
    }
    
    // Mover n-1 discos para auxiliar
    torre_hanoi(n - 1, origem, auxiliar, destino);
    
    // Mover disco maior para destino
    printf("Mover disco %d de %c para %c\n", n, origem, destino);
    movimentos_hanoi++;
    
    // Mover n-1 discos do auxiliar para destino
    torre_hanoi(n - 1, auxiliar, destino, origem);
}

// ==================== POTÊNCIA ====================

/**
 * Potência recursiva ingênua
 * Complexidade: O(n)
 */
long potencia_ingenua(int base, int exp) {
    if (exp == 0) {
        return 1;
    }
    return base * potencia_ingenua(base, exp - 1);
}

/**
 * Potência com exponenciação rápida (binary exponentiation)
 * Complexidade: O(log n)
 * 
 * Ideia: x^n = (x^(n/2))^2 se n é par
 *        x^n = x * (x^(n/2))^2 se n é ímpar
 */
long potencia_rapida(int base, int exp) {
    if (exp == 0) {
        return 1;
    }
    
    // Calcula metade
    long metade = potencia_rapida(base, exp / 2);
    
    // Combina
    if (exp % 2 == 0) {
        return metade * metade;
    } else {
        return base * metade * metade;
    }
}

// ==================== INVERTER STRING ====================

/**
 * Inverte string recursivamente
 */
void inverter_string(char *str, int inicio, int fim) {
    // Caso base
    if (inicio >= fim) {
        return;
    }
    
    // Trocar caracteres
    char temp = str[inicio];
    str[inicio] = str[fim];
    str[fim] = temp;
    
    // Recursão no resto
    inverter_string(str, inicio + 1, fim - 1);
}

// ==================== PALINDROMO ====================

/**
 * Verifica se string é palíndromo
 */
int eh_palindromo(char *str, int inicio, int fim) {
    // Caso base: string vazia ou um caractere
    if (inicio >= fim) {
        return 1; // É palíndromo
    }
    
    // Se caracteres não correspondem, não é palíndromo
    if (str[inicio] != str[fim]) {
        return 0;
    }
    
    // Verificar o resto
    return eh_palindromo(str, inicio + 1, fim - 1);
}

// ==================== MDC (ALGORITMO DE EUCLIDES) ====================

/**
 * Máximo Divisor Comum - Algoritmo de Euclides
 * Um dos algoritmos mais antigos conhecidos
 * Complexidade: O(log(min(a,b)))
 */
int mdc(int a, int b) {
    // Caso base
    if (b == 0) {
        return a;
    }
    // Caso recursivo
    return mdc(b, a % b);
}

// ==================== FUNÇÕES DE TESTE ====================

void testar_fatorial() {
    printf("=== TESTE FATORIAL ===\n");
    printf("Fatorial de 5: %ld\n", fatorial(5));
    printf("Fatorial de 10: %ld\n", fatorial(10));
    printf("Fatorial tail de 5: %ld\n", fatorial_tail(5, 1));
    printf("Fatorial tail de 10: %ld\n", fatorial_tail(10, 1));
    printf("\n");
}

void testar_fibonacci() {
    printf("=== TESTE FIBONACCI ===\n");
    
    // Reinicializar memo
    memo_initialized = 0;
    
    printf("Fibonacci ingênuo (n=20): %ld\n", fibonacci_ingenuo(20));
    printf("Fibonacci com memo (n=20): %ld\n", fibonacci_memo(20));
    printf("Fibonacci com memo (n=40): %ld\n", fibonacci_memo(40));
    
    printf("\nSequência Fibonacci (0-10): ");
    memo_initialized = 0;  // Reinicializar para nova sequência
    for (int i = 0; i <= 10; i++) {
        printf("%ld ", fibonacci_memo(i));
    }
    printf("\n\n");
}

void testar_soma_array() {
    printf("=== TESTE SOMA ARRAY ===\n");
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Array: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]\n");
    printf("Soma linear: %d\n", soma_array(arr, n));
    printf("Soma divisão: %d\n", soma_array_divisao(arr, 0, n - 1));
    printf("\n");
}

void testar_busca_binaria() {
    printf("=== TESTE BUSCA BINÁRIA ===\n");
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Array ordenado: [1, 3, 5, 7, 9, 11, 13, 15, 17, 19]\n");
    printf("Buscar 7: índice %d\n", busca_binaria(arr, 0, n - 1, 7));
    printf("Buscar 15: índice %d\n", busca_binaria(arr, 0, n - 1, 15));
    printf("Buscar 8: índice %d\n", busca_binaria(arr, 0, n - 1, 8));
    printf("\n");
}

void testar_hanoi() {
    printf("=== TESTE TORRE DE HANOI (3 discos) ===\n");
    movimentos_hanoi = 0;
    torre_hanoi(3, 'A', 'C', 'B');
    printf("Total de movimentos: %d (esperado: 2^3 - 1 = 7)\n\n", movimentos_hanoi);
}

void testar_potencia() {
    printf("=== TESTE POTÊNCIA ===\n");
    printf("2^10 (ingênua): %ld\n", potencia_ingenua(2, 10));
    printf("2^10 (rápida): %ld\n", potencia_rapida(2, 10));
    printf("3^5 (rápida): %ld\n", potencia_rapida(3, 5));
    printf("2^20 (rápida): %ld\n", potencia_rapida(2, 20));
    printf("\n");
}

void testar_string() {
    printf("=== TESTE STRING ===\n");
    
    char str[] = "recursao";
    printf("String original: %s\n", str);
    inverter_string(str, 0, strlen(str) - 1);
    printf("String invertida: %s\n", str);
    
    char palindromo1[] = "ana";
    char palindromo2[] = "arara";
    char nao_palindromo[] = "teste";
    
    printf("\n'%s' é palíndromo? %s\n", palindromo1, 
           eh_palindromo(palindromo1, 0, strlen(palindromo1) - 1) ? "Sim" : "Não");
    printf("'%s' é palíndromo? %s\n", palindromo2, 
           eh_palindromo(palindromo2, 0, strlen(palindromo2) - 1) ? "Sim" : "Não");
    printf("'%s' é palíndromo? %s\n", nao_palindromo, 
           eh_palindromo(nao_palindromo, 0, strlen(nao_palindromo) - 1) ? "Sim" : "Não");
    printf("\n");
}

void testar_mdc() {
    printf("=== TESTE MDC (Euclides) ===\n");
    printf("MDC(48, 18) = %d\n", mdc(48, 18));
    printf("MDC(100, 25) = %d\n", mdc(100, 25));
    printf("MDC(17, 13) = %d\n", mdc(17, 13));
    printf("\n");
}

// ==================== FUNÇÃO PRINCIPAL ====================

int main() {
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║        ALGORITMOS RECURSIVOS - FUNDAMENTOS               ║\n");
    printf("║   Base para Estruturas de Dados Avançadas                ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    testar_fatorial();
    testar_fibonacci();
    testar_soma_array();
    testar_busca_binaria();
    testar_hanoi();
    testar_potencia();
    testar_string();
    testar_mdc();
    
    printf("═══════════════════════════════════════════════════════════\n");
    printf("Recursão é fundamental para entender:\n");
    printf("- Divisão e conquista (próximo tópico)\n");
    printf("- Travessia de árvores e grafos\n");
    printf("- Backtracking\n");
    printf("- Programação dinâmica\n");
    printf("═══════════════════════════════════════════════════════════\n");
    
    return 0;
}
