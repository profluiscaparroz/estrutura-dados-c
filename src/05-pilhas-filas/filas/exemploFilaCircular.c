#include <stdio.h>
#include <stdlib.h>

#define MAX 5 // Define o tamanho máximo da fila

// Estrutura da fila circular
typedef struct {
    int itens[MAX];
    int frente; // Índice do início da fila
    int tras;   // Índice do final da fila
} FilaCircular;

// Inicializa a fila circular
void inicializarFila(FilaCircular *fila) {
    fila->frente = -1;
    fila->tras = -1;
}

// Verifica se a fila está cheia
int estaCheia(FilaCircular *fila) {
    return (fila->frente == (fila->tras + 1) % MAX);
}

// Verifica se a fila está vazia
int estaVazia(FilaCircular *fila) {
    return (fila->frente == -1);
}

// Insere um elemento na fila circular
void enfileirar(FilaCircular *fila, int valor) {
    if (estaCheia(fila)) {
        printf("Erro: Fila cheia!\n");
        return;
    }
    if (estaVazia(fila)) {
        fila->frente = 0;
    }
    fila->tras = (fila->tras + 1) % MAX;
    fila->itens[fila->tras] = valor;
    printf("Enfileirado: %d\n", valor);
}

// Remove um elemento da fila circular
int desenfileirar(FilaCircular *fila) {
    if (estaVazia(fila)) {
        printf("Erro: Fila vazia!\n");
        return -1;
    }
    int valor = fila->itens[fila->frente];
    if (fila->frente == fila->tras) {
        // A fila ficou vazia
        fila->frente = -1;
        fila->tras = -1;
    } else {
        fila->frente = (fila->frente + 1) % MAX;
    }
    printf("Desenfileirado: %d\n", valor);
    return valor;
}

// Exibe os elementos da fila circular
void exibirFila(FilaCircular *fila) {
    if (estaVazia(fila)) {
        printf("Fila vazia!\n");
        return;
    }
    printf("Fila: ");
    int i = fila->frente;
    while (1) {
        printf("%d ", fila->itens[i]);
        if (i == fila->tras) {
            break;
        }
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main() {
    /*
    * Uma fila circular é uma estrutura de dados que utiliza um array fixo e 
    * reaproveita os espaços vazios no início do array quando elementos são removidos.
    * útil para economizar memória e evitar a necessidade de realocar elementos.
    */

    FilaCircular fila;
    inicializarFila(&fila);

    // Testando a fila circular
    enfileirar(&fila, 10);
    enfileirar(&fila, 20);
    enfileirar(&fila, 30);
    enfileirar(&fila, 40);
    enfileirar(&fila, 50); // Fila cheia aqui
    exibirFila(&fila);

    desenfileirar(&fila);
    desenfileirar(&fila);
    exibirFila(&fila);

    enfileirar(&fila, 60);
    enfileirar(&fila, 70); // Reaproveitando espaços
    exibirFila(&fila);

    return 0;
}