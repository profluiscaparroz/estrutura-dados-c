# Métodos de Ordenação em C

Este diretório contém implementações completas e detalhadas de algoritmos clássicos de ordenação em linguagem C, acompanhadas de análises teóricas profundas, exemplos práticos passo-a-passo e comparações rigorosas de desempenho.

## 📖 Introdução aos Algoritmos de Ordenação

### O que é Ordenação?

Ordenação é um processo fundamental em ciência da computação que consiste em **reorganizar uma sequência de elementos em uma ordem específica** (geralmente crescente ou decrescente). Este é um dos problemas mais estudados e aplicados na computação, sendo essencial para:

- **Otimização de Buscas**: Estruturas ordenadas permitem buscas eficientes (O(log n) vs O(n))
- **Análise de Dados**: Facilita identificação de medianas, quartis e outliers
- **Preparação para Algoritmos**: Muitos algoritmos requerem dados pré-ordenados
- **Interface com Usuários**: Apresentação organizada de informações
- **Otimização de I/O**: Acesso sequencial otimizado em sistemas de arquivos

### Conceitos Fundamentais

#### Estabilidade
Um algoritmo é **estável** quando mantém a ordem relativa de elementos com chaves iguais. Por exemplo, se temos dois registros com o mesmo valor de ordenação, um algoritmo estável garantirá que a ordem original entre eles seja preservada.

**Exemplo Prático**: Ordenando uma lista de alunos primeiro por nome e depois por nota. Um algoritmo estável mantém a ordem alfabética para alunos com a mesma nota.

#### In-Place
Um algoritmo é **in-place** quando requer apenas O(1) ou O(log n) de memória adicional, além do espaço ocupado pela entrada. Isso significa que a ordenação ocorre sobre o próprio array original, sem necessidade de copiar grandes volumes de dados.

#### Adaptatividade
Um algoritmo é **adaptativo** quando seu desempenho melhora significativamente para entradas já parcialmente ordenadas. Por exemplo, o Insertion Sort atinge O(n) para arrays quase ordenados.

### Por que estudar diferentes algoritmos?

Não existe um "melhor algoritmo universal" de ordenação. A escolha depende de:
- **Tamanho da entrada**: Algoritmos simples podem ser mais rápidos para pequenas entradas
- **Distribuição dos dados**: Arrays quase ordenados, completamente aleatórios, ou invertidos
- **Restrições de memória**: Alguns algoritmos requerem espaço adicional significativo
- **Necessidade de estabilidade**: Quando a ordem relativa deve ser preservada
- **Hardware disponível**: Cache, processadores paralelos, memória disponível

## 📁 Arquivos Disponíveis

### Algoritmos de Ordenação Implementados

| Arquivo | Algoritmo | Complexidade (Tempo) | Complexidade (Espaço) | Estável | In-Place |
|---------|-----------|---------------------|----------------------|---------|----------|
| `bubbleSort.c` | Bubble Sort | O(n²) | O(1) | ✅ Sim | ✅ Sim |
| `bubbleSortOptimized.c` | Bubble Sort Otimizado | O(n) a O(n²) | O(1) | ✅ Sim | ✅ Sim |
| `insertSort.c` | Insertion Sort | O(n²) | O(1) | ✅ Sim | ✅ Sim |
| `selectSort.c` | Selection Sort | O(n²) | O(1) | ❌ Não | ✅ Sim |
| `quickSort.c` | Quick Sort | O(n log n) avg, O(n²) worst | O(log n) | ❌ Não | ✅ Sim |
| `mergeSort.c` | Merge Sort | O(n log n) | O(n) | ✅ Sim | ❌ Não |
| `heapSort.c` | Heap Sort | O(n log n) | O(1) | ❌ Não | ✅ Sim |
| `shellSort.c` | Shell Sort | O(n^1.5) | O(1) | ❌ Não | ✅ Sim |

### Ferramentas e Exemplos

| Arquivo | Descrição |
|---------|-----------|
| `comparacao.c` | Benchmark de performance entre algoritmos |
| `ordenacao_busca.c` | Integração de ordenação com algoritmos de busca |
| `Makefile` | Sistema de compilação automatizado |
| `README.md` | Esta documentação |

## 🔍 Detalhes dos Algoritmos

### 1. Bubble Sort (`bubbleSort.c`)

#### Explicação Acadêmica

O **Bubble Sort** é um algoritmo de ordenação por comparação que recebe seu nome da forma como os elementos maiores "borbulham" para o topo (final) do array, assim como bolhas de ar sobem na água. É o algoritmo de ordenação mais simples de entender e implementar, sendo frequentemente usado como introdução ao estudo de algoritmos.

**Princípio de Funcionamento:**
O algoritmo realiza múltiplas passagens pelo array, comparando pares de elementos adjacentes e trocando-os se estiverem fora de ordem. A cada passagem completa, o maior elemento ainda não ordenado é movido para sua posição final.

**Análise Matemática da Complexidade:**
- **Número de comparações**: No pior caso, são necessárias n-1 comparações na primeira passagem, n-2 na segunda, até 1 na última. O total é: (n-1) + (n-2) + ... + 1 = n(n-1)/2 = O(n²)
- **Número de trocas**: No pior caso (array em ordem reversa), cada comparação resulta em uma troca, totalizando O(n²) trocas
- **Melhor caso**: Quando o array já está ordenado, são feitas n-1 comparações sem trocas, resultando em O(n) com a otimização de flag

**Invariante do Algoritmo:**
Após a i-ésima iteração do loop externo, os i maiores elementos estão em suas posições finais corretas no final do array.

**Como funciona:**
- Compara elementos adjacentes e os troca se estiverem fora de ordem
- Repete o processo até que nenhuma troca seja necessária
- O maior elemento "borbulha" para o final a cada passagem
- A cada iteração, o número de comparações necessárias diminui em 1

**Quando usar:**
- Listas muito pequenas (< 10 elementos) onde a simplicidade é mais importante
- Fins educacionais para ensinar conceitos de ordenação
- Quando simplicidade de implementação é crítica
- Arrays que já estão quase ordenados (com a versão otimizada)

**Exemplo de uso passo-a-passo:**
```c
int arr[] = {64, 34, 25, 12, 22, 11, 90};
int n = 7;

// Estado inicial: [64, 34, 25, 12, 22, 11, 90]

// Passagem 1:
// [34, 64, 25, 12, 22, 11, 90] (troca 64 e 34)
// [34, 25, 64, 12, 22, 11, 90] (troca 64 e 25)
// [34, 25, 12, 64, 22, 11, 90] (troca 64 e 12)
// [34, 25, 12, 22, 64, 11, 90] (troca 64 e 22)
// [34, 25, 12, 22, 11, 64, 90] (troca 64 e 11)
// [34, 25, 12, 22, 11, 64, 90] (64 < 90, sem troca)
// Resultado: 90 está na posição final

// Passagem 2:
// [25, 34, 12, 22, 11, 64, 90]
// [25, 12, 34, 22, 11, 64, 90]
// [25, 12, 22, 34, 11, 64, 90]
// [25, 12, 22, 11, 34, 64, 90]
// Resultado: 64 está na posição final

// ... continua até estar completamente ordenado
// Resultado final: [11, 12, 22, 25, 34, 64, 90]

bubbleSort(arr, n);
```

**Pseudocódigo Formal:**
```
BUBBLE-SORT(A, n)
1  for i ← 1 to n-1
2      for j ← 1 to n-i
3          if A[j] > A[j+1]
4              swap A[j] with A[j+1]
```

