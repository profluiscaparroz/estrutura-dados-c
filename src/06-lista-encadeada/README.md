# Listas Encadeadas em C

## 📋 Visão Geral

As listas encadeadas são estruturas de dados dinâmicas fundamentais que permitem armazenar elementos de forma não contígua na memória. Este módulo apresenta implementações completas de diferentes tipos de listas encadeadas em C, explorando suas características, vantagens e aplicações práticas.

## 🔗 Conceitos Fundamentais

### O que é uma Lista Encadeada?

Uma lista encadeada é uma estrutura de dados linear onde os elementos (nós) são armazenados em posições arbitrárias da memória e conectados através de ponteiros. Cada nó contém dados e uma referência (ponteiro) para o próximo nó da sequência.

#### Características Principais
- **Tamanho Dinâmico**: Cresce e diminui durante a execução
- **Alocação Não Contígua**: Nós podem estar em qualquer lugar da memória
- **Acesso Sequencial**: Necessário percorrer desde o início
- **Eficiência em Inserções/Remoções**: O(1) em posições conhecidas

## 🗂️ Tipos de Listas Implementadas

### 1. Lista Simplesmente Encadeada
- **Arquivo**: `listaSimples.c`
- **Características**: Cada nó aponta apenas para o próximo
- **Navegação**: Unidirecional (apenas para frente)

### 2. Lista Duplamente Encadeada
- **Arquivo**: `listaDupla.c`
- **Características**: Cada nó tem ponteiros para anterior e próximo
- **Navegação**: Bidirecional (frente e trás)

### 3. Exemplos Incrementais
- **`exemplo0.c`**: Conceitos básicos e primeiro nó
- **`exemplo1.c`**: Inserção no início
- **`exemplo2.c`**: Inserção no final
- **`exemplo3.c`**: Remoção de elementos
- **`exemplo4.c`**: Busca e navegação
- **`exemplo.c`**: Implementação completa

## 🏗️ Estruturas de Dados

### Lista Simplesmente Encadeada
```c
typedef struct Node {
    int data;           // Dados do nó
    struct Node* next;  // Ponteiro para o próximo nó
} Node;

typedef struct {
    Node* head;         // Ponteiro para o primeiro nó
    int size;          // Tamanho atual da lista
} LinkedList;
```

### Lista Duplamente Encadeada
```c
typedef struct DNode {
    int data;              // Dados do nó
    struct DNode* next;    // Ponteiro para o próximo nó
    struct DNode* prev;    // Ponteiro para o nó anterior
} DNode;

typedef struct {
    DNode* head;           // Ponteiro para o primeiro nó
    DNode* tail;           // Ponteiro para o último nó
    int size;             // Tamanho atual da lista
} DoublyLinkedList;
```

## ⚙️ Operações Fundamentais

### Lista Simplesmente Encadeada

#### Inserção
```c
// Inserir no início - O(1)
void insertAtBeginning(LinkedList* list, int data);

// Inserir no final - O(n)
void insertAtEnd(LinkedList* list, int data);

// Inserir em posição específica - O(n)
void insertAtPosition(LinkedList* list, int data, int position);
```

#### Remoção
```c
// Remover do início - O(1)
void removeFromBeginning(LinkedList* list);

// Remover do final - O(n)
void removeFromEnd(LinkedList* list);

// Remover por valor - O(n)
void removeByValue(LinkedList* list, int value);
```

#### Busca e Acesso
```c
// Buscar elemento - O(n)
Node* search(LinkedList* list, int value);

// Acessar por índice - O(n)
int getElement(LinkedList* list, int index);

// Exibir lista - O(n)
void displayList(LinkedList* list);
```

### Lista Duplamente Encadeada

#### Vantagens Adicionais
```c
// Inserir no final - O(1) (com ponteiro tail)
void insertAtEnd(DoublyLinkedList* list, int data);

// Remover do final - O(1) (com ponteiro tail)
void removeFromEnd(DoublyLinkedList* list);

// Navegar em ambas as direções
void displayForward(DoublyLinkedList* list);
void displayBackward(DoublyLinkedList* list);
```

## 📊 Análise de Complexidade

