/**
 * Vertex Cover - Algoritmo de Aproximação 2-Aproximação via Maximal Matching
 * 
 * Problema: Encontrar conjunto mínimo de vértices que cobre todas as arestas
 * Algoritmo: Incluir ambos endpoints de cada aresta em um matching maximal
 * Fator de Aproximação: 2 (garantido)
 * Complexidade: O(V + E) tempo, O(V) espaço
 * 
 * Autor: Implementação educacional
 * Data: 2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_VERTICES 100

/**
 * Estrutura para representar um grafo usando lista de adjacências
 */
typedef struct {
    int n_vertices;                          // Número de vértices
    bool adj[MAX_VERTICES][MAX_VERTICES];    // Matriz de adjacência
    int graus[MAX_VERTICES];                 // Grau de cada vértice
} Grafo;

/**
 * Inicializa um grafo vazio com n vértices
 */
void inicializar_grafo(Grafo* g, int n) {
    g->n_vertices = n;
    
    // Inicializa matriz de adjacência e graus
    for (int i = 0; i < n; i++) {
        g->graus[i] = 0;
        for (int j = 0; j < n; j++) {
            g->adj[i][j] = false;
        }
    }
}

/**
 * Adiciona uma aresta não-direcionada entre u e v
 */
void adicionar_aresta(Grafo* g, int u, int v) {
    if (u < 0 || u >= g->n_vertices || v < 0 || v >= g->n_vertices) {
        printf("Erro: vértices inválidos\n");
        return;
    }
    
    if (!g->adj[u][v]) {  // Evita arestas duplicadas
        g->adj[u][v] = true;
        g->adj[v][u] = true;
        g->graus[u]++;
        g->graus[v]++;
    }
}

/**
 * Remove uma aresta entre u e v
 */
void remover_aresta(Grafo* g, int u, int v) {
    if (g->adj[u][v]) {
        g->adj[u][v] = false;
        g->adj[v][u] = false;
        g->graus[u]--;
        g->graus[v]--;
    }
}

/**
 * Verifica se ainda existem arestas no grafo
 */
bool tem_arestas(Grafo* g) {
    for (int i = 0; i < g->n_vertices; i++) {
        if (g->graus[i] > 0) {
            return true;
        }
    }
    return false;
}

/**
 * Encontra uma aresta arbitrária no grafo
 * Retorna true se encontrou, false caso contrário
 */
bool encontrar_aresta(Grafo* g, int* u, int* v) {
    for (int i = 0; i < g->n_vertices; i++) {
        for (int j = i + 1; j < g->n_vertices; j++) {
            if (g->adj[i][j]) {
                *u = i;
                *v = j;
                return true;
            }
        }
    }
    return false;
}

/**
 * Remove todas as arestas incidentes ao vértice v
 */
void remover_arestas_incidentes(Grafo* g, int v) {
    for (int i = 0; i < g->n_vertices; i++) {
        if (g->adj[v][i]) {
            remover_aresta(g, v, i);
        }
    }
}

/**
 * Algoritmo de 2-Aproximação para Vertex Cover via Maximal Matching
 * 
 * Algoritmo:
 * 1. Enquanto houver arestas:
 *    a) Escolhe aresta (u,v) arbitrária
 *    b) Adiciona u e v ao cover
 *    c) Remove todas arestas incidentes a u ou v
 * 
 * Garantia: |cover| ≤ 2 × OPT
 * 
 * @param g Grafo de entrada
 * @param cover Array para armazenar vértices no cover
 * @return Tamanho do vertex cover
 */
