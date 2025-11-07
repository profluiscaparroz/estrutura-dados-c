/*
 * ============================================================================
 * SISTEMA DE GERENCIAMENTO DE BIBLIOTECA - SQLite em C
 * ============================================================================
 * 
 * OBJETIVO DIDÁTICO:
 * Este programa demonstra como usar SQLite em C para criar um sistema completo
 * de gerenciamento de biblioteca. Você aprenderá a:
 * 
 * 1. Conectar e criar banco de dados SQLite
 * 2. Criar tabelas com SQL
 * 3. Realizar operações CRUD (Create, Read, Update, Delete)
 * 4. Usar Prepared Statements para segurança
 * 5. Implementar busca e relatórios
 * 6. Gerenciar transações
 * 
 * ESTRUTURA DO BANCO DE DADOS:
 * - Tabela: livros
 *   - id: INTEGER PRIMARY KEY AUTOINCREMENT (chave primária)
 *   - titulo: TEXT NOT NULL (título do livro)
 *   - autor: TEXT NOT NULL (autor do livro)
 *   - editora: TEXT (editora)
 *   - ano: INTEGER (ano de publicação)
 *   - preco: REAL (preço em reais)
 *   - estoque: INTEGER (quantidade em estoque)
 * 
 * COMPILAÇÃO:
 * Linux/Mac: gcc biblioteca_completa.c -o biblioteca -lsqlite3
 * Windows:   gcc biblioteca_completa.c -o biblioteca.exe -lsqlite3
 * 
 * EXECUÇÃO:
 * ./biblioteca (Linux/Mac)
 * biblioteca.exe (Windows)
 * 
 * AUTOR: Sistema Educacional de Estruturas de Dados
 * DATA: Novembro 2024
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

// ============================================================================
// DEFINIÇÃO DE CONSTANTES
// ============================================================================

#define MAX_TITULO 100
#define MAX_AUTOR 80
#define MAX_EDITORA 80
#define MAX_SQL 512

// ============================================================================
// ESTRUTURAS DE DADOS
// ============================================================================

/*
 * ESTRUTURA: Livro
 * DESCRIÇÃO: Representa um livro no sistema
 * 
 * Esta estrutura mapeia diretamente para as colunas da tabela 'livros'
 * no banco de dados SQLite. É usada para facilitar a manipulação dos
 * dados em memória antes de inserir/atualizar no banco.
 */
typedef struct {
    int id;                      // ID único do livro (chave primária)
    char titulo[MAX_TITULO];     // Título do livro
    char autor[MAX_AUTOR];       // Nome do autor
    char editora[MAX_EDITORA];   // Nome da editora
    int ano;                     // Ano de publicação
    double preco;                // Preço em reais
    int estoque;                 // Quantidade em estoque
} Livro;

// ============================================================================
// FUNÇÕES AUXILIARES
// ============================================================================

/*
 * FUNÇÃO: limpar_buffer
 * DESCRIÇÃO: Limpa o buffer de entrada após leitura
 * 
 * Esta função é necessária para evitar problemas quando usamos scanf seguido
 * de gets ou fgets. Remove caracteres residuais do buffer de entrada.
 */
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/*
 * FUNÇÃO: pausar
 * DESCRIÇÃO: Pausa a execução aguardando o usuário pressionar ENTER
 * 
 * Útil para permitir que o usuário leia mensagens antes de limpar a tela
 */
void pausar() {
    printf("\nPressione ENTER para continuar...");
    limpar_buffer();
}

/*
 * FUNÇÃO: limpar_tela
 * DESCRIÇÃO: Limpa a tela do console
 * 
 * Usa comandos diferentes dependendo do sistema operacional
 */
void limpar_tela() {
    #ifdef _WIN32
        system("cls");  // Windows
    #else
        system("clear");  // Linux/Mac
    #endif
}

// ============================================================================
// FUNÇÕES DE BANCO DE DADOS
// ============================================================================

/*
 * FUNÇÃO: criar_tabela_livros
 * DESCRIÇÃO: Cria a tabela 'livros' no banco de dados se ela não existir
 * PARÂMETRO: db - ponteiro para a conexão do banco de dados
 * RETORNO: 0 se sucesso, código de erro caso contrário
 * 
 * EXPLICAÇÃO DO SQL:
 * - CREATE TABLE IF NOT EXISTS: Cria apenas se não existir
 * - INTEGER PRIMARY KEY AUTOINCREMENT: Chave primária que incrementa automaticamente
 * - NOT NULL: Campo obrigatório (não pode ser vazio)
 * - DEFAULT 0: Valor padrão caso não seja fornecido
 */
