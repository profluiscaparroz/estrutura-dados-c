/*
 * ============================================================================
 * SISTEMA DE GERENCIAMENTO DE PEDIDOS DE RESTAURANTE
 * ============================================================================
 * 
 * OBJETIVO DIDÁTICO:
 * Este programa demonstra a aplicação prática de estruturas de dados
 * fundamentais (vetores, pilhas, filas) e algoritmos (ordenação e busca)
 * em um cenário real de um restaurante.
 * 
 * ESTRUTURAS DE DADOS UTILIZADAS:
 * 1. VETORES (Arrays)     - Menu de itens e lista de pedidos
 * 2. BUSCA BINÁRIA        - Buscar itens por código O(log n)
 * 3. BUSCA LINEAR         - Buscar itens por nome O(n)
 * 4. QUICK SORT           - Ordenar pedidos O(n log n)
 * 5. INSERTION SORT       - Ordenar pequenas listas O(n²)
 * 6. FILA (Queue - FIFO)  - Gerenciar pedidos na cozinha
 * 7. PILHA (Stack - LIFO) - Histórico de ações para undo
 * 
 * AUTOR: Sistema Educacional de Estruturas de Dados
 * DATA: Outubro 2025
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ============================================================================
// DEFINIÇÃO DE CONSTANTES
// ============================================================================

#define MAX_MENU 50              // Capacidade máxima do menu
#define MAX_PEDIDOS 100          // Capacidade máxima de pedidos simultâneos
#define MAX_ITENS_PEDIDO 20      // Máximo de itens por pedido
#define MAX_HISTORICO 10         // Tamanho máximo do histórico (pilha)
#define MAX_NOME 50              // Tamanho máximo para nomes
#define MAX_OBSERVACAO 100       // Tamanho máximo para observações

// ============================================================================
// DEFINIÇÃO DAS ESTRUTURAS DE DADOS
// ============================================================================

/*
 * ESTRUTURA: ItemMenu
 * DESCRIÇÃO: Representa um item do cardápio do restaurante
 * USO: Armazenado em um VETOR para acesso rápido O(1) por índice
 */
typedef struct {
    int codigo;                  // Código único do item (usado para busca binária)
    char nome[MAX_NOME];         // Nome do prato
    char categoria[20];          // Categoria: "entrada", "prato", "bebida", "sobremesa"
    float preco;                 // Preço em reais
    int tempoPreparo;            // Tempo de preparo em minutos
} ItemMenu;

/*
 * ESTRUTURA: ItemPedido
 * DESCRIÇÃO: Representa um item dentro de um pedido (com quantidade)
 * USO: Array dentro da estrutura Pedido
 */
typedef struct {
    int codigoItem;              // Referência ao código do item no menu
    int quantidade;              // Quantidade pedida
    char observacao[MAX_OBSERVACAO]; // Observações especiais (ex: "sem cebola")
} ItemPedido;

/*
 * ESTRUTURA: Pedido
 * DESCRIÇÃO: Representa um pedido completo de uma mesa
 * USO: Armazenado em VETOR e manipulado pela FILA
 */
typedef struct {
    int numeroPedido;            // Número único identificador
    int mesa;                    // Número da mesa
    ItemPedido itens[MAX_ITENS_PEDIDO]; // Array de itens pedidos
    int quantidadeItens;         // Contador de itens no pedido
    float valorTotal;            // Valor total calculado
    int prioridade;              // 1=baixa, 2=normal, 3=alta, 4=urgente
    time_t horaPedido;           // Timestamp para calcular tempo de espera
    int status;                  // 0=aguardando, 1=preparando, 2=pronto, 3=entregue
} Pedido;

/*
 * ESTRUTURA: NoFila
 * DESCRIÇÃO: Nó de uma lista encadeada usada para implementar a fila
 * USO: Componente básico da estrutura FilaPedidos (QUEUE)
 * 
 * EXPLICAÇÃO: Uma fila precisa de uma estrutura encadeada para permitir
 * inserção O(1) no fim e remoção O(1) no início
 */
typedef struct NoFila {
    Pedido pedido;               // Dados armazenados no nó
    struct NoFila* proximo;      // Ponteiro para o próximo nó
} NoFila;

/*
 * ESTRUTURA: FilaPedidos (QUEUE - FIFO)
 * DESCRIÇÃO: Implementação de uma fila para gerenciar pedidos na cozinha
 * PRINCÍPIO: FIFO (First In, First Out) - Primeiro a entrar é primeiro a sair
 * 
 * APLICAÇÃO PRÁTICA: Pedidos são processados na ordem de chegada, garantindo
 * justiça no atendimento. O primeiro pedido feito é o primeiro a ser preparado.
 * 
 * COMPLEXIDADE:
 * - Enfileirar (enqueue): O(1)
 * - Desenfileirar (dequeue): O(1)
 * - Ver próximo: O(1)
 */
typedef struct {
    NoFila* inicio;              // Ponteiro para o primeiro nó (onde remove)
    NoFila* fim;                 // Ponteiro para o último nó (onde insere)
    int tamanho;                 // Quantidade de pedidos na fila
} FilaPedidos;

/*
 * ESTRUTURA: Acao
 * DESCRIÇÃO: Representa uma ação que pode ser desfeita (undo)
 * USO: Armazenada na pilha de histórico
 */
typedef struct {
    char descricao[100];         // Descrição da ação realizada
    int numeroPedido;            // Número do pedido afetado
    time_t momento;              // Timestamp da ação
} Acao;

/*
 * ESTRUTURA: PilhaHistorico (STACK - LIFO)
 * DESCRIÇÃO: Implementação de uma pilha para gerenciar histórico de ações
 * PRINCÍPIO: LIFO (Last In, First Out) - Último a entrar é primeiro a sair
 * 
 * APLICAÇÃO PRÁTICA: Ao desfazer ações, queremos desfazer a mais recente
 * primeiro, depois a anterior, e assim por diante. Perfeito para UNDO.
 * 
 * COMPLEXIDADE:
 * - Empilhar (push): O(1)
 * - Desempilhar (pop): O(1)
 * - Ver topo (peek): O(1)
 */
