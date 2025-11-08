/*
 * ============================================================================
 * EXEMPLO 5: DELETE - Deletando Dados em SQLite
 * ============================================================================
 * 
 * OBJETIVO:
 * Este exemplo demonstra como deletar dados em SQLite usando C.
 * Você aprenderá a:
 * - Deletar registros com DELETE
 * - Usar WHERE para deletar registros específicos
 * - Deletar com condições múltiplas
 * - Verificar quantas linhas foram deletadas
 * - Deletar com segurança usando Prepared Statements
 * 
 * CONCEITOS ABORDADOS:
 * - DELETE FROM: comando para deletar dados
 * - WHERE: especificar quais registros deletar
 * - sqlite3_changes(): verificar linhas deletadas
 * - Prepared Statements para DELETE seguro
 * - Importância do WHERE (evitar deletar todos os dados!)
 * 
 * ⚠️  ATENÇÃO: DELETE é uma operação IRREVERSÍVEL!
 *     Sempre faça backup antes de deletar dados importantes!
 * 
 * COMPILAÇÃO:
 * gcc 05_delete.c -o 05_delete -lsqlite3
 * 
 * EXECUÇÃO:
 * ./05_delete
 * ============================================================================
 */

#include <stdio.h>
#include <sqlite3.h>
#include <string.h>

void criar_e_popular_banco(sqlite3 *db) {
    char *err_msg = NULL;
    
    const char *sql_create = 
        "CREATE TABLE IF NOT EXISTS produtos ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    nome TEXT NOT NULL,"
        "    preco REAL NOT NULL,"
        "    estoque INTEGER DEFAULT 0,"
        "    ativo INTEGER DEFAULT 1"  // 1 = ativo, 0 = inativo
        ");";
    
    sqlite3_exec(db, sql_create, NULL, NULL, &err_msg);
    
    // Limpar dados antigos
    sqlite3_exec(db, "DELETE FROM produtos;", NULL, NULL, NULL);
    
    // Inserir dados
    const char *sql_insert = 
        "INSERT INTO produtos (nome, preco, estoque, ativo) VALUES "
        "('Notebook Dell', 3499.90, 5, 1),"
        "('Mouse Logitech', 89.90, 0, 1),"       // Estoque zerado
        "('Teclado Mecânico', 299.90, 15, 1),"
        "('Monitor LG', 899.90, 8, 1),"
        "('Headset Antigo', 199.90, 3, 0),"      // Inativo
        "('Webcam Antiga', 149.90, 0, 0),"       // Inativo e sem estoque
        "('SSD 500GB', 299.90, 20, 1),"
        "('HD Externo', 349.90, 0, 1),"          // Estoque zerado
        "('Impressora HP', 599.90, 5, 1),"
        "('Scanner Velho', 199.90, 0, 0);";      // Inativo e sem estoque
    
    sqlite3_exec(db, sql_insert, NULL, NULL, &err_msg);
    printf("✅ Banco populado com 10 produtos\n\n");
}

void listar_produtos(sqlite3 *db, const char *titulo) {
    printf("%s\n\n", titulo);
    
    sqlite3_stmt *stmt;
    const char *sql = 
        "SELECT id, nome, preco, estoque, ativo FROM produtos ORDER BY id;";
    
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    printf("%-4s %-22s %12s %10s %8s\n", 
           "ID", "Nome", "Preço", "Estoque", "Status");
    printf("%-4s %-22s %12s %10s %8s\n",
           "----", "----------------------", "------------", "----------", "--------");
    
    int count = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *nome = sqlite3_column_text(stmt, 1);
        double preco = sqlite3_column_double(stmt, 2);
        int estoque = sqlite3_column_int(stmt, 3);
        int ativo = sqlite3_column_int(stmt, 4);
        
        printf("%-4d %-22s R$ %9.2f %10d %8s\n", 
               id, nome, preco, estoque, ativo ? "Ativo" : "Inativo");
        count++;
    }
    
    printf("\nTotal: %d produto(s)\n\n", count);
    sqlite3_finalize(stmt);
}

/*
 * EXEMPLO 1: DELETE simples por ID
 */
void exemplo_delete_por_id(sqlite3 *db, int produto_id) {
    printf("=== EXEMPLO 1: DELETE POR ID ===\n\n");
    printf("Deletando produto ID %d...\n\n", produto_id);
    
    // Primeiro, mostrar o produto que será deletado
    sqlite3_stmt *stmt;
    const char *sql_select = "SELECT nome FROM produtos WHERE id = ?;";
    
    sqlite3_prepare_v2(db, sql_select, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, produto_id);
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *nome = sqlite3_column_text(stmt, 0);
        printf("Produto a deletar: %s\n\n", nome);
    } else {
        printf("❌ Produto ID %d não encontrado!\n\n", produto_id);
        sqlite3_finalize(stmt);
        return;
    }
    sqlite3_finalize(stmt);
    
    // Deletar o produto
    const char *sql_delete = "DELETE FROM produtos WHERE id = ?;";
    
    sqlite3_prepare_v2(db, sql_delete, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, produto_id);
    
    if (sqlite3_step(stmt) == SQLITE_DONE) {
        int changes = sqlite3_changes(db);
        printf("✅ Produto deletado! %d linha(s) removida(s)\n\n", changes);
    } else {
        fprintf(stderr, "❌ Erro ao deletar: %s\n\n", sqlite3_errmsg(db));
    }
    
    sqlite3_finalize(stmt);
    listar_produtos(db, "Produtos após DELETE:");
}

/*
 * EXEMPLO 2: DELETE com condição simples
 */
void exemplo_delete_condicao(sqlite3 *db) {
    printf("=== EXEMPLO 2: DELETE COM CONDIÇÃO ===\n\n");
    printf("Deletando produtos inativos (ativo = 0)...\n\n");
    
    const char *sql = "DELETE FROM produtos WHERE ativo = 0;";
    
    char *err_msg = NULL;
    int rc = sqlite3_exec(db, sql, NULL, NULL, &err_msg);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "❌ Erro: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        int changes = sqlite3_changes(db);
        printf("✅ %d produto(s) inativo(s) deletado(s)\n\n", changes);
    }
    
    listar_produtos(db, "Produtos após DELETE:");
}

/*
 * EXEMPLO 3: DELETE com múltiplas condições
 */
void exemplo_delete_multiplas_condicoes(sqlite3 *db) {
    printf("=== EXEMPLO 3: DELETE COM MÚLTIPLAS CONDIÇÕES ===\n\n");
    printf("Deletando produtos com estoque zerado E inativos...\n\n");
    
    const char *sql = 
        "DELETE FROM produtos "
        "WHERE estoque = 0 AND ativo = 0;";
    
    char *err_msg = NULL;
    int rc = sqlite3_exec(db, sql, NULL, NULL, &err_msg);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "❌ Erro: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        int changes = sqlite3_changes(db);
        printf("✅ %d produto(s) deletado(s)\n\n", changes);
    }
    
    listar_produtos(db, "Produtos após DELETE:");
}

/*
 * EXEMPLO 4: DELETE com confirmação
 */
void exemplo_delete_com_confirmacao(sqlite3 *db) {
    printf("=== EXEMPLO 4: DELETE COM CONFIRMAÇÃO ===\n\n");
    
    // Primeiro, contar quantos serão deletados
    sqlite3_stmt *stmt;
    const char *sql_count = "SELECT COUNT(*) FROM produtos WHERE estoque = 0;";
    
    sqlite3_prepare_v2(db, sql_count, -1, &stmt, NULL);
    sqlite3_step(stmt);
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    
    if (count == 0) {
        printf("Nenhum produto com estoque zerado para deletar.\n\n");
        return;
    }
    
    printf("Encontrado(s) %d produto(s) com estoque zerado.\n", count);
    printf("Esses produtos serão deletados:\n\n");
    
    // Listar produtos que serão deletados
    const char *sql_list = "SELECT id, nome FROM produtos WHERE estoque = 0;";
    
    sqlite3_prepare_v2(db, sql_list, -1, &stmt, NULL);
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *nome = sqlite3_column_text(stmt, 1);
        printf("  • ID %d: %s\n", id, nome);
    }
    sqlite3_finalize(stmt);
    
    printf("\nConfirma a exclusão? (s/n): ");
    char resposta;
    scanf(" %c", &resposta);
    
    if (resposta == 's' || resposta == 'S') {
        const char *sql_delete = "DELETE FROM produtos WHERE estoque = 0;";
        char *err_msg = NULL;
        
        if (sqlite3_exec(db, sql_delete, NULL, NULL, &err_msg) == SQLITE_OK) {
            printf("\n✅ %d produto(s) deletado(s) com sucesso!\n\n", 
                   sqlite3_changes(db));
        } else {
            fprintf(stderr, "\n❌ Erro ao deletar: %s\n\n", err_msg);
            sqlite3_free(err_msg);
        }
    } else {
        printf("\n❌ Operação cancelada pelo usuário.\n\n");
    }
    
    listar_produtos(db, "Produtos após operação:");
}

/*
 * EXEMPLO 5: Soft Delete (marcar como inativo ao invés de deletar)
 */
void exemplo_soft_delete(sqlite3 *db, int produto_id) {
    printf("=== EXEMPLO 5: SOFT DELETE (DESATIVAÇÃO) ===\n\n");
    printf("Ao invés de deletar, vamos desativar o produto ID %d\n\n", produto_id);
    
    sqlite3_stmt *stmt;
    
    // Verificar se existe
    const char *sql_check = "SELECT nome, ativo FROM produtos WHERE id = ?;";
    sqlite3_prepare_v2(db, sql_check, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, produto_id);
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *nome = sqlite3_column_text(stmt, 0);
        int ativo = sqlite3_column_int(stmt, 1);
        
        printf("Produto: %s\n", nome);
        printf("Status atual: %s\n\n", ativo ? "Ativo" : "Inativo");
        
        sqlite3_finalize(stmt);
        
        // Desativar (soft delete)
        const char *sql_update = "UPDATE produtos SET ativo = 0 WHERE id = ?;";
        sqlite3_prepare_v2(db, sql_update, -1, &stmt, NULL);
        sqlite3_bind_int(stmt, 1, produto_id);
        
        if (sqlite3_step(stmt) == SQLITE_DONE) {
            printf("✅ Produto desativado (soft delete)\n");
            printf("💡 Dados preservados, apenas marcado como inativo\n\n");
        }
        
        sqlite3_finalize(stmt);
    } else {
        printf("❌ Produto não encontrado!\n\n");
        sqlite3_finalize(stmt);
    }
    
    listar_produtos(db, "Produtos após soft delete:");
}

/*
 * EXEMPLO 6: DELETE com JOIN (deletar baseado em relacionamento)
 */
void exemplo_delete_avancado(sqlite3 *db) {
    printf("=== EXEMPLO 6: DELETE AVANÇADO ===\n\n");
    printf("Deletando produtos com preço acima da média...\n\n");
    
    // Primeiro, calcular o preço médio
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "SELECT AVG(preco) FROM produtos;", -1, &stmt, NULL);
    sqlite3_step(stmt);
    double preco_medio = sqlite3_column_double(stmt, 0);
    sqlite3_finalize(stmt);
    
    printf("Preço médio: R$ %.2f\n\n", preco_medio);
    
    // Deletar produtos acima da média
    const char *sql = 
        "DELETE FROM produtos "
        "WHERE preco > (SELECT AVG(preco) FROM produtos);";
    
    char *err_msg = NULL;
    if (sqlite3_exec(db, sql, NULL, NULL, &err_msg) == SQLITE_OK) {
        int changes = sqlite3_changes(db);
        printf("✅ %d produto(s) acima da média deletado(s)\n\n", changes);
    } else {
        fprintf(stderr, "❌ Erro: %s\n\n", err_msg);
        sqlite3_free(err_msg);
    }
    
    listar_produtos(db, "Produtos restantes:");
}

int main() {
    sqlite3 *db;
    int rc;

    printf("=== EXEMPLO 5: DELETE - DELETANDO DADOS ===\n\n");

    rc = sqlite3_open("exemplo05.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "❌ Erro ao abrir banco: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    
    criar_e_popular_banco(db);
    listar_produtos(db, "=== PRODUTOS INICIAIS ===");
    
    // Exemplos de DELETE
    exemplo_delete_por_id(db, 5);
    exemplo_delete_multiplas_condicoes(db);
    exemplo_delete_com_confirmacao(db);
    exemplo_soft_delete(db, 1);
    exemplo_delete_avancado(db);
    
    // Resumo
    printf("=== RESUMO ===\n\n");
    printf("✓ Você aprendeu a:\n");
    printf("  - Deletar registros com DELETE FROM\n");
    printf("  - Usar WHERE para especificar registros\n");
    printf("  - Deletar com Prepared Statements (seguro)\n");
    printf("  - Deletar com múltiplas condições\n");
    printf("  - Implementar confirmação antes de deletar\n");
    printf("  - Usar soft delete (desativação ao invés de deletar)\n");
    printf("  - Verificar linhas deletadas com sqlite3_changes()\n\n");
    
    printf("⚠️  IMPORTANTE:\n");
    printf("  1. DELETE é IRREVERSÍVEL - sempre faça backup!\n");
    printf("  2. Sempre use WHERE - sem ele, TODOS os registros são deletados!\n");
    printf("  3. Considere soft delete para manter histórico\n");
    printf("  4. Teste em ambiente de desenvolvimento primeiro\n\n");
    
    printf("📁 Arquivo criado: exemplo05.db\n\n");

    sqlite3_close(db);
    return 0;
}