int criar_tabela_livros(sqlite3 *db) {
    const char *sql = 
        "CREATE TABLE IF NOT EXISTS livros ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"  // ID único auto-incrementado
        "titulo TEXT NOT NULL,"                   // Título obrigatório
        "autor TEXT NOT NULL,"                    // Autor obrigatório
        "editora TEXT,"                           // Editora opcional
        "ano INTEGER,"                            // Ano opcional
        "preco REAL DEFAULT 0.0,"                 // Preço com valor padrão
        "estoque INTEGER DEFAULT 0"               // Estoque com valor padrão
        ");";
    
    char *err_msg = NULL;
    int rc = sqlite3_exec(db, sql, NULL, NULL, &err_msg);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao criar tabela: %s\n", err_msg);
        sqlite3_free(err_msg);
        return rc;
    }
    
    return SQLITE_OK;
}

/*
 * FUNÇÃO: adicionar_livro
 * DESCRIÇÃO: Adiciona um novo livro ao banco de dados
 * PARÂMETRO: db - ponteiro para a conexão do banco de dados
 * 
 * PASSOS:
 * 1. Solicita dados do usuário
 * 2. Prepara statement SQL com placeholders (?)
 * 3. Vincula (bind) os valores aos placeholders
 * 4. Executa o statement
 * 5. Finaliza o statement (libera memória)
 * 
 * USO DE PREPARED STATEMENTS:
 * - Previne SQL Injection (segurança)
 * - Melhor performance
 * - Código mais limpo
 */
void adicionar_livro(sqlite3 *db) {
    Livro livro;
    
    limpar_tela();
    printf("\n=== ADICIONAR NOVO LIVRO ===\n\n");
    
    // Coletar dados do usuário
    printf("Título: ");
    limpar_buffer();
    fgets(livro.titulo, MAX_TITULO, stdin);
    livro.titulo[strcspn(livro.titulo, "\n")] = 0;  // Remove '\n'
    
    printf("Autor: ");
    fgets(livro.autor, MAX_AUTOR, stdin);
    livro.autor[strcspn(livro.autor, "\n")] = 0;
    
    printf("Editora: ");
    fgets(livro.editora, MAX_EDITORA, stdin);
    livro.editora[strcspn(livro.editora, "\n")] = 0;
    
    printf("Ano de publicação: ");
    scanf("%d", &livro.ano);
    
    printf("Preço (R$): ");
    scanf("%lf", &livro.preco);
    
    printf("Quantidade em estoque: ");
    scanf("%d", &livro.estoque);
    
    // Preparar SQL com placeholders (?)
    // Os placeholders serão substituídos pelos valores reais de forma segura
    const char *sql = "INSERT INTO livros (titulo, autor, editora, ano, preco, estoque) "
                      "VALUES (?, ?, ?, ?, ?, ?);";
    
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar statement: %s\n", sqlite3_errmsg(db));
        pausar();
        return;
    }
    
    // Vincular valores aos placeholders
    // Índices começam em 1 (não em 0!)
    // SQLITE_TRANSIENT indica que SQLite deve fazer cópia da string
    sqlite3_bind_text(stmt, 1, livro.titulo, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, livro.autor, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, livro.editora, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 4, livro.ano);
    sqlite3_bind_double(stmt, 5, livro.preco);
    sqlite3_bind_int(stmt, 6, livro.estoque);
    
    // Executar o statement
    rc = sqlite3_step(stmt);
    
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Erro ao inserir livro: %s\n", sqlite3_errmsg(db));
    } else {
        // sqlite3_last_insert_rowid retorna o ID do último registro inserido
        printf("\n✓ Livro adicionado com sucesso! (ID: %lld)\n", 
               sqlite3_last_insert_rowid(db));
    }
    
    // IMPORTANTE: Sempre finalizar o statement para liberar memória
    sqlite3_finalize(stmt);
    pausar();
}

