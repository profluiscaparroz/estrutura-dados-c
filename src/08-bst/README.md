# Árvore Binária de Busca (Binary Search Tree - BST)

## 📋 Visão Geral

A Árvore Binária de Busca (BST - Binary Search Tree) é uma das estruturas de dados fundamentais em ciência da computação, representando um caso particular de árvores binárias com propriedades específicas que permitem operações de busca, inserção e remoção eficientes. Esta estrutura combina os benefícios do acesso ordenado de arrays com a flexibilidade dinâmica de listas encadeadas, tornando-se essencial em inúmeras aplicações computacionais modernas.

### Importância e Aplicações

As Árvores Binárias de Busca são onipresentes em sistemas computacionais por oferecerem um equilíbrio entre eficiência e simplicidade de implementação:

- **Sistemas de Banco de Dados**: Índices B-Tree e suas variantes são derivadas de BSTs para busca eficiente em grandes volumes de dados
- **Compiladores**: Tabelas de símbolos utilizam BSTs para armazenar e recuperar identificadores rapidamente
- **Sistemas de Arquivos**: Estruturas de diretório em sistemas operacionais frequentemente empregam árvores de busca
- **Bibliotecas Padrão**: Implementações de `map` e `set` em C++ STL baseiam-se em árvores balanceadas (Red-Black Trees)
- **Roteadores de Rede**: Tabelas de roteamento utilizam estruturas derivadas de BSTs para decisões rápidas
- **Sistemas de Autocompletar**: Sugestões em tempo real em motores de busca e editores de texto
- **Gerenciamento de Memória**: Alocadores de memória utilizam árvores para rastrear blocos livres
- **Análise de Dados**: Ordenação e ranking de elementos em estruturas dinâmicas

### Fundamentação Teórica

Do ponto de vista da teoria da computação, as BSTs representam uma aplicação elegante do paradigma **dividir para conquistar** em estruturas de dados dinâmicas. Diferentemente de arrays ordenados que oferecem busca O(log n) mas inserção O(n), as BSTs mantêm complexidade logarítmica para todas as operações principais quando a árvore permanece balanceada.

A eficiência das BSTs está intrinsecamente relacionada à sua **altura**. Uma árvore balanceada com n nós possui altura O(log n), garantindo que operações percorram no máximo log₂(n) níveis. Por outro lado, inserções em ordem específica podem degenerar a árvore em uma lista encadeada com altura O(n), degradando todas as operações.

Este módulo apresenta uma implementação completa e documentada de BST em C, com análise detalhada de complexidade, fundamentos matemáticos, casos de uso e respostas às perguntas mais frequentes.

## 🌳 Conceito e Definição Formal

### Definição Matemática

Uma **Árvore Binária de Busca** é uma estrutura de dados hierárquica que satisfaz as seguintes propriedades:

1. **Propriedade de Ordenação**: Para cada nó N na árvore:
   - Todos os nós na subárvore esquerda de N contêm valores **menores** que o valor de N
   - Todos os nós na subárvore direita de N contêm valores **maiores** que o valor de N
   
2. **Propriedade Recursiva**: Cada subárvore (esquerda e direita) também é uma BST

Formalmente, seja T uma árvore binária e N um nó qualquer em T. Definimos:
```
∀ n_left ∈ subárvore_esquerda(N): valor(n_left) < valor(N)
∀ n_right ∈ subárvore_direita(N): valor(n_right) > valor(N)
```

### Propriedades Estruturais

1. **Altura**: O comprimento do caminho mais longo da raiz até uma folha
   - Árvore balanceada: h = ⌊log₂(n)⌋
   - Árvore degenerada: h = n - 1
   
2. **Número de Nós**: Para uma árvore de altura h:
   - Mínimo: h + 1 nós (lista encadeada)
   - Máximo: 2^(h+1) - 1 nós (árvore completa)

3. **Travessia In-Order**: Percorrer uma BST em ordem simétrica (esquerda-raiz-direita) produz os elementos em **ordem crescente**

### Vantagens Acadêmicas

1. **Eficiência Temporal**: Operações fundamentais em O(log n) no caso médio
2. **Dinamismo**: Suporta inserções e remoções sem reorganização completa da estrutura
3. **Ordenação Implícita**: Mantém elementos ordenados sem custo adicional
4. **Acesso Flexível**: Permite busca por valor, mínimo, máximo, predecessor e sucessor
5. **Base Teórica**: Fundamento para estruturas avançadas (AVL, Red-Black, B-Trees)

### Desvantagens e Limitações

1. **Degeneração**: Pode degenerar em lista encadeada O(n) com inserções ordenadas
2. **Ausência de Balanceamento**: Não garante altura logarítmica automaticamente
3. **Complexidade de Remoção**: Remoção de nós com dois filhos requer cuidados especiais
4. **Overhead de Ponteiros**: Cada nó requer dois ponteiros adicionais (esquerda/direita)
5. **Sensibilidade à Ordem**: Performance dependente da ordem de inserção

