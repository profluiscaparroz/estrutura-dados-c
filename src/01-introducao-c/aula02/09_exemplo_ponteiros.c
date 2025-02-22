/*
 * Ponteiros em C: Explicação e Exemplos
 * 
 * Em C, um ponteiro é uma variável que armazena o endereço de memória de outra variável.
 * Ponteiros são amplamente utilizados para manipulação de arrays, strings, estruturas e alocação dinâmica de memória.
 */

 #include <stdio.h>

 void exemploPonteiro() {
     int x = 10;
     int *p = &x; // Ponteiro armazenando o endereço de x
 
     printf("Valor de x: %d\n", x);
     printf("Endereço de x: %p\n", &x);
     printf("Valor armazenado no ponteiro p: %p\n", p);
     printf("Valor apontado por p: %d\n", *p); // Acessando o valor de x via ponteiro
 }
 
 void manipulacaoComPonteiros() {
     int a = 5, b = 10;
     int *ptr1 = &a, *ptr2 = &b;
     
     printf("Antes da troca: a = %d, b = %d\n", a, b);
     
     // Trocando valores usando ponteiros
     int temp = *ptr1;
     *ptr1 = *ptr2;
     *ptr2 = temp;
     
     printf("Depois da troca: a = %d, b = %d\n", a, b);
 }
 
 void alocacaoDinamica() {
     int *arr;
     int tamanho = 5;
     
     arr = (int *)malloc(tamanho * sizeof(int)); // Alocando memória dinamicamente
     if (arr == NULL) {
         printf("Erro na alocação de memória\n");
         return;
     }
     
     for (int i = 0; i < tamanho; i++) {
         arr[i] = i * 2; // Preenchendo o array
     }
     
     printf("Array alocado dinamicamente:\n");
     for (int i = 0; i < tamanho; i++) {
         printf("%d ", arr[i]);
     }
     printf("\n");
     
     free(arr); // Liberando a memória alocada
 }
 
 int main() {
     printf("### Exemplo de Ponteiro ###\n");
     exemploPonteiro();
     
     printf("\n### Manipulação com Ponteiros ###\n");
     manipulacaoComPonteiros();
     
     printf("\n### Alocação Dinâmica de Memória ###\n");
     alocacaoDinamica();
     
     return 0;
 }
 