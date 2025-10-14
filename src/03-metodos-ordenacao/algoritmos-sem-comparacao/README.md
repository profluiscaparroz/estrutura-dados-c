# Algoritmos de Ordenação Sem Comparação

Este diretório contém implementações de algoritmos de ordenação que **não utilizam comparações** entre elementos para determinar sua ordem. Em vez disso, eles se baseiam em propriedades específicas dos dados, como frequência, dígitos ou distribuição.

## 🚀 Características Principais

Ao contrário dos algoritmos baseados em comparação (que têm limite inferior de Ω(n log n)), os algoritmos sem comparação podem alcançar **complexidade linear O(n)** sob condições específicas.

### Vantagens
- ✅ Podem ser mais rápidos que O(n log n) para casos específicos
- ✅ Complexidade linear quando as condições são atendidas
- ✅ Úteis para tipos de dados específicos (inteiros, strings)

### Limitações
- ⚠️ Requerem conhecimento prévio sobre os dados (range, distribuição)
- ⚠️ Podem usar mais memória (não são in-place)
- ⚠️ Funcionam melhor com tipos de dados específicos

## 📁 Algoritmos Implementados

### 1. Counting Sort (`countingSort.c`)

**Ordenação por Contagem**

- **Complexidade de Tempo**: O(n + k), onde k é o range dos valores
- **Complexidade de Espaço**: O(n + k)
- **Estável**: ✅ Sim
- **In-place**: ❌ Não

**Funcionamento**: Conta a frequência de cada elemento e usa essas contagens para determinar a posição final de cada elemento.

**Melhor uso**:
- Quando o range de valores (k) é pequeno comparado com n
- Para inteiros não-negativos
- Quando estabilidade é necessária

**Exemplo**:
```c
int arr[] = {4, 2, 2, 8, 3, 3, 1};
countingSort(arr, 7);
// Resultado: [1, 2, 2, 3, 3, 4, 8]
```

### 2. Radix Sort (`radixSort.c`)

**Ordenação por Dígitos**

- **Complexidade de Tempo**: O(d × (n + k)), onde d é o número de dígitos e k é a base
- **Complexidade de Espaço**: O(n + k)
- **Estável**: ✅ Sim
- **In-place**: ❌ Não

**Funcionamento**: Ordena os números dígito por dígito, começando do dígito menos significativo (unidades) até o mais significativo. Usa counting sort como sub-rotina.

**Melhor uso**:
- Para inteiros com número fixo de dígitos
- Quando o número de dígitos é pequeno
- Números com base fixa (decimal, binário, etc)

**Exemplo**:
```c
int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
radixSort(arr, 8);
// Resultado: [2, 24, 45, 66, 75, 90, 170, 802]
```

### 3. Bucket Sort (`bucketSort.c`)

**Ordenação por Baldes**

- **Complexidade de Tempo**: O(n + k) no caso médio, O(n²) no pior caso
- **Complexidade de Espaço**: O(n + k)
- **Estável**: Depende do algoritmo usado nos baldes
- **In-place**: ❌ Não

**Funcionamento**: Distribui os elementos em vários "baldes" (buckets) baseado em seu valor, ordena cada balde individualmente, e depois concatena os baldes.

**Melhor uso**:
- Quando os dados estão uniformemente distribuídos
- Para números em ponto flutuante no intervalo [0, 1)
- Para otimizar ordenação com distribuição conhecida

**Exemplo**:
```c
float arr[] = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
bucketSort(arr, 6);
// Resultado: [0.123, 0.343, 0.565, 0.656, 0.665, 0.897]
```

## 🔍 Comparação com Algoritmos Baseados em Comparação

| Característica | Baseados em Comparação | Sem Comparação |
|----------------|------------------------|----------------|
| **Limite inferior** | Ω(n log n) | O(n) possível |
| **Requisitos** | Relação de ordem | Propriedades dos dados |
| **Flexibilidade** | Funcionam com qualquer tipo | Tipos específicos |
| **Memória** | Podem ser in-place | Geralmente requerem espaço extra |
| **Exemplos** | Quick Sort, Merge Sort | Counting, Radix, Bucket |

## 📊 Quando Usar Cada Algoritmo

