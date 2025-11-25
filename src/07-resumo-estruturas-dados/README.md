# Resumo das Estruturas de Dados Fundamentais

## 📚 Visão Geral

Este documento apresenta um **resumo consolidado** de todas as estruturas de dados e algoritmos fundamentais estudados até o momento, desde vetores e matrizes até listas encadeadas. O objetivo é fornecer uma visão panorâmica dos conceitos, permitindo revisão rápida e comparação entre as diferentes estruturas.

### Por que Estudar Estruturas de Dados?

Estruturas de dados são a **base da programação eficiente**. Elas determinam como os dados são organizados, armazenados e manipulados na memória do computador. A escolha correta de uma estrutura de dados pode fazer a diferença entre um programa que executa em milissegundos e outro que leva horas para processar a mesma quantidade de dados.

**Benefícios de dominar estruturas de dados:**
- ✅ Escrever código mais eficiente e performático
- ✅ Resolver problemas complexos de forma elegante
- ✅ Passar em entrevistas técnicas de empresas de tecnologia
- ✅ Compreender como linguagens e frameworks funcionam internamente
- ✅ Tomar decisões de design de software fundamentadas

### Pré-requisitos

Para aproveitar ao máximo este material, você deve ter conhecimento básico de:
- Programação em linguagem C (variáveis, funções, ponteiros)
- Alocação dinâmica de memória (`malloc`, `free`)
- Conceitos básicos de análise de algoritmos

## 🎯 Objetivo do Resumo

Este resumo consolida os seguintes tópicos estudados:
1. **Vetores e Matrizes** - Estruturas de dados estáticas contíguas
2. **Métodos de Ordenação** - Algoritmos clássicos de organização de dados
3. **Métodos de Pesquisa** - Técnicas de busca e localização de elementos
4. **Pilhas e Filas** - Estruturas lineares com acesso restrito (TADs)
5. **Listas Encadeadas** - Estruturas dinâmicas não contíguas

### Como Usar Este Material

1. **Leitura teórica**: Estude cada seção para compreender os conceitos
2. **Análise de código**: Examine os exemplos de código fornecidos
3. **Prática**: Execute o arquivo `exemplo-completo.c` para ver tudo funcionando
4. **Exercícios**: Complete os desafios propostos ao final de cada seção

---

## 📖 Fundamentos Teóricos: Estruturas de Dados e Tipos Abstratos de Dados

### O que é uma Estrutura de Dados?

Uma **estrutura de dados** é uma forma sistemática de organizar, armazenar e gerenciar dados na memória de um computador, de modo a permitir seu uso eficiente. Do ponto de vista acadêmico, estruturas de dados são modelos matemáticos que definem a organização lógica dos dados e as operações que podem ser realizadas sobre eles.

#### Definição Formal

Formalmente, uma estrutura de dados pode ser definida como uma tupla **(D, F, A)** onde:

**D** representa o conjunto de dados (domínio)
- Exemplo:
    - Em uma lista, o domínio pode ser qualquer tipo de dado (inteiros, strings, objetos).
    - Em uma árvore binária, o domínio são os nós que contêm valores e referências para filhos.
      
**F** representa o conjunto de funções ou operações aplicáveis aos dados
- Exemplos:
    - Para uma fila (queue): enqueue, dequeue, peek.
    - Para uma pilha (stack): push, pop, top.
- Essas funções devem respeitar as propriedades da estrutura (não podemos, por exemplo, remover de uma fila vazia sem tratar isso).
  
**A** representa o conjunto de axiomas ou propriedades que governam o comportamento das operações
- Exemplos:
    - Em uma pilha: após um push(x) seguido de pop(), o elemento retornado deve ser x (propriedade LIFO).
    - Em uma fila: a ordem de saída deve ser a mesma ordem de entrada (propriedade FIFO).
- Esses axiomas são importantes para provar correção e consistência.

#### Classificação das Estruturas de Dados

As estruturas de dados podem ser classificadas de diferentes formas:

**1. Quanto à Organização:**
- **Lineares**: Os elementos são organizados sequencialmente (vetores, listas, pilhas, filas)
- **Não-Lineares**: Os elementos são organizados de forma hierárquica ou em rede (árvores, grafos)

**2. Quanto à Alocação de Memória:**
- **Estáticas**: Tamanho fixo definido em tempo de compilação (arrays)
- **Dinâmicas**: Tamanho variável, alocação em tempo de execução (listas encadeadas)

**3. Quanto à Homogeneidade:**
- **Homogêneas**: Todos os elementos são do mesmo tipo (vetores de inteiros)
- **Heterogêneas**: Elementos de tipos diferentes (structs, registros)

#### Importância Acadêmica

O estudo de estruturas de dados é fundamental na Ciência da Computação porque:

1. **Eficiência Algorítmica**: A escolha da estrutura de dados impacta diretamente a complexidade temporal e espacial dos algoritmos
2. **Modelagem de Problemas**: Permite representar problemas do mundo real de forma computacional
3. **Fundamento para Disciplinas Avançadas**: Base para estudo de bancos de dados, sistemas operacionais, compiladores e inteligência artificial
4. **Análise de Complexidade**: Permite avaliar e comparar soluções computacionais de forma rigorosa

### O que é um Tipo Abstrato de Dados (TAD)?

Um **Tipo Abstrato de Dados (TAD)**, do inglês *Abstract Data Type (ADT)*, é um modelo matemático que define um tipo de dado através de seu comportamento (semântica), independentemente de sua implementação concreta. É uma abstração que especifica **O QUE** as operações fazem, sem definir **COMO** elas são implementadas.

#### Definição Formal

Um TAD é definido formalmente por:
- **Um conjunto de valores** (domínio)
- **Um conjunto de operações** sobre esses valores
- **Especificações formais** (pré-condições, pós-condições e invariantes)

#### Componentes de um TAD

1. **Interface**: Conjunto de operações públicas disponíveis para os usuários
2. **Especificação**: Descrição formal do comportamento de cada operação
3. **Implementação**: Realização concreta do TAD (oculta do usuário)

#### Exemplo Acadêmico: TAD Pilha

```
TAD Pilha
    Domínio: Sequência de elementos do tipo T
    
    Operações:
        criar(): Pilha
            - Pré-condição: nenhuma
            - Pós-condição: retorna uma pilha vazia
            
        empilhar(p: Pilha, e: T): Pilha
            - Pré-condição: nenhuma
            - Pós-condição: retorna pilha com e no topo
            
        desempilhar(p: Pilha): (Pilha, T)
            - Pré-condição: pilha não está vazia
            - Pós-condição: retorna pilha sem o elemento do topo e o elemento removido
            
        topo(p: Pilha): T
            - Pré-condição: pilha não está vazia
            - Pós-condição: retorna o elemento do topo sem removê-lo
            
        estaVazia(p: Pilha): Booleano
            - Pré-condição: nenhuma
            - Pós-condição: retorna verdadeiro se pilha está vazia
            
    Axiomas:
        - topo(empilhar(p, e)) = e
        - estaVazia(criar()) = verdadeiro
        - estaVazia(empilhar(p, e)) = falso
```

#### Princípios Fundamentais dos TADs

1. **Encapsulamento**: Os detalhes de implementação são ocultados do usuário
2. **Abstração**: O usuário interage apenas com a interface, não com a implementação
3. **Modularidade**: TADs podem ser desenvolvidos e testados independentemente
4. **Reutilização**: A mesma interface pode ter múltiplas implementações

#### Relação entre TAD e Estrutura de Dados

| Aspecto | TAD | Estrutura de Dados |
|---------|-----|-------------------|
| **Nível** | Abstrato (conceitual) | Concreto (implementação) |
| **Define** | O que fazer (comportamento) | Como fazer (algoritmos) |
| **Foco** | Interface e especificação | Organização na memória |
| **Exemplo** | TAD Pilha | Array ou Lista Encadeada |

#### Importância do Conceito de TAD

1. **Separação de Interesses**: Divide o problema em especificação e implementação
2. **Manutenibilidade**: Permite alterar a implementação sem afetar o código cliente
3. **Correção de Software**: Facilita a verificação formal de programas
4. **Design de Software**: Fundamento para programação orientada a objetos e interfaces

### Hierarquia de Abstração

A relação entre os conceitos pode ser visualizada em níveis de abstração:

```
┌─────────────────────────────────────────┐
│     TIPO ABSTRATO DE DADOS (TAD)        │  ← Nível mais alto (O QUÊ)
│     Especificação comportamental        │
└─────────────────────────────────────────┘
                    ↓
┌─────────────────────────────────────────┐
│       ESTRUTURA DE DADOS                │  ← Nível intermediário (COMO organizar)
│       Organização lógica dos dados      │
└─────────────────────────────────────────┘
                    ↓
┌─────────────────────────────────────────┐
│       REPRESENTAÇÃO NA MEMÓRIA          │  ← Nível mais baixo (ONDE)
│       Bits, bytes, endereços            │
└─────────────────────────────────────────┘
```

### Referências Acadêmicas

- **Wirth, N. (1976)**. *Algorithms + Data Structures = Programs*. Prentice Hall.
- **Aho, A. V., Hopcroft, J. E., & Ullman, J. D. (1983)**. *Data Structures and Algorithms*. Addison-Wesley.
- **Liskov, B., & Zilles, S. (1974)**. Programming with abstract data types. *ACM SIGPLAN Notices*, 9(4), 50-59.

---

## 1️⃣ Vetores e Matrizes

### Conceito Fundamental
Vetores (arrays) e matrizes são **estruturas de dados estáticas** que armazenam elementos do mesmo tipo em **posições contíguas de memória**. São as estruturas mais básicas e fundamentais da computação.

A contiguidade de memória significa que os elementos são armazenados um ao lado do outro, o que permite calcular diretamente o endereço de qualquer elemento usando uma fórmula simples. Esta característica é a razão pela qual o acesso por índice é extremamente rápido (O(1)).

### Como Funciona na Memória

Quando você declara um vetor `int v[5]`, o compilador reserva um bloco contíguo de memória suficiente para armazenar 5 inteiros. Se cada inteiro ocupa 4 bytes, serão reservados 20 bytes consecutivos:

```
Endereço base: 1000
v[0] → 1000-1003 (4 bytes)
v[1] → 1004-1007 (4 bytes)
v[2] → 1008-1011 (4 bytes)
v[3] → 1012-1015 (4 bytes)
v[4] → 1016-1019 (4 bytes)
```

Para acessar `v[i]`, o processador calcula: `endereço = base + (i × tamanho_elemento)`

### Características Principais

#### Vetores (Arrays Unidimensionais)
- **Definição**: Coleção linear de elementos do mesmo tipo
- **Acesso**: Direto por índice em O(1)
- **Alocação**: Contígua na memória
- **Tamanho**: Fixo (estático) ou dinâmico (com realocação)

**Exemplo Básico**:
```c
int vetor[5] = {10, 20, 30, 40, 50};
// Acesso: vetor[2] retorna 30
// Endereço = base + (índice × tamanho_elemento)
```

**Exemplo Completo - Operações com Vetores**:
```c
#include <stdio.h>
#include <stdlib.h>

// Função para imprimir vetor
void imprimirVetor(int arr[], int n, const char* nome) {
    printf("%s: [", nome);
    for (int i = 0; i < n; i++) {
        printf("%d%s", arr[i], i < n-1 ? ", " : "");
    }
    printf("]\n");
}

// Função para somar elementos do vetor
int somarVetor(int arr[], int n) {
    int soma = 0;
    for (int i = 0; i < n; i++) {
        soma += arr[i];
    }
    return soma;
}

// Função para encontrar maior elemento
int maiorElemento(int arr[], int n) {
    int maior = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maior) {
            maior = arr[i];
        }
    }
    return maior;
}

// Função para inverter vetor
void inverterVetor(int arr[], int n) {
    for (int i = 0; i < n / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[n - 1 - i];
        arr[n - 1 - i] = temp;
    }
}

int main() {
    int numeros[5] = {10, 25, 8, 42, 15};
    int n = 5;
    
    imprimirVetor(numeros, n, "Original");
    printf("Soma: %d\n", somarVetor(numeros, n));
    printf("Maior: %d\n", maiorElemento(numeros, n));
    
    inverterVetor(numeros, n);
    imprimirVetor(numeros, n, "Invertido");
    
    return 0;
}
```

#### Matrizes (Arrays Bidimensionais)
- **Definição**: Array de arrays, organizado em linhas e colunas
- **Armazenamento**: Row-major order (linhas consecutivas)
- **Acesso**: matriz[i][j] em O(1)

Matrizes são essenciais para representar dados tabulares, imagens, grafos e sistemas de equações lineares.

**Exemplo Básico**:
```c
int matriz[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};
// Acesso: matriz[1][2] retorna 6
```

**Exemplo Completo - Operações com Matrizes**:
```c
#include <stdio.h>

#define LINHAS 3
#define COLUNAS 3

// Função para imprimir matriz
void imprimirMatriz(int mat[LINHAS][COLUNAS]) {
    printf("Matriz:\n");
    for (int i = 0; i < LINHAS; i++) {
        printf("  ");
        for (int j = 0; j < COLUNAS; j++) {
            printf("%3d ", mat[i][j]);
        }
        printf("\n");
    }
}

// Função para calcular soma de todos elementos
int somaMatriz(int mat[LINHAS][COLUNAS]) {
    int soma = 0;
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            soma += mat[i][j];
        }
    }
    return soma;
}

// Função para calcular soma da diagonal principal
int somaDiagonalPrincipal(int mat[LINHAS][COLUNAS]) {
    int soma = 0;
    for (int i = 0; i < LINHAS; i++) {
        soma += mat[i][i];
    }
    return soma;
}

// Função para transpor matriz
void transporMatriz(int mat[LINHAS][COLUNAS], int resultado[COLUNAS][LINHAS]) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            resultado[j][i] = mat[i][j];
        }
    }
}

// Função para multiplicar matrizes
void multiplicarMatrizes(int A[LINHAS][COLUNAS], int B[LINHAS][COLUNAS], 
                         int resultado[LINHAS][COLUNAS]) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            resultado[i][j] = 0;
            for (int k = 0; k < COLUNAS; k++) {
                resultado[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int matriz[LINHAS][COLUNAS] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    imprimirMatriz(matriz);
    printf("Soma total: %d\n", somaMatriz(matriz));
    printf("Soma diagonal principal: %d\n", somaDiagonalPrincipal(matriz));
    
    int transposta[COLUNAS][LINHAS];
    transporMatriz(matriz, transposta);
    printf("\nMatriz Transposta:\n");
    for (int i = 0; i < COLUNAS; i++) {
        printf("  ");
        for (int j = 0; j < LINHAS; j++) {
            printf("%3d ", transposta[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
```

### Complexidade das Operações

| Operação | Complexidade | Observação |
|----------|--------------|------------|
| Acesso por índice | O(1) | Cálculo direto do endereço |
| Busca em array não ordenado | O(n) | Busca linear |
| Busca em array ordenado | O(log n) | Busca binária |
| Inserção no final | O(1)* | *Amortizado se dinâmico |
| Inserção no meio | O(n) | Necessário deslocar elementos |
| Remoção | O(n) | Necessário deslocar elementos |

### Vantagens
✅ Acesso direto extremamente rápido O(1)  
✅ Localidade de cache excelente (dados contíguos)  
✅ Simples de implementar e usar  
✅ Baixo overhead de memória  

### Desvantagens
❌ Tamanho fixo (arrays estáticos)  
❌ Inserção/remoção custosa O(n)  
❌ Desperdício de memória se não totalmente utilizado  

### Aplicações Práticas
- Armazenamento de dados tabulares
- Processamento de imagens (matriz de pixels)
- Implementação de outras estruturas (heaps, hash tables)
- Matrizes matemáticas e álgebra linear
- Strings (vetores de caracteres)

---

## 2️⃣ Métodos de Ordenação

### Conceito Fundamental
Ordenação é o processo de **reorganizar elementos em uma ordem específica** (crescente/decrescente). É um dos problemas mais estudados em computação, com impacto direto na eficiência de outras operações (especialmente buscas).

### Por que Ordenação é Importante?

A ordenação é fundamental porque:
1. **Acelera buscas**: Em dados ordenados, podemos usar busca binária (O(log n)) ao invés de busca linear (O(n))
2. **Facilita detecção de duplicatas**: Elementos iguais ficam adjacentes
3. **Simplifica análise de dados**: Encontrar mediana, moda, máximo e mínimo é mais fácil
4. **Base para outros algoritmos**: Muitos algoritmos dependem de dados ordenados

### Classificação dos Algoritmos

#### Algoritmos O(n²) - Simples, mas Ineficientes para Grandes Dados

Estes algoritmos são ideais para aprendizado e conjuntos pequenos de dados (< 50 elementos).

