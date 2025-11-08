/*
 * ============================================================================
 * EXEMPLO 4: UPDATE - Atualizando Dados em SQLite
 * ============================================================================
 * 
 * OBJETIVO:
 * Este exemplo demonstra como atualizar dados em SQLite usando C.
 * Você aprenderá a:
 * - Atualizar registros com UPDATE
 * - Usar WHERE para atualizar registros específicos
 * - Atualizar múltiplos campos
 * - Atualizar com base em cálculos
 * - Verificar quantas linhas foram afetadas
 * 
 * CONCEITOS ABORDADOS:
 * - UPDATE: comando para atualizar dados
 * - SET: definir novos valores
 * - WHERE: especificar quais registros atualizar
 * - sqlite3_changes(): verificar linhas afetadas
 * - Prepared Statements para UPDATE seguro
 * 
 * COMPILAÇÃO:
 * gcc 04_update.c -o 04_update -lsqlite3
 * 
 * EXECUÇÃO:
 * ./04_update
 * ============================================================================
 */

#include <stdio.h>
#include <sqlite3.h>

void criar_e_popular_banco(sqlite3 *db) {
    char *err_msg = NULL;
    
    const char *sql_create = 
        "CREATE TABLE IF NOT EXISTS produtos ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    nome TEXT NOT NULL,"
        "    preco REAL NOT NULL,"
        "    estoque INTEGER DEFAULT 0,"
        "    desconto REAL DEFAULT 0.0"
        ");";
    
    sqlite3_exec(db, sql_create, NULL, NULL, &err_msg);
    
    // Verificar se já tem dados
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "SELECT COUNT(*) FROM produtos;", -1, &stmt, NULL);
    sqlite3_step(stmt);
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    
    if (count > 0) {
        // Limpar dados antigos para o exemplo
        sqlite3_exec(db, "DELETE FROM produtos;", NULL, NULL, NULL);
    }
    
    // Inserir dados
    const char *sql_insert = 
        "INSERT INTO produtos (nome, preco, estoque, desconto) VALUES "
        "('Notebook Dell', 3499.90, 5, 0.0),"
        "('Mouse Logitech', 89.90, 25, 0.0),"
        "('Teclado Mecânico', 299.90, 15, 0.0),"
        "('Monitor LG', 899.90, 8, 0.0),"
        "('Headset', 199.90, 20, 0.0);";
    
    sqlite3_exec(db, sql_insert, NULL, NULL, &err_msg);
    printf("✅ Banco populado com 5 produtos\n\n");
}

void listar_produtos(sqlite3 *db, const char *titulo) {
    printf("%s\n\n", titulo);
    
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id, nome, preco, estoque, desconto FROM produtos;";
    
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    printf("%-4s %-20s %12s %10s %10s\n", 
           "ID", "Nome", "Preço", "Estoque", "Desconto");
    printf("%-4s %-20s %12s %10s %10s\n",
           "----", "--------------------", "------------", "----------", "----------");
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *nome = sqlite3_column_text(stmt, 1);
        double preco = sqlite3_column_double(stmt, 2);
        int estoque = sqlite3_column_int(stmt, 3);
        double desconto = sqlite3_column_double(stmt, 4);
        
        printf("%-4d %-20s R$ %9.2f %10d %9.1f%%\n", 
               id, nome, preco, estoque, desconto * 100);
    }
    
    sqlite3_finalize(stmt);
    printf("\n");
}

/*
 * EXEMPLO 1: UPDATE simples de um campo
 */
void exemplo_update_simples(sqlite3 *db) {
    printf("=== EXEMPLO 1: UPDATE SIMPLES ===\n\n");
    
    // Atualizar preço de um produto específico
    printf("Atualizando preço do produto ID 1...\n\n");
    
    const char *sql = "UPDATE produtos SET preco = 3299.90 WHERE id = 1;";
    
    char *err_msg = NULL;
    int rc = sqlite3_exec(db, sql, NULL, NULL, &err_msg);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "❌ Erro: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        int changes = sqlite3_changes(db);
        printf("✅ UPDATE executado! %d linha(s) afetada(s)\n\n", changes);
    }
    
    listar_produtos(db, "Produtos após UPDATE:");
}

/*
 * EXEMPLO 2: UPDATE parametrizado (SEGURO)
 */
void exemplo_update_parametrizado(sqlite3 *db, int produto_id, double novo_preco) {
    printf("=== EXEMPLO 2: UPDATE PARAMETRIZADO (SEGURO) ===\n\n");
    printf("Atualizando preço do produto ID %d para R$ %.2f\n\n", 
           produto_id, novo_preco);
    
    sqlite3_stmt *stmt;
    const char *sql = "UPDATE produtos SET preco = ? WHERE id = ?;";
    
    // Preparar statement
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "❌ Erro ao preparar: %s\n", sqlite3_errmsg(db));
        return;
    }
    
    // Vincular parâmetros
    sqlite3_bind_double(stmt, 1, novo_preco);
    sqlite3_bind_int(stmt, 2, produto_id);
    
    // Executar
    rc = sqlite3_step(stmt);
    
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "❌ Erro ao executar: %s\n", sqlite3_errmsg(db));
    } else {
        int changes = sqlite3_changes(db);
        printf("✅ Preço atualizado! %d linha(s) afetada(s)\n\n", changes);
    }
    
    sqlite3_finalize(stmt);
    listar_produtos(db, "Produtos após UPDATE:");
}

/*
 * EXEMPLO 3: UPDATE de múltiplos campos
 */
void exemplo_update_multiplos_campos(sqlite3 *db) {
    printf("=== EXEMPLO 3: UPDATE DE MÚLTIPLOS CAMPOS ===\n\n");
    printf("Atualizando preço e estoque do produto ID 3\n\n");
    
    sqlite3_stmt *stmt;
    const char *sql = 
        "UPDATE produtos "
        "SET preco = ?, estoque = ? "
        "WHERE id = ?;";
    
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    // Novo preço: 279.90, Novo estoque: 20, Produto ID: 3
    sqlite3_bind_double(stmt, 1, 279.90);
    sqlite3_bind_int(stmt, 2, 20);
    sqlite3_bind_int(stmt, 3, 3);
    
    if (sqlite3_step(stmt) == SQLITE_DONE) {
        printf("✅ Campos atualizados com sucesso!\n\n");
    }
    
    sqlite3_finalize(stmt);
    listar_produtos(db, "Produtos após UPDATE:");
}

/*
 * EXEMPLO 4: UPDATE com cálculo
 */
void exemplo_update_com_calculo(sqlite3 *db) {
    printf("=== EXEMPLO 4: UPDATE COM CÁLCULO ===\n\n");
    printf("Aplicando 10%% de desconto em todos os produtos\n\n");
    
    const char *sql = 
        "UPDATE produtos "
        "SET preco = preco * 0.9, "  // 10% de desconto
        "    desconto = 0.10;";       // Registrar desconto aplicado
    
    char *err_msg = NULL;
    int rc = sqlite3_exec(db, sql, NULL, NULL, &err_msg);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "❌ Erro: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        int changes = sqlite3_changes(db);
        printf("✅ Desconto aplicado! %d produto(s) atualizado(s)\n\n", changes);
    }
    
    listar_produtos(db, "Produtos com desconto:");
}

/*
 * EXEMPLO 5: UPDATE condicional
 */
void exemplo_update_condicional(sqlite3 *db) {
    printf("=== EXEMPLO 5: UPDATE CONDICIONAL ===\n\n");
    printf("Aumentando estoque de produtos com estoque baixo (<10)\n\n");
    
    const char *sql = 
        "UPDATE produtos "
        "SET estoque = estoque + 20 "
        "WHERE estoque < 10;";
    
    char *err_msg = NULL;
    int rc = sqlite3_exec(db, sql, NULL, NULL, &err_msg);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "❌ Erro: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        int changes = sqlite3_changes(db);
        printf("✅ Estoque aumentado! %d produto(s) atualizado(s)\n\n", changes);
    }
    
    listar_produtos(db, "Produtos após reposição:");
}

/*
 * EXEMPLO 6: UPDATE com verificação antes
 */
void exemplo_update_seguro(sqlite3 *db, int produto_id) {
    printf("=== EXEMPLO 6: UPDATE COM VERIFICAÇÃO PRÉVIA ===\n\n");
    
    // Primeiro, verificar se o produto existe
    sqlite3_stmt *stmt;
    const char *sql_check = "SELECT nome, preco FROM produtos WHERE id = ?;";
    
    sqlite3_prepare_v2(db, sql_check, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, produto_id);
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *nome = sqlite3_column_text(stmt, 0);
        double preco_atual = sqlite3_column_double(stmt, 1);
        
        printf("Produto encontrado: %s (R$ %.2f)\n", nome, preco_atual);
        printf("Aplicando aumento de 5%%...\n\n");
        
        double novo_preco = preco_atual * 1.05;
        
        sqlite3_finalize(stmt);
        
        // Agora atualizar
        const char *sql_update = "UPDATE produtos SET preco = ? WHERE id = ?;";
        sqlite3_prepare_v2(db, sql_update, -1, &stmt, NULL);
        sqlite3_bind_double(stmt, 1, novo_preco);
        sqlite3_bind_int(stmt, 2, produto_id);
        
        if (sqlite3_step(stmt) == SQLITE_DONE) {
            printf("✅ Preço atualizado: R$ %.2f → R$ %.2f\n\n", 
                   preco_atual, novo_preco);
        }
        sqlite3_finalize(stmt);
    } else {
        printf("❌ Produto ID %d não encontrado!\n\n", produto_id);
        sqlite3_finalize(stmt);
    }
}

int main() {
    sqlite3 *db;
    int rc;

    printf("=== EXEMPLO 4: UPDATE - ATUALIZANDO DADOS ===\n\n");

    rc = sqlite3_open("exemplo04.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "❌ Erro ao abrir banco: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    
    criar_e_popular_banco(db);
    listar_produtos(db, "=== PRODUTOS INICIAIS ===");
    
    // Exemplos de UPDATE
    exemplo_update_simples(db);
    exemplo_update_parametrizado(db, 2, 79.90);
    exemplo_update_multiplos_campos(db);
    exemplo_update_com_calculo(db);
    exemplo_update_condicional(db);
    exemplo_update_seguro(db, 1);
    
    // Resumo
    printf("=== RESUMO ===\n\n");
    printf("✓ Você aprendeu a:\n");
    printf("  - Atualizar registros com UPDATE\n");
    printf("  - Usar WHERE para especificar registros\n");
    printf("  - Atualizar com Prepared Statements (seguro)\n");
    printf("  - Atualizar múltiplos campos\n");
    printf("  - Fazer UPDATE com cálculos\n");
    printf("  - Verificar linhas afetadas com sqlite3_changes()\n");
    printf("  - Fazer verificações antes de atualizar\n\n");
    
    printf("⚠️  IMPORTANTE: Sempre use WHERE em UPDATE!\n");
    printf("    Sem WHERE, TODOS os registros serão atualizados!\n\n");
    
    printf("📁 Arquivo criado: exemplo04.db\n\n");

    sqlite3_close(db);
    return 0;
}
