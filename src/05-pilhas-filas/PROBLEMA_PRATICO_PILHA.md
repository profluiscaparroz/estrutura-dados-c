# Problema Prático: Sistema de Desfazer/Refazer (Undo/Redo) de Editor de Texto

## 📋 Descrição do Problema

Um editor de texto simples precisa implementar funcionalidades de:
- **UNDO** (Ctrl+Z): Desfazer última ação
- **REDO** (Ctrl+Y): Refazer ação desfeita
- Manter histórico limitado de ações
- Limpar histórico de redo ao fazer nova ação

**Por que usar Pilhas (Stack)?**
- LIFO (Last In, First Out) - Última ação é a primeira a desfazer
- Push O(1) - Adicionar nova ação
- Pop O(1) - Desfazer/refazer
- Estrutura natural para histórico sequencial

## 🔴 Problema: Implementação Sem Estrutura de Dados Adequada

```c
#include <stdio.h>
#include <string.h>

#define MAX_ACOES 100

typedef struct {
    char tipo[20];      // "inserir", "deletar"
    char texto[100];
    int posicao;
} Acao;

// PROBLEMA: Usa array sem controle adequado de pilha
Acao historico[MAX_ACOES];
int topo = -1;

// PROBLEMA: Não tem pilha de redo
void adicionarAcao(Acao a) {
    if (topo < MAX_ACOES - 1) {
        topo++;
        historico[topo] = a;
    }
}

// PROBLEMA: Não move ação para redo, perde dados
void desfazer() {
    if (topo >= 0) {
        printf("Desfazendo: %s\n", historico[topo].tipo);
        topo--;  // Simplesmente decrementa, perde a ação!
    }
}

// PROBLEMA: Sem implementação de redo
void refazer() {
    printf("Redo não implementado!\n");
}

int main() {
    Acao a1 = {"inserir", "Olá", 0};
    Acao a2 = {"inserir", " Mundo", 4};
    
    adicionarAcao(a1);
    adicionarAcao(a2);
    
    desfazer();  // Perde a ação permanentemente
    refazer();   // Não funciona
    
    return 0;
}
```

### Problemas Identificados:
1. ❌ Ações desfeitas são perdidas (não há pilha de redo)
2. ❌ Nova ação não limpa histórico de redo
3. ❌ Sem controle adequado de limites
4. ❌ Não reconstrói o texto após undo/redo

## ✅ Solução: Duas Pilhas (Undo e Redo)

