#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

/**
 * Programa de exemplo para busca de palavras em strings usando expressões regulares (regex)
 * 
 * Este arquivo demonstra como usar a biblioteca regex.h do POSIX
 * para realizar buscas avançadas de padrões em strings.
 * 
 * Operações implementadas:
 * 1. Busca básica com regex
 * 2. Busca case-insensitive com regex
 * 3. Busca de padrões específicos (números, emails, etc.)
 * 4. Extração de múltiplas ocorrências
 * 5. Validação de formatos
 * 
 * NOTA: Este exemplo usa regex.h (POSIX), que pode não estar disponível
 * em todos os sistemas (especialmente Windows com alguns compiladores).
 * Em sistemas Unix/Linux/macOS geralmente está disponível.
 */

// Estrutura para armazenar informações sobre uma correspondência encontrada
typedef struct {
    int inicio;     // Posição inicial da correspondência
    int fim;        // Posição final da correspondência
    char texto[256]; // Texto da correspondência
} Correspondencia;

// Função para compilar uma expressão regular
// Parâmetros:
// - regex: ponteiro para a estrutura regex_t
// - padrao: string com o padrão da expressão regular
// - flags: flags para compilação (REG_ICASE para case-insensitive, etc.)
// Retorna:
// - 0 se a compilação foi bem-sucedida
// - código de erro caso contrário
int compilarRegex(regex_t* regex, const char* padrao, int flags) {
    int resultado = regcomp(regex, padrao, flags | REG_EXTENDED);
    
    if (resultado != 0) {
        char mensagem_erro[256];
        regerror(resultado, regex, mensagem_erro, sizeof(mensagem_erro));
        printf("Erro ao compilar regex \"%s\": %s\n", padrao, mensagem_erro);
    }
    
    return resultado;
}

// Função para buscar um padrão em uma string usando regex
// Parâmetros:
// - texto: string onde será feita a busca
// - padrao: padrão regex a ser buscado
// - case_sensitive: 1 para busca sensível a maiúsculas, 0 para insensível
// Retorna:
// - 1 se o padrão foi encontrado
// - 0 se não foi encontrado
// - -1 em caso de erro
int buscarComRegex(const char* texto, const char* padrao, int case_sensitive) {
    if (texto == NULL || padrao == NULL) {
        return -1;
    }
    
    regex_t regex;
    int flags = case_sensitive ? 0 : REG_ICASE;
    
    // Compilar a expressão regular
    if (compilarRegex(&regex, padrao, flags) != 0) {
        return -1;
    }
    
    // Executar a busca
    int resultado = regexec(&regex, texto, 0, NULL, 0);
    
    // Liberar memória da regex
    regfree(&regex);
    
    return (resultado == 0) ? 1 : 0;
}

// Função para encontrar a primeira correspondência de um padrão
// Parâmetros:
// - texto: string onde será feita a busca
// - padrao: padrão regex a ser buscado
// - correspondencia: ponteiro para estrutura que receberá o resultado
// - case_sensitive: 1 para busca sensível a maiúsculas, 0 para insensível
// Retorna:
// - 1 se encontrou correspondência
// - 0 se não encontrou
// - -1 em caso de erro
int encontrarCorrespondencia(const char* texto, const char* padrao, 
                           Correspondencia* correspondencia, int case_sensitive) {
    if (texto == NULL || padrao == NULL || correspondencia == NULL) {
        return -1;
    }
    
    regex_t regex;
    regmatch_t match[1];
    int flags = case_sensitive ? 0 : REG_ICASE;
    
    // Compilar a expressão regular
    if (compilarRegex(&regex, padrao, flags) != 0) {
        return -1;
    }
    
    // Executar a busca
    int resultado = regexec(&regex, texto, 1, match, 0);
    
    if (resultado == 0) {
        // Correspondência encontrada
        correspondencia->inicio = (int)match[0].rm_so;
        correspondencia->fim = (int)match[0].rm_eo;
        
        // Copiar o texto da correspondência
        int tamanho = correspondencia->fim - correspondencia->inicio;
        if (tamanho < (int)(sizeof(correspondencia->texto) - 1)) {
            strncpy(correspondencia->texto, texto + correspondencia->inicio, tamanho);
            correspondencia->texto[tamanho] = '\0';
        } else {
            correspondencia->texto[0] = '\0';
        }
        
        regfree(&regex);
        return 1;
    }
    
    regfree(&regex);
    return 0;
}

