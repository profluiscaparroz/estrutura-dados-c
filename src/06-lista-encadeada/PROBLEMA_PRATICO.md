# Problema Prático: Sistema de Playlist de Música

## 📋 Descrição do Problema

Um aplicativo de música precisa gerenciar playlist:
- Adicionar músicas em qualquer posição
- Remover músicas específicas
- Navegar para próxima/anterior
- Modo shuffle (embaralhar)
- Buscar música por nome
- Não sabe quantas músicas terá (tamanho dinâmico)

**Por que usar Lista Encadeada?**
- Inserção/remoção O(1) quando temos o nó
- Tamanho dinâmico (não precisa alocar array grande)
- Navegação natural próximo/anterior (lista duplamente encadeada)
- Eficiente para inserções/remoções frequentes no meio

## 🔴 Problema: Usar Array com Tamanho Fixo

```c
#include <stdio.h>
#include <string.h>

#define MAX_MUSICAS 100

typedef struct {
    int id;
    char titulo[100];
    char artista[50];
    int duracao;  // segundos
} Musica;

// PROBLEMA: Array fixo limita tamanho
Musica playlist[MAX_MUSICAS];
int total = 0;
int atual = 0;

// PROBLEMA: Inserir no meio é O(n) - precisa deslocar
void inserir(Musica m, int pos) {
    if (total >= MAX_MUSICAS) return;
    
    // Deslocar todos elementos - INEFICIENTE!
    for (int i = total; i > pos; i--) {
        playlist[i] = playlist[i-1];
    }
    playlist[pos] = m;
    total++;
}

// PROBLEMA: Remover também é O(n)
void remover(int pos) {
    for (int i = pos; i < total - 1; i++) {
        playlist[i] = playlist[i+1];
    }
    total--;
}

int main() {
    Musica m1 = {1, "Song 1", "Artist A", 180};
    Musica m2 = {2, "Song 2", "Artist B", 200};
    
    inserir(m1, 0);
    inserir(m2, 1);
    
    // Inserir no meio = O(n)
    Musica m3 = {3, "Song 3", "Artist C", 220};
    inserir(m3, 1);  // Desloca m2
    
    return 0;
}
```

### Problemas Identificados:
1. ❌ Tamanho fixo (MAX_MUSICAS)
2. ❌ Inserção/remoção O(n) por deslocamento
3. ❌ Desperdiça memória se playlist pequena
4. ❌ Não suporta navegação bidirecional eficiente

## ✅ Solução: Lista Duplamente Encadeada

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// ============= ESTRUTURAS =============

typedef struct Musica {
    int id;
    char titulo[100];
    char artista[50];
    int duracao;  // Em segundos
} Musica;

// Nó da lista duplamente encadeada
typedef struct No {
    Musica musica;
    struct No *proximo;
    struct No *anterior;
} No;

// Lista com ponteiros para início, fim e atual
typedef struct {
    No *inicio;
    No *fim;
    No *atual;      // Música tocando agora
    int tamanho;
    bool modoRepetir;
    bool modoAleatorio;
} Playlist;

// ============= FUNÇÕES AUXILIARES =============

// Formatar duração em MM:SS
void formatarDuracao(int segundos, char *buffer) {
    int min = segundos / 60;
    int seg = segundos % 60;
    sprintf(buffer, "%02d:%02d", min, seg);
}

// Criar novo nó
No* criarNo(Musica musica) {
    No *novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("❌ Erro ao alocar memória!\n");
        return NULL;
    }
    
    novo->musica = musica;
    novo->proximo = NULL;
    novo->anterior = NULL;
    return novo;
}

// ============= OPERAÇÕES DA LISTA =============

void inicializarPlaylist(Playlist *p) {
    p->inicio = NULL;
    p->fim = NULL;
    p->atual = NULL;
    p->tamanho = 0;
    p->modoRepetir = false;
    p->modoAleatorio = false;
}

