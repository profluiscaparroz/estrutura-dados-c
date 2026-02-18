# 📚 Problemas Práticos - Estruturas de Dados em C

Este diretório contém exemplos práticos de problemas do dia a dia resolvidos com estruturas de dados em C.

## 🎯 Objetivo

Cada problema demonstra:
- ❌ **Implementação ineficiente** (código problemático)
- ✅ **Solução otimizada** (código correto)
- 📊 **Análise de complexidade** (Big O)
- 💡 **Casos de uso** e aplicações reais
- 📝 **Como compilar e executar**

## 📋 Índice de Problemas

### 1. [Vetores e Matrizes](02-vetor-matriz/PROBLEMA_PRATICO.md)
**Sistema de Gerenciamento de Estoque**
- Problema: Busca linear O(n), sem validação de limites
- Solução: Struct organizada, validação completa, tratamento de erros
- Conceitos: Arrays contíguos, acesso O(1), validação de limites

### 2. [Métodos de Ordenação](03-metodos-ordenacao/PROBLEMA_PRATICO.md)
**Sistema de Classificação de Notas Escolares**
- Problema: Bubble Sort O(n²) para grandes volumes
- Solução: Quick Sort O(n log n), comparadores personalizados
- Conceitos: Algoritmos de ordenação, desempate, estatísticas

### 3. [Algoritmos de Pesquisa](04-pesquisa/PROBLEMA_PRATICO.md)
**Sistema de Busca de Produtos em E-commerce**
- Problema: Sempre busca linear O(n)
- Solução: Busca Binária O(log n), Busca Interpolada O(log log n)
- Conceitos: Busca em dados ordenados, autocompletar, otimizações

### 4. [Pilhas](05-pilhas-filas/PROBLEMA_PRATICO_PILHA.md)
**Sistema de Desfazer/Refazer (Undo/Redo)**
- Problema: Array simples perde histórico de redo
- Solução: Duas pilhas (undo + redo), LIFO
- Conceitos: Pilha LIFO, push/pop O(1), histórico de ações

### 5. [Filas](05-pilhas-filas/PROBLEMA_PRATICO_FILA.md)
**Sistema de Atendimento de Call Center**
- Problema: Dequeue O(n) com deslocamento de array
- Solução: Fila circular O(1), sistema de prioridade
- Conceitos: Fila FIFO, fila circular, múltiplas prioridades

### 6. [Lista Encadeada](06-lista-encadeada/PROBLEMA_PRATICO.md)
**Sistema de Playlist de Música**
- Problema: Array fixo, inserção/remoção O(n)
- Solução: Lista duplamente encadeada, navegação bidirecional O(1)
- Conceitos: Nós dinâmicos, ponteiros duplos, tamanho dinâmico

### 7. [Grafos](07-grafos/PROBLEMA_PRATICO.md)
**Sistema de Navegação GPS (Dijkstra)**
- Problema: Busca exaustiva exponencial
- Solução: Algoritmo de Dijkstra O((V+E) log V) com Min-Heap
- Conceitos: Menor caminho, lista de adjacência, relaxamento de arestas

### 8. [Árvore Binária de Busca](08-bst/PROBLEMA_PRATICO.md)
**Sistema de Dicionário com Autocompletar**
- Problema: Busca linear O(n), sem ordem
- Solução: BST com busca O(log n), in-order = alfabética
- Conceitos: Propriedade BST, percursos, autocompletar eficiente

### 9. [Heap (Fila de Prioridade)](09-heap/PROBLEMA_PRATICO.md)
**Sistema de Priorização de Tarefas**
- Problema: Obter máximo sempre O(n)
- Solução: Max-Heap com extração O(log n)
- Conceitos: Heap binário, heapify, array como estrutura

### 10. [Hash Tables](10-hash-tables/PROBLEMA_PRATICO.md)
**Sistema de Cache de Aplicação Web**
- Problema: Busca O(n) inaceitável para cache
- Solução: Hash Table O(1) + política LRU
- Conceitos: Função hash, chaining, LRU, hit rate

## 🚀 Como Usar

### Compilar um Exemplo

```bash
# Navegar para o diretório
cd src/02-vetor-matriz

# Extrair código C do markdown (opcional, para teste)
# ... ou copiar manualmente o código da seção "Solução"

# Compilar
gcc PROBLEMA_PRATICO.c -o programa -Wall

# Executar
./programa
```

### Estudar os Exemplos

