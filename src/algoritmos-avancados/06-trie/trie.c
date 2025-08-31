#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26

// Estrutura do nó da Trie
typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    bool is_end_of_word;
} TrieNode;

// Função para criar um novo nó da Trie
TrieNode* createNode() {
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    node->is_end_of_word = false;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    return node;
}

// Função para inserir uma palavra na Trie
void insert(TrieNode *root, const char *word) {
    TrieNode *node = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';  // assume somente letras minúsculas
        if (node->children[index] == NULL) {
            node->children[index] = createNode();
        }
        node = node->children[index];
    }
    node->is_end_of_word = true;
}

// Função para buscar uma palavra na Trie
bool search(TrieNode *root, const char *word) {
    TrieNode *node = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (node->children[index] == NULL) {
            return false;
        }
        node = node->children[index];
    }
    return node->is_end_of_word;
}

// Função para verificar se um nó tem filhos
bool hasChildren(TrieNode *node) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL) {
            return true;
        }
    }
    return false;
}

// Função auxiliar para deletar recursivamente
TrieNode* deleteHelper(TrieNode *root, const char *word, int index, int len) {
    if (index == len) {
        // Chegamos ao final da palavra
        if (root->is_end_of_word) {
            root->is_end_of_word = false;
        }
        
        // Se o nó não tem filhos, pode ser deletado
        if (!hasChildren(root)) {
            free(root);
            root = NULL;
        }
        return root;
    }
    
    int charIndex = word[index] - 'a';
    TrieNode *node = root->children[charIndex];
    
    if (node == NULL) {
        return root; // Palavra não existe
    }
    
    node = deleteHelper(node, word, index + 1, len);
    root->children[charIndex] = node;
    
    // Se o nó atual não marca fim de palavra e não tem filhos, deletar
    if (!root->is_end_of_word && !hasChildren(root) && root != NULL) {
        free(root);
        root = NULL;
    }
    
    return root;
}

// Função para deletar uma palavra da Trie
void deleteWord(TrieNode *root, const char *word) {
    int len = 0;
    while (word[len] != '\0') len++; // Calcular comprimento
    deleteHelper(root, word, 0, len);
}

// Função para buscar palavras com prefixo
void searchPrefix(TrieNode *root, const char *prefix, char *current_word, int level) {
    if (root->is_end_of_word) {
        current_word[level] = '\0';
        printf("%s\n", current_word);
    }
    
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i] != NULL) {
            current_word[level] = 'a' + i;
            searchPrefix(root->children[i], prefix, current_word, level + 1);
        }
    }
}

// Função para encontrar todas as palavras com um dado prefixo
void findWordsWithPrefix(TrieNode *root, const char *prefix) {
    TrieNode *node = root;
    
    // Navegar até o final do prefixo
    for (int i = 0; prefix[i] != '\0'; i++) {
        int index = prefix[i] - 'a';
        if (node->children[index] == NULL) {
            printf("Nenhuma palavra encontrada com prefixo '%s'\n", prefix);
            return;
        }
        node = node->children[index];
    }
    
    // Buscar todas as palavras a partir deste nó
    char current_word[100];
    int prefix_len = 0;
    while (prefix[prefix_len] != '\0') prefix_len++;
    
    for (int i = 0; i < prefix_len; i++) {
        current_word[i] = prefix[i];
    }
    
    printf("Palavras com prefixo '%s':\n", prefix);
    searchPrefix(node, prefix, current_word, prefix_len);
}

// Função para liberar a memória da Trie
void freeTrie(TrieNode *root) {
    if (root == NULL) return;
    
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i] != NULL) {
            freeTrie(root->children[i]);
        }
    }
    free(root);
}

// Exemplo de uso
int main() {
    TrieNode *trie = createNode();
    
    // Inserir palavras
    insert(trie, "carro");
    insert(trie, "casa");
    insert(trie, "cachorro");
    insert(trie, "cafe");
    insert(trie, "carta");
    insert(trie, "cartas");
    
    printf("Buscas:\n");
    printf("carro: %s\n", search(trie, "carro") ? "encontrado" : "não encontrado");
    printf("cas: %s\n", search(trie, "cas") ? "encontrado" : "não encontrado");
    printf("casa: %s\n", search(trie, "casa") ? "encontrado" : "não encontrado");
    printf("cachorro: %s\n", search(trie, "cachorro") ? "encontrado" : "não encontrado");
    
    printf("\n");
    findWordsWithPrefix(trie, "ca");
    
    printf("\n");
    findWordsWithPrefix(trie, "car");
    
    // Deletar uma palavra
    printf("\nDeletando 'casa'...\n");
    deleteWord(trie, "casa");
    printf("casa: %s\n", search(trie, "casa") ? "encontrado" : "não encontrado");
    
    // Liberar memória
    freeTrie(trie);
    
    return 0;
}