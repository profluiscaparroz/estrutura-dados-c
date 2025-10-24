# Sistema de Gerenciamento de Pedidos de Restaurante
## Documento de Requisitos Completo

---

## 1. SOLICITAÇÃO DA ANALISTA DE NEGÓCIO

### 1.1 Contexto do Negócio
**De:** Maria Silva - Analista de Negócio  
**Para:** Equipe de Arquitetura e Desenvolvimento  
**Data:** 24 de Outubro de 2025  
**Assunto:** Necessidade de Sistema de Gerenciamento de Pedidos

#### Problema Identificado
Nosso restaurante "Sabor da Casa" está enfrentando sérios problemas operacionais:

1. **Perda de Pedidos**: Garçons anotam pedidos em papel, que frequentemente se perdem ou ficam ilegíveis
2. **Desorganização na Cozinha**: Pedidos chegam sem ordem de prioridade, causando atrasos
3. **Falta de Controle**: Não há como saber quais pedidos estão prontos, em preparo ou aguardando
4. **Erros de Cobrança**: Dificuldade em calcular o total dos pedidos corretamente
5. **Impossibilidade de Cancelamento**: Quando um cliente quer cancelar, é difícil desfazer o pedido

#### Necessidades do Negócio
- **Velocidade**: Sistema deve ser rápido para não atrasar o atendimento
- **Confiabilidade**: Nenhum pedido pode ser perdido
- **Rastreabilidade**: Saber o status de cada pedido em tempo real
- **Flexibilidade**: Permitir modificações e cancelamentos
- **Simplicidade**: Interface fácil para garçons e cozinheiros

#### Requisitos Funcionais Identificados

**RF01 - Cadastro de Itens do Menu**
- Sistema deve permitir cadastrar pratos com: código, nome, categoria, preço e tempo de preparo
- Deve suportar pelo menos 50 itens diferentes no menu

**RF02 - Realização de Pedidos**
- Garçom deve conseguir criar um novo pedido informando: mesa, itens e quantidades
- Sistema deve calcular automaticamente o total do pedido
- Cada pedido deve ter um número único de identificação

**RF03 - Fila de Preparo**
- Pedidos devem entrar em uma fila automática para a cozinha
- Cozinha processa pedidos na ordem de chegada (FIFO)
- Sistema deve mostrar qual pedido está sendo preparado

**RF04 - Priorização de Pedidos**
- Pedidos urgentes (crianças, idosos, clientes VIP) devem ter prioridade
- Sistema deve permitir reordenar pedidos por urgência

**RF05 - Busca de Itens**
- Sistema deve permitir busca rápida de itens do menu por nome ou código
- Busca deve funcionar mesmo com menu grande

**RF06 - Histórico e Cancelamento (Undo)**
- Sistema deve manter histórico das últimas 10 ações
- Deve permitir desfazer (undo) ações como adicionar ou remover itens

**RF07 - Relatórios**
- Listar todos os pedidos em aberto
- Mostrar pedidos ordenados por tempo de espera
- Exibir total de vendas do dia

#### Métricas de Sucesso
- Reduzir tempo médio de atendimento em 30%
- Eliminar 100% dos erros de pedidos perdidos
- Reduzir erros de cobrança em 90%

---

## 2. ANÁLISE DO ARQUITETO DE SOFTWARE

### 2.1 Visão Arquitetural
**De:** João Santos - Arquiteto de Software  
**Para:** Equipe de Desenvolvimento  
**Assunto:** Arquitetura do Sistema de Pedidos

#### Decisões Arquiteturais

**DA01 - Linguagem e Paradigma**
- **Decisão**: Implementar em C puro, programação procedural
- **Justificativa**: 
  - Performance crítica (tempo de resposta < 100ms)
  - Ambiente embarcado (terminal de pedidos com recursos limitados)
  - Controle preciso de memória
  - Requisito acadêmico: demonstrar estruturas de dados fundamentais

**DA02 - Estruturas de Dados a Utilizar**

**2.1 VETORES (Arrays)**
- **Uso**: Armazenar menu de itens e lista de pedidos
- **Justificativa**: 
  - Acesso O(1) por índice
  - Menu tem tamanho relativamente fixo
  - Melhor localidade de cache
- **Implementação**: Array estático com capacidade máxima definida

**2.2 ALGORITMOS DE ORDENAÇÃO**
- **Uso**: Ordenar pedidos por prioridade, tempo de espera, ou valor
- **Algoritmos a implementar**:
  - **Quick Sort**: Para ordenação geral (O(n log n) médio)
  - **Insertion Sort**: Para listas pequenas ou quase ordenadas (O(n²) pior caso, mas O(n) melhor caso)