### Use Counting Sort quando:
- O range de valores é pequeno (k ≈ O(n))
- Você tem apenas inteiros não-negativos
- Precisa de um algoritmo estável
- Exemplo: Ordenar idades de pessoas (0-120)

### Use Radix Sort quando:
- Você tem números com número fixo de dígitos
- O número de dígitos é pequeno
- Precisa de estabilidade
- Exemplo: Ordenar números de telefone, CEPs

### Use Bucket Sort quando:
- Os dados estão uniformemente distribuídos
- Você conhece a distribuição dos dados
- Trabalhando com números em ponto flutuante
- Exemplo: Ordenar pontuações normalizadas (0.0 a 1.0)

## 🚀 Como Compilar e Executar

### Compilar todos os algoritmos:
```bash
gcc -o countingSort countingSort.c -Wall -Wextra -O2
gcc -o radixSort radixSort.c -Wall -Wextra -O2
gcc -o bucketSort bucketSort.c -Wall -Wextra -O2
```

### Executar:
```bash
./countingSort
./radixSort
./bucketSort
```

### Compilar com debug:
```bash
gcc -o countingSort countingSort.c -Wall -Wextra -g
```

## 📚 Teoria e Fundamentos

### Por que podem ser mais rápidos que O(n log n)?

O limite inferior de Ω(n log n) para algoritmos de ordenação **se aplica apenas a algoritmos baseados em comparação**. Este limite vem da teoria da informação: há n! permutações possíveis de n elementos, e você precisa de pelo menos log₂(n!) ≈ n log n comparações para distinguir entre elas.

Algoritmos sem comparação **contornam este limite** ao não usar comparações diretas. Em vez disso, eles:

1. **Counting Sort**: Usa as chaves como índices em um array
2. **Radix Sort**: Usa a estrutura posicional dos números
3. **Bucket Sort**: Usa conhecimento sobre a distribuição dos dados

### Limitações Teóricas

Apesar de poderem ser lineares, esses algoritmos têm suas próprias limitações:

- **Counting Sort**: O(n + k) - se k >> n, pode ser pior que O(n log n)
- **Radix Sort**: O(d × n) - se d é grande, perde eficiência
- **Bucket Sort**: O(n²) no pior caso se todos os elementos caem no mesmo balde

## 🧪 Exemplos de Uso Prático

### Counting Sort - Ordenar votos por idade
```c
// Array de idades (18-65)
int idades[] = {23, 45, 32, 18, 65, 23, 34, 45};
countingSort(idades, 8);
```

### Radix Sort - Ordenar números de matrícula
```c
// Números de 6 dígitos
int matriculas[] = {123456, 234567, 123123, 987654};
radixSort(matriculas, 4);
```

### Bucket Sort - Ordenar notas normalizadas
```c
// Notas entre 0.0 e 1.0
float notas[] = {0.85, 0.92, 0.73, 0.65, 0.88};
bucketSort(notas, 5);
```

## 📖 Referências

1. **Cormen, T. H., et al.** - "Introduction to Algorithms" (4th ed.)
   - Capítulo 8: Sorting in Linear Time
   
2. **Knuth, D. E.** - "The Art of Computer Programming, Vol. 3: Sorting and Searching"
   - Seção 5.2: Internal Sorting (especialmente 5.2.5 sobre Sorting by Distribution)

3. **Sedgewick, R.** - "Algorithms" (4th ed.)
   - Capítulo 5: Strings (para Radix Sort)

## 🎯 Exercícios Sugeridos

1. **Modificar Counting Sort** para trabalhar com números negativos
2. **Implementar Radix Sort** para strings
3. **Otimizar Bucket Sort** para melhor distribuição de baldes
4. **Comparar performance** com algoritmos baseados em comparação
5. **Implementar versão paralela** usando threads (para arrays grandes)

## 💡 Dicas de Implementação

1. **Sempre valide** se seus dados atendem aos requisitos do algoritmo
2. **Cuidado com overflow** ao calcular índices
3. **Considere o trade-off** memória vs. tempo
4. **Use profiling** para identificar gargalos
5. **Teste com diferentes distribuições** de dados

---

**Nota**: Estes algoritmos são ferramentas especializadas. Use-os quando as condições forem apropriadas, mas não hesite em usar Quick Sort ou Merge Sort para casos gerais!
