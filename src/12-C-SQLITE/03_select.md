# Exemplo 3: SELECT - Consultando Dados

## 📋 Objetivo

Este exemplo demonstra como **consultar dados** em SQLite usando C. SELECT é o comando mais utilizado em bancos de dados.

## 🎯 O que você vai aprender

- Selecionar todas as colunas com `SELECT *`
- Selecionar colunas específicas
- Filtrar resultados com `WHERE`
- Ordenar com `ORDER BY`
- Limitar resultados com `LIMIT`
- Usar funções de agregação (`COUNT`, `SUM`, `AVG`, `MIN`, `MAX`)
- Agrupar dados com `GROUP BY`
- Buscar padrões com `LIKE`
- Ler valores das colunas com `sqlite3_column_*`

## 📝 Sintaxe Básica do SELECT

```sql
SELECT colunas
FROM tabela
WHERE condição
ORDER BY coluna [ASC|DESC]
LIMIT número;
```

## 🔍 Tipos de SELECT

### 1. SELECT * (todas as colunas)

```sql
SELECT * FROM produtos;
```

**Uso:** Quando precisa de todos os dados
**Cuidado:** Pode ser lento em tabelas grandes

### 2. SELECT com colunas específicas

```sql
SELECT nome, preco FROM produtos;
```

**Vantagem:** Mais rápido e eficiente
**Recomendação:** Use sempre que possível

### 3. SELECT com WHERE (filtro)

```sql
SELECT * FROM produtos WHERE preco < 300;
SELECT * FROM produtos WHERE categoria = 'Informática';
SELECT * FROM produtos WHERE estoque > 0 AND preco < 500;
```

**Operadores WHERE:**
| Operador | Significado | Exemplo |
|----------|-------------|---------|
| `=` | Igual | `preco = 100` |
| `!=` ou `<>` | Diferente | `categoria != 'Móveis'` |
| `<` | Menor | `preco < 300` |
| `>` | Maior | `estoque > 10` |
| `<=` | Menor ou igual | `preco <= 500` |
| `>=` | Maior ou igual | `estoque >= 5` |
| `AND` | E lógico | `preco < 500 AND estoque > 0` |
| `OR` | OU lógico | `categoria = 'A' OR categoria = 'B'` |
| `IN` | Em lista | `categoria IN ('A', 'B', 'C')` |
| `BETWEEN` | Entre valores | `preco BETWEEN 100 AND 500` |
| `LIKE` | Padrão | `nome LIKE '%Mouse%'` |
| `IS NULL` | É nulo | `descricao IS NULL` |
| `IS NOT NULL` | Não é nulo | `descricao IS NOT NULL` |

### 4. SELECT com ORDER BY (ordenação)

```sql
SELECT * FROM produtos ORDER BY preco ASC;   -- Crescente
SELECT * FROM produtos ORDER BY preco DESC;  -- Decrescente
SELECT * FROM produtos ORDER BY categoria, nome;  -- Múltiplas colunas
```

### 5. SELECT com LIMIT (limitar resultados)

```sql
SELECT * FROM produtos LIMIT 10;              -- Primeiros 10
SELECT * FROM produtos ORDER BY preco DESC LIMIT 5;  -- Top 5 mais caros
SELECT * FROM produtos LIMIT 10 OFFSET 20;    -- Pular 20, pegar 10 (paginação)
```

## 📊 Funções de Agregação

### COUNT - Contar registros

```c
// SQL: SELECT COUNT(*) FROM produtos;
sqlite3_stmt *stmt;
sqlite3_prepare_v2(db, "SELECT COUNT(*) FROM produtos;", -1, &stmt, NULL);
if (sqlite3_step(stmt) == SQLITE_ROW) {
    int total = sqlite3_column_int(stmt, 0);
    printf("Total: %d\n", total);
}
sqlite3_finalize(stmt);
```

### SUM - Somar valores

```sql
SELECT SUM(preco) FROM produtos;              -- Soma dos preços
SELECT SUM(preco * estoque) FROM produtos;    -- Valor total do inventário
```

### AVG - Média

```sql
SELECT AVG(preco) FROM produtos;              -- Preço médio
SELECT AVG(estoque) FROM produtos;            -- Estoque médio
```

### MIN e MAX - Mínimo e Máximo

```sql
SELECT MIN(preco), MAX(preco) FROM produtos;  -- Menor e maior preço
```

