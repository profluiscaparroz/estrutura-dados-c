# Problema Prático: Sistema de Navegação GPS (Menor Caminho)

## 📋 Descrição do Problema

Um aplicativo de GPS precisa:
- Encontrar o caminho mais curto entre dois pontos
- Considerar distâncias reais das ruas
- Evitar tráfego (pesos dinâmicos)
- Sugerir rotas alternativas
- Calcular tempo estimado de chegada

**Por que usar Grafos?**
- Modelar rede de ruas (vértices = cruzamentos, arestas = ruas)
- Dijkstra para menor caminho com pesos
- BFS para menor número de ruas
- Representar conexões complexas

## 🔴 Problema: Busca Exaustiva Sem Algoritmo Adequado

```c
#include <stdio.h>
#include <limits.h>

#define V 10

// PROBLEMA: Matriz de adjacência desperdiça memória
int grafo[V][V];

// PROBLEMA: Força bruta - testa todos caminhos possíveis
int menorCaminho = INT_MAX;

void buscarTodosCaminhos(int atual, int destino, int distancia) {
    if (atual == destino) {
        if (distancia < menorCaminho) {
            menorCaminho = distancia;
        }
        return;
    }
    
    // PROBLEMA: Complexidade exponencial!
    // Pode revisitar nós infinitamente
    for (int i = 0; i < V; i++) {
        if (grafo[atual][i] > 0) {
            buscarTodosCaminhos(i, destino, distancia + grafo[atual][i]);
        }
    }
}

int main() {
    // Inicializar grafo...
    buscarTodosCaminhos(0, 5, 0);
    printf("Menor caminho: %d\n", menorCaminho);
    return 0;
}
```

### Problemas Identificados:
1. ❌ Complexidade exponencial - testa todos caminhos
2. ❌ Pode entrar em loop infinito
3. ❌ Não marca nós visitados
4. ❌ Matriz desperdiça memória para grafos esparsos
5. ❌ Não reconstrói o caminho

## ✅ Solução: Algoritmo de Dijkstra com Heap

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define MAX_VERTICES 20
#define INF INT_MAX

// ============= ESTRUTURAS =============

typedef struct {
    char nome[50];
    double latitude;
    double longitude;
} Local;

// Nó da lista de adjacência
typedef struct Aresta {
    int destino;
    int peso;  // Distância em metros
    char nomeRua[50];
    struct Aresta *proxima;
} Aresta;

// Grafo usando lista de adjacência
typedef struct {
    Local locais[MAX_VERTICES];
    Aresta *adjacencias[MAX_VERTICES];
    int numVertices;
} Grafo;

// Nó do heap de prioridade para Dijkstra
typedef struct {
    int vertice;
    int distancia;
} NoHeap;

// Min-Heap para Dijkstra
typedef struct {
    NoHeap nos[MAX_VERTICES];
    int tamanho;
    int posicao[MAX_VERTICES];  // Rastreia posição no heap
} MinHeap;

// ============= FUNÇÕES DO HEAP =============

void inicializarHeap(MinHeap *h) {
    h->tamanho = 0;
}

