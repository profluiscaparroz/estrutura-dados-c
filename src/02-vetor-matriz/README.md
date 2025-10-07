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
Um **vetor** (ou array) é uma estrutura de dados que armazena uma coleção de elementos do mesmo tipo em posições consecutivas da memória. Em C, vetores são a base fundamental para muitas outras estruturas de dados e são essenciais para compreender programação eficiente.

**Por que vetores são importantes?**
- Permitem armazenar múltiplos valores relacionados em uma única variável
- Facilitam o processamento de grandes quantidades de dados
- São a base para estruturas mais complexas como listas, pilhas e filas
- Oferecem acesso extremamente rápido aos elementos

#### Características dos Vetores:

- **Acesso direto:** O(1) - Tempo constante para acessar qualquer elemento
  - Você pode acessar diretamente o elemento na posição `i` usando `vetor[i]`
  - Não precisa percorrer outros elementos para chegar ao desejado
  - Exemplo: Se você quer o 100º elemento, acessa diretamente `vetor[99]` (lembrando que índices começam em 0)

- **Memória contígua:** Elementos armazenados sequencialmente na memória RAM
  - Os elementos ocupam posições adjacentes na memória
  - Se um elemento está no endereço X, o próximo está em X + tamanho_do_tipo
  - Isso permite cálculos rápidos de endereços: `endereço_do_elemento_i = endereço_base + i * sizeof(tipo)`
  - Melhora o desempenho devido à localidade de cache (cache locality)

- **Índice baseado em zero:** Primeiro elemento no índice 0, último em (tamanho-1)
  - Esta convenção vem da matemática de ponteiros: `vetor[i]` é equivalente a `*(vetor + i)`
  - Um vetor de 5 elementos tem índices 0, 1, 2, 3, 4 (nunca 5!)
  - Acessar `vetor[5]` em um vetor de tamanho 5 causa erro de acesso à memória (buffer overflow)

- **Tamanho fixo:** O tamanho deve ser definido e não pode mudar facilmente
  - **Vetores estáticos:** Tamanho definido em tempo de compilação
  - **Vetores dinâmicos:** Tamanho definido em tempo de execução com `malloc`, mas ainda fixo após alocação
  - Para "aumentar" um vetor dinâmico, é necessário alocar novo espaço e copiar os dados (operação custosa)

#### Declaração e Inicialização:

**1. Declaração Básica (Sem Inicialização):**
```c
int numeros[5];  // Cria vetor com 5 posições
// ⚠️ CUIDADO: Valores iniciais são indefinidos (lixo de memória)
// É boa prática inicializar antes de usar!
```

**2. Declaração com Inicialização Completa:**
```c
int numeros[5] = {10, 20, 30, 40, 50};
// Cada posição recebe um valor específico
// numeros[0] = 10, numeros[1] = 20, ..., numeros[4] = 50
```

**3. Declaração com Inicialização Parcial:**
```c
int numeros[5] = {10, 20};
// numeros[0] = 10, numeros[1] = 20
// numeros[2] = 0, numeros[3] = 0, numeros[4] = 0
// Posições não inicializadas recebem 0
```

**4. Inicialização com Zeros:**
```c
int numeros[5] = {0};  // Todos os elementos = 0
// Forma rápida e segura de zerar um vetor
```

**5. Tamanho Inferido pelo Compilador:**
```c
int numeros[] = {10, 20, 30, 40, 50};
// Compilador calcula tamanho = 5
// Útil quando você não quer contar os elementos manualmente
```

**6. Alocação Dinâmica (Heap):**
```c
int *numeros = malloc(5 * sizeof(int));
// Aloca memória em tempo de execução
// Permite tamanho variável (determinado durante execução)
// ⚠️ IMPORTANTE: Sempre verificar se malloc retornou NULL
// ⚠️ IMPORTANTE: Sempre fazer free(numeros) ao terminar de usar!

// Exemplo completo com verificação:
int tamanho = 5;
int *numeros = malloc(tamanho * sizeof(int));
if (numeros == NULL) {
    printf("Erro: Não foi possível alocar memória!\n");
    return 1;
}
// ... usar o vetor ...
free(numeros);  // Libera a memória
```

**7. Alocação Dinâmica Inicializada com Zeros:**
```c
int *numeros = calloc(5, sizeof(int));
// Similar ao malloc, mas inicializa tudo com 0
// calloc(n, size) = malloc(n * size) + inicialização com zeros
```

---

## 📊 Operações Básicas com Vetores - Exemplos Detalhados

