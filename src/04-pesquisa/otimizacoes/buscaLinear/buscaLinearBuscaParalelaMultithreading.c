#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Estrutura para passar argumentos para as threads
typedef struct {
    int *array; // Ponteiro para o array
    int start;  // Índice inicial da busca
    int end;    // Índice final da busca
    int target; // Valor a ser buscado
    int result; // Resultado da busca (índice encontrado ou -1)
} ThreadArgs;

// Função executada por cada thread
void *linear_search_thread(void *args) {
    ThreadArgs *data = (ThreadArgs *)args;

    // Realiza a busca linear no intervalo especificado
    for (int i = data->start; i < data->end; i++) {
        if (data->array[i] == data->target) {
            data->result = i; // Armazena o índice encontrado
            pthread_exit(NULL); // Finaliza a thread
        }
    }

    data->result = -1; // Não encontrou o valor
    pthread_exit(NULL);
}

int main() {
    // Explicação sobre Busca Paralela com Multi-threading:
    // A busca paralela com multi-threading divide o trabalho de busca em várias threads,
    // permitindo que diferentes partes do array sejam processadas simultaneamente.
    // Isso pode acelerar a busca em arrays grandes, aproveitando o poder de múltiplos núcleos de CPU.

    int array[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int size = sizeof(array) / sizeof(array[0]);
    int target = 7; // Valor a ser buscado
    int num_threads = 4; // Número de threads a serem usadas

    pthread_t threads[num_threads];
    ThreadArgs thread_args[num_threads];
    int chunk_size = size / num_threads;
    int found_index = -1;

    // Cria as threads e divide o trabalho
    for (int i = 0; i < num_threads; i++) {
        thread_args[i].array = array;
        thread_args[i].start = i * chunk_size;
        thread_args[i].end = (i == num_threads - 1) ? size : (i + 1) * chunk_size;
        thread_args[i].target = target;
        thread_args[i].result = -1;

        pthread_create(&threads[i], NULL, linear_search_thread, &thread_args[i]);
    }

    // Aguarda as threads terminarem
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);

        // Verifica se alguma thread encontrou o valor
        if (thread_args[i].result != -1) {
            found_index = thread_args[i].result;
        }
    }

    // Exibe o resultado
    if (found_index != -1) {
        printf("Valor %d encontrado no índice %d.\n", target, found_index);
    } else {
        printf("Valor %d não encontrado no array.\n", target);
    }

    return 0;
}