/**
 * ============================================================================
 * AVL TREE - ÁRVORE BINÁRIA BALANCEADA POR ALTURA
 * ============================================================================
 * 
 * AVL Tree é uma árvore binária de busca auto-balanceada onde a diferença
 * de altura entre subárvores esquerda e direita de qualquer nó é no máximo 1.
 * 
 * Inventada por Adelson-Velsky e Landis em 1962, foi a primeira estrutura
 * de dados auto-balanceada a ser inventada.
 * 
 * Características:
 * - Busca, inserção e remoção: O(log n) no pior caso
 * - Altura máxima: 1.44 * log₂(n+2) - 0.328
 * - Mais balanceada que Red-Black Trees
 * - Usa rotações para manter o balanceamento
 * 
 * Pré-requisito: Splay Tree (13-splay-tree)
 * Próximo: Skip List (15-skip-list)
 * 
 * Autor: Estrutura de Dados em C
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ==================== ESTRUTURA DA AVL TREE ====================

typedef struct AVLNode {
    int key;
    int height;
    struct AVLNode *left;
    struct AVLNode *right;
} AVLNode;

typedef struct {
    AVLNode *root;
    int size;
} AVLTree;

// ==================== FUNÇÕES AUXILIARES ====================

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(AVLNode *node) {
    return node ? node->height : 0;
}

int balance_factor(AVLNode *node) {
    return node ? height(node->left) - height(node->right) : 0;
}

void update_height(AVLNode *node) {
    if (node) {
        node->height = 1 + max(height(node->left), height(node->right));
    }
}

AVLNode* create_node(int key) {
    AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
    node->key = key;
    node->height = 1;
    node->left = node->right = NULL;
    return node;
}

// ==================== ROTAÇÕES ====================

/**
 * Rotação à direita
 *         y                x
 *        / \              / \
 *       x   T3    =>    T1   y
 *      / \                  / \
 *     T1  T2              T2  T3
 */
AVLNode* rotate_right(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;
    
    // Realizar rotação
    x->right = y;
    y->left = T2;
    
    // Atualizar alturas
    update_height(y);
    update_height(x);
    
    return x;
}

/**
 * Rotação à esquerda
 *       x                  y
 *      / \                / \
 *     T1  y      =>      x   T3
 *        / \            / \
 *       T2  T3        T1  T2
 */
AVLNode* rotate_left(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;
    
    // Realizar rotação
    y->left = x;
    x->right = T2;
    
    // Atualizar alturas
    update_height(x);
    update_height(y);
    
    return y;
}

// ==================== INSERÇÃO ====================

/**
 * Inserir chave na AVL Tree
 */
AVLNode* avl_insert(AVLNode *node, int key) {
    // 1. Inserção BST normal
    if (node == NULL) {
        return create_node(key);
    }
    
    if (key < node->key) {
        node->left = avl_insert(node->left, key);
    } else if (key > node->key) {
        node->right = avl_insert(node->right, key);
    } else {
        // Chave duplicada
        return node;
    }
    
    // 2. Atualizar altura do ancestral
    update_height(node);
    
    // 3. Obter fator de balanceamento
    int balance = balance_factor(node);
    
    // 4. Casos de desbalanceamento
    
    // Caso Left-Left (LL)
    if (balance > 1 && key < node->left->key) {
        return rotate_right(node);
    }
    
    // Caso Right-Right (RR)
    if (balance < -1 && key > node->right->key) {
        return rotate_left(node);
    }
    
    // Caso Left-Right (LR)
    if (balance > 1 && key > node->left->key) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    
    // Caso Right-Left (RL)
    if (balance < -1 && key < node->right->key) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    
    return node;
}

// ==================== REMOÇÃO ====================

/**
 * Encontrar nó com valor mínimo
 */
