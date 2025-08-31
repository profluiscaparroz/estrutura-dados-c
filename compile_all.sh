#!/bin/bash

# ====================================================================
# SCRIPT DE COMPILAÇÃO PRINCIPAL - ESTRUTURA DE DADOS EM C
# ====================================================================
# 
# Este script compila e testa todos os arquivos C do repositório
# de Estrutura de Dados em C.
# 
# Funcionalidades:
# - Compilação automática de todos os diretórios
# - Execução de testes automatizados
# - Relatório de cobertura de compilação
# - Detecção de erros e avisos
# - Suporte a diferentes modos (debug, release, test)
# 
# Uso:
#   ./compile_all.sh [modo] [diretorio]
# 
# Modos disponíveis:
#   all     - Compila tudo (padrão)
#   test    - Compila e executa testes
#   clean   - Limpa arquivos compilados
#   debug   - Compilação com símbolos de debug
#   release - Compilação otimizada
#   help    - Mostra esta ajuda
# 
# Exemplos:
#   ./compile_all.sh
#   ./compile_all.sh test
#   ./compile_all.sh debug 08-bst
#   ./compile_all.sh clean
# 
# Autor: Estrutura de Dados em C
# Data: 2024
# ====================================================================

set -e  # Parar em caso de erro

# Cores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Configurações
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SRC_DIR="$SCRIPT_DIR/src"
CC="gcc"
CFLAGS="-Wall -Wextra -std=c99 -pedantic"
DEBUG_FLAGS="-g -DDEBUG"
RELEASE_FLAGS="-O2 -DNDEBUG"

# Contadores
total_dirs=0
compiled_dirs=0
failed_dirs=0
total_files=0
compiled_files=0
failed_files=0

# Arrays para acompanhar resultados
declare -a failed_compilations
declare -a successful_compilations

# ==================== FUNÇÕES UTILITÁRIAS ====================

print_header() {
    echo -e "${CYAN}╔═══════════════════════════════════════════════════════════╗${NC}"
    echo -e "${CYAN}║${NC}               ESTRUTURA DE DADOS EM C                    ${CYAN}║${NC}"
    echo -e "${CYAN}║${NC}            Script de Compilação Principal                ${CYAN}║${NC}"
    echo -e "${CYAN}╚═══════════════════════════════════════════════════════════╝${NC}"
    echo
}

print_section() {
    echo -e "\n${BLUE}=== $1 ===${NC}"
}

print_success() {
    echo -e "${GREEN}✅ $1${NC}"
}

print_warning() {
    echo -e "${YELLOW}⚠️  $1${NC}"
}

print_error() {
    echo -e "${RED}❌ $1${NC}"
}

print_info() {
    echo -e "${PURPLE}ℹ️  $1${NC}"
}

# ==================== FUNÇÃO DE AJUDA ====================

show_help() {
    echo "Script de Compilação - Estrutura de Dados em C"
    echo
    echo "USO:"
    echo "  $0 [modo] [diretorio_especifico]"
    echo
    echo "MODOS:"
    echo "  all     - Compila todos os arquivos (padrão)"
    echo "  test    - Compila e executa testes"
    echo "  clean   - Limpa arquivos compilados"
    echo "  debug   - Compilação com símbolos de debug"
    echo "  release - Compilação otimizada"
    echo "  help    - Mostra esta ajuda"
    echo
    echo "EXEMPLOS:"
    echo "  $0                    # Compila tudo"
    echo "  $0 test               # Compila e testa tudo"
    echo "  $0 debug 08-bst       # Compila BST em modo debug"
    echo "  $0 clean              # Limpa arquivos compilados"
    echo "  $0 release            # Compilação otimizada"
    echo
    echo "ESTRUTURA DE DIRETÓRIOS SUPORTADOS:"
    find "$SRC_DIR" -maxdepth 1 -type d -name "[0-9]*" | sort | sed 's|.*/|  |'
}

# ==================== COMPILAÇÃO DE DIRETÓRIOS ====================

compile_directory() {
    local dir="$1"
    local mode="$2"
    local dir_name=$(basename "$dir")
    
    print_info "Processando $dir_name..."
    
    cd "$dir"
    
    # Verificar se tem Makefile
    if [ -f "Makefile" ]; then
        compile_with_makefile "$dir_name" "$mode"
    else
        compile_c_files "$dir_name" "$mode"
    fi
    
    cd - > /dev/null
}

