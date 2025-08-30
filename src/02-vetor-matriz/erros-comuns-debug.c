#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * ERROS COMUNS EM VETORES E MATRIZES
 * Este arquivo demonstra erros comuns e suas correções
 */

// ============================================================================
// ERRO 1: ACESSO FORA DOS LIMITES (BUFFER OVERFLOW)
// ============================================================================

void demonstrar_buffer_overflow() {
    printf("=== ERRO 1: BUFFER OVERFLOW ===\n\n");
    
    int vetor[5] = {1, 2, 3, 4, 5};
    
    printf("Vetor válido (índices 0-4):\n");
    for (int i = 0; i < 5; i++) {
        printf("vetor[%d] = %d\n", i, vetor[i]);
    }
    
    printf("\n❌ ERRO COMUM - Acesso fora dos limites:\n");
    // CUIDADO: Este código causa undefined behavior!
    // for (int i = 0; i <= 5; i++) {  // Note o <= que deveria ser <
    //     printf("vetor[%d] = %d\n", i, vetor[i]);  // vetor[5] é inválido!
    // }
    
    printf("// ❌ Código problemático:\n");
    printf("// for (int i = 0; i <= 5; i++) {  // <= deveria ser <\n");
    printf("//     printf(\"vetor[%%d] = %%d\\n\", i, vetor[i]);\n");
    printf("// }\n\n");
    
    printf("✅ CORREÇÃO - Sempre verificar limites:\n");
    for (int i = 0; i < 5; i++) {  // Uso correto do <
        printf("vetor[%d] = %d\n", i, vetor[i]);
    }
    
    printf("\n✅ DICA: Use const para tamanho:\n");
    printf("const int TAMANHO = 5;\n");
    printf("int vetor[TAMANHO];\n");
    printf("for (int i = 0; i < TAMANHO; i++) { ... }\n\n");
}

// ============================================================================
// ERRO 2: NÃO INICIALIZAR VETORES
// ============================================================================

void demonstrar_nao_inicializacao() {
    printf("=== ERRO 2: VETORES NÃO INICIALIZADOS ===\n\n");
    
    printf("❌ ERRO COMUM - Usar vetor sem inicializar:\n");
    int vetor_nao_inicializado[3];
    printf("Valores aleatórios (lixo de memória):\n");
    for (int i = 0; i < 3; i++) {
        printf("vetor_nao_inicializado[%d] = %d (valor aleatório!)\n", 
               i, vetor_nao_inicializado[i]);
    }
    
    printf("\n✅ CORREÇÃO - Sempre inicializar:\n");
    
    // Método 1: Inicialização direta
    int vetor1[3] = {0, 0, 0};
    printf("Inicialização direta: ");
    for (int i = 0; i < 3; i++) {
        printf("%d ", vetor1[i]);
    }
    printf("\n");
    
    // Método 2: Inicialização com zeros
    int vetor2[3] = {0};  // Todos elementos ficam 0
    printf("Inicialização com zeros: ");
    for (int i = 0; i < 3; i++) {
        printf("%d ", vetor2[i]);
    }
    printf("\n");
    
    // Método 3: Inicialização em loop
    int vetor3[3];
    for (int i = 0; i < 3; i++) {
        vetor3[i] = i + 1;
    }
    printf("Inicialização em loop: ");
    for (int i = 0; i < 3; i++) {
        printf("%d ", vetor3[i]);
    }
    printf("\n\n");
}

// ============================================================================
// ERRO 3: VAZAMENTOS DE MEMÓRIA
// ============================================================================