void trocarNos(NoHeap *a, NoHeap *b) {
    NoHeap temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(MinHeap *h, int idx) {
    if (idx == 0) return;
    
    int pai = (idx - 1) / 2;
    
    if (h->nos[idx].distancia < h->nos[pai].distancia) {
        // Atualizar posições
        h->posicao[h->nos[idx].vertice] = pai;
        h->posicao[h->nos[pai].vertice] = idx;
        
        trocarNos(&h->nos[idx], &h->nos[pai]);
        heapifyUp(h, pai);
    }
}

void heapifyDown(MinHeap *h, int idx) {
    int menor = idx;
    int esquerda = 2 * idx + 1;
    int direita = 2 * idx + 2;
    
    if (esquerda < h->tamanho && 
        h->nos[esquerda].distancia < h->nos[menor].distancia) {
        menor = esquerda;
    }
    
    if (direita < h->tamanho && 
        h->nos[direita].distancia < h->nos[menor].distancia) {
        menor = direita;
    }
    
    if (menor != idx) {
        h->posicao[h->nos[idx].vertice] = menor;
        h->posicao[h->nos[menor].vertice] = idx;
        
        trocarNos(&h->nos[idx], &h->nos[menor]);
        heapifyDown(h, menor);
    }
}

void inserirHeap(MinHeap *h, int vertice, int distancia) {
    if (h->tamanho >= MAX_VERTICES) return;
    
    int idx = h->tamanho;
    h->nos[idx].vertice = vertice;
    h->nos[idx].distancia = distancia;
    h->posicao[vertice] = idx;
    h->tamanho++;
    
    heapifyUp(h, idx);
}

NoHeap extrairMin(MinHeap *h) {
    NoHeap min = h->nos[0];
    
    h->tamanho--;
    if (h->tamanho > 0) {
        h->nos[0] = h->nos[h->tamanho];
        h->posicao[h->nos[0].vertice] = 0;
        heapifyDown(h, 0);
    }
    
    return min;
}

void diminuirChave(MinHeap *h, int vertice, int novaDistancia) {
    int idx = h->posicao[vertice];
    h->nos[idx].distancia = novaDistancia;
    heapifyUp(h, idx);
}

bool heapVazio(MinHeap *h) {
    return h->tamanho == 0;
}

// ============= FUNÇÕES DO GRAFO =============

void inicializarGrafo(Grafo *g) {
    g->numVertices = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        g->adjacencias[i] = NULL;
    }
}

int adicionarLocal(Grafo *g, const char *nome, double lat, double lon) {
    if (g->numVertices >= MAX_VERTICES) {
        printf("⚠️  Limite de vértices atingido\n");
        return -1;
    }
    
    int id = g->numVertices;
    strcpy(g->locais[id].nome, nome);
    g->locais[id].latitude = lat;
    g->locais[id].longitude = lon;
    g->numVertices++;
    
    return id;
}

void adicionarRua(Grafo *g, int origem, int destino, int distancia, const char *nomeRua) {
    // Adicionar aresta origem -> destino
    Aresta *nova = (Aresta*)malloc(sizeof(Aresta));
    nova->destino = destino;
    nova->peso = distancia;
    strcpy(nova->nomeRua, nomeRua);
    nova->proxima = g->adjacencias[origem];
    g->adjacencias[origem] = nova;
    
    // Grafo não direcionado: adicionar destino -> origem
    nova = (Aresta*)malloc(sizeof(Aresta));
    nova->destino = origem;
    nova->peso = distancia;
    strcpy(nova->nomeRua, nomeRua);
    nova->proxima = g->adjacencias[destino];
    g->adjacencias[destino] = nova;
}

// ============= ALGORITMO DE DIJKSTRA =============

void dijkstra(Grafo *g, int origem, int destino, int *distancias, int *anteriores) {
    MinHeap heap;
    inicializarHeap(&heap);
    bool visitado[MAX_VERTICES] = {false};
    
    // Inicializar distâncias
    for (int i = 0; i < g->numVertices; i++) {
        distancias[i] = INF;
        anteriores[i] = -1;
    }
    
    distancias[origem] = 0;
    inserirHeap(&heap, origem, 0);
    
    printf("\n🔍 Executando Dijkstra de '%s' para '%s'...\n\n",
           g->locais[origem].nome, g->locais[destino].nome);
    
    while (!heapVazio(&heap)) {
        NoHeap noAtual = extrairMin(&heap);
        int u = noAtual.vertice;
        
        if (visitado[u]) continue;
        visitado[u] = true;
        
        printf("  Visitando: %s (distância: %d m)\n", 
               g->locais[u].nome, distancias[u]);
        
        // Se chegou no destino, pode parar (otimização)
        if (u == destino) {
            printf("\n✓ Destino alcançado!\n");
            break;
        }
        
        // Relaxar arestas adjacentes
        Aresta *aresta = g->adjacencias[u];
        while (aresta != NULL) {
            int v = aresta->destino;
            int peso = aresta->peso;
            
            if (!visitado[v] && distancias[u] != INF) {
                int novaDistancia = distancias[u] + peso;
                
                if (novaDistancia < distancias[v]) {
                    distancias[v] = novaDistancia;
                    anteriores[v] = u;
                    
                    if (heap.posicao[v] < heap.tamanho) {
                        diminuirChave(&heap, v, novaDistancia);
                    } else {
                        inserirHeap(&heap, v, novaDistancia);
                    }
                }
            }
            
            aresta = aresta->proxima;
        }
    }
}