| Operação | Lista Simples | Lista Dupla | Array Dinâmico |
|----------|---------------|-------------|----------------|
| Inserção início | O(1) | O(1) | O(n) |
| Inserção final | O(n) | O(1)* | O(1)** |
| Remoção início | O(1) | O(1) | O(n) |
| Remoção final | O(n) | O(1)* | O(1) |
| Busca | O(n) | O(n) | O(n) |
| Acesso aleatório | O(n) | O(n) | O(1) |

*Com ponteiro tail  
**Amortizado

## 🔧 Vantagens e Desvantagens

### ✅ Vantagens das Listas Encadeadas
- **Tamanho Dinâmico**: Não há limite pré-definido
- **Inserção/Remoção Eficiente**: O(1) em posições conhecidas
- **Flexibilidade**: Fácil reorganização de elementos
- **Uso de Memória**: Aloca apenas o necessário

### ❌ Desvantagens das Listas Encadeadas
- **Overhead de Memória**: Ponteiros extras por nó
- **Acesso Sequencial**: Não há acesso direto por índice
- **Cache Performance**: Elementos não são contíguos
- **Complexidade**: Mais difícil de implementar que arrays

## 🚀 Aplicações Práticas

### 1. Sistemas Operacionais
- **Lista de Processos**: Gerenciamento dinâmico de processos
- **Gerenciamento de Memória**: Blocos livres e ocupados
- **Escalonamento**: Filas de processos prontos

### 2. Estruturas de Dados Avançadas
- **Implementação de Pilhas**: Stack baseada em lista
- **Implementação de Filas**: Queue com inserção/remoção eficiente
- **Grafos**: Lista de adjacências

### 3. Aplicações Comerciais
- **Playlist de Música**: Navegação entre músicas
- **Histórico de Navegação**: Lista de páginas visitadas
- **Carrinho de Compras**: Itens dinamicamente adicionados/removidos

### 4. Algoritmos
- **Merge Sort**: Divisão e conquista em listas
- **Detecção de Ciclos**: Algoritmo de Floyd (tortoise and hare)
- **Reversão**: Inversão de sequências

## 🛠️ Como Compilar e Executar

### Compilação Básica
```bash
# Lista simples
gcc -o lista_simples listaSimples.c
./lista_simples

# Lista dupla
gcc -o lista_dupla listaDupla.c
./lista_dupla
```

### Compilação com Debug
```bash
gcc -g -Wall -Wextra -o debug_lista listaSimples.c
gdb ./debug_lista
```

### Compilação dos Exemplos
```bash
# Compilar todos os exemplos
for i in {0..4}; do
    gcc -o exemplo$i exemplo$i.c
    ./exemplo$i
done
```

## 🎯 Exemplos de Implementação

### Criar e Inicializar Lista
```c
LinkedList* createList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->size = 0;
    return list;
}
```

### Inserção no Início
```c
void insertAtBeginning(LinkedList* list, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;
    list->size++;
}
```

### Busca com Retorno de Posição
```c
int findPosition(LinkedList* list, int value) {
    Node* current = list->head;
    int position = 0;
    
    while (current != NULL) {
        if (current->data == value) {
            return position;
        }
        current = current->next;
        position++;
    }
    
    return -1; // Não encontrado
}
```

### Reversão de Lista
```c
void reverseList(LinkedList* list) {
    Node* prev = NULL;
    Node* current = list->head;
    Node* next = NULL;
    
    while (current != NULL) {
        next = current->next;    // Armazenar próximo
        current->next = prev;    // Reverter o link
        prev = current;          // Mover prev
        current = next;          // Mover current
    }
    
    list->head = prev;          // Atualizar head
}
```

## 🧠 Padrões e Técnicas Avançadas

### 1. Técnica dos Dois Ponteiros
```c
// Encontrar o meio da lista
Node* findMiddle(LinkedList* list) {
    Node* slow = list->head;
    Node* fast = list->head;
    
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;
}
```

### 2. Detecção de Ciclos (Floyd's Algorithm)
```c
bool hasCycle(LinkedList* list) {
    Node* slow = list->head;
    Node* fast = list->head;
    
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) {
            return true; // Ciclo detectado
        }
    }
    
    return false; // Sem ciclo
}
```

