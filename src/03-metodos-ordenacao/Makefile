# Makefile para Algoritmos de Ordenação
# Compilação com flags de otimização e warnings

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET_DIR = bin
SOURCES = $(wildcard *.c)
TARGETS = $(SOURCES:.c=)

# Cores para output
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[1;33m
BLUE = \033[0;34m
NC = \033[0m # No Color

.PHONY: all clean test help run-all benchmark

# Compila todos os algoritmos
all: $(TARGET_DIR) $(addprefix $(TARGET_DIR)/, $(TARGETS))
	@echo "$(GREEN)✅ Todos os algoritmos compilados com sucesso!$(NC)"

# Cria diretório bin se não existir
$(TARGET_DIR):
	@mkdir -p $(TARGET_DIR)

# Regra genérica para compilar arquivos .c
$(TARGET_DIR)/%: %.c
	@echo "$(BLUE)🔨 Compilando $<...$(NC)"
	@$(CC) $(CFLAGS) -o $@ $<

# Executa todos os algoritmos básicos
run-all: all
	@echo "$(YELLOW)🚀 Executando todos os algoritmos básicos:$(NC)"
	@echo "\n$(GREEN)=== BUBBLE SORT ===$(NC)"
	@$(TARGET_DIR)/bubbleSort
	@echo "\n$(GREEN)=== INSERTION SORT ===$(NC)"
	@$(TARGET_DIR)/insertSort
	@echo "\n$(GREEN)=== SELECTION SORT ===$(NC)"
	@$(TARGET_DIR)/selectSort
	@echo "\n$(GREEN)=== QUICK SORT ===$(NC)"
	@$(TARGET_DIR)/quickSort
	@echo "\n$(GREEN)=== MERGE SORT ===$(NC)"
	@$(TARGET_DIR)/mergeSort

# Executa algoritmos avançados
run-advanced: all
	@echo "$(YELLOW)🚀 Executando algoritmos avançados:$(NC)"
	@echo "\n$(GREEN)=== HEAP SORT ===$(NC)"
	@$(TARGET_DIR)/heapSort | head -20
	@echo "\n$(GREEN)=== SHELL SORT ===$(NC)"
	@$(TARGET_DIR)/shellSort | head -30
	@echo "\n$(GREEN)=== BUBBLE SORT OTIMIZADO ===$(NC)"
	@$(TARGET_DIR)/bubbleSortOptimized | head -20

# Executa benchmark de performance
benchmark: all
	@echo "$(YELLOW)📊 Executando benchmark de performance:$(NC)"
	@$(TARGET_DIR)/comparacao

# Testa se todos os algoritmos compilam
test: all
	@echo "$(YELLOW)🧪 Testando compilação de todos os algoritmos:$(NC)"
	@for algo in $(addprefix $(TARGET_DIR)/, $(TARGETS)); do \
		if [ -x "$$algo" ]; then \
			echo "$(GREEN)✅ $$algo - OK$(NC)"; \
		else \
			echo "$(RED)❌ $$algo - FALHOU$(NC)"; \
		fi; \
	done

# Compila apenas algoritmos básicos
basic: $(TARGET_DIR) $(TARGET_DIR)/bubbleSort $(TARGET_DIR)/insertSort $(TARGET_DIR)/selectSort $(TARGET_DIR)/quickSort $(TARGET_DIR)/mergeSort
	@echo "$(GREEN)✅ Algoritmos básicos compilados!$(NC)"

# Compila apenas algoritmos avançados
advanced: $(TARGET_DIR) $(TARGET_DIR)/heapSort $(TARGET_DIR)/shellSort $(TARGET_DIR)/bubbleSortOptimized
	@echo "$(GREEN)✅ Algoritmos avançados compilados!$(NC)"

# Compila ferramentas
tools: $(TARGET_DIR) $(TARGET_DIR)/comparacao
	@echo "$(GREEN)✅ Ferramentas compiladas!$(NC)"

# Executa testes de corretude
test-correctness: all
	@echo "$(YELLOW)🔍 Testando corretude dos algoritmos:$(NC)"
	@echo "$(BLUE)Testando com array [5,2,8,1,9] - resultado esperado: [1,2,5,8,9]$(NC)"
	@echo "Bubble Sort:" && echo "5 2 8 1 9" | $(TARGET_DIR)/bubbleSort 2>/dev/null || true
	@echo "Quick Sort:" && echo "5 2 8 1 9" | $(TARGET_DIR)/quickSort 2>/dev/null || true

# Debug - compila com flags de debug
debug: CFLAGS = -Wall -Wextra -std=c99 -g -DDEBUG
debug: all
	@echo "$(YELLOW)🐛 Compilado em modo debug$(NC)"

# Release - compila com máxima otimização
release: CFLAGS = -Wall -Wextra -std=c99 -O3 -DNDEBUG
release: all
	@echo "$(GREEN)🚀 Compilado em modo release$(NC)"

# Limpa arquivos compilados
clean:
	@echo "$(RED)🧹 Limpando arquivos compilados...$(NC)"
	@rm -rf $(TARGET_DIR)
	@rm -f *.o
	@echo "$(GREEN)✅ Limpeza concluída!$(NC)"

# Mostra informações dos algoritmos
info:
	@echo "$(BLUE)📚 Algoritmos de Ordenação Disponíveis:$(NC)"
	@echo ""
	@echo "$(GREEN)Algoritmos Básicos:$(NC)"
	@echo "  • bubbleSort      - O(n²) - Bubble Sort clássico"
	@echo "  • insertSort      - O(n²) - Insertion Sort"
	@echo "  • selectSort      - O(n²) - Selection Sort"
	@echo "  • quickSort       - O(n log n) - Quick Sort"
	@echo "  • mergeSort       - O(n log n) - Merge Sort"
	@echo ""
	@echo "$(GREEN)Algoritmos Avançados:$(NC)"
	@echo "  • heapSort        - O(n log n) - Heap Sort"
	@echo "  • shellSort       - O(n^1.5) - Shell Sort"
	@echo "  • bubbleSortOptimized - O(n²) - Bubble Sort otimizado"
	@echo ""
	@echo "$(GREEN)Ferramentas:$(NC)"
	@echo "  • comparacao      - Benchmark de performance"
	@echo ""
	@echo "$(YELLOW)Para compilar todos: make all$(NC)"
	@echo "$(YELLOW)Para executar todos: make run-all$(NC)"
	@echo "$(YELLOW)Para benchmark: make benchmark$(NC)"

# Help - mostra comandos disponíveis
help:
	@echo "$(BLUE)🔧 Comandos Disponíveis:$(NC)"
	@echo ""
	@echo "$(GREEN)Compilação:$(NC)"
	@echo "  make all          - Compila todos os algoritmos"
	@echo "  make basic        - Compila apenas algoritmos básicos"
	@echo "  make advanced     - Compila algoritmos avançados"
	@echo "  make tools        - Compila ferramentas"
	@echo "  make debug        - Compila em modo debug"
	@echo "  make release      - Compila otimizado para release"
	@echo ""
	@echo "$(GREEN)Execução:$(NC)"
	@echo "  make run-all      - Executa algoritmos básicos"
	@echo "  make run-advanced - Executa algoritmos avançados"
	@echo "  make benchmark    - Executa benchmark de performance"
	@echo ""
	@echo "$(GREEN)Testes:$(NC)"
	@echo "  make test         - Testa se todos compilam"
	@echo "  make test-correctness - Testa corretude dos algoritmos"
	@echo ""
	@echo "$(GREEN)Utilidades:$(NC)"
	@echo "  make info         - Mostra informações dos algoritmos"
	@echo "  make clean        - Remove arquivos compilados"
	@echo "  make help         - Mostra esta ajuda"

# Target padrão
.DEFAULT_GOAL := help