### 2. Insertion Sort (`insertSort.c`)

#### Explicação Acadêmica

O **Insertion Sort** é um algoritmo de ordenação intuitivo que simula a forma como naturalmente ordenamos cartas em nossas mãos. O algoritmo mantém uma sublista ordenada à esquerda e insere, um por vez, cada elemento restante na posição correta dentro dessa sublista ordenada.

**Princípio de Funcionamento:**
O algoritmo divide conceitualmente o array em duas partes: uma parte ordenada (inicialmente contendo apenas o primeiro elemento) e uma parte não ordenada (o restante). A cada iteração, o algoritmo pega o primeiro elemento da parte não ordenada e o insere na posição correta da parte ordenada.

**Análise Matemática da Complexidade:**
- **Melhor caso (O(n))**: Quando o array já está ordenado, cada elemento requer apenas uma comparação para confirmar que está na posição correta
- **Pior caso (O(n²))**: Quando o array está em ordem reversa, cada novo elemento deve ser comparado com todos os elementos já ordenados e movido para o início
- **Caso médio (O(n²))**: Em média, cada elemento precisa ser comparado com metade dos elementos já ordenados

**Características Especiais:**
- **Online**: Pode ordenar elementos conforme eles chegam (não precisa ter todos os dados de uma vez)
- **Adaptativo**: Desempenho melhora significativamente com dados parcialmente ordenados
- **Estável**: Mantém a ordem relativa de elementos iguais

**Como funciona:**
- Constrói a lista ordenada um elemento por vez, da esquerda para a direita
- Insere cada elemento na posição correta em relação aos já ordenados
- Similar a organizar cartas na mão: você pega uma carta e a insere no lugar certo
- Elementos maiores são "deslocados" para a direita para abrir espaço

**Quando usar:**
- Arrays pequenos ou quase ordenados (extremamente eficiente nestes casos)
- Como parte de algoritmos híbridos (ex: Timsort usa Insertion Sort para pequenos subarrays)
- Quando estabilidade é importante
- Ordenação online (dados chegando em tempo real)
- Quando a simplicidade de implementação é crítica

**Exemplo de uso detalhado:**
```c
int arr[] = {12, 11, 13, 5, 6};
int n = 5;

// Estado inicial: [12, 11, 13, 5, 6]
// Parte ordenada: [12] | Parte não ordenada: [11, 13, 5, 6]

// Iteração 1: Inserir 11
// Comparar 11 com 12: 11 < 12, então mover 12 para direita
// Inserir 11 na posição 0
// Resultado: [11, 12, 13, 5, 6]
// Parte ordenada: [11, 12] | Parte não ordenada: [13, 5, 6]

// Iteração 2: Inserir 13
// Comparar 13 com 12: 13 > 12, já está no lugar certo
// Resultado: [11, 12, 13, 5, 6]
// Parte ordenada: [11, 12, 13] | Parte não ordenada: [5, 6]

// Iteração 3: Inserir 5
// Comparar 5 com 13: 5 < 13, mover 13
// Comparar 5 com 12: 5 < 12, mover 12
// Comparar 5 com 11: 5 < 11, mover 11
// Inserir 5 na posição 0
// Resultado: [5, 11, 12, 13, 6]
// Parte ordenada: [5, 11, 12, 13] | Parte não ordenada: [6]

// Iteração 4: Inserir 6
// Comparar 6 com 13: 6 < 13, mover 13
// Comparar 6 com 12: 6 < 12, mover 12
// Comparar 6 com 11: 6 < 11, mover 11
// Comparar 6 com 5: 6 > 5, inserir após 5
// Resultado: [5, 6, 11, 12, 13]

insertionSort(arr, n);
// Resultado final: {5, 6, 11, 12, 13}
```

**Pseudocódigo Formal:**
```
INSERTION-SORT(A, n)
1  for i ← 2 to n
2      key ← A[i]
3      j ← i - 1
4      while j > 0 and A[j] > key
5          A[j+1] ← A[j]
6          j ← j - 1
7      A[j+1] ← key
```

**Otimizações Possíveis:**
- **Binary Insertion Sort**: Usar busca binária para encontrar a posição de inserção (reduz comparações mas não trocas)
- **Shell Sort**: Variação que compara elementos distantes primeiro

### 3. Selection Sort (`selectSort.c`)

#### Explicação Acadêmica

O **Selection Sort** é um algoritmo de ordenação por comparação que divide o array em duas partes: uma sublista ordenada e uma sublista não ordenada. A cada iteração, o algoritmo **seleciona** o menor (ou maior) elemento da parte não ordenada e o move para o final da parte ordenada.

**Princípio de Funcionamento:**
O algoritmo mantém um invariante: após i iterações, os i menores elementos estão em suas posições finais corretas. Para cada posição no array, o algoritmo procura o menor elemento na parte não ordenada e o coloca na posição atual.

**Análise Matemática da Complexidade:**
- **Todas as variações (melhor, médio e pior caso): O(n²)**
- **Comparações**: Sempre realiza exatamente (n-1) + (n-2) + ... + 1 = n(n-1)/2 comparações
- **Trocas**: Realiza no máximo n-1 trocas (uma por iteração)
- A complexidade é sempre O(n²), independente da configuração inicial dos dados

**Características Distintivas:**
- **Número mínimo de trocas**: Entre os algoritmos O(n²), realiza o menor número de operações de troca
- **Não adaptativo**: Não se beneficia de dados parcialmente ordenados
- **Não estável**: Pode alterar a ordem relativa de elementos iguais (mas pode ser tornado estável com modificações)

**Como funciona:**
- Encontra o menor elemento e o coloca na primeira posição
- Encontra o segundo menor e o coloca na segunda posição
- Repete até ordenar toda a lista
- Em cada iteração i, apenas a posição i é modificada (após encontrar o mínimo)

**Quando usar:**
- Quando o número de trocas deve ser minimizado (importante em sistemas onde escrever é custoso)
- Listas pequenas onde simplicidade é importante
- Quando a memória é extremamente limitada (O(1) adicional)
- Em sistemas embarcados onde operações de escrita são caras

**Exemplo de uso detalhado:**
```c
int arr[] = {64, 25, 12, 22, 11};
int n = 5;

// Estado inicial: [64, 25, 12, 22, 11]

// Iteração 1: Encontrar mínimo de posição 0 até 4
// Mínimo encontrado: 11 (posição 4)
// Trocar arr[0] com arr[4]
// Resultado: [11, 25, 12, 22, 64]
// Parte ordenada: [11] | Não ordenada: [25, 12, 22, 64]

// Iteração 2: Encontrar mínimo de posição 1 até 4
// Mínimo encontrado: 12 (posição 2)
// Trocar arr[1] com arr[2]
// Resultado: [11, 12, 25, 22, 64]
// Parte ordenada: [11, 12] | Não ordenada: [25, 22, 64]

// Iteração 3: Encontrar mínimo de posição 2 até 4
// Mínimo encontrado: 22 (posição 3)
// Trocar arr[2] com arr[3]
// Resultado: [11, 12, 22, 25, 64]
// Parte ordenada: [11, 12, 22] | Não ordenada: [25, 64]

// Iteração 4: Encontrar mínimo de posição 3 até 4
// Mínimo encontrado: 25 (posição 3)
// Sem troca necessária (já está no lugar)
// Resultado: [11, 12, 22, 25, 64]
// Parte ordenada: [11, 12, 22, 25] | Não ordenada: [64]

// Último elemento já está ordenado
// Resultado final: [11, 12, 22, 25, 64]

selectionSort(arr, n);
// Total de trocas: 3 (muito menos que Bubble Sort)
```

