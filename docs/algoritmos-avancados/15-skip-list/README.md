# Aula de Ciência da Computação: Skip List – História, Funcionamento e Aplicações

## Introdução

A **Skip List** é uma estrutura de dados probabilística que permite busca, inserção e remoção de elementos em tempo logarítmico esperado, com uma implementação consideravelmente mais simples que árvores balanceadas como AVL ou Red-Black Trees. Foi inventada por William Pugh em 1990 como uma alternativa prática às estruturas de dados baseadas em árvores balanceadas.

---

## 1. História e Motivação

A Skip List foi introduzida por William Pugh no artigo **"Skip Lists: A Probabilistic Alternative to Balanced Trees"**, publicado na Communications of the ACM em junho de 1990. Pugh observou que, embora árvores balanceadas como AVL e Red-Black Trees fossem eficientes, sua implementação era complexa e propensa a erros.

Antes da Skip List, as principais estruturas para busca ordenada eram:

* **Listas Encadeadas Ordenadas**: Simples de implementar, mas com busca O(n), tornando-as impraticáveis para grandes volumes de dados.
* **Árvores Binárias de Busca Balanceadas (AVL, Red-Black)**: Oferecem busca em O(log n), mas com implementação complexa envolvendo rotações e balanceamento.
* **Árvores B e B+**: Eficientes para sistemas de banco de dados, mas também complexas e otimizadas para acesso em disco.

Segundo Pugh (1990), "Skip lists são estruturas de dados que usam randomização para alcançar balanceamento probabilístico ao invés de balanceamento rigorosamente imposto". A principal vantagem é a simplicidade: enquanto árvores balanceadas exigem operações de rotação e rebalanceamento complexas, Skip Lists utilizam níveis aleatórios para manter o desempenho logarítmico.

---

## 2. O que era feito antes da Skip List?

Antes da Skip List, as estruturas de dados para busca ordenada apresentavam trade-offs significativos:

* **Listas Ligadas Simples**: Fáceis de implementar, mas com tempo de busca linear O(n).
* **Arrays Ordenados**: Busca rápida com busca binária O(log n), mas inserções e remoções são custosas O(n) devido ao deslocamento de elementos.
* **Árvores AVL e Red-Black**: Garantem O(log n) para todas as operações, mas a complexidade de implementação é alta, especialmente para inserção e remoção.

A Skip List surgiu como uma solução que combina simplicidade de implementação com desempenho próximo ao das árvores balanceadas, usando probabilidade ao invés de estrutura rígida.

---

## 3. Como funciona a Skip List?

Uma Skip List é composta por múltiplas listas encadeadas sobrepostas:

* **Nível 0 (base)**: Contém todos os elementos em ordem.
* **Níveis superiores**: Contêm subconjuntos dos elementos, servindo como "expressos" para pular elementos durante a busca.

### Estrutura

Cada nó possui:
* Um valor (chave).
* Um vetor de ponteiros `forward[]`, onde `forward[i]` aponta para o próximo nó no nível `i`.

O número de níveis de um nó é determinado probabilisticamente no momento da inserção, usando uma distribuição geométrica. Tipicamente, um nó tem nível `i+1` com probabilidade `1/2` de ter nível `i`.

### Operações

* **Busca**: Começa no nível mais alto e, em cada passo, se o próximo nó tiver valor menor ou igual ao buscado, avança; caso contrário, desce um nível. A busca continua até encontrar o elemento ou atingir NULL.

* **Inserção**: Similar à busca, mas ao encontrar a posição correta, um novo nó é criado com um nível aleatório e inserido em todos os níveis necessários.

* **Remoção**: Busca o elemento e remove seus ponteiros de todos os níveis em que aparece.

---

## 4. Vantagens da Skip List

* **Simplicidade de Implementação**: Não requer operações complexas de rotação ou rebalanceamento como em árvores AVL/Red-Black.
* **Desempenho Esperado O(log n)**: Para busca, inserção e remoção, com alta probabilidade.
* **Estrutura Dinâmica**: Cresce e encolhe naturalmente sem necessidade de reorganização global.
* **Concorrência**: Mais fácil de paralelizar que árvores balanceadas, pois modificações são localizadas.
* **Iteração Ordenada**: Simples de percorrer os elementos em ordem, seguindo o nível base.

