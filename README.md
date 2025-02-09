# Introdução à Disciplina de Estrutura de Dados

## O que é Estrutura de Dados?

A disciplina de **Estrutura de Dados** é um dos pilares fundamentais da Ciência da Computação. Ela se concentra no estudo e na implementação de diferentes formas de organização, armazenamento e manipulação de dados para resolver problemas computacionais de maneira eficiente. Ao aprender estruturas de dados, os alunos desenvolvem habilidades essenciais para criar programas que otimizam o uso de recursos como memória e tempo de processamento.

### Por que estudar Estruturas de Dados?

A escolha correta de uma estrutura de dados pode determinar o sucesso ou o fracasso de um sistema. Alguns motivos para estudar estruturas de dados incluem:

- **Eficiência:** Reduzir o tempo de execução de algoritmos.
- **Organização:** Facilitar a manutenção e escalabilidade de projetos.
- **Flexibilidade:** Resolver problemas complexos com soluções elegantes e adaptáveis.
- **Base para outros conceitos:** Estruturas de dados são essenciais em diversas áreas, como Inteligência Artificial, Desenvolvimento de Jogos, Redes de Computadores e muito mais.

---

## Principais Conceitos

### Tipos de Estruturas de Dados

1. **Estruturas Lineares**
   - **Arrays:** Coleções de elementos armazenados em posições contíguas.
   - **Listas Ligadas:** Conjuntos de nós conectados por ponteiros.
   - **Filas:** Estruturas FIFO (*First-In, First-Out*).
   - **Pilhas:** Estruturas LIFO (*Last-In, First-Out*).

2. **Estruturas Não-Lineares**
   - **Árvores:** Estruturas hierárquicas, como Árvores Binárias e Árvores AVL.
   - **Grafos:** Representações de relações entre pares de elementos (vértices e arestas).

3. **Tabelas Hash**
   - Estruturas que utilizam funções de dispersão (hashing) para mapeamento eficiente de dados.

### Operações Básicas

- Inserção
- Remoção
- Busca
- Ordenação
- Travessia (em árvores e grafos)

---
## Tópicos da disciplina

### Vetores e Matrizes  
**Vetores:**  
Um vetor (ou array unidimensional) é uma estrutura de dados linear que armazena uma coleção de elementos do mesmo tipo em posições consecutivas de memória. Ele é usado para armazenar e acessar elementos de forma rápida, utilizando um índice. Por exemplo, um vetor pode ser usado para armazenar as notas de um aluno em diferentes disciplinas.  
Exemplo:  
```plaintext
vetor = [10, 20, 30, 40]  
```

**Matrizes:**  
Uma matriz (ou array bidimensional) é uma extensão dos vetores, permitindo armazenar dados em duas dimensões, como linhas e colunas. As matrizes são úteis em aplicações como gráficos, tabelas e álgebra linear.  
Exemplo:  
```plaintext
matriz = [[1, 2, 3],  
          [4, 5, 6],  
          [7, 8, 9]]  
```

### Métodos de Ordenação  
Métodos de ordenação são algoritmos usados para organizar dados em ordem crescente ou decrescente. Alguns dos principais são:  

- **Bubble Sort:** Percorre o array várias vezes, trocando elementos adjacentes fora de ordem. Simples, mas ineficiente para grandes volumes de dados.  
- **Quick Sort:** Usa a técnica de divisão e conquista, escolhendo um elemento como pivô e particionando os elementos em menores ou maiores que o pivô. Muito eficiente.  
- **Merge Sort:** Também baseado em divisão e conquista, divide o array em partes menores, ordena e depois mescla as partes.  
- **Insertion Sort:** Insere elementos de forma ordenada em um subarray enquanto percorre o array principal.  

Cada método tem vantagens dependendo do tamanho e da natureza dos dados a serem ordenados.  

### Métodos de Pesquisa  
Métodos de pesquisa são usados para encontrar elementos dentro de estruturas de dados. Os principais incluem:  

- **Busca Linear:** Percorre os elementos um por um até encontrar o desejado ou alcançar o final. É simples, mas ineficiente para grandes conjuntos de dados.  
- **Busca Binária:** Requer que os dados estejam ordenados. Divide repetidamente o conjunto em dois, descartando metade a cada iteração até encontrar o elemento desejado. Muito mais eficiente que a busca linear.  
- **Pesquisa em Tabelas Hash:** Usa uma função hash para calcular o índice de armazenamento, permitindo acesso rápido e eficiente.  

### Filas e Pilhas  
**Filas:**  
Uma fila é uma estrutura de dados linear baseada no princípio FIFO (*First-In, First-Out*), onde o primeiro elemento inserido é o primeiro a ser removido. Filas são usadas em situações como processamento de tarefas em ordem ou em sistemas de mensagens.  
Exemplo:  
```plaintext
Fila: [1, 2, 3]  
Operação de inserção: Entra o 4 → [1, 2, 3, 4]  
Operação de remoção: Sai o 1 → [2, 3, 4]  
```

**Pilhas:**  
Uma pilha é baseada no princípio LIFO (*Last-In, First-Out*), onde o último elemento inserido é o primeiro a ser removido. Pilhas são úteis em situações como gerenciamento de chamadas em recursão ou desfazer ações em editores de texto.  
Exemplo:  
```plaintext
Pilha: [1, 2, 3]  
Operação de inserção: Entra o 4 → [1, 2, 3, 4]  
Operação de remoção: Sai o 4 → [1, 2, 3]  
```

### Listas Encadeadas  
Uma lista encadeada é uma estrutura de dados onde cada elemento (ou nó) contém dois componentes: o valor armazenado e um ponteiro que aponta para o próximo nó da lista. Diferente de arrays, listas encadeadas não armazenam elementos em posições consecutivas de memória, o que permite maior flexibilidade na alocação dinâmica de memória.  