typedef struct {
    Acao acoes[MAX_HISTORICO];   // Array fixo de ações
    int topo;                    // Índice do topo (-1 = pilha vazia)
} PilhaHistorico;

// ============================================================================
// VARIÁVEIS GLOBAIS
// ============================================================================

ItemMenu menu[MAX_MENU];         // VETOR: Menu do restaurante
int tamanhoMenu = 0;             // Contador de itens no menu

Pedido pedidos[MAX_PEDIDOS];     // VETOR: Todos os pedidos
int totalPedidos = 0;            // Contador de pedidos

FilaPedidos* filaCozinha;        // FILA: Pedidos aguardando preparo
PilhaHistorico historico;        // PILHA: Histórico de ações para undo

int proximoNumeroPedido = 1;     // Gerador de número único de pedido

// ============================================================================
// MÓDULO 1: FUNÇÕES AUXILIARES E UTILITÁRIAS
// ============================================================================

/*
 * FUNÇÃO: limparBuffer
 * DESCRIÇÃO: Limpa o buffer de entrada (stdin) para evitar problemas com scanf
 * COMPLEXIDADE: O(1)
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/*
 * FUNÇÃO: pausar
 * DESCRIÇÃO: Pausa a execução aguardando o usuário pressionar Enter
 * COMPLEXIDADE: O(1)
 */
void pausar() {
    printf("\nPressione ENTER para continuar...");
    limparBuffer();
    getchar();
}

/*
 * FUNÇÃO: limparTela
 * DESCRIÇÃO: Limpa a tela do console (multiplataforma)
 * COMPLEXIDADE: O(1)
 */
void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// ============================================================================
// MÓDULO 2: GERENCIAMENTO DO MENU (VETORES + BUSCA)
// ============================================================================

/*
 * FUNÇÃO: inicializarMenu
 * DESCRIÇÃO: Preenche o menu com itens pré-cadastrados para demonstração
 * COMPLEXIDADE: O(n) onde n = número de itens iniciais
 * 
 * OBSERVAÇÃO: Em um sistema real, isso viria de um banco de dados
 */
void inicializarMenu() {
    // Item 1
    menu[0].codigo = 101;
    strcpy(menu[0].nome, "Feijoada Completa");
    strcpy(menu[0].categoria, "prato");
    menu[0].preco = 45.90;
    menu[0].tempoPreparo = 30;
    
    // Item 2
    menu[1].codigo = 102;
    strcpy(menu[1].nome, "Bife à Parmegiana");
    strcpy(menu[1].categoria, "prato");
    menu[1].preco = 38.50;
    menu[1].tempoPreparo = 25;
    
    // Item 3
    menu[2].codigo = 103;
    strcpy(menu[2].nome, "Lasanha Bolonhesa");
    strcpy(menu[2].categoria, "prato");
    menu[2].preco = 32.00;
    menu[2].tempoPreparo = 20;
    
    // Item 4
    menu[3].codigo = 104;
    strcpy(menu[3].nome, "Salmão Grelhado");
    strcpy(menu[3].categoria, "prato");
    menu[3].preco = 52.00;
    menu[3].tempoPreparo = 20;
    
    // Item 5
    menu[4].codigo = 201;
    strcpy(menu[4].nome, "Coxinha de Frango");
    strcpy(menu[4].categoria, "entrada");
    menu[4].preco = 8.50;
    menu[4].tempoPreparo = 10;
    
    // Item 6
    menu[5].codigo = 202;
    strcpy(menu[5].nome, "Bruschetta");
    strcpy(menu[5].categoria, "entrada");
    menu[5].preco = 12.00;
    menu[5].tempoPreparo = 8;
    
    // Item 7
    menu[6].codigo = 301;
    strcpy(menu[6].nome, "Refrigerante Lata");
    strcpy(menu[6].categoria, "bebida");
    menu[6].preco = 6.00;
    menu[6].tempoPreparo = 1;
    
    // Item 8
    menu[7].codigo = 302;
    strcpy(menu[7].nome, "Suco Natural");
    strcpy(menu[7].categoria, "bebida");
    menu[7].preco = 9.00;
    menu[7].tempoPreparo = 5;
    
    // Item 9
    menu[8].codigo = 401;
    strcpy(menu[8].nome, "Pudim de Leite");
    strcpy(menu[8].categoria, "sobremesa");
    menu[8].preco = 12.00;
    menu[8].tempoPreparo = 5;
    
    // Item 10
    menu[9].codigo = 402;
    strcpy(menu[9].nome, "Petit Gateau");
    strcpy(menu[9].categoria, "sobremesa");
    menu[9].preco = 18.00;
    menu[9].tempoPreparo = 12;
    
    tamanhoMenu = 10;
    
    printf("✓ Menu inicializado com %d itens\n", tamanhoMenu);
}

/*
 * FUNÇÃO: buscarItemPorCodigo
 * DESCRIÇÃO: Busca um item no menu usando BUSCA BINÁRIA
 * COMPLEXIDADE: O(log n) - logarítmica
 * 
 * ALGORITMO: Busca Binária
 * PRÉ-CONDIÇÃO: O vetor menu[] DEVE estar ordenado por código
 * 
 * FUNCIONAMENTO:
 * 1. Divide o espaço de busca ao meio a cada iteração
 * 2. Compara o código buscado com o elemento do meio
 * 3. Se igual: encontrou, retorna
 * 4. Se menor: busca na metade esquerda
 * 5. Se maior: busca na metade direita
 * 
 * VANTAGEM: Para um menu com 1000 itens, busca em no máximo 10 comparações!
 */
ItemMenu* buscarItemPorCodigo(int codigo) {
    int esquerda = 0;
    int direita = tamanhoMenu - 1;
    
    // Enquanto houver espaço para buscar
    while (esquerda <= direita) {
        // Calcula o índice do meio
        // Nota: usar (esq + dir) / 2 pode causar overflow em arrays grandes
        int meio = esquerda + (direita - esquerda) / 2;
        
        // Compara o código buscado com o elemento do meio
        if (menu[meio].codigo == codigo) {
            // ✓ Encontrou! Retorna ponteiro para o item
            return &menu[meio];
        }
        
        if (menu[meio].codigo < codigo) {
            // Código buscado é maior: busca na metade direita
            esquerda = meio + 1;
        } else {
            // Código buscado é menor: busca na metade esquerda
            direita = meio - 1;
        }
    }
    
    // Não encontrou
    return NULL;
}

