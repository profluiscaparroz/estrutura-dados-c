#include <stdio.h>

// Escopo de variável global. 
// Todas as funções do dentro do arquivo irá conseguir 
// 'ver' e modificar
int var = 35;
int idade;

void funcao()
{
	printf("%d", var);
}

void exemploVariavelLocal()
{
	int var = 10;
	{
		printf("%d\n", var);
		{
			int var = 20;
			printf("%d\n", var);
		}
	}
}

void exemploVariavelEstatica() {
		// Variável local persistente entre chamadas
		static int contador = 0;
		contador++;

		printf("Chamada %d: Valor do contador = %d\n", contador, contador);
}

int main(void) {
	exemploVariavelLocal();
	exemploVariavelEstatica();
	exemploVariavelEstatica();
	exemploVariavelEstatica();
	exemploVariavelEstatica();
	return 0;
}