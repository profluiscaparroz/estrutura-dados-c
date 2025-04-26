#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*
 * Uma fila assíncrona é uma estrutura de dados que permite a comunicação entre diferentes threads
 * de forma segura e eficiente. Ela é projetada para ser acessada simultaneamente por múltiplas threads,
 * garantindo que as operações de enfileiramento (enqueue) e desenfileiramento (dequeue) sejam realizadas
 * de maneira sincronizada. Isso é alcançado utilizando mecanismos de exclusão mútua (como mutexes) e
 * variáveis de condição para gerenciar o acesso concorrente.
 *
 * Essa abordagem é útil em sistemas multithreaded, onde produtores (threads que adicionam elementos à fila)
 * e consumidores (threads que removem elementos da fila) precisam trabalhar de forma independente, sem
 * bloquear uns aos outros desnecessariamente.
 */

// Uma lista duplamente ligada é uma estrutura de dados onde cada nó contém um ponteiro para o próximo nó e outro para o nó anterior.
// Isso permite a navegação em ambas as direções (para frente e para trás). É útil para implementar estruturas como filas e deques,
// pois permite inserções e remoções eficientes em ambas as extremidades.

typedef struct Node {
    void *data;               // Ponteiro genérico para armazenar os dados do nó
    struct Node *next;        // Ponteiro para o próximo nó
    struct Node *prev;        // Ponteiro para o nó anterior
} Node;

typedef struct {
    Node *head;               // Ponteiro para o início da fila
    Node *tail;               // Ponteiro para o final da fila
    pthread_mutex_t lock;     // Mutex para garantir exclusão mútua
    pthread_cond_t cond;      // Variável de condição para sincronização
} AsyncQueue;

// Função para criar uma nova fila assincrona
AsyncQueue *createQueue() {
    AsyncQueue *queue = (AsyncQueue *)malloc(sizeof(AsyncQueue)); // Aloca memória para a fila
    queue->head = NULL;                                          // Inicializa o início como NULL
    queue->tail = NULL;                                          // Inicializa o final como NULL
    pthread_mutex_init(&queue->lock, NULL);                      // Inicializa o mutex
    pthread_cond_init(&queue->cond, NULL);                       // Inicializa a variável de condição
    return queue;
}

// Função para adicionar um elemento à fila
void enqueue(AsyncQueue *queue, void *data) {
    Node *newNode = (Node *)malloc(sizeof(Node));                // Aloca memória para um novo nó
    newNode->data = data;                                        // Armazena os dados no nó
    newNode->next = NULL;                                        // O próximo nó é NULL
    newNode->prev = NULL;                                        // O nó anterior é NULL

    pthread_mutex_lock(&queue->lock);                            // Bloqueia o mutex para acesso exclusivo

    if (queue->tail == NULL) {                                   // Se a fila estiver vazia
        queue->head = newNode;                                   // O novo nó é o início
        queue->tail = newNode;                                   // O novo nó é o final
    } else {
        queue->tail->next = newNode;                             // O próximo do nó final aponta para o novo nó
        newNode->prev = queue->tail;                             // O anterior do novo nó aponta para o nó final
        queue->tail = newNode;                                   // Atualiza o final da fila
    }

    pthread_cond_signal(&queue->cond);                           // Sinaliza que um novo elemento foi adicionado
    pthread_mutex_unlock(&queue->lock);                          // Desbloqueia o mutex
}

// Função para remover um elemento da fila
void *dequeue(AsyncQueue *queue) {
    pthread_mutex_lock(&queue->lock);                            // Bloqueia o mutex para acesso exclusivo

    while (queue->head == NULL) {                                // Se a fila estiver vazia
        pthread_cond_wait(&queue->cond, &queue->lock);           // Aguarda até que um elemento seja adicionado
    }

    Node *node = queue->head;                                    // Obtém o nó do início da fila
    void *data = node->data;                                     // Armazena os dados do nó
    queue->head = node->next;                                    // Atualiza o início da fila

    if (queue->head == NULL) {                                   // Se a fila ficou vazia
        queue->tail = NULL;                                      // Atualiza o final para NULL
    } else {
        queue->head->prev = NULL;                                // Remove a referência ao nó anterior
    }

    free(node);                                                  // Libera a memória do nó removido
    pthread_mutex_unlock(&queue->lock);                          // Desbloqueia o mutex
    return data;                                                 // Retorna os dados do nó removido
}

// Função para destruir a fila e liberar a memória
void destroyQueue(AsyncQueue *queue) {
    pthread_mutex_lock(&queue->lock);                            // Bloqueia o mutex para acesso exclusivo

    Node *current = queue->head;                                 // Começa pelo início da fila
    while (current != NULL) {                                    // Percorre todos os nós
        Node *next = current->next;                              // Armazena o próximo nó
        free(current);                                           // Libera o nó atual
        current = next;                                          // Move para o próximo nó
    }

    pthread_mutex_unlock(&queue->lock);                          // Desbloqueia o mutex
    pthread_mutex_destroy(&queue->lock);                         // Destroi o mutex
    pthread_cond_destroy(&queue->cond);                          // Destroi a variável de condição
    free(queue);                                                 // Libera a memória da fila
}

// Exemplo de uso da fila assincrona
void *producer(void *arg) {
    AsyncQueue *queue = (AsyncQueue *)arg;
    for (int i = 0; i < 10; i++) {
        int *data = (int *)malloc(sizeof(int));
        *data = i;
        printf("Produzindo: %d\n", *data);
        enqueue(queue, data);
    }
    return NULL;
}

void *consumer(void *arg) {
    AsyncQueue *queue = (AsyncQueue *)arg;
    for (int i = 0; i < 10; i++) {
        int *data = (int *)dequeue(queue);
        printf("Consumindo: %d\n", *data);
        free(data);
    }
    return NULL;
}

int main() {
    AsyncQueue *queue = createQueue();

    pthread_t producerThread, consumerThread;
    pthread_create(&producerThread, NULL, producer, queue);
    pthread_create(&consumerThread, NULL, consumer, queue);

    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    destroyQueue(queue);
    return 0;
}