### GROUP BY - Agrupar resultados

```sql
-- Contar produtos por categoria
SELECT categoria, COUNT(*) as total
FROM produtos
GROUP BY categoria;

-- Soma do estoque por categoria
SELECT categoria, SUM(estoque)
FROM produtos
GROUP BY categoria;
```

## 💻 Lendo Valores das Colunas

```c
while (sqlite3_step(stmt) == SQLITE_ROW) {
    // Índice começa em 0!
    int id = sqlite3_column_int(stmt, 0);
    const unsigned char *nome = sqlite3_column_text(stmt, 1);
    double preco = sqlite3_column_double(stmt, 2);
    
    // Verificar se valor é NULL
    if (sqlite3_column_type(stmt, 3) == SQLITE_NULL) {
        printf("Valor é NULL\n");
    }
    
    // Obter tamanho do texto
    int tamanho = sqlite3_column_bytes(stmt, 1);
}
```

### Funções sqlite3_column_*

| Função | Tipo Retornado | Uso |
|--------|----------------|-----|
| `sqlite3_column_int()` | `int` | Números inteiros |
| `sqlite3_column_int64()` | `sqlite3_int64` | Inteiros grandes |
| `sqlite3_column_double()` | `double` | Números decimais |
| `sqlite3_column_text()` | `const unsigned char*` | Texto/strings |
| `sqlite3_column_blob()` | `const void*` | Dados binários |
| `sqlite3_column_bytes()` | `int` | Tamanho em bytes |
| `sqlite3_column_type()` | `int` | Tipo da coluna (SQLITE_INTEGER, SQLITE_TEXT, etc.) |

## 🔍 LIKE - Busca por Padrão

```sql
-- % = qualquer sequência de caracteres
SELECT * FROM produtos WHERE nome LIKE '%Mouse%';    -- Contém "Mouse"
SELECT * FROM produtos WHERE nome LIKE 'Mouse%';     -- Começa com "Mouse"
SELECT * FROM produtos WHERE nome LIKE '%Mouse';     -- Termina com "Mouse"

-- _ = um único caractere
SELECT * FROM produtos WHERE codigo LIKE 'A___';     -- A seguido de 3 caracteres
```

**Exemplo em C:**

```c
sqlite3_stmt *stmt;
const char *sql = "SELECT nome FROM produtos WHERE nome LIKE ?;";
sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

// Buscar produtos que contenham "Mouse"
sqlite3_bind_text(stmt, 1, "%Mouse%", -1, SQLITE_TRANSIENT);

while (sqlite3_step(stmt) == SQLITE_ROW) {
    const unsigned char *nome = sqlite3_column_text(stmt, 0);
    printf("%s\n", nome);
}
sqlite3_finalize(stmt);
```

## 💻 Compilação e Execução

```bash
# Compilar
gcc 03_select.c -o 03_select -lsqlite3

# Executar
./03_select
```

## 🎓 Exercícios Práticos

1. **Fácil**: Modifique para listar apenas produtos com estoque acima de 15 unidades

2. **Médio**: Crie uma consulta que mostre os 3 produtos mais baratos de cada categoria

3. **Avançado**: Implemente uma função de busca que aceite múltiplos filtros (categoria, faixa de preço, estoque mínimo)

## 💡 Dicas Importantes

1. ✅ **Sempre use WHERE parametrizado** para segurança
2. ✅ **Índice das colunas começa em 0**, não em 1
3. ✅ **Verifique SQLITE_ROW** antes de ler valores
4. ✅ **Use SELECT com colunas específicas** ao invés de SELECT *
5. ✅ **Crie índices** para colunas frequentemente filtradas/ordenadas
6. ⚠️ **LIKE é case-insensitive** por padrão no SQLite
7. ⚠️ **TEXT retornado é const**, não modifique

## 🔗 Próximos Passos

- **Exemplo 4**: UPDATE - Atualizar dados
- **Exemplo 5**: DELETE - Deletar dados
- **Exemplo 6**: JOINs - Relacionar tabelas

## 📚 Referências

- [SQLite SELECT](https://www.sqlite.org/lang_select.html)
- [Aggregate Functions](https://www.sqlite.org/lang_aggfunc.html)
- [Column Functions](https://www.sqlite.org/c3ref/column_blob.html)
