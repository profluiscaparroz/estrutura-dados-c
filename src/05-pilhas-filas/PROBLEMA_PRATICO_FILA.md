# Problema Prático: Sistema de Atendimento de Call Center

## 📋 Descrição do Problema

Um call center precisa gerenciar atendimento de clientes:
- Clientes chegam e entram em fila de espera
- Atendentes atendem clientes na ordem de chegada (FIFO)
- Sistema de prioridade: clientes VIP têm atendimento prioritário
- Estatísticas: tempo médio de espera, clientes atendidos

**Por que usar Filas (Queue)?**
- FIFO (First In, First Out) - Quem chega primeiro é atendido primeiro
- Enqueue O(1) - Adicionar cliente à fila
- Dequeue O(1) - Atender próximo cliente
- Justiça no atendimento

## 🔴 Problema: Implementação Ineficiente com Array Simples

```c
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_CLIENTES 100

typedef struct {
    int id;
    char nome[50];
    int prioridade;  // 0=normal, 1=VIP
    time_t chegada;
} Cliente;

// PROBLEMA: Usa array linear, dequeue é O(n)
Cliente fila[MAX_CLIENTES];
int tamanho = 0;

void enfileirar(Cliente c) {
    if (tamanho < MAX_CLIENTES) {
        fila[tamanho++] = c;
    }
}

// PROBLEMA: Remove do início deslocando todo array - O(n)!
Cliente desenfileirar() {
    Cliente c = fila[0];
    
    // Desloca todos elementos - MUITO INEFICIENTE
    for (int i = 0; i < tamanho - 1; i++) {
        fila[i] = fila[i + 1];
    }
    tamanho--;
    
    return c;
}

// PROBLEMA: Não considera prioridade
// PROBLEMA: Sem tratamento de fila vazia

int main() {
    Cliente c1 = {1, "João Silva", 0, time(NULL)};
    Cliente c2 = {2, "Maria VIP", 1, time(NULL)};
    
    enfileirar(c1);
    enfileirar(c2);
    
    // Maria deveria ser atendida primeiro (VIP)!
    // Mas será João (ordem de chegada)
    Cliente atendido = desenfileirar();
    printf("Atendendo: %s\n", atendido.nome);
    
    return 0;
}
```

### Problemas Identificados:
1. ❌ Dequeue O(n) - desloca todo array
2. ❌ Não implementa prioridade
3. ❌ Sem fila circular (desperdiça espaço)
4. ❌ Sem validações adequadas
5. ❌ Não calcula tempo de espera

## ✅ Solução: Fila Circular com Sistema de Prioridade

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_CLIENTES 50
#define MAX_ATENDENTES 3

// ============= ESTRUTURAS =============

typedef enum {
    NORMAL = 0,
    VIP = 1
} Prioridade;

typedef struct {
    int id;
    char nome[50];
    char assunto[100];
    Prioridade prioridade;
    time_t horaChegada;
} Cliente;

// Fila Circular
typedef struct {
    Cliente clientes[MAX_CLIENTES];
    int frente;      // Índice do primeiro elemento
    int tras;        // Índice da próxima posição livre
    int tamanho;     // Quantidade de elementos
} Fila;

typedef struct {
    int id;
    char nome[20];
    bool ocupado;
    Cliente *clienteAtual;
    time_t inicioAtendimento;
} Atendente;

typedef struct {
    Fila filaNormal;
    Fila filaVIP;
    Atendente atendentes[MAX_ATENDENTES];
    int totalAtendidos;
    int tempoEsperaTotal;  // Em segundos
} CallCenter;

// ============= OPERAÇÕES DE FILA CIRCULAR =============

void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = 0;
    f->tamanho = 0;
}

bool filaVazia(Fila *f) {
    return f->tamanho == 0;
}

bool filaCheia(Fila *f) {
    return f->tamanho == MAX_CLIENTES;
}

// Enfileirar - O(1)
bool enqueue(Fila *f, Cliente c) {
    if (filaCheia(f)) {
        printf("⚠️  Fila cheia!\n");
        return false;
    }
    
    f->clientes[f->tras] = c;
    f->tras = (f->tras + 1) % MAX_CLIENTES;  // Circular
    f->tamanho++;
    return true;
}