```c
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ACOES 50
#define MAX_TEXTO 1000

// ============= ESTRUTURAS =============

typedef enum {
    INSERIR,
    DELETAR,
    SUBSTITUIR
} TipoAcao;

typedef struct {
    TipoAcao tipo;
    char texto[100];     // Texto inserido ou deletado
    int posicao;         // Posição da ação
    int tamanho;         // Tamanho do texto afetado
} Acao;

// Estrutura da Pilha
typedef struct {
    Acao acoes[MAX_ACOES];
    int topo;
} Pilha;

// Editor com documento e duas pilhas
typedef struct {
    char documento[MAX_TEXTO];
    Pilha pilhaUndo;
    Pilha pilhaRedo;
} Editor;

// ============= OPERAÇÕES DE PILHA =============

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

bool pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

bool pilhaCheia(Pilha *p) {
    return p->topo == MAX_ACOES - 1;
}

bool push(Pilha *p, Acao acao) {
    if (pilhaCheia(p)) {
        printf("⚠️  Histórico cheio! Ação mais antiga removida.\n");
        // Remover ação mais antiga (shift array)
        for (int i = 0; i < p->topo; i++) {
            p->acoes[i] = p->acoes[i + 1];
        }
        p->topo--;
    }
    
    p->topo++;
    p->acoes[p->topo] = acao;
    return true;
}

bool pop(Pilha *p, Acao *acao) {
    if (pilhaVazia(p)) {
        return false;
    }
    
    *acao = p->acoes[p->topo];
    p->topo--;
    return true;
}

Acao* peek(Pilha *p) {
    if (pilhaVazia(p)) {
        return NULL;
    }
    return &p->acoes[p->topo];
}

int tamanho(Pilha *p) {
    return p->topo + 1;
}

// ============= OPERAÇÕES DO EDITOR =============

void inicializarEditor(Editor *ed) {
    strcpy(ed->documento, "");
    inicializarPilha(&ed->pilhaUndo);
    inicializarPilha(&ed->pilhaRedo);
}

// Insere texto na posição especificada
void inserirTexto(Editor *ed, const char *texto, int pos) {
    int len = strlen(texto);
    int docLen = strlen(ed->documento);
    
    if (pos > docLen) pos = docLen;
    
    // Registrar ação antes de executar
    Acao acao = {INSERIR, "", pos, len};
    strncpy(acao.texto, texto, sizeof(acao.texto) - 1);
    
    // Executar inserção
    memmove(ed->documento + pos + len, 
            ed->documento + pos, 
            docLen - pos + 1);
    memcpy(ed->documento + pos, texto, len);
    
    // Adicionar à pilha de undo
    push(&ed->pilhaUndo, acao);
    
    // IMPORTANTE: Limpar pilha de redo ao fazer nova ação
    inicializarPilha(&ed->pilhaRedo);
    
    printf("✓ Inserido '%s' na posição %d\n", texto, pos);
}

// Deleta texto da posição especificada
void deletarTexto(Editor *ed, int pos, int tamanho) {
    int docLen = strlen(ed->documento);
    
    if (pos >= docLen || tamanho <= 0) {
        printf("⚠️  Deleção inválida\n");
        return;
    }
    
    if (pos + tamanho > docLen) {
        tamanho = docLen - pos;
    }
    
    // Registrar ação (salvar texto deletado)
    Acao acao = {DELETAR, "", pos, tamanho};
    strncpy(acao.texto, ed->documento + pos, tamanho);
    acao.texto[tamanho] = '\0';
    
    // Executar deleção
    memmove(ed->documento + pos,
            ed->documento + pos + tamanho,
            docLen - pos - tamanho + 1);
    
    // Adicionar à pilha de undo
    push(&ed->pilhaUndo, acao);
    
    // Limpar pilha de redo
    inicializarPilha(&ed->pilhaRedo);
    
    printf("✓ Deletado '%s' da posição %d\n", acao.texto, pos);
}

// Desfaz última ação
bool desfazer(Editor *ed) {
    Acao acao;
    
    if (!pop(&ed->pilhaUndo, &acao)) {
        printf("⚠️  Nada para desfazer\n");
        return false;
    }
    
    // Executar operação inversa
    if (acao.tipo == INSERIR) {
        // Desfazer inserção = deletar o texto
        memmove(ed->documento + acao.posicao,
                ed->documento + acao.posicao + acao.tamanho,
                strlen(ed->documento) - acao.posicao - acao.tamanho + 1);
        
        printf("↶ UNDO: Removido '%s'\n", acao.texto);
        
    } else if (acao.tipo == DELETAR) {
        // Desfazer deleção = reinserir o texto
        int docLen = strlen(ed->documento);
        memmove(ed->documento + acao.posicao + acao.tamanho,
                ed->documento + acao.posicao,
                docLen - acao.posicao + 1);
        memcpy(ed->documento + acao.posicao, acao.texto, acao.tamanho);
        
        printf("↶ UNDO: Restaurado '%s'\n", acao.texto);
    }
    
    // Mover ação para pilha de redo
    push(&ed->pilhaRedo, acao);
    
    return true;
}

// Refaz última ação desfeita
bool refazer(Editor *ed) {
    Acao acao;
    
    if (!pop(&ed->pilhaRedo, &acao)) {
        printf("⚠️  Nada para refazer\n");
        return false;
    }
    
    // Executar ação novamente
    if (acao.tipo == INSERIR) {
        // Refazer inserção
        int docLen = strlen(ed->documento);
        memmove(ed->documento + acao.posicao + acao.tamanho,
                ed->documento + acao.posicao,
                docLen - acao.posicao + 1);
        memcpy(ed->documento + acao.posicao, acao.texto, acao.tamanho);
        
        printf("↷ REDO: Inserido '%s'\n", acao.texto);
        
    } else if (acao.tipo == DELETAR) {
        // Refazer deleção
        memmove(ed->documento + acao.posicao,
                ed->documento + acao.posicao + acao.tamanho,
                strlen(ed->documento) - acao.posicao - acao.tamanho + 1);
        
        printf("↷ REDO: Deletado '%s'\n", acao.texto);
    }
    
    // Mover ação de volta para pilha de undo
    push(&ed->pilhaUndo, acao);
    
    return true;
}

// Exibe estado atual do editor
void exibirEditor(Editor *ed) {
    printf("\n┌─ Documento ─────────────────┐\n");
    printf("│ \"%s\"\n", ed->documento);
    printf("└─────────────────────────────┘\n");
    printf("Histórico: %d undo | %d redo\n", 
           tamanho(&ed->pilhaUndo), 
           tamanho(&ed->pilhaRedo));
}

// ============= MAIN =============

int main() {
    Editor editor;
    inicializarEditor(&editor);
    
    printf("=== EDITOR DE TEXTO COM UNDO/REDO ===\n");
    printf("Usando estrutura de PILHA (Stack)\n\n");
    
    // Sequência de operações
    printf("--- Operação 1: Inserir texto ---\n");
    inserirTexto(&editor, "Olá", 0);
    exibirEditor(&editor);
    
    printf("\n--- Operação 2: Inserir mais texto ---\n");
    inserirTexto(&editor, " Mundo", 3);
    exibirEditor(&editor);
    
    printf("\n--- Operação 3: Inserir exclamação ---\n");
    inserirTexto(&editor, "!", 9);
    exibirEditor(&editor);
    
    printf("\n--- Operação 4: Deletar parte ---\n");
    deletarTexto(&editor, 3, 6);  // Remove " Mundo"
    exibirEditor(&editor);
    
    printf("\n--- UNDO 1 ---\n");
    desfazer(&editor);
    exibirEditor(&editor);
    
    printf("\n--- UNDO 2 ---\n");
    desfazer(&editor);
    exibirEditor(&editor);
    
    printf("\n--- REDO 1 ---\n");
    refazer(&editor);
    exibirEditor(&editor);
    
    printf("\n--- Nova ação: Limpa histórico de REDO ---\n");
    inserirTexto(&editor, " C!", 9);
    exibirEditor(&editor);
    
    printf("\n--- Tentativa de REDO (deve falhar) ---\n");
    refazer(&editor);
    exibirEditor(&editor);
    
    printf("\n--- Múltiplos UNDOs ---\n");
    desfazer(&editor);
    desfazer(&editor);
    desfazer(&editor);
    desfazer(&editor);
    desfazer(&editor);  // Deve avisar que não há mais
    exibirEditor(&editor);
    
    return 0;
}
```

