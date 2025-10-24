# Makefile para Sistema de Gerenciamento de Pedidos de Restaurante
# Demonstra compilação de projeto com estruturas de dados

# Compilador
CC = gcc

# Flags de compilação
# -Wall: Mostra todos os warnings
# -Wextra: Warnings extras
# -std=c99: Usa padrão C99
# -O2: Otimização nível 2 (boa performance sem comprometer debug)
CFLAGS = -Wall -Wextra -std=c99 -O2

# Flags de debug (use 'make debug' para compilar com debug)
DEBUG_FLAGS = -g -DDEBUG

# Nome do executável
TARGET = restaurante

# Arquivo fonte
SRC = sistema_restaurante.c

# Arquivo objeto
OBJ = $(SRC:.c=.o)

# Regra padrão (executada ao rodar apenas 'make')
all: $(TARGET)
	@echo "✓ Compilação concluída com sucesso!"
	@echo "→ Execute com: ./$(TARGET)"

# Regra para criar o executável
$(TARGET): $(SRC)
	@echo "→ Compilando $(SRC)..."
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Regra para compilar com debug
debug: $(SRC)
	@echo "→ Compilando com símbolos de debug..."
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(SRC) -o $(TARGET)
	@echo "✓ Versão debug compilada!"
	@echo "→ Execute com gdb: gdb ./$(TARGET)"

# Regra para executar o programa
run: $(TARGET)
	@echo "→ Executando $(TARGET)..."
	@./$(TARGET)

# Regra para limpar arquivos gerados
clean:
	@echo "→ Limpando arquivos compilados..."
	@rm -f $(TARGET) $(OBJ) *~
	@echo "✓ Limpeza concluída!"

# Regra para verificar warnings e erros
check: $(SRC)
	@echo "→ Verificando código..."
	$(CC) $(CFLAGS) -fsyntax-only $(SRC)
	@echo "✓ Código verificado - sem erros de sintaxe!"

# Regra para mostrar ajuda
help:
	@echo "════════════════════════════════════════════════════════════"
	@echo "  Makefile - Sistema de Gerenciamento de Restaurante"
	@echo "════════════════════════════════════════════════════════════"
	@echo ""
	@echo "Comandos disponíveis:"
	@echo ""
	@echo "  make          - Compila o programa"
	@echo "  make debug    - Compila com símbolos de debug"
	@echo "  make run      - Compila e executa o programa"
	@echo "  make clean    - Remove arquivos compilados"
	@echo "  make check    - Verifica sintaxe do código"
	@echo "  make help     - Mostra esta ajuda"
	@echo ""
	@echo "════════════════════════════════════════════════════════════"

# Declara regras que não são arquivos
.PHONY: all clean run debug check help
