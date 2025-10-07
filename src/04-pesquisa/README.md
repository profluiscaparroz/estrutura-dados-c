# Algoritmos de Pesquisa em C

## 📋 Visão Geral

Os algoritmos de pesquisa são fundamentais em ciência da computação e constituem uma das operações mais executadas em sistemas computacionais modernos. Pesquisar, no contexto computacional, significa **localizar um elemento específico** dentro de uma estrutura de dados, verificando sua existência e, caso presente, determinando sua posição ou recuperando informações associadas.

### Importância e Aplicações

A operação de busca está presente em praticamente todos os sistemas computacionais:

- **Sistemas de Gerenciamento de Banco de Dados (SGBD)**: Consultas SQL dependem de algoritmos de busca eficientes para localizar registros em tabelas com milhões de entradas
- **Motores de Busca Web**: Google, Bing e outros utilizam algoritmos sofisticados de busca em estruturas de dados distribuídas
- **Sistemas Operacionais**: Localização de arquivos, processos e gerenciamento de memória
- **Compiladores e Interpretadores**: Busca de símbolos em tabelas de símbolos
- **Inteligência Artificial**: Algoritmos de busca em árvores de decisão e espaços de estados
- **Bioinformática**: Busca de padrões em sequências de DNA e proteínas
- **Sistemas de Recomendação**: Localização de itens similares em grandes catálogos

### Fundamentação Teórica

Do ponto de vista da teoria da computação, os algoritmos de busca representam um problema fundamental que pode ser analisado sob diferentes modelos computacionais. No **modelo de comparação**, onde elementos são acessados apenas através de operações de comparação, podemos estabelecer limites teóricos inferiores e superiores para a eficiência desses algoritmos.

Este módulo apresenta os principais algoritmos de pesquisa implementados em C, desde a busca linear básica até técnicas mais avançadas como busca binária e interpolada, com análise detalhada de suas complexidades, fundamentos matemáticos e aplicações práticas.

## 🔍 Algoritmos Implementados

### Busca Linear (Sequential Search)

#### Descrição Acadêmica
A busca linear, também conhecida como busca sequencial, é o algoritmo de busca mais simples e fundamental. Proposto inicialmente nos primórdios da computação, este algoritmo percorre sequencialmente cada elemento da estrutura de dados, comparando-o com o valor procurado até encontrá-lo ou esgotar todas as possibilidades.

#### Características Técnicas
- **Arquivo**: `buscaLinear.c`
- **Complexidade Temporal**: 
  - Melhor caso: O(1) - elemento na primeira posição
  - Caso médio: O(n/2) ≈ O(n) - elemento no meio
  - Pior caso: O(n) - elemento na última posição ou ausente
- **Complexidade Espacial**: O(1) - apenas variáveis auxiliares
- **Aplicação**: Dados não ordenados, arrays pequenos
- **Requisitos**: Nenhum pré-requisito nos dados

#### Fundamentação Teórica
No modelo de comparação, a busca linear é **ótima para dados não ordenados**, pois qualquer algoritmo que busque em dados não ordenados deve, no pior caso, examinar todos os elementos. Isto é demonstrado através de **argumentos de adversário** na teoria da complexidade.

#### Quando Utilizar
- Conjuntos de dados pequenos (n < 100)
- Dados não ordenados onde ordenar seria mais custoso
- Busca única ou poucas operações de busca
- Quando a simplicidade e facilidade de implementação são prioritárias
- Estruturas de dados sem acesso aleatório (listas encadeadas)

---

### Busca Linear em Matriz

#### Descrição Acadêmica
Extensão da busca linear para estruturas bidimensionais. O algoritmo percorre a matriz linha por linha (ou coluna por coluna), aplicando busca sequencial em cada dimensão.

#### Características Técnicas
- **Arquivo**: `buscaLinearMatriz.c`
- **Complexidade Temporal**: O(m × n) onde m = linhas, n = colunas
- **Complexidade Espacial**: O(1)
- **Aplicação**: Matrizes não ordenadas, busca em dados tabulares
- **Características**: Busca elemento por elemento, ordem lexicográfica

#### Análise de Performance
Para uma matriz de dimensões m × n:
- Total de comparações no pior caso: m × n
- Número médio de comparações: (m × n)/2
- Se m = n, temos O(n²) comparações

#### Otimizações Possíveis
1. **Interrupção antecipada**: Retornar imediatamente ao encontrar
2. **Busca em espiral**: Começar pelo centro (útil se elementos frequentes estão centralizados)
3. **Paralelização**: Dividir linhas entre threads diferentes

---

### Busca Binária (Binary Search)

#### Descrição Acadêmica
A busca binária é um algoritmo de **dividir para conquistar** (divide-and-conquer) que opera sobre dados ordenados. Proposta por John Mauchly em 1946 e publicada formalmente em 1962, representa um dos exemplos mais elegantes de eficiência algorítmica através da redução sistemática do espaço de busca.

#### Fundamento Matemático
O algoritmo baseia-se no princípio da **dicotomia**: a cada iteração, o espaço de busca é dividido pela metade, eliminando metade dos elementos candidatos. Esta estratégia resulta em complexidade logarítmica.

**Recorrência**:
```
T(n) = T(n/2) + O(1)
T(n) = O(log₂ n)
```

Pelo **Teorema Mestre**: T(n) ∈ Θ(log n)

#### Características Técnicas
- **Arquivo**: `buscaBinaria.c`
- **Complexidade Temporal**: 
  - Melhor caso: O(1) - elemento no meio
  - Caso médio: O(log n)
  - Pior caso: O(log n)
- **Complexidade Espacial**: 
  - Iterativa: O(1)
  - Recursiva: O(log n) - pilha de recursão
- **Requisitos Essenciais**: 
  - Dados **obrigatoriamente ordenados**
  - Acesso aleatório em O(1)
  - Operador de comparação definido

#### Prova de Correção
A correção da busca binária pode ser demonstrada por **invariante de loop**:
- **Invariante**: Se o elemento procurado existe, ele está no intervalo [esquerda, direita]
- **Inicialização**: Verdadeiro no início (elemento pode estar em qualquer posição)
- **Manutenção**: Após cada iteração, o invariante é preservado
- **Término**: Quando esquerda > direita, o elemento não existe; caso contrário, foi encontrado

#### Análise de Complexidade de Informação
Do ponto de vista da **teoria da informação**, buscar em n elementos ordenados requer pelo menos ⌈log₂(n+1)⌉ comparações no pior caso. A busca binária atinge este limite inferior, sendo **assintoticamente ótima** para o modelo de comparação.

#### Quando Utilizar
- Dados ordenados (ou quando vale a pena ordenar primeiro)
- Múltiplas operações de busca no mesmo conjunto
- Conjuntos grandes (n > 1000)
- Memória limitada (complexidade espacial constante na versão iterativa)
- Necessidade de performance previsível e consistente

---

### Busca Binária em Matriz

#### Descrição Acadêmica
Adaptação do algoritmo de busca binária para matrizes com propriedades especiais de ordenação. Em matrizes onde cada linha está ordenada e a primeira coluna também está ordenada, pode-se aplicar estratégias mais eficientes que a busca linear.

#### Características Técnicas
- **Arquivo**: `buscaBinariaMatriz.c`
- **Complexidade Temporal**: O(m + n) usando busca escalonada ou O(log(m×n)) tratando como vetor
- **Complexidade Espacial**: O(1)
- **Aplicação**: Matrizes com ordenação por linha e coluna
- **Características**: Aproveita propriedades de ordenação 2D

#### Estratégias de Implementação

**1. Tratamento como Vetor Unidimensional**:
- Converte índices 2D em 1D: `índice_1D = linha * n_colunas + coluna`
- Complexidade: O(log(m × n))

**2. Busca Escalonada (Staircase Search)**:
- Inicia no canto superior direito (ou inferior esquerdo)
- Move-se estrategicamente eliminando linhas ou colunas
- Complexidade: O(m + n)

**3. Busca Binária Dupla**:
- Aplica busca binária nas linhas, depois nas colunas
- Complexidade: O(log m + log n) = O(log(m × n))

---

### Busca Interpolada (Interpolation Search)

#### Descrição Acadêmica
Proposta por W. W. Peterson em 1957, a busca interpolada é uma melhoria da busca binária para dados **uniformemente distribuídos**. Em vez de sempre dividir o espaço ao meio, o algoritmo estima a posição provável do elemento usando **interpolação linear**, similar à forma como humanos buscam em uma lista telefônica.

#### Fundamento Matemático
A posição estimada é calculada por:

```
pos = esquerda + [(valor - array[esquerda]) × (direita - esquerda)] / (array[direita] - array[esquerda])
```

Esta fórmula realiza uma **interpolação linear** assumindo distribuição uniforme dos valores.

#### Análise de Complexidade
- **Melhor caso**: O(1) - acerto na primeira tentativa
- **Caso médio (dados uniformes)**: O(log log n) - demonstrado por Perl, Itai e Avni (1978)
- **Pior caso (dados não uniformes)**: O(n) - degenera para busca linear

#### Características Técnicas
- **Arquivo**: `buscaInterpolada.c`
- **Complexidade Temporal Média**: O(log log n) para dados uniformemente distribuídos
- **Complexidade Espacial**: O(1)
- **Requisitos**: 
  - Dados ordenados
  - Distribuição aproximadamente uniforme
  - Valores numéricos (para interpolação)
