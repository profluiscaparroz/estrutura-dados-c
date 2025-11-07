# SQLite em C - Banco de Dados Embarcado

## 📚 Visão Geral

Este módulo demonstra como usar **SQLite**, um banco de dados SQL leve e embarcado, em programas C. SQLite é ideal para aplicações que precisam armazenar dados estruturados de forma persistente sem a complexidade de um servidor de banco de dados completo.

---

## 📂 Índice de Exemplos

Este módulo contém exemplos progressivos que ensinam SQLite do básico ao avançado:

### Exemplos Básicos (CRUD)

1. **[01_create_table](./01_create_table.md)** - Criando tabelas
   - Como criar tabelas com constraints
   - PRIMARY KEY, NOT NULL, UNIQUE, CHECK, DEFAULT
   - Tipos de dados em SQLite

2. **[02_insert](./02_insert.md)** - Inserindo dados
   - INSERT INTO com Prepared Statements
   - Segurança contra SQL Injection
   - Transações para inserções em lote

3. **[03_select](./03_select.md)** - Consultando dados
   - SELECT com WHERE, ORDER BY, LIMIT
   - Funções de agregação (COUNT, SUM, AVG, MIN, MAX)
   - Busca por padrão com LIKE

4. **[04_update](./04_update.md)** - Atualizando dados
   - UPDATE com WHERE
   - Atualizar múltiplos campos
   - UPDATE com cálculos

5. **[05_delete](./05_delete.md)** - Deletando dados
   - DELETE com confirmação
   - Soft delete (desativação)
   - Boas práticas de segurança

### Exemplos Avançados

6. **[06_joins](./06_joins.md)** - Relacionando tabelas
   - INNER JOIN e LEFT JOIN
   - Foreign Keys
   - Múltiplos JOINs
   - Consultas complexas

7. **[07_transacoes](./07_transacoes.md)** - Transações
   - BEGIN, COMMIT, ROLLBACK
   - Atomicidade (tudo ou nada)
   - Performance 10-100x melhor
   - Savepoints

8. **[biblioteca_completa.c](./biblioteca_completa.c)** - Sistema Completo
   - Aplicação completa de gerenciamento de biblioteca
   - Interface interativa
   - Todas as operações CRUD
   - Relatórios e estatísticas

---

## 🚀 Início Rápido

### Compilar todos os exemplos

```bash
make
```

### Executar um exemplo específico

```bash
./01_create_table
./02_insert
./03_select
# etc...
```

### Limpar arquivos compilados

```bash
make clean        # Remove executáveis
make cleandb      # Remove bancos de dados
make cleanall     # Remove tudo
```

### Obter ajuda

```bash
make help
```

---

### 🎯 Objetivos Didáticos

- Compreender os fundamentos de bancos de dados relacionais
- Aprender SQL (Structured Query Language)
- Implementar operações CRUD em C usando SQLite
- Gerenciar dados persistentes em aplicações C
- Entender a diferença entre armazenamento em memória e em disco

---

## 🗄️ O que é SQLite?

**SQLite** é um motor de banco de dados SQL:
- **Embarcado**: Roda no mesmo processo da aplicação (sem servidor)
- **Zero-configuração**: Não precisa instalação ou configuração
- **Self-contained**: Todo o banco em um único arquivo
- **ACID-compliant**: Garante Atomicidade, Consistência, Isolamento e Durabilidade
- **Cross-platform**: Funciona em Windows, Linux, Mac, Android, iOS, etc.

### Por que usar SQLite?

| Característica | SQLite | MySQL/PostgreSQL |
|----------------|--------|------------------|
| **Configuração** | Nenhuma | Servidor separado |
| **Tamanho** | ~600 KB | Vários MB |
| **Uso** | Aplicações locais | Aplicações web/cliente-servidor |
| **Performance** | Excelente para leitura | Excelente para escrita concorrente |
| **Deployment** | Um arquivo | Servidor + configuração |

### Quando usar SQLite?

