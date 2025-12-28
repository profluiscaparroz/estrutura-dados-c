# Exercícios de Vetores

## 📋 Visão Geral

Este diretório contém exercícios práticos para consolidar o conhecimento sobre vetores (arrays) em C. Os exercícios cobrem desde operações básicas até manipulações mais complexas.

## 📚 Exercícios Disponíveis

### Exercício 1 - `exercicio1.c` e `exercicio1_vetor.c`
Operações fundamentais com vetores.

**Objetivos:**
- Declaração e inicialização
- Leitura de dados do usuário
- Operações básicas de manipulação
- Exibição de resultados

### Exercício 2 - `exercicio2.c` e `exercicio2_vetor.c`
Operações intermediárias com vetores.

**Objetivos:**
- Busca de elementos
- Cálculos estatísticos (média, mínimo, máximo)
- Manipulação de dados
- Validação de entrada

### Exercício 3 - `exercicio3_vetor.c`
Algoritmos de manipulação de vetores.

**Objetivos:**
- Ordenação de elementos
- Remoção de duplicatas
- Inversão de vetores
- Operações avançadas

### Exercício 4 - `exercicio4_vetor.c`
Operações matemáticas com vetores.

**Objetivos:**
- Operações aritméticas
- Produto escalar
- Soma de vetores
- Normalização

### Exercício 5 - `exercicio5_vetor.c`
Desafios e problemas complexos.

**Objetivos:**
- Resolução de problemas práticos
- Combinação de conceitos
- Otimização de algoritmos
- Análise de complexidade

## 🔧 Compilação e Execução

### Compilar Individual

```bash
gcc -Wall -Wextra -std=c99 -o ex1 exercicio1_vetor.c
./ex1
```

### Compilar Todos

```bash
for i in 1 2 3 4 5; do
    gcc -Wall -Wextra -std=c99 -o ex$i exercicio${i}_vetor.c
done
```

### Executar Sequencialmente

```bash
./ex1
./ex2
./ex3
./ex4
./ex5
```

## ✅ Checklist de Habilidades

Antes de considerar os exercícios completos, você deve ser capaz de:

### Básico
- [ ] Declarar vetores de diferentes tipos
- [ ] Inicializar vetores com valores
- [ ] Acessar e modificar elementos
- [ ] Percorrer vetores com laços
- [ ] Imprimir conteúdo de vetores

### Intermediário
- [ ] Implementar busca linear
- [ ] Calcular soma, média, mínimo e máximo
- [ ] Copiar vetores
- [ ] Comparar vetores
- [ ] Inverter ordem dos elementos

### Avançado
- [ ] Implementar algoritmos de ordenação
- [ ] Remover duplicatas
- [ ] Mesclar vetores ordenados
- [ ] Implementar busca binária
- [ ] Trabalhar com alocação dinâmica

## 📖 Conceitos Cobertos

### Operações Básicas

```c
// Leitura de vetor
for (int i = 0; i < tamanho; i++) {
    printf("Digite o elemento %d: ", i + 1);
    scanf("%d", &vetor[i]);
}

// Impressão de vetor
for (int i = 0; i < tamanho; i++) {
    printf("%d ", vetor[i]);
}
printf("\n");
```

### Busca Linear

```c
int buscar(int vetor[], int tamanho, int chave) {
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i] == chave) {
            return i;
        }
    }
    return -1;
}
```

### Cálculo de Média

```c
float calcular_media(int vetor[], int tamanho) {
    int soma = 0;
    for (int i = 0; i < tamanho; i++) {
        soma += vetor[i];
    }
    return (float)soma / tamanho;
}
```

### Encontrar Máximo

```c
int encontrar_maximo(int vetor[], int tamanho) {
    int max = vetor[0];
    for (int i = 1; i < tamanho; i++) {
        if (vetor[i] > max) {
            max = vetor[i];
        }
    }
    return max;
}
```

### Inverter Vetor

```c
void inverter(int vetor[], int tamanho) {
    for (int i = 0; i < tamanho / 2; i++) {
        int temp = vetor[i];
        vetor[i] = vetor[tamanho - 1 - i];
        vetor[tamanho - 1 - i] = temp;
    }
}
```

## 🐛 Problemas Comuns e Soluções

### Problema 1: Estouro de Buffer
```c
// ERRADO
int vetor[5];
for (int i = 0; i <= 5; i++) {  // i vai de 0 a 5 (6 iterações)
    vetor[i] = i;
}

// CORRETO
for (int i = 0; i < 5; i++) {  // i vai de 0 a 4 (5 iterações)
    vetor[i] = i;
}
```

### Problema 2: Leitura com scanf
```c
// CUIDADO com buffer de entrada
int valor;
scanf("%d", &valor);
getchar();  // Limpar '\n' do buffer
```

### Problema 3: Comparação de Vetores
```c
// ERRADO
if (vetor1 == vetor2)  // Compara ponteiros, não conteúdo

// CORRETO
int iguais = 1;
for (int i = 0; i < tamanho; i++) {
    if (vetor1[i] != vetor2[i]) {
        iguais = 0;
        break;
    }
}
```

## 💡 Dicas para Resolução

1. **Leia o enunciado cuidadosamente** - Entenda o que é pedido antes de programar
2. **Planeje antes de codificar** - Esboce o algoritmo no papel
3. **Teste com casos simples** - Use vetores pequenos para testar
4. **Verifique limites** - Sempre valide índices de acesso
5. **Use nomes descritivos** - Variáveis com nomes claros facilitam debug
6. **Compile com warnings** - Use `-Wall -Wextra` para detectar problemas

## 🚀 Desafios Adicionais

Após completar os exercícios básicos, tente:

1. **Rotação de Vetor**: Rotacionar elementos k posições
2. **Segundo Maior**: Encontrar o segundo maior elemento
3. **Interseção**: Encontrar elementos comuns entre dois vetores
4. **Partição**: Separar elementos pares e ímpares
5. **Histograma**: Contar frequência de cada elemento

## 📊 Complexidade Esperada

| Operação | Complexidade |
|----------|-------------|
| Acesso | O(1) |
| Busca Linear | O(n) |
| Inserção | O(n) |
| Remoção | O(n) |
| Inversão | O(n) |
| Ordenação (simples) | O(n²) |

## 🔗 Recursos

- Revise os exemplos no diretório **exemplo/**
- Consulte as operações no diretório **operacoes/**
- [Algoritmos de Busca](https://en.wikipedia.org/wiki/Search_algorithm)
- [Algoritmos de Ordenação](https://en.wikipedia.org/wiki/Sorting_algorithm)

---

**Repositório**: https://github.com/profluiscaparroz/estrutura-dados-c