/*
 * FUNÇÃO: listar_livros
 * DESCRIÇÃO: Lista todos os livros cadastrados no banco de dados
 * PARÂMETRO: db - ponteiro para a conexão do banco de dados
 * 
 * EXPLICAÇÃO:
 * - Usa SELECT * para buscar todas as colunas
 * - sqlite3_step() retorna SQLITE_ROW enquanto houver linhas
 * - sqlite3_column_* extrai dados de cada coluna
 * - Índice das colunas começa em 0
 */
void listar_livros(sqlite3 *db) {
    limpar_tela();
    printf("\n=== LISTA DE LIVROS ===\n\n");
    
    const char *sql = "SELECT id, titulo, autor, editora, ano, preco, estoque "
                      "FROM livros ORDER BY titulo;";
    
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar consulta: %s\n", sqlite3_errmsg(db));
        pausar();
        return;
    }
    
    // Cabeçalho da listagem
    printf("%-5s %-30s %-25s %-20s %6s %10s %8s\n", 
           "ID", "Título", "Autor", "Editora", "Ano", "Preço", "Estoque");
    printf("─────────────────────────────────────────────────────────────────────"
           "───────────────────────────────────────\n");
    
    int count = 0;
    
    // Loop enquanto houver linhas (SQLITE_ROW)
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // Extrair dados de cada coluna
        // Índices começam em 0
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *titulo = sqlite3_column_text(stmt, 1);
        const unsigned char *autor = sqlite3_column_text(stmt, 2);
        const unsigned char *editora = sqlite3_column_text(stmt, 3);
        int ano = sqlite3_column_int(stmt, 4);
        double preco = sqlite3_column_double(stmt, 5);
        int estoque = sqlite3_column_int(stmt, 6);
        
        // Exibir linha formatada
        printf("%-5d %-30s %-25s %-20s %6d R$ %7.2f %8d\n", 
               id, titulo, autor, editora, ano, preco, estoque);
        count++;
    }
    
    printf("\nTotal de livros: %d\n", count);
    
    sqlite3_finalize(stmt);
    pausar();
}

/*
 * FUNÇÃO: buscar_livro_por_id
 * DESCRIÇÃO: Busca e exibe um livro específico pelo ID
 * PARÂMETRO: db - ponteiro para a conexão do banco de dados
 * 
 * EXPLICAÇÃO:
 * - WHERE id = ? filtra pelo ID específico
 * - Usa prepared statement para segurança
 */
void buscar_livro_por_id(sqlite3 *db) {
    int id;
    
    limpar_tela();
    printf("\n=== BUSCAR LIVRO POR ID ===\n\n");
    printf("Digite o ID do livro: ");
    scanf("%d", &id);
    
    const char *sql = "SELECT id, titulo, autor, editora, ano, preco, estoque "
                      "FROM livros WHERE id = ?;";
    
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar consulta: %s\n", sqlite3_errmsg(db));
        pausar();
        return;
    }
    
    // Vincular o ID à consulta
    sqlite3_bind_int(stmt, 1, id);
    
    // Executar e verificar se encontrou
    rc = sqlite3_step(stmt);
    
    if (rc == SQLITE_ROW) {
        // Livro encontrado - exibir detalhes
        printf("\n┌─────────────────────────────────────────────────────┐\n");
        printf("│ INFORMAÇÕES DO LIVRO                                │\n");
        printf("└─────────────────────────────────────────────────────┘\n");
        printf("ID:       %d\n", sqlite3_column_int(stmt, 0));
        printf("Título:   %s\n", sqlite3_column_text(stmt, 1));
        printf("Autor:    %s\n", sqlite3_column_text(stmt, 2));
        printf("Editora:  %s\n", sqlite3_column_text(stmt, 3));
        printf("Ano:      %d\n", sqlite3_column_int(stmt, 4));
        printf("Preço:    R$ %.2f\n", sqlite3_column_double(stmt, 5));
        printf("Estoque:  %d unidades\n", sqlite3_column_int(stmt, 6));
    } else {
        printf("\n✗ Livro com ID %d não encontrado.\n", id);
    }
    
    sqlite3_finalize(stmt);
    pausar();
}

/*
 * FUNÇÃO: buscar_livro_por_titulo
 * DESCRIÇÃO: Busca livros pelo título (busca parcial)
 * PARÂMETRO: db - ponteiro para a conexão do banco de dados
 * 
 * EXPLICAÇÃO:
 * - LIKE '%termo%' busca título que contenha o termo em qualquer posição
 * - % é coringa que representa qualquer sequência de caracteres
 * - Exemplo: buscar "senhor" encontra "O Senhor dos Anéis"
 */
