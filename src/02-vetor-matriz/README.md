# Vetores e Matrizes em C

Este diretório contém exemplos completos e documentação sobre **vetores (arrays)** e **matrizes** em C, incluindo manipulação de strings como vetores de caracteres.

## 📚 Conteúdo

### 📁 Estrutura de Arquivos
- **`vetor/`** - Exemplos e exercícios com vetores unidimensionais
- **`matriz/`** - Exemplos e exercícios com matrizes (vetores bidimensionais)
- **`questoes-academicas.md`** - Questões acadêmicas com respostas detalhadas
- **`README-exemplos-avancados.md`** - Guia de navegação dos exemplos avançados
- **`analise-performance.md`** - Análise de performance e otimizações

---

## 🎯 Conceitos Fundamentais

### Vetores (Arrays)
Um **vetor** é uma estrutura de dados que armazena elementos do mesmo tipo em posições consecutivas da memória. Em C, vetores são a base para muitas outras estruturas de dados.

#### Características dos Vetores:
- **Acesso direto:** O(1) para acessar qualquer elemento
- **Memória contígua:** Elementos armazenados sequencialmente
- **Índice baseado em zero:** Primeiro elemento no índice 0
- **Tamanho fixo:** Determinado na declaração (estático) ou na alocação (dinâmico)

#### Declaração e Inicialização:
```c
// Declaração com tamanho fixo
int numeros[5];

// Declaração com inicialização
int numeros[5] = {10, 20, 30, 40, 50};

// Tamanho inferido pelo compilador
int numeros[] = {10, 20, 30, 40, 50}; // tamanho = 5

// Alocação dinâmica
int *numeros = malloc(5 * sizeof(int));
```

---

## 🔤 Strings como Vetores de Caracteres

**Strings em C são vetores de caracteres terminados com '\0'**. Esta é uma das aplicações mais importantes de vetores na programação C.

### Conceitos Fundamentais sobre Strings

#### 1. Representação de Strings
```c
// String literal
char nome[] = "Carlos";  // Array: ['C','a','r','l','o','s','\0']

// Declaração com tamanho específico
char nome[20] = "Carlos"; // 19 caracteres úteis + '\0'

// Ponteiro para string literal (somente leitura)
char *nome = "Carlos";

// Array de caracteres inicializado manualmente
char nome[] = {'C', 'a', 'r', 'l', 'o', 's', '\0'};
```

#### 2. Manipulação Básica de Strings (Sem `string.h`)

**Calculando comprimento de string:**
```c
int comprimento_string(char *str) {
    int contador = 0;
    while (str[contador] != '\0') {
        contador++;
    }
    return contador;
}
```

**Copiando strings:**
```c
void copiar_string(char *destino, char *origem) {
    int i = 0;
    while (origem[i] != '\0') {
        destino[i] = origem[i];
        i++;
    }
    destino[i] = '\0'; // Adiciona terminador
}
```

**Concatenando strings:**
```c
void concatenar_string(char *destino, char *origem) {
    int i = 0, j = 0;
    
    // Encontra o final da string de destino
    while (destino[i] != '\0') {
        i++;
    }
    
    // Adiciona a string origem ao final
    while (origem[j] != '\0') {
        destino[i] = origem[j];
        i++;
        j++;
    }
    destino[i] = '\0'; // Adiciona terminador
}
```

#### 3. Vetores de Strings (Array de Strings)
```c
// Array de ponteiros para strings
char *nomes[3] = {"Ana", "Bruno", "Carlos"};

// Array bidimensional de caracteres
char nomes[3][20] = {"Ana", "Bruno", "Carlos"};

// Alocação dinâmica de array de strings
char **nomes = malloc(3 * sizeof(char*));
nomes[0] = malloc(20 * sizeof(char));
strcpy(nomes[0], "Ana");
```

### Vantagens e Desvantagens

**Vantagens dos Vetores:**
- Acesso rápido por índice O(1)
- Eficiência de memória (dados contíguos)
- Cache-friendly (boa localidade espacial)
- Simplicidade de implementação

**Desvantagens dos Vetores:**
- Tamanho fixo (vetores estáticos)
- Inserção/remoção custosa O(n)
- Possibilidade de overflow
- Não há verificação automática de limites

**Vantagens das Strings como Vetores:**
- Controle total sobre a memória
- Eficiência máxima
- Compatibilidade com funções de sistema
- Base para entender outras estruturas

**Desvantagens das Strings como Vetores:**
- Gerenciamento manual da memória
- Vulnerabilidade a buffer overflow
- Necessidade de controlar o terminador '\0'
- Ausência de funcionalidades avançadas

---

## 🎲 Matrizes (Arrays Bidimensionais)

### Conceitos Fundamentais
Uma **matriz** é um vetor de vetores, organizando dados em linhas e colunas.