**Pseudocódigo Formal:**
```
SELECTION-SORT(A, n)
1  for i ← 1 to n-1
2      min ← i
3      for j ← i+1 to n
4          if A[j] < A[min]
5              min ← j
6      if min ≠ i
7          swap A[i] with A[min]
```

**Comparação com outros algoritmos O(n²):**
- **vs Bubble Sort**: Menos trocas, mas sempre O(n²)
- **vs Insertion Sort**: Não se adapta a dados parcialmente ordenados
- **Vantagem única**: Mínimo número de escritas na memória

### 4. Quick Sort (`quickSort.c`)

#### Explicação Acadêmica

O **Quick Sort** é um dos algoritmos de ordenação mais eficientes e amplamente utilizados na prática. Desenvolvido por Tony Hoare em 1959, ele utiliza a estratégia de **divisão e conquista** (divide-and-conquer) para alcançar um desempenho médio de O(n log n).

**Princípio de Funcionamento:**
O algoritmo seleciona um elemento como **pivô** e particiona o array de forma que:
1. Todos os elementos menores que o pivô ficam à sua esquerda
2. Todos os elementos maiores que o pivô ficam à sua direita
3. O pivô está em sua posição final correta
4. O processo é aplicado recursivamente às sublistas esquerda e direita

**Análise Matemática da Complexidade:**

**Melhor e Caso Médio: O(n log n)**
- Ocorre quando o pivô divide o array aproximadamente ao meio a cada nível
- Profundidade da árvore de recursão: log₂(n)
- Trabalho em cada nível: O(n) para particionar
- Total: O(n) × log(n) = O(n log n)

**Pior Caso: O(n²)**
- Ocorre quando o pivô é sempre o menor ou maior elemento
- Array já ordenado ou em ordem reversa (com pivô simples)
- Profundidade da recursão: n
- Total: n + (n-1) + (n-2) + ... + 1 = O(n²)

**Análise de Recorrência:**
- Melhor caso: T(n) = 2T(n/2) + O(n) = O(n log n) (Teorema Mestre)
- Pior caso: T(n) = T(n-1) + O(n) = O(n²)

**Por que é rápido na prática?**
1. **Constantes pequenas**: O fator constante no O(n log n) é pequeno
2. **Cache-friendly**: Boa localidade de referência
3. **In-place**: Não requer memória adicional significativa
4. **Pivô aleatório**: Com pivô aleatório, o pior caso é muito raro

**Como funciona:**
- Escolhe um pivô e particiona o array
- Elementos menores ficam à esquerda, maiores à direita
- Aplica recursivamente o processo nas partições
- Pivô fica em sua posição final a cada partição

**Quando usar:**
- Listas grandes (a escolha padrão para ordenação de uso geral)
- Quando velocidade média é importante
- Implementação padrão em muitas bibliotecas (qsort em C)
- Quando memória extra é limitada

**Exemplo de uso detalhado:**
```c
int arr[] = {10, 7, 8, 9, 1, 5};
int n = 6;

// Estado inicial: [10, 7, 8, 9, 1, 5]
// Escolher pivô: 5 (último elemento)

// Partição 1:
// i = -1
// j=0: arr[0]=10 > 5, não faz nada
// j=1: arr[1]=7 > 5, não faz nada  
// j=2: arr[2]=8 > 5, não faz nada
// j=3: arr[3]=9 > 5, não faz nada
// j=4: arr[4]=1 < 5, i++, trocar arr[0] e arr[4]
// Array: [1, 7, 8, 9, 10, 5]
// Colocar pivô na posição correta: trocar arr[1] e arr[5]
// Array: [1, 5, 8, 9, 10, 7]
// Pivô 5 está na posição 1 (posição final)

// Recursão esquerda: [1] (já ordenado)
// Recursão direita: [8, 9, 10, 7]

// Partição da direita (escolher 7 como pivô):
// Array: [1, 5, 7, 9, 10, 8]
// Pivô 7 na posição 2

// Recursão: [8, 9, 10]
// Array: [1, 5, 7, 8, 9, 10]

quickSort(arr, 0, n - 1);
// Resultado final: {1, 5, 7, 8, 9, 10}
```

**Pseudocódigo Formal:**
```
QUICKSORT(A, p, r)
1  if p < r
2      q ← PARTITION(A, p, r)
3      QUICKSORT(A, p, q-1)
4      QUICKSORT(A, q+1, r)

PARTITION(A, p, r)
1  pivot ← A[r]
2  i ← p - 1
3  for j ← p to r-1
4      if A[j] ≤ pivot
5          i ← i + 1
6          swap A[i] with A[j]
7  swap A[i+1] with A[r]
8  return i + 1
```

**Estratégias de Escolha de Pivô:**
1. **Último elemento**: Simples, mas pior caso para arrays ordenados
2. **Primeiro elemento**: Similar ao último
3. **Elemento aleatório**: Evita pior caso com alta probabilidade
4. **Mediana de três**: Escolhe a mediana entre primeiro, meio e último (boa na prática)
5. **Mediana das medianas**: Garante O(n log n) mas com overhead

**Otimizações Avançadas:**
- **Cutoff para Insertion Sort**: Usar Insertion Sort para subarrays pequenos (< 10 elementos)
- **Tail recursion**: Eliminar uma chamada recursiva
- **3-way partitioning**: Lidar eficientemente com elementos duplicados

### 5. Merge Sort (`mergeSort.c`)

#### Explicação Acadêmica

O **Merge Sort** é um algoritmo de ordenação baseado no paradigma de **divisão e conquista**, desenvolvido por John von Neumann em 1945. É notável por sua **garantia de complexidade O(n log n)** em todos os casos e por ser um algoritmo **estável**.

**Princípio de Funcionamento:**
O algoritmo divide recursivamente o array em duas metades até que cada subarray contenha apenas um elemento (que está trivialmente ordenado). Em seguida, combina (merge) esses subarrays de forma ordenada, construindo progressivamente arrays maiores ordenados até reconstruir o array completo.

**Análise Matemática da Complexidade:**

A relação de recorrência do Merge Sort é:
```
T(n) = 2T(n/2) + O(n)
```
Onde:
- `2T(n/2)`: Ordenar duas metades do array
- `O(n)`: Tempo para combinar (merge) as duas metades ordenadas

**Aplicando o Teorema Mestre:**
- a = 2 (número de subproblemas)
- b = 2 (tamanho de cada subproblema)
- f(n) = O(n) (trabalho para combinar)
- log_b(a) = log_2(2) = 1

Como f(n) = Θ(n^log_b(a)), aplicamos o caso 2 do Teorema Mestre:
**T(n) = Θ(n log n)**

**Profundidade da Recursão**: log₂(n) níveis
**Trabalho por nível**: O(n) comparações e cópias
**Total**: O(n) × log(n) = **O(n log n)** em todos os casos

**Características Únicas:**
- **Garantia de performance**: Sempre O(n log n), mesmo no pior caso
- **Estável**: Mantém ordem relativa de elementos iguais
- **Não in-place**: Requer O(n) memória adicional
- **Paralelizável**: As duas metades podem ser ordenadas em paralelo

**Como funciona:**
- Divide o array recursivamente ao meio até ter subarrays de tamanho 1
- Combina (merge) pares de subarrays ordenados em arrays maiores ordenados
- Repete o processo até reconstruir o array completo ordenado
- A operação de merge é fundamental: combina dois arrays ordenados em um