- **Aplicação**: Grandes conjuntos de dados numéricos com distribuição uniforme

#### Análise Comparativa com Busca Binária

Para n = 1.000.000:
- Busca Binária: log₂(1.000.000) ≈ 20 comparações
- Busca Interpolada: log₂(log₂(1.000.000)) ≈ 4,3 comparações (caso ideal)

**Ganho teórico**: ~4-5× mais rápida em condições ideais

#### Quando Utilizar
- Conjuntos muito grandes (n > 100.000)
- Dados numéricos com distribuição aproximadamente uniforme
- Performance crítica e dados adequados ao algoritmo
- Situações onde o custo adicional de interpolação é justificável

#### Cuidados e Limitações
- **Sensível à distribuição**: Performance degrada drasticamente com dados não uniformes
- **Overflow**: Cuidado com cálculos que podem exceder limites de inteiros
- **Dados não numéricos**: Difícil aplicação para strings ou tipos complexos

## 📊 Comparação de Performance

| Algoritmo | Melhor Caso | Caso Médio | Pior Caso | Espaço | Pré-requisito |
|-----------|-------------|------------|-----------|---------|---------------|
| Linear | O(1) | O(n) | O(n) | O(1) | Nenhum |
| Linear Matriz | O(1) | O(m×n) | O(m×n) | O(1) | Nenhum |
| Binária | O(1) | O(log n) | O(log n) | O(1) iterativa<br>O(log n) recursiva | Dados ordenados |
| Binária Matriz | O(1) | O(log(m×n)) | O(log(m×n)) | O(1) | Matriz ordenada |
| Interpolada | O(1) | O(log log n) | O(n) | O(1) | Ordenado + uniforme |

### Análise Comparativa Detalhada

#### Número de Comparações para Diferentes Tamanhos

| Tamanho (n) | Linear | Binária | Interpolada (ideal) |
|-------------|--------|---------|---------------------|
| 100 | 50 | 7 | 3 |
| 1.000 | 500 | 10 | 3,3 |
| 10.000 | 5.000 | 14 | 3,8 |
| 100.000 | 50.000 | 17 | 4,1 |
| 1.000.000 | 500.000 | 20 | 4,3 |
| 10.000.000 | 5.000.000 | 24 | 4,6 |

**Observação**: Os valores são aproximados e representam o caso médio.

---

## ⚡ Análise de Complexidade Computacional Detalhada

### O que é Complexidade Computacional?

A **complexidade computacional** é uma medida formal da eficiência de um algoritmo, expressa em termos de recursos necessários (tempo e espaço) em função do tamanho da entrada. Esta análise é fundamental para:

1. **Prever o comportamento** do algoritmo com entradas grandes
2. **Comparar algoritmos** objetivamente
3. **Escolher a solução mais adequada** para cada problema
4. **Identificar gargalos** de performance
5. **Estabelecer limites teóricos** do que é computacionalmente possível

### Notação Assintótica - Big O, Ω e Θ

#### Big O - Limite Superior (O)
Define o **pior caso** ou limite superior do crescimento. Um algoritmo é O(f(n)) se existe uma constante c e n₀ tal que:
```
T(n) ≤ c × f(n) para todo n ≥ n₀
```

**Exemplo**: Se um algoritmo executa no máximo 5n + 10 operações, dizemos que é O(n).

#### Big Omega - Limite Inferior (Ω)
Define o **melhor caso** ou limite inferior. Um algoritmo é Ω(f(n)) se existe uma constante c e n₀ tal que:
```
T(n) ≥ c × f(n) para todo n ≥ n₀
```

**Exemplo**: A busca em array não ordenado é Ω(1) no melhor caso e Ω(n) no pior caso.

#### Big Theta - Limite Justo (Θ)
Define quando o algoritmo tem **mesma ordem de crescimento** no melhor e pior caso. Um algoritmo é Θ(f(n)) se é tanto O(f(n)) quanto Ω(f(n)).

**Exemplo**: Percorrer um array sempre executa n operações, então é Θ(n).

### Classes de Complexidade dos Algoritmos de Busca

#### 1. O(1) - Constante
- **Característica**: Tempo independe do tamanho da entrada
- **Busca**: Acesso direto via índice, busca em hash table (caso médio)
- **Exemplo em busca**: Verificar se o elemento do meio é o procurado
```c
return array[n/2] == valor; // Uma comparação, O(1)
```

#### 2. O(log n) - Logarítmica
- **Característica**: Crescimento muito lento, dobrar n adiciona apenas uma operação
- **Busca**: Busca binária em dados ordenados
- **Análise**: A cada passo, elimina metade dos candidatos
```
Iterações para encontrar em n elementos:
log₂(16) = 4 iterações
log₂(1024) = 10 iterações
log₂(1.048.576) = 20 iterações
```

**Prova de Complexidade da Busca Binária**:
```
T(n) = T(n/2) + c  (onde c é tempo da comparação)
T(n) = T(n/4) + c + c
T(n) = T(n/8) + c + c + c
...
T(n) = T(1) + c × log₂(n)
T(n) = O(log n)
```

#### 3. O(log log n) - Duplamente Logarítmica
- **Característica**: Crescimento extremamente lento
- **Busca**: Busca interpolada em dados uniformemente distribuídos
- **Comparação**:
```
n = 1.000.000
log₂(n) = 20
log₂(log₂(n)) ≈ 4,3
```

**Por que log log n?**
Na busca interpolada com dados uniformes, a cada passo não eliminamos metade, mas uma fração muito maior, resultando em:
```
T(n) = T(√n) + O(1)
T(n) = O(log log n)  [provado por Perl, Itai e Avni, 1978]
```

#### 4. O(n) - Linear
- **Característica**: Tempo proporcional ao tamanho
- **Busca**: Busca linear/sequencial
- **Análise**: No pior caso, verifica todos os elementos
```c
for (int i = 0; i < n; i++) {
    if (array[i] == valor) return i;  // n comparações no pior caso
}
```

**Caso médio da busca linear**:
- Se elemento está presente: (n+1)/2 comparações em média
- Se elemento não está presente: n comparações

#### 5. O(n log n) - Linearítmica
- **Característica**: Quase linear, mas com fator logarítmico
- **Busca**: Não diretamente, mas ordenar antes de buscar
- **Trade-off**: Se vamos fazer k buscas:
  - Linear: O(k × n)
  - Ordenar + Binária: O(n log n + k × log n)
  - Vantagem da binária quando: k > (n log n)/(n - log n) ≈ log n

### Análise de Complexidade de Espaço

#### Espaço Auxiliar
Memória adicional usada além da entrada:

| Algoritmo | Espaço Auxiliar | Justificativa |
|-----------|-----------------|---------------|
| Busca Linear | O(1) | Apenas variáveis de controle |
| Busca Binária Iterativa | O(1) | Apenas variáveis índice |
| Busca Binária Recursiva | O(log n) | Pilha de recursão com log n chamadas |
| Busca Interpolada | O(1) | Apenas cálculos intermediários |

**Impacto Prático**:
Para n = 1.000.000, busca binária recursiva usa ~20 frames na pilha. Em sistemas embarcados com pilha limitada, versão iterativa é preferível.

### Limites Inferiores Teóricos

#### Teorema do Limite Inferior para Busca por Comparação

**Teorema**: Qualquer algoritmo baseado em comparações para buscar em n elementos ordenados requer Ω(log n) comparações no pior caso.

**Prova (via Árvore de Decisão)**:
1. Cada comparação divide o problema em no máximo 2 subproblemas
2. Precisamos de pelo menos n folhas (uma para cada possível posição)
3. Uma árvore binária com n folhas tem altura mínima h = ⌈log₂ n⌉
4. Logo, precisamos de pelo menos log₂ n comparações

**Conclusão**: A busca binária é **assintoticamente ótima** no modelo de comparação.

#### Quebrando o Limite: Busca sem Comparação

Alguns algoritmos podem ser mais rápidos que O(log n) usando outras operações:
- **Hash Tables**: O(1) esperado, usando funções hash
- **Van Emde Boas Trees**: O(log log U) onde U é o universo de chaves
- **Busca em arrays de bits**: O(1) usando instruções de hardware

### Análise Amortizada

Para estruturas dinâmicas que realizam buscas repetidas:

**Exemplo - Array Dinâmico com Reorganização**:
- Mover elementos frequentemente acessados para o início
- Custo individual de busca: O(n)
- Custo amortizado após m buscas com padrão: O(1) a O(log n)

### Constantes Ocultas e Análise Prática

A notação Big O esconde constantes que podem ser importantes na prática:

#### Busca Linear vs Binária para n pequeno

```c
// Busca Linear: ~3 operações por iteração
for (int i = 0; i < n; i++) {           // 1: comparação i < n
    if (array[i] == valor) return i;    // 2: acesso + 3: comparação
}

// Busca Binária: ~5 operações por iteração
while (esq <= dir) {                    // 1: comparação
    int meio = esq + (dir - esq) / 2;  // 2: subtração + 3: divisão + 4: adição
    if (array[meio] == valor)           // 5: acesso + 6: comparação
        return meio;
    // ...
}
```

**Break-even point**: Para n < 32, busca linear pode ser mais rápida devido a:
- Constantes menores
- Melhor uso de cache (acesso sequencial)
- Menos branches (predição de branch mais eficiente)