/*
 * FUNÇÃO: buscarItemPorNome
 * DESCRIÇÃO: Busca um item no menu usando BUSCA LINEAR
 * COMPLEXIDADE: O(n) - linear
 * 
 * ALGORITMO: Busca Linear (Sequential Search)
 * 
 * FUNCIONAMENTO:
 * 1. Percorre todo o vetor do início ao fim
 * 2. Compara o nome de cada item com o nome buscado
 * 3. Quando encontrar, retorna
 * 4. Se chegar ao fim sem encontrar, retorna NULL
 * 
 * POR QUE BUSCA LINEAR?
 * - O vetor não está ordenado por nome (só por código)
 * - Busca por substring (strstr) não funciona com busca binária
 * - Para dataset pequeno (< 100 itens), performance é aceitável
 */
ItemMenu* buscarItemPorNome(char* nome) {
    // Percorre todos os itens do menu
    for (int i = 0; i < tamanhoMenu; i++) {
        // strstr retorna != NULL se 'nome' está contido em menu[i].nome
        // Isso permite busca parcial: "fei" encontra "Feijoada"
        if (strstr(menu[i].nome, nome) != NULL) {
            return &menu[i];
        }
    }
    
    // Não encontrou
    return NULL;
}

/*
 * FUNÇÃO: exibirMenu
 * DESCRIÇÃO: Exibe todos os itens do menu formatado
 * COMPLEXIDADE: O(n)
 */
void exibirMenu() {
    printf("\n");
    printf("═══════════════════════════════════════════════════════════════════════\n");
    printf("                         MENU DO RESTAURANTE                            \n");
    printf("═══════════════════════════════════════════════════════════════════════\n");
    printf("%-8s %-30s %-12s %10s %8s\n", "CÓDIGO", "NOME", "CATEGORIA", "PREÇO", "TEMPO");
    printf("───────────────────────────────────────────────────────────────────────\n");
    
    for (int i = 0; i < tamanhoMenu; i++) {
        printf("%-8d %-30s %-12s R$ %7.2f %5d min\n",
               menu[i].codigo,
               menu[i].nome,
               menu[i].categoria,
               menu[i].preco,
               menu[i].tempoPreparo);
    }
    
    printf("═══════════════════════════════════════════════════════════════════════\n");
}

// ============================================================================
// MÓDULO 3: GERENCIAMENTO DE PEDIDOS (VETORES + ORDENAÇÃO)
// ============================================================================

/*
 * FUNÇÃO: criarPedido
 * DESCRIÇÃO: Cria um novo pedido vazio para uma mesa
 * COMPLEXIDADE: O(1)
 */
void criarPedido(Pedido* pedido, int mesa) {
    pedido->numeroPedido = proximoNumeroPedido++;
    pedido->mesa = mesa;
    pedido->quantidadeItens = 0;
    pedido->valorTotal = 0.0;
    pedido->prioridade = 2;  // Normal por padrão
    pedido->horaPedido = time(NULL);  // Timestamp atual
    pedido->status = 0;  // Aguardando
    
    printf("✓ Pedido #%d criado para mesa %d\n", pedido->numeroPedido, mesa);
}

/*
 * FUNÇÃO: adicionarItemAoPedido
 * DESCRIÇÃO: Adiciona um item ao pedido
 * COMPLEXIDADE: O(1)
 */
void adicionarItemAoPedido(Pedido* pedido, int codigoItem, int quantidade, char* observacao) {
    // Validação: verifica se há espaço no pedido
    if (pedido->quantidadeItens >= MAX_ITENS_PEDIDO) {
        printf("✗ ERRO: Pedido já contém o máximo de %d itens\n", MAX_ITENS_PEDIDO);
        return;
    }
    
    // Validação: verifica se o item existe no menu
    ItemMenu* item = buscarItemPorCodigo(codigoItem);
    if (item == NULL) {
        printf("✗ ERRO: Item com código %d não encontrado no menu\n", codigoItem);
        return;
    }
    
    // Adiciona o item ao pedido
    int idx = pedido->quantidadeItens;
    pedido->itens[idx].codigoItem = codigoItem;
    pedido->itens[idx].quantidade = quantidade;
    strcpy(pedido->itens[idx].observacao, observacao);
    
    // Incrementa contador e atualiza valor total
    pedido->quantidadeItens++;
    pedido->valorTotal += item->preco * quantidade;
    
    printf("✓ Adicionado: %dx %s - R$ %.2f\n", 
           quantidade, item->nome, item->preco * quantidade);
}

/*
 * FUNÇÃO: exibirPedido
 * DESCRIÇÃO: Exibe os detalhes de um pedido
 * COMPLEXIDADE: O(m) onde m = quantidade de itens no pedido
 */
void exibirPedido(Pedido* pedido) {
    printf("\n┌─────────────────────────────────────────────────────────────┐\n");
    printf("│ PEDIDO #%-4d | Mesa: %-2d | Prioridade: ", 
           pedido->numeroPedido, pedido->mesa);
    
    // Exibe prioridade com cores
    switch(pedido->prioridade) {
        case 1: printf("BAIXA     │\n"); break;
        case 2: printf("NORMAL    │\n"); break;
        case 3: printf("ALTA      │\n"); break;
        case 4: printf("URGENTE   │\n"); break;
    }
    
    printf("├─────────────────────────────────────────────────────────────┤\n");
    printf("│ %-3s %-28s %-6s %12s │\n", "QTD", "ITEM", "OBS", "SUBTOTAL");
    printf("├─────────────────────────────────────────────────────────────┤\n");
    
    // Percorre todos os itens do pedido
    for (int i = 0; i < pedido->quantidadeItens; i++) {
        ItemMenu* item = buscarItemPorCodigo(pedido->itens[i].codigoItem);
        if (item != NULL) {
            float subtotal = item->preco * pedido->itens[i].quantidade;
            
            // Trunca observação se for muito longa
            char obs[7];
            strncpy(obs, pedido->itens[i].observacao, 6);
            obs[6] = '\0';
            
            printf("│ %-3d %-28s %-6s R$ %9.2f │\n",
                   pedido->itens[i].quantidade,
                   item->nome,
                   strlen(pedido->itens[i].observacao) > 0 ? obs : "-",
                   subtotal);
        }
    }
    
    printf("├─────────────────────────────────────────────────────────────┤\n");
    printf("│ %-46s R$ %9.2f │\n", "TOTAL:", pedido->valorTotal);
    printf("└─────────────────────────────────────────────────────────────┘\n");
}