void buscar_livro_por_titulo(sqlite3 *db) {
    char termo[MAX_TITULO];
    char busca[MAX_TITULO + 2];  // +2 para adicionar %
    
    limpar_tela();
    printf("\n=== BUSCAR LIVRO POR TÍTULO ===\n\n");
    printf("Digite o título (ou parte dele): ");
    limpar_buffer();
    fgets(termo, MAX_TITULO, stdin);
    termo[strcspn(termo, "\n")] = 0;
    
    // Construir padrão de busca: %termo%
    sprintf(busca, "%%%s%%", termo);
    
    const char *sql = "SELECT id, titulo, autor, preco, estoque "
                      "FROM livros WHERE titulo LIKE ? ORDER BY titulo;";
    
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar consulta: %s\n", sqlite3_errmsg(db));
        pausar();
        return;
    }
    
    sqlite3_bind_text(stmt, 1, busca, -1, SQLITE_TRANSIENT);
    
    printf("\n%-5s %-40s %-30s %10s %8s\n", 
           "ID", "Título", "Autor", "Preço", "Estoque");
    printf("────────────────────────────────────────────────────────────"
           "─────────────────────────────────────\n");
    
    int count = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("%-5d %-40s %-30s R$ %7.2f %8d\n",
               sqlite3_column_int(stmt, 0),
               sqlite3_column_text(stmt, 1),
               sqlite3_column_text(stmt, 2),
               sqlite3_column_double(stmt, 3),
               sqlite3_column_int(stmt, 4));
        count++;
    }
    
    if (count == 0) {
        printf("\nNenhum livro encontrado com o termo \"%s\".\n", termo);
    } else {
        printf("\n%d livro(s) encontrado(s).\n", count);
    }
    
    sqlite3_finalize(stmt);
    pausar();
}

/*
 * FUNÇÃO: atualizar_preco
 * DESCRIÇÃO: Atualiza o preço de um livro
 * PARÂMETRO: db - ponteiro para a conexão do banco de dados
 * 
 * EXPLICAÇÃO:
 * - UPDATE modifica registros existentes
 * - SET define novos valores
 * - WHERE especifica qual(is) registro(s) modificar
 * - IMPORTANTE: Sempre use WHERE em UPDATE, senão atualiza TODOS os registros!
 */
void atualizar_preco(sqlite3 *db) {
    int id;
    double novo_preco;
    
    limpar_tela();
    printf("\n=== ATUALIZAR PREÇO ===\n\n");
    printf("Digite o ID do livro: ");
    scanf("%d", &id);
    printf("Digite o novo preço (R$): ");
    scanf("%lf", &novo_preco);
    
    if (novo_preco < 0) {
        printf("\n✗ Erro: Preço não pode ser negativo.\n");
        pausar();
        return;
    }
    
    const char *sql = "UPDATE livros SET preco = ? WHERE id = ?;";
    
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar statement: %s\n", sqlite3_errmsg(db));
        pausar();
        return;
    }
    
    sqlite3_bind_double(stmt, 1, novo_preco);
    sqlite3_bind_int(stmt, 2, id);
    
    rc = sqlite3_step(stmt);
    
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Erro ao atualizar: %s\n", sqlite3_errmsg(db));
    } else {
        // sqlite3_changes() retorna número de linhas afetadas
        int changes = sqlite3_changes(db);
        if (changes > 0) {
            printf("\n✓ Preço atualizado com sucesso!\n");
        } else {
            printf("\n✗ Livro com ID %d não encontrado.\n", id);
        }
    }
    
    sqlite3_finalize(stmt);
    pausar();
}

/*
 * FUNÇÃO: atualizar_estoque
 * DESCRIÇÃO: Adiciona ou remove unidades do estoque
 * PARÂMETRO: db - ponteiro para a conexão do banco de dados
 * 
 * EXPLICAÇÃO:
 * - Permite incrementar (entrada) ou decrementar (saída) estoque
 * - Verifica se quantidade é suficiente antes de remover
 */