✅ **Use SQLite quando:**
- Aplicações desktop/mobile
- Armazenamento local de dados
- Protótipos e testes
- Aplicações embarcadas (IoT, dispositivos)
- Cache de dados
- Configurações e preferências
- Análise de dados (data science)

❌ **Não use SQLite quando:**
- Alta concorrência de escrita (muitos usuários escrevendo simultaneamente)
- Banco de dados > 1 TB
- Cliente-servidor em rede
- Controle de acesso granular por usuário

---

## 📖 Fundamentos de SQL

### O que é SQL?

**SQL (Structured Query Language)** é uma linguagem padrão para gerenciar bancos de dados relacionais. Ela permite:
- Criar, modificar e excluir tabelas (estrutura)
- Inserir, consultar, atualizar e deletar dados (CRUD)
- Controlar transações e garantir integridade

### Conceitos Fundamentais

#### 1. **Banco de Dados Relacional**
Dados organizados em **tabelas** (relações) com:
- **Linhas (registros/tuplas)**: Cada linha é uma entrada única
- **Colunas (campos/atributos)**: Cada coluna tem um tipo de dado específico

**Exemplo - Tabela de Livros:**
```
+---------+----------------------------+------------------+-------+------+
| id      | titulo                     | autor            | ano   | preco|
+---------+----------------------------+------------------+-------+------+
| 1       | 1984                       | George Orwell    | 1949  | 29.90|
| 2       | O Senhor dos Anéis         | J.R.R. Tolkien   | 1954  | 49.90|
| 3       | Dom Casmurro               | Machado de Assis | 1899  | 19.90|
+---------+----------------------------+------------------+-------+------+
```

#### 2. **Chave Primária (Primary Key)**
- Identifica **unicamente** cada registro
- Não pode ser NULL
- Geralmente um número inteiro auto-incrementado
- Exemplo: coluna `id` na tabela acima

#### 3. **Tipos de Dados em SQLite**

| Tipo SQLite | Descrição | Exemplo em C |
|-------------|-----------|--------------|
| **INTEGER** | Número inteiro (1, 2, 8 bytes) | `int`, `long long` |
| **REAL** | Ponto flutuante (8 bytes) | `double` |
| **TEXT** | String UTF-8 | `char*` |
| **BLOB** | Binary Large Object | `void*` (bytes) |
| **NULL** | Valor nulo | `NULL` |

**Observação**: SQLite usa tipagem dinâmica - tipos são sugestões, não restrições rígidas.

#### 4. **Transações ACID**

- **Atomicidade**: Operação completa ou nada (tudo ou nada)
- **Consistência**: Dados sempre em estado válido
- **Isolamento**: Transações não interferem entre si
- **Durabilidade**: Dados persistem após commit

---

## 🔧 Comandos SQL Essenciais

### DDL - Data Definition Language (Definição de Estrutura)

#### CREATE TABLE - Criar Tabela
```sql
CREATE TABLE livros (
    id INTEGER PRIMARY KEY AUTOINCREMENT,  -- Chave primária auto-incrementada
    titulo TEXT NOT NULL,                   -- Campo obrigatório
    autor TEXT NOT NULL,
    editora TEXT,
    ano INTEGER,
    preco REAL DEFAULT 0.0,                 -- Valor padrão
    estoque INTEGER DEFAULT 0
);
```

**Constraints (Restrições):**
- `PRIMARY KEY`: Identifica unicamente cada registro
- `AUTOINCREMENT`: SQLite gera valor automaticamente
- `NOT NULL`: Campo obrigatório (não pode ser vazio)
- `UNIQUE`: Valor deve ser único na tabela
- `DEFAULT valor`: Valor padrão se não fornecido
- `CHECK (condição)`: Validação customizada
- `FOREIGN KEY`: Relacionamento com outra tabela

#### ALTER TABLE - Modificar Tabela
```sql
ALTER TABLE livros ADD COLUMN isbn TEXT;           -- Adicionar coluna
ALTER TABLE livros RENAME TO livros_disponiveis;   -- Renomear tabela
```

