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

---

#### 📊 Como Funciona - Passo a Passo (Tipo Planilha Excel)

Vamos ordenar o array: **[4, 2, 2, 8, 3, 3, 1]**

**PASSO 1: Array Original**
```
Índice:  0  1  2  3  4  5  6
Valor:   4  2  2  8  3  3  1
```

**PASSO 2: Encontrar o Valor Máximo**
- Percorremos o array e encontramos o maior valor: **8**
- Isso significa que precisamos de um array de contagem de tamanho 9 (0 a 8)

**PASSO 3: Criar Array de Contagem (count)**
- Criamos um array `count` de tamanho 9 (índices de 0 a 8)
- Inicialmente todos os valores são 0

```
Valor:    0  1  2  3  4  5  6  7  8
Count:    0  0  0  0  0  0  0  0  0
```

**PASSO 4: Contar Frequência de Cada Elemento**
- Percorremos o array original
- Para cada elemento, incrementamos count[elemento]

```
Processando 4: count[4]++
Processando 2: count[2]++
Processando 2: count[2]++
Processando 8: count[8]++
Processando 3: count[3]++
Processando 3: count[3]++
Processando 1: count[1]++

Resultado:
Valor:    0  1  2  3  4  5  6  7  8
Count:    0  1  2  2  1  0  0  0  1
         ↑  ↑  ↑  ↑  ↑           ↑
         |  1x 2x 2x 1x          1x
       nunca aparece
```

**PASSO 5: Calcular Posições Acumuladas**
- Transformamos count em posições acumuladas
- count[i] = count[i] + count[i-1]
- Isso nos dá a posição final de cada elemento

```
Antes:    0  1  2  3  4  5  6  7  8
          0  1  2  2  1  0  0  0  1

Calculando acumulado:
count[1] = count[1] + count[0] = 1 + 0 = 1
count[2] = count[2] + count[1] = 2 + 1 = 3
count[3] = count[3] + count[2] = 2 + 3 = 5
count[4] = count[4] + count[3] = 1 + 5 = 6
count[5] = count[5] + count[4] = 0 + 6 = 6
count[6] = count[6] + count[5] = 0 + 6 = 6
count[7] = count[7] + count[6] = 0 + 6 = 6
count[8] = count[8] + count[7] = 1 + 6 = 7

Depois:   0  1  2  3  4  5  6  7  8
          0  1  3  5  6  6  6  6  7
             ↑  ↑  ↑  ↑           ↑
             |  |  |  |           |
          1 vai até posição 1
             2 vai até posição 3
                3 vai até posição 5
                   4 vai até posição 6
                      8 vai até posição 7
```

**PASSO 6: Construir Array de Saída (de trás para frente para manter estabilidade)**
- Percorremos o array original de trás para frente
- Para cada elemento, colocamos na posição indicada por count
- Depois decrementamos count para o próximo elemento igual

```
Array original: [4, 2, 2, 8, 3, 3, 1]
Índices:         0  1  2  3  4  5  6

Processando de trás para frente (i = 6 até i = 0):

i=6, valor=1:
  count[1]=1, então output[1-1]=output[0]=1
  count[1]-- → count[1]=0
  Output: [1, _, _, _, _, _, _]

i=5, valor=3:
  count[3]=5, então output[5-1]=output[4]=3
  count[3]-- → count[3]=4
  Output: [1, _, _, _, 3, _, _]

i=4, valor=3:
  count[3]=4, então output[4-1]=output[3]=3
  count[3]-- → count[3]=3
  Output: [1, _, _, 3, 3, _, _]

i=3, valor=8:
  count[8]=7, então output[7-1]=output[6]=8
  count[8]-- → count[8]=6
  Output: [1, _, _, 3, 3, _, 8]

i=2, valor=2:
  count[2]=3, então output[3-1]=output[2]=2
  count[2]-- → count[2]=2
  Output: [1, _, 2, 3, 3, _, 8]

i=1, valor=2:
  count[2]=2, então output[2-1]=output[1]=2
  count[2]-- → count[2]=1
  Output: [1, 2, 2, 3, 3, _, 8]

i=0, valor=4:
  count[4]=6, então output[6-1]=output[5]=4
  count[4]-- → count[4]=5
  Output: [1, 2, 2, 3, 3, 4, 8]
```

