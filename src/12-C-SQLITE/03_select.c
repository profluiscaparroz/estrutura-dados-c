/*
 * ============================================================================
 * EXEMPLO 3: SELECT - Consultando Dados em SQLite
 * ============================================================================
 * 
 * OBJETIVO:
 * Este exemplo demonstra como consultar dados em SQLite usando C.
 * Você aprenderá a:
 * - Realizar consultas com SELECT
 * - Filtrar dados com WHERE
 * - Ordenar resultados com ORDER BY
 * - Limitar resultados com LIMIT
 * - Usar funções de agregação (COUNT, SUM, AVG, MIN, MAX)
 * - Ler diferentes tipos de dados das colunas
 * 
 * CONCEITOS ABORDADOS:
 * - SELECT: comando para consultar dados
 * - WHERE: filtrar resultados
 * - ORDER BY: ordenar resultados
 * - LIMIT: limitar número de resultados
 * - Funções de agregação
 * - sqlite3_column_*: ler valores das colunas
 * 
 * COMPILAÇÃO:
 * gcc 03_select.c -o 03_select -lsqlite3
 * 
 * EXECUÇÃO:
 * ./03_select
 * ============================================================================
 */

#include <stdio.h>
#include <sqlite3.h>

/*
 * FUNÇÃO: criar_e_popular_banco
 * DESCRIÇÃO: Cria tabela e insere dados de exemplo
 */
void criar_e_popular_banco(sqlite3 *db) {
    char *err_msg = NULL;
    
    // Criar tabela
    const char *sql_create = 
        "CREATE TABLE IF NOT EXISTS produtos ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    nome TEXT NOT NULL,"
        "    categoria TEXT NOT NULL,"
        "    preco REAL NOT NULL,"
        "    estoque INTEGER DEFAULT 0"
        ");";
    
    sqlite3_exec(db, sql_create, NULL, NULL, &err_msg);
    
    // Verificar se já tem dados
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "SELECT COUNT(*) FROM produtos;", -1, &stmt, NULL);
    sqlite3_step(stmt);
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    
    if (count > 0) {
        printf("✅ Banco já possui %d produtos\n\n", count);
        return;
    }
    
    // Inserir dados de exemplo
    printf("Populando banco de dados...\n");
    
    const char *sql_insert = 
        "INSERT INTO produtos (nome, categoria, preco, estoque) VALUES "
        "('Notebook Dell', 'Informática', 3499.90, 5),"
        "('Mouse Logitech', 'Informática', 89.90, 25),"
        "('Teclado Mecânico', 'Informática', 299.90, 15),"
        "('Monitor LG 24\"', 'Informática', 899.90, 8),"
        "('Cadeira Gamer', 'Móveis', 799.90, 10),"
        "('Mesa para Computador', 'Móveis', 349.90, 12),"
        "('Webcam Logitech', 'Informática', 249.90, 20),"
        "('Headset Razer', 'Informática', 399.90, 18),"
        "('SSD 500GB', 'Informática', 299.90, 30),"
        "('HD Externo 1TB', 'Informática', 349.90, 22);";
    
    sqlite3_exec(db, sql_insert, NULL, NULL, &err_msg);
    printf("✅ 10 produtos inseridos com sucesso!\n\n");
}

/*
 * FUNÇÃO: exemplo_select_simples
 * DESCRIÇÃO: SELECT básico - seleciona todas as linhas e colunas
 */
void exemplo_select_simples(sqlite3 *db) {
    printf("=== EXEMPLO 1: SELECT SIMPLES ===\n\n");
    printf("SQL: SELECT * FROM produtos;\n\n");
    
    sqlite3_stmt *stmt;
    const char *sql = "SELECT * FROM produtos;";
    
    // Preparar statement
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "❌ Erro: %s\n", sqlite3_errmsg(db));
        return;
    }
    
    // Cabeçalho
    printf("%-4s %-25s %-15s %12s %8s\n", 
           "ID", "Nome", "Categoria", "Preço", "Estoque");
    printf("%-4s %-25s %-15s %12s %8s\n",
           "----", "-------------------------", "---------------", 
           "------------", "--------");
    
    // Iterar pelos resultados
    // sqlite3_step() retorna SQLITE_ROW enquanto houver dados
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // sqlite3_column_* lê valores das colunas (índice começa em 0)
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *nome = sqlite3_column_text(stmt, 1);
        const unsigned char *categoria = sqlite3_column_text(stmt, 2);
        double preco = sqlite3_column_double(stmt, 3);
        int estoque = sqlite3_column_int(stmt, 4);
        
        printf("%-4d %-25s %-15s R$ %9.2f %8d\n", 
               id, nome, categoria, preco, estoque);
    }
    
    // Liberar statement
    sqlite3_finalize(stmt);
    printf("\n");
}

