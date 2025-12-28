# Aula 02 - Controle de Fluxo, Laços e Ponteiros

## 📋 Visão Geral

Esta aula apresenta conceitos intermediários da linguagem C, incluindo operadores, estruturas de controle de fluxo, laços de repetição, ponteiros e manipulação de strings.

## 📚 Conteúdo da Aula

### Exemplos Incluídos

1. **01_exemplo_operadores.c** - Operadores aritméticos, lógicos e relacionais
2. **02_exemplo_controle_fluxo.c** - Estruturas if, else, switch-case
3. **03_exemplo_laco_repeticao.c** - Laços for, while, do-while
4. **04_exemplo_salto.c** - Comandos break, continue, return
5. **05_exemplo_ponteiros.c** - Introdução a ponteiros
6. **05b_exemplo_ponteiros.c** - Exemplos adicionais de ponteiros
7. **06a_exemplo_string.c** - Manipulação de strings
8. **06b_exemplo_string.c** - Mais exemplos com strings
9. **07_controle_fluxo_completo.c** - Exemplo completo combinando conceitos

## 🎯 Objetivos de Aprendizado

Ao concluir esta aula, você será capaz de:

- ✅ Utilizar operadores aritméticos, lógicos e relacionais
- ✅ Implementar estruturas de decisão (if/else, switch)
- ✅ Criar laços de repetição (for, while, do-while)
- ✅ Usar comandos de salto (break, continue, return)
- ✅ Compreender e manipular ponteiros
- ✅ Trabalhar com strings em C
- ✅ Combinar estruturas de controle em programas complexos

## 🔧 Compilação e Execução

Para compilar qualquer exemplo:

```bash
gcc -Wall -Wextra -std=c99 -o programa nome_do_arquivo.c
./programa
```

Exemplo:
```bash
gcc -Wall -Wextra -std=c99 -o controle 02_exemplo_controle_fluxo.c
./controle
```

## 📖 Conceitos-Chave

### Operadores

**Aritméticos**: `+`, `-`, `*`, `/`, `%`  
**Relacionais**: `==`, `!=`, `<`, `>`, `<=`, `>=`  
**Lógicos**: `&&` (AND), `||` (OR), `!` (NOT)  
**Atribuição**: `=`, `+=`, `-=`, `*=`, `/=`, `%=`

### Estruturas de Controle

**Decisão:**
```c
if (condição) {
    // código
} else if (outra_condição) {
    // código
} else {
    // código
}

switch (variavel) {
    case valor1:
        // código
        break;
    default:
        // código
}
```

**Laços:**
```c
for (int i = 0; i < n; i++) {
    // código
}

while (condição) {
    // código
}

do {
    // código
} while (condição);
```

### Ponteiros

```c
int x = 10;
int *ptr = &x;  // ptr aponta para x
*ptr = 20;      // Modifica o valor de x através do ponteiro
```

**Conceitos importantes:**
- `&` - operador de endereço (address-of)
- `*` - operador de indireção (dereference)
- Ponteiros armazenam endereços de memória

### Strings em C

```c
char str[50] = "Hello";
char *ptr = "World";  // String literal

// Funções comuns
strlen(str)           // Comprimento
strcpy(dest, src)     // Copiar
strcat(dest, src)     // Concatenar
strcmp(str1, str2)    // Comparar
```

## 📝 Exercícios

O diretório `exercicio/` contém exercícios práticos:
- **exercicioCadastro.c** - Sistema de cadastro
- **exercicioContaVogaisConsoante.c** - Contagem de vogais e consoantes
- **exercicioSomaMultiplo.c** - Operações matemáticas com laços
- **exerciciosSimples.c** - Exercícios diversos

Consulte o README dentro do diretório de exercícios para mais detalhes.

## ⚠️ Cuidados com Ponteiros

1. **Sempre inicialize ponteiros** antes de usá-los
2. **Não acesse memória não alocada**
3. **Cuidado com ponteiros pendentes (dangling pointers)**
4. **Libere memória alocada dinamicamente** com `free()`

## 🔗 Próximos Passos

Após dominar os conceitos desta aula, você estará preparado para:
- Trabalhar com estruturas de dados mais complexas
- Entender alocação dinâmica de memória
- Implementar algoritmos com eficiência

## 📚 Recursos Adicionais

- [C Pointer Tutorial](https://en.cppreference.com/w/c/language/pointer)
- [C String Functions](https://en.cppreference.com/w/c/string/byte)
- [Control Flow Structures](https://en.cppreference.com/w/c/language/statements)

---

**Repositório**: https://github.com/profluiscaparroz/estrutura-dados-c