// Função para encontrar todas as correspondências de um padrão
// Parâmetros:
// - texto: string onde será feita a busca
// - padrao: padrão regex a ser buscado
// - correspondencias: array para armazenar os resultados
// - max_correspondencias: tamanho máximo do array
// - case_sensitive: 1 para busca sensível a maiúsculas, 0 para insensível
// Retorna:
// - Número de correspondências encontradas
// - -1 em caso de erro
int encontrarTodasCorrespondencias(const char* texto, const char* padrao,
                                 Correspondencia correspondencias[], int max_correspondencias,
                                 int case_sensitive) {
    if (texto == NULL || padrao == NULL || correspondencias == NULL) {
        return -1;
    }
    
    regex_t regex;
    regmatch_t match[1];
    int flags = case_sensitive ? 0 : REG_ICASE;
    int contador = 0;
    
    // Compilar a expressão regular
    if (compilarRegex(&regex, padrao, flags) != 0) {
        return -1;
    }
    
    const char* ptr = texto;
    
    // Buscar todas as ocorrências
    while (contador < max_correspondencias && regexec(&regex, ptr, 1, match, 0) == 0) {
        // Calcular posições absolutas
        correspondencias[contador].inicio = (int)(ptr - texto + match[0].rm_so);
        correspondencias[contador].fim = (int)(ptr - texto + match[0].rm_eo);
        
        // Copiar o texto da correspondência
        int tamanho = match[0].rm_eo - match[0].rm_so;
        if (tamanho < (int)(sizeof(correspondencias[contador].texto) - 1)) {
            strncpy(correspondencias[contador].texto, ptr + match[0].rm_so, tamanho);
            correspondencias[contador].texto[tamanho] = '\0';
        } else {
            correspondencias[contador].texto[0] = '\0';
        }
        
        contador++;
        
        // Mover o ponteiro para após a correspondência atual
        ptr += match[0].rm_eo;
        
        // Se a correspondência foi vazia, avançar pelo menos um caractere
        if (match[0].rm_so == match[0].rm_eo) {
            if (*ptr == '\0') break;
            ptr++;
        }
    }
    
    regfree(&regex);
    return contador;
}

// Função para validar formato de email usando regex
// Parâmetros:
// - email: string a ser validada
// Retorna:
// - 1 se é um email válido
// - 0 se não é válido
int validarEmail(const char* email) {
    // Padrão simples para email (não cobre todos os casos RFC)
    const char* padrao = "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$";
    return buscarComRegex(email, padrao, 1);
}

// Função para extrair números de uma string
// Parâmetros:
// - texto: string onde buscar números
// - numeros: array para armazenar os números encontrados
// - max_numeros: tamanho máximo do array
// Retorna:
// - Quantidade de números encontrados
int extrairNumeros(const char* texto, Correspondencia numeros[], int max_numeros) {
    const char* padrao = "[0-9]+";
    return encontrarTodasCorrespondencias(texto, padrao, numeros, max_numeros, 1);
}

// Função para extrair palavras que começam com maiúscula
// Parâmetros:
// - texto: string onde buscar
// - palavras: array para armazenar as palavras encontradas
// - max_palavras: tamanho máximo do array
// Retorna:
// - Quantidade de palavras encontradas
int extrairPalavraMaiuscula(const char* texto, Correspondencia palavras[], int max_palavras) {
    const char* padrao = "\\b[A-Z][a-zA-Z]*\\b";
    return encontrarTodasCorrespondencias(texto, padrao, palavras, max_palavras, 1);
}