void atualizar_estoque(sqlite3 *db) {
    int id, quantidade;
    char operacao;
    
    limpar_tela();
    printf("\n=== ATUALIZAR ESTOQUE ===\n\n");
    printf("Digite o ID do livro: ");
    scanf("%d", &id);
    
    // Primeiro, buscar estoque atual
    const char *sql_busca = "SELECT estoque FROM livros WHERE id = ?;";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql_busca, -1, &stmt, NULL);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro: %s\n", sqlite3_errmsg(db));
        pausar();
        return;
    }
    
    sqlite3_bind_int(stmt, 1, id);
    rc = sqlite3_step(stmt);
    
    if (rc != SQLITE_ROW) {
        printf("\n✗ Livro com ID %d não encontrado.\n", id);
        sqlite3_finalize(stmt);
        pausar();
        return;
    }
    
    int estoque_atual = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    
    printf("Estoque atual: %d unidades\n", estoque_atual);
    printf("\nOperação:\n");
    printf("  [E] Entrada (adicionar)\n");
    printf("  [S] Saída (remover)\n");
    printf("Escolha: ");
    limpar_buffer();
    scanf("%c", &operacao);
    
    printf("Quantidade: ");
    scanf("%d", &quantidade);
    
    if (quantidade <= 0) {
        printf("\n✗ Quantidade deve ser positiva.\n");
        pausar();
        return;
    }
    
    int novo_estoque;
    
    if (operacao == 'E' || operacao == 'e') {
        // Entrada: adicionar ao estoque
        novo_estoque = estoque_atual + quantidade;
    } else if (operacao == 'S' || operacao == 's') {
        // Saída: remover do estoque
        if (quantidade > estoque_atual) {
            printf("\n✗ Estoque insuficiente! (disponível: %d)\n", estoque_atual);
            pausar();
            return;
        }
        novo_estoque = estoque_atual - quantidade;
    } else {
        printf("\n✗ Operação inválida.\n");
        pausar();
        return;
    }
    
    // Atualizar estoque
    const char *sql_update = "UPDATE livros SET estoque = ? WHERE id = ?;";
    rc = sqlite3_prepare_v2(db, sql_update, -1, &stmt, NULL);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro: %s\n", sqlite3_errmsg(db));
        pausar();
        return;
    }
    
    sqlite3_bind_int(stmt, 1, novo_estoque);
    sqlite3_bind_int(stmt, 2, id);
    
    rc = sqlite3_step(stmt);
    
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Erro ao atualizar: %s\n", sqlite3_errmsg(db));
    } else {
        printf("\n✓ Estoque atualizado com sucesso!\n");
        printf("Estoque anterior: %d\n", estoque_atual);
        printf("Estoque atual: %d\n", novo_estoque);
    }
    
    sqlite3_finalize(stmt);
    pausar();
}

/*
 * FUNÇÃO: remover_livro
 * DESCRIÇÃO: Remove um livro do banco de dados
 * PARÂMETRO: db - ponteiro para a conexão do banco de dados
 * 
 * EXPLICAÇÃO:
 * - DELETE FROM remove registros
 * - WHERE especifica qual registro remover
 * - CUIDADO: DELETE sem WHERE remove TODOS os registros!
 * - Solicita confirmação do usuário antes de remover
 */
void remover_livro(sqlite3 *db) {
    int id;
    char confirmacao;
    
    limpar_tela();
    printf("\n=== REMOVER LIVRO ===\n\n");
    printf("Digite o ID do livro: ");
    scanf("%d", &id);
    
    // Primeiro, mostrar informações do livro
    const char *sql_busca = "SELECT titulo, autor FROM livros WHERE id = ?;";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql_busca, -1, &stmt, NULL);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro: %s\n", sqlite3_errmsg(db));
        pausar();
        return;
    }
    
    sqlite3_bind_int(stmt, 1, id);
    rc = sqlite3_step(stmt);
    
    if (rc != SQLITE_ROW) {
        printf("\n✗ Livro com ID %d não encontrado.\n", id);
        sqlite3_finalize(stmt);
        pausar();
        return;
    }
    
    // Exibir informações e pedir confirmação
    printf("\nLivro: %s\n", sqlite3_column_text(stmt, 0));
    printf("Autor: %s\n", sqlite3_column_text(stmt, 1));
    sqlite3_finalize(stmt);
    
    printf("\n⚠️  ATENÇÃO: Esta ação não pode ser desfeita!\n");
    printf("Confirma a remoção? [S/N]: ");
    limpar_buffer();
    scanf("%c", &confirmacao);
    
    if (confirmacao != 'S' && confirmacao != 's') {
        printf("\nOperação cancelada.\n");
        pausar();
        return;
    }
    
    // Remover livro
    const char *sql_delete = "DELETE FROM livros WHERE id = ?;";
    rc = sqlite3_prepare_v2(db, sql_delete, -1, &stmt, NULL);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro: %s\n", sqlite3_errmsg(db));
        pausar();
        return;
    }
    
    sqlite3_bind_int(stmt, 1, id);
    rc = sqlite3_step(stmt);
    
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Erro ao remover: %s\n", sqlite3_errmsg(db));
    } else {
        printf("\n✓ Livro removido com sucesso!\n");
    }
    
    sqlite3_finalize(stmt);
    pausar();
}