/*
 * FUNÇÃO: compararPedidosPorPrioridade
 * DESCRIÇÃO: Função auxiliar para comparar dois pedidos por prioridade
 * USO: Utilizada pelo Quick Sort
 * RETORNO: 
 *   > 0 se p1 tem maior prioridade que p2
 *   < 0 se p1 tem menor prioridade que p2
 *   = 0 se igual
 */
int compararPedidosPorPrioridade(const void* a, const void* b) {
    Pedido* p1 = (Pedido*)a;
    Pedido* p2 = (Pedido*)b;
    
    // Ordem decrescente: maior prioridade primeiro
    return p2->prioridade - p1->prioridade;
}

/*
 * FUNÇÃO: ordenarPedidosPorPrioridade
 * DESCRIÇÃO: Ordena array de pedidos usando QUICK SORT
 * COMPLEXIDADE: 
 *   - Melhor caso: O(n log n)
 *   - Caso médio: O(n log n)
 *   - Pior caso: O(n²) - raro com pivô bem escolhido
 * 
 * ALGORITMO: Quick Sort (implementado pela biblioteca C - qsort)
 * 
 * POR QUE QUICK SORT?
 * - É o algoritmo de ordenação de uso geral mais rápido na prática
 * - Constantes multiplicativas pequenas
 * - Boa localidade de cache (in-place)
 * - Biblioteca C otimiza a escolha do pivô
 * 
 * FUNCIONAMENTO (recursivo):
 * 1. Escolhe um pivô (elemento de referência)
 * 2. Particiona o array: elementos menores à esquerda, maiores à direita
 * 3. Ordena recursivamente as duas partições
 * 
 * COMPARAÇÃO COM OUTROS ALGORITMOS:
 * - Merge Sort: O(n log n) sempre, mas usa O(n) memória extra
 * - Heap Sort: O(n log n) sempre, mas constantes maiores
 * - Bubble Sort: O(n²) - muito lento para n > 100
 * - Insertion Sort: O(n²), mas O(n) se quase ordenado
 */
void ordenarPedidosPorPrioridade(Pedido arr[], int n) {
    // qsort é a implementação otimizada de Quick Sort da biblioteca padrão C
    // Parâmetros:
    //   1. Ponteiro para o array
    //   2. Número de elementos
    //   3. Tamanho de cada elemento
    //   4. Função de comparação
    qsort(arr, n, sizeof(Pedido), compararPedidosPorPrioridade);
    
    printf("✓ %d pedidos ordenados por prioridade (Quick Sort)\n", n);
}

// ============================================================================
// MÓDULO 4: FILA DE PEDIDOS (QUEUE - FIFO)
// ============================================================================

/*
 * FUNÇÃO: criarFila
 * DESCRIÇÃO: Cria e inicializa uma fila vazia
 * COMPLEXIDADE: O(1)
 * 
 * EXPLICAÇÃO: A fila é implementada como lista encadeada para permitir
 * operações O(1) tanto na inserção (fim) quanto na remoção (início)
 */
FilaPedidos* criarFila() {
    FilaPedidos* fila = (FilaPedidos*)malloc(sizeof(FilaPedidos));
    
    // Validação de alocação de memória
    if (fila == NULL) {
        printf("✗ ERRO: Falha ao alocar memória para a fila\n");
        return NULL;
    }
    
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
    
    return fila;
}

/*
 * FUNÇÃO: enfileirar
 * DESCRIÇÃO: Adiciona um pedido ao FIM da fila
 * COMPLEXIDADE: O(1) - tempo constante
 * 
 * ALGORITMO: Inserção no fim de lista encadeada
 * 
 * EXPLICAÇÃO DO FIFO:
 * - FIFO = First In, First Out (Primeiro a Entrar, Primeiro a Sair)
 * - Como uma fila de banco: quem chega primeiro é atendido primeiro
 * - Pedidos são adicionados no FIM e removidos do INÍCIO
 * - Garante justiça: ordem de chegada é respeitada
 * 
 * PASSOS:
 * 1. Aloca novo nó
 * 2. Copia pedido para o nó
 * 3. Se fila vazia: novo nó é início E fim
 * 4. Se não: conecta ao fim atual e atualiza ponteiro fim
 */
void enfileirar(FilaPedidos* fila, Pedido pedido) {
    // Aloca memória para novo nó
    NoFila* novoNo = (NoFila*)malloc(sizeof(NoFila));
    
    // Validação de alocação
    if (novoNo == NULL) {
        printf("✗ ERRO: Falha ao alocar memória para nó da fila\n");
        return;
    }
    
    // Copia o pedido para o novo nó
    novoNo->pedido = pedido;
    novoNo->proximo = NULL;
    
    // CASO 1: Fila está vazia
    if (fila->fim == NULL) {
        // Novo nó é tanto o início quanto o fim
        fila->inicio = novoNo;
        fila->fim = novoNo;
    }
    // CASO 2: Fila tem elementos
    else {
        // Conecta o nó atual do fim ao novo nó
        fila->fim->proximo = novoNo;
        // Atualiza o ponteiro fim
        fila->fim = novoNo;
    }
    
    fila->tamanho++;
    
    printf("✓ Pedido #%d enfileirado (Posição: %d na fila)\n", 
           pedido.numeroPedido, fila->tamanho);
}

