# Exemplo 6: JOINs - Relacionando Tabelas

## 📋 Objetivo

Este exemplo demonstra como **relacionar múltiplas tabelas** usando JOINs. É essencial para trabalhar com dados estruturados em bancos de dados relacionais.

## 🎯 O que você vai aprender

- Criar tabelas relacionadas com Foreign Keys
- Usar INNER JOIN para combinar tabelas
- Usar LEFT JOIN para incluir registros sem correspondência
- Realizar consultas complexas com múltiplos JOINs
- Combinar JOINs com agregações
- Usar aliases de tabelas

## 📝 Conceitos Fundamentais

### Foreign Key (Chave Estrangeira)

Uma chave estrangeira é uma coluna que referencia a chave primária de outra tabela, criando um relacionamento:

```sql
CREATE TABLE produtos (
    id INTEGER PRIMARY KEY,
    nome TEXT,
    categoria_id INTEGER,
    FOREIGN KEY (categoria_id) REFERENCES categorias(id)
);
```

### Tipos de JOIN

| Tipo | Descrição | Uso |
|------|-----------|-----|
| **INNER JOIN** | Retorna apenas registros que existem em AMBAS tabelas | Dados relacionados obrigatórios |
| **LEFT JOIN** | Retorna TODOS da esquerda + correspondentes da direita | Incluir registros sem relacionamento |
| **RIGHT JOIN** | (Não suportado no SQLite) Use LEFT JOIN invertendo tabelas | - |
| **CROSS JOIN** | Produto cartesiano (todas combinações) | Raramente usado |

## 🔍 INNER JOIN

Retorna apenas linhas onde há correspondência em ambas as tabelas:

```sql
SELECT produtos.nome, categorias.nome AS categoria
FROM produtos
INNER JOIN categorias ON produtos.categoria_id = categorias.id;
```

**Diagrama Visual:**
```
Tabela A    INNER JOIN    Tabela B
   ╔═══╗         ╔═══╗
   ║   ║         ║   ║
   ║ A ╠═══════╗ ║   ║
   ║   ║       ║ ║   ║
   ╚═══╝       ╚═╬═══╣
                 ║ B ║
                 ╚═══╝
         Retorna apenas A∩B
```

### Exemplo em C:

```c
sqlite3_stmt *stmt;
const char *sql = 
    "SELECT p.nome AS produto, c.nome AS categoria "
    "FROM produtos p "
    "INNER JOIN categorias c ON p.categoria_id = c.id;";

sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

while (sqlite3_step(stmt) == SQLITE_ROW) {
    const unsigned char *produto = sqlite3_column_text(stmt, 0);
    const unsigned char *categoria = sqlite3_column_text(stmt, 1);
    printf("%s - %s\n", produto, categoria);
}

sqlite3_finalize(stmt);
```

## 🔍 LEFT JOIN

Retorna TODAS as linhas da tabela esquerda, mesmo sem correspondência na direita:

```sql
SELECT categorias.nome, COUNT(produtos.id) AS total
FROM categorias
LEFT JOIN produtos ON categorias.id = produtos.categoria_id
GROUP BY categorias.id;
```

**Diagrama Visual:**
```
Tabela A    LEFT JOIN    Tabela B
   ╔═══╗         ╔═══╗
   ║   ║         ║   ║
   ║ A ╠═══════╗ ║   ║
   ║   ║       ║ ║   ║
   ╚═══╝       ╚═╬═══╣
                 ║ B ║
                 ╚═══╝
         Retorna A + A∩B
```

**Quando usar LEFT JOIN:**
- Listar todas as categorias, mesmo as sem produtos
- Listar todos os clientes, mesmo os sem pedidos
- Relatórios que precisam incluir dados "vazios"

## 🔍 Múltiplos JOINs

Você pode combinar várias tabelas em uma única consulta:

```sql
SELECT 
    cli.nome AS cliente,
    prod.nome AS produto,
    cat.nome AS categoria
FROM pedidos ped
INNER JOIN clientes cli ON ped.cliente_id = cli.id
INNER JOIN produtos prod ON ped.produto_id = prod.id
INNER JOIN categorias cat ON prod.categoria_id = cat.id;
```

