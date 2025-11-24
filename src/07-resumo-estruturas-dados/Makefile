# Makefile para Resumo de Estruturas de Dados
# 
# Uso:
#   make          - Compila o exemplo completo
#   make run      - Compila e executa o exemplo
#   make clean    - Remove arquivos compilados
#   make help     - Mostra esta ajuda

CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2
TARGET = exemplo-completo
SRC = exemplo-completo.c

# Cores para output
GREEN = \033[0;32m
YELLOW = \033[1;33m
NC = \033[0m # No Color

.PHONY: all run clean help

all: $(TARGET)
	@echo "$(GREEN)✓ Compilação concluída com sucesso!$(NC)"
	@echo "Execute com: ./$(TARGET)"

$(TARGET): $(SRC)
	@echo "$(YELLOW)Compilando $(SRC)...$(NC)"
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: all
	@echo "$(GREEN)Executando demonstração...$(NC)"
	@echo ""
	./$(TARGET)

clean:
	@echo "$(YELLOW)Limpando arquivos compilados...$(NC)"
	rm -f $(TARGET)
	@echo "$(GREEN)✓ Limpeza concluída!$(NC)"

help:
	@echo "Makefile para Resumo de Estruturas de Dados"
	@echo ""
	@echo "Comandos disponíveis:"
	@echo "  make          - Compila o exemplo completo"
	@echo "  make run      - Compila e executa o exemplo"
	@echo "  make clean    - Remove arquivos compilados"
	@echo "  make help     - Mostra esta ajuda"
	@echo ""
	@echo "Exemplo de uso:"
	@echo "  $$ make run"
