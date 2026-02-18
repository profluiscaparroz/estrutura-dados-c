# Problema Prático: Sistema de Dicionário com Autocompletar

## 📋 Descrição do Problema

Um dicionário de palavras precisa:
- Inserir palavras rapidamente
- Buscar palavras eficientemente
- Autocompletar palavras (sugerir palavras que começam com prefixo)
- Listar palavras em ordem alfabética
- Verificar se palavra existe
- Contar quantas palavras começam com determinado prefixo

**Por que usar Árvore Binária de Busca (BST)?**
- Busca O(log n) em média (balanceada)
- Inserção O(log n) em média
- Percurso in-order fornece ordem alfabética automaticamente
- Estrutura hierárquica facilita busca por prefixos

## 🔴 Problema: Busca Linear em Array Não Ordenado

```c
#include <stdio.h>
#include <string.h>

#define MAX_PALAVRAS 10000

char dicionario[MAX_PALAVRAS][50];
int total = 0;

// PROBLEMA: Busca linear O(n)
int buscar(const char *palavra) {
    for (int i = 0; i < total; i++) {
        if (strcmp(dicionario[i], palavra) == 0) {
            return i;
        }
    }
    return -1;
}

// PROBLEMA: Não mantém ordem, dificulta autocompletar
void inserir(const char *palavra) {
    if (total < MAX_PALAVRAS) {
        strcpy(dicionario[total++], palavra);
    }
}

// PROBLEMA: Autocompletar é O(n) e ineficiente
void autocompletar(const char *prefixo) {
    for (int i = 0; i < total; i++) {
        if (strncmp(dicionario[i], prefixo, strlen(prefixo)) == 0) {
            printf("%s\n", dicionario[i]);
        }
    }
}

int main() {
    inserir("casa");
    inserir("cachorro");
    inserir("carro");
    
    // Busca lenta
    buscar("cachorro");  // O(n)
    
    // Autocompletar ineficiente
    autocompletar("ca");  // O(n)
    
    return 0;
}
```

### Problemas Identificados:
1. ❌ Busca O(n) - muito lenta
2. ❌ Inserção não mantém ordem
3. ❌ Autocompletar percorre todo array
4. ❌ Tamanho fixo (array)
5. ❌ Não aproveita estrutura dos dados

## ✅ Solução: Árvore Binária de Busca (BST)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_PALAVRA 50

// ============= ESTRUTURAS =============

typedef struct No {
    char palavra[MAX_PALAVRA];
    char definicao[200];
    int frequencia;  // Quantas vezes foi buscada
    struct No *esquerda;
    struct No *direita;
} No;

typedef struct {
    No *raiz;
    int totalPalavras;
} Dicionario;

// ============= FUNÇÕES AUXILIARES =============

void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// ============= OPERAÇÕES DA BST =============

No* criarNo(const char *palavra, const char *definicao) {
    No *novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("❌ Erro ao alocar memória\n");
        return NULL;
    }
    
    strcpy(novo->palavra, palavra);
    toLowerCase(novo->palavra);
    strcpy(novo->definicao, definicao);
    novo->frequencia = 0;
    novo->esquerda = NULL;
    novo->direita = NULL;
    
    return novo;
}

// Inserir palavra na BST - O(log n) médio, O(n) pior caso
No* inserir(No *raiz, const char *palavra, const char *definicao) {
    if (raiz == NULL) {
        return criarNo(palavra, definicao);
    }
    
    char palavraLower[MAX_PALAVRA];
    strcpy(palavraLower, palavra);
    toLowerCase(palavraLower);
    
    int cmp = strcmp(palavraLower, raiz->palavra);
    
    if (cmp < 0) {
        raiz->esquerda = inserir(raiz->esquerda, palavra, definicao);
    } else if (cmp > 0) {
        raiz->direita = inserir(raiz->direita, palavra, definicao);
    } else {
        // Palavra já existe, atualizar definição
        strcpy(raiz->definicao, definicao);
        printf("⚠️  Palavra '%s' já existia. Definição atualizada.\n", palavra);
    }
    
    return raiz;
}

// Buscar palavra - O(log n) médio
No* buscar(No *raiz, const char *palavra) {
    if (raiz == NULL) {
        return NULL;
    }
    
    char palavraLower[MAX_PALAVRA];
    strcpy(palavraLower, palavra);
    toLowerCase(palavraLower);
    
    int cmp = strcmp(palavraLower, raiz->palavra);
    
    if (cmp == 0) {
        raiz->frequencia++;  // Incrementa contador de buscas
        return raiz;
    } else if (cmp < 0) {
        return buscar(raiz->esquerda, palavra);
    } else {
        return buscar(raiz->direita, palavra);
    }
}

// Encontrar mínimo (mais à esquerda)
No* encontrarMinimo(No *raiz) {
    while (raiz->esquerda != NULL) {
        raiz = raiz->esquerda;
    }
    return raiz;
}

// Remover palavra - O(log n) médio
No* remover(No *raiz, const char *palavra) {
    if (raiz == NULL) {
        return NULL;
    }
    
    char palavraLower[MAX_PALAVRA];
    strcpy(palavraLower, palavra);
    toLowerCase(palavraLower);
    
    int cmp = strcmp(palavraLower, raiz->palavra);
    
    if (cmp < 0) {
        raiz->esquerda = remover(raiz->esquerda, palavra);
    } else if (cmp > 0) {
        raiz->direita = remover(raiz->direita, palavra);
    } else {
        // Encontrou o nó a remover
        
        // Caso 1: Nó folha (sem filhos)
        if (raiz->esquerda == NULL && raiz->direita == NULL) {
            free(raiz);
            return NULL;
        }
        
        // Caso 2: Apenas um filho
        else if (raiz->esquerda == NULL) {
            No *temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            No *temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        
        // Caso 3: Dois filhos
        else {
            No *sucessor = encontrarMinimo(raiz->direita);
            strcpy(raiz->palavra, sucessor->palavra);
            strcpy(raiz->definicao, sucessor->definicao);
            raiz->frequencia = sucessor->frequencia;
            raiz->direita = remover(raiz->direita, sucessor->palavra);
        }
    }
    
    return raiz;
}

// ============= PERCURSOS =============

// In-order: Esquerda -> Raiz -> Direita (ordem alfabética!)
void percorrerInOrder(No *raiz) {
    if (raiz != NULL) {
        percorrerInOrder(raiz->esquerda);
        printf("  • %s: %s\n", raiz->palavra, raiz->definicao);
        percorrerInOrder(raiz->direita);
    }
}

// Autocompletar: palavras que começam com prefixo
void autocompletar(No *raiz, const char *prefixo, int *count) {
    if (raiz == NULL) return;
    
    char prefixoLower[MAX_PALAVRA];
    strcpy(prefixoLower, prefixo);
    toLowerCase(prefixoLower);
    
    int prefixoLen = strlen(prefixoLower);
    
    // Verificar se palavra atual corresponde
    if (strncmp(raiz->palavra, prefixoLower, prefixoLen) == 0) {
        printf("  → %s: %s\n", raiz->palavra, raiz->definicao);
        (*count)++;
    }
    
    // Otimização: só vai para esquerda se o prefixo é menor
    if (strcmp(prefixoLower, raiz->palavra) <= 0) {
        autocompletar(raiz->esquerda, prefixo, count);
    }
    
    // Otimização: só vai para direita se o prefixo é maior ou igual
    if (strcmp(prefixoLower, raiz->palavra) >= 0 || 
        strncmp(raiz->palavra, prefixoLower, prefixoLen) == 0) {
        autocompletar(raiz->direita, prefixo, count);
    }
}

// Contar palavras com prefixo
int contarPrefixo(No *raiz, const char *prefixo) {
    if (raiz == NULL) return 0;
    
    char prefixoLower[MAX_PALAVRA];
    strcpy(prefixoLower, prefixo);
    toLowerCase(prefixoLower);
    
    int prefixoLen = strlen(prefixoLower);
    int count = 0;
    
    if (strncmp(raiz->palavra, prefixoLower, prefixoLen) == 0) {
        count = 1;
    }
    
    if (strcmp(prefixoLower, raiz->palavra) <= 0) {
        count += contarPrefixo(raiz->esquerda, prefixo);
    }
    
    if (strcmp(prefixoLower, raiz->palavra) >= 0 || 
        strncmp(raiz->palavra, prefixoLower, prefixoLen) == 0) {
        count += contarPrefixo(raiz->direita, prefixo);
    }
    
    return count;
}

// Palavras mais buscadas
void listarMaisBuscadas(No *raiz, int minFreq) {
    if (raiz != NULL) {
        listarMaisBuscadas(raiz->esquerda, minFreq);
        
        if (raiz->frequencia >= minFreq) {
            printf("  🔥 %s (%d buscas): %s\n", 
                   raiz->palavra, raiz->frequencia, raiz->definicao);
        }
        
        listarMaisBuscadas(raiz->direita, minFreq);
    }
}

// Calcular altura da árvore
int calcularAltura(No *raiz) {
    if (raiz == NULL) return 0;
    
    int alturaEsq = calcularAltura(raiz->esquerda);
    int alturaDir = calcularAltura(raiz->direita);
    
    return 1 + (alturaEsq > alturaDir ? alturaEsq : alturaDir);
}

// Contar total de nós
int contarNos(No *raiz) {
    if (raiz == NULL) return 0;
    return 1 + contarNos(raiz->esquerda) + contarNos(raiz->direita);
}

// Liberar memória
void destruirArvore(No *raiz) {
    if (raiz != NULL) {
        destruirArvore(raiz->esquerda);
        destruirArvore(raiz->direita);
        free(raiz);
    }
}

// ============= FUNÇÕES DO DICIONÁRIO =============

void inicializarDicionario(Dicionario *dict) {
    dict->raiz = NULL;
    dict->totalPalavras = 0;
}

void adicionarPalavra(Dicionario *dict, const char *palavra, const char *definicao) {
    int nosAntes = contarNos(dict->raiz);
    dict->raiz = inserir(dict->raiz, palavra, definicao);
    int nosDepois = contarNos(dict->raiz);
    
    if (nosDepois > nosAntes) {
        dict->totalPalavras++;
        printf("✓ Palavra '%s' adicionada\n", palavra);
    }
}

void buscarPalavra(Dicionario *dict, const char *palavra) {
    No *resultado = buscar(dict->raiz, palavra);
    
    if (resultado != NULL) {
        printf("\n📖 PALAVRA ENCONTRADA:\n");
        printf("  Palavra: %s\n", resultado->palavra);
        printf("  Definição: %s\n", resultado->definicao);
        printf("  Buscas: %d vez(es)\n", resultado->frequencia);
    } else {
        printf("\n❌ Palavra '%s' não encontrada no dicionário\n", palavra);
    }
}

void exibirEstatisticas(Dicionario *dict) {
    int altura = calcularAltura(dict->raiz);
    int nos = contarNos(dict->raiz);
    
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║     ESTATÍSTICAS DO DICIONÁRIO         ║\n");
    printf("╚════════════════════════════════════════╝\n");
    printf("  📚 Total de palavras: %d\n", nos);
    printf("  🌳 Altura da árvore: %d\n", altura);
    printf("  ⚖️  Balanceamento: %s\n", 
           (altura <= nos * 0.5) ? "Boa" : "Poderia melhorar");
}

// ============= MAIN =============

int main() {
    Dicionario dicionario;
    inicializarDicionario(&dicionario);
    
    printf("╔════════════════════════════════════════╗\n");
    printf("║   DICIONÁRIO COM AUTOCOMPLETAR         ║\n");
    printf("║   Usando Árvore Binária de Busca       ║\n");
    printf("╚════════════════════════════════════════╝\n\n");
    
    // Adicionar palavras
    printf("=== ADICIONANDO PALAVRAS ===\n\n");
    adicionarPalavra(&dicionario, "casa", "Lugar onde se mora");
    adicionarPalavra(&dicionario, "cachorro", "Animal de estimação, amigo do homem");
    adicionarPalavra(&dicionario, "carro", "Veículo automotor de quatro rodas");
    adicionarPalavra(&dicionario, "computador", "Máquina eletrônica para processar dados");
    adicionarPalavra(&dicionario, "caneta", "Instrumento para escrever");
    adicionarPalavra(&dicionario, "café", "Bebida estimulante de cor escura");
    adicionarPalavra(&dicionario, "livro", "Conjunto de páginas escritas");
    adicionarPalavra(&dicionario, "luz", "Radiação eletromagnética visível");
    adicionarPalavra(&dicionario, "mesa", "Móvel com superfície plana");
    adicionarPalavra(&dicionario, "python", "Linguagem de programação interpretada");
    
    exibirEstatisticas(&dicionario);
    
    // Buscar palavras
    printf("\n\n=== BUSCANDO PALAVRAS ===\n");
    buscarPalavra(&dicionario, "computador");
    buscarPalavra(&dicionario, "casa");
    buscarPalavra(&dicionario, "python");
    buscarPalavra(&dicionario, "inexistente");
    
    // Buscar novamente para incrementar frequência
    buscar(dicionario.raiz, "computador");
    buscar(dicionario.raiz, "python");
    buscar(dicionario.raiz, "python");
    
    // Autocompletar
    printf("\n\n=== AUTOCOMPLETAR 'ca' ===\n");
    int count = 0;
    autocompletar(dicionario.raiz, "ca", &count);
    printf("Total: %d palavra(s)\n", count);
    
    printf("\n=== AUTOCOMPLETAR 'comp' ===\n");
    count = 0;
    autocompletar(dicionario.raiz, "comp", &count);
    printf("Total: %d palavra(s)\n", count);
    
    // Contar palavras com prefixo
    printf("\n=== CONTAR PREFIXOS ===\n");
    printf("  Palavras começando com 'c': %d\n", 
           contarPrefixo(dicionario.raiz, "c"));
    printf("  Palavras começando com 'ca': %d\n", 
           contarPrefixo(dicionario.raiz, "ca"));
    printf("  Palavras começando com 'l': %d\n", 
           contarPrefixo(dicionario.raiz, "l"));
    
    // Palavras mais buscadas
    printf("\n=== PALAVRAS MAIS BUSCADAS (≥2) ===\n");
    listarMaisBuscadas(dicionario.raiz, 2);
    
    // Listar todas em ordem alfabética
    printf("\n=== DICIONÁRIO COMPLETO (Ordem Alfabética) ===\n");
    percorrerInOrder(dicionario.raiz);
    
    // Remover palavra
    printf("\n=== REMOVENDO PALAVRA ===\n");
    dicionario.raiz = remover(dicionario.raiz, "luz");
    printf("✓ Palavra 'luz' removida\n");
    
    exibirEstatisticas(&dicionario);
    
    // Liberar memória
    destruirArvore(dicionario.raiz);
    printf("\n✓ Dicionário destruído\n");
    
    return 0;
}
```

## 📊 Análise de Complexidade

| Operação | BST Balanceada | BST Desbalanceada | Array Ordenado | Array Não Ordenado |
|----------|----------------|-------------------|----------------|-------------------|
| Buscar | O(log n) ✅ | O(n) ❌ | O(log n)* | O(n) |
| Inserir | O(log n) ✅ | O(n) | O(n) | O(1) |
| Remover | O(log n) ✅ | O(n) | O(n) | O(n) |
| Min/Max | O(log n) | O(n) | O(1) | O(n) |
| In-order | O(n) | O(n) | O(n) | - |
| Autocompletar | O(log n + k)** ✅ | O(n) | O(log n + k)* | O(n) |

*Com busca binária  
**k = número de resultados

## 🎯 Conceitos de BST Aplicados

- ✅ **Propriedade BST** - Esquerda < Raiz < Direita
- ✅ **Inserção recursiva** - O(log n) em média
- ✅ **Busca eficiente** - Elimina metade a cada nível
- ✅ **In-order traversal** - Ordem alfabética automática
- ✅ **Remoção com 3 casos** - Folha, 1 filho, 2 filhos
- ✅ **Autocompletar otimizado** - Poda de ramos irrelevantes

## 💡 Quando Usar BST

| Cenário | Use BST | Use Outra Estrutura |
|---------|---------|---------------------|
| Busca + Inserções frequentes | ✅ | Hash (só busca) |
| Precisa ordem | ✅ | Hash não mantém ordem |
| Range queries | ✅ | Array necessita ordenação |
| Dados sempre ordenados | ❌ | Array + Binary Search |
| Autocompletar | ✅ | Trie é melhor |
| Balanceamento garantido | ❌ | Use AVL/Red-Black |

## 📝 Como Compilar e Executar

```bash
# Compilar
gcc PROBLEMA_PRATICO.c -o dicionario -Wall

# Executar
./dicionario
```

## 📚 Lições Aprendidas

1. **In-order = alfabética** - Percurso in-order em BST resulta em ordem
2. **Busca elimina metade** - Como busca binária, mas dinâmica
3. **3 casos de remoção** - Folha, 1 filho, 2 filhos (sucessor)
4. **Desbalanceamento** - BST pode virar lista (O(n))
5. **Autocompletar eficiente** - Poda ramos que não iniciam com prefixo
6. **Recursão natural** - Estrutura recursiva facilita operações

## 🔍 Melhorias e Variações

1. **AVL Tree** - Auto-balanceamento garante O(log n)
2. **Red-Black Tree** - Balanceamento com menos rotações
3. **Trie** - Melhor para autocompletar e prefixos
4. **B-Tree** - Para dados em disco (databases)
5. **Splay Tree** - Move itens frequentes para raiz
6. **Treap** - BST + Heap (randomizado)
