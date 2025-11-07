# Exemplo 2: INSERT INTO - Inserindo Dados

## 📋 Objetivo

Este exemplo demonstra como **inserir dados** em tabelas SQLite usando C. Após criar tabelas, precisamos populá-las com informações.

## 🎯 O que você vai aprender

- Como inserir dados com `INSERT INTO`
- Usar **Prepared Statements** para segurança
- Vincular valores com `sqlite3_bind_*`
- Inserir múltiplos registros eficientemente
- Usar **transações** para melhor performance
- Obter o ID do registro inserido

## 📝 Conceitos Importantes

### INSERT INTO

Existem duas sintaxes principais:

```sql
-- Especificar colunas (RECOMENDADO)
INSERT INTO produtos (nome, preco, quantidade) 
VALUES ('Mouse', 25.90, 10);

-- Todas as colunas na ordem (não recomendado)
INSERT INTO produtos 
VALUES (NULL, 'Mouse', 'Mouse USB', 25.90, 10);
```

### Prepared Statements vs SQL Direto

| Aspecto | SQL Direto | Prepared Statement |
|---------|-----------|-------------------|
| **Segurança** | ❌ Vulnerável a SQL Injection | ✅ Seguro |
| **Performance** | ⚠️ Compila a cada execução | ✅ Compila uma vez |
| **Reuso** | ❌ Não reutilizável | ✅ Reutilizável |
| **Código** | ⚠️ Concatenação de strings | ✅ Limpo e legível |

#### Exemplo de SQL Injection (VULNERÁVEL):

```c
// ❌ NUNCA FAÇA ISSO!
char sql[256];
sprintf(sql, "INSERT INTO users (name) VALUES ('%s');", user_input);
// Se user_input = "'); DROP TABLE users; --"
// SQL resultante: INSERT INTO users (name) VALUES (''); DROP TABLE users; --');
```

#### Solução com Prepared Statement (SEGURO):

```c
// ✅ SEGURO
const char *sql = "INSERT INTO users (name) VALUES (?);";
sqlite3_stmt *stmt;
sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
sqlite3_bind_text(stmt, 1, user_input, -1, SQLITE_TRANSIENT);
sqlite3_step(stmt);
sqlite3_finalize(stmt);
```

## 🔍 Métodos de Inserção

### Método 1: INSERT Simples (Não Recomendado)

```c
const char *sql = 
    "INSERT INTO produtos (nome, preco) "
    "VALUES ('Notebook', 2999.90);";
    
sqlite3_exec(db, sql, NULL, NULL, &err_msg);
```

**Problemas:**
- ❌ Vulnerável a SQL Injection
- ❌ Dificulta valores dinâmicos
- ❌ Menor performance

### Método 2: Prepared Statement (RECOMENDADO)

```c
// 1. Preparar
const char *sql = "INSERT INTO produtos (nome, preco) VALUES (?, ?);";
sqlite3_stmt *stmt;
sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

// 2. Vincular valores
sqlite3_bind_text(stmt, 1, "Notebook", -1, SQLITE_TRANSIENT);
sqlite3_bind_double(stmt, 2, 2999.90);

// 3. Executar
sqlite3_step(stmt);

// 4. Finalizar
sqlite3_finalize(stmt);
```

**Vantagens:**
- ✅ Seguro contra SQL Injection
- ✅ Valores dinâmicos fáceis
- ✅ Melhor performance
- ✅ Código mais limpo

### Método 3: Inserção em Lote com Transação

```c
// Iniciar transação
sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, NULL);

// Preparar statement uma vez
sqlite3_stmt *stmt;
const char *sql = "INSERT INTO produtos (nome, preco) VALUES (?, ?);";
sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

// Inserir múltiplos registros
for (int i = 0; i < 1000; i++) {
    sqlite3_reset(stmt);  // Limpar bindings anteriores
    sqlite3_bind_text(stmt, 1, produtos[i].nome, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 2, produtos[i].preco);
    sqlite3_step(stmt);
}

sqlite3_finalize(stmt);

// Confirmar transação
sqlite3_exec(db, "COMMIT;", NULL, NULL, NULL);
```

**Performance:**
- Sem transação: ~1.000 inserções/segundo
- Com transação: ~10.000+ inserções/segundo
- **Speedup: 10-100x mais rápido!**

## 💻 Funções sqlite3_bind_*

### Tipos de bind disponíveis:

```c
// Texto (string)
sqlite3_bind_text(stmt, index, valor, length, destructor);

// Número inteiro
sqlite3_bind_int(stmt, index, valor);
sqlite3_bind_int64(stmt, index, valor);

// Número decimal
sqlite3_bind_double(stmt, index, valor);

// NULL
sqlite3_bind_null(stmt, index);

// Dados binários (BLOB)
sqlite3_bind_blob(stmt, index, data, size, destructor);
```

### Parâmetros importantes:

- **index**: Posição do placeholder (começa em 1, não 0!)
- **destructor**: 
  - `SQLITE_TRANSIENT`: SQLite copia o valor (use para strings locais)
  - `SQLITE_STATIC`: SQLite não copia (use para strings constantes)

## 🎓 Funções Úteis

### Obter ID do registro inserido

```c
long long id = sqlite3_last_insert_rowid(db);
printf("ID gerado: %lld\n", id);
```

### Resetar statement para reuso

```c
sqlite3_reset(stmt);  // Limpa bindings
sqlite3_clear_bindings(stmt);  // Limpa todos os bindings explicitamente
```

### Verificar número de mudanças

```c
int changes = sqlite3_changes(db);
printf("Linhas afetadas: %d\n", changes);
```

## 💻 Compilação e Execução

```bash
# Compilar
gcc 02_insert.c -o 02_insert -lsqlite3

# Executar
./02_insert
```

## 📊 Saída Esperada

```
=== EXEMPLO 2: INSERT INTO ===

✅ Banco de dados aberto
✅ Tabela criada/verificada

=== MÉTODO 1: INSERT SIMPLES (NÃO RECOMENDADO) ===

✅ Produto inserido com sucesso!
   ID gerado: 1

=== MÉTODO 2: PREPARED STATEMENT (RECOMENDADO) ===

✅ Produto 'Impressora' inserido com sucesso!
   ID gerado: 2
✅ Produto 'Scanner' inserido com sucesso!
   ID gerado: 3

=== MÉTODO 3: INSERÇÃO EM LOTE COM TRANSAÇÃO ===

Iniciando inserção de 5 produtos...

  ✓ Mouse USB - R$ 25.90
  ✓ Teclado Mecânico - R$ 299.90
  ✓ Monitor 24" - R$ 799.90
  ✓ Webcam HD - R$ 189.90
  ✓ Headset Gamer - R$ 149.90

✅ 5 produtos inseridos com sucesso!

=== PRODUTOS CADASTRADOS ===

ID   Nome                          Preço         Qtd
---- ------------------------- ------------ ----------
1    Notebook                  R$   2999.90         10
2    Impressora                R$    399.90          8
3    Scanner                   R$    199.90         12
...
```

## 🎓 Exercícios Práticos

1. **Fácil**: Modifique o código para inserir 3 produtos de sua escolha

2. **Médio**: Crie uma função que leia dados do usuário (teclado) e insira no banco

3. **Avançado**: Implemente um sistema que leia produtos de um arquivo CSV e insira no banco usando transações

## 💡 Dicas Importantes

1. ✅ **Sempre use Prepared Statements** em código de produção
2. ✅ **Use transações** para inserções em lote (muito mais rápido)
3. ✅ **Sempre finalize statements** com `sqlite3_finalize()`
4. ✅ **Verifique retornos**: `SQLITE_DONE` para INSERT bem-sucedido
5. ⚠️ **Índice dos placeholders começa em 1**, não em 0!
6. ⚠️ **SQLITE_TRANSIENT vs SQLITE_STATIC**: escolha corretamente

## ⚠️ Erros Comuns

### Erro: "UNIQUE constraint failed"

```
Causa: Tentou inserir valor duplicado em coluna UNIQUE
Solução: Verifique se o valor já existe antes de inserir
```

### Erro: "NOT NULL constraint failed"

```
Causa: Tentou inserir NULL em coluna NOT NULL
Solução: Forneça valor para todas as colunas obrigatórias
```

### Erro: Bind index out of range

```
Causa: Índice do bind está errado
Solução: Verifique se índice começa em 1 e corresponde aos placeholders
```

## 🔗 Próximos Passos

Após dominar INSERT, veja:
- **Exemplo 3**: SELECT - Consultar dados
- **Exemplo 4**: UPDATE - Atualizar dados
- **Exemplo 5**: DELETE - Deletar dados

## 📚 Referências

- [SQLite INSERT](https://www.sqlite.org/lang_insert.html)
- [Prepared Statements](https://www.sqlite.org/c3ref/prepare.html)
- [Binding Values](https://www.sqlite.org/c3ref/bind_blob.html)
- [Transactions](https://www.sqlite.org/lang_transaction.html)
