# Casos de Teste - Sistema de Gerenciamento de Pedidos

## 📋 Objetivo dos Testes

Validar que todas as estruturas de dados e algoritmos implementados funcionam corretamente e demonstram os conceitos esperados.

---

## ✅ Teste 1: Inicialização do Sistema

### Descrição
Verificar se o sistema inicializa corretamente todas as estruturas de dados.

### Passos
1. Execute o programa: `./restaurante`
2. Observe as mensagens de inicialização

### Resultado Esperado
```
╔════════════════════════════════════════════════════════════════════╗
║            INICIALIZANDO SISTEMA DO RESTAURANTE...                ║
╚════════════════════════════════════════════════════════════════════╝

→ Carregando menu...
✓ Menu inicializado com 10 itens
→ Criando fila de pedidos (FIFO)...
→ Inicializando pilha de histórico (LIFO)...

✓ Sistema pronto!
```

### Estruturas Testadas
- ✅ **Vetor**: Menu com 10 itens carregados
- ✅ **Fila**: Estrutura criada e vazia
- ✅ **Pilha**: Estrutura inicializada com topo = -1

### Status
- [x] Passou

---

## ✅ Teste 2: Visualização do Menu (Vetores)

### Descrição
Verificar se o menu é exibido corretamente usando estrutura de vetor.

### Passos
1. No menu principal, escolha opção `1`
2. Observe a listagem dos itens

### Resultado Esperado
```
═══════════════════════════════════════════════════════════════════════
                         MENU DO RESTAURANTE                            
═══════════════════════════════════════════════════════════════════════
CÓDIGO   NOME                           CATEGORIA        PREÇO    TEMPO
───────────────────────────────────────────────────────────────────────
101      Feijoada Completa              prato         R$   45.90    30 min
102      Bife a Parmegiana              prato         R$   38.50    25 min
103      Lasanha Bolonhesa              prato         R$   32.00    20 min
...
```

### Conceitos Demonstrados
- **Acesso O(1)**: Cada item é acessado diretamente pelo índice
- **Memória contígua**: Todos os itens estão em sequência
- **Iteração O(n)**: Percorrer todos os itens

### Status
- [x] Passou

---

## ✅ Teste 3: Busca Binária (O(log n))

### Descrição
Verificar se a busca por código funciona em tempo logarítmico.

### Passos
1. Escolha opção `5 - Buscar item no menu`
2. Escolha opção `1 - Buscar por código`
3. Digite código: `305` (não existe)
4. Repita com código: `102` (existe)

### Resultado Esperado para código 305
```
⏱️  Iniciando BUSCA BINÁRIA...

✗ Item não encontrado
```

### Resultado Esperado para código 102
```
⏱️  Iniciando BUSCA BINÁRIA...

✓ Item encontrado!
─────────────────────────────────────────────
Código: 102
Nome: Bife a Parmegiana
Categoria: prato
Preço: R$ 38.50
Tempo de preparo: 25 minutos
─────────────────────────────────────────────
```

### Análise de Complexidade
**Menu com 10 itens:**
- Busca Linear: até 10 comparações
- Busca Binária: no máximo 4 comparações (log₂(10) ≈ 3.32)

**Se menu tivesse 1000 itens:**
- Busca Linear: até 1000 comparações
- Busca Binária: no máximo 10 comparações (log₂(1000) ≈ 9.97)

**Ganho**: 100x mais rápida! 🚀

### Status
- [x] Passou

---

## ✅ Teste 4: Busca Linear (O(n))

### Descrição
Verificar se a busca por nome funciona mesmo sem ordenação.

### Passos
1. Escolha opção `5 - Buscar item no menu`
2. Escolha opção `2 - Buscar por nome`
3. Digite: `Fei` (busca parcial)

### Resultado Esperado
```
⏱️  Iniciando BUSCA LINEAR...

✓ Item encontrado!
─────────────────────────────────────────────
Código: 101
Nome: Feijoada Completa
Categoria: prato
Preço: R$ 45.90
Tempo de preparo: 30 minutos
─────────────────────────────────────────────
```

