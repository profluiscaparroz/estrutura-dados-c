# Exemplo 5: DELETE - Deletando Dados

## 📋 Objetivo

Este exemplo demonstra como **deletar dados** em SQLite usando C. DELETE remove registros permanentemente do banco de dados.

## ⚠️ ATENÇÃO: DELETE É IRREVERSÍVEL!

**Sempre faça backup antes de deletar dados importantes!**

## 🎯 O que você vai aprender

- Deletar registros com `DELETE FROM`
- Usar `WHERE` para especificar registros
- Deletar com Prepared Statements (seguro)
- Deletar com múltiplas condições
- Implementar confirmação antes de deletar
- Soft delete (desativação ao invés de deletar)
- Verificar linhas deletadas

## 📝 Sintaxe Básica do DELETE

```sql
DELETE FROM tabela
WHERE condição;
```

## ⚠️ PERIGO: DELETE sem WHERE!

```sql
-- ❌ PERIGO: Deleta TODOS os registros!
DELETE FROM produtos;

-- ✅ CORRETO: Deleta apenas o produto ID 5
DELETE FROM produtos WHERE id = 5;
```

**Sem WHERE, TODOS os registros são deletados!**

## 🔍 Tipos de DELETE

### 1. DELETE por ID

```sql
DELETE FROM produtos WHERE id = 10;
```

### 2. DELETE com condição simples

```sql
DELETE FROM produtos WHERE estoque = 0;
DELETE FROM produtos WHERE preco < 10;
```

### 3. DELETE com múltiplas condições

```sql
-- AND: ambas condições devem ser verdadeiras
DELETE FROM produtos 
WHERE estoque = 0 AND ativo = 0;

-- OR: pelo menos uma condição deve ser verdadeira
DELETE FROM produtos 
WHERE categoria = 'Descontinuado' OR preco < 5;
```

### 4. DELETE baseado em subconsulta

```sql
-- Deletar produtos com preço acima da média
DELETE FROM produtos 
WHERE preco > (SELECT AVG(preco) FROM produtos);
```

### 5. DELETE com IN

```sql
-- Deletar múltiplos IDs
DELETE FROM produtos 
WHERE id IN (1, 5, 10, 15);

-- Deletar múltiplas categorias
DELETE FROM produtos 
WHERE categoria IN ('Antigo', 'Descontinuado');
```

## 💻 DELETE em C

### Método 1: SQL Direto

```c
const char *sql = "DELETE FROM produtos WHERE id = 5;";
char *err_msg = NULL;

int rc = sqlite3_exec(db, sql, NULL, NULL, &err_msg);
if (rc != SQLITE_OK) {
    fprintf(stderr, "Erro: %s\n", err_msg);
    sqlite3_free(err_msg);
} else {
    int changes = sqlite3_changes(db);
    printf("%d linha(s) deletada(s)\n", changes);
}
```

### Método 2: Prepared Statement (RECOMENDADO)

```c
sqlite3_stmt *stmt;
const char *sql = "DELETE FROM produtos WHERE id = ?;";

// Preparar
sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

// Vincular ID
sqlite3_bind_int(stmt, 1, produto_id);

// Executar
if (sqlite3_step(stmt) == SQLITE_DONE) {
    int changes = sqlite3_changes(db);
    printf("Deletado! %d linha(s)\n", changes);
}

// Finalizar
sqlite3_finalize(stmt);
```

### DELETE com Confirmação

```c
// 1. Contar quantos serão deletados
sqlite3_stmt *stmt;
const char *sql_count = "SELECT COUNT(*) FROM produtos WHERE estoque = 0;";

sqlite3_prepare_v2(db, sql_count, -1, &stmt, NULL);
sqlite3_step(stmt);
int count = sqlite3_column_int(stmt, 0);
sqlite3_finalize(stmt);

if (count > 0) {
    printf("%d produto(s) será(ão) deletado(s).\n", count);
    printf("Confirma? (s/n): ");
    
    char resposta;
    scanf(" %c", &resposta);
    
    if (resposta == 's' || resposta == 'S') {
        // 2. Deletar
        const char *sql_delete = "DELETE FROM produtos WHERE estoque = 0;";
        char *err_msg = NULL;
        
        if (sqlite3_exec(db, sql_delete, NULL, NULL, &err_msg) == SQLITE_OK) {
            printf("Deletado com sucesso!\n");
        }
    } else {
        printf("Operação cancelada.\n");
    }
}
```

## 🛡️ Soft Delete (Alternativa Segura)

Ao invés de deletar permanentemente, **marque como inativo**:

```sql
-- Adicionar coluna 'ativo' na tabela
ALTER TABLE produtos ADD COLUMN ativo INTEGER DEFAULT 1;

-- Soft delete: marcar como inativo
UPDATE produtos SET ativo = 0 WHERE id = 5;

-- Consultar apenas ativos
SELECT * FROM produtos WHERE ativo = 1;
```