**Quando usar:**
- Quando garantia de O(n log n) é essencial (sistemas críticos)
- Quando estabilidade é requerida
- Quando memória extra está disponível
- Ordenação externa (arquivos muito grandes)
- Dados em listas encadeadas (não requer acesso aleatório)

**Exemplo de uso detalhado:**
```c
int arr[] = {38, 27, 43, 3, 9, 82, 10};
int n = 7;

// Divisão (fase top-down):
//          [38, 27, 43, 3, 9, 82, 10]
//         /                           \
//    [38, 27, 43, 3]              [9, 82, 10]
//    /            \                /         \
// [38, 27]      [43, 3]        [9, 82]      [10]
//  /    \        /   \          /   \
// [38] [27]    [43] [3]       [9] [82]

// Conquista (fase bottom-up - merge):

// Nível 1: Merge de pares individuais
// [38] + [27] → [27, 38]
// [43] + [3]  → [3, 43]
// [9] + [82]  → [9, 82]
// [10] permanece

// Nível 2: Merge de pares ordenados
// [27, 38] + [3, 43]  → [3, 27, 38, 43]
//   Passo a passo:
//   Compare 27 e 3:  3 < 27  → [3]
//   Compare 27 e 43: 27 < 43 → [3, 27]
//   Compare 38 e 43: 38 < 43 → [3, 27, 38]
//   Restou 43              → [3, 27, 38, 43]

// [9, 82] + [10] → [9, 10, 82]
//   Compare 9 e 10:  9 < 10  → [9]
//   Compare 82 e 10: 10 < 82 → [9, 10]
//   Restou 82              → [9, 10, 82]

// Nível 3: Merge final
// [3, 27, 38, 43] + [9, 10, 82] → [3, 9, 10, 27, 38, 43, 82]
//   Compare 3 e 9:   3 < 9   → [3]
//   Compare 27 e 9:  9 < 27  → [3, 9]
//   Compare 27 e 10: 10 < 27 → [3, 9, 10]
//   Compare 27 e 82: 27 < 82 → [3, 9, 10, 27]
//   Compare 38 e 82: 38 < 82 → [3, 9, 10, 27, 38]
//   Compare 43 e 82: 43 < 82 → [3, 9, 10, 27, 38, 43]
//   Restou 82              → [3, 9, 10, 27, 38, 43, 82]

mergeSort(arr, 0, n - 1);
// Resultado final: {3, 9, 10, 27, 38, 43, 82}
```

**Pseudocódigo Formal:**
```
MERGE-SORT(A, p, r)
1  if p < r
2      q ← ⌊(p + r) / 2⌋
3      MERGE-SORT(A, p, q)
4      MERGE-SORT(A, q+1, r)
5      MERGE(A, p, q, r)

MERGE(A, p, q, r)
1  n1 ← q - p + 1
2  n2 ← r - q
3  create arrays L[1..n1] and R[1..n2]
4  for i ← 1 to n1
5      L[i] ← A[p + i - 1]
6  for j ← 1 to n2
7      R[j] ← A[q + j]
8  i ← 1, j ← 1, k ← p
9  while i ≤ n1 and j ≤ n2
10     if L[i] ≤ R[j]
11         A[k] ← L[i]
12         i ← i + 1
13     else
14         A[k] ← R[j]
15         j ← j + 1
16     k ← k + 1
17 while i ≤ n1
18     A[k] ← L[i]
19     i ← i + 1, k ← k + 1
20 while j ≤ n2
21     A[k] ← R[j]
22     j ← j + 1, k ← k + 1
```

**Variações e Otimizações:**

1. **Bottom-Up Merge Sort (iterativo)**:
```c
// Evita recursão, útil em sistemas com stack limitado
void mergeSortBottomUp(int arr[], int n) {
    for (int size = 1; size < n; size *= 2) {
        for (int start = 0; start < n - size; start += 2 * size) {
            int mid = start + size - 1;
            int end = min(start + 2 * size - 1, n - 1);
            merge(arr, start, mid, end);
        }
    }
}
```

2. **Natural Merge Sort**:
   - Detecta runs (sequências já ordenadas) naturalmente presentes nos dados
   - Base do Tim Sort usado no Python

3. **In-Place Merge Sort**:
   - Reduz uso de memória para O(1), mas com complexidade maior
   - Mais complexo de implementar

**Aplicações Especiais:**

- **Ordenação Externa**: Para arquivos maiores que a RAM
  ```
  Exemplo: Ordenar arquivo de 100GB com 8GB RAM
  1. Divide arquivo em chunks de 8GB
  2. Ordena cada chunk com Quick Sort
  3. Faz merge externo dos chunks ordenados
  ```

- **Listas Encadeadas**: Merge Sort é ideal (O(1) extra)
  ```c
  // Não precisa de array auxiliar!
  Node* mergeSortList(Node* head) {
      if (!head || !head->next) return head;
      Node* mid = getMiddle(head);
      Node* left = head;
      Node* right = mid->next;
      mid->next = NULL;
      return merge(mergeSortList(left), mergeSortList(right));
  }
  ```

**Comparação: Merge Sort vs Quick Sort**

| Aspecto | Merge Sort | Quick Sort |
|---------|-----------|------------|
| Pior caso | O(n log n) ✅ | O(n²) ❌ |
| Médio caso | O(n log n) | O(n log n) |
| Memória | O(n) ❌ | O(log n) ✅ |
| Estável | Sim ✅ | Não ❌ |
| Cache | Menos eficiente | Mais eficiente ✅ |
| Paralelização | Fácil ✅ | Mais difícil |

### 6. Heap Sort (`heapSort.c`)

#### Explicação Acadêmica

O **Heap Sort** é um algoritmo de ordenação baseado na estrutura de dados **heap binário**. Desenvolvido por J. W. J. Williams em 1964, combina as melhores características de Merge Sort (garantia O(n log n)) e Insertion Sort (in-place, O(1) extra).

**Estrutura de Dados: Heap Binário**

Um **max-heap** é uma árvore binária completa onde cada nó é maior ou igual a seus filhos:
```
        90
       /  \
     85    30
    /  \   /
   70  10 15

Propriedade: arr[i] ≥ arr[2i+1] e arr[i] ≥ arr[2i+2]
```

**Representação em Array:**
```c
arr[] = [90, 85, 30, 70, 10, 15]
Índices dos filhos de arr[i]:
- Filho esquerdo: 2*i + 1
- Filho direito:  2*i + 2
- Pai de arr[i]: (i-1)/2
```

**Princípio de Funcionamento:**

1. **Construir heap**: Transforma o array em um max-heap (O(n))
2. **Extração iterativa**: Remove o máximo (raiz) e reconstrói heap (n × O(log n))

**Análise Matemática:**

**Fase 1 - Build Heap: O(n)**
```
Surpreendentemente, construir heap é O(n), não O(n log n)!

Análise:
- Altura h = log n
- Nós na altura h: n/2^(h+1)
- Custo de heapify na altura h: O(h)
- Total: Σ(h=0 to log n) [n/2^(h+1) × h] = O(n)
```

**Fase 2 - Ordenação: O(n log n)**
```
- n iterações (uma por elemento)
- Cada iteração: heapify O(log n)
- Total: n × log n = O(n log n)
```

**Como funciona:**
- Constrói um max-heap a partir do array
- Troca o maior elemento (raiz) com o último
- Reduz o tamanho do heap e reconstrói (heapify)
- Repete até ordenar todo o array
- Elementos vão sendo colocados em ordem no final do array