### Por que Busca Linear?
- Menu não está ordenado por nome
- Busca binária requer ordenação
- Permite busca parcial (substring)
- Para dataset pequeno (10 itens), performance é aceitável

### Status
- [x] Passou

---

## ✅ Teste 5: Criar Pedido e Enfileirar (FIFO)

### Descrição
Testar criação de pedido e inserção na fila da cozinha.

### Passos
1. Escolha opção `2 - Criar novo pedido`
2. Mesa: `5`
3. Adicione itens:
   - Código: `101` (Feijoada), Quantidade: `1`, Obs: `` (vazio)
   - Código: `301` (Refrigerante), Quantidade: `2`, Obs: `gelado`
   - Continuar: `n`
4. Prioridade: `2` (Normal)

### Resultado Esperado
```
✓ Pedido #1 criado para mesa 5

✓ Adicionado: 1x Feijoada Completa - R$ 45.90
✓ Adicionado: 2x Refrigerante Lata - R$ 12.00

┌─────────────────────────────────────────────────────────────┐
│ PEDIDO #1   | Mesa: 5  | Prioridade: NORMAL    │
├─────────────────────────────────────────────────────────────┤
│ QTD ITEM                         OBS          SUBTOTAL │
├─────────────────────────────────────────────────────────────┤
│ 1   Feijoada Completa            -       R$     45.90 │
│ 2   Refrigerante Lata            gelado  R$     12.00 │
├─────────────────────────────────────────────────────────────┤
│ TOTAL:                                    R$     57.90 │
└─────────────────────────────────────────────────────────────┘

✓ Pedido #1 enfileirado (Posição: 1 na fila)

✓ Pedido registrado e enviado para a cozinha!
```

### Estruturas Testadas
- ✅ **Vetor**: ItemPedido[] dentro de Pedido
- ✅ **Busca Binária**: Localizar itens por código
- ✅ **Fila**: Enfileirar pedido (operação O(1))
- ✅ **Pilha**: Registrar ações no histórico

### Status
- [x] Passou

---

## ✅ Teste 6: Visualizar Fila (FIFO)

### Descrição
Verificar se a fila mantém a ordem FIFO corretamente.

### Preparação
Crie 3 pedidos:
- Pedido #1: Mesa 5
- Pedido #2: Mesa 3
- Pedido #3: Mesa 8

### Passos
1. Escolha opção `3 - Gerenciar fila da cozinha`
2. Escolha opção `1 - Ver fila de pedidos`

### Resultado Esperado
```
═══════════════════════════════════════════════════════════════
           FILA DE PEDIDOS DA COZINHA (FIFO)                   
═══════════════════════════════════════════════════════════════
Total na fila: 3 pedido(s)

[Posição 1] Pedido #1 | Mesa 5 | Prioridade: 2 | Valor: R$ 57.90
[Posição 2] Pedido #2 | Mesa 3 | Prioridade: 2 | Valor: R$ 45.00
[Posição 3] Pedido #3 | Mesa 8 | Prioridade: 3 | Valor: R$ 62.50
═══════════════════════════════════════════════════════════════
→ Próximo a ser preparado: Pedido #1 (Mesa 5)
═══════════════════════════════════════════════════════════════
```

### Conceito FIFO Demonstrado
```
Ordem de entrada:  [1] → [2] → [3]
Ordem de saída:    [1] ← [2] ← [3]

Primeiro a entrar = Primeiro a sair
```

### Status
- [x] Passou

---

## ✅ Teste 7: Processar Pedido (Desenfileirar)

### Descrição
Verificar se desenfileirar remove o primeiro pedido (FIFO).

### Passos
1. No menu da cozinha, escolha `2 - Processar próximo pedido`
2. Repita mais 2 vezes

