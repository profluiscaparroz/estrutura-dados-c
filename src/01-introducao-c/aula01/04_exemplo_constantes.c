#include <stdio.h>
#define valorConstante 50

void exemploConstInvalido() {
  const int var = 100;
  // Não pode atribuir valor
  // var = 200;
}

void exemploExibirConstante() {
  printf("Sou um valor constante %d\n", valorConstante);
}

void exemploRedefinirConstante()
{
	printf("%d\n", valorConstante);

#ifdef valorConstante
#undef valorConstante
	
#define valorConstante 30
#endif

	printf("%d\n", valorConstante);
}

int main(void) {
  exemploConstInvalido();
  exemploExibirConstante();
	exemploRedefinirConstante();
  return 0;
}