##### **Bubble Sort**
- **Complexidade**: O(n²) médio/pior, O(n) melhor caso
- **Estabilidade**: Estável
- **Método**: Comparações adjacentes, "bolhas" sobem
- **Uso**: Apenas educacional, arrays muito pequenos

**Como funciona**: Percorre o array repetidamente, comparando elementos adjacentes e trocando-os se estiverem na ordem errada. Elementos maiores "borbulham" para o final.

**Exemplo Visual**:
```
Passo 1: [64, 34, 25, 12] → comparar 64 e 34 → trocar → [34, 64, 25, 12]
Passo 2: [34, 64, 25, 12] → comparar 64 e 25 → trocar → [34, 25, 64, 12]
Passo 3: [34, 25, 64, 12] → comparar 64 e 12 → trocar → [34, 25, 12, 64]
(64 está na posição final correta)
... continua até ordenar completamente
```

**Implementação Completa**:
```c
#include <stdio.h>
#include <stdbool.h>

// Bubble Sort com otimização de parada antecipada
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool trocou = false;  // Otimização: detecta se houve troca
        
        // Últimos i elementos já estão ordenados
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Troca arr[j] e arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                trocou = true;
            }
        }
        
        // Se não houve nenhuma troca, array já está ordenado
        if (!trocou) {
            break;
        }
    }
}

// Exemplo de uso
int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Array original: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    
    bubbleSort(arr, n);
    
    printf("\nArray ordenado: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    
    return 0;
}
```

##### **Insertion Sort**
- **Complexidade**: O(n²) médio/pior, O(n) melhor caso
- **Estabilidade**: Estável
- **Método**: Insere elemento na posição correta
- **Vantagem**: **Adaptativo** - eficiente para dados quase ordenados
- **Uso**: Arrays pequenos (< 50), dados quase ordenados

**Como funciona**: Funciona como ordenar cartas na mão. Pega um elemento de cada vez e insere na posição correta entre os elementos já ordenados.

**Exemplo Visual**:
```
Inicial: [5, 2, 4, 6, 1, 3]
Passo 1: [5, 2, 4, 6, 1, 3] → inserir 2 → [2, 5, 4, 6, 1, 3]
Passo 2: [2, 5, 4, 6, 1, 3] → inserir 4 → [2, 4, 5, 6, 1, 3]
Passo 3: [2, 4, 5, 6, 1, 3] → inserir 6 → [2, 4, 5, 6, 1, 3] (já na posição)
Passo 4: [2, 4, 5, 6, 1, 3] → inserir 1 → [1, 2, 4, 5, 6, 3]
Passo 5: [1, 2, 4, 5, 6, 3] → inserir 3 → [1, 2, 3, 4, 5, 6]
```

**Implementação Completa**:
```c
// Insertion Sort - ideal para arrays pequenos ou quase ordenados
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int chave = arr[i];  // Elemento a ser inserido
        int j = i - 1;
        
        // Move elementos maiores que a chave uma posição à frente
        while (j >= 0 && arr[j] > chave) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        
        // Insere a chave na posição correta
        arr[j + 1] = chave;
    }
}

// Versão com contagem de operações para análise
void insertionSortComContagem(int arr[], int n, int* comparacoes, int* movimentos) {
    *comparacoes = 0;
    *movimentos = 0;
    
    for (int i = 1; i < n; i++) {
        int chave = arr[i];
        int j = i - 1;
        
        while (j >= 0) {
            (*comparacoes)++;
            if (arr[j] > chave) {
                arr[j + 1] = arr[j];
                (*movimentos)++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = chave;
        (*movimentos)++;
    }
}
```

##### **Selection Sort**
- **Complexidade**: O(n²) sempre (não adaptativo)
- **Estabilidade**: Não estável
- **Método**: Seleciona o menor e coloca na posição correta
- **Vantagem**: Número mínimo de escritas (n-1 trocas)
- **Uso**: Quando escrita é cara (Flash memory)

**Como funciona**: Encontra o menor elemento e coloca na primeira posição, depois encontra o segundo menor e coloca na segunda posição, e assim por diante.

**Implementação Completa**:
```c
// Selection Sort - minimiza número de escritas
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        // Encontrar o índice do menor elemento no subarray não ordenado
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        
        // Trocar o menor elemento encontrado com o primeiro elemento não ordenado
        if (min_idx != i) {
            int temp = arr[min_idx];
            arr[min_idx] = arr[i];
            arr[i] = temp;
        }
    }
}
```

#### Algoritmos O(n log n) - Eficientes para Uso Geral

Estes algoritmos são adequados para grandes conjuntos de dados e são usados em produção.

##### **Quick Sort**
- **Complexidade**: O(n log n) médio, O(n²) pior caso
- **Estabilidade**: Não estável
- **Método**: Divisão e conquista com pivô
- **Espaço**: O(log n) pilha de recursão
- **Vantagem**: **In-place**, constantes pequenas, muito rápido na prática
- **Uso**: Algoritmo de ordenação de uso geral mais popular

**Como funciona**: 
1. Escolhe um elemento como pivô
2. Particiona o array: elementos menores que o pivô à esquerda, maiores à direita
3. Recursivamente ordena as duas partições

**Exemplo Visual**:
```
Array: [8, 4, 2, 9, 5, 1, 6, 3, 7]
Pivô = 7

Particionamento:
Menores que 7: [4, 2, 5, 1, 6, 3]
Pivô: [7]
Maiores que 7: [8, 9]

Resultado: [4, 2, 5, 1, 6, 3] + [7] + [8, 9]
Continua recursivamente nas partições...
```

**Implementação Completa**:
```c
// Função auxiliar para trocar dois elementos
void trocar(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Particionamento usando o último elemento como pivô
int particionar(int arr[], int baixo, int alto) {
    int pivo = arr[alto];  // Pivô é o último elemento
    int i = baixo - 1;     // Índice do menor elemento
    
    for (int j = baixo; j < alto; j++) {
        // Se elemento atual é menor ou igual ao pivô
        if (arr[j] <= pivo) {
            i++;
            trocar(&arr[i], &arr[j]);
        }
    }
    
    // Coloca o pivô na posição correta
    trocar(&arr[i + 1], &arr[alto]);
    return i + 1;
}

// Quick Sort recursivo
void quickSort(int arr[], int baixo, int alto) {
    if (baixo < alto) {
        // pi é o índice do pivô após particionamento
        int pi = particionar(arr, baixo, alto);
        
        // Ordena elementos antes e depois do pivô
        quickSort(arr, baixo, pi - 1);
        quickSort(arr, pi + 1, alto);
    }
}

// Exemplo de uso
int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Array original: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    
    quickSort(arr, 0, n - 1);
    
    printf("\nArray ordenado: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    
    return 0;
}
```

##### **Merge Sort**
- **Complexidade**: O(n log n) sempre (garantido)
- **Estabilidade**: Estável
- **Método**: Divisão e conquista com mesclagem
- **Espaço**: O(n) array auxiliar
- **Vantagem**: Previsível, garantia de O(n log n)
- **Uso**: Quando estabilidade é necessária, ordenação externa

**Como funciona**:
1. Divide o array ao meio recursivamente até ter arrays de 1 elemento
2. Mescla os arrays ordenados de volta, mantendo a ordem

**Exemplo Visual**:
```
Divisão:
[38, 27, 43, 3, 9, 82, 10]
       ↓
[38, 27, 43] e [3, 9, 82, 10]
       ↓              ↓
[38] [27, 43]    [3, 9] [82, 10]
       ↓              ↓
[38] [27] [43]  [3] [9] [82] [10]

Mesclagem:
[27, 38, 43] e [3, 9, 10, 82]
              ↓
[3, 9, 10, 27, 38, 43, 82]
```

**Implementação Completa**:
```c
// Função para mesclar dois subarrays ordenados
void mesclar(int arr[], int esq, int meio, int dir) {
    int n1 = meio - esq + 1;
    int n2 = dir - meio;
    
    // Criar arrays temporários
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));
    
    // Copiar dados para arrays temporários
    for (int i = 0; i < n1; i++)
        L[i] = arr[esq + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[meio + 1 + j];
    
    // Mesclar os arrays temporários de volta
    int i = 0, j = 0, k = esq;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    // Copiar elementos restantes de L[], se houver
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // Copiar elementos restantes de R[], se houver
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    free(L);
    free(R);
}

// Merge Sort recursivo
void mergeSort(int arr[], int esq, int dir) {
    if (esq < dir) {
        int meio = esq + (dir - esq) / 2;
        
        // Ordena primeira e segunda metade
        mergeSort(arr, esq, meio);
        mergeSort(arr, meio + 1, dir);
        
        // Mescla as metades ordenadas
        mesclar(arr, esq, meio, dir);
    }
}

// Exemplo de uso
int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Array original: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    
    mergeSort(arr, 0, n - 1);
    
    printf("\nArray ordenado: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    
    return 0;
}
```