### 1. Acesso e Modificação de Elementos

**Acesso por Índice:**
```c
int vetor[5] = {10, 20, 30, 40, 50};

// Leitura
int valor = vetor[2];  // valor = 30
printf("Elemento na posição 2: %d\n", vetor[2]);

// Modificação
vetor[2] = 99;  // Agora vetor = {10, 20, 99, 40, 50}

// Complexidade: O(1) - tempo constante
// Explicação: O acesso é direto via cálculo de endereço
```

### 2. Percorrer um Vetor (Traversal)

**Percorrendo do início ao fim:**
```c
int vetor[5] = {10, 20, 30, 40, 50};

// Método 1: for tradicional
for (int i = 0; i < 5; i++) {
    printf("%d ", vetor[i]);
}
// Saída: 10 20 30 40 50

// Método 2: while
int i = 0;
while (i < 5) {
    printf("%d ", vetor[i]);
    i++;
}

// Complexidade: O(n) onde n é o tamanho do vetor
// Explicação: Precisamos visitar cada elemento uma vez
```

### 3. Buscar um Elemento (Busca Linear)

```c
int buscar(int vetor[], int tamanho, int valor) {
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i] == valor) {
            return i;  // Retorna a posição onde encontrou
        }
    }
    return -1;  // Retorna -1 se não encontrou
}

// Exemplo de uso:
int numeros[5] = {10, 20, 30, 40, 50};
int posicao = buscar(numeros, 5, 30);
if (posicao != -1) {
    printf("Encontrado na posição %d\n", posicao);  // Saída: posição 2
}

// Complexidade: 
// - Melhor caso: O(1) - elemento está na primeira posição
// - Pior caso: O(n) - elemento está na última posição ou não existe
// - Caso médio: O(n/2) = O(n) - em média, percorre metade do vetor
```

### 4. Inserir Elemento no Final

```c
int inserir_no_final(int *vetor, int *tamanho, int valor, int capacidade) {
    if (*tamanho >= capacidade) {
        printf("Erro: Vetor cheio!\n");
        return 0;  // Falha
    }
    
    vetor[*tamanho] = valor;  // Insere na próxima posição livre
    (*tamanho)++;              // Incrementa o tamanho
    return 1;  // Sucesso
}

// Exemplo:
int numeros[10] = {10, 20, 30};  // capacidade = 10, tamanho atual = 3
int tamanho = 3;
inserir_no_final(numeros, &tamanho, 40, 10);
// Agora: numeros = {10, 20, 30, 40, ...}, tamanho = 4

// Complexidade: O(1) - operação de tempo constante
// Explicação: Apenas adiciona no final, sem mover elementos
```

### 5. Inserir Elemento em Posição Específica

```c
int inserir_na_posicao(int vetor[], int *tamanho, int posicao, int valor, int capacidade) {
    // Validações
    if (*tamanho >= capacidade) {
        printf("Erro: Vetor cheio!\n");
        return 0;
    }
    if (posicao < 0 || posicao > *tamanho) {
        printf("Erro: Posição inválida!\n");
        return 0;
    }
    
    // Desloca elementos para a direita
    // Começa do final e vai até a posição desejada
    for (int i = *tamanho; i > posicao; i--) {
        vetor[i] = vetor[i-1];
    }
    
    vetor[posicao] = valor;  // Insere o novo valor
    (*tamanho)++;
    return 1;
}

// Exemplo visual:
// Vetor inicial: [10, 20, 30, 40, 50]
// Inserir 99 na posição 2:
//   Passo 1: [10, 20, 30, 40, 50, _] (aumenta espaço)
//   Passo 2: [10, 20, 30, 40, 40, 50] (desloca 40)
//   Passo 3: [10, 20, 30, 30, 40, 50] (desloca 30)
//   Passo 4: [10, 20, 99, 30, 40, 50] (insere 99)

// Complexidade: O(n) onde n é o número de elementos após a posição
// Explicação: Precisa deslocar elementos para abrir espaço
// - Melhor caso: O(1) - inserir no final
// - Pior caso: O(n) - inserir no início (desloca todos)
```

### 6. Remover Elemento de Posição Específica