#### DROP TABLE - Deletar Tabela
```sql
DROP TABLE IF EXISTS livros;  -- Remove tabela (cuidado!)
```

---

### DML - Data Manipulation Language (Manipulação de Dados)

#### INSERT - Inserir Dados
```sql
-- Inserir um registro especificando colunas
INSERT INTO livros (titulo, autor, ano, preco, estoque)
VALUES ('1984', 'George Orwell', 1949, 29.90, 15);

-- Inserir múltiplos registros
INSERT INTO livros (titulo, autor, ano, preco, estoque) VALUES
    ('O Senhor dos Anéis', 'J.R.R. Tolkien', 1954, 49.90, 8),
    ('Dom Casmurro', 'Machado de Assis', 1899, 19.90, 20);
```

#### SELECT - Consultar Dados
```sql
-- Selecionar todas as colunas
SELECT * FROM livros;

-- Selecionar colunas específicas
SELECT titulo, autor, preco FROM livros;

-- Filtrar com WHERE
SELECT * FROM livros WHERE preco < 30.00;

-- Ordenar com ORDER BY
SELECT * FROM livros ORDER BY preco DESC;  -- Descendente (mais caro primeiro)

-- Limitar resultados
SELECT * FROM livros LIMIT 10;

-- Combinar condições
SELECT * FROM livros 
WHERE ano > 1900 AND preco < 50.00 
ORDER BY ano ASC;
```

**Operadores em WHERE:**
- `=`, `!=`, `<>` (diferente)
- `<`, `>`, `<=`, `>=`
- `BETWEEN a AND b`
- `IN (lista)`
- `LIKE 'padrão'` (texto, `%` = qualquer coisa, `_` = um caractere)
- `IS NULL`, `IS NOT NULL`
- `AND`, `OR`, `NOT`

**Exemplos de LIKE:**
```sql
SELECT * FROM livros WHERE titulo LIKE '%Senhor%';     -- Contém "Senhor"
SELECT * FROM livros WHERE autor LIKE 'J.%';           -- Começa com "J."
SELECT * FROM livros WHERE titulo LIKE '____';         -- Exatamente 4 caracteres
```

#### UPDATE - Atualizar Dados
```sql
-- Atualizar um campo
UPDATE livros SET preco = 34.90 WHERE id = 1;

-- Atualizar múltiplos campos
UPDATE livros 
SET preco = preco * 1.10, estoque = estoque - 1 
WHERE id = 2;

-- Atualizar todos (cuidado!)
UPDATE livros SET estoque = 0;  -- Remove estoque de TODOS os livros
```

⚠️ **CUIDADO**: Sempre use WHERE em UPDATE, senão atualiza TODOS os registros!

#### DELETE - Deletar Dados
```sql
-- Deletar registro específico
DELETE FROM livros WHERE id = 3;

-- Deletar com condição
DELETE FROM livros WHERE estoque = 0;

-- Deletar tudo (cuidado!)
DELETE FROM livros;  -- Remove TODOS os registros
```

⚠️ **CUIDADO**: Sempre use WHERE em DELETE, senão remove TODOS os registros!

---

### DQL - Consultas Avançadas

#### Funções de Agregação
```sql
-- Contar registros
SELECT COUNT(*) FROM livros;                        -- Total de livros
SELECT COUNT(*) FROM livros WHERE preco > 30;      -- Livros acima de R$30

-- Somar valores
SELECT SUM(estoque) FROM livros;                    -- Total em estoque
SELECT SUM(preco * estoque) FROM livros;           -- Valor total do inventário

-- Média, Mínimo, Máximo
SELECT AVG(preco) FROM livros;                      -- Preço médio
SELECT MIN(preco) FROM livros;                      -- Livro mais barato
SELECT MAX(preco) FROM livros;                      -- Livro mais caro
```