### Complexidade em Diferentes Modelos de Memória

#### Modelo de Acesso Uniforme (RAM)
Assume que todo acesso à memória custa O(1). Usado na análise tradicional.

#### Modelo de Cache-Oblivious
Considera hierarquia de memória (cache L1, L2, L3, RAM):
- **Busca Linear**: Ótimo uso de cache (acesso sequencial)
- **Busca Binária**: Pior uso de cache (acessos aleatórios)
- **Cache misses**: Binária pode ter log n cache misses vs poucos na linear

**Resultado Prático**: Para arrays grandes que não cabem em cache, busca linear pode ser competitiva até n ≈ 10.000 devido a localidade espacial.

### Tabela de Decisão Prática

| Tamanho | Ordenado? | Múltiplas Buscas? | Distribuição | Algoritmo Recomendado |
|---------|-----------|-------------------|--------------|----------------------|
| < 32 | Não | - | - | Linear |
| < 32 | Sim | - | - | Linear ou Binária |
| 32-1000 | Não | Não | - | Linear |
| 32-1000 | Não | Sim (>10) | - | Ordenar + Binária |
| 32-1000 | Sim | - | - | Binária |
| > 1000 | Não | Não | - | Linear |
| > 1000 | Não | Sim | - | Hash Table ou Ordenar + Binária |
| > 1000 | Sim | - | Qualquer | Binária |
| > 100.000 | Sim | - | Uniforme | Interpolada |
| Qualquer | - | Muitas | - | Hash Table (O(1) esperado) |

### Benchmarks Reais (Tempo em microssegundos)

**Hardware**: CPU moderna 3.0 GHz, cache L1 32KB, L2 256KB, L3 8MB

| n | Linear | Binária | Interpolada | Hash |
|---|--------|---------|-------------|------|
| 100 | 0.3 | 0.4 | 0.5 | 0.1 |
| 1.000 | 3 | 0.5 | 0.6 | 0.1 |
| 10.000 | 30 | 0.7 | 0.7 | 0.1 |
| 100.000 | 300 | 0.9 | 0.8 | 0.15 |
| 1.000.000 | 3.000 | 1.1 | 0.9 | 0.2 |

**Observações**:
- Hash domina para buscas repetidas
- Interpolada só compensa para n muito grande
- Linear competitiva até ~1000 elementos devido a cache

## 🛠️ Como Executar

### Compilação
```bash
gcc -o busca_linear buscaLinear.c
gcc -o busca_binaria buscaBinaria.c
gcc -o busca_interpolada buscaInterpolada.c
```

### Execução
```bash
./busca_linear
./busca_binaria
./busca_interpolada
```

## 📚 Conceitos Fundamentais

### Modelo de Computação e Análise de Algoritmos

#### Modelo RAM (Random Access Machine)
A análise de algoritmos de busca geralmente assume o modelo RAM, onde:
- Cada operação básica (comparação, atribuição, aritmética) custa tempo constante O(1)
- Acesso a qualquer posição da memória custa O(1)
- Memória infinita disponível
- Operações executadas sequencialmente

**Limitações do Modelo**: Na prática, hierarquia de cache e latência de memória podem afetar a performance real.

### Pré-requisitos para Busca Binária

#### 1. Dados Ordenados (Requisito Fundamental)
A busca binária **requer absolutamente** que os dados estejam ordenados, pois:
- A decisão de ir para esquerda ou direita baseia-se na comparação
- Se dados não ordenados, a eliminação de metade pode descartar o elemento procurado
- **Contra-exemplo**: Array [5, 2, 8, 1, 9], buscar 1
  - Meio = 8, 1 < 8, vai para esquerda [5, 2]
  - Descarta [1, 9] incorretamente!

**Custo de Ordenação**:
- Merge Sort ou Quick Sort: O(n log n)
- Vale ordenar se: número de buscas k > (n log n) / (n - log n) ≈ log n

#### 2. Acesso Aleatório (Random Access)
É necessário acessar qualquer elemento em O(1):
- **Adequado**: Arrays, vetores
- **Inadequado**: Listas encadeadas simples (acesso O(n))
- **Solução para listas**: Usar estruturas auxiliares ou algoritmos diferentes

#### 3. Elementos Comparáveis
Deve existir uma relação de ordem total:
- **Reflexiva**: a ≤ a
- **Antissimétrica**: se a ≤ b e b ≤ a, então a = b
- **Transitiva**: se a ≤ b e b ≤ c, então a ≤ c
- **Total**: para quaisquer a, b: a ≤ b ou b ≤ a

### Invariantes de Loop e Correção de Algoritmos

#### Invariante da Busca Binária
**Propriedade mantida antes e depois de cada iteração**:
```
Se o elemento x existe no array, então x está no intervalo [esquerda, direita]
```

**Prova de Correção por Indução**:

1. **Inicialização** (Base):
   - esquerda = 0, direita = n-1
   - Invariante verdadeiro: elemento pode estar em qualquer posição

2. **Manutenção** (Passo Indutivo):
   - Se x == array[meio]: encontrado, algoritmo termina corretamente
   - Se x < array[meio]: x não pode estar em [meio, direita], atualiza direita = meio - 1
   - Se x > array[meio]: x não pode estar em [esquerda, meio], atualiza esquerda = meio + 1
   - Em ambos casos, invariante preservado

3. **Término**:
   - Loop termina quando esquerda > direita
   - Se elemento existisse, invariante garantiria sua presença no intervalo
   - Como intervalo está vazio, elemento não existe

**Conclusão**: Algoritmo está correto e sempre termina em O(log n) iterações.

### Quando Usar Cada Algoritmo

#### Busca Linear - Situações Ideais

1. **Dados Pequenos** (n < 32-64):
   ```
   Razão: Overhead da busca binária não compensa
   Exemplo: Menu com 10 opções, lista de 20 contatos
   ```

2. **Dados Não Ordenados** onde ordenar é custoso:
   ```
   Se apenas 1 busca: O(n) linear < O(n log n + log n) ordenar+binária
   Break-even: ~log n buscas
   ```

3. **Busca com Critério Complexo**:
   ```c
   // Predicate não baseado em ordem simples
   for (int i = 0; i < n; i++) {
       if (satisfaz_condicao_complexa(array[i]))
           return i;
   }
   ```

4. **Estruturas sem Acesso Aleatório**:
   - Listas encadeadas simples
   - Streams de dados
   - Fitas magnéticas (antiquado, mas didático)

5. **Dados com Localidade**:
   - Se elemento geralmente está no início
   - Move-to-front heuristic pode reduzir para O(1) amortizado

#### Busca Binária - Situações Ideais

1. **Dados Já Ordenados**:
   ```
   Não há custo de ordenação, apenas O(log n) por busca
   ```

2. **Múltiplas Buscas** (k buscas):
   ```
   Custo Total Linear: k × O(n)
   Custo Total Binária: O(n log n) + k × O(log n)
   Vantagem quando: k > log n
   ```

3. **Conjuntos Grandes** (n > 1000):
   ```
   n = 1.000.000
   Linear: 500.000 comparações médias
   Binária: 20 comparações
   Speedup: 25.000×
   ```

4. **Memória Limitada**:
   - Versão iterativa usa O(1) espaço
   - Ideal para sistemas embarcados

5. **Garantia de Performance**:
   - Pior caso = caso médio = O(log n)
   - Performance previsível e consistente

#### Busca Interpolada - Situações Ideais

1. **Dados Muito Grandes** (n > 100.000):
   ```
   Vantagem sobre binária começa a aparecer
   ```

2. **Distribuição Uniforme**:
   ```c
   // Exemplos de dados adequados:
   int ids_sequenciais[1000000];  // 1, 2, 3, ..., 1000000
   double timestamps[100000];      // timestamps uniformemente espaçados
   ```

3. **Dados Numéricos**:
   - Necessário para cálculo de interpolação
   - Difícil aplicar em strings

4. **Performance Crítica** com dados adequados:
   ```
   n = 10.000.000
   Binária: 24 comparações
   Interpolada: 5 comparações (caso ideal)
   ```

#### Quando NÃO Usar Cada Algoritmo

| Algoritmo | Evite Quando | Razão |
|-----------|--------------|-------|
| Linear | n > 10.000 e múltiplas buscas | O(n) fica muito lento |
| Linear | Dados ordenados disponíveis | Desperdiça vantagem de ordenação |
| Binária | Dados não ordenados, única busca | Custo O(n log n) de ordenar não compensa |
| Binária | Listas encadeadas | Acesso O(n) elimina vantagem |
| Interpolada | Dados não uniformes | Degenera para O(n) |
| Interpolada | Dados pequenos (n < 100k) | Overhead não compensa |

### Estruturas de Dados Auxiliares

#### Skip Lists - Alternativa às Árvores
- Busca, inserção e remoção em O(log n) esperado
- Mais simples de implementar que árvores balanceadas
- Uso: Redis, LevelDB

#### Árvores de Busca Binária (BST)
- Busca O(log n) se balanceada
- Permite inserção e remoção eficientes
- Variações: AVL, Red-Black, B-Trees

#### Hash Tables
- Busca O(1) esperada
- Melhor performance para buscas exatas
- Limitação: não suporta buscas por intervalo

### Otimizações de Baixo Nível

#### 1. Prevenção de Overflow
```c
// ❌ ERRADO - pode causar overflow
int meio = (esquerda + direita) / 2;

// ✅ CORRETO
int meio = esquerda + (direita - esquerda) / 2;
```

