# Makefile para exemplos de Vetores e Matrizes
# Uso: make [target]
# Para compilar todos: make all
# Para limpar: make clean

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS = -lm

# Diretórios
VETOR_DIR = vetor/exemplo
MATRIZ_DIR = matriz
RAIZ_DIR = .

# Executáveis
EXECUTAVEIS = exemploSimples \
              exemploStringVetores \
              exemploAvancadoVetor \
              exemploAvancadoMatriz \
              aplicacoesPraticas \
              errosComuns \
              exemploMatrizSimples \
              exemploMatrizDinamica \
              exemploOperacoesMatrizes

.PHONY: all clean help test exemplos-basicos exemplos-avancados

# Target padrão
all: $(EXECUTAVEIS)

# Exemplos básicos
exemplos-basicos: exemploSimples exemploStringVetores exemploMatrizSimples
	@echo "Exemplos básicos compilados com sucesso!"

# Exemplos avançados
exemplos-avancados: exemploAvancadoVetor exemploAvancadoMatriz aplicacoesPraticas errosComuns
	@echo "Exemplos avançados compilados com sucesso!"

# Compilação dos executáveis
exemploSimples: $(VETOR_DIR)/exemploSimples.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

exemploStringVetores: $(VETOR_DIR)/exemploStringVetores.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

exemploAvancadoVetor: $(VETOR_DIR)/exemploAvancado.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

exemploAvancadoMatriz: $(MATRIZ_DIR)/exemploAvancado.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

aplicacoesPraticas: $(RAIZ_DIR)/aplicacoes-praticas.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

errosComuns: $(RAIZ_DIR)/erros-comuns-debug.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

exemploMatrizSimples: $(MATRIZ_DIR)/exemploMatrizSimples.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

exemploMatrizDinamica: $(MATRIZ_DIR)/exemploMatrizDinamica.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

exemploOperacoesMatrizes: $(MATRIZ_DIR)/exemploOperacoesMatrizes.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

# Testes rápidos
test: exemplos-basicos
	@echo "=== Testando exemplo simples de vetor ==="
	@echo "1\n2\n3\n4\n5" | ./exemploSimples || true
	@echo ""
	@echo "=== Testando exemplo de strings com vetores ==="
	@echo "teste\nstring\nfim" | ./exemploStringVetores || true
	@echo ""
	@echo "=== Testando exemplo simples de matriz ==="
	@./exemploMatrizSimples
	@echo ""
	@echo "Testes básicos concluídos!"

# Limpeza
clean:
	rm -f $(EXECUTAVEIS)
	@echo "Arquivos executáveis removidos!"

# Compilação com otimizações
release: CFLAGS += -O3 -DNDEBUG
release: all

# Compilação para debug/sanitizers
debug: CFLAGS += -fsanitize=address -fsanitize=undefined
debug: all

# Ajuda
help:
	@echo "Makefile para Exemplos de Vetores e Matrizes"
	@echo ""
	@echo "Targets disponíveis:"
	@echo "  all                 - Compila todos os exemplos"
	@echo "  exemplos-basicos    - Compila apenas exemplos básicos"
	@echo "  exemplos-avancados  - Compila apenas exemplos avançados"
	@echo "  test               - Compila e testa exemplos básicos"
	@echo "  clean              - Remove todos os executáveis"
	@echo "  release            - Compila com otimizações (-O3)"
	@echo "  debug              - Compila com sanitizers"
	@echo "  help               - Mostra esta ajuda"
	@echo ""
	@echo "Exemplos individuais:"
	@echo "  exemploSimples          - Exemplo básico de vetores"
	@echo "  exemploStringVetores    - Manipulação de strings com vetores"
	@echo "  exemploAvancadoVetor    - Exemplos avançados de vetores"
	@echo "  exemploAvancadoMatriz   - Exemplos avançados de matrizes"
	@echo "  aplicacoesPraticas      - Aplicações práticas"
	@echo "  errosComuns            - Demonstração de erros comuns"
	@echo ""
	@echo "Uso:"
	@echo "  make                   # Compila tudo"
	@echo "  make test              # Testa exemplos básicos"
	@echo "  make exemploSimples    # Compila apenas exemplo simples"
	@echo "  make clean             # Limpa executáveis"