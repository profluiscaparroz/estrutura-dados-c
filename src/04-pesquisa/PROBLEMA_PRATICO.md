# Problema Prático: Sistema de Busca de Produtos em E-commerce

## 📋 Descrição do Problema

Um e-commerce precisa implementar sistema de busca eficiente:
- Buscar produtos por código (ID numérico)
- Buscar produtos por nome (busca textual)
- Autocompletar durante digitação
- Filtrar por faixa de preço
- Sistema deve ser rápido mesmo com milhares de produtos

**Por que usar Algoritmos de Busca?**
- Busca Linear: O(n) - simples mas lenta
- Busca Binária: O(log n) - rápida mas precisa ordenação
- Busca Interpolada: O(log log n) - ótima para dados uniformes

## 🔴 Problema: Sempre Usar Busca Linear

```c
#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 10000

typedef struct {
    int id;
    char nome[100];
    float preco;
    int estoque;
} Produto;

// PROBLEMA: Sempre O(n) mesmo com IDs ordenados
Produto* buscarPorId(Produto *produtos, int total, int id) {
    for (int i = 0; i < total; i++) {
        if (produtos[i].id == id) {
            return &produtos[i];
        }
    }
    return NULL;
}

// PROBLEMA: Busca case-sensitive e ineficiente
void buscarPorNome(Produto *produtos, int total, const char *termo) {
    printf("Resultados para '%s':\n", termo);
    for (int i = 0; i < total; i++) {
        if (strstr(produtos[i].nome, termo) != NULL) {
            printf("- %s (R$ %.2f)\n", produtos[i].nome, produtos[i].preco);
        }
    }
}

int main() {
    Produto catalogo[MAX_PRODUTOS];
    int total = 5;
    
    // Simular produtos (IDs ordenados!)
    catalogo[0] = (Produto){101, "Mouse Gamer RGB", 89.90, 50};
    catalogo[1] = (Produto){205, "Teclado Mecânico", 299.00, 30};
    catalogo[2] = (Produto){308, "Monitor 24 LED", 699.00, 15};
    catalogo[3] = (Produto){412, "Webcam Full HD", 189.90, 25};
    catalogo[4] = (Produto){520, "Headset Wireless", 249.00, 40};
    
    // Buscar produto
    Produto *p = buscarPorId(catalogo, total, 308);
    if (p) {
        printf("Encontrado: %s\n", p->nome);
    }
    
    // PROBLEMA: Desperdiça a ordenação dos IDs!
    // Poderia usar busca binária O(log n)
    
    return 0;
}
```

### Problemas Identificados:
1. ❌ Busca linear O(n) mesmo com dados ordenados
2. ❌ Busca textual case-sensitive
3. ❌ Não aproveita estrutura dos dados
4. ❌ Sem otimização para buscas frequentes

## ✅ Solução: Implementação Otimizada com Múltiplas Estratégias