```c
int remover_da_posicao(int vetor[], int *tamanho, int posicao) {
    if (posicao < 0 || posicao >= *tamanho) {
        printf("Erro: Posição inválida!\n");
        return 0;
    }
    
    // Desloca elementos para a esquerda
    for (int i = posicao; i < *tamanho - 1; i++) {
        vetor[i] = vetor[i+1];
    }
    
    (*tamanho)--;
    return 1;
}

// Exemplo visual:
// Vetor inicial: [10, 20, 30, 40, 50]
// Remover da posição 2 (valor 30):
//   Passo 1: [10, 20, 40, 40, 50] (copia 40 para posição 2)
//   Passo 2: [10, 20, 40, 50, 50] (copia 50 para posição 3)
//   Resultado: [10, 20, 40, 50] (tamanho = 4)

// Complexidade: O(n)
// Explicação: Similar à inserção, precisa deslocar elementos
// - Melhor caso: O(1) - remover do final
// - Pior caso: O(n) - remover do início
```

### 7. Somar Todos os Elementos

```c
int somar_elementos(int vetor[], int tamanho) {
    int soma = 0;
    for (int i = 0; i < tamanho; i++) {
        soma += vetor[i];
    }
    return soma;
}

// Exemplo:
int numeros[5] = {10, 20, 30, 40, 50};
int resultado = somar_elementos(numeros, 5);
// resultado = 10 + 20 + 30 + 40 + 50 = 150

// Complexidade: O(n)
// Explicação: Precisa visitar cada elemento uma vez
```

### 8. Encontrar Maior e Menor Elemento

```c
void encontrar_maior_menor(int vetor[], int tamanho, int *maior, int *menor) {
    if (tamanho == 0) return;
    
    *maior = vetor[0];  // Assume primeiro como maior
    *menor = vetor[0];  // Assume primeiro como menor
    
    for (int i = 1; i < tamanho; i++) {
        if (vetor[i] > *maior) {
            *maior = vetor[i];
        }
        if (vetor[i] < *menor) {
            *menor = vetor[i];
        }
    }
}

// Exemplo:
int numeros[5] = {30, 10, 50, 20, 40};
int maior, menor;
encontrar_maior_menor(numeros, 5, &maior, &menor);
// maior = 50, menor = 10

// Complexidade: O(n)
// Explicação: Uma passada pelo vetor, comparando cada elemento
// Número de comparações: 2(n-1) no pior caso
```

### 9. Reverter um Vetor

```c
void reverter_vetor(int vetor[], int tamanho) {
    int inicio = 0;
    int fim = tamanho - 1;
    
    while (inicio < fim) {
        // Troca elementos das extremidades
        int temp = vetor[inicio];
        vetor[inicio] = vetor[fim];
        vetor[fim] = temp;
        
        inicio++;
        fim--;
    }
}

// Exemplo visual:
// Inicial: [10, 20, 30, 40, 50]
// Passo 1: [50, 20, 30, 40, 10] (troca 10↔50)
// Passo 2: [50, 40, 30, 20, 10] (troca 20↔40)
// Final:   [50, 40, 30, 20, 10] (30 fica no meio)

// Complexidade: O(n/2) = O(n)
// Explicação: Percorre metade do vetor fazendo trocas
// Número de trocas: n/2
```

### 10. Copiar um Vetor

```c
void copiar_vetor(int origem[], int destino[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        destino[i] = origem[i];
    }
}

// Ou usando memcpy (mais rápido):
#include <string.h>
memcpy(destino, origem, tamanho * sizeof(int));

// Complexidade: O(n)
// Explicação: Precisa copiar cada elemento individualmente
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

Uma **matriz** é um vetor de vetores, organizando dados em **linhas e colunas**, formando uma estrutura bidimensional. Matrizes são fundamentais para representar dados tabulares, imagens, grafos e muito mais.

**Por que matrizes são importantes?**
- Representam dados em forma de tabela (planilhas, grades)
- Essenciais em álgebra linear e computação científica
- Usadas em processamento de imagens (cada pixel é um elemento)
- Representam grafos através de matrizes de adjacência
- Fundamentais em machine learning e deep learning

**Visualização:**
```
Matriz 3x4 (3 linhas, 4 colunas):

        coluna 0  coluna 1  coluna 2  coluna 3
linha 0    [1]       [2]       [3]       [4]
linha 1    [5]       [6]       [7]       [8]
linha 2    [9]       [10]      [11]      [12]

Acesso: matriz[linha][coluna]
Exemplo: matriz[1][2] = 7
```

### Representação na Memória

**Matrizes estáticas em C são armazenadas em row-major order (ordem por linhas):**
```
Matriz 3x4:
[1]  [2]  [3]  [4]
[5]  [6]  [7]  [8]
[9]  [10] [11] [12]