1. **Leia o problema** - Entenda o contexto real
2. **Analise o código problemático** - Identifique os erros
3. **Estude a solução** - Veja as melhorias
4. **Compare complexidades** - Entenda o ganho de performance
5. **Compile e execute** - Veja funcionando na prática
6. **Modifique o código** - Experimente variações

## 📊 Resumo de Complexidades

| Estrutura | Buscar | Inserir | Remover | Espaço | Melhor Para |
|-----------|--------|---------|---------|--------|-------------|
| Array | O(n) | O(1)* | O(n) | O(n) | Acesso aleatório |
| Lista Encadeada | O(n) | O(1)** | O(1)** | O(n) | Inserções/remoções |
| BST | O(log n) | O(log n) | O(log n) | O(n) | Dados ordenados |
| Heap | O(n) | O(log n) | O(log n) | O(n) | Priorização |
| Hash Table | O(1) | O(1) | O(1) | O(n) | Chave-valor |
| Grafo (Adj List) | O(V+E) | O(1) | O(E) | O(V+E) | Relações |

*No final do array  
**Quando temos o nó

## 💡 Dicas para Escolher a Estrutura Certa

### Use **Array/Vetor** quando:
- ✅ Tamanho conhecido e fixo
- ✅ Acesso aleatório frequente (por índice)
- ✅ Cache-friendly (dados contíguos)

### Use **Lista Encadeada** quando:
- ✅ Tamanho dinâmico desconhecido
- ✅ Muitas inserções/remoções no meio
- ✅ Navegação sequencial

### Use **BST** quando:
- ✅ Precisa manter dados ordenados
- ✅ Busca + inserção frequentes
- ✅ Range queries (intervalos)

### Use **Heap** quando:
- ✅ Precisa sempre do máximo/mínimo
- ✅ Fila de prioridade
- ✅ K maiores/menores elementos

### Use **Hash Table** quando:
- ✅ Busca deve ser O(1)
- ✅ Chave-valor
- ✅ Não precisa ordenação

### Use **Grafo** quando:
- ✅ Modelar conexões/relacionamentos
- ✅ Caminhos mínimos
- ✅ Redes (sociais, transporte, etc)

## 🎓 Conceitos-Chave Demonstrados

1. **Trade-off Tempo vs Espaço** - Arrays são compactos, listas usam mais memória
2. **Validação é essencial** - Sempre verificar limites e erros
3. **Complexidade importa** - O(1) vs O(n) faz diferença enorme
4. **Estrutura certa para cada problema** - Não existe "melhor estrutura"
5. **Código limpo** - Funções modulares, nomes descritivos
6. **Teste seus códigos** - Compile e execute para aprender

## 📚 Recursos Adicionais

- **READMEs principais**: Cada diretório tem README detalhado com teoria
- **Código-fonte**: Exemplos completos e funcionais
- **Comentários**: Código bem documentado
- **Análise**: Complexidade de tempo e espaço

## 🔧 Compilação e Requisitos

### Requisitos
- GCC (GNU Compiler Collection)
- C Standard Library

### Flags Recomendadas
```bash
gcc arquivo.c -o programa -Wall -Wextra -std=c11
```

- `-Wall`: Habilita warnings importantes
- `-Wextra`: Warnings adicionais
- `-std=c11`: Usa padrão C11

## ✅ Checklist de Aprendizado

Ao estudar cada estrutura, certifique-se de:

- [ ] Entender o problema real que ela resolve
- [ ] Saber a complexidade das operações principais
- [ ] Identificar quando usar vs quando não usar
- [ ] Conseguir implementar do zero
- [ ] Saber as variações (ex: BST → AVL, Red-Black)
- [ ] Conhecer aplicações reais

## 🎯 Próximos Passos

1. **Implemente variações** - Tente modificar os exemplos
2. **Crie seus próprios problemas** - Aplique em projetos pessoais
3. **Estude estruturas avançadas** - AVL, Red-Black, B-Trees, etc
4. **Pratique em plataformas** - LeetCode, HackerRank, CodeForces
5. **Contribua** - Adicione mais exemplos ao repositório!

## 📖 Referências

- Introduction to Algorithms (CLRS)
- Data Structures and Algorithms in C (Goodrich, Tamassia)
- The Art of Computer Programming (Knuth)

---

**Autor**: Compilado como exercício prático para o repositório de Estruturas de Dados em C

**Licença**: Mesma do repositório principal

**Última Atualização**: 2026-02-18
