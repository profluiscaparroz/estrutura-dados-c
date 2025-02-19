#include <stdbool.h>
#include <stdio.h>
#define bool int
#define true 1
#define false 0

void exemploPerguntas()
{
	int idadePessoa = 18;
	bool maiorDeIdade = idadePessoa >= 18;
	bool menorDeIdade = idadePessoa < 18;
	printf("Eh maior de idade: %d\n", maiorDeIdade);
	printf("Eh menor de idade: %d\n", menorDeIdade);
	
	float altura = 1.85f;
	bool possuiAlturaPermitida = altura >= 1.50f;
	printf("Eh possivel entrar: %d\n", possuiAlturaPermitida);
		
	char nome[] = "Maria Silva";
	bool iniciaComLetraM = nome[0] == 'M';
	printf("Inicia com M: %d\n", iniciaComLetraM);

	double pi = 3.141592653589;
	bool possuiPi = pi == 3.141592653589;
	printf("Possui Pi: %d\n", possuiPi);
	
}
	
void exemploBooleanoDefine() {
  bool a = true;
  bool b = false;

  printf("True : %d\n", a);
  printf("False : %d", b);
}

void exemploBooleano() {
  // Usando inteiros como booleanos
  int verdadeiro = true;
  int falso = false;

  printf("Valor verdadeiro: %d\n", verdadeiro);
  printf("Valor falso: %d\n", falso);

  // Usando inteiros em expressões booleanas
  int x = 5;
  int y = 10;
  int resultado = (x < y);

  printf("O resultado da expressão (x < y) é: %d\n", resultado);
}

void exemploBooleanoBiblioteca() {
  // Boolean data types declared
  bool a = true;
  bool b = false;

  printf("True : %d\n", a);
  printf("False : %d", b);
}

int main() {
    exemploBooleano();
    exemploBooleanoBiblioteca();
    exemploBooleanoDefine();
    exemploPerguntas();
    return 0;
}