Na memória (sequencial):
[1][2][3][4][5][6][7][8][9][10][11][12]
└─ linha 0 ─┘└─ linha 1 ─┘└─ linha 2 ─┘

Endereço do elemento [i][j]:
endereço_base + (i * num_colunas + j) * sizeof(tipo)
```

**Esta organização tem implicações importantes:**
- Acessar elementos da mesma linha é mais rápido (cache-friendly)
- Percorrer por colunas pode ser mais lento (cache misses)
- Processamento por linhas é geralmente mais eficiente

#### Declaração de Matrizes:

**1. Declaração Básica:**
```c
int matriz[3][4];  // 3 linhas, 4 colunas (12 elementos total)
// ⚠️ Valores iniciais são indefinidos
```

**2. Inicialização Completa:**
```c
int matriz[2][3] = {
    {1, 2, 3},    // linha 0
    {4, 5, 6}     // linha 1
};
// matriz[0][0]=1, matriz[0][1]=2, ..., matriz[1][2]=6
```

**3. Inicialização Alternativa (forma linear):**
```c
int matriz[2][3] = {1, 2, 3, 4, 5, 6};
// Compilador distribui automaticamente:
// {1,2,3} -> linha 0
// {4,5,6} -> linha 1
```

**4. Inicialização Parcial:**
```c
int matriz[2][3] = {
    {1, 2},       // linha 0: [1, 2, 0]
    {4}           // linha 1: [4, 0, 0]
};
// Elementos não especificados = 0
```

**5. Inicialização com Zeros:**
```c
int matriz[3][4] = {0};  // Todos os elementos = 0
// Forma rápida e segura de zerar uma matriz
```

**6. Tamanho Inferido (primeira dimensão):**
```c
int matriz[][3] = {
    {1, 2, 3},
    {4, 5, 6}
};
// Compilador infere: matriz[2][3]
// ⚠️ Número de colunas DEVE ser especificado!
```

**7. Alocação Dinâmica - Método 1 (array de ponteiros):**
```c
int linhas = 3, colunas = 4;
int **matriz = malloc(linhas * sizeof(int*));

for (int i = 0; i < linhas; i++) {
    matriz[i] = malloc(colunas * sizeof(int));
}

// Usar: matriz[i][j]

// Liberar memória:
for (int i = 0; i < linhas; i++) {
    free(matriz[i]);
}
free(matriz);
```

**8. Alocação Dinâmica - Método 2 (bloco contíguo):**
```c
int linhas = 3, colunas = 4;
int *matriz = malloc(linhas * colunas * sizeof(int));

// Acessar elemento [i][j]:
// matriz[i * colunas + j]

// Ou criar uma macro:
#define MAT(i,j) matriz[(i)*colunas + (j)]
// Usar: MAT(1,2) = 10;

// Liberar: free(matriz);
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

## 📐 Operações com Matrizes - Exemplos Detalhados

### 1. Acesso e Modificação de Elementos

```c
int matriz[3][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}
};

// Leitura
int valor = matriz[1][2];  // linha 1, coluna 2 = 7

// Modificação
matriz[1][2] = 99;  // Agora matriz[1][2] = 99

// Complexidade: O(1) - acesso direto
```

### 2. Percorrer uma Matriz

**Percorrer por linhas (mais eficiente):**
```c
int matriz[3][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}
};

// Percorre linha por linha
for (int i = 0; i < 3; i++) {           // Para cada linha
    for (int j = 0; j < 4; j++) {       // Para cada coluna
        printf("%d ", matriz[i][j]);
    }
    printf("\n");
}
// Saída:
// 1 2 3 4
// 5 6 7 8
// 9 10 11 12

// Complexidade: O(m × n) onde m=linhas, n=colunas
// Explicação: Visita cada um dos m×n elementos uma vez
```

**Percorrer por colunas:**
```c
// Percorre coluna por coluna
for (int j = 0; j < 4; j++) {           // Para cada coluna
    for (int i = 0; i < 3; i++) {       // Para cada linha
        printf("%d ", matriz[i][j]);
    }
    printf("\n");
}
// Saída:
// 1 5 9
// 2 6 10
// 3 7 11
// 4 8 12

// ⚠️ Menos eficiente que percorrer por linhas devido ao cache
```

### 3. Soma de Matrizes

