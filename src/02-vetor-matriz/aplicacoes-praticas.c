#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// ============================================================================
// APLICAÇÃO 1: SISTEMA DE NOTAS ESCOLARES
// ============================================================================

typedef struct {
    char nome[50];
    float notas[4];  // 4 bimestres
    float media;
    int aprovado;
} Aluno;

void sistema_notas() {
    printf("=== SISTEMA DE NOTAS ESCOLARES ===\n\n");
    
    int num_alunos = 5;
    Aluno turma[5] = {
        {"Ana Silva", {8.5, 7.2, 9.0, 8.8}, 0, 0},
        {"Bruno Costa", {6.0, 5.5, 7.2, 6.8}, 0, 0},
        {"Carlos Lima", {9.2, 8.7, 9.5, 9.0}, 0, 0},
        {"Diana Santos", {4.5, 5.0, 6.2, 5.8}, 0, 0},
        {"Eduardo Pereira", {7.8, 8.2, 7.5, 8.0}, 0, 0}
    };
    
    // Calculando médias e status de aprovação
    printf("Processamento das notas:\n");
    printf("%-20s %s %s %s %s %s %s\n", "Nome", "1°B", "2°B", "3°B", "4°B", "Média", "Status");
    printf("------------------------------------------------------------------------\n");
    
    float soma_classe = 0;
    int aprovados = 0;
    
    for (int i = 0; i < num_alunos; i++) {
        float soma = 0;
        for (int j = 0; j < 4; j++) {
            soma += turma[i].notas[j];
        }
        turma[i].media = soma / 4;
        turma[i].aprovado = (turma[i].media >= 7.0) ? 1 : 0;
        
        soma_classe += turma[i].media;
        if (turma[i].aprovado) aprovados++;
        
        printf("%-20s %.1f %.1f %.1f %.1f %.2f %s\n", 
               turma[i].nome, 
               turma[i].notas[0], turma[i].notas[1], 
               turma[i].notas[2], turma[i].notas[3],
               turma[i].media,
               turma[i].aprovado ? "APROVADO" : "REPROVADO");
    }
    
    printf("------------------------------------------------------------------------\n");
    printf("Média da classe: %.2f\n", soma_classe / num_alunos);
    printf("Taxa de aprovação: %.1f%% (%d/%d alunos)\n\n", 
           (float)aprovados/num_alunos*100, aprovados, num_alunos);
}

// ============================================================================
// APLICAÇÃO 2: PROCESSAMENTO DE IMAGEM (FILTROS)
// ============================================================================