/*
 * FUNÇÃO: desenfileirar
 * DESCRIÇÃO: Remove e retorna o pedido do INÍCIO da fila
 * COMPLEXIDADE: O(1) - tempo constante
 * 
 * ALGORITMO: Remoção do início de lista encadeada
 * 
 * PASSOS:
 * 1. Verifica se fila está vazia
 * 2. Guarda referência ao nó do início
 * 3. Atualiza ponteiro início para o próximo nó
 * 4. Se ficou vazia, atualiza fim também
 * 5. Copia pedido do nó removido
 * 6. Libera memória do nó
 * 7. Retorna pedido
 */
Pedido desenfileirar(FilaPedidos* fila) {
    Pedido pedidoVazio = {0};  // Pedido vazio para retornar em caso de erro
    
    // Validação: verifica se fila está vazia
    if (fila->inicio == NULL) {
        printf("✗ ERRO: Tentativa de desenfileirar de fila vazia\n");
        return pedidoVazio;
    }
    
    // Guarda referência ao nó que será removido
    NoFila* noRemovido = fila->inicio;
    
    // Copia o pedido antes de liberar o nó
    Pedido pedido = noRemovido->pedido;
    
    // Atualiza o ponteiro início para o próximo nó
    fila->inicio = noRemovido->proximo;
    
    // Se a fila ficou vazia, atualiza o ponteiro fim também
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }
    
    // Libera a memória do nó removido
    free(noRemovido);
    
    fila->tamanho--;
    
    printf("✓ Pedido #%d desenfileirado da cozinha\n", pedido.numeroPedido);
    
    return pedido;
}

/*
 * FUNÇÃO: verProximoPedido
 * DESCRIÇÃO: Retorna o pedido do início da fila SEM removê-lo
 * COMPLEXIDADE: O(1)
 * USO: Permite ver qual pedido será processado sem modificar a fila
 */
Pedido* verProximoPedido(FilaPedidos* fila) {
    if (fila->inicio == NULL) {
        return NULL;
    }
    return &(fila->inicio->pedido);
}

/*
 * FUNÇÃO: filaVazia
 * DESCRIÇÃO: Verifica se a fila está vazia
 * COMPLEXIDADE: O(1)
 */
int filaVazia(FilaPedidos* fila) {
    return (fila->inicio == NULL);
}

/*
 * FUNÇÃO: exibirFila
 * DESCRIÇÃO: Exibe todos os pedidos na fila (do início ao fim)
 * COMPLEXIDADE: O(n) onde n = tamanho da fila
 */
void exibirFila(FilaPedidos* fila) {
    printf("\n");
    printf("═══════════════════════════════════════════════════════════════\n");
    printf("           FILA DE PEDIDOS DA COZINHA (FIFO)                   \n");
    printf("═══════════════════════════════════════════════════════════════\n");
    
    if (filaVazia(fila)) {
        printf("│ Fila vazia - Nenhum pedido aguardando                      │\n");
        printf("═══════════════════════════════════════════════════════════════\n");
        return;
    }
    
    printf("Total na fila: %d pedido(s)\n\n", fila->tamanho);
    
    NoFila* atual = fila->inicio;
    int posicao = 1;
    
    // Percorre a fila do início ao fim
    while (atual != NULL) {
        printf("[Posição %d] ", posicao);
        printf("Pedido #%d | Mesa %d | Prioridade: %d | Valor: R$ %.2f\n",
               atual->pedido.numeroPedido,
               atual->pedido.mesa,
               atual->pedido.prioridade,
               atual->pedido.valorTotal);
        
        atual = atual->proximo;
        posicao++;
    }
    
    printf("═══════════════════════════════════════════════════════════════\n");
    printf("→ Próximo a ser preparado: Pedido #%d (Mesa %d)\n", 
           fila->inicio->pedido.numeroPedido,
           fila->inicio->pedido.mesa);
    printf("═══════════════════════════════════════════════════════════════\n");
}

// ============================================================================
// MÓDULO 5: PILHA DE HISTÓRICO (STACK - LIFO)
// ============================================================================

/*
 * FUNÇÃO: inicializarPilha
 * DESCRIÇÃO: Inicializa a pilha de histórico
 * COMPLEXIDADE: O(1)
 */
void inicializarPilha(PilhaHistorico* pilha) {
    pilha->topo = -1;  // -1 indica pilha vazia
}

/*
 * FUNÇÃO: empilharAcao
 * DESCRIÇÃO: Adiciona uma ação ao TOPO da pilha
 * COMPLEXIDADE: O(1) - tempo constante
 * 
 * ALGORITMO: Inserção em array (no fim)
 * 
 * EXPLICAÇÃO DO LIFO:
 * - LIFO = Last In, First Out (Último a Entrar, Primeiro a Sair)
 * - Como uma pilha de pratos: você coloca e remove sempre do topo
 * - Perfeito para UNDO: desfazemos a última ação primeiro
 * 
 * PASSOS:
 * 1. Verifica se pilha está cheia
 * 2. Se cheia, descarta a ação mais antiga (opcional)
 * 3. Incrementa topo
 * 4. Adiciona ação no novo topo
 * 
 * LIMITAÇÃO: Pilha tem tamanho fixo (MAX_HISTORICO = 10)
 * Se ultrapassar, ações mais antigas são perdidas
 */
void empilharAcao(PilhaHistorico* pilha, char* descricao, int numeroPedido) {
    // Verifica se pilha está cheia
    if (pilha->topo >= MAX_HISTORICO - 1) {
        // Opção 1: Descartar ação mais antiga (shift)
        // Move todas as ações uma posição para baixo
        for (int i = 0; i < MAX_HISTORICO - 1; i++) {
            pilha->acoes[i] = pilha->acoes[i + 1];
        }
        pilha->topo = MAX_HISTORICO - 2;  // Ajusta topo
    }
    
    // Incrementa topo
    pilha->topo++;
    
    // Adiciona nova ação no topo
    strcpy(pilha->acoes[pilha->topo].descricao, descricao);
    pilha->acoes[pilha->topo].numeroPedido = numeroPedido;
    pilha->acoes[pilha->topo].momento = time(NULL);
}

