# Operações com Vetores

## 📋 Visão Geral

Este diretório contém implementações completas de operações fundamentais com vetores, incluindo busca, inserção, remoção, reversão e manipulação de strings.

## 📚 Operações Implementadas

### Operações de Busca

**01procurarItem.c** - Busca de elementos no vetor  
**exemploProcurarItem.c** - Exemplo didático de busca  
**procurarPalavraRegex.c** - Busca de padrões usando expressões regulares  
**procurarPalavraSemStringH.c** - Busca de substring sem usar `string.h`  
**procurarPalavraStringH.c** - Busca de substring usando `string.h`

**Conceitos:**
- Busca linear O(n)
- Busca de substrings
- Pattern matching
- Comparação de strings

### Operações de Inserção

**03insertItem.c** - Inserção de elementos em posições específicas  
**exemploInserirUltimaPosicao.c** - Inserção no final do vetor

**Conceitos:**
- Inserção em posição arbitrária
- Deslocamento de elementos
- Gerenciamento de capacidade
- Inserção eficiente

### Operações de Remoção

**02deletarItem.c** - Remoção de elementos  
**exemploDeletarItemVetor.c** - Exemplo de deleção

**Conceitos:**
- Remoção por índice
- Remoção por valor
- Compactação do vetor
- Atualização de tamanho

### Operações de Transformação

**03reverterVetor.c** - Reversão de vetores  
**exemploReverterVetor.c** - Exemplo de reversão  
**exemploVarredura.c** - Varredura e processamento

**Conceitos:**
- Inversão in-place
- Troca de elementos
- Varredura completa
- Processamento de dados

## 🔧 Compilação

### Compilar Individual

```bash
gcc -Wall -Wextra -std=c99 -o busca 01procurarItem.c
gcc -Wall -Wextra -std=c99 -o insere 03insertItem.c
gcc -Wall -Wextra -std=c99 -o remove 02deletarItem.c
gcc -Wall -Wextra -std=c99 -o reverte 03reverterVetor.c
```

### Para exemplos com regex

```bash
gcc -Wall -Wextra -std=c99 -o regex procurarPalavraRegex.c
```

## 📖 Operações Detalhadas

### 1. Busca Linear

```c
int buscar(int vetor[], int tamanho, int chave) {
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i] == chave) {
            return i;  // Retorna índice do elemento
        }
    }
    return -1;  // Não encontrado
}
```

**Complexidade:** O(n)  
**Uso:** Vetores não ordenados

### 2. Inserção em Posição

```c
int inserir(int vetor[], int *tamanho, int capacidade, int posicao, int valor) {
    // Verificar se há espaço
    if (*tamanho >= capacidade) {
        return 0;  // Falha
    }
    
    // Verificar posição válida
    if (posicao < 0 || posicao > *tamanho) {
        return 0;
    }
    
    // Deslocar elementos para a direita
    for (int i = *tamanho; i > posicao; i--) {
        vetor[i] = vetor[i - 1];
    }
    
    // Inserir novo elemento
    vetor[posicao] = valor;
    (*tamanho)++;
    
    return 1;  // Sucesso
}
```

**Complexidade:** O(n)  
**Pior caso:** Inserção no início

### 3. Remoção de Elemento

```c
int remover(int vetor[], int *tamanho, int posicao) {
    // Verificar posição válida
    if (posicao < 0 || posicao >= *tamanho) {
        return 0;  // Falha
    }
    
    // Deslocar elementos para a esquerda
    for (int i = posicao; i < *tamanho - 1; i++) {
        vetor[i] = vetor[i + 1];
    }
    
    (*tamanho)--;
    
    return 1;  // Sucesso
}
```

**Complexidade:** O(n)  
**Pior caso:** Remoção no início

### 4. Reversão de Vetor

```c
void reverter(int vetor[], int tamanho) {
    int inicio = 0;
    int fim = tamanho - 1;
    
    while (inicio < fim) {
        // Trocar elementos
        int temp = vetor[inicio];
        vetor[inicio] = vetor[fim];
        vetor[fim] = temp;
        
        inicio++;
        fim--;
    }
}
```

