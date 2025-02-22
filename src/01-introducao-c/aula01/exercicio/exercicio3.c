#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 100
typedef struct {
    int codigo;
    char descricao[MAX_SIZE];
    float valorTotal;
    int quantidadeItens;
    bool achouCaro;
} Item;

void cadastrarItem(Item *item) {
    printf("Digite o codigo do item: ");
    scanf("%d", &item->codigo);
    printf("Digite a descricao do item: ");
    scanf(" %[^\n]s", item->descricao);
    printf("Digite o valor total do item: ");
    scanf("%f", &item->valorTotal);
    printf("Digite a quantidade de itens: ");
    scanf("%d", &item->quantidadeItens);
    item->achouCaro = item->valorTotal > 1000;
}

void cadastrarItemPorParametros(Item *item, int codigo, char *descricao, float valorTotal, int quantidadeItens, bool achouCaro) {
    item->codigo = codigo;
    strcpy(item->descricao, descricao);
    item->valorTotal = valorTotal;
    item->quantidadeItens = quantidadeItens;
    item->achouCaro = achouCaro;
}

void exibirItem(Item *item) {
    printf("Codigo: %d\n", item->codigo);
    printf("Descricao: %s\n", item->descricao);
    printf("Valor total: %.2f\n", item->valorTotal);
    printf("Quantidade de itens: %d\n", item->quantidadeItens);
    printf("Achou caro: %s\n", item->achouCaro ? "Sim" : "Nao");
}

int main() {
    Item item[5];
    cadastrarItem(&item[0]);
    cadastrarItemPorParametros(&item[1], 2, "Item 2", 2000.0f, 2, true);
    cadastrarItemPorParametros(&item[2], 2, "Item 2", 2000.0f, 2, true);
    cadastrarItemPorParametros(&item[3], 2, "Item 2", 2000.0f, 2, true);
    cadastrarItemPorParametros(&item[4], 2, "Item 2", 2000.0f, 2, true);
    
    exibirItem(&item[0]);
    exibirItem(&item[1]);
    exibirItem(&item[2]);
    exibirItem(&item[3]);
    exibirItem(&item[4]);

    return 0;
}