// Função de demonstração das operações com regex
void demonstrarBuscasRegex() {
    printf("=== DEMONSTRAÇÃO DE BUSCAS COM REGEX ===\n\n");
    
    const char* texto = "João Silva tem 25 anos e trabalha na empresa TechCorp. "
                       "Seu email é joao.silva@techcorp.com.br e seu telefone é (11) 98765-4321. "
                       "Maria Santos, de 30 anos, trabalha na MegaTech.";
    
    printf("Texto de exemplo:\n\"%s\"\n\n", texto);
    
    // 1. Busca básica de palavra
    printf("1. BUSCA BÁSICA COM REGEX:\n");
    const char* padrao1 = "\\bjoão\\b"; // \\b indica fronteira de palavra
    int resultado1 = buscarComRegex(texto, padrao1, 0); // case-insensitive
    
    if (resultado1 == 1) {
        printf("   ✅ Padrão \"%s\" encontrado (case-insensitive)\n", padrao1);
    } else if (resultado1 == 0) {
        printf("   ❌ Padrão \"%s\" não encontrado\n", padrao1);
    } else {
        printf("   ⚠️  Erro na busca do padrão \"%s\"\n", padrao1);
    }
    
    // 2. Busca de números
    printf("\n2. EXTRAÇÃO DE NÚMEROS:\n");
    Correspondencia numeros[10];
    int qtd_numeros = extrairNumeros(texto, numeros, 10);
    
    if (qtd_numeros > 0) {
        printf("   Números encontrados: %d\n", qtd_numeros);
        for (int i = 0; i < qtd_numeros; i++) {
            printf("   - \"%s\" (posição %d-%d)\n", 
                   numeros[i].texto, numeros[i].inicio, numeros[i].fim);
        }
    } else {
        printf("   Nenhum número encontrado\n");
    }
    
    // 3. Busca de palavras com maiúscula
    printf("\n3. PALAVRAS INICIADAS COM MAIÚSCULA:\n");
    Correspondencia palavras[10];
    int qtd_palavras = extrairPalavraMaiuscula(texto, palavras, 10);
    
    if (qtd_palavras > 0) {
        printf("   Palavras encontradas: %d\n", qtd_palavras);
        for (int i = 0; i < qtd_palavras; i++) {
            printf("   - \"%s\" (posição %d-%d)\n", 
                   palavras[i].texto, palavras[i].inicio, palavras[i].fim);
        }
    } else {
        printf("   Nenhuma palavra encontrada\n");
    }
    
    // 4. Validação de email
    printf("\n4. VALIDAÇÃO DE EMAIL:\n");
    const char* emails_teste[] = {
        "joao.silva@techcorp.com.br",
        "maria@empresa.com",
        "email_invalido",
        "test@",
        "usuario@dominio.co"
    };
    
    int num_emails = sizeof(emails_teste) / sizeof(emails_teste[0]);
    for (int i = 0; i < num_emails; i++) {
        int valido = validarEmail(emails_teste[i]);
        printf("   \"%s\" - %s\n", emails_teste[i], 
               valido ? "✅ VÁLIDO" : "❌ INVÁLIDO");
    }
    
    // 5. Busca de padrão de telefone
    printf("\n5. BUSCA DE PADRÃO DE TELEFONE:\n");
    const char* padrao_telefone = "\\([0-9]{2}\\) [0-9]{4,5}-[0-9]{4}";
    Correspondencia telefone;
    
    if (encontrarCorrespondencia(texto, padrao_telefone, &telefone, 1)) {
        printf("   ✅ Telefone encontrado: \"%s\" (posição %d-%d)\n",
               telefone.texto, telefone.inicio, telefone.fim);
    } else {
        printf("   ❌ Nenhum telefone no formato esperado encontrado\n");
    }
    
    // 6. Busca de palavras específicas (case-insensitive)
    printf("\n6. BUSCA CASE-INSENSITIVE:\n");
    const char* padrao_empresa = "\\b(tech|mega).*\\b";
    Correspondencia empresas[5];
    int qtd_empresas = encontrarTodasCorrespondencias(texto, padrao_empresa, empresas, 5, 0);
    
    if (qtd_empresas > 0) {
        printf("   Empresas de tecnologia encontradas: %d\n", qtd_empresas);
        for (int i = 0; i < qtd_empresas; i++) {
            printf("   - \"%s\" (posição %d-%d)\n",
                   empresas[i].texto, empresas[i].inicio, empresas[i].fim);
        }
    } else {
        printf("   Nenhuma empresa de tecnologia encontrada\n");
    }
}

// Função para demonstrar padrões regex avançados
void demonstrarPadroesAvancados() {
    printf("\n=== PADRÕES REGEX AVANÇADOS ===\n\n");
    
    printf("Exemplos de padrões úteis:\n\n");
    
    printf("1. VALIDAÇÕES:\n");
    printf("   - Email: ^[a-zA-Z0-9.%%_+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$\n");
    printf("   - CPF: ^[0-9]{3}\\.[0-9]{3}\\.[0-9]{3}-[0-9]{2}$\n");
    printf("   - Telefone: ^\\([0-9]{2}\\) [0-9]{4,5}-[0-9]{4}$\n");
    printf("   - CEP: ^[0-9]{5}-[0-9]{3}$\n");
    
    printf("\n2. EXTRAÇÃO DE DADOS:\n");
    printf("   - Números: [0-9]+\n");
    printf("   - Palavras: \\b[a-zA-Z]+\\b\n");
    printf("   - URLs: https?://[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}\n");
    printf("   - Datas (DD/MM/YYYY): [0-9]{1,2}/[0-9]{1,2}/[0-9]{4}\n");
    
    printf("\n3. METACARACTERES IMPORTANTES:\n");
    printf("   - . (ponto): qualquer caractere\n");
    printf("   - * (asterisco): zero ou mais repetições\n");
    printf("   - + (mais): uma ou mais repetições\n");
    printf("   - ? (interrogação): zero ou uma ocorrência\n");
    printf("   - ^ (circunflexo): início da string\n");
    printf("   - $ (dólar): fim da string\n");
    printf("   - [] (colchetes): classe de caracteres\n");
    printf("   - () (parênteses): grupo\n");
    printf("   - | (pipe): alternativa (ou)\n");
    printf("   - \\b: fronteira de palavra\n");
    
    // Exemplo prático
    printf("\n4. EXEMPLO PRÁTICO - EXTRAÇÃO DE INFORMAÇÕES:\n");
    const char* texto_dados = "Data: 15/03/2024, CPF: 123.456.789-00, "
                             "URL: https://www.exemplo.com.br, "
                             "Email: contato@exemplo.com";
    
    printf("Texto: \"%s\"\n\n", texto_dados);
    
    // Extrair datas
    Correspondencia datas[5];
    int qtd_datas = encontrarTodasCorrespondencias(texto_dados, 
        "[0-9]{1,2}/[0-9]{1,2}/[0-9]{4}", datas, 5, 1);
    
    if (qtd_datas > 0) {
        printf("Datas encontradas:\n");
        for (int i = 0; i < qtd_datas; i++) {
            printf("   - %s\n", datas[i].texto);
        }
    }
    
    // Extrair URLs
    Correspondencia urls[5];
    int qtd_urls = encontrarTodasCorrespondencias(texto_dados,
        "https?://[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}", urls, 5, 1);
    
    if (qtd_urls > 0) {
        printf("URLs encontradas:\n");
        for (int i = 0; i < qtd_urls; i++) {
            printf("   - %s\n", urls[i].texto);
        }
    }
}

