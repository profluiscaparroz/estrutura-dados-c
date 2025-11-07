# Exemplo 1: CREATE TABLE - Criando Tabelas em SQLite

## 📋 Objetivo

Este exemplo demonstra como **criar tabelas** em SQLite usando C. É o primeiro passo para qualquer aplicação que use banco de dados.

## 🎯 O que você vai aprender

- Como conectar ao banco de dados SQLite
- Como criar tabelas com `CREATE TABLE`
- Definir tipos de dados (INTEGER, TEXT, REAL)
- Usar constraints: PRIMARY KEY, NOT NULL, UNIQUE, CHECK, DEFAULT
- Verificar tabelas criadas
- Visualizar estrutura das tabelas

## 📝 Conceitos Importantes

### CREATE TABLE

O comando `CREATE TABLE` cria uma nova tabela no banco de dados:

```sql
CREATE TABLE nome_tabela (
    coluna1 tipo constraints,
    coluna2 tipo constraints,
    ...
);
```

### Tipos de Dados em SQLite

| Tipo | Descrição | Exemplo em C |
|------|-----------|--------------|
| **INTEGER** | Número inteiro | `int`, `long` |
| **REAL** | Número com decimais | `double`, `float` |
| **TEXT** | Texto/String | `char*` |
| **BLOB** | Dados binários | `void*` |
| **NULL** | Valor nulo | `NULL` |

### Constraints (Restrições)

| Constraint | Significado | Exemplo |
|------------|-------------|---------|
| **PRIMARY KEY** | Identifica unicamente cada linha | `id INTEGER PRIMARY KEY` |
| **AUTOINCREMENT** | Gera valores automaticamente | `id INTEGER PRIMARY KEY AUTOINCREMENT` |
| **NOT NULL** | Campo obrigatório | `nome TEXT NOT NULL` |
| **UNIQUE** | Valor deve ser único | `email TEXT UNIQUE` |
| **DEFAULT** | Valor padrão | `quantidade INTEGER DEFAULT 0` |
| **CHECK** | Valida condição | `idade INTEGER CHECK(idade >= 18)` |

## 🔍 Estrutura do Código

### 1. Incluir biblioteca SQLite

```c
#include <sqlite3.h>
```

### 2. Abrir conexão

```c
sqlite3 *db;
int rc = sqlite3_open("exemplo01.db", &db);
```

- Se o arquivo não existir, SQLite cria automaticamente
- Sempre verificar se `rc == SQLITE_OK`

### 3. Criar tabela

```c
const char *sql = 
    "CREATE TABLE IF NOT EXISTS produtos ("
    "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
    "    nome TEXT NOT NULL,"
    "    preco REAL NOT NULL,"
    "    quantidade INTEGER DEFAULT 0"
    ");";

rc = sqlite3_exec(db, sql, NULL, NULL, &err_msg);
```

### 4. Fechar conexão

```c
sqlite3_close(db);
```

## 💻 Compilação e Execução

```bash
# Compilar
gcc 01_create_table.c -o 01_create_table -lsqlite3

# Executar
./01_create_table
```

## 📊 Saída Esperada

```
=== EXEMPLO 1: CREATE TABLE ===

1. Abrindo conexão com o banco de dados...
   ✅ Banco de dados aberto com sucesso!

2. Criando tabela 'produtos'...
   ✅ Tabela 'produtos' criada com sucesso!

3. Criando tabela 'clientes' com constraints adicionais...
   ✅ Tabela 'clientes' criada com sucesso!

4. Verificando tabelas criadas no banco de dados...
   Tabelas encontradas:
   - clientes
   - produtos

5. Estrutura da tabela 'produtos':
   ID    Nome                 Tipo       Not Null   Default   
   -------------------------------------------------------------
   0     id                   INTEGER    Não        NULL      
   1     nome                 TEXT       Sim        NULL      
   2     descricao            TEXT       Não        NULL      
   3     preco                REAL       Sim        NULL      
   4     quantidade           INTEGER    Não        0         
```

## 🔧 Explorando o Banco Criado

Após executar o programa, você pode explorar o banco usando o cliente SQLite:

```bash
# Abrir o banco
sqlite3 exemplo01.db

# Listar tabelas
.tables

# Ver estrutura de uma tabela
.schema produtos

# Sair
.quit
```

## 🎓 Exercícios Práticos

1. **Fácil**: Modifique o código para criar uma tabela `categorias` com colunas: `id`, `nome`, `descricao`

2. **Médio**: Adicione uma coluna `data_cadastro` do tipo TEXT com valor DEFAULT 'CURRENT_TIMESTAMP'

3. **Avançado**: Crie uma tabela `pedidos` que relacione com `produtos` usando FOREIGN KEY

## 💡 Dicas Importantes

1. ✅ **Sempre use `IF NOT EXISTS`** para evitar erros ao reexecutar o programa
2. ✅ **Verifique retornos** com `if (rc != SQLITE_OK)`
3. ✅ **Libere memória** de mensagens de erro com `sqlite3_free(err_msg)`
4. ✅ **Feche conexões** com `sqlite3_close(db)` ao terminar
5. ⚠️ **PRIMARY KEY**: Toda tabela deve ter uma (boa prática)
6. ⚠️ **AUTOINCREMENT**: Útil para IDs automáticos

## 🔗 Próximos Passos

Após entender como criar tabelas, veja:
- **Exemplo 2**: INSERT INTO - Inserir dados
- **Exemplo 3**: SELECT - Consultar dados
- **Exemplo 4**: UPDATE - Atualizar dados
- **Exemplo 5**: DELETE - Deletar dados

## 📚 Referências

- [SQLite CREATE TABLE](https://www.sqlite.org/lang_createtable.html)
- [SQLite Datatypes](https://www.sqlite.org/datatype3.html)
- [SQLite C/C++ Interface](https://www.sqlite.org/c3ref/intro.html)