```c
void somar_matrizes(int A[][4], int B[][4], int resultado[][4], int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            resultado[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Exemplo:
int A[2][3] = {{1, 2, 3}, {4, 5, 6}};
int B[2][3] = {{7, 8, 9}, {10, 11, 12}};
int C[2][3];

somar_matrizes(A, B, C, 2, 3);
// C = {{8, 10, 12}, {14, 16, 18}}

// Complexidade: O(m × n)
// Explicação: Percorre cada elemento uma vez
// Número de operações: m × n somas
```

### 4. Multiplicação de Matrizes

```c
void multiplicar_matrizes(int A[][10], int B[][10], int C[][10], 
                          int m, int n, int p) {
    // A é m×n, B é n×p, C será m×p
    
    // Inicializa C com zeros
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            C[i][j] = 0;
        }
    }
    
    // Calcula multiplicação
    for (int i = 0; i < m; i++) {           // Para cada linha de A
        for (int j = 0; j < p; j++) {       // Para cada coluna de B
            for (int k = 0; k < n; k++) {   // Produto escalar
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Exemplo visual:
// A (2×3):        B (3×2):        C (2×2):
// [1  2  3]       [7  8]          [?  ?]
// [4  5  6]       [9  10]         [?  ?]
//                 [11 12]
//
// C[0][0] = 1×7 + 2×9 + 3×11 = 7 + 18 + 33 = 58
// C[0][1] = 1×8 + 2×10 + 3×12 = 8 + 20 + 36 = 64
// C[1][0] = 4×7 + 5×9 + 6×11 = 28 + 45 + 66 = 139
// C[1][1] = 4×8 + 5×10 + 6×12 = 32 + 50 + 72 = 154
//
// Resultado C:
// [58   64]
// [139  154]

// Complexidade: O(m × n × p)
// Explicação: Três loops aninhados
// Número de multiplicações: m × n × p
// Número de somas: m × p × (n-1)
// ⚠️ Esta é uma operação custosa para matrizes grandes!
```

### 5. Transposição de Matriz

```c
void transpor(int matriz[][4], int transposta[][3], int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            transposta[j][i] = matriz[i][j];
        }
    }
}

// Exemplo visual:
// Original (2×3):     Transposta (3×2):
// [1  2  3]           [1  4]
// [4  5  6]           [2  5]
//                     [3  6]
//
// Linha vira coluna, coluna vira linha

// Complexidade: O(m × n)
// Explicação: Visita cada elemento uma vez
```

**Transposição in-place (matriz quadrada):**
```c
void transpor_quadrada(int matriz[][4], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {  // j começa em i+1
            // Troca matriz[i][j] com matriz[j][i]
            int temp = matriz[i][j];
            matriz[i][j] = matriz[j][i];
            matriz[j][i] = temp;
        }
    }
}

// ⚠️ Só funciona para matrizes quadradas (n×n)
// Complexidade: O(n²/2) = O(n²)
// Vantagem: Não precisa de matriz auxiliar
```

### 6. Buscar Elemento em Matriz

```c
int buscar_elemento(int matriz[][4], int linhas, int colunas, int valor, 
                    int *linha_result, int *coluna_result) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j] == valor) {
                *linha_result = i;
                *coluna_result = j;
                return 1;  // Encontrou
            }
        }
    }
    return 0;  // Não encontrou
}

// Exemplo:
int matriz[3][4] = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}};
int linha, coluna;

if (buscar_elemento(matriz, 3, 4, 7, &linha, &coluna)) {
    printf("Encontrado em [%d][%d]\n", linha, coluna);  // [1][2]
}

// Complexidade: O(m × n)
// - Melhor caso: O(1) - elemento na posição [0][0]
// - Pior caso: O(m×n) - elemento na última posição ou não existe
```

**Busca em matriz ordenada (algoritmo otimizado):**
```c
// Para matriz onde cada linha e coluna está ordenada
int buscar_matriz_ordenada(int matriz[][4], int linhas, int colunas, int valor) {
    int i = 0;
    int j = colunas - 1;  // Começa no canto superior direito
    
    while (i < linhas && j >= 0) {
        if (matriz[i][j] == valor) {
            return 1;  // Encontrou
        }
        else if (matriz[i][j] > valor) {
            j--;  // Move para esquerda
        }
        else {
            i++;  // Move para baixo
        }
    }
    return 0;  // Não encontrou
}

// Complexidade: O(m + n) - muito melhor que O(m×n)!
// Funciona apenas para matrizes ordenadas
```

### 7. Somar Elementos da Diagonal Principal