AVLNode* find_min(AVLNode *node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

/**
 * Remover chave da AVL Tree
 */
AVLNode* avl_delete(AVLNode *node, int key) {
    // 1. Remoção BST normal
    if (node == NULL) {
        return NULL;
    }
    
    if (key < node->key) {
        node->left = avl_delete(node->left, key);
    } else if (key > node->key) {
        node->right = avl_delete(node->right, key);
    } else {
        // Nó encontrado
        
        // Caso com 0 ou 1 filho
        if (node->left == NULL || node->right == NULL) {
            AVLNode *temp = node->left ? node->left : node->right;
            
            if (temp == NULL) {
                // Sem filhos
                temp = node;
                node = NULL;
            } else {
                // Um filho
                *node = *temp;
            }
            free(temp);
        } else {
            // Dois filhos: pegar sucessor in-order
            AVLNode *temp = find_min(node->right);
            node->key = temp->key;
            node->right = avl_delete(node->right, temp->key);
        }
    }
    
    if (node == NULL) {
        return NULL;
    }
    
    // 2. Atualizar altura
    update_height(node);
    
    // 3. Balancear
    int balance = balance_factor(node);
    
    // Caso Left-Left
    if (balance > 1 && balance_factor(node->left) >= 0) {
        return rotate_right(node);
    }
    
    // Caso Left-Right
    if (balance > 1 && balance_factor(node->left) < 0) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    
    // Caso Right-Right
    if (balance < -1 && balance_factor(node->right) <= 0) {
        return rotate_left(node);
    }
    
    // Caso Right-Left
    if (balance < -1 && balance_factor(node->right) > 0) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    
    return node;
}

// ==================== BUSCA ====================

AVLNode* avl_search(AVLNode *node, int key) {
    if (node == NULL || node->key == key) {
        return node;
    }
    
    if (key < node->key) {
        return avl_search(node->left, key);
    }
    return avl_search(node->right, key);
}

// ==================== TRAVESSIAS ====================

void inorder(AVLNode *node) {
    if (node) {
        inorder(node->left);
        printf("%d ", node->key);
        inorder(node->right);
    }
}

void preorder(AVLNode *node) {
    if (node) {
        printf("%d ", node->key);
        preorder(node->left);
        preorder(node->right);
    }
}

// ==================== VISUALIZAÇÃO ====================

void print_tree_helper(AVLNode *node, int level, char prefix) {
    if (node == NULL) return;
    
    for (int i = 0; i < level; i++) printf("    ");
    printf("%c── %d (h:%d, bf:%d)\n", prefix, node->key, 
           node->height, balance_factor(node));
    
    print_tree_helper(node->left, level + 1, 'L');
    print_tree_helper(node->right, level + 1, 'R');
}

void print_tree(AVLTree *tree) {
    if (tree->root == NULL) {
        printf("(árvore vazia)\n");
        return;
    }
    printf("Raiz: %d (altura: %d)\n", tree->root->key, tree->root->height);
    print_tree_helper(tree->root->left, 0, 'L');
    print_tree_helper(tree->root->right, 0, 'R');
}

// ==================== VERIFICAÇÃO ====================

/**
 * Verificar se a árvore é uma BST válida
 */
bool is_bst(AVLNode *node, int min, int max) {
    if (node == NULL) return true;
    
    if (node->key <= min || node->key >= max) return false;
    
    return is_bst(node->left, min, node->key) &&
           is_bst(node->right, node->key, max);
}

/**
 * Verificar se a árvore está balanceada (AVL)
 */
bool is_balanced(AVLNode *node) {
    if (node == NULL) return true;
    
    int bf = balance_factor(node);
    if (bf < -1 || bf > 1) return false;
    
    return is_balanced(node->left) && is_balanced(node->right);
}

// ==================== CRIAÇÃO E LIBERAÇÃO ====================

AVLTree* avl_create() {
    AVLTree *tree = (AVLTree *)malloc(sizeof(AVLTree));
    tree->root = NULL;
    tree->size = 0;
    return tree;
}

void avl_insert_wrapper(AVLTree *tree, int key) {
    tree->root = avl_insert(tree->root, key);
    tree->size++;
}

void avl_delete_wrapper(AVLTree *tree, int key) {
    tree->root = avl_delete(tree->root, key);
    tree->size--;
}

void free_tree(AVLNode *node) {
    if (node) {
        free_tree(node->left);
        free_tree(node->right);
        free(node);
    }
}

void avl_free(AVLTree *tree) {
    free_tree(tree->root);
    free(tree);
}

// ==================== TESTES ====================

void testar_insercao() {
    printf("=== TESTE DE INSERÇÃO AVL ===\n\n");
    
    AVLTree *tree = avl_create();
    
    int valores[] = {10, 20, 30, 40, 50, 25};
    int n = sizeof(valores) / sizeof(valores[0]);
    
    printf("Inserindo sequencialmente: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", valores[i]);
    }
    printf("\n\n");
    
    for (int i = 0; i < n; i++) {
        avl_insert_wrapper(tree, valores[i]);
        printf("Após inserir %d:\n", valores[i]);
        print_tree(tree);
        printf("\n");
    }
    
    printf("Verificação:\n");
    printf("  É BST válida: %s\n", is_bst(tree->root, -1000000, 1000000) ? "Sim" : "Não");
    printf("  Está balanceada: %s\n", is_balanced(tree->root) ? "Sim" : "Não");
    printf("\n");
    
    avl_free(tree);
}

void testar_rotacoes() {
    printf("=== DEMONSTRAÇÃO DE ROTAÇÕES ===\n\n");
    
    printf("1. Caso LEFT-LEFT (LL) - Rotação simples à direita:\n");
    printf("   Inserindo: 30, 20, 10\n");
    AVLTree *tree = avl_create();
    avl_insert_wrapper(tree, 30);
    avl_insert_wrapper(tree, 20);
    avl_insert_wrapper(tree, 10);
    print_tree(tree);
    printf("\n");
    avl_free(tree);
    
    printf("2. Caso RIGHT-RIGHT (RR) - Rotação simples à esquerda:\n");
    printf("   Inserindo: 10, 20, 30\n");
    tree = avl_create();
    avl_insert_wrapper(tree, 10);
    avl_insert_wrapper(tree, 20);
    avl_insert_wrapper(tree, 30);
    print_tree(tree);
    printf("\n");
    avl_free(tree);
    
    printf("3. Caso LEFT-RIGHT (LR) - Rotação dupla:\n");
    printf("   Inserindo: 30, 10, 20\n");
    tree = avl_create();
    avl_insert_wrapper(tree, 30);
    avl_insert_wrapper(tree, 10);
    avl_insert_wrapper(tree, 20);
    print_tree(tree);
    printf("\n");
    avl_free(tree);
    
    printf("4. Caso RIGHT-LEFT (RL) - Rotação dupla:\n");
    printf("   Inserindo: 10, 30, 20\n");
    tree = avl_create();
    avl_insert_wrapper(tree, 10);
    avl_insert_wrapper(tree, 30);
    avl_insert_wrapper(tree, 20);
    print_tree(tree);
    printf("\n");
    avl_free(tree);
}

