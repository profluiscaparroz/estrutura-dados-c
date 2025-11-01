#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Estrutura para representar um nó da pilha
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Estrutura para representar a pilha
typedef struct Stack {
    Node* top;
    int tamanho;
} Stack;

// Função para inicializar a pilha
void initializeStack(Stack* stack) {
    stack->top = NULL;
    stack->tamanho = 0;
}

// Função para verificar se a pilha está vazia
bool isEmpty(Stack* stack) {
    return stack->top == NULL;
}

// Função para empilhar com verificação de alocação de memória
bool push(Stack* stack, int value) {
    // Tentar alocar memória para novo nó
    Node* newNode = (Node*)malloc(sizeof(Node));
    
    // ERRO COMUM: Não verificar se malloc retornou NULL
    if (newNode == NULL) {
        printf("ERRO: Falha na alocação de memória!\n");
        printf("      malloc() retornou NULL - memória insuficiente.\n");
        return false;
    }
    
    newNode->data = value;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->tamanho++;
    
    return true;
}

// Função para desempilhar com tratamento adequado de memória
bool pop(Stack* stack, int* value) {
    if (isEmpty(stack)) {
        printf("ERRO: Tentativa de desempilhar de pilha vazia!\n");
        return false;
    }
    
    Node* temp = stack->top;
    *value = temp->data;
    stack->top = temp->next;
    
    // IMPORTANTE: Liberar memória do nó removido
    free(temp);
    stack->tamanho--;
    
    return true;
}

// Função para desempilhar SEM liberar memória (DEMONSTRAÇÃO DE ERRO)
bool popComMemoryLeak(Stack* stack, int* value) {
    if (isEmpty(stack)) {
        printf("ERRO: Tentativa de desempilhar de pilha vazia!\n");
        return false;
    }
    
    Node* temp = stack->top;
    *value = temp->data;
    stack->top = temp->next;
    
    // ERRO: NÃO LIBERAR A MEMÓRIA - CAUSA MEMORY LEAK!
    // free(temp);  // Esta linha foi omitida intencionalmente
    stack->tamanho--;
    
    return true;
}

// Função para limpar toda a pilha liberando memória
void clearStack(Stack* stack) {
    Node* current = stack->top;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    stack->top = NULL;
    stack->tamanho = 0;
}

// Função para exibir informações da pilha
void displayStack(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Pilha: [vazia]\n");
        return;
    }
    
    printf("Pilha (tamanho: %d): ", stack->tamanho);
    Node* current = stack->top;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Função que simula alocação massiva até falhar
void demonstrarFalhaAlocacao() {
    printf("\n=== DEMONSTRAÇÃO DE FALHA DE ALOCAÇÃO ===\n");
    printf("Tentando alocar memória até falhar...\n\n");
    
    Stack stack;
    initializeStack(&stack);
    
    int contador = 0;
    int limite = 1000000; // Limite de segurança para evitar travar o sistema
    
    printf("Empilhando elementos até encontrar limite de memória (max %d):\n", limite);
    
    // Tentar empilhar muitos elementos
    while (contador < limite) {
        if (!push(&stack, contador)) {
            printf("\nFalha após %d alocações bem-sucedidas!\n", contador);
            printf("Sistema sem memória disponível.\n");
            break;
        }
        
        // Mostrar progresso a cada 100000 elementos
        if (contador % 100000 == 0 && contador > 0) {
            printf("  %d elementos empilhados...\n", contador);
        }
        
        contador++;
    }
    
    if (contador == limite) {
        printf("\nLimite de segurança atingido: %d elementos empilhados.\n", contador);
    }
    
    printf("Limpando pilha para liberar memória...\n");
    clearStack(&stack);
    printf("Memória liberada com sucesso.\n");
}

