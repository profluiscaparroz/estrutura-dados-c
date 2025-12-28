# Exercícios - Aula 01

## 📋 Visão Geral

Este diretório contém exercícios práticos para fixação dos conceitos apresentados na Aula 01 sobre fundamentos da linguagem C.

## 📚 Exercícios Disponíveis

### Exercício 1 - `exercicio1.c`
Criação e manipulação de estruturas (structs) para representar dados de pessoas.

**Conceitos trabalhados:**
- Declaração de estruturas
- Uso de `typedef`
- Manipulação de strings com `strcpy`
- Formatação de saída com `printf`

**Objetivo:** Criar uma estrutura `Pessoa` com diversos campos (nome, idade, CPF, altura, etc.) e manipular seus dados.

### Exercício 2 - `exercicio2.c`
Trabalho com tipos de dados e operações básicas.

**Conceitos trabalhados:**
- Tipos de dados primitivos
- Operações aritméticas
- Entrada e saída de dados

### Exercício 3 - `exercicio3.c`
Prática adicional com conceitos fundamentais.

**Conceitos trabalhados:**
- Combinação de conceitos da aula
- Resolução de problemas práticos

## 🔧 Como Compilar e Executar

Para compilar qualquer exercício:

```bash
gcc -Wall -Wextra -std=c99 -o exercicio1 exercicio1.c
./exercicio1
```

Ou compile todos de uma vez:

```bash
gcc -Wall -Wextra -std=c99 -o ex1 exercicio1.c
gcc -Wall -Wextra -std=c99 -o ex2 exercicio2.c
gcc -Wall -Wextra -std=c99 -o ex3 exercicio3.c
```

## ✅ Checklist de Aprendizado

Antes de prosseguir, certifique-se de que você consegue:

- [ ] Declarar estruturas com `typedef`
- [ ] Inicializar e manipular variáveis de estruturas
- [ ] Usar funções de string como `strcpy`
- [ ] Formatar saída com `printf` usando diferentes especificadores (%s, %d, %f)
- [ ] Compreender os tipos de dados apropriados para cada campo

## 📖 Dicas

1. **Strings em C**: São arrays de caracteres terminados com `\0`
2. **strcpy**: Use para copiar strings, não o operador `=`
3. **Especificadores de formato**:
   - `%s` - string
   - `%d` - inteiro
   - `%f` - float
   - `%.2f` - float com 2 casas decimais
4. **Tipos unsigned**: Use quando os valores nunca serão negativos (ex: idade)

## 🐛 Problemas Comuns

### Erro de Compilação: "incompatible types"
**Solução**: Verifique se está usando `strcpy` para strings, não atribuição direta.

### Warning: "format specifies type X but argument has type Y"
**Solução**: Use o especificador correto no printf (veja as dicas acima).

### Saída incorreta de strings
**Solução**: Certifique-se de que declarou arrays de caracteres com tamanho suficiente.

## 🚀 Desafios Adicionais

Após completar os exercícios, tente:

1. Criar um array de estruturas `Pessoa` com múltiplas pessoas
2. Implementar uma função para imprimir os dados de uma pessoa
3. Adicionar validação de dados (ex: idade não pode ser negativa)
4. Criar uma função para comparar duas pessoas

## 🔗 Recursos

- Revise os exemplos na pasta principal da aula01
- Consulte a documentação da linguagem C para funções de string
- [C String Functions](https://en.cppreference.com/w/c/string/byte)

---

**Repositório**: https://github.com/profluiscaparroz/estrutura-dados-c
