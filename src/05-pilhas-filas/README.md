# Pilhas e Filas em C

## 📋 Visão Geral

Pilhas (stacks) e filas (queues) são estruturas de dados lineares fundamentais que seguem princípios específicos de inserção e remoção de elementos. Este módulo apresenta implementações completas dessas estruturas em C, explorando suas características, aplicações e variações.

### Contexto Histórico e Importância

As estruturas de dados pilhas e filas emergiram naturalmente durante o desenvolvimento inicial da ciência da computação na década de 1940-1950:

- **Pilhas**: A primeira implementação explícita em hardware foi na **Burroughs B5000** (1961), um dos primeiros computadores baseados em arquitetura de pilha (*stack machine*). Alan Turing já havia sugerido a necessidade de armazenamento hierárquico de estado em seus trabalhos teóricos. Linguagens como **Forth** (1970) e **PostScript** (1982) usam pilhas como mecanismo central de execução.

- **Filas**: Surgiram inicialmente para modelar sistemas de escalonamento e buffer em sistemas operacionais primitivos. O conceito de **FIFO** (First In, First Out) é fundamental para entender fluxos de dados em sistemas computacionais desde os primórdios da computação.

Estas estruturas são cruciais porque:

1. **Modelam comportamentos naturais**: Pilhas representam processos hierárquicos reversíveis (como chamadas de função), enquanto filas modelam processos sequenciais de atendimento.

2. **Base para algoritmos fundamentais**: Pilhas são essenciais para DFS (Depth-First Search) e avaliação de expressões; filas são fundamentais para BFS (Breadth-First Search) e sistemas de escalonamento.

3. **Eficiência computacional**: Ambas oferecem operações em tempo constante O(1), tornando-as ideais para cenários onde desempenho é crítico.

4. **Fundamento teórico**: Pilhas são base para **Autômatos com Pilha** (Pushdown Automata - PDA), usados na teoria de linguagens formais e compiladores.

## 📚 Conceitos Fundamentais

### 🥞 Pilha (Stack)

#### Definição Formal

Uma pilha é uma **estrutura de dados abstrata** (ADT - Abstract Data Type) que implementa o princípio **LIFO** (Last In, First Out), onde o último elemento inserido é o primeiro a ser removido. Matematicamente, podemos modelar uma pilha como uma sequência ordenada:

$$S = [s_1, s_2, \ldots, s_n]$$

onde $s_n$ é o **topo** da pilha e $s_1$ é a **base**.

#### Fundamentação Teórica

**Por que pilhas são importantes na computação?**

1. **Localidade de Referência**: O último dado inserido é o primeiro a ser removido, o que é excelente para cache e eficiência de memória, pois os dados recentemente acessados têm alta probabilidade de serem acessados novamente.

2. **Modelagem Hierárquica**: Pilhas modelam naturalmente fluxos hierárquicos e temporais. Ao empilhar chamadas de funções, caminhamos em uma árvore de decisão de forma controlada, permitindo backtracking eficiente.

3. **Teoria dos Autômatos**: Pilhas são base para **Autômatos com Pilha** (Pushdown Automata - PDA), máquinas teóricas capazes de reconhecer **linguagens livres de contexto**. Formalmente:

$$\text{PDA} = (Q, \Sigma, \Gamma, \delta, q_0, Z_0, F)$$

onde:
- $Q$: conjunto de estados
- $\Sigma$: alfabeto de entrada
- $\Gamma$: alfabeto da pilha
- $\delta$: função de transição $Q \times (\Sigma \cup \{\epsilon\}) \times \Gamma \rightarrow \mathcal{P}(Q \times \Gamma^*)$
- $q_0$: estado inicial
- $Z_0$: símbolo inicial da pilha
- $F$: conjunto de estados finais

Esta estrutura formal é fundamental para **análise sintática de linguagens de programação** e **teoria da computação**.

#### Características Principais

- **Topo (Top)**: Posição do último elemento inserido, única posição acessível diretamente
- **Base**: Primeira posição da pilha, acessível apenas quando a pilha contém um único elemento
- **Capacidade**: Número máximo de elementos (em implementações com tamanho fixo)
- **Tamanho Atual**: Número de elementos presentes na pilha em um dado momento
- **Restrição de Acesso**: Não é possível acessar elementos no meio da pilha sem remover os elementos acima

#### Propriedades Fundamentais

1. **Ordem Estrita**: Só é possível acessar o **último** elemento inserido
2. **Restrição de Acesso**: Não se pode "pular" elementos intermediários
3. **Operações em Tempo Constante**: Push e pop são realizadas em $O(1)$
4. **Invariante**: Após $k$ operações push seguidas de $j$ operações pop (onde $j \leq k$), os primeiros $k-j$ elementos inseridos permanecem na pilha na ordem original

#### Operações Fundamentais

- **Push(x)**: Inserir elemento $x$ no topo da pilha
  - Pré-condição: Pilha não está cheia (em implementações com tamanho fixo)
  - Pós-condição: Tamanho aumenta em 1, $x$ torna-se o novo topo
  - Complexidade: $O(1)$

- **Pop()**: Remover e retornar o elemento do topo
  - Pré-condição: Pilha não está vazia
  - Pós-condição: Tamanho diminui em 1, elemento anterior ao topo torna-se o novo topo
  - Complexidade: $O(1)$

- **Top/Peek()**: Visualizar elemento do topo sem remover
  - Pré-condição: Pilha não está vazia
  - Pós-condição: Estado da pilha permanece inalterado
  - Complexidade: $O(1)$

- **IsEmpty()**: Verificar se a pilha está vazia
  - Retorna verdadeiro se tamanho = 0
  - Complexidade: $O(1)$

- **IsFull()**: Verificar se a pilha está cheia (apenas para implementações com tamanho fixo)
  - Retorna verdadeiro se tamanho = capacidade
  - Complexidade: $O(1)$

### 🚶 Fila (Queue)

#### Definição Formal

Uma fila é uma **estrutura de dados abstrata** que implementa o princípio **FIFO** (First In, First Out), onde o primeiro elemento inserido é o primeiro a ser removido. Matematicamente, podemos representar uma fila como:

$$Q = [q_1, q_2, \ldots, q_n]$$

onde $q_1$ é a **frente** (front) e $q_n$ é a **traseira** (rear) da fila.

#### Fundamentação Teórica

**Por que filas são importantes na computação?**

1. **Modelagem de Processos Sequenciais**: Filas modelam naturalmente sistemas de atendimento, buffers e pipelines, refletindo a ordem de chegada dos elementos.

2. **Justiça e Equidade**: O princípio FIFO garante que nenhum elemento será "pulado", implementando um conceito de justiça no processamento.

3. **Algoritmos de Grafos**: Filas são fundamentais para algoritmos de busca em largura (BFS), que exploram grafos camada por camada, garantindo o caminho mais curto em grafos não ponderados.

4. **Teoria de Filas**: Campo matemático completo (Queueing Theory) desenvolvido por Agner Krarup Erlang (1909) para analisar sistemas de telecomunicações. Usa processos estocásticos para modelar:
   - Taxa de chegada ($\lambda$)
   - Taxa de atendimento ($\mu$)
   - Utilização do sistema ($\rho = \lambda / \mu$)
   - Tempo médio de espera (Lei de Little: $L = \lambda W$)

5. **Sistemas Distribuídos**: Message queues são fundamentais em arquiteturas modernas (RabbitMQ, Kafka, SQS), permitindo comunicação assíncrona entre componentes.

#### Características Principais

- **Frente (Front)**: Posição do primeiro elemento, onde ocorrem as remoções
- **Traseira (Rear)**: Posição do último elemento, onde ocorrem as inserções
- **Capacidade**: Número máximo de elementos (em implementações com tamanho fixo)
- **Tamanho Atual**: Número de elementos presentes na fila
- **Acesso Restrito**: Apenas as extremidades (frente e traseira) são acessíveis diretamente

#### Propriedades Fundamentais

1. **Ordem de Chegada**: Elementos são removidos na mesma ordem em que foram inseridos
2. **Acesso Dual**: Inserções ocorrem em uma extremidade, remoções em outra
3. **Operações em Tempo Constante**: Enqueue e dequeue são $O(1)$
4. **Invariante**: Para qualquer sequência de operações, se $x$ foi inserido antes de $y$, então $x$ será removido antes de $y$ (desde que ambos permaneçam na fila)

#### Operações Fundamentais

- **Enqueue(x)**: Inserir elemento $x$ na traseira da fila
  - Pré-condição: Fila não está cheia
  - Pós-condição: Tamanho aumenta em 1, $x$ torna-se o novo elemento da traseira
  - Complexidade: $O(1)$

- **Dequeue()**: Remover e retornar o elemento da frente
  - Pré-condição: Fila não está vazia
  - Pós-condição: Tamanho diminui em 1, próximo elemento torna-se a nova frente
  - Complexidade: $O(1)$

- **Front()**: Visualizar primeiro elemento sem remover
  - Pré-condição: Fila não está vazia
  - Pós-condição: Estado da fila permanece inalterado
  - Complexidade: $O(1)$

- **IsEmpty()**: Verificar se a fila está vazia
  - Retorna verdadeiro se tamanho = 0
  - Complexidade: $O(1)$

- **IsFull()**: Verificar se a fila está cheia (apenas para implementações com tamanho fixo)
  - Retorna verdadeiro se tamanho = capacidade
  - Complexidade: $O(1)$

#### Problema do "Falso Overflow" em Filas Lineares

Em implementações com array linear, pode ocorrer uma situação onde a fila indica estar cheia, mas existem posições vazias no início do array (após várias operações de dequeue). Este é o **falso overflow**.

**Solução: Fila Circular**

A fila circular usa aritmética modular para "conectar" o final do array ao início:
- Índice da traseira: $(rear + 1) \mod capacity$
- Índice da frente: $(front + 1) \mod capacity$

Isso permite reutilizar espaços liberados no início do array, eliminando o falso overflow e mantendo operações $O(1)$.

## 🗂️ Estrutura dos Arquivos

### Implementações de Pilha
```
pilhas/
├── pilha_array.c          # Implementação com array estático
├── pilha_dinamica.c       # Implementação com alocação dinâmica
├── pilha_lista.c          # Implementação com lista ligada
└── exemplos_pilha.c       # Exemplos práticos de uso
```

### Implementações de Fila
```
filas/
├── fila_array.c           # Implementação com array estático
├── fila_circular.c        # Fila circular otimizada
├── fila_dinamica.c        # Implementação com alocação dinâmica
├── fila_lista.c           # Implementação com lista ligada
└── exemplos_fila.c        # Exemplos práticos de uso
```

## 🔧 Implementações Disponíveis

### Pilha com Array Estático
```c
typedef struct {
    int items[MAX_SIZE];
    int top;
} Stack;

// Operações básicas
void push(Stack* s, int item);
int pop(Stack* s);
int peek(Stack* s);
bool isEmpty(Stack* s);
bool isFull(Stack* s);
```

### Fila Circular
```c
typedef struct {
    int items[MAX_SIZE];
    int front;
    int rear;
    int count;
} CircularQueue;

// Operações básicas
void enqueue(CircularQueue* q, int item);
int dequeue(CircularQueue* q);
int front(CircularQueue* q);
bool isEmpty(CircularQueue* q);
bool isFull(CircularQueue* q);
```

## 📊 Comparação de Implementações

| Implementação | Inserção | Remoção | Espaço | Vantagens | Desvantagens |
|---------------|----------|---------|---------|-----------|--------------|
| Array Estático | O(1) | O(1) | O(n) | Simples, rápida | Tamanho fixo |
| Array Dinâmico | O(1)* | O(1) | O(n) | Tamanho flexível | Realocação custosa |
| Lista Ligada | O(1) | O(1) | O(n) | Sem limite pré-definido | Overhead de ponteiros |
| Fila Circular | O(1) | O(1) | O(n) | Eficiente em espaço | Implementação complexa |

*Amortizado

## 🚀 Aplicações Práticas

Esta seção explora as aplicações de pilhas e filas em diversos contextos, desde fundamentos teóricos até sistemas reais de produção.

### Aplicações de Pilhas

#### 1. Controle de Chamadas de Função (Call Stack)

**Contexto Acadêmico:**

A pilha de chamadas é um mecanismo fundamental em todas as linguagens de programação modernas. Quando uma função é chamada, o sistema cria um **activation record** (registro de ativação) contendo:

- **Parâmetros da função**: Valores passados para a função
- **Variáveis locais**: Espaço para variáveis declaradas na função
- **Endereço de retorno**: Onde continuar após a função terminar
- **Frame pointer anterior**: Para reconstruir o frame do chamador
- **Valores salvos de registradores**: Estado da CPU

**Estrutura do Activation Record:**

```c
typedef struct {
    void* return_address;      // Onde retornar
    void* frame_pointer;       // Base do frame anterior
    int parameters[MAX_PARAMS]; // Parâmetros da função
    int local_vars[MAX_LOCALS]; // Variáveis locais
    int saved_registers[8];    // Estado dos registradores
} ActivationRecord;
```

**Por que LIFO?**

O princípio LIFO é perfeito para chamadas de função porque:
1. A última função chamada (mais recente) deve retornar primeiro
2. O retorno segue o caminho inverso das chamadas
3. Cada nível de recursão adiciona uma nova camada que será removida ao retornar

**Exemplo de Recursão:**

