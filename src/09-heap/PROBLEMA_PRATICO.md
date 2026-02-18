# Problema Prático: Sistema de Priorização de Tarefas (To-Do List)

## 📋 Descrição do Problema

Um aplicativo de gerenciamento de tarefas precisa:
- Adicionar tarefas com diferentes prioridades
- Sempre processar a tarefa de maior prioridade primeiro
- Atualizar prioridades dinamicamente
- Mostrar top N tarefas mais prioritárias
- Remover tarefas concluídas

**Por que usar Heap (Fila de Prioridade)?**
- Inserção O(log n)
- Extração do máximo O(log n)
- Visualizar máximo O(1)
- Estrutura ideal para priorização
- Heap binário usa array (eficiente em memória)

## 🔴 Problema: Array Não Ordenado com Busca Linear

```c
#include <stdio.h>
#include <string.h>

#define MAX_TAREFAS 100

typedef struct {
    int id;
    char descricao[100];
    int prioridade;  // 1=baixa, 10=alta
} Tarefa;

Tarefa tarefas[MAX_TAREFAS];
int total = 0;

// PROBLEMA: Inserção O(1) mas busca de máximo O(n)
void adicionar(Tarefa t) {
    if (total < MAX_TAREFAS) {
        tarefas[total++] = t;
    }
}

// PROBLEMA: Precisa percorrer todo array - O(n)!
Tarefa obterMaiorPrioridade() {
    int maxIdx = 0;
    for (int i = 1; i < total; i++) {
        if (tarefas[i].prioridade > tarefas[maxIdx].prioridade) {
            maxIdx = i;
        }
    }
    return tarefas[maxIdx];
}

// PROBLEMA: Remoção também O(n)
void remover(int id) {
    for (int i = 0; i < total; i++) {
        if (tarefas[i].id == id) {
            // Desloca elementos - O(n)
            for (int j = i; j < total - 1; j++) {
                tarefas[j] = tarefas[j+1];
            }
            total--;
            break;
        }
    }
}

int main() {
    Tarefa t1 = {1, "Comprar leite", 3};
    Tarefa t2 = {2, "Reunião urgente", 10};
    
    adicionar(t1);
    adicionar(t2);
    
    // Sempre O(n) para encontrar maior prioridade
    Tarefa proxima = obterMaiorPrioridade();
    
    return 0;
}
```

### Problemas Identificados:
1. ❌ Obter máximo sempre O(n)
2. ❌ Ineficiente para muitas tarefas
3. ❌ Remoção desloca array
4. ❌ Não aproveita estrutura de heap

## ✅ Solução: Max-Heap (Fila de Prioridade)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_TAREFAS 100

// ============= ESTRUTURAS =============

typedef enum {
    BAIXA = 1,
    MEDIA = 5,
    ALTA = 8,
    URGENTE = 10
} NivelPrioridade;

typedef struct {
    int id;
    char descricao[200];
    char categoria[50];
    int prioridade;
    time_t dataCriacao;
    time_t prazo;
} Tarefa;

// Max-Heap de tarefas
typedef struct {
    Tarefa tarefas[MAX_TAREFAS];
    int tamanho;
    int proximoId;
} HeapTarefas;

// ============= FUNÇÕES AUXILIARES =============

void formatarData(time_t tempo, char *buffer) {
    struct tm *info = localtime(&tempo);
    strftime(buffer, 80, "%d/%m/%Y %H:%M", info);
}

const char* nomePrioridade(int prioridade) {
    if (prioridade >= URGENTE) return "🔴 URGENTE";
    if (prioridade >= ALTA) return "🟠 ALTA";
    if (prioridade >= MEDIA) return "🟡 MÉDIA";
    return "🟢 BAIXA";
}

// ============= OPERAÇÕES DO MAX-HEAP =============

void inicializarHeap(HeapTarefas *heap) {
    heap->tamanho = 0;
    heap->proximoId = 1;
}

// Retorna índice do pai
int pai(int i) {
    return (i - 1) / 2;
}

// Retorna índice do filho esquerdo
int filhoEsquerdo(int i) {
    return 2 * i + 1;
}

// Retorna índice do filho direito
int filhoDireito(int i) {
    return 2 * i + 2;
}

