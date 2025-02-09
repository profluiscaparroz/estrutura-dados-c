#include <stdio.h>

// Função para demonstrar diferentes tipos de conversão de dados em C
void conversaoTipos()
{
    // Conversão de int para float
    // Aqui, um número inteiro (int) é explicitamente convertido para ponto flutuante (float)
    int inteiro = 10;
    float flutuante = (float)inteiro; // Casting explícito de int para float
    printf("Conversão de int para float: %d -> %.2f\n", inteiro, flutuante);

    // Conversão de float para int
    // Quando convertemos um número float para int, a parte decimal é descartada
    float numeroDecimal = 5.75;
    int numeroInteiro = (int)numeroDecimal; // Casting explícito de float para int
    printf("Conversão de float para int: %.2f -> %d\n", numeroDecimal, numeroInteiro);

    // Conversão de char para int
    // Em C, os caracteres são armazenados internamente como códigos ASCII
    char caractere = 'A';
    int codigoAscii = (int)caractere; // Casting explícito de char para int
    printf("Conversão de char para int: '%c' -> %d\n", caractere, codigoAscii);

    // Conversão de int para char
    // Podemos converter um código ASCII (int) para o caractere correspondente
    int codigoAscii2 = 98;
    char caractere2 = (char)codigoAscii2; // Casting explícito de int para char
    printf("Conversão de int para char: %d -> '%c'\n", codigoAscii2, caractere2);
}

int main()
{
    // Chamando a função que demonstra conversões de tipos
    conversaoTipos();
    return 0;
}