- **Justificativa**: 
  - Quick Sort é eficiente para conjuntos maiores
  - Insertion Sort é adaptativo e eficiente para pequenas quantidades

**2.3 ALGORITMOS DE BUSCA**
- **Uso**: Buscar itens do menu por código ou nome
- **Algoritmos a implementar**:
  - **Busca Linear**: Para busca por nome (array não ordenado)
  - **Busca Binária**: Para busca por código (array ordenado por código)
- **Justificativa**: 
  - Menu ordenado por código permite busca O(log n)
  - Busca por nome requer busca linear O(n) mas com dataset pequeno

**2.4 PILHA (Stack)**
- **Uso**: Implementar sistema de Undo (desfazer ações)
- **Operações**: Push (empilhar), Pop (desempilhar), Peek (topo)
- **Justificativa**: 
  - LIFO perfeito para histórico de ações
  - Última ação é primeira a ser desfeita
  - Memória limitada (últimas 10 ações)

**2.5 FILA (Queue)**
- **Uso**: Gerenciar fila de pedidos na cozinha
- **Operações**: Enqueue (enfileirar), Dequeue (desenfileirar), Front (início)
- **Justificativa**: 
  - FIFO garante ordem justa de atendimento
  - Primeiro pedido a entrar é primeiro a ser preparado
  - Operações O(1)

#### Diagrama de Componentes

```
┌─────────────────────────────────────────────────────────────┐
│                    SISTEMA DE PEDIDOS                        │
├─────────────────────────────────────────────────────────────┤
│                                                               │
│  ┌─────────────────┐         ┌──────────────────┐          │
│  │  MENU (Vetor)   │────────▶│ Busca Linear     │          │
│  │  - Item[]       │         │ Busca Binária    │          │
│  │  - Códigos      │         └──────────────────┘          │
│  │  - Preços       │                                         │
│  └─────────────────┘                                         │
│           │                                                   │
│           ▼                                                   │
│  ┌─────────────────┐         ┌──────────────────┐          │
│  │ PEDIDOS (Vetor) │────────▶│ Quick Sort       │          │
│  │  - Pedido[]     │         │ Insertion Sort   │          │
│  │  - Prioridades  │         │ (por prioridade) │          │
│  └─────────────────┘         └──────────────────┘          │
│           │                                                   │
│           ▼                                                   │
│  ┌─────────────────┐                                         │
│  │ FILA COZINHA    │  ◀─── FIFO (First In, First Out)      │
│  │  - Queue        │                                         │
│  │  - Pedidos      │                                         │
│  └─────────────────┘                                         │
│           │                                                   │
│           ▼                                                   │
│  ┌─────────────────┐                                         │
│  │ PILHA HISTÓRICO │  ◀─── LIFO (Last In, First Out)       │
│  │  - Stack        │                                         │
│  │  - Ações        │                                         │
│  └─────────────────┘                                         │
│                                                               │
└─────────────────────────────────────────────────────────────┘
```

#### Requisitos Não-Funcionais

**RNF01 - Performance**
- Busca de item: < 10ms
- Adicionar pedido: < 50ms
- Ordenar pedidos: < 100ms (até 100 pedidos)

**RNF02 - Confiabilidade**
- Sistema não deve perder pedidos
- Validação de todos os inputs
- Tratamento de erros de memória

**RNF03 - Usabilidade**
- Menu interativo via terminal
- Mensagens claras e informativas
- Feedback imediato de operações

**RNF04 - Manutenibilidade**
- Código bem comentado
- Funções pequenas e focadas (< 50 linhas)
- Nomenclatura descritiva em português

---

## 3. ESPECIFICAÇÃO DO ENGENHEIRO DE SOFTWARE

### 3.1 Especificação Técnica Detalhada
**De:** Pedro Oliveira - Engenheiro de Software  
**Para:** Equipe de Desenvolvimento  
**Assunto:** Especificação de Implementação

#### Estruturas de Dados Definidas

