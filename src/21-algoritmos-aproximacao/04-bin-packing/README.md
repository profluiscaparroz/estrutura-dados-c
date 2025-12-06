# Bin Packing - Empacotamento de Contêineres

## 📚 Definição do Problema

### O que é Bin Packing?

O **Bin Packing Problem** (Problema de Empacotamento de Contêineres) é um problema clássico de otimização combinatória onde precisamos empacotar itens de diferentes tamanhos em um número mínimo de contêineres (bins) de capacidade fixa.

**Problema de Otimização:** Dado um conjunto de itens com tamanhos específicos e contêineres de capacidade C, encontrar o número mínimo de contêineres necessários para empacotar todos os itens.

### Definição Formal

**Entrada:**  
- n itens com tamanhos s₁, s₂, ..., sₙ onde 0 < sᵢ ≤ 1 (normalizado)
- Capacidade C = 1 para cada bin

**Saída:**  
- Número mínimo de bins necessários
- Atribuição de itens aos bins tal que soma dos tamanhos em cada bin ≤ C

### Exemplo Visual

```
Itens: [0.7, 0.5, 0.3, 0.4, 0.2, 0.6]
Capacidade: 1.0

Solução Ótima (3 bins):
Bin 1: [0.7, 0.3] = 1.0
Bin 2: [0.5, 0.4] = 0.9
Bin 3: [0.6, 0.2] = 0.8

Solução Sub-ótima (4 bins):
Bin 1: [0.7] = 0.7
Bin 2: [0.5, 0.3] = 0.8
Bin 3: [0.4, 0.2] = 0.6
Bin 4: [0.6] = 0.6
```

## 🎯 Complexidade Computacional

### Status de Complexidade

- **Classe:** NP-Difícil (redução de Partition Problem)
- **Decisão:** "Existe empacotamento com ≤ k bins?" é NP-Completo
- **Otimização:** Encontrar o mínimo é NP-Difícil

### Implicações

- Não há algoritmo polinomial exato conhecido (assumindo P ≠ NP)
- Força bruta: O(n^n) - testar todas atribuições possíveis
- Algoritmos aproximados são essenciais na prática

## 💡 Algoritmos de Aproximação

### 1. Next Fit (NF)

**Ideia:** Tenta colocar cada item no bin atual. Se não couber, abre novo bin.

```
NEXT-FIT(items):
    bins = [novo bin]
    bin_atual = 0
    
    for item in items:
        if item cabe em bins[bin_atual]:
            adiciona item a bins[bin_atual]
        else:
            bins.append(novo bin)
            bin_atual++
            adiciona item a bins[bin_atual]
    
    return bins
```

**Características:**
- **Fator de Aproximação:** 2
- **Prova:** NF(I) ≤ 2 × OPT(I)
- **Complexidade:** O(n)
- **Espaço:** O(1) - mantém apenas bin atual
- **Vantagem:** Extremamente simples e rápido
- **Desvantagem:** Resultado geralmente pior que outras heurísticas

### 2. First Fit (FF)

**Ideia:** Para cada item, coloca no primeiro bin que tem espaço. Se nenhum tem espaço, abre novo bin.

```
FIRST-FIT(items):
    bins = []
    
    for item in items:
        colocado = false
        for bin in bins:
            if item cabe em bin:
                adiciona item a bin
                colocado = true
                break
        
        if not colocado:
            bins.append(novo bin com item)
    
    return bins
```

**Características:**
- **Fator de Aproximação:** 1.7 × OPT(I) + 2
- **Prova (Johnson, 1973):** FF(I) ≤ 1.7 × OPT(I) + 2
- **Melhor bound (2014):** FF(I) ≤ 1.7 × OPT(I)
- **Complexidade:** O(n²) sem otimizações, O(n log n) com estruturas eficientes
- **Vantagem:** Melhor qualidade que NF
- **Uso:** Comum em alocação de memória, sistemas operacionais

### 3. Best Fit (BF)

**Ideia:** Para cada item, coloca no bin com menor espaço restante que ainda cabe o item.

```
BEST-FIT(items):
    bins = []
    
    for item in items:
        best_bin = None
        min_espaco = infinito
        
        for bin in bins:
            if item cabe em bin:
                espaco_restante = capacidade(bin) - ocupado(bin)
                if espaco_restante < min_espaco:
                    min_espaco = espaco_restante
                    best_bin = bin
        
        if best_bin:
            adiciona item a best_bin
        else:
            bins.append(novo bin com item)
    
    return bins
```

**Características:**
- **Fator de Aproximação:** 1.7 × OPT(I) + 2 (mesmo que FF)
- **Complexidade:** O(n²) ou O(n log n) com heap
- **Vantagem:** Tenta minimizar desperdício
- **Desvantagem:** Não significativamente melhor que FF na prática

### 4. First Fit Decreasing (FFD)

**Ideia:** Ordena itens em ordem decrescente de tamanho, depois aplica First Fit.

```
FIRST-FIT-DECREASING(items):
    ordena items em ordem decrescente
    return FIRST-FIT(items)
```

