#include <stdio.h>

int main() {
    int codigoCliente = 1;
    char nomeCliente[50] = "Jose Da Silva";
    char logradouroCliente[50] = "Rua 1, 123";
    char descricaoProduto[50] = "Produto 1";
    float precoProduto = 100.0f;
    char aprovado = 'S';

    // Exibindo os valores
    printf("Codigo do cliente: %d\n", codigoCliente);
    printf("Nome do cliente: %s\n", nomeCliente);
    printf("Logradouro do cliente: %s\n", logradouroCliente);
    printf("Descricao do produto: %s\n", descricaoProduto);
    printf("Preco do produto: %.2f\n", precoProduto);
    printf("Aprovado: %c\n", aprovado);
}