#### Declaração de Matrizes:
```c
// Matriz estática
int matriz[3][4]; // 3 linhas, 4 colunas

// Matriz com inicialização
int matriz[2][3] = {
    {1, 2, 3},
    {4, 5, 6}
};

// Alocação dinâmica
int **matriz = malloc(linhas * sizeof(int*));
for (int i = 0; i < linhas; i++) {
    matriz[i] = malloc(colunas * sizeof(int));
}
```

#### Strings em Matrizes:
```c
// Matriz de caracteres (uma string grande)
char texto[5][20]; // 5 strings de até 19 caracteres cada

// Preenchendo a matriz
strcpy(texto[0], "Primeira linha");
strcpy(texto[1], "Segunda linha");
```

---

## ⚡ Operações Comuns e Complexidade

| Operação | Vetor | Matriz | Complexidade |
|----------|--------|--------|--------------|
| Acesso | `arr[i]` | `mat[i][j]` | O(1) |
| Busca Linear | percorrer | percorrer linhas/colunas | O(n) / O(m×n) |
| Inserção no final | adicionar | adicionar linha/coluna | O(1) / O(n) |
| Inserção no meio | deslocar elementos | reestruturar | O(n) / O(m×n) |
| Remoção | deslocar elementos | reestruturar | O(n) / O(m×n) |

---

## 🔧 Exemplos Práticos

### 1. Sistema de Notas com Strings
```c
#include <stdio.h>

#define MAX_ALUNOS 5
#define MAX_NOME 50

typedef struct {
    char nome[MAX_NOME];
    float nota;
} Aluno;

void exibir_alunos(Aluno alunos[], int quantidade) {
    printf("\n=== RELATÓRIO DE NOTAS ===\n");
    for (int i = 0; i < quantidade; i++) {
        printf("Aluno: %-20s | Nota: %.2f\n", 
               alunos[i].nome, alunos[i].nota);
    }
}
```

### 2. Processamento de Texto
```c
// Contar palavras em um texto
int contar_palavras(char *texto) {
    int palavras = 0;
    int em_palavra = 0;
    
    for (int i = 0; texto[i] != '\0'; i++) {
        if (texto[i] != ' ' && texto[i] != '\t' && texto[i] != '\n') {
            if (!em_palavra) {
                palavras++;
                em_palavra = 1;
            }
        } else {
            em_palavra = 0;
        }
    }
    
    return palavras;
}
```

---

## 📖 Material de Estudo

### Para Iniciantes:
1. Execute `vetor/exemplo/exemploSimples.c`
2. Estude `matriz/exemploMatrizSimples.c`
3. Leia as primeiras questões em `questoes-academicas.md`

### Para Intermediários:
1. Analise `vetor/exemplo/exemploAvancado.c`
2. Implemente as funções de string manualmente
3. Estude alocação dinâmica de matrizes

### Para Avançados:
1. Execute `aplicacoes-praticas.c`
2. Analise performance em `analise-performance.md`
3. Implemente algoritmos de processamento de texto

---

## 🚀 Como Compilar e Executar

```bash
# Compilar exemplo básico
make exemploSimples

# Compilar todos os exemplos
make all

# Executar testes
make test

# Limpar executáveis
make clean
```

---

## ⚠️ Cuidados Importantes

### Buffer Overflow em Strings:
```c
// PERIGOSO - pode causar overflow
char buffer[10];
strcpy(buffer, "String muito longa que não cabe");

// SEGURO - controla o tamanho
char buffer[10];
strncpy(buffer, "String longa", sizeof(buffer) - 1);
buffer[sizeof(buffer) - 1] = '\0';
```

### Gerenciamento de Memória:
```c
// SEMPRE libere memória alocada dinamicamente
char **strings = malloc(n * sizeof(char*));
// ... usar strings ...
for (int i = 0; i < n; i++) {
    free(strings[i]);
}
free(strings);
```

---

## 🎯 Próximos Passos

Após dominar vetores e matrizes:
1. **Listas Ligadas** - Estruturas dinâmicas
2. **Pilhas e Filas** - Implementadas com vetores
3. **Árvores** - Estruturas hierárquicas
4. **Grafos** - Representação com matrizes de adjacência

---

## 📚 Arquivos de Exemplo

| Arquivo | Descrição |
|---------|-----------|
| `vetor/exemplo/exemploSimples.c` | Operações básicas com vetores |
| `vetor/exemplo/exemploStringVetores.c` | Manipulação de strings com vetores |
| `matriz/exemploMatrizSimples.c` | Operações básicas com matrizes |
| `aplicacoes-praticas.c` | Aplicações reais |
| `questoes-academicas.md` | Exercícios e teoria |

**Estude, pratique e domine as estruturas fundamentais da programação em C!** 🚀