**RESULTADO FINAL:**
```
Array Ordenado: [1, 2, 2, 3, 3, 4, 8]
                 ↑  ↑  ↑  ↑  ↑  ↑  ↑
                 |  |  |  |  |  |  |
              menor              maior
```

**💡 Por que funciona?**
- O array `count` nos diz quantos elementos são menores ou iguais a cada valor
- Isso determina exatamente onde cada elemento deve ficar no array ordenado
- Processar de trás para frente mantém a ordem relativa de elementos iguais (estabilidade)

**Exemplo de Código**:
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

---

#### 📊 Como Funciona - Passo a Passo (Tipo Planilha Excel)

Vamos ordenar o array: **[170, 45, 75, 90, 802, 24, 2, 66]**

**CONCEITO CHAVE**: Radix Sort ordena números processando cada dígito separadamente, **começando da direita (unidades) para a esquerda (centenas, milhares, etc.)**

**PASSO 0: Array Original**
```
Índice:  0    1   2   3    4   5   6   7
Valor:  170  45  75  90  802  24   2  66

Vamos representar cada número por seus dígitos:
170 = 1 7 0
 45 = 0 4 5
 75 = 0 7 5
 90 = 0 9 0
802 = 8 0 2
 24 = 0 2 4
  2 = 0 0 2
 66 = 0 6 6
```

**PASSO 1: Encontrar o Valor Máximo**
- Maior valor: **802**
- Número de dígitos: **3** (centenas, dezenas, unidades)
- Vamos fazer 3 passadas: unidades → dezenas → centenas

---

**🔄 PASSADA 1: Ordenar pelo dígito das UNIDADES (posição 1)**

Extraindo o dígito das unidades de cada número:
```
Número:  170  45  75  90  802  24   2  66
Unidade:  0   5   5   0    2   4   2   6
          ↑   ↑   ↑   ↑    ↑   ↑   ↑   ↑
```

Aplicando Counting Sort no dígito das unidades:
```
Dígito 0: 170, 90   (2 números)
Dígito 1: (nenhum)
Dígito 2: 802, 2    (2 números)
Dígito 3: (nenhum)
Dígito 4: 24        (1 número)
Dígito 5: 45, 75    (2 números)
Dígito 6: 66        (1 número)
Dígito 7: (nenhum)
Dígito 8: (nenhum)
Dígito 9: (nenhum)

Array após ordenar por UNIDADES:
[170, 90, 802, 2, 24, 45, 75, 66]
  ↑   ↑    ↑  ↑   ↑   ↑   ↑   ↑
  0   0    2  2   4   5   5   6  ← dígitos das unidades em ordem
```

---

**🔄 PASSADA 2: Ordenar pelo dígito das DEZENAS (posição 10)**

Agora pegamos o resultado anterior e ordenamos pelas dezenas:
```
Array atual: [170, 90, 802, 2, 24, 45, 75, 66]

Extraindo o dígito das dezenas:
Número:  170  90  802   2  24  45  75  66
Dezena:   7   9    0   0   2   4   7   6
          ↑   ↑    ↑   ↑   ↑   ↑   ↑   ↑
```

Aplicando Counting Sort no dígito das dezenas:
```
Dígito 0: 802, 2    (2 números)
Dígito 1: (nenhum)
Dígito 2: 24        (1 número)
Dígito 3: (nenhum)
Dígito 4: 45        (1 número)
Dígito 5: (nenhum)
Dígito 6: 66        (1 número)
Dígito 7: 170, 75   (2 números)
Dígito 8: (nenhum)
Dígito 9: 90        (1 número)

Array após ordenar por DEZENAS:
[802, 2, 24, 45, 66, 170, 75, 90]
  ↑  ↑   ↑   ↑   ↑    ↑   ↑   ↑
  0  0   2   4   6    7   7   9  ← dígitos das dezenas em ordem
```