## 📊 Análise de Complexidade

| Operação | Complexidade Temporal | Complexidade Espacial |
|----------|----------------------|----------------------|
| Push (adicionar ação) | O(1) | O(1) |
| Pop (remover ação) | O(1) | O(1) |
| Peek (ver topo) | O(1) | O(1) |
| Undo | O(n)* | O(1) |
| Redo | O(n)* | O(1) |

*O(n) devido à manipulação de string (memmove), não da pilha

## 🎯 Conceitos de Pilha Aplicados

- ✅ **LIFO** (Last In, First Out)
- ✅ **Push/Pop** em O(1)
- ✅ **Duas pilhas** para undo/redo
- ✅ **Limpar redo** ao fazer nova ação
- ✅ **Histórico limitado** com overflow handling
- ✅ **Validação** de pilha vazia/cheia

## 💡 Casos de Uso de Pilhas

| Aplicação | Por que Pilha? |
|-----------|----------------|
| Undo/Redo | LIFO - última ação primeiro |
| Navegador (Back/Forward) | Histórico sequencial |
| Validação de parênteses | Empilha '(' e desempilha com ')' |
| Expressões matemáticas | Notação pós-fixa (RPN) |
| Call stack (funções) | Última função chamada retorna primeiro |
| DFS em grafos | Exploração em profundidade |

## 📝 Como Compilar e Executar

```bash
# Compilar
gcc PROBLEMA_PRATICO.c -o editor -Wall

# Executar
./editor
```

## 🧪 Exemplo de Saída

```
=== EDITOR DE TEXTO COM UNDO/REDO ===
Usando estrutura de PILHA (Stack)

--- Operação 1: Inserir texto ---
✓ Inserido 'Olá' na posição 0

┌─ Documento ─────────────────┐
│ "Olá"
└─────────────────────────────┘
Histórico: 1 undo | 0 redo

--- Operação 3: Inserir exclamação ---
✓ Inserido '!' na posição 9

┌─ Documento ─────────────────┐
│ "Olá Mundo!"
└─────────────────────────────┘
Histórico: 3 undo | 0 redo

--- UNDO 1 ---
↶ UNDO: Removido '!'

┌─ Documento ─────────────────┐
│ "Olá Mundo"
└─────────────────────────────┘
Histórico: 2 undo | 1 redo

--- REDO 1 ---
↷ REDO: Inserido '!'

┌─ Documento ─────────────────┐
│ "Olá Mundo!"
└─────────────────────────────┘
Histórico: 3 undo | 0 redo
```

## 📚 Lições Aprendidas

1. **Duas pilhas necessárias** - Uma para undo, outra para redo
2. **Limpar redo ao agir** - Nova ação invalida histórico de redo
3. **Salvar inversa** - Undo precisa dos dados originais
4. **LIFO perfeito** - Última ação é sempre a primeira a desfazer
5. **Limite de histórico** - Previne uso excessivo de memória
6. **Validação essencial** - Sempre verificar pilhas vazias/cheias

## 🔍 Melhorias Possíveis

1. **Compressão de ações** - Juntar múltiplas inserções sequenciais
2. **Ações compostas** - Substituir = deletar + inserir como uma ação
3. **Timestamps** - Registrar quando cada ação foi feita
4. **Undo seletivo** - Desfazer ação específica (mais complexo)
5. **Persistência** - Salvar histórico em arquivo
6. **Memória dinâmica** - Pilha ilimitada com malloc/free