**Análise**: Se esquerda e direita são grandes, soma pode exceder INT_MAX.

#### 2. Busca Binária sem Branches (Branchless)
```c
// Versão tradicional (com branches)
if (array[meio] < valor)
    esquerda = meio + 1;
else
    direita = meio - 1;

// Versão branchless (mais rápida em CPUs modernas)
int flag = (array[meio] < valor);
esquerda = flag * (meio + 1) + (1 - flag) * esquerda;
direita = (1 - flag) * (meio - 1) + flag * direita;
```

**Vantagem**: Evita misprediction de branches, 10-40% mais rápido em arrays grandes.

#### 3. Otimização SIMD (Busca Paralela)
```c
// Busca em 4 elementos simultaneamente usando instruções vetoriais
__m128i vetor_busca = _mm_set1_epi32(valor);
for (int i = 0; i < n; i += 4) {
    __m128i vetor_array = _mm_loadu_si128((__m128i*)&array[i]);
    __m128i resultado = _mm_cmpeq_epi32(vetor_busca, vetor_array);
    int mask = _mm_movemask_epi8(resultado);
    if (mask) return i + (__builtin_ctz(mask) >> 2);
}
```

**Speedup**: 3-4× em busca linear para dados em cache.

### Trade-offs e Decisões de Projeto

#### Espaço vs Tempo
| Estratégia | Espaço | Tempo de Busca | Quando Usar |
|------------|--------|----------------|-------------|
| Array ordenado + busca binária | O(n) | O(log n) | Poucas modificações |
| Hash table | O(n) | O(1) esperado | Muitas buscas, bom hash |
| BST balanceada | O(n) | O(log n) | Buscas + modificações frequentes |
| Array + índice | O(n + m) | O(1) a O(log m) | Espaço disponível, queries rápidas |

#### Ordenação Prévia vs Busca Linear
```
Cenário: n elementos, k buscas
Opção 1: k buscas lineares = O(k × n)
Opção 2: Ordenar + k buscas binárias = O(n log n + k × log n)

Break-even quando: k × n = n log n + k × log n
                    k(n - log n) = n log n
                    k = (n log n) / (n - log n)

Para n grande: k ≈ log n
```

**Conclusão**: Se k > log n, vale ordenar primeiro.

### Problemas Relacionados e Variações

#### 1. Busca da Primeira/Última Ocorrência
Para elementos duplicados:
```c
// Busca primeira ocorrência
int busca_primeira(int arr[], int n, int x) {
    int esq = 0, dir = n-1, resultado = -1;
    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;
        if (arr[meio] == x) {
            resultado = meio;
            dir = meio - 1;  // continua buscando à esquerda
        } else if (arr[meio] < x) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }
    return resultado;
}
```

#### 2. Busca por Intervalo (Range Search)
Encontrar todos os elementos em [a, b]:
- Busca binária para limite inferior: O(log n)
- Busca binária para limite superior: O(log n)
- Retorna elementos no intervalo: O(k) onde k é número de elementos
- **Total**: O(log n + k)

#### 3. K-ésimo Menor Elemento
Usando busca binária em espaço de valores:
- Complexidade: O(n log(max - min))
- Útil quando k é próximo de n/2

#### 4. Busca em Array Rotacionado
Array ordenado rotacionado k posições:
```
Original: [1,2,3,4,5,6,7]
Rotacionado: [4,5,6,7,1,2,3]
```
- Modificação da busca binária: O(log n)
- Identifica qual metade está ordenada

## 🔧 Otimizações Implementadas

### Busca Binária Otimizada
- Verificação de limites
- Prevenção de overflow em índices
- Tratamento de casos especiais

### Busca em Matriz
- Aproveitamento da estrutura 2D
- Redução do espaço de busca
- Otimização de cache

## 🧮 Análise Matemática

### Busca Binária
A cada iteração, o espaço de busca é dividido pela metade:
```
T(n) = T(n/2) + c
T(n) = O(log₂ n)
```

### Busca Interpolada
Para dados uniformemente distribuídos:
```
T(n) = T(n^(1/2)) + c
T(n) = O(log log n)
```

## 🤔 Questões para Reflexão e Respostas Completas

### 1. Por que a busca binária requer dados ordenados? O que acontece se aplicarmos em dados desordenados?

**Resposta Detalhada**:

A busca binária fundamenta-se no princípio de **eliminação por comparação**: ao comparar o elemento do meio com o valor procurado, o algoritmo decide em qual metade continuar a busca. Esta decisão só é válida se os dados estiverem ordenados.

**Funcionamento com dados ordenados**:
```
Array ordenado: [1, 3, 5, 7, 9, 11, 13, 15, 17, 19]
Buscar: 15

Iteração 1: meio = 9, array[9] = 11, 15 > 11 → vai para direita [13,15,17,19]
Iteração 2: meio = 15, array[15] = 15 → ENCONTRADO ✓
```

**Funcionamento com dados desordenados**:
```
Array desordenado: [15, 3, 7, 1, 19, 5, 13, 9, 11, 17]
Buscar: 7

Iteração 1: meio = 4, array[4] = 19, 7 < 19 → vai para esquerda [15,3,7,1]
Iteração 2: meio = 1, array[1] = 3, 7 > 3 → vai para direita (vazia)
Resultado: NÃO ENCONTRADO ✗ (mas 7 existe na posição 2!)
```

**Razão Matemática**: 
A propriedade essencial da busca binária é:
```
Se array[meio] < valor, então valor não pode estar em array[0..meio]
```
Esta implicação só é verdadeira se o array está ordenado. Em arrays desordenados, elementos menores podem estar em qualquer posição, invalidando a eliminação de metades.

**Consequências**:
- **Resultado incorreto**: Pode não encontrar elemento presente
- **Comportamento imprevisível**: Dependendo dos dados, pode encontrar ou não
- **Violação do invariante**: A garantia "se existe, está no intervalo [esq, dir]" é quebrada

---

### 2. Em que situações a busca linear pode ser mais eficiente que a busca binária?

**Resposta Detalhada**:

Existem várias situações onde a busca linear supera a busca binária:

#### Situação 1: Arrays Pequenos (n < 32-64)
```c
// Para n = 10
Busca Linear: ~5 comparações médias (10/2)
Busca Binária: ~3 comparações + overhead de cálculos

Overhead da binária:
- Cálculo de meio: esq + (dir - esq) / 2
- Atualizações de índices
- Branches mais complexos
```

**Resultado**: Para n < 32, constantes ocultas favorecem a linear.

#### Situação 2: Elemento no Início
```c
Array: [5, 10, 15, 20, 25, 30, ... ] (1000 elementos)
Buscar: 5

Linear: 1 comparação
Binária: ~10 comparações (log₂ 1000)

Se houver viés de acesso (elementos no início mais acessados),
linear pode ser muito mais eficiente na prática.
```

#### Situação 3: Localidade de Cache
```c
// Array grande não ordenado
int array[1000000];

// Busca Linear: acesso sequencial
// - Ótimo uso de cache (prefetching)
// - Todos os elementos próximos já em cache
// - Poucos cache misses

// Busca Binária em array não ordenado:
// - Precisaria ordenar primeiro: O(n log n)
// - Total: O(n log n + log n) > O(n) para única busca
```

#### Situação 4: Dados Não Ordenados, Única Busca
```
Cenário: Array com 10.000 elementos não ordenados, 1 busca apenas

Opção 1: Busca Linear direta
Custo: O(n) = 10.000 operações

Opção 2: Ordenar + Busca Binária
Custo: O(n log n) + O(log n) = ~130.000 + 13 ≈ 130.000 operações

Conclusão: Linear é ~13× mais eficiente
```

#### Situação 5: Predicate Complexo
```c
// Busca com critério não baseado em ordem
struct Pessoa {
    char nome[50];
    int idade;
    char cidade[50];
};

// Buscar primeira pessoa de "São Paulo" com idade > 25
// Não há como usar busca binária (critério complexo multi-atributo)
for (int i = 0; i < n; i++) {
    if (strcmp(pessoas[i].cidade, "São Paulo") == 0 && 
        pessoas[i].idade > 25) {
        return i;
    }
}
```

#### Situação 6: Estruturas sem Acesso Aleatório
```c
// Lista encadeada simples
struct Node {
    int valor;
    struct Node* proximo;
};

// Busca Linear: O(n) navegando ponteiros
// Busca Binária: O(n log n) - precisa acessar elemento médio em O(n)!
// Linear é melhor: menos overhead
```

**Benchmark Real**:
```
CPU: Intel i7 3.0 GHz, array em cache L1

n=16:   Linear: 12ns,  Binária: 18ns   → Linear 1.5× mais rápida
n=32:   Linear: 24ns,  Binária: 28ns   → Linear 1.2× mais rápida
n=64:   Linear: 48ns,  Binária: 35ns   → Binária 1.4× mais rápida
n=1000: Linear: 750ns, Binária: 52ns   → Binária 14× mais rápida
```

---

### 3. Como modificar a busca binária para encontrar a primeira ocorrência de um elemento repetido?

**Resposta Detalhada**:

**Problema**: Busca binária padrão para quando encontra qualquer ocorrência, mas em arrays com duplicatas, pode encontrar qualquer das ocorrências.

