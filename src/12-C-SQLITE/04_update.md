# Exemplo 4: UPDATE - Atualizando Dados

## 📋 Objetivo

Este exemplo demonstra como **atualizar dados** em SQLite usando C. UPDATE é usado para modificar registros existentes.

## 🎯 O que você vai aprender

- Atualizar registros com `UPDATE`
- Usar `WHERE` para especificar registros
- Atualizar com Prepared Statements (seguro)
- Atualizar múltiplos campos
- Fazer UPDATE com cálculos
- Verificar linhas afetadas
- Implementar verificações antes de atualizar

## 📝 Sintaxe Básica do UPDATE

```sql
UPDATE tabela
SET coluna1 = valor1, coluna2 = valor2
WHERE condição;
```

## ⚠️ IMPORTANTE: Sempre use WHERE!

```sql
-- ❌ PERIGO: Atualiza TODOS os registros!
UPDATE produtos SET preco = 0;

-- ✅ CORRETO: Atualiza apenas o produto ID 5
UPDATE produtos SET preco = 99.90 WHERE id = 5;
```

## 🔍 Tipos de UPDATE

### 1. UPDATE de um campo

```sql
UPDATE produtos SET preco = 299.90 WHERE id = 1;
```

### 2. UPDATE de múltiplos campos

```sql
UPDATE produtos 
SET preco = 399.90, estoque = 15 
WHERE id = 2;
```

### 3. UPDATE com cálculo

```sql
-- Aumentar 10% no preço
UPDATE produtos SET preco = preco * 1.10;

-- Reduzir estoque
UPDATE produtos SET estoque = estoque - 1 WHERE id = 3;

-- Aplicar desconto condicional
UPDATE produtos 
SET preco = preco * 0.9 
WHERE estoque > 50;
```

### 4. UPDATE condicional

```sql
-- Atualizar apenas produtos específicos
UPDATE produtos 
SET desconto = 0.15 
WHERE categoria = 'Eletrônicos' AND preco > 1000;
```

## 💻 UPDATE em C

### Método 1: SQL Direto (Não Recomendado)

```c
const char *sql = "UPDATE produtos SET preco = 299.90 WHERE id = 1;";
char *err_msg = NULL;

int rc = sqlite3_exec(db, sql, NULL, NULL, &err_msg);
if (rc != SQLITE_OK) {
    fprintf(stderr, "Erro: %s\n", err_msg);
    sqlite3_free(err_msg);
}

// Verificar quantas linhas foram afetadas
int changes = sqlite3_changes(db);
printf("Linhas atualizadas: %d\n", changes);
```

### Método 2: Prepared Statement (RECOMENDADO)

```c
sqlite3_stmt *stmt;
const char *sql = "UPDATE produtos SET preco = ? WHERE id = ?;";

// Preparar
sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

// Vincular valores
sqlite3_bind_double(stmt, 1, 399.90);  // Novo preço
sqlite3_bind_int(stmt, 2, 5);          // ID do produto

// Executar
if (sqlite3_step(stmt) == SQLITE_DONE) {
    int changes = sqlite3_changes(db);
    printf("Atualizado com sucesso! %d linha(s)\n", changes);
}

// Finalizar
sqlite3_finalize(stmt);
```

### UPDATE com Verificação Prévia

```c
// 1. Verificar se existe
sqlite3_stmt *stmt;
const char *sql_check = "SELECT nome, preco FROM produtos WHERE id = ?;";

sqlite3_prepare_v2(db, sql_check, -1, &stmt, NULL);
sqlite3_bind_int(stmt, 1, produto_id);

if (sqlite3_step(stmt) == SQLITE_ROW) {
    const unsigned char *nome = sqlite3_column_text(stmt, 0);
    double preco_atual = sqlite3_column_double(stmt, 1);
    
    printf("Produto: %s (R$ %.2f)\n", nome, preco_atual);
    sqlite3_finalize(stmt);
    
    // 2. Atualizar
    const char *sql_update = "UPDATE produtos SET preco = ? WHERE id = ?;";
    sqlite3_prepare_v2(db, sql_update, -1, &stmt, NULL);
    sqlite3_bind_double(stmt, 1, novo_preco);
    sqlite3_bind_int(stmt, 2, produto_id);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
} else {
    printf("Produto não encontrado!\n");
    sqlite3_finalize(stmt);
}
```