**Quando usar:**
- Quando garantia de O(n log n) é necessária **e** memória é limitada
- Sistemas em tempo real com requisitos previsíveis
- Quando estabilidade não é importante
- Implementação de fila de prioridade com ordenação

**Exemplo de uso detalhado:**
```c
int arr[] = {12, 11, 13, 5, 6, 7};
int n = 6;

// Fase 1: Construir Max-Heap
// Array original: [12, 11, 13, 5, 6, 7]

// Começar do último nó não-folha: i = n/2 - 1 = 2
// Índice 2 (valor 13): já satisfaz propriedade heap
//       12
//      /  \
//    11    13
//   /  \   /
//  5   6  7

// Índice 1 (valor 11): comparar com filhos (5, 6)
// 11 > 6, ok
//       12
//      /  \
//    11    13
//   /  \   /
//  5   6  7

// Índice 0 (valor 12): comparar com filhos (11, 13)
// 12 < 13, trocar!
//       13
//      /  \
//    11    12
//   /  \   /
//  5   6  7

// Array após build-heap: [13, 11, 12, 5, 6, 7]

// Fase 2: Ordenação (extrair máximo repetidamente)

// Iteração 1:
// Trocar raiz (13) com último elemento (7)
// [7, 11, 12, 5, 6, | 13]
// Heapify na raiz:
//       12
//      /  \
//    11    7
//   /  \
//  5   6
// Array: [12, 11, 7, 5, 6, | 13]

// Iteração 2:
// Trocar raiz (12) com último não-ordenado (6)
// [6, 11, 7, 5, | 12, 13]
// Heapify:
//       11
//      /  \
//    6     7
//   /
//  5
// Array: [11, 6, 7, 5, | 12, 13]

// Iteração 3:
// [5, 6, 7, | 11, 12, 13]
// Heapify:
//       7
//      /  \
//    6     5
// Array: [7, 6, 5, | 11, 12, 13]

// Iteração 4:
// [5, 6, | 7, 11, 12, 13]
// Heapify:
//       6
//      /
//    5
// Array: [6, 5, | 7, 11, 12, 13]

// Iteração 5:
// [5, | 6, 7, 11, 12, 13]

// Resultado final: [5, 6, 7, 11, 12, 13]

heapSort(arr, n);
```

**Pseudocódigo Formal:**
```
HEAP-SORT(A, n)
1  BUILD-MAX-HEAP(A, n)
2  for i ← n downto 2
3      swap A[1] with A[i]
4      heap-size ← heap-size - 1
5      MAX-HEAPIFY(A, 1)

BUILD-MAX-HEAP(A, n)
1  heap-size ← n
2  for i ← ⌊n/2⌋ downto 1
3      MAX-HEAPIFY(A, i)

MAX-HEAPIFY(A, i)
1  l ← LEFT(i)
2  r ← RIGHT(i)
3  if l ≤ heap-size and A[l] > A[i]
4      largest ← l
5  else largest ← i
6  if r ≤ heap-size and A[r] > A[largest]
7      largest ← r
8  if largest ≠ i
9      swap A[i] with A[largest]
10     MAX-HEAPIFY(A, largest)
```

**Aplicações do Heap:**
- **Ordenação**: Heap Sort
- **Fila de prioridade**: Hospitais (triagem), SO (escalonamento)
- **Algoritmo de Dijkstra**: Caminho mais curto
- **Huffman coding**: Compressão de dados
- **K maiores elementos**: Heap de tamanho k

### 7. Shell Sort (`shellSort.c`)

#### Explicação Acadêmica

O **Shell Sort**, desenvolvido por Donald Shell em 1959, é uma **generalização sofisticada do Insertion Sort**. Ele supera a limitação do Insertion Sort de comparar apenas elementos adjacentes, usando uma sequência de "gaps" (intervalos) decrescentes.

**Princípio de Funcionamento:**

Em vez de comparar elementos adjacentes (gap = 1), o Shell Sort começa comparando elementos distantes e gradualmente reduz o gap até chegar a 1 (Insertion Sort normal). Esta estratégia move elementos para perto de suas posições finais mais rapidamente.

**Como funciona:**
- Generalização do Insertion Sort com gaps decrescentes
- Começa comparando elementos distantes (gap grande)
- Reduz o gap progressivamente
- Termina com gap = 1 (Insertion Sort clássico)
- Array fica "quase ordenado" antes do passo final

**Análise de Complexidade:**

A complexidade depende **crucialmente da sequência de gaps escolhida**:

| Sequência de Gap | Complexidade | Autor |
|------------------|--------------|-------|
| n/2, n/4, ..., 1 | O(n²) | Shell (original) |
| 2^k - 1 | O(n^1.5) | Hibbard |
| 2^i × 3^j | O(n log² n) | Pratt |
| (9×4^i - 9×2^i + 1)/5 | O(n^1.3) | Sedgewick |
| Desconhecido | ? | Ciura (melhor na prática) |

**Sequências de Gap Comuns:**

1. **Shell Original**: n/2, n/4, n/8, ..., 1
   ```c
   for (gap = n/2; gap > 0; gap /= 2)
   ```
   - Simples mas pior caso O(n²)

2. **Knuth**: (3^k - 1)/2 = 1, 4, 13, 40, 121, ...
   ```c
   gap = 1;
   while (gap < n/3) gap = 3*gap + 1;
   for (; gap > 0; gap /= 3)
   ```
   - Complexidade O(n^1.5)
   - Popular e eficiente

3. **Ciura**: 1, 4, 10, 23, 57, 132, 301, 701, 1750, ...
   ```c
   int gaps[] = {701, 301, 132, 57, 23, 10, 4, 1};
   ```
   - Melhor desempenho prático
   - Empiricamente determinado

**Quando usar:**
- Arrays de tamanho médio (1000-5000 elementos)
- Quando simplicidade de implementação é importante
- Como alternativa ao Insertion Sort para arrays maiores
- Quando não pode usar recursão (sistemas embarcados)
- Código legado que precisa ser simples e eficiente

**Exemplo de uso detalhado:**
```c
int arr[] = {23, 29, 15, 19, 31, 7, 9, 5, 2};
int n = 9;

// Usando sequência de Knuth: gaps = [4, 1]

// Gap = 4:
// Comparar elementos a distância 4
// Sublistas: 
//   [23, 31, 2] (índices 0, 4, 8)
//   [29, 7]     (índices 1, 5)
//   [15, 9]     (índices 2, 6)
//   [19, 5]     (índices 3, 7)

// Ordenar cada sublista com Insertion Sort:
// [23, 31, 2] → [2, 23, 31]  arr: [2, 29, 15, 19, 31, 7, 9, 5, 23]
// [29, 7]     → [7, 29]       arr: [2, 7, 15, 19, 31, 29, 9, 5, 23]
// [15, 9]     → [9, 15]       arr: [2, 7, 9, 19, 31, 29, 15, 5, 23]
// [19, 5]     → [5, 19]       arr: [2, 7, 9, 5, 31, 29, 15, 19, 23]

// Array após gap=4: [2, 7, 9, 5, 31, 29, 15, 19, 23]
// Observe: não está ordenado, mas elementos grandes moveram para direita

// Gap = 1 (Insertion Sort normal):
// [2, 7, 9, 5, 31, 29, 15, 19, 23]
// Inserir 5: [2, 5, 7, 9, 31, 29, 15, 19, 23]
// Inserir 31: já no lugar
// Inserir 29: [2, 5, 7, 9, 29, 31, 15, 19, 23]
// Inserir 15: [2, 5, 7, 9, 15, 29, 31, 19, 23]
// Inserir 19: [2, 5, 7, 9, 15, 19, 29, 31, 23]
// Inserir 23: [2, 5, 7, 9, 15, 19, 23, 29, 31]

shellSort(arr, n);
// Resultado final: {2, 5, 7, 9, 15, 19, 23, 29, 31}

// Vantagem: O passo final (gap=1) é muito mais rápido porque
// o array já está "quase ordenado" pelos passos anteriores
```