#### GROUP BY - Agrupar Resultados
```sql
-- Contar livros por autor
SELECT autor, COUNT(*) as quantidade
FROM livros
GROUP BY autor
ORDER BY quantidade DESC;

-- Valor médio por editora
SELECT editora, AVG(preco) as preco_medio
FROM livros
GROUP BY editora
HAVING AVG(preco) > 25.00;  -- HAVING filtra após agrupar
```

#### DISTINCT - Valores Únicos
```sql
-- Listar todos os autores (sem repetição)
SELECT DISTINCT autor FROM livros;

-- Listar editoras únicas
SELECT DISTINCT editora FROM livros WHERE editora IS NOT NULL;
```

---

## 🔗 Relacionamentos entre Tabelas

### Chave Estrangeira (Foreign Key)

Relaciona duas tabelas através de uma coluna que referencia a chave primária de outra tabela.

**Exemplo - Sistema de Biblioteca com Empréstimos:**

```sql
-- Tabela de Livros
CREATE TABLE livros (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    titulo TEXT NOT NULL,
    autor TEXT NOT NULL
);

-- Tabela de Clientes
CREATE TABLE clientes (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nome TEXT NOT NULL,
    cpf TEXT UNIQUE NOT NULL
);

-- Tabela de Empréstimos (relacionamento)
CREATE TABLE emprestimos (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    livro_id INTEGER NOT NULL,
    cliente_id INTEGER NOT NULL,
    data_emprestimo DATE NOT NULL,
    data_devolucao DATE,
    FOREIGN KEY (livro_id) REFERENCES livros(id),
    FOREIGN KEY (cliente_id) REFERENCES clientes(id)
);
```

### JOIN - Combinar Tabelas

#### INNER JOIN - Registros que existem em ambas as tabelas
```sql
-- Listar empréstimos com informações do livro e cliente
SELECT 
    e.id,
    l.titulo,
    c.nome,
    e.data_emprestimo
FROM emprestimos e
INNER JOIN livros l ON e.livro_id = l.id
INNER JOIN clientes c ON e.cliente_id = c.id;
```

#### LEFT JOIN - Todos da esquerda + correspondentes da direita
```sql
-- Listar todos os livros, mesmo os que nunca foram emprestados
SELECT 
    l.titulo,
    COUNT(e.id) as vezes_emprestado
FROM livros l
LEFT JOIN emprestimos e ON l.id = e.livro_id
GROUP BY l.id;
```

---

## 💻 SQLite em C - API Principal

### 1. Incluir Biblioteca
```c
#include <sqlite3.h>
```

### 2. Tipos Principais
```c
sqlite3 *db;           // Ponteiro para conexão do banco
sqlite3_stmt *stmt;    // Statement preparado (consulta compilada)
```

### 3. Abrir/Fechar Banco de Dados

#### sqlite3_open() - Abrir Conexão
```c
int sqlite3_open(const char *filename, sqlite3 **db);

// Exemplo
sqlite3 *db;
int rc = sqlite3_open("biblioteca.db", &db);
if (rc != SQLITE_OK) {
    fprintf(stderr, "Erro ao abrir banco: %s\n", sqlite3_errmsg(db));
    return 1;
}
```
- **filename**: Nome do arquivo (cria se não existir)
- **db**: Ponteiro para receber a conexão
- **Retorno**: `SQLITE_OK` (0) se sucesso, código de erro caso contrário

#### sqlite3_close() - Fechar Conexão
```c
int sqlite3_close(sqlite3 *db);

// Exemplo
sqlite3_close(db);
```

### 4. Executar SQL Simples

#### sqlite3_exec() - Executar SQL Direto
```c
int sqlite3_exec(
    sqlite3 *db,                           // Conexão
    const char *sql,                       // SQL a executar
    int (*callback)(void*,int,char**,char**),  // Função callback (opcional)
    void *data,                            // Dados para callback
    char **errmsg                          // Mensagem de erro
);

// Exemplo - Criar tabela
char *err_msg = NULL;
const char *sql = "CREATE TABLE IF NOT EXISTS livros ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                  "titulo TEXT NOT NULL,"
                  "autor TEXT NOT NULL,"
                  "preco REAL);";

int rc = sqlite3_exec(db, sql, NULL, NULL, &err_msg);
if (rc != SQLITE_OK) {
    fprintf(stderr, "Erro SQL: %s\n", err_msg);
    sqlite3_free(err_msg);
}
```

