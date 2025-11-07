# ============================================================================
# Makefile para Sistema de Biblioteca com SQLite
# ============================================================================
#
# OBJETIVO:
# Este Makefile facilita a compilação do sistema de biblioteca.
#
# COMANDOS:
#   make          - Compila o programa
#   make run      - Compila e executa o programa
#   make clean    - Remove arquivos compilados
#   make cleandb  - Remove o banco de dados
#   make cleanall - Remove tudo (binários e banco)
#
# ============================================================================

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LIBS = -lsqlite3

# Nome do executável
TARGET = biblioteca

# Arquivos fonte
SRC = biblioteca_completa.c

# Banco de dados
DB = biblioteca.db

# ============================================================================
# REGRAS DE COMPILAÇÃO
# ============================================================================

# Regra padrão: compila o programa
all: $(TARGET)
	@echo "✓ Compilação concluída com sucesso!"
	@echo "Execute com: ./$(TARGET)"

# Compilar o programa
$(TARGET): $(SRC)
	@echo "Compilando $(SRC)..."
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

# Compilar e executar
run: $(TARGET)
	@echo "Executando $(TARGET)..."
	@echo ""
	./$(TARGET)

# Limpar arquivos compilados
clean:
	@echo "Removendo arquivos compilados..."
	rm -f $(TARGET)
	@echo "✓ Limpeza concluída!"

# Limpar banco de dados
cleandb:
	@echo "Removendo banco de dados..."
	rm -f $(DB)
	@echo "✓ Banco de dados removido!"

# Limpar tudo (binários + banco)
cleanall: clean cleandb
	@echo "✓ Limpeza completa concluída!"

# Ajuda
help:
	@echo "Comandos disponíveis:"
	@echo "  make          - Compila o programa"
	@echo "  make run      - Compila e executa"
	@echo "  make clean    - Remove arquivos compilados"
	@echo "  make cleandb  - Remove o banco de dados"
	@echo "  make cleanall - Remove tudo"
	@echo "  make help     - Mostra esta mensagem"

# Evitar conflitos com arquivos de mesmo nome
.PHONY: all run clean cleandb cleanall help