int main() {
    printf("=== EXEMPLOS DE BUSCA DE PALAVRAS COM REGEX ===\n\n");
    
    // Verificar se regex está disponível
    regex_t teste;
    if (regcomp(&teste, "test", REG_EXTENDED) != 0) {
        printf("❌ ERRO: Biblioteca regex não está disponível neste sistema.\n");
        printf("Este exemplo requer um sistema compatível com POSIX regex.\n");
        printf("Em sistemas Windows, pode ser necessário instalar biblioturas adicionais.\n");
        return 1;
    }
    regfree(&teste);
    
    printf("✅ Biblioteca regex disponível!\n\n");
    
    // Demonstração principal
    demonstrarBuscasRegex();
    
    // Demonstração de padrões avançados
    demonstrarPadroesAvancados();
    
    printf("\n=== EXEMPLO INTERATIVO ===\n");
    
    // Exemplo interativo
    char texto_usuario[1000];
    char padrao_usuario[200];
    
    printf("Digite um texto para análise (máximo 999 caracteres): ");
    if (fgets(texto_usuario, sizeof(texto_usuario), stdin) != NULL) {
        // Remove quebra de linha
        size_t len = strlen(texto_usuario);
        if (len > 0 && texto_usuario[len-1] == '\n') {
            texto_usuario[len-1] = '\0';
        }
        
        printf("Digite um padrão regex (ex: \\b[A-Z][a-z]+\\b para palavras com maiúscula): ");
        if (fgets(padrao_usuario, sizeof(padrao_usuario), stdin) != NULL) {
            // Remove quebra de linha
            len = strlen(padrao_usuario);
            if (len > 0 && padrao_usuario[len-1] == '\n') {
                padrao_usuario[len-1] = '\0';
            }
            
            printf("\n=== RESULTADOS DA BUSCA REGEX ===\n");
            
            // Busca todas as correspondências
            Correspondencia resultados[20];
            int qtd_resultados = encontrarTodasCorrespondencias(texto_usuario, padrao_usuario,
                                                              resultados, 20, 1);
            
            if (qtd_resultados > 0) {
                printf("✅ %d correspondência(s) encontrada(s):\n", qtd_resultados);
                for (int i = 0; i < qtd_resultados; i++) {
                    printf("   %d. \"%s\" (posição %d-%d)\n", i+1,
                           resultados[i].texto, resultados[i].inicio, resultados[i].fim);
                }
            } else if (qtd_resultados == 0) {
                printf("❌ Nenhuma correspondência encontrada para o padrão \"%s\"\n", padrao_usuario);
            } else {
                printf("⚠️  Erro na execução da regex. Verifique se o padrão está correto.\n");
            }
        }
    }
    
    printf("\n=== CONCEITOS IMPORTANTES ===\n");
    printf("1. Regex permite busca de padrões complexos, não apenas texto literal\n");
    printf("2. Mais poderoso que busca simples, mas também mais complexo\n");
    printf("3. Útil para validação de formatos (email, telefone, CPF, etc.)\n");
    printf("4. Permite extração de dados estruturados de textos\n");
    printf("5. Sintaxe pode variar entre implementações (POSIX, PCRE, etc.)\n");
    printf("6. Performance pode ser menor que busca simples para casos básicos\n");
    printf("7. Essencial para processamento avançado de texto\n");
    
    return 0;
}