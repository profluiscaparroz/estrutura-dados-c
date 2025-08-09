#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó para lista duplamente encadeada
typedef struct DNode {
    int data;
    struct DNode* next;
    struct DNode* prev;
} DNode;

// Estrutura da lista duplamente encadeada
typedef struct DoublyLinkedList {
    DNode* head;
    DNode* tail;
    int size;
} DoublyLinkedList;

// Criar lista duplamente encadeada
DoublyLinkedList* criarListaDupla() {
    DoublyLinkedList* lista = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
    if (lista) {
        lista->head = NULL;
        lista->tail = NULL;
        lista->size = 0;
    }
    return lista;
}

// Inserir no início
void inserirInicioDupla(DoublyLinkedList* lista, int valor) {
    DNode* novoNo = (DNode*)malloc(sizeof(DNode));
    if (!novoNo) {
        printf("Erro na alocação de memória\n");
        return;
    }
    
    novoNo->data = valor;
    novoNo->prev = NULL;
    novoNo->next = lista->head;
    
    if (lista->head != NULL) {
        lista->head->prev = novoNo;
    } else {
        lista->tail = novoNo; // Lista estava vazia
    }
    
    lista->head = novoNo;
    lista->size++;
}

// Inserir no final
void inserirFimDupla(DoublyLinkedList* lista, int valor) {
    DNode* novoNo = (DNode*)malloc(sizeof(DNode));
    if (!novoNo) {
        printf("Erro na alocação de memória\n");
        return;
    }
    
    novoNo->data = valor;
    novoNo->next = NULL;
    novoNo->prev = lista->tail;
    
    if (lista->tail != NULL) {
        lista->tail->next = novoNo;
    } else {
        lista->head = novoNo; // Lista estava vazia
    }
    
    lista->tail = novoNo;
    lista->size++;
}

// Inserir em posição específica
void inserirPosicaoDupla(DoublyLinkedList* lista, int valor, int posicao) {
    if (posicao < 0 || posicao > lista->size) {
        printf("Posição inválida\n");
        return;
    }
    
    if (posicao == 0) {
        inserirInicioDupla(lista, valor);
        return;
    }
    
    if (posicao == lista->size) {
        inserirFimDupla(lista, valor);
        return;
    }
    
    DNode* novoNo = (DNode*)malloc(sizeof(DNode));
    if (!novoNo) {
        printf("Erro na alocação de memória\n");
        return;
    }
    
    novoNo->data = valor;
    
    // Decidir se percorrer do início ou do fim (otimização)
    DNode* temp;
    if (posicao < lista->size / 2) {
        // Percorrer do início
        temp = lista->head;
        for (int i = 0; i < posicao; i++) {
            temp = temp->next;
        }
    } else {
        // Percorrer do fim
        temp = lista->tail;
        for (int i = lista->size - 1; i > posicao; i--) {
            temp = temp->prev;
        }
    }
    
    // Inserir o novo nó antes de temp
    novoNo->next = temp;
    novoNo->prev = temp->prev;
    temp->prev->next = novoNo;
    temp->prev = novoNo;
    lista->size++;
}

// Buscar elemento
int buscarDupla(DoublyLinkedList* lista, int valor) {
    DNode* temp = lista->head;
    int posicao = 0;
    
    while (temp != NULL) {
        if (temp->data == valor) {
            return posicao;
        }
        temp = temp->next;
        posicao++;
    }
    
    return -1;
}

// Buscar da direita para esquerda
int buscarDuplaReverso(DoublyLinkedList* lista, int valor) {
    DNode* temp = lista->tail;
    int posicao = lista->size - 1;
    
    while (temp != NULL) {
        if (temp->data == valor) {
            return posicao;
        }
        temp = temp->prev;
        posicao--;
    }
    
    return -1;
}

// Imprimir da esquerda para direita
void imprimirEsquerdaDireita(DoublyLinkedList* lista) {
    printf("Esquerda -> Direita (%d elementos): ", lista->size);
    DNode* temp = lista->head;
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Imprimir da direita para esquerda
void imprimirDireitaEsquerda(DoublyLinkedList* lista) {
    printf("Direita -> Esquerda (%d elementos): ", lista->size);
    DNode* temp = lista->tail;
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->prev;
    }
    printf("NULL\n");
}

// Remover do início
int removerInicioDupla(DoublyLinkedList* lista) {
    if (lista->head == NULL) {
        printf("Lista vazia\n");
        return -1;
    }
    
    DNode* temp = lista->head;
    int valor = temp->data;
    
    lista->head = temp->next;
    if (lista->head != NULL) {
        lista->head->prev = NULL;
    } else {
        lista->tail = NULL; // Lista ficou vazia
    }
    
    free(temp);
    lista->size--;
    return valor;
}

// Remover do final
int removerFimDupla(DoublyLinkedList* lista) {
    if (lista->tail == NULL) {
        printf("Lista vazia\n");
        return -1;
    }
    
    DNode* temp = lista->tail;
    int valor = temp->data;
    
    lista->tail = temp->prev;
    if (lista->tail != NULL) {
        lista->tail->next = NULL;
    } else {
        lista->head = NULL; // Lista ficou vazia
    }
    
    free(temp);
    lista->size--;
    return valor;
}

