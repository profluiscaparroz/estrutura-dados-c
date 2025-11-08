# ============================================================================
# Makefile para Exemplos de SQLite em C
# ============================================================================
#
# OBJETIVO:
# Este Makefile facilita a compilação de todos os exemplos de SQLite.
#
# COMANDOS:
#   make          - Compila todos os exemplos
#   make examples - Compila todos os exemplos
#   make biblioteca - Compila apenas o sistema de biblioteca
#   make clean    - Remove arquivos compilados
#   make cleandb  - Remove bancos de dados de exemplo
#   make cleanall - Remove tudo (binários e bancos)
#
# ============================================================================

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LIBS = -lsqlite3

# Executáveis
TARGET = biblioteca
EXAMPLES = 01_create_table 02_insert 03_select 04_update 05_delete 06_joins 07_transacoes

# Arquivos fonte
SRC = biblioteca_completa.c

# Bancos de dados
DBS = biblioteca.db exemplo01.db exemplo02.db exemplo03.db exemplo04.db exemplo05.db exemplo06.db exemplo07.db

# ============================================================================
# REGRAS DE COMPILAÇÃO
# ============================================================================

# Regra padrão: compila todos os exemplos
all: examples $(TARGET)
	@echo ""
	@echo "✅ Compilação concluída com sucesso!"
	@echo ""
	@echo "Execute os exemplos:"
	@echo "  ./01_create_table"
	@echo "  ./02_insert"
	@echo "  ./03_select"
	@echo "  ./04_update"
	@echo "  ./05_delete"
	@echo "  ./06_joins"
	@echo "  ./07_transacoes"
	@echo "  ./biblioteca"
	@echo ""

# Compilar todos os exemplos
examples: $(EXAMPLES)
	@echo "✓ Exemplos compilados!"

# Regra genérica para compilar exemplos
%: %.c
	@echo "Compilando $<..."
	@$(CC) $(CFLAGS) $< -o $@ $(LIBS)

# Compilar sistema de biblioteca
$(TARGET): $(SRC)
	@echo "Compilando $(SRC)..."
	@$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

# Compilar e executar
run: $(TARGET)
	@echo "Executando $(TARGET)..."
	@echo ""
	./$(TARGET)

# Limpar arquivos compilados
clean:
	@echo "Removendo arquivos compilados..."
	@rm -f $(TARGET) $(EXAMPLES)
	@echo "✓ Limpeza concluída!"

# Limpar bancos de dados
cleandb:
	@echo "Removendo bancos de dados..."
	@rm -f $(DBS)
	@echo "✓ Bancos de dados removidos!"

# Limpar tudo (binários + bancos)
cleanall: clean cleandb
	@echo "✓ Limpeza completa concluída!"

# Testar um exemplo específico
test-%: %
	@echo ""
	@echo "=== Executando $< ==="
	@echo ""
	@./$<

# Ajuda
help:
	@echo "Comandos disponíveis:"
	@echo "  make              - Compila todos os exemplos"
	@echo "  make examples     - Compila todos os exemplos"
	@echo "  make biblioteca   - Compila apenas o sistema de biblioteca"
	@echo "  make 01_create_table - Compila exemplo específico"
	@echo "  make test-01_create_table - Compila e executa exemplo específico"
	@echo "  make clean        - Remove arquivos compilados"
	@echo "  make cleandb      - Remove bancos de dados"
	@echo "  make cleanall     - Remove tudo"
	@echo "  make help         - Mostra esta mensagem"
	@echo ""
	@echo "Exemplos disponíveis:"
	@echo "  01_create_table   - Criar tabelas"
	@echo "  02_insert         - Inserir dados"
	@echo "  03_select         - Consultar dados"
	@echo "  04_update         - Atualizar dados"
	@echo "  05_delete         - Deletar dados"
	@echo "  06_joins          - Relacionar tabelas (JOINs)"
	@echo "  07_transacoes     - Transações e atomicidade"
	@echo "  biblioteca        - Sistema completo de biblioteca"

# Evitar conflitos com arquivos de mesmo nome
.PHONY: all examples run clean cleandb cleanall help test-% biblioteca