void demonstrar_vazamento_memoria() {
    printf("=== ERRO 3: VAZAMENTOS DE MEMÓRIA ===\n\n");
    
    printf("❌ ERRO COMUM - Esquecer de liberar memória:\n");
    printf("int *vetor = malloc(100 * sizeof(int));\n");
    printf("// ... usar vetor ...\n");
    printf("// ❌ Esqueceu de chamar free(vetor)!\n\n");
    
    printf("✅ CORREÇÃO - Sempre fazer free:\n");
    int *vetor = malloc(5 * sizeof(int));
    if (vetor == NULL) {
        printf("Erro na alocação!\n");
        return;
    }
    
    // Usar o vetor
    for (int i = 0; i < 5; i++) {
        vetor[i] = i * i;
    }
    
    printf("Vetor alocado e preenchido: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
    
    // ✅ Liberar memória
    free(vetor);
    vetor = NULL;  // Boa prática: evita uso após free
    printf("Memória liberada com sucesso!\n\n");
    
    printf("✅ PADRÃO RECOMENDADO:\n");
    printf("ptr = malloc(...);\n");
    printf("if (ptr == NULL) { /* tratar erro */ }\n");
    printf("/* usar ptr */\n");
    printf("free(ptr);\n");
    printf("ptr = NULL;\n\n");
}

// ============================================================================
// ERRO 4: PROBLEMAS COM MATRIZES DINÂMICAS
// ============================================================================

void demonstrar_erro_matriz_dinamica() {
    printf("=== ERRO 4: MATRIZES DINÂMICAS ===\n\n");
    
    printf("❌ ERRO COMUM - Liberação incorreta:\n");
    printf("int **mat = malloc(linhas * sizeof(int*));\n");
    printf("for (int i = 0; i < linhas; i++) {\n");
    printf("    mat[i] = malloc(colunas * sizeof(int));\n");
    printf("}\n");
    printf("// ❌ free(mat); // Libera apenas o array de ponteiros!\n\n");
    
    printf("✅ CORREÇÃO - Liberar na ordem correta:\n");
    
    int linhas = 3, colunas = 4;
    int **matriz = malloc(linhas * sizeof(int*));
    
    if (matriz == NULL) {
        printf("Erro na alocação da matriz!\n");
        return;
    }
    
    // Alocar cada linha
    for (int i = 0; i < linhas; i++) {
        matriz[i] = malloc(colunas * sizeof(int));
        if (matriz[i] == NULL) {
            printf("Erro na alocação da linha %d!\n", i);
            // Liberar linhas já alocadas
            for (int j = 0; j < i; j++) {
                free(matriz[j]);
            }
            free(matriz);
            return;
        }
    }
    
    // Usar a matriz
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = i * colunas + j;
        }
    }
    
    printf("Matriz %dx%d criada:\n", linhas, colunas);
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%2d ", matriz[i][j]);
        }
        printf("\n");
    }
    
    // ✅ Liberar na ordem correta: primeiro as linhas, depois o array de ponteiros
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
    matriz = NULL;
    
    printf("Matriz liberada corretamente!\n\n");
}

// ============================================================================
// ERRO 5: CONFUSÃO ENTRE TAMANHO E NÚMERO DE ELEMENTOS
// ============================================================================

void demonstrar_confusao_sizeof() {
    printf("=== ERRO 5: CONFUSÃO COM SIZEOF ===\n\n");
    
    int vetor[] = {1, 2, 3, 4, 5, 6};
    
    printf("❌ ERRO COMUM - Confundir bytes com elementos:\n");
    printf("sizeof(vetor) = %lu bytes\n", sizeof(vetor));
    printf("// ❌ for (int i = 0; i < sizeof(vetor); i++)  // ERRADO!\n\n");
    
    printf("✅ CORREÇÃO - Calcular número de elementos:\n");
    int num_elementos = sizeof(vetor) / sizeof(vetor[0]);
    printf("Número de elementos = sizeof(vetor) / sizeof(vetor[0])\n");
    printf("Número de elementos = %lu / %lu = %d\n", 
           sizeof(vetor), sizeof(vetor[0]), num_elementos);
    
    printf("Usando corretamente:\n");
    for (int i = 0; i < num_elementos; i++) {
        printf("vetor[%d] = %d\n", i, vetor[i]);
    }
    
    printf("\n✅ MACRO ÚTIL:\n");
    printf("#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))\n\n");
}

// Função auxiliar para demonstrar problema com sizeof em parâmetros
void funcao_com_vetor(int arr[]) {
    printf("=== SIZEOF EM PARÂMETROS DE FUNÇÃO ===\n\n");
    
    printf("❌ PROBLEMA - sizeof em parâmetro:\n");
    printf("sizeof(arr) na função = %lu bytes\n", sizeof(arr));
    printf("// arr é na verdade um ponteiro, não um array!\n");
    printf("// sizeof(arr) = sizeof(int*) = %lu bytes\n\n", sizeof(int*));
    
    printf("✅ SOLUÇÃO - Passar tamanho separadamente:\n");
    printf("void funcao(int arr[], int tamanho) { ... }\n\n");
}

// ============================================================================
// ERRO 6: PROBLEMAS COM STRINGS (ARRAYS DE CHAR)
// ============================================================================

void demonstrar_erros_string() {
    printf("=== ERRO 6: PROBLEMAS COM STRINGS ===\n\n");
    
    printf("❌ ERRO COMUM - Esquecer do \\0 terminador:\n");
    char str_sem_terminador[5] = {'H', 'e', 'l', 'l', 'o'};  // SEM \\0!
    printf("String sem terminador: '");
    for (int i = 0; i < 5; i++) {
        printf("%c", str_sem_terminador[i]);
    }
    printf("' (pode imprimir lixo após 'Hello')\n\n");
    
    printf("✅ CORREÇÃO - Sempre incluir \\0:\n");
    char str_correta[6] = {'H', 'e', 'l', 'l', 'o', '\\0'};
    // Ou simplesmente: char str_correta[] = "Hello";
    printf("String correta: '%s'\n\n", str_correta);
    
    printf("❌ ERRO COMUM - Buffer muito pequeno:\n");
    printf("char nome[5];\n");
    printf("strcpy(nome, \"João Silva\");  // ❌ Overflow! 'João Silva' tem 10 chars\n\n");
    
    printf("✅ CORREÇÃO - Verificar tamanho:\n");
    char nome[20];  // Buffer suficiente
    strcpy(nome, "João Silva");
    printf("Nome: '%s' (buffer de %lu bytes)\n", nome, sizeof(nome));
    
    printf("\n✅ AINDA MELHOR - Usar strncpy:\n");
    char destino[10];
    strncpy(destino, "Texto muito longo", sizeof(destino) - 1);
    destino[sizeof(destino) - 1] = '\\0';  // Garantir terminação
    printf("Texto truncado: '%s'\n\n", destino);
}

