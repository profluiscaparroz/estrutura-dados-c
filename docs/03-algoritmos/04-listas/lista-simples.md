# Lista Simplesmente Encadeada

Conceito
- Cada nó aponta para o próximo.

Operações básicas
```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int size;
} LinkedList;

LinkedList* create_list() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->size = 0;
    return list;
}

void insert_at_beginning(LinkedList* list, int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = list->head;
    list->head = new_node;
    list->size++;
}

void insert_at_end(LinkedList* list, int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    list->size++;
}

bool delete_node(LinkedList* list, int data) {
    if (list->head == NULL) return false;
    
    if (list->head->data == data) {
        Node* temp = list->head;
        list->head = list->head->next;
        free(temp);
        list->size--;
        return true;
    }
    
    Node* current = list->head;
    while (current->next != NULL && current->next->data != data) {
        current = current->next;
    }
    
    if (current->next != NULL) {
        Node* temp = current->next;
        current->next = current->next->next;
        free(temp);
        list->size--;
        return true;
    }
    
    return false;
}

Node* search(LinkedList* list, int data) {
    Node* current = list->head;
    while (current != NULL) {
        if (current->data == data) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void print_list(LinkedList* list) {
    Node* current = list->head;
    printf("Lista: ");
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void destroy_list(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

int main() {
    LinkedList* list = create_list();
    
    insert_at_beginning(list, 10);
    insert_at_beginning(list, 20);
    insert_at_end(list, 30);
    print_list(list);
    
    delete_node(list, 20);
    print_list(list);
    
    Node* found = search(list, 10);
    if (found) {
        printf("Elemento %d encontrado\n", found->data);
    }
    
    destroy_list(list);
    return 0;
}
```

Complexidade
- Inserção no início: O(1)
- Inserção no final: O(n)
- Busca: O(n)
- Remoção: O(n)