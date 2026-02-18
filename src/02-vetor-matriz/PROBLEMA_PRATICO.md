# Problema Prático: Sistema de Gerenciamento de Estoque

## 📋 Descrição do Problema

Uma pequena loja precisa controlar o estoque de produtos. O dono precisa:
- Adicionar novos produtos ao estoque
- Atualizar a quantidade de produtos
- Buscar produtos por ID
- Listar produtos com estoque baixo (menos de 10 unidades)

**Por que usar Vetores?**
- Acesso direto O(1) usando índice/ID do produto
- Estrutura contígua em memória = melhor cache
- Simples de implementar e manter

## 🔴 Problema: Implementação Ineficiente

```c
#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 100

typedef struct {
    int id;
    char nome[50];
    int quantidade;
    float preco;
} Produto;

// PROBLEMA: Busca linear toda vez - O(n)
int buscarProduto(Produto *estoque, int total, int id) {
    for (int i = 0; i < total; i++) {
        if (estoque[i].id == id) {
            return i;
        }
    }
    return -1;
}

// PROBLEMA: Não verifica limites do vetor
void adicionarProduto(Produto *estoque, int *total, Produto novo) {
    estoque[*total] = novo;  // Pode estourar o vetor!
    (*total)++;
}

// PROBLEMA: Não trata produto inexistente
void atualizarQuantidade(Produto *estoque, int total, int id, int novaQtd) {
    int pos = buscarProduto(estoque, total, id);
    estoque[pos].quantidade = novaQtd;  // Pode dar erro se pos == -1!
}

int main() {
    Produto estoque[MAX_PRODUTOS];
    int total = 0;
    
    // Adicionar produtos
    Produto p1 = {1, "Caneta Azul", 50, 1.50};
    Produto p2 = {2, "Caderno 100 Folhas", 20, 15.00};
    Produto p3 = {3, "Lapis HB", 5, 0.80};
    
    adicionarProduto(estoque, &total, p1);
    adicionarProduto(estoque, &total, p2);
    adicionarProduto(estoque, &total, p3);
    
    printf("Total de produtos: %d\n", total);
    
    // PROBLEMA: Não verifica se produto existe
    atualizarQuantidade(estoque, total, 999, 100);
    
    return 0;
}
```

### Problemas Identificados:
1. ❌ Busca sempre O(n) - ineficiente
2. ❌ Sem validação de limites do vetor
3. ❌ Sem tratamento de erros
4. ❌ Código não é modular

## ✅ Solução: Implementação Correta