/*
 * FUNÇÃO: exemplo_select_colunas
 * DESCRIÇÃO: SELECT com colunas específicas
 */
void exemplo_select_colunas(sqlite3 *db) {
    printf("=== EXEMPLO 2: SELECT DE COLUNAS ESPECÍFICAS ===\n\n");
    printf("SQL: SELECT nome, preco FROM produtos;\n\n");
    
    sqlite3_stmt *stmt;
    const char *sql = "SELECT nome, preco FROM produtos;";
    
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    printf("%-30s %12s\n", "Produto", "Preço");
    printf("%-30s %12s\n", "------------------------------", "------------");
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *nome = sqlite3_column_text(stmt, 0);
        double preco = sqlite3_column_double(stmt, 1);
        
        printf("%-30s R$ %9.2f\n", nome, preco);
    }
    
    sqlite3_finalize(stmt);
    printf("\n");
}

/*
 * FUNÇÃO: exemplo_where
 * DESCRIÇÃO: SELECT com filtro WHERE
 */
void exemplo_where(sqlite3 *db) {
    printf("=== EXEMPLO 3: SELECT COM WHERE (FILTRO) ===\n\n");
    printf("SQL: SELECT * FROM produtos WHERE preco < 300;\n\n");
    
    sqlite3_stmt *stmt;
    const char *sql = "SELECT nome, preco FROM produtos WHERE preco < 300 ORDER BY preco;";
    
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    printf("Produtos com preço menor que R$ 300,00:\n\n");
    printf("%-30s %12s\n", "Produto", "Preço");
    printf("%-30s %12s\n", "------------------------------", "------------");
    
    int count = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *nome = sqlite3_column_text(stmt, 0);
        double preco = sqlite3_column_double(stmt, 1);
        
        printf("%-30s R$ %9.2f\n", nome, preco);
        count++;
    }
    
    printf("\nTotal: %d produtos\n\n", count);
    sqlite3_finalize(stmt);
}

/*
 * FUNÇÃO: exemplo_where_parametrizado
 * DESCRIÇÃO: WHERE com valores parametrizados (seguro)
 */
void exemplo_where_parametrizado(sqlite3 *db, const char *categoria) {
    printf("=== EXEMPLO 4: WHERE PARAMETRIZADO ===\n\n");
    printf("SQL: SELECT * FROM produtos WHERE categoria = ?;\n");
    printf("Parâmetro: categoria = '%s'\n\n", categoria);
    
    sqlite3_stmt *stmt;
    const char *sql = "SELECT nome, preco, estoque FROM produtos WHERE categoria = ?;";
    
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    // Vincular parâmetro
    sqlite3_bind_text(stmt, 1, categoria, -1, SQLITE_TRANSIENT);
    
    printf("Produtos da categoria '%s':\n\n", categoria);
    printf("%-30s %12s %10s\n", "Produto", "Preço", "Estoque");
    printf("%-30s %12s %10s\n", "------------------------------", "------------", "----------");
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *nome = sqlite3_column_text(stmt, 0);
        double preco = sqlite3_column_double(stmt, 1);
        int estoque = sqlite3_column_int(stmt, 2);
        
        printf("%-30s R$ %9.2f %10d\n", nome, preco, estoque);
    }
    
    sqlite3_finalize(stmt);
    printf("\n");
}

/*
 * FUNÇÃO: exemplo_order_by
 * DESCRIÇÃO: SELECT com ordenação
 */
void exemplo_order_by(sqlite3 *db) {
    printf("=== EXEMPLO 5: ORDER BY (ORDENAÇÃO) ===\n\n");
    printf("SQL: SELECT * FROM produtos ORDER BY preco DESC LIMIT 5;\n\n");
    printf("Top 5 produtos mais caros:\n\n");
    
    sqlite3_stmt *stmt;
    const char *sql = 
        "SELECT nome, preco FROM produtos "
        "ORDER BY preco DESC "  // DESC = decrescente, ASC = crescente
        "LIMIT 5;";             // Apenas 5 resultados
    
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    int posicao = 1;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *nome = sqlite3_column_text(stmt, 0);
        double preco = sqlite3_column_double(stmt, 1);
        
        printf("%d. %-30s R$ %9.2f\n", posicao++, nome, preco);
    }
    
    sqlite3_finalize(stmt);
    printf("\n");
}

/*
 * FUNÇÃO: exemplo_agregacao
 * DESCRIÇÃO: Funções de agregação (COUNT, SUM, AVG, MIN, MAX)
 */