---

**🔄 PASSADA 3: Ordenar pelo dígito das CENTENAS (posição 100)**

Agora pegamos o resultado anterior e ordenamos pelas centenas:
```
Array atual: [802, 2, 24, 45, 66, 170, 75, 90]

Extraindo o dígito das centenas:
Número:  802  2  24  45  66  170  75  90
Centena:  8  0   0   0   0    1   0   0
          ↑  ↑   ↑   ↑   ↑    ↑   ↑   ↑
```

Aplicando Counting Sort no dígito das centenas:
```
Dígito 0: 2, 24, 45, 66, 75, 90   (6 números)
Dígito 1: 170                      (1 número)
Dígito 2: (nenhum)
...
Dígito 8: 802                      (1 número)

Array após ordenar por CENTENAS (FINAL):
[2, 24, 45, 66, 75, 90, 170, 802]
 ↑   ↑   ↑   ↑   ↑   ↑    ↑    ↑
 0   0   0   0   0   0    1    8  ← dígitos das centenas em ordem
```

---

**RESULTADO FINAL:**
```
Array Original:  [170, 45, 75, 90, 802, 24, 2, 66]
Array Ordenado:  [2, 24, 45, 66, 75, 90, 170, 802]
                  ↑                              ↑
                menor                          maior
```

**📋 Resumo Visual das Passadas:**
```
Original:          [170,  45,  75,  90, 802,  24,   2,  66]
                         ↓ Ordena por UNIDADES ↓
Após Unidades:     [170,  90, 802,   2,  24,  45,  75,  66]
                         ↓ Ordena por DEZENAS ↓
Após Dezenas:      [802,   2,  24,  45,  66, 170,  75,  90]
                         ↓ Ordena por CENTENAS ↓
FINAL:             [  2,  24,  45,  66,  75,  90, 170, 802] ✓
```

**💡 Por que funciona?**
- Processando da direita para esquerda (unidades → dezenas → centenas), cada passada mantém a ordenação das passadas anteriores
- A **estabilidade** do Counting Sort é crucial: números com o mesmo dígito mantêm sua ordem relativa
- Exemplo: Na passada de centenas, 2 e 24 ambos têm 0 como centena. Como 2 vem antes de 24 na passada anterior, ele permanece antes na final
- É como ordenar cartas: primeiro por naipe, depois por valor - a ordem final considera ambos os critérios

**Exemplo de Código**:
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

---

#### 📊 Como Funciona - Passo a Passo (Tipo Planilha Excel)

Vamos ordenar o array: **[0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68]**

**CONCEITO CHAVE**: Bucket Sort distribui os elementos em "baldes" (buckets) baseado em faixas de valores, ordena cada balde separadamente, e depois junta todos.

**PASSO 0: Array Original**
```
Índice:  0     1     2     3     4     5     6     7     8     9
Valor:  0.78  0.17  0.39  0.26  0.72  0.94  0.21  0.12  0.23  0.68

Vamos usar 10 baldes para valores entre 0.0 e 1.0
```

**PASSO 1: Criar os Baldes Vazios**
- Número de baldes: **10** (mesmo que o número de elementos)
- Cada balde representa um intervalo de valores

```
Balde 0: [0.00 - 0.10) → vazio
Balde 1: [0.10 - 0.20) → vazio
Balde 2: [0.20 - 0.30) → vazio
Balde 3: [0.30 - 0.40) → vazio
Balde 4: [0.40 - 0.50) → vazio
Balde 5: [0.50 - 0.60) → vazio
Balde 6: [0.60 - 0.70) → vazio
Balde 7: [0.70 - 0.80) → vazio
Balde 8: [0.80 - 0.90) → vazio
Balde 9: [0.90 - 1.00) → vazio
```

---

**PASSO 2: Distribuir Elementos nos Baldes**

