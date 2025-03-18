#include <stdio.h>

void exemploWhile()
{
	int contador = 5;
	while (contador > 0)
	{
		printf("Contador: %d\n", contador);
		contador++;
		//ou
		//contador = contador + 1;
	}
}

void exemploDoWhile()
{
	int contador = 1;
	do {
		printf("contador %d\n", contador);
		contador++;
	} while (contador < 5);
}

void exemploFor()
{
	for (int indice = 0; indice < 5; indice++)
	{
		printf("indice: %d\n", indice);
	}
}

void exemploGoto()
{
	int contador = 1;

	inicio:
	printf("contador: %d\n", contador);
	contador++;
	if(contador < 5)
	{
		goto inicio;
	}
	
}

void exemploContinue()
{
	for (int i = 0; i < 10; i++) {
			// Se o número não for par, pular para a próxima iteração
			if (i % 2 != 0) {
					continue;
			}

			// Se o número for par, imprimir
			printf("%d é par.\n", i);
	}

}

void exemploBreak()
{
	int contador = 0;

	// Exemplo: encontrar o primeiro número maior que 5 em uma sequência
	while (1) {
			// Incrementa o contador a cada iteração
			contador++;

			// Se o contador for maior que 5, sai do loop
			if (contador > 5) {
					break;
			}

			// Se o contador não for maior que 5, continua o loop
			printf("Contador: %d\n", contador);
	}

	// Impressão após sair do loop
	printf("Saiu do loop. Contador final: %d\n", contador);
}

// Perceba que é usado int no lugar do void
int exemploReturnComValor(int valor1, int valor2)
{
	return valor1 + valor2;
}

void exemploReturnSemValor()
{
	int idade = 18;
	if(idade >= 18)
	{
		printf("Maior de idade");
		return;
	}
	printf("Menor de idade");
}

void ehMaiorDeIdade(int idade)
{
	if(idade >= 18)
	{
		printf("Adulto");
	}
	else if(idade >= 60)
	{
		printf("Idoso");
	}
	else
	{
		printf("Criança");
	}
}

void exibirIdadePares()
{
	int idades[] = {15, 25, 36, 40, 85, 74, 12, 30};
	// Faz o cálculo da quantidade de elementos do array
	size_t tamanho = sizeof(idades) / sizeof(idades[0]);

	for (int i = 1; i <= tamanho; i++) {
		if(idades[i] % 2 == 0)
		{
			printf("Idade %d é par\n", idades[i]);
		}
	}
}

void somatorio()
{
	int soma = 0;
	for (int i = 1; i <= 500; i++)
	{
		if(i % 2 != 0)
			soma += i;
	}
	printf("Soma: %d\n", soma);
}

int main(void) {
    exemploWhile();
    exemploDoWhile();
    exemploFor();
    exemploContinue();
    exibirIdadePares();

    unsigned int idades[] = {15, 25, 36, 40, 85, 74, 12, 30};
    printf("%lu\n", sizeof(idades));
    printf("%lu", sizeof(idades[0]));
    printf("%lu", sizeof(idades) / sizeof(idades[0]));
    size_t tamanho = sizeof(idades) / sizeof(idades[0]);
    for (size_t i = 0; i <= tamanho; i++)
    {
        ehMaiorDeIdade(idades[i]);
    }
    
    somatorio();
    
    return 0;
}