#include <stdio.h>

void exemploGoto()
{
    int num = 0;

    printf("Digite um número (0 para sair): ");
    scanf("%d", &num);

    if (num == 0) {
        goto end;
    }

    printf("Você digitou: %d\n", num);

end:
    printf("Programa encerrado.\n");
}

void exemploContinue()
{
    for (size_t i = 0; i < 10; i++)
    {
        if(i % 2 != 0){
            continue;
        }
        printf("%d é par.\n", i);
    }
}

void exemploBreak()
{
    for (size_t i = 0; i < 10; i++)
    {
        if(i == 5){
            break;
        }
        printf("%d\n", i);
    }
}

void exemploReturn()
{
    for (size_t i = 0; i < 10; i++)
    {
        if(i == 5){
            return;
        }
        printf("%d\n", i);
    }
}

int main() {
    exemploGoto();
    exemploContinue();
    exemploBreak();
    exemploReturn();
    return 0;
}