**Estrutura:**
```
pedidos → clientes (cliente_id)
       → produtos (produto_id) → categorias (categoria_id)
```

## 💻 Aliases de Tabelas

Use aliases (AS) para queries mais legíveis:

```sql
-- Sem alias (verboso)
SELECT produtos.nome, categorias.nome
FROM produtos
INNER JOIN categorias ON produtos.categoria_id = categorias.id;

-- Com alias (limpo)
SELECT p.nome, c.nome
FROM produtos p
INNER JOIN categorias c ON p.categoria_id = c.id;
```

## 🎓 Padrões Comuns

### 1. Lista de Produtos com Categoria

```sql
SELECT p.nome, p.preco, c.nome AS categoria
FROM produtos p
INNER JOIN categorias c ON p.categoria_id = c.id
ORDER BY c.nome, p.nome;
```

### 2. Contagem por Categoria

```sql
SELECT c.nome, COUNT(p.id) AS total
FROM categorias c
LEFT JOIN produtos p ON c.id = p.categoria_id
GROUP BY c.id, c.nome;
```

### 3. Pedidos com Detalhes Completos

```sql
SELECT 
    cli.nome AS cliente,
    prod.nome AS produto,
    ped.quantidade,
    (ped.quantidade * prod.preco) AS total
FROM pedidos ped
INNER JOIN clientes cli ON ped.cliente_id = cli.id
INNER JOIN produtos prod ON ped.produto_id = prod.id;
```

### 4. Top Clientes por Valor

```sql
SELECT 
    c.nome,
    SUM(ped.quantidade * p.preco) AS valor_total
FROM clientes c
INNER JOIN pedidos ped ON c.id = ped.cliente_id
INNER JOIN produtos p ON ped.produto_id = p.id
GROUP BY c.id, c.nome
ORDER BY valor_total DESC
LIMIT 10;
```

## 💡 Habilitar Foreign Keys no SQLite

Por padrão, foreign keys estão **desabilitadas** no SQLite:

```c
// Habilitar foreign keys
sqlite3_exec(db, "PRAGMA foreign_keys = ON;", NULL, NULL, NULL);
```

**Importante:** Faça isso logo após abrir o banco!

## 💻 Compilação e Execução

```bash
# Compilar
gcc 06_joins.c -o 06_joins -lsqlite3

# Executar
./06_joins
```

## 🎓 Exercícios Práticos

1. **Fácil**: Crie uma consulta que liste produtos sem categoria (use LEFT JOIN)

2. **Médio**: Implemente um relatório de vendas por mês usando JOINs

3. **Avançado**: Crie um sistema de tags onde produtos podem ter múltiplas tags (relação N:N)

## 💡 Dicas Importantes

1. ✅ **Use aliases** para queries mais legíveis
2. ✅ **INNER JOIN quando dados obrigatórios**, LEFT JOIN quando opcionais
3. ✅ **Habilite Foreign Keys** com PRAGMA
4. ✅ **Crie índices** em colunas de foreign keys para performance
5. ⚠️ **Cuidado com múltiplos JOINs** - pode ficar lento
6. ⚠️ **LEFT JOIN pode retornar NULL** - trate adequadamente

## 🔗 Diferença entre INNER e LEFT JOIN

```sql
-- Dados exemplo:
Categorias: [1: Eletrônicos, 2: Livros, 3: Roupas]
Produtos: [
  {nome: "TV", categoria_id: 1},
  {nome: "Mouse", categoria_id: 1},
  {nome: "Livro C", categoria_id: 2}
]

-- INNER JOIN: retorna 3 produtos (apenas os que têm categoria)
-- LEFT JOIN (categorias left): retorna 3 linhas
--   - 2 produtos de Eletrônicos
--   - 1 produto de Livros
--   - 0 produtos de Roupas (mas categoria aparece com NULL em produto)
```

## 📚 Referências

- [SQLite INNER JOIN](https://www.sqlite.org/lang_select.html#simpleselect)
- [SQLite Foreign Keys](https://www.sqlite.org/foreignkeys.html)
- [PRAGMA foreign_keys](https://www.sqlite.org/pragma.html#pragma_foreign_keys)