/*
 * FUNÇÃO: relatorio_estatisticas
 * DESCRIÇÃO: Exibe estatísticas gerais do banco de dados
 * PARÂMETRO: db - ponteiro para a conexão do banco de dados
 * 
 * EXPLICAÇÃO:
 * - COUNT(*) conta total de registros
 * - SUM() soma valores de uma coluna
 * - AVG() calcula média
 * - MIN() e MAX() encontram menor e maior valor
 */
void relatorio_estatisticas(sqlite3 *db) {
    limpar_tela();
    printf("\n=== ESTATÍSTICAS DA BIBLIOTECA ===\n\n");
    
    // Total de livros
    const char *sql_count = "SELECT COUNT(*) FROM livros;";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql_count, -1, &stmt, NULL);
    sqlite3_step(stmt);
    int total_livros = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    
    // Total em estoque
    const char *sql_estoque = "SELECT SUM(estoque) FROM livros;";
    sqlite3_prepare_v2(db, sql_estoque, -1, &stmt, NULL);
    sqlite3_step(stmt);
    int total_estoque = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    
    // Valor total do inventário
    const char *sql_valor = "SELECT SUM(preco * estoque) FROM livros;";
    sqlite3_prepare_v2(db, sql_valor, -1, &stmt, NULL);
    sqlite3_step(stmt);
    double valor_inventario = sqlite3_column_double(stmt, 0);
    sqlite3_finalize(stmt);
    
    // Preço médio
    const char *sql_media = "SELECT AVG(preco) FROM livros;";
    sqlite3_prepare_v2(db, sql_media, -1, &stmt, NULL);
    sqlite3_step(stmt);
    double preco_medio = sqlite3_column_double(stmt, 0);
    sqlite3_finalize(stmt);
    
    // Livro mais caro
    const char *sql_max = "SELECT titulo, preco FROM livros ORDER BY preco DESC LIMIT 1;";
    sqlite3_prepare_v2(db, sql_max, -1, &stmt, NULL);
    
    printf("📊 Resumo Geral:\n");
    printf("───────────────────────────────────────────\n");
    printf("Total de livros cadastrados:  %d\n", total_livros);
    printf("Total de unidades em estoque: %d\n", total_estoque);
    printf("Valor total do inventário:    R$ %.2f\n", valor_inventario);
    printf("Preço médio dos livros:       R$ %.2f\n", preco_medio);
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("\n💰 Livro mais caro:\n");
        printf("   %s - R$ %.2f\n", 
               sqlite3_column_text(stmt, 0),
               sqlite3_column_double(stmt, 1));
    }
    sqlite3_finalize(stmt);
    
    // Livro mais barato
    const char *sql_min = "SELECT titulo, preco FROM livros ORDER BY preco ASC LIMIT 1;";
    sqlite3_prepare_v2(db, sql_min, -1, &stmt, NULL);
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("\n💵 Livro mais barato:\n");
        printf("   %s - R$ %.2f\n", 
               sqlite3_column_text(stmt, 0),
               sqlite3_column_double(stmt, 1));
    }
    sqlite3_finalize(stmt);
    
    // Livros com estoque baixo (< 5)
    const char *sql_baixo = "SELECT titulo, estoque FROM livros WHERE estoque < 5 ORDER BY estoque;";
    sqlite3_prepare_v2(db, sql_baixo, -1, &stmt, NULL);
    
    printf("\n⚠️  Livros com estoque baixo (< 5 unidades):\n");
    int count_baixo = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        if (count_baixo == 0) {
            printf("   %-40s %s\n", "Título", "Estoque");
            printf("   ────────────────────────────────────────────────\n");
        }
        printf("   %-40s %d\n", 
               sqlite3_column_text(stmt, 0),
               sqlite3_column_int(stmt, 1));
        count_baixo++;
    }
    
    if (count_baixo == 0) {
        printf("   Nenhum livro com estoque baixo.\n");
    }
    
    sqlite3_finalize(stmt);
    pausar();
}

