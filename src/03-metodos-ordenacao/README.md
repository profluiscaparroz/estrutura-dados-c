# Métodos de Ordenação em C

Este diretório contém implementações de algoritmos clássicos de ordenação em linguagem C, com exemplos práticos e comparações de desempenho.

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

**Como funciona:**
- Compara elementos adjacentes e os troca se estiverem fora de ordem
- Repete o processo até que nenhuma troca seja necessária
- O maior elemento "borbulha" para o final a cada passagem

**Quando usar:**
- Listas muito pequenas (< 10 elementos)
- Fins educacionais
- Quando simplicidade é mais importante que eficiência

**Exemplo de uso:**
```c
int arr[] = {64, 34, 25, 12, 22, 11, 90};
int n = 7;
bubbleSort(arr, n);
// Resultado: {11, 12, 22, 25, 34, 64, 90}
```

### 2. Insertion Sort (`insertSort.c`)

**Como funciona:**
- Constrói a lista ordenada um elemento por vez
- Insere cada elemento na posição correta em relação aos já ordenados
- Similar a organizar cartas na mão

**Quando usar:**
- Arrays pequenos ou quase ordenados
- Como parte de algoritmos híbridos
- Quando estabilidade é importante

**Exemplo de uso:**
```c
int arr[] = {12, 11, 13, 5, 6};
int n = 5;
insertionSort(arr, n);
// Resultado: {5, 6, 11, 12, 13}
```

### 3. Selection Sort (`selectSort.c`)

**Como funciona:**
- Encontra o menor elemento e o coloca na primeira posição
- Encontra o segundo menor e o coloca na segunda posição
- Repete até ordenar toda a lista

**Quando usar:**
- Quando o número de trocas deve ser minimizado
- Listas pequenas
- Quando a memória é limitada

**Exemplo de uso:**
```c
int arr[] = {64, 25, 12, 22, 11};
int n = 5;
selectionSort(arr, n);
// Resultado: {11, 12, 22, 25, 64}
```

### 4. Quick Sort (`quickSort.c`)

**Como funciona:**
- Escolhe um pivô e particiona o array
- Elementos menores ficam à esquerda, maiores à direita
- Aplica recursivamente o processo nas partições

**Quando usar:**
- Listas grandes
- Quando velocidade média é importante
- Implementação padrão em muitas bibliotecas

**Exemplo de uso:**
```c
int arr[] = {10, 7, 8, 9, 1, 5};
int n = 6;
quickSort(arr, 0, n - 1);
// Resultado: {1, 5, 7, 8, 9, 10}
```

### 6. Heap Sort (`heapSort.c`)

**Como funciona:**
- Constrói um heap máximo a partir do array
- Extrai repetidamente o máximo (raiz) para o final
- Reconstrói o heap com elementos restantes

**Quando usar:**
- Quando garantia de O(n log n) é necessária
- Sistemas com restrições de memória
- Quando estabilidade não é importante

**Exemplo de uso:**
```c
int arr[] = {12, 11, 13, 5, 6, 7};
int n = 6;
heapSort(arr, n);
// Resultado: {5, 6, 7, 11, 12, 13}
```

### 7. Shell Sort (`shellSort.c`)

**Como funciona:**
- Generalização do Insertion Sort
- Usa gaps decrescentes para comparar elementos distantes
- Termina com gap = 1 (Insertion Sort normal)

**Quando usar:**
- Arrays de tamanho médio (1000-5000 elementos)
- Quando simplicidade de implementação é importante
- Como alternativa ao Insertion Sort para arrays maiores

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

## 🤔 Questões para Reflexão

1. **Estabilidade**: Por que a estabilidade é importante em algoritmos de ordenação? Dê um exemplo prático onde isso seria relevante.

2. **Complexidade**: Explique por que Quick Sort tem complexidade O(n²) no pior caso, mas ainda é considerado um dos melhores algoritmos na prática.

3. **Escolha de Algoritmo**: Para um array de 1 milhão de elementos já parcialmente ordenado, qual algoritmo você escolheria e por quê?

4. **Otimização**: Como o Bubble Sort otimizado consegue atingir O(n) no melhor caso?

5. **Aplicação**: Em que situações específicas você usaria Insertion Sort em vez de Quick Sort?

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