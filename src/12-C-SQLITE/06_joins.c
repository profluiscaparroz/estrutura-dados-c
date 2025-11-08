/*
 * ============================================================================
 * EXEMPLO 6: JOINs - Relacionando Tabelas em SQLite
 * ============================================================================
 * 
 * OBJETIVO:
 * Este exemplo demonstra como relacionar múltiplas tabelas usando JOINs.
 * Você aprenderá a:
 * - Criar tabelas relacionadas com Foreign Keys
 * - Usar INNER JOIN para combinar tabelas
 * - Usar LEFT JOIN para incluir registros sem correspondência
 * - Realizar consultas complexas com múltiplos JOINs
 * - Entender a diferença entre tipos de JOIN
 * 
 * CONCEITOS ABORDADOS:
 * - Foreign Key: chave estrangeira
 * - INNER JOIN: registros que existem em ambas tabelas
 * - LEFT JOIN: todos da esquerda + correspondentes da direita
 * - RIGHT JOIN: (não suportado diretamente no SQLite)
 * - Aliases de tabelas (AS)
 * 
 * COMPILAÇÃO:
 * gcc 06_joins.c -o 06_joins -lsqlite3
 * 
 * EXECUÇÃO:
 * ./06_joins
 * ============================================================================
 */

#include <stdio.h>
#include <sqlite3.h>

void criar_schema(sqlite3 *db) {
    char *err_msg = NULL;
    
    printf("Criando schema do banco de dados...\n\n");
    
    // Habilitar Foreign Keys (desabilitado por padrão no SQLite)
    sqlite3_exec(db, "PRAGMA foreign_keys = ON;", NULL, NULL, NULL);
    
    // Tabela de Categorias
    const char *sql_categorias = 
        "CREATE TABLE IF NOT EXISTS categorias ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    nome TEXT NOT NULL UNIQUE,"
        "    descricao TEXT"
        ");";
    
    // Tabela de Produtos (com Foreign Key para categorias)
    const char *sql_produtos = 
        "CREATE TABLE IF NOT EXISTS produtos ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    nome TEXT NOT NULL,"
        "    preco REAL NOT NULL,"
        "    categoria_id INTEGER,"
        "    FOREIGN KEY (categoria_id) REFERENCES categorias(id)"
        ");";
    
    // Tabela de Clientes
    const char *sql_clientes = 
        "CREATE TABLE IF NOT EXISTS clientes ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    nome TEXT NOT NULL,"
        "    email TEXT UNIQUE,"
        "    cidade TEXT"
        ");";
    
    // Tabela de Pedidos (relaciona clientes e produtos)
    const char *sql_pedidos = 
        "CREATE TABLE IF NOT EXISTS pedidos ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    cliente_id INTEGER NOT NULL,"
        "    produto_id INTEGER NOT NULL,"
        "    quantidade INTEGER NOT NULL,"
        "    data TEXT NOT NULL,"
        "    FOREIGN KEY (cliente_id) REFERENCES clientes(id),"
        "    FOREIGN KEY (produto_id) REFERENCES produtos(id)"
        ");";
    
    sqlite3_exec(db, sql_categorias, NULL, NULL, &err_msg);
    sqlite3_exec(db, sql_produtos, NULL, NULL, &err_msg);
    sqlite3_exec(db, sql_clientes, NULL, NULL, &err_msg);
    sqlite3_exec(db, sql_pedidos, NULL, NULL, &err_msg);
    
    printf("✅ Schema criado com sucesso!\n\n");
}