##### **Heap Sort**
- **Complexidade**: O(n log n) sempre
- **Estabilidade**: Não estável
- **Método**: Construir heap e extrair máximo
- **Espaço**: O(1) - in-place
- **Vantagem**: In-place com garantia O(n log n)
- **Uso**: Quando espaço é limitado

**Como funciona**:
1. Constrói um max-heap a partir do array
2. Repetidamente extrai o máximo (raiz) e reconstrói o heap

**Implementação Completa**:
```c
// Função auxiliar para manter a propriedade do heap
void heapify(int arr[], int n, int i) {
    int maior = i;        // Inicializa maior como raiz
    int esq = 2 * i + 1;  // Filho esquerdo
    int dir = 2 * i + 2;  // Filho direito
    
    // Se filho esquerdo é maior que a raiz
    if (esq < n && arr[esq] > arr[maior])
        maior = esq;
    
    // Se filho direito é maior que o maior até agora
    if (dir < n && arr[dir] > arr[maior])
        maior = dir;
    
    // Se o maior não é a raiz
    if (maior != i) {
        int temp = arr[i];
        arr[i] = arr[maior];
        arr[maior] = temp;
        
        // Recursivamente heapify a subárvore afetada
        heapify(arr, n, maior);
    }
}

// Heap Sort
void heapSort(int arr[], int n) {
    // Construir heap (reorganizar array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    
    // Extrair elementos do heap um por um
    for (int i = n - 1; i > 0; i--) {
        // Move raiz atual para o final
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        
        // Chama heapify na heap reduzida
        heapify(arr, i, 0);
    }
}
```

### Comparação Completa

| Algoritmo | Melhor | Médio | Pior | Espaço | Estável | In-place |
|-----------|--------|-------|------|---------|---------|----------|
| Bubble Sort | O(n) | O(n²) | O(n²) | O(1) | ✅ | ✅ |
| Insertion Sort | O(n) | O(n²) | O(n²) | O(1) | ✅ | ✅ |
| Selection Sort | O(n²) | O(n²) | O(n²) | O(1) | ❌ | ✅ |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | O(log n) | ❌ | ✅ |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) | ✅ | ❌ |
| Heap Sort | O(n log n) | O(n log n) | O(n log n) | O(1) | ❌ | ✅ |

### Teorema Fundamental
**Limite inferior para ordenação baseada em comparações**: Ω(n log n)
- Qualquer algoritmo de ordenação por comparação requer pelo menos Ω(n log n) comparações no pior caso
- Provado através de teoria da informação (há n! permutações possíveis)

### Escolha Prática por Cenário
1. **Uso geral**: Quick Sort (otimizado)
2. **Estabilidade necessária**: Merge Sort ou Timsort
3. **Espaço limitado**: Heap Sort
4. **Dados quase ordenados**: Insertion Sort
5. **Garantia O(n log n)**: Merge Sort ou Heap Sort
6. **Arrays pequenos (n < 50)**: Insertion Sort

---

## 3️⃣ Métodos de Pesquisa

### Conceito Fundamental
Pesquisa (busca) é a operação de **localizar um elemento específico** dentro de uma coleção de dados. É uma das operações mais executadas em sistemas computacionais.

### Por que Busca é Importante?

Em qualquer sistema de software, a busca é uma operação fundamental:
- **Bancos de dados**: Encontrar registros por chave
- **Sistemas de arquivos**: Localizar arquivos por nome
- **Redes sociais**: Buscar usuários ou posts
- **E-commerce**: Encontrar produtos

A escolha do algoritmo de busca correto pode fazer a diferença entre uma resposta instantânea e segundos de espera.

### Algoritmos Fundamentais

#### **Busca Linear (Sequential Search)**

**Características**:
- **Complexidade**: O(n) pior caso, O(1) melhor caso
- **Espaço**: O(1)
- **Pré-requisito**: Nenhum (funciona em dados não ordenados)
- **Método**: Percorre sequencialmente cada elemento

**Como funciona**: Examina cada elemento do início ao fim até encontrar o elemento buscado ou chegar ao final do array.

**Exemplo Visual**:
```
Array: [4, 2, 7, 1, 9, 3]
Buscando: 9

Passo 1: Compara com 4 → não é
Passo 2: Compara com 2 → não é
Passo 3: Compara com 7 → não é
Passo 4: Compara com 1 → não é
Passo 5: Compara com 9 → ENCONTRADO! (índice 4)
```

**Implementação Básica**:
```c
int buscaLinear(int arr[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x)
            return i;  // Encontrado
    }
    return -1;  // Não encontrado
}
```

**Implementação Completa com Variações**:
```c
#include <stdio.h>
#include <stdbool.h>

// Busca linear básica - retorna índice ou -1
int buscaLinear(int arr[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x)
            return i;
    }
    return -1;
}

// Busca linear com contagem de comparações
int buscaLinearComContagem(int arr[], int n, int x, int* comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < n; i++) {
        (*comparacoes)++;
        if (arr[i] == x)
            return i;
    }
    return -1;
}

// Busca linear com sentinela (otimização)
// Coloca o elemento no final para evitar verificação de limite
int buscaLinearSentinela(int arr[], int n, int x) {
    int ultimo = arr[n - 1];  // Guarda último elemento
    arr[n - 1] = x;           // Coloca sentinela
    
    int i = 0;
    while (arr[i] != x)
        i++;
    
    arr[n - 1] = ultimo;      // Restaura último elemento
    
    if (i < n - 1 || arr[n - 1] == x)
        return i;
    return -1;
}

// Busca que retorna todas as ocorrências
int buscaTodasOcorrencias(int arr[], int n, int x, int indices[], int* count) {
    *count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == x) {
            indices[*count] = i;
            (*count)++;
        }
    }
    return *count > 0 ? indices[0] : -1;
}

// Exemplo de uso
int main() {
    int arr[] = {5, 2, 8, 2, 9, 1, 2, 7};
    int n = 8;
    int comparacoes;
    
    // Busca básica
    int pos = buscaLinear(arr, n, 9);
    printf("Busca por 9: %s (índice %d)\n", 
           pos != -1 ? "Encontrado" : "Não encontrado", pos);
    
    // Busca com contagem
    pos = buscaLinearComContagem(arr, n, 7, &comparacoes);
    printf("Busca por 7: Encontrado no índice %d após %d comparações\n", 
           pos, comparacoes);
    
    // Busca todas ocorrências
    int indices[10];
    int count;
    buscaTodasOcorrencias(arr, n, 2, indices, &count);
    printf("Busca por 2: %d ocorrências nos índices: ", count);
    for (int i = 0; i < count; i++) {
        printf("%d ", indices[i]);
    }
    printf("\n");
    
    return 0;
}
```

**Análise**:
- Busca bem-sucedida média: (n+1)/2 comparações
- Busca mal-sucedida: sempre n comparações
- **Ótima para dados não ordenados**

**Quando usar**:
- Arrays pequenos (n < 100)
- Dados não ordenados
- Busca única (ordenar seria mais caro)
- Estruturas sem acesso aleatório (listas encadeadas)

#### **Busca Binária (Binary Search)**

**Características**:
- **Complexidade**: O(log n) pior caso, O(1) melhor caso
- **Espaço**: O(1) iterativa, O(log n) recursiva
- **Pré-requisito**: **Array ordenado**
- **Método**: Divisão sucessiva ao meio

**Como funciona**: Divide o espaço de busca pela metade a cada iteração. Se o elemento do meio é maior que o buscado, descarta a metade superior; se é menor, descarta a metade inferior.

**Exemplo Visual**:
```
Array ordenado: [2, 5, 8, 12, 16, 23, 38, 45, 56, 67, 78]
Buscando: 23

Passo 1: meio = 23 (índice 5)
         23 == 23? SIM! ENCONTRADO!

Buscando: 56
Passo 1: [2, 5, 8, 12, 16, 23, 38, 45, 56, 67, 78]
                        ↑ meio = 23
         56 > 23 → buscar na metade direita

Passo 2: [38, 45, 56, 67, 78]
              ↑ meio = 56
         56 == 56? SIM! ENCONTRADO!
```

