#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Estrutura da lista para manter informações adicionais
typedef struct LinkedList {
    Node* head;
    int size;
} LinkedList;

// Inicializar a lista
LinkedList* criarLista() {
    LinkedList* lista = (LinkedList*)malloc(sizeof(LinkedList));
    if (lista) {
        lista->head = NULL;
        lista->size = 0;
    }
    return lista;
}

// Inserir no início da lista
void inserirInicio(LinkedList* lista, int valor) {
    Node* novoNo = (Node*)malloc(sizeof(Node));
    if (!novoNo) {
        printf("Erro na alocação de memória\n");
        return;
    }
    
    novoNo->data = valor;
    novoNo->next = lista->head;
    lista->head = novoNo;
    lista->size++;
}

// Inserir no final da lista
void inserirFim(LinkedList* lista, int valor) {
    Node* novoNo = (Node*)malloc(sizeof(Node));
    if (!novoNo) {
        printf("Erro na alocação de memória\n");
        return;
    }
    
    novoNo->data = valor;
    novoNo->next = NULL;
    
    if (lista->head == NULL) {
        lista->head = novoNo;
    } else {
        Node* temp = lista->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = novoNo;
    }
    lista->size++;
}

// Inserir em posição específica
void inserirPosicao(LinkedList* lista, int valor, int posicao) {
    if (posicao < 0 || posicao > lista->size) {
        printf("Posição inválida\n");
        return;
    }
    
    if (posicao == 0) {
        inserirInicio(lista, valor);
        return;
    }
    
    Node* novoNo = (Node*)malloc(sizeof(Node));
    if (!novoNo) {
        printf("Erro na alocação de memória\n");
        return;
    }
    
    novoNo->data = valor;
    
    Node* temp = lista->head;
    for (int i = 0; i < posicao - 1; i++) {
        temp = temp->next;
    }
    
    novoNo->next = temp->next;
    temp->next = novoNo;
    lista->size++;
}

// Buscar elemento na lista
int buscar(LinkedList* lista, int valor) {
    Node* temp = lista->head;
    int posicao = 0;
    
    while (temp != NULL) {
        if (temp->data == valor) {
            return posicao;
        }
        temp = temp->next;
        posicao++;
    }
    
    return -1; // Não encontrado
}

// Remover do início
int removerInicio(LinkedList* lista) {
    if (lista->head == NULL) {
        printf("Lista vazia\n");
        return -1;
    }
    
    Node* temp = lista->head;
    int valor = temp->data;
    lista->head = temp->next;
    free(temp);
    lista->size--;
    
    return valor;
}

// Remover do final
int removerFim(LinkedList* lista) {
    if (lista->head == NULL) {
        printf("Lista vazia\n");
        return -1;
    }
    
    if (lista->head->next == NULL) {
        int valor = lista->head->data;
        free(lista->head);
        lista->head = NULL;
        lista->size--;
        return valor;
    }
    
    Node* temp = lista->head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    
    int valor = temp->next->data;
    free(temp->next);
    temp->next = NULL;
    lista->size--;
    
    return valor;
}

// Remover por valor
int removerValor(LinkedList* lista, int valor) {
    if (lista->head == NULL) {
        return 0; // Lista vazia
    }
    
    // Se for o primeiro elemento
    if (lista->head->data == valor) {
        Node* temp = lista->head;
        lista->head = temp->next;
        free(temp);
        lista->size--;
        return 1;
    }
    
    Node* temp = lista->head;
    while (temp->next != NULL && temp->next->data != valor) {
        temp = temp->next;
    }
    
    if (temp->next == NULL) {
        return 0; // Não encontrado
    }
    
    Node* noParaRemover = temp->next;
    temp->next = noParaRemover->next;
    free(noParaRemover);
    lista->size--;
    return 1;
}