int vertex_cover_2approx(Grafo* g, int cover[]) {
    // Cria cópia do grafo para não modificar o original
    Grafo g_temp;
    memcpy(&g_temp, g, sizeof(Grafo));
    
    int tamanho_cover = 0;
    int u, v;
    
    printf("\n=== Executando Algoritmo de 2-Aproximação ===\n");
    
    int iteracao = 1;
    // Enquanto houver arestas no grafo
    while (tem_arestas(&g_temp)) {
        // Encontra uma aresta arbitrária
        if (encontrar_aresta(&g_temp, &u, &v)) {
            printf("\nIteração %d:\n", iteracao++);
            printf("  Aresta escolhida: (%d, %d)\n", u, v);
            
            // Adiciona ambos endpoints ao cover
            cover[tamanho_cover++] = u;
            cover[tamanho_cover++] = v;
            
            printf("  Vértices adicionados ao cover: %d, %d\n", u, v);
            printf("  Tamanho atual do cover: %d\n", tamanho_cover);
            
            // Remove todas arestas incidentes a u ou v
            remover_arestas_incidentes(&g_temp, u);
            remover_arestas_incidentes(&g_temp, v);
        }
    }
    
    printf("\n=== Algoritmo Concluído ===\n");
    printf("Tamanho final do vertex cover: %d\n", tamanho_cover);
    
    return tamanho_cover;
}

/**
 * Verifica se um conjunto de vértices é um vertex cover válido
 */
bool verificar_cover(Grafo* g, int cover[], int tamanho) {
    // Para cada aresta, verifica se pelo menos um endpoint está no cover
    for (int i = 0; i < g->n_vertices; i++) {
        for (int j = i + 1; j < g->n_vertices; j++) {
            if (g->adj[i][j]) {
                // Verifica se i ou j está no cover
                bool coberta = false;
                for (int k = 0; k < tamanho; k++) {
                    if (cover[k] == i || cover[k] == j) {
                        coberta = true;
                        break;
                    }
                }
                
                if (!coberta) {
                    printf("Erro: Aresta (%d, %d) não está coberta!\n", i, j);
                    return false;
                }
            }
        }
    }
    return true;
}

/**
 * Imprime o grafo
 */
void imprimir_grafo(Grafo* g) {
    printf("\nGrafo com %d vértices:\n", g->n_vertices);
    printf("Arestas: ");
    
    int count = 0;
    for (int i = 0; i < g->n_vertices; i++) {
        for (int j = i + 1; j < g->n_vertices; j++) {
            if (g->adj[i][j]) {
                printf("(%d,%d) ", i, j);
                count++;
            }
        }
    }
    printf("\nTotal de arestas: %d\n", count);
    
    printf("Graus: ");
    for (int i = 0; i < g->n_vertices; i++) {
        printf("v%d:%d ", i, g->graus[i]);
    }
    printf("\n");
}

/**
 * Exemplo 1: Grafo simples em linha
 * 
 *    0 --- 1 --- 2 --- 3
 * 
 * Vertex Cover ótimo: {1, 2} (tamanho 2)
 * 2-Aproximação pode dar: {0,1,2,3} ou {1,2} dependendo da escolha
 */
void exemplo1() {
    printf("\n" "========================================\n");
    printf("EXEMPLO 1: Grafo em Linha (Path Graph)\n");
    printf("========================================\n");
    
    Grafo g;
    inicializar_grafo(&g, 4);
    
    adicionar_aresta(&g, 0, 1);
    adicionar_aresta(&g, 1, 2);
    adicionar_aresta(&g, 2, 3);
    
    imprimir_grafo(&g);
    
    int cover[MAX_VERTICES];
    int tamanho = vertex_cover_2approx(&g, cover);
    
    printf("\nVertex Cover encontrado: {");
    for (int i = 0; i < tamanho; i++) {
        printf("%d%s", cover[i], i < tamanho - 1 ? ", " : "");
    }
    printf("}\n");
    
    // Verifica se é válido
    if (verificar_cover(&g, cover, tamanho)) {
        printf("✓ Cover válido!\n");
    } else {
        printf("✗ Cover inválido!\n");
    }
    
    printf("\nAnálise:\n");
    printf("- Tamanho do cover: %d\n", tamanho);
    printf("- Vertex cover ótimo: 2 vértices\n");
    printf("- Fator de aproximação real: %.2f\n", (float)tamanho / 2);
}

/**
 * Exemplo 2: Grafo completo K4
 * 
 *    0 --- 1
 *    |\ /|
 *    | X |
 *    |/ \|
 *    3 --- 2
 * 
 * Vertex Cover ótimo: qualquer 3 vértices (tamanho 3)
 * 2-Aproximação: 4 vértices (pior caso)
 */
