#include <stdio.h>

int main() {
    // Inicializacao simples
    int matriz[3][4]; // Declaração de uma matriz 3x4

    // Inicializacao completa
    int matrizCompleta[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    int matrizAlternativa[2][3] = {1, 2, 3, 4, 5, 6};
    // Compilador distribui automaticamente:
    // {1,2,3} -> linha 0
    // {4,5,6} -> linha 1

    int matrizParcial[2][3] = {
        {1, 2},       // linha 0: [1, 2, 0]
        {4}           // linha 1: [4, 0, 0]
    };
    // Elementos não especificados = 0

    int matrizComZeros[3][4] = {0};  // Todos os elementos = 0
    // Forma rápida e segura de zerar uma matriz

    int matrizInferido[][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    // Compilador infere: matriz[2][3]
    // ⚠️ Número de colunas DEVE ser especificado!
}