```c
int fibonacci(int n) {
    // Frame 1 é empilhado
    if (n <= 1) return n;
    
    // Frame 2 para fib(n-1) é empilhado
    int a = fibonacci(n - 1);
    
    // Frame 2 retorna (desempilha), Frame 3 para fib(n-2) é empilhado
    int b = fibonacci(n - 2);
    
    // Frame 3 retorna (desempilha)
    return a + b;
    // Frame 1 retorna (desempilha)
}

// Chamada fibonacci(4):
// Stack: [fib(4)]
// Stack: [fib(4), fib(3)]
// Stack: [fib(4), fib(3), fib(2)]
// Stack: [fib(4), fib(3), fib(2), fib(1)] ← mais profundo
// Stack: [fib(4), fib(3), fib(2)] ← fib(1) retornou
// ... e assim por diante
```

**Profundidade da Pilha:**

Cada chamada recursiva consome espaço na pilha. Stack overflow ocorre quando:
- Recursão muito profunda
- Recursão infinita (sem caso base)
- Variáveis locais muito grandes

**Stack Overflow Example:**

```c
void infiniteRecursion(int n) {
    int bigArray[10000];  // Consome ~40KB por chamada
    infiniteRecursion(n + 1);  // Sem condição de parada!
}
// Stack size típico: 1-8 MB
// Overflow após ~25-200 chamadas
```

**Tail Call Optimization:**

Compiladores modernos podem otimizar recursão de cauda:

```c
// Recursão de cauda (otimizável)
int factorial_tail(int n, int acc) {
    if (n == 0) return acc;
    return factorial_tail(n - 1, n * acc);  // Última operação é chamada
}

// Compilador pode transformar em loop:
int factorial_tail_optimized(int n, int acc) {
    while (n != 0) {
        acc = n * acc;
        n = n - 1;
    }
    return acc;
}
```

**Aplicações Reais:**
- Todos os programas usam call stack implicitamente
- Debuggers (GDB, LLDB) inspecionam a pilha: comando `backtrace`
- Exception handling: unwinding the stack
- Profilers analisam hot paths na pilha

#### 2. Avaliação de Expressões Matemáticas

**Contexto Teórico:**

Expressões matemáticas podem ser representadas em três notações:

1. **Infixa**: Operador entre operandos - `3 + 4 * 2`
2. **Pós-fixa (RPN)**: Operador após operandos - `3 4 2 * +`
3. **Pré-fixa (Polonesa)**: Operador antes operandos - `+ 3 * 4 2`

**Por que notação pós-fixa?**
- Não requer parênteses
- Avaliação unambígua
- Implementação simples com pilha
- Usado em calculadoras HP, linguagens como PostScript e Forth

**Algoritmo de Avaliação (RPN):**

```c
int evaluateRPN(char* expression) {
    Stack s;
    initStack(&s);
    
    char* token = strtok(expression, " ");
    while (token != NULL) {
        if (isNumber(token)) {
            // Empilha operando
            push(&s, atoi(token));
        } else {
            // Desempilha dois operandos
            int b = pop(&s);  // Segundo operando
            int a = pop(&s);  // Primeiro operando
            
            // Calcula resultado
            int result;
            switch (token[0]) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = a / b; break;
            }
            
            // Empilha resultado
            push(&s, result);
        }
        token = strtok(NULL, " ");
    }
    
    // Resultado final no topo
    return pop(&s);
}

// Exemplo: "3 4 2 * +"
// Stack: [3]
// Stack: [3, 4]
// Stack: [3, 4, 2]
// Stack: [3, 8]      ← 4 * 2 = 8
// Stack: [11]        ← 3 + 8 = 11
// Resultado: 11
```

**Análise de Complexidade:**
- Cada token processado uma vez: O(n)
- Cada operação de pilha: O(1)
- **Total: Θ(n)** onde n = número de tokens

**Conversão Infixa → Pós-fixa (Shunting Yard Algorithm):**

Algoritmo de Dijkstra para conversão:

```c
char* infixToPostfix(char* infix) {
    Stack operators;
    initStack(&operators);
    char* postfix = malloc(strlen(infix) * 2);
    int pos = 0;
    
    for (int i = 0; infix[i]; i++) {
        char c = infix[i];
        
        if (isdigit(c)) {
            // Operando vai direto para saída
            postfix[pos++] = c;
            postfix[pos++] = ' ';
        }
        else if (c == '(') {
            // Abre parênteses empilha
            push(&operators, c);
        }
        else if (c == ')') {
            // Fecha parênteses: desempilha até encontrar '('
            while (!isEmpty(&operators) && peek(&operators) != '(') {
                postfix[pos++] = pop(&operators);
                postfix[pos++] = ' ';
            }
            pop(&operators);  // Remove '('
        }
        else if (isOperator(c)) {
            // Operador: desempilha operadores de maior ou igual precedência
            while (!isEmpty(&operators) && 
                   precedence(peek(&operators)) >= precedence(c)) {
                postfix[pos++] = pop(&operators);
                postfix[pos++] = ' ';
            }
            push(&operators, c);
        }
    }
    
    // Desempilha operadores restantes
    while (!isEmpty(&operators)) {
        postfix[pos++] = pop(&operators);
        postfix[pos++] = ' ';
    }
    
    postfix[pos] = '\0';
    return postfix;
}

int precedence(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3;
        default: return 0;
    }
}

// Exemplo: "3 + 4 * 2"
// Output: "3 4 2 * +"
```

**Aplicações Reais:**
- Calculadoras científicas (HP RPN)
- Compiladores: parsing de expressões
- Interpretadores: avaliação de expressões
- Linguagens de programação: operador de precedência

#### 3. Verificação de Parênteses Balanceados

**Problema Formal:**

Dada uma string contendo caracteres `()[]{}`, determinar se os parênteses estão balanceados.

**Definição Matemática:**

Uma string S de parênteses é balanceada se:
1. String vazia é balanceada
2. Se A é balanceada, então `(A)`, `[A]`, `{A}` são balanceadas
3. Se A e B são balanceadas, então AB é balanceada

**Gramática Livre de Contexto:**

```
S → ε              (vazio)
S → (S)            (parênteses ao redor)
S → [S]
S → {S}
S → SS             (concatenação)
```

**Algoritmo com Pilha:**

```c
bool isBalanced(char* expression) {
    Stack s;
    initStack(&s);
    
    for (int i = 0; expression[i]; i++) {
        char c = expression[i];
        
        // Abre: empilha
        if (c == '(' || c == '[' || c == '{') {
            push(&s, c);
        }
        // Fecha: verifica correspondência
        else if (c == ')' || c == ']' || c == '}') {
            if (isEmpty(&s)) return false;  // Fecha sem abrir
            
            char top = pop(&s);
            if (!isMatchingPair(top, c)) {
                return false;  // Tipo incompatível
            }
        }
    }
    
    return isEmpty(&s);  // Deve ter consumido todos
}

bool isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}

// Exemplos:
// "()" → true
// "()[]{}" → true
// "(]" → false (tipo incompatível)
// "(()" → false (não vazio ao final)
// "())" → false (fecha sem abrir)
```

**Prova de Correção:**

**Teorema:** O algoritmo retorna verdadeiro sse a string é balanceada.

**Prova (⇒):** Se algoritmo retorna verdadeiro, então balanceada.
- Algoritmo retorna verdadeiro apenas se pilha vazia ao final
- Cada 'fecha' foi pareado com 'abre' correspondente
- Logo, estrutura está balanceada ∎

**Prova (⇐):** Se balanceada, então algoritmo retorna verdadeiro.
- Por indução na estrutura da gramática:
  - Base (ε): pilha vazia, retorna verdadeiro ✓
  - Passo ((S)): empilha '(', processa S recursivamente, desempilha ao encontrar ')'
  - Passo (SS): processa S₁, depois S₂, ambos mantêm invariante ∎

**Complexidade:**
- Tempo: **Θ(n)** - percorre string uma vez
- Espaço: **O(n)** - no pior caso (string com apenas 'abre')

**Extensão: Verificação de Sintaxe de Código:**

```c
bool validateCodeSyntax(char* code) {
    Stack s;
    initStack(&s);
    bool inString = false;
    bool inComment = false;
    
    for (int i = 0; code[i]; i++) {
        // Tratar strings e comentários
        if (code[i] == '"' && code[i-1] != '\\') {
            inString = !inString;
            continue;
        }
        if (inString || inComment) continue;
        
        // Verificar balanceamento
        if (code[i] == '{' || code[i] == '(' || code[i] == '[') {
            push(&s, code[i]);
        }
        else if (code[i] == '}' || code[i] == ')' || code[i] == ']') {
            if (isEmpty(&s)) return false;
            char top = pop(&s);
            if (!isMatchingPair(top, code[i])) return false;
        }
    }
    
    return isEmpty(&s);
}
```

**Aplicações Reais:**
- IDEs: verificação de sintaxe em tempo real
- Linters: validação de código
- Compiladores: análise léxica e sintática
- Editores de texto: bracket matching

#### 4. Busca em Profundidade (DFS) em Grafos

**Fundamento Teórico:**

DFS é um algoritmo fundamental para exploração de grafos que visita vértices o mais profundamente possível antes de fazer backtracking.

**Propriedades do DFS:**
1. Explora um ramo completamente antes de explorar outro
2. Usa pilha (implícita via recursão ou explícita)
3. Tempo de execução: Θ(V + E)
4. Espaço: O(V) para pilha + visitados

**DFS Recursivo (Pilha Implícita):**

```c
void dfsRecursive(Graph* g, int v, bool visited[]) {
    // Marca como visitado
    visited[v] = true;
    printf("%d ", v);
    
    // Visita todos vizinhos não visitados
    for (int i = 0; i < g->adjListSize[v]; i++) {
        int w = g->adjList[v][i];
        if (!visited[w]) {
            dfsRecursive(g, w, visited);  // Chamada recursiva empilha
        }
    }
    // Retorno desempilha automaticamente
}
```

**DFS Iterativo (Pilha Explícita):**

```c
void dfsIterative(Graph* g, int start) {
    bool visited[MAX_VERTICES] = {false};
    Stack s;
    initStack(&s);
    
    push(&s, start);
    
    while (!isEmpty(&s)) {
        int v = pop(&s);
        
        if (!visited[v]) {
            visited[v] = true;
            printf("%d ", v);
            
            // Empilha vizinhos não visitados
            // (em ordem reversa para manter mesma ordem que recursão)
            for (int i = g->adjListSize[v] - 1; i >= 0; i--) {
                int w = g->adjList[v][i];
                if (!visited[w]) {
                    push(&s, w);
                }
            }
        }
    }
}
```

**Aplicações do DFS:**

1. **Detecção de Ciclos:**
```c
bool hasCycleDFS(Graph* g, int v, bool visited[], bool recStack[]) {
    visited[v] = true;
    recStack[v] = true;  // Marca como na pilha de recursão
    
    for (int i = 0; i < g->adjListSize[v]; i++) {
        int w = g->adjList[v][i];
        
        if (!visited[w]) {
            if (hasCycleDFS(g, w, visited, recStack))
                return true;
        }
        else if (recStack[w]) {
            return true;  // Encontrou vértice na pilha atual = ciclo!
        }
    }
    
    recStack[v] = false;  // Remove da pilha de recursão
    return false;
}
```

2. **Ordenação Topológica:**
```c
void topologicalSortUtil(Graph* g, int v, bool visited[], Stack* result) {
    visited[v] = true;
    
    // Visita todos vizinhos primeiro
    for (int i = 0; i < g->adjListSize[v]; i++) {
        int w = g->adjList[v][i];
        if (!visited[w]) {
            topologicalSortUtil(g, w, visited, result);
        }
    }
    
    // Empilha vértice após visitar todos descendentes
    push(result, v);  // Ordem reversa de finalização
}

void topologicalSort(Graph* g) {
    bool visited[MAX_VERTICES] = {false};
    Stack result;
    initStack(&result);
    
    for (int v = 0; v < g->numVertices; v++) {
        if (!visited[v]) {
            topologicalSortUtil(g, v, visited, &result);
        }
    }
    
    // Desempilha para obter ordem topológica
    while (!isEmpty(&result)) {
        printf("%d ", pop(&result));
    }
}
```

3. **Componentes Fortemente Conexas (Algoritmo de Tarjan):**
```c
void tarjanSCC(Graph* g, int v, int disc[], int low[], 
               bool onStack[], Stack* s, int* time) {
    disc[v] = low[v] = ++(*time);
    push(s, v);
    onStack[v] = true;
    
    for (int i = 0; i < g->adjListSize[v]; i++) {
        int w = g->adjList[v][i];
        
        if (disc[w] == -1) {
            tarjanSCC(g, w, disc, low, onStack, s, time);
            low[v] = min(low[v], low[w]);
        }
        else if (onStack[w]) {
            low[v] = min(low[v], disc[w]);
        }
    }
    
    // Se v é raiz de SCC
    if (low[v] == disc[v]) {
        printf("SCC: ");
        int w;
        do {
            w = pop(s);
            onStack[w] = false;
            printf("%d ", w);
        } while (w != v);
        printf("\n");
    }
}
```

**Aplicações Reais:**
- Compiladores: análise de dependências
- Roteamento: encontrar caminhos em redes
- Puzzle solving: labirintos, Sudoku
- Web crawling: exploração de links
- Game AI: busca de caminhos

#### 5. Outras Aplicações Importantes de Pilhas

**5.1 Parsing e Compiladores:**

```c
// Parser de expressões usando pilha
ASTNode* parseExpression(Token tokens[]) {
    Stack operands;
    Stack operators;
    
    for (int i = 0; tokens[i].type != END; i++) {
        if (tokens[i].type == NUMBER) {
            ASTNode* node = createNode(tokens[i].value);
            push(&operands, node);
        }
        else if (tokens[i].type == OPERATOR) {
            while (!isEmpty(&operators) && 
                   precedence(peek(&operators)) >= precedence(tokens[i])) {
                processOperator(&operands, &operators);
            }
            push(&operators, tokens[i]);
        }
    }
    
    while (!isEmpty(&operators)) {
        processOperator(&operands, &operators);
    }
    
    return pop(&operands);
}
```