/*
 * FUNÇÃO: desempilharAcao
 * DESCRIÇÃO: Remove e retorna a ação do TOPO da pilha
 * COMPLEXIDADE: O(1) - tempo constante
 * 
 * PASSOS:
 * 1. Verifica se pilha está vazia
 * 2. Copia ação do topo
 * 3. Decrementa topo
 * 4. Retorna ação
 */
Acao desempilharAcao(PilhaHistorico* pilha) {
    Acao acaoVazia = {0};
    
    // Validação: verifica se pilha está vazia
    if (pilha->topo < 0) {
        printf("✗ ERRO: Pilha de histórico vazia - nada para desfazer\n");
        return acaoVazia;
    }
    
    // Copia ação do topo
    Acao acao = pilha->acoes[pilha->topo];
    
    // Remove do topo (decrementa índice)
    pilha->topo--;
    
    return acao;
}

/*
 * FUNÇÃO: pilhaVazia
 * DESCRIÇÃO: Verifica se a pilha está vazia
 * COMPLEXIDADE: O(1)
 */
int pilhaVazia(PilhaHistorico* pilha) {
    return (pilha->topo < 0);
}

/*
 * FUNÇÃO: exibirHistorico
 * DESCRIÇÃO: Exibe todas as ações do histórico (do topo para baixo)
 * COMPLEXIDADE: O(n) onde n = número de ações
 */
void exibirHistorico(PilhaHistorico* pilha) {
    printf("\n");
    printf("═══════════════════════════════════════════════════════════════\n");
    printf("              HISTÓRICO DE AÇÕES (LIFO - Stack)                \n");
    printf("═══════════════════════════════════════════════════════════════\n");
    
    if (pilhaVazia(pilha)) {
        printf("│ Histórico vazio - Nenhuma ação registrada                  │\n");
        printf("═══════════════════════════════════════════════════════════════\n");
        return;
    }
    
    printf("Total: %d ação(ões) | Limite: %d\n\n", pilha->topo + 1, MAX_HISTORICO);
    
    // Percorre do topo (mais recente) para baixo (mais antiga)
    for (int i = pilha->topo; i >= 0; i--) {
        printf("[%d] %s - Pedido #%d\n", 
               pilha->topo - i + 1,
               pilha->acoes[i].descricao,
               pilha->acoes[i].numeroPedido);
    }
    
    printf("═══════════════════════════════════════════════════════════════\n");
    printf("→ Próximo UNDO desfará: %s\n", pilha->acoes[pilha->topo].descricao);
    printf("═══════════════════════════════════════════════════════════════\n");
}

// ============================================================================
// MÓDULO 6: INTERFACE DO USUÁRIO E MENU INTERATIVO
// ============================================================================

/*
 * FUNÇÃO: menuCriarPedido
 * DESCRIÇÃO: Interface para criar um novo pedido
 * DEMONSTRA: Uso de vetores, busca, e adição à fila
 */
void menuCriarPedido() {
    limparTela();
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║                     CRIAR NOVO PEDIDO                         ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n");
    
    int mesa;
    printf("\nNúmero da mesa: ");
    scanf("%d", &mesa);
    limparBuffer();
    
    // Cria novo pedido
    Pedido novoPedido;
    criarPedido(&novoPedido, mesa);
    
    // Empilha ação no histórico
    char descricao[100];
    sprintf(descricao, "Pedido #%d criado para mesa %d", novoPedido.numeroPedido, mesa);
    empilharAcao(&historico, descricao, novoPedido.numeroPedido);
    
    // Loop para adicionar itens
    char continuar = 's';
    while (continuar == 's' || continuar == 'S') {
        exibirMenu();
        
        int codigo, quantidade;
        char observacao[MAX_OBSERVACAO] = "";
        
        printf("\nCódigo do item: ");
        scanf("%d", &codigo);
        limparBuffer();
        
        printf("Quantidade: ");
        scanf("%d", &quantidade);
        limparBuffer();
        
        printf("Observação (Enter para pular): ");
        fgets(observacao, MAX_OBSERVACAO, stdin);
        observacao[strcspn(observacao, "\n")] = 0;  // Remove \n
        
        // Adiciona item ao pedido (já valida internamente)
        adicionarItemAoPedido(&novoPedido, codigo, quantidade, observacao);
        
        // Empilha ação
        sprintf(descricao, "Item %d adicionado ao pedido #%d", codigo, novoPedido.numeroPedido);
        empilharAcao(&historico, descricao, novoPedido.numeroPedido);
        
        printf("\nAdicionar mais itens? (s/n): ");
        scanf(" %c", &continuar);
        limparBuffer();
    }
    
    // Exibe resumo do pedido
    exibirPedido(&novoPedido);
    
    // Define prioridade
    printf("\nDefina a prioridade:\n");
    printf("1 - Baixa\n");
    printf("2 - Normal\n");
    printf("3 - Alta\n");
    printf("4 - Urgente\n");
    printf("Escolha: ");
    scanf("%d", &novoPedido.prioridade);
    limparBuffer();
    
    // Adiciona pedido ao vetor global e à fila
    if (totalPedidos < MAX_PEDIDOS) {
        pedidos[totalPedidos] = novoPedido;
        totalPedidos++;
        
        // Enfileira na cozinha
        enfileirar(filaCozinha, novoPedido);
        
        // Empilha ação
        sprintf(descricao, "Pedido #%d enviado para cozinha", novoPedido.numeroPedido);
        empilharAcao(&historico, descricao, novoPedido.numeroPedido);
        
        printf("\n✓ Pedido registrado e enviado para a cozinha!\n");
    } else {
        printf("\n✗ ERRO: Limite de pedidos atingido (%d)\n", MAX_PEDIDOS);
    }
    
    pausar();
}

/*
 * FUNÇÃO: menuGerenciarCozinha
 * DESCRIÇÃO: Interface para gerenciar a fila de pedidos da cozinha
 * DEMONSTRA: Operações de fila (enqueue, dequeue, peek)
 */
