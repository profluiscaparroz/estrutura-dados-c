# Exemplos de Vetores

## 📋 Visão Geral

Este diretório contém exemplos didáticos e progressivos sobre o uso de vetores (arrays) em C, desde conceitos básicos até técnicas avançadas.

## 📚 Exemplos Incluídos

### 1. exemploSimples.c
Introdução básica a vetores com exemplos simples.

**Conceitos:**
- Declaração de vetores
- Inicialização
- Acesso a elementos
- Impressão de vetores

### 2. exemploAlocacaoDinamica.c
Demonstração de alocação dinâmica de memória para vetores.

**Conceitos:**
- `malloc()` e `free()`
- Verificação de erros de alocação
- Gerenciamento de memória
- Vetores de tamanho variável

### 3. exemploVetorManipulacao.c
Operações de manipulação de elementos em vetores.

**Conceitos:**
- Modificação de elementos
- Iteração sobre vetores
- Operações matemáticas
- Cálculos agregados (soma, média)

### 4. exemploPassagemPorParametro.c
Como passar vetores para funções.

**Conceitos:**
- Passagem de arrays como argumentos
- Modificação por referência
- Passagem do tamanho do vetor
- Funções que retornam vetores

### 5. exemploStringVetores.c
Strings como vetores de caracteres.

**Conceitos:**
- Strings são arrays de `char`
- Terminador nulo `\0`
- Funções de string (`strlen`, `strcpy`, `strcmp`)
- Manipulação de caracteres

### 6. exemploAvancado.c
Técnicas avançadas com vetores.

**Conceitos:**
- Vetores multidimensionais
- Ponteiros e vetores
- Aritmética de ponteiros
- Otimizações

## 🔧 Compilação

Para compilar qualquer exemplo:

```bash
gcc -Wall -Wextra -std=c99 -o exemplo exemploSimples.c
./exemplo
```

Para compilar todos:

```bash
gcc -Wall -Wextra -std=c99 -o simples exemploSimples.c
gcc -Wall -Wextra -std=c99 -o dinamico exemploAlocacaoDinamica.c
gcc -Wall -Wextra -std=c99 -o manipulacao exemploVetorManipulacao.c
gcc -Wall -Wextra -std=c99 -o parametro exemploPassagemPorParametro.c
gcc -Wall -Wextra -std=c99 -o string exemploStringVetores.c
gcc -Wall -Wextra -std=c99 -o avancado exemploAvancado.c
```

## 📖 Conceitos Fundamentais

### Declaração e Inicialização

```c
// Básico
int numeros[5];

// Com inicialização
int numeros[5] = {1, 2, 3, 4, 5};

// Tamanho inferido
int numeros[] = {10, 20, 30};

// Alocação dinâmica
int *numeros = (int*)malloc(tamanho * sizeof(int));
```

### Acesso a Elementos

```c
// Leitura
int valor = vetor[indice];

// Escrita
vetor[indice] = novo_valor;

// Via ponteiro
int valor = *(vetor + indice);
```

### Passagem para Funções

```c
void processar(int vetor[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        // processar vetor[i]
    }
}

// Chamada
processar(meu_vetor, 10);
```

## 💡 Padrões Comuns

### Preenchimento

```c
for (int i = 0; i < tamanho; i++) {
    vetor[i] = valor_inicial;
}
```

### Soma de Elementos

```c
int soma = 0;
for (int i = 0; i < tamanho; i++) {
    soma += vetor[i];
}
```

### Busca de Máximo

```c
int maximo = vetor[0];
for (int i = 1; i < tamanho; i++) {
    if (vetor[i] > maximo) {
        maximo = vetor[i];
    }
}
```

### Cópia de Vetores

```c
for (int i = 0; i < tamanho; i++) {
    destino[i] = origem[i];
}

// Ou usando memcpy
memcpy(destino, origem, tamanho * sizeof(int));
```

## ⚠️ Erros Comuns

### 1. Acesso Fora dos Limites

```c
int vetor[5];
vetor[5] = 10;  // ERRO! Índices válidos: 0 a 4
```

### 2. Não Liberar Memória

```c
int *vetor = (int*)malloc(10 * sizeof(int));
// ... usar vetor ...
// ERRO: esqueceu de chamar free(vetor);
```

### 3. Usar Vetor Não Inicializado

```c
int vetor[5];
printf("%d\n", vetor[0]);  // CUIDADO! Valor indefinido
```

### 4. Passar Tamanho Errado

```c
void funcao(int vetor[], int tamanho);

int v[5];
funcao(v, 10);  // ERRO! Tamanho incorreto
```

## 🎯 Objetivos de Aprendizado

Após estudar estes exemplos, você deve ser capaz de:

- ✅ Declarar e inicializar vetores
- ✅ Acessar e modificar elementos
- ✅ Usar alocação dinâmica corretamente
- ✅ Passar vetores para funções
- ✅ Trabalhar com strings
- ✅ Evitar erros comuns
- ✅ Gerenciar memória adequadamente

## 🚀 Ordem Recomendada de Estudo

1. **exemploSimples.c** - Comece aqui
2. **exemploVetorManipulacao.c** - Operações básicas
3. **exemploPassagemPorParametro.c** - Funções
4. **exemploAlocacaoDinamica.c** - Memória dinâmica
5. **exemploStringVetores.c** - Strings
6. **exemploAvancado.c** - Técnicas avançadas

## 📚 Recursos Adicionais

- [C Arrays](https://en.cppreference.com/w/c/language/array)
- [Dynamic Memory](https://en.cppreference.com/w/c/memory)
- [C Strings](https://en.cppreference.com/w/c/string/byte)

## 🔗 Próximos Passos

Após dominar estes exemplos:
- Pratique com os exercícios no diretório **exercicios/**
- Estude as operações avançadas no diretório **operacoes/**

---

**Repositório**: https://github.com/profluiscaparroz/estrutura-dados-c