### 5. Prepared Statements - Consultas Seguras

**Por que usar Prepared Statements?**
- ✅ Previne SQL Injection
- ✅ Melhor performance (SQL compilado uma vez, executado várias vezes)
- ✅ Código mais limpo e seguro

#### Fluxo de Prepared Statement
```
1. Prepare  → Compila SQL
2. Bind     → Vincula parâmetros
3. Step     → Executa e processa resultados
4. Finalize → Libera recursos
```

#### sqlite3_prepare_v2() - Compilar SQL
```c
int sqlite3_prepare_v2(
    sqlite3 *db,              // Conexão
    const char *sql,          // SQL com placeholders (?)
    int nByte,                // Tamanho do SQL (-1 para auto)
    sqlite3_stmt **stmt,      // Statement resultante
    const char **pzTail       // Resto do SQL (usar NULL)
);

// Exemplo
const char *sql = "INSERT INTO livros (titulo, autor, preco) VALUES (?, ?, ?);";
sqlite3_stmt *stmt;
int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
```

#### Bind - Vincular Parâmetros
```c
// Vincular texto (índice começa em 1)
int sqlite3_bind_text(stmt, 1, "1984", -1, SQLITE_TRANSIENT);
int sqlite3_bind_text(stmt, 2, "George Orwell", -1, SQLITE_TRANSIENT);

// Vincular número
int sqlite3_bind_double(stmt, 3, 29.90);
int sqlite3_bind_int(stmt, 1, 42);

// Vincular NULL
int sqlite3_bind_null(stmt, 1);
```

**Flags do bind_text:**
- `SQLITE_STATIC`: String permanece válida (não copia)
- `SQLITE_TRANSIENT`: SQLite faz cópia da string
- Usar `SQLITE_TRANSIENT` para strings locais/temporárias

#### sqlite3_step() - Executar
```c
int rc = sqlite3_step(stmt);

// Retornos possíveis:
// SQLITE_DONE  - Execução completa (INSERT/UPDATE/DELETE)
// SQLITE_ROW   - Linha disponível (SELECT)
// SQLITE_ERROR - Erro na execução
```

#### Ler Resultados (SELECT)
```c
// Exemplo - Listar livros
const char *sql = "SELECT id, titulo, autor, preco FROM livros;";
sqlite3_stmt *stmt;
sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

while (sqlite3_step(stmt) == SQLITE_ROW) {
    int id = sqlite3_column_int(stmt, 0);
    const unsigned char *titulo = sqlite3_column_text(stmt, 1);
    const unsigned char *autor = sqlite3_column_text(stmt, 2);
    double preco = sqlite3_column_double(stmt, 3);
    
    printf("%d | %s | %s | R$ %.2f\n", id, titulo, autor, preco);
}

sqlite3_finalize(stmt);
```

#### sqlite3_finalize() - Liberar Statement
```c
sqlite3_finalize(stmt);
```

---

## 🔒 Transações

Transações garantem que um conjunto de operações seja executado completamente ou não seja executado.

### Comandos de Transação
```sql
BEGIN TRANSACTION;    -- Inicia transação
COMMIT;               -- Confirma alterações
ROLLBACK;             -- Desfaz alterações
```

### Exemplo em C
```c
// Iniciar transação
sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, NULL);

// Operações
sqlite3_exec(db, "INSERT INTO livros ...", NULL, NULL, NULL);
sqlite3_exec(db, "UPDATE livros ...", NULL, NULL, NULL);

// Se tudo OK, confirma
if (tudo_ok) {
    sqlite3_exec(db, "COMMIT;", NULL, NULL, NULL);
} else {
    // Se erro, desfaz tudo
    sqlite3_exec(db, "ROLLBACK;", NULL, NULL, NULL);
}
```