**5.2 Backtracking (N-Queens Problem):**

```c
void solveNQueens(int board[], int row, int n, Stack* solution) {
    if (row == n) {
        printSolution(solution);
        return;
    }
    
    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col, n)) {
            push(solution, col);  // Tenta colocar rainha
            board[row] = col;
            
            solveNQueens(board, row + 1, n, solution);
            
            pop(solution);  // Backtrack
            board[row] = -1;
        }
    }
}
```

**5.3 Function Call Tracing:**

```c
// Tracer para debugging
Stack callStack;

void enterFunction(char* funcName) {
    push(&callStack, funcName);
    printf("-> Entering: %s (depth: %d)\n", 
           funcName, stackSize(&callStack));
}

void exitFunction() {
    char* funcName = pop(&callStack);
    printf("<- Exiting: %s (depth: %d)\n", 
           funcName, stackSize(&callStack));
}
```

### Aplicações de Filas

#### 1. Sistemas Operacionais - Escalonamento de Processos

**Contexto Teórico:**

Sistemas operacionais usam filas para implementar políticas de escalonamento justas. O princípio FIFO garante que processos sejam atendidos na ordem de chegada.

**Round-Robin Scheduling:**

```c
typedef struct {
    int pid;              // Process ID
    int burstTime;        // Tempo de CPU necessário
    int remainingTime;    // Tempo restante
    int arrivalTime;      // Quando chegou
    int priority;         // Prioridade
} Process;

void roundRobinScheduler(Process processes[], int n, int quantum) {
    Queue readyQueue;
    initQueue(&readyQueue);
    
    int currentTime = 0;
    int completed = 0;
    
    // Enfileira processos que chegaram
    for (int i = 0; i < n; i++) {
        if (processes[i].arrivalTime == 0) {
            enqueue(&readyQueue, &processes[i]);
        }
    }
    
    while (completed < n) {
        if (isEmpty(&readyQueue)) {
            currentTime++;
            continue;
        }
        
        Process* current = dequeue(&readyQueue);
        
        printf("Time %d: Running process %d\n", currentTime, current->pid);
        
        // Executa por quantum ou até terminar
        int executeTime = min(quantum, current->remainingTime);
        current->remainingTime -= executeTime;
        currentTime += executeTime;
        
        // Enfileira novos processos que chegaram
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && 
                processes[i].remainingTime > 0 &&
                !inQueue(&readyQueue, &processes[i])) {
                enqueue(&readyQueue, &processes[i]);
            }
        }
        
        // Re-enfileira se não terminou
        if (current->remainingTime > 0) {
            enqueue(&readyQueue, current);
        } else {
            completed++;
            printf("Process %d completed at time %d\n", 
                   current->pid, currentTime);
        }
    }
}
```

**Análise de Performance:**

Para n processos com quantum q:
- Tempo médio de resposta: depende da política
- Overhead de context switch: O(1) por troca
- Fairness: garantida pelo FIFO

**5.4 Multi-level Feedback Queue:**

```c
#define NUM_LEVELS 3

typedef struct {
    Queue queues[NUM_LEVELS];  // Múltiplas filas de prioridade
    int quantum[NUM_LEVELS];   // Quantum por nível
} MLFQ;

void initMLFQ(MLFQ* mlfq) {
    for (int i = 0; i < NUM_LEVELS; i++) {
        initQueue(&mlfq->queues[i]);
        mlfq->quantum[i] = (1 << i);  // Quantum dobra a cada nível
    }
}

void scheduleMFLQ(MLFQ* mlfq) {
    // Processa filas em ordem de prioridade
    for (int level = 0; level < NUM_LEVELS; level++) {
        if (!isEmpty(&mlfq->queues[level])) {
            Process* p = dequeue(&mlfq->queues[level]);
            
            int executeTime = min(mlfq->quantum[level], p->remainingTime);
            p->remainingTime -= executeTime;
            
            if (p->remainingTime > 0) {
                // Move para próximo nível (menor prioridade)
                int nextLevel = min(level + 1, NUM_LEVELS - 1);
                enqueue(&mlfq->queues[nextLevel], p);
            }
            
            break;  // Processa apenas um processo por vez
        }
    }
}
```

**Aplicações Reais:**
- Linux CFS (Completely Fair Scheduler)
- Windows Thread Scheduler
- MacOS Dispatcher

#### 2. Busca em Largura (BFS) em Grafos

**Fundamento Teórico:**

BFS explora grafos camada por camada, garantindo o caminho mais curto em grafos não ponderados.

**Teorema:** BFS encontra o caminho mais curto de s para todos vértices alcançáveis.

**Prova:** Por indução na distância:
- Base: distância 0 (vértice inicial) está correto
- Hipótese: todos vértices a distância ≤ k foram descobertos corretamente
- Passo: vértices a distância k+1 são descobertos quando processamos vértices a distância k
- FIFO garante que processamos todos de distância k antes de k+1 ∎

**Implementação Completa:**

```c
void bfs(Graph* g, int start, int distance[], int parent[]) {
    bool visited[MAX_VERTICES] = {false};
    Queue q;
    initQueue(&q);
    
    // Inicializa distâncias
    for (int i = 0; i < g->numVertices; i++) {
        distance[i] = -1;  // Infinito
        parent[i] = -1;    // Sem pai
    }
    
    visited[start] = true;
    distance[start] = 0;
    enqueue(&q, start);
    
    while (!isEmpty(&q)) {
        int v = dequeue(&q);
        printf("Visitando %d (distância %d)\n", v, distance[v]);
        
        // Explora vizinhos
        for (int i = 0; i < g->adjListSize[v]; i++) {
            int w = g->adjList[v][i];
            
            if (!visited[w]) {
                visited[w] = true;
                distance[w] = distance[v] + 1;  // Distância correta!
                parent[w] = v;
                enqueue(&q, w);
            }
        }
    }
}

void printShortestPath(int parent[], int start, int dest) {
    if (dest == start) {
        printf("%d", start);
        return;
    }
    if (parent[dest] == -1) {
        printf("Sem caminho");
        return;
    }
    
    printShortestPath(parent, start, parent[dest]);
    printf(" -> %d", dest);
}
```

**Análise de Complexidade:**
- Tempo: **Θ(V + E)** - cada vértice enfileirado uma vez, cada aresta examinada uma vez
- Espaço: **O(V)** - fila + arrays visited/distance/parent

**Aplicações do BFS:**

**1. Caminho Mais Curto em Redes Sociais:**
```c
int degreesOfSeparation(SocialNetwork* net, int person1, int person2) {
    int distance[MAX_PEOPLE];
    bfs(net->graph, person1, distance, NULL);
    return distance[person2];
}
// "Six degrees of separation"
```

**2. Web Crawler:**
```c
void crawlWeb(char* seedURL, int maxDepth) {
    Queue urlQueue;
    Set visited;
    
    enqueue(&urlQueue, seedURL);
    
    while (!isEmpty(&urlQueue) && depth <= maxDepth) {
        char* url = dequeue(&urlQueue);
        
        if (contains(&visited, url)) continue;
        add(&visited, url);
        
        Page* page = fetchPage(url);
        processPage(page);
        
        // Enfileira todos links da página
        for (int i = 0; i < page->numLinks; i++) {
            if (!contains(&visited, page->links[i])) {
                enqueue(&urlQueue, page->links[i]);
            }
        }
    }
}
```

**3. Componentes Conexas:**
```c
int countConnectedComponents(Graph* g) {
    bool visited[MAX_VERTICES] = {false};
    int components = 0;
    
    for (int v = 0; v < g->numVertices; v++) {
        if (!visited[v]) {
            components++;
            bfsMarkComponent(g, v, visited);
        }
    }
    
    return components;
}
```

#### 3. Simulações de Sistemas de Filas (Queueing Theory)

**Teoria de Filas (Erlang, 1909):**

Sistema de filas caracterizado por:
- **λ (lambda)**: Taxa de chegada (clientes/minuto)
- **μ (mu)**: Taxa de atendimento (clientes/minuto)
- **ρ (rho)**: Utilização = λ/μ

**Lei de Little:** L = λW
- L: número médio de clientes no sistema
- W: tempo médio de espera
- λ: taxa de chegada

**Simulação M/M/1 (Markovian/Markovian/1 server):**

```c
typedef struct {
    int customerId;
    double arrivalTime;
    double serviceTime;
} Customer;

typedef struct {
    double totalWaitTime;
    int customersServed;
    double serverIdleTime;
    double totalServiceTime;
} QueueStatistics;

void simulateMM1Queue(double lambda, double mu, double simTime) {
    Queue customerQueue;
    initQueue(&customerQueue);
    
    QueueStatistics stats = {0};
    double currentTime = 0;
    double nextArrival = exponentialRandom(1/lambda);
    bool serverBusy = false;
    double serviceEndTime = 0;
    
    while (currentTime < simTime) {
        // Próximo evento: chegada ou fim de serviço?
        if (nextArrival < serviceEndTime || !serverBusy) {
            // Evento: Chegada de cliente
            currentTime = nextArrival;
            
            Customer* c = malloc(sizeof(Customer));
            c->customerId = stats.customersServed++;
            c->arrivalTime = currentTime;
            c->serviceTime = exponentialRandom(1/mu);
            
            enqueue(&customerQueue, c);
            
            // Próxima chegada
            nextArrival = currentTime + exponentialRandom(1/lambda);
            
            // Se servidor livre, inicia atendimento
            if (!serverBusy) {
                Customer* serving = dequeue(&customerQueue);
                serverBusy = true;
                serviceEndTime = currentTime + serving->serviceTime;
                
                stats.totalWaitTime += (currentTime - serving->arrivalTime);
                stats.totalServiceTime += serving->serviceTime;
            }
        } else {
            // Evento: Fim de serviço
            currentTime = serviceEndTime;
            serverBusy = false;
            
            // Atende próximo cliente se houver
            if (!isEmpty(&customerQueue)) {
                Customer* serving = dequeue(&customerQueue);
                serverBusy = true;
                serviceEndTime = currentTime + serving->serviceTime;
                
                stats.totalWaitTime += (currentTime - serving->arrivalTime);
                stats.totalServiceTime += serving->serviceTime;
            } else {
                stats.serverIdleTime += (nextArrival - currentTime);
            }
        }
    }
    
    // Estatísticas
    printf("Clientes atendidos: %d\n", stats.customersServed);
    printf("Tempo médio de espera: %.2f\n", 
           stats.totalWaitTime / stats.customersServed);
    printf("Utilização do servidor: %.2f%%\n", 
           100 * (1 - stats.serverIdleTime / simTime));
    printf("Comprimento médio da fila: %.2f\n", 
           stats.totalWaitTime / simTime);  // Lei de Little
}

double exponentialRandom(double rate) {
    return -log(1.0 - (double)rand() / RAND_MAX) / rate;
}
```

**Aplicações Reais:**
- Call centers: dimensionar número de atendentes
- Servidores web: capacity planning
- Hospitais: gerenciamento de emergências
- Bancos: otimização de caixas

#### 4. Programação Assíncrona e Event Loops

**Event Loop (Node.js, JavaScript, Python asyncio):**

```c
typedef struct {
    void (*callback)(void*);
    void* data;
    double executeAt;
} Event;

typedef struct {
    Queue eventQueue;
    bool running;
} EventLoop;

void initEventLoop(EventLoop* loop) {
    initQueue(&loop->eventQueue);
    loop->running = false;
}

void scheduleEvent(EventLoop* loop, void (*callback)(void*), 
                   void* data, double delay) {
    Event* event = malloc(sizeof(Event));
    event->callback = callback;
    event->data = data;
    event->executeAt = getCurrentTime() + delay;
    
    enqueue(&loop->eventQueue, event);
}

void runEventLoop(EventLoop* loop) {
    loop->running = true;
    
    while (loop->running && !isEmpty(&loop->eventQueue)) {
        Event* event = dequeue(&loop->eventQueue);
        
        // Espera até tempo de execução
        double now = getCurrentTime();
        if (event->executeAt > now) {
            sleep(event->executeAt - now);
        }
        
        // Executa callback
        event->callback(event->data);
        
        free(event);
    }
}

// Exemplo de uso
void onTimeout(void* data) {
    printf("Timer expired: %s\n", (char*)data);
}

void onHTTPRequest(void* data) {
    HTTPRequest* req = (HTTPRequest*)data;
    processRequest(req);
}

int main() {
    EventLoop loop;
    initEventLoop(&loop);
    
    scheduleEvent(&loop, onTimeout, "First timer", 1.0);
    scheduleEvent(&loop, onHTTPRequest, request1, 0.5);
    scheduleEvent(&loop, onTimeout, "Second timer", 2.0);
    
    runEventLoop(&loop);
    
    return 0;
}
```

#### 5. Outras Aplicações Importantes de Filas

**5.1 Buffer de Impressão:**

```c
typedef struct {
    char* documentName;
    int pages;
    int priority;
    time_t submitTime;
} PrintJob;

void printSpooler() {
    Queue printQueue;
    initQueue(&printQueue);
    
    while (systemRunning) {
        // Adiciona novos trabalhos
        if (hasNewJob()) {
            PrintJob* job = getNewJob();
            enqueue(&printQueue, job);
            printf("Enfileirado: %s (%d páginas)\n", 
                   job->documentName, job->pages);
        }
        
        // Processa próximo trabalho
        if (!isEmpty(&printQueue) && printerReady()) {
            PrintJob* job = dequeue(&printQueue);
            printf("Imprimindo: %s\n", job->documentName);
            printDocument(job);
        }
        
        sleep(1);
    }
}
```