**Implementação Iterativa**:
```c
int buscaBinaria(int arr[], int n, int x) {
    int esq = 0, dir = n - 1;
    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;  // Evita overflow
        
        if (arr[meio] == x)
            return meio;
        
        if (arr[meio] < x)
            esq = meio + 1;
        else
            dir = meio - 1;
    }
    return -1;
}
```

**Implementação Completa com Variações**:
```c
#include <stdio.h>

// Busca binária iterativa
int buscaBinariaIterativa(int arr[], int n, int x) {
    int esq = 0, dir = n - 1;
    
    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;  // Evita overflow
        
        if (arr[meio] == x)
            return meio;
        else if (arr[meio] < x)
            esq = meio + 1;
        else
            dir = meio - 1;
    }
    
    return -1;
}

// Busca binária recursiva
int buscaBinariaRecursiva(int arr[], int esq, int dir, int x) {
    if (esq > dir)
        return -1;
    
    int meio = esq + (dir - esq) / 2;
    
    if (arr[meio] == x)
        return meio;
    else if (arr[meio] < x)
        return buscaBinariaRecursiva(arr, meio + 1, dir, x);
    else
        return buscaBinariaRecursiva(arr, esq, meio - 1, x);
}

// Encontra a primeira ocorrência de x (lower bound)
int primeiraOcorrencia(int arr[], int n, int x) {
    int esq = 0, dir = n - 1;
    int resultado = -1;
    
    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;
        
        if (arr[meio] == x) {
            resultado = meio;
            dir = meio - 1;  // Continua procurando à esquerda
        } else if (arr[meio] < x) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }
    
    return resultado;
}

// Encontra a última ocorrência de x (upper bound)
int ultimaOcorrencia(int arr[], int n, int x) {
    int esq = 0, dir = n - 1;
    int resultado = -1;
    
    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;
        
        if (arr[meio] == x) {
            resultado = meio;
            esq = meio + 1;  // Continua procurando à direita
        } else if (arr[meio] < x) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }
    
    return resultado;
}

// Conta quantas vezes x aparece no array ordenado
int contarOcorrencias(int arr[], int n, int x) {
    int primeira = primeiraOcorrencia(arr, n, x);
    if (primeira == -1)
        return 0;
    int ultima = ultimaOcorrencia(arr, n, x);
    return ultima - primeira + 1;
}

// Exemplo de uso
int main() {
    int arr[] = {2, 5, 5, 5, 8, 12, 16, 23, 38, 45};
    int n = 10;
    
    printf("Array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n\n");
    
    // Busca básica
    int pos = buscaBinariaIterativa(arr, n, 23);
    printf("Busca por 23: índice %d\n", pos);
    
    // Busca recursiva
    pos = buscaBinariaRecursiva(arr, 0, n - 1, 12);
    printf("Busca recursiva por 12: índice %d\n", pos);
    
    // Primeira e última ocorrência
    int primeira = primeiraOcorrencia(arr, n, 5);
    int ultima = ultimaOcorrencia(arr, n, 5);
    printf("Elemento 5: primeira ocorrência em %d, última em %d\n", 
           primeira, ultima);
    
    // Contar ocorrências
    int count = contarOcorrencias(arr, n, 5);
    printf("Elemento 5 aparece %d vezes\n", count);
    
    return 0;
}
```

**Análise**:
- Número máximo de comparações: ⌊log₂ n⌋ + 1
- Para n = 1.000.000: apenas 20 comparações
- **Exponencialmente mais rápida que busca linear**

**Quando usar**:
- Arrays grandes ordenados
- Múltiplas operações de busca
- Quando o custo de ordenação já foi amortizado

### Comparação: Linear vs Binária

| Aspecto | Busca Linear | Busca Binária |
|---------|--------------|---------------|
| Complexidade | O(n) | O(log n) |
| Pré-requisito | Nenhum | Array ordenado |
| Melhor para | Dados pequenos/não ordenados | Dados grandes ordenados |
| Comparações (n=1M) | ~500.000 (média) | ~20 |
| Implementação | Muito simples | Simples |

### Estruturas Avançadas para Busca

- **Tabelas Hash**: O(1) caso médio, mas não mantém ordem
- **Árvores de Busca Binária (BST)**: O(log n) se balanceada
- **Árvores AVL/Red-Black**: O(log n) garantido

---

## 4️⃣ Pilhas e Filas

### Conceito Fundamental
Pilhas e filas são **Tipos Abstratos de Dados (TAD)** que implementam estruturas lineares com **acesso restrito**, ou seja, permitem inserção e remoção apenas em posições específicas, seguindo políticas bem definidas.

### O que é um TAD (Tipo Abstrato de Dados)?

Um TAD define:
- **O QUE** fazer (interface, operações)
- **NÃO COMO** fazer (implementação)

Isso permite:
- Encapsulamento: detalhes internos ficam ocultos
- Substituibilidade: pode trocar a implementação sem afetar o código cliente
- Abstração: foco no comportamento, não nos detalhes

### Pilha (Stack) - LIFO

#### Definição
Estrutura que segue o princípio **LIFO** (*Last-In, First-Out*): o último elemento inserido é o primeiro a ser removido.

**Analogia**: Pilha de pratos - você adiciona e remove sempre do topo.

**Aplicações do mundo real**:
- **Ctrl+Z no editor**: Desfaz a última ação (última a entrar, primeira a sair)
- **Botão "Voltar" no navegador**: Volta para a página mais recente
- **Chamadas de função**: A última função chamada é a primeira a retornar

#### Operações Fundamentais
```c
typedef struct {
    int topo;
    int capacidade;
    int* array;
} Pilha;

void push(Pilha* p, int elemento);  // Empilhar - O(1)
int pop(Pilha* p);                   // Desempilhar - O(1)
int peek(Pilha* p);                  // Ver topo - O(1)
bool vazia(Pilha* p);                // Verificar se vazia - O(1)
```

#### Exemplo Visual
```
Pilha: [1, 2, 3]
push(4) → [1, 2, 3, 4]  // 4 entra no topo
pop()   → [1, 2, 3]     // 4 sai (último que entrou)
```

#### Implementação Completa com Array
```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definição da estrutura da Pilha
typedef struct {
    int* array;      // Array para armazenar elementos
    int topo;        // Índice do topo (-1 se vazia)
    int capacidade;  // Capacidade máxima
} Pilha;

// Criar uma nova pilha
Pilha* criarPilha(int capacidade) {
    Pilha* pilha = (Pilha*)malloc(sizeof(Pilha));
    pilha->capacidade = capacidade;
    pilha->topo = -1;
    pilha->array = (int*)malloc(capacidade * sizeof(int));
    return pilha;
}

// Verificar se está vazia
bool pilhaVazia(Pilha* pilha) {
    return pilha->topo == -1;
}

// Verificar se está cheia
bool pilhaCheia(Pilha* pilha) {
    return pilha->topo == pilha->capacidade - 1;
}

// Empilhar elemento - O(1)
bool push(Pilha* pilha, int item) {
    if (pilhaCheia(pilha)) {
        printf("Erro: Pilha cheia! Não foi possível adicionar %d\n", item);
        return false;
    }
    pilha->array[++pilha->topo] = item;
    printf("Empilhado: %d\n", item);
    return true;
}

// Desempilhar elemento - O(1)
int pop(Pilha* pilha) {
    if (pilhaVazia(pilha)) {
        printf("Erro: Pilha vazia!\n");
        return -1;  // Valor de erro
    }
    int item = pilha->array[pilha->topo--];
    printf("Desempilhado: %d\n", item);
    return item;
}

// Ver elemento do topo sem remover - O(1)
int peek(Pilha* pilha) {
    if (pilhaVazia(pilha)) {
        printf("Pilha vazia!\n");
        return -1;
    }
    return pilha->array[pilha->topo];
}

// Retornar número de elementos
int tamanho(Pilha* pilha) {
    return pilha->topo + 1;
}

// Imprimir pilha
void imprimirPilha(Pilha* pilha) {
    if (pilhaVazia(pilha)) {
        printf("Pilha vazia\n");
        return;
    }
    printf("Pilha (base → topo): ");
    for (int i = 0; i <= pilha->topo; i++) {
        printf("%d ", pilha->array[i]);
    }
    printf("\n");
}

// Liberar memória
void liberarPilha(Pilha* pilha) {
    free(pilha->array);
    free(pilha);
}

// Exemplo de uso
int main() {
    Pilha* pilha = criarPilha(5);
    
    push(pilha, 10);
    push(pilha, 20);
    push(pilha, 30);
    
    imprimirPilha(pilha);
    printf("Topo: %d\n", peek(pilha));
    printf("Tamanho: %d\n\n", tamanho(pilha));
    
    pop(pilha);
    imprimirPilha(pilha);
    
    liberarPilha(pilha);
    return 0;
}
```