```c
int somar_diagonal(int matriz[][4], int n) {
    int soma = 0;
    for (int i = 0; i < n; i++) {
        soma += matriz[i][i];  // Elementos onde linha == coluna
    }
    return soma;
}

// Exemplo:
// [1  2  3]
// [4  5  6]  -> diagonal: 1, 5, 9 -> soma = 15
// [7  8  9]

// Complexidade: O(n)
// Explicação: Visita apenas n elementos (não n²)
```

### 8. Rotação de Matriz 90 Graus

```c
void rotacionar_90(int matriz[][4], int n) {
    // Passo 1: Transpor a matriz
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            int temp = matriz[i][j];
            matriz[i][j] = matriz[j][i];
            matriz[j][i] = temp;
        }
    }
    
    // Passo 2: Inverter cada linha
    for (int i = 0; i < n; i++) {
        int esq = 0, dir = n-1;
        while (esq < dir) {
            int temp = matriz[i][esq];
            matriz[i][esq] = matriz[i][dir];
            matriz[i][dir] = temp;
            esq++;
            dir--;
        }
    }
}

// Exemplo visual:
// Original:          Após transpor:     Após inverter linhas:
// [1  2  3]          [1  4  7]          [7  4  1]
// [4  5  6]    ->    [2  5  8]    ->    [8  5  2]
// [7  8  9]          [3  6  9]          [9  6  3]
//
// Rotação 90° no sentido horário

// Complexidade: O(n²)
// Explicação: Transpor = O(n²/2), Inverter = O(n²/2), Total = O(n²)
```

### 9. Verificar Matriz Simétrica

```c
int eh_simetrica(int matriz[][4], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (matriz[i][j] != matriz[j][i]) {
                return 0;  // Não é simétrica
            }
        }
    }
    return 1;  // É simétrica
}

// Matriz simétrica: matriz[i][j] == matriz[j][i] para todo i,j
// Exemplo:
// [1  2  3]
// [2  5  6]  -> Simétrica (espelhada na diagonal)
// [3  6  9]

// Complexidade: O(n²/2) = O(n²)
// Apenas verifica metade dos elementos (acima da diagonal)
```

### 10. Preencher Matriz em Espiral

```c
void preencher_espiral(int matriz[][10], int n) {
    int valor = 1;
    int cima = 0, baixo = n-1, esq = 0, dir = n-1;
    
    while (cima <= baixo && esq <= dir) {
        // Preenche linha superior (esquerda -> direita)
        for (int j = esq; j <= dir; j++) {
            matriz[cima][j] = valor++;
        }
        cima++;
        
        // Preenche coluna direita (cima -> baixo)
        for (int i = cima; i <= baixo; i++) {
            matriz[i][dir] = valor++;
        }
        dir--;
        
        // Preenche linha inferior (direita -> esquerda)
        if (cima <= baixo) {
            for (int j = dir; j >= esq; j--) {
                matriz[baixo][j] = valor++;
            }
            baixo--;
        }
        
        // Preenche coluna esquerda (baixo -> cima)
        if (esq <= dir) {
            for (int i = baixo; i >= cima; i--) {
                matriz[i][esq] = valor++;
            }
            esq++;
        }
    }
}

// Exemplo para matriz 4×4:
// [1   2   3   4]
// [12  13  14  5]
// [11  16  15  6]
// [10  9   8   7]

// Complexidade: O(n²)
// Explicação: Preenche todos os n² elementos em ordem espiral
```

---

## ⚡ Análise de Complexidade Computacional - Detalhada

### O que é Complexidade Computacional?

A **complexidade computacional** mede a eficiência de um algoritmo em termos de:
- **Tempo:** Quantas operações são necessárias?
- **Espaço:** Quanta memória é necessária?

Usamos a **notação Big O** para descrever o comportamento assintótico (quando n cresce muito).

### Notações Comuns de Complexidade

**Do mais rápido para o mais lento:**

1. **O(1) - Constante:** Sempre executa o mesmo número de operações
   - Exemplo: Acessar `vetor[5]`
   - Não importa se o vetor tem 10 ou 1 milhão de elementos

2. **O(log n) - Logarítmica:** Cresce muito lentamente
   - Exemplo: Busca binária em vetor ordenado
   - Dobrar n adiciona apenas uma operação

3. **O(n) - Linear:** Cresce proporcionalmente ao tamanho
   - Exemplo: Percorrer um vetor
   - Dobrar n dobra o número de operações

4. **O(n log n) - Linearítmica:** Quase linear
   - Exemplo: Algoritmos eficientes de ordenação (Merge Sort, Quick Sort)
   - Melhor que O(n²) para grandes valores de n