// Desenfileirar - O(1)
bool dequeue(Fila *f, Cliente *c) {
    if (filaVazia(f)) {
        return false;
    }
    
    *c = f->clientes[f->frente];
    f->frente = (f->frente + 1) % MAX_CLIENTES;  // Circular
    f->tamanho--;
    return true;
}

// Ver primeiro da fila sem remover - O(1)
Cliente* peek(Fila *f) {
    if (filaVazia(f)) {
        return NULL;
    }
    return &f->clientes[f->frente];
}

int tamanhoFila(Fila *f) {
    return f->tamanho;
}

// ============= OPERAÇÕES DO CALL CENTER =============

void inicializarCallCenter(CallCenter *cc) {
    inicializarFila(&cc->filaNormal);
    inicializarFila(&cc->filaVIP);
    cc->totalAtendidos = 0;
    cc->tempoEsperaTotal = 0;
    
    // Inicializar atendentes
    char *nomes[] = {"Ana", "Bruno", "Carla"};
    for (int i = 0; i < MAX_ATENDENTES; i++) {
        cc->atendentes[i].id = i + 1;
        strcpy(cc->atendentes[i].nome, nomes[i]);
        cc->atendentes[i].ocupado = false;
        cc->atendentes[i].clienteAtual = NULL;
    }
}

// Adicionar cliente à fila apropriada
void adicionarCliente(CallCenter *cc, Cliente c) {
    c.horaChegada = time(NULL);
    
    if (c.prioridade == VIP) {
        if (enqueue(&cc->filaVIP, c)) {
            printf("✓ Cliente VIP '%s' adicionado à fila prioritária\n", c.nome);
            printf("  Posição na fila VIP: %d\n", tamanhoFila(&cc->filaVIP));
        }
    } else {
        if (enqueue(&cc->filaNormal, c)) {
            printf("✓ Cliente '%s' adicionado à fila\n", c.nome);
            printf("  Posição na fila: %d\n", tamanhoFila(&cc->filaNormal));
        }
    }
}

// Busca atendente disponível
Atendente* buscarAtendenteDisponivel(CallCenter *cc) {
    for (int i = 0; i < MAX_ATENDENTES; i++) {
        if (!cc->atendentes[i].ocupado) {
            return &cc->atendentes[i];
        }
    }
    return NULL;
}

// Atende próximo cliente (VIP tem prioridade)
bool atenderProximoCliente(CallCenter *cc) {
    Atendente *atendente = buscarAtendenteDisponivel(cc);
    
    if (atendente == NULL) {
        printf("⚠️  Todos os atendentes estão ocupados\n");
        return false;
    }
    
    Cliente cliente;
    bool atendido = false;
    
    // Prioridade: Fila VIP primeiro
    if (dequeue(&cc->filaVIP, &cliente)) {
        printf("🌟 Atendendo cliente VIP\n");
        atendido = true;
    } else if (dequeue(&cc->filaNormal, &cliente)) {
        printf("👤 Atendendo cliente normal\n");
        atendido = true;
    }
    
    if (!atendido) {
        printf("ℹ️  Não há clientes na fila\n");
        return false;
    }
    
    // Calcular tempo de espera
    time_t agora = time(NULL);
    int tempoEspera = (int)difftime(agora, cliente.horaChegada);
    
    // Registrar atendimento
    // Nota: A memória alocada aqui deve ser liberada em finalizarAtendimento()
    atendente->ocupado = true;
    atendente->clienteAtual = malloc(sizeof(Cliente));
    if (atendente->clienteAtual == NULL) {
        printf("❌ Erro de memória: não foi possível registrar o atendimento do cliente.\n");
        atendente->ocupado = false;
        return false;
    }
    *atendente->clienteAtual = cliente;
    atendente->inicioAtendimento = agora;
    
    cc->totalAtendidos++;
    cc->tempoEsperaTotal += tempoEspera;
    
    printf("  Atendente: %s (ID: %d)\n", atendente->nome, atendente->id);
    printf("  Cliente: %s (ID: %d)\n", cliente.nome, cliente.id);
    printf("  Assunto: %s\n", cliente.assunto);
    printf("  Tempo de espera: %d segundos\n", tempoEspera);
    
    return true;
}