```c
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_PRODUTOS 10000
#define MAX_RESULTADOS 50

typedef struct {
    int id;
    char nome[100];
    float preco;
    int estoque;
} Produto;

// Converte string para minúscula (para busca case-insensitive)
void toLowerCase(char *str, char *dest) {
    int i = 0;
    while (str[i]) {
        dest[i] = tolower(str[i]);
        i++;
    }
    dest[i] = '\0';
}

// ============= BUSCA BINÁRIA - O(log n) =============
// Requer: Produtos ordenados por ID
Produto* buscaBinariaPorId(Produto *produtos, int total, int id) {
    int left = 0;
    int right = total - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (produtos[mid].id == id) {
            return &produtos[mid];
        }
        
        if (produtos[mid].id < id) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return NULL;
}

// ============= BUSCA INTERPOLADA - O(log log n) =============
// Melhor que binária para dados uniformemente distribuídos
Produto* buscaInterpoladaPorId(Produto *produtos, int total, int id) {
    int low = 0;
    int high = total - 1;
    
    while (low <= high && id >= produtos[low].id && id <= produtos[high].id) {
        // Se apenas um elemento
        if (low == high) {
            if (produtos[low].id == id) return &produtos[low];
            return NULL;
        }
        
        // Verificar se IDs são iguais (evitar divisão por zero)
        if (produtos[high].id == produtos[low].id) {
            if (produtos[low].id == id) return &produtos[low];
            return NULL;
        }
        
        // Estimativa da posição usando interpolação
        int pos = low + ((double)(high - low) / 
                        (produtos[high].id - produtos[low].id)) * 
                        (id - produtos[low].id);
        
        if (produtos[pos].id == id) {
            return &produtos[pos];
        }
        
        if (produtos[pos].id < id) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }
    
    return NULL;
}

// ============= BUSCA LINEAR COM OTIMIZAÇÕES =============
// Para dados não ordenados ou busca por nome
int buscaLinearPorNome(Produto *produtos, int total, const char *termo, 
                       Produto **resultados) {
    char termoBusca[100];
    toLowerCase((char*)termo, termoBusca);
    
    int count = 0;
    
    for (int i = 0; i < total && count < MAX_RESULTADOS; i++) {
        char nomeMinusculo[100];
        toLowerCase(produtos[i].nome, nomeMinusculo);
        
        if (strstr(nomeMinusculo, termoBusca) != NULL) {
            resultados[count++] = &produtos[i];
        }
    }
    
    return count;
}

// ============= BUSCA POR FAIXA DE PREÇO =============
// Otimizada: para em early exit quando possível
int buscaPorFaixaPreco(Produto *produtos, int total, float min, float max,
                       Produto **resultados) {
    int count = 0;
    
    for (int i = 0; i < total && count < MAX_RESULTADOS; i++) {
        if (produtos[i].preco >= min && produtos[i].preco <= max) {
            resultados[count++] = &produtos[i];
        }
    }
    
    return count;
}

// ============= AUTOCOMPLETAR =============
// Retorna produtos que começam com o termo
int autocompletar(Produto *produtos, int total, const char *prefixo,
                  Produto **resultados) {
    char prefixoMinusculo[100];
    toLowerCase((char*)prefixo, prefixoMinusculo);
    
    int count = 0;
    int prefixoLen = strlen(prefixoMinusculo);
    
    for (int i = 0; i < total && count < MAX_RESULTADOS; i++) {
        char nomeMinusculo[100];
        toLowerCase(produtos[i].nome, nomeMinusculo);
        
        if (strncmp(nomeMinusculo, prefixoMinusculo, prefixoLen) == 0) {
            resultados[count++] = &produtos[i];
        }
    }
    
    return count;
}

// Função auxiliar para trocar produtos (para ordenação)
void trocarProdutos(Produto *a, Produto *b) {
    Produto temp = *a;
    *a = *b;
    *b = temp;
}

// Ordenar produtos por ID (Quick Sort simplificado)
void ordenarPorId(Produto *produtos, int low, int high) {
    if (low < high) {
        int pivot = produtos[high].id;
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            if (produtos[j].id <= pivot) {
                i++;
                trocarProdutos(&produtos[i], &produtos[j]);
            }
        }
        trocarProdutos(&produtos[i + 1], &produtos[high]);
        int pi = i + 1;
        
        ordenarPorId(produtos, low, pi - 1);
        ordenarPorId(produtos, pi + 1, high);
    }
}

// Exibe produto formatado
void exibirProduto(Produto *p) {
    printf("  ID: %d | %s | R$ %.2f | Estoque: %d\n",
           p->id, p->nome, p->preco, p->estoque);
}

// Testa performance das buscas
void testarPerformance(Produto *catalogo, int total) {
    printf("\n=== TESTE DE PERFORMANCE ===\n");
    
    int idBuscar = 5050;  // ID no meio do catálogo
    
    // Simular múltiplas buscas para medir desempenho
    printf("\nBuscando ID %d em catálogo de %d produtos:\n", idBuscar, total);
    
    // Busca Linear (simulação)
    printf("• Busca Linear:      ~%d comparações (O(n))\n", total/2);
    
    // Busca Binária (simulação)
    int compBinaria = 0;
    int temp = total;
    while (temp > 1) {
        temp /= 2;
        compBinaria++;
    }
    printf("• Busca Binária:     ~%d comparações (O(log n))\n", compBinaria);
    
    // Busca Interpolada (simulação)
    printf("• Busca Interpolada: ~%d comparações (O(log log n))\n", 
           compBinaria / 2);
}

int main() {
    Produto catalogo[100];
    int total = 0;
    
    printf("=== SISTEMA DE BUSCA DE PRODUTOS ===\n\n");
    
    // Simular catálogo de produtos (IDs em ordem)
    char *nomes[] = {
        "Mouse Gamer RGB", "Teclado Mecânico", "Monitor 24 LED",
        "Webcam Full HD", "Headset Wireless", "Mousepad XL",
        "Gabinete ATX", "Fonte 500W", "Memória RAM 16GB",
        "SSD 480GB", "Mouse Pad Gamer", "Teclado Gamer RGB"
    };
    
    float precos[] = {89.90, 299.00, 699.00, 189.90, 249.00, 49.90,
                      199.00, 189.00, 349.00, 279.00, 79.90, 399.00};
    
    // Gerar produtos com IDs não uniformes
    int ids[] = {101, 205, 308, 412, 520, 625, 730, 835, 940, 1045, 1150, 1255};
    
    for (int i = 0; i < 12; i++) {
        catalogo[i].id = ids[i];
        strcpy(catalogo[i].nome, nomes[i]);
        catalogo[i].preco = precos[i];
        catalogo[i].estoque = 10 + (i * 5);
        total++;
    }
    
    // Garantir ordenação por ID
    ordenarPorId(catalogo, 0, total - 1);
    
    printf("Catálogo carregado: %d produtos\n", total);
    
    // ===== TESTE 1: BUSCA BINÁRIA POR ID =====
    printf("\n--- TESTE 1: Busca Binária por ID ---\n");
    int idBusca = 520;
    Produto *p = buscaBinariaPorId(catalogo, total, idBusca);
    if (p) {
        printf("✓ Produto ID %d encontrado:\n", idBusca);
        exibirProduto(p);
    } else {
        printf("✗ Produto não encontrado\n");
    }
    
    // ===== TESTE 2: BUSCA INTERPOLADA =====
    printf("\n--- TESTE 2: Busca Interpolada por ID ---\n");
    idBusca = 940;
    p = buscaInterpoladaPorId(catalogo, total, idBusca);
    if (p) {
        printf("✓ Produto ID %d encontrado:\n", idBusca);
        exibirProduto(p);
    }
    
    // ===== TESTE 3: BUSCA POR NOME =====
    printf("\n--- TESTE 3: Busca por Nome (case-insensitive) ---\n");
    Produto *resultados[MAX_RESULTADOS];
    int found = buscaLinearPorNome(catalogo, total, "gamer", resultados);
    printf("Encontrados %d produtos com 'gamer':\n", found);
    for (int i = 0; i < found; i++) {
        exibirProduto(resultados[i]);
    }
    
    // ===== TESTE 4: AUTOCOMPLETAR =====
    printf("\n--- TESTE 4: Autocompletar 'tec' ---\n");
    found = autocompletar(catalogo, total, "tec", resultados);
    printf("Sugestões (%d):\n", found);
    for (int i = 0; i < found; i++) {
        printf("  → %s\n", resultados[i]->nome);
    }
    
    // ===== TESTE 5: BUSCA POR FAIXA DE PREÇO =====
    printf("\n--- TESTE 5: Produtos entre R$ 150 e R$ 300 ---\n");
    found = buscaPorFaixaPreco(catalogo, total, 150.0, 300.0, resultados);
    printf("Encontrados %d produtos:\n", found);
    for (int i = 0; i < found; i++) {
        exibirProduto(resultados[i]);
    }
    
    // ===== TESTE 6: PRODUTO INEXISTENTE =====
    printf("\n--- TESTE 6: Buscar produto inexistente ---\n");
    p = buscaBinariaPorId(catalogo, total, 9999);
    if (p == NULL) {
        printf("✓ Corretamente retornou NULL para ID inexistente\n");
    }
    
    // Teste de performance (simulado)
    testarPerformance(catalogo, 10000);
    
    return 0;
}
```

