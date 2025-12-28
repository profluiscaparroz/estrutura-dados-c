# Vetores (Arrays)

## 📋 Visão Geral

Este diretório contém material completo sobre vetores (arrays unidimensionais) em C, incluindo exemplos práticos, exercícios e operações fundamentais.

## 📁 Estrutura do Diretório

### Subdiretórios

- **exemplo/** - Exemplos didáticos de uso de vetores
- **exercicios/** - Exercícios práticos para fixação
- **operacoes/** - Operações fundamentais com vetores (busca, inserção, remoção)

## 🎯 Conceitos Abordados

- Declaração e inicialização de vetores
- Alocação estática e dinâmica
- Passagem de vetores como parâmetros
- Manipulação de elementos
- Strings como vetores de caracteres
- Ponteiros e vetores
- Operações de busca, inserção e remoção

## 🔧 Compilação

Para compilar exemplos deste diretório:

```bash
gcc -Wall -Wextra -std=c99 -o programa arquivo.c
./programa
```

## 📖 Fundamentos de Vetores

### Declaração

```c
// Forma 1: Tamanho fixo
int numeros[10];

// Forma 2: Com inicialização
int numeros[5] = {1, 2, 3, 4, 5};

// Forma 3: Tamanho inferido
int numeros[] = {10, 20, 30};  // Compilador infere tamanho 3

// Forma 4: Inicialização parcial
int numeros[10] = {1, 2, 3};  // Resto inicializado com 0
```

### Alocação Dinâmica

```c
// Alocar
int *vetor = (int*)malloc(tamanho * sizeof(int));
if (vetor == NULL) {
    printf("Erro de alocação\n");
    return 1;
}

// Usar
for (int i = 0; i < tamanho; i++) {
    vetor[i] = i * 10;
}

// Liberar
free(vetor);
```

### Passagem como Parâmetro

```c
// Forma 1: Array notation
void processar(int vetor[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        vetor[i] *= 2;
    }
}

// Forma 2: Pointer notation (equivalente)
void processar(int *vetor, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        vetor[i] *= 2;
    }
}
```

## 💡 Operações Básicas

### Inicialização

```c
// Zerar vetor
for (int i = 0; i < tamanho; i++) {
    vetor[i] = 0;
}

// Preencher com valor
for (int i = 0; i < tamanho; i++) {
    vetor[i] = valor;
}
```

### Impressão

```c
printf("Vetor: [");
for (int i = 0; i < tamanho; i++) {
    printf("%d", vetor[i]);
    if (i < tamanho - 1) printf(", ");
}
printf("]\n");
```

### Cópia

```c
// Método 1: Loop
for (int i = 0; i < tamanho; i++) {
    destino[i] = origem[i];
}

// Método 2: memcpy
memcpy(destino, origem, tamanho * sizeof(int));
```

### Busca

```c
// Busca linear
int buscar(int vetor[], int tamanho, int valor) {
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i] == valor) {
            return i;  // Retorna índice
        }
    }
    return -1;  // Não encontrado
}
```

## 📚 Conteúdo dos Subdiretórios

### exemplo/
Contém exemplos progressivos desde o básico até conceitos avançados:
- Alocação dinâmica
- Manipulação de elementos
- Passagem por parâmetro
- Strings e vetores

### exercicios/
Exercícios práticos para consolidar conhecimento:
- Operações básicas
- Algoritmos de manipulação
- Resolução de problemas

### operacoes/
Implementações de operações fundamentais:
- Busca de elementos
- Inserção em posições
- Remoção de elementos
- Reversão de vetores
- Varredura e processamento

## ⚠️ Cuidados Importantes

1. **Limites**: Sempre verifique se o índice está dentro dos limites (0 ≤ i < tamanho)
2. **Inicialização**: Vetores locais não são inicializados automaticamente
3. **Tamanho**: C não armazena o tamanho do vetor, você deve gerenciá-lo
4. **Memória**: Libere memória alocada com `malloc` usando `free`
5. **Overflow**: Buffer overflow é um erro comum e perigoso

## 🔍 Vetores e Ponteiros

```c
int vetor[5] = {1, 2, 3, 4, 5};

// Estas expressões são equivalentes:
vetor[i]
*(vetor + i)

// Nome do vetor é um ponteiro para o primeiro elemento
int *ptr = vetor;  // Equivalente a: int *ptr = &vetor[0];
```

## 📊 Complexidade de Operações

| Operação | Complexidade |
|----------|-------------|
| Acesso por índice | O(1) |
| Busca linear | O(n) |
| Busca binária (ordenado) | O(log n) |
| Inserção no início | O(n) |
| Inserção no fim | O(1) |
| Remoção no início | O(n) |
| Remoção no fim | O(1) |

## 🚀 Navegação

Para aprender sobre vetores de forma progressiva:

1. Comece com **exemplo/** para entender os fundamentos
2. Pratique com **exercicios/** para fixar o conhecimento
3. Estude **operacoes/** para ver implementações completas

---

**Repositório**: https://github.com/profluiscaparroz/estrutura-dados-c