// Finaliza atendimento
void finalizarAtendimento(CallCenter *cc, int atendenteId) {
    if (atendenteId < 1 || atendenteId > MAX_ATENDENTES) {
        printf("⚠️  Atendente inválido\n");
        return;
    }
    
    Atendente *atendente = &cc->atendentes[atendenteId - 1];
    
    if (!atendente->ocupado) {
        printf("⚠️  Atendente %s não está ocupado\n", atendente->nome);
        return;
    }
    
    time_t agora = time(NULL);
    int duracao = (int)difftime(agora, atendente->inicioAtendimento);
    
    printf("✓ Atendimento finalizado\n");
    printf("  Atendente: %s\n", atendente->nome);
    printf("  Cliente: %s\n", atendente->clienteAtual->nome);
    printf("  Duração: %d segundos\n", duracao);
    
    free(atendente->clienteAtual);
    atendente->clienteAtual = NULL;
    atendente->ocupado = false;
}

// Exibe status do call center
void exibirStatus(CallCenter *cc) {
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║     STATUS DO CALL CENTER              ║\n");
    printf("╚════════════════════════════════════════╝\n");
    
    printf("\n📊 ESTATÍSTICAS:\n");
    printf("  Clientes atendidos: %d\n", cc->totalAtendidos);
    if (cc->totalAtendidos > 0) {
        float tempoMedio = (float)cc->tempoEsperaTotal / cc->totalAtendidos;
        printf("  Tempo médio de espera: %.1f segundos\n", tempoMedio);
    }
    
    printf("\n👥 ATENDENTES:\n");
    for (int i = 0; i < MAX_ATENDENTES; i++) {
        Atendente *a = &cc->atendentes[i];
        if (a->ocupado) {
            printf("  %s (ID %d): 🔴 OCUPADO - Atendendo %s\n",
                   a->nome, a->id, a->clienteAtual->nome);
        } else {
            printf("  %s (ID %d): 🟢 DISPONÍVEL\n", a->nome, a->id);
        }
    }
    
    printf("\n📞 FILAS DE ESPERA:\n");
    printf("  🌟 Fila VIP: %d cliente(s)\n", tamanhoFila(&cc->filaVIP));
    printf("  👤 Fila Normal: %d cliente(s)\n", tamanhoFila(&cc->filaNormal));
    
    if (!filaVazia(&cc->filaVIP)) {
        Cliente *proximo = peek(&cc->filaVIP);
        printf("  → Próximo VIP: %s\n", proximo->nome);
    } else if (!filaVazia(&cc->filaNormal)) {
        Cliente *proximo = peek(&cc->filaNormal);
        printf("  → Próximo: %s\n", proximo->nome);
    }
}

// ============= MAIN =============