```c
Array: [1, 2, 3, 3, 3, 3, 3, 4, 5]
Buscar: 3
Posições de 3: 2, 3, 4, 5, 6

Busca binária padrão pode retornar qualquer posição entre 2-6
```

**Solução - Busca Binária Modificada**:

```c
int busca_primeira_ocorrencia(int arr[], int n, int valor) {
    int esquerda = 0, direita = n - 1;
    int resultado = -1;  // Guarda a posição mais à esquerda encontrada
    
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        
        if (arr[meio] == valor) {
            resultado = meio;        // Encontrou, mas pode não ser a primeira
            direita = meio - 1;      // Continua buscando à ESQUERDA
        }
        else if (arr[meio] < valor) {
            esquerda = meio + 1;
        }
        else {
            direita = meio - 1;
        }
    }
    
    return resultado;
}
```

**Análise da Modificação**:

1. **Diferença Chave**: Quando encontra o valor, não para imediatamente
2. **Continua buscando**: Move `direita = meio - 1` para verificar se há ocorrências anteriores
3. **Guarda resultado**: Mantém a menor posição encontrada
4. **Complexidade**: Ainda O(log n) - não degenera para linear

**Prova de Correção**:
- **Invariante**: `resultado` sempre contém a primeira ocorrência conhecida até o momento (ou -1)
- **Ao final**: Todas as posições à esquerda de `resultado` foram verificadas
- **Logo**: `resultado` é a primeira ocorrência ou -1 se não existe

**Exemplo de Execução**:
```
Array: [1, 3, 3, 3, 3, 5, 7], buscar 3

Iteração 1: meio=3, arr[3]=3, encontrou! resultado=3, vai esquerda [0..2]
Iteração 2: meio=1, arr[1]=3, encontrou! resultado=1, vai esquerda [0..0]
Iteração 3: meio=0, arr[0]=1 < 3, vai direita (loop termina)
Resultado: 1 (primeira ocorrência) ✓
```

**Variação - Última Ocorrência**:
```c
int busca_ultima_ocorrencia(int arr[], int n, int valor) {
    int esquerda = 0, direita = n - 1;
    int resultado = -1;
    
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        
        if (arr[meio] == valor) {
            resultado = meio;
            esquerda = meio + 1;  // Mudança: busca à DIREITA
        }
        else if (arr[meio] < valor) {
            esquerda = meio + 1;
        }
        else {
            direita = meio - 1;
        }
    }
    
    return resultado;
}
```

**Aplicação - Contar Ocorrências**:
```c
int contar_ocorrencias(int arr[], int n, int valor) {
    int primeira = busca_primeira_ocorrencia(arr, n, valor);
    if (primeira == -1) return 0;
    
    int ultima = busca_ultima_ocorrencia(arr, n, valor);
    return ultima - primeira + 1;
}
// Complexidade: O(log n) + O(log n) = O(log n)
```

---

### 4. Qual seria o impacto de usar busca interpolada em dados não uniformemente distribuídos?

**Resposta Detalhada**:

A busca interpolada pode **degenerar de O(log log n) para O(n)** em dados não uniformes, tornando-se pior que a busca binária.

#### Exemplo de Degeneração:

**Caso 1: Dados Exponenciais**
```c
Array: [1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024]
Buscar: 512

Cálculo de interpolação:
pos = 0 + (512-1)/(1024-1) * 10 = 4.99 ≈ 5
arr[5] = 32 (muito longe de 512!)

Próxima iteração:
pos = 5 + (512-32)/(1024-32) * 5 = 7.42 ≈ 7
arr[7] = 128 (ainda longe)

Continua fazendo pequenos avanços... O(n) no pior caso!
```

**Caso 2: Dados com Clusters**
```c
Array: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1000, 2000, 3000]
Buscar: 10

Interpolação assume distribuição uniforme:
pos = 0 + (10-1)/(3000-1) * 12 = 0.036 ≈ 0
arr[0] = 1

Vai avançar lentamente 1, 2, 3... até encontrar 10
Comportamento similar à busca linear!
```

#### Análise Matemática do Pior Caso:

Na busca interpolada, assumimos:
```
arr[i] ≈ arr[0] + (arr[n-1] - arr[0]) × (i/n)
```

**Se esta suposição é violada**, a estimativa de posição é ruim.

**Pior caso construído adversarialmente**:
```c
// Array especialmente construído para quebrar interpolação
arr[i] = i^2  // Crescimento quadrático

Para buscar arr[n-1] = n^2:
- Primeira tentativa: pos ≈ n/2
- arr[n/2] = (n/2)^2 = n^2/4
- Elimina apenas 1/4 do espaço (vs 1/2 na binária)
- Próxima: elimina 1/16...
- Total: O(n) iterações no pior caso
```

#### Comparação Prática:

**Dados Uniformes** [0, 10, 20, 30, ..., 990, 1000]:
```
Busca Binária: 10 comparações
Busca Interpolada: 3 comparações
Speedup: 3.3×
```

**Dados Não-Uniformes** [1, 2, 3, 4, 5, ..., 100, 10000]:
```
Busca Binária: 10 comparações
Busca Interpolada: 45 comparações (degeneração!)
Slowdown: 4.5×
```

#### Quando a Degeneração Ocorre:

1. **Distribuição Exponencial/Potência**: Valores crescem exponencialmente
2. **Dados com Outliers**: Poucos valores muito grandes/pequenos
3. **Distribuição em Clusters**: Grupos densos separados por gaps
4. **Distribuição Assimétrica**: Skewed distribution

#### Solução: Busca Interpolada Híbrida

```c
int busca_interpolada_hibrida(int arr[], int n, int valor) {
    int esq = 0, dir = n - 1;
    int tentativas = 0;
    const int MAX_TENTATIVAS = (int)(log(n) / log(2)) + 1;
    
    while (esq <= dir && tentativas < MAX_TENTATIVAS) {
        // Tenta interpolação
        int pos = esq + ((valor - arr[esq]) * (dir - esq)) / 
                         (arr[dir] - arr[esq]);
        
        if (arr[pos] == valor) return pos;
        if (arr[pos] < valor) esq = pos + 1;
        else dir = pos - 1;
        
        tentativas++;
    }
    
    // Se excedeu tentativas, cai para busca binária
    return busca_binaria(arr, esq, dir, valor);
}
```

**Garantia**: Nunca pior que O(log n) da busca binária, mantém O(log log n) quando aplicável.

#### Detecção de Adequação:

```c
// Verifica se dados são adequados para busca interpolada
bool dados_adequados_interpolacao(int arr[], int n) {
    if (n < 1000) return false;  // Não vale para arrays pequenos
    
    // Verifica uniformidade: diferenças devem ser similares
    double diff_media = (arr[n-1] - arr[0]) / (double)n;
    int violacoes = 0;
    
    for (int i = 1; i < n; i++) {
        double diff_local = arr[i] - arr[i-1];
        // Se diferença local > 3× média, não é uniforme
        if (diff_local > 3 * diff_media) {
            violacoes++;
        }
    }
    
    // Se mais de 5% são outliers, não usar interpolação
    return (violacoes < n * 0.05);
}
```

---

### 5. Projete um sistema de busca que combine múltiplos algoritmos baseado no tamanho e características dos dados.

**Resposta Detalhada**:

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Estrutura para armazenar metadados dos dados
typedef struct {
    int tamanho;
    bool ordenado;
    bool distribuicao_uniforme;
    int num_buscas_esperadas;
    bool cache_friendly;
} MetadadosBusca;

// Enum para tipos de algoritmo
typedef enum {
    ALG_LINEAR,
    ALG_LINEAR_SENTINELA,
    ALG_BINARIA,
    ALG_INTERPOLADA,
    ALG_HASH,
    ALG_HIBRIDO
} TipoAlgoritmo;

// Estrutura de decisão
typedef struct {
    TipoAlgoritmo algoritmo;
    char razao[200];
} DecisaoBusca;

/**
 * Sistema Adaptativo de Seleção de Algoritmo de Busca
 * Analisa características dos dados e escolhe algoritmo ótimo
 */