**Pseudocódigo Formal (Knuth):**
```
SHELL-SORT(A, n)
1  gap ← 1
2  while gap < n/3
3      gap ← 3 × gap + 1
4  while gap > 0
5      for i ← gap to n
6          temp ← A[i]
7          j ← i
8          while j ≥ gap and A[j-gap] > temp
9              A[j] ← A[j-gap]
10             j ← j - gap
11         A[j] ← temp
12     gap ← gap / 3
```

**Por que Shell Sort funciona?**

**Intuição**: Mover elementos para perto de suas posições finais rapidamente
```
Array inicial: [100, 90, 80, 70, ..., 3, 2, 1]

Insertion Sort normal (gap=1):
- 100 precisa mover 99 posições → 99 trocas
- Total: O(n²) movimentações

Shell Sort com gaps grandes:
- Gap=33: 100 move 3 posições → 3 trocas
- Gap=11: Ajustes finos
- Gap=1:  Array já quase ordenado → O(n)
```

**Análise Visual:**

```
Gap grande (h): "desentupir" inversões distantes
          ╭─────────h─────────╮
[9, 2, 8, 3, 7, 4, 6, 5, 1]
 ↓              ↓          ↓
Compara elementos distantes

Gap pequeno: ajustes finos locais
    ╭─h─╮
[1, 3, 2, 5, 4, 7, 6, 9, 8]
```

**Comparação com outros algoritmos:**

| Aspecto | Shell Sort | Insertion Sort | Quick Sort |
|---------|-----------|----------------|------------|
| Complexidade | O(n^1.3) * | O(n²) | O(n log n) |
| Memória | O(1) ✅ | O(1) ✅ | O(log n) |
| Estável | Não ❌ | Sim ✅ | Não ❌ |
| Adaptativo | Sim ✅ | Sim ✅ | Não ❌ |
| Recursão | Não ✅ | Não ✅ | Sim ❌ |
| Implementação | Simples ✅ | Muito simples | Média |

*Depende da sequência de gaps

**Quando NÃO usar Shell Sort:**
- Arrays muito grandes (> 100k): Quick/Merge Sort são melhores
- Necessidade de estabilidade: Use Merge Sort
- Performance crítica: Quick Sort é mais rápido
- Necessita garantia O(n log n): Merge/Heap Sort

**Exemplo de uso:**
```c
int arr[] = {23, 29, 15, 19, 31, 7, 9, 5, 2};
int n = 9;
shellSort(arr, n);
// Resultado: {2, 5, 7, 9, 15, 19, 23, 29, 31}
```

### 8. Bubble Sort Otimizado (`bubbleSortOptimized.c`)

**Como funciona:**
- Versão melhorada do Bubble Sort
- Para quando nenhuma troca é feita (array já ordenado)
- Reduz o melhor caso de O(n²) para O(n)

**Quando usar:**
- Fins educacionais para mostrar otimizações
- Arrays pequenos que podem estar parcialmente ordenados

## 🛠️ Ferramentas Disponíveis

### Comparação de Performance (`comparacao.c`)

Ferramenta completa para benchmark dos algoritmos:
- Testa diferentes tipos de arrays (aleatório, ordenado, reverso)
- Mede tempo de execução
- Verifica corretude dos resultados
- Gera relatório comparativo

### Integração com Busca (`ordenacao_busca.c`)

Demonstra a relação entre ordenação e algoritmos de busca:
- Compara busca linear vs. binária
- Mostra quando vale a pena ordenar antes de buscar
- Inclui busca interpolada
- Análise de trade-offs

## 🚀 Como Compilar e Executar

### Uso do Makefile (Recomendado)

Este diretório inclui um Makefile completo para facilitar a compilação e teste:

```bash
# Compilar todos os algoritmos
make all

# Executar algoritmos básicos
make run-all

# Executar algoritmos avançados  
make run-advanced

# Executar benchmark de performance
make benchmark

# Testar se todos compilam
make test

# Ver ajuda completa
make help
```

### Compilação Individual
```bash
gcc -Wall -Wextra -std=c99 -o bubbleSort bubbleSort.c
./bubbleSort
```

### Compilação com Otimização
```bash
# Debug
make debug

# Release (máxima otimização)
make release
```

## 📊 Comparação de Desempenho

### Para Arrays Pequenos (n < 50)
1. **Insertion Sort** - Melhor para arrays quase ordenados
2. **Selection Sort** - Menor número de trocas
3. **Bubble Sort** - Apenas para fins educacionais

### Para Arrays Médios (50 < n < 1000)
1. **Quick Sort** - Geralmente o mais rápido
2. **Merge Sort** - Consistente, estável
3. **Insertion Sort** - Para arrays quase ordenados

### Para Arrays Grandes (n > 1000)
1. **Merge Sort** - Consistente O(n log n)
2. **Quick Sort** - Rápido em média, mas O(n²) no pior caso
3. **Evitar** algoritmos O(n²)

## 🛠️ Otimizações Possíveis

### Bubble Sort Otimizado
- Parar quando nenhuma troca for feita
- Reduzir o alcance a cada passagem

### Quick Sort Otimizado
- Escolha inteligente do pivô (mediana de três)
- Alternar para Insertion Sort em arrays pequenos
- Implementação iterativa para evitar stack overflow

### Merge Sort Otimizado
- Usar arrays pré-alocados para merge
- Alternar para Insertion Sort em subarrays pequenos

## 🧪 Casos de Teste Recomendados

### Casos Básicos
```c
// Array vazio
int arr[] = {};
int n = 0;

// Array com um elemento
int arr[] = {42};
int n = 1;

// Array já ordenado
int arr[] = {1, 2, 3, 4, 5};
int n = 5;

// Array em ordem inversa
int arr[] = {5, 4, 3, 2, 1};
int n = 5;

// Array com elementos duplicados
int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5};
int n = 9;
```

## 📚 Referências

- Donald E. Knuth. *The Art of Computer Programming, Volume 3: Sorting and Searching*
- Robert Sedgewick. *Algorithms in C*
- Thomas H. Cormen et al. *Introduction to Algorithms* (CLRS)

## 🤔 Questões para Reflexão (com Respostas Detalhadas)

### Questão 1: Estabilidade em Algoritmos de Ordenação

**Pergunta**: Por que a estabilidade é importante em algoritmos de ordenação? Dê um exemplo prático onde isso seria relevante.

**Resposta Detalhada**:

A **estabilidade** é a propriedade de um algoritmo de ordenação que garante que elementos com chaves iguais mantenham sua ordem relativa original após a ordenação. 

**Por que é importante?**

1. **Ordenação em múltiplas etapas**: Quando queremos ordenar por múltiplos critérios sequencialmente
2. **Preservação de ordem anterior**: Quando dados já possuem alguma ordenação significativa
3. **Consistência de resultados**: Garante comportamento previsível e reproduzível

**Exemplo Prático Detalhado**:

Imagine uma tabela de alunos com nome e nota:
```
Original:
[("Maria", 85), ("João", 90), ("Ana", 85), ("Pedro", 90)]
```

Se ordenarmos primeiro por nome (alfabeticamente):
```
[("Ana", 85), ("João", 90), ("Maria", 85), ("Pedro", 90)]
```