// Imprimir a lista
void imprimirLista(LinkedList* lista) {
    printf("Lista (%d elementos): ", lista->size);
    Node* temp = lista->head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Liberar toda a lista
void liberarLista(LinkedList* lista) {
    Node* temp = lista->head;
    while (temp != NULL) {
        Node* proximo = temp->next;
        free(temp);
        temp = proximo;
    }
    free(lista);
}

// Função para reverter a lista
void reverterLista(LinkedList* lista) {
    Node* anterior = NULL;
    Node* atual = lista->head;
    Node* proximo = NULL;
    
    while (atual != NULL) {
        proximo = atual->next;  // Salva o próximo nó
        atual->next = anterior; // Reverte o link
        anterior = atual;       // Move anterior para frente
        atual = proximo;        // Move atual para frente
    }
    
    lista->head = anterior; // Atualiza o head
}

// Função para encontrar o meio da lista
Node* encontrarMeio(LinkedList* lista) {
    if (lista->head == NULL) {
        return NULL;
    }
    
    Node* lento = lista->head;
    Node* rapido = lista->head;
    
    // Técnica do ponteiro duplo
    while (rapido != NULL && rapido->next != NULL) {
        lento = lento->next;
        rapido = rapido->next->next;
    }
    
    return lento;
}

// Função para detectar ciclo na lista (Algoritmo de Floyd)
int temCiclo(LinkedList* lista) {
    if (lista->head == NULL) {
        return 0;
    }
    
    Node* lento = lista->head;
    Node* rapido = lista->head;
    
    while (rapido != NULL && rapido->next != NULL) {
        lento = lento->next;
        rapido = rapido->next->next;
        
        if (lento == rapido) {
            return 1; // Ciclo detectado
        }
    }
    
    return 0; // Sem ciclo
}

// Função para remover duplicatas de uma lista ordenada
void removerDuplicatasOrdenada(LinkedList* lista) {
    Node* atual = lista->head;
    
    while (atual != NULL && atual->next != NULL) {
        if (atual->data == atual->next->data) {
            Node* temp = atual->next;
            atual->next = temp->next;
            free(temp);
            lista->size--;
        } else {
            atual = atual->next;
        }
    }
}

int main() {
    LinkedList* lista = criarLista();
    
    printf("=== Demonstração de Lista Encadeada Simples ===\n\n");
    
    // Inserções
    printf("1. Inserindo elementos...\n");
    inserirInicio(lista, 10);
    inserirInicio(lista, 5);
    inserirFim(lista, 20);
    inserirFim(lista, 25);
    inserirPosicao(lista, 15, 2);
    
    imprimirLista(lista);
    
    // Busca
    printf("\n2. Buscando elementos:\n");
    int pos = buscar(lista, 15);
    printf("Elemento 15 encontrado na posição: %d\n", pos);
    
    pos = buscar(lista, 100);
    printf("Elemento 100 encontrado na posição: %d\n", pos);
    
    // Encontrar meio
    printf("\n3. Encontrando o meio da lista:\n");
    Node* meio = encontrarMeio(lista);
    if (meio) {
        printf("Elemento do meio: %d\n", meio->data);
    }
    
    // Verificar ciclo
    printf("\n4. Verificando se há ciclo:\n");
    printf("Tem ciclo: %s\n", temCiclo(lista) ? "Sim" : "Não");
    
    // Reverter lista
    printf("\n5. Revertendo a lista:\n");
    reverterLista(lista);
    imprimirLista(lista);
    
    // Voltar ao normal
    reverterLista(lista);
    printf("Lista voltou ao normal:\n");
    imprimirLista(lista);
    
    // Remoções
    printf("\n6. Removendo elementos:\n");
    printf("Removido do início: %d\n", removerInicio(lista));
    imprimirLista(lista);
    
    printf("Removido do fim: %d\n", removerFim(lista));
    imprimirLista(lista);
    
    printf("Removendo valor 15: %s\n", removerValor(lista, 15) ? "Sucesso" : "Falhou");
    imprimirLista(lista);
    
    // Teste de remoção de duplicatas
    printf("\n7. Testando remoção de duplicatas:\n");
    // Adicionar alguns duplicatas
    inserirFim(lista, 10);
    inserirFim(lista, 10);
    inserirFim(lista, 20);
    printf("Lista com duplicatas:\n");
    imprimirLista(lista);
    
    removerDuplicatasOrdenada(lista);
    printf("Lista após remover duplicatas:\n");
    imprimirLista(lista);
    
    liberarLista(lista);
    return 0;
}