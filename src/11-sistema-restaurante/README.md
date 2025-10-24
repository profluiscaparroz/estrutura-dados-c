# Sistema de Gerenciamento de Pedidos de Restaurante

## 📚 Visão Geral do Projeto

Este é um **projeto didático completo** que demonstra a aplicação prática de estruturas de dados fundamentais em um cenário real: um sistema de gerenciamento de pedidos para restaurante.

### 🎯 Objetivo Didático

Ensinar aos alunos como as estruturas de dados estudadas em sala de aula são aplicadas em problemas reais, mostrando:
- **Quando** usar cada estrutura
- **Por que** determinada escolha é melhor
- **Como** implementar corretamente
- **Qual** a complexidade computacional de cada operação

---

## 🏗️ Estruturas de Dados Implementadas

### 1. **Vetores (Arrays)** 📊
- **Uso**: Armazenar menu de itens e lista de pedidos
- **Vantagem**: Acesso direto O(1) por índice
- **Aplicação**: Menu do restaurante com 50 itens
```c
ItemMenu menu[MAX_MENU];        // Menu do restaurante
Pedido pedidos[MAX_PEDIDOS];    // Todos os pedidos
```

### 2. **Busca Binária** 🔍
- **Uso**: Buscar item do menu por código
- **Complexidade**: O(log n)
- **Pré-requisito**: Array ordenado por código
- **Aplicação**: Localizar rapidamente um prato pelo código
```c
ItemMenu* buscarItemPorCodigo(int codigo);  // O(log n)
```

### 3. **Busca Linear** 🔎
- **Uso**: Buscar item do menu por nome
- **Complexidade**: O(n)
- **Aplicação**: Buscar "Feijoada" no menu
```c
ItemMenu* buscarItemPorNome(char* nome);    // O(n)
```

### 4. **Quick Sort** ⚡
- **Uso**: Ordenar pedidos por prioridade, tempo ou valor
- **Complexidade**: O(n log n) médio
- **Aplicação**: Organizar pedidos urgentes primeiro
```c
void ordenarPedidosPorPrioridade(Pedido arr[], int n);  // O(n log n)
```

### 5. **Fila (Queue - FIFO)** 🔄
- **Princípio**: First In, First Out (Primeiro a entrar, primeiro a sair)
- **Uso**: Gerenciar pedidos na cozinha
- **Complexidade**: O(1) para enfileirar e desenfileirar
- **Aplicação**: Pedidos são processados na ordem de chegada
```c
void enfileirar(FilaPedidos* fila, Pedido pedido);     // O(1)
Pedido desenfileirar(FilaPedidos* fila);               // O(1)
```

**Analogia**: Como uma fila de banco - quem chega primeiro é atendido primeiro!

### 6. **Pilha (Stack - LIFO)** 📚
- **Princípio**: Last In, First Out (Último a entrar, primeiro a sair)
- **Uso**: Histórico de ações para implementar UNDO
- **Complexidade**: O(1) para empilhar e desempilhar
- **Aplicação**: Desfazer a última ação realizada
```c
void empilharAcao(PilhaHistorico* pilha, Acao acao);   // O(1)
Acao desempilharAcao(PilhaHistorico* pilha);           // O(1)
```

**Analogia**: Como uma pilha de pratos - você sempre pega e coloca no topo!

---

## 🎓 Conceitos Importantes

### Por que Fila para Pedidos?

**Problema**: Vários pedidos chegam ao mesmo tempo. Como decidir qual preparar primeiro?

**Solução**: FILA (FIFO)
- ✅ Garante justiça: ordem de chegada é respeitada
- ✅ Evita que pedidos antigos sejam esquecidos
- ✅ Cliente sabe que será atendido na ordem

