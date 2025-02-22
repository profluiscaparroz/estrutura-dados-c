#include <stdio.h>

void exercicio1(){
	int valor1 = 10;
	int valor2 = 15;
	if(valor1 >= valor2){
		printf("%d", valor1 - valor2);
	}
	else {
		printf("%d", valor2 - valor1);
	}	
}

void exercicio2(){
	int valor1 = 15;
	if(valor1 < 0){
		printf("%d", valor1 * -1);
	}
	else
	{
		printf("%d", valor1);
	}
}

void exercicio3(){
	int valor1 = 16;
	int valor2 = 15;
	if(valor1 >= valor2){
		printf("%d, %d", valor2, valor1);
	} else {
		printf("%d, %d", valor1, valor2);
	}
}

void exercicio4(){
	int valor1 = 0;
	if(valor1 > 0){
		printf("Positivo");
	} else	if(valor1 == 0){
		printf("Zero");
	} else {
		printf("Negativo");
	}
}

int main(void) {
	//exercicio1();
	//exercicio2();
	//exercicio3();
	exercicio4();
  return 0;
}