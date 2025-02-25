#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100
#define MAX_ITENS 5
#define sim 1
#define nao 0

static int contador = 0;

typedef struct {
	int codigo;
	char descricao[MAX_SIZE];
	float valorTotal;
	int quantidadeItens;
	bool achouCaro;
} Item;

void cadastrarItem(
	Item *item, 
	int codigo, 
	const char *descricao,
	float valorTotal, 
	int quantidadeItens, 
	bool achouCaro) 
{
	item->codigo = codigo;
	strcpy(item->descricao, descricao);
	item->valorTotal = valorTotal;
	item->quantidadeItens = quantidadeItens;
	contador++;
}

void visualizarItem(const Item *item) {
	printf("Código: %d\n", item->codigo);
	printf("Descrição: %s\n", item->descricao);
	printf("Valor Total: %.2f\n", item->valorTotal);
	printf("Quantidade de Itens: %d\n", item->quantidadeItens);
	printf("Achou Caro? %s\n", item->achouCaro ? "Sim" : "Não");
}

void editarItem(Item *itens, int indice, int codigo, const char *descricao, float valorTotal, int quantidadeItens, bool achouCaro) {

	itens[indice].codigo = codigo;
	strcpy(itens[indice].descricao, descricao);
	itens[indice].valorTotal = valorTotal;
	itens[indice].quantidadeItens = quantidadeItens;
	itens[indice].achouCaro = achouCaro;

	printf("Item editado com sucesso.\n");
}

void editarItemName(Item *itens, int indice, const char *descricao) {
	strcpy(itens[indice].descricao, descricao);
	printf("Item editado com sucesso.\n");
}

void editarPreco(Item *itens, int indice, float novoPreco) {
	itens[indice].valorTotal = novoPreco;
	printf("Preço do item editado com sucesso.\n");
}

void apagarItem(Item *itens, int indice) {

	itens[indice].codigo = 0;
	strcpy(itens[indice].descricao, "Produto não cadastrado");
	itens[indice].valorTotal = 0.00;
	itens[indice].quantidadeItens = 0.00;
	itens[indice].achouCaro = "Não";

	printf("Item editado com sucesso.\n");
}

int main(void) {
	Item itens[MAX_ITENS];
	short int indiceItem = 0;
	cadastrarItem(&itens[indiceItem++], 1, "Arroz", 25.86, 1, sim);
	cadastrarItem(&itens[indiceItem++], 2, "Feijao", 11.59, 3, sim);
	cadastrarItem(&itens[indiceItem++], 3, "Macarrao", 3.96, 5, nao);
	cadastrarItem(&itens[indiceItem++], 4, "Molho", 2.99, 5, nao);
	cadastrarItem(&itens[indiceItem++], 5, "Farinha de Trigo", 8.79, 2, sim);

	printf("Quantidade de itens cadastrados: %d\n", contador);

	editarItem(itens, 0, 1, "Arroz Integral", 30.50, 2, sim);
	apagarItem(itens, &indiceItem);

	editarItemName(itens, 0, "Feijão");

	editarPreco(itens, 0, 6.00);
	apagarItem(itens, 3);
	editarPreco(itens, 1, 2.00);
	visualizarItem(&itens[0]);

	return 0;
}