**Exemplo Prático**:
```
Mesa 5 faz pedido às 12:00 → Enfileira
Mesa 3 faz pedido às 12:05 → Enfileira
Mesa 8 faz pedido às 12:10 → Enfileira

Cozinha processa:
1º → Mesa 5 (12:00) ← Desenfileira
2º → Mesa 3 (12:05) ← Desenfileira
3º → Mesa 8 (12:10) ← Desenfileira
```

### Por que Pilha para Histórico?

**Problema**: Cliente quer cancelar item que acabou de adicionar. Como reverter?

**Solução**: PILHA (LIFO)
- ✅ Última ação é mais fácil de desfazer
- ✅ Mantém ordem cronológica reversa
- ✅ Implementação simples e eficiente

**Exemplo Prático**:
```
Ações empilhadas (ordem cronológica):
[Fundo]  Ação 1: Criou pedido
         Ação 2: Adicionou item A
         Ação 3: Adicionou item B
[Topo]   Ação 4: Adicionou item C

Desfazer (UNDO):
1º UNDO → Remove Ação 4 (item C)
2º UNDO → Remove Ação 3 (item B)
3º UNDO → Remove Ação 2 (item A)
```

### Por que Busca Binária é Mais Rápida?

**Comparação Prática**:

Menu com 1000 itens:
- **Busca Linear**: Pode precisar verificar TODOS os 1000 itens → 1000 comparações
- **Busca Binária**: Máximo de 10 comparações! (log₂(1000) ≈ 10)

**Como funciona**:
```
Buscar código 305 em menu ordenado [101, 102, ..., 305, ..., 999]:

Iteração 1: Verifica meio → 500 | 305 < 500, busca metade esquerda
Iteração 2: Verifica meio → 250 | 305 > 250, busca metade direita
Iteração 3: Verifica meio → 375 | 305 < 375, busca metade esquerda
Iteração 4: Verifica meio → 312 | 305 < 312, busca metade esquerda
Iteração 5: Verifica meio → 305 | ✓ Encontrou!

Total: 5 comparações ao invés de potencialmente 305!
```

---

## 🚀 Como Compilar e Executar

### Compilação Manual

```bash
gcc sistema_restaurante.c -o restaurante
./restaurante
```

### Usando o Makefile (se disponível)

```bash
make
./restaurante
```

---

## 📖 Fluxo de Uso do Sistema

### 1. Menu Principal
```
╔════════════════════════════════════════════════════════════════════╗
║     SISTEMA DE GERENCIAMENTO DE PEDIDOS - RESTAURANTE             ║
║                    Sabor da Casa                                   ║
╚════════════════════════════════════════════════════════════════════╝

  DEMONSTRAÇÃO DE ESTRUTURAS DE DADOS:
  • Vetores       → Menu e lista de pedidos
  • Busca Binária → Buscar item por código O(log n)
  • Busca Linear  → Buscar item por nome O(n)
  • Quick Sort    → Ordenar pedidos O(n log n)
  • Fila (FIFO)   → Gerenciar pedidos da cozinha
  • Pilha (LIFO)  → Histórico de ações (undo)

────────────────────────────────────────────────────────────────────

1 - Ver menu do restaurante
2 - Criar novo pedido
3 - Gerenciar fila da cozinha (FIFO)
4 - Ordenar pedidos (Quick Sort)
5 - Buscar item no menu
6 - Ver histórico de ações (Stack)
0 - Sair
```

### 2. Criar Pedido
1. Escolha a opção `2 - Criar novo pedido`
2. Informe o número da mesa
3. Adicione itens usando códigos do menu
4. Defina quantidade e observações
5. Escolha a prioridade (1=baixa, 2=normal, 3=alta, 4=urgente)
6. Pedido é automaticamente adicionado à fila da cozinha

**Estruturas usadas**:
- ✅ **Vetor**: Armazenar itens do pedido
- ✅ **Busca Binária**: Localizar item por código
- ✅ **Fila**: Enfileirar pedido
- ✅ **Pilha**: Registrar ação no histórico