void testar_delecao() {
    printf("=== TESTE DE DELEÇÃO AVL ===\n\n");
    
    AVLTree *tree = avl_create();
    
    for (int i = 1; i <= 7; i++) {
        avl_insert_wrapper(tree, i * 10);
    }
    
    printf("Árvore inicial:\n");
    print_tree(tree);
    printf("In-order: ");
    inorder(tree->root);
    printf("\n\n");
    
    printf("Deletando 20...\n");
    avl_delete_wrapper(tree, 20);
    print_tree(tree);
    printf("\n");
    
    printf("Deletando 40...\n");
    avl_delete_wrapper(tree, 40);
    print_tree(tree);
    printf("\n");
    
    printf("Verificação após deleções:\n");
    printf("  É BST válida: %s\n", is_bst(tree->root, -1000000, 1000000) ? "Sim" : "Não");
    printf("  Está balanceada: %s\n", is_balanced(tree->root) ? "Sim" : "Não");
    printf("\n");
    
    avl_free(tree);
}

void testar_pior_caso() {
    printf("=== TESTE PIOR CASO (BST vs AVL) ===\n\n");
    
    printf("Inserindo elementos em ordem crescente (1 a 15):\n\n");
    
    AVLTree *tree = avl_create();
    
    for (int i = 1; i <= 15; i++) {
        avl_insert_wrapper(tree, i);
    }
    
    printf("Árvore AVL resultante:\n");
    print_tree(tree);
    printf("\n");
    
    printf("Comparação:\n");
    printf("  BST normal: altura = 15 (degenerou em lista)\n");
    printf("  AVL Tree: altura = %d (balanceada!)\n", height(tree->root));
    printf("  Altura ótima: log2(15) ≈ 4\n\n");
    
    avl_free(tree);
}

void comparar_estruturas() {
    printf("=== COMPARAÇÃO DE ÁRVORES BALANCEADAS ===\n\n");
    
    printf("┌──────────────────┬──────────────┬──────────────┬──────────────┐\n");
    printf("│ Propriedade      │ AVL Tree     │ Red-Black    │ Splay Tree   │\n");
    printf("├──────────────────┼──────────────┼──────────────┼──────────────┤\n");
    printf("│ Busca (pior)     │ O(log n)     │ O(log n)     │ O(n)         │\n");
    printf("│ Inserção (pior)  │ O(log n)     │ O(log n)     │ O(n)         │\n");
    printf("│ Remoção (pior)   │ O(log n)     │ O(log n)     │ O(n)         │\n");
    printf("│ Amortizado       │ O(log n)     │ O(log n)     │ O(log n)     │\n");
    printf("│ Altura máxima    │ 1.44 log n   │ 2 log n      │ n            │\n");
    printf("│ Rotações insert  │ ≤ 2          │ ≤ 2          │ O(log n)     │\n");
    printf("│ Rotações delete  │ O(log n)     │ ≤ 3          │ O(log n)     │\n");
    printf("│ Armazenamento    │ altura       │ cor (1 bit)  │ nenhum       │\n");
    printf("└──────────────────┴──────────────┴──────────────┴──────────────┘\n\n");
    
    printf("AVL: Melhor para aplicações com muitas buscas.\n");
    printf("Red-Black: Melhor para aplicações com muitas inserções/remoções.\n");
    printf("Splay: Melhor quando há localidade temporal de acessos.\n\n");
}

// ==================== FUNÇÃO PRINCIPAL ====================

int main() {
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║                     AVL TREE                             ║\n");
    printf("║   Árvore Binária Auto-Balanceada por Altura              ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    testar_rotacoes();
    testar_insercao();
    testar_delecao();
    testar_pior_caso();
    comparar_estruturas();
    
    printf("═══════════════════════════════════════════════════════════\n");
    printf("Propriedades da AVL Tree:\n");
    printf("- Fator de balanceamento: -1, 0, ou +1 em cada nó\n");
    printf("- Altura garantida: O(log n)\n");
    printf("- Todas operações: O(log n) no pior caso\n");
    printf("- Primeira estrutura auto-balanceada (1962)\n");
    printf("\n");
    printf("Próximo: Skip List (15) - lista com níveis probabilísticos\n");
    printf("═══════════════════════════════════════════════════════════\n");
    
    return 0;
}