#### Aplicação Prática: Verificação de Parênteses Balanceados
```c
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX 100

typedef struct {
    char array[MAX];
    int topo;
} PilhaChar;

void inicializarPilha(PilhaChar* p) { p->topo = -1; }
bool vazia(PilhaChar* p) { return p->topo == -1; }
void push(PilhaChar* p, char c) { p->array[++p->topo] = c; }
char pop(PilhaChar* p) { return p->array[p->topo--]; }

// Verifica se os parênteses estão balanceados
bool parentesesBalanceados(const char* expressao) {
    PilhaChar pilha;
    inicializarPilha(&pilha);
    
    for (int i = 0; expressao[i] != '\0'; i++) {
        char c = expressao[i];
        
        // Se é um caractere de abertura, empilha
        if (c == '(' || c == '[' || c == '{') {
            push(&pilha, c);
        }
        // Se é um caractere de fechamento
        else if (c == ')' || c == ']' || c == '}') {
            // Pilha vazia = sem par correspondente
            if (vazia(&pilha))
                return false;
            
            char topo = pop(&pilha);
            
            // Verifica se o par corresponde
            if ((c == ')' && topo != '(') ||
                (c == ']' && topo != '[') ||
                (c == '}' && topo != '{'))
                return false;
        }
    }
    
    // Pilha deve estar vazia no final
    return vazia(&pilha);
}

int main() {
    const char* testes[] = {
        "{[()]}",
        "((()))",
        "{[(])}",
        "((())",
        "a + (b * c) - [d / e]"
    };
    
    for (int i = 0; i < 5; i++) {
        printf("\"%s\" → %s\n", testes[i], 
               parentesesBalanceados(testes[i]) ? "Balanceado ✓" : "Desbalanceado ✗");
    }
    
    return 0;
}
```

#### Implementações
1. **Com Array**: Acesso rápido, tamanho limitado
2. **Com Lista Encadeada**: Tamanho dinâmico, overhead de ponteiros

#### Aplicações Práticas
✅ Gerenciamento de chamadas de função (call stack)  
✅ Avaliação de expressões matemáticas (notação polonesa)  
✅ Desfazer/Refazer (undo/redo) em editores  
✅ Navegação de histórico (back button no navegador)  
✅ Verificação de balanceamento de parênteses  
✅ Algoritmos de travessia (DFS em grafos)  

### Fila (Queue) - FIFO

#### Definição
Estrutura que segue o princípio **FIFO** (*First-In, First-Out*): o primeiro elemento inserido é o primeiro a ser removido.

**Analogia**: Fila de banco - quem chega primeiro é atendido primeiro.

**Aplicações do mundo real**:
- **Fila de impressão**: Documentos são impressos na ordem de chegada
- **Atendimento em bancos/hospitais**: Primeiro a chegar, primeiro a ser atendido
- **Buffer de vídeo streaming**: Dados chegam e são consumidos em ordem

#### Operações Fundamentais
```c
typedef struct {
    int frente;
    int tras;
    int capacidade;
    int* array;
} Fila;

void enqueue(Fila* f, int elemento);  // Enfileirar - O(1)
int dequeue(Fila* f);                  // Desenfileirar - O(1)
int front(Fila* f);                    // Ver primeiro - O(1)
bool vazia(Fila* f);                   // Verificar se vazia - O(1)
```

#### Exemplo Visual
```
Fila: [1, 2, 3]
enqueue(4) → [1, 2, 3, 4]  // 4 entra no final
dequeue()  → [2, 3, 4]     // 1 sai (primeiro que entrou)
```

#### Implementação Completa - Fila Circular
```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Fila Circular - usa o array de forma circular para evitar desperdício
typedef struct {
    int* array;
    int frente;      // Índice do primeiro elemento
    int tras;        // Índice onde será inserido o próximo
    int tamanho;     // Quantidade atual de elementos
    int capacidade;  // Capacidade máxima
} FilaCircular;

// Criar fila
FilaCircular* criarFila(int capacidade) {
    FilaCircular* fila = (FilaCircular*)malloc(sizeof(FilaCircular));
    fila->capacidade = capacidade;
    fila->frente = 0;
    fila->tras = 0;
    fila->tamanho = 0;
    fila->array = (int*)malloc(capacidade * sizeof(int));
    return fila;
}

// Verificar se está vazia
bool filaVazia(FilaCircular* fila) {
    return fila->tamanho == 0;
}

// Verificar se está cheia
bool filaCheia(FilaCircular* fila) {
    return fila->tamanho == fila->capacidade;
}

// Enfileirar - O(1)
bool enqueue(FilaCircular* fila, int item) {
    if (filaCheia(fila)) {
        printf("Erro: Fila cheia!\n");
        return false;
    }
    
    fila->array[fila->tras] = item;
    fila->tras = (fila->tras + 1) % fila->capacidade;  // Circular
    fila->tamanho++;
    printf("Enfileirado: %d\n", item);
    return true;
}

// Desenfileirar - O(1)
int dequeue(FilaCircular* fila) {
    if (filaVazia(fila)) {
        printf("Erro: Fila vazia!\n");
        return -1;
    }
    
    int item = fila->array[fila->frente];
    fila->frente = (fila->frente + 1) % fila->capacidade;  // Circular
    fila->tamanho--;
    printf("Desenfileirado: %d\n", item);
    return item;
}

// Ver primeiro elemento sem remover
int front(FilaCircular* fila) {
    if (filaVazia(fila)) {
        printf("Fila vazia!\n");
        return -1;
    }
    return fila->array[fila->frente];
}

// Ver último elemento sem remover
int rear(FilaCircular* fila) {
    if (filaVazia(fila)) {
        printf("Fila vazia!\n");
        return -1;
    }
    int pos = (fila->tras - 1 + fila->capacidade) % fila->capacidade;
    return fila->array[pos];
}

// Imprimir fila
void imprimirFila(FilaCircular* fila) {
    if (filaVazia(fila)) {
        printf("Fila vazia\n");
        return;
    }
    
    printf("Fila (frente → trás): ");
    int i = fila->frente;
    for (int count = 0; count < fila->tamanho; count++) {
        printf("%d ", fila->array[i]);
        i = (i + 1) % fila->capacidade;
    }
    printf("\n");
}

// Liberar memória
void liberarFila(FilaCircular* fila) {
    free(fila->array);
    free(fila);
}

// Exemplo de uso
int main() {
    FilaCircular* fila = criarFila(5);
    
    enqueue(fila, 10);
    enqueue(fila, 20);
    enqueue(fila, 30);
    
    imprimirFila(fila);
    printf("Primeiro: %d, Último: %d\n\n", front(fila), rear(fila));
    
    dequeue(fila);
    dequeue(fila);
    
    enqueue(fila, 40);
    enqueue(fila, 50);
    
    imprimirFila(fila);
    
    liberarFila(fila);
    return 0;
}
```

#### Aplicação Prática: Simulação de Atendimento
```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_FILA 20

typedef struct {
    int clientes[MAX_FILA];
    int frente, tras, tamanho;
} FilaAtendimento;

void inicializarFila(FilaAtendimento* f) {
    f->frente = 0;
    f->tras = 0;
    f->tamanho = 0;
}

bool chegaCliente(FilaAtendimento* f, int numero) {
    if (f->tamanho >= MAX_FILA) {
        printf("❌ Cliente %d: Fila cheia! Desistiu.\n", numero);
        return false;
    }
    f->clientes[f->tras] = numero;
    f->tras = (f->tras + 1) % MAX_FILA;
    f->tamanho++;
    printf("➡️ Cliente %d entrou na fila. Tamanho: %d\n", numero, f->tamanho);
    return true;
}

int atenderCliente(FilaAtendimento* f) {
    if (f->tamanho == 0) {
        printf("😴 Nenhum cliente na fila.\n");
        return -1;
    }
    int cliente = f->clientes[f->frente];
    f->frente = (f->frente + 1) % MAX_FILA;
    f->tamanho--;
    printf("✅ Cliente %d atendido. Restantes: %d\n", cliente, f->tamanho);
    return cliente;
}

int main() {
    FilaAtendimento fila;
    inicializarFila(&fila);
    
    printf("=== Simulação de Atendimento Bancário ===\n\n");
    
    // Simulação de chegadas e atendimentos
    chegaCliente(&fila, 1);
    chegaCliente(&fila, 2);
    chegaCliente(&fila, 3);
    
    printf("\n--- Início do atendimento ---\n");
    atenderCliente(&fila);
    
    chegaCliente(&fila, 4);
    chegaCliente(&fila, 5);
    
    printf("\n--- Continuando atendimento ---\n");
    atenderCliente(&fila);
    atenderCliente(&fila);
    atenderCliente(&fila);
    atenderCliente(&fila);
    
    printf("\n--- Fim do expediente ---\n");
    atenderCliente(&fila);  // Fila vazia
    
    return 0;
}
```

