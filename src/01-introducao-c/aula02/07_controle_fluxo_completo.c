/*
 * ====================================================================
 * DEMONSTRAÇÃO COMPLETA DE CONTROLE DE FLUXO EM C
 * ====================================================================
 * 
 * Este arquivo implementa exemplos abrangentes de todas as estruturas
 * de controle de fluxo mencionadas na documentação do curso, incluindo:
 * 
 * 1. Estruturas Condicionais:
 *    - if, else, else if
 *    - switch/case
 *    - Operadores relacionais e lógicos
 * 
 * 2. Estruturas de Repetição:
 *    - for loops
 *    - while loops
 *    - do-while loops
 * 
 * 3. Estruturas de Salto:
 *    - break
 *    - continue
 *    - goto (uso limitado)
 *    - return
 * 
 * 4. Aplicações Práticas:
 *    - Validação de entrada
 *    - Menus interativos
 *    - Processamento de dados
 * 
 * Baseado na documentação em docs/01-introducao/02-controle-fluxo/
 * 
 * Autor: Estrutura de Dados em C
 * Data: 2024
 * ====================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ==================== ESTRUTURAS CONDICIONAIS ====================

/**
 * Demonstra o uso básico de if-else com diferentes condições
 */
void demonstrar_if_else() {
    printf("=== DEMONSTRAÇÃO DE IF-ELSE ===\n");
    
    int idade = 20;
    float altura = 1.75f;
    char genero = 'M';
    
    printf("Dados: Idade=%d, Altura=%.2f, Gênero=%c\n", idade, altura, genero);
    
    // Exemplo 1: Condição simples
    if (idade >= 18) {
        printf("✓ Maior de idade\n");
    } else {
        printf("✗ Menor de idade\n");
    }
    
    // Exemplo 2: Múltiplas condições com else if
    if (idade < 13) {
        printf("Categoria: Criança\n");
    } else if (idade < 18) {
        printf("Categoria: Adolescente\n");
    } else if (idade < 60) {
        printf("Categoria: Adulto\n");
    } else {
        printf("Categoria: Idoso\n");
    }
    
    // Exemplo 3: Operadores lógicos (&&, ||, !)
    if (idade >= 18 && altura >= 1.60f) {
        printf("✓ Pode dirigir e alcançar os pedais\n");
    } else {
        printf("✗ Não atende todos os requisitos para dirigir\n");
    }
    
    printf("\n");
}

/**
 * Demonstra o uso de switch-case para múltiplas opções
 */
void demonstrar_switch_case() {
    printf("=== DEMONSTRAÇÃO DE SWITCH-CASE ===\n");
    
    int opcao_menu = 2;
    char nota = 'B';
    int dia_semana = 3;
    
    // Exemplo 1: Menu de opções
    printf("Opção selecionada: %d\n", opcao_menu);
    switch (opcao_menu) {
        case 1:
            printf("Ação: Criar novo arquivo\n");
            break;
        case 2:
            printf("Ação: Abrir arquivo existente\n");
            break;
        case 3:
            printf("Ação: Salvar arquivo\n");
            break;
        case 4:
            printf("Ação: Sair do programa\n");
            break;
        default:
            printf("Ação: Opção inválida\n");
            break;
    }
    
    // Exemplo 2: Conversão de nota para conceito
    printf("\nNota: %c\n", nota);
    switch (nota) {
        case 'A':
        case 'a':
            printf("Conceito: Excelente (90-100)\n");
            break;
        case 'B':
        case 'b':
            printf("Conceito: Bom (80-89)\n");
            break;
        case 'C':
        case 'c':
            printf("Conceito: Regular (70-79)\n");
            break;
        case 'D':
        case 'd':
            printf("Conceito: Insuficiente (60-69)\n");
            break;
        case 'F':
        case 'f':
            printf("Conceito: Reprovado (0-59)\n");
            break;
        default:
            printf("Conceito: Nota inválida\n");
            break;
    }
    
    // Exemplo 3: Dias da semana (demonstrando fall-through intencional)
    printf("\nDia da semana: %d\n", dia_semana);
    switch (dia_semana) {
        case 1:
            printf("Segunda-feira");
            break;
        case 2:
            printf("Terça-feira");
            break;
        case 3:
            printf("Quarta-feira");
            break;
        case 4:
            printf("Quinta-feira");
            break;
        case 5:
            printf("Sexta-feira");
            break;
        case 6:
        case 7:
            printf("Final de semana");
            break;
        default:
            printf("Dia inválido");
            break;
    }
    printf("\n\n");
}