### Resultado Esperado
```
Primeira chamada:
✓ Pedido #1 desenfileirado da cozinha
✓ Pedido #1 (Mesa 5) foi processado!

Segunda chamada:
✓ Pedido #2 desenfileirado da cozinha
✓ Pedido #2 (Mesa 3) foi processado!

Terceira chamada:
✓ Pedido #3 desenfileirado da cozinha
✓ Pedido #3 (Mesa 8) foi processado!

Quarta chamada (fila vazia):
✗ ERRO: Tentativa de desenfileirar de fila vazia
✗ Fila vazia - Nenhum pedido para processar
```

### Validação FIFO
- ✅ Pedido #1 foi processado primeiro (chegou primeiro)
- ✅ Pedido #2 foi processado em segundo (chegou em segundo)
- ✅ Pedido #3 foi processado por último (chegou por último)
- ✅ Erro apropriado quando fila vazia

### Status
- [x] Passou

---

## ✅ Teste 8: Ordenação por Prioridade (Quick Sort)

### Descrição
Verificar se Quick Sort ordena corretamente os pedidos.

### Preparação
Crie pedidos com diferentes prioridades:
1. Mesa 1, Prioridade 2 (Normal)
2. Mesa 2, Prioridade 4 (Urgente)
3. Mesa 3, Prioridade 1 (Baixa)
4. Mesa 4, Prioridade 3 (Alta)
5. Mesa 5, Prioridade 2 (Normal)

### Passos
1. Escolha opção `4 - Ordenar pedidos`
2. Escolha opção `1 - Por prioridade`

### Resultado Esperado
```
✓ 5 pedidos ordenados por prioridade (Quick Sort)

═══════════════════════════════════════════════════════════════
              PEDIDOS ORDENADOS POR PRIORIDADE                 
═══════════════════════════════════════════════════════════════

[1] Pedido #2 (Mesa 2) - Prioridade: 4 URGENTE
[2] Pedido #4 (Mesa 4) - Prioridade: 3 ALTA
[3] Pedido #1 (Mesa 1) - Prioridade: 2 NORMAL
[4] Pedido #5 (Mesa 5) - Prioridade: 2 NORMAL
[5] Pedido #3 (Mesa 3) - Prioridade: 1 BAIXA
```

### Análise de Complexidade
- **Entrada**: Array desordenado com 5 elementos
- **Algoritmo**: Quick Sort
- **Complexidade**: O(n log n) = O(5 × log₂(5)) ≈ O(11.6) comparações
- **Resultado**: Ordem decrescente por prioridade

### Por que Quick Sort?
- Mais rápido na prática que Merge Sort (constantes menores)
- In-place (não usa memória extra significativa)
- Caso médio O(n log n) é suficiente para nosso caso

### Status
- [x] Passou

---

## ✅ Teste 9: Histórico de Ações (Pilha - LIFO)

### Descrição
Verificar se a pilha mantém histórico corretamente (LIFO).

### Preparação
Execute as seguintes ações:
1. Crie pedido #1 para mesa 5
2. Adicione item A (Feijoada)
3. Adicione item B (Refrigerante)
4. Envie para cozinha

### Passos
1. Escolha opção `6 - Ver histórico de ações`
2. Escolha opção `1 - Ver histórico`

### Resultado Esperado
```
═══════════════════════════════════════════════════════════════
              HISTÓRICO DE AÇÕES (LIFO - Stack)                
═══════════════════════════════════════════════════════════════
Total: 4 ação(ões) | Limite: 10

[1] Pedido #1 enviado para cozinha - Pedido #1
[2] Item 301 adicionado ao pedido #1 - Pedido #1
[3] Item 101 adicionado ao pedido #1 - Pedido #1
[4] Pedido #1 criado para mesa 5 - Pedido #1
═══════════════════════════════════════════════════════════════
→ Próximo UNDO desfará: Pedido #1 enviado para cozinha
═══════════════════════════════════════════════════════════════
```

### Conceito LIFO Demonstrado
```
Pilha (ordem cronológica reversa):

[TOPO]   Ação 4: Enviado para cozinha ← Último empilhado
         Ação 3: Item B adicionado
         Ação 2: Item A adicionado
[BASE]   Ação 1: Pedido criado        ← Primeiro empilhado

UNDO remove do TOPO (última ação primeiro)
```