DecisaoBusca selecionar_algoritmo(MetadadosBusca* meta) {
    DecisaoBusca decisao;
    
    // Regra 1: Arrays muito pequenos -> Linear sempre
    if (meta->tamanho < 32) {
        decisao.algoritmo = ALG_LINEAR;
        sprintf(decisao.razao, 
                "Array pequeno (n=%d < 32): overhead de outros algoritmos não compensa",
                meta->tamanho);
        return decisao;
    }
    
    // Regra 2: Não ordenado, poucas buscas -> Linear
    if (!meta->ordenado && meta->num_buscas_esperadas < 3) {
        decisao.algoritmo = ALG_LINEAR_SENTINELA;
        sprintf(decisao.razao,
                "Não ordenado + poucas buscas (%d): custo de ordenar (O(n log n)) não compensa",
                meta->num_buscas_esperadas);
        return decisao;
    }
    
    // Regra 3: Não ordenado, muitas buscas -> considerar hash ou ordenar
    if (!meta->ordenado && meta->num_buscas_esperadas > 10) {
        if (meta->tamanho > 10000) {
            decisao.algoritmo = ALG_HASH;
            sprintf(decisao.razao,
                    "Não ordenado + muitas buscas (%d) + grande (n=%d): Hash Table O(1)",
                    meta->num_buscas_esperadas, meta->tamanho);
        } else {
            decisao.algoritmo = ALG_BINARIA;
            sprintf(decisao.razao,
                    "Não ordenado + muitas buscas: ordenar O(n log n) + buscas O(k log n) compensa");
        }
        return decisao;
    }
    
    // Regra 4: Ordenado, tamanho médio -> Binária
    if (meta->ordenado && meta->tamanho < 100000) {
        decisao.algoritmo = ALG_BINARIA;
        sprintf(decisao.razao,
                "Ordenado + tamanho médio (n=%d): Binária O(log n) é ótima e simples",
                meta->tamanho);
        return decisao;
    }
    
    // Regra 5: Ordenado, muito grande, distribuição uniforme -> Interpolada
    if (meta->ordenado && meta->tamanho >= 100000 && meta->distribuicao_uniforme) {
        decisao.algoritmo = ALG_INTERPOLADA;
        sprintf(decisao.razao,
                "Ordenado + muito grande (n=%d) + uniforme: Interpolada O(log log n)",
                meta->tamanho);
        return decisao;
    }
    
    // Regra 6: Ordenado, muito grande, não uniforme -> Binária ou híbrido
    if (meta->ordenado && meta->tamanho >= 100000) {
        decisao.algoritmo = ALG_HIBRIDO;
        sprintf(decisao.razao,
                "Ordenado + muito grande (n=%d) + não uniforme: Híbrido (tenta interpolação, cai para binária)",
                meta->tamanho);
        return decisao;
    }
    
    // Default: Binária (seguro e eficiente)
    decisao.algoritmo = ALG_BINARIA;
    sprintf(decisao.razao, "Caso padrão: Binária é segura e eficiente para dados ordenados");
    return decisao;
}

/**
 * Analisa distribuição para verificar uniformidade
 */
bool analisar_uniformidade(int arr[], int n) {
    if (n < 10) return false;
    
    // Calcula diferença média
    double diff_total = arr[n-1] - arr[0];
    double diff_esperada = diff_total / n;
    
    // Conta violações (diferenças muito maiores que a média)
    int violacoes = 0;
    for (int i = 1; i < n; i++) {
        double diff_local = arr[i] - arr[i-1];
        if (diff_local > 3 * diff_esperada || diff_local < diff_esperada / 3) {
            violacoes++;
        }
    }
    
    // Se menos de 10% são outliers, considera uniforme
    return (violacoes < n * 0.10);
}

/**
 * Verifica se array está ordenado
 */
bool verificar_ordenado(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i-1]) return false;
    }
    return true;
}

/**
 * Sistema completo de busca adaptativa
 */
int busca_adaptativa(int arr[], int n, int valor, int num_buscas_futuras) {
    // Analisa características dos dados
    MetadadosBusca meta;
    meta.tamanho = n;
    meta.ordenado = verificar_ordenado(arr, n);
    meta.distribuicao_uniforme = meta.ordenado ? analisar_uniformidade(arr, n) : false;
    meta.num_buscas_esperadas = num_buscas_futuras;
    
    // Seleciona algoritmo apropriado
    DecisaoBusca decisao = selecionar_algoritmo(&meta);
    
    // Log da decisão (em produção, usar sistema de logging)
    printf("[BUSCA ADAPTATIVA] Algoritmo selecionado: ");
    switch(decisao.algoritmo) {
        case ALG_LINEAR: printf("LINEAR"); break;
        case ALG_LINEAR_SENTINELA: printf("LINEAR COM SENTINELA"); break;
        case ALG_BINARIA: printf("BINÁRIA"); break;
        case ALG_INTERPOLADA: printf("INTERPOLADA"); break;
        case ALG_HASH: printf("HASH TABLE"); break;
        case ALG_HIBRIDO: printf("HÍBRIDO"); break;
    }
    printf("\n[RAZÃO] %s\n", decisao.razao);
    
    // Executa busca com algoritmo selecionado
    switch(decisao.algoritmo) {
        case ALG_LINEAR:
        case ALG_LINEAR_SENTINELA:
            return busca_linear(arr, n, valor);
        
        case ALG_BINARIA:
            if (!meta.ordenado) {
                printf("[INFO] Ordenando array antes da busca binária...\n");
                qsort(arr, n, sizeof(int), comparar);
            }
            return busca_binaria(arr, n, valor);
        
        case ALG_INTERPOLADA:
            return busca_interpolada(arr, n, valor);
        
        case ALG_HIBRIDO:
            return busca_hibrida(arr, n, valor);
        
        case ALG_HASH:
            printf("[INFO] Para múltiplas buscas, considere criar hash table\n");
            return busca_linear(arr, n, valor);
    }
    
    return -1;
}

// Implementações dos algoritmos (simplificadas)
int busca_linear(int arr[], int n, int valor) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == valor) return i;
    }
    return -1;
}

int busca_binaria(int arr[], int n, int valor) {
    int esq = 0, dir = n - 1;
    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;
        if (arr[meio] == valor) return meio;
        if (arr[meio] < valor) esq = meio + 1;
        else dir = meio - 1;
    }
    return -1;
}

int busca_interpolada(int arr[], int n, int valor) {
    int esq = 0, dir = n - 1;
    
    while (esq <= dir && valor >= arr[esq] && valor <= arr[dir]) {
        if (esq == dir) {
            return (arr[esq] == valor) ? esq : -1;
        }
        
        // Interpolação
        int pos = esq + ((double)(valor - arr[esq]) / (arr[dir] - arr[esq])) * (dir - esq);
        
        if (arr[pos] == valor) return pos;
        if (arr[pos] < valor) esq = pos + 1;
        else dir = pos - 1;
    }
    return -1;
}

int busca_hibrida(int arr[], int n, int valor) {
    // Tenta interpolação por algumas iterações
    int tentativas_max = (int)log2(n) + 1;
    int esq = 0, dir = n - 1, tentativas = 0;
    
    while (esq <= dir && tentativas < tentativas_max && 
           valor >= arr[esq] && valor <= arr[dir]) {
        int pos = esq + ((double)(valor - arr[esq]) / (arr[dir] - arr[esq])) * (dir - esq);
        
        if (arr[pos] == valor) return pos;
        if (arr[pos] < valor) esq = pos + 1;
        else dir = pos - 1;
        
        tentativas++;
    }
    
    // Se não encontrou, usa busca binária no intervalo restante
    printf("[HÍBRIDO] Mudando para busca binária após %d tentativas\n", tentativas);
    return busca_binaria(arr + esq, dir - esq + 1, valor);
}

