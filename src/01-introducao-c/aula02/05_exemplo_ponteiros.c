#include <stdio.h>

// Função que recebe um inteiro e o imprime
void soma(int num1, int num2) { printf("A soma é: %d\n", (num1 + num2)); }

// Função que retorna a soma de dois inteiros
int somaRetorna(int a, int b) { return a + b; }

// Função que recebe dois inteiros e troca seus valores usando ponteiros
void exemploPonteiroEmFuncao(int *ptrA, int *ptrB) {
  int temp =
      *ptrA; // Armazena o valor apontado por ptrA em uma variável temporária
  *ptrA = *ptrB; // Atribui o valor apontado por ptrB para ptrA
  *ptrB = temp;  // Atribui o valor temporário para ptrB
}

void exemploTamanhoPonteiro() {
  int array[] = {10, 20, 30, 40, 50};
  char nome[] = "Joao";
  char *ptr = nome;
  printf("%d em bytes\n", sizeof(array));
  printf("%d em bytes\n", sizeof(nome));
  printf("%d em bytes\n", sizeof(ptr));
  printf("A primeira letra é %c\n", *(ptr));
}

void exemploPonteiroDePonteiroDePonteiro() {
  int x = 10;
  int *ptr1 = &x;      // Ponteiro para x
  int **ptr2 = &ptr1;  // Ponteiro para ptr1
  int ***ptr3 = &ptr2; // Ponteiro para ptr2

  // Imprime o valor de x usando ptr3
  printf("Valor de x (através de ptr3): %d\n", ***ptr3);
}

void exemploPonteiroDePonteiro() {
  int x = 10;
  int *ptr1 = &x;     // Ponteiro para x
  int **ptr2 = &ptr1; // Ponteiro para ptr1
	
  // Imprime o valor de x usando ponteiro ptr1
  printf("Valor de x: %d\n", *ptr1);

  // Imprime o valor de x usando ponteiro para ponteiro ptr2
  printf("Valor de x (através de ptr2): %d\n", **ptr2);

  // Altera o valor de x usando ptr1
  *ptr1 = 20;
  printf("Novo valor de x: %d\n", x);

  // Altera o valor de x usando ptr2
  **ptr2 = 30;
  printf("Novo valor de x (alterado através de ptr2): %d\n", x);
}

void exemploPonteiroFuncaoRetorna() {
  // Declaração de um ponteiro para função que retorna inteiros
  int (*ptr)(int, int);

  // Atribui o endereço da função 'soma' ao ponteiro
  ptr = somaRetorna;

  // Chama a função através do ponteiro e imprime o resultado
  int resultado = ptr(10, 20);
  printf("Resultado da soma: %d\n", resultado);
}

void exemploPonteiroFuncao() {
  void (*ptr)(int, int); // Ponteiro para função que não retorna valor

  ptr = soma; // Atribui o endereço da função 'soma' ao ponteiro

  // Chama a função através do ponteiro
  ptr(100, 150);
}

void apontaElementoArray() {
  int array[] = {10, 20, 30, 40, 50};
  int *ptr = array; // Ponteiro para o primeiro elemento do array

  // Imprime os elementos do array usando aritmética de ponteiros
  for (int i = 0; i < 5; i++) {
    printf("Elemento %d: %d\n", i, *(ptr + i));
  }
}

void exemploPonteiro() {
  int var = 10; // Declaração de uma variável inteira
  int *ptr;     // Declaração de um ponteiro para inteiro

  ptr = &var; // Atribui o endereço de 'var' ao ponteiro 'ptr'

  printf("Tamanho em bits de um ponteiro: %d\n", sizeof(ptr) * 8);
  printf("Tamanho em bits de um inteiro: %d\n", sizeof(var) * 8);

  // Imprime endereço de memória da variável 'var'
  printf("Endereço de memória da variável 'var': %p\n", &var);
  printf("Endereço de memória da variável 'ptr': %p\n", &ptr);

  // Imprime o valor de 'var' e o valor apontado por 'ptr'
  printf("Valor de var: %d\n", var);
  printf("Valor apontado por ptr: %d\n", *ptr);

  // Modifica o valor de 'var' através do ponteiro 'ptr'
  *ptr = 20;

  // Imprime o novo valor de 'var' e o valor apontado por 'ptr'
  printf("Novo valor de var: %d\n", var);
  printf("Novo valor apontado por ptr: %d\n", *ptr);
}

void exemploPonteiroNulo() {
  int *ptr = NULL; // Ponteiro nulo

  if (ptr == NULL) {
    printf("O ponteiro ptr aponta para NULL\n");
  }
}

void exemploPonteiroVariaveis() {
  int var1 = 10;
  int var2 = 20;
  int *ptr1 = &var1;
  int *ptr2 = &var2;

  printf("Endereço de var1: %p\n", &var1);
  printf("Endereço de var2: %p\n", &var2);
}

int main(void) {
  exemploPonteiroVariaveis();
  // exemploPonteiro();
  // apontaElementoArray();
   // exemploPonteiroFuncao();
  // exemploPonteiroFuncaoRetorna();
  // exemploPonteiroDePonteiro();
  // exemploPonteiroDePonteiroDePonteiro();
  // exemploTamanhoPonteiro();
  // int a = 5, b = 10;
  // exemploPonteiroEmFuncao(&a, &b);
  return 0;
}