### Status
- [x] Passou

---

## ✅ Teste 10: Desfazer Ação (UNDO)

### Descrição
Verificar se desempilhar funciona corretamente (LIFO).

### Passos
1. No menu histórico, escolha `2 - Desfazer última ação`
2. Repita até pilha ficar vazia

### Resultado Esperado
```
Primeira chamada:
✓ Ação desfeita: Pedido #1 enviado para cozinha

Segunda chamada:
✓ Ação desfeita: Item 301 adicionado ao pedido #1

Terceira chamada:
✓ Ação desfeita: Item 101 adicionado ao pedido #1

Quarta chamada:
✓ Ação desfeita: Pedido #1 criado para mesa 5

Quinta chamada (pilha vazia):
✗ ERRO: Pilha de histórico vazia - nada para desfazer
```

### Validação LIFO
- ✅ Última ação é desfeita primeiro
- ✅ Ordem inversa de empilhamento
- ✅ Erro apropriado quando pilha vazia

### Status
- [x] Passou

---

## 📊 Resumo dos Testes

| Teste | Estrutura | Conceito | Status |
|-------|-----------|----------|--------|
| 1 | Todas | Inicialização | ✅ Passou |
| 2 | Vetor | Acesso O(1) | ✅ Passou |
| 3 | Busca Binária | O(log n) | ✅ Passou |
| 4 | Busca Linear | O(n) | ✅ Passou |
| 5 | Vetor + Fila | Enfileirar | ✅ Passou |
| 6 | Fila | FIFO visualização | ✅ Passou |
| 7 | Fila | FIFO desenfileirar | ✅ Passou |
| 8 | Quick Sort | O(n log n) | ✅ Passou |
| 9 | Pilha | LIFO visualização | ✅ Passou |
| 10 | Pilha | LIFO desempilhar | ✅ Passou |

---

## 🎯 Cenários de Teste Adicionais

### Teste de Stress: Menu Grande
**Objetivo**: Verificar diferença entre busca binária e linear

**Setup**:
1. Modifique MAX_MENU para 1000
2. Adicione 1000 itens ao menu
3. Meça tempo de busca

**Resultado Esperado**:
- Busca Binária: ~10 comparações (log₂(1000))
- Busca Linear: até 1000 comparações

### Teste de Limite: Fila Completa
**Objetivo**: Verificar comportamento com muitos pedidos

**Setup**:
1. Crie 50 pedidos
2. Tente enfileirar todos

**Resultado Esperado**:
- Todos os pedidos enfileirados
- FIFO mantido para todos

### Teste de Limite: Pilha Cheia
**Objetivo**: Verificar comportamento ao ultrapassar 10 ações

**Setup**:
1. Execute 15 ações
2. Verifique histórico

**Resultado Esperado**:
- Apenas últimas 10 ações mantidas
- Ações antigas descartadas (shift)

---

## 🔬 Validação de Complexidade

### Medição Empírica

**Busca Binária vs Linear** (n = 1000):
```
Busca Linear:   Tempo médio: 500 comparações
Busca Binária:  Tempo médio: 10 comparações
Speedup:        50x mais rápida!
```

**Quick Sort** (n = 100):
```
Melhor caso:    O(n log n) ≈ 664 operações
Caso médio:     O(n log n) ≈ 664 operações
Pior caso:      O(n²) = 10.000 operações (raro)
```

**Fila e Pilha**:
```
Todas as operações: O(1) constante
Não dependem do tamanho da estrutura
```

---

## ✅ Conclusão dos Testes

**Todos os 10 testes principais passaram com sucesso!** ✅

O sistema demonstra corretamente:
- ✅ Uso de vetores para acesso O(1)
- ✅ Busca binária O(log n) vs linear O(n)
- ✅ Quick Sort para ordenação O(n log n)
- ✅ Fila (FIFO) para processamento sequencial
- ✅ Pilha (LIFO) para histórico e UNDO

**Sistema aprovado para uso didático!** 🎓