**Quando usar transações?**
- Múltiplas operações que devem ser atômicas
- Transferência de valores (débito em A, crédito em B)
- Melhor performance (batch de inserções)

---

## 🎓 Exemplo Prático - Sistema de Biblioteca

O arquivo `biblioteca_completa.c` implementa um sistema completo de gerenciamento de biblioteca com:

### Funcionalidades Implementadas

1. **Gerenciamento de Livros**
   - Adicionar novo livro
   - Listar todos os livros
   - Buscar livro por ID, título ou autor
   - Atualizar informações (preço, estoque)
   - Remover livro

2. **Operações de Estoque**
   - Controle de quantidade em estoque
   - Venda de livros (reduz estoque)
   - Relatório de estoque baixo

3. **Relatórios e Estatísticas**
   - Total de livros cadastrados
   - Valor total do inventário
   - Livro mais caro e mais barato
   - Livros por autor

4. **Interface Interativa**
   - Menu intuitivo em console
   - Validação de entrada do usuário
   - Mensagens de erro claras

### Estrutura do Código

```c
// 1. Inicialização
sqlite3 *db;
sqlite3_open("biblioteca.db", &db);

// 2. Criar tabela (se não existir)
criar_tabela_livros(db);

// 3. Menu interativo
while (1) {
    exibir_menu();
    int opcao = ler_opcao();
    
    switch (opcao) {
        case 1: adicionar_livro(db); break;
        case 2: listar_livros(db); break;
        case 3: buscar_livro(db); break;
        // ...
    }
}

// 4. Finalização
sqlite3_close(db);
```

---

## 📊 Comparação: Vetores vs SQLite

| Aspecto | Vetor (Array em Memória) | SQLite (Banco de Dados) |
|---------|--------------------------|-------------------------|
| **Persistência** | ❌ Dados perdidos ao fechar | ✅ Dados salvos em arquivo |
| **Capacidade** | ⚠️ Limitado pela RAM | ✅ GB/TB de dados |
| **Busca** | O(n) linear ou O(log n) binário | ✅ O(log n) com índices |
| **Complexidade** | Simples | Requer SQL |
| **Performance** | 🚀 Muito rápida | ⚡ Rápida |
| **Uso de memória** | Alta (tudo na RAM) | Baixa (só necessário) |
| **Concorrência** | ❌ Difícil | ✅ Suportada |
| **Backup** | ⚠️ Serialização manual | ✅ Copiar arquivo .db |

**Conclusão**: Use vetores para dados temporários e pequenos; use SQLite para dados persistentes e estruturados.

---

## 🔍 Boas Práticas

### 1. Sempre Verificar Retornos
```c
int rc = sqlite3_exec(db, sql, NULL, NULL, &err_msg);
if (rc != SQLITE_OK) {
    fprintf(stderr, "Erro: %s\n", err_msg);
    sqlite3_free(err_msg);
}
```

### 2. Usar Prepared Statements
```c
// ❌ INSEGURO - Vulnerável a SQL Injection
char sql[256];
sprintf(sql, "SELECT * FROM users WHERE username='%s'", user_input);

// ✅ SEGURO - Prepared Statement
const char *sql = "SELECT * FROM users WHERE username=?";
sqlite3_stmt *stmt;
sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
sqlite3_bind_text(stmt, 1, user_input, -1, SQLITE_TRANSIENT);
```

### 3. Sempre Finalizar Statements
```c
sqlite3_stmt *stmt;
sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
// ... usar statement ...
sqlite3_finalize(stmt);  // IMPORTANTE: Liberar memória
```

### 4. Tratar Erros Adequadamente
```c
int rc = sqlite3_step(stmt);
if (rc != SQLITE_DONE && rc != SQLITE_ROW) {
    fprintf(stderr, "Erro: %s\n", sqlite3_errmsg(db));
}
```