```c
// ============================================
// ESTRUTURA 1: Item do Menu
// ============================================
typedef struct {
    int codigo;              // Identificador único (1-9999)
    char nome[50];           // Nome do prato (ex: "Feijoada Completa")
    char categoria[20];      // Categoria (entrada, prato, bebida, sobremesa)
    float preco;             // Preço em reais (ex: 35.90)
    int tempoPreparo;        // Tempo de preparo em minutos (ex: 25)
} ItemMenu;

// ============================================
// ESTRUTURA 2: Item de um Pedido
// ============================================
typedef struct {
    int codigoItem;          // Referência ao item do menu
    int quantidade;          // Quantidade pedida (ex: 2)
    char observacao[100];    // Observações (ex: "sem cebola")
} ItemPedido;

// ============================================
// ESTRUTURA 3: Pedido Completo
// ============================================
typedef struct {
    int numeroPedido;        // Número único do pedido
    int mesa;                // Número da mesa (1-50)
    ItemPedido itens[20];    // Array de itens pedidos (máx 20)
    int quantidadeItens;     // Quantidade de itens no pedido
    float valorTotal;        // Valor total calculado
    int prioridade;          // Prioridade (1=baixa, 2=normal, 3=alta, 4=urgente)
    time_t horaPedido;       // Timestamp do pedido
    int status;              // 0=aguardando, 1=preparando, 2=pronto, 3=entregue
} Pedido;

// ============================================
// ESTRUTURA 4: Nó da Fila
// ============================================
typedef struct NoFila {
    Pedido pedido;           // Pedido armazenado no nó
    struct NoFila* proximo;  // Ponteiro para próximo nó
} NoFila;

// ============================================
// ESTRUTURA 5: Fila de Pedidos
// ============================================
typedef struct {
    NoFila* inicio;          // Ponteiro para início da fila
    NoFila* fim;             // Ponteiro para fim da fila
    int tamanho;             // Quantidade de pedidos na fila
} FilaPedidos;

// ============================================
// ESTRUTURA 6: Ação (para histórico/undo)
// ============================================
typedef struct {
    char descricao[100];     // Descrição da ação
    int tipoDado;            // Tipo: 1=pedido, 2=item
    void* dados;             // Ponteiro para dados salvos
} Acao;

// ============================================
// ESTRUTURA 7: Pilha de Histórico
// ============================================
typedef struct {
    Acao acoes[10];          // Array de ações (máx 10)
    int topo;                // Índice do topo da pilha (-1 = vazia)
} PilhaHistorico;
```

#### Funções Principais a Implementar

**MÓDULO 1: Gerenciamento de Menu (Vetores + Busca)**
```c
void inicializarMenu(ItemMenu menu[], int* tamanho);
void adicionarItemMenu(ItemMenu menu[], int* tamanho, ItemMenu item);
ItemMenu* buscarItemPorCodigo(ItemMenu menu[], int tamanho, int codigo);     // Busca Binária O(log n)
ItemMenu* buscarItemPorNome(ItemMenu menu[], int tamanho, char* nome);       // Busca Linear O(n)
void exibirMenu(ItemMenu menu[], int tamanho);
```

**MÓDULO 2: Gerenciamento de Pedidos (Vetores + Ordenação)**
```c
void criarPedido(Pedido* pedido, int numero, int mesa);
void adicionarItemAoPedido(Pedido* pedido, ItemPedido item);
float calcularTotalPedido(Pedido* pedido, ItemMenu menu[], int tamanhoMenu);
void exibirPedido(Pedido* pedido, ItemMenu menu[], int tamanhoMenu);

// Ordenação de pedidos
void ordenarPedidosPorPrioridade(Pedido pedidos[], int n);      // Quick Sort
void ordenarPedidosPorTempo(Pedido pedidos[], int n);           // Quick Sort
void ordenarPedidosPorValor(Pedido pedidos[], int n);           // Quick Sort
```

**MÓDULO 3: Fila de Pedidos da Cozinha (Queue)**
```c
FilaPedidos* criarFila();
void enfileirar(FilaPedidos* fila, Pedido pedido);              // O(1)
Pedido desenfileirar(FilaPedidos* fila);                        // O(1)
Pedido* verProximoPedido(FilaPedidos* fila);                    // O(1)
int filaVazia(FilaPedidos* fila);
void exibirFila(FilaPedidos* fila, ItemMenu menu[], int tamanhoMenu);
void liberarFila(FilaPedidos* fila);
```

**MÓDULO 4: Histórico com Undo (Stack)**
```c
void inicializarPilha(PilhaHistorico* pilha);
void empilharAcao(PilhaHistorico* pilha, Acao acao);            // O(1)
Acao desempilharAcao(PilhaHistorico* pilha);                    // O(1)
int pilhaVazia(PilhaHistorico* pilha);
int pilhaCheia(PilhaHistorico* pilha);
void exibirHistorico(PilhaHistorico* pilha);
```

**MÓDULO 5: Interface do Usuário**
```c
void exibirMenuPrincipal();
void gerenciarPedidos();
void gerenciarCozinha();
void exibirRelatorios();
```

#### Complexidade Computacional Esperada

