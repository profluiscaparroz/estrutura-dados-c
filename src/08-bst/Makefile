# Makefile para BST (Binary Search Tree)
# Compilação e testes automatizados

# Configurações do compilador
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic
DEBUG_FLAGS = -g -DDEBUG
RELEASE_FLAGS = -O2 -DNDEBUG

# Arquivos
SOURCES = bst.c
EXECUTABLE = bst
TEST_EXECUTABLE = test_bst

# Regras principais
.PHONY: all clean debug release test help

# Compilação padrão
all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	@echo "🔨 Compilando BST..."
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SOURCES)
	@echo "✅ Compilação concluída: $(EXECUTABLE)"

# Versão de debug
debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean $(EXECUTABLE)
	@echo "🐛 Versão DEBUG compilada"

# Versão otimizada
release: CFLAGS += $(RELEASE_FLAGS)
release: clean $(EXECUTABLE)
	@echo "🚀 Versão RELEASE compilada"

# Executar testes
test: $(EXECUTABLE)
	@echo "🧪 Executando testes da BST..."
	@echo "============================================"
	./$(EXECUTABLE)
	@echo "============================================"
	@echo "✅ Testes concluídos"

# Executar com valgrind (se disponível)
memcheck: $(EXECUTABLE)
	@echo "🔍 Verificando memória com Valgrind..."
	@if command -v valgrind >/dev/null 2>&1; then \
		valgrind --leak-check=full --show-leak-kinds=all ./$(EXECUTABLE); \
	else \
		echo "❌ Valgrind não encontrado, executando normalmente..."; \
		./$(EXECUTABLE); \
	fi

# Análise estática (se disponível)
static-analysis:
	@echo "📊 Executando análise estática..."
	@if command -v cppcheck >/dev/null 2>&1; then \
		cppcheck --enable=all --std=c99 $(SOURCES); \
	else \
		echo "❌ cppcheck não encontrado"; \
	fi

# Limpeza
clean:
	@echo "🧹 Limpando arquivos compilados..."
	rm -f $(EXECUTABLE) $(TEST_EXECUTABLE) *.o *.out
	@echo "✅ Limpeza concluída"

# Informações sobre alvos disponíveis
help:
	@echo "📖 Alvos disponíveis:"
	@echo "  all          - Compilar BST (padrão)"
	@echo "  debug        - Compilar versão debug"
	@echo "  release      - Compilar versão otimizada"
	@echo "  test         - Compilar e executar testes"
	@echo "  memcheck     - Executar com verificação de memória"
	@echo "  static-analysis - Executar análise estática"
	@echo "  clean        - Limpar arquivos compilados"
	@echo "  help         - Mostrar esta ajuda"

# Informações de status
status:
	@echo "📋 Status do projeto BST:"
	@echo "  Fontes: $(SOURCES)"
	@echo "  Executável: $(EXECUTABLE)"
	@echo "  Compilador: $(CC)"
	@echo "  Flags: $(CFLAGS)"
	@if [ -f $(EXECUTABLE) ]; then \
		echo "  Status: ✅ Compilado"; \
		echo "  Tamanho: $$(du -h $(EXECUTABLE) | cut -f1)"; \
	else \
		echo "  Status: ❌ Não compilado"; \
	fi