### 3. Gerenciar Fila da Cozinha
1. Escolha a opção `3 - Gerenciar fila da cozinha`
2. Ver todos os pedidos na fila (ordem FIFO)
3. Processar próximo pedido (desenfileirar)
4. Ver qual será o próximo sem remover

**Estruturas usadas**:
- ✅ **Fila (FIFO)**: Gerenciar ordem de processamento
- ✅ **Pilha**: Registrar processamento no histórico

### 4. Ordenar Pedidos
1. Escolha a opção `4 - Ordenar pedidos`
2. Sistema usa **Quick Sort** para ordenar por prioridade
3. Pedidos urgentes aparecem primeiro

**Estruturas usadas**:
- ✅ **Quick Sort**: O(n log n) para ordenação eficiente
- ✅ **Vetor**: Base para ordenação

### 5. Buscar Item
1. Escolha a opção `5 - Buscar item no menu`
2. Opção 1: Buscar por código (Busca Binária - O(log n))
3. Opção 2: Buscar por nome (Busca Linear - O(n))

**Estruturas usadas**:
- ✅ **Busca Binária** ou **Busca Linear**
- ✅ **Vetor**: Menu de itens

### 6. Histórico (UNDO)
1. Escolha a opção `6 - Ver histórico de ações`
2. Ver todas as ações registradas (do topo para baixo)
3. Desfazer última ação (desempilhar)

**Estruturas usadas**:
- ✅ **Pilha (LIFO)**: Histórico de ações

---

## 📊 Análise de Complexidade

| Operação | Estrutura | Melhor Caso | Caso Médio | Pior Caso | Espaço |
|----------|-----------|-------------|------------|-----------|---------|
| Buscar item por código | Busca Binária | O(1) | O(log n) | O(log n) | O(1) |
| Buscar item por nome | Busca Linear | O(1) | O(n) | O(n) | O(1) |
| Ordenar pedidos | Quick Sort | O(n log n) | O(n log n) | O(n²)* | O(log n) |
| Enfileirar pedido | Fila | O(1) | O(1) | O(1) | O(1) |
| Desenfileirar pedido | Fila | O(1) | O(1) | O(1) | O(1) |
| Empilhar ação | Pilha | O(1) | O(1) | O(1) | O(1) |
| Desempilhar ação | Pilha | O(1) | O(1) | O(1) | O(1) |
| Acessar item por índice | Vetor | O(1) | O(1) | O(1) | O(1) |

\* O pior caso O(n²) do Quick Sort é raro com boa escolha de pivô (usamos qsort da stdlib que é otimizado)

---

## 🧪 Casos de Teste

### Teste 1: Criar Pedido Simples
```
1. Criar pedido para mesa 5
2. Adicionar: 1x Feijoada (código 101)
3. Adicionar: 1x Refrigerante (código 301)
4. Prioridade: Normal (2)
5. Verificar: Pedido aparece na fila da cozinha
```

**Resultado Esperado**:
- ✅ Pedido criado com sucesso
- ✅ Valor total calculado corretamente (R$ 51.90)
- ✅ Pedido enfileirado
- ✅ Ações registradas no histórico

### Teste 2: Processar Fila (FIFO)
```
1. Criar 3 pedidos (mesas 1, 2, 3)
2. Verificar ordem na fila: [Mesa 1] → [Mesa 2] → [Mesa 3]
3. Processar próximo pedido
4. Verificar: Mesa 1 foi processada
5. Fila agora: [Mesa 2] → [Mesa 3]
```

**Resultado Esperado**:
- ✅ Primeiro a entrar é primeiro a sair (FIFO)
- ✅ Ordem mantida corretamente

### Teste 3: Busca Binária vs Linear
```
Menu com 10 itens:

Busca por código 305 (Busca Binária):
- Máximo 4 comparações (log₂(10) ≈ 3.32)

Busca por nome "Salmao" (Busca Linear):
- Pode precisar até 10 comparações
- Mas permite busca parcial ("Sal" encontra "Salmao")
```