### 3. Merge de Listas Ordenadas
```c
LinkedList* mergeSortedLists(LinkedList* list1, LinkedList* list2) {
    LinkedList* merged = createList();
    Node* current1 = list1->head;
    Node* current2 = list2->head;
    
    while (current1 != NULL && current2 != NULL) {
        if (current1->data <= current2->data) {
            insertAtEnd(merged, current1->data);
            current1 = current1->next;
        } else {
            insertAtEnd(merged, current2->data);
            current2 = current2->next;
        }
    }
    
    // Adicionar elementos restantes
    while (current1 != NULL) {
        insertAtEnd(merged, current1->data);
        current1 = current1->next;
    }
    
    while (current2 != NULL) {
        insertAtEnd(merged, current2->data);
        current2 = current2->next;
    }
    
    return merged;
}
```

## 🤔 Questões para Reflexão

1. **Análise**: Por que listas encadeadas são mais eficientes para inserções/remoções frequentes em comparação com arrays?

2. **Implementação**: Como você implementaria uma função para encontrar o k-ésimo elemento do final da lista em uma única passada?

3. **Memória**: Calcule o overhead de memória de uma lista encadeada versus um array para armazenar 1000 inteiros.

4. **Algoritmos**: Explique como o algoritmo de Floyd para detecção de ciclos funciona matematicamente.

5. **Design**: Quando você escolheria uma lista duplamente encadeada em vez de uma lista simplesmente encadeada?

## 📋 Exercícios Práticos

### Nível Básico
1. Implemente uma função que conte o número de nós na lista
2. Crie uma função que encontre o maior elemento da lista
3. Desenvolva uma função que remova todos os elementos duplicados

### Nível Intermediário
4. Implemente uma função que rotacione a lista k posições para a direita
5. Crie uma função que intercale duas listas ordenadas
6. Desenvolva uma função que agrupe nós com valores pares e ímpares

### Nível Avançado
7. Implemente o algoritmo merge sort para listas encadeadas
8. Crie uma função que detecte e remova ciclos em uma lista
9. Desenvolva uma estrutura de lista encadeada thread-safe

### Desafios
10. Implemente uma lista encadeada que mantenha referências para elementos frequentemente acessados
11. Crie uma lista encadeada com compressão automática de elementos duplicados consecutivos
12. Desenvolva uma lista encadeada com snapshots (versioning)

## 🔍 Debugging e Testes

### Problemas Comuns
- **Memory Leaks**: Não liberar nós removidos
- **Segmentation Fault**: Acessar ponteiros nulos
- **Ponteiros Perdidos**: Perder referência para nós
- **Ciclos Infinitos**: Criar referências circulares

### Técnicas de Debug
```c
// Função para verificar integridade da lista
bool verifyListIntegrity(LinkedList* list) {
    if (list->size == 0 && list->head != NULL) return false;
    if (list->size > 0 && list->head == NULL) return false;
    
    int count = 0;
    Node* current = list->head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    
    return count == list->size;
}
```

### Ferramentas Úteis
```bash
# Verificar vazamentos de memória
valgrind --leak-check=full --track-origins=yes ./programa

# Debug step-by-step
gdb ./programa
(gdb) break insertAtBeginning
(gdb) run
(gdb) print *list
(gdb) step
```

## 📚 Referências e Leituras Complementares

- **Livros**:
  - Cormen, T. H. et al. *Introduction to Algorithms*. MIT Press.
  - Sedgewick, R. *Algorithms in C*. Addison-Wesley.
  - Tenenbaum, A. M. *Data Structures Using C*. Prentice Hall.

- **Artigos**:
  - Floyd, R. W. (1967). "Nondeterministic Algorithms". *Journal of the ACM*.
  - Knuth, D. E. (1973). "Sorting and Searching". *The Art of Computer Programming*.

- **Recursos Online**:
  - GeeksforGeeks: Data Structures
  - CS50: Harvard's Computer Science Course
  - MIT OpenCourseWare: Introduction to Algorithms