## 📊 Análise de Complexidade Computacional

### Complexidade das Operações Principais

A análise de complexidade de uma BST depende crucialmente da **altura** da árvore. Apresentamos a análise para os três cenários principais:

#### 1. Busca (Search)

**Descrição**: Localizar um valor específico na árvore

**Algoritmo**: Comparação sucessiva começando da raiz, descendo para esquerda ou direita

**Complexidade Temporal**:
- **Melhor Caso**: O(1) - elemento está na raiz
- **Caso Médio**: O(log n) - árvore razoavelmente balanceada
- **Pior Caso**: O(n) - árvore degenerada em lista

**Complexidade Espacial**:
- **Implementação Iterativa**: O(1) - apenas variáveis auxiliares
- **Implementação Recursiva**: O(h) - pilha de chamadas, onde h é a altura

**Análise Matemática**:
```
Número de comparações no caso médio = log₂(n) + 1
Probabilidade de encontrar em profundidade d: P(d) = 2^d / n (árvore completa)
```

#### 2. Inserção (Insert)

**Descrição**: Adicionar um novo valor mantendo a propriedade BST

**Algoritmo**: Busca pela posição correta + criação de novo nó folha

**Complexidade Temporal**:
- **Melhor Caso**: O(1) - inserção na raiz de árvore vazia
- **Caso Médio**: O(log n) - árvore balanceada
- **Pior Caso**: O(n) - inserção em árvore degenerada

**Complexidade Espacial**:
- **Implementação Iterativa**: O(1)
- **Implementação Recursiva**: O(h)
- **Espaço para novo nó**: O(1) constante por inserção

**Análise Amortizada**:
Inserir n elementos em sequência aleatória resulta em altura esperada O(log n), portanto:
```
Custo total de n inserções = O(n log n)
Custo amortizado por inserção = O(log n)
```

#### 3. Remoção (Delete)

**Descrição**: Remover um nó mantendo a propriedade BST

**Algoritmo**: Localizar nó + tratamento de três casos (0, 1 ou 2 filhos)

**Complexidade Temporal**:
- **Melhor Caso**: O(1) - remoção de folha na raiz (árvore unitária)
- **Caso Médio**: O(log n) - árvore balanceada
- **Pior Caso**: O(n) - árvore degenerada

**Casos de Remoção**:
1. **Nó Folha** (0 filhos): O(log n) busca + O(1) remoção
2. **Nó com 1 Filho**: O(log n) busca + O(1) reconexão
3. **Nó com 2 Filhos**: O(log n) busca + O(log n) encontrar sucessor + O(1) substituição

**Complexidade Espacial**: O(h) para chamadas recursivas

#### 4. Travessias (Traversals)

**Descrição**: Visitar todos os nós da árvore em ordem específica

**Tipos**:
- **In-Order** (esquerda-raiz-direita): Produz sequência ordenada
- **Pre-Order** (raiz-esquerda-direita): Útil para copiar árvores
- **Post-Order** (esquerda-direita-raiz): Útil para liberar memória

**Complexidade Temporal**: O(n) - cada nó visitado exatamente uma vez
**Complexidade Espacial**: 
- **Iterativa com pilha explícita**: O(h)
- **Recursiva**: O(h) pilha de chamadas

#### 5. Operações Auxiliares

| Operação | Descrição | Complexidade Temporal | Complexidade Espacial |
|----------|-----------|----------------------|----------------------|
| **Mínimo** | Encontrar menor valor | O(h) | O(1) iterativo, O(h) recursivo |
| **Máximo** | Encontrar maior valor | O(h) | O(1) iterativo, O(h) recursivo |
| **Sucessor** | Próximo elemento em ordem | O(h) | O(1) |
| **Predecessor** | Elemento anterior em ordem | O(h) | O(1) |
| **Altura** | Calcular altura da árvore | O(n) | O(h) |
| **Tamanho** | Contar número de nós | O(n) | O(h) |

### Análise Probabilística

Em uma BST construída com n inserções de valores aleatórios uniformemente distribuídos:

**Altura Esperada**: 
```
E[h] ≈ 2.99 × log₂(n) ≈ 4.31 × ln(n)
```

**Custo Médio de Busca**:
```
C(n) ≈ 2 × ln(n) ≈ 1.39 × log₂(n)
```

Estes resultados, demonstrados por análise combinatória, indicam que árvores aleatórias tendem a ser razoavelmente balanceadas.

### Comparação com Outras Estruturas

| Estrutura | Busca | Inserção | Remoção | Ordenação |
|-----------|-------|----------|---------|-----------|
| **Array Ordenado** | O(log n) | O(n) | O(n) | O(n log n) |
| **Array Não-Ordenado** | O(n) | O(1) | O(n) | O(n log n) |
| **Lista Encadeada** | O(n) | O(1)* | O(n) | O(n log n) |
| **BST (balanceada)** | O(log n) | O(log n) | O(log n) | O(n) |
| **BST (degenerada)** | O(n) | O(n) | O(n) | O(n²) |
| **Hash Table** | O(1)* | O(1)* | O(1)* | N/A |
| **AVL Tree** | O(log n) | O(log n) | O(log n) | O(n) |

\* Caso médio com boas funções hash ou conhecimento da posição

### Teoremas Fundamentais

**Teorema 1 (Altura de BST Aleatória)**:
A altura de uma BST construída por inserções aleatórias de n chaves distintas é O(log n) com alta probabilidade.

**Teorema 2 (Custo de Busca)**:
O custo médio de busca bem-sucedida em uma BST aleatória é Θ(log n).

**Teorema 3 (Caminho Interno)**:
O comprimento do caminho interno médio de uma BST aleatória de n nós é aproximadamente 1.39n log₂(n).

## 💻 Estrutura de Dados

### Definição do Nó

```c
typedef struct Node {
    int data;              // Valor armazenado no nó
    struct Node* left;     // Ponteiro para subárvore esquerda
    struct Node* right;    // Ponteiro para subárvore direita
} Node;
```

**Observações**:
- Estrutura autoreferenciada (ponteiros para o mesmo tipo)
- Campo `data` pode ser generalizado com `void*` ou templates em C++
- Pode incluir ponteiro para pai em implementações avançadas

### Variante com Ponteiro para Pai

```c
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    struct Node* parent;   // Facilita operações de sucessor/predecessor
} Node;
```

**Vantagens**: Simplifica cálculo de sucessor e predecessor sem recursão
**Desvantagens**: Overhead de memória (33% mais ponteiros)

## 🔧 Operações Principais

### 1. Criação de Nó

```c
Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Erro de alocação de memória\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}
```

**Importância**: Inicialização correta evita comportamento indefinido
**Verificação de Erro**: Essencial em sistemas críticos

### 2. Inserção

**Abordagem Recursiva**:
```c
Node* insert(Node* root, int data) {
    // Caso base: posição encontrada
    if (root == NULL) {
        return create_node(data);
    }
    
    // Recursão: descer pela árvore
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    // Se data == root->data, ignorar (sem duplicatas)
    
    return root;
}
```

**Invariante**: A propriedade BST é mantida após cada inserção

**Abordagem Iterativa** (mais eficiente em espaço):
```c
Node* insert_iterative(Node* root, int data) {
    Node* new_node = create_node(data);
    
    if (root == NULL) {
        return new_node;
    }
    
    Node* current = root;
    Node* parent = NULL;
    
    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else if (data > current->data) {
            current = current->right;
        } else {
            free(new_node); // Duplicata
            return root;
        }
    }
    
    if (data < parent->data) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }
    
    return root;
}
```

### 3. Busca

**Abordagem Recursiva**:
```c
Node* search(Node* root, int data) {
    // Casos base
    if (root == NULL || root->data == data) {
        return root;
    }
    
    // Recursão baseada na propriedade BST
    if (data < root->data) {
        return search(root->left, data);
    }
    
    return search(root->right, data);
}
```

**Abordagem Iterativa**:
```c
Node* search_iterative(Node* root, int data) {
    while (root != NULL && root->data != data) {
        if (data < root->data) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return root;
}
```

### 4. Encontrar Mínimo e Máximo

```c
// Menor valor: nó mais à esquerda
Node* find_min(Node* root) {
    if (root == NULL) {
        return NULL;
    }
    
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Maior valor: nó mais à direita
Node* find_max(Node* root) {
    if (root == NULL) {
        return NULL;
    }
    
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}
```

### 5. Remoção (Operação mais Complexa)

```c
Node* delete_node(Node* root, int data) {
    if (root == NULL) {
        return root;
    }
    
    // Fase 1: Localizar o nó
    if (data < root->data) {
        root->left = delete_node(root->left, data);
    } else if (data > root->data) {
        root->right = delete_node(root->right, data);
    } else {
        // Nó encontrado - Fase 2: Remover
        
        // Caso 1: Nó folha ou com um filho à direita
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        
        // Caso 2: Nó com um filho à esquerda
        if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        
        // Caso 3: Nó com dois filhos
        // Estratégia: Substituir pelo sucessor in-order
        Node* successor = find_min(root->right);
        root->data = successor->data;
        root->right = delete_node(root->right, successor->data);
    }
    
    return root;
}
```

**Estratégias de Remoção com Dois Filhos**:
1. **Sucessor In-Order**: Menor valor da subárvore direita (implementado acima)
2. **Predecessor In-Order**: Maior valor da subárvore esquerda (alternativa)

Ambas mantêm a propriedade BST após remoção.

### 6. Travessias

**In-Order (Esquerda-Raiz-Direita)**: Ordem Crescente
```c
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}
```