**5.2 Produtor-Consumidor com Fila:**

```c
Queue sharedQueue;
pthread_mutex_t lock;
pthread_cond_t notEmpty, notFull;

void* producer(void* arg) {
    while (running) {
        Item* item = produceItem();
        
        pthread_mutex_lock(&lock);
        while (isFull(&sharedQueue)) {
            pthread_cond_wait(&notFull, &lock);
        }
        
        enqueue(&sharedQueue, item);
        pthread_cond_signal(&notEmpty);
        pthread_mutex_unlock(&lock);
    }
}

void* consumer(void* arg) {
    while (running) {
        pthread_mutex_lock(&lock);
        while (isEmpty(&sharedQueue)) {
            pthread_cond_wait(&notEmpty, &lock);
        }
        
        Item* item = dequeue(&sharedQueue);
        pthread_cond_signal(&notFull);
        pthread_mutex_unlock(&lock);
        
        consumeItem(item);
    }
}
```

**5.3 Message Queues (RabbitMQ, Kafka style):**

```c
typedef struct {
    char* topic;
    char* message;
    int priority;
    time_t timestamp;
} Message;

typedef struct {
    Queue messageQueue;
    List subscribers;
    char* topicName;
} MessageTopic;

void publishMessage(MessageBroker* broker, char* topic, char* msg) {
    MessageTopic* t = findTopic(broker, topic);
    if (t == NULL) {
        t = createTopic(broker, topic);
    }
    
    Message* message = createMessage(topic, msg);
    enqueue(&t->messageQueue, message);
    
    notifySubscribers(t);
}

void subscribeToTopic(MessageBroker* broker, char* topic, 
                      void (*callback)(Message*)) {
    MessageTopic* t = findTopic(broker, topic);
    if (t == NULL) {
        t = createTopic(broker, topic);
    }
    
    addSubscriber(&t->subscribers, callback);
    
    // Processa mensagens pendentes
    while (!isEmpty(&t->messageQueue)) {
        Message* msg = dequeue(&t->messageQueue);
        callback(msg);
    }
}
```

**Aplicações Reais:**
- RabbitMQ, Apache Kafka: message brokers
- AWS SQS, Azure Queue Storage: cloud queues
- Redis: pub/sub system
- ZeroMQ: distributed messaging

## 🛠️ Como Compilar e Executar

### Compilação Individual
```bash
# Pilhas
gcc -o pilha_teste pilhas/pilha_array.c
gcc -o pilha_dinamica pilhas/pilha_dinamica.c

# Filas
gcc -o fila_teste filas/fila_array.c
gcc -o fila_circular filas/fila_circular.c
```

### Execução com Testes
```bash
./pilha_teste
./fila_teste
```

### Compilação com Debugging
```bash
gcc -g -Wall -o debug_pilha pilhas/pilha_array.c
gdb ./debug_pilha
```

## 🎯 Exemplos de Uso

### Verificação de Parênteses Balanceados
```c
bool isBalanced(char* expression) {
    Stack s;
    initStack(&s);
    
    for (int i = 0; expression[i]; i++) {
        if (expression[i] == '(' || expression[i] == '[' || expression[i] == '{') {
            push(&s, expression[i]);
        } else if (expression[i] == ')' || expression[i] == ']' || expression[i] == '}') {
            if (isEmpty(&s)) return false;
            char top = pop(&s);
            if (!isMatchingPair(top, expression[i])) return false;
        }
    }
    
    return isEmpty(&s);
}
```

### Simulação de Fila de Atendimento
```c
void simulateServiceQueue() {
    Queue serviceQueue;
    initQueue(&serviceQueue);
    
    // Adicionar clientes
    enqueue(&serviceQueue, 1); // Cliente 1
    enqueue(&serviceQueue, 2); // Cliente 2
    enqueue(&serviceQueue, 3); // Cliente 3
    
    // Atender clientes
    while (!isEmpty(&serviceQueue)) {
        int customer = dequeue(&serviceQueue);
        printf("Atendendo cliente %d\n", customer);
    }
}
```

## 🧠 Análise de Complexidade

Esta seção apresenta uma análise detalhada e rigorosa da complexidade computacional das operações em pilhas e filas, incluindo análise amortizada, trade-offs entre implementações e provas formais.

### Fundamentos de Análise de Complexidade

#### Notação Assintótica

- **O(f(n))** (Big O): Limite superior assintótico - descreve o pior caso
- **Ω(f(n))** (Big Omega): Limite inferior assintótico - descreve o melhor caso
- **Θ(f(n))** (Big Theta): Limite apertado - quando o pior e melhor caso coincidem

#### Análise Amortizada

A **análise amortizada** calcula o custo médio de uma operação em uma sequência de operações, distribuindo custos ocasionalmente altos por operações mais baratas. Existem três métodos principais:

1. **Método Agregado**: Calcula o custo total de $n$ operações e divide por $n$
2. **Método Contábil**: Atribui custos diferentes para diferentes operações
3. **Método Potencial**: Define uma função potencial que mede o "trabalho acumulado"

### Complexidade de Operações em Pilha

#### Implementação com Array Estático

**Estrutura:**
```c
typedef struct {
    int items[MAX_SIZE];
    int top;  // índice do topo, -1 se vazia
} Stack;
```

**Análise de Operações:**

| Operação | Complexidade Temporal | Complexidade Espacial | Justificativa |
|----------|----------------------|----------------------|---------------|
| Push | **Θ(1)** | O(1) | Incrementa `top` e atribui valor - operações primitivas constantes |
| Pop | **Θ(1)** | O(1) | Decrementa `top` e retorna valor - operações primitivas constantes |
| Peek | **Θ(1)** | O(1) | Acesso direto a `items[top]` - indexação de array é O(1) |
| IsEmpty | **Θ(1)** | O(1) | Compara `top == -1` - comparação primitiva |
| IsFull | **Θ(1)** | O(1) | Compara `top == MAX_SIZE - 1` - comparação primitiva |
| Busca | **O(n)** | O(1) | Pior caso: percorrer toda a pilha |
| Espaço Total | - | **Θ(n)** | Array pré-alocado de tamanho n |

**Prova Formal da Complexidade do Push:**

Seja $T(n)$ o tempo de execução de push em uma pilha de tamanho $n$:
1. Verificação `if (isFull(s))`: $c_1$ operações (constante)
2. Incremento `s->top++`: $c_2$ operações (constante)
3. Atribuição `s->items[s->top] = item`: $c_3$ operações (constante)

Portanto: $T(n) = c_1 + c_2 + c_3 = c$ (constante), logo $T(n) = \Theta(1)$

**Vantagens:**
- Implementação extremamente simples
- Máxima eficiência em tempo para operações básicas
- Boa localidade de cache (elementos contíguos na memória)
- Sem overhead de ponteiros

**Desvantagens:**
- Tamanho fixo definido em tempo de compilação
- Desperdício de memória se a capacidade não for totalmente utilizada
- Overflow se exceder capacidade

#### Implementação com Array Dinâmico

**Estrutura:**
```c
typedef struct {
    int* items;
    int top;
    int capacity;
} DynamicStack;
```

**Estratégia de Redimensionamento:**
Quando a pilha atinge capacidade máxima, duplicamos o tamanho:
```c
if (top == capacity - 1) {
    capacity *= 2;
    items = realloc(items, capacity * sizeof(int));
}
```

**Análise de Operações:**

| Operação | Complexidade (Pior Caso) | Complexidade (Amortizada) | Justificativa |
|----------|-------------------------|--------------------------|---------------|
| Push | **O(n)** | **Θ(1)** | Redimensionamento ocasional custa O(n), mas é raro |
| Pop | **Θ(1)** | **Θ(1)** | Sempre constante |
| Peek | **Θ(1)** | **Θ(1)** | Acesso direto |
| Espaço | - | **O(n)** | Array dinâmico |

**Análise Amortizada do Push (Método Agregado):**

Considere uma sequência de $n$ operações push em uma pilha inicialmente vazia com capacidade inicial $c_0 = 1$:

- Operações sem redimensionamento: custo unitário = 1
- Operações com redimensionamento: custo = tamanho atual + 1 (copiar + inserir)

Redimensionamentos ocorrem quando $top = 1, 2, 4, 8, 16, \ldots, 2^k$ onde $2^k < n$

Custo total de redimensionamentos: $1 + 2 + 4 + 8 + \ldots + 2^k = 2^{k+1} - 1 < 2n$

Custo total de $n$ operações: $n + 2n = 3n$

**Custo amortizado por operação: $\frac{3n}{n} = 3 = \Theta(1)$**

**Prova usando Método Potencial:**

Define função potencial: $\Phi(D) = 2 \cdot \text{size} - \text{capacity}$

- Após push sem redimensionamento: $\Phi$ aumenta em 2
- Custo real = 1, custo amortizado = $1 + 2 = 3$

- Após push com redimensionamento (dobra capacidade de $m$ para $2m$):
  - Custo real = $m + 1$ (copiar $m$ elementos + inserir 1)
  - $\Phi_{antes} = 2m - m = m$
  - $\Phi_{depois} = 2(m+1) - 2m = 2$
  - Custo amortizado = $(m + 1) + (2 - m) = 3 = \Theta(1)$

#### Implementação com Lista Ligada

**Estrutura:**
```c
typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
    int size;
} LinkedStack;
```

**Análise de Operações:**

| Operação | Complexidade Temporal | Complexidade Espacial | Justificativa |
|----------|----------------------|----------------------|---------------|
| Push | **Θ(1)** | O(1) | Inserção no início da lista |
| Pop | **Θ(1)** | O(1) | Remoção do início da lista |
| Peek | **Θ(1)** | O(1) | Acesso ao primeiro nó |
| Busca | **O(n)** | O(1) | Percorrer lista até encontrar |
| Espaço Total | - | **Θ(n)** | n nós, cada um com overhead de ponteiro |

**Vantagens:**
- Tamanho dinâmico sem necessidade de redimensionamento
- Sem limite pré-definido (apenas memória disponível)
- Não desperdiça espaço pré-alocado

**Desvantagens:**
- Overhead de memória: cada elemento requer espaço adicional para ponteiro (8 bytes em sistemas 64-bit)
- Pior localidade de cache (nós podem estar espalhados na memória)
- Fragmentação de memória
- Alocação dinâmica mais lenta que acesso a array

### Complexidade de Operações em Fila

#### Implementação com Array Linear (Ingênua)

**Problema: Falso Overflow**

```c
typedef struct {
    int items[MAX_SIZE];
    int front;  // índice da frente
    int rear;   // índice da traseira
} LinearQueue;
```

Após várias operações de dequeue, `front` avança, deixando espaços vazios no início do array que não podem ser reutilizados.

**Complexidade:**
- Enqueue: O(1) - desde que `rear < MAX_SIZE`
- Dequeue: O(1) - apenas incrementa `front`
- **Problema**: Fila pode indicar cheia (`rear == MAX_SIZE - 1`) mesmo com espaços vazios no início

**Esta implementação é academicamente importante apenas para entender o problema que a fila circular resolve.**

#### Implementação com Fila Circular

**Estrutura:**
```c
typedef struct {
    int items[MAX_SIZE];
    int front;
    int rear;
    int count;  // número de elementos
} CircularQueue;
```

**Aritmética Modular:**
- Próximo índice da traseira: `(rear + 1) % MAX_SIZE`
- Próximo índice da frente: `(front + 1) % MAX_SIZE`

**Análise de Operações:**

| Operação | Complexidade Temporal | Complexidade Espacial | Justificativa |
|----------|----------------------|----------------------|---------------|
| Enqueue | **Θ(1)** | O(1) | Atualização de índices com aritmética modular |
| Dequeue | **Θ(1)** | O(1) | Atualização de índices com aritmética modular |
| Front | **Θ(1)** | O(1) | Acesso direto a `items[front]` |
| Busca | **O(n)** | O(1) | Percorrer circularmente até encontrar |
| Espaço Total | - | **Θ(n)** | Array pré-alocado |

**Prova da Eliminação do Falso Overflow:**

Seja $n$ a capacidade da fila circular. Após $k$ operações enqueue e $j$ operações dequeue onde $k > n$ e $j > 0$:

- Fila linear: `rear = k`, pode indicar overflow mesmo se $k - j < n$
- Fila circular: `rear = k % n`, reutiliza posições liberadas por dequeue

Portanto, fila circular está cheia se e somente se `count == n`, eliminando o falso overflow.

**Vantagens:**
- Utilização completa do espaço alocado
- Operações O(1) garantidas
- Boa localidade de cache

**Desvantagens:**
- Lógica de implementação mais complexa (aritmética modular)
- Tamanho fixo

#### Implementação com Array Dinâmico

Similar à pilha, mas requer cuidado adicional ao redimensionar para manter a ordem FIFO:

**Análise:**
- Enqueue: **O(n)** pior caso, **Θ(1)** amortizado (mesma análise da pilha)
- Dequeue: **Θ(1)** sempre
- Redimensionamento requer cópia ordenada: custo O(n), mas amortizado O(1)

#### Implementação com Lista Ligada

**Estrutura:**
```c
typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
    int size;
} LinkedQueue;
```

**Análise de Operações:**

| Operação | Complexidade Temporal | Complexidade Espacial | Justificativa |
|----------|----------------------|----------------------|---------------|
| Enqueue | **Θ(1)** | O(1) | Inserção no final (via ponteiro `rear`) |
| Dequeue | **Θ(1)** | O(1) | Remoção do início (via ponteiro `front`) |
| Front | **Θ(1)** | O(1) | Acesso ao nó `front` |
| Busca | **O(n)** | O(1) | Percorrer lista |
| Espaço Total | - | **Θ(n)** | n nós + overhead de ponteiros |