// ==================== ESTRUTURAS DE REPETIÇÃO ====================

/**
 * Demonstra diferentes tipos de loops for
 */
void demonstrar_for_loops() {
    printf("=== DEMONSTRAÇÃO DE FOR LOOPS ===\n");
    
    // Exemplo 1: Loop básico
    printf("Contagem crescente de 1 a 5: ");
    for (int i = 1; i <= 5; i++) {
        printf("%d ", i);
    }
    printf("\n");
    
    // Exemplo 2: Loop decrescente
    printf("Contagem decrescente de 10 a 6: ");
    for (int i = 10; i >= 6; i--) {
        printf("%d ", i);
    }
    printf("\n");
    
    // Exemplo 3: Loop com incremento personalizado
    printf("Números pares de 0 a 10: ");
    for (int i = 0; i <= 10; i += 2) {
        printf("%d ", i);
    }
    printf("\n");
    
    // Exemplo 4: Loop aninhado para criar tabela de multiplicação
    printf("\nTabela de multiplicação 3x3:\n");
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            printf("%2d ", i * j);
        }
        printf("\n");
    }
    
    printf("\n");
}

/**
 * Demonstra diferentes usos de while loops
 */
void demonstrar_while_loops() {
    printf("=== DEMONSTRAÇÃO DE WHILE LOOPS ===\n");
    
    // Exemplo 1: Contagem com while
    printf("Contagem com while (1 a 5): ");
    int contador = 1;
    while (contador <= 5) {
        printf("%d ", contador);
        contador++;
    }
    printf("\n");
    
    // Exemplo 2: Busca em array
    int numeros[] = {10, 25, 30, 45, 50};
    int tamanho = sizeof(numeros) / sizeof(numeros[0]);
    int procurado = 30;
    int encontrado = 0;
    int indice = 0;
    
    printf("Procurando %d no array: ", procurado);
    while (indice < tamanho && !encontrado) {
        if (numeros[indice] == procurado) {
            encontrado = 1;
            printf("Encontrado na posição %d\n", indice);
        }
        indice++;
    }
    
    if (!encontrado) {
        printf("Não encontrado\n");
    }
    
    // Exemplo 3: Validação de entrada (simulado)
    int tentativas = 0;
    int senha_correta = 1234;
    int senha_tentativa = 1111; // Simular entrada errada
    
    printf("\nSimulação de validação de senha:\n");
    while (tentativas < 3 && senha_tentativa != senha_correta) {
        tentativas++;
        printf("Tentativa %d: Senha incorreta (%d)\n", tentativas, senha_tentativa);
        
        // Simular diferentes tentativas
        if (tentativas == 1) senha_tentativa = 2222;
        else if (tentativas == 2) senha_tentativa = 1234; // Acerta na 3ª
    }
    
    if (senha_tentativa == senha_correta) {
        printf("✓ Acesso autorizado!\n");
    } else {
        printf("✗ Acesso negado - muitas tentativas\n");
    }
    
    printf("\n");
}

/**
 * Demonstra o uso de do-while loops
 */
void demonstrar_do_while() {
    printf("=== DEMONSTRAÇÃO DE DO-WHILE ===\n");
    
    // Exemplo 1: Menu que executa pelo menos uma vez
    int opcao;
    int execucoes = 0;
    
    printf("Simulação de menu interativo:\n");
    do {
        execucoes++;
        // Simular diferentes opções
        if (execucoes == 1) opcao = 1;
        else if (execucoes == 2) opcao = 2;
        else opcao = 0; // Sair
        
        printf("Execução %d - Opção escolhida: %d\n", execucoes, opcao);
        
        switch (opcao) {
            case 1:
                printf("  → Processando opção 1...\n");
                break;
            case 2:
                printf("  → Processando opção 2...\n");
                break;
            case 0:
                printf("  → Saindo do menu...\n");
                break;
            default:
                printf("  → Opção inválida\n");
                break;
        }
        
    } while (opcao != 0 && execucoes < 5); // Limite para evitar loop infinito
    
    printf("Menu encerrado após %d execuções\n\n", execucoes);
}

// ==================== ESTRUTURAS DE SALTO ====================