### 5. Usar Transações para Múltiplas Inserções
```c
// Muito mais rápido que inserções individuais
sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, NULL);
for (int i = 0; i < 1000; i++) {
    inserir_registro(db, ...);
}
sqlite3_exec(db, "COMMIT;", NULL, NULL, NULL);
```

---

## 🛠️ Compilação

### Linux/Mac
```bash
gcc biblioteca_completa.c -o biblioteca -lsqlite3
./biblioteca
```

### Windows (MinGW)
```bash
gcc biblioteca_completa.c -o biblioteca.exe -lsqlite3
biblioteca.exe
```

### Verificar SQLite Instalado
```bash
# Linux (Debian/Ubuntu)
sudo apt-get install libsqlite3-dev

# Mac (Homebrew)
brew install sqlite3

# Verificar instalação
sqlite3 --version
```

---

## 📚 Recursos Adicionais

### Documentação Oficial
- **SQLite**: https://www.sqlite.org/docs.html
- **C/C++ API**: https://www.sqlite.org/c3ref/intro.html
- **SQL Tutorial**: https://www.sqlite.org/lang.html

### Ferramentas Úteis
- **DB Browser for SQLite**: Interface gráfica para visualizar bancos SQLite
  - https://sqlitebrowser.org/
- **sqlite3 CLI**: Linha de comando para interagir com bancos
  - `sqlite3 biblioteca.db` → abre banco em modo interativo

### Comandos Úteis no sqlite3 CLI
```sql
.tables              -- Listar tabelas
.schema livros       -- Ver estrutura da tabela
.mode column         -- Formatar saída em colunas
.headers on          -- Mostrar cabeçalhos
.output arquivo.txt  -- Redirecionar saída
.read script.sql     -- Executar arquivo SQL
.quit                -- Sair
```

---

## 🎯 Exercícios Propostos

### Nível Básico
1. Adicione uma coluna `isbn` na tabela de livros
2. Implemente busca por faixa de preço (ex: livros entre R$20 e R$40)
3. Crie função para listar livros ordenados por ano de publicação

### Nível Intermediário
4. Adicione tabela de categorias e relacione com livros (1:N)
5. Implemente sistema de empréstimos com data de devolução
6. Crie relatório de livros mais vendidos

### Nível Avançado
7. Implemente sistema de autenticação de usuários
8. Adicione suporte a múltiplas cópias do mesmo livro
9. Crie índices para otimizar buscas frequentes
10. Implemente backup automático do banco de dados

---

## ⚠️ Erros Comuns e Soluções

### 1. "unable to open database file"
**Causa**: Permissões ou caminho inválido  
**Solução**: Verificar permissões do diretório e caminho absoluto/relativo

### 2. "SQL logic error"
**Causa**: Erro de sintaxe SQL  
**Solução**: Verificar SQL com `sqlite3_errmsg(db)`

### 3. "database is locked"
**Causa**: Outra conexão está escrevendo  
**Solução**: Fechar outras conexões ou usar transações

### 4. Segmentation Fault
**Causa**: Acessar statement após finalize ou não inicializar  
**Solução**: Sempre verificar ponteiros e fluxo de prepare/finalize

### 5. "library not found: -lsqlite3"
**Causa**: SQLite não instalado  
**Solução**: Instalar libsqlite3-dev (Linux) ou sqlite3 (Mac/Windows)

---

## 🏆 Conclusão

SQLite é uma ferramenta poderosa para adicionar persistência de dados em aplicações C de forma simples e eficiente. Ao dominar SQLite e SQL, você pode criar aplicações robustas que armazenam, consultam e manipulam grandes volumes de dados estruturados.

**Próximos Passos:**
1. Compile e execute `biblioteca_completa.c`
2. Experimente modificar o código
3. Adicione novas funcionalidades
4. Explore a documentação oficial do SQLite
5. Pratique escrevendo consultas SQL complexas

**Lembre-se**: A prática é essencial! Quanto mais você usa SQL e SQLite, mais natural se torna trabalhar com bancos de dados.

---

**Autor**: Sistema Educacional de Estruturas de Dados  
**Última Atualização**: Novembro 2024