**Tipos de listas encadeadas:**  
- **Lista Simplesmente Encadeada:** Cada nó aponta apenas para o próximo.  
- **Lista Duplamente Encadeada:** Cada nó tem dois ponteiros: um para o próximo e outro para o anterior.  
- **Lista Circular:** O último nó aponta para o primeiro, formando um ciclo.  

Listas encadeadas são úteis em aplicações onde o tamanho da estrutura de dados é dinâmico e alterações frequentes (inserções e remoções) são necessárias.  

Exemplo de uma lista simplesmente encadeada:  
```plaintext
[10 | *] -> [20 | *] -> [30 | NULL]  
```  
### Árvores  

As árvores são estruturas de dados hierárquicas que consistem em nós conectados por arestas, formando uma organização em forma de "ramificações". O nó principal é chamado de **raiz**, e cada nó pode ter "filhos", que são outros nós conectados a ele.  

#### Componentes de uma árvore:  
- **Raiz:** O nó principal, que não possui pai.  
- **Nós internos:** Nós que possuem pelo menos um filho.  
- **Folhas:** Nós que não possuem filhos.  
- **Altura:** O número máximo de níveis entre a raiz e as folhas.  

#### Tipos de árvores:  
1. **Árvores Binárias:** Cada nó pode ter no máximo dois filhos (esquerda e direita).  
2. **Árvores de Busca Binária (BST):** Uma árvore binária em que os nós à esquerda são menores que o pai, e os à direita são maiores.  
3. **Árvores Balanceadas:** Estruturas como AVL e Red-Black Trees garantem que a altura da árvore permaneça equilibrada para operações eficientes.  
4. **Árvores B e B+:** Usadas em bancos de dados e sistemas de arquivos para armazenar dados de forma eficiente.  
5. **Heap:** Árvores binárias usadas em algoritmos de ordenação e filas de prioridade.  

As árvores são amplamente usadas em cenários como representação hierárquica de informações, algoritmos de busca e compressão de dados.  

---

### Grafos  

Os grafos são estruturas de dados generalizadas usadas para modelar relações entre pares de objetos. Um grafo é composto por:  
- **Vértices (ou nós):** Representam os elementos.  
- **Arestas:** Conexões entre os vértices, que podem ser direcionadas ou não.  

#### Tipos de grafos:  
- **Grafo não direcionado:** As arestas não têm direção, ou seja, as conexões são bidirecionais.  
- **Grafo direcionado (ou dígrafo):** As arestas têm uma direção específica.  
- **Grafo ponderado:** As arestas possuem pesos associados, como distâncias ou custos.  
- **Grafos completos:** Cada vértice está conectado a todos os outros.  

#### Aplicações de grafos:  
- Redes sociais (amigos conectados).  
- Rotas de GPS (nós como locais e arestas como estradas com peso).  
- Análise de redes elétricas ou de transporte.  

Algoritmos famosos como **Dijkstra** (para encontrar o caminho mais curto) e **Kruskal** (para encontrar a árvore geradora mínima) são amplamente usados em grafos.  

---

## Repositórios de Exemplo no GitHub

A prática é essencial para consolidar o conhecimento em Estruturas de Dados. Aqui estão alguns repositórios no GitHub que oferecem implementações e exercícios:

1. **[The Algorithms - Data Structures](https://github.com/TheAlgorithms/C)**
   - Repositório comunitário com implementações de estruturas de dados e algoritmos em várias linguagens.

2. **[Awesome Data Structures](https://github.com/lnishan/awesome-competitive-programming)**
   - Uma coleção de recursos e repositórios voltados para programação competitiva, com foco em estruturas de dados.

3. **[Data Structures in Python](https://github.com/joeyajames/Python)**
   - Implementações das principais estruturas de dados em Python.

4. **[CLRS Algorithms](https://github.com/gzc/CLRS)**
   - Implementações baseadas no livro clássico *Introduction to Algorithms* (Cormen).

5. **[Data Structures and Algorithms in C++](https://github.com/mission-peace/interview)**
   - Exemplos e explicações de estruturas de dados para entrevistas técnicas.

---

## Ferramentas de Aprendizado

Além dos repositórios de código, existem diversas ferramentas para ajudar a visualizar e entender como funcionam as estruturas de dados:

- **[VisuAlgo](https://visualgo.net/en)**: Plataforma interativa para visualizar estruturas de dados e algoritmos.
- **[GeeksforGeeks](https://www.geeksforgeeks.org/data-structures/)**: Artigos e implementações práticas.
- **[Codeforces](https://codeforces.com/)** e **[LeetCode](https://leetcode.com/)**: Plataformas de prática com problemas que exigem conhecimento de estruturas de dados.


## Referências

1. **Livros:**
   - *Introduction to Algorithms* - Cormen, Leiserson, Rivest, Stein (CLRS).
   - *Algorithms* - Robert Sedgewick e Kevin Wayne.
   - *Data Structures and Algorithm Analysis in C* - Mark Allen Weiss.

2. **Artigos e Tutoriais Online:**
   - [GeeksforGeeks - Data Structures](https://www.geeksforgeeks.org/data-structures/)
   - [TutorialsPoint - Data Structures](https://www.tutorialspoint.com/data_structures_algorithms/index.htm)

3. **Cursos Online:**
   - [Coursera - Data Structures and Algorithms](https://www.coursera.org/specializations/data-structures-algorithms)
   - [edX - Data Structures Fundamentals](https://www.edx.org/course/data-structures-fundamentals)

---