void menuGerenciarCozinha() {
    limparTela();
    
    int opcao;
    do {
        printf("\n");
        printf("╔═══════════════════════════════════════════════════════════════╗\n");
        printf("║                  GERENCIAR FILA DA COZINHA                    ║\n");
        printf("╚═══════════════════════════════════════════════════════════════╝\n");
        printf("\n");
        printf("1 - Ver fila de pedidos\n");
        printf("2 - Processar próximo pedido (desenfileirar)\n");
        printf("3 - Ver próximo pedido (sem remover)\n");
        printf("0 - Voltar\n");
        printf("\nEscolha: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                exibirFila(filaCozinha);
                pausar();
                break;
                
            case 2: {
                if (!filaVazia(filaCozinha)) {
                    Pedido p = desenfileirar(filaCozinha);
                    printf("\n✓ Pedido #%d (Mesa %d) foi processado!\n", p.numeroPedido, p.mesa);
                    
                    // Empilha ação
                    char desc[100];
                    sprintf(desc, "Pedido #%d processado na cozinha", p.numeroPedido);
                    empilharAcao(&historico, desc, p.numeroPedido);
                } else {
                    printf("\n✗ Fila vazia - Nenhum pedido para processar\n");
                }
                pausar();
                break;
            }
                
            case 3: {
                Pedido* p = verProximoPedido(filaCozinha);
                if (p != NULL) {
                    printf("\n→ Próximo pedido a ser preparado:\n");
                    exibirPedido(p);
                } else {
                    printf("\n✗ Fila vazia\n");
                }
                pausar();
                break;
            }
        }
        
    } while(opcao != 0);
}

/*
 * FUNÇÃO: menuOrdenarPedidos
 * DESCRIÇÃO: Interface para ordenar e visualizar pedidos
 * DEMONSTRA: Algoritmos de ordenação (Quick Sort)
 */
void menuOrdenarPedidos() {
    limparTela();
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║                     ORDENAR PEDIDOS                           ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n");
    
    if (totalPedidos == 0) {
        printf("\n✗ Nenhum pedido cadastrado\n");
        pausar();
        return;
    }
    
    // Cria cópia do array para ordenar (não modifica original)
    Pedido pedidosOrdenados[MAX_PEDIDOS];
    memcpy(pedidosOrdenados, pedidos, totalPedidos * sizeof(Pedido));
    
    printf("\nOrdenar por:\n");
    printf("1 - Prioridade (decrescente)\n");
    printf("Escolha: ");
    
    int opcao;
    scanf("%d", &opcao);
    limparBuffer();
    
    if (opcao == 1) {
        // Ordena usando Quick Sort
        ordenarPedidosPorPrioridade(pedidosOrdenados, totalPedidos);
        
        printf("\n");
        printf("═══════════════════════════════════════════════════════════════\n");
        printf("              PEDIDOS ORDENADOS POR PRIORIDADE                 \n");
        printf("═══════════════════════════════════════════════════════════════\n");
        
        for (int i = 0; i < totalPedidos; i++) {
            printf("\n[%d] ", i + 1);
            exibirPedido(&pedidosOrdenados[i]);
        }
    }
    
    pausar();
}

/*
 * FUNÇÃO: menuBuscarItem
 * DESCRIÇÃO: Interface para buscar itens no menu
 * DEMONSTRA: Busca binária (por código) e busca linear (por nome)
 */
void menuBuscarItem() {
    limparTela();
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║                      BUSCAR ITEM DO MENU                      ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n");
    
    printf("\nBuscar por:\n");
    printf("1 - Código (Busca Binária - O(log n))\n");
    printf("2 - Nome (Busca Linear - O(n))\n");
    printf("Escolha: ");
    
    int opcao;
    scanf("%d", &opcao);
    limparBuffer();
    
    if (opcao == 1) {
        int codigo;
        printf("\nDigite o código: ");
        scanf("%d", &codigo);
        limparBuffer();
        
        printf("\n⏱️  Iniciando BUSCA BINÁRIA...\n");
        ItemMenu* item = buscarItemPorCodigo(codigo);
        
        if (item != NULL) {
            printf("\n✓ Item encontrado!\n");
            printf("─────────────────────────────────────────────\n");
            printf("Código: %d\n", item->codigo);
            printf("Nome: %s\n", item->nome);
            printf("Categoria: %s\n", item->categoria);
            printf("Preço: R$ %.2f\n", item->preco);
            printf("Tempo de preparo: %d minutos\n", item->tempoPreparo);
            printf("─────────────────────────────────────────────\n");
        } else {
            printf("\n✗ Item não encontrado\n");
        }
        
    } else if (opcao == 2) {
        char nome[MAX_NOME];
        printf("\nDigite o nome (ou parte): ");
        fgets(nome, MAX_NOME, stdin);
        nome[strcspn(nome, "\n")] = 0;
        
        printf("\n⏱️  Iniciando BUSCA LINEAR...\n");
        ItemMenu* item = buscarItemPorNome(nome);
        
        if (item != NULL) {
            printf("\n✓ Item encontrado!\n");
            printf("─────────────────────────────────────────────\n");
            printf("Código: %d\n", item->codigo);
            printf("Nome: %s\n", item->nome);
            printf("Categoria: %s\n", item->categoria);
            printf("Preço: R$ %.2f\n", item->preco);
            printf("Tempo de preparo: %d minutos\n", item->tempoPreparo);
            printf("─────────────────────────────────────────────\n");
        } else {
            printf("\n✗ Item não encontrado\n");
        }
    }
    
    pausar();
}

/*
 * FUNÇÃO: menuHistorico
 * DESCRIÇÃO: Interface para visualizar e usar o histórico (undo)
 * DEMONSTRA: Operações de pilha (push, pop, peek)
 */
