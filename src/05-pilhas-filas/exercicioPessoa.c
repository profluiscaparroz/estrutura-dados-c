#include <stdio.h>
#include <stdlib.h>

#define TAM_NOME 100
#define TAM_CPF 15
#define TAM_DATA 11
#define TAM_MOTIVO 10

typedef struct Pessoa {
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    char data_nascimento[TAM_DATA];
    char motivo_visita[TAM_MOTIVO]; // "Reclamar" ou "Elogiar"
    struct Pessoa* prox;
} Pessoa;

typedef struct {
    Pessoa* inicio;
    Pessoa* fim;
} Fila;

// Função para copiar texto (substitui strcpy)
void copiaTexto(char* destino, const char* origem) {
    int i = 0;
    while (origem[i] != '\0') {
        destino[i] = origem[i];
        i++;
    }
    destino[i] = '\0';
}

// Função para comparar dois textos (substitui strcmp)
int comparaTexto(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return 0;
        i++;
    }
    return (a[i] == '\0' && b[i] == '\0');
}

// Inicializa a fila
void inicializaFila(Fila* fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

// Enfileira uma nova pessoa
void enfileirar(Fila* fila, char* nome, char* cpf, char* data_nasc, char* motivo) {
    Pessoa* nova = (Pessoa*) malloc(sizeof(Pessoa));
    copiaTexto(nova->nome, nome);
    copiaTexto(nova->cpf, cpf);
    copiaTexto(nova->data_nascimento, data_nasc);
    copiaTexto(nova->motivo_visita, motivo);
    nova->prox = NULL;

    if (fila->fim == NULL) {
        fila->inicio = fila->fim = nova;
    } else {
        fila->fim->prox = nova;
        fila->fim = nova;
    }
}

// Desenfileira uma pessoa e retorna ponteiro
Pessoa* desenfileirar(Fila* fila) {
    if (fila->inicio == NULL) return NULL;

    Pessoa* removida = fila->inicio;
    fila->inicio = fila->inicio->prox;
    if (fila->inicio == NULL) fila->fim = NULL;

    return removida;
}

// Função principal
int main() {
    Fila fila;
    inicializaFila(&fila);

    // Inserindo 5 pessoas
    enfileirar(&fila, "Ana Silva", "12345678900", "01/01/1990", "Reclamar");
    enfileirar(&fila, "Carlos Lima", "98765432100", "15/03/1985", "Elogiar");
    enfileirar(&fila, "Marcos Souza", "32165498700", "12/12/1975", "Reclamar");
    enfileirar(&fila, "Julia Costa", "45612378900", "25/09/1995", "Elogiar");
    enfileirar(&fila, "Fernanda Rocha", "65498712300", "30/06/2000", "Reclamar");

    int reclamar = 0, elogiar = 0;

    Pessoa* pessoa;
    while ((pessoa = desenfileirar(&fila)) != NULL) {
        if (comparaTexto(pessoa->motivo_visita, "Reclamar")) {
            reclamar++;
        } else if (comparaTexto(pessoa->motivo_visita, "Elogiar")) {
            elogiar++;
        }
        free(pessoa);
    }

    // Exibe a saída ordenada
    if (reclamar < elogiar) {
        printf("Na fila de hoje tivemos %d pessoas que vieram reclamar e %d para elogiar.\n", reclamar, elogiar);
    } else {
        printf("Na fila de hoje tivemos %d pessoas que vieram elogiar e %d para reclamar.\n", elogiar, reclamar);
    }

    return 0;
}
