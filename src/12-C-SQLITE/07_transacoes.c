/*
 * ============================================================================
 * EXEMPLO 7: TRANSAÇÕES - Operações Atômicas em SQLite
 * ============================================================================
 * 
 * OBJETIVO:
 * Este exemplo demonstra como usar transações em SQLite.
 * Você aprenderá a:
 * - Iniciar, confirmar e desfazer transações
 * - Garantir atomicidade de operações
 * - Melhorar performance com transações
 * - Tratar erros adequadamente
 * - Usar savepoints para transações aninhadas
 * 
 * CONCEITOS ABORDADOS:
 * - BEGIN TRANSACTION: iniciar transação
 * - COMMIT: confirmar alterações
 * - ROLLBACK: desfazer alterações
 * - SAVEPOINT: ponto de salvamento
 * - Atomicidade: tudo ou nada
 * 
 * COMPILAÇÃO:
 * gcc 07_transacoes.c -o 07_transacoes -lsqlite3
 * 
 * EXECUÇÃO:
 * ./07_transacoes
 * ============================================================================
 */

#include <stdio.h>
#include <sqlite3.h>
#include <time.h>

void criar_schema(sqlite3 *db) {
    char *err_msg = NULL;
    
    const char *sql_contas = 
        "CREATE TABLE IF NOT EXISTS contas ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    titular TEXT NOT NULL,"
        "    saldo REAL NOT NULL DEFAULT 0 CHECK(saldo >= 0)"
        ");";
    
    const char *sql_transacoes = 
        "CREATE TABLE IF NOT EXISTS historico_transacoes ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    conta_origem INTEGER,"
        "    conta_destino INTEGER,"
        "    valor REAL NOT NULL,"
        "    tipo TEXT NOT NULL,"
        "    data TEXT NOT NULL,"
        "    status TEXT NOT NULL"
        ");";
    
    sqlite3_exec(db, sql_contas, NULL, NULL, &err_msg);
    sqlite3_exec(db, sql_transacoes, NULL, NULL, &err_msg);
    
    // Limpar e popular dados
    sqlite3_exec(db, "DELETE FROM historico_transacoes;", NULL, NULL, NULL);
    sqlite3_exec(db, "DELETE FROM contas;", NULL, NULL, NULL);
    
    const char *sql_insert = 
        "INSERT INTO contas (titular, saldo) VALUES "
        "('João Silva', 1000.00),"
        "('Maria Santos', 500.00),"
        "('Pedro Costa', 1500.00);";
    
    sqlite3_exec(db, sql_insert, NULL, NULL, &err_msg);
    
    printf("✅ Schema criado e dados populados\n\n");
}

void listar_contas(sqlite3 *db, const char *titulo) {
    printf("%s\n\n", titulo);
    
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id, titular, saldo FROM contas ORDER BY id;";
    
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    printf("%-5s %-20s %15s\n", "ID", "Titular", "Saldo");
    printf("%-5s %-20s %15s\n", "-----", "--------------------", "---------------");
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *titular = sqlite3_column_text(stmt, 1);
        double saldo = sqlite3_column_double(stmt, 2);
        
        printf("%-5d %-20s R$ %12.2f\n", id, titular, saldo);
    }
    
    sqlite3_finalize(stmt);
    printf("\n");
}

/*
 * EXEMPLO 1: Transação básica - COMMIT
 */
void exemplo_transacao_commit(sqlite3 *db) {
    printf("=== EXEMPLO 1: TRANSAÇÃO COM COMMIT ===\n\n");
    printf("Depositando R$ 200,00 na conta de João\n\n");
    
    char *err_msg = NULL;
    
    // INICIAR TRANSAÇÃO
    sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, &err_msg);
    
    // Atualizar saldo
    const char *sql_update = 
        "UPDATE contas SET saldo = saldo + 200.00 WHERE id = 1;";
    
    int rc = sqlite3_exec(db, sql_update, NULL, NULL, &err_msg);
    
    if (rc == SQLITE_OK) {
        // Registrar histórico
        const char *sql_hist = 
            "INSERT INTO historico_transacoes "
            "(conta_destino, valor, tipo, data, status) "
            "VALUES (1, 200.00, 'Depósito', datetime('now'), 'Aprovado');";
        
        sqlite3_exec(db, sql_hist, NULL, NULL, &err_msg);
        
        // CONFIRMAR TRANSAÇÃO
        sqlite3_exec(db, "COMMIT;", NULL, NULL, &err_msg);
        printf("✅ Transação confirmada com COMMIT!\n\n");
    } else {
        // DESFAZER em caso de erro
        sqlite3_exec(db, "ROLLBACK;", NULL, NULL, &err_msg);
        printf("❌ Erro: transação desfeita com ROLLBACK\n\n");
    }
    
    listar_contas(db, "Contas após transação:");
}

/*
 * EXEMPLO 2: Transação com ROLLBACK (erro intencional)
 */
void exemplo_transacao_rollback(sqlite3 *db) {
    printf("=== EXEMPLO 2: TRANSAÇÃO COM ROLLBACK ===\n\n");
    printf("Tentando sacar R$ 2000,00 da conta de Maria (saldo insuficiente)\n\n");
    
    char *err_msg = NULL;
    
    // INICIAR TRANSAÇÃO
    sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, &err_msg);
    
    // Tentar sacar (vai falhar porque saldo fica negativo)
    const char *sql_update = 
        "UPDATE contas SET saldo = saldo - 2000.00 WHERE id = 2;";
    
    int rc = sqlite3_exec(db, sql_update, NULL, NULL, &err_msg);
    
    if (rc != SQLITE_OK) {
        // ROLLBACK: desfazer alterações
        sqlite3_exec(db, "ROLLBACK;", NULL, NULL, &err_msg);
        printf("❌ Operação negada: saldo insuficiente\n");
        printf("✅ Transação desfeita com ROLLBACK - dados preservados\n\n");
    } else {
        sqlite3_exec(db, "COMMIT;", NULL, NULL, &err_msg);
    }
    
    listar_contas(db, "Contas após tentativa de saque (rollback):");
}

/*
 * EXEMPLO 3: Transferência entre contas (transação atômica)
 */
void transferir(sqlite3 *db, int conta_origem, int conta_destino, double valor) {
    printf("=== EXEMPLO 3: TRANSFERÊNCIA (TRANSAÇÃO ATÔMICA) ===\n\n");
    printf("Transferindo R$ %.2f da conta %d para conta %d\n\n", 
           valor, conta_origem, conta_destino);
    
    char *err_msg = NULL;
    int sucesso = 1;
    
    // INICIAR TRANSAÇÃO
    sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, &err_msg);
    
    // PASSO 1: Debitar da conta origem
    sqlite3_stmt *stmt;
    const char *sql_debito = 
        "UPDATE contas SET saldo = saldo - ? WHERE id = ?;";
    
    sqlite3_prepare_v2(db, sql_debito, -1, &stmt, NULL);
    sqlite3_bind_double(stmt, 1, valor);
    sqlite3_bind_int(stmt, 2, conta_origem);
    
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf("❌ Erro ao debitar da conta origem\n");
        sucesso = 0;
    }
    sqlite3_finalize(stmt);
    
    // PASSO 2: Creditar na conta destino (só se o débito funcionou)
    if (sucesso) {
        const char *sql_credito = 
            "UPDATE contas SET saldo = saldo + ? WHERE id = ?;";
        
        sqlite3_prepare_v2(db, sql_credito, -1, &stmt, NULL);
        sqlite3_bind_double(stmt, 1, valor);
        sqlite3_bind_int(stmt, 2, conta_destino);
        
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            printf("❌ Erro ao creditar na conta destino\n");
            sucesso = 0;
        }
        sqlite3_finalize(stmt);
    }
    
    // PASSO 3: Registrar no histórico
    if (sucesso) {
        const char *sql_hist = 
            "INSERT INTO historico_transacoes "
            "(conta_origem, conta_destino, valor, tipo, data, status) "
            "VALUES (?, ?, ?, 'Transferência', datetime('now'), 'Aprovado');";
        
        sqlite3_prepare_v2(db, sql_hist, -1, &stmt, NULL);
        sqlite3_bind_int(stmt, 1, conta_origem);
        sqlite3_bind_int(stmt, 2, conta_destino);
        sqlite3_bind_double(stmt, 3, valor);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
    
    // DECIDIR: COMMIT ou ROLLBACK
    if (sucesso) {
        sqlite3_exec(db, "COMMIT;", NULL, NULL, &err_msg);
        printf("✅ Transferência realizada com sucesso!\n");
        printf("   Todas as operações confirmadas (COMMIT)\n\n");
    } else {
        sqlite3_exec(db, "ROLLBACK;", NULL, NULL, &err_msg);
        printf("❌ Transferência cancelada\n");
        printf("   Todas as operações desfeitas (ROLLBACK)\n\n");
    }
    
    listar_contas(db, "Contas após transferência:");
}

/*
 * EXEMPLO 4: Performance com transações
 */
void exemplo_performance(sqlite3 *db) {
    printf("=== EXEMPLO 4: PERFORMANCE COM TRANSAÇÕES ===\n\n");
    
    char *err_msg = NULL;
    clock_t inicio, fim;
    double tempo_sem, tempo_com;
    const int NUM_OPERACOES = 1000;
    
    // Limpar tabela de teste
    sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS teste (id INTEGER, valor INTEGER);", 
                 NULL, NULL, NULL);
    sqlite3_exec(db, "DELETE FROM teste;", NULL, NULL, NULL);
    
    // Teste SEM transação
    printf("Inserindo %d registros SEM transação...\n", NUM_OPERACOES);
    inicio = clock();
    
    for (int i = 0; i < NUM_OPERACOES; i++) {
        char sql[100];
        sprintf(sql, "INSERT INTO teste VALUES (%d, %d);", i, i * 2);
        sqlite3_exec(db, sql, NULL, NULL, &err_msg);
    }
    
    fim = clock();
    tempo_sem = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("  Tempo: %.3f segundos\n\n", tempo_sem);
    
    // Limpar novamente
    sqlite3_exec(db, "DELETE FROM teste;", NULL, NULL, NULL);
    
    // Teste COM transação
    printf("Inserindo %d registros COM transação...\n", NUM_OPERACOES);
    inicio = clock();
    
    sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, &err_msg);
    
    for (int i = 0; i < NUM_OPERACOES; i++) {
        char sql[100];
        sprintf(sql, "INSERT INTO teste VALUES (%d, %d);", i, i * 2);
        sqlite3_exec(db, sql, NULL, NULL, &err_msg);
    }
    
    sqlite3_exec(db, "COMMIT;", NULL, NULL, &err_msg);
    
    fim = clock();
    tempo_com = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("  Tempo: %.3f segundos\n\n", tempo_com);
    
    // Comparação
    printf("📊 RESULTADO:\n");
    printf("  Sem transação: %.3f segundos\n", tempo_sem);
    printf("  Com transação: %.3f segundos\n", tempo_com);
    printf("  Speedup: %.1fx mais rápido!\n\n", tempo_sem / tempo_com);
    
    // Limpar
    sqlite3_exec(db, "DROP TABLE teste;", NULL, NULL, NULL);
}

/*
 * EXEMPLO 5: Savepoints (transações aninhadas)
 */
void exemplo_savepoints(sqlite3 *db) {
    printf("=== EXEMPLO 5: SAVEPOINTS ===\n\n");
    printf("Usando savepoints para desfazer parcialmente\n\n");
    
    char *err_msg = NULL;
    
    // Iniciar transação principal
    sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, &err_msg);
    
    // Operação 1: Depósito de R$ 100
    printf("1. Depositando R$ 100 na conta 1\n");
    sqlite3_exec(db, "UPDATE contas SET saldo = saldo + 100 WHERE id = 1;", 
                 NULL, NULL, &err_msg);
    
    // SAVEPOINT A
    sqlite3_exec(db, "SAVEPOINT sp1;", NULL, NULL, &err_msg);
    printf("   SAVEPOINT sp1 criado\n\n");
    
    // Operação 2: Depósito de R$ 200
    printf("2. Depositando R$ 200 na conta 1\n");
    sqlite3_exec(db, "UPDATE contas SET saldo = saldo + 200 WHERE id = 1;", 
                 NULL, NULL, &err_msg);
    
    // SAVEPOINT B
    sqlite3_exec(db, "SAVEPOINT sp2;", NULL, NULL, &err_msg);
    printf("   SAVEPOINT sp2 criado\n\n");
    
    // Operação 3: Depósito de R$ 300 (vamos desfazer esta)
    printf("3. Depositando R$ 300 na conta 1\n");
    sqlite3_exec(db, "UPDATE contas SET saldo = saldo + 300 WHERE id = 1;", 
                 NULL, NULL, &err_msg);
    printf("   (vamos desfazer esta operação)\n\n");
    
    // ROLLBACK para sp2 (desfaz apenas operação 3)
    sqlite3_exec(db, "ROLLBACK TO sp2;", NULL, NULL, &err_msg);
    printf("4. ROLLBACK TO sp2 - operação 3 desfeita\n");
    printf("   Operações 1 e 2 mantidas\n\n");
    
    // COMMIT da transação principal
    sqlite3_exec(db, "COMMIT;", NULL, NULL, &err_msg);
    printf("5. COMMIT - operações 1 e 2 confirmadas\n\n");
    
    listar_contas(db, "Contas após savepoints:");
}

int main() {
    sqlite3 *db;
    int rc;

    printf("=== EXEMPLO 7: TRANSAÇÕES ===\n\n");

    rc = sqlite3_open("exemplo07.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "❌ Erro ao abrir banco: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    
    criar_schema(db);
    listar_contas(db, "=== CONTAS INICIAIS ===");
    
    // Exemplos de transações
    exemplo_transacao_commit(db);
    exemplo_transacao_rollback(db);
    transferir(db, 1, 3, 300.00);
    exemplo_performance(db);
    exemplo_savepoints(db);
    
    // Resumo
    printf("=== RESUMO ===\n\n");
    printf("✓ Você aprendeu a:\n");
    printf("  - Iniciar transações com BEGIN TRANSACTION\n");
    printf("  - Confirmar alterações com COMMIT\n");
    printf("  - Desfazer alterações com ROLLBACK\n");
    printf("  - Garantir atomicidade (tudo ou nada)\n");
    printf("  - Melhorar performance drasticamente\n");
    printf("  - Usar savepoints para controle fino\n");
    printf("  - Tratar erros adequadamente\n\n");
    
    printf("💡 Dica: Use transações para operações relacionadas!\n");
    printf("⚡ Performance: 10-100x mais rápido com transações!\n");
    printf("📁 Arquivo criado: exemplo07.db\n\n");

    sqlite3_close(db);
    return 0;
}
