# Consistent Hashing

## 📚 Definição Formal

**Consistent Hashing** é uma técnica de hashing distribuído que minimiza a quantidade de remapeamento necessário quando o número de slots (nós) em uma tabela hash muda. Em contraste com hashing tradicional, onde a adição ou remoção de um slot requer remapear quase todas as chaves, consistent hashing remapeia apenas **K/n** chaves em média, onde K é o número de chaves e n é o número de slots.

## 🎓 Fundamentação Teórica

### Origem Histórica

O Consistent Hashing foi introduzido por:

- **Karger, Leighton, et al. (1997)**: Artigo seminal "Consistent Hashing and Random Trees: Distributed Caching Protocols for Relieving Hot Spots on the World Wide Web" no STOC.
- **Motivação original**: Distribuição de carga em web caches

### Problema do Hashing Tradicional

No hashing tradicional com módulo:

```
servidor = hash(chave) mod n
```

**Problema**: Quando n muda para n±1, quase todas as chaves são remapeadas:
- Fração de chaves remapeadas: (n-1)/n ≈ 100% para n grande

### Propriedades Formais do Consistent Hashing

1. **Balanceamento**: Com alta probabilidade, cada nó recebe aproximadamente 1/n das chaves
2. **Monotonicidade**: Quando nós são adicionados, chaves só migram para novos nós
3. **Spread**: Cada chave é mapeada para O(log n) nós diferentes através de múltiplas visões
4. **Load**: Cada nó pode ter no máximo O(log n) vezes a carga média

## 🔄 Funcionamento do Anel Hash

### Conceito do Anel (Hash Ring)

1. O espaço de hash é representado como um anel circular [0, 2^m - 1]
2. Tanto nós quanto chaves são mapeados para posições no anel
3. Uma chave é atribuída ao primeiro nó encontrado no sentido horário

```
        0
       /|\
      / | \
     /  |  \
   330  |  30
    \   |   /
     \  |  /
      \ | /
  270 --+-- 90
      / | \
     /  |  \
    /   |   \
   210  |  150
        |
       180
```

### Algoritmo de Lookup

```
LOOKUP(key)
    hash_key = hash(key)
    for each node in sorted_order(nodes)
        if node.hash >= hash_key
            return node
    return first_node  // Wrap around
```

**Complexidade**: O(n) naive, O(log n) com busca binária

## 📊 Análise de Complexidade

| Operação | Complexidade | Descrição |
|----------|--------------|-----------|
| Inserir chave | O(log n) | Busca binária no anel |
| Lookup | O(log n) | Busca do nó responsável |
| Adicionar nó | O(K/n + log n) | Remapear K/n chaves |
| Remover nó | O(K/n + log n) | Remapear K/n chaves |

## 🎯 Virtual Nodes (Nós Virtuais)

### Problema de Distribuição Desigual

Com poucos nós físicos, a distribuição pode ser desbalanceada:
- Variância alta no número de chaves por nó
- Esperado: K/n chaves por nó
- Desvio padrão: O(√(K/n))

### Solução: Nós Virtuais

Cada nó físico é representado por múltiplos nós virtuais no anel:

```
Nó físico A → {A₁, A₂, A₃, ..., Aᵥ}
Nó físico B → {B₁, B₂, B₃, ..., Bᵥ}
```

**Benefícios**:
- Distribuição mais uniforme
- Número de virtual nodes por nó físico pode variar (proporcional à capacidade)
- Recomendação: 100-200 virtual nodes por nó físico

### Análise com Virtual Nodes

- Com v virtual nodes por nó físico
- Total de pontos no anel: n × v
- Variância reduzida por fator de √v

## 🛠️ Implementação

### Estrutura de Dados

```c
typedef struct {
    char name[50];
    unsigned int hash;
} VirtualNode;

typedef struct {
    VirtualNode *ring;    // Array ordenado de virtual nodes
    int ring_size;
    int num_physical_nodes;
    int virtual_nodes_per_physical;
} ConsistentHash;
```

### Funções Hash Recomendadas

