#include <stdio.h>

void exemploSimplesIf()
{
	int idade = 16;

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
	if(idade >= 18)
	{
		if(altura >= 1.6)
		{
			printf("Pode entrar no brinquedo");
		}
		else
		{
			printf("Não pode entra no brinquedo");
		}
	}
	
}

void exemploIfElseIf()
{
	int idade = 16;
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

int main(void) {
	//exemploSimplesIf();
	//exemploIfAninhado();
	//exemploIfElseIf();
	exemploSwitch();
	return 0;
}