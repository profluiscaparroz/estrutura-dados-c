#include <stdio.h>
#include <string.h>

// Definição da struct para representar um aluno
struct Aluno {
  char nome[50];
  float nota1;
  float nota2;
  float nota3;
};

// Função para criar um novo aluno
struct Aluno criarAluno(char nome[], float nota1, float nota2, float nota3) {
  struct Aluno a;
  strcpy(a.nome, nome);
  a.nota1 = nota1;
  a.nota2 = nota2;
  a.nota3 = nota3;
  return a;
}

// Função para calcular a média das notas do aluno
float calcularMedia(struct Aluno a) {
  return (a.nota1 + a.nota2 + a.nota3) / 3;
}

// Função para verificar se o aluno foi aprovado
int verificarAprovacao(struct Aluno a, float mediaCorte) {
  return calcularMedia(a) >= mediaCorte;
}

// Função para imprimir as informações do aluno
void imprimirAluno(struct Aluno a) {
  printf("Aluno: %s\n", a.nome);
  printf("Notas: %.2f, %.2f, %.2f\n", a.nota1, a.nota2, a.nota3);
  printf("Média: %.2f\n", calcularMedia(a));
  if (verificarAprovacao(a, 7.0)) {
    printf("Status: Aprovado\n");
  } else {
    printf("Status: Reprovado\n");
  }
}

// Função principal
int main() {
  // Criando um aluno
  struct Aluno aluno1 = criarAluno("João Silva", 6.5, 7.8, 9.0);

  // Imprimindo as informações do aluno
  imprimirAluno(aluno1);

  return 0;
}