// Reconstruir caminho
void imprimirCaminho(Grafo *g, int origem, int destino, int *anteriores, int *distancias) {
    if (distancias[destino] == INF) {
        printf("\n❌ Não há caminho de '%s' para '%s'\n",
               g->locais[origem].nome, g->locais[destino].nome);
        return;
    }
    
    // Reconstruir caminho
    int caminho[MAX_VERTICES];
    int tamanhoCaminho = 0;
    int atual = destino;
    
    while (atual != -1) {
        caminho[tamanhoCaminho++] = atual;
        atual = anteriores[atual];
    }
    
    // Imprimir caminho (do início ao fim)
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║          ROTA ENCONTRADA               ║\n");
    printf("╚════════════════════════════════════════╝\n\n");
    
    printf("📍 Origem: %s\n", g->locais[origem].nome);
    printf("📍 Destino: %s\n", g->locais[destino].nome);
    printf("📏 Distância total: %.2f km\n\n", distancias[destino] / 1000.0);
    
    printf("🗺️  ROTA:\n");
    for (int i = tamanhoCaminho - 1; i >= 0; i--) {
        int v = caminho[i];
        
        if (i == tamanhoCaminho - 1) {
            printf("  1. 🚗 Partida: %s\n", g->locais[v].nome);
        } else {
            int anterior = caminho[i + 1];
            
            // Encontrar nome da rua
            Aresta *aresta = g->adjacencias[anterior];
            while (aresta != NULL && aresta->destino != v) {
                aresta = aresta->proxima;
            }
            
            if (i == 0) {
                printf("  %d. 🏁 Chegada: %s", tamanhoCaminho, g->locais[v].nome);
            } else {
                printf("  %d. ➡️  %s", tamanhoCaminho - i, g->locais[v].nome);
            }
            
            if (aresta) {
                printf(" (via %s - %d m)", aresta->nomeRua, aresta->peso);
            }
            printf("\n");
        }
    }
    
    // Estimar tempo (assumindo 40 km/h)
    float velocidadeMedia = 40.0; // km/h
    float tempoHoras = (distancias[destino] / 1000.0) / velocidadeMedia;
    int minutos = (int)(tempoHoras * 60);
    
    printf("\n⏱️  Tempo estimado: %d minutos (a %.0f km/h)\n", 
           minutos, velocidadeMedia);
}

// ============= MAIN =============

