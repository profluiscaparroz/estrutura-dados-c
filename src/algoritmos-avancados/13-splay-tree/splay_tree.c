/**
 * ============================================================================
 * SPLAY TREE - ÁRVORE AUTO-AJUSTÁVEL
 * ============================================================================
 * 
 * Splay Tree é uma árvore binária de busca auto-ajustável que move o nó
 * acessado para a raiz através de uma série de rotações (splay).
 * 
 * Características:
 * - Todas operações: O(log n) amortizado
 * - Elementos acessados recentemente ficam próximos à raiz
 * - Sem armazenamento de informação de balanceamento
 * - Excelente para padrões de acesso não-uniformes
 * 
 * Propriedades importantes:
 * - Static Optimality: para sequências fixas, performance próxima ao ótimo
 * - Working Set Property: acesso rápido a elementos recentes
 * - Dynamic Finger: bom para acessos sequenciais
 * 
 * Pré-requisito: Treap (12-treap)
 * 
 * Autor: Estrutura de Dados em C
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ==================== ESTRUTURA DA SPLAY TREE ====================

typedef struct SplayNode {
    int key;
    struct SplayNode *left;
    struct SplayNode *right;
    struct SplayNode *parent;
} SplayNode;

typedef struct {
    SplayNode *root;
    int size;
} SplayTree;

// ==================== FUNÇÕES AUXILIARES ====================

SplayNode* create_node(int key) {
    SplayNode *node = (SplayNode *)malloc(sizeof(SplayNode));
    node->key = key;
    node->left = node->right = node->parent = NULL;
    return node;
}

SplayTree* splay_create() {
    SplayTree *tree = (SplayTree *)malloc(sizeof(SplayTree));
    tree->root = NULL;
    tree->size = 0;
    return tree;
}

// ==================== ROTAÇÕES ====================

/**
 * Rotação à direita (zig)
 */
void rotate_right(SplayTree *tree, SplayNode *x) {
    SplayNode *y = x->parent;
    
    if (y->parent) {
        if (y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }
    } else {
        tree->root = x;
    }
    
    x->parent = y->parent;
    y->parent = x;
    
    y->left = x->right;
    if (x->right) {
        x->right->parent = y;
    }
    
    x->right = y;
}

/**
 * Rotação à esquerda (zag)
 */
void rotate_left(SplayTree *tree, SplayNode *x) {
    SplayNode *y = x->parent;
    
    if (y->parent) {
        if (y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }
    } else {
        tree->root = x;
    }
    
    x->parent = y->parent;
    y->parent = x;
    
    y->right = x->left;
    if (x->left) {
        x->left->parent = y;
    }
    
    x->left = y;
}

// ==================== OPERAÇÃO SPLAY ====================

/**
 * Move o nó x para a raiz através de rotações
 * 
 * Casos:
 * 1. Zig: x é filho da raiz
 * 2. Zig-zig: x e pai são ambos filhos esquerdos (ou direitos)
 * 3. Zig-zag: x é filho esquerdo de filho direito (ou vice-versa)
 */
void splay(SplayTree *tree, SplayNode *x) {
    while (x->parent != NULL) {
        SplayNode *p = x->parent;      // Pai
        SplayNode *g = p->parent;      // Avô
        
        if (g == NULL) {
            // Caso 1: Zig (pai é a raiz)
            if (x == p->left) {
                rotate_right(tree, x);
            } else {
                rotate_left(tree, x);
            }
        } else if (x == p->left && p == g->left) {
            // Caso 2: Zig-zig (ambos esquerdos)
            rotate_right(tree, p);
            rotate_right(tree, x);
        } else if (x == p->right && p == g->right) {
            // Caso 2: Zig-zig (ambos direitos)
            rotate_left(tree, p);
            rotate_left(tree, x);
        } else if (x == p->right && p == g->left) {
            // Caso 3: Zig-zag (esquerda-direita)
            rotate_left(tree, x);
            rotate_right(tree, x);
        } else {
            // Caso 3: Zig-zag (direita-esquerda)
            rotate_right(tree, x);
            rotate_left(tree, x);
        }
    }
}

// ==================== OPERAÇÕES PRINCIPAIS ====================

/**
 * Inserir chave na Splay Tree
 */
void splay_insert(SplayTree *tree, int key) {
    SplayNode *new_node = create_node(key);
    
    if (tree->root == NULL) {
        tree->root = new_node;
        tree->size++;
        return;
    }
    
    SplayNode *current = tree->root;
    SplayNode *parent = NULL;
    
    while (current != NULL) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        } else if (key > current->key) {
            current = current->right;
        } else {
            // Chave duplicada
            free(new_node);
            splay(tree, current);  // Mover para raiz mesmo assim
            return;
        }
    }
    
    new_node->parent = parent;
    
    if (key < parent->key) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }
    
    tree->size++;
    splay(tree, new_node);
}

