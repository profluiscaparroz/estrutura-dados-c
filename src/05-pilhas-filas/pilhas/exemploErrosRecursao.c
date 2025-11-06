#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// =================================================================
// DEMONSTRAÇÃO DE ERROS RELACIONADOS À PILHA DE RECURSÃO
// =================================================================
// Este arquivo demonstra problemas comuns com stack overflow
// causados por recursão excessiva, que é um erro frequente em
// algoritmos avançados.
// =================================================================

// Contador global para rastrear profundidade de recursão
int profundidadeRecursao = 0;
int maxProfundidade = 0;

// =================================================================
// EXEMPLO 1: Recursão infinita (causa stack overflow)
// =================================================================

// Função com recursão infinita - NUNCA USAR!
void recursaoInfinita(int n) {
    profundidadeRecursao++;
    if (profundidadeRecursao > maxProfundidade) {
        maxProfundidade = profundidadeRecursao;
    }
    
    // Sem caso base - recursão nunca para!
    printf("Nível %d\n", n);
    recursaoInfinita(n + 1);  // ERRO: Nunca para!
    
    profundidadeRecursao--;
}

// Demonstração controlada de recursão profunda
void demonstrarRecursaoInfinita() {
    printf("=== EXEMPLO 1: RECURSÃO INFINITA ===\n");
    printf("AVISO: Código comentado para evitar stack overflow!\n\n");
    
    printf("Recursão infinita ocorre quando:\n");
    printf("  - Falta caso base (condição de parada)\n");
    printf("  - Caso base nunca é alcançado\n");
    printf("  - Cada chamada adiciona frame na pilha\n");
    printf("  - Eventualmente: Stack Overflow!\n\n");
    
    printf("Código problemático:\n");
    printf("  void recursaoInfinita(int n) {\n");
    printf("      printf(\"Nível %%d\\n\", n);\n");
    printf("      recursaoInfinita(n + 1);  // ERRO: Sem caso base!\n");
    printf("  }\n\n");
    
    // NÃO EXECUTAR: causaria stack overflow
    // recursaoInfinita(0);
    
    printf("Resultado: Programa trava com 'Segmentation fault' ou 'Stack overflow'\n");
}

// =================================================================
// EXEMPLO 2: Recursão profunda demais (Fibonacci ingênuo)
// =================================================================

// Fibonacci recursivo ingênuo - ineficiente e pode causar stack overflow
long long fibonacciRecursivoIngenuo(int n) {
    profundidadeRecursao++;
    if (profundidadeRecursao > maxProfundidade) {
        maxProfundidade = profundidadeRecursao;
    }
    
    if (n <= 1) {
        profundidadeRecursao--;
        return n;
    }
    
    long long resultado = fibonacciRecursivoIngenuo(n - 1) + fibonacciRecursivoIngenuo(n - 2);
    profundidadeRecursao--;
    return resultado;
}

// Fibonacci iterativo - solução eficiente
long long fibonacciIterativo(int n) {
    if (n <= 1) return n;
    
    long long a = 0, b = 1, temp;
    for (int i = 2; i <= n; i++) {
        temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

void demonstrarFibonacciRecursivo() {
    printf("\n=== EXEMPLO 2: RECURSÃO PROFUNDA (FIBONACCI) ===\n\n");
    
    printf("Fibonacci recursivo ingênuo tem problemas:\n");
    printf("  1. Recalcula mesmos valores múltiplas vezes\n");
    printf("  2. Complexidade exponencial O(2^n)\n");
    printf("  3. Pode causar stack overflow para n grande\n\n");
    
    int valores[] = {10, 20, 30, 35};
    int numValores = sizeof(valores) / sizeof(valores[0]);
    
    for (int i = 0; i < numValores; i++) {
        int n = valores[i];
        profundidadeRecursao = 0;
        maxProfundidade = 0;
        
        printf("Fibonacci(%d):\n", n);
        
        if (n <= 35) {  // Limite de segurança
            long long resultado = fibonacciRecursivoIngenuo(n);
            printf("  Recursivo: %lld (profundidade máxima: %d)\n", resultado, maxProfundidade);
        } else {
            printf("  Recursivo: IGNORADO (muito lento e arriscado)\n");
        }
        
        long long resultadoIter = fibonacciIterativo(n);
        printf("  Iterativo: %lld (sem risco de stack overflow)\n\n", resultadoIter);
    }
    
    printf("AVISO: Não tente fibonacci(50) com versão recursiva!\n");
    printf("        Levaria horas e poderia causar stack overflow.\n");
}

// =================================================================
// EXEMPLO 3: Árvore binária muito profunda
// =================================================================

typedef struct Node {
    int valor;
    struct Node* esquerda;
    struct Node* direita;
} Node;

Node* criarNo(int valor) {
    Node* novo = (Node*)malloc(sizeof(Node));
    if (novo == NULL) {
        printf("ERRO: Falha ao alocar memória!\n");
        exit(1);
    }
    novo->valor = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// Criar árvore degenerada (como lista ligada) - pior caso
Node* criarArvoreDegenerada(int altura) {
    if (altura == 0) return NULL;
    
    Node* raiz = criarNo(altura);
    raiz->esquerda = criarArvoreDegenerada(altura - 1);
    return raiz;
}

// Percorrer árvore com recursão - pode causar stack overflow
void percorrerInOrdem(Node* raiz, int nivel) {
    if (raiz == NULL) return;
    
    profundidadeRecursao++;
    if (profundidadeRecursao > maxProfundidade) {
        maxProfundidade = profundidadeRecursao;
    }
    
    percorrerInOrdem(raiz->esquerda, nivel + 1);
    // printf("Nível %d: %d\n", nivel, raiz->valor);
    percorrerInOrdem(raiz->direita, nivel + 1);
    
    profundidadeRecursao--;
}

void liberarArvore(Node* raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}

void demonstrarArvoreRecursiva() {
    printf("\n=== EXEMPLO 3: ÁRVORE BINÁRIA PROFUNDA ===\n\n");
    
    printf("Árvore degenerada (pior caso) causa problemas:\n");
    printf("  - Comporta-se como lista ligada\n");
    printf("  - Altura = número de nós\n");
    printf("  - Recursão atinge profundidade = altura\n");
    printf("  - Pode causar stack overflow\n\n");
    
    int alturas[] = {10, 100, 1000, 5000};
    int numAlturas = sizeof(alturas) / sizeof(alturas[0]);
    
    for (int i = 0; i < numAlturas; i++) {
        int altura = alturas[i];
        profundidadeRecursao = 0;
        maxProfundidade = 0;
        
        printf("Árvore com altura %d:\n", altura);
        
        if (altura <= 5000) {  // Limite de segurança
            Node* raiz = criarArvoreDegenerada(altura);
            percorrerInOrdem(raiz, 0);
            printf("  Percorrida com sucesso (profundidade: %d)\n", maxProfundidade);
            liberarArvore(raiz);
        } else {
            printf("  IGNORADO (risco de stack overflow)\n");
        }
        printf("\n");
    }
    
    printf("SOLUÇÃO: Usar iteração com pilha explícita ao invés de recursão.\n");
}

// =================================================================
// EXEMPLO 4: Backtracking com estado profundo (N-Queens)
// =================================================================

#define MAX_N 20

int tabuleiro[MAX_N];
int solucoesEncontradas = 0;

bool seguro(int linha, int coluna, int n) {
    for (int i = 0; i < linha; i++) {
        if (tabuleiro[i] == coluna || 
            abs(tabuleiro[i] - coluna) == abs(i - linha)) {
            return false;
        }
    }
    return true;
}

void resolverNQueens(int linha, int n, int limite) {
    profundidadeRecursao++;
    if (profundidadeRecursao > maxProfundidade) {
        maxProfundidade = profundidadeRecursao;
    }
    
    if (solucoesEncontradas >= limite) {
        profundidadeRecursao--;
        return;
    }
    
    if (linha == n) {
        solucoesEncontradas++;
        profundidadeRecursao--;
        return;
    }
    
    for (int coluna = 0; coluna < n; coluna++) {
        if (seguro(linha, coluna, n)) {
            tabuleiro[linha] = coluna;
            resolverNQueens(linha + 1, n, limite);
        }
    }
    
    profundidadeRecursao--;
}

void demonstrarBacktracking() {
    printf("\n=== EXEMPLO 4: BACKTRACKING (N-QUEENS) ===\n\n");
    
    printf("Problema N-Queens usa backtracking recursivo:\n");
    printf("  - Profundidade = N (tamanho do tabuleiro)\n");
    printf("  - Cada nível testa N posições\n");
    printf("  - Para N grande, muitas chamadas recursivas\n\n");
    
    int tamanhos[] = {4, 8, 12, 15};
    int numTamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);
    
    for (int i = 0; i < numTamanhos; i++) {
        int n = tamanhos[i];
        profundidadeRecursao = 0;
        maxProfundidade = 0;
        solucoesEncontradas = 0;
        
        printf("%d-Queens:\n", n);
        resolverNQueens(0, n, 5);  // Limitar a 5 soluções
        printf("  Soluções encontradas: %d\n", solucoesEncontradas);
        printf("  Profundidade máxima: %d\n", maxProfundidade);
        printf("  Sem problema de stack overflow (N pequeno)\n\n");
    }
    
    printf("NOTA: N-Queens com N > 20 pode ter problemas em sistemas com pilha limitada.\n");
}

// =================================================================
// EXEMPLO 5: Comparação de pilha implícita vs explícita
// =================================================================

typedef struct StackNode {
    Node* treeNode;
    struct StackNode* next;
} StackNode;

void pushStack(StackNode** top, Node* treeNode) {
    StackNode* novo = (StackNode*)malloc(sizeof(StackNode));
    novo->treeNode = treeNode;
    novo->next = *top;
    *top = novo;
}

Node* popStack(StackNode** top) {
    if (*top == NULL) return NULL;
    StackNode* temp = *top;
    Node* treeNode = temp->treeNode;
    *top = temp->next;
    free(temp);
    return treeNode;
}

// Percorrer árvore iterativamente com pilha explícita
void percorrerIterativo(Node* raiz) {
    if (raiz == NULL) return;
    
    StackNode* pilha = NULL;
    Node* atual = raiz;
    
    while (atual != NULL || pilha != NULL) {
        while (atual != NULL) {
            pushStack(&pilha, atual);
            atual = atual->esquerda;
        }
        
        atual = popStack(&pilha);
        // printf("Visitando: %d\n", atual->valor);
        atual = atual->direita;
    }
}

void demonstrarPilhaExplicita() {
    printf("\n=== EXEMPLO 5: PILHA IMPLÍCITA VS EXPLÍCITA ===\n\n");
    
    printf("Comparação de abordagens:\n\n");
    
    printf("RECURSÃO (Pilha Implícita):\n");
    printf("  Vantagens:\n");
    printf("    + Código mais limpo e legível\n");
    printf("    + Mais fácil de escrever e entender\n");
    printf("  Desvantagens:\n");
    printf("    - Tamanho de pilha limitado pelo sistema\n");
    printf("    - Stack overflow para problemas profundos\n");
    printf("    - Difícil controlar uso de memória\n\n");
    
    printf("ITERAÇÃO (Pilha Explícita):\n");
    printf("  Vantagens:\n");
    printf("    + Controle total sobre uso de memória\n");
    printf("    + Sem risco de stack overflow do sistema\n");
    printf("    + Pode processar estruturas muito profundas\n");
    printf("  Desvantagens:\n");
    printf("    - Código mais complexo\n");
    printf("    - Precisa gerenciar pilha manualmente\n\n");
    
    int altura = 10000;
    printf("Testando árvore com altura %d:\n\n", altura);
    
    Node* raiz = criarArvoreDegenerada(altura);
    
    printf("Abordagem recursiva:\n");
    profundidadeRecursao = 0;
    maxProfundidade = 0;
    printf("  AVISO: Pode causar stack overflow em alguns sistemas!\n");
    printf("  (Teste desabilitado por segurança)\n\n");
    // percorrerInOrdem(raiz, 0);  // Comentado - pode causar stack overflow
    
    printf("Abordagem iterativa:\n");
    percorrerIterativo(raiz);
    printf("  Sucesso! Processada sem problemas.\n");
    printf("  Pilha explícita não tem limite de sistema.\n\n");
    
    liberarArvore(raiz);
}

// =================================================================
// Função principal
// =================================================================

int main() {
    printf("=== DEMONSTRAÇÃO DE ERROS DE STACK EM ALGORITMOS AVANÇADOS ===\n\n");
    
    // Exemplo 1: Recursão infinita
    demonstrarRecursaoInfinita();
    
    // Exemplo 2: Fibonacci recursivo
    demonstrarFibonacciRecursivo();
    
    // Exemplo 3: Árvore binária profunda
    demonstrarArvoreRecursiva();
    
    // Exemplo 4: Backtracking
    demonstrarBacktracking();
    
    // Exemplo 5: Pilha explícita vs implícita
    demonstrarPilhaExplicita();
    
    // =================================================================
    // LIÇÕES APRENDIDAS
    // =================================================================
    printf("\n=== LIÇÕES APRENDIDAS SOBRE STACK OVERFLOW EM ALGORITMOS ===\n\n");
    
    printf("CAUSAS DE STACK OVERFLOW EM ALGORITMOS:\n\n");
    
    printf("1. Recursão infinita ou muito profunda:\n");
    printf("   - Falta de caso base\n");
    printf("   - Caso base nunca alcançado\n");
    printf("   - Profundidade = tamanho da entrada\n\n");
    
    printf("2. Árvores/grafos desbalanceados:\n");
    printf("   - Árvore degenerada (como lista)\n");
    printf("   - Altura O(n) ao invés de O(log n)\n\n");
    
    printf("3. Algoritmos exponenciais:\n");
    printf("   - Fibonacci recursivo\n");
    printf("   - Subset generation\n");
    printf("   - Alguns problemas de backtracking\n\n");
    
    printf("4. Estruturas muito grandes:\n");
    printf("   - Arrays grandes alocados na pilha\n");
    printf("   - Estruturas complexas em variáveis locais\n\n");
    
    printf("SOLUÇÕES E BOAS PRÁTICAS:\n\n");
    
    printf("✓ Usar iteração ao invés de recursão quando possível\n");
    printf("✓ Implementar pilha explícita para controlar memória\n");
    printf("✓ Usar programação dinâmica (DP) para evitar recálculos\n");
    printf("✓ Limitar profundidade de recursão com verificações\n");
    printf("✓ Alocar estruturas grandes no heap, não na pilha\n");
    printf("✓ Usar tail recursion quando o compilador suporta otimização\n");
    printf("✓ Considerar aumentar tamanho da pilha (ulimit no Linux)\n");
    printf("✓ Testar com entradas grandes antes de produção\n");
    printf("✓ Monitorar uso de pilha em sistemas embarcados\n\n");
    
    printf("FERRAMENTAS ÚTEIS:\n");
    printf("  - ulimit -s (Linux): Ver/alterar tamanho da pilha\n");
    printf("  - valgrind --tool=massif: Analisar uso de memória\n");
    printf("  - gdb: Debugar stack overflow\n");
    printf("  - Sanitizers: Detectar problemas em tempo de compilação\n");
    
    return 0;
}