// Troca duas tarefas
void trocar(Tarefa *a, Tarefa *b) {
    Tarefa temp = *a;
    *a = *b;
    *b = temp;
}

// Comparador: maior prioridade, depois menor prazo (mais urgente)
bool temMaiorPrioridade(Tarefa *a, Tarefa *b) {
    if (a->prioridade != b->prioridade) {
        return a->prioridade > b->prioridade;
    }
    // Desempate: prazo mais próximo
    return a->prazo < b->prazo;
}

// Heapify para cima (após inserção) - O(log n)
void heapifyUp(HeapTarefas *heap, int idx) {
    if (idx == 0) return;
    
    int p = pai(idx);
    
    if (temMaiorPrioridade(&heap->tarefas[idx], &heap->tarefas[p])) {
        trocar(&heap->tarefas[idx], &heap->tarefas[p]);
        heapifyUp(heap, p);
    }
}

// Heapify para baixo (após remoção) - O(log n)
void heapifyDown(HeapTarefas *heap, int idx) {
    int maior = idx;
    int esq = filhoEsquerdo(idx);
    int dir = filhoDireito(idx);
    
    if (esq < heap->tamanho && 
        temMaiorPrioridade(&heap->tarefas[esq], &heap->tarefas[maior])) {
        maior = esq;
    }
    
    if (dir < heap->tamanho && 
        temMaiorPrioridade(&heap->tarefas[dir], &heap->tarefas[maior])) {
        maior = dir;
    }
    
    if (maior != idx) {
        trocar(&heap->tarefas[idx], &heap->tarefas[maior]);
        heapifyDown(heap, maior);
    }
}

// Inserir tarefa - O(log n)
bool inserir(HeapTarefas *heap, const char *descricao, const char *categoria, 
             int prioridade, int diasPrazo) {
    if (heap->tamanho >= MAX_TAREFAS) {
        printf("⚠️  Heap cheio!\n");
        return false;
    }
    
    Tarefa novaTarefa;
    novaTarefa.id = heap->proximoId++;
    strcpy(novaTarefa.descricao, descricao);
    strcpy(novaTarefa.categoria, categoria);
    novaTarefa.prioridade = prioridade;
    novaTarefa.dataCriacao = time(NULL);
    novaTarefa.prazo = time(NULL) + (diasPrazo * 24 * 3600);
    
    // Inserir no final do array
    heap->tarefas[heap->tamanho] = novaTarefa;
    heap->tamanho++;
    
    // Restaurar propriedade do heap
    heapifyUp(heap, heap->tamanho - 1);
    
    printf("✓ Tarefa #%d adicionada: '%s' [%s]\n", 
           novaTarefa.id, descricao, nomePrioridade(prioridade));
    
    return true;
}

// Extrair tarefa de maior prioridade - O(log n)
bool extrairMaximo(HeapTarefas *heap, Tarefa *tarefa) {
    if (heap->tamanho == 0) {
        printf("⚠️  Não há tarefas!\n");
        return false;
    }
    
    // Tarefa no topo é a de maior prioridade
    *tarefa = heap->tarefas[0];
    
    // Mover última tarefa para o topo
    heap->tarefas[0] = heap->tarefas[heap->tamanho - 1];
    heap->tamanho--;
    
    // Restaurar propriedade do heap
    if (heap->tamanho > 0) {
        heapifyDown(heap, 0);
    }
    
    return true;
}

// Ver tarefa de maior prioridade sem remover - O(1)
Tarefa* verMaximo(HeapTarefas *heap) {
    if (heap->tamanho == 0) {
        return NULL;
    }
    return &heap->tarefas[0];
}

// Aumentar prioridade de uma tarefa - O(n) busca + O(log n) heapify
bool aumentarPrioridade(HeapTarefas *heap, int id, int novaPrioridade) {
    // Buscar tarefa pelo ID
    int idx = -1;
    for (int i = 0; i < heap->tamanho; i++) {
        if (heap->tarefas[i].id == id) {
            idx = i;
            break;
        }
    }
    
    if (idx == -1) {
        printf("⚠️  Tarefa #%d não encontrada\n", id);
        return false;
    }
    
    if (novaPrioridade <= heap->tarefas[idx].prioridade) {
        printf("⚠️  Nova prioridade deve ser maior\n");
        return false;
    }
    
    heap->tarefas[idx].prioridade = novaPrioridade;
    heapifyUp(heap, idx);
    
    printf("✓ Prioridade da tarefa #%d aumentada para %d [%s]\n", 
           id, novaPrioridade, nomePrioridade(novaPrioridade));
    
    return true;
}