// Função que demonstra memory leak
void demonstrarMemoryLeak() {
    printf("\n=== DEMONSTRAÇÃO DE MEMORY LEAK ===\n");
    printf("Criando pilha e desempilhando sem liberar memória...\n\n");
    
    Stack stack;
    initializeStack(&stack);
    
    // Empilhar alguns elementos
    printf("Empilhando 5 elementos:\n");
    for (int i = 1; i <= 5; i++) {
        push(&stack, i * 10);
        printf("  Empilhado: %d\n", i * 10);
    }
    
    displayStack(&stack);
    
    // Desempilhar usando função COM memory leak
    printf("\nDesempilhando com função que NÃO libera memória (popComMemoryLeak):\n");
    int valor;
    for (int i = 0; i < 3; i++) {
        if (popComMemoryLeak(&stack, &valor)) {
            printf("  Desempilhado: %d (ATENÇÃO: memória NÃO foi liberada!)\n", valor);
        }
    }
    
    printf("\nRESULTADO:\n");
    printf("- 3 nós foram removidos da pilha\n");
    printf("- A memória desses nós NÃO foi liberada\n");
    printf("- MEMORY LEAK: 3 blocos de memória estão perdidos\n");
    printf("- Em programa longo, isso pode esgotar toda a memória!\n");
    
    // Limpar o resto corretamente
    printf("\nLimpando o resto da pilha CORRETAMENTE:\n");
    clearStack(&stack);
    printf("Pilha limpa (mas os 3 primeiros nós ainda estão vazando memória).\n");
}

// Função que demonstra double free (erro grave)
void demonstrarDoubleFree() {
    printf("\n=== DEMONSTRAÇÃO DE DOUBLE FREE (ERRO GRAVE) ===\n");
    printf("Liberando a mesma memória duas vezes causa comportamento indefinido.\n\n");
    
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }
    
    node->data = 42;
    node->next = NULL;
    
    printf("Nó alocado com valor: %d\n", node->data);
    printf("Endereço do nó: %p\n", (void*)node);
    
    printf("\nLiberando memória pela primeira vez (correto)...\n");
    free(node);
    printf("free() executado com sucesso.\n");
    
    printf("\nAVISO: O código abaixo está comentado para evitar crash!\n");
    printf("Descomentar causaria:\n");
    printf("  - Comportamento indefinido\n");
    printf("  - Corrupção de heap\n");
    printf("  - Possível segmentation fault\n");
    printf("  - Possível crash do programa\n\n");
    
    // NÃO FAZER ISSO! Double free causa erro grave:
    // printf("Tentando liberar a mesma memória novamente (ERRO!)...\n");
    // free(node);  // COMENTADO PARA EVITAR CRASH
    
    printf("O ponteiro 'node' agora é inválido e não deve ser usado!\n");
}

// Função que demonstra uso após free (use-after-free)
void demonstrarUseAfterFree() {
    printf("\n=== DEMONSTRAÇÃO DE USE-AFTER-FREE ===\n");
    printf("Acessar memória após liberá-la causa comportamento indefinido.\n\n");
    
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }
    
    node->data = 123;
    printf("Nó criado com valor: %d\n", node->data);
    printf("Endereço: %p\n", (void*)node);
    
    printf("\nLiberando memória...\n");
    free(node);
    
    printf("\nAVISO: Código abaixo está comentado para evitar comportamento indefinido!\n");
    printf("Acessar node->data após free() pode:\n");
    printf("  - Retornar valor inesperado\n");
    printf("  - Causar segmentation fault\n");
    printf("  - Corromper dados de outras estruturas\n");
    printf("  - Funcionar 'por acaso' mas falhar depois\n\n");
    
    // NÃO FAZER ISSO! Use-after-free é erro grave:
    // printf("Tentando acessar node->data após free (ERRO!)...\n");
    // printf("Valor: %d\n", node->data);  // COMENTADO - comportamento indefinido!
    
    // Boa prática: definir ponteiro como NULL após free
    node = NULL;
    printf("Boa prática: Após free(), defina ponteiro como NULL.\n");
    printf("Agora node = %p (seguro verificar se é NULL antes de usar)\n", (void*)node);
}