### Comparação Detalhada de Implementações

#### Trade-offs de Tempo vs. Espaço

| Implementação | Inserção | Remoção | Espaço por Elemento | Overhead Total | Localidade Cache |
|---------------|----------|---------|---------------------|----------------|------------------|
| Array Estático | Θ(1) | Θ(1) | `sizeof(T)` | 0% | ⭐⭐⭐⭐⭐ Excelente |
| Array Dinâmico | O(n) / Θ(1)* | Θ(1) | `sizeof(T)` | 0-50% desperdício** | ⭐⭐⭐⭐ Muito Boa |
| Lista Ligada | Θ(1) | Θ(1) | `sizeof(T) + sizeof(ptr)` | ~100%*** | ⭐⭐ Ruim |
| Fila Circular | Θ(1) | Θ(1) | `sizeof(T)` | 0% | ⭐⭐⭐⭐⭐ Excelente |

\* Amortizado  
** Após redimensionamento, até 50% do array pode estar vazio  
*** Em sistema 64-bit, ponteiro adiciona 8 bytes por elemento (100% se `sizeof(T) = 8`)

#### Recomendações de Uso

**Use Array Estático quando:**
- Limite superior de tamanho é conhecido
- Desempenho máximo é crítico
- Ambiente com recursos limitados (sistemas embarcados)
- Exemplos: Buffer de comunicação, cache de tamanho fixo

**Use Array Dinâmico quando:**
- Tamanho não é conhecido antecipadamente
- Crescimento é esperado mas não frequente
- Operações de leitura são mais comuns que escritas
- Exemplos: Histórico de comandos, undo/redo buffer

**Use Lista Ligada quando:**
- Tamanho varia drasticamente e frequentemente
- Memória fragmentada não é problema
- Overhead de ponteiros é aceitável
- Exemplos: Sistemas com inserções/remoções muito frequentes

**Use Fila Circular quando:**
- Implementando buffer circular para streaming
- Tamanho fixo conhecido é adequado
- Máxima eficiência em espaço e tempo é necessária
- Exemplos: Buffer de áudio/vídeo, ring buffer em drivers

### Análise de Espaço Detalhada

#### Overhead de Memória por Implementação

Assumindo `int` (4 bytes) em sistema 64-bit:

**Array Estático (capacidade = 1000):**
```
Elementos: 1000 × 4 bytes = 4000 bytes
Metadados: 1 int (top) = 4 bytes
Total: 4004 bytes
Overhead: 0.1%
```

**Array Dinâmico (1000 elementos, capacidade = 1024 após crescimento):**
```
Elementos: 1024 × 4 bytes = 4096 bytes (desperdício de 96 bytes)
Metadados: 1 ponteiro + 2 ints = 8 + 8 = 16 bytes
Total: 4112 bytes
Overhead: 2.8%
```

**Lista Ligada (1000 elementos):**
```
Elementos: 1000 × (4 bytes data + 8 bytes ponteiro) = 12000 bytes
Metadados: 2 ponteiros + 1 int = 16 + 4 = 20 bytes
Total: 12020 bytes
Overhead: 200%! (3x mais memória que array)
```

### Considerações sobre Cache e Performance Real

#### Impacto da Hierarquia de Memória

Computadores modernos possuem hierarquia de memória:
- **Registradores**: < 1ns
- **Cache L1**: ~1-3ns
- **Cache L2**: ~10-20ns
- **Cache L3**: ~40-75ns
- **RAM**: ~100-300ns
- **SSD**: ~100,000ns
- **HDD**: ~10,000,000ns

**Arrays oferecem melhor localidade espacial**: elementos consecutivos são carregados juntos em linhas de cache (tipicamente 64 bytes), reduzindo cache misses.

**Listas ligadas sofrem com cache misses**: cada acesso pode requerer busca na RAM, 10-30x mais lento que cache hit.

**Exemplo Prático:**
Para percorrer 1000 elementos:
- Array: ~10-20 cache misses (64 bytes/linha × 4 bytes/int ≈ 16 ints por linha)
- Lista Ligada: ~1000 cache misses (cada nó pode estar em locação diferente)
- **Diferença real de performance: 50-100x mais lento para lista ligada!**

### Complexidade de Algoritmos que Usam Pilhas/Filas

#### Avaliação de Expressões Pós-fixas (RPN)

**Algoritmo:**
```
Para cada token na expressão:
    Se número: push na pilha
    Se operador: pop dois operandos, calcula, push resultado
Resultado final: top da pilha
```

**Análise:**
- Cada token processado exatamente uma vez: O(n)
- Cada operação de pilha: O(1)
- **Complexidade total: Θ(n)** onde n = número de tokens
- **Complexidade espacial: O(n)** no pior caso (expressão com apenas números)

#### Verificação de Parênteses Balanceados

**Análise:**
- Percorre string uma vez: O(n)
- Push/pop para cada parêntese: O(1) cada
- **Complexidade temporal: Θ(n)** onde n = comprimento da string
- **Complexidade espacial: O(n)** no pior caso (string com apenas abre parênteses)

#### Busca em Largura (BFS) com Fila

**Algoritmo:**
```
Enfileira vértice inicial
Enquanto fila não vazia:
    v = dequeue()
    Para cada vizinho w de v:
        Se w não visitado: enqueue(w)
```

**Análise:**
- Cada vértice enfileirado e desenfileirado exatamente uma vez: O(V)
- Cada aresta examinada exatamente uma vez: O(E)
- Operações de fila: O(1) cada
- **Complexidade temporal: Θ(V + E)**
- **Complexidade espacial: O(V)** para fila + visitados

#### Busca em Profundidade (DFS) com Pilha

Similar ao BFS, mas usa pilha:
- **Complexidade temporal: Θ(V + E)**
- **Complexidade espacial: O(V)** para pilha + visitados

### Análise de Casos Extremos

#### Pior Caso para Pilha/Fila

**Operação de Busca:**
- Pior caso: elemento não existe ou está no fundo
- Requer desempilhar/desenfileirar todos elementos
- Complexidade: Θ(n)
- **Conclusão**: Pilhas e filas não são adequadas para buscas

#### Melhor Caso

**Todas operações fundamentais:** Θ(1)
- Push/Pop/Enqueue/Dequeue sempre constantes
- Independente do tamanho da estrutura
- **Conclusão**: Ideais quando apenas extremidades são acessadas

## 🤔 Questões para Reflexão (com Respostas Completas)

### Questão 1: Por que pilhas são ideais para implementar recursão e filas para algoritmos de busca em largura?

**Resposta Completa:**

**Pilhas e Recursão:**

A relação entre pilhas e recursão é fundamental e natural por várias razões:

1. **Call Stack (Pilha de Chamadas)**:
   - Toda linguagem de programação usa uma pilha implícita para gerenciar chamadas de função
   - Cada chamada recursiva empilha um novo **activation record** (registro de ativação) contendo:
     - Parâmetros da função
     - Variáveis locais
     - Endereço de retorno
     - Estado dos registradores

2. **Ordem LIFO Natural**:
   - Chamadas recursivas seguem padrão LIFO: a última função chamada é a primeira a retornar
   - Exemplo em fatorial:
     ```
     fat(4) chama fat(3)
     fat(3) chama fat(2)
     fat(2) chama fat(1)
     fat(1) retorna primeiro ← LIFO!
     ```

3. **Simulação Explícita**:
   - Qualquer recursão pode ser convertida em iteração + pilha explícita
   - Exemplo: DFS recursivo vs. DFS iterativo com pilha

**Código Demonstrativo - Recursão Implícita vs. Pilha Explícita:**

```c
// Versão Recursiva (usa pilha implícita do sistema)
void dfs_recursivo(Grafo* g, int v, bool visitado[]) {
    visitado[v] = true;
    printf("%d ", v);
    
    for (int i = 0; i < g->num_vizinhos[v]; i++) {
        int w = g->vizinhos[v][i];
        if (!visitado[w]) {
            dfs_recursivo(g, w, visitado);  // Push implícito na call stack
        }
    }
}

// Versão Iterativa (usa pilha explícita)
void dfs_iterativo(Grafo* g, int inicio, bool visitado[]) {
    Stack s;
    initStack(&s);
    push(&s, inicio);
    
    while (!isEmpty(&s)) {
        int v = pop(&s);  // Pop explícito
        
        if (!visitado[v]) {
            visitado[v] = true;
            printf("%d ", v);
            
            for (int i = 0; i < g->num_vizinhos[v]; i++) {
                int w = g->vizinhos[v][i];
                if (!visitado[w]) {
                    push(&s, w);  // Push explícito
                }
            }
        }
    }
}
```

**Análise de Complexidade:**
- Ambas versões: **Θ(V + E)** onde V = vértices, E = arestas
- Recursiva: espaço implícito O(V) na call stack
- Iterativa: espaço explícito O(V) na pilha

**Filas e BFS:**

Filas são ideais para BFS pelos seguintes motivos:

1. **Exploração por Níveis**:
   - BFS explora grafos camada por camada (nível por nível)
   - FIFO garante que todos vértices de nível k sejam processados antes de nível k+1
   - Isto é essencial para encontrar **caminhos mais curtos** em grafos não ponderados

2. **Garantia de Ordem**:
   - Vértices são visitados em ordem crescente de distância da origem
   - FIFO mantém esta propriedade automaticamente

3. **Prova Formal**:
   
   **Teorema**: BFS com fila encontra o caminho mais curto em grafos não ponderados.
   
   **Prova por Indução:**
   - **Base**: Vértice inicial tem distância 0 (correto)
   - **Hipótese**: Todos vértices a distância ≤ k foram descobertos corretamente
   - **Passo**: Seja v um vértice a distância k+1. Existe u a distância k adjacente a v.
     - Por hipótese, u foi enfileirado quando sua distância foi determinada
     - Quando u é desenfileirado, v é enfileirado com distância k+1
     - FIFO garante que nenhum vértice a distância > k+1 será processado antes de v
   - Logo, v é descoberto com distância correta k+1 ∎

**Código Demonstrativo - BFS:**

```c
void bfs(Grafo* g, int inicio) {
    bool visitado[MAX_V] = {false};
    int distancia[MAX_V];
    Queue q;
    initQueue(&q);
    
    visitado[inicio] = true;
    distancia[inicio] = 0;
    enqueue(&q, inicio);
    
    while (!isEmpty(&q)) {
        int v = dequeue(&q);  // FIFO: processa na ordem de descoberta
        printf("Vértice %d (distância %d)\n", v, distancia[v]);
        
        for (int i = 0; i < g->num_vizinhos[v]; i++) {
            int w = g->vizinhos[v][i];
            if (!visitado[w]) {
                visitado[w] = true;
                distancia[w] = distancia[v] + 1;  // Distância correta garantida!
                enqueue(&q, w);
            }
        }
    }
}
```

**Por que pilha não funciona para encontrar caminhos mais curtos?**

Se usássemos pilha (LIFO) no lugar de fila:
- Algoritmo seria DFS, não BFS
- Exploraria caminhos até o final antes de explorar alternativas
- Não garante caminho mais curto

**Exemplo:**
```
Grafo:    1 --- 2
          |     |
          3 --- 4

Partindo de 1, querendo chegar em 4:
- BFS (fila): Encontra 1→2→4 (distância 2) ✓
- DFS (pilha): Pode encontrar 1→3→4 ou 1→2→4 (não garante o menor)
```

---

### Questão 2: Quais são as vantagens e desvantagens de implementar uma pilha usando arrays versus listas ligadas?

**Resposta Completa:**

Esta é uma questão fundamental que envolve trade-offs entre diferentes recursos computacionais. Vamos analisar detalhadamente:

#### Implementação com Array

**Vantagens:**

1. **Acesso Sequencial Eficiente - Localidade de Cache**
   - Elementos armazenados contiguamente na memória
   - CPU carrega linhas de cache (tipicamente 64 bytes) de uma vez
   - **Impacto Real**: 10-100x mais rápido que lista ligada para operações em sequência
   
   ```
   Cache Line (64 bytes): [int₀|int₁|int₂|...|int₁₅]
   Acessar int₀ carrega automaticamente int₁ até int₁₅ no cache
   ```

2. **Menor Overhead de Memória**
   ```
   Array: 4 bytes por int
   Lista: 4 bytes (data) + 8 bytes (ponteiro em 64-bit) = 12 bytes
   Overhead da lista: 200% de memória extra!
   ```

3. **Implementação Mais Simples**
   - Menos ponteiros para gerenciar
   - Menos propensão a bugs (memory leaks, dangling pointers)
   - Código mais curto e legível

4. **Acesso Aleatório Possível**
   - Pode acessar qualquer elemento via índice em O(1)
   - Útil para debugging ou operações especiais

5. **Melhor para Hardware Moderno**
   - Prefetching automático pelo CPU
   - Vetorização (SIMD) possível
   - Branch prediction mais efetivo

**Desvantagens:**

1. **Tamanho Fixo (Array Estático)**
   - Deve definir capacidade máxima antecipadamente
   - Overflow se exceder capacidade
   - Desperdício de memória se usar pouco do espaço alocado
   
   ```c
   Stack s[1000];  // E se precisar de 1001? E se usar apenas 10?
   ```

2. **Redimensionamento Custoso (Array Dinâmico)**
   - Requer alocar novo array e copiar todos elementos: O(n)
   - Embora amortizado seja O(1), picos de latência podem ser problemáticos
   - Exemplo: sistema de tempo real não tolera pausas de redimensionamento

3. **Fragmentação em Arrays Dinâmicos**
   - Após crescimento, pode existir dois blocos grandes alocados temporariamente
   - Pico de memória: até 2n elementos durante realloc

