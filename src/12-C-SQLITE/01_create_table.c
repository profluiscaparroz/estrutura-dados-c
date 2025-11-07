/*
 * ============================================================================
 * EXEMPLO 1: CREATE TABLE - Criando Tabelas em SQLite
 * ============================================================================
 * 
 * OBJETIVO:
 * Este exemplo demonstra como criar tabelas em SQLite usando C.
 * Você aprenderá a:
 * - Conectar ao banco de dados SQLite
 * - Criar uma tabela simples
 * - Definir tipos de dados e constraints
 * - Tratar erros adequadamente
 * 
 * CONCEITOS ABORDADOS:
 * - CREATE TABLE: comando para criar tabelas
 * - PRIMARY KEY: chave primária (identificador único)
 * - AUTOINCREMENT: incremento automático de IDs
 * - NOT NULL: campo obrigatório
 * - DEFAULT: valor padrão
 * 
 * COMPILAÇÃO:
 * gcc 01_create_table.c -o 01_create_table -lsqlite3
 * 
 * EXECUÇÃO:
 * ./01_create_table
 * ============================================================================
 */

#include <stdio.h>
#include <sqlite3.h>

int main() {
    sqlite3 *db;
    char *err_msg = NULL;
    int rc;

    printf("=== EXEMPLO 1: CREATE TABLE ===\n\n");

    // ========================================================================
    // PASSO 1: ABRIR CONEXÃO COM O BANCO DE DADOS
    // ========================================================================
    printf("1. Abrindo conexão com o banco de dados...\n");
    
    rc = sqlite3_open("exemplo01.db", &db);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "   ❌ Erro ao abrir banco: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    
    printf("   ✅ Banco de dados aberto com sucesso!\n\n");

    // ========================================================================
    // PASSO 2: CRIAR TABELA SIMPLES
    // ========================================================================
    printf("2. Criando tabela 'produtos'...\n\n");
    
    /*
     * SQL EXPLICADO:
     * 
     * CREATE TABLE IF NOT EXISTS produtos (
     *     - IF NOT EXISTS: Cria apenas se a tabela não existir
     *     - Evita erro caso execute o programa múltiplas vezes
     * 
     *     id INTEGER PRIMARY KEY AUTOINCREMENT,
     *     - INTEGER: Tipo de dado numérico inteiro
     *     - PRIMARY KEY: Define este campo como chave primária (única)
     *     - AUTOINCREMENT: SQLite gera automaticamente o próximo ID
     * 
     *     nome TEXT NOT NULL,
     *     - TEXT: Tipo de dado texto (string)
     *     - NOT NULL: Campo obrigatório (não pode ser vazio)
     * 
     *     descricao TEXT,
     *     - Sem NOT NULL: Campo opcional
     * 
     *     preco REAL NOT NULL,
     *     - REAL: Tipo de dado numérico com decimais (ponto flutuante)
     *     - NOT NULL: Preço é obrigatório
     * 
     *     quantidade INTEGER DEFAULT 0
     *     - DEFAULT 0: Se não informado, assume valor 0
     * );
     */
    const char *sql_create = 
        "CREATE TABLE IF NOT EXISTS produtos ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    nome TEXT NOT NULL,"
        "    descricao TEXT,"
        "    preco REAL NOT NULL,"
        "    quantidade INTEGER DEFAULT 0"
        ");";
    
    // Executar o comando SQL
    rc = sqlite3_exec(db, sql_create, NULL, NULL, &err_msg);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "   ❌ Erro ao criar tabela: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }
    
    printf("   ✅ Tabela 'produtos' criada com sucesso!\n\n");

    // ========================================================================
    // PASSO 3: CRIAR TABELA COM MAIS CONSTRAINTS
    // ========================================================================
    printf("3. Criando tabela 'clientes' com constraints adicionais...\n\n");
    
    /*
     * CONSTRAINTS ADICIONAIS:
     * - UNIQUE: Garante que o valor seja único na coluna
     * - CHECK: Valida uma condição (ex: idade >= 18)
     */
    const char *sql_create_clientes = 
        "CREATE TABLE IF NOT EXISTS clientes ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    nome TEXT NOT NULL,"
        "    email TEXT UNIQUE NOT NULL,"  // Email deve ser único
        "    cpf TEXT UNIQUE NOT NULL,"     // CPF deve ser único
        "    idade INTEGER CHECK(idade >= 18),"  // Cliente deve ter 18+ anos
        "    saldo REAL DEFAULT 0.0 CHECK(saldo >= 0)"  // Saldo não pode ser negativo
        ");";
    
    rc = sqlite3_exec(db, sql_create_clientes, NULL, NULL, &err_msg);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "   ❌ Erro ao criar tabela: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }
    
    printf("   ✅ Tabela 'clientes' criada com sucesso!\n\n");

    // ========================================================================
    // PASSO 4: VERIFICAR TABELAS CRIADAS
    // ========================================================================
    printf("4. Verificando tabelas criadas no banco de dados...\n\n");
    
    const char *sql_list_tables = 
        "SELECT name FROM sqlite_master WHERE type='table' ORDER BY name;";
    
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql_list_tables, -1, &stmt, NULL);
    
    if (rc == SQLITE_OK) {
        printf("   Tabelas encontradas:\n");
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            const unsigned char *table_name = sqlite3_column_text(stmt, 0);
            printf("   - %s\n", table_name);
        }
        printf("\n");
    }
    
    sqlite3_finalize(stmt);

    // ========================================================================
    // PASSO 5: MOSTRAR ESTRUTURA DAS TABELAS
    // ========================================================================
    printf("5. Estrutura da tabela 'produtos':\n\n");
    
    const char *sql_schema = "PRAGMA table_info(produtos);";
    
    rc = sqlite3_prepare_v2(db, sql_schema, -1, &stmt, NULL);
    
    if (rc == SQLITE_OK) {
        printf("   %-5s %-20s %-10s %-10s %-10s\n", 
               "ID", "Nome", "Tipo", "Not Null", "Default");
        printf("   %s\n", "-------------------------------------------------------------");
        
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int cid = sqlite3_column_int(stmt, 0);
            const unsigned char *name = sqlite3_column_text(stmt, 1);
            const unsigned char *type = sqlite3_column_text(stmt, 2);
            int notnull = sqlite3_column_int(stmt, 3);
            const unsigned char *dflt = sqlite3_column_text(stmt, 4);
            
            printf("   %-5d %-20s %-10s %-10s %-10s\n", 
                   cid, name, type, notnull ? "Sim" : "Não", 
                   dflt ? (const char *)dflt : "NULL");
        }
        printf("\n");
    }
    
    sqlite3_finalize(stmt);

    // ========================================================================
    // PASSO 6: FECHAR CONEXÃO
    // ========================================================================
    printf("6. Fechando conexão com o banco de dados...\n");
    sqlite3_close(db);
    printf("   ✅ Conexão fechada com sucesso!\n\n");

    // ========================================================================
    // RESUMO
    // ========================================================================
    printf("=== RESUMO ===\n\n");
    printf("✓ Você aprendeu a:\n");
    printf("  - Conectar ao banco de dados SQLite\n");
    printf("  - Criar tabelas com CREATE TABLE\n");
    printf("  - Definir PRIMARY KEY e AUTOINCREMENT\n");
    printf("  - Usar constraints: NOT NULL, UNIQUE, CHECK, DEFAULT\n");
    printf("  - Verificar tabelas criadas\n");
    printf("  - Visualizar estrutura das tabelas\n");
    printf("  - Fechar conexão adequadamente\n\n");
    
    printf("📁 Arquivo criado: exemplo01.db\n");
    printf("💡 Dica: Use 'sqlite3 exemplo01.db' para explorar o banco!\n\n");

    return 0;
}
