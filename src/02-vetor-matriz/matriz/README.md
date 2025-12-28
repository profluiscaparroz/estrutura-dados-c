# Exemplos de Matrizes

## 📋 Visão Geral

Este diretório contém exemplos práticos de trabalho com matrizes (arrays bidimensionais) em C, demonstrando diferentes técnicas de manipulação, alocação de memória e operações.

## 📚 Exemplos Incluídos

- **exemplo01.c** - Introdução básica a matrizes
- **exemplo02.c** - Operações fundamentais com matrizes
- **exemplo03.c** - Manipulação intermediária de matrizes
- **exemplo04.c** - Técnicas avançadas
- **exemplo05_operacoes.c** - Operações matemáticas (soma, multiplicação)
- **exemplo06_performance.c** - Análise de performance e otimização
- **exemplo4_colunas_diferentes.c** - Matrizes irregulares (jagged arrays)
- **exemploAvancado.c** - Exemplos avançados de matrizes
- **exemploExibeEnderecoPonteiro.c** - Demonstração de endereços de memória
- **exemploExibeEnderecoPonteiroContinuo.c** - Análise de layout de memória
- **exemploMatrizDinamica.c** - Alocação dinâmica de matrizes
- **exemploMatrizSimples.c** - Exemplo simples e didático
- **exemploMatrizSimples2.c** - Variação do exemplo simples
- **exemploOperacoesMatrizes.c** - Operações completas entre matrizes
- **exemploPonteiroGenerico.c** - Uso de ponteiros genéricos (void*)

## 🎯 Conceitos Trabalhados

- Declaração e inicialização de matrizes
- Alocação estática vs dinâmica
- Acesso e manipulação de elementos
- Operações matemáticas (soma, multiplicação, transposição)
- Ponteiros e matrizes
- Layout de memória
- Otimização de performance
- Matrizes irregulares

## 🔧 Compilação

```bash
# Compilar qualquer exemplo
gcc -Wall -Wextra -std=c99 -o matriz exemploMatrizSimples.c
./matriz

# Com otimizações
gcc -Wall -Wextra -std=c99 -O2 -o matriz exemplo06_performance.c
./matriz
```

## 📖 Formas de Declarar Matrizes

### 1. Alocação Estática

```c
// Forma 1: Tamanho fixo
int matriz[3][4];  // 3 linhas, 4 colunas

// Forma 2: Com inicialização
int matriz[3][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}
};

// Forma 3: Tamanho inferido
int matriz[][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8}
};  // Compilador infere 2 linhas
```

### 2. Alocação Dinâmica

```c
// Método 1: Array de ponteiros
int **matriz = (int**)malloc(linhas * sizeof(int*));
for (int i = 0; i < linhas; i++) {
    matriz[i] = (int*)malloc(colunas * sizeof(int));
}

// Método 2: Bloco contíguo (mais eficiente)
int *matriz = (int*)malloc(linhas * colunas * sizeof(int));
// Acesso: matriz[i * colunas + j]

// Liberar memória
for (int i = 0; i < linhas; i++) {
    free(matriz[i]);  // Método 1
}
free(matriz);
```

## 💡 Operações Comuns

### Inicialização

```c
for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
        matriz[i][j] = 0;  // Zerar matriz
    }
}
```

### Impressão

```c
for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
        printf("%4d ", matriz[i][j]);
    }
    printf("\n");
}
```

### Soma de Matrizes

```c
for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
        C[i][j] = A[i][j] + B[i][j];
    }
}
```

### Multiplicação de Matrizes

```c
// A (m x n) * B (n x p) = C (m x p)
for (int i = 0; i < m; i++) {
    for (int j = 0; j < p; j++) {
        C[i][j] = 0;
        for (int k = 0; k < n; k++) {
            C[i][j] += A[i][k] * B[k][j];
        }
    }
}
```

### Transposição

```c
for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
        T[j][i] = M[i][j];
    }
}
```

## ⚡ Considerações de Performance

1. **Cache Locality**: Acesse elementos sequencialmente
2. **Layout de Memória**: Prefira alocação contígua
3. **Loop Order**: Otimize ordem dos laços (row-major order)

```c
// Mais eficiente (row-major)
for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
        processar(matriz[i][j]);
    }
}

// Menos eficiente (column-major)
for (int j = 0; j < colunas; j++) {
    for (int i = 0; i < linhas; i++) {
        processar(matriz[i][j]);
    }
}
```

## 🔍 Acesso via Ponteiros

```c
int matriz[3][4];

// Acesso tradicional
int valor = matriz[i][j];

// Acesso via ponteiro
int valor = *(*(matriz + i) + j);

// Ou
int valor = *(&matriz[0][0] + i * 4 + j);
```

## ⚠️ Cuidados

1. **Limites**: Sempre verifique índices (0 ≤ i < linhas, 0 ≤ j < colunas)
2. **Memória**: Libere memória alocada dinamicamente
3. **Dimensões**: Em funções, passe as dimensões explicitamente
4. **Overflow**: Cuidado com operações que podem exceder limites

## 📚 Recursos Adicionais

- [C Arrays](https://en.cppreference.com/w/c/language/array)
- [Dynamic Memory Allocation](https://en.cppreference.com/w/c/memory)
- [Matrix Operations](https://en.wikipedia.org/wiki/Matrix_(mathematics))

---

**Repositório**: https://github.com/profluiscaparroz/estrutura-dados-c