#### Tipos Especiais
1. **Fila Circular**: Usa array circular para evitar desperdício
2. **Deque**: Inserção/remoção em ambas as extremidades
3. **Fila de Prioridade**: Elementos têm prioridade (heap)

#### Aplicações Práticas
✅ Sistemas de impressão (fila de impressão)  
✅ Gerenciamento de processos em SO (scheduler)  
✅ Buffers de comunicação (redes, I/O)  
✅ Simulações (atendimento, trânsito)  
✅ Algoritmos de travessia em largura (BFS)  
✅ Cache de requisições em servidores  

### Comparação: Pilha vs Fila

| Característica | Pilha (LIFO) | Fila (FIFO) |
|----------------|--------------|-------------|
| Ordem de saída | Último que entrou | Primeiro que entrou |
| Inserção | Topo | Final (rear) |
| Remoção | Topo | Início (front) |
| Analogia | Pilha de pratos | Fila de banco |
| Complexidade | O(1) todas ops | O(1) todas ops |

### TAD vs Implementação
- **TAD**: Define O QUE fazer (interface, operações)
- **Implementação**: Define COMO fazer (array, lista encadeada)

Ambas as estruturas podem ser implementadas com arrays ou listas encadeadas, cada uma com trade-offs diferentes.

---

## 5️⃣ Listas Encadeadas

### Conceito Fundamental
Listas encadeadas são **estruturas de dados dinâmicas** onde elementos (nós) são armazenados em **posições não contíguas** da memória, conectados através de **ponteiros**. Cada nó contém dados e referência(s) ao(s) próximo(s) nó(s).

### Definição Formal
Uma lista encadeada L é uma sequência de n ≥ 0 nós, onde cada nó i contém:
- **Campo de dados**: `data[i]`
- **Ponteiro(s)**: `next[i]` (e opcionalmente `prev[i]`)

### Tipos de Listas Encadeadas

#### **1. Lista Simplesmente Encadeada**

**Estrutura do Nó**:
```c
typedef struct Node {
    int data;           // Dados armazenados
    struct Node* next;  // Ponteiro para próximo nó
} Node;
```

**Representação Visual**:
```
[10|*] -> [20|*] -> [30|*] -> [40|NULL]
 ^
head
```

**Características**:
- Cada nó aponta apenas para o próximo
- Travessia apenas em uma direção (frente)
- Inserção/remoção O(1) se posição conhecida
- Acesso sequencial O(n)

#### **2. Lista Duplamente Encadeada**

**Estrutura do Nó**:
```c
typedef struct Node {
    int data;
    struct Node* next;  // Próximo
    struct Node* prev;  // Anterior
} Node;
```

**Representação Visual**:
```
NULL<-[*|10|*]<->[*|20|*]<->[*|30|*]<->[*|40|*]->NULL
       ^
      head
```

**Características**:
- Cada nó aponta para próximo E anterior
- Travessia em ambas as direções
- Remoção mais eficiente (não precisa de nó anterior)
- Maior overhead de memória (dois ponteiros)

#### **3. Lista Circular**

**Representação Visual**:
```
[10|*] -> [20|*] -> [30|*] -> [40|*]
  ^                              |
  |______________________________|
```

**Características**:
- Último nó aponta de volta para o primeiro
- Não há NULL no final
- Útil para aplicações round-robin

### Operações Fundamentais e Complexidade

| Operação | Lista Encadeada | Array |
|----------|-----------------|-------|
| Acesso por índice | O(n) | O(1) |
| Busca | O(n) | O(n) |
| Inserção no início | O(1) | O(n) |
| Inserção no final | O(n)* ou O(1)** | O(1)*** |
| Inserção no meio | O(1)**** | O(n) |
| Remoção no início | O(1) | O(n) |
| Remoção no final | O(n)* ou O(1)** | O(1) |
| Remoção no meio | O(1)**** | O(n) |

\* Lista simples sem ponteiro para final  
** Com ponteiro para o final (tail)  
*** Array dinâmico, pode ser O(n) ocasionalmente  
**** Assumindo que você já tem ponteiro para o nó

### Vantagens das Listas Encadeadas
✅ **Tamanho dinâmico** - Cresce/diminui conforme necessário  
✅ **Inserção/remoção eficiente** - O(1) em posições conhecidas  
✅ **Não requer memória contígua** - Funciona com memória fragmentada  
✅ **Sem realocação** - Não precisa copiar dados ao crescer  

### Desvantagens
❌ **Acesso sequencial** - Sem acesso direto O(1) por índice  
❌ **Overhead de memória** - Ponteiros adicionais  
❌ **Cache locality ruim** - Nós dispersos na memória  
❌ **Mais complexo** - Gerenciamento de ponteiros  

### Quando Usar Lista Encadeada?

**Use lista encadeada quando**:
- Inserções/remoções frequentes no início/meio
- Tamanho imprevisível e altamente variável
- Não precisa de acesso aleatório
- Memória fragmentada

**Use array quando**:
- Acesso aleatório frequente
- Tamanho conhecido ou previsível
- Iterações sequenciais (melhor cache)
- Memória limitada (sem overhead de ponteiros)

### Aplicações Práticas
✅ Implementação de pilhas e filas dinâmicas  
✅ Gerenciamento de memória (free lists)  
✅ Listas de adjacência em grafos  
✅ Navegação de histórico (browser)  
✅ Playlists de música  
✅ Editor de texto (buffer gap, rope)  
✅ Tabelas hash com encadeamento (collision resolution)  

### Exemplo Completo: Operações Básicas

```c
// Criação de nó
Node* criarNo(int data) {
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->data = data;
    novo->next = NULL;
    return novo;
}

// Inserção no início - O(1)
void inserirInicio(Node** head, int data) {
    Node* novo = criarNo(data);
    novo->next = *head;
    *head = novo;
}

// Inserção no final - O(n)
void inserirFinal(Node** head, int data) {
    Node* novo = criarNo(data);
    
    if (*head == NULL) {
        *head = novo;
        return;
    }
    
    Node* temp = *head;
    while (temp->next != NULL)
        temp = temp->next;
    
    temp->next = novo;
}

// Busca - O(n)
Node* buscar(Node* head, int data) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->data == data)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

// Remoção - O(n)
void remover(Node** head, int data) {
    Node* temp = *head;
    Node* prev = NULL;
    
    // Se é o primeiro nó
    if (temp != NULL && temp->data == data) {
        *head = temp->next;
        free(temp);
        return;
    }
    
    // Buscar o nó
    while (temp != NULL && temp->data != data) {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp == NULL) return;  // Não encontrado
    
    prev->next = temp->next;
    free(temp);
}

// Imprimir - O(n)
void imprimir(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Liberar memória - O(n)
void liberar(Node** head) {
    Node* atual = *head;
    Node* proximo;
    
    while (atual != NULL) {
        proximo = atual->next;
        free(atual);
        atual = proximo;
    }
    
    *head = NULL;
}
```

---

## 📊 Tabela Comparativa: Todas as Estruturas

### Complexidade de Operações

| Estrutura | Acesso | Busca | Inserção | Remoção | Espaço |
|-----------|--------|-------|----------|---------|---------|
| **Array** | O(1) | O(n) | O(n) | O(n) | O(n) |
| **Array Ordenado** | O(1) | O(log n) | O(n) | O(n) | O(n) |
| **Lista Encadeada** | O(n) | O(n) | O(1)* | O(1)* | O(n) |
| **Pilha** | O(n) | O(n) | O(1) | O(1) | O(n) |
| **Fila** | O(n) | O(n) | O(1) | O(1) | O(n) |

\* Com ponteiro para o nó

### Características Principais

| Estrutura | Tamanho | Memória | Acesso | Melhor Para |
|-----------|---------|---------|--------|-------------|
| **Array** | Fixo | Contígua | Aleatório O(1) | Acesso frequente por índice |
| **Lista Encadeada** | Dinâmico | Dispersa | Sequencial O(n) | Inserções/remoções frequentes |
| **Pilha** | Variável | Depende | Topo O(1) | LIFO (último entra, primeiro sai) |
| **Fila** | Variável | Depende | Extremidades O(1) | FIFO (primeiro entra, primeiro sai) |