Para cada elemento, calculamos o índice do balde:
**bucketIndex = floor(n × valor)** onde n = 10

Processando cada elemento:

```
0.78 → balde = floor(10 × 0.78) = floor(7.8) = 7
  Balde 7: [0.78]

0.17 → balde = floor(10 × 0.17) = floor(1.7) = 1
  Balde 1: [0.17]

0.39 → balde = floor(10 × 0.39) = floor(3.9) = 3
  Balde 3: [0.39]

0.26 → balde = floor(10 × 0.26) = floor(2.6) = 2
  Balde 2: [0.26]

0.72 → balde = floor(10 × 0.72) = floor(7.2) = 7
  Balde 7: [0.78, 0.72]

0.94 → balde = floor(10 × 0.94) = floor(9.4) = 9
  Balde 9: [0.94]

0.21 → balde = floor(10 × 0.21) = floor(2.1) = 2
  Balde 2: [0.26, 0.21]

0.12 → balde = floor(10 × 0.12) = floor(1.2) = 1
  Balde 1: [0.17, 0.12]

0.23 → balde = floor(10 × 0.23) = floor(2.3) = 2
  Balde 2: [0.26, 0.21, 0.23]

0.68 → balde = floor(10 × 0.68) = floor(6.8) = 6
  Balde 6: [0.68]
```

**Estado dos Baldes Após Distribuição:**
```
Balde 0: [0.00-0.10) → [ ] (vazio)
Balde 1: [0.10-0.20) → [0.17, 0.12]
Balde 2: [0.20-0.30) → [0.26, 0.21, 0.23]
Balde 3: [0.30-0.40) → [0.39]
Balde 4: [0.40-0.50) → [ ] (vazio)
Balde 5: [0.50-0.60) → [ ] (vazio)
Balde 6: [0.60-0.70) → [0.68]
Balde 7: [0.70-0.80) → [0.78, 0.72]
Balde 8: [0.80-0.90) → [ ] (vazio)
Balde 9: [0.90-1.00) → [0.94]
```

---

**PASSO 3: Ordenar Cada Balde Individualmente**

Usamos Insertion Sort (ou outro algoritmo) para ordenar cada balde:

```
Balde 0: [ ] → [ ] (já ordenado)

Balde 1: [0.17, 0.12]
  Comparando: 0.17 > 0.12? Sim, troca
  Resultado: [0.12, 0.17]

Balde 2: [0.26, 0.21, 0.23]
  Passo 1: 0.26 e 0.21 → [0.21, 0.26, 0.23]
  Passo 2: inserir 0.23 → [0.21, 0.23, 0.26]
  Resultado: [0.21, 0.23, 0.26]

Balde 3: [0.39] → [0.39] (apenas 1 elemento)

Balde 4: [ ] → [ ] (vazio)

Balde 5: [ ] → [ ] (vazio)

Balde 6: [0.68] → [0.68] (apenas 1 elemento)

Balde 7: [0.78, 0.72]
  Comparando: 0.78 > 0.72? Sim, troca
  Resultado: [0.72, 0.78]

Balde 8: [ ] → [ ] (vazio)

Balde 9: [0.94] → [0.94] (apenas 1 elemento)
```

**Estado dos Baldes Após Ordenação Individual:**
```
Balde 0: [ ]
Balde 1: [0.12, 0.17]        ✓ ordenado
Balde 2: [0.21, 0.23, 0.26]  ✓ ordenado
Balde 3: [0.39]              ✓ ordenado
Balde 4: [ ]
Balde 5: [ ]
Balde 6: [0.68]              ✓ ordenado
Balde 7: [0.72, 0.78]        ✓ ordenado
Balde 8: [ ]
Balde 9: [0.94]              ✓ ordenado
```

---

**PASSO 4: Concatenar os Baldes**

Juntamos todos os baldes em ordem (do balde 0 ao balde 9):

