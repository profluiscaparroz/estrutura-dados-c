#include <stdio.h>
#include <math.h>

// Função para a qual queremos encontrar a solução (exemplo: f(x) = x^2 - 2)
// Retorna o valor de f(x) para um dado x
double funcao(double x) {
    return x * x - 2; // Exemplo: encontrar a raiz quadrada de 2
}

// Função para realizar a busca binária em um domínio contínuo
// Parâmetros:
// - esquerda: limite inferior do intervalo
// - direita: limite superior do intervalo
// - precisao: precisão desejada para o resultado
// Retorna:
// - O valor aproximado de x que satisfaz f(x) ≈ 0
double buscaBinariaContinuo(double esquerda, double direita, double precisao) {
    double meio;

    // Continua enquanto o intervalo for maior que a precisão desejada
    while ((direita - esquerda) > precisao) {
        meio = (esquerda + direita) / 2.0; // Calcula o ponto médio do intervalo

        // Verifica o valor da função no ponto médio
        double valorMeio = funcao(meio);

        // Se f(meio) for aproximadamente 0, encontramos a solução
        if (fabs(valorMeio) < precisao) {
            return meio;
        }

        // Decide em qual metade do intervalo continuar a busca
        if (valorMeio > 0) {
            direita = meio; // A solução está na metade esquerda
        } else {
            esquerda = meio; // A solução está na metade direita
        }
    }

    // Retorna o ponto médio como a solução aproximada
    return (esquerda + direita) / 2.0;
}

int main() {
    // Intervalo inicial para a busca
    double esquerda = 0.0;
    double direita = 2.0;

    // Precisão desejada para o resultado
    double precisao = 0.00001;

    // Chama a função de busca binária em domínios contínuos
    double resultado = buscaBinariaContinuo(esquerda, direita, precisao);

    // Exibe o resultado
    printf("A solução aproximada é: %.10f\n", resultado);

    return 0;
}

/*
Contexto e Explicação da Abordagem:

A Busca Binária em Domínios Contínuos é uma extensão da busca binária tradicional, aplicada a intervalos contínuos de números reais. É amplamente utilizada em problemas de otimização e aproximação numérica, como encontrar raízes de funções ou valores que satisfazem uma condição específica.

Passos da abordagem:
1. **Definição do intervalo inicial:**
   - O intervalo `[esquerda, direita]` deve conter a solução desejada. Por exemplo, para encontrar a raiz quadrada de 2, podemos usar `[0, 2]`.

2. **Divisão do intervalo:**
   - O ponto médio do intervalo é calculado como `(esquerda + direita) / 2.0`.

3. **Avaliação da função:**
   - A função `f(x)` é avaliada no ponto médio.
   - Se `f(meio)` for aproximadamente 0 (dentro da precisão desejada), o ponto médio é retornado como a solução.

4. **Redução do intervalo:**
   - Se `f(meio) > 0`, a solução está na metade esquerda, e o intervalo é reduzido para `[esquerda, meio]`.
   - Se `f(meio) < 0`, a solução está na metade direita, e o intervalo é reduzido para `[meio, direita]`.

5. **Convergência:**
   - O processo continua até que o tamanho do intervalo seja menor que a precisão desejada.

**Complexidade de Tempo:**
- A complexidade é **O(log((direita - esquerda) / precisao))**, onde `direita - esquerda` é o tamanho inicial do intervalo e `precisao` é o critério de parada.

**Exemplo no código:**
- A função `f(x) = x^2 - 2` é usada para encontrar a raiz quadrada de 2.
- O intervalo inicial é `[0, 2]`, e a precisão desejada é `0.00001`.
- A solução aproximada será `√2 ≈ 1.41421`.

**Vantagens:**
- Simples de implementar.
- Alta precisão, dependendo do critério de parada.

**Desvantagens:**
- Requer que o intervalo inicial contenha a solução.
- Não funciona bem para funções com múltiplas raízes no intervalo.

Essa abordagem é amplamente utilizada em problemas de engenharia, física e matemática para encontrar soluções aproximadas de equações não lineares.
*/