// Função que demonstra NULL pointer dereference
void demonstrarNullPointer() {
    printf("\n=== DEMONSTRAÇÃO DE NULL POINTER DEREFERENCE ===\n");
    printf("Acessar membro de ponteiro NULL causa segmentation fault.\n\n");
    
    Stack* stack = NULL;  // Ponteiro não inicializado
    
    printf("stack = NULL (ponteiro não inicializado)\n");
    
    printf("\nTentando usar pilha sem verificar se é NULL:\n");
    printf("AVISO: Código abaixo está comentado para evitar crash!\n\n");
    
    // NÃO FAZER ISSO! NULL pointer dereference:
    // if (isEmpty(stack)) {  // COMENTADO - causaria segmentation fault!
    //     printf("Pilha vazia\n");
    // }
    
    printf("Sempre verificar se ponteiro é válido antes de usar:\n");
    
    if (stack != NULL) {
        printf("Pilha válida, pode usar.\n");
    } else {
        printf("Pilha é NULL! Não pode ser usada.\n");
        printf("Solução: Alocar memória primeiro:\n");
        stack = (Stack*)malloc(sizeof(Stack));
        if (stack != NULL) {
            initializeStack(stack);
            printf("Pilha alocada e inicializada com sucesso!\n");
            free(stack);
        }
    }
}

// Função principal
int main() {
    printf("=== DEMONSTRAÇÃO DE ERROS DE MEMÓRIA EM PILHAS ===\n");
    
    // Demonstrar diferentes tipos de erros de memória
    demonstrarMemoryLeak();
    
    demonstrarDoubleFree();
    
    demonstrarUseAfterFree();
    
    demonstrarNullPointer();
    
    // Demonstração de falha de alocação (comentado por ser intensivo)
    // Descomentar se quiser ver erro de falta de memória
    // demonstrarFalhaAlocacao();
    
    // =================================================================
    // LIÇÕES APRENDIDAS E BOAS PRÁTICAS
    // =================================================================
    printf("\n=== LIÇÕES APRENDIDAS SOBRE GERENCIAMENTO DE MEMÓRIA ===\n\n");
    
    printf("ERROS COMUNS COM MEMÓRIA EM PILHAS:\n\n");
    
    printf("1. Falha ao verificar retorno de malloc():\n");
    printf("   - malloc() pode retornar NULL se não houver memória\n");
    printf("   - SEMPRE verificar se malloc() retornou NULL\n\n");
    
    printf("2. Memory Leak (vazamento de memória):\n");
    printf("   - Esquecer de chamar free() para memória alocada\n");
    printf("   - Cada nó removido da pilha DEVE ter sua memória liberada\n");
    printf("   - Acumula ao longo do tempo até esgotar memória\n\n");
    
    printf("3. Double Free (liberar duas vezes):\n");
    printf("   - Chamar free() duas vezes no mesmo ponteiro\n");
    printf("   - Causa corrupção de heap e comportamento indefinido\n");
    printf("   - Pode causar crash do programa\n\n");
    
    printf("4. Use-After-Free (usar após liberar):\n");
    printf("   - Acessar memória depois de chamar free()\n");
    printf("   - Comportamento indefinido e imprevisível\n");
    printf("   - Pode parecer funcionar mas falhar aleatoriamente\n\n");
    
    printf("5. NULL Pointer Dereference:\n");
    printf("   - Tentar acessar membro de ponteiro NULL\n");
    printf("   - Causa segmentation fault imediato\n\n");
    
    printf("BOAS PRÁTICAS:\n\n");
    printf("✓ Sempre verificar retorno de malloc()\n");
    printf("✓ Para cada malloc(), garantir um free() correspondente\n");
    printf("✓ Após free(), definir ponteiro como NULL\n");
    printf("✓ Verificar se ponteiro é NULL antes de usar\n");
    printf("✓ Usar ferramentas como valgrind para detectar memory leaks\n");
    printf("✓ Implementar função de limpeza (clearStack) para liberar tudo\n");
    printf("✓ Em caso de falha de alocação, fazer cleanup apropriado\n");
    printf("✓ Considerar usar RAII em C++ ou smart pointers quando possível\n");
    
    return 0;
}