/*
 * FUNÇÃO: listar_por_autor
 * DESCRIÇÃO: Lista todos os livros agrupados por autor
 * PARÂMETRO: db - ponteiro para a conexão do banco de dados
 * 
 * EXPLICAÇÃO:
 * - GROUP BY agrupa registros por uma coluna
 * - COUNT(*) conta quantos livros cada autor tem
 * - Útil para ver distribuição de livros por autor
 */
void listar_por_autor(sqlite3 *db) {
    limpar_tela();
    printf("\n=== LIVROS POR AUTOR ===\n\n");
    
    const char *sql = "SELECT autor, COUNT(*) as quantidade, SUM(estoque) as total_estoque "
                      "FROM livros GROUP BY autor ORDER BY quantidade DESC;";
    
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro: %s\n", sqlite3_errmsg(db));
        pausar();
        return;
    }
    
    printf("%-30s %12s %15s\n", "Autor", "Quantidade", "Total Estoque");
    printf("───────────────────────────────────────────────────────────\n");
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("%-30s %12d %15d\n",
               sqlite3_column_text(stmt, 0),
               sqlite3_column_int(stmt, 1),
               sqlite3_column_int(stmt, 2));
    }
    
    sqlite3_finalize(stmt);
    pausar();
}

/*
 * FUNÇÃO: inserir_dados_exemplo
 * DESCRIÇÃO: Insere alguns livros de exemplo no banco de dados
 * PARÂMETRO: db - ponteiro para a conexão do banco de dados
 * 
 * EXPLICAÇÃO:
 * - Útil para popular o banco com dados de teste
 * - Usa transação para inserir múltiplos registros de forma eficiente
 * - BEGIN TRANSACTION + COMMIT ou ROLLBACK
 */
void inserir_dados_exemplo(sqlite3 *db) {
    limpar_tela();
    printf("\n=== INSERIR DADOS DE EXEMPLO ===\n\n");
    
    char confirmacao;
    printf("Isso adicionará 10 livros de exemplo ao banco.\n");
    printf("Confirma? [S/N]: ");
    limpar_buffer();
    scanf("%c", &confirmacao);
    
    if (confirmacao != 'S' && confirmacao != 's') {
        printf("\nOperação cancelada.\n");
        pausar();
        return;
    }
    
    // Iniciar transação para melhor performance
    sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, NULL);
    
    const char *livros_exemplo[][5] = {
        {"1984", "George Orwell", "Companhia das Letras", "1949", "29.90"},
        {"O Senhor dos Anéis", "J.R.R. Tolkien", "Martins Fontes", "1954", "49.90"},
        {"Dom Casmurro", "Machado de Assis", "Penguin", "1899", "19.90"},
        {"Cem Anos de Solidão", "Gabriel García Márquez", "Record", "1967", "39.90"},
        {"O Pequeno Príncipe", "Antoine de Saint-Exupéry", "Agir", "1943", "24.90"},
        {"Harry Potter e a Pedra Filosofal", "J.K. Rowling", "Rocco", "1997", "34.90"},
        {"O Hobbit", "J.R.R. Tolkien", "Martins Fontes", "1937", "32.90"},
        {"A Revolução dos Bichos", "George Orwell", "Companhia das Letras", "1945", "27.90"},
        {"O Cortiço", "Aluísio Azevedo", "Ática", "1890", "22.90"},
        {"Grande Sertão: Veredas", "Guimarães Rosa", "Nova Fronteira", "1956", "44.90"}
    };
    
    const char *sql = "INSERT INTO livros (titulo, autor, editora, ano, preco, estoque) "
                      "VALUES (?, ?, ?, ?, ?, ?);";
    
    sqlite3_stmt *stmt;
    int sucesso = 1;
    
    for (int i = 0; i < 10; i++) {
        sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
        
        sqlite3_bind_text(stmt, 1, livros_exemplo[i][0], -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, livros_exemplo[i][1], -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, livros_exemplo[i][2], -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 4, atoi(livros_exemplo[i][3]));
        sqlite3_bind_double(stmt, 5, atof(livros_exemplo[i][4]));
        sqlite3_bind_int(stmt, 6, 10 + (i * 2));  // Estoque variável
        
        int rc = sqlite3_step(stmt);
        
        if (rc != SQLITE_DONE) {
            fprintf(stderr, "Erro ao inserir livro %d: %s\n", i+1, sqlite3_errmsg(db));
            sucesso = 0;
            break;
        }
        
        sqlite3_finalize(stmt);
    }
    
    if (sucesso) {
        // Confirmar transação
        sqlite3_exec(db, "COMMIT;", NULL, NULL, NULL);
        printf("\n✓ 10 livros de exemplo inseridos com sucesso!\n");
    } else {
        // Desfazer transação em caso de erro
        sqlite3_exec(db, "ROLLBACK;", NULL, NULL, NULL);
        printf("\n✗ Erro ao inserir dados. Operação cancelada.\n");
    }
    
    pausar();
}