#### Implementação com Lista Ligada

**Vantagens:**

1. **Tamanho Verdadeiramente Dinâmico**
   - Cresce e diminui conforme necessário
   - Sem redimensionamento custoso
   - Apenas limite: memória disponível no sistema

2. **Inserção/Remoção Sempre O(1)**
   - Não há redimensionamento
   - Complexidade previsível e constante
   - Ideal para sistemas de tempo real

3. **Melhor Utilização de Memória Fragmentada**
   - Pode usar "buracos" pequenos de memória
   - Array grande pode falhar mesmo com memória total suficiente

4. **Sem Desperdício de Capacidade**
   - Usa exatamente a memória necessária para elementos atuais
   - Array pode reservar 2x o necessário após crescimento

**Desvantagens:**

1. **Overhead Significativo de Memória**
   ```
   Para pilha de 1000 ints em sistema 64-bit:
   Array: 1000 × 4 = 4,000 bytes
   Lista: 1000 × (4 + 8) = 12,000 bytes (3x mais!)
   ```

2. **Péssima Localidade de Cache**
   - Nós espalhados aleatoriamente na memória
   - Cada acesso pode causar cache miss
   - **Impacto Real**: Pode ser 50-100x mais lento que array

3. **Fragmentação de Memória**
   - Pequenas alocações frequentes fragmentam heap
   - Pode degradar performance do allocator ao longo do tempo

4. **Maior Complexidade de Implementação**
   - Gerenciamento de ponteiros
   - Risco de memory leaks
   - Risco de dangling pointers

5. **Overhead de Alocação Dinâmica**
   - malloc/free são custosos (100-1000 ciclos de CPU)
   - Array faz uma alocação, lista faz n alocações

#### Análise Quantitativa Comparativa

**Experimento: Push de 1 milhão de elementos**

| Métrica | Array Estático | Array Dinâmico | Lista Ligada |
|---------|----------------|----------------|--------------|
| Tempo Total | 10ms | 15ms* | 250ms |
| Memória Usada | 4 MB | 4-8 MB | 12 MB |
| Cache Misses | ~1,000 | ~1,500 | ~1,000,000 |
| Alocações malloc | 0 | ~20** | 1,000,000 |

\* Inclui redimensionamentos  
\** Dobrando tamanho: log₂(1M) ≈ 20 redimensionamentos

**Experimento: Pop de todos elementos após push**

| Métrica | Array | Lista Ligada |
|---------|-------|--------------|
| Tempo | 5ms | 150ms*** |
| Motivo | Acesso sequencial no cache | Cache miss em cada acesso |

\*** Incluindo tempo de free()

#### Recomendações de Uso

**Use Array quando:**
- ✅ Limite superior é conhecido ou estimável
- ✅ Performance é crítica
- ✅ Memória cache é importante
- ✅ Trabalhando com sistemas embarcados
- ✅ Implementando algoritmos de processamento em massa

**Exemplos:**
- Buffer de comandos em interpretador
- Histórico de navegação (limite razoável)
- Stack de execução em máquina virtual
- Parser de expressões

**Use Lista Ligada quando:**
- ✅ Tamanho varia muito e imprevisível
- ✅ Inserções/remoções devem ter latência garantida
- ✅ Memória fragmentada é problema
- ✅ Overhead de ponteiros é aceitável

**Exemplos:**
- Sistema com requisitos de tempo real strict
- Ambiente com memória muito fragmentada
- Quando tamanho pode crescer indefinidamente
- Implementações pedagógicas

#### Trade-off Fundamental

Esta questão ilustra um trade-off clássico em ciência da computação:

**Arrays: Otimizado para tempo de acesso**
- Excelente performance através de localidade espacial
- Custo: flexibilidade reduzida

**Listas: Otimizado para flexibilidade**
- Tamanho dinâmico ilimitado
- Custo: performance degradada por cache misses

**Conclusão:** Não existe "melhor" escolha absoluta. A decisão depende dos requisitos específicos:
- Performance crítica + tamanho previsível → Array
- Tamanho altamente variável + latência previsível → Lista Ligada
- Para maioria dos casos práticos → Array Dinâmico oferece bom equilíbrio

---

### Questão 3: Como uma fila circular resolve o problema de "falso overflow" em filas implementadas com arrays?

**Resposta Completa:**

O "falso overflow" é um problema clássico em filas implementadas com arrays lineares. Vamos entender profundamente o problema e sua solução.

#### O Problema: Falso Overflow em Fila Linear

**Implementação Ingênua:**

```c
typedef struct {
    int items[MAX_SIZE];
    int front;  // índice do primeiro elemento
    int rear;   // índice do último elemento
} LinearQueue;

void enqueue(LinearQueue* q, int item) {
    if (q->rear == MAX_SIZE - 1) {
        printf("Overflow!\n");  // Mas será que realmente está cheia?
        return;
    }
    q->items[++q->rear] = item;
}

int dequeue(LinearQueue* q) {
    if (q->front > q->rear) {
        printf("Underflow!\n");
        return -1;
    }
    return q->items[q->front++];
}
```

**Cenário do Problema:**

```
Operações:
1. enqueue(1), enqueue(2), enqueue(3), enqueue(4), enqueue(5)
   Array: [1,2,3,4,5] front=0, rear=4

2. dequeue() × 3
   Array: [_,_,_,4,5] front=3, rear=4
   (elementos 1,2,3 foram removidos, espaço vazio!)

3. enqueue(6), enqueue(7)
   Array: [_,_,_,4,5,6,7] front=3, rear=6

4. enqueue(8) - AINDA HÁ ESPAÇO!
   rear=7 (MAX_SIZE-1), mas posições 0,1,2 estão vazias!
   
5. enqueue(9) - FALSO OVERFLOW!
   rear == MAX_SIZE-1, operação rejeitada
   Mas posições 0,1,2 estão disponíveis! ← PROBLEMA
```

**Visualização:**
```
Estado após passo 4:
[_][_][_][4][5][6][7][8]
 ↑               ↑   ↑
espaço       front rear
vazio!
```

**Por que é "Falso"?**
- Fila indica estar cheia (`rear == MAX_SIZE - 1`)
- Mas existem posições vazias no início
- Capacidade real não foi atingida
- Elementos atuais < MAX_SIZE, mas não aceita mais inserções

#### A Solução: Fila Circular

**Ideia Central:**
Usar **aritmética modular** para "conectar" o final do array ao início, criando um array circular lógico.

**Implementação:**

```c
typedef struct {
    int items[MAX_SIZE];
    int front;
    int rear;
    int count;  // Número atual de elementos (crucial!)
} CircularQueue;

void initQueue(CircularQueue* q) {
    q->front = 0;
    q->rear = -1;  // ou MAX_SIZE - 1
    q->count = 0;
}

bool isFull(CircularQueue* q) {
    return q->count == MAX_SIZE;  // Critério correto!
}

bool isEmpty(CircularQueue* q) {
    return q->count == 0;
}

void enqueue(CircularQueue* q, int item) {
    if (isFull(q)) {
        printf("Overflow verdadeiro!\n");
        return;
    }
    
    // Aritmética modular: "volta ao início" automaticamente
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->items[q->rear] = item;
    q->count++;
}

int dequeue(CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Underflow!\n");
        return -1;
    }
    
    int item = q->items[q->front];
    q->front = (q->front + 1) % MAX_SIZE;  // Aritmética modular
    q->count--;
    return item;
}
```

**Como a Aritmética Modular Funciona:**

```
MAX_SIZE = 8

Índices lineares: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, ...
Índices circulares: 0, 1, 2, 3, 4, 5, 6, 7, 0, 1,  2, ...
                                        ↑
                               "volta ao início"

Fórmula: próximo_índice = (índice_atual + 1) % MAX_SIZE

Exemplos:
(0 + 1) % 8 = 1
(6 + 1) % 8 = 7
(7 + 1) % 8 = 0  ← Volta ao início!
```

**Visualização Circular:**

```
     [0]
   [7] [1]
 [6]     [2]
 [5]     [3]
   [4] 

Após rear=7, próximo rear = (7+1)%8 = 0
```

#### Demonstração Passo-a-Passo

**Fila circular com MAX_SIZE = 5:**

```
Operação                    Estado                      front rear count
------------------------------------------------------------------------
init                        [_][_][_][_][_]             0     -1    0
enqueue(1)                  [1][_][_][_][_]             0      0    1
enqueue(2)                  [1][2][_][_][_]             0      1    2
enqueue(3)                  [1][2][3][_][_]             0      2    3
dequeue() → 1               [_][2][3][_][_]             1      2    2
dequeue() → 2               [_][_][3][_][_]             2      2    1
enqueue(4)                  [_][_][3][4][_]             2      3    2
enqueue(5)                  [_][_][3][4][5]             2      4    3
enqueue(6)                  [6][_][3][4][5]             2      0    4  ← REUTILIZA posição 0!
                            ↑ rear voltou ao início
enqueue(7)                  [6][7][3][4][5]             2      1    5  ← CHEIO!
                               ↑ rear avançou para 1
enqueue(8)                  OVERFLOW VERDADEIRO         2      1    5
                            (count == MAX_SIZE)
```

**Observe:** Posição 0 foi reutilizada! Sem falso overflow.

#### Análise Matemática da Correção

**Teorema:** Fila circular está cheia se e somente se `count == MAX_SIZE`.

**Prova:**

**(⇒) Se a fila está realmente cheia, então count == MAX_SIZE:**
- Fila cheia significa todas MAX_SIZE posições ocupadas
- `count` incrementa em cada enqueue e decrementa em cada dequeue
- Logo, `count` reflete exatamente o número de elementos
- Se todas posições ocupadas, `count = MAX_SIZE` ∎

**(⇐) Se count == MAX_SIZE, então a fila está realmente cheia:**
- `count` só incrementa se enqueue bem-sucedido
- `count` só decrementa se dequeue bem-sucedido
- Se `count = MAX_SIZE`, foram feitos MAX_SIZE enqueues mais que dequeues
- Logo, todas posições estão ocupadas ∎

**Invariante da Fila Circular:**

Após qualquer sequência de operações:
1. Número de elementos na fila = `count`
2. Se `count > 0`, elemento mais antigo está em `items[front]`
3. Se `count > 0`, elemento mais recente está em `items[rear]`
4. Próximo enqueue irá para `items[(rear + 1) % MAX_SIZE]`
5. Próximo dequeue removerá `items[front]` e avançará `front = (front + 1) % MAX_SIZE`

#### Análise de Complexidade

**Fila Linear (ingênua):**
- Enqueue: O(1) até rear == MAX_SIZE - 1
- Dequeue: O(1)
- Utilização de espaço: Pode ser < 50% antes de overflow
- **Problema:** Falso overflow

**Fila Circular:**
- Enqueue: **Θ(1)** sempre
- Dequeue: **Θ(1)** sempre
- Utilização de espaço: **100%** antes de overflow real
- Sem falso overflow

**Complexidade da aritmética modular:**
- Operação `%` (módulo): O(1) em hardware moderno
- Em hardware sem instrução de módulo, pode usar: `if (rear + 1 == MAX_SIZE) rear = 0; else rear++;`

#### Por Que Precisamos de `count`?

Sem `count`, temos ambiguidade:

```
Caso 1: Fila vazia      [_][_][_][_]  front=0, rear=0
Caso 2: Fila com 1      [X][_][_][_]  front=0, rear=0
Caso 3: Fila cheia      [X][X][X][X]  front=0, rear=3

Próximo enqueue: rear = (3+1)%4 = 0
                 [X][X][X][X]  front=0, rear=0 ← Igual ao caso 1!
```

**Soluções alternativas ao `count`:**

1. **Desperdiçar uma posição:**
   ```c
   bool isFull(q) { return (rear + 1) % MAX_SIZE == front; }
   // Capacidade efetiva = MAX_SIZE - 1
   ```

2. **Flag adicional:**
   ```c
   bool isEmpty(q) { return !q->hasElements; }
   bool isFull(q) { return q->hasElements && q->front == q->rear; }
   ```

3. **Usar `count` (mais claro e direto)** ✓

#### Aplicações Práticas

**Onde filas circulares são essenciais:**

1. **Buffer Circular (Ring Buffer)**
   - Streaming de áudio/vídeo
   - Captura de dados de sensores
   - Logging circular (substitui dados antigos automaticamente)

2. **Driver de Dispositivos**
   - Buffer de teclado
   - Buffer de rede
   - Comunicação serial

3. **Produtor-Consumidor**
   - Thread produtora insere dados
   - Thread consumidora remove dados
   - Fila circular evita realocação

**Exemplo de código real:**

```c
// Buffer circular de logging
#define LOG_SIZE 1000
CircularQueue log_buffer;

void log_message(char* msg) {
    if (isFull(&log_buffer)) {
        dequeue(&log_buffer);  // Remove mais antigo
    }
    enqueue(&log_buffer, msg);  // Adiciona novo
}
// Sempre mantém últimas 1000 mensagens!
```

#### Conclusão

A fila circular resolve o falso overflow através de:

1. **Aritmética modular**: Reutiliza posições liberadas no início
2. **Contador de elementos**: Distingue entre vazio e cheio
3. **Utilização ótima**: 100% do espaço alocado

**Trade-offs:**
- ✅ Elimina falso overflow
- ✅ Mantém O(1) para todas operações
- ✅ Utilização máxima de espaço
- ❌ Lógica um pouco mais complexa
- ❌ Ainda tem tamanho fixo (resolver com lista ligada ou array dinâmico)

---

### Questão 4: Projete um sistema de undo/redo para um editor de texto usando pilhas. Quais operações você implementaria?

**Resposta Completa:**

