# Exemplos de Pilhas em C

Este diretório contém exemplos progressivos sobre implementação e uso de pilhas (stacks) em C, incluindo demonstrações de erros comuns e boas práticas.

## 📚 Índice de Exemplos

### Exemplos Básicos

1. **exemploPilhas.c** - Implementação básica de pilha usando array estático
   - Estrutura de pilha com tamanho fixo
   - Operações básicas: empilhar, desempilhar, verificar estado
   - Exemplo simples de uso

2. **exemploPilhasAlocacaoDinamica.c** - Pilha com alocação dinâmica
   - Implementação usando lista encadeada
   - Alocação de nós com malloc/free
   - Sem limite de tamanho pré-definido

3. **exemploPilhasGenericas.c** - Pilha genérica com void*
   - Suporte a qualquer tipo de dado
   - Uso de ponteiros genéricos
   - Exemplo de flexibilidade em C

### 🔴 Exemplos de Erros e Problemas Comuns

> **IMPORTANTE**: Estes exemplos demonstram erros propositalmente para fins educacionais. Eles mostram o que NÃO fazer e como tratar erros corretamente.

4. **exemploErrosEstouro.c** ⚠️ - Stack Overflow e Underflow
   - **Demonstra:**
     - Stack Overflow: Tentar empilhar em pilha cheia
     - Stack Underflow: Tentar desempilhar de pilha vazia
     - Acesso inválido ao topo de pilha vazia
     - Loops sem verificação de limites
   - **Ensina:**
     - Importância de verificar estado da pilha antes de operações
     - Como implementar tratamento de erros com valores de retorno
     - Boas práticas para evitar esses erros

5. **exemploErrosMemoria.c** 💾 - Erros de Gerenciamento de Memória
   - **Demonstra:**
     - Memory Leak (vazamento de memória)
     - Falha de alocação (malloc retorna NULL)
     - Double Free (liberar memória duas vezes)
     - Use-After-Free (usar memória após liberar)
     - NULL Pointer Dereference
   - **Ensina:**
     - Como verificar retorno de malloc()
     - Importância de liberar memória alocada
     - Definir ponteiros como NULL após free()
     - Uso de valgrind para detectar leaks

6. **exemploErrosRecursao.c** 🔄 - Stack Overflow em Algoritmos Recursivos
   - **Demonstra:**
     - Recursão infinita (sem caso base)
     - Recursão muito profunda (Fibonacci ingênuo)
     - Árvores binárias degeneradas
     - Backtracking (N-Queens)
     - Comparação: recursão vs iteração com pilha explícita
   - **Ensina:**
     - Problemas de stack overflow em algoritmos avançados
     - Quando usar recursão vs iteração
     - Como converter recursão em iteração
     - Técnicas para evitar estouro de pilha

## 🚀 Como Compilar e Executar

### Compilar um exemplo individual:
```bash
gcc -Wall -Wextra -o programa nomeDoArquivo.c
./programa
```

### Exemplos específicos:

```bash
# Exemplo básico de pilha
gcc -Wall -Wextra -o exemploPilhas exemploPilhas.c
./exemploPilhas

# Exemplos de erros
gcc -Wall -Wextra -o exemploErrosEstouro exemploErrosEstouro.c
./exemploErrosEstouro

gcc -Wall -Wextra -o exemploErrosMemoria exemploErrosMemoria.c
./exemploErrosMemoria

gcc -Wall -Wextra -o exemploErrosRecursao exemploErrosRecursao.c -lm
./exemploErrosRecursao
```

### Usando o script de compilação do repositório:
```bash
cd /caminho/para/repositorio
./compile_all.sh
```

## 🔍 Detecção de Erros com Valgrind

Para detectar memory leaks e outros problemas de memória, use o valgrind:

```bash
# Instalar valgrind (se necessário)
sudo apt-get install valgrind  # Ubuntu/Debian
sudo yum install valgrind      # CentOS/RHEL

# Executar com valgrind
gcc -g -o exemploErrosMemoria exemploErrosMemoria.c
valgrind --leak-check=full --show-leak-kinds=all ./exemploErrosMemoria
```

## 📖 Conceitos Importantes

### O que é uma Pilha?
Uma pilha (stack) é uma estrutura de dados linear que segue o princípio **LIFO** (Last-In, First-Out):
- O último elemento inserido é o primeiro a ser removido
- Analogia: Pilha de pratos - você adiciona e remove do topo

### Operações Básicas
- **push()** - Empilhar: Adiciona elemento no topo
- **pop()** - Desempilhar: Remove elemento do topo
- **peek()/top()** - Ver o topo sem remover
- **isEmpty()** - Verifica se pilha está vazia
- **isFull()** - Verifica se pilha está cheia (array fixo)