/**
 * Buscar chave na Splay Tree
 * Retorna o nó se encontrado, ou NULL
 * O nó acessado (ou último visitado) é movido para a raiz
 */
SplayNode* splay_search(SplayTree *tree, int key) {
    SplayNode *current = tree->root;
    SplayNode *last = NULL;
    
    while (current != NULL) {
        last = current;
        if (key < current->key) {
            current = current->left;
        } else if (key > current->key) {
            current = current->right;
        } else {
            splay(tree, current);
            return current;
        }
    }
    
    if (last != NULL) {
        splay(tree, last);
    }
    
    return NULL;
}

/**
 * Encontrar mínimo na subárvore
 */
SplayNode* find_min(SplayNode *node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

/**
 * Encontrar máximo na subárvore
 */
SplayNode* find_max(SplayNode *node) {
    while (node->right != NULL) {
        node = node->right;
    }
    return node;
}

/**
 * Deletar chave da Splay Tree
 */
void splay_delete(SplayTree *tree, int key) {
    if (tree->root == NULL) return;
    
    // Primeiro, buscar e fazer splay do nó
    SplayNode *node = splay_search(tree, key);
    
    if (node == NULL || tree->root->key != key) {
        return;  // Não encontrado
    }
    
    // Agora a raiz tem a chave a ser deletada
    SplayNode *left = tree->root->left;
    SplayNode *right = tree->root->right;
    
    free(tree->root);
    tree->size--;
    
    if (left == NULL) {
        tree->root = right;
        if (right) right->parent = NULL;
    } else if (right == NULL) {
        tree->root = left;
        left->parent = NULL;
    } else {
        // Fazer splay do máximo da subárvore esquerda
        left->parent = NULL;
        tree->root = left;
        
        SplayNode *max_left = find_max(left);
        splay(tree, max_left);
        
        // Agora max_left é a raiz e não tem filho direito
        tree->root->right = right;
        right->parent = tree->root;
    }
}

// ==================== OPERAÇÕES ADICIONAIS ====================

/**
 * Encontrar sucessor
 */
SplayNode* splay_successor(SplayTree *tree, int key) {
    splay_search(tree, key);
    
    if (tree->root == NULL) return NULL;
    
    if (tree->root->key > key) {
        return tree->root;
    }
    
    if (tree->root->right == NULL) {
        return NULL;
    }
    
    return find_min(tree->root->right);
}

/**
 * Encontrar predecessor
 */
SplayNode* splay_predecessor(SplayTree *tree, int key) {
    splay_search(tree, key);
    
    if (tree->root == NULL) return NULL;
    
    if (tree->root->key < key) {
        return tree->root;
    }
    
    if (tree->root->left == NULL) {
        return NULL;
    }
    
    return find_max(tree->root->left);
}

// ==================== TRAVESSIAS ====================

void inorder(SplayNode *node) {
    if (node) {
        inorder(node->left);
        printf("%d ", node->key);
        inorder(node->right);
    }
}

int tree_height(SplayNode *node) {
    if (node == NULL) return -1;
    
    int left_h = tree_height(node->left);
    int right_h = tree_height(node->right);
    
    return 1 + (left_h > right_h ? left_h : right_h);
}

void print_tree_helper(SplayNode *node, int level, char prefix) {
    if (node == NULL) return;
    
    for (int i = 0; i < level; i++) printf("    ");
    printf("%c── %d\n", prefix, node->key);
    
    print_tree_helper(node->left, level + 1, 'L');
    print_tree_helper(node->right, level + 1, 'R');
}

void print_tree(SplayTree *tree) {
    if (tree->root == NULL) {
        printf("(árvore vazia)\n");
        return;
    }
    printf("Raiz: %d\n", tree->root->key);
    print_tree_helper(tree->root->left, 0, 'L');
    print_tree_helper(tree->root->right, 0, 'R');
}

// ==================== LIBERAÇÃO DE MEMÓRIA ====================

void free_tree(SplayNode *node) {
    if (node) {
        free_tree(node->left);
        free_tree(node->right);
        free(node);
    }
}

void splay_free(SplayTree *tree) {
    free_tree(tree->root);
    free(tree);
}

// ==================== TESTES ====================

void testar_basico() {
    printf("=== TESTE BÁSICO SPLAY TREE ===\n\n");
    
    SplayTree *tree = splay_create();
    
    int valores[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(valores) / sizeof(valores[0]);
    
    printf("Inserindo: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", valores[i]);
        splay_insert(tree, valores[i]);
    }
    printf("\n\n");
    
    printf("Após inserções (último elemento na raiz):\n");
    print_tree(tree);
    printf("\n");
    
    printf("Travessia In-Order: ");
    inorder(tree->root);
    printf("\n\n");
    
    splay_free(tree);
}

void testar_splay_effect() {
    printf("=== EFEITO DO SPLAY ===\n\n");
    
    SplayTree *tree = splay_create();
    
    for (int i = 1; i <= 7; i++) {
        splay_insert(tree, i * 10);
    }
    
    printf("Árvore inicial:\n");
    print_tree(tree);
    printf("Altura: %d\n\n", tree_height(tree->root));
    
    printf("Buscando 20 (vai para raiz)...\n");
    splay_search(tree, 20);
    printf("Após buscar 20:\n");
    print_tree(tree);
    printf("\n");
    
    printf("Buscando 60 (vai para raiz)...\n");
    splay_search(tree, 60);
    printf("Após buscar 60:\n");
    print_tree(tree);
    printf("\n");
    
    splay_free(tree);
}

void testar_delecao() {
    printf("=== TESTE DE DELEÇÃO ===\n\n");
    
    SplayTree *tree = splay_create();
    
    for (int i = 1; i <= 7; i++) {
        splay_insert(tree, i * 10);
    }
    
    printf("Árvore inicial: ");
    inorder(tree->root);
    printf("\n\n");
    
    printf("Deletando 40...\n");
    splay_delete(tree, 40);
    printf("Resultado: ");
    inorder(tree->root);
    printf("\n");
    print_tree(tree);
    printf("\n");
    
    printf("Deletando raiz (%d)...\n", tree->root->key);
    splay_delete(tree, tree->root->key);
    printf("Resultado: ");
    inorder(tree->root);
    printf("\n\n");
    
    splay_free(tree);
}

void testar_localidade() {
    printf("=== TESTE DE LOCALIDADE TEMPORAL ===\n\n");
    
    SplayTree *tree = splay_create();
    
    // Inserir muitos elementos
    for (int i = 0; i < 100; i++) {
        splay_insert(tree, i);
    }
    
    printf("Árvore com 100 elementos (0-99)\n");
    printf("Altura inicial: %d\n\n", tree_height(tree->root));
    
    // Acessar repetidamente elementos próximos
    printf("Acessando elementos 50, 51, 52 repetidamente...\n");
    for (int i = 0; i < 10; i++) {
        splay_search(tree, 50);
        splay_search(tree, 51);
        splay_search(tree, 52);
    }
    
    printf("Após acessos repetidos:\n");
    printf("  Raiz: %d\n", tree->root->key);
    printf("  Elementos recentes estão próximos da raiz!\n\n");
    
    splay_free(tree);
}

void testar_working_set() {
    printf("=== WORKING SET PROPERTY ===\n\n");
    
    SplayTree *tree = splay_create();
    
    for (int i = 0; i < 1000; i++) {
        splay_insert(tree, i);
    }
    
    printf("Árvore com 1000 elementos\n");
    printf("Altura inicial: %d\n\n", tree_height(tree->root));
    
    // Simular working set (conjunto de trabalho)
    printf("Acessando working set {100, 101, 102, 103, 104}...\n");
    for (int r = 0; r < 100; r++) {
        for (int i = 100; i <= 104; i++) {
            splay_search(tree, i);
        }
    }
    
    printf("Após 500 acessos ao working set:\n");
    printf("  Raiz: %d\n", tree->root->key);
    printf("  Working set fica próximo à raiz = acesso rápido!\n\n");
    
    splay_free(tree);
}

void comparar_com_bst() {
    printf("=== COMPARAÇÃO COM BST NORMAL ===\n\n");
    
    printf("Para sequência de acessos não-uniforme:\n");
    printf("┌────────────────────┬───────────────┬────────────────┐\n");
    printf("│ Operação           │ BST Normal    │ Splay Tree     │\n");
    printf("├────────────────────┼───────────────┼────────────────┤\n");
    printf("│ Busca (pior caso)  │ O(n)          │ O(n)           │\n");
    printf("│ Busca (amortizado) │ O(log n)      │ O(log n)       │\n");
    printf("│ Acesso repetido    │ O(h) sempre   │ O(1) após splay│\n");
    printf("│ Working set        │ O(h) sempre   │ O(log w)*      │\n");
    printf("│ Armazenamento extra│ Nenhum        │ Nenhum         │\n");
    printf("└────────────────────┴───────────────┴────────────────┘\n");
    printf("\n* w = tamanho do working set\n\n");
}

// ==================== FUNÇÃO PRINCIPAL ====================

int main() {
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║                    SPLAY TREE                            ║\n");
    printf("║   Árvore auto-ajustável com localidade temporal          ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    testar_basico();
    testar_splay_effect();
    testar_delecao();
    testar_localidade();
    testar_working_set();
    comparar_com_bst();
    
    printf("═══════════════════════════════════════════════════════════\n");
    printf("Propriedades da Splay Tree:\n");
    printf("- Operações amortizadas: O(log n)\n");
    printf("- Elementos recentes ficam próximos à raiz\n");
    printf("- Sem necessidade de armazenar balanceamento\n");
    printf("- Excelente para caches e padrões de acesso localizados\n");
    printf("\n");
    printf("Próximo: AVL Tree (14) - balanceamento por altura\n");
    printf("═══════════════════════════════════════════════════════════\n");
    
    return 0;
}
