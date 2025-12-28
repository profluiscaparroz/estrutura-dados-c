# Exercícios - Aula 02

## 📋 Visão Geral

Este diretório contém exercícios práticos para fixação dos conceitos de controle de fluxo, laços de repetição, ponteiros e strings apresentados na Aula 02.

## 📚 Exercícios Disponíveis

### Exercício 1 - `exercicioCadastro.c`
Sistema simples de cadastro utilizando estruturas de controle.

**Conceitos trabalhados:**
- Estruturas de decisão (if/else)
- Laços de repetição
- Manipulação de dados
- Entrada e saída de dados

**Objetivo:** Implementar um sistema básico de cadastro que permita adicionar e consultar informações.

### Exercício 2 - `exercicioContaVogaisConsoante.c`
Programa para contar vogais e consoantes em uma string.

**Conceitos trabalhados:**
- Manipulação de strings
- Laços de repetição
- Estruturas de decisão
- Operadores lógicos

**Objetivo:** Percorrer uma string e identificar/contar vogais e consoantes.

### Exercício 3 - `exercicioSomaMultiplo.c`
Operações matemáticas com múltiplos usando laços.

**Conceitos trabalhados:**
- Laços de repetição (for/while)
- Operadores aritméticos
- Operador módulo (%)
- Lógica de múltiplos

**Objetivo:** Calcular soma de múltiplos de um número em um intervalo.

### Exercício 4 - `exerciciosSimples.c`
Conjunto de exercícios variados para prática geral.

**Conceitos trabalhados:**
- Combinação de todos os conceitos da aula
- Resolução de problemas diversos
- Implementação de algoritmos simples

## 🔧 Como Compilar e Executar

Para compilar qualquer exercício:

```bash
gcc -Wall -Wextra -std=c99 -o cadastro exercicioCadastro.c
./cadastro
```

Ou compile todos de uma vez:

```bash
gcc -Wall -Wextra -std=c99 -o cadastro exercicioCadastro.c
gcc -Wall -Wextra -std=c99 -o vogais exercicioContaVogaisConsoante.c
gcc -Wall -Wextra -std=c99 -o soma exercicioSomaMultiplo.c
gcc -Wall -Wextra -std=c99 -o simples exerciciosSimples.c
```

## ✅ Checklist de Aprendizado

Antes de prosseguir, certifique-se de que você consegue:

- [ ] Implementar estruturas de decisão (if/else, switch)
- [ ] Criar e controlar laços de repetição
- [ ] Manipular strings caractere por caractere
- [ ] Usar operadores lógicos e relacionais corretamente
- [ ] Implementar lógica para identificar padrões (vogais, múltiplos, etc.)
- [ ] Combinar diferentes estruturas de controle

## 📖 Dicas

### Para Contar Vogais e Consoantes

```c
// Verificar se é vogal
if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
    c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
    vogais++;
}

// Verificar se é letra
if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
    // É uma letra
}
```

### Para Trabalhar com Múltiplos

```c
// Verificar se 'n' é múltiplo de 'x'
if (n % x == 0) {
    // n é múltiplo de x
}

// Somar múltiplos de 'x' até 'limite'
int soma = 0;
for (int i = x; i <= limite; i += x) {
    soma += i;
}
```

### Para Strings

```c
// Percorrer string até encontrar '\0'
for (int i = 0; str[i] != '\0'; i++) {
    // processar str[i]
}

// Ou usando strlen
int len = strlen(str);
for (int i = 0; i < len; i++) {
    // processar str[i]
}
```

## 🐛 Problemas Comuns

### Laço Infinito
**Problema**: O laço nunca termina.  
**Solução**: Verifique se a condição de parada está correta e se as variáveis são atualizadas dentro do laço.

### Acesso Fora dos Limites do Array
**Problema**: Erro de segmentação ao acessar string.  
**Solução**: Sempre verifique se o índice está dentro dos limites (`i < strlen(str)` ou `str[i] != '\0'`).

### Comparação de Strings com ==
**Problema**: Comparação não funciona como esperado.  
**Solução**: Use `strcmp()` para comparar strings, não o operador `==`.

## 🚀 Desafios Adicionais

Após completar os exercícios, tente:

1. **Exercício de Vogais**: Adicionar contagem de cada vogal separadamente
2. **Exercício de Múltiplos**: Calcular múltiplos comuns entre dois números
3. **Sistema de Cadastro**: Adicionar função de busca e edição
4. **Validação**: Adicionar validação de entrada em todos os exercícios

## 💡 Exemplos Úteis

### Estrutura de Menu

```c
int opcao;
do {
    printf("\n=== MENU ===\n");
    printf("1. Opção 1\n");
    printf("2. Opção 2\n");
    printf("0. Sair\n");
    printf("Escolha: ");
    scanf("%d", &opcao);
    
    switch(opcao) {
        case 1:
            // código
            break;
        case 2:
            // código
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida!\n");
    }
} while(opcao != 0);
```

## 🔗 Recursos

- Revise os exemplos na pasta principal da aula02
- Consulte a documentação de funções de string
- [C Control Structures](https://en.cppreference.com/w/c/language/statements)
- [C String Functions](https://en.cppreference.com/w/c/string/byte)

---

**Repositório**: https://github.com/profluiscaparroz/estrutura-dados-c