int main() {
    CallCenter callCenter;
    inicializarCallCenter(&callCenter);
    
    printf("╔════════════════════════════════════════╗\n");
    printf("║   SISTEMA DE CALL CENTER               ║\n");
    printf("║   Usando FILA CIRCULAR + PRIORIDADE    ║\n");
    printf("╚════════════════════════════════════════╝\n\n");
    
    // Simular chegada de clientes
    printf("=== CLIENTES CHEGANDO ===\n\n");
    
    Cliente c1 = {1, "João Silva", "Dúvida sobre fatura", NORMAL};
    adicionarCliente(&callCenter, c1);
    
    Cliente c2 = {2, "Maria Santos", "Problema urgente", VIP};
    adicionarCliente(&callCenter, c2);
    
    Cliente c3 = {3, "Pedro Costa", "Informação sobre plano", NORMAL};
    adicionarCliente(&callCenter, c3);
    
    Cliente c4 = {4, "Ana Oliveira", "Cancelamento - VIP", VIP};
    adicionarCliente(&callCenter, c4);
    
    Cliente c5 = {5, "Carlos Lima", "Suporte técnico", NORMAL};
    adicionarCliente(&callCenter, c5);
    
    exibirStatus(&callCenter);
    
    // Simular atendimentos
    printf("\n\n=== INICIANDO ATENDIMENTOS ===\n\n");
    
    printf("--- Atendimento 1 ---\n");
    atenderProximoCliente(&callCenter);  // Deve pegar Maria (VIP)
    
    printf("\n--- Atendimento 2 ---\n");
    atenderProximoCliente(&callCenter);  // Deve pegar Ana (VIP)
    
    printf("\n--- Atendimento 3 ---\n");
    atenderProximoCliente(&callCenter);  // Deve pegar João (normal)
    
    printf("\n--- Tentativa 4 (todos ocupados) ---\n");
    atenderProximoCliente(&callCenter);  // Deve falhar
    
    exibirStatus(&callCenter);
    
    // Finalizar alguns atendimentos
    printf("\n\n=== FINALIZANDO ATENDIMENTOS ===\n\n");
    
    finalizarAtendimento(&callCenter, 1);  // Ana finaliza
    finalizarAtendimento(&callCenter, 2);  // Bruno finaliza
    
    exibirStatus(&callCenter);
    
    // Novos atendimentos
    printf("\n\n=== CONTINUANDO ATENDIMENTOS ===\n\n");
    
    atenderProximoCliente(&callCenter);  // Pedro
    atenderProximoCliente(&callCenter);  // Carlos
    
    exibirStatus(&callCenter);
    
    return 0;
}
```

## 📊 Análise de Complexidade

| Operação | Array Linear | Fila Circular | Fila com Prioridade |
|----------|--------------|---------------|---------------------|
| Enqueue | O(1) | O(1) | O(1)* |
| Dequeue | O(n) ❌ | O(1) ✅ | O(1)* |
| Peek | O(1) | O(1) | O(1) |
| Tamanho | O(1) | O(1) | O(1) |

*Com duas filas separadas (VIP e Normal)

## 🎯 Conceitos de Fila Aplicados

- ✅ **FIFO** (First In, First Out)
- ✅ **Fila Circular** - Reutiliza espaço vazio
- ✅ **Enqueue/Dequeue** em O(1)
- ✅ **Sistema de Prioridade** - Duas filas
- ✅ **Peek** - Ver sem remover
- ✅ **Validações** - Fila vazia/cheia

## 💡 Casos de Uso de Filas

| Aplicação | Por que Fila? |
|-----------|---------------|
| Call Center | FIFO - ordem de chegada |
| Impressora | Jobs processados em ordem |
| BFS em Grafos | Exploração em largura |
| Sistema de Mensagens | Processamento assíncrono |
| Cache LRU | Menos recente primeiro |
| Simulação de processos | Escalonamento FIFO |

## 📝 Como Compilar e Executar

```bash
# Compilar
gcc PROBLEMA_PRATICO_FILA.c -o callcenter -Wall

# Executar
./callcenter
```

## 🧪 Exemplo de Saída (parcial)

```
╔════════════════════════════════════════╗
║   SISTEMA DE CALL CENTER               ║
║   Usando FILA CIRCULAR + PRIORIDADE    ║
╚════════════════════════════════════════╝

=== CLIENTES CHEGANDO ===

✓ Cliente 'João Silva' adicionado à fila
  Posição na fila: 1
✓ Cliente VIP 'Maria Santos' adicionado à fila prioritária
  Posição na fila VIP: 1

╔════════════════════════════════════════╗
║     STATUS DO CALL CENTER              ║
╚════════════════════════════════════════╝

📊 ESTATÍSTICAS:
  Clientes atendidos: 0

👥 ATENDENTES:
  Ana (ID 1): 🟢 DISPONÍVEL
  Bruno (ID 2): 🟢 DISPONÍVEL
  Carla (ID 3): 🟢 DISPONÍVEL

📞 FILAS DE ESPERA:
  🌟 Fila VIP: 2 cliente(s)
  👤 Fila Normal: 3 cliente(s)
  → Próximo VIP: Maria Santos

=== INICIANDO ATENDIMENTOS ===

--- Atendimento 1 ---
🌟 Atendendo cliente VIP
  Atendente: Ana (ID: 1)
  Cliente: Maria Santos (ID: 2)
  Assunto: Problema urgente
  Tempo de espera: 0 segundos
```

## 📚 Lições Aprendidas

1. **Fila Circular é eficiente** - Evita deslocamento O(n)
2. **Prioridade com múltiplas filas** - Simples e eficaz
3. **Módulo para circular** - `(index + 1) % MAX` é a chave
4. **Separar frente e trás** - Necessário para fila circular
5. **Validar vazia/cheia** - Previne erros
6. **FIFO para justiça** - Clientes atendidos na ordem certa

## 🔍 Melhorias Possíveis

1. **Heap para prioridades** - Mais níveis de prioridade
2. **Fila dinâmica** - Lista encadeada para tamanho ilimitado
3. **Múltiplas prioridades** - Não apenas VIP/Normal
4. **SLA tracking** - Alertas para espera muito longa
5. **Load balancing** - Distribuir igualmente entre atendentes
6. **Callbacks** - Ligar de volta se espera > X minutos