/**
 * Demonstra o uso de break e continue
 */
void demonstrar_break_continue() {
    printf("=== DEMONSTRAÇÃO DE BREAK E CONTINUE ===\n");
    
    // Exemplo 1: break para sair de loop
    printf("Exemplo com break (parar ao encontrar 7):\n");
    for (int i = 1; i <= 10; i++) {
        if (i == 7) {
            printf("Encontrou 7, parando o loop\n");
            break;
        }
        printf("%d ", i);
    }
    printf("\n\n");
    
    // Exemplo 2: continue para pular iterações
    printf("Exemplo com continue (pular números pares):\n");
    printf("Números ímpares de 1 a 10: ");
    for (int i = 1; i <= 10; i++) {
        if (i % 2 == 0) {
            continue; // Pula números pares
        }
        printf("%d ", i);
    }
    printf("\n\n");
    
    // Exemplo 3: break em loops aninhados
    printf("Break em loops aninhados (encontrar coordenada específica):\n");
    bool encontrou = false;
    int target_x = 2, target_y = 3;
    
    for (int x = 0; x < 5 && !encontrou; x++) {
        for (int y = 0; y < 5; y++) {
            printf("Verificando (%d,%d) ", x, y);
            if (x == target_x && y == target_y) {
                printf("- Encontrado!\n");
                encontrou = true;
                break; // Sai do loop interno
            }
            printf("\n");
        }
        if (encontrou) break; // Sai do loop externo
    }
    
    printf("\n");
}

/**
 * Demonstra função com múltiplos pontos de retorno
 */
int calcular_fatorial_com_validacao(int n) {
    // Validação de entrada com return antecipado
    if (n < 0) {
        printf("Erro: Fatorial não definido para números negativos\n");
        return -1; // Retorno de erro
    }
    
    if (n == 0 || n == 1) {
        return 1; // Casos base
    }
    
    // Cálculo normal
    int resultado = 1;
    for (int i = 2; i <= n; i++) {
        resultado *= i;
    }
    
    return resultado;
}

/**
 * Demonstra estruturas de retorno e validação
 */
void demonstrar_returns() {
    printf("=== DEMONSTRAÇÃO DE RETURNS ===\n");
    
    int numeros[] = {-1, 0, 1, 5, 10};
    int tamanho = sizeof(numeros) / sizeof(numeros[0]);
    
    for (int i = 0; i < tamanho; i++) {
        int numero = numeros[i];
        printf("Fatorial de %d: ", numero);
        
        int resultado = calcular_fatorial_com_validacao(numero);
        if (resultado == -1) {
            printf("Cálculo inválido\n");
        } else {
            printf("%d\n", resultado);
        }
    }
    
    printf("\n");
}

// ==================== APLICAÇÕES PRÁTICAS ====================

/**
 * Sistema de calculadora simples demonstrando uso integrado de controle de fluxo
 */
void calculadora_simples() {
    printf("=== CALCULADORA SIMPLES (DEMONSTRAÇÃO) ===\n");
    
    // Simulação de operações (em um programa real, usaria entrada do usuário)
    struct {
        double a, b;
        char operador;
    } operacoes[] = {
        {10.0, 5.0, '+'},
        {15.0, 3.0, '-'},
        {6.0, 4.0, '*'},
        {20.0, 4.0, '/'},
        {10.0, 0.0, '/'},  // Teste divisão por zero
        {5.0, 2.0, '%'}    // Operador inválido
    };
    
    int num_operacoes = sizeof(operacoes) / sizeof(operacoes[0]);
    
    for (int i = 0; i < num_operacoes; i++) {
        double a = operacoes[i].a;
        double b = operacoes[i].b;
        char op = operacoes[i].operador;
        double resultado = 0;
        bool operacao_valida = true;
        
        printf("Operação %d: %.1f %c %.1f = ", i+1, a, op, b);
        
        switch (op) {
            case '+':
                resultado = a + b;
                break;
            case '-':
                resultado = a - b;
                break;
            case '*':
                resultado = a * b;
                break;
            case '/':
                if (b != 0) {
                    resultado = a / b;
                } else {
                    printf("Erro: Divisão por zero!");
                    operacao_valida = false;
                }
                break;
            default:
                printf("Erro: Operador inválido!");
                operacao_valida = false;
                break;
        }
        
        if (operacao_valida) {
            printf("%.2f", resultado);
        }
        
        printf("\n");
    }
    
    printf("\n");
}