---

## 🎓 Conceitos Teóricos Importantes

### 1. Complexidade Computacional

#### Notação Big O
Descreve o comportamento assintótico - como o algoritmo escala quando n → ∞

**Classes de complexidade (do mais rápido ao mais lento)**:
- **O(1)** - Constante: Não depende do tamanho da entrada
- **O(log n)** - Logarítmica: Divide problema ao meio (busca binária)
- **O(n)** - Linear: Cresce proporcionalmente (busca linear)
- **O(n log n)** - Linearítmica: Divide e conquista eficiente (merge/quick sort)
- **O(n²)** - Quadrática: Dois loops aninhados (bubble/insertion sort)
- **O(2ⁿ)** - Exponencial: Praticamente inviável para n > 30

### 2. Trade-offs Fundamentais

#### Tempo vs Espaço
- Arrays: Menos memória, acesso O(1)
- Listas: Mais memória (ponteiros), inserção O(1)

#### Estabilidade vs Performance
- Merge Sort: Estável, mas usa O(n) espaço
- Quick Sort: Mais rápido, mas não estável

#### Simplicidade vs Eficiência
- Insertion Sort: Simples, O(n²)
- Quick Sort: Complexo, O(n log n)

### 3. Tipos Abstratos de Dados (TAD)

**TAD** define **O QUE** fazer (interface, operações, comportamento)  
**Implementação** define **COMO** fazer (estrutura concreta, algoritmos)

**Exemplo**:
- **TAD Pilha**: Define push(), pop(), peek()
- **Implementação**: Pode usar array ou lista encadeada

Este conceito permite:
- **Encapsulamento**: Esconde detalhes internos
- **Abstração**: Foca na funcionalidade, não na implementação
- **Substituibilidade**: Trocar implementação sem quebrar código cliente

---

## 🎯 Guia de Escolha de Estrutura de Dados

### Decisão Baseada em Operações Predominantes

```
Precisa de acesso aleatório frequente?
│
├─ Sim → ARRAY
│   └─ Muitas buscas? → ARRAY ORDENADO + busca binária
│
└─ Não
    │
    ├─ Inserções/remoções no início/meio?
    │   └─ Sim → LISTA ENCADEADA
    │
    ├─ Precisa de LIFO (último entra, primeiro sai)?
    │   └─ Sim → PILHA
    │
    ├─ Precisa de FIFO (primeiro entra, primeiro sai)?
    │   └─ Sim → FILA
    │
    └─ Muitas operações de ordenação?
        └─ Sim → Escolha algoritmo baseado em:
            ├─ n pequeno (< 50): INSERTION SORT
            ├─ n médio/grande: QUICK SORT
            ├─ Estabilidade necessária: MERGE SORT
            └─ Espaço limitado: HEAP SORT
```

### Cenários Práticos

1. **Sistema de gerenciamento de alunos**
   - Array ordenado + busca binária (muitas consultas por matrícula)

2. **Editor de texto (undo/redo)**
   - Pilha (desfazer ações em ordem reversa)

3. **Sistema de impressão**
   - Fila (atender na ordem de chegada)

4. **Playlist de músicas**
   - Lista encadeada (inserir/remover no meio)

5. **Processamento de grandes datasets**
   - Quick Sort ou Merge Sort (eficiência)

---

## 📈 Gráfico de Crescimento de Complexidade

Para n = 1.000.000 de elementos:

| Complexidade | Operações | Tempo Estimado* |
|--------------|-----------|-----------------|
| O(1) | 1 | < 1 ns |
| O(log n) | 20 | 20 ns |
| O(n) | 1.000.000 | 1 ms |
| O(n log n) | 20.000.000 | 20 ms |
| O(n²) | 1.000.000.000.000 | ~17 minutos |
| O(2ⁿ) | Para n=30: ~1 bilhão | ~1 segundo |
| O(2ⁿ) | Para n=40: ~1 trilhão | ~18 minutos |

\* Assumindo 1 operação = 1 nanosegundo (CPU moderna a ~1 GHz)  
**Observação**: O crescimento exponencial torna O(2ⁿ) inviável para n > 30-40.

**Lição**: Complexidade importa enormemente para grandes datasets!

---

## 🔑 Pontos-Chave para Lembrar

### Vetores e Matrizes
- ✅ Acesso O(1), mas inserção/remoção O(n)
- ✅ Memória contígua = excelente cache
- ✅ Use quando acesso aleatório é prioritário

### Ordenação
- ✅ Quick Sort para uso geral
- ✅ Merge Sort quando estabilidade é necessária
- ✅ Insertion Sort para arrays pequenos ou quase ordenados

### Busca
- ✅ Linear O(n) para dados não ordenados
- ✅ Binária O(log n) para dados ordenados
- ✅ Ordenar vale a pena se múltiplas buscas

### Pilhas e Filas
- ✅ Pilha = LIFO, Fila = FIFO
- ✅ Todas as operações em O(1)
- ✅ TAD pode ter múltiplas implementações

### Listas Encadeadas
- ✅ Dinâmicas, flexíveis
- ✅ Inserção/remoção O(1) com ponteiro
- ✅ Acesso sequencial O(n)

---

## 📚 Referências e Materiais de Estudo

### Documentação Detalhada por Tópico
- [Vetores e Matrizes](../02-vetor-matriz/README.md)
- [Métodos de Ordenação](../03-metodos-ordenacao/README.md)
- [Métodos de Pesquisa](../04-pesquisa/README.md)
- [Pilhas e Filas](../05-pilhas-filas/README.md)
- [Listas Encadeadas](../06-lista-encadeada/README.md)

### Livros Recomendados
1. **Cormen et al. (2022)** - *Introduction to Algorithms*, 4th Edition (CLRS)
2. **Knuth (1997-presente)** - *The Art of Computer Programming*, Volumes 1-4B (série em publicação)
3. **Sedgewick & Wayne (2011)** - *Algorithms*, 4th Edition

*Nota: As datas referem-se às edições usadas como referência principal para este material educacional.*

### Ferramentas de Visualização
- [VisuAlgo](https://visualgo.net/) - Visualização interativa de algoritmos
- [Data Structure Visualizations](https://www.cs.usfca.edu/~galles/visualization/)

---

## 🎯 Exercícios de Revisão

### Questões Teóricas

1. **Por que arrays têm acesso O(1) por índice?**
   - Resposta: Cálculo direto do endereço: `base + (índice × tamanho_elemento)`

2. **Qual a diferença entre estável e in-place?**
   - Estável: Mantém ordem relativa de elementos iguais
   - In-place: Usa O(1) memória adicional

3. **Quando usar lista encadeada ao invés de array?**
   - Quando: Inserções/remoções frequentes, tamanho imprevisível, não precisa acesso aleatório

4. **Por que busca binária é O(log n)?**
   - A cada iteração, elimina metade das possibilidades. log₂(n) iterações até 1 elemento.

5. **Qual a diferença entre TAD e estrutura de dados?**
   - TAD: Especificação abstrata (O QUE)
   - Estrutura: Implementação concreta (COMO)

### Desafios Práticos

1. Implemente uma pilha usando lista encadeada
2. Implemente uma fila circular com array
3. Modifique Quick Sort para ser estável
4. Implemente busca binária recursiva
5. Crie uma lista duplamente encadeada com as operações básicas

---

## 🎓 Conclusão

Este resumo consolidou os cinco tópicos fundamentais de estruturas de dados:
1. **Vetores e Matrizes** - Base de tudo, acesso direto
2. **Ordenação** - Organização eficiente de dados
3. **Busca** - Localização rápida de elementos
4. **Pilhas e Filas** - TADs com acesso restrito
5. **Listas Encadeadas** - Estruturas dinâmicas flexíveis

### Mensagem Final

Não existe estrutura de dados "melhor" universal. A escolha correta depende de:
- Operações predominantes
- Tamanho dos dados
- Restrições de memória
- Requisitos de performance

**Domine os fundamentos, entenda os trade-offs, escolha sabiamente!** 🚀

---

## 📅 Próximos Passos

Após dominar esses conceitos fundamentais, você estará preparado para:
- Árvores (BST, AVL, B-Trees)
- Grafos e algoritmos de caminho mínimo
- Tabelas hash e funções de dispersão
- Estruturas de dados avançadas (Heaps, Tries, etc.)
- Algoritmos de programação dinâmica
- Análise de algoritmos mais profunda

**Continue estudando e praticando! A jornada está apenas começando.** 💪