### Complexidade de Tempo
- Push: O(1)
- Pop: O(1)
- Peek: O(1)
- isEmpty: O(1)

## ⚠️ Erros Comuns e Como Evitá-los

### 1. Stack Overflow
**Problema:** Tentar empilhar em pilha cheia
```c
// ERRADO - Não verifica se está cheia
empilhar(&pilha, valor);

// CORRETO - Verifica antes
if (!estaCheia(&pilha)) {
    empilhar(&pilha, valor);
} else {
    printf("Erro: Pilha cheia!\n");
}
```

### 2. Stack Underflow
**Problema:** Tentar desempilhar de pilha vazia
```c
// ERRADO - Não verifica se está vazia
int valor = desempilhar(&pilha);

// CORRETO - Verifica antes
if (!estaVazia(&pilha)) {
    int valor = desempilhar(&pilha);
} else {
    printf("Erro: Pilha vazia!\n");
}
```

### 3. Memory Leak
**Problema:** Não liberar memória alocada
```c
// ERRADO - Esquece de liberar
Node* node = desempilhar(&pilha);
// ... usa node ...
// Esqueceu: free(node);

// CORRETO - Sempre liberar
Node* node = desempilhar(&pilha);
// ... usa node ...
free(node);  // Libera memória
```

### 4. Recursão Profunda
**Problema:** Recursão pode causar stack overflow
```c
// ARRISCADO - Recursão profunda
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n-1) + fibonacci(n-2);  // Exponencial!
}

// MELHOR - Iterativo
int fibonacci(int n) {
    if (n <= 1) return n;
    int a = 0, b = 1, temp;
    for (int i = 2; i <= n; i++) {
        temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}
```

## 💡 Boas Práticas

1. **Sempre verificar retornos de funções**
   - malloc() pode retornar NULL
   - Operações de pilha podem falhar

2. **Usar tipos de retorno booleanos para indicar sucesso/falha**
   ```c
   bool empilhar(Pilha* p, int valor) {
       if (estaCheia(p)) return false;
       // ... empilhar ...
       return true;
   }
   ```

3. **Implementar funções de limpeza**
   ```c
   void limparPilha(Pilha* p) {
       while (!estaVazia(p)) {
           desempilhar(p);
       }
   }
   ```

4. **Definir ponteiros como NULL após free()**
   ```c
   free(ptr);
   ptr = NULL;  // Evita dangling pointer
   ```

5. **Usar pilha dinâmica quando tamanho é imprevisível**
   - Array fixo: Quando tamanho máximo é conhecido
   - Lista encadeada: Quando tamanho varia muito

## 🔧 Ferramentas Úteis

### Para Debugging
- **gdb** - GNU Debugger
- **valgrind** - Detector de memory leaks
- **AddressSanitizer** - Detector de erros de memória em tempo de compilação

### Para Análise de Performance
- **perf** - Profiler de performance do Linux
- **gprof** - GNU Profiler
- **Compiler Explorer (godbolt.org)** - Ver código assembly gerado

## 📚 Aplicações de Pilhas

1. **Avaliação de expressões matemáticas**
   - Conversão infixa para pós-fixa
   - Calculadoras

2. **Gerenciamento de chamadas de função**
   - Call stack do sistema
   - Recursão

3. **Desfazer/Refazer (Undo/Redo)**
   - Editores de texto
   - Navegadores (histórico)

4. **Parsing de código**
   - Compiladores
   - Verificação de parênteses balanceados

5. **Backtracking**
   - Resolução de labirintos
   - Quebra-cabeças (Sudoku, N-Queens)

6. **Navegação em estruturas**
   - Travessia de árvores (DFS)
   - Travessia de grafos

## 🎓 Recursos Adicionais

- **Livro**: "The C Programming Language" - Kernighan & Ritchie
- **Online**: [GeeksforGeeks - Stack Data Structure](https://www.geeksforgeeks.org/stack-data-structure/)
- **Visualização**: [VisuAlgo - Stack Visualization](https://visualgo.net/en/list)
- **Prática**: [LeetCode - Stack Problems](https://leetcode.com/tag/stack/)

## 🤝 Contribuindo

Se você encontrou um bug ou tem sugestões para novos exemplos:
1. Abra uma issue no repositório
2. Descreva o problema ou sugestão claramente
3. Se possível, forneça exemplos de código

## 📝 Licença

Este material é parte do repositório de Estrutura de Dados em C e segue a mesma licença do repositório principal.

---

**Autor**: Prof. Luis Caparroz  
**Disciplina**: Estrutura de Dados  
**Última atualização**: Novembro 2024