## 🎓 Funções Úteis

### sqlite3_changes()

Retorna o número de linhas afetadas pela última operação UPDATE/INSERT/DELETE:

```c
int changes = sqlite3_changes(db);
printf("Linhas modificadas: %d\n", changes);
```

**Importante:** Retorna 0 se nenhuma linha foi afetada (WHERE não encontrou registros)

### sqlite3_total_changes()

Retorna o total de mudanças desde que o banco foi aberto:

```c
int total = sqlite3_total_changes(db);
printf("Total de mudanças: %d\n", total);
```

## 💡 Padrões Comuns de UPDATE

### Aumentar/Diminuir Valor

```sql
-- Aumentar preço em 10%
UPDATE produtos SET preco = preco * 1.10;

-- Adicionar ao estoque
UPDATE produtos SET estoque = estoque + 50 WHERE id = 1;

-- Remover do estoque
UPDATE produtos SET estoque = estoque - 1 WHERE id = 2;
```

### UPDATE com CASE (condicional)

```sql
UPDATE produtos
SET desconto = CASE
    WHEN preco > 1000 THEN 0.15
    WHEN preco > 500 THEN 0.10
    ELSE 0.05
END;
```

### UPDATE baseado em subconsulta

```sql
-- Atualizar preço para a média
UPDATE produtos
SET preco = (SELECT AVG(preco) FROM produtos)
WHERE id = 5;
```

## 💻 Compilação e Execução

```bash
# Compilar
gcc 04_update.c -o 04_update -lsqlite3

# Executar
./04_update
```

## 🎓 Exercícios Práticos

1. **Fácil**: Crie uma função que aumente o preço de todos os produtos de uma categoria

2. **Médio**: Implemente um sistema de "ajuste de estoque" que permita adicionar ou remover unidades

3. **Avançado**: Crie um sistema de "reajuste automático" que aumente preços com base na inflação

## 💡 Dicas Importantes

1. ✅ **Sempre use WHERE** para evitar atualizar todos os registros
2. ✅ **Verifique sqlite3_changes()** para confirmar que atualizou o esperado
3. ✅ **Use Prepared Statements** para segurança
4. ✅ **Faça backup** antes de UPDATE em produção
5. ✅ **Teste em desenvolvimento** antes de produção
6. ⚠️ **UPDATE é imediato** - não há "desfazer"
7. ⚠️ **Sem WHERE = atualiza TUDO!**

## ⚠️ Erros Comuns

### Atualizar sem WHERE

```sql
-- ❌ PERIGO: Atualiza TODOS os produtos!
UPDATE produtos SET preco = 0;
```

**Solução:** Sempre inclua WHERE

### Esquecer de verificar o retorno

```c
// ❌ Não verifica se funcionou
sqlite3_step(stmt);

// ✅ Verifica o retorno
if (sqlite3_step(stmt) == SQLITE_DONE) {
    printf("Sucesso!\n");
} else {
    fprintf(stderr, "Erro: %s\n", sqlite3_errmsg(db));
}
```

## 🔗 Próximos Passos

- **Exemplo 5**: DELETE - Deletar dados
- **Exemplo 6**: JOINs - Relacionar tabelas
- **Exemplo 7**: Transações - Operações atômicas

## 📚 Referências

- [SQLite UPDATE](https://www.sqlite.org/lang_update.html)
- [sqlite3_changes()](https://www.sqlite.org/c3ref/changes.html)