### Vantagens do Soft Delete:

| Aspecto | Hard Delete | Soft Delete |
|---------|-------------|-------------|
| **Recuperação** | ❌ Impossível | ✅ Possível |
| **Histórico** | ❌ Perdido | ✅ Mantido |
| **Auditoria** | ❌ Sem rastro | ✅ Rastreável |
| **Performance** | ✅ Melhor | ⚠️ Ligeiramente pior |

### Implementação em C:

```c
// Soft delete
const char *sql = "UPDATE produtos SET ativo = 0 WHERE id = ?;";
sqlite3_stmt *stmt;
sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
sqlite3_bind_int(stmt, 1, produto_id);
sqlite3_step(stmt);
sqlite3_finalize(stmt);

printf("Produto desativado (soft delete)\n");
printf("Dados preservados, apenas marcado como inativo\n");
```

## 🎓 Funções Úteis

### sqlite3_changes()

```c
int changes = sqlite3_changes(db);
printf("Linhas deletadas: %d\n", changes);
```

- Retorna 0 se nenhuma linha foi deletada
- Útil para verificar se o DELETE encontrou registros

## 💡 Estratégias de Segurança

### 1. Backup antes de deletar

```bash
# Fazer backup do banco
cp biblioteca.db biblioteca_backup.db
```

### 2. Usar transações

```c
// Iniciar transação
sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, NULL);

// Deletar
const char *sql = "DELETE FROM produtos WHERE categoria = 'Teste';";
if (sqlite3_exec(db, sql, NULL, NULL, &err_msg) == SQLITE_OK) {
    // Confirmar se tudo OK
    sqlite3_exec(db, "COMMIT;", NULL, NULL, NULL);
} else {
    // Desfazer se houver erro
    sqlite3_exec(db, "ROLLBACK;", NULL, NULL, NULL);
}
```

### 3. Verificar antes de deletar

```c
// 1. Listar o que será deletado
SELECT * FROM produtos WHERE condicao;

// 2. Se OK, então deletar
DELETE FROM produtos WHERE condicao;
```

### 4. Limitar o número de deleções

```sql
-- SQLite não suporta LIMIT diretamente em DELETE
-- Mas você pode usar subconsulta:
DELETE FROM produtos 
WHERE id IN (
    SELECT id FROM produtos 
    WHERE estoque = 0 
    LIMIT 10
);
```

## 💻 Compilação e Execução

```bash
# Compilar
gcc 05_delete.c -o 05_delete -lsqlite3

# Executar
./05_delete
```

## 🎓 Exercícios Práticos

1. **Fácil**: Crie uma função que delete produtos por categoria

2. **Médio**: Implemente um sistema de "lixeira" onde produtos deletados vão para uma tabela separada

3. **Avançado**: Crie um sistema de "cleanup automático" que deleta registros antigos baseado em data

## 💡 Dicas Importantes

1. ✅ **SEMPRE use WHERE** - sem ele, TUDO é deletado!
2. ✅ **Faça backup** antes de deletar em produção
3. ✅ **Considere soft delete** para manter histórico
4. ✅ **Use transações** para operações críticas
5. ✅ **Teste em desenvolvimento** primeiro
6. ✅ **Implemente confirmação** para operações destrutivas
7. ⚠️ **DELETE é permanente** - não há "Ctrl+Z"
8. ⚠️ **Verifique sqlite3_changes()** para confirmar

## ⚠️ Erros Comuns

### 1. DELETE sem WHERE

```sql
-- ❌ PERIGO!
DELETE FROM produtos;  -- Deleta TUDO!
```

### 2. Não verificar o resultado

```c
// ❌ Não verifica se deletou algo
sqlite3_exec(db, sql, NULL, NULL, NULL);

// ✅ Verifica quantas linhas foram deletadas
sqlite3_exec(db, sql, NULL, NULL, NULL);
int changes = sqlite3_changes(db);
if (changes == 0) {
    printf("Nenhum registro encontrado para deletar\n");
}
```

### 3. Não fazer backup

```
❌ Deletar dados importantes sem backup
✅ Sempre fazer backup antes de operações destrutivas
```

## 🔗 Próximos Passos

- **Exemplo 6**: JOINs - Relacionar tabelas
- **Exemplo 7**: Transações - Operações atômicas
- **Exemplo 8**: Índices - Otimizar consultas

## 📚 Referências

- [SQLite DELETE](https://www.sqlite.org/lang_delete.html)
- [sqlite3_changes()](https://www.sqlite.org/c3ref/changes.html)
- [Best Practices](https://www.sqlite.org/quirks.html)
