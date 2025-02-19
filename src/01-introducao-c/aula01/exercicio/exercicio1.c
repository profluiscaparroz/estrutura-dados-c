#include <stdio.h>
#include <string.h>

typedef struct {
  char nome[50];
  unsigned int idade;
  char cpf[12];
  float altura;
  char carteiraDeMotorista[4];
  char possuiCarroProprio[4];
  char tipoSanguineo[4];
}  Pessoa;

int main()
{
    Pessoa jose;
   
    strcpy(jose.nome, "Jose Da Silva");
    jose.idade = 30;
    strcpy(jose.cpf, "98765432111");
    jose.altura = 1.85f;
    strcpy(jose.carteiraDeMotorista, "Sim");
    strcpy(jose.possuiCarroProprio, "Nao");
    strcpy(jose.tipoSanguineo, "AB-");
    printf("Meu nome é %s\n", jose.nome);
    printf("Meu nome é %d\n", jose.idade);
    printf("Meu nome é %s\n", jose.cpf);
    printf("Meu nome é %.2f\n", jose.altura);
    printf("Meu nome é %s\n", jose.carteiraDeMotorista);
    printf("Meu nome é %s\n", jose.possuiCarroProprio);
    printf("Meu nome é %s", jose.tipoSanguineo);  
   
    return 0;
}