## 📊 Análise de Complexidade

| Algoritmo | Pré-requisito | Melhor | Médio | Pior | Uso de Memória |
|-----------|---------------|--------|-------|------|----------------|
| **Linear** | Nenhum | O(1) | O(n) | O(n) | O(1) |
| **Binária** | Dados ordenados | O(1) | O(log n) | O(log n) | O(1) |
| **Interpolada** | Ordenados + uniformes | O(1) | O(log log n) | O(n) | O(1) |

## 💡 Quando Usar Cada Busca

| Cenário | Algoritmo | Justificativa |
|---------|-----------|---------------|
| Dados não ordenados | Linear | Única opção |
| Poucos elementos (< 50) | Linear | Simples e rápido o suficiente |
| Dados ordenados (geral) | Binária | Sempre O(log n) |
| IDs sequenciais uniformes | Interpolada | Melhor performance |
| Busca textual/substring | Linear | Precisa verificar conteúdo |
| Múltiplos critérios | Linear | Mais flexível |

## 🎯 Conceitos Aplicados

- ✅ Busca Binária com array ordenado
- ✅ Busca Interpolada para otimização
- ✅ Busca case-insensitive com toLowerCase
- ✅ Autocompletar com strncmp
- ✅ Busca por range (faixa de valores)
- ✅ Comparação de performance entre algoritmos