/**
 * Demonstra análise de dados com controle de fluxo
 */
void analisar_dados() {
    printf("=== ANÁLISE DE DADOS ===\n");
    
    int vendas[] = {150, 200, 180, 220, 190, 250, 300, 280, 320, 290};
    int dias = sizeof(vendas) / sizeof(vendas[0]);
    
    // Análise usando vários tipos de loops e condições
    int total = 0;
    int maior_venda = vendas[0];
    int menor_venda = vendas[0];
    int dias_acima_media = 0;
    int sequencia_crescimento = 0;
    int max_sequencia = 0;
    
    // Primeira passada: estatísticas básicas
    for (int i = 0; i < dias; i++) {
        total += vendas[i];
        
        if (vendas[i] > maior_venda) {
            maior_venda = vendas[i];
        }
        
        if (vendas[i] < menor_venda) {
            menor_venda = vendas[i];
        }
    }
    
    double media = (double)total / dias;
    
    // Segunda passada: análise de tendências
    for (int i = 0; i < dias; i++) {
        if (vendas[i] > media) {
            dias_acima_media++;
        }
        
        // Verificar sequências de crescimento
        if (i > 0 && vendas[i] > vendas[i-1]) {
            sequencia_crescimento++;
        } else {
            if (sequencia_crescimento > max_sequencia) {
                max_sequencia = sequencia_crescimento;
            }
            sequencia_crescimento = 0;
        }
    }
    
    // Verificar última sequência
    if (sequencia_crescimento > max_sequencia) {
        max_sequencia = sequencia_crescimento;
    }
    
    // Relatório
    printf("Dados de vendas dos últimos %d dias:\n", dias);
    printf("Vendas por dia: ");
    for (int i = 0; i < dias; i++) {
        printf("%d ", vendas[i]);
    }
    printf("\n\n");
    
    printf("Estatísticas:\n");
    printf("- Total de vendas: %d\n", total);
    printf("- Média diária: %.1f\n", media);
    printf("- Maior venda: %d\n", maior_venda);
    printf("- Menor venda: %d\n", menor_venda);
    printf("- Dias acima da média: %d/%d\n", dias_acima_media, dias);
    printf("- Maior sequência de crescimento: %d dias\n", max_sequencia);
    
    // Classificação da performance
    if (media >= 250) {
        printf("- Avaliação: Excelente performance!\n");
    } else if (media >= 200) {
        printf("- Avaliação: Boa performance\n");
    } else if (media >= 150) {
        printf("- Avaliação: Performance regular\n");
    } else {
        printf("- Avaliação: Performance abaixo do esperado\n");
    }
    
    printf("\n");
}

// ==================== FUNÇÃO PRINCIPAL ====================

/**
 * Função principal que executa todas as demonstrações
 */
int main() {
    printf("╔═══════════════════════════════════════════════════════════╗\n");
    printf("║        DEMONSTRAÇÃO COMPLETA DE CONTROLE DE FLUXO        ║\n");
    printf("║                      LINGUAGEM C                         ║\n");
    printf("╚═══════════════════════════════════════════════════════════╝\n\n");
    
    // Executar todas as demonstrações
    demonstrar_if_else();
    demonstrar_switch_case();
    demonstrar_for_loops();
    demonstrar_while_loops();
    demonstrar_do_while();
    demonstrar_break_continue();
    demonstrar_returns();
    calculadora_simples();
    analisar_dados();
    
    printf("╔═══════════════════════════════════════════════════════════╗\n");
    printf("║            DEMONSTRAÇÃO CONCLUÍDA COM SUCESSO            ║\n");
    printf("║                                                           ║\n");
    printf("║ Este exemplo abrangeu:                                    ║\n");
    printf("║ • Estruturas condicionais (if/else, switch)              ║\n");
    printf("║ • Estruturas de repetição (for, while, do-while)         ║\n");
    printf("║ • Estruturas de salto (break, continue, return)          ║\n");
    printf("║ • Aplicações práticas e análise de dados                 ║\n");
    printf("║                                                           ║\n");
    printf("║ Para mais exemplos, consulte a documentação em           ║\n");
    printf("║ docs/01-introducao/02-controle-fluxo/                    ║\n");
    printf("╚═══════════════════════════════════════════════════════════╝\n");
    
    return 0;
}