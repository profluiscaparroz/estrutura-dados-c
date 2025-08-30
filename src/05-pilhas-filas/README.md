# Pilhas e Filas em C

## 📋 Visão Geral

Pilhas (stacks) e filas (queues) são estruturas de dados lineares fundamentais que seguem princípios específicos de inserção e remoção de elementos. Este módulo apresenta implementações completas dessas estruturas em C, explorando suas características, aplicações e variações.

## 📚 Conceitos Fundamentais

### 🥞 Pilha (Stack)
Uma pilha é uma estrutura de dados que segue o princípio **LIFO** (Last In, First Out), onde o último elemento inserido é o primeiro a ser removido.

#### Características Principais
- **Topo (Top)**: Posição do último elemento inserido
- **Base**: Primeira posição da pilha
- **Capacidade**: Número máximo de elementos
- **Tamanho Atual**: Número de elementos presentes

#### Operações Fundamentais
- **Push**: Inserir elemento no topo
- **Pop**: Remover elemento do topo
- **Top/Peek**: Visualizar elemento do topo sem remover
- **IsEmpty**: Verificar se a pilha está vazia
- **IsFull**: Verificar se a pilha está cheia

### 🚶 Fila (Queue)
Uma fila é uma estrutura de dados que segue o princípio **FIFO** (First In, First Out), onde o primeiro elemento inserido é o primeiro a ser removido.

#### Características Principais
- **Frente (Front)**: Posição do primeiro elemento
- **Traseira (Rear)**: Posição do último elemento
- **Capacidade**: Número máximo de elementos
- **Tamanho Atual**: Número de elementos presentes

#### Operações Fundamentais
- **Enqueue**: Inserir elemento na traseira
- **Dequeue**: Remover elemento da frente
- **Front**: Visualizar primeiro elemento sem remover
- **IsEmpty**: Verificar se a fila está vazia
- **IsFull**: Verificar se a fila está cheia

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

### Aplicações de Pilhas
1. **Controle de Chamadas de Função**
   - Stack de execução
   - Recursão
   - Retorno de funções

2. **Avaliação de Expressões**
   - Conversão infixa para pós-fixa
   - Calculadora
   - Parser de expressões

3. **Navegação e Histórico**
   - Histórico do browser
   - Undo/Redo operations
   - Navegação em editores

4. **Algoritmos de Grafos**
   - Busca em profundidade (DFS)
   - Verificação de parênteses balanceados
   - Conversão de notações

### Aplicações de Filas
1. **Sistemas Operacionais**
   - Escalonamento de processos
   - Buffer de impressão
   - Gerenciamento de recursos

2. **Algoritmos de Grafos**
   - Busca em largura (BFS)
   - Algoritmo de Dijkstra
   - Árvore geradora mínima

3. **Simulações**
   - Filas de atendimento
   - Sistemas de semáforos
   - Modelagem de tráfego

4. **Programação Assíncrona**
   - Event loops
   - Message queues
   - Task scheduling

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

### Operações em Pilha
- **Push**: O(1) - Inserção constante no topo
- **Pop**: O(1) - Remoção constante do topo
- **Peek**: O(1) - Acesso direto ao topo
- **Busca**: O(n) - Necessário percorrer elementos

### Operações em Fila
- **Enqueue**: O(1) - Inserção constante na traseira
- **Dequeue**: O(1) - Remoção constante da frente
- **Front**: O(1) - Acesso direto à frente
- **Busca**: O(n) - Necessário percorrer elementos

## 🤔 Questões para Reflexão

1. **Conceitual**: Explique por que pilhas são ideais para implementar recursão e filas para algoritmos de busca em largura.

2. **Implementação**: Quais são as vantagens e desvantagens de implementar uma pilha usando arrays versus listas ligadas?

3. **Otimização**: Como uma fila circular resolve o problema de "falso overflow" em filas implementadas com arrays?

4. **Aplicação**: Projete um sistema de undo/redo para um editor de texto usando pilhas. Quais operações você implementaria?

5. **Análise**: Compare o uso de memória entre uma fila implementada com array circular versus lista ligada para 1000 elementos.

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