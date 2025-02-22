#include <stdio.h>

void exemploSimplesIf()
{
	int idade = 16;

	// Verificando se a pessoa é maior de idade (18 anos ou mais)
	int ehMaiorDeIdade = idade >= 18;
	printf("%d\n", ehMaiorDeIdade);
	if(ehMaiorDeIdade)
	{
		printf("É maior de idade");
	}
	else
	{
		printf("É menor de idade");
	}
}

void exemploIfAninhado()
{
	int idade = 18;
	float altura = 1.85f;

	// Verificando se a pessoa tem idade suficiente e altura para entrar no brinquedo
	if(idade >= 18)
	{
		if(altura >= 1.6)
		{
			printf("Pode entrar no brinquedo");
		}
		else
		{
			printf("Não pode entrar no brinquedo");
		}
	}
}

void exemploIfElseIf()
{
	int idade = 16;

	// Verificando as condições de idade para entrar no brinquedo
	if(idade >= 18)
	{
		printf("Pode entrar no brinquedo");
	}
	else if(idade >= 16)
	{
		printf("Pode entrar no brinquedo com acompanhante");
	}
	else
	{
		printf("Não pode entrar");
	}
}

void exemploSwitch()
{
	int mes = 2;

	// Verificando o mês utilizando o comando switch
	switch(mes){
		case 1:
			printf("Janeiro");
			break;
		case 2:
			printf("Fevereiro");
			break;
		case 3:
			printf("Março");
			break;
		default:
			printf("Mês não cadastrado");
	}
}

void exemploCondicionalComStrings()
{
	char sexo = 'M'; // 'M' para masculino e 'F' para feminino

	// Verificando o sexo da pessoa
	if(sexo == 'M')
	{
		printf("Sexo masculino");
	}
	else if(sexo == 'F')
	{
		printf("Sexo feminino");
	}
	else
	{
		printf("Sexo não informado corretamente");
	}
}

void exemploCondicionalComFloat()
{
	float temperatura = 36.6f;

	// Verificando a temperatura corporal
	if(temperatura >= 37.5f)
	{
		printf("Febre alta");
	}
	else if(temperatura >= 37.0f)
	{
		printf("Febre moderada");
	}
	else
	{
		printf("Temperatura normal");
	}
}

void exemploCondicionalComArrays()
{
	int numeros[] = {3, 5, 7, 10, 15};
	int tamanho = sizeof(numeros) / sizeof(numeros[0]);

	// Verificando se um número específico está no array
	int numeroProcurado = 10;
	int encontrado = 0;

	for(int i = 0; i < tamanho; i++)
	{
		if(numeros[i] == numeroProcurado)
		{
			encontrado = 1;
			break;
		}
	}

	if(encontrado)
	{
		printf("Número encontrado no array");
	}
	else
	{
		printf("Número não encontrado no array");
	}
}

int main(void) {
	exemploSimplesIf();
	exemploIfAninhado();
	exemploIfElseIf();
	exemploSwitch();
	exemploCondicionalComStrings();
	exemploCondicionalComFloat();
	exemploCondicionalComArrays();
	return 0;
}