void popular_dados(sqlite3 *db) {
    char *err_msg = NULL;
    
    printf("Populando banco de dados...\n\n");
    
    // Limpar dados existentes
    sqlite3_exec(db, "DELETE FROM pedidos;", NULL, NULL, NULL);
    sqlite3_exec(db, "DELETE FROM produtos;", NULL, NULL, NULL);
    sqlite3_exec(db, "DELETE FROM categorias;", NULL, NULL, NULL);
    sqlite3_exec(db, "DELETE FROM clientes;", NULL, NULL, NULL);
    
    // Inserir categorias
    const char *sql_insert_cat = 
        "INSERT INTO categorias (nome, descricao) VALUES "
        "('Eletrônicos', 'Produtos eletrônicos e gadgets'),"
        "('Informática', 'Computadores e acessórios'),"
        "('Móveis', 'Móveis para escritório');";
    
    // Inserir produtos
    const char *sql_insert_prod = 
        "INSERT INTO produtos (nome, preco, categoria_id) VALUES "
        "('Notebook Dell', 3499.90, 2),"
        "('Mouse Logitech', 89.90, 2),"
        "('Teclado Mecânico', 299.90, 2),"
        "('Monitor LG', 899.90, 1),"
        "('Webcam', 249.90, 1),"
        "('Cadeira Gamer', 799.90, 3),"
        "('Mesa Escritório', 549.90, 3),"
        "('Smartphone', 1999.90, 1),"
        "('Tablet', 1299.90, 1),"
        "('Impressora HP', 599.90, 2);";
    
    // Inserir clientes
    const char *sql_insert_cli = 
        "INSERT INTO clientes (nome, email, cidade) VALUES "
        "('João Silva', 'joao@email.com', 'São Paulo'),"
        "('Maria Santos', 'maria@email.com', 'Rio de Janeiro'),"
        "('Pedro Costa', 'pedro@email.com', 'Belo Horizonte'),"
        "('Ana Paula', 'ana@email.com', 'São Paulo'),"
        "('Carlos Lima', 'carlos@email.com', 'Curitiba');";
    
    // Inserir pedidos
    const char *sql_insert_ped = 
        "INSERT INTO pedidos (cliente_id, produto_id, quantidade, data) VALUES "
        "(1, 1, 1, '2024-11-01'),"  // João comprou Notebook
        "(1, 2, 2, '2024-11-01'),"  // João comprou 2 Mouses
        "(2, 4, 1, '2024-11-02'),"  // Maria comprou Monitor
        "(3, 6, 1, '2024-11-03'),"  // Pedro comprou Cadeira
        "(4, 8, 1, '2024-11-04'),"  // Ana comprou Smartphone
        "(1, 3, 1, '2024-11-05'),"  // João comprou Teclado
        "(2, 5, 1, '2024-11-05'),"  // Maria comprou Webcam
        "(5, 7, 1, '2024-11-06');"; // Carlos comprou Mesa
    
    sqlite3_exec(db, sql_insert_cat, NULL, NULL, &err_msg);
    sqlite3_exec(db, sql_insert_prod, NULL, NULL, &err_msg);
    sqlite3_exec(db, sql_insert_cli, NULL, NULL, &err_msg);
    sqlite3_exec(db, sql_insert_ped, NULL, NULL, &err_msg);
    
    printf("✅ Dados inseridos com sucesso!\n\n");
}

void exemplo_inner_join(sqlite3 *db) {
    printf("=== EXEMPLO 1: INNER JOIN ===\n\n");
    printf("Listar produtos com suas categorias:\n\n");
    
    sqlite3_stmt *stmt;
    const char *sql = 
        "SELECT p.nome AS produto, p.preco, c.nome AS categoria "
        "FROM produtos p "
        "INNER JOIN categorias c ON p.categoria_id = c.id "
        "ORDER BY c.nome, p.nome;";
    
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    printf("%-25s %12s %-15s\n", "Produto", "Preço", "Categoria");
    printf("%-25s %12s %-15s\n", 
           "-------------------------", "------------", "---------------");
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *produto = sqlite3_column_text(stmt, 0);
        double preco = sqlite3_column_double(stmt, 1);
        const unsigned char *categoria = sqlite3_column_text(stmt, 2);
        
        printf("%-25s R$ %9.2f %-15s\n", produto, preco, categoria);
    }
    
    sqlite3_finalize(stmt);
    printf("\n");
}

void exemplo_left_join(sqlite3 *db) {
    printf("=== EXEMPLO 2: LEFT JOIN ===\n\n");
    printf("Listar TODAS categorias e seus produtos (mesmo sem produtos):\n\n");
    
    sqlite3_stmt *stmt;
    const char *sql = 
        "SELECT c.nome AS categoria, COUNT(p.id) AS total_produtos "
        "FROM categorias c "
        "LEFT JOIN produtos p ON c.id = p.categoria_id "
        "GROUP BY c.id, c.nome;";
    
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    printf("%-20s %15s\n", "Categoria", "Total Produtos");
    printf("%-20s %15s\n", "--------------------", "---------------");
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *categoria = sqlite3_column_text(stmt, 0);
        int total = sqlite3_column_int(stmt, 1);
        
        printf("%-20s %15d\n", categoria, total);
    }
    
    sqlite3_finalize(stmt);
    printf("\n");
}

void exemplo_multiplos_joins(sqlite3 *db) {
    printf("=== EXEMPLO 3: MÚLTIPLOS JOINs ===\n\n");
    printf("Listar pedidos com informações completas:\n\n");
    
    sqlite3_stmt *stmt;
    const char *sql = 
        "SELECT "
        "    cli.nome AS cliente, "
        "    prod.nome AS produto, "
        "    cat.nome AS categoria, "
        "    ped.quantidade, "
        "    prod.preco, "
        "    (ped.quantidade * prod.preco) AS total "
        "FROM pedidos ped "
        "INNER JOIN clientes cli ON ped.cliente_id = cli.id "
        "INNER JOIN produtos prod ON ped.produto_id = prod.id "
        "INNER JOIN categorias cat ON prod.categoria_id = cat.id "
        "ORDER BY ped.data, ped.id;";
    
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    printf("%-15s %-20s %-12s %5s %12s %12s\n", 
           "Cliente", "Produto", "Categoria", "Qtd", "Preço", "Total");
    printf("%-15s %-20s %-12s %5s %12s %12s\n",
           "---------------", "--------------------", "------------", 
           "-----", "------------", "------------");
    
    double total_geral = 0;
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *cliente = sqlite3_column_text(stmt, 0);
        const unsigned char *produto = sqlite3_column_text(stmt, 1);
        const unsigned char *categoria = sqlite3_column_text(stmt, 2);
        int quantidade = sqlite3_column_int(stmt, 3);
        double preco = sqlite3_column_double(stmt, 4);
        double total = sqlite3_column_double(stmt, 5);
        
        printf("%-15s %-20s %-12s %5d R$ %9.2f R$ %9.2f\n", 
               cliente, produto, categoria, quantidade, preco, total);
        
        total_geral += total;
    }
    
    printf("\n%73s R$ %9.2f\n", "TOTAL GERAL:", total_geral);
    
    sqlite3_finalize(stmt);
    printf("\n");
}