**Resultado Esperado**:
- ✅ Busca binária é mais rápida para códigos
- ✅ Busca linear necessária para nomes

### Teste 4: Ordenação por Prioridade
```
1. Criar pedidos com prioridades: [2, 4, 1, 3, 2]
2. Ordenar usando Quick Sort
3. Resultado: [4, 3, 2, 2, 1]
```

**Resultado Esperado**:
- ✅ Pedidos urgentes (4) aparecem primeiro
- ✅ Ordem decrescente de prioridade

### Teste 5: Histórico (UNDO)
```
1. Criar pedido (empilha ação)
2. Adicionar item A (empilha ação)
3. Adicionar item B (empilha ação)
4. UNDO → Remove item B
5. UNDO → Remove item A
6. UNDO → Desfaz criação do pedido
```

**Resultado Esperado**:
- ✅ Ações desfeitas na ordem inversa (LIFO)
- ✅ Pilha vazia ao final

---

## 💡 Conceitos Aprendidos

### 1. **Vetores são eficientes para acesso direto**
- Se você sabe o índice, acesso é O(1)
- Perfeito para menu de tamanho fixo

### 2. **Busca Binária exige ordem**
- Só funciona em arrays ordenados
- Mas é exponencialmente mais rápida que busca linear

### 3. **Filas garantem justiça**
- FIFO é perfeito para processamento sequencial
- Usado em: impressoras, processamento de requisições, agendamento de tarefas

### 4. **Pilhas são ideais para reverter ações**
- LIFO natural para UNDO/REDO
- Usado em: editores de texto, navegadores (histórico de páginas), recursão

### 5. **Quick Sort é rápido na prática**
- Embora pior caso seja O(n²), é raro
- Constantes multiplicativas pequenas
- In-place (usa pouca memória extra)

### 6. **Cada estrutura tem seu propósito**
- Não existe "melhor estrutura" absoluta
- Escolha depende do problema e padrões de acesso

---

## 🎯 Exercícios Propostos

### Exercício 1: Adicionar Funcionalidade
Implemente uma função para **remover um item específico da fila** (não apenas o primeiro).

**Desafio**: Como manter a eficiência O(1)?  
**Dica**: Pode ser necessário percorrer a fila O(n).

### Exercício 2: Melhorar Busca
Implemente **busca por categoria** (ex: listar todas as "bebidas").

**Desafio**: Qual estrutura de dados seria mais eficiente?  
**Dica**: Um mapa/hash table seria O(1), mas vetor + busca linear O(n) é suficiente para dataset pequeno.

### Exercício 3: Fila de Prioridade
Modifique a fila para ser uma **fila de prioridade** usando heap.

**Desafio**: Pedidos urgentes devem ser processados primeiro, mesmo que não sejam os primeiros da fila.  
**Dica**: Use um min-heap ou max-heap.

### Exercício 4: Persistência
Implemente funções para **salvar e carregar** pedidos de um arquivo.

**Desafio**: Como serializar estruturas complexas?  
**Dica**: Use fprintf/fscanf ou formato binário com fwrite/fread.

### Exercício 5: Estatísticas
Adicione um módulo de **relatórios** que calcule:
- Tempo médio de espera
- Item mais pedido
- Faturamento total

**Desafio**: Como fazer eficientemente?  
**Dica**: Mantenha contadores incrementais ao invés de recalcular sempre.

---

## 🔗 Relação com o Mundo Real

### Sistemas Reais que Usam Estas Estruturas:

1. **Uber/iFood - Fila de Pedidos**
   - Fila FIFO para processar pedidos
   - Ordenação por proximidade (Quick Sort)

2. **Ctrl+Z em Editores - Pilha**
   - Word, VS Code, Photoshop: todos usam pilha para UNDO

3. **Google Search - Busca Binária**
   - Índices ordenados permitem busca ultra-rápida