compile_with_makefile() {
    local dir_name="$1"
    local mode="$2"
    
    print_info "  Usando Makefile em $dir_name"
    
    case "$mode" in
        "clean")
            if make clean 2>/dev/null; then
                print_success "  Limpeza concluída em $dir_name"
            else
                print_warning "  Falha na limpeza em $dir_name"
            fi
            ;;
        "test")
            if make clean 2>/dev/null && make test 2>/dev/null; then
                print_success "  Testes executados com sucesso em $dir_name"
                ((compiled_dirs++))
                successful_compilations+=("$dir_name (Makefile + test)")
            else
                print_error "  Falha nos testes em $dir_name"
                ((failed_dirs++))
                failed_compilations+=("$dir_name (Makefile test)")
            fi
            ;;
        "debug")
            if make clean 2>/dev/null && make debug 2>/dev/null; then
                print_success "  Debug compilado em $dir_name"
                ((compiled_dirs++))
                successful_compilations+=("$dir_name (Makefile debug)")
            else
                print_error "  Falha na compilação debug em $dir_name"
                ((failed_dirs++))
                failed_compilations+=("$dir_name (Makefile debug)")
            fi
            ;;
        "release")
            if make clean 2>/dev/null && make release 2>/dev/null; then
                print_success "  Release compilado em $dir_name"
                ((compiled_dirs++))
                successful_compilations+=("$dir_name (Makefile release)")
            else
                print_error "  Falha na compilação release em $dir_name"
                ((failed_dirs++))
                failed_compilations+=("$dir_name (Makefile release)")
            fi
            ;;
        *)
            if make clean 2>/dev/null && make 2>/dev/null; then
                print_success "  Compilado com sucesso em $dir_name"
                ((compiled_dirs++))
                successful_compilations+=("$dir_name (Makefile)")
            else
                print_error "  Falha na compilação em $dir_name"
                ((failed_dirs++))
                failed_compilations+=("$dir_name (Makefile)")
            fi
            ;;
    esac
}

compile_c_files() {
    local dir_name="$1"
    local mode="$2"
    local flags="$CFLAGS"
    
    case "$mode" in
        "debug")
            flags="$CFLAGS $DEBUG_FLAGS"
            ;;
        "release")
            flags="$CFLAGS $RELEASE_FLAGS"
            ;;
        "clean")
            print_info "  Limpando arquivos em $dir_name"
            rm -f *.o *.out a.out 2>/dev/null || true
            find . -type f -executable -not -name "*.c" -not -name "*.h" -not -name "Makefile" -delete 2>/dev/null || true
            print_success "  Limpeza concluída em $dir_name"
            return
            ;;
    esac
    
    local c_files=(*.c)
    if [ ! -f "${c_files[0]}" ]; then
        print_warning "  Nenhum arquivo .c encontrado em $dir_name"
        return
    fi
    
    local compiled_any=false
    
    for c_file in *.c; do
        if [ -f "$c_file" ]; then
            ((total_files++))
            local exe_name="${c_file%.c}"
            
            print_info "    Compilando $c_file..."
            
            if $CC $flags -o "$exe_name" "$c_file" 2>/dev/null; then
                print_success "    ✅ $c_file → $exe_name"
                ((compiled_files++))
                compiled_any=true
                
                # Se modo test, tentar executar
                if [ "$mode" = "test" ] && [ -x "./$exe_name" ]; then
                    print_info "    🧪 Testando $exe_name..."
                    if timeout 10s "./$exe_name" >/dev/null 2>&1; then
                        print_success "    ✅ Teste de $exe_name executado"
                    else
                        print_warning "    ⚠️  Teste de $exe_name falhou ou timeout"
                    fi
                fi
                
            else
                print_error "    ❌ Falha ao compilar $c_file"
                ((failed_files++))
                failed_compilations+=("$dir_name/$c_file")
            fi
        fi
    done
    
    if [ "$compiled_any" = true ]; then
        ((compiled_dirs++))
        successful_compilations+=("$dir_name (arquivos individuais)")
    else
        ((failed_dirs++))
    fi
}

# ==================== RELATÓRIO FINAL ====================