void exemplo_agregacao_com_join(sqlite3 *db) {
    printf("=== EXEMPLO 4: AGREGAÇÃO COM JOIN ===\n\n");
    printf("Total de vendas por cliente:\n\n");
    
    sqlite3_stmt *stmt;
    const char *sql = 
        "SELECT "
        "    c.nome AS cliente, "
        "    c.cidade, "
        "    COUNT(ped.id) AS total_pedidos, "
        "    SUM(ped.quantidade * p.preco) AS valor_total "
        "FROM clientes c "
        "LEFT JOIN pedidos ped ON c.id = ped.cliente_id "
        "LEFT JOIN produtos p ON ped.produto_id = p.id "
        "GROUP BY c.id, c.nome, c.cidade "
        "ORDER BY valor_total DESC;";
    
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    printf("%-20s %-18s %8s %15s\n", 
           "Cliente", "Cidade", "Pedidos", "Valor Total");
    printf("%-20s %-18s %8s %15s\n",
           "--------------------", "------------------", 
           "--------", "---------------");
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *cliente = sqlite3_column_text(stmt, 0);
        const unsigned char *cidade = sqlite3_column_text(stmt, 1);
        int pedidos = sqlite3_column_int(stmt, 2);
        
        // Verificar se valor_total é NULL
        if (sqlite3_column_type(stmt, 3) == SQLITE_NULL) {
            printf("%-20s %-18s %8d %15s\n", 
                   cliente, cidade, pedidos, "R$ 0.00");
        } else {
            double valor = sqlite3_column_double(stmt, 3);
            printf("%-20s %-18s %8d R$ %12.2f\n", 
                   cliente, cidade, pedidos, valor);
        }
    }
    
    sqlite3_finalize(stmt);
    printf("\n");
}

void exemplo_subconsulta_com_join(sqlite3 *db) {
    printf("=== EXEMPLO 5: SUBCONSULTA COM JOIN ===\n\n");
    printf("Produtos mais vendidos:\n\n");
    
    sqlite3_stmt *stmt;
    const char *sql = 
        "SELECT "
        "    p.nome AS produto, "
        "    c.nome AS categoria, "
        "    SUM(ped.quantidade) AS total_vendido "
        "FROM produtos p "
        "INNER JOIN categorias c ON p.categoria_id = c.id "
        "INNER JOIN pedidos ped ON p.id = ped.produto_id "
        "GROUP BY p.id, p.nome, c.nome "
        "ORDER BY total_vendido DESC "
        "LIMIT 5;";
    
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    printf("%5s %-25s %-15s %12s\n", "Pos", "Produto", "Categoria", "Vendidos");
    printf("%5s %-25s %-15s %12s\n", "-----", "-------------------------", 
           "---------------", "------------");
    
    int pos = 1;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *produto = sqlite3_column_text(stmt, 0);
        const unsigned char *categoria = sqlite3_column_text(stmt, 1);
        int vendidos = sqlite3_column_int(stmt, 2);
        
        printf("%5d %-25s %-15s %12d\n", pos++, produto, categoria, vendidos);
    }
    
    sqlite3_finalize(stmt);
    printf("\n");
}

int main() {
    sqlite3 *db;
    int rc;

    printf("=== EXEMPLO 6: JOINs - RELACIONANDO TABELAS ===\n\n");

    rc = sqlite3_open("exemplo06.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "❌ Erro ao abrir banco: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    
    criar_schema(db);
    popular_dados(db);
    
    // Exemplos de JOINs
    exemplo_inner_join(db);
    exemplo_left_join(db);
    exemplo_multiplos_joins(db);
    exemplo_agregacao_com_join(db);
    exemplo_subconsulta_com_join(db);
    
    // Resumo
    printf("=== RESUMO ===\n\n");
    printf("✓ Você aprendeu a:\n");
    printf("  - Criar tabelas relacionadas com Foreign Keys\n");
    printf("  - Usar INNER JOIN para combinar tabelas\n");
    printf("  - Usar LEFT JOIN para incluir registros sem correspondência\n");
    printf("  - Realizar múltiplos JOINs em uma consulta\n");
    printf("  - Combinar JOINs com agregação\n");
    printf("  - Usar aliases de tabelas (AS)\n");
    printf("  - Criar consultas complexas com relacionamentos\n\n");
    
    printf("💡 Dica: Use aliases (AS) para tornar queries mais legíveis!\n");
    printf("📁 Arquivo criado: exemplo06.db\n\n");

    sqlite3_close(db);
    return 0;
}