Este é um exemplo clássico de aplicação prática de pilhas. Vamos projetar um sistema completo e robusto.

#### Arquitetura do Sistema

**Conceito Central:**
- **Pilha de Undo**: Armazena operações já realizadas (pode desfazer)
- **Pilha de Redo**: Armazena operações desfeitas (pode refazer)

**Princípio de Funcionamento:**
1. Quando usuário faz uma operação → empilha em Undo, limpa Redo
2. Quando usuário faz Undo → pop de Undo, executa operação inversa, push em Redo
3. Quando usuário faz Redo → pop de Redo, re-executa operação, push em Undo

#### Estruturas de Dados

```c
// Tipos de operações possíveis
typedef enum {
    OP_INSERT,      // Inserir texto
    OP_DELETE,      // Deletar texto
    OP_REPLACE,     // Substituir texto
    OP_FORMAT       // Mudança de formatação
} OperationType;

// Estrutura que representa uma operação
typedef struct {
    OperationType type;
    int position;           // Posição no documento
    char* content;          // Conteúdo afetado
    int length;             // Tamanho do conteúdo
    
    // Para operação de replace/format
    char* old_content;      // Conteúdo anterior
    int old_length;
    
    // Metadados
    time_t timestamp;       // Quando foi executada
    int group_id;           // Para agrupar operações relacionadas
} Operation;

// Sistema de undo/redo
typedef struct {
    Stack undo_stack;       // Pilha de operações que podem ser desfeitas
    Stack redo_stack;       // Pilha de operações que podem ser refeitas
    char* document;         // Documento atual
    int doc_size;           // Tamanho do documento
    int max_undo_levels;    // Limite de undos (gerenciar memória)
} EditorState;
```

#### Operações Fundamentais

**1. Inicialização:**

```c
void initEditor(EditorState* editor, int max_undo) {
    initStack(&editor->undo_stack);
    initStack(&editor->redo_stack);
    editor->document = malloc(INITIAL_DOC_SIZE);
    editor->document[0] = '\0';
    editor->doc_size = 0;
    editor->max_undo_levels = max_undo;
}
```

**2. Executar Operação (Insert):**

```c
void executeInsert(EditorState* editor, int pos, char* text) {
    // 1. Salvar operação na pilha de undo
    Operation* op = malloc(sizeof(Operation));
    op->type = OP_INSERT;
    op->position = pos;
    op->length = strlen(text);
    op->content = strdup(text);  // Cópia do texto inserido
    op->timestamp = time(NULL);
    
    push(&editor->undo_stack, op);
    
    // 2. Limpar pilha de redo (nova operação invalida redos)
    clearStack(&editor->redo_stack);
    
    // 3. Executar inserção no documento
    insertTextInDocument(editor, pos, text);
    
    // 4. Gerenciar limite de undos
    if (stackSize(&editor->undo_stack) > editor->max_undo_levels) {
        Operation* oldest = removeBottom(&editor->undo_stack);
        freeOperation(oldest);
    }
}

void insertTextInDocument(EditorState* editor, int pos, char* text) {
    int text_len = strlen(text);
    int new_size = editor->doc_size + text_len;
    
    // Realocar se necessário
    if (new_size >= editor->doc_capacity) {
        editor->doc_capacity *= 2;
        editor->document = realloc(editor->document, editor->doc_capacity);
    }
    
    // Mover texto após posição para frente
    memmove(editor->document + pos + text_len,
            editor->document + pos,
            editor->doc_size - pos);
    
    // Inserir novo texto
    memcpy(editor->document + pos, text, text_len);
    editor->doc_size = new_size;
    editor->document[new_size] = '\0';
}
```

**3. Executar Operação (Delete):**

```c
void executeDelete(EditorState* editor, int pos, int length) {
    // 1. Salvar operação na pilha de undo
    // IMPORTANTE: Salvar o conteúdo deletado para poder restaurar!
    Operation* op = malloc(sizeof(Operation));
    op->type = OP_DELETE;
    op->position = pos;
    op->length = length;
    op->content = malloc(length + 1);
    memcpy(op->content, editor->document + pos, length);
    op->content[length] = '\0';
    op->timestamp = time(NULL);
    
    push(&editor->undo_stack, op);
    clearStack(&editor->redo_stack);
    
    // 2. Executar deleção no documento
    deleteTextInDocument(editor, pos, length);
}

void deleteTextInDocument(EditorState* editor, int pos, int length) {
    // Mover texto após a região deletada para trás
    memmove(editor->document + pos,
            editor->document + pos + length,
            editor->doc_size - pos - length);
    
    editor->doc_size -= length;
    editor->document[editor->doc_size] = '\0';
}
```

**4. Operação Undo:**

```c
void undo(EditorState* editor) {
    if (isEmpty(&editor->undo_stack)) {
        printf("Nada para desfazer!\n");
        return;
    }
    
    // 1. Remover operação da pilha de undo
    Operation* op = pop(&editor->undo_stack);
    
    // 2. Executar operação inversa
    switch (op->type) {
        case OP_INSERT:
            // Inverso de INSERT é DELETE
            deleteTextInDocument(editor, op->position, op->length);
            break;
            
        case OP_DELETE:
            // Inverso de DELETE é INSERT (com conteúdo salvo)
            insertTextInDocument(editor, op->position, op->content);
            break;
            
        case OP_REPLACE:
            // Inverso de REPLACE é REPLACE com conteúdo antigo
            replaceTextInDocument(editor, op->position, op->length, op->old_content);
            break;
    }
    
    // 3. Mover operação para pilha de redo
    push(&editor->redo_stack, op);
    
    printf("Undo executado: %s na posição %d\n",
           operationTypeName(op->type), op->position);
}
```

**5. Operação Redo:**

```c
void redo(EditorState* editor) {
    if (isEmpty(&editor->redo_stack)) {
        printf("Nada para refazer!\n");
        return;
    }
    
    // 1. Remover operação da pilha de redo
    Operation* op = pop(&editor->redo_stack);
    
    // 2. Re-executar operação original
    switch (op->type) {
        case OP_INSERT:
            insertTextInDocument(editor, op->position, op->content);
            break;
            
        case OP_DELETE:
            deleteTextInDocument(editor, op->position, op->length);
            break;
            
        case OP_REPLACE:
            replaceTextInDocument(editor, op->position, op->old_length, op->content);
            break;
    }
    
    // 3. Mover operação de volta para pilha de undo
    push(&editor->undo_stack, op);
    
    printf("Redo executado: %s na posição %d\n",
           operationTypeName(op->type), op->position);
}
```

#### Operações Avançadas

**1. Agrupamento de Operações (Grouping):**

Problema: Digitar "Hello" resulta em 5 operações separadas. Undo deve desfazer a palavra inteira, não letra por letra.

Solução: Agrupar operações relacionadas:

```c
typedef struct {
    Operation** operations;  // Array de operações no grupo
    int count;
    int group_id;
    time_t start_time;
} OperationGroup;

// Agrupar operações dentro de intervalo de tempo
#define GROUP_TIMEOUT_MS 500

void executeInsertGrouped(EditorState* editor, int pos, char* text) {
    Operation* op = createInsertOp(pos, text);
    
    // Verificar se deve agrupar com operação anterior
    if (!isEmpty(&editor->undo_stack)) {
        Operation* last = peek(&editor->undo_stack);
        time_t now = time(NULL);
        
        // Se mesma operação, posição adjacente, e dentro do timeout
        if (last->type == OP_INSERT &&
            last->position + last->length == pos &&
            difftime(now, last->timestamp) < GROUP_TIMEOUT_MS / 1000.0) {
            
            // Expandir operação anterior em vez de criar nova
            expandOperation(last, text);
            free(op);
            return;
        }
    }
    
    // Caso contrário, adicionar como nova operação
    push(&editor->undo_stack, op);
    insertTextInDocument(editor, pos, text);
}
```

**2. Undo/Redo Seletivo:**

Permitir desfazer operação específica sem desfazer todas após ela:

```c
void undoSpecificOperation(EditorState* editor, int operation_id) {
    // Remover operação específica da pilha
    Operation* op = removeOperationById(&editor->undo_stack, operation_id);
    
    // Executar inverso
    executeInverse(editor, op);
    
    // Não adicionar a redo_stack pois é operação "avançada"
    freeOperation(op);
}
```

**3. Limite de Memória para Undo:**

```c
void pushWithLimit(EditorState* editor, Operation* op) {
    // Se atingiu limite, remover operação mais antiga
    if (stackSize(&editor->undo_stack) >= editor->max_undo_levels) {
        Operation* oldest = removeBottom(&editor->undo_stack);
        freeOperation(oldest);
    }
    
    push(&editor->undo_stack, op);
}
```

**4. Salvar Estado do Documento:**

```c
typedef struct {
    char* document_snapshot;
    int snapshot_size;
    int undo_stack_size;
} Checkpoint;

void createCheckpoint(EditorState* editor) {
    Checkpoint* cp = malloc(sizeof(Checkpoint));
    cp->document_snapshot = strdup(editor->document);
    cp->snapshot_size = editor->doc_size;
    cp->undo_stack_size = stackSize(&editor->undo_stack);
    
    // Salvar checkpoint na pilha separada
    push(&editor->checkpoints, cp);
}

void restoreCheckpoint(EditorState* editor) {
    if (isEmpty(&editor->checkpoints)) return;
    
    Checkpoint* cp = pop(&editor->checkpoints);
    
    // Restaurar documento
    free(editor->document);
    editor->document = cp->document_snapshot;
    editor->doc_size = cp->snapshot_size;
    
    // Descartar operações após checkpoint
    while (stackSize(&editor->undo_stack) > cp->undo_stack_size) {
        Operation* op = pop(&editor->undo_stack);
        freeOperation(op);
    }
    
    free(cp);
}
```

#### Análise de Complexidade

**Operações:**

| Operação | Complexidade Temporal | Complexidade Espacial | Notas |
|----------|----------------------|----------------------|-------|
| Insert | O(n) | O(m) | n = tamanho doc, m = tamanho texto inserido |
| Delete | O(n) | O(m) | Deve salvar texto deletado |
| Undo | O(n) | O(1) | Executa operação inversa |
| Redo | O(n) | O(1) | Re-executa operação |
| Peek Undo/Redo | O(1) | O(1) | Apenas olha topo da pilha |

**Espaço Total:**
- Documento: O(n) onde n = tamanho do documento
- Pilha de undo: O(k × m) onde k = número de operações, m = tamanho médio
- Pilha de redo: O(k × m)
- **Total: O(n + k × m)**

**Otimizações possíveis:**

1. **Compressão de Operações:**
   - Pequenas edições podem ser agrupadas
   - Reduz k (número de operações)

2. **Limite de Undo Levels:**
   - Limitar k a valor razoável (ex: 100-1000)
   - Evita crescimento ilimitado de memória

3. **Operações Diferenciais:**
   - Armazenar apenas diferenças, não conteúdo completo
   - Reduz m (tamanho por operação)

#### Exemplo de Uso Completo

```c
int main() {
    EditorState editor;
    initEditor(&editor, 100);  // Até 100 níveis de undo
    
    // Usuário digita "Hello"
    executeInsert(&editor, 0, "H");
    executeInsert(&editor, 1, "e");
    executeInsert(&editor, 2, "l");
    executeInsert(&editor, 3, "l");
    executeInsert(&editor, 4, "o");
    // Documento: "Hello"
    
    // Usuário insere espaço e "World"
    executeInsert(&editor, 5, " ");
    executeInsert(&editor, 6, "World");
    // Documento: "Hello World"
    
    // Usuário percebe erro, faz undo 2 vezes
    undo(&editor);  // Remove "World"
    undo(&editor);  // Remove " "
    // Documento: "Hello"
    
    // Usuário decide refazer
    redo(&editor);  // Adiciona " "
    redo(&editor);  // Adiciona "World"
    // Documento: "Hello World"
    
    // Nova edição limpa redo
    executeDelete(&editor, 6, 5);  // Delete "World"
    // Documento: "Hello "
    // Pilha de redo foi limpa!
    
    // Tenta redo (não há nada)
    redo(&editor);  // Output: "Nada para refazer!"
    
    return 0;
}
```

#### Considerações Avançadas

**1. Performance em Documentos Grandes:**
- Inserções/deleções em documentos grandes (MB) são custosas
- Solução: Usar estruturas mais eficientes (Gap Buffer, Rope, Piece Table)

**2. Undo Persistente:**
- Salvar pilhas de undo/redo em arquivo
- Permite undo após fechar e reabrir editor

**3. Undo Colaborativo:**
- Múltiplos usuários editando
- Necessita resolução de conflitos (Operational Transformation ou CRDT)

**4. Memory Management:**
- Liberação correta de memória das operações
- Evitar memory leaks em pilhas de undo/redo

#### Conclusão

Sistema de undo/redo ilustra perfeitamente o uso de pilhas:
- **Pilhas mantêm ordem temporal**: LIFO corresponde à ordem inversa de execução
- **Operações inversas são naturais**: cada operação tem inversa clara
- **Gerenciamento de estado simplificado**: pilhas encapsulam histórico

**Implementações reais:**
- Photoshop: History panel (pilha de estados)
- Microsoft Word: Undo/Redo (pilha de operações)
- Git: Commits e reverts (estrutura similar a pilha)
- Editores de texto modernos (VS Code, Sublime): Sistemas sofisticados baseados neste princípio

---

### Questão 5: Compare o uso de memória entre uma fila implementada com array circular versus lista ligada para 1000 elementos.

**Resposta Completa:**

Esta questão nos permite explorar profundamente os trade-offs de memória entre diferentes implementações. Vamos fazer uma análise rigorosa e quantitativa.

#### Premissas da Análise