```
Resultado = Balde 0 + Balde 1 + Balde 2 + ... + Balde 9

Resultado = [ ] + [0.12, 0.17] + [0.21, 0.23, 0.26] + [0.39] + [ ] + 
            [ ] + [0.68] + [0.72, 0.78] + [ ] + [0.94]

Resultado = [0.12, 0.17, 0.21, 0.23, 0.26, 0.39, 0.68, 0.72, 0.78, 0.94]
```

---

**RESULTADO FINAL:**
```
Array Original:  [0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68]
Array Ordenado:  [0.12, 0.17, 0.21, 0.23, 0.26, 0.39, 0.68, 0.72, 0.78, 0.94]
                  ↑                                                          ↑
                menor                                                      maior
```

**📋 Visualização Completa do Processo:**
```
                    DISTRIBUIÇÃO NOS BALDES
                    
Original: [0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68]
              ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓

Balde 0: [0.00-0.10) → [ ]
Balde 1: [0.10-0.20) → [0.17, 0.12] → ordena → [0.12, 0.17]
Balde 2: [0.20-0.30) → [0.26, 0.21, 0.23] → ordena → [0.21, 0.23, 0.26]
Balde 3: [0.30-0.40) → [0.39]
Balde 4: [0.40-0.50) → [ ]
Balde 5: [0.50-0.60) → [ ]
Balde 6: [0.60-0.70) → [0.68]
Balde 7: [0.70-0.80) → [0.78, 0.72] → ordena → [0.72, 0.78]
Balde 8: [0.80-0.90) → [ ]
Balde 9: [0.90-1.00) → [0.94]

              ↓ CONCATENA TODOS OS BALDES ↓

Final: [0.12, 0.17, 0.21, 0.23, 0.26, 0.39, 0.68, 0.72, 0.78, 0.94] ✓
```

**💡 Por que funciona?**
- Os elementos são distribuídos em baldes baseado em sua magnitude (valores menores vão para baldes menores)
- Como os baldes representam intervalos ordenados (balde 0 < balde 1 < balde 2...), concatená-los produz um array ordenado
- A eficiência depende da **distribuição uniforme**: se todos os elementos caírem no mesmo balde, vira O(n²)
- É como organizar cartas de baralho: primeiro separa por naipe, depois ordena cada naipe separadamente

**⚠️ Nota sobre Performance:**
- **Melhor caso**: Elementos uniformemente distribuídos → cada balde tem poucos elementos → O(n)
- **Pior caso**: Todos elementos no mesmo balde → O(n²) (pior que Quick Sort!)
- **Chave do sucesso**: Conhecer a distribuição dos dados de antemão

**Exemplo de Código**:
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

---

## 🎯 Comparação Detalhada Entre os 3 Algoritmos

### Tabela Comparativa Completa

| Aspecto | Counting Sort | Radix Sort | Bucket Sort |
|---------|--------------|------------|-------------|
| **Complexidade Tempo (Médio)** | O(n + k) | O(d × (n + k)) | O(n + n²/k) ≈ O(n) |
| **Complexidade Tempo (Pior)** | O(n + k) | O(d × (n + k)) | O(n²) |
| **Complexidade Espaço** | O(n + k) | O(n + k) | O(n × k) |
| **Estável** | ✅ Sim | ✅ Sim | Depende |
| **In-place** | ❌ Não | ❌ Não | ❌ Não |
| **Tipo de Dados** | Inteiros não-negativos | Inteiros | Float/Int distribuídos |
| **Requisito Principal** | Range pequeno (k ≤ n) | Poucos dígitos (d pequeno) | Distribuição uniforme |
| **Quando k ou d é grande** | ❌ Ruim | ❌ Ruim | ✅ OK se uniforme |
| **Facilidade de Implementação** | ⭐⭐⭐ Fácil | ⭐⭐ Médio | ⭐ Difícil |

**Legenda:**
- n = número de elementos
- k = range dos valores (max - min + 1) para Counting; base (10) para Radix; número de baldes para Bucket
- d = número de dígitos