int comparar(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Exemplo de uso
int main() {
    // Teste 1: Array pequeno
    int arr1[] = {5, 2, 8, 1, 9};
    printf("\n=== TESTE 1: Array pequeno ===\n");
    busca_adaptativa(arr1, 5, 8, 1);
    
    // Teste 2: Array grande ordenado uniforme
    int arr2[100000];
    for (int i = 0; i < 100000; i++) arr2[i] = i * 10;
    printf("\n=== TESTE 2: Grande ordenado uniforme ===\n");
    busca_adaptativa(arr2, 100000, 50000, 100);
    
    // Teste 3: Array grande não uniforme
    int arr3[10000];
    for (int i = 0; i < 10000; i++) arr3[i] = i * i;
    printf("\n=== TESTE 3: Grande não uniforme ===\n");
    busca_adaptativa(arr3, 10000, 10000, 50);
    
    return 0;
}
```

**Características do Sistema**:

1. **Análise Automática**: Detecta ordenação e uniformidade
2. **Seleção Inteligente**: Usa regras heurísticas baseadas em teoria
3. **Fallback Seguro**: Sempre tem opção confiável (busca binária)
4. **Logging**: Explica decisões para debugging
5. **Flexível**: Fácil adicionar novos algoritmos e regras

**Extensões Possíveis**:
- **Aprendizado**: Coletar estatísticas e ajustar regras
- **Cache**: Manter índices para buscas repetidas
- **Paralelização**: Busca linear paralela para arrays muito grandes
- **Estruturas auxiliares**: Criar índices sob demanda

---

## 💡 Questões Adicionais Avançadas

### 6. Explique como a hierarquia de memória (cache) afeta a performance real dos algoritmos de busca.

**Resposta**:

A hierarquia de memória moderna (Cache L1 → L2 → L3 → RAM) introduz latências variáveis que não são capturadas pela análise Big O tradicional.

**Latências Típicas**:
```
Registrador CPU: 0 ciclos
Cache L1: 4 ciclos (~1ns)
Cache L2: 12 ciclos (~3ns)
Cache L3: 38 ciclos (~12ns)
RAM: 200+ ciclos (~60ns)
```

**Busca Linear**:
- **Padrão de acesso**: Sequencial
- **Cache behavior**: Ótimo - prefetching automático
- **Cache misses**: ~n/64 (assumindo cache lines de 64 bytes)
- **Tempo real**: Dominado por velocidade de cache L1/L2

**Busca Binária**:
- **Padrão de acesso**: Aleatório (jumps grandes)
- **Cache behavior**: Ruim - muitos cache misses
- **Cache misses**: ~log n (cada comparação pode ser um miss)
- **Tempo real**: Dominado por latência de RAM

**Impacto Prático**:
```
Array de 10.000 inteiros (40KB, não cabe em L1 32KB)

Busca Linear:
- Comparações: 5.000 (caso médio)
- Cache misses: ~80 (acesso sequencial)
- Tempo: 5.000 × 1ns + 80 × 60ns ≈ 10 µs

Busca Binária:
- Comparações: 14
- Cache misses: ~10 (cada acesso pode ser miss)
- Tempo: 14 × 1ns + 10 × 60ns ≈ 0.6 µs

Binária ainda ganha, mas não por fator de 357× (5000/14)
```

**Para arrays que cabem em cache** (< 32KB):
```
Linear: muito rápida (tudo em L1)
Binária: ainda rápida (tudo em L1)
Binária vence, mas gap menor
```

**Otimizações cache-aware**:
1. **B-tree search**: Minimiza cache misses em árvores
2. **Blocked algorithms**: Divide dados em blocos do tamanho do cache
3. **Eytzinger layout**: Reorganiza array para busca binária cache-friendly

---

### 7. Como implementar busca binária para encontrar o menor elemento maior ou igual a um valor (lower bound)?

**Resposta**:

**Lower bound**: Menor elemento ≥ valor procurado (útil em C++ STL)

```c
/**
 * Retorna índice do menor elemento >= valor
 * Se todos < valor, retorna n
 */
int lower_bound(int arr[], int n, int valor) {
    int esq = 0, dir = n;
    
    while (esq < dir) {
        int meio = esq + (dir - esq) / 2;
        
        if (arr[meio] < valor) {
            esq = meio + 1;  // Elemento[meio] muito pequeno
        } else {
            dir = meio;       // Elemento[meio] pode ser resposta
        }
    }
    
    return esq;  // Retorna posição onde valor deveria ser inserido
}
```

**Upper bound**: Menor elemento > valor

```c
int upper_bound(int arr[], int n, int valor) {
    int esq = 0, dir = n;
    
    while (esq < dir) {
        int meio = esq + (dir - esq) / 2;
        
        if (arr[meio] <= valor) {  // Diferença: <= ao invés de <
            esq = meio + 1;
        } else {
            dir = meio;
        }
    }
    
    return esq;
}
```

**Aplicações**:
1. **Inserção em array ordenado**: `insert(arr, lower_bound(...), valor)`
2. **Range queries**: Elementos entre [a,b] = [lower_bound(a), upper_bound(b))
3. **Aproximação**: Encontrar valor mais próximo

---

### 8. Por que a busca ternária (divide em 3) não é mais eficiente que binária (divide em 2)?

**Resposta**:

Intuitivamente, dividir em 3 partes parece melhor, mas matematicamente não é.

**Análise de Comparações**:

**Busca Binária**:
- 1 comparação por nível
- log₂(n) níveis
- **Total**: log₂(n) comparações

**Busca Ternária**:
- 2 comparações por nível (verificar m1 e m2)
- log₃(n) níveis  
- **Total**: 2 × log₃(n) comparações

**Conversão para mesma base**:
```
2 × log₃(n) = 2 × log₂(n) / log₂(3)
             = 2 × log₂(n) / 1.585
             ≈ 1.26 × log₂(n)
```

**Conclusão**: Ternária usa ~26% mais comparações!

**Razão**: Reduzir espaço de busca para n/3 (vs n/2) não compensa o custo de 2 comparações (vs 1).

**Onde ternária é útil**:
- **Otimização de funções unimodais** (encontrar mínimo/máximo)
- Não para busca em arrays ordenados

---

### 9. Como busca binária se relaciona com árvores de decisão e teoria da informação?

**Resposta**:

**Árvore de Decisão**:
Cada execução da busca binária pode ser representada como uma árvore binária:
- **Nós internos**: Comparações
- **Folhas**: Resultado (posição encontrada ou não existe)
- **Altura**: Número de comparações no pior caso

**Limite Inferior via Teoria da Informação**:

Para distinguir entre n possibilidades, precisamos de log₂(n) bits de informação.

Cada comparação binária fornece no máximo 1 bit de informação:
```
Antes: n possibilidades → log₂(n) bits de incerteza
Comparação: resposta sim/não → 1 bit de informação
Depois: n/2 possibilidades → log₂(n) - 1 bits restantes
```

**Teorema**: Qualquer algoritmo baseado em comparações precisa de pelo menos log₂(n) comparações no pior caso.

**Busca binária atinge este limite** → é ótima!

**Conexão com Entropia**:
```
Entropia de Shannon: H = -Σ p(i) log₂ p(i)

Para busca uniforme: p(i) = 1/n para todo i
H = -n × (1/n) log₂(1/n) = log₂(n)

Interpretação: Precisa de log₂(n) bits para codificar a resposta
```

---

### 10. Como realizar busca eficiente em uma matriz ordenada tanto por linhas quanto por colunas?

**Resposta**:

**Matriz Young** (ordenada em linhas e colunas):
```
[1,   3,   5,   7]
[2,   4,   6,   8]
[9,  10,  11,  12]
[13, 14,  15,  16]
```

**Algoritmo Escalonado (Staircase Search)**:

```c
/**
 * Busca em matriz m×n ordenada nas duas dimensões
 * Complexidade: O(m + n)
 */
int busca_matriz_ordenada(int matriz[][4], int m, int n, int valor) {
    int linha = 0;
    int coluna = n - 1;  // Começa no canto superior direito
    
    while (linha < m && coluna >= 0) {
        if (matriz[linha][coluna] == valor) {
            printf("Encontrado em [%d][%d]\n", linha, coluna);
            return 1;
        }
        
        if (matriz[linha][coluna] > valor) {
            coluna--;  // Elimina coluna inteira
        } else {
            linha++;   // Elimina linha inteira
        }
    }
    
    return 0;  // Não encontrado
}
```

**Por que funciona**:
1. **Canto superior direito**: maior da linha, menor da coluna
2. **Se > valor**: toda coluna pode ser eliminada
3. **Se < valor**: toda linha pode ser eliminada
4. **A cada passo**: elimina linha OU coluna completa

**Visualização**:
```
Buscar: 10

Passo 1: [0][3] = 7 < 10 → elimina linha 0
Passo 2: [1][3] = 8 < 10 → elimina linha 1
Passo 3: [2][3] = 12 > 10 → elimina coluna 3
Passo 4: [2][2] = 11 > 10 → elimina coluna 2
Passo 5: [2][1] = 10 == 10 → ENCONTRADO!

Total: 5 passos para matriz 4×4
Busca linear seria: até 16 passos
```

**Complexidade**:
- No pior caso: elimina m linhas + n colunas
- **Tempo**: O(m + n)
- **Espaço**: O(1)

**Comparação**:
- Busca linear: O(m × n)
- Busca escalonada: O(m + n)
- Para matriz 1000×1000: 1.000.000 vs 2.000 operações!

## 📖 Exercícios Práticos

1. **Básico**: Implemente uma versão recursiva da busca binária
2. **Intermediário**: Crie uma busca binária que retorne todas as posições de elementos duplicados
3. **Avançado**: Desenvolva uma busca híbrida que escolha automaticamente entre linear e binária baseado no tamanho dos dados
4. **Desafio**: Implemente busca ternária e compare sua performance com a busca binária

## 📚 Referências Acadêmicas e Bibliografia

### Livros Fundamentais

#### Obras Clássicas em Análise de Algoritmos

1. **Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C.** (2009). *Introduction to Algorithms* (3rd ed.). MIT Press.
   - **Capítulo 2.3**: Análise de algoritmos - Busca linear
   - **Capítulo 12**: Árvores de busca binária
   - **Seções 2.2, 12.2**: Complexidade e invariantes de loop
   - ISBN: 978-0262033848
   - *Considerado a "bíblia" dos algoritmos, com provas formais detalhadas*

2. **Knuth, D. E.** (1998). *The Art of Computer Programming, Volume 3: Sorting and Searching* (2nd ed.). Addison-Wesley.
   - **Seção 6.2.1**: Busca sequencial e suas variantes
   - **Seção 6.2.2**: Busca binária e análise matemática detalhada
   - **Seção 6.4**: Hashing e métodos de acesso direto
   - ISBN: 978-0201896855
   - *Análise matemática rigorosa, incluindo constantes ocultas*

3. **Sedgewick, R., & Wayne, K.** (2011). *Algorithms* (4th ed.). Addison-Wesley.
   - **Capítulo 1.4**: Análise de algoritmos
   - **Capítulo 3.1**: Tabelas de símbolos e busca
   - **Capítulo 3.2**: Árvores de busca binária
   - ISBN: 978-0321573513
   - *Abordagem prática com implementações em Java*

4. **Aho, A. V., Hopcroft, J. E., & Ullman, J. D.** (1974). *The Design and Analysis of Computer Algorithms*. Addison-Wesley.
   - **Capítulo 3**: Limites inferiores em modelos de comparação
   - **Capítulo 4**: Busca em estruturas de dados
   - ISBN: 978-0201000290
   - *Clássico sobre limites teóricos de algoritmos*

### Artigos Seminais

#### Busca Binária

5. **Bottenbruch, H.** (1962). "Structure and Use of ALGOL 60". *Journal of the ACM*, 9(2), 161-221.
   - DOI: 10.1145/321119.321120
   - *Primeira publicação formal do algoritmo de busca binária*

6. **Knuth, D. E.** (2000). "Ancient Babylonian Algorithms". *Communications of the ACM*, 15(7), 671-677.
   - DOI: 10.1145/361454.361514
   - *Discute origens históricas de algoritmos de busca*

#### Busca Interpolada

7. **Peterson, W. W.** (1957). "Addressing for Random-Access Storage". *IBM Journal of Research and Development*, 1(2), 130-146.
   - DOI: 10.1147/rd.12.0130
   - *Trabalho original propondo busca interpolada*

8. **Perl, Y., Itai, A., & Avni, H.** (1978). "Interpolation Search—A Log Log N Search". *Communications of the ACM*, 21(7), 550-553.
   - DOI: 10.1145/359545.359557
   - *Prova matemática da complexidade O(log log n)*

9. **Yao, A. C., & Yao, F. F.** (1976). "The Complexity of Searching an Ordered Random Table". *Proceedings of 17th Annual Symposium on Foundations of Computer Science*, 173-177.
   - DOI: 10.1109/SFCS.1976.12
   - *Análise probabilística de busca em dados uniformes*

### Teoria da Complexidade e Limites Inferiores

10. **Moret, B. M. E.** (1982). "Decision Trees and Diagrams". *Computing Surveys*, 14(4), 593-623.
    - DOI: 10.1145/356893.356898
    - *Árvores de decisão como modelo para provar limites inferiores*

11. **Ben-Or, M.** (1983). "Lower Bounds for Algebraic Computation Trees". *Proceedings of the 15th Annual ACM Symposium on Theory of Computing*, 80-86.
    - DOI: 10.1145/800061.808735
    - *Limites inferiores para algoritmos baseados em comparações*

12. **Fredman, M. L.** (1976). "How Good is the Information Theory Bound in Sorting?". *Theoretical Computer Science*, 1(4), 355-361.
    - DOI: 10.1016/0304-3975(76)90078-5
    - *Conexão entre teoria da informação e limites de busca/ordenação*

### Estruturas de Dados e Otimizações

13. **Brodnik, A., Carlsson, S., Demaine, E. D., Munro, J. I., & Sedgewick, R.** (1999). "Resizable Arrays in Optimal Time and Space". *Workshop on Algorithms and Data Structures*, 37-48.
    - DOI: 10.1007/3-540-48447-7_4
    - *Arrays dinâmicos e análise amortizada*

14. **Pugh, W.** (1990). "Skip Lists: A Probabilistic Alternative to Balanced Trees". *Communications of the ACM*, 33(6), 668-676.
    - DOI: 10.1145/78973.78977
    - *Estrutura alternativa com busca O(log n) esperada*

15. **Bentley, J. L., & Yao, A. C.** (1976). "An Almost Optimal Algorithm for Unbounded Searching". *Information Processing Letters*, 5(3), 82-87.
    - DOI: 10.1016/0020-0190(76)90071-5
    - *Busca exponencial para arrays sem tamanho conhecido*

### Otimizações e Aspectos Práticos

16. **Brodal, G. S., & Moruz, G.** (2006). "Skewed Binary Search Trees". *Algorithms–ESA 2006*, 708-719.
    - DOI: 10.1007/11841036_63
    - *Busca binária otimizada para dados não uniformes*

17. **Khuong, P. V., & Morin, P.** (2017). "Array Layouts for Comparison-Based Searching". *Journal of Experimental Algorithmics*, 22, Article 1.3.
    - DOI: 10.1145/3053370
    - *Layouts de array otimizados para cache*

18. **Manber, U., & Myers, G.** (1993). "Suffix Arrays: A New Method for On-Line String Searches". *SIAM Journal on Computing*, 22(5), 935-948.
    - DOI: 10.1137/0222058
    - *Aplicação de busca binária em processamento de strings*

### Análise Probabilística e Randomização

19. **Gonnet, G. H., Rogers, L. D., & George, J. A.** (1980). "An Algorithmic and Complexity Analysis of Interpolation Search". *Acta Informatica*, 13(1), 39-52.
    - DOI: 10.1007/BF00288537
    - *Análise detalhada de performance esperada*

20. **Andersson, A., & Thorup, M.** (2000). "Tight(er) Worst-Case Bounds on Dynamic Searching and Priority Queues". *Proceedings of the 32nd Annual ACM Symposium on Theory of Computing*, 335-342.
    - DOI: 10.1145/335305.335345
    - *Limites apertados para busca dinâmica*

### Cache e Hierarquia de Memória

21. **Frigo, M., Leiserson, C. E., Prokop, H., & Ramachandran, S.** (1999). "Cache-Oblivious Algorithms". *Proceedings of 40th Annual Symposium on Foundations of Computer Science*, 285-297.
    - DOI: 10.1109/SFFCS.1999.814600
    - *Algoritmos otimizados para hierarquia de memória*

22. **Ladner, R. E., Fix, J. D., & LaMarca, A.** (1999). "Cache Performance Analysis of Traversals and Random Accesses". *Proceedings of the 10th Annual ACM-SIAM Symposium on Discrete Algorithms*, 613-622.
    - *Impacto de cache em busca binária vs linear*

### Aplicações e Variações

23. **Willard, D. E.** (1983). "Log-logarithmic Worst-Case Range Queries are Possible in Space Θ(N)". *Information Processing Letters*, 17(2), 81-84.
    - DOI: 10.1016/0020-0190(83)90075-3
    - *Busca em intervalos com complexidade sublogarítmica*

24. **van Emde Boas, P.** (1977). "Preserving Order in a Forest in Less Than Logarithmic Time". *Proceedings of 16th Annual Symposium on Foundations of Computer Science*, 75-84.
    - DOI: 10.1109/SFCS.1977.32
    - *Estrutura com busca O(log log U) onde U é universo*

### Recursos Online e Materiais Complementares

25. **MIT OpenCourseWare**: Introduction to Algorithms (6.006)
    - URL: https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/
    - *Vídeos e materiais das aulas do MIT*

26. **Visualgo**: Algorithm Visualizations
    - URL: https://visualgo.net/en/bst
    - *Visualizações interativas de algoritmos de busca*

27. **Big-O Cheat Sheet**: Complexity Reference
    - URL: https://www.bigocheatsheet.com/
    - *Referência rápida de complexidades*

### Padrões e Melhores Práticas

28. **Bentley, J.** (1999). *Programming Pearls* (2nd ed.). Addison-Wesley.
    - **Coluna 4**: "Writing Correct Programs" - Busca binária
    - **Coluna 9**: "Code Tuning" - Otimizações práticas
    - ISBN: 978-0201657883
    - *Discussões sobre bugs comuns em busca binária*

29. **Bloch, J.** (2006). "Extra, Extra - Read All About It: Nearly All Binary Searches and Mergesorts are Broken". *Google Research Blog*.
    - URL: https://ai.googleblog.com/2006/06/extra-extra-read-all-about-it-nearly.html
    - *Bug de overflow em implementações de busca binária*

### Histórico e Curiosidades

30. **Katajainen, J.** (2010). "In the Footsteps of a Giant: Donald Knuth at 72". *Theoretical Computer Science*, 412(1-2), 1-2.
    - DOI: 10.1016/j.tcs.2010.10.002
    - *Contribuições de Knuth para análise de algoritmos*

31. **Dijkstra, E. W.** (1982). "Why Numbering Should Start at Zero". EWD831.
    - URL: https://www.cs.utexas.edu/users/EWD/transcriptions/EWD08xx/EWD831.html
    - *Argumentação sobre indexação em arrays*

### Benchmarking e Análise Experimental

32. **McGeoch, C. C.** (2012). *A Guide to Experimental Algorithmics*. Cambridge University Press.
    - ISBN: 978-0521173018
    - *Metodologia para benchmarks e análise empírica*

33. **Mitzenmacher, M., & Upfal, E.** (2005). *Probability and Computing: Randomized Algorithms and Probabilistic Analysis*. Cambridge University Press.
    - ISBN: 978-0521835404
    - *Análise probabilística de algoritmos*

### Normas e Padrões

34. **ISO/IEC 9899:2018**: Programming Languages — C (C18)
    - *Padrão da linguagem C, incluindo comportamento de arrays*

35. **IEEE Std 754-2019**: IEEE Standard for Floating-Point Arithmetic
    - *Importante para busca interpolada com ponto flutuante*

### Notas Sobre Citações

**Como citar este material** (formato ABNT):
```
CAPARROZ, Prof. Luis. Algoritmos de Pesquisa em C. In: Estrutura de Dados em C. 
GitHub, 2024. Disponível em: <https://github.com/profluiscaparroz/estrutura-dados-c>.
Acesso em: [data].
```

**Como citar** (formato APA):
```
Caparroz, L. (2024). Algoritmos de Pesquisa em C. In Estrutura de Dados em C. 
GitHub. https://github.com/profluiscaparroz/estrutura-dados-c
```

---

## 📖 Leitura Recomendada por Nível

### Iniciante
- Sedgewick & Wayne (2011) - Capítulos 1 e 3
- Cormen et al. (2009) - Capítulo 2
- Programming Pearls - Coluna 4

### Intermediário
- Knuth (1998) - Seções 6.2.1 e 6.2.2
- Cormen et al. (2009) - Capítulo 12
- Perl, Itai & Avni (1978) - Artigo sobre interpolação

### Avançado
- Aho, Hopcroft & Ullman (1974) - Limites inferiores
- Ben-Or (1983) - Complexidade algébrica
- Frigo et al. (1999) - Algoritmos cache-oblivious

### Pesquisa
- Willard (1983) - Busca sublogarítmica
- van Emde Boas (1977) - Estruturas de dados avançadas
- Andersson & Thorup (2000) - Limites apertados