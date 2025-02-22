#include <stdio.h>

// Função para calcular o comprimento de uma string
int comprimentoString(char *str) {
		int comprimento = 0;
		while (str[comprimento] != '\0') {
				comprimento++;
		}
		return comprimento;
}

// Função para copiar uma string para outra
void copiarString(char *destino, char *origem) {
		int i = 0;
		while (origem[i] != '\0') {
				destino[i] = origem[i];
				i++;
		}
		destino[i] = '\0'; // Adiciona o caractere nulo no final da string copiada
}

// Função para concatenar duas strings
void concatenarString(char *destino, char *origem) {
		int i = 0;
		int j = 0;

		// Encontra o final da string de destino
		while (destino[i] != '\0') {
				i++;
		}

		// Adiciona a string de origem ao final da string de destino
		while (origem[j] != '\0') {
				destino[i] = origem[j];
				i++;
				j++;
		}
		destino[i] = '\0'; // Adiciona o caractere nulo no final da string concatenada
}

// Função para comparar duas strings
int compararString(char *str1, char *str2) {
		int i = 0;
		while (str1[i] != '\0' && str2[i] != '\0') {
				if (str1[i] != str2[i]) {
						// Retorno a diferença
						return str1[i] - str2[i]; 
				}
				i++;
		}
		// String de diferentes tamanhos 
		return str1[i] - str2[i]; 
}

// Função principal
int main() {
		char str1[100] = "Hello";
		char str2[100] = "World";
		char str3[100];

		// Demonstrando a função comprimentoString
		printf("Comprimento de str1: %d\n", comprimentoString(str1));

		// Demonstrando a função copiarString
		copiarString(str3, str1);
		printf("Cópia de str1 em str3: %s\n", str3);

		// Demonstrando a função concatenarString
		concatenarString(str1, str2);
		printf("Concatenando str2 ao final de str1: %s\n", str1);

		// Demonstrando a função compararString
		int cmpResult = compararString("abc", "abc");
		printf("Comparação de 'abc' com 'abc': %d\n", cmpResult);
		cmpResult = compararString("abc", "abd");
		printf("Comparação de 'abc' com 'abd': %d\n", cmpResult);
		cmpResult = compararString("abc", "ab");
		printf("Comparação de 'abc' com 'ab': %d\n", cmpResult);

		return 0;
}