Agora, ordenando por nota de forma **estável**:
```
[("Ana", 85), ("Maria", 85), ("João", 90), ("Pedro", 90)]
```
Note que Ana continua antes de Maria (ambas com 85) e João antes de Pedro (ambos com 90), mantendo a ordem alfabética.

Se usássemos um algoritmo **instável** (como Quick Sort padrão):
```
[("Maria", 85), ("Ana", 85), ("Pedro", 90), ("João", 90)]
```
A ordem alfabética foi perdida para alunos com a mesma nota.

**Aplicações Reais**:
- **Banco de dados**: Consultas com ORDER BY múltiplo (ORDER BY departamento, nome)
- **Sistemas de arquivos**: Ordenação por tipo e depois por data
- **E-commerce**: Ordenar produtos por categoria, depois por preço
- **Processamento de logs**: Ordenar por timestamp mantendo ordem de eventos simultâneos

**Algoritmos Estáveis vs Instáveis**:
- ✅ **Estáveis**: Merge Sort, Insertion Sort, Bubble Sort, Counting Sort
- ❌ **Instáveis**: Quick Sort, Heap Sort, Selection Sort, Shell Sort

### Questão 2: Quick Sort - Paradoxo da Complexidade

**Pergunta**: Explique por que Quick Sort tem complexidade O(n²) no pior caso, mas ainda é considerado um dos melhores algoritmos na prática.

**Resposta Detalhada**:

**Por que O(n²) no pior caso?**

O pior caso ocorre quando o pivô escolhido é sempre o menor ou maior elemento, criando partições extremamente desbalanceadas:

```
Array: [1, 2, 3, 4, 5]
Escolhendo último elemento como pivô:

Nível 1: pivô=5, particiona em [1,2,3,4] e []  - n comparações
Nível 2: pivô=4, particiona em [1,2,3] e []    - (n-1) comparações  
Nível 3: pivô=3, particiona em [1,2] e []      - (n-2) comparações
...
Total: n + (n-1) + (n-2) + ... + 1 = n(n+1)/2 = O(n²)
```

**Por que ainda é o melhor na prática?**

1. **Caso Médio Dominante**: 
   - O(n log n) ocorre em ~99.99% dos casos com dados reais
   - Pior caso O(n²) é extremamente raro com pivô aleatório
   - Probabilidade de pior caso com pivô aleatório: < 1/(n!)

2. **Constantes Pequenas**:
   ```
   Quick Sort: ~1.4 × n log n comparações (média)
   Merge Sort: ~1.0 × n log n comparações, mas mais movimentações
   Heap Sort: ~2.0 × n log n comparações
   ```

3. **Cache Efficiency**:
   - Quick Sort trabalha in-place com boa localidade de referência
   - Acessa dados sequencialmente (friendly para cache L1/L2)
   - Merge Sort requer memória adicional e mais cache misses

4. **Otimizações Práticas**:
   - **Mediana de três**: Escolhe pivô melhor que primeiro/último
   - **Introsort**: Detecta recursão profunda e muda para Heap Sort
   - **Cutoff**: Usa Insertion Sort para subarrays pequenos (< 10)

5. **Comparação Real-World** (array de 1 milhão de elementos):
   ```
   Quick Sort (otimizado):  ~50ms
   Merge Sort:              ~80ms  (estável, mas mais lento)
   Heap Sort:               ~120ms (garantia O(n log n), mas lento)
   ```

**Conclusão**: Na prática, Quick Sort combina velocidade média excepcional com baixo uso de memória, superando as garantias teóricas de pior caso através de otimizações inteligentes.

### Questão 3: Escolha de Algoritmo para Dados Parcialmente Ordenados

**Pergunta**: Para um array de 1 milhão de elementos já parcialmente ordenado, qual algoritmo você escolheria e por quê?

**Resposta Detalhada**:

**Resposta curta**: **Insertion Sort** ou **Tim Sort** (híbrido).

**Análise Completa**:

**Insertion Sort** seria surpreendentemente a melhor escolha! Aqui está o porquê:

1. **Adaptatividade**:
   - Em arrays parcialmente ordenados, muitos elementos já estão próximos de suas posições finais
   - Insertion Sort requer apenas O(1) comparação por elemento já posicionado
   - Complexidade: O(n + d) onde d = número de inversões

2. **Análise Quantitativa**:
   ```
   Array 90% ordenado (1M elementos):
   - Insertion Sort: ~0.1n comparações = 100k comparações
   - Quick Sort: ~1.4n log n = 28M comparações
   - Merge Sort: ~1.0n log n = 20M comparações
   ```

3. **Exemplo Numérico**:
   ```
   Array: [1,2,3,4,5,100,7,8,9,10]
   
   Insertion Sort:
   - Elementos 1-5: Já ordenados, 1 comparação cada
   - Elemento 100: 1 comparação (100 > 5)
   - Elemento 7: 2 comparações (move 100)
   - Elementos 8-10: 1 comparação cada
   Total: ~12 comparações
   
   Quick Sort:
   - Deve processar todo array recursivamente
   - Não se beneficia da ordem parcial
   Total: ~30+ comparações
   ```

**Tim Sort - A Solução Industrial**:

O algoritmo usado no Python e Java combina o melhor dos dois mundos:
```python
def timsort(array):
    # 1. Detecta "runs" (sequências ordenadas)
    runs = find_runs(array)  # Encontra subsequências ordenadas
    
    # 2. Estende runs curtos com Insertion Sort
    for run in runs:
        if len(run) < MIN_MERGE:
            insertion_sort(run)
    
    # 3. Merge runs usando Merge Sort
    while len(runs) > 1:
        merge_runs(runs)
```

**Características do Tim Sort**:
- Detecta e aproveita ordem parcial existente
- Estável
- O(n) no melhor caso, O(n log n) no pior
- Usado em: Python's sorted(), Java's Arrays.sort(), Android

**Quando usar cada um**:
- **70%+ ordenado**: Insertion Sort puro
- **Dados mistos**: Tim Sort
- **Sem informação**: Quick Sort ou Merge Sort

**Benchmark Real** (1M elementos, 80% ordenados):
```
Insertion Sort: ~15ms
Tim Sort:       ~20ms
Quick Sort:     ~80ms
Merge Sort:     ~100ms
```

### Questão 4: Otimização do Bubble Sort

**Pergunta**: Como o Bubble Sort otimizado consegue atingir O(n) no melhor caso?

**Resposta Detalhada**:

**Mecanismo da Otimização**:

O Bubble Sort otimizado usa uma **flag booleana** para detectar quando o array já está ordenado:

```c
void bubbleSortOptimized(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;  // Flag: assumindo que não há trocas
        
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = 1;  // Marca que houve troca
            }
        }
        
        // Se não houve troca, array está ordenado
        if (swapped == 0) {
            break;  // Termina o algoritmo
        }
    }
}
```

**Análise do Melhor Caso**:

Para um array **já ordenado** [1, 2, 3, 4, 5]:

```
Passagem 1:
- Compara 1 e 2: 1 < 2, sem troca
- Compara 2 e 3: 2 < 3, sem troca
- Compara 3 e 4: 3 < 4, sem troca
- Compara 4 e 5: 4 < 5, sem troca
- swapped = 0 (nenhuma troca feita)
- BREAK - algoritmo termina!

Total: n-1 comparações = O(n)
```

**Sem otimização**:
```
Passagem 1: (n-1) comparações
Passagem 2: (n-2) comparações
Passagem 3: (n-3) comparações
...
Total: (n-1) + (n-2) + ... + 1 = O(n²)
```

