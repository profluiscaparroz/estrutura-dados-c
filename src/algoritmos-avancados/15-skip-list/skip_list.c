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
