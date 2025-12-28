# Aula 01 - Fundamentos da Linguagem C

## 📋 Visão Geral

Esta aula apresenta os fundamentos essenciais da linguagem C, incluindo conceitos básicos de sintaxe, tipos de dados, variáveis, constantes, estruturas e escopo.

## 📚 Conteúdo da Aula

### Exemplos Incluídos

1. **00_exemplo_encontra_raiz.c** - Exemplo de operações matemáticas e funções
2. **01_introducao_variaveis.c** - Introdução a variáveis, tipos de dados e declarações
3. **02_introducao_conversao_tipos.c** - Conversão de tipos (type casting)
4. **03_exemplo_struct.c** - Estruturas (structs) em C
5. **04_exemplo_constantes.c** - Uso de constantes e macros
6. **05_exemplo_booleano.c** - Tipos booleanos em C
7. **06_variaives_estaticas.c** - Variáveis estáticas e seu comportamento (nota: nome do arquivo contém erro de digitação)
8. **07_exemplo_escopo.c** - Escopo de variáveis (local, global, estático)

## 🎯 Objetivos de Aprendizado

Ao concluir esta aula, você será capaz de:

- ✅ Declarar e inicializar variáveis em C
- ✅ Entender os diferentes tipos de dados primitivos
- ✅ Utilizar constantes e macros
- ✅ Criar e manipular estruturas (structs)
- ✅ Compreender conversão de tipos
- ✅ Entender escopo de variáveis
- ✅ Trabalhar com variáveis estáticas

## 🔧 Compilação e Execução

Para compilar qualquer exemplo:

```bash
gcc -Wall -Wextra -std=c99 -o programa nome_do_arquivo.c
./programa
```

Exemplo:
```bash
gcc -Wall -Wextra -std=c99 -o variaveis 01_introducao_variaveis.c
./variaveis
```

## 📖 Conceitos-Chave

### Tipos de Dados Primitivos
- `int` - Números inteiros
- `float` - Números de ponto flutuante (precisão simples)
- `double` - Números de ponto flutuante (precisão dupla)
- `char` - Caracteres
- `bool` - Valores booleanos (requer `<stdbool.h>`)

### Modificadores
- `unsigned` - Apenas valores positivos
- `signed` - Valores positivos e negativos (padrão)
- `long` - Maior alcance de valores
- `short` - Menor alcance de valores

### Constantes
```c
const double PI = 3.14159;  // Constante em tempo de execução
#define MAX_SIZE 100        // Macro (constante em tempo de compilação)
```

### Estruturas (Structs)
```c
typedef struct {
    char nome[50];
    int idade;
} Pessoa;
```

### Escopo de Variáveis
- **Global** - Visível em todo o programa
- **Local** - Visível apenas dentro da função
- **Estática** - Mantém valor entre chamadas de função

## 📝 Exercícios

O diretório `exercicio/` contém exercícios práticos para fixação dos conceitos apresentados. Consulte o README dentro do diretório de exercícios para mais detalhes.

## 🔗 Próximos Passos

Após dominar os conceitos desta aula, prossiga para:
- **aula02** - Controle de fluxo e estruturas de repetição

## 📚 Recursos Adicionais

- [Documentação C Standard Library](https://en.cppreference.com/w/c)
- [GCC Compiler Documentation](https://gcc.gnu.org/onlinedocs/)

---

**Repositório**: https://github.com/profluiscaparroz/estrutura-dados-c