5. **O(n²) - Quadrática:** Cresce rapidamente
   - Exemplo: Dois loops aninhados
   - Dobrar n quadruplica o número de operações

6. **O(n³) - Cúbica:** Muito lento para grandes n
   - Exemplo: Três loops aninhados
   - Multiplicação ingênua de matrizes

7. **O(2ⁿ) - Exponencial:** Extremamente lento
   - Exemplo: Problemas de força bruta
   - Impraticável para n > 30

**Comparação visual (para n = 100):**
```
O(1)        = 1 operação
O(log n)    ≈ 7 operações
O(n)        = 100 operações
O(n log n)  ≈ 700 operações
O(n²)       = 10.000 operações
O(n³)       = 1.000.000 operações
O(2ⁿ)       ≈ 1.267.650.600.228.229.401.496.703.205.376 operações (impraticável!)
```

### Complexidade de Operações em Vetores e Matrizes

#### **Vetores (Array 1D)**

| Operação | Complexidade | Explicação Detalhada |
|----------|--------------|----------------------|
| **Acesso** | O(1) | Cálculo direto: `endereço = base + i × sizeof(tipo)`. Uma operação aritmética. |
| **Modificação** | O(1) | Acessa e modifica diretamente. Uma ou duas operações. |
| **Busca (não ordenado)** | O(n) | No pior caso, verifica todos os n elementos. Média: n/2 comparações. |
| **Busca (ordenado)** | O(log n) | Busca binária: divide pela metade a cada passo. log₂(n) comparações. |
| **Inserção no final** | O(1)* | Se há espaço, apenas adiciona. *Amortizado se usar realocação dinâmica. |
| **Inserção no início** | O(n) | Precisa deslocar todos os n elementos uma posição à direita. |
| **Inserção no meio** | O(n) | Em média, desloca n/2 elementos. Pior caso: desloca n elementos. |
| **Remoção do final** | O(1) | Apenas decrementa o tamanho. Nenhum deslocamento. |
| **Remoção do início** | O(n) | Desloca todos os n-1 elementos à esquerda. |
| **Remoção do meio** | O(n) | Em média, desloca n/2 elementos. |
| **Percorrer** | O(n) | Visita cada um dos n elementos exatamente uma vez. |
| **Reverter** | O(n) | n/2 trocas, cada troca é O(1). Total: O(n). |
| **Copiar** | O(n) | Copia cada um dos n elementos. |
| **Somar elementos** | O(n) | Uma adição para cada elemento. n adições. |
| **Encontrar maior/menor** | O(n) | Uma ou duas comparações por elemento. n-1 iterações. |
| **Ordenação** | O(n²) ou O(n log n) | Bubble/Insertion: O(n²). Merge/Quick: O(n log n). |

**Análise Detalhada - Inserção no Meio:**
```c
// Inserir valor na posição k em vetor de tamanho n
void inserir(int v[], int n, int k, int valor) {
    for (int i = n; i > k; i--) {  // Loop executa (n-k) vezes
        v[i] = v[i-1];              // Cada iteração: 1 atribuição
    }
    v[k] = valor;                   // 1 atribuição final
}

// Análise de casos:
// Melhor caso (k = n): 0 deslocamentos -> O(1)
// Pior caso (k = 0): n deslocamentos -> O(n)
// Caso médio (k = n/2): n/2 deslocamentos -> O(n)
```

#### **Matrizes (Array 2D)**

| Operação | Complexidade | Explicação Detalhada |
|----------|--------------|----------------------|
| **Acesso** | O(1) | `endereço = base + (i × cols + j) × sizeof`. Operação aritmética constante. |
| **Busca Linear** | O(m × n) | Verifica todos os m×n elementos no pior caso. |
| **Busca (ordenada)** | O(m + n) | Algoritmo especial partindo do canto. Muito melhor que O(m×n)! |
| **Percorrer** | O(m × n) | Visita cada um dos m×n elementos uma vez. |
| **Soma de matrizes** | O(m × n) | Uma adição para cada um dos m×n elementos. |
| **Multiplicação** | O(m × n × p) | Três loops aninhados. Para cada elemento de C (m×n), faz p multiplicações. |
| **Transposição** | O(m × n) | Copia cada elemento uma vez para nova posição. |
| **Transposição in-place** | O(n²) | Apenas matrizes quadradas. n²/2 trocas. |
| **Inserção de linha** | O(m × n) | Precisa deslocar todas as linhas abaixo. |
| **Remoção de linha** | O(m × n) | Desloca todas as linhas abaixo para cima. |
| **Diagonal** | O(n) | Apenas n elementos na diagonal de matriz n×n. |
| **Rotação 90°** | O(n²) | Transpor (O(n²)) + inverter linhas (O(n²)) = O(n²). |

