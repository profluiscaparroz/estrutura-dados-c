#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// CONSTANTES
const double PI = 3.14159;
#define MAX_SIZE 10

// VARIÁVEIS GLOBAIS
int variavelGlobal = 10;

// DEFINIÇÕES DE TIPOS
typedef long int tipo_longo;

typedef struct {
  char nome[50];
  int idade;
} Cliente;

// EXIBIÇÃO DE CONSTANTES
void exibindoConstante() {
  printf("Constantes:\n");
  printf("MAX_SIZE: %d\n", MAX_SIZE);
  printf("PI: %.5f\n\n", PI);
}

// FORMAS DE DECLARAR VARIÁVEIS
void formasDeclararVariaveis() {
  int numero = 10;
  float preco = 25.99;
  char caractere = 'A';

  printf("Exemplo de declaração e inicialização:\n");
  printf("Numero: %d\n", numero);
  printf("Preco: %.2f\n", preco);
  printf("Caractere: %c\n\n", caractere);
}

// TIPOS DE VARIÁVEIS
void exemplosVariaveis() {
  printf("Tipos de Variáveis:\n");
  printf("char signed: %c\n", 'A');
  printf("int signed: %d\n", 2147483647);
  printf("unsigned int: %u\n", 4294967295U);
  printf("float: %.2f\n", 3.14f);
  printf("double: %.10f\n", 3.1415926535);
  printf("bool verdadeiro: %d\n", true);
  printf("bool falso: %d\n\n", false);
}

// ARRAYS DE CARACTERES
void exemploSimplesVetoresCaracteres() {
  char mensagem[] = "Exemplo de array de char";
  char nomeUsuario[50];

   // Não é possível fazer a seguinte atribuição com =, pois string são imutáveis
  // nomeUsuario = "João da Costa";
  // Para funcionar é preciso alocar memória para a string ou usar a biblioteca
  // string.h
  strcpy(nomeUsuario, "João da Costa");
  printf("Mensagem: %s\n", mensagem);
  printf("Olá, %s! Bem-vindo!\n\n", nomeUsuario);
}

// COPIANDO STRINGS SEM STRING.H
void exemploAlocacaoVetoresSemUsoStringH() {
  char nomeUsuario[50];
  const char *nomeOriginal = "João da Costa";

  for (int i = 0; i < 49 && nomeOriginal[i] != '\0'; ++i) {
    nomeUsuario[i] = nomeOriginal[i];
  }
  nomeUsuario[49] = '\0';

  printf("Nome do usuário (manual): %s\n\n", nomeUsuario);
}

// STRUCT: ENTRADA DO USUÁRIO
void exemploUtilizandoStructPessoaEntradaUsuario() {
  struct {
    char nome[50];
    int idade;
  } pessoa;

  printf("Digite o nome: ");
  scanf("%s", pessoa.nome);

  printf("Digite a idade: ");
  scanf("%d", &pessoa.idade);

  printf("Nome: %s\n", pessoa.nome);
  printf("Idade: %d\n\n", pessoa.idade);
}

// STRUCT: CLIENTE COM TYPEDEF
void exemploUtilizandoStructClienteEntradaUsuario() {
  Cliente cliente;

  printf("Digite o nome: ");
  scanf("%s", cliente.nome);

  printf("Digite a idade: ");
  scanf("%d", &cliente.idade);

  printf("Nome: %s\n", cliente.nome);
  printf("Idade: %d\n\n", cliente.idade);
}

int main() {
  exibindoConstante();
  formasDeclararVariaveis();
  exemplosVariaveis();
  exemploSimplesVetoresCaracteres();
  exemploAlocacaoVetoresSemUsoStringH();
  exemploUtilizandoStructPessoaEntradaUsuario();
  exemploUtilizandoStructClienteEntradaUsuario();
  return 0;
}