void exemplo2() {
    printf("\n" "========================================\n");
    printf("EXEMPLO 2: Grafo Completo K4\n");
    printf("========================================\n");
    
    Grafo g;
    inicializar_grafo(&g, 4);
    
    // Adiciona todas as arestas (grafo completo)
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            adicionar_aresta(&g, i, j);
        }
    }
    
    imprimir_grafo(&g);
    
    int cover[MAX_VERTICES];
    int tamanho = vertex_cover_2approx(&g, cover);
    
    printf("\nVertex Cover encontrado: {");
    for (int i = 0; i < tamanho; i++) {
        printf("%d%s", cover[i], i < tamanho - 1 ? ", " : "");
    }
    printf("}\n");
    
    if (verificar_cover(&g, cover, tamanho)) {
        printf("✓ Cover válido!\n");
    }
    
    printf("\nAnálise:\n");
    printf("- Tamanho do cover: %d\n", tamanho);
    printf("- Vertex cover ótimo: 3 vértices\n");
    printf("- Fator de aproximação real: %.2f\n", (float)tamanho / 3);
}

/**
 * Exemplo 3: Grafo estrela
 * 
 *      1
 *      |
 *  2---0---3
 *      |
 *      4
 * 
 * Vertex Cover ótimo: {0} (tamanho 1)
 * 2-Aproximação: todos os vértices (pior caso tight)
 */
void exemplo3() {
    printf("\n" "========================================\n");
    printf("EXEMPLO 3: Grafo Estrela (Star Graph)\n");
    printf("========================================\n");
    
    Grafo g;
    inicializar_grafo(&g, 5);
    
    // Centro é vértice 0
    adicionar_aresta(&g, 0, 1);
    adicionar_aresta(&g, 0, 2);
    adicionar_aresta(&g, 0, 3);
    adicionar_aresta(&g, 0, 4);
    
    imprimir_grafo(&g);
    
    int cover[MAX_VERTICES];
    int tamanho = vertex_cover_2approx(&g, cover);
    
    printf("\nVertex Cover encontrado: {");
    for (int i = 0; i < tamanho; i++) {
        printf("%d%s", cover[i], i < tamanho - 1 ? ", " : "");
    }
    printf("}\n");
    
    if (verificar_cover(&g, cover, tamanho)) {
        printf("✓ Cover válido!\n");
    }
    
    printf("\nAnálise:\n");
    printf("- Tamanho do cover: %d\n", tamanho);
    printf("- Vertex cover ótimo: 1 vértice (centro)\n");
    printf("- Fator de aproximação real: %.2f\n", (float)tamanho / 1);
    printf("- NOTA: Este é o PIOR CASO - atinge exatamente fator 2!\n");
}

/**
 * Função principal
 */
int main() {
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════╗\n");
    printf("║   VERTEX COVER - Algoritmo de 2-Aproximação              ║\n");
    printf("║   Via Maximal Matching                                    ║\n");
    printf("╚═══════════════════════════════════════════════════════════╝\n");
    
    printf("\nEste programa demonstra o algoritmo de 2-aproximação\n");
    printf("para o problema NP-Completo de Vertex Cover.\n");
    printf("\nGarantia: |cover| ≤ 2 × OPT\n");
    printf("Complexidade: O(V + E)\n");
    
    // Executa exemplos
    exemplo1();
    exemplo2();
    exemplo3();
    
    printf("\n" "========================================\n");
    printf("RESUMO\n");
    printf("========================================\n");
    printf("O algoritmo de 2-aproximação via maximal matching:\n");
    printf("✓ É rápido: O(V + E)\n");
    printf("✓ Tem garantia teórica: nunca pior que 2× ótimo\n");
    printf("✓ É simples de implementar\n");
    printf("✗ Pode dar soluções ruins em grafos estrela\n");
    printf("✗ Não é sempre melhor que heurísticas na prática\n");
    printf("\nLimitação teórica: 2-aproximação é essencialmente ótimo\n");
    printf("(não existe (2-ε)-aprox a menos que P=NP)\n");
    
    return 0;
}