// Adicionar música no final - O(1)
bool adicionarFinal(Playlist *p, Musica musica) {
    No *novo = criarNo(musica);
    if (novo == NULL) return false;
    
    if (p->inicio == NULL) {
        // Lista vazia
        p->inicio = novo;
        p->fim = novo;
        p->atual = novo;  // Primeira música é a atual
    } else {
        // Adicionar no final
        novo->anterior = p->fim;
        p->fim->proximo = novo;
        p->fim = novo;
    }
    
    p->tamanho++;
    char duracao[10];
    formatarDuracao(musica.duracao, duracao);
    printf("✓ Adicionada: '%s' - %s (%s)\n", 
           musica.titulo, musica.artista, duracao);
    return true;
}

// Inserir música em posição específica - O(n) para busca, O(1) para inserção
bool inserirNaPosicao(Playlist *p, Musica musica, int posicao) {
    if (posicao < 0 || posicao > p->tamanho) {
        printf("⚠️  Posição inválida!\n");
        return false;
    }
    
    if (posicao == p->tamanho) {
        return adicionarFinal(p, musica);
    }
    
    No *novo = criarNo(musica);
    if (novo == NULL) return false;
    
    if (posicao == 0) {
        // Inserir no início
        novo->proximo = p->inicio;
        p->inicio->anterior = novo;
        p->inicio = novo;
    } else {
        // Navegar até posição
        No *atual = p->inicio;
        for (int i = 0; i < posicao; i++) {
            atual = atual->proximo;
        }
        
        // Inserir antes do nó atual
        novo->anterior = atual->anterior;
        novo->proximo = atual;
        atual->anterior->proximo = novo;
        atual->anterior = novo;
    }
    
    p->tamanho++;
    printf("✓ Inserida na posição %d: '%s'\n", posicao, musica.titulo);
    return true;
}

// Remover música por ID - O(n)
bool removerPorId(Playlist *p, int id) {
    No *atual = p->inicio;
    
    while (atual != NULL) {
        if (atual->musica.id == id) {
            // Atualizar ponteiros
            if (atual->anterior != NULL) {
                atual->anterior->proximo = atual->proximo;
            } else {
                p->inicio = atual->proximo;
            }
            
            if (atual->proximo != NULL) {
                atual->proximo->anterior = atual->anterior;
            } else {
                p->fim = atual->anterior;
            }
            
            // Se estava tocando, avançar
            if (p->atual == atual) {
                p->atual = atual->proximo ? atual->proximo : p->inicio;
            }
            
            printf("✓ Removida: '%s'\n", atual->musica.titulo);
            free(atual);
            p->tamanho--;
            return true;
        }
        atual = atual->proximo;
    }
    
    printf("⚠️  Música ID %d não encontrada\n", id);
    return false;
}

// Buscar música por título - O(n)
No* buscarPorTitulo(Playlist *p, const char *titulo) {
    No *atual = p->inicio;
    
    while (atual != NULL) {
        if (strstr(atual->musica.titulo, titulo) != NULL) {
            return atual;
        }
        atual = atual->proximo;
    }
    
    return NULL;
}

// ============= REPRODUÇÃO =============

void exibirMusicaAtual(Playlist *p) {
    if (p->atual == NULL) {
        printf("⏹️  Nenhuma música tocando\n");
        return;
    }
    
    char duracao[10];
    formatarDuracao(p->atual->musica.duracao, duracao);
    
    printf("\n♪ TOCANDO AGORA ♪\n");
    printf("  🎵 %s\n", p->atual->musica.titulo);
    printf("  👤 %s\n", p->atual->musica.artista);
    printf("  ⏱️  %s\n", duracao);
    
    if (p->modoRepetir) printf("  🔁 Modo Repetir\n");
    if (p->modoAleatorio) printf("  🔀 Modo Aleatório\n");
}