// ============================================================================
// MENU PRINCIPAL
// ============================================================================

/*
 * FUNÇÃO: exibir_menu
 * DESCRIÇÃO: Exibe o menu principal do sistema
 */
void exibir_menu() {
    limpar_tela();
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════╗\n");
    printf("║     SISTEMA DE GERENCIAMENTO DE BIBLIOTECA - SQLite      ║\n");
    printf("╚═══════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("  📚 GERENCIAMENTO DE LIVROS\n");
    printf("     1. Adicionar novo livro\n");
    printf("     2. Listar todos os livros\n");
    printf("     3. Buscar livro por ID\n");
    printf("     4. Buscar livro por título\n");
    printf("     5. Atualizar preço\n");
    printf("     6. Atualizar estoque\n");
    printf("     7. Remover livro\n");
    printf("\n");
    printf("  📊 RELATÓRIOS\n");
    printf("     8. Estatísticas gerais\n");
    printf("     9. Listar por autor\n");
    printf("\n");
    printf("  🔧 UTILITÁRIOS\n");
    printf("    10. Inserir dados de exemplo\n");
    printf("\n");
    printf("     0. Sair\n");
    printf("\n");
    printf("───────────────────────────────────────────────────────────\n");
    printf("Escolha uma opção: ");
}

// ============================================================================
// FUNÇÃO PRINCIPAL
// ============================================================================

/*
 * FUNÇÃO: main
 * DESCRIÇÃO: Ponto de entrada do programa
 * 
 * FLUXO:
 * 1. Abrir/criar banco de dados
 * 2. Criar tabela (se não existir)
 * 3. Loop do menu principal
 * 4. Fechar banco ao sair
 */
int main() {
    sqlite3 *db;
    int opcao;
    
    // Abrir ou criar banco de dados
    // Se o arquivo não existir, SQLite cria automaticamente
    int rc = sqlite3_open("biblioteca.db", &db);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao abrir banco de dados: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    
    printf("✓ Banco de dados aberto com sucesso!\n");
    
    // Criar tabela de livros se não existir
    if (criar_tabela_livros(db) != SQLITE_OK) {
        sqlite3_close(db);
        return 1;
    }
    
    // Loop principal do menu
    do {
        exibir_menu();
        
        if (scanf("%d", &opcao) != 1) {
            limpar_buffer();
            opcao = -1;  // Opção inválida
        }
        
        switch (opcao) {
            case 1:
                adicionar_livro(db);
                break;
            case 2:
                listar_livros(db);
                break;
            case 3:
                buscar_livro_por_id(db);
                break;
            case 4:
                buscar_livro_por_titulo(db);
                break;
            case 5:
                atualizar_preco(db);
                break;
            case 6:
                atualizar_estoque(db);
                break;
            case 7:
                remover_livro(db);
                break;
            case 8:
                relatorio_estatisticas(db);
                break;
            case 9:
                listar_por_autor(db);
                break;
            case 10:
                inserir_dados_exemplo(db);
                break;
            case 0:
                limpar_tela();
                printf("\n✓ Encerrando sistema...\n");
                printf("Obrigado por usar o Sistema de Biblioteca!\n\n");
                break;
            default:
                printf("\n✗ Opção inválida! Tente novamente.\n");
                pausar();
        }
        
    } while (opcao != 0);
    
    // Fechar banco de dados
    sqlite3_close(db);
    
    return 0;
}