| Operação | Estrutura Usada | Complexidade | Justificativa |
|----------|----------------|--------------|---------------|
| Buscar item por código | Busca Binária | O(log n) | Menu ordenado por código |
| Buscar item por nome | Busca Linear | O(n) | Array não ordenado por nome |
| Adicionar pedido à fila | Fila (Queue) | O(1) | Inserção no fim da fila |
| Processar próximo pedido | Fila (Queue) | O(1) | Remoção do início da fila |
| Desfazer ação | Pilha (Stack) | O(1) | Remoção do topo |
| Salvar ação no histórico | Pilha (Stack) | O(1) | Inserção no topo |
| Ordenar n pedidos | Quick Sort | O(n log n) | Média do Quick Sort |
| Calcular total do pedido | Loop simples | O(m) | m = qtd de itens no pedido |

#### Casos de Teste Obrigatórios

**CT01 - Menu Vazio**
- Tentar buscar item em menu vazio
- Resultado esperado: Mensagem de erro apropriada

**CT02 - Busca Binária**
- Buscar código existente: deve retornar item
- Buscar código inexistente: deve retornar NULL

**CT03 - Fila Vazia**
- Tentar desenfileirar de fila vazia
- Resultado esperado: Mensagem de erro

**CT04 - Pilha Cheia**
- Empilhar 11 ações (limite é 10)
- Resultado esperado: Ação mais antiga é descartada

**CT05 - Ordenação**
- Criar 5 pedidos com prioridades aleatórias
- Ordenar por prioridade
- Verificar ordem correta

**CT06 - Pedido Completo**
- Criar pedido com múltiplos itens
- Calcular total
- Adicionar à fila
- Processar na cozinha

---

## 4. ROADMAP DE IMPLEMENTAÇÃO

### Fase 1: Estruturas Básicas (2 horas)
- [ ] Definir todas as structs
- [ ] Implementar funções de inicialização
- [ ] Criar menu de exemplo com 10 itens

### Fase 2: Vetores e Busca (2 horas)
- [ ] Implementar busca binária por código
- [ ] Implementar busca linear por nome
- [ ] Testes de busca

### Fase 3: Ordenação (2 horas)
- [ ] Implementar Quick Sort para pedidos
- [ ] Implementar Insertion Sort
- [ ] Funções de comparação (prioridade, tempo, valor)

### Fase 4: Fila (1.5 horas)
- [ ] Implementar todas operações de fila
- [ ] Testes de enfileirar/desenfileirar
- [ ] Exibição da fila

### Fase 5: Pilha (1.5 horas)
- [ ] Implementar todas operações de pilha
- [ ] Sistema de undo
- [ ] Exibição do histórico

### Fase 6: Interface e Integração (2 horas)
- [ ] Menu interativo
- [ ] Integração de todos os módulos
- [ ] Testes completos

### Fase 7: Documentação (1 hora)
- [ ] Comentários detalhados em todo código
- [ ] README com exemplos de uso
- [ ] Análise de complexidade de cada função

---

## 5. OBJETIVOS DIDÁTICOS

Este projeto foi projetado para ensinar:

✅ **Vetores**: Armazenamento eficiente e acesso direto  
✅ **Ordenação**: Comparação prática entre algoritmos (Quick Sort vs Insertion Sort)  
✅ **Busca**: Diferença entre busca linear O(n) e binária O(log n)  
✅ **Pilhas**: Conceito LIFO aplicado ao undo  
✅ **Filas**: Conceito FIFO aplicado a sistema real  
✅ **Análise de Complexidade**: Entender impacto prático das escolhas  
✅ **Modularização**: Organização de código em funções coesas  
✅ **Comentários**: Como documentar código de forma profissional  

---

## 6. ENTREGA ESPERADA

### Arquivos a Criar:
1. `sistema_restaurante.c` - Código principal com todas implementações
2. `README.md` - Documentação do projeto
3. `Makefile` - Para compilação
4. `TESTES.md` - Casos de teste e resultados

### Critérios de Aceitação:
✅ Todas as estruturas de dados implementadas corretamente  
✅ Comentários explicativos em TODAS as funções  
✅ Sistema funcional e testado  
✅ Análise de complexidade documentada  
✅ Código compila sem warnings  
✅ Memória gerenciada corretamente (sem leaks)  

---

**Aprovações Necessárias:**
- [ ] Analista de Negócio (requisitos atendidos)
- [ ] Arquiteto de Software (arquitetura seguida)
- [ ] Engenheiro de Software (especificação implementada)
- [ ] Professor (objetivos didáticos alcançados)

---

**Documento aprovado para implementação.**  
**Início: Imediatamente**  
**Prazo: 12 horas de desenvolvimento**