// ============================================================================
// FERRAMENTAS DE DEBUG
// ============================================================================

void demonstrar_tecnicas_debug() {
    printf("=== TÉCNICAS DE DEBUG ===\n\n");
    
    printf("1. ASSERTIONS para verificar condições:\n");
    printf("#include <assert.h>\n");
    printf("assert(indice >= 0 && indice < tamanho);\n\n");
    
    printf("2. PRINTS de debug:\n");
    printf("#ifdef DEBUG\n");
    printf("    printf(\"Debug: i=%%d, valor=%%d\\n\", i, vetor[i]);\n");
    printf("#endif\n\n");
    
    printf("3. VALGRIND para detectar vazamentos:\n");
    printf("valgrind --leak-check=full ./meu_programa\n\n");
    
    printf("4. COMPILAR com flags de debug:\n");
    printf("gcc -g -Wall -Wextra -fsanitize=address programa.c\n\n");
    
    printf("5. INICIALIZAR com valores reconhecíveis:\n");
    int vetor_debug[5];
    for (int i = 0; i < 5; i++) {
        vetor_debug[i] = 0xDEADBEEF;  // Valor fácil de reconhecer
    }
    printf("Valores de debug: ");
    for (int i = 0; i < 5; i++) {
        printf("0x%X ", vetor_debug[i]);
    }
    printf("\n\n");
}

// ============================================================================
// CHECKLIST DE BOAS PRÁTICAS
// ============================================================================

void mostrar_checklist() {
    printf("=== CHECKLIST DE BOAS PRÁTICAS ===\n\n");
    
    printf("✅ ANTES DE USAR ARRAYS:\n");
    printf("   □ Verificar se índices estão dentro dos limites\n");
    printf("   □ Inicializar todos os elementos\n");
    printf("   □ Usar const para tamanhos fixos\n");
    printf("   □ Documentar o range válido de índices\n\n");
    
    printf("✅ PARA ALOCAÇÃO DINÂMICA:\n");
    printf("   □ Verificar se malloc() retornou NULL\n");
    printf("   □ Liberar memória com free()\n");
    printf("   □ Definir ponteiro como NULL após free()\n");
    printf("   □ Para matrizes: liberar linhas antes da matriz\n\n");
    
    printf("✅ PARA STRINGS:\n");
    printf("   □ Reservar espaço para '\\0' terminador\n");
    printf("   □ Usar strncpy() ao invés de strcpy()\n");
    printf("   □ Verificar tamanho antes de copiar\n");
    printf("   □ Garantir terminação com '\\0'\n\n");
    
    printf("✅ PARA DEBUG:\n");
    printf("   □ Compilar com -Wall -Wextra\n");
    printf("   □ Usar Valgrind para detectar vazamentos\n");
    printf("   □ Adicionar assertions em pontos críticos\n");
    printf("   □ Testar com dados extremos (arrays vazios, muito grandes)\n\n");
}

int main() {
    printf("***** ERROS COMUNS E DEBUGGING EM VETORES/MATRIZES *****\n\n");
    
    demonstrar_buffer_overflow();
    demonstrar_nao_inicializacao();
    demonstrar_vazamento_memoria();
    demonstrar_erro_matriz_dinamica();
    demonstrar_confusao_sizeof();
    
    int exemplo[] = {1, 2, 3};
    funcao_com_vetor(exemplo);
    
    demonstrar_erros_string();
    demonstrar_tecnicas_debug();
    mostrar_checklist();
    
    printf("=== RESUMO ===\n");
    printf("Os erros mais comuns são:\n");
    printf("1. Buffer overflow (acesso fora dos limites)\n");
    printf("2. Não inicializar variáveis\n");
    printf("3. Vazamentos de memória\n");
    printf("4. Liberação incorreta de matrizes dinâmicas\n");
    printf("5. Confusão entre sizeof e número de elementos\n");
    printf("6. Problemas com terminação de strings\n\n");
    
    printf("💡 DICA FINAL: Sempre teste com dados extremos e use ferramentas\n");
    printf("   de debugging como Valgrind e AddressSanitizer!\n");
    
    return 0;
}