## 📝 Como Compilar e Executar

```bash
# Compilar
gcc PROBLEMA_PRATICO.c -o busca -Wall -lm

# Executar
./busca
```

## 🧪 Exemplo de Saída

```
=== SISTEMA DE BUSCA DE PRODUTOS ===

Catálogo carregado: 12 produtos

--- TESTE 1: Busca Binária por ID ---
✓ Produto ID 520 encontrado:
  ID: 520 | Headset Wireless | R$ 249.00 | Estoque: 30

--- TESTE 3: Busca por Nome (case-insensitive) ---
Encontrados 3 produtos com 'gamer':
  ID: 101 | Mouse Gamer RGB | R$ 89.90 | Estoque: 10
  ID: 1150 | Mouse Pad Gamer | R$ 79.90 | Estoque: 60
  ID: 1255 | Teclado Gamer RGB | R$ 399.00 | Estoque: 65

--- TESTE 4: Autocompletar 'tec' ---
Sugestões (2):
  → Teclado Mecânico
  → Teclado Gamer RGB

=== TESTE DE PERFORMANCE ===
Buscando ID 5050 em catálogo de 10000 produtos:
• Busca Linear:      ~5000 comparações (O(n))
• Busca Binária:     ~13 comparações (O(log n))
• Busca Interpolada: ~6 comparações (O(log log n))
```

## 📚 Lições Aprendidas

1. **Escolha baseada em dados** - Busca binária precisa ordenação
2. **Interpolação para uniformes** - Melhor que binária com IDs sequenciais
3. **Case-insensitive** - Melhora experiência do usuário
4. **Early exit** - Pare quando encontrar ou limite alcançado
5. **Trade-offs** - Ordenar custa O(n log n) mas busca fica O(log n)
6. **Performance importa** - 5000 vs 13 comparações é significativo!

## 🔍 Otimizações Avançadas

Para sistemas maiores, considere:
- **Hash Tables**: O(1) para busca exata por ID
- **Tries**: Autocompletar muito eficiente
- **Índices invertidos**: Para busca textual (full-text search)
- **B-Trees**: Para dados em disco (databases)