**Complexidade:** O(n)  
**Espaço:** O(1) - in-place

### 5. Busca de Substring

```c
// Sem usar string.h
int buscar_substring(const char *texto, const char *padrao) {
    int len_texto = 0, len_padrao = 0;
    
    // Calcular comprimentos
    while (texto[len_texto] != '\0') len_texto++;
    while (padrao[len_padrao] != '\0') len_padrao++;
    
    // Buscar padrão
    for (int i = 0; i <= len_texto - len_padrao; i++) {
        int j;
        for (j = 0; j < len_padrao; j++) {
            if (texto[i + j] != padrao[j]) {
                break;
            }
        }
        if (j == len_padrao) {
            return i;  // Padrão encontrado
        }
    }
    
    return -1;  // Não encontrado
}
```

**Complexidade:** O(n × m) onde n = len(texto), m = len(padrao)

## 📊 Análise de Complexidade

| Operação | Melhor Caso | Caso Médio | Pior Caso | Espaço |
|----------|------------|------------|-----------|--------|
| Busca Linear | O(1) | O(n) | O(n) | O(1) |
| Inserção Início | O(n) | O(n) | O(n) | O(1) |
| Inserção Fim | O(1) | O(1) | O(1) | O(1) |
| Remoção Início | O(n) | O(n) | O(n) | O(1) |
| Remoção Fim | O(1) | O(1) | O(1) | O(1) |
| Reversão | O(n) | O(n) | O(n) | O(1) |
| Busca Substring | O(m) | O(n×m) | O(n×m) | O(1) |

## 💡 Padrões de Uso

### Manter Vetor Ordenado

```c
// Inserir mantendo ordem
void inserir_ordenado(int vetor[], int *tamanho, int valor) {
    int i = *tamanho - 1;
    
    // Encontrar posição
    while (i >= 0 && vetor[i] > valor) {
        vetor[i + 1] = vetor[i];
        i--;
    }
    
    vetor[i + 1] = valor;
    (*tamanho)++;
}
```

### Remover Duplicatas

```c
int remover_duplicatas(int vetor[], int tamanho) {
    if (tamanho <= 1) return tamanho;
    
    int novo_tamanho = 1;
    
    for (int i = 1; i < tamanho; i++) {
        int duplicado = 0;
        for (int j = 0; j < novo_tamanho; j++) {
            if (vetor[i] == vetor[j]) {
                duplicado = 1;
                break;
            }
        }
        if (!duplicado) {
            vetor[novo_tamanho] = vetor[i];
            novo_tamanho++;
        }
    }
    
    return novo_tamanho;
}
```

## ⚠️ Cuidados Importantes

1. **Verificar Limites**: Sempre valide índices e capacidade
2. **Atualizar Tamanho**: Mantenha o tamanho atualizado após operações
3. **Ordem de Deslocamento**: 
   - Inserção: deslocar da direita para esquerda
   - Remoção: deslocar da esquerda para direita
4. **Validação de Entrada**: Verifique parâmetros antes de processar
5. **Gerenciamento de Memória**: Para vetores dinâmicos, considere realocação

## 🚀 Otimizações

### Busca em Vetor Ordenado

```c
// Busca binária - O(log n)
int busca_binaria(int vetor[], int tamanho, int chave) {
    int esquerda = 0;
    int direita = tamanho - 1;
    
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        
        if (vetor[meio] == chave) {
            return meio;
        }
        
        if (vetor[meio] < chave) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    
    return -1;
}
```

## 📚 Recursos Adicionais

- [Search Algorithms](https://en.wikipedia.org/wiki/Search_algorithm)
- [Array Manipulation](https://en.cppreference.com/w/c/algorithm)
- [String Search](https://en.wikipedia.org/wiki/String-searching_algorithm)

---

**Repositório**: https://github.com/profluiscaparroz/estrutura-dados-c