// Listar top N tarefas
void listarTopN(HeapTarefas *heap, int n) {
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║     TOP %d TAREFAS PRIORITÁRIAS        \n", n);
    printf("╚════════════════════════════════════════╝\n\n");
    
    if (heap->tamanho == 0) {
        printf("  (nenhuma tarefa)\n");
        return;
    }
    
    // Criar heap temporário para não alterar o original
    HeapTarefas tempHeap = *heap;
    
    int count = (n < tempHeap.tamanho) ? n : tempHeap.tamanho;
    
    for (int i = 0; i < count; i++) {
        Tarefa t;
        extrairMaximo(&tempHeap, &t);
        
        char dataPrazo[80];
        formatarData(t.prazo, dataPrazo);
        
        printf("%d. %s #%d\n", i + 1, nomePrioridade(t.prioridade), t.id);
        printf("   📝 %s\n", t.descricao);
        printf("   🏷️  %s\n", t.categoria);
        printf("   ⏰ Prazo: %s\n\n", dataPrazo);
    }
}

// Processar próxima tarefa (remover e executar)
void processarProxima(HeapTarefas *heap) {
    Tarefa tarefa;
    
    if (extrairMaximo(heap, &tarefa)) {
        printf("\n✅ PROCESSANDO TAREFA:\n");
        printf("   ID: #%d\n", tarefa.id);
        printf("   Descrição: %s\n", tarefa.descricao);
        printf("   Categoria: %s\n", tarefa.categoria);
        printf("   Prioridade: %s\n", nomePrioridade(tarefa.prioridade));
        
        char dataPrazo[80];
        formatarData(tarefa.prazo, dataPrazo);
        printf("   Prazo: %s\n", dataPrazo);
        
        printf("\n   ✓ Tarefa concluída!\n");
    }
}

// Exibir estatísticas
void exibirEstatisticas(HeapTarefas *heap) {
    if (heap->tamanho == 0) {
        printf("\n📊 Nenhuma tarefa pendente\n");
        return;
    }
    
    int urgentes = 0, altas = 0, medias = 0, baixas = 0;
    
    for (int i = 0; i < heap->tamanho; i++) {
        int p = heap->tarefas[i].prioridade;
        if (p >= URGENTE) urgentes++;
        else if (p >= ALTA) altas++;
        else if (p >= MEDIA) medias++;
        else baixas++;
    }
    
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║        ESTATÍSTICAS                    ║\n");
    printf("╚════════════════════════════════════════╝\n");
    printf("  📊 Total de tarefas: %d\n\n", heap->tamanho);
    printf("  🔴 Urgentes: %d\n", urgentes);
    printf("  🟠 Altas: %d\n", altas);
    printf("  🟡 Médias: %d\n", medias);
    printf("  🟢 Baixas: %d\n", baixas);
}

// ============= MAIN =============