**Otimizações Adicionais**:

1. **Cocktail Sort** (Bubble Sort bidirecional):
```c
void cocktailSort(int arr[], int n) {
    int swapped = 1;
    int start = 0, end = n - 1;
    
    while (swapped) {
        swapped = 0;
        
        // Passagem da esquerda para direita
        for (int i = start; i < end; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(&arr[i], &arr[i + 1]);
                swapped = 1;
            }
        }
        
        if (!swapped) break;
        
        end--;
        swapped = 0;
        
        // Passagem da direita para esquerda
        for (int i = end - 1; i >= start; i--) {
            if (arr[i] > arr[i + 1]) {
                swap(&arr[i], &arr[i + 1]);
                swapped = 1;
            }
        }
        
        start++;
    }
}
```
**Benefício**: Elementos pequenos no final "descem" mais rápido.

2. **Redução de range**:
```c
// Memoriza a última posição de troca
int lastSwap = n - 1;
for (int i = 0; i < n - 1; i++) {
    int newLastSwap = 0;
    for (int j = 0; j < lastSwap; j++) {
        if (arr[j] > arr[j + 1]) {
            swap(&arr[j], &arr[j + 1]);
            newLastSwap = j;
        }
    }
    if (newLastSwap == 0) break;
    lastSwap = newLastSwap;
}
```

**Quando a Otimização Realmente Ajuda**:
- Arrays já ordenados: O(n²) → O(n)
- Arrays quase ordenados: Reduz iterações significativamente
- Arrays aleatórios: Pouca melhora (ainda O(n²))

### Questão 5: Insertion Sort vs Quick Sort - Quando Usar?

**Pergunta**: Em que situações específicas você usaria Insertion Sort em vez de Quick Sort?

**Resposta Detalhada**:

**Situações Favoráveis ao Insertion Sort**:

1. **Arrays Pequenos (n < 10-50)**:
```
Benchmark (milissegundos):
n=10:  Insertion Sort: 0.001ms, Quick Sort: 0.002ms
n=20:  Insertion Sort: 0.003ms, Quick Sort: 0.005ms
n=50:  Insertion Sort: 0.015ms, Quick Sort: 0.025ms

Motivo: Overhead de recursão do Quick Sort supera o benefício
```

2. **Arrays Quase Ordenados**:
```c
// Array 95% ordenado
int arr[] = {1,2,3,4,5,100,7,8,9,10,11,12};

Insertion Sort: O(n + d) onde d = inversões
- Apenas ~7 inversões para corrigir
- Tempo: ~O(n)

Quick Sort: O(n log n)
- Não detecta ordem existente
- Sempre divide e conquista
```

3. **Ordenação Online (streaming)**:
```c
// Recebendo dados em tempo real
void processNewData(int value) {
    addToArray(value);
    insertionSort(array, size);  // Incrementalmente mantém ordenado
}

// Insertion Sort insere novo elemento em O(n)
// Quick Sort precisaria reordenar tudo em O(n log n)
```

4. **Estabilidade Requerida com Memória Limitada**:
```
Requisitos:
- Deve ser estável: ✓ Insertion Sort, ✗ Quick Sort
- Deve ser in-place: ✓ Ambos
- Memória O(1): ✓ Insertion Sort O(1), Quick Sort O(log n) pela pilha

Escolha: Insertion Sort
```

5. **Sistemas Embarcados com Restrições**:
```c
// Microcontrolador com 4KB RAM, processando 20 sensores
struct SensorData sensors[20];

// Insertion Sort:
// - Código simples: ~30 linhas
// - Sem recursão: stack pequeno
// - Previsível: sempre n² no pior caso

// Quick Sort:
// - Mais complexo: ~100 linhas  
// - Recursão: pode estourar stack
// - Imprevisível: n² no pior caso inesperado
```

6. **Quando Simplicidade é Crítica**:
```c
// Insertion Sort - cristalino
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
// 9 linhas, fácil de auditar e provar correto

// Quick Sort - mais complexo
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
// Requer função partition adicional, recursão, mais difícil provar
```

**Tabela de Decisão Prática**:

| Cenário | Escolha | Razão |
|---------|---------|-------|
| n < 50 | Insertion Sort | Menos overhead |
| 90%+ ordenado | Insertion Sort | O(n) adaptativo |
| Dados aleatórios grandes | Quick Sort | O(n log n) médio |
| Streaming/Online | Insertion Sort | Insere incrementalmente |
| Estável + In-place | Insertion Sort | Quick Sort não é estável |
| Embarcado/Crítico | Insertion Sort | Sem recursão, simples |
| Performance máxima | Tim Sort/Introsort | Híbrido = melhor dos 2 |

**Solução Industrial - Algoritmos Híbridos**:

A maioria das bibliotecas modernas usa uma combinação:

```c
void hybridSort(int arr[], int low, int high) {
    int size = high - low + 1;
    
    // Arrays pequenos: Insertion Sort
    if (size < CUTOFF) {  // CUTOFF = 10-20
        insertionSort(arr, low, high);
        return;
    }
    
    // Arrays grandes: Quick Sort
    int pi = partition(arr, low, high);
    hybridSort(arr, low, pi - 1);
    hybridSort(arr, pi + 1, high);
}
```

**Exemplos Reais**:
- **C++ std::sort**: Introsort (Quick + Heap + Insertion)
- **Python sorted()**: Tim Sort (Merge + Insertion)
- **Java Arrays.sort()**: Dual-Pivot Quick + Insertion
- **Linux kernel**: Heap Sort (garantias em kernel space)

**Conclusão**: Insertion Sort domina em pequenas escalas e dados parcialmente ordenados. Quick Sort domina em grandes volumes de dados aleatórios. Algoritmos modernos combinam ambos para obter o melhor resultado.

## 📋 Exercícios Práticos

### Nível Básico
1. Implemente uma versão do Bubble Sort que conte o número de trocas realizadas
2. Modifique o Selection Sort para encontrar simultaneamente o maior e menor elemento
3. Crie uma versão do Insertion Sort que ordene em ordem decrescente

### Nível Intermediário
4. Implemente uma versão híbrida que use Insertion Sort para subarrays pequenos (< 10 elementos) e Quick Sort para arrays maiores
5. Desenvolva uma função que determine automaticamente o melhor algoritmo baseado no tamanho e características do array
6. Crie um Merge Sort iterativo (bottom-up) em vez da versão recursiva

### Nível Avançado
7. Implemente o algoritmo Introsort (Quick Sort com fallback para Heap Sort)
8. Desenvolva uma versão paralela do Merge Sort usando threads
9. Crie um algoritmo de ordenação adaptativo que detecte padrões nos dados

### Desafios
10. Implemente Radix Sort para números negativos
11. Desenvolva um algoritmo de ordenação externo para arquivos que não cabem na memória
12. Crie um visualizador em tempo real dos algoritmos de ordenação

## 🔧 Próximas Implementações

- [ ] Radix Sort (ordenação por dígitos)
- [ ] Counting Sort (ordenação por contagem)
- [ ] Bucket Sort (ordenação por baldes)
- [ ] Tim Sort (algoritmo híbrido usado no Python)
- [ ] Introsort (Quick Sort + Heap Sort híbrido)
- [ ] Visualizador gráfico de algoritmos
- [ ] Testes automatizados unitários
- [ ] Análise de estabilidade detalhada
- [ ] Implementações paralelas (OpenMP)
- [ ] Comparação com bibliotecas padrão (qsort)