int main() {
    Grafo mapa;
    inicializarGrafo(&mapa);
    
    printf("╔════════════════════════════════════════╗\n");
    printf("║     SISTEMA DE NAVEGAÇÃO GPS           ║\n");
    printf("║    Algoritmo de Dijkstra - Grafos      ║\n");
    printf("╚════════════════════════════════════════╝\n");
    
    // Criar mapa de uma cidade fictícia
    int casa = adicionarLocal(&mapa, "Casa", -23.5505, -46.6333);
    int mercado = adicionarLocal(&mapa, "Mercado", -23.5515, -46.6343);
    int escola = adicionarLocal(&mapa, "Escola", -23.5525, -46.6353);
    int parque = adicionarLocal(&mapa, "Parque", -23.5535, -46.6363);
    int hospital = adicionarLocal(&mapa, "Hospital", -23.5545, -46.6373);
    int shopping = adicionarLocal(&mapa, "Shopping", -23.5555, -46.6383);
    int trabalho = adicionarLocal(&mapa, "Trabalho", -23.5565, -46.6393);
    
    printf("\n📍 Locais cadastrados: %d\n", mapa.numVertices);
    
    // Adicionar ruas (arestas) com distâncias em metros
    printf("\n🛣️  Construindo mapa de ruas...\n");
    adicionarRua(&mapa, casa, mercado, 500, "Rua das Flores");
    adicionarRua(&mapa, casa, escola, 800, "Av. Principal");
    adicionarRua(&mapa, mercado, escola, 400, "Rua do Comércio");
    adicionarRua(&mapa, mercado, parque, 600, "Rua Verde");
    adicionarRua(&mapa, escola, hospital, 700, "Av. da Saúde");
    adicionarRua(&mapa, parque, hospital, 500, "Rua do Parque");
    adicionarRua(&mapa, parque, shopping, 900, "Av. Shopping");
    adicionarRua(&mapa, hospital, shopping, 400, "Rua Central");
    adicionarRua(&mapa, hospital, trabalho, 1000, "Av. do Trabalho");
    adicionarRua(&mapa, shopping, trabalho, 600, "Rua Comercial");
    
    printf("✓ Mapa construído com sucesso!\n");
    
    // Calcular menor caminho: Casa -> Trabalho
    int distancias[MAX_VERTICES];
    int anteriores[MAX_VERTICES];
    
    dijkstra(&mapa, casa, trabalho, distancias, anteriores);
    imprimirCaminho(&mapa, casa, trabalho, anteriores, distancias);
    
    // Outro exemplo: Casa -> Shopping
    printf("\n\n" "═════════════════════════════════════════\n\n");
    
    dijkstra(&mapa, casa, shopping, distancias, anteriores);
    imprimirCaminho(&mapa, casa, shopping, anteriores, distancias);
    
    // Liberar memória
    for (int i = 0; i < mapa.numVertices; i++) {
        Aresta *aresta = mapa.adjacencias[i];
        while (aresta != NULL) {
            Aresta *temp = aresta;
            aresta = aresta->proxima;
            free(temp);
        }
    }
    
    return 0;
}
```

## 📊 Análise de Complexidade

| Algoritmo | Complexidade | Uso | Vantagens | Desvantagens |
|-----------|--------------|-----|-----------|--------------|
| **BFS** | O(V + E) | Menor nº arestas | Simples | Não considera pesos |
| **Dijkstra** | O((V+E) log V)* | Menor caminho pesos ≥ 0 | Eficiente | Não funciona com pesos negativos |
| **Bellman-Ford** | O(V·E) | Pesos negativos | Detecta ciclos negativos | Mais lento |
| **A*** | O(E) | Heurística | Mais rápido que Dijkstra | Precisa heurística |

*Com Min-Heap

## 🎯 Conceitos de Grafos Aplicados

- ✅ **Lista de adjacência** - Eficiente para grafos esparsos
- ✅ **Dijkstra com Min-Heap** - O((V+E) log V)
- ✅ **Relaxamento de arestas** - Atualiza distâncias
- ✅ **Reconstrução de caminho** - Array de anteriores
- ✅ **Grafo não-direcionado** - Ruas bidirecionais
- ✅ **Pesos nas arestas** - Distâncias reais

## 💡 Aplicações Reais de Grafos

| Problema | Algoritmo | Uso |
|----------|-----------|-----|
| GPS/Navegação | Dijkstra, A* | Menor caminho |
| Redes sociais | BFS, DFS | Amigos em comum, sugestões |
| Internet/Roteamento | Dijkstra, Bellman-Ford | Roteamento de pacotes |
| Jogos | A*, Dijkstra | Pathfinding de NPCs |
| Redes de distribuição | MST (Prim/Kruskal) | Minimizar cabeamento |
| Detecção de ciclos | DFS | Deadlock detection |

## 📝 Como Compilar e Executar

```bash
# Compilar
gcc PROBLEMA_PRATICO.c -o gps -Wall

# Executar
./gps
```

## 📚 Lições Aprendidas

1. **Lista > Matriz** - Para grafos esparsos (poucas conexões)
2. **Heap otimiza Dijkstra** - De O(V²) para O((V+E) log V)
3. **Relaxamento é chave** - Sempre busca caminho melhor
4. **Reconstruir caminho** - Array de anteriores é essencial
5. **Early exit** - Pode parar ao alcançar destino
6. **Grafo bidirecional** - Ruas de mão dupla = 2 arestas

## 🔍 Otimizações Possíveis

1. **A* (A-star)** - Usa heurística (distância euclidiana) para ser mais rápido
2. **Grafo direcionado** - Ruas de mão única
3. **Pesos dinâmicos** - Considerar trânsito em tempo real
4. **K menores caminhos** - Rotas alternativas
5. **Restrições** - Evitar pedágios, preferir rodovias
6. **Bidirecional Dijkstra** - Busca dos dois lados simultaneamente