// Remover por valor
int removerValorDupla(DoublyLinkedList* lista, int valor) {
    DNode* temp = lista->head;
    
    while (temp != NULL) {
        if (temp->data == valor) {
            // Ajustar ponteiros dos nós adjacentes
            if (temp->prev != NULL) {
                temp->prev->next = temp->next;
            } else {
                lista->head = temp->next; // temp era o primeiro
            }
            
            if (temp->next != NULL) {
                temp->next->prev = temp->prev;
            } else {
                lista->tail = temp->prev; // temp era o último
            }
            
            free(temp);
            lista->size--;
            return 1;
        }
        temp = temp->next;
    }
    
    return 0; // Não encontrado
}

// Remover nó específico (quando você tem a referência direta)
void removerNoDupla(DoublyLinkedList* lista, DNode* no) {
    if (no == NULL) return;
    
    if (no->prev != NULL) {
        no->prev->next = no->next;
    } else {
        lista->head = no->next;
    }
    
    if (no->next != NULL) {
        no->next->prev = no->prev;
    } else {
        lista->tail = no->prev;
    }
    
    free(no);
    lista->size--;
}

// Reverter a lista duplamente encadeada
void reverterListaDupla(DoublyLinkedList* lista) {
    DNode* temp = NULL;
    DNode* atual = lista->head;
    
    // Trocar head e tail
    lista->tail = lista->head;
    
    // Trocar next e prev para todos os nós
    while (atual != NULL) {
        temp = atual->prev;
        atual->prev = atual->next;
        atual->next = temp;
        atual = atual->prev;
    }
    
    // Atualizar head (que agora aponta para o que era tail)
    if (temp != NULL) {
        lista->head = temp->prev;
    }
}

// Liberar lista duplamente encadeada
void liberarListaDupla(DoublyLinkedList* lista) {
    DNode* temp = lista->head;
    while (temp != NULL) {
        DNode* proximo = temp->next;
        free(temp);
        temp = proximo;
    }
    free(lista);
}

// Função para ordenar a lista (insertion sort adaptado)
void ordenarListaDupla(DoublyLinkedList* lista) {
    if (lista->head == NULL || lista->head->next == NULL) {
        return; // Lista vazia ou com um elemento
    }
    
    DNode* atual = lista->head->next;
    
    while (atual != NULL) {
        DNode* proximo = atual->next;
        int valorAtual = atual->data;
        
        // Encontrar a posição correta para inserir
        DNode* pos = atual->prev;
        while (pos != NULL && pos->data > valorAtual) {
            pos = pos->prev;
        }
        
        // Se atual já está na posição correta
        if (pos == atual->prev) {
            atual = proximo;
            continue;
        }
        
        // Remover atual de sua posição
        if (atual->next != NULL) {
            atual->next->prev = atual->prev;
        } else {
            lista->tail = atual->prev;
        }
        atual->prev->next = atual->next;
        
        // Inserir atual na nova posição
        if (pos == NULL) {
            // Inserir no início
            atual->prev = NULL;
            atual->next = lista->head;
            lista->head->prev = atual;
            lista->head = atual;
        } else {
            // Inserir após pos
            atual->prev = pos;
            atual->next = pos->next;
            if (pos->next != NULL) {
                pos->next->prev = atual;
            }
            pos->next = atual;
        }
        
        atual = proximo;
    }
}

int main() {
    DoublyLinkedList* lista = criarListaDupla();
    
    printf("=== Demonstração de Lista Duplamente Encadeada ===\n\n");
    
    // Inserções
    printf("1. Inserindo elementos...\n");
    inserirInicioDupla(lista, 10);
    inserirInicioDupla(lista, 5);
    inserirFimDupla(lista, 20);
    inserirFimDupla(lista, 25);
    inserirPosicaoDupla(lista, 15, 2);
    
    printf("Lista após inserções:\n");
    imprimirEsquerdaDireita(lista);
    imprimirDireitaEsquerda(lista);
    
    // Busca
    printf("\n2. Buscando elementos:\n");
    int pos = buscarDupla(lista, 15);
    printf("Busca normal - Elemento 15 encontrado na posição: %d\n", pos);
    
    pos = buscarDuplaReverso(lista, 15);
    printf("Busca reversa - Elemento 15 encontrado na posição: %d\n", pos);
    
    // Remoções
    printf("\n3. Removendo elementos:\n");
    printf("Removido do início: %d\n", removerInicioDupla(lista));
    printf("Removido do fim: %d\n", removerFimDupla(lista));
    
    printf("Lista após remoções:\n");
    imprimirEsquerdaDireita(lista);
    
    // Remover por valor
    printf("\n4. Removendo por valor:\n");
    printf("Removendo valor 15: %s\n", removerValorDupla(lista, 15) ? "Sucesso" : "Falhou");
    imprimirEsquerdaDireita(lista);
    
    // Adicionar mais elementos para testar ordenação
    printf("\n5. Adicionando elementos desordenados:\n");
    inserirFimDupla(lista, 5);
    inserirFimDupla(lista, 30);
    inserirFimDupla(lista, 1);
    inserirFimDupla(lista, 15);
    
    printf("Lista antes da ordenação:\n");
    imprimirEsquerdaDireita(lista);
    
    ordenarListaDupla(lista);
    printf("Lista após ordenação:\n");
    imprimirEsquerdaDireita(lista);
    
    // Reverter lista
    printf("\n6. Revertendo a lista:\n");
    reverterListaDupla(lista);
    imprimirEsquerdaDireita(lista);
    imprimirDireitaEsquerda(lista);
    
    liberarListaDupla(lista);
    return 0;
}