print_final_report() {
    local mode="$1"
    
    print_section "RELATÓRIO FINAL"
    
    echo -e "${CYAN}Modo de compilação:${NC} $mode"
    echo -e "${CYAN}Diretórios processados:${NC} $total_dirs"
    echo -e "${GREEN}Sucessos:${NC} $compiled_dirs"
    echo -e "${RED}Falhas:${NC} $failed_dirs"
    
    if [ $total_files -gt 0 ]; then
        echo -e "${CYAN}Arquivos processados:${NC} $total_files"
        echo -e "${GREEN}Compilados:${NC} $compiled_files"
        echo -e "${RED}Falharam:${NC} $failed_files"
    fi
    
    if [ ${#successful_compilations[@]} -gt 0 ]; then
        echo -e "\n${GREEN}✅ COMPILAÇÕES SUCESSOSAS:${NC}"
        for success in "${successful_compilations[@]}"; do
            echo -e "  ${GREEN}✓${NC} $success"
        done
    fi
    
    if [ ${#failed_compilations[@]} -gt 0 ]; then
        echo -e "\n${RED}❌ FALHAS DE COMPILAÇÃO:${NC}"
        for failure in "${failed_compilations[@]}"; do
            echo -e "  ${RED}✗${NC} $failure"
        done
    fi
    
    # Cálculo de percentuais
    if [ $total_dirs -gt 0 ]; then
        local success_rate=$(( (compiled_dirs * 100) / total_dirs ))
        echo -e "\n${CYAN}Taxa de sucesso:${NC} $success_rate%"
        
        if [ $success_rate -eq 100 ]; then
            print_success "🎉 PERFEITO! Todas as compilações foram bem-sucedidas!"
        elif [ $success_rate -ge 80 ]; then
            print_success "👍 MUITO BOM! Maioria das compilações bem-sucedidas."
        elif [ $success_rate -ge 60 ]; then
            print_warning "⚠️  REGULAR. Algumas compilações falharam."
        else
            print_error "💥 CRÍTICO! Muitas falhas de compilação."
        fi
    fi
}

# ==================== FUNÇÃO PRINCIPAL ====================

main() {
    local mode="${1:-all}"
    local specific_dir="$2"
    
    print_header
    
    # Verificar ajuda
    if [ "$mode" = "help" ] || [ "$mode" = "-h" ] || [ "$mode" = "--help" ]; then
        show_help
        exit 0
    fi
    
    # Verificar se diretório src existe
    if [ ! -d "$SRC_DIR" ]; then
        print_error "Diretório src não encontrado em $SRC_DIR"
        exit 1
    fi
    
    print_info "Diretório base: $SRC_DIR"
    print_info "Modo: $mode"
    
    if [ -n "$specific_dir" ]; then
        print_info "Diretório específico: $specific_dir"
    fi
    
    # Determinar diretórios para processar
    local dirs_to_process=()
    
    if [ -n "$specific_dir" ]; then
        local target_dir="$SRC_DIR/$specific_dir"
        if [ -d "$target_dir" ]; then
            dirs_to_process=("$target_dir")
        else
            print_error "Diretório $specific_dir não encontrado"
            exit 1
        fi
    else
        # Processar todos os diretórios numerados
        while IFS= read -r -d '' dir; do
            dirs_to_process+=("$dir")
        done < <(find "$SRC_DIR" -maxdepth 1 -type d -name "[0-9]*" -print0 | sort -z)
    fi
    
    total_dirs=${#dirs_to_process[@]}
    
    if [ $total_dirs -eq 0 ]; then
        print_warning "Nenhum diretório encontrado para processar"
        exit 0
    fi
    
    print_section "INICIANDO COMPILAÇÃO"
    print_info "Processando $total_dirs diretório(s)..."
    
    # Processar cada diretório
    for dir in "${dirs_to_process[@]}"; do
        compile_directory "$dir" "$mode"
    done
    
    # Relatório final
    print_final_report "$mode"
    
    # Código de saída baseado no sucesso
    if [ $failed_dirs -eq 0 ] && [ $failed_files -eq 0 ]; then
        exit 0
    else
        exit 1
    fi
}

# ==================== EXECUÇÃO ====================

# Verificar se o script está sendo executado diretamente
if [ "${BASH_SOURCE[0]}" = "${0}" ]; then
    main "$@"
fi