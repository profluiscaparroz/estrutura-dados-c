# Guia Rápido - Sistema de Biblioteca SQLite

## 🚀 Início Rápido

### Pré-requisitos

Você precisa ter instalado:
- GCC (compilador C)
- SQLite3 e libsqlite3-dev

#### Instalação do SQLite (se necessário)

**Linux (Ubuntu/Debian):**
```bash
sudo apt-get update
sudo apt-get install gcc libsqlite3-dev
```

**Linux (Fedora/RedHat):**
```bash
sudo dnf install gcc sqlite-devel
```

**Mac OS:**
```bash
brew install sqlite3
```

**Windows:**
- Baixe MinGW-w64
- Baixe SQLite precompilado de https://www.sqlite.org/download.html

### Compilação

```bash
# Entre no diretório
cd src/12-C-SQLITE

# Compile o programa
make

# Ou compile manualmente
gcc -Wall -Wextra -std=c11 biblioteca_completa.c -o biblioteca -lsqlite3
```

### Execução

```bash
# Execute o programa
./biblioteca

# Ou no Windows
biblioteca.exe
```

## 📖 Usando o Sistema

### Primeira Vez

Quando você executar o programa pela primeira vez:

1. Um arquivo `biblioteca.db` será criado automaticamente
2. A tabela `livros` será criada
3. Escolha a opção **10** para inserir dados de exemplo
4. Explore as outras funcionalidades!

### Menu Principal

```
1. Adicionar novo livro       - Insere um livro manualmente
2. Listar todos os livros      - Mostra todos os livros cadastrados
3. Buscar livro por ID         - Busca pelo código único
4. Buscar livro por título     - Busca por nome (parcial)
5. Atualizar preço             - Modifica o preço de um livro
6. Atualizar estoque           - Adiciona/remove do estoque
7. Remover livro               - Deleta um livro (irreversível!)
8. Estatísticas gerais         - Relatório completo
9. Listar por autor            - Agrupa livros por autor
10. Inserir dados de exemplo   - Adiciona 10 livros de teste
0. Sair                        - Fecha o programa
```

## 💡 Exemplos de Uso

### Exemplo 1: Adicionar um Livro

```
Escolha uma opção: 1

Título: O Nome do Vento
Autor: Patrick Rothfuss
Editora: Arqueiro
Ano de publicação: 2007
Preço (R$): 44.90
Quantidade em estoque: 5

✓ Livro adicionado com sucesso! (ID: 11)
```

### Exemplo 2: Buscar por Título

```
Escolha uma opção: 4

Digite o título (ou parte dele): senhor

ID    Título                    Autor              Preço      Estoque
─────────────────────────────────────────────────────────────────────
2     O Senhor dos Anéis       J.R.R. Tolkien     R$ 49.90   12

1 livro(s) encontrado(s).
```

### Exemplo 3: Atualizar Estoque

```
Escolha uma opção: 6

Digite o ID do livro: 2
Estoque atual: 12 unidades

Operação:
  [E] Entrada (adicionar)
  [S] Saída (remover)
Escolha: S
Quantidade: 1

✓ Estoque atualizado com sucesso!
Estoque anterior: 12
Estoque atual: 11
```

## 🔧 Comandos do Makefile

```bash
make          # Compila o programa
make run      # Compila e executa
make clean    # Remove o executável
make cleandb  # Remove o banco de dados
make cleanall # Remove tudo
make help     # Mostra ajuda
```

## 🗄️ Acessando o Banco Diretamente

Você pode acessar o banco de dados diretamente usando o sqlite3:

```bash
# Abrir o banco
sqlite3 biblioteca.db

# Comandos úteis dentro do sqlite3
.tables                        # Listar tabelas
.schema livros                 # Ver estrutura da tabela
SELECT * FROM livros;          # Ver todos os livros
SELECT * FROM livros WHERE preco < 30;  # Buscar livros baratos
.quit                          # Sair
```

## 📝 Estrutura do Banco de Dados

### Tabela: livros

| Coluna   | Tipo    | Descrição                    |
|----------|---------|------------------------------|
| id       | INTEGER | Chave primária (auto-increment) |
| titulo   | TEXT    | Título do livro              |
| autor    | TEXT    | Nome do autor                |
| editora  | TEXT    | Nome da editora              |
| ano      | INTEGER | Ano de publicação            |
| preco    | REAL    | Preço em reais               |
| estoque  | INTEGER | Quantidade em estoque        |

## ⚠️ Dicas Importantes

1. **Backup**: O arquivo `biblioteca.db` contém todos os seus dados. Faça backup regularmente!
   ```bash
   cp biblioteca.db biblioteca_backup.db
   ```

2. **Remover livros**: A remoção é irreversível! Sempre confirme antes de deletar.

3. **Estoque negativo**: O sistema não permite estoque negativo. Se tentar remover mais do que há em estoque, receberá um erro.

4. **Busca por título**: A busca é case-sensitive e aceita termos parciais. Por exemplo, "senhor" encontra "O Senhor dos Anéis".

5. **Transações**: Ao inserir dados de exemplo, o sistema usa transações. Se houver erro, nenhum dado será inserido.

## 🐛 Resolução de Problemas

### Erro: "library not found: -lsqlite3"

**Solução**: Instale a biblioteca de desenvolvimento do SQLite:
```bash
# Ubuntu/Debian
sudo apt-get install libsqlite3-dev

# Mac
brew install sqlite3
```

### Erro: "unable to open database file"

**Solução**: Verifique as permissões do diretório:
```bash
ls -la biblioteca.db
chmod 644 biblioteca.db  # Se necessário
```

### Erro: "database is locked"

**Solução**: Feche todas as outras conexões ao banco:
```bash
# Verifique se há processos usando o arquivo
lsof biblioteca.db

# Se necessário, mate o processo
kill -9 <PID>
```

## 📚 Recursos Adicionais

- **README.md**: Documentação completa sobre SQL e SQLite
- **biblioteca_completa.c**: Código-fonte totalmente comentado
- **SQLite Documentation**: https://www.sqlite.org/docs.html

## 🎓 Exercícios Sugeridos

1. Adicione uma coluna `isbn` à tabela
2. Crie uma função para buscar livros por faixa de preço
3. Implemente um sistema de categorias
4. Adicione suporte a múltiplos autores por livro
5. Crie um relatório de livros mais vendidos

---

**Divirta-se explorando SQLite em C! 🚀📚**