### 🎓 Qual Algoritmo Escolher?

```
┌─────────────────────────────────────────────────────────┐
│         ÁRVORE DE DECISÃO PARA ESCOLHA                  │
└─────────────────────────────────────────────────────────┘

Você tem inteiros não-negativos?
│
├─ SIM ──→ O range é pequeno (k ≈ n)?
│          │
│          ├─ SIM ──→ ✅ USE COUNTING SORT
│          │          • Mais simples e eficiente
│          │          • Exemplo: idades (0-120), notas (0-100)
│          │
│          └─ NÃO ──→ Os números têm poucos dígitos?
│                     │
│                     ├─ SIM ──→ ✅ USE RADIX SORT
│                     │          • Melhor para números grandes
│                     │          • Exemplo: CEPs, telefones, IDs
│                     │
│                     └─ NÃO ──→ ⚠️ Use Quick/Merge Sort
│
└─ NÃO ──→ São números float entre [0, 1)?
           │
           ├─ SIM ──→ Distribuição uniforme conhecida?
           │          │
           │          ├─ SIM ──→ ✅ USE BUCKET SORT
           │          │          • Ótimo para dados uniformes
           │          │          • Exemplo: probabilidades, notas normalizadas
           │          │
           │          └─ NÃO ──→ ⚠️ Use Quick/Merge Sort
           │
           └─ NÃO ──→ ⚠️ Use algoritmos baseados em comparação
```

### 📊 Exemplos Práticos de Uso

#### Exemplo 1: Ordenar Idades de Estudantes
```
Dados: [23, 19, 25, 19, 22, 21, 23, 20]
Range: 19-25 (k = 7, n = 8)
✅ ESCOLHA: Counting Sort
Razão: Range pequeno, inteiros não-negativos
```

#### Exemplo 2: Ordenar CEPs
```
Dados: [12345678, 98765432, 11111111, 55555555]
Range: 11111111-98765432 (k muito grande!)
Dígitos: 8 (d = 8)
✅ ESCOLHA: Radix Sort
Razão: Range enorme, mas poucos dígitos
```

#### Exemplo 3: Ordenar Notas Normalizadas
```
Dados: [0.85, 0.92, 0.73, 0.65, 0.88, 0.79]
Range: [0, 1), distribuição uniforme
✅ ESCOLHA: Bucket Sort
Razão: Float uniformemente distribuídos
```

#### Exemplo 4: Ordenar Números Aleatórios Grandes
```
Dados: [9847621938, 1928374655, 8273645512, ...]
Range: Enorme
Dígitos: Muitos (10+)
❌ NÃO USE algoritmos sem comparação
✅ ESCOLHA: Quick Sort ou Merge Sort
Razão: Nem range nem dígitos são favoráveis
```

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

### ✅ Boas Práticas

1. **Sempre valide** se seus dados atendem aos requisitos do algoritmo
   ```c
   // Para Counting Sort, verificar se há valores negativos
   for (int i = 0; i < n; i++) {
       if (arr[i] < 0) {
           printf("Erro: Counting Sort não aceita negativos!\n");
           return;
       }
   }
   ```

2. **Cuidado com overflow** ao calcular índices
   ```c
   // Para Bucket Sort
   int bucketIndex = (int)(numBuckets * arr[i]);
   if (bucketIndex >= numBuckets) {
       bucketIndex = numBuckets - 1;  // Prevenir overflow
   }
   ```

3. **Considere o trade-off** memória vs. tempo
   - Counting Sort: O(k) memória extra - pode ser proibitivo se k é muito grande
   - Radix Sort: O(n) memória extra - mais aceitável
   - Bucket Sort: O(n + k) memória extra - cuidado com muitos baldes

4. **Use profiling** para identificar gargalos
   ```c
   clock_t start = clock();
   countingSort(arr, n);
   clock_t end = clock();
   printf("Tempo: %f segundos\n", (double)(end - start) / CLOCKS_PER_SEC);
   ```

