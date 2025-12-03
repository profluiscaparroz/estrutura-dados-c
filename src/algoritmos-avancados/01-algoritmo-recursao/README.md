# Algoritmos Recursivos - Fundamentos

## 📚 Definição Formal

A **recursão** é uma técnica algorítmica fundamental onde uma função resolve um problema dividindo-o em subproblemas menores da mesma natureza, invocando a si mesma até atingir um caso base que encerra a recursão.

Formalmente, uma função recursiva `f` é definida por:

```
f(n) = {
    caso_base,           se n satisfaz condição de parada
    g(f(n'), ...),       caso contrário, onde n' < n
}
```

Onde `g` é uma função que combina os resultados das chamadas recursivas.

## 🎓 Fundamentação Teórica

### Origem Histórica

O conceito de recursão tem raízes na **lógica matemática** e foi formalizado por:

- **Gödel (1931)**: Funções recursivas primitivas no Teorema da Incompletude
- **Church (1936)**: Cálculo Lambda e computabilidade
- **Turing (1936)**: Máquinas de Turing e funções computáveis
- **McCarthy (1960)**: Implementação prática em LISP, primeira linguagem com suporte nativo à recursão

### Princípio da Indução Matemática

A recursão está intimamente ligada ao **Princípio da Indução Matemática**:

1. **Caso Base**: Prova-se que a propriedade vale para o caso inicial
2. **Passo Indutivo**: Assume-se que vale para `n` e prova-se para `n+1`

Este princípio garante a correção de algoritmos recursivos quando:
- O caso base é corretamente tratado
- Cada chamada recursiva aproxima-se do caso base

## ⚙️ Características Fundamentais

### Componentes de uma Função Recursiva

1. **Caso Base** (Base Case)
   - Condição de parada que evita recursão infinita
   - Retorna um valor trivial sem chamada recursiva
   - Deve ser alcançável a partir de qualquer entrada válida

2. **Caso Recursivo** (Recursive Case)
   - Divide o problema em subproblemas menores
   - Realiza chamada(s) recursiva(s)
   - Combina resultados para formar a solução

3. **Progresso** (Progress)
   - Cada chamada deve reduzir o tamanho do problema
   - Garante terminação do algoritmo

## 📊 Análise de Complexidade

### Complexidade de Tempo

A análise de algoritmos recursivos frequentemente utiliza **relações de recorrência**:

| Algoritmo | Recorrência | Complexidade |
|-----------|-------------|--------------|
| Fatorial | T(n) = T(n-1) + O(1) | O(n) |
| Fibonacci Ingênuo | T(n) = T(n-1) + T(n-2) + O(1) | O(2ⁿ) |
| Busca Binária | T(n) = T(n/2) + O(1) | O(log n) |
| Merge Sort | T(n) = 2T(n/2) + O(n) | O(n log n) |
| Torre de Hanoi | T(n) = 2T(n-1) + O(1) | O(2ⁿ) |

### Teorema Mestre

Para recorrências da forma `T(n) = aT(n/b) + f(n)`:

- Se `f(n) = O(n^c)` onde `c < log_b(a)`: T(n) = Θ(n^(log_b(a)))
- Se `f(n) = Θ(n^(log_b(a)))`: T(n) = Θ(n^(log_b(a)) log n)
- Se `f(n) = Ω(n^c)` onde `c > log_b(a)`: T(n) = Θ(f(n))

### Complexidade de Espaço

A recursão utiliza a **pilha de chamadas** (call stack):

- Cada chamada recursiva aloca um **frame** na pilha
- Espaço: O(profundidade máxima da recursão)
- Risco: **Stack Overflow** para recursões muito profundas

## 🔍 Tipos de Recursão

### 1. Recursão Linear (Linear Recursion)

Uma única chamada recursiva por invocação:

```c
int fatorial(int n) {
    if (n <= 1) return 1;
    return n * fatorial(n - 1);  // Uma chamada
}
```

**Complexidade**: O(n) tempo, O(n) espaço

### 2. Recursão de Cauda (Tail Recursion)

A chamada recursiva é a última operação:

