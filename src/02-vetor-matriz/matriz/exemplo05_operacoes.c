#include <stdio.h>
#include <stdlib.h>

void AcessoModificacao(){
    int matriz[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    // Leitura
    int valor = matriz[1][2];  // linha 1, coluna 2 = 7
    
    // Modificação
    matriz[1][2] = 99;  // Agora matriz[1][2] = 99
    
    // Complexidade: O(1) - acesso direto
}

void percorrerLinha(){
    int matriz[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    // Percorre linha por linha
    for (int i = 0; i < 3; i++) {           // Para cada linha
        for (int j = 0; j < 4; j++) {       // Para cada coluna
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    // Saída:
    // 1 2 3 4
    // 5 6 7 8
    // 9 10 11 12
    
    // Complexidade: O(m × n) onde m=linhas, n=colunas
    // Explicação: Visita cada um dos m×n elementos uma vez
}

void percorrerColuna() {

    int matriz[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    // Percorre coluna por coluna
    for (int j = 0; j < 4; j++) {           // Para cada coluna
        for (int i = 0; i < 3; i++) {       // Para cada linha
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    // Saída:
    // 1 5 9
    // 2 6 10
    // 3 7 11
    // 4 8 12

    // ⚠️ Menos eficiente que percorrer por linhas devido ao cache
}

int main() {


}