Segundo Pugh (1990), "algoritmos para skip lists são simples, eficientes e fáceis de implementar".

---

## 5. Desvantagens da Skip List

* **Uso de Memória**: Cada nó pode ter múltiplos ponteiros, aumentando o consumo de memória em comparação com listas simples.
* **Desempenho no Pior Caso**: Embora improvável, no pior caso, todas as operações podem degenerar para O(n) se os níveis forem mal distribuídos.
* **Aleatoriedade**: O desempenho depende da qualidade do gerador de números aleatórios.
* **Cache Locality**: Pode ter pior desempenho de cache comparado a estruturas contíguas como arrays, devido aos múltiplos ponteiros.

---

## 6. Aplicações Práticas

Skip Lists são utilizadas em diversos sistemas:

* **Redis**: Usa Skip Lists para implementar Sorted Sets (ZSET), permitindo operações rápidas de range queries.
* **LevelDB e RocksDB**: Usam Skip Lists nas memtables para inserções em memória antes de persistir em disco.
* **Java ConcurrentSkipListMap**: Implementação thread-safe de mapa ordenado na biblioteca padrão do Java.
* **Sistemas de Indexação**: Para manter índices ordenados com inserções e buscas rápidas.

---

## Onde a Skip List é usada no dia a dia?

1. **Bancos de dados em memória e caches distribuídos**:
   * Redis utiliza Skip Lists para estruturas de dados ordenadas (Sorted Sets), permitindo operações como busca por intervalo de scores de forma eficiente.

2. **Sistemas de armazenamento de dados**:
   * LevelDB e RocksDB usam Skip Lists para memtables, estruturas temporárias em memória que armazenam dados antes de serem escritos em disco.

3. **Concorrência e programação paralela**:
   * ConcurrentSkipListMap e ConcurrentSkipListSet em Java fornecem estruturas ordenadas thread-safe sem necessidade de locks globais.

4. **Sistemas de indexação**:
   * Utilizadas em índices de bases de dados onde inserções e buscas frequentes são necessárias.

---

## Como podemos melhorar a Skip List para uso prático?

Embora a Skip List já seja eficiente, algumas otimizações podem melhorá-la:

### 1. **Ajuste da probabilidade de nível**
* O valor padrão de `p = 0.5` (50% de chance de subir de nível) pode ser ajustado. Valores como `p = 0.25` reduzem o uso de memória, mas podem aumentar ligeiramente o tempo de busca.

### 2. **Limitação do número máximo de níveis**
* Definir um limite máximo de níveis (ex: `log₂(n)`) previne desperdício de memória e garante desempenho previsível.

### 3. **Otimização de cache**
* Usar arrays compactos ou pools de memória pode melhorar a localidade de cache, tornando acessos mais rápidos.

### 4. **Técnicas de lock-free para concorrência**
* Implementações lock-free permitem alta concorrência sem contenção, melhorando desempenho em sistemas multi-core.

### 5. **Compactação de nós**
* Armazenar múltiplas chaves em um único nó pode reduzir overhead de ponteiros e melhorar cache.

---

# Implementação da Skip List em Python