**Sistema:** Linux x86-64 (64 bits)
**Compilador:** GCC com alinhamento padrão
**Elementos:** 1000 inteiros (int = 4 bytes)

#### Implementação com Array Circular

**Estrutura:**

```c
typedef struct {
    int items[1000];    // Array de elementos
    int front;          // Índice da frente
    int rear;           // Índice da traseira
    int count;          // Número de elementos
} CircularQueue;
```

**Cálculo Detalhado de Memória:**

```
Componente                  Tamanho           Cálculo
-----------------------------------------------------------
items[1000]                 4000 bytes        1000 × 4
front (int)                 4 bytes
rear (int)                  4 bytes
count (int)                 4 bytes
Padding (alinhamento)       4 bytes*          Para alinhar a 8 bytes

TOTAL                       4016 bytes        ≈ 3.92 KB
```

\* Em sistemas 64-bit, estruturas frequentemente são alinhadas a 8 bytes

**Verificação com sizeof:**

```c
printf("sizeof(CircularQueue) = %zu bytes\n", sizeof(CircularQueue));
// Output: 4016 bytes (dependendo do compilador)
```

**Análise:**
- **Memória por elemento:** 4016 / 1000 = 4.016 bytes
- **Overhead total:** 16 bytes (0.4%)
- **Overhead por elemento:** 0.016 bytes
- **Utilização:** 99.6% eficiente

#### Implementação com Lista Ligada

**Estruturas:**

```c
typedef struct Node {
    int data;               // Dados do elemento
    struct Node* next;      // Ponteiro para próximo nó
} Node;

typedef struct {
    Node* front;            // Ponteiro para primeiro nó
    Node* rear;             // Ponteiro para último nó
    int count;              // Número de elementos
} LinkedQueue;
```

**Cálculo Detalhado de Memória:**

**Por Nó:**
```
Componente                  Tamanho           Observação
-----------------------------------------------------------
data (int)                  4 bytes
Padding                     4 bytes           Alinhamento para ponteiro
next (ponteiro)             8 bytes           Ponteiro em sistema 64-bit

TOTAL POR NÓ               16 bytes
```

**Estrutura da Fila:**
```
Componente                  Tamanho
-----------------------------------------------------------
front (ponteiro)            8 bytes
rear (ponteiro)             8 bytes
count (int)                 4 bytes
Padding                     4 bytes

TOTAL DA ESTRUTURA         24 bytes
```

**Total para 1000 Elementos:**
```
1000 nós                    16000 bytes       1000 × 16
Estrutura da fila           24 bytes
Overhead do malloc          ~32000 bytes*     ~32 bytes por alocação

TOTAL                       48024 bytes       ≈ 46.90 KB
```

\* Malloc adiciona overhead para gerenciar blocos (header, footer, alinhamento)

**Nota sobre overhead do malloc:**

Cada chamada a `malloc()` adiciona metadata:

```
┌─────────────────────────────────┐
│ malloc header (16-32 bytes)     │  ← Metadata do allocator
├─────────────────────────────────┤
│ User data (16 bytes - Node)     │  ← Dados que solicitamos
├─────────────────────────────────┤
│ Padding/Footer (0-16 bytes)     │  ← Alinhamento
└─────────────────────────────────┘

Total: ~32-48 bytes por alocação de 16 bytes!
```

**Análise:**
- **Memória por elemento:** 48024 / 1000 = 48.024 bytes
- **Overhead total:** 44024 bytes (1100%)
- **Overhead por elemento:** 44.024 bytes
- **Utilização:** 8.3% eficiente (91.7% é overhead!)

#### Comparação Direta

| Métrica | Array Circular | Lista Ligada | Diferença |
|---------|----------------|--------------|-----------|
| **Memória Total** | 4,016 bytes | 48,024 bytes | **12x mais** para lista |
| **Por Elemento** | 4.016 bytes | 48.024 bytes | **12x mais** para lista |
| **Overhead Total** | 16 bytes | 44,024 bytes | **2751x mais** para lista |
| **Overhead %** | 0.4% | 1100% | Lista desperdiça 11x mais que usa |
| **Eficiência** | 99.6% | 8.3% | Array 12x mais eficiente |

**Visualização Gráfica:**

```
Memória Usada (escala logarítmica):

Array Circular:  ████ (4 KB)
Lista Ligada:    ████████████████████████████████████████████████ (48 KB)
                 |---|---|---|---|---|---|---|---|---|---|---|---|
                 0   5   10  15  20  25  30  35  40  45  50  55  60 KB
```

#### Análise Detalhada do Overhead

**1. Overhead de Ponteiros:**

```
Array:   0 ponteiros por elemento
Lista:   1 ponteiro (8 bytes) por elemento = 8000 bytes total

Desperdício: 8000 bytes (2x os dados reais!)
```

**2. Overhead de Alinhamento:**

```c
// Array: alinhamento da estrutura inteira (4 bytes)
struct CircularQueue {
    int items[1000];  // 4000 bytes
    int front;        // 4 bytes
    int rear;         // 4 bytes  
    int count;        // 4 bytes
    // Padding: 4 bytes para alinhar a 8
};  // Total: 4016 bytes

// Lista: alinhamento POR NÓ (4 bytes × 1000 = 4000 bytes)
struct Node {
    int data;         // 4 bytes
    // Padding: 4 bytes para alinhar ponteiro
    Node* next;       // 8 bytes
};  // Total: 16 bytes × 1000 = 16000 bytes
```

**3. Overhead do Allocator:**

```
Array: 1 alocação × 32 bytes overhead = 32 bytes
Lista: 1000 alocações × 32 bytes overhead = 32000 bytes

Desperdício adicional: 31968 bytes!
```

#### Impacto em Diferentes Tamanhos

**Extrapolação para diferentes números de elementos:**

| Elementos | Array Circular | Lista Ligada | Razão |
|-----------|----------------|--------------|-------|
| 10 | 56 bytes | 504 bytes | 9.0x |
| 100 | 416 bytes | 4824 bytes | 11.6x |
| 1,000 | 4,016 bytes | 48,024 bytes | 12.0x |
| 10,000 | 40,016 bytes | 480,024 bytes | 12.0x |
| 100,000 | 400,016 bytes | 4,800,024 bytes | 12.0x |

**Observação:** Razão converge para ~12x para grandes n.

**Por quê 12x?**

```
Lista usa: 4 (data) + 12 (ponteiro+padding+malloc overhead) = 16 por elemento + 32 overhead de malloc ≈ 48
Array usa: 4 (data) + 0.016 (overhead amortizado) ≈ 4

Razão: 48 / 4 = 12x
```

#### Impacto no Cache

**Cache Line (típico): 64 bytes**

**Array Circular:**
```
Cache Line: [int₀|int₁|...|int₁₅]  ← 16 ints por cache line

Acessar 1000 elementos:
Cache misses: 1000 / 16 = 63 cache misses
```

**Lista Ligada:**
```
Cache Line: [Node₀: data|next → ] [Node₁ em outro lugar...]

Cada acesso a nó diferente = cache miss provável

Acessar 1000 elementos:
Cache misses: ~1000 cache misses (pior caso)
```

**Diferença:** 16x mais cache misses para lista ligada!

**Impacto em performance real:**
- Cache hit: ~1-3 ns
- Cache miss (RAM): ~100-300 ns
- **Percorrer lista ligada pode ser 100x mais lento que array!**

#### Considerações Adicionais

**1. Fragmentação de Memória:**

**Array:**
- Uma alocação contígua de 4KB
- Requer 4KB contínuos disponíveis
- Pode falhar em sistema fragmentado

**Lista:**
- 1000 alocações de 16 bytes cada
- Pode usar "buracos" pequenos na memória
- Menos provável de falhar, mas fragmenta mais o heap

**2. Overhead de Desalocação:**

**Array:**
```c
free(queue->items);  // Uma chamada a free()
```

**Lista:**
```c
while (front != NULL) {
    Node* temp = front;
    front = front->next;
    free(temp);  // 1000 chamadas a free()!
}
```

**Custo:** Lista requer 1000× mais operações de desalocação

**3. Crescimento Dinâmico:**

**Array (com realloc):**
```c
// Dobrar capacidade: alocar 2n, copiar n, liberar n
queue->items = realloc(queue->items, new_size);
// Custo: O(n) tempo, mas memória temporária 3n durante cópia
```

**Lista:**
```c
// Adicionar elemento: alocar 1 nó
Node* new_node = malloc(sizeof(Node));
// Custo: O(1) sempre, sem picos de memória
```

#### Quando Lista Ligada Vence em Memória?

**Cenário: Fila com capacidade fixa mas ocupação variável**

```
Capacidade: 10000
Ocupação média: 100

Array Circular:
- Aloca: 10000 × 4 = 40000 bytes (sempre)
- Usa: ~100 × 4 = 400 bytes
- Desperdício: 39600 bytes (99%)

Lista Ligada:
- Aloca: 100 × 48 = 4800 bytes (dinamicamente)
- Usa: 4800 bytes
- Desperdício: 0%

Lista vence! 40KB vs 4.8KB
```

**Conclusão:** Lista ligada vence quando:
- Capacidade máxima >> ocupação média
- Tamanho varia drasticamente
- Memória é mais valiosa que performance

#### Recomendações Práticas

**Use Array Circular quando:**
- ✅ Capacidade conhecida ou estimável
- ✅ Memória é abundante
- ✅ Performance é crítica
- ✅ Boa localidade de cache é importante
- **Ideal para:** Buffers, sistemas embarcados, high-performance computing

**Use Lista Ligada quando:**
- ✅ Tamanho varia muito (ordem de grandeza)
- ✅ Memória é muito limitada E tamanho imprevisível
- ✅ Fragmentação de memória é problema
- ✅ Overhead de 12x é aceitável
- **Ideal para:** Sistemas com memória fragmentada, tamanho extremamente variável

#### Medição Real

**Código de Benchmark:**

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Medir memória de processo (Linux)
size_t getCurrentRSS() {
    FILE* fp = fopen("/proc/self/statm", "r");
    size_t rss;
    fscanf(fp, "%*s %zu", &rss);
    fclose(fp);
    return rss * sysconf(_SC_PAGESIZE);
}

int main() {
    const int N = 1000;
    
    printf("=== Array Circular ===\n");
    size_t mem_before = getCurrentRSS();
    
    CircularQueue* cq = malloc(sizeof(CircularQueue));
    initQueue(cq);
    for (int i = 0; i < N; i++) {
        enqueue(cq, i);
    }
    
    size_t mem_after = getCurrentRSS();
    printf("Memória usada: %zu bytes\n", mem_after - mem_before);
    printf("sizeof(CircularQueue): %zu bytes\n", sizeof(CircularQueue));
    
    free(cq);
    
    printf("\n=== Lista Ligada ===\n");
    mem_before = getCurrentRSS();
    
    LinkedQueue* lq = malloc(sizeof(LinkedQueue));
    initLinkedQueue(lq);
    for (int i = 0; i < N; i++) {
        enqueueLinked(lq, i);
    }
    
    mem_after = getCurrentRSS();
    printf("Memória usada: %zu bytes\n", mem_after - mem_before);
    printf("Estimativa teórica: %d bytes\n", N * 48 + 24);
    
    return 0;
}
```

**Output esperado:**
```
=== Array Circular ===
Memória usada: 4096 bytes (página inteira)
sizeof(CircularQueue): 4016 bytes

=== Lista Ligada ===
Memória usada: 49152 bytes (12 páginas)
Estimativa teórica: 48024 bytes
```

#### Conclusão Final

Para 1000 elementos de tipo int:

**Array Circular:**
- ✅ 4,016 bytes (4 KB)
- ✅ 99.6% eficiente
- ✅ Excelente para cache
- ❌ Tamanho fixo

**Lista Ligada:**
- ❌ 48,024 bytes (48 KB) - **12x mais memória**
- ❌ 8.3% eficiente - 91.7% é overhead
- ❌ Ruim para cache
- ✅ Tamanho dinâmico verdadeiro

**Veredicto:** Array circular é vastamente superior em uso de memória para este caso, usando apenas 1/12 da memória da lista ligada. A lista ligada só é vantajosa quando o tamanho varia drasticamente e de forma imprevisível, compensando seu enorme overhead.

## 📋 Exercícios Práticos

### Nível Básico
1. Implemente uma função que inverta uma string usando pilha
2. Crie uma fila que armazene números pares e ímpares separadamente
3. Desenvolva um verificador de expressões matemáticas balanceadas

### Nível Intermediário
4. Implemente uma pilha que mantenha o valor mínimo em O(1)
5. Crie uma fila com prioridade usando arrays
6. Desenvolva um simulador de impressora com fila de trabalhos

### Nível Avançado
7. Implemente uma calculadora pós-fixa completa
8. Crie um sistema de navegação de páginas web com histórico
9. Desenvolva um escalonador de processos usando múltiplas filas

## 🔍 Debugging e Testes

### Casos de Teste Importantes
- Operações em estruturas vazias
- Operações em estruturas cheias
- Sequências de operações mistas
- Casos extremos (overflow/underflow)

### Ferramentas de Debug
```bash
# Verificar vazamentos de memória
valgrind --leak-check=full ./programa

# Debug com GDB
gdb ./programa
(gdb) break função
(gdb) run
(gdb) print variavel
```

## 📚 Referências

- Cormen, T. H. et al. (2009). *Introduction to Algorithms*. MIT Press.
- Sedgewick, R. (2011). *Algorithms in C*. Addison-Wesley.
- Tenenbaum, A. M. (1990). *Data Structures Using C*. Prentice Hall.
- Weiss, M. A. (2006). *Data Structures and Algorithm Analysis in C*. Addison-Wesley.