**Pre-Order (Raiz-Esquerda-Direita)**: Útil para copiar estrutura
```c
void preorder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}
```

**Post-Order (Esquerda-Direita-Raiz)**: Útil para liberar memória
```c
void postorder(Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}
```

### 7. Destruição da Árvore

```c
void destroy_tree(Node* root) {
    if (root != NULL) {
        destroy_tree(root->left);   // Liberar subárvore esquerda
        destroy_tree(root->right);  // Liberar subárvore direita
        free(root);                 // Liberar nó atual
    }
}
```

**Importante**: Usar travessia post-order para evitar acessar memória liberada

## 📚 Exemplo Completo de Uso

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    Node* root = NULL;
    
    // Construindo a árvore
    printf("=== Construção da BST ===\n");
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(values) / sizeof(values[0]);
    
    for (int i = 0; i < n; i++) {
        root = insert(root, values[i]);
        printf("Inserido: %d\n", values[i]);
    }
    
    // Travessia in-order (ordem crescente)
    printf("\n=== Travessia In-Order ===\n");
    inorder(root);
    printf("\n");
    
    // Buscas
    printf("\n=== Operações de Busca ===\n");
    int search_value = 40;
    Node* found = search(root, search_value);
    if (found != NULL) {
        printf("Valor %d encontrado!\n", search_value);
    } else {
        printf("Valor %d não encontrado.\n", search_value);
    }
    
    // Mínimo e Máximo
    Node* min = find_min(root);
    Node* max = find_max(root);
    printf("Valor mínimo: %d\n", min->data);
    printf("Valor máximo: %d\n", max->data);
    
    // Remoção
    printf("\n=== Teste de Remoção ===\n");
    root = delete_node(root, 20);
    printf("Após remover 20: ");
    inorder(root);
    printf("\n");
    
    root = delete_node(root, 30);
    printf("Após remover 30: ");
    inorder(root);
    printf("\n");
    
    root = delete_node(root, 50);
    printf("Após remover 50: ");
    inorder(root);
    printf("\n");
    
    // Limpeza
    destroy_tree(root);
    
    return 0;
}
```

**Saída Esperada**:
```
=== Construção da BST ===
Inserido: 50
Inserido: 30
Inserido: 70
Inserido: 20
Inserido: 40
Inserido: 60
Inserido: 80

=== Travessia In-Order ===
20 30 40 50 60 70 80

=== Operações de Busca ===
Valor 40 encontrado!
Valor mínimo: 20
Valor máximo: 80

=== Teste de Remoção ===
Após remover 20: 30 40 50 60 70 80
Após remover 30: 40 50 60 70 80
Após remover 50: 40 60 70 80
```

## ❓ Perguntas Frequentes (FAQ)

### 1. Por que usar BST ao invés de arrays ordenados?

**Resposta Completa**:

Arrays ordenados oferecem busca binária em O(log n), mas sofrem com inserções e remoções em O(n) devido ao deslocamento de elementos. BSTs mantêm O(log n) para todas as operações principais quando balanceadas.

**Análise Quantitativa**:
- Para **n = 1.000.000** elementos:
  - Array: Inserção/Remoção ≈ 1 milhão de operações
  - BST: Inserção/Remoção ≈ 20 operações (log₂(1.000.000) ≈ 20)

**Quando preferir Arrays**:
- Dados estáticos (poucas modificações)
- Requisitos rigorosos de uso de memória
- Necessidade de acesso por índice O(1)

**Quando preferir BSTs**:
- Dados dinâmicos (frequentes inserções/remoções)
- Requisitos de ordenação implícita
- Operações de range queries (busca por intervalo)

### 2. Como evitar que uma BST degenere em lista encadeada?

**Resposta Completa**:

A degeneração ocorre quando inserções seguem ordem específica (crescente/decrescente), resultando em altura O(n). Existem três abordagens principais:

**1. Aleatorização da Entrada**:
```c
// Embaralhar valores antes de inserir
void shuffle(int arr[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}
```

**2. Árvores Auto-Balanceadas**:
- **AVL Trees**: Balanceamento rigoroso (altura sempre O(log n))
- **Red-Black Trees**: Balanceamento relaxado, mais eficiente em modificações
- **Splay Trees**: Auto-ajuste por acessos frequentes

**3. Reconstrução Periódica**:
```c
// Reconstruir BST de array ordenado (árvore balanceada)
Node* build_balanced_bst(int arr[], int start, int end) {
    if (start > end) {
        return NULL;
    }
    
    int mid = (start + end) / 2;
    Node* root = create_node(arr[mid]);
    
    root->left = build_balanced_bst(arr, start, mid - 1);
    root->right = build_balanced_bst(arr, mid + 1, end);
    
    return root;
}
```

**Custo da Reconstrução**: O(n) tempo e espaço

### 3. Qual a diferença entre BST e árvores balanceadas (AVL, Red-Black)?

**Resposta Completa**:

| Característica | BST | AVL Tree | Red-Black Tree |
|----------------|-----|----------|----------------|
| **Garantia de Balanceamento** | Nenhuma | Rigorosa | Relaxada |
| **Altura Máxima** | O(n) | 1.44 log(n) | 2 log(n) |
| **Busca** | O(h) | O(log n) | O(log n) |
| **Inserção** | O(h) | O(log n) | O(log n) |
| **Remoção** | O(h) | O(log n) | O(log n) |
| **Rotações por Inserção** | 0 | ≤ 2 | ≤ 2 |
| **Rotações por Remoção** | 0 | O(log n) | ≤ 3 |
| **Complexidade de Implementação** | Simples | Média | Alta |
| **Uso de Memória** | 2 ponteiros/nó | 2 ponteiros + altura/balanço | 2 ponteiros + bit de cor |

**AVL Trees**:
- **Vantagem**: Busca mais rápida (árvore mais balanceada)
- **Desvantagem**: Mais rotações em inserção/remoção

**Red-Black Trees**:
- **Vantagem**: Menos rotações (melhor para modificações frequentes)
- **Desvantagem**: Busca ligeiramente mais lenta que AVL
- **Uso**: Biblioteca padrão C++ STL (`std::map`, `std::set`)

**BST Simples**:
- **Vantagem**: Implementação simples, eficiente para dados aleatórios
- **Desvantagem**: Sem garantias de performance no pior caso

### 4. Como calcular a altura de uma BST?

**Resposta Completa**:

```c
int tree_height(Node* root) {
    if (root == NULL) {
        return -1;  // Convenção: altura de árvore vazia é -1
                    // Alternativa: retornar 0 (altura de árvore com 1 nó = 0)
    }
    
    int left_height = tree_height(root->left);
    int right_height = tree_height(root->right);
    
    return 1 + (left_height > right_height ? left_height : right_height);
}
```

**Complexidade**: O(n) - visita cada nó uma vez

**Convenções**:
- Altura de árvore vazia: -1 (nós contados) ou 0 (níveis contados)
- Altura de folha: 0
- Altura de raiz com filhos: max(altura_esquerda, altura_direita) + 1

**Cálculo de Profundidade de um Nó**:
```c
int node_depth(Node* root, int value, int depth) {
    if (root == NULL) {
        return -1;  // Valor não encontrado
    }
    
    if (root->data == value) {
        return depth;
    }
    
    if (value < root->data) {
        return node_depth(root->left, value, depth + 1);
    }
    
    return node_depth(root->right, value, depth + 1);
}
```

### 5. É possível ter duplicatas em uma BST?

**Resposta Completa**:

Sim, existem três abordagens principais para lidar com valores duplicados:

**1. Proibir Duplicatas** (mais comum):
```c
Node* insert(Node* root, int data) {
    if (root == NULL) {
        return create_node(data);
    }
    
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    // Se data == root->data, não fazer nada (ignorar)
    
    return root;
}
```

**2. Permitir Duplicatas à Direita** (ou à esquerda):
```c
Node* insert_with_duplicates(Node* root, int data) {
    if (root == NULL) {
        return create_node(data);
    }
    
    if (data <= root->data) {  // <= ao invés de <
        root->left = insert_with_duplicates(root->left, data);
    } else {
        root->right = insert_with_duplicates(root->right, data);
    }
    
    return root;
}
```

**3. Contador de Frequência**:
```c
typedef struct Node {
    int data;
    int count;  // Número de ocorrências
    struct Node* left;
    struct Node* right;
} Node;

Node* insert_with_count(Node* root, int data) {
    if (root == NULL) {
        Node* node = create_node(data);
        node->count = 1;
        return node;
    }
    
    if (data == root->data) {
        root->count++;
    } else if (data < root->data) {
        root->left = insert_with_count(root->left, data);
    } else {
        root->right = insert_with_count(root->right, data);
    }
    
    return root;
}
```

**Comparação das Abordagens**:
- **Sem Duplicatas**: Mais simples, comportamento previsível
- **Duplicatas Permitidas**: Árvore pode ficar desbalanceada com muitas duplicatas
- **Contador**: Mais eficiente em memória, melhor para multisets

### 6. Como verificar se uma árvore binária é uma BST válida?

**Resposta Completa**:

Verificação incorreta (comum mas falha):
```c
// INCORRETO: Apenas verifica propriedade local
bool is_bst_wrong(Node* root) {
    if (root == NULL) return true;
    
    if (root->left != NULL && root->left->data > root->data)
        return false;
    if (root->right != NULL && root->right->data < root->data)
        return false;
    
    return is_bst_wrong(root->left) && is_bst_wrong(root->right);
}
```

**Por que falha?** Exemplo:
```
      10
     /  \
    5   15
   / \
  1  20  <- 20 > 10 viola BST, mas verifica apenas 20 > 5
```

**Verificação Correta com Limites**:
```c
bool is_bst_helper(Node* root, long min, long max) {
    if (root == NULL) {
        return true;
    }
    
    // Verificar se valor está dentro do intervalo válido
    if (root->data <= min || root->data >= max) {
        return false;
    }
    
    // Verificar subárvores com intervalos atualizados
    return is_bst_helper(root->left, min, root->data) &&
           is_bst_helper(root->right, root->data, max);
}

bool is_bst(Node* root) {
    return is_bst_helper(root, LONG_MIN, LONG_MAX);
}
```

**Abordagem Alternativa (In-Order)**:
```c
bool is_bst_inorder(Node* root, int* prev) {
    if (root == NULL) {
        return true;
    }
    
    // Verificar subárvore esquerda
    if (!is_bst_inorder(root->left, prev)) {
        return false;
    }
    
    // Verificar se valor atual é maior que anterior
    if (*prev >= root->data) {
        return false;
    }
    
    *prev = root->data;
    
    // Verificar subárvore direita
    return is_bst_inorder(root->right, prev);
}

bool validate_bst(Node* root) {
    int prev = INT_MIN;
    return is_bst_inorder(root, &prev);
}
```

**Complexidade**: O(n) para ambas abordagens

### 7. Como encontrar o k-ésimo menor elemento em uma BST?

**Resposta Completa**:

**Abordagem 1: In-Order com Contador**:
```c
void kth_smallest_helper(Node* root, int k, int* count, int* result) {
    if (root == NULL || *count >= k) {
        return;
    }
    
    // Processar subárvore esquerda
    kth_smallest_helper(root->left, k, count, result);
    
    // Processar nó atual
    (*count)++;
    if (*count == k) {
        *result = root->data;
        return;
    }
    
    // Processar subárvore direita
    kth_smallest_helper(root->right, k, count, result);
}

int kth_smallest(Node* root, int k) {
    int count = 0;
    int result = -1;
    kth_smallest_helper(root, k, &count, &result);
    return result;
}
```

**Complexidade**: O(k) no melhor caso, O(n) no pior caso

**Abordagem 2: Manter Tamanho de Subárvores**:
```c
typedef struct Node {
    int data;
    int size;  // Número de nós na subárvore (incluindo o próprio)
    struct Node* left;
    struct Node* right;
} Node;

int kth_smallest_optimized(Node* root, int k) {
    if (root == NULL) {
        return -1;
    }
    
    int left_size = (root->left != NULL) ? root->left->size : 0;
    
    if (k <= left_size) {
        return kth_smallest_optimized(root->left, k);
    } else if (k == left_size + 1) {
        return root->data;
    } else {
        return kth_smallest_optimized(root->right, k - left_size - 1);
    }
}
```

**Complexidade**: O(h) = O(log n) em árvore balanceada

**Trade-off**: Segunda abordagem requer manutenção do campo `size` durante inserções/remoções

### 8. Como converter uma BST em uma lista duplamente encadeada ordenada?

**Resposta Completa**:

O objetivo é reorganizar os ponteiros left/right para formar uma lista circular duplamente encadeada.

```c
void tree_to_list_helper(Node* root, Node** head, Node** prev) {
    if (root == NULL) {
        return;
    }
    
    // Processar subárvore esquerda
    tree_to_list_helper(root->left, head, prev);
    
    // Processar nó atual
    if (*prev == NULL) {
        // Primeiro nó (menor)
        *head = root;
    } else {
        // Conectar com nó anterior
        (*prev)->right = root;
        root->left = *prev;
    }
    
    *prev = root;
    
    // Processar subárvore direita
    tree_to_list_helper(root->right, head, prev);
}

Node* tree_to_list(Node* root) {
    Node* head = NULL;
    Node* prev = NULL;
    
    tree_to_list_helper(root, &head, &prev);
    
    // Fazer lista circular (opcional)
    if (head != NULL && prev != NULL) {
        prev->right = head;
        head->left = prev;
    }
    
    return head;
}
```

**Complexidade**: O(n) tempo, O(h) espaço (pilha de recursão)

**Aplicação**: Conversão para estruturas lineares mantendo ordenação

### 9. Qual a diferença entre sucessor e predecessor em uma BST?

**Resposta Completa**:

**Sucessor**: Menor valor maior que o nó dado (próximo na ordem crescente)
**Predecessor**: Maior valor menor que o nó dado (anterior na ordem crescente)

**Encontrar Sucessor**:
```c
Node* find_successor(Node* root, Node* node) {
    // Caso 1: Nó tem subárvore direita
    if (node->right != NULL) {
        return find_min(node->right);
    }
    
    // Caso 2: Sucessor é ancestral
    Node* successor = NULL;
    while (root != NULL) {
        if (node->data < root->data) {
            successor = root;
            root = root->left;
        } else if (node->data > root->data) {
            root = root->right;
        } else {
            break;
        }
    }
    
    return successor;
}
```

**Encontrar Predecessor**:
```c
Node* find_predecessor(Node* root, Node* node) {
    // Caso 1: Nó tem subárvore esquerda
    if (node->left != NULL) {
        return find_max(node->left);
    }
    
    // Caso 2: Predecessor é ancestral
    Node* predecessor = NULL;
    while (root != NULL) {
        if (node->data > root->data) {
            predecessor = root;
            root = root->right;
        } else if (node->data < root->data) {
            root = root->left;
        } else {
            break;
        }
    }
    
    return predecessor;
}
```

**Exemplo**:
```
      50
     /  \
   30    70
   / \   / \
  20 40 60 80

Sucessor de 30: 40
Sucessor de 40: 50
Predecessor de 50: 40
Predecessor de 40: 30
```

**Complexidade**: O(h)

### 10. Como implementar range queries (busca por intervalo) em BST?

**Resposta Completa**:

Range query busca todos os valores no intervalo [min, max].

```c
void range_search(Node* root, int min, int max) {
    if (root == NULL) {
        return;
    }
    
    // Se valor atual é maior que min, pode haver valores na esquerda
    if (root->data > min) {
        range_search(root->left, min, max);
    }
    
    // Se valor está no intervalo, processar
    if (root->data >= min && root->data <= max) {
        printf("%d ", root->data);
    }
    
    // Se valor atual é menor que max, pode haver valores na direita
    if (root->data < max) {
        range_search(root->right, min, max);
    }
}
```

**Complexidade**: O(h + k) onde k é o número de elementos no intervalo

**Versão com Coleta de Resultados**:
```c
void range_search_collect(Node* root, int min, int max, int* result, int* index) {
    if (root == NULL) {
        return;
    }
    
    if (root->data > min) {
        range_search_collect(root->left, min, max, result, index);
    }
    
    if (root->data >= min && root->data <= max) {
        result[(*index)++] = root->data;
    }
    
    if (root->data < max) {
        range_search_collect(root->right, min, max, result, index);
    }
}
```

**Exemplo**:
```
Árvore: 20 30 40 50 60 70 80
range_search(root, 35, 65) retorna: 40 50 60
```

### 11. Como balancear uma BST desbalanceada?

**Resposta Completa**:

**Algoritmo**:
1. Extrair elementos em ordem (in-order traversal) → O(n)
2. Construir BST balanceada de array ordenado → O(n)

```c
// Passo 1: Extrair elementos em array
void store_inorder(Node* root, int arr[], int* index) {
    if (root == NULL) {
        return;
    }
    
    store_inorder(root->left, arr, index);
    arr[(*index)++] = root->data;
    store_inorder(root->right, arr, index);
}

// Passo 2: Construir BST balanceada
Node* build_balanced_tree(int arr[], int start, int end) {
    if (start > end) {
        return NULL;
    }
    
    int mid = start + (end - start) / 2;
    Node* root = create_node(arr[mid]);
    
    root->left = build_balanced_tree(arr, start, mid - 1);
    root->right = build_balanced_tree(arr, mid + 1, end);
    
    return root;
}

// Função principal
Node* balance_bst(Node* root) {
    if (root == NULL) {
        return NULL;
    }
    
    // Contar nós
    int n = count_nodes(root);
    int* arr = (int*)malloc(n * sizeof(int));
    int index = 0;
    
    // Extrair elementos ordenados
    store_inorder(root, arr, &index);
    
    // Destruir árvore antiga
    destroy_tree(root);
    
    // Construir árvore balanceada
    Node* balanced = build_balanced_tree(arr, 0, n - 1);
    
    free(arr);
    return balanced;
}
```

**Complexidade Total**: O(n) tempo, O(n) espaço

**Resultado**: Árvore com altura ⌊log₂(n)⌋

### 12. Como mesclar duas BSTs?

**Resposta Completa**:

**Abordagem 1: Inserção Direta** (simples mas ineficiente):
```c
Node* merge_bst_simple(Node* bst1, Node* bst2) {
    // Inserir todos os elementos de bst2 em bst1
    merge_insert(bst1, bst2);
    return bst1;
}

void merge_insert(Node* dest, Node* source) {
    if (source == NULL) return;
    
    merge_insert(dest, source->left);
    dest = insert(dest, source->data);
    merge_insert(dest, source->right);
}
```

**Complexidade**: O(n₁ × h₁ + n₂ × h₁) onde n₁, n₂ são tamanhos e h₁ é altura da primeira árvore

**Abordagem 2: Mesclar Arrays Ordenados** (eficiente):
```c
Node* merge_bst_optimal(Node* bst1, Node* bst2) {
    int n1 = count_nodes(bst1);
    int n2 = count_nodes(bst2);
    
    // Extrair arrays ordenados
    int* arr1 = (int*)malloc(n1 * sizeof(int));
    int* arr2 = (int*)malloc(n2 * sizeof(int));
    int idx1 = 0, idx2 = 0;
    
    store_inorder(bst1, arr1, &idx1);
    store_inorder(bst2, arr2, &idx2);
    
    // Mesclar arrays ordenados
    int* merged = (int*)malloc((n1 + n2) * sizeof(int));
    int k = 0, i = 0, j = 0;
    
    while (i < n1 && j < n2) {
        if (arr1[i] < arr2[j]) {
            merged[k++] = arr1[i++];
        } else {
            merged[k++] = arr2[j++];
        }
    }
    
    while (i < n1) merged[k++] = arr1[i++];
    while (j < n2) merged[k++] = arr2[j++];
    
    // Construir BST balanceada
    Node* result = build_balanced_tree(merged, 0, k - 1);
    
    free(arr1);
    free(arr2);
    free(merged);
    
    return result;
}
```

**Complexidade**: O(n₁ + n₂) tempo, O(n₁ + n₂) espaço
**Vantagem**: Resultado é BST balanceada

## 🛠️ Compilação e Execução

### Usando o Makefile

```bash
# Compilação padrão
make

# Executar testes
make test

# Compilação com debug
make debug

# Compilação otimizada (release)
make release

# Verificar memória com Valgrind
make memcheck

# Análise estática
make static-analysis

# Limpar arquivos compilados
make clean

# Ver ajuda
make help
```

### Compilação Manual

```bash
# Compilação básica
gcc -Wall -Wextra -std=c99 -o bst bst.c

# Com otimizações
gcc -Wall -Wextra -std=c99 -O2 -o bst bst.c

# Com debug
gcc -Wall -Wextra -std=c99 -g -o bst bst.c

# Executar
./bst
```

### Verificação de Memória

```bash
valgrind --leak-check=full --show-leak-kinds=all ./bst
```

## 📖 Referências Acadêmicas

1. **Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C.** (2009). *Introduction to Algorithms* (3rd ed.). MIT Press.
   - Capítulo 12: Binary Search Trees
   - Análise completa de complexidade e provas formais

2. **Knuth, D. E.** (1998). *The Art of Computer Programming, Volume 3: Sorting and Searching* (2nd ed.). Addison-Wesley.
   - Seção 6.2.2: Binary Tree Searching
   - Análise matemática detalhada de BSTs aleatórias

3. **Sedgewick, R., & Wayne, K.** (2011). *Algorithms* (4th ed.). Addison-Wesley.
   - Seção 3.2: Binary Search Trees
   - Implementações práticas e otimizações

4. **Aho, A. V., Hopcroft, J. E., & Ullman, J. D.** (1983). *Data Structures and Algorithms*. Addison-Wesley.
   - Fundamentos teóricos de estruturas hierárquicas

5. **Weiss, M. A.** (2014). *Data Structures and Algorithm Analysis in C* (2nd ed.). Pearson.
   - Implementações em C com análise de performance

6. **Goodrich, M. T., Tamassia, R., & Goldwasser, M. H.** (2014). *Data Structures and Algorithms in Python*. Wiley.
   - Análise comparativa de estruturas de busca

## 📝 Notas de Implementação

### Boas Práticas

1. **Verificação de Ponteiros Nulos**: Sempre verificar `root != NULL`
2. **Liberação de Memória**: Usar travessia post-order em `destroy_tree`
3. **Tratamento de Erro**: Verificar retorno de `malloc`
4. **Consistência**: Decidir convenção para duplicatas e documentar
5. **Recursão vs Iteração**: Preferir iterativo para economizar espaço quando possível

### Otimizações Avançadas

1. **Thread BST**: Ponteiros para sucessor/predecessor em nós folha
2. **Caching**: Armazenar altura ou tamanho de subárvore
3. **Lazy Deletion**: Marcar nós como deletados sem remover fisicamente
4. **Memory Pooling**: Pré-alocar blocos de nós para reduzir chamadas a `malloc`

### Limitações Conhecidas

1. Não há balanceamento automático
2. Performance degradada com inserções ordenadas
3. Overhead de ponteiros (16 bytes por nó em sistemas 64-bit)
4. Não thread-safe (requer sincronização para acesso concorrente)

## 🎓 Exercícios Propostos

1. **Básico**: Implementar função para contar o número de folhas
2. **Intermediário**: Implementar função para verificar se duas BSTs são idênticas
3. **Avançado**: Implementar serialização/desserialização de BST
4. **Desafio**: Implementar BST genérica com `void*` para qualquer tipo de dado
5. **Pesquisa**: Comparar performance de BST vs Hash Table para diferentes workloads

---

**Autor**: Estrutura de Dados em C  
**Data**: 2024  
**Licença**: Educacional  
**Repositório**: https://github.com/profluiscaparroz/estrutura-dados-c
