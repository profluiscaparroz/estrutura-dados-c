#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
O que é um ponteiro void (void*):
Um ponteiro genérico (void*) é um tipo especial de ponteiro em C que pode armazenar o endereço de qualquer tipo de dado, sem especificar qual o tipo desse dado. Isso o torna extremamente flexível para criar funções e estruturas de dados genéricas.

Características principais:
Flexibilidade: pode apontar para qualquer tipo de dado (int, float, char, struct, etc.)
Não possui aritmética de ponteiro: como o compilador não sabe o tamanho do dado, não é possível realizar operações como ptr++
Requer conversão (casting): para acessar o conteúdo, é necessário converter o ponteiro void para o tipo apropriado
Tamanho fixo: independente do tipo apontado, o ponteiro void ocupa o mesmo espaço (geralmente 4 ou 8 bytes)

Usos comuns:
Funções genéricas: como malloc(), free(), qsort(), bsearch()
Callbacks: funções que recebem dados de tipos diversos
Implementações de estruturas de dados genéricas: como listas, pilhas ou árvores
Manipulação de memória de baixo nível

Pontos importantes:
Sem verificação de tipo: o compilador não verifica se a conversão é apropriada
Responsabilidade do programador: garantir que a conversão seja feita para o tipo correto
Não permite desreferenciamento direto: você não pode fazer *ptr sem antes converter
Utilizado amplamente na biblioteca padrão C: funções como malloc() retornam void*
Considerações de segurança:
O uso incorreto pode levar a comportamentos indefinidos
Sempre certifique-se de converter para o tipo correto antes de acessar o conteúdo
Em linguagens mais modernas como C++, existem alternativas mais seguras como templates

*/

// Função genérica que imprime diferentes tipos de dados
void imprimir_dado(void *ptr, char tipo) {
    switch(tipo) {
        case 'i': // inteiro
            printf("Valor inteiro: %d\n", *((int*)ptr));
            break;
        case 'f': // float
            printf("Valor float: %.2f\n", *((float*)ptr));
            break;
        case 'c': // char
            printf("Caractere: %c\n", *((char*)ptr));
            break;
        case 's': // string
            printf("String: %s\n", (char*)ptr);
            break;
    }
}

// Função para trocar valores de qualquer tipo
void trocar(void *a, void *b, size_t tamanho) {
    // Buffer temporário para armazenar os dados durante a troca
    void *temp = malloc(tamanho);
    
    // Copia o conteúdo de 'a' para o buffer temporário
    memcpy(temp, a, tamanho);
    // Copia o conteúdo de 'b' para 'a'
    memcpy(a, b, tamanho);
    // Copia o conteúdo do buffer temporário para 'b'
    memcpy(b, temp, tamanho);
    
    free(temp);
}

int main() {
    // Exemplos com diferentes tipos de dados
    int num = 42;
    float pi = 3.14159;
    char letra = 'A';
    char texto[] = "Olá, mundo!";
    
    // Usando ponteiro void para diferentes tipos
    void *ptr;
    
    // Aponta para um inteiro
    ptr = &num;
    imprimir_dado(ptr, 'i');
    
    // Aponta para um float
    ptr = &pi;
    imprimir_dado(ptr, 'f');
    
    // Aponta para um char
    ptr = &letra;
    imprimir_dado(ptr, 'c');
    
    // Aponta para uma string
    ptr = texto;
    imprimir_dado(ptr, 's');
    
    // Exemplo de troca de valores
    int a = 10, b = 20;
    printf("\nAntes da troca: a = %d, b = %d\n", a, b);
    trocar(&a, &b, sizeof(int));
    printf("Depois da troca: a = %d, b = %d\n", a, b);
    
    return 0;
}