```c
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PRODUTOS 100
#define ESTOQUE_MINIMO 10

typedef struct {
    int id;
    char nome[50];
    int quantidade;
    float preco;
} Produto;

typedef struct {
    Produto produtos[MAX_PRODUTOS];
    int total;
} Estoque;

// Inicializa o estoque
void inicializarEstoque(Estoque *est) {
    est->total = 0;
}

// Busca produto por ID - O(n) mas necessário sem ordenação
int buscarProduto(Estoque *est, int id) {
    for (int i = 0; i < est->total; i++) {
        if (est->produtos[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Adiciona produto com validação
bool adicionarProduto(Estoque *est, Produto novo) {
    // Validação: verifica se há espaço
    if (est->total >= MAX_PRODUTOS) {
        printf("ERRO: Estoque cheio!\n");
        return false;
    }
    
    // Validação: verifica se ID já existe
    if (buscarProduto(est, novo.id) != -1) {
        printf("ERRO: Produto com ID %d já existe!\n", novo.id);
        return false;
    }
    
    est->produtos[est->total] = novo;
    est->total++;
    printf("✓ Produto '%s' adicionado com sucesso!\n", novo.nome);
    return true;
}

// Atualiza quantidade com validação
bool atualizarQuantidade(Estoque *est, int id, int novaQtd) {
    int pos = buscarProduto(est, id);
    
    if (pos == -1) {
        printf("ERRO: Produto ID %d não encontrado!\n", id);
        return false;
    }
    
    if (novaQtd < 0) {
        printf("ERRO: Quantidade não pode ser negativa!\n");
        return false;
    }
    
    est->produtos[pos].quantidade = novaQtd;
    printf("✓ Quantidade do produto '%s' atualizada para %d\n", 
           est->produtos[pos].nome, novaQtd);
    return true;
}

// Lista produtos com estoque baixo
void listarEstoqueBaixo(Estoque *est) {
    printf("\n=== PRODUTOS COM ESTOQUE BAIXO ===\n");
    bool encontrou = false;
    
    for (int i = 0; i < est->total; i++) {
        if (est->produtos[i].quantidade < ESTOQUE_MINIMO) {
            printf("⚠️  ID: %d | %s | Qtd: %d | R$ %.2f\n",
                   est->produtos[i].id,
                   est->produtos[i].nome,
                   est->produtos[i].quantidade,
                   est->produtos[i].preco);
            encontrou = true;
        }
    }
    
    if (!encontrou) {
        printf("✓ Todos os produtos com estoque adequado!\n");
    }
}

// Exibe todos os produtos
void exibirEstoque(Estoque *est) {
    printf("\n=== ESTOQUE COMPLETO ===\n");
    printf("Total de produtos: %d\n\n", est->total);
    
    for (int i = 0; i < est->total; i++) {
        printf("ID: %d | %s | Qtd: %d | R$ %.2f\n",
               est->produtos[i].id,
               est->produtos[i].nome,
               est->produtos[i].quantidade,
               est->produtos[i].preco);
    }
}

int main() {
    Estoque estoque;
    inicializarEstoque(&estoque);
    
    printf("=== SISTEMA DE GERENCIAMENTO DE ESTOQUE ===\n\n");
    
    // Adicionar produtos
    Produto p1 = {1, "Caneta Azul", 50, 1.50};
    Produto p2 = {2, "Caderno 100 Folhas", 20, 15.00};
    Produto p3 = {3, "Lapis HB", 5, 0.80};
    Produto p4 = {4, "Borracha Branca", 8, 1.20};
    
    adicionarProduto(&estoque, p1);
    adicionarProduto(&estoque, p2);
    adicionarProduto(&estoque, p3);
    adicionarProduto(&estoque, p4);
    
    // Tentar adicionar produto duplicado
    printf("\nTentando adicionar produto duplicado:\n");
    Produto p5 = {2, "Caderno Duplicado", 30, 20.00};
    adicionarProduto(&estoque, p5);
    
    // Exibir estoque completo
    exibirEstoque(&estoque);
    
    // Atualizar quantidade
    printf("\nAtualizando quantidades:\n");
    atualizarQuantidade(&estoque, 1, 45);
    atualizarQuantidade(&estoque, 3, 3);
    
    // Tentar atualizar produto inexistente
    printf("\nTentando atualizar produto inexistente:\n");
    atualizarQuantidade(&estoque, 999, 100);
    
    // Listar produtos com estoque baixo
    listarEstoqueBaixo(&estoque);
    
    return 0;
}
```

## 📊 Análise de Complexidade

| Operação | Complexidade | Justificativa |
|----------|--------------|---------------|
| Adicionar produto | O(n) | Precisa verificar se ID já existe |
| Buscar produto | O(n) | Busca linear no vetor não ordenado |
| Atualizar quantidade | O(n) | Depende da busca |
| Listar estoque baixo | O(n) | Precisa percorrer todo o vetor |

## 💡 Melhorias Possíveis

1. **Ordenar por ID**: Permitiria busca binária O(log n)
2. **Usar Hash Table**: Busca O(1) em média
3. **Usar ID como índice direto**: Se IDs forem sequenciais (0, 1, 2...)

## 🎯 Conceitos Aplicados

- ✅ Estruturas de dados contíguas (vetor)
- ✅ Struct para agrupar dados relacionados
- ✅ Validação de limites
- ✅ Tratamento de erros
- ✅ Encapsulamento de dados
- ✅ Busca linear

## 📝 Como Compilar e Executar

```bash
# Compilar
gcc PROBLEMA_PRATICO.c -o estoque -Wall

# Executar
./estoque
```

## 📚 Lições Aprendidas

1. **Sempre valide limites de vetores** - Evita buffer overflow
2. **Trate erros adequadamente** - Retorne status de sucesso/falha
3. **Use tipos booleanos** - Código mais legível (stdbool.h)
4. **Encapsule dados em structs** - Melhor organização
5. **Documente complexidade** - Facilita otimizações futuras