// Próxima música - O(1)
void proximaMusica(Playlist *p) {
    if (p->atual == NULL) {
        printf("⚠️  Playlist vazia\n");
        return;
    }
    
    if (p->modoAleatorio) {
        // Escolher música aleatória
        int posicao = rand() % p->tamanho;
        No *temp = p->inicio;
        for (int i = 0; i < posicao; i++) {
            temp = temp->proximo;
        }
        p->atual = temp;
        printf("⏭️  Próxima (aleatória)\n");
    } else if (p->atual->proximo != NULL) {
        p->atual = p->atual->proximo;
        printf("⏭️  Próxima música\n");
    } else if (p->modoRepetir) {
        p->atual = p->inicio;
        printf("🔁 Voltando ao início\n");
    } else {
        printf("⏹️  Fim da playlist\n");
    }
    
    exibirMusicaAtual(p);
}

// Música anterior - O(1)
void musicaAnterior(Playlist *p) {
    if (p->atual == NULL) {
        printf("⚠️  Playlist vazia\n");
        return;
    }
    
    if (p->atual->anterior != NULL) {
        p->atual = p->atual->anterior;
        printf("⏮️  Música anterior\n");
    } else if (p->modoRepetir) {
        p->atual = p->fim;
        printf("🔁 Indo para o final\n");
    } else {
        printf("⏹️  Já está no início\n");
    }
    
    exibirMusicaAtual(p);
}

// Listar todas as músicas - O(n)
void listarPlaylist(Playlist *p) {
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║          PLAYLIST (%d músicas)         \n", p->tamanho);
    printf("╚════════════════════════════════════════╝\n\n");
    
    if (p->inicio == NULL) {
        printf("  (vazia)\n");
        return;
    }
    
    No *atual = p->inicio;
    int pos = 1;
    int duracaoTotal = 0;
    
    while (atual != NULL) {
        char duracao[10];
        formatarDuracao(atual->musica.duracao, duracao);
        
        char marcador = (atual == p->atual) ? '▶' : ' ';
        
        printf("%c %2d. %-30s %-20s %s\n",
               marcador, pos,
               atual->musica.titulo,
               atual->musica.artista,
               duracao);
        
        duracaoTotal += atual->musica.duracao;
        atual = atual->proximo;
        pos++;
    }
    
    char duracaoFormatada[10];
    formatarDuracao(duracaoTotal, duracaoFormatada);
    printf("\nDuração total: %s\n", duracaoFormatada);
}

