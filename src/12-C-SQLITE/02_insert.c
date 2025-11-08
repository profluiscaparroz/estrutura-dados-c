/*
 * ============================================================================
 * EXEMPLO 2: INSERT INTO - Inserindo Dados em SQLite
 * ============================================================================
 * 
 * OBJETIVO:
 * Este exemplo demonstra como inserir dados em tabelas SQLite usando C.
 * Você aprenderá a:
 * - Inserir dados usando INSERT INTO
 * - Usar Prepared Statements (segurança contra SQL Injection)
 * - Inserir múltiplos registros
 * - Usar transações para performance
 * 
 * CONCEITOS ABORDADOS:
 * - INSERT INTO: comando para inserir dados
 * - Prepared Statements: consultas parametrizadas seguras
 * - sqlite3_bind_*: vincular valores aos placeholders
 * - Transações: agrupar operações para melhor performance
 * 
 * COMPILAÇÃO:
 * gcc 02_insert.c -o 02_insert -lsqlite3
 * 
 * EXECUÇÃO:
 * ./02_insert
 * ============================================================================
 */

#include <stdio.h>
#include <sqlite3.h>
#include <string.h>

/*
 * FUNÇÃO: inserir_produto_simples
 * DESCRIÇÃO: Insere um produto usando INSERT INTO direto (não recomendado)
 * 
 * ⚠️ ATENÇÃO: Este método é mostrado apenas para fins didáticos.
 * Não é recomendado em produção pois é vulnerável a SQL Injection!
 */
void inserir_produto_simples(sqlite3 *db) {
    char *err_msg = NULL;
    
    printf("\n=== MÉTODO 1: INSERT SIMPLES (NÃO RECOMENDADO) ===\n\n");
    
    const char *sql = 
        "INSERT INTO produtos (nome, descricao, preco, quantidade) "
        "VALUES ('Notebook', 'Notebook Dell 15 polegadas', 2999.90, 10);";
    
    int rc = sqlite3_exec(db, sql, NULL, NULL, &err_msg);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "❌ Erro ao inserir: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("✅ Produto inserido com sucesso!\n");
        printf("   ID gerado: %lld\n", (long long)sqlite3_last_insert_rowid(db));
    }
}

/*
 * FUNÇÃO: inserir_produto_seguro
 * DESCRIÇÃO: Insere um produto usando Prepared Statement (RECOMENDADO)
 * 
 * ✅ Vantagens:
 * - Previne SQL Injection
 * - Melhor performance
 * - Código mais limpo e seguro
 */
void inserir_produto_seguro(sqlite3 *db, const char *nome, const char *descricao, 
                           double preco, int quantidade) {
    sqlite3_stmt *stmt;
    
    /*
     * PREPARED STATEMENT:
     * - Use '?' como placeholder para valores
     * - Vincule valores usando sqlite3_bind_*
     * - SQLite trata os dados adequadamente (previne SQL Injection)
     */
    const char *sql = 
        "INSERT INTO produtos (nome, descricao, preco, quantidade) "
        "VALUES (?, ?, ?, ?);";
    
    // PASSO 1: Preparar o statement
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "❌ Erro ao preparar statement: %s\n", sqlite3_errmsg(db));
        return;
    }
    
    // PASSO 2: Vincular valores aos placeholders (índice começa em 1)
    sqlite3_bind_text(stmt, 1, nome, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, descricao, -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 3, preco);
    sqlite3_bind_int(stmt, 4, quantidade);
    
    /*
     * SQLITE_TRANSIENT: SQLite faz uma cópia da string
     * Use para strings temporárias/locais que podem ser desalocadas
     * 
     * SQLITE_STATIC: SQLite não copia, string deve permanecer válida
     * Use para strings constantes ou globais
     */
    
    // PASSO 3: Executar o statement
    rc = sqlite3_step(stmt);
    
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "❌ Erro ao executar: %s\n", sqlite3_errmsg(db));
    } else {
        printf("✅ Produto '%s' inserido com sucesso!\n", nome);
        printf("   ID gerado: %lld\n", (long long)sqlite3_last_insert_rowid(db));
    }
    
    // PASSO 4: Finalizar o statement (liberar memória)
    sqlite3_finalize(stmt);
}

/*
 * FUNÇÃO: inserir_multiplos_produtos
 * DESCRIÇÃO: Insere múltiplos produtos usando transações
 * 
 * 💡 TRANSAÇÕES melhoram performance drasticamente:
 * - Sem transação: ~1000 inserções/segundo
 * - Com transação: ~10000+ inserções/segundo
 */
void inserir_multiplos_produtos(sqlite3 *db) {
    printf("\n=== MÉTODO 3: INSERÇÃO EM LOTE COM TRANSAÇÃO ===\n\n");
    
    // Dados para inserir
    struct {
        const char *nome;
        const char *descricao;
        double preco;
        int quantidade;
    } produtos[] = {
        {"Mouse USB", "Mouse óptico com fio USB", 25.90, 50},
        {"Teclado Mecânico", "Teclado mecânico RGB", 299.90, 20},
        {"Monitor 24\"", "Monitor LED Full HD 24 polegadas", 799.90, 15},
        {"Webcam HD", "Webcam 1080p para streaming", 189.90, 30},
        {"Headset Gamer", "Headset com microfone e LED", 149.90, 25}
    };
    
    int num_produtos = sizeof(produtos) / sizeof(produtos[0]);
    
    // INICIAR TRANSAÇÃO
    sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, NULL);
    
    printf("Iniciando inserção de %d produtos...\n\n", num_produtos);
    
    // Preparar statement uma vez (reutilizar)
    sqlite3_stmt *stmt;
    const char *sql = 
        "INSERT INTO produtos (nome, descricao, preco, quantidade) "
        "VALUES (?, ?, ?, ?);";
    
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    // Inserir cada produto
    for (int i = 0; i < num_produtos; i++) {
        // Limpar bindings anteriores
        sqlite3_reset(stmt);
        
        // Vincular novos valores
        sqlite3_bind_text(stmt, 1, produtos[i].nome, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, produtos[i].descricao, -1, SQLITE_STATIC);
        sqlite3_bind_double(stmt, 3, produtos[i].preco);
        sqlite3_bind_int(stmt, 4, produtos[i].quantidade);
        
        // Executar
        if (sqlite3_step(stmt) == SQLITE_DONE) {
            printf("  ✓ %s - R$ %.2f\n", produtos[i].nome, produtos[i].preco);
        } else {
            printf("  ✗ Erro ao inserir %s\n", produtos[i].nome);
        }
    }
    
    sqlite3_finalize(stmt);
    
    // CONFIRMAR TRANSAÇÃO
    sqlite3_exec(db, "COMMIT;", NULL, NULL, NULL);
    
    printf("\n✅ %d produtos inseridos com sucesso!\n", num_produtos);
}

/*
 * FUNÇÃO: listar_produtos
 * DESCRIÇÃO: Lista todos os produtos inseridos
 */
void listar_produtos(sqlite3 *db) {
    printf("\n=== PRODUTOS CADASTRADOS ===\n\n");
    
    sqlite3_stmt *stmt;
    const char *sql = 
        "SELECT id, nome, preco, quantidade FROM produtos ORDER BY id;";
    
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    printf("%-4s %-25s %12s %10s\n", "ID", "Nome", "Preço", "Qtd");
    printf("%-4s %-25s %12s %10s\n", "----", "-------------------------", 
           "------------", "----------");
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *nome = sqlite3_column_text(stmt, 1);
        double preco = sqlite3_column_double(stmt, 2);
        int quantidade = sqlite3_column_int(stmt, 3);
        
        printf("%-4d %-25s R$ %9.2f %10d\n", id, nome, preco, quantidade);
    }
    
    sqlite3_finalize(stmt);
    printf("\n");
}

/*
 * FUNÇÃO: estatisticas
 * DESCRIÇÃO: Mostra estatísticas dos produtos
 */
void estatisticas(sqlite3 *db) {
    printf("=== ESTATÍSTICAS ===\n\n");
    
    sqlite3_stmt *stmt;
    
    // Contar total de produtos
    sqlite3_prepare_v2(db, "SELECT COUNT(*) FROM produtos;", -1, &stmt, NULL);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int total = sqlite3_column_int(stmt, 0);
        printf("Total de produtos: %d\n", total);
    }
    sqlite3_finalize(stmt);
    
    // Valor total do estoque
    sqlite3_prepare_v2(db, 
        "SELECT SUM(preco * quantidade) FROM produtos;", -1, &stmt, NULL);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        double valor_total = sqlite3_column_double(stmt, 0);
        printf("Valor total do estoque: R$ %.2f\n", valor_total);
    }
    sqlite3_finalize(stmt);
    
    // Preço médio
    sqlite3_prepare_v2(db, "SELECT AVG(preco) FROM produtos;", -1, &stmt, NULL);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        double preco_medio = sqlite3_column_double(stmt, 0);
        printf("Preço médio: R$ %.2f\n", preco_medio);
    }
    sqlite3_finalize(stmt);
    
    printf("\n");
}

int main() {
    sqlite3 *db;
    char *err_msg = NULL;
    int rc;

    printf("=== EXEMPLO 2: INSERT INTO ===\n\n");

    // Abrir banco
    rc = sqlite3_open("exemplo02.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "❌ Erro ao abrir banco: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    
    printf("✅ Banco de dados aberto\n");

    // Criar tabela
    const char *sql_create = 
        "CREATE TABLE IF NOT EXISTS produtos ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    nome TEXT NOT NULL,"
        "    descricao TEXT,"
        "    preco REAL NOT NULL,"
        "    quantidade INTEGER DEFAULT 0"
        ");";
    
    sqlite3_exec(db, sql_create, NULL, NULL, &err_msg);
    printf("✅ Tabela criada/verificada\n");

    // MÉTODO 1: Inserção simples (não recomendado)
    inserir_produto_simples(db);

    // MÉTODO 2: Inserção segura com Prepared Statement (RECOMENDADO)
    printf("\n=== MÉTODO 2: PREPARED STATEMENT (RECOMENDADO) ===\n\n");
    inserir_produto_seguro(db, "Impressora", "Impressora jato de tinta", 399.90, 8);
    inserir_produto_seguro(db, "Scanner", "Scanner de mesa A4", 199.90, 12);

    // MÉTODO 3: Inserção em lote com transação
    inserir_multiplos_produtos(db);

    // Listar produtos inseridos
    listar_produtos(db);

    // Mostrar estatísticas
    estatisticas(db);

    // Resumo
    printf("=== RESUMO ===\n\n");
    printf("✓ Você aprendeu a:\n");
    printf("  - Inserir dados com INSERT INTO\n");
    printf("  - Usar Prepared Statements (segurança)\n");
    printf("  - Vincular valores com sqlite3_bind_*\n");
    printf("  - Usar transações para melhor performance\n");
    printf("  - Obter ID gerado com sqlite3_last_insert_rowid()\n");
    printf("  - Reutilizar statements com sqlite3_reset()\n\n");
    
    printf("💡 Dica: Sempre use Prepared Statements em produção!\n");
    printf("📁 Arquivo criado: exemplo02.db\n\n");

    // Fechar banco
    sqlite3_close(db);

    return 0;
}