4. **Sistema Operacional - Fila de Processos**
   - CPU processa tarefas em fila (escalonamento FIFO)

5. **Netflix/YouTube - Fila de Reprodução**
   - Próximos vídeos em fila FIFO

---

## 📚 Referências e Leitura Adicional

### Livros
- **Cormen et al.** - *Introduction to Algorithms* (Capítulos sobre ordenação e estruturas básicas)
- **Sedgewick** - *Algorithms in C* (Implementações práticas)

### Artigos
- Hoare, C.A.R (1961) - "Algorithm 64: Quicksort"
- Knuth, D.E. (1973) - "The Art of Computer Programming Vol. 3: Sorting and Searching"

### Online
- [VisuAlgo](https://visualgo.net/) - Visualizar estruturas de dados
- [GeeksforGeeks](https://www.geeksforgeeks.org/data-structures/) - Tutoriais e implementações

---

## 👥 Autor e Contribuições

**Projeto Educacional**: Sistema de Gerenciamento de Restaurante  
**Objetivo**: Ensinar estruturas de dados através de exemplo prático  
**Público-Alvo**: Estudantes de Estrutura de Dados e Algoritmos

---

## 📝 Licença

Este é um projeto educacional livre para uso em sala de aula e estudos.

---

## ❓ FAQ - Perguntas Frequentes

### P: Por que não usar apenas vetores para tudo?
**R:** Vetores são ótimos para acesso direto, mas:
- Inserção/remoção no meio é O(n) - lenta
- Filas e pilhas com vetores desperdiçam espaço ou requerem deslocamentos
- Lista encadeada permite inserção/remoção O(1) em qualquer posição (se você tem o ponteiro)

### P: Por que a busca binária precisa de array ordenado?
**R:** A busca binária funciona descartando metade dos elementos a cada comparação. Isso só é possível se sabemos que:
- Valores à esquerda são menores
- Valores à direita são maiores
Em array desordenado, não podemos fazer essa garantia.

### P: Quando usar fila vs pilha?
**R:** 
- **Fila (FIFO)**: Quando ordem de chegada importa (atendimento, impressão, processamento sequencial)
- **Pilha (LIFO)**: Quando você precisa reverter ou processar de trás para frente (UNDO, recursão, expressões matemáticas)

### P: O Quick Sort sempre é melhor?
**R:** Não! Depende do contexto:
- **Quick Sort**: Melhor para uso geral, in-place
- **Merge Sort**: Melhor se precisa estabilidade ou tem dados em disco
- **Insertion Sort**: Melhor para arrays pequenos (< 10) ou quase ordenados
- **Counting Sort**: Melhor para inteiros em range pequeno

### P: Como o sistema lida com memória?
**R:**
- **Vetores**: Alocação estática (tamanho fixo em tempo de compilação)
- **Fila**: Alocação dinâmica (malloc/free para cada nó)
- **Pilha**: Alocação estática (array fixo de 10 ações)

---

## 🎓 Conclusão

Este projeto demonstra que estruturas de dados não são conceitos abstratos, mas ferramentas práticas para resolver problemas reais. Cada estrutura tem seu propósito e compreender quando usar cada uma é essencial para ser um bom programador.

**Principais Aprendizados**:
- ✅ Vetores são simples mas poderosos
- ✅ Busca binária é muito mais rápida que linear (mas precisa de ordem)
- ✅ Quick Sort é rápido na prática para ordenação geral
- ✅ Filas (FIFO) garantem justiça e ordem
- ✅ Pilhas (LIFO) são perfeitas para reverter ações
- ✅ Escolher a estrutura certa pode mudar O(n²) para O(log n)!

**Próximos Passos**:
1. Execute o programa e teste todas as funcionalidades
2. Tente os exercícios propostos
3. Modifique o código para adicionar novas features
4. Compare performance com diferentes tamanhos de dados

**Boa sorte nos estudos! 🚀**