1. **MD5** (128 bits) - Boa distribuição, mais lento
2. **SHA-1** (160 bits) - Criptograficamente forte
3. **MurmurHash3** (32/128 bits) - Rápido, não criptográfico
4. **xxHash** - Muito rápido, boa distribuição

### Escolha da Função Hash

Para consistent hashing, a função deve ter:
- **Uniformidade**: Distribuição uniforme no espaço de hash
- **Determinismo**: Mesma entrada → mesmo hash
- **Velocidade**: Para alta taxa de operações (use MurmurHash ou xxHash)

## 📈 Aplicações Práticas

### 1. Sistemas de Cache Distribuído

**Amazon DynamoDB**:
- Usa consistent hashing para particionamento
- Virtual nodes para balanceamento de carga

**Apache Cassandra**:
- Particionador baseado em consistent hashing
- Token ring para distribuição de dados

**Memcached / Redis Cluster**:
- Sharding de dados entre instâncias

### 2. Content Delivery Networks (CDNs)

**Akamai**:
- Roteamento de requisições para servidores de cache
- Minimiza redistribuição quando servidores falham

### 3. Load Balancers

**NGINX**:
- Upstream consistent hashing
- Sticky sessions sem estado compartilhado

### 4. Bancos de Dados Distribuídos

**Riak**:
- Consistent hashing com handoff
- Preference list para replicação

## 🔄 Variantes e Extensões

### 1. Jump Consistent Hash (Google, 2014)

**Vantagens**:
- Não requer armazenamento de ring
- O(1) tempo de lookup
- Perfeitamente uniforme

**Desvantagem**:
- Só funciona com nós numerados sequencialmente

```c
int32_t JumpConsistentHash(uint64_t key, int32_t num_buckets) {
    int64_t b = -1, j = 0;
    while (j < num_buckets) {
        b = j;
        key = key * 2862933555777941757ULL + 1;
        j = (b + 1) * ((double)(1LL << 31) / ((key >> 33) + 1));
    }
    return b;
}
```

### 2. Maglev Hashing (Google, 2016)

- Lookup table para O(1) acesso
- Mudança mínima quando backends mudam
- Usado em balanceadores de carga do Google

### 3. Rendezvous Hashing (HRW)

- Cada chave calcula score para cada nó
- Escolhe nó com maior score
- O(n) lookup, mas distribuição perfeita

## ⚠️ Considerações de Projeto

### Tratamento de Falhas

1. **Detecção de Falha**: Heartbeats, timeouts
2. **Redistribuição**: Chaves do nó falhado vão para o próximo no anel
3. **Recuperação**: Quando nó volta, chaves retornam automaticamente

### Replicação

Estratégia de preferência (preference list):
- Replicar chave nos próximos N nós no anel
- Evitar réplicas no mesmo rack físico

### Hot Spots

Mesmo com consistent hashing, hot spots podem ocorrer:
- Soluções: Caching local, rate limiting, virtual nodes dinâmicos

## 📖 Referências Bibliográficas

1. **Karger, D., Lehman, E., Leighton, T., et al.** (1997). Consistent Hashing and Random Trees: Distributed Caching Protocols for Relieving Hot Spots on the World Wide Web. *Proceedings of STOC*, 654-663.

2. **DeCandia, G., Hastorun, D., et al.** (2007). Dynamo: Amazon's Highly Available Key-value Store. *SOSP*, 205-220.

3. **Lakshman, A., & Malik, P.** (2010). Cassandra: A Decentralized Structured Storage System. *ACM SIGOPS Operating Systems Review*, 44(2), 35-40.

4. **Lamping, J., & Veach, E.** (2014). A Fast, Minimal Memory, Consistent Hash Algorithm. *arXiv:1406.2294*.

5. **Eisenbud, D. E., et al.** (2016). Maglev: A Fast and Reliable Software Network Load Balancer. *NSDI*, 523-535.

## 🔗 Navegação

← **[02-algoritmo-divisao-conquista](../02-algoritmo-divisao-conquista/)**: Divisão e Conquista

→ **[04-hash-table-avancada](../04-hash-table-avancada/)**: Tabelas Hash Avançadas

---

*Este material faz parte do curso de Estrutura de Dados em C.*