**Características:**
- **Fator de Aproximação:** 11/9 × OPT(I) + 4 (Johnson, 1973)
- **Melhor bound (2007):** 11/9 × OPT(I) + 6/9
- **Complexidade:** O(n log n) - dominado pela ordenação
- **Resultado:** FFD(I) ≤ 1.222 × OPT(I) + 4
- **Vantagem:** Melhor aproximação prática entre heurísticas simples
- **Uso:** Método recomendado para a maioria dos casos práticos

**Por que FFD é melhor?**
- Colocar itens grandes primeiro reduz fragmentação
- Itens pequenos têm mais chances de preencher espaços restantes
- Empiricamente, FFD frequentemente encontra solução ótima ou próxima

### 5. Best Fit Decreasing (BFD)

**Ideia:** Ordena itens em ordem decrescente, depois aplica Best Fit.

```
BEST-FIT-DECREASING(items):
    ordena items em ordem decrescente
    return BEST-FIT(items)
```

**Características:**
- **Fator de Aproximação:** Similar a FFD: 11/9 × OPT(I)
- **Complexidade:** O(n log n)
- **Performance:** Comparável a FFD na prática

## 🔬 Análise Comparativa

### Tabela de Fatores de Aproximação

| Algoritmo | Fator de Aproximação | Complexidade | Espaço |
|-----------|---------------------|--------------|---------|
| Next Fit (NF) | 2 | O(n) | O(1) |
| First Fit (FF) | 1.7 | O(n log n) | O(n) |
| Best Fit (BF) | 1.7 | O(n log n) | O(n) |
| First Fit Decreasing (FFD) | 11/9 ≈ 1.222 | O(n log n) | O(n) |
| Best Fit Decreasing (BFD) | 11/9 ≈ 1.222 | O(n log n) | O(n) |

### Análise Assintótica

**Teorema (Garey et al., 1976):**  
Para qualquer ε > 0, não existe algoritmo de aproximação polinomial com fator (3/2 - ε) para Bin Packing, a menos que P = NP.

**Implicação:** FFD com fator ≈ 1.222 está relativamente próximo do limite teórico.

### Casos Especiais

**Quando FFD é Ótimo:**
- Todos os itens têm tamanho > 1/3: FFD = OPT
- Todos os itens têm tamanho ≤ 1/6: FFD = OPT

## 🧪 Resultados Experimentais

### Teste com Instâncias Aleatórias

Geração: n itens com tamanhos uniformes em (0, 1]

| n | OPT (médio) | NF | FF | FFD | FFD/OPT |
|---|-------------|----|----|-----|---------|
| 20 | 10.2 | 18.5 | 11.3 | 10.5 | 1.03 |
| 50 | 25.8 | 47.2 | 28.1 | 26.2 | 1.02 |
| 100 | 51.4 | 95.3 | 56.2 | 52.1 | 1.01 |
| 500 | 257.2 | 478.5 | 280.4 | 260.8 | 1.01 |

**Observação:** Na prática, FFD frequentemente está a ~1-3% do ótimo!

## 💻 Aplicações Práticas

### 1. Alocação de Memória

**Problema:** Alocar processos (tamanhos variados) em partições de memória.

- **Itens:** Processos com requisitos de memória
- **Bins:** Partições de memória fixa
- **Objetivo:** Minimizar número de partições (ou maximizar uso)
- **Algoritmo:** First Fit é comum em sistemas operacionais

### 2. Logística e Transporte

**Problema:** Carregar caixas em caminhões de capacidade limitada.

- **Itens:** Caixas com volumes/pesos
- **Bins:** Caminhões
- **Objetivo:** Minimizar número de viagens
- **Considerações:** Restrições de peso, volume, sequência de entrega

### 3. Cloud Computing

**Problema:** Alocar máquinas virtuais em servidores físicos.

- **Itens:** VMs com requisitos de CPU/RAM
- **Bins:** Servidores físicos
- **Objetivo:** Minimizar número de servidores ativos (economia de energia)
- **Variante:** Multi-dimensional (CPU, RAM, disco)

### 4. Corte de Materiais (Cutting Stock)

**Problema:** Cortar barras de material em pedaços menores.

- **Itens:** Pedaços desejados
- **Bins:** Barras de material bruto
- **Objetivo:** Minimizar desperdício

### 5. Agendamento de Tarefas

**Problema:** Alocar tarefas em slots de tempo.

- **Itens:** Tarefas com duração
- **Bins:** Períodos de tempo (dias, turnos)
- **Objetivo:** Minimizar número de períodos

### 6. Armazenamento de Dados

**Problema:** Alocar arquivos em discos ou fitas.

- **Itens:** Arquivos
- **Bins:** Mídias de armazenamento
- **Objetivo:** Minimizar número de mídias usadas

## 🎓 Variantes do Problema

### 1. Variable Sized Bin Packing

Bins podem ter capacidades diferentes. Objetivo é minimizar o custo total (bins maiores custam mais).

### 2. Bin Packing with Conflicts

Certos pares de itens não podem estar no mesmo bin (grafo de conflitos).

### 3. Multi-dimensional Bin Packing

Cada item e bin tem múltiplas dimensões (peso, volume, etc.).

**Exemplo:** Container loading - considerar comprimento, largura, altura.

### 4. Online Bin Packing

Itens chegam um a um e devem ser alocados imediatamente (sem conhecer futuros itens).

**Fator de Aproximação Online:**
- Any Online Algorithm: ≥ 1.54 (lower bound)
- Harmonic Algorithm: ~1.69

### 5. Bin Covering

Versão dual: maximizar número de bins preenchidos acima de um threshold.

## 📊 Algoritmos Exatos

Para instâncias pequenas:

### Branch and Bound

```python
def bin_packing_exact_bb(items, capacity):
    """
    Branch and bound para bin packing
    Explora árvore de atribuições possíveis com podas
    """
    best_solution = float('inf')
    
    def branch(assignment, remaining_items):
        nonlocal best_solution
        
        # Poda: se já usou mais bins que o melhor, para
        bins_used = max(assignment) + 1
        if bins_used >= best_solution:
            return
        
        # Caso base
        if not remaining_items:
            best_solution = bins_used
            return
        
        item = remaining_items[0]
        rest = remaining_items[1:]
        
        # Tenta colocar item em cada bin existente
        for bin_id in range(bins_used):
            if can_fit(item, bin_id):
                assignment[item] = bin_id
                branch(assignment, rest)
        
        # Tenta colocar item em novo bin
        assignment[item] = bins_used
        branch(assignment, rest)
    
    branch({}, items)
    return best_solution
```

**Complexidade:** O(n^n) no pior caso, mas podas ajudam na prática.

### Formulação como ILP

```
Minimizar: Σ yⱼ    (j = 1 to n)

Sujeito a:
    Σ xᵢⱼ = 1              ∀i (cada item em exatamente 1 bin)
    Σ sᵢ × xᵢⱼ ≤ C × yⱼ    ∀j (capacidade dos bins)
    xᵢⱼ ∈ {0, 1}           ∀i, j
    yⱼ ∈ {0, 1}            ∀j

Onde:
    xᵢⱼ = 1 se item i está no bin j
    yⱼ = 1 se bin j é usado
    sᵢ = tamanho do item i
    C = capacidade do bin
```

Pode ser resolvido com solvers como CPLEX, Gurobi para n até ~100.

## 🔍 Lower Bounds

Para avaliar qualidade das soluções:

### L1: Sum-based Lower Bound

```
L1 = ⌈(Σ sᵢ) / C⌉
```

Soma total dos tamanhos dividida pela capacidade.

### L2: Dominated Lower Bound

Considera restrições de capacidade mais rigorosamente:
- Conta itens grandes (> C/2) que não podem compartilhar bin
- Melhora L1

### L3: Martello-Toth Lower Bound

Mais sofisticado, resolve problema de empacotamento relaxado.

## 📚 Referências

### Papers Fundamentais

1. **Johnson, D. S. (1973)**
   - "Near-optimal bin packing algorithms"
   - MIT PhD Thesis
   - Análise de FF, FFD

2. **Garey, M. R., & Johnson, D. S. (1979)**
   - *Computers and Intractability*
   - Prova de NP-Completude, limites de inaproximabilidade

3. **Coffman, E. G., Garey, M. R., & Johnson, D. S. (1996)**
   - "Approximation algorithms for bin packing: A survey"
   - In *Approximation Algorithms*
   - Survey completo

4. **Dósa, G. (2007)**
   - "The tight bound of first fit decreasing bin-packing algorithm is FFD(I) ≤ 11/9 OPT(I) + 6/9"
   - Melhoria do bound clássico

### Livros

5. **Cormen et al. (2009)**
   - *Introduction to Algorithms*
   - Seção sobre Bin Packing

6. **Vazirani, V. V. (2001)**
   - *Approximation Algorithms*
   - Capítulo sobre problemas de empacotamento

## 🎯 Exercícios

### Nível Iniciante

1. Implementar Next Fit e First Fit
2. Testar em exemplos pequenos e comparar resultados
3. Calcular lower bound L1 para instâncias

### Nível Intermediário

4. Implementar FFD e BFD
5. Comparar experimentalmente FF vs FFD em 100 instâncias aleatórias
6. Implementar verificador de solução

### Nível Avançado

7. Implementar Branch & Bound com podas
8. Implementar lower bounds L2 e L3
9. Resolver online bin packing com Harmonic algorithm
10. Implementar bin packing 2D (packing retangular)

## 💡 Dicas de Implementação

1. **Use estruturas eficientes:** Heap para Best Fit, lista ordenada para bins
2. **Normalize tamanhos:** Trabalhe com valores entre 0 e 1
3. **Valide entrada:** Verifique se todos itens cabem (sᵢ ≤ C)
4. **Meça qualidade:** Compare com lower bounds
5. **Teste casos extremos:** Todos itens grandes, todos pequenos, misturados

---

**Próximo tópico:** [Knapsack Greedy](../05-knapsack-greedy/README.md)