// Liberar memória - O(n)
void destruirPlaylist(Playlist *p) {
    No *atual = p->inicio;
    
    while (atual != NULL) {
        No *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    
    p->inicio = NULL;
    p->fim = NULL;
    p->atual = NULL;
    p->tamanho = 0;
    
    printf("✓ Playlist limpa\n");
}

// ============= MAIN =============

int main() {
    srand(time(NULL));
    
    Playlist playlist;
    inicializarPlaylist(&playlist);
    
    printf("╔════════════════════════════════════════╗\n");
    printf("║     SISTEMA DE PLAYLIST - SPOTIFY      ║\n");
    printf("║    Usando Lista Duplamente Encadeada   ║\n");
    printf("╚════════════════════════════════════════╝\n\n");
    
    // Adicionar músicas
    printf("=== ADICIONANDO MÚSICAS ===\n\n");
    
    Musica m1 = {1, "Bohemian Rhapsody", "Queen", 354};
    Musica m2 = {2, "Stairway to Heaven", "Led Zeppelin", 482};
    Musica m3 = {3, "Hotel California", "Eagles", 391};
    Musica m4 = {4, "Imagine", "John Lennon", 183};
    Musica m5 = {5, "Sweet Child O' Mine", "Guns N' Roses", 356};
    
    adicionarFinal(&playlist, m1);
    adicionarFinal(&playlist, m2);
    adicionarFinal(&playlist, m3);
    adicionarFinal(&playlist, m4);
    adicionarFinal(&playlist, m5);
    
    listarPlaylist(&playlist);
    exibirMusicaAtual(&playlist);
    
    // Inserir música no meio
    printf("\n\n=== INSERINDO NO MEIO ===\n");
    Musica m6 = {6, "Smells Like Teen Spirit", "Nirvana", 301};
    inserirNaPosicao(&playlist, m6, 2);
    
    listarPlaylist(&playlist);
    
    // Navegação
    printf("\n=== NAVEGAÇÃO ===\n\n");
    proximaMusica(&playlist);
    proximaMusica(&playlist);
    musicaAnterior(&playlist);
    
    // Buscar música
    printf("\n=== BUSCA ===\n");
    No *encontrada = buscarPorTitulo(&playlist, "Imagine");
    if (encontrada) {
        printf("✓ Encontrada: '%s' - %s\n", 
               encontrada->musica.titulo, 
               encontrada->musica.artista);
    }
    
    // Remover música
    printf("\n=== REMOÇÃO ===\n");
    removerPorId(&playlist, 3);
    
    listarPlaylist(&playlist);
    
    // Modo aleatório
    printf("\n=== MODO ALEATÓRIO ===\n");
    playlist.modoAleatorio = true;
    proximaMusica(&playlist);
    proximaMusica(&playlist);
    
    // Limpeza
    printf("\n=== LIMPEZA ===\n");
    destruirPlaylist(&playlist);
    
    return 0;
}
```

## 📊 Análise de Complexidade

| Operação | Array | Lista Simples | Lista Dupla |
|----------|-------|---------------|-------------|
| Adicionar final | O(1)* | O(n) | O(1) ✅ |
| Adicionar início | O(n) | O(1) | O(1) ✅ |
| Inserir meio | O(n) | O(n) | O(n)** |
| Remover | O(n) | O(n) | O(n)** |
| Próximo/Anterior | O(1) | O(n)/O(1) | O(1) ✅ |
| Buscar | O(n) | O(n) | O(n) |
| Acesso direto | O(1) ✅ | O(n) | O(n) |

*Se array não estiver cheio  
**O(n) para buscar, mas O(1) para inserir/remover quando tem o nó

## 🎯 Conceitos de Lista Encadeada Aplicados

- ✅ **Nós dinâmicos** com malloc/free
- ✅ **Ponteiros duplos** (próximo e anterior)
- ✅ **Inserção/remoção eficiente** quando tem o nó
- ✅ **Navegação bidirecional** O(1)
- ✅ **Tamanho dinâmico** - cresce conforme necessário
- ✅ **Tratamento de casos especiais** (início, fim, meio)

## 💡 Quando Usar Lista Encadeada

| Cenário | Use Lista Encadeada | Use Array |
|---------|---------------------|-----------|
| Muitas inserções/remoções | ✅ | ❌ |
| Acesso aleatório frequente | ❌ | ✅ |
| Tamanho desconhecido | ✅ | ❌ |
| Memória contígua necessária | ❌ | ✅ |
| Cache-friendly | ❌ | ✅ |
| Navegação sequencial | ✅ | ✅ |

## 📝 Como Compilar e Executar

```bash
# Compilar
gcc PROBLEMA_PRATICO.c -o playlist -Wall

# Executar
./playlist
```

## 📚 Lições Aprendidas

1. **Lista dupla > lista simples** - Navegação bidirecional O(1)
2. **Sempre liberar memória** - free() para cada malloc()
3. **Tratar casos especiais** - Início, fim, lista vazia
4. **Ponteiro para atual** - Facilita operações de reprodução
5. **Validar posições** - Evitar acesso inválido
6. **Vantagem dinâmica** - Não precisa definir tamanho máximo

## 🔍 Melhorias Possíveis

1. **Lista circular** - Último aponta para primeiro (repetir automático)
2. **Skip list** - Acesso mais rápido com níveis
3. **Hash + Lista** - O(1) para busca por ID
4. **Persistência** - Salvar/carregar de arquivo
5. **Histórico de reprodução** - Pilha de músicas tocadas
6. **Fila de reprodução** - Fila separada de próximas músicas