**Análise Detalhada - Multiplicação de Matrizes:**
```c
// C = A × B, onde A é m×n, B é n×p, C é m×p
void multiplicar(int A[][N], int B[][P], int C[][P], int m, int n, int p) {
    for (int i = 0; i < m; i++) {          // Loop m vezes
        for (int j = 0; j < p; j++) {      // Loop p vezes
            C[i][j] = 0;                    // 1 atribuição
            for (int k = 0; k < n; k++) {  // Loop n vezes
                C[i][j] += A[i][k] * B[k][j];  // 1 mult + 1 soma
            }
        }
    }
}

// Contagem de operações:
// - Número de elementos em C: m × p
// - Para cada elemento: n multiplicações + n somas
// - Total de multiplicações: m × n × p
// - Total de somas: m × n × p
// - Complexidade total: O(m × n × p)
//
// Exemplo: Multiplicar duas matrizes 1000×1000
// Operações: 1000 × 1000 × 1000 = 1.000.000.000 (1 bilhão!)
// A 1 GHz: aproximadamente 1 segundo
```

### Complexidade de Espaço

**Vetores:**
- Vetor estático de n elementos: **O(n)** bytes (n × sizeof(tipo))
- Vetor dinâmico: **O(n)** + overhead do malloc (alguns bytes extras)

**Matrizes:**
- Matriz m×n estática: **O(m × n)** bytes
- Matriz m×n dinâmica (ponteiros): **O(m × n) + O(m)** para array de ponteiros
- Matriz contígua: **O(m × n)** (mais eficiente)

**Exemplo:**
```c
int vetor[1000];              // 1000 × 4 = 4.000 bytes = 4 KB
int matriz[100][100];         // 10.000 × 4 = 40.000 bytes = 40 KB
int matriz_3d[50][50][50];    // 125.000 × 4 = 500.000 bytes = 500 KB
```

### Impacto da Complexidade no Mundo Real

**Exemplo 1: Busca Linear vs Busca Binária**
```
Vetor de 1 milhão de elementos:
- Busca linear: até 1.000.000 comparações (pior caso)
- Busca binária: até 20 comparações (log₂(1.000.000) ≈ 20)
- Diferença: 50.000 vezes mais rápido!
```

**Exemplo 2: Multiplicação de Matrizes**
```
Matrizes 1000×1000:
- Algoritmo ingênuo O(n³): 1.000.000.000 operações
- Algoritmo de Strassen O(n^2.8): ≈ 159.000.000 operações
- Diferença: 6,3 vezes mais rápido!

Matrizes 2000×2000:
- Algoritmo ingênuo: 8.000.000.000 operações (8× maior)
- Tempo: aproximadamente 8 segundos (a 1 GHz)
```

**Exemplo 3: Importância do Cache**
```c
// Método 1: Percorrer por linhas (cache-friendly)
for (int i = 0; i < 1000; i++)
    for (int j = 0; j < 1000; j++)
        soma += matriz[i][j];
// Tempo: ~1 ms

// Método 2: Percorrer por colunas (cache miss)
for (int j = 0; j < 1000; j++)
    for (int i = 0; i < 1000; i++)
        soma += matriz[i][j];
// Tempo: ~3-5 ms
// Mesma complexidade O(n²), mas 3-5× mais lento na prática!
```

### Dicas para Otimização

1. **Evite operações O(n) dentro de loops:**
   ```c
   // ❌ Ruim: O(n²)
   for (int i = 0; i < n; i++)
       for (int j = 0; j < strlen(str); j++)  // strlen é O(n)!
   
   // ✅ Bom: O(n)
   int len = strlen(str);  // Calcular uma vez
   for (int i = 0; i < n; i++)
       for (int j = 0; j < len; j++)
   ```

2. **Percorra matrizes por linhas, não por colunas**

3. **Use busca binária quando possível** (se o vetor está ordenado)

4. **Algoritmos O(n log n) são aceitáveis para n até 10⁶**

5. **Algoritmos O(n²) são aceitáveis para n até 10⁴**

6. **Algoritmos O(n³) são aceitáveis para n até 500**

---

## ⚡ Operações Comuns e Complexidade - Tabela Resumida

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