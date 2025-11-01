#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 5 // Define o tamanho máximo da pilha (pequeno para demonstração)

// Estrutura para representar a pilha
typedef struct {
    int itens[MAX];
    int topo;
} Pilha;

// Função para inicializar a pilha
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

// Função para verificar se a pilha está cheia
bool estaCheia(Pilha *p) {
    return p->topo == MAX - 1;
}

// Função para verificar se a pilha está vazia
bool estaVazia(Pilha *p) {
    return p->topo == -1;
}

// Função para empilhar (push) com tratamento de erro
bool empilhar(Pilha *p, int valor) {
    if (estaCheia(p)) {
        printf("ERRO: Stack Overflow! Não é possível empilhar %d.\n", valor);
        printf("      A pilha atingiu sua capacidade máxima de %d elementos.\n", MAX);
        return false;
    }
    p->itens[++p->topo] = valor;
    printf("Empilhado: %d (posição %d/%d)\n", valor, p->topo + 1, MAX);
    return true;
}

// Função para desempilhar (pop) com tratamento de erro
bool desempilhar(Pilha *p, int *valor) {
    if (estaVazia(p)) {
        printf("ERRO: Stack Underflow! A pilha está vazia.\n");
        return false;
    }
    *valor = p->itens[p->topo--];
    return true;
}

// Função para ver o topo da pilha sem remover
bool topo(Pilha *p, int *valor) {
    if (estaVazia(p)) {
        printf("ERRO: Pilha vazia! Não há elemento no topo.\n");
        return false;
    }
    *valor = p->itens[p->topo];
    return true;
}

// Função para exibir o estado da pilha
void exibirPilha(Pilha *p) {
    if (estaVazia(p)) {
        printf("Pilha: [vazia]\n");
        return;
    }
    printf("Pilha (topo -> base): [");
    for (int i = p->topo; i >= 0; i--) {
        printf("%d", p->itens[i]);
        if (i > 0) printf(", ");
    }
    printf("] - %d/%d elementos\n", p->topo + 1, MAX);
}

// Função principal demonstrando erros comuns de pilha
int main() {
    printf("=== DEMONSTRAÇÃO DE ERROS COMUNS EM PILHAS ===\n\n");
    
    Pilha p;
    inicializarPilha(&p);
    
    // =================================================================
    // EXEMPLO 1: Demonstração de Stack Overflow
    // =================================================================
    printf("1. DEMONSTRAÇÃO DE STACK OVERFLOW:\n");
    printf("   Tentando empilhar mais elementos do que a capacidade da pilha...\n\n");
    
    // Empilhar até atingir a capacidade
    for (int i = 1; i <= MAX; i++) {
        empilhar(&p, i * 10);
    }
    printf("\n");
    exibirPilha(&p);
    printf("\n");
    
    // Tentar empilhar além da capacidade - causará Stack Overflow
    printf("Tentando adicionar mais um elemento...\n");
    empilhar(&p, 99);
    printf("\n");
    
    // Tentativa adicional para demonstrar o erro múltiplas vezes
    printf("Tentando adicionar outro elemento...\n");
    empilhar(&p, 100);
    printf("\n");
    
    // =================================================================
    // EXEMPLO 2: Demonstração de Stack Underflow
    // =================================================================
    printf("2. DEMONSTRAÇÃO DE STACK UNDERFLOW:\n");
    printf("   Esvaziando a pilha completamente...\n\n");
    
    int valor;
    // Desempilhar todos os elementos
    while (!estaVazia(&p)) {
        if (desempilhar(&p, &valor)) {
            printf("Desempilhado: %d\n", valor);
        }
    }
    printf("\n");
    exibirPilha(&p);
    printf("\n");
    
    // Tentar desempilhar de pilha vazia - causará Stack Underflow
    printf("Tentando desempilhar de pilha vazia...\n");
    desempilhar(&p, &valor);
    printf("\n");
    
    printf("Tentando desempilhar novamente...\n");
    desempilhar(&p, &valor);
    printf("\n");
    
    // =================================================================
    // EXEMPLO 3: Tentativa de acessar topo de pilha vazia
    // =================================================================
    printf("3. DEMONSTRAÇÃO DE ACESSO A TOPO VAZIO:\n");
    printf("   Tentando ver o topo de uma pilha vazia...\n\n");
    
    topo(&p, &valor);
    printf("\n");
    
    // =================================================================
    // EXEMPLO 4: Cenário realista de uso incorreto
    // =================================================================
    printf("4. CENÁRIO REALISTA - LOOP SEM VERIFICAÇÃO:\n");
    printf("   Simulando um algoritmo que não verifica limites...\n\n");
    
    // Reconstruir pilha
    for (int i = 1; i <= 3; i++) {
        empilhar(&p, i);
    }
    printf("\n");
    
    // Tentar desempilhar mais elementos do que existem
    printf("Tentando desempilhar 5 elementos (mas só existem 3):\n");
    for (int i = 0; i < 5; i++) {
        printf("Iteração %d: ", i + 1);
        if (desempilhar(&p, &valor)) {
            printf("Sucesso - valor = %d\n", valor);
        } else {
            printf("Falha ao desempilhar!\n");
        }
    }
    printf("\n");
    
    // =================================================================
    // LIÇÕES APRENDIDAS E BOAS PRÁTICAS
    // =================================================================
    printf("=== LIÇÕES APRENDIDAS ===\n\n");
    printf("ERROS COMUNS EM PILHAS:\n");
    printf("1. Stack Overflow: Tentar empilhar quando a pilha está cheia\n");
    printf("   - Causa: Não verificar estaCheia() antes de empilhar\n");
    printf("   - Solução: Sempre verificar se há espaço disponível\n\n");
    
    printf("2. Stack Underflow: Tentar desempilhar quando a pilha está vazia\n");
    printf("   - Causa: Não verificar estaVazia() antes de desempilhar\n");
    printf("   - Solução: Sempre verificar se há elementos na pilha\n\n");
    
    printf("3. Acesso a elemento inválido: Acessar topo de pilha vazia\n");
    printf("   - Causa: Assumir que sempre há elementos\n");
    printf("   - Solução: Verificar estado da pilha antes de acessar\n\n");
    
    printf("BOAS PRÁTICAS:\n");
    printf("- Use funções que retornam bool para indicar sucesso/falha\n");
    printf("- Sempre verifique o retorno das operações de pilha\n");
    printf("- Implemente tratamento adequado de erros\n");
    printf("- Considere usar pilhas dinâmicas quando o tamanho é imprevisível\n");
    printf("- Em sistemas críticos, use logging para rastrear erros\n");
    
    return 0;
}