// Simula uma imagem em escala de cinza (0-255)
void processar_imagem() {
    printf("=== PROCESSAMENTO DE IMAGEM ===\n\n");
    
    const int ALTURA = 8, LARGURA = 8;
    
    // Imagem original (simulada)
    int imagem[8][8] = {
        {100, 120, 130, 140, 150, 160, 170, 180},
        {110, 125, 135, 145, 155, 165, 175, 185},
        {120, 130, 140, 150, 160, 170, 180, 190},
        {130, 135, 145, 155, 165, 175, 185, 195},
        {140, 140, 150, 160, 170, 180, 190, 200},
        {150, 145, 155, 165, 175, 185, 195, 205},
        {160, 150, 160, 170, 180, 190, 200, 210},
        {170, 155, 165, 175, 185, 195, 205, 215}
    };
    
    int resultado[8][8];
    
    printf("Imagem original (8x8 pixels):\n");
    for (int i = 0; i < ALTURA; i++) {
        for (int j = 0; j < LARGURA; j++) {
            printf("%3d ", imagem[i][j]);
        }
        printf("\n");
    }
    
    // Filtro de suavização (blur) 3x3
    printf("\nAplicando filtro de suavização 3x3...\n");
    
    // Kernel de suavização
    float kernel[3][3] = {
        {1.0/9, 1.0/9, 1.0/9},
        {1.0/9, 1.0/9, 1.0/9},
        {1.0/9, 1.0/9, 1.0/9}
    };
    
    // Aplicação do filtro (convolução)
    for (int i = 1; i < ALTURA-1; i++) {
        for (int j = 1; j < LARGURA-1; j++) {
            float soma = 0;
            for (int ki = -1; ki <= 1; ki++) {
                for (int kj = -1; kj <= 1; kj++) {
                    soma += imagem[i+ki][j+kj] * kernel[ki+1][kj+1];
                }
            }
            resultado[i][j] = (int)soma;
        }
    }
    
    // Bordas mantidas iguais
    for (int i = 0; i < ALTURA; i++) {
        resultado[i][0] = imagem[i][0];
        resultado[i][LARGURA-1] = imagem[i][LARGURA-1];
    }
    for (int j = 0; j < LARGURA; j++) {
        resultado[0][j] = imagem[0][j];
        resultado[ALTURA-1][j] = imagem[ALTURA-1][j];
    }
    
    printf("\nImagem após filtro de suavização:\n");
    for (int i = 0; i < ALTURA; i++) {
        for (int j = 0; j < LARGURA; j++) {
            printf("%3d ", resultado[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// ============================================================================
// APLICAÇÃO 3: ANÁLISE DE DADOS CIENTÍFICOS
// ============================================================================

void analise_dados_cientificos() {
    printf("=== ANÁLISE DE DADOS CIENTÍFICOS ===\n");
    printf("Simulação: Temperatura diária em 5 cidades durante 1 semana\n\n");
    
    const char cidades[5][20] = {"São Paulo", "Rio de Janeiro", "Brasília", "Salvador", "Manaus"};
    const char dias[7][15] = {"Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sábado", "Domingo"};
    
    // Dados de temperatura (°C)
    float temperaturas[5][7] = {
        {22.5, 24.0, 23.2, 21.8, 25.1, 26.3, 24.7},  // São Paulo
        {28.3, 29.1, 30.2, 27.9, 31.0, 32.1, 30.5},  // Rio de Janeiro
        {25.8, 27.2, 26.4, 24.9, 28.3, 29.0, 27.6},  // Brasília
        {30.1, 31.2, 32.0, 29.8, 33.1, 34.2, 32.8},  // Salvador
        {32.4, 33.1, 31.9, 30.6, 34.2, 35.1, 33.7}   // Manaus
    };
    
    // Exibindo dados
    printf("%-15s", "Cidade");
    for (int j = 0; j < 7; j++) {
        printf("%10s", dias[j]);
    }
    printf("%10s %10s %10s\n", "Média", "Mín", "Máx");
    printf("---------------------------------------------------------------------------------\n");
    
    float soma_geral = 0;
    int total_medicoes = 0;
    
    for (int i = 0; i < 5; i++) {
        printf("%-15s", cidades[i]);
        
        float soma_cidade = 0, min_cidade = temperaturas[i][0], max_cidade = temperaturas[i][0];
        
        for (int j = 0; j < 7; j++) {
            printf("%9.1f°", temperaturas[i][j]);
            soma_cidade += temperaturas[i][j];
            soma_geral += temperaturas[i][j];
            total_medicoes++;
            
            if (temperaturas[i][j] < min_cidade) min_cidade = temperaturas[i][j];
            if (temperaturas[i][j] > max_cidade) max_cidade = temperaturas[i][j];
        }
        
        float media_cidade = soma_cidade / 7;
        printf("%9.1f°%9.1f°%9.1f°\n", media_cidade, min_cidade, max_cidade);
    }
    
    printf("---------------------------------------------------------------------------------\n");
    printf("Média nacional: %.1f°C\n\n", soma_geral / total_medicoes);
    
    // Análise de correlação entre cidades
    printf("Análise de correlação de temperaturas:\n");
    printf("Comparando São Paulo com as outras cidades:\n");
    
    for (int i = 1; i < 5; i++) {
        float soma_sp = 0, soma_cidade = 0, soma_produto = 0;
        float soma_sp_quadrado = 0, soma_cidade_quadrado = 0;
        
        for (int j = 0; j < 7; j++) {
            soma_sp += temperaturas[0][j];
            soma_cidade += temperaturas[i][j];
            soma_produto += temperaturas[0][j] * temperaturas[i][j];
            soma_sp_quadrado += temperaturas[0][j] * temperaturas[0][j];
            soma_cidade_quadrado += temperaturas[i][j] * temperaturas[i][j];
        }
        
        float correlacao = (7 * soma_produto - soma_sp * soma_cidade) /
                          sqrt((7 * soma_sp_quadrado - soma_sp * soma_sp) *
                               (7 * soma_cidade_quadrado - soma_cidade * soma_cidade));
        
        printf("São Paulo x %-15s: correlação = %.3f ", cidades[i], correlacao);
        if (correlacao > 0.8) printf("(forte correlação positiva)\n");
        else if (correlacao > 0.3) printf("(correlação moderada)\n");
        else printf("(correlação fraca)\n");
    }
    printf("\n");
}

// ============================================================================
// APLICAÇÃO 4: ALGORITMO GENÉTICO SIMPLES
// ============================================================================

void algoritmo_genetico_simples() {
    printf("=== ALGORITMO GENÉTICO SIMPLES ===\n");
    printf("Problema: Encontrar vetor binário que maximize a soma dos elementos\n");
    printf("Tamanho do cromossomo: 8 bits\n\n");
    
    const int TAMANHO_POP = 6;
    const int TAMANHO_CROMOSSOMO = 8;
    const int GERACOES = 5;
    
    // População inicial (matriz 6x8)
    int populacao[6][8] = {
        {1, 0, 1, 1, 0, 1, 0, 1},
        {0, 1, 1, 0, 1, 1, 1, 0},
        {1, 1, 0, 1, 1, 0, 1, 1},
        {0, 0, 1, 1, 1, 1, 0, 0},
        {1, 0, 0, 1, 0, 1, 1, 1},
        {0, 1, 1, 1, 0, 0, 1, 0}
    };
    
    for (int geracao = 0; geracao < GERACOES; geracao++) {
        printf("Geração %d:\n", geracao + 1);
        printf("Indivíduo     Cromossomo        Fitness\n");
        printf("----------------------------------------\n");
        
        int fitness[6];
        int melhor_fitness = 0, melhor_individuo = 0;
        
        // Calcular fitness (soma dos bits)
        for (int i = 0; i < TAMANHO_POP; i++) {
            fitness[i] = 0;
            printf("    %d         ", i + 1);
            
            for (int j = 0; j < TAMANHO_CROMOSSOMO; j++) {
                printf("%d", populacao[i][j]);
                fitness[i] += populacao[i][j];
            }
            
            printf("           %d\n", fitness[i]);
            
            if (fitness[i] > melhor_fitness) {
                melhor_fitness = fitness[i];
                melhor_individuo = i;
            }
        }
        
        printf("Melhor: Indivíduo %d com fitness %d\n\n", 
               melhor_individuo + 1, melhor_fitness);
        
        // Mutação simples (inverter um bit aleatório em cada indivíduo)
        if (geracao < GERACOES - 1) {
            for (int i = 0; i < TAMANHO_POP; i++) {
                int pos_mutacao = rand() % TAMANHO_CROMOSSOMO;
                populacao[i][pos_mutacao] = 1 - populacao[i][pos_mutacao];
            }
        }
    }
}

// ============================================================================
// APLICAÇÃO 5: SIMULAÇÃO DE JOGO DA VIDA (CONWAY)
// ============================================================================

void jogo_da_vida() {
    printf("=== JOGO DA VIDA (CONWAY) ===\n");
    printf("Simulação em grid 10x10 por 3 gerações\n\n");
    
    const int SIZE = 10;
    int grid[10][10] = {0};  // Inicializar com zeros
    int proximo[10][10];
    
    // Configuração inicial (glider)
    grid[1][2] = 1;
    grid[2][3] = 1;
    grid[3][1] = 1;
    grid[3][2] = 1;
    grid[3][3] = 1;
    
    // Adicionar mais algumas células vivas
    grid[6][6] = 1;
    grid[6][7] = 1;
    grid[7][6] = 1;
    grid[7][7] = 1;
    
    for (int geracao = 0; geracao < 4; geracao++) {
        printf("Geração %d:\n", geracao);
        
        // Imprimir grid atual
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                printf("%c ", grid[i][j] ? '●' : '○');
            }
            printf("\n");
        }
        printf("\n");
        
        if (geracao < 3) {
            // Calcular próxima geração
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    int vizinhos = 0;
                    
                    // Contar vizinhos vivos
                    for (int di = -1; di <= 1; di++) {
                        for (int dj = -1; dj <= 1; dj++) {
                            if (di == 0 && dj == 0) continue;
                            
                            int ni = i + di;
                            int nj = j + dj;
                            
                            if (ni >= 0 && ni < SIZE && nj >= 0 && nj < SIZE) {
                                vizinhos += grid[ni][nj];
                            }
                        }
                    }
                    
                    // Aplicar regras
                    if (grid[i][j] == 1) {  // Célula viva
                        proximo[i][j] = (vizinhos == 2 || vizinhos == 3) ? 1 : 0;
                    } else {  // Célula morta
                        proximo[i][j] = (vizinhos == 3) ? 1 : 0;
                    }
                }
            }
            
            // Copiar próxima geração para grid atual
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    grid[i][j] = proximo[i][j];
                }
            }
        }
    }
}

int main() {
    printf("***** APLICAÇÕES PRÁTICAS DE VETORES E MATRIZES *****\n\n");
    
    srand(time(NULL));  // Inicializar gerador de números aleatórios
    
    // 1. Sistema de notas escolares
    sistema_notas();
    
    // 2. Processamento de imagem
    processar_imagem();
    
    // 3. Análise de dados científicos
    analise_dados_cientificos();
    
    // 4. Algoritmo genético simples
    algoritmo_genetico_simples();
    
    // 5. Jogo da vida
    jogo_da_vida();
    
    printf("=== RESUMO DAS APLICAÇÕES ===\n");
    printf("1. Sistema de Notas: Processamento de dados tabulares\n");
    printf("2. Processamento de Imagem: Convolução e filtros matriciais\n");
    printf("3. Análise Científica: Estatísticas e correlações\n");
    printf("4. Algoritmo Genético: Otimização populacional\n");
    printf("5. Jogo da Vida: Autômatos celulares\n\n");
    
    printf("Todas essas aplicações demonstram a versatilidade e importância\n");
    printf("dos vetores e matrizes em problemas computacionais reais.\n");
    
    return 0;
}