void exemplo_agregacao(sqlite3 *db) {
    printf("=== EXEMPLO 6: FUNÇÕES DE AGREGAÇÃO ===\n\n");
    
    sqlite3_stmt *stmt;
    
    // COUNT - Contar registros
    printf("1. COUNT - Total de produtos:\n");
    sqlite3_prepare_v2(db, "SELECT COUNT(*) FROM produtos;", -1, &stmt, NULL);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int total = sqlite3_column_int(stmt, 0);
        printf("   Total: %d produtos\n\n", total);
    }
    sqlite3_finalize(stmt);
    
    // SUM - Somar valores
    printf("2. SUM - Valor total do estoque:\n");
    sqlite3_prepare_v2(db, 
        "SELECT SUM(preco * estoque) FROM produtos;", -1, &stmt, NULL);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        double valor_total = sqlite3_column_double(stmt, 0);
        printf("   Valor total: R$ %.2f\n\n", valor_total);
    }
    sqlite3_finalize(stmt);
    
    // AVG - Média
    printf("3. AVG - Preço médio:\n");
    sqlite3_prepare_v2(db, "SELECT AVG(preco) FROM produtos;", -1, &stmt, NULL);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        double preco_medio = sqlite3_column_double(stmt, 0);
        printf("   Preço médio: R$ %.2f\n\n", preco_medio);
    }
    sqlite3_finalize(stmt);
    
    // MIN e MAX
    printf("4. MIN e MAX - Produto mais barato e mais caro:\n");
    sqlite3_prepare_v2(db, 
        "SELECT MIN(preco), MAX(preco) FROM produtos;", -1, &stmt, NULL);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        double min_preco = sqlite3_column_double(stmt, 0);
        double max_preco = sqlite3_column_double(stmt, 1);
        printf("   Mais barato: R$ %.2f\n", min_preco);
        printf("   Mais caro: R$ %.2f\n\n", max_preco);
    }
    sqlite3_finalize(stmt);
    
    // GROUP BY - Agrupar
    printf("5. GROUP BY - Produtos por categoria:\n");
    sqlite3_prepare_v2(db, 
        "SELECT categoria, COUNT(*), SUM(estoque) "
        "FROM produtos "
        "GROUP BY categoria;", -1, &stmt, NULL);
    
    printf("   %-15s %10s %15s\n", "Categoria", "Produtos", "Total Estoque");
    printf("   %-15s %10s %15s\n", "---------------", "----------", "---------------");
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *categoria = sqlite3_column_text(stmt, 0);
        int count = sqlite3_column_int(stmt, 1);
        int total_estoque = sqlite3_column_int(stmt, 2);
        
        printf("   %-15s %10d %15d\n", categoria, count, total_estoque);
    }
    sqlite3_finalize(stmt);
    printf("\n");
}

/*
 * FUNÇÃO: exemplo_like
 * DESCRIÇÃO: Busca por padrão com LIKE
 */
void exemplo_like(sqlite3 *db) {
    printf("=== EXEMPLO 7: LIKE (BUSCA POR PADRÃO) ===\n\n");
    printf("SQL: SELECT * FROM produtos WHERE nome LIKE '%%Logitech%%';\n\n");
    printf("Produtos da marca Logitech:\n\n");
    
    sqlite3_stmt *stmt;
    const char *sql = "SELECT nome, preco FROM produtos WHERE nome LIKE '%Logitech%';";
    
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *nome = sqlite3_column_text(stmt, 0);
        double preco = sqlite3_column_double(stmt, 1);
        
        printf("  • %-30s R$ %.2f\n", nome, preco);
    }
    
    sqlite3_finalize(stmt);
    printf("\n");
}

int main() {
    sqlite3 *db;
    int rc;

    printf("=== EXEMPLO 3: SELECT - CONSULTANDO DADOS ===\n\n");

    // Abrir banco
    rc = sqlite3_open("exemplo03.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "❌ Erro ao abrir banco: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    
    // Criar e popular banco
    criar_e_popular_banco(db);
    
    // Exemplos de SELECT
    exemplo_select_simples(db);
    exemplo_select_colunas(db);
    exemplo_where(db);
    exemplo_where_parametrizado(db, "Informática");
    exemplo_order_by(db);
    exemplo_agregacao(db);
    exemplo_like(db);
    
    // Resumo
    printf("=== RESUMO ===\n\n");
    printf("✓ Você aprendeu a:\n");
    printf("  - Selecionar todas as colunas com SELECT *\n");
    printf("  - Selecionar colunas específicas\n");
    printf("  - Filtrar com WHERE\n");
    printf("  - Usar WHERE parametrizado (seguro)\n");
    printf("  - Ordenar com ORDER BY (ASC/DESC)\n");
    printf("  - Limitar resultados com LIMIT\n");
    printf("  - Usar funções de agregação (COUNT, SUM, AVG, MIN, MAX)\n");
    printf("  - Agrupar com GROUP BY\n");
    printf("  - Buscar padrões com LIKE\n");
    printf("  - Ler valores com sqlite3_column_*\n\n");
    
    printf("📁 Arquivo criado: exemplo03.db\n\n");

    // Fechar banco
    sqlite3_close(db);

    return 0;
}