int main() {
    HeapTarefas todoList;
    inicializarHeap(&todoList);
    
    printf("╔════════════════════════════════════════╗\n");
    printf("║   SISTEMA DE GERENCIAMENTO DE TAREFAS ║\n");
    printf("║        Usando MAX-HEAP                 ║\n");
    printf("╚════════════════════════════════════════╝\n\n");
    
    // Adicionar tarefas
    printf("=== ADICIONANDO TAREFAS ===\n\n");
    
    inserir(&todoList, "Preparar apresentação", "Trabalho", URGENTE, 1);
    inserir(&todoList, "Comprar presente aniversário", "Pessoal", ALTA, 3);
    inserir(&todoList, "Revisar código do projeto", "Trabalho", ALTA, 2);
    inserir(&todoList, "Pagar conta de luz", "Financeiro", MEDIA, 5);
    inserir(&todoList, "Estudar para certificação", "Educação", MEDIA, 7);
    inserir(&todoList, "Ligar para dentista", "Saúde", BAIXA, 10);
    inserir(&todoList, "Organizar armário", "Casa", BAIXA, 15);
    inserir(&todoList, "Responder email cliente", "Trabalho", URGENTE, 1);
    
    exibirEstatisticas(&todoList);
    
    // Ver próxima tarefa sem remover
    printf("\n=== PRÓXIMA TAREFA ===\n");
    Tarefa *proxima = verMaximo(&todoList);
    if (proxima) {
        printf("🎯 Próxima: #%d - %s [%s]\n", 
               proxima->id, proxima->descricao, nomePrioridade(proxima->prioridade));
    }
    
    // Listar top 3
    listarTopN(&todoList, 3);
    
    // Processar tarefas
    printf("\n=== PROCESSANDO TAREFAS ===\n");
    processarProxima(&todoList);
    processarProxima(&todoList);
    
    // Aumentar prioridade
    printf("\n\n=== AUMENTANDO PRIORIDADE ===\n");
    aumentarPrioridade(&todoList, 4, URGENTE);
    
    // Listar top 3 atualizado
    listarTopN(&todoList, 3);
    
    // Processar mais tarefas
    printf("=== PROCESSANDO MAIS TAREFAS ===\n");
    processarProxima(&todoList);
    processarProxima(&todoList);
    
    exibirEstatisticas(&todoList);
    
    printf("\n✓ Sistema de tarefas finalizado\n");
    
    return 0;
}
```

## 📊 Análise de Complexidade

| Operação | Array Não Ordenado | Array Ordenado | Max-Heap |
|----------|-------------------|----------------|----------|
| Inserir | O(1) | O(n) | **O(log n)** ✅ |
| Extrair máximo | O(n) | O(1)* | **O(log n)** ✅ |
| Ver máximo | O(n) | O(1) | **O(1)** ✅ |
| Aumentar prioridade | O(1)** | O(n) | **O(log n)*** ✅ |
| Construir heap | - | - | **O(n)** ✅ |

*Precisa reorganizar após remoção  
**Mas busca de máximo é O(n)  
***Após encontrar elemento (busca O(n))

## 🎯 Conceitos de Heap Aplicados

- ✅ **Propriedade do Max-Heap** - Pai ≥ Filhos
- ✅ **Array como estrutura** - Eficiente em memória
- ✅ **Heapify Up/Down** - Restaura propriedade
- ✅ **Extração O(log n)** - Sempre pega o maior
- ✅ **Índices calculados** - pai(i), esquerda(i), direita(i)
- ✅ **Comparador customizado** - Prioridade + prazo

## 💡 Aplicações de Heap

| Problema | Tipo de Heap | Por quê? |
|----------|--------------|----------|
| Fila de prioridade | Max/Min Heap | Acesso O(1) ao maior/menor |
| Heap Sort | Max Heap | Ordenação O(n log n) |
| K maiores elementos | Min Heap tamanho K | Manter top K |
| Dijkstra | Min Heap | Vértice com menor distância |
| Sistema de tarefas | Max Heap | Maior prioridade primeiro |
| Mediana em stream | 2 Heaps | Max para metade menor, Min para maior |

## 📝 Como Compilar e Executar

```bash
# Compilar
gcc PROBLEMA_PRATICO.c -o tarefas -Wall

# Executar
./tarefas
```

## 📚 Lições Aprendidas

1. **Heap ≠ Binary Search Tree** - Não tem ordenação total
2. **Array é suficiente** - Não precisa ponteiros
3. **Cálculo de índices** - Pai: (i-1)/2, Filhos: 2i+1, 2i+2
4. **Heapify é chave** - Restaura propriedade após mudanças
5. **Peek O(1)** - Raiz sempre tem extremo (max ou min)
6. **Não é para busca** - Busca de elemento arbitrário é O(n)

## 🔍 Variações e Otimizações

1. **Min-Heap** - Para menor prioridade primeiro
2. **D-ary Heap** - Mais de 2 filhos por nó
3. **Fibonacci Heap** - Decrease-key O(1) amortizado
4. **Pairing Heap** - Alternativa mais simples ao Fibonacci
5. **Indexed Heap** - Hash map para busca O(1) de elementos
6. **Build-Heap** - Construir heap em O(n) (vs O(n log n) inserções)