5. **Teste com diferentes distribuições** de dados
   - Dados uniformemente distribuídos
   - Dados com muitas repetições
   - Dados já ordenados
   - Dados em ordem reversa

### ❌ Erros Comuns a Evitar

#### Erro 1: Usar Counting Sort com range muito grande
```c
// ❌ ERRADO
int arr[] = {1, 1000000, 2};  // Range = 1000000
countingSort(arr, 3);  // Aloca array de 1M posições!

// ✅ CORRETO - Use Quick Sort para esse caso
```

#### Erro 2: Esquecer de zerar arrays de contagem
```c
// ❌ ERRADO
int count[10];  // Pode conter lixo!

// ✅ CORRETO
int count[10] = {0};  // Ou usar calloc()
```

#### Erro 3: Não processar Radix Sort de trás para frente
```c
// ❌ ERRADO - Processa da frente para trás
for (int i = 0; i < n; i++) {  
    output[count[digit] - 1] = arr[i];
    count[digit]--;
}

// ✅ CORRETO - Processa de trás para frente (mantém estabilidade)
for (int i = n - 1; i >= 0; i--) {
    output[count[digit] - 1] = arr[i];
    count[digit]--;
}
```

#### Erro 4: Usar Bucket Sort sem verificar distribuição
```c
// ❌ ERRADO - Assume distribuição uniforme sem verificar
float arr[] = {0.01, 0.02, 0.03, 0.99, 0.98, 0.97};  
// Má distribuição: metade perto de 0, metade perto de 1
bucketSort(arr, 6);  // Baldes do meio ficam vazios!

// ✅ CORRETO - Usar Quick Sort ou adaptar número de baldes
```

#### Erro 5: Não liberar memória alocada
```c
// ❌ ERRADO
int *count = (int *)calloc(max + 1, sizeof(int));
countingSort(arr, n);
// Esqueceu de fazer free(count)! Memory leak!

// ✅ CORRETO
int *count = (int *)calloc(max + 1, sizeof(int));
countingSort(arr, n);
free(count);  // Sempre liberar memória
```

### 🎯 Checklist de Validação

Antes de usar um algoritmo sem comparação, verifique:

**Para Counting Sort:**
- [ ] Todos os valores são inteiros não-negativos?
- [ ] O range (max - min) é pequeno comparado com n?
- [ ] Tenho memória O(k) disponível?
- [ ] Preciso de estabilidade?

**Para Radix Sort:**
- [ ] Os números têm número fixo de dígitos?
- [ ] O número de dígitos (d) é pequeno?
- [ ] Posso usar uma base apropriada (binária, decimal)?
- [ ] Tenho memória O(n) disponível?

**Para Bucket Sort:**
- [ ] Conheço a distribuição dos dados?
- [ ] Os dados estão uniformemente distribuídos?
- [ ] Estou trabalhando com float [0, 1) ou posso normalizar?
- [ ] Tenho memória para criar múltiplos baldes?

### 🔬 Experimentos Sugeridos

1. **Comparar performance real**:
   - Implemente e compare todos os 3 algoritmos
   - Use arrays de diferentes tamanhos (10, 100, 1000, 10000)
   - Meça tempo e uso de memória

2. **Testar casos extremos**:
   - Array com todos elementos iguais
   - Array já ordenado
   - Array em ordem reversa
   - Array com um único elemento diferente

3. **Visualizar o processo**:
   - Adicione prints para ver cada passo
   - Crie versões que mostram o estado intermediário
   - Compare com animações online

4. **Otimizações**:
   - Tente otimizar Counting Sort para números negativos
   - Implemente Radix Sort com base 256 (bytes)
   - Experimente diferentes números de baldes no Bucket Sort

---

**Nota Final**: Estes algoritmos são ferramentas especializadas. Use-os quando as condições forem apropriadas, mas não hesite em usar Quick Sort ou Merge Sort para casos gerais! A escolha do algoritmo certo pode fazer a diferença entre O(n) e O(n²) - sempre analise seus dados primeiro! 🚀