void menuHistorico() {
    limparTela();
    
    int opcao;
    do {
        printf("\n");
        printf("╔═══════════════════════════════════════════════════════════════╗\n");
        printf("║                    HISTÓRICO DE AÇÕES                         ║\n");
        printf("╚═══════════════════════════════════════════════════════════════╝\n");
        printf("\n");
        printf("1 - Ver histórico\n");
        printf("2 - Desfazer última ação (UNDO)\n");
        printf("0 - Voltar\n");
        printf("\nEscolha: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                exibirHistorico(&historico);
                pausar();
                break;
                
            case 2: {
                if (!pilhaVazia(&historico)) {
                    Acao acao = desempilharAcao(&historico);
                    printf("\n✓ Ação desfeita: %s\n", acao.descricao);
                    printf("(Nota: Esta é uma demonstração - o undo real exigiria\n");
                    printf(" implementação de reversão de cada tipo de operação)\n");
                } else {
                    printf("\n✗ Histórico vazio - Nada para desfazer\n");
                }
                pausar();
                break;
            }
        }
        
    } while(opcao != 0);
}

/*
 * FUNÇÃO: menuPrincipal
 * DESCRIÇÃO: Menu principal do sistema
 */
void menuPrincipal() {
    int opcao;
    
    do {
        limparTela();
        printf("\n");
        printf("╔════════════════════════════════════════════════════════════════════╗\n");
        printf("║     SISTEMA DE GERENCIAMENTO DE PEDIDOS - RESTAURANTE             ║\n");
        printf("║                    Sabor da Casa                                   ║\n");
        printf("╚════════════════════════════════════════════════════════════════════╝\n");
        printf("\n");
        printf("  DEMONSTRAÇÃO DE ESTRUTURAS DE DADOS:\n");
        printf("  • Vetores       → Menu e lista de pedidos\n");
        printf("  • Busca Binária → Buscar item por código O(log n)\n");
        printf("  • Busca Linear  → Buscar item por nome O(n)\n");
        printf("  • Quick Sort    → Ordenar pedidos O(n log n)\n");
        printf("  • Fila (FIFO)   → Gerenciar pedidos da cozinha\n");
        printf("  • Pilha (LIFO)  → Histórico de ações (undo)\n");
        printf("\n");
        printf("────────────────────────────────────────────────────────────────────\n");
        printf("\n");
        printf("1 - Ver menu do restaurante\n");
        printf("2 - Criar novo pedido\n");
        printf("3 - Gerenciar fila da cozinha (FIFO)\n");
        printf("4 - Ordenar pedidos (Quick Sort)\n");
        printf("5 - Buscar item no menu\n");
        printf("6 - Ver histórico de ações (Stack)\n");
        printf("0 - Sair\n");
        printf("\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                limparTela();
                exibirMenu();
                pausar();
                break;
                
            case 2:
                menuCriarPedido();
                break;
                
            case 3:
                menuGerenciarCozinha();
                break;
                
            case 4:
                menuOrdenarPedidos();
                break;
                
            case 5:
                menuBuscarItem();
                break;
                
            case 6:
                menuHistorico();
                break;
                
            case 0:
                printf("\n✓ Encerrando sistema...\n");
                break;
                
            default:
                printf("\n✗ Opção inválida!\n");
                pausar();
        }
        
    } while(opcao != 0);
}

// ============================================================================
// FUNÇÃO PRINCIPAL
// ============================================================================

/*
 * FUNÇÃO: main
 * DESCRIÇÃO: Ponto de entrada do programa
 * 
 * INICIALIZAÇÃO:
 * 1. Inicializa menu com itens pré-cadastrados
 * 2. Cria fila de pedidos
 * 3. Inicializa pilha de histórico
 * 4. Inicia interface do usuário
 * 
 * LIMPEZA:
 * - Libera memória alocada dinamicamente (fila)
 */
int main() {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════════╗\n");
    printf("║            INICIALIZANDO SISTEMA DO RESTAURANTE...                ║\n");
    printf("╚════════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    
    // Inicializa estruturas de dados
    printf("→ Carregando menu...\n");
    inicializarMenu();
    
    printf("→ Criando fila de pedidos (FIFO)...\n");
    filaCozinha = criarFila();
    if (filaCozinha == NULL) {
        printf("✗ ERRO CRÍTICO: Falha ao criar fila\n");
        return 1;
    }
    
    printf("→ Inicializando pilha de histórico (LIFO)...\n");
    inicializarPilha(&historico);
    
    printf("\n✓ Sistema pronto!\n");
    pausar();
    
    // Executa menu principal
    menuPrincipal();
    
    // Limpeza
    printf("\n→ Liberando recursos...\n");
    // TODO: Implementar liberação completa da fila
    // (percorrer todos os nós e liberar)
    
    printf("✓ Sistema encerrado com sucesso!\n\n");
    
    return 0;
}

/*
 * ============================================================================
 * FIM DO PROGRAMA
 * ============================================================================
 * 
 * ANÁLISE DE COMPLEXIDADE - RESUMO:
 * 
 * OPERAÇÃO                      | ESTRUTURA    | COMPLEXIDADE | JUSTIFICATIVA
 * ─────────────────────────────────────────────────────────────────────────
 * Buscar item por código        | Busca Bin.   | O(log n)     | Array ordenado
 * Buscar item por nome          | Busca Lin.   | O(n)         | Array não ord.
 * Ordenar pedidos               | Quick Sort   | O(n log n)   | Média do QS
 * Enfileirar pedido             | Fila (Queue) | O(1)         | Inserção no fim
 * Desenfileirar pedido          | Fila (Queue) | O(1)         | Remoção início
 * Ver próximo pedido            | Fila (Queue) | O(1)         | Acesso início
 * Empilhar ação                 | Pilha (Stack)| O(1)         | Inserção no topo
 * Desempilhar ação              | Pilha (Stack)| O(1)         | Remoção do topo
 * Acessar item do menu por índice| Vetor      | O(1)         | Acesso direto
 * 
 * MEMÓRIA UTILIZADA:
 * - Menu: O(n) onde n = número de itens
 * - Pedidos: O(m) onde m = número de pedidos
 * - Fila: O(f) onde f = pedidos na fila
 * - Pilha: O(1) - tamanho fixo (10 ações)
 * 
 * TOTAL: O(n + m + f) = O(n) considerando que n, m, f são proporcionais
 * 
 * ============================================================================
 */