```python
import random

class Node:
    def __init__(self, key, level):
        self.key = key
        self.forward = [None] * (level + 1)

class SkipList:
    def __init__(self, max_level=16, p=0.5):
        self.max_level = max_level
        self.p = p
        self.header = Node(float('-inf'), max_level)
        self.level = 0
    
    def random_level(self):
        level = 0
        while random.random() < self.p and level < self.max_level:
            level += 1
        return level
    
    def search(self, key):
        current = self.header
        for i in range(self.level, -1, -1):
            while current.forward[i] and current.forward[i].key < key:
                current = current.forward[i]
        current = current.forward[0]
        if current and current.key == key:
            return True
        return False
    
    def insert(self, key):
        update = [None] * (self.max_level + 1)
        current = self.header
        
        for i in range(self.level, -1, -1):
            while current.forward[i] and current.forward[i].key < key:
                current = current.forward[i]
            update[i] = current
        
        current = current.forward[0]
        
        if current is None or current.key != key:
            new_level = self.random_level()
            
            if new_level > self.level:
                for i in range(self.level + 1, new_level + 1):
                    update[i] = self.header
                self.level = new_level
            
            new_node = Node(key, new_level)
            for i in range(new_level + 1):
                new_node.forward[i] = update[i].forward[i]
                update[i].forward[i] = new_node
    
    def delete(self, key):
        update = [None] * (self.max_level + 1)
        current = self.header
        
        for i in range(self.level, -1, -1):
            while current.forward[i] and current.forward[i].key < key:
                current = current.forward[i]
            update[i] = current
        
        current = current.forward[0]
        
        if current and current.key == key:
            for i in range(self.level + 1):
                if update[i].forward[i] != current:
                    break
                update[i].forward[i] = current.forward[i]
            
            while self.level > 0 and self.header.forward[self.level] is None:
                self.level -= 1
    
    def display(self):
        for level in range(self.level, -1, -1):
            print(f"Level {level}: ", end="")
            node = self.header.forward[level]
            while node:
                print(f"{node.key} ", end="")
                node = node.forward[level]
            print()

# Exemplo de uso
if __name__ == "__main__":
    skip_list = SkipList()
    
    # Inserir elementos
    for value in [3, 6, 7, 9, 12, 19, 17, 26, 21, 25]:
        skip_list.insert(value)
    
    skip_list.display()
    
    print(f"\nBuscar 19: {skip_list.search(19)}")
    print(f"Buscar 15: {skip_list.search(15)}")
    
    print("\nRemovendo 19...")
    skip_list.delete(19)
    skip_list.display()
```

---

# Implementação da Skip List em C

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX_LEVEL 16
#define P_FACTOR 0.5

// Estrutura do nó da Skip List
typedef struct Node {
    int key;
    struct Node **forward;  // Array de ponteiros para próximos nós
} Node;

// Estrutura da Skip List
typedef struct SkipList {
    int max_level;
    int level;
    Node *header;
} SkipList;

// Função para criar um novo nó
Node* createNode(int key, int level) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->forward = (Node **)malloc(sizeof(Node *) * (level + 1));
    for (int i = 0; i <= level; i++) {
        node->forward[i] = NULL;
    }
    return node;
}

// Função para criar uma Skip List
SkipList* createSkipList() {
    SkipList *list = (SkipList *)malloc(sizeof(SkipList));
    list->max_level = MAX_LEVEL;
    list->level = 0;
    list->header = createNode(-1, MAX_LEVEL);
    return list;
}

// Função para gerar nível aleatório
int randomLevel() {
    int level = 0;
    while ((rand() / (double)RAND_MAX) < P_FACTOR && level < MAX_LEVEL) {
        level++;
    }
    return level;
}

// Função para buscar uma chave
bool search(SkipList *list, int key) {
    Node *current = list->header;
    
    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->key < key) {
            current = current->forward[i];
        }
    }
    
    current = current->forward[0];
    
    if (current != NULL && current->key == key) {
        return true;
    }
    return false;
}

// Função para inserir uma chave
void insert(SkipList *list, int key) {
    Node *update[MAX_LEVEL + 1];
    Node *current = list->header;
    
    // Encontrar posição de inserção
    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->key < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }
    
    current = current->forward[0];
    
    // Se a chave não existe, inserir
    if (current == NULL || current->key != key) {
        int new_level = randomLevel();
        
        // Se o novo nível é maior que o nível atual
        if (new_level > list->level) {
            for (int i = list->level + 1; i <= new_level; i++) {
                update[i] = list->header;
            }
            list->level = new_level;
        }
        
        Node *new_node = createNode(key, new_level);
        
        // Inserir o nó atualizando ponteiros
        for (int i = 0; i <= new_level; i++) {
            new_node->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = new_node;
        }
        
        printf("Inserido: %d (nível %d)\n", key, new_level);
    }
}