```c
int fatorial_tail(int n, int acc) {
    if (n <= 1) return acc;
    return fatorial_tail(n - 1, n * acc);  // Última operação
}
```

**Otimização**: Compiladores podem transformar em iteração (TCO - Tail Call Optimization), reduzindo espaço para O(1).

### 3. Recursão Múltipla (Multiple Recursion)

Múltiplas chamadas recursivas por invocação:

```c
long fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n-1) + fibonacci(n-2);  // Duas chamadas
}
```

**Problema**: Crescimento exponencial O(2ⁿ) sem otimização.

### 4. Recursão Mútua (Mutual Recursion)

Duas ou mais funções que se chamam mutuamente:

```c
bool eh_par(int n) {
    if (n == 0) return true;
    return eh_impar(n - 1);
}

bool eh_impar(int n) {
    if (n == 0) return false;
    return eh_par(n - 1);
}
```

### 5. Recursão Aninhada (Nested Recursion)

Resultado de uma chamada recursiva é argumento de outra:

```c
int ackermann(int m, int n) {
    if (m == 0) return n + 1;
    if (n == 0) return ackermann(m - 1, 1);
    return ackermann(m - 1, ackermann(m, n - 1));  // Aninhada
}
```

## 🛠️ Técnicas de Otimização

### 1. Memoização

Armazenar resultados de subproblemas para evitar recálculo:

```c
long memo[100] = {0};
int memo_calculado[100] = {0};

long fibonacci_memo(int n) {
    if (n <= 1) return n;
    if (memo_calculado[n]) return memo[n];
    
    memo[n] = fibonacci_memo(n-1) + fibonacci_memo(n-2);
    memo_calculado[n] = 1;
    return memo[n];
}
```

**Redução**: O(2ⁿ) → O(n)

### 2. Conversão para Iteração

Toda recursão pode ser convertida em iteração usando pilha explícita:

```c
long fatorial_iterativo(int n) {
    long resultado = 1;
    for (int i = 2; i <= n; i++) {
        resultado *= i;
    }
    return resultado;
}
```

### 3. Divisão e Conquista Eficiente

Dividir problema em partes iguais para complexidade ótima:

```c
// Exponenciação rápida: O(log n) ao invés de O(n)
long potencia_rapida(int base, int exp) {
    if (exp == 0) return 1;
    long metade = potencia_rapida(base, exp / 2);
    if (exp % 2 == 0) return metade * metade;
    return base * metade * metade;
}
```

## 🎯 Aplicações Fundamentais

### 1. Algoritmos de Ordenação
- **Merge Sort**: Divisão e conquista O(n log n)
- **Quick Sort**: Particionamento recursivo

### 2. Estruturas de Dados
- **Travessia de Árvores**: Pré-ordem, In-ordem, Pós-ordem
- **Operações em Grafos**: DFS (Busca em Profundidade)

### 3. Problemas Clássicos
- **Torres de Hanoi**: 2ⁿ - 1 movimentos
- **Problema das N Rainhas**: Backtracking
- **Fibonacci**: Sequência recursiva natural

### 4. Parsing e Compiladores
- **Análise Sintática**: Descendente recursivo
- **Avaliação de Expressões**: Árvores de expressão

## 📖 Referências Bibliográficas

1. **Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C.** (2009). *Introduction to Algorithms* (3rd ed.). MIT Press. Capítulos 2 e 4.

2. **Knuth, D. E.** (1997). *The Art of Computer Programming, Vol. 1: Fundamental Algorithms* (3rd ed.). Addison-Wesley. Seção 1.2.

3. **Sedgewick, R., & Wayne, K.** (2011). *Algorithms* (4th ed.). Addison-Wesley. Capítulo 2.

4. **Abelson, H., & Sussman, G. J.** (1996). *Structure and Interpretation of Computer Programs* (2nd ed.). MIT Press.

5. **McCarthy, J.** (1960). Recursive functions of symbolic expressions and their computation by machine. *Communications of the ACM*, 3(4), 184-195.

## 🔗 Próximo Tópico

→ **[02-algoritmo-divisao-conquista](../02-algoritmo-divisao-conquista/)**: Paradigma de Divisão e Conquista

---

*Este material faz parte do curso de Estrutura de Dados em C.*
