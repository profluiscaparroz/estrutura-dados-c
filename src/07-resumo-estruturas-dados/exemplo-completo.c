/*
 * EXEMPLO COMPLETO: DEMONSTRAÇÃO DAS ESTRUTURAS DE DADOS FUNDAMENTAIS
 * 
 * Este programa demonstra na prática os conceitos das cinco estruturas fundamentais:
 * 1. Vetores e Matrizes - estruturas estáticas contíguas
 * 2. Métodos de Ordenação - Bubble Sort, Insertion Sort, Quick Sort, Merge Sort
 * 3. Métodos de Pesquisa - Busca Linear e Busca Binária
 * 4. Pilhas e Filas - TADs com acesso restrito (LIFO e FIFO)
 * 5. Listas Encadeadas - Simplesmente e Duplamente encadeadas
 * 
 * Também inclui uma demonstração de comparação de performance entre busca linear
 * e busca binária para ilustrar a importância da escolha do algoritmo correto.
 * 
 * Compile: gcc exemplo-completo.c -o exemplo-completo
 * Execute: ./exemplo-completo
 * 
 * Alternativamente, use o Makefile:
 *   make          - Compila o programa
 *   make run      - Compila e executa
 *   make clean    - Remove executável
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// ============================================================================
// 1. VETORES E MATRIZES
// ============================================================================

void demonstrar_vetores() {
    printf("\n=== 1. VETORES E MATRIZES ===\n");
    
    // Vetor estático
    int vetor[5] = {64, 34, 25, 12, 22};
    printf("\nVetor original: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", vetor[i]);
    }
    
    // Matriz 3x3
    int matriz[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    printf("\n\nMatriz 3x3:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    
    // Demonstrar acesso O(1)
    printf("\nAcesso direto (O(1)): vetor[2] = %d\n", vetor[2]);
    printf("Acesso direto (O(1)): matriz[1][2] = %d\n", matriz[1][2]);
}

// ============================================================================
// 2. MÉTODOS DE ORDENAÇÃO
// ============================================================================

// Bubble Sort - O(n²)
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool trocou = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                trocou = true;
            }
        }
        if (!trocou) break;  // Otimização
    }
}

// Quick Sort - O(n log n) médio
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Insertion Sort - O(n²) mas eficiente para arrays pequenos/quase ordenados
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int chave = arr[i];
        int j = i - 1;
        
        // Move elementos maiores que a chave uma posição à frente
        while (j >= 0 && arr[j] > chave) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = chave;
    }
}

// Merge Sort - O(n log n) garantido, estável
void merge(int arr[], int esq, int meio, int dir) {
    int n1 = meio - esq + 1;
    int n2 = dir - meio;
    
    // Criar arrays temporários
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));
    
    // Copiar dados para arrays temporários
    for (int i = 0; i < n1; i++)
        L[i] = arr[esq + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[meio + 1 + j];
    
    // Mesclar os arrays temporários de volta
    int i = 0, j = 0, k = esq;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    // Copiar elementos restantes
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    free(L);
    free(R);
}

void mergeSort(int arr[], int esq, int dir) {
    if (esq < dir) {
        int meio = esq + (dir - esq) / 2;
        
        mergeSort(arr, esq, meio);
        mergeSort(arr, meio + 1, dir);
        merge(arr, esq, meio, dir);
    }
}

void demonstrar_ordenacao() {
    printf("\n=== 2. MÉTODOS DE ORDENAÇÃO ===\n");
    
    // Testar Bubble Sort
    int arr1[] = {64, 34, 25, 12, 22};
    int n1 = 5;
    
    printf("\nBubble Sort (O(n²)):");
    printf("\nAntes: ");
    for (int i = 0; i < n1; i++) printf("%d ", arr1[i]);
    
    bubbleSort(arr1, n1);
    
    printf("\nDepois: ");
    for (int i = 0; i < n1; i++) printf("%d ", arr1[i]);
    
    // Testar Insertion Sort
    int arr2[] = {64, 34, 25, 12, 22};
    int n2 = 5;
    
    printf("\n\nInsertion Sort (O(n²) - eficiente para arrays pequenos):");
    printf("\nAntes: ");
    for (int i = 0; i < n2; i++) printf("%d ", arr2[i]);
    
    insertionSort(arr2, n2);
    
    printf("\nDepois: ");
    for (int i = 0; i < n2; i++) printf("%d ", arr2[i]);
    
    // Testar Quick Sort
    int arr3[] = {64, 34, 25, 12, 22, 90, 11};
    int n3 = 7;
    
    printf("\n\nQuick Sort (O(n log n) médio):");
    printf("\nAntes: ");
    for (int i = 0; i < n3; i++) printf("%d ", arr3[i]);
    
    quickSort(arr3, 0, n3 - 1);
    
    printf("\nDepois: ");
    for (int i = 0; i < n3; i++) printf("%d ", arr3[i]);
    
    // Testar Merge Sort
    int arr4[] = {38, 27, 43, 3, 9, 82, 10};
    int n4 = 7;
    
    printf("\n\nMerge Sort (O(n log n) garantido, estável):");
    printf("\nAntes: ");
    for (int i = 0; i < n4; i++) printf("%d ", arr4[i]);
    
    mergeSort(arr4, 0, n4 - 1);
    
    printf("\nDepois: ");
    for (int i = 0; i < n4; i++) printf("%d ", arr4[i]);
    printf("\n");
}

// ============================================================================
// 3. MÉTODOS DE PESQUISA
// ============================================================================

// Busca Linear - O(n)
int buscaLinear(int arr[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x)
            return i;
    }
    return -1;
}

// Busca Binária - O(log n)
int buscaBinaria(int arr[], int n, int x) {
    int esq = 0, dir = n - 1;
    
    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;
        
        if (arr[meio] == x)
            return meio;
        
        if (arr[meio] < x)
            esq = meio + 1;
        else
            dir = meio - 1;
    }
    
    return -1;
}

void demonstrar_pesquisa() {
    printf("\n=== 3. MÉTODOS DE PESQUISA ===\n");
    
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 45, 56, 67, 78};
    int n = 11;
    int buscar = 23;
    
    printf("\nArray: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\nBuscando elemento: %d\n", buscar);
    
    // Busca Linear
    int pos1 = buscaLinear(arr, n, buscar);
    printf("\nBusca Linear (O(n)): ");
    if (pos1 != -1)
        printf("Encontrado na posição %d\n", pos1);
    else
        printf("Não encontrado\n");
    
    // Busca Binária (array já está ordenado)
    int pos2 = buscaBinaria(arr, n, buscar);
    printf("Busca Binária (O(log n)): ");
    if (pos2 != -1)
        printf("Encontrado na posição %d\n", pos2);
    else
        printf("Não encontrado\n");
}

// ============================================================================
// 4. PILHAS E FILAS
// ============================================================================

// PILHA (Stack) - LIFO
typedef struct {
    int topo;
    int capacidade;
    int* array;
} Pilha;

Pilha* criarPilha(int capacidade) {
    Pilha* pilha = (Pilha*)malloc(sizeof(Pilha));
    pilha->capacidade = capacidade;
    pilha->topo = -1;
    pilha->array = (int*)malloc(capacidade * sizeof(int));
    return pilha;
}

bool pilhaVazia(Pilha* pilha) {
    return pilha->topo == -1;
}

bool pilhaCheia(Pilha* pilha) {
    return pilha->topo == pilha->capacidade - 1;
}

void push(Pilha* pilha, int item) {
    if (pilhaCheia(pilha)) {
        printf("Pilha cheia!\n");
        return;
    }
    pilha->array[++pilha->topo] = item;
}

int pop(Pilha* pilha) {
    if (pilhaVazia(pilha)) {
        printf("Pilha vazia!\n");
        return -1;
    }
    return pilha->array[pilha->topo--];
}

int peek(Pilha* pilha) {
    if (pilhaVazia(pilha)) {
        return -1;
    }
    return pilha->array[pilha->topo];
}

// FILA (Queue) - FIFO
typedef struct {
    int frente, tras, tamanho;
    int capacidade;
    int* array;
} Fila;

Fila* criarFila(int capacidade) {
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    fila->capacidade = capacidade;
    fila->frente = 0;
    fila->tamanho = 0;
    fila->tras = capacidade - 1;
    fila->array = (int*)malloc(capacidade * sizeof(int));
    return fila;
}

bool filaVazia(Fila* fila) {
    return fila->tamanho == 0;
}

bool filaCheia(Fila* fila) {
    return fila->tamanho == fila->capacidade;
}

void enqueue(Fila* fila, int item) {
    if (filaCheia(fila)) {
        printf("Fila cheia!\n");
        return;
    }
    fila->tras = (fila->tras + 1) % fila->capacidade;
    fila->array[fila->tras] = item;
    fila->tamanho++;
}

int dequeue(Fila* fila) {
    if (filaVazia(fila)) {
        printf("Fila vazia!\n");
        return -1;
    }
    int item = fila->array[fila->frente];
    fila->frente = (fila->frente + 1) % fila->capacidade;
    fila->tamanho--;
    return item;
}

void demonstrar_pilha_fila() {
    printf("\n=== 4. PILHAS E FILAS ===\n");
    
    // Demonstrar Pilha (LIFO)
    printf("\nPILHA (LIFO - Last In, First Out):\n");
    Pilha* pilha = criarPilha(5);
    
    printf("Empilhando: 10, 20, 30\n");
    push(pilha, 10);
    push(pilha, 20);
    push(pilha, 30);
    
    printf("Topo da pilha: %d\n", peek(pilha));
    printf("Desempilhando: %d\n", pop(pilha));  // 30 (último que entrou)
    printf("Desempilhando: %d\n", pop(pilha));  // 20
    printf("Topo agora: %d\n", peek(pilha));    // 10
    
    // Demonstrar Fila (FIFO)
    printf("\nFILA (FIFO - First In, First Out):\n");
    Fila* fila = criarFila(5);
    
    printf("Enfileirando: 10, 20, 30\n");
    enqueue(fila, 10);
    enqueue(fila, 20);
    enqueue(fila, 30);
    
    printf("Desenfileirando: %d\n", dequeue(fila));  // 10 (primeiro que entrou)
    printf("Desenfileirando: %d\n", dequeue(fila));  // 20
    printf("Próximo na fila: %d\n", fila->array[fila->frente]);  // 30
    
    // Liberar memória
    free(pilha->array);
    free(pilha);
    free(fila->array);
    free(fila);
}

// ============================================================================
// 5. LISTAS ENCADEADAS
// ============================================================================

// Nó da lista encadeada
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Criar novo nó
Node* criarNo(int data) {
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->data = data;
    novo->next = NULL;
    return novo;
}

// Inserir no início - O(1)
void inserirInicio(Node** head, int data) {
    Node* novo = criarNo(data);
    novo->next = *head;
    *head = novo;
}

// Inserir no final - O(n)
void inserirFinal(Node** head, int data) {
    Node* novo = criarNo(data);
    
    if (*head == NULL) {
        *head = novo;
        return;
    }
    
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = novo;
}

// Buscar - O(n)
Node* buscar(Node* head, int data) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->data == data)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

// Remover - O(n)
void remover(Node** head, int data) {
    Node* temp = *head;
    Node* prev = NULL;
    
    // Se é o primeiro nó
    if (temp != NULL && temp->data == data) {
        *head = temp->next;
        free(temp);
        return;
    }
    
    // Buscar o nó
    while (temp != NULL && temp->data != data) {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp == NULL) return;  // Não encontrado
    
    prev->next = temp->next;
    free(temp);
}

// Imprimir lista
void imprimirLista(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Liberar memória
void liberarLista(Node** head) {
    Node* atual = *head;
    Node* proximo;
    
    while (atual != NULL) {
        proximo = atual->next;
        free(atual);
        atual = proximo;
    }
    
    *head = NULL;
}

// ============================================================================
// 5.1 LISTA DUPLAMENTE ENCADEADA
// ============================================================================

// Nó da lista duplamente encadeada
typedef struct DNode {
    int data;
    struct DNode* prev;  // Ponteiro para o nó anterior
    struct DNode* next;  // Ponteiro para o próximo nó
} DNode;

// Criar novo nó
DNode* criarDNo(int data) {
    DNode* novo = (DNode*)malloc(sizeof(DNode));
    novo->data = data;
    novo->prev = NULL;
    novo->next = NULL;
    return novo;
}

// Inserir no início - O(1)
void inserirDInicio(DNode** head, int data) {
    DNode* novo = criarDNo(data);
    novo->next = *head;
    
    if (*head != NULL) {
        (*head)->prev = novo;
    }
    
    *head = novo;
}

// Inserir no final - O(n) sem tail pointer
void inserirDFinal(DNode** head, int data) {
    DNode* novo = criarDNo(data);
    
    if (*head == NULL) {
        *head = novo;
        return;
    }
    
    DNode* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    
    temp->next = novo;
    novo->prev = temp;
}

// Remover nó específico - O(1) se tiver ponteiro direto
void removerDNo(DNode** head, DNode* del) {
    if (*head == NULL || del == NULL) return;
    
    // Se é o primeiro nó
    if (*head == del) {
        *head = del->next;
    }
    
    // Atualiza o próximo nó se existir
    if (del->next != NULL) {
        del->next->prev = del->prev;
    }
    
    // Atualiza o nó anterior se existir
    if (del->prev != NULL) {
        del->prev->next = del->next;
    }
    
    free(del);
}

// Imprimir lista para frente
void imprimirDListaFrente(DNode* head) {
    DNode* temp = head;
    printf("NULL <-> ");
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Imprimir lista para trás
void imprimirDListaTras(DNode* head) {
    if (head == NULL) {
        printf("Lista vazia\n");
        return;
    }
    
    // Ir até o último nó
    DNode* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    
    // Imprimir de trás para frente
    printf("NULL <-> ");
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->prev;
    }
    printf("NULL\n");
}

// Liberar lista duplamente encadeada
void liberarDLista(DNode** head) {
    DNode* atual = *head;
    DNode* proximo;
    
    while (atual != NULL) {
        proximo = atual->next;
        free(atual);
        atual = proximo;
    }
    
    *head = NULL;
}

void demonstrar_lista_encadeada() {
    printf("\n=== 5. LISTAS ENCADEADAS ===\n");
    
    // Lista Simplesmente Encadeada
    printf("\n--- Lista Simplesmente Encadeada ---\n");
    Node* head = NULL;
    
    printf("\nInserindo no início: 30, 20, 10\n");
    inserirInicio(&head, 30);
    inserirInicio(&head, 20);
    inserirInicio(&head, 10);
    printf("Lista: ");
    imprimirLista(head);
    
    printf("\nInserindo no final: 40, 50\n");
    inserirFinal(&head, 40);
    inserirFinal(&head, 50);
    printf("Lista: ");
    imprimirLista(head);
    
    printf("\nBuscando elemento 30...\n");
    Node* encontrado = buscar(head, 30);
    if (encontrado != NULL)
        printf("Elemento 30 encontrado!\n");
    else
        printf("Elemento 30 não encontrado.\n");
    
    printf("\nRemovendo elemento 20...\n");
    remover(&head, 20);
    printf("Lista: ");
    imprimirLista(head);
    
    // Liberar memória da lista simples
    liberarLista(&head);
    
    // Lista Duplamente Encadeada
    printf("\n--- Lista Duplamente Encadeada ---\n");
    DNode* dhead = NULL;
    
    printf("\nInserindo no início: 30, 20, 10\n");
    inserirDInicio(&dhead, 30);
    inserirDInicio(&dhead, 20);
    inserirDInicio(&dhead, 10);
    printf("Lista (frente): ");
    imprimirDListaFrente(dhead);
    
    printf("\nInserindo no final: 40, 50\n");
    inserirDFinal(&dhead, 40);
    inserirDFinal(&dhead, 50);
    printf("Lista (frente): ");
    imprimirDListaFrente(dhead);
    printf("Lista (trás):   ");
    imprimirDListaTras(dhead);
    
    // Liberar memória da lista dupla
    liberarDLista(&dhead);
}

// ============================================================================
// COMPARAÇÃO DE PERFORMANCE
// ============================================================================

void demonstrar_comparacao_performance() {
    printf("\n=== COMPARAÇÃO DE PERFORMANCE ===\n");
    
    int n = 100000;
    int iterations = 1000;  // Múltiplas iterações para medição precisa
    
    // Criar array ordenado
    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = i * 2;  // 0, 2, 4, 6, ...
    }
    
    int buscar_elemento = n - 2;  // Quase no final
    
    // Busca Linear - Múltiplas iterações
    clock_t inicio_linear = clock();
    for (int i = 0; i < iterations; i++) {
        buscaLinear(arr, n, buscar_elemento);
    }
    clock_t fim_linear = clock();
    double tempo_linear = ((double)(fim_linear - inicio_linear)) / CLOCKS_PER_SEC * 1000000 / iterations;
    
    // Busca Binária - Múltiplas iterações
    clock_t inicio_binaria = clock();
    for (int i = 0; i < iterations; i++) {
        buscaBinaria(arr, n, buscar_elemento);
    }
    clock_t fim_binaria = clock();
    double tempo_binaria = ((double)(fim_binaria - inicio_binaria)) / CLOCKS_PER_SEC * 1000000 / iterations;
    
    printf("\nBusca em array de %d elementos (média de %d execuções):\n", n, iterations);
    printf("Elemento buscado (próximo ao final): %d\n", buscar_elemento);
    printf("\nBusca Linear:  %.3f µs\n", tempo_linear);
    printf("Busca Binária: %.3f µs\n", tempo_binaria);
    if (tempo_binaria > 1e-9) {  // Evita divisão por zero com epsilon
        printf("Speedup: %.1fx mais rápida!\n", tempo_linear / tempo_binaria);
    }
    
    free(arr);
}

// ============================================================================
// MAIN - EXECUTAR TODAS AS DEMONSTRAÇÕES
// ============================================================================

void imprimir_cabecalho() {
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║   DEMONSTRAÇÃO DAS ESTRUTURAS DE DADOS FUNDAMENTAIS         ║\n");
    printf("║                                                              ║\n");
    printf("║   Este programa demonstra na prática:                       ║\n");
    printf("║   1. Vetores e Matrizes                                     ║\n");
    printf("║   2. Métodos de Ordenação (Bubble, Insertion, Quick, Merge) ║\n");
    printf("║   3. Métodos de Pesquisa (Linear, Binária)                  ║\n");
    printf("║   4. Pilhas (LIFO) e Filas (FIFO)                           ║\n");
    printf("║   5. Listas Encadeadas (Simples e Dupla)                    ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n");
}

int main() {
    imprimir_cabecalho();
    
    // Executar todas as demonstrações
    demonstrar_vetores();
    demonstrar_ordenacao();
    demonstrar_pesquisa();
    demonstrar_pilha_fila();
    demonstrar_lista_encadeada();
    demonstrar_comparacao_performance();
    
    printf("\n╔══════════════════════════════════════════════════════════════╗\n");
    printf("║   CONCLUSÃO                                                  ║\n");
    printf("║                                                              ║\n");
    printf("║   Você viu na prática como funcionam as principais          ║\n");
    printf("║   estruturas de dados fundamentais!                         ║\n");
    printf("║                                                              ║\n");
    printf("║   Pontos-chave:                                             ║\n");
    printf("║   • Arrays: Acesso O(1), mas inserção O(n)                  ║\n");
    printf("║   • Quick/Merge Sort: O(n log n) - Muito eficientes!        ║\n");
    printf("║   • Busca Binária: O(log n) - Exponencialmente rápida!     ║\n");
    printf("║   • Pilha: LIFO - Último entra, primeiro sai                ║\n");
    printf("║   • Fila: FIFO - Primeiro entra, primeiro sai               ║\n");
    printf("║   • Lista Simples: Navegação em uma direção                 ║\n");
    printf("║   • Lista Dupla: Navegação bidirecional                     ║\n");
    printf("║                                                              ║\n");
    printf("║   Continue estudando e praticando! 🚀                       ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n\n");
    
    return 0;
}