// Função para deletar uma chave
void deleteKey(SkipList *list, int key) {
    Node *update[MAX_LEVEL + 1];
    Node *current = list->header;
    
    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->key < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }
    
    current = current->forward[0];
    
    if (current != NULL && current->key == key) {
        for (int i = 0; i <= list->level; i++) {
            if (update[i]->forward[i] != current) {
                break;
            }
            update[i]->forward[i] = current->forward[i];
        }
        
        free(current->forward);
        free(current);
        
        // Reduzir o nível se necessário
        while (list->level > 0 && list->header->forward[list->level] == NULL) {
            list->level--;
        }
        
        printf("Deletado: %d\n", key);
    }
}

// Função para exibir a Skip List
void display(SkipList *list) {
    printf("\n=== Skip List ===\n");
    for (int i = list->level; i >= 0; i--) {
        Node *node = list->header->forward[i];
        printf("Nível %d: ", i);
        while (node != NULL) {
            printf("%d ", node->key);
            node = node->forward[i];
        }
        printf("\n");
    }
    printf("\n");
}

// Função para liberar memória
void freeSkipList(SkipList *list) {
    Node *current = list->header->forward[0];
    Node *temp;
    
    while (current != NULL) {
        temp = current;
        current = current->forward[0];
        free(temp->forward);
        free(temp);
    }
    
    free(list->header->forward);
    free(list->header);
    free(list);
}

// Exemplo de uso
int main() {
    srand(time(NULL));
    
    SkipList *list = createSkipList();
    
    printf("=== Inserindo elementos ===\n");
    int values[] = {3, 6, 7, 9, 12, 19, 17, 26, 21, 25};
    int n = sizeof(values) / sizeof(values[0]);
    
    for (int i = 0; i < n; i++) {
        insert(list, values[i]);
    }
    
    display(list);
    
    printf("Buscar 19: %s\n", search(list, 19) ? "Encontrado" : "Não encontrado");
    printf("Buscar 15: %s\n", search(list, 15) ? "Encontrado" : "Não encontrado");
    
    printf("\n=== Deletando 19 ===\n");
    deleteKey(list, 19);
    
    display(list);
    
    printf("Buscar 19: %s\n", search(list, 19) ? "Encontrado" : "Não encontrado");
    
    freeSkipList(list);
    
    return 0;
}
```

---

## 7. Conclusão

A Skip List representa uma inovação elegante na área de estruturas de dados, oferecendo uma alternativa simples e eficiente às árvores balanceadas. Sua principal contribuição foi demonstrar que aleatoriedade pode ser usada efetivamente para alcançar bom desempenho sem complexidade algorítmica excessiva.

Como William Pugh (1990) afirmou: "Skip lists são uma alternativa probabilística simples às árvores balanceadas. Elas oferecem as mesmas garantias de desempenho esperado e são consideravelmente mais simples de implementar".

Desde sua introdução, Skip Lists têm sido amplamente adotadas em sistemas de alto desempenho, especialmente em aplicações que requerem estruturas de dados ordenadas com alta concorrência.

---

## Referências

* Pugh, W. (1990). **Skip Lists: A Probabilistic Alternative to Balanced Trees**. *Communications of the ACM*, 33(6), 668-676. DOI: [10.1145/78973.78977](https://doi.org/10.1145/78973.78977)

* Pugh, W. (1998). **Concurrent Maintenance of Skip Lists**. Technical Report CS-TR-3222, University of Maryland.

* Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009). *Introduction to Algorithms* (3rd ed.). MIT Press.

* Redis Documentation. **Sorted Sets Implementation**. Disponível em: https://redis.io/topics/data-types

* Java Documentation. **ConcurrentSkipListMap**. Oracle. Disponível em: https://docs.oracle.com/javase/8/docs/api/java/util/concurrent/ConcurrentSkipListMap.html
