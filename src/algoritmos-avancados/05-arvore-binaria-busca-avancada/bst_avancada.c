/**
 * ============================================================================
 * ÁRVORE BINÁRIA DE BUSCA AVANÇADA
 * ============================================================================
 * 
 * Este arquivo demonstra conceitos avançados de árvores binárias de busca,
 * servindo como base para entender estruturas mais complexas como:
 * - Trie (06-trie)
 * - AVL Tree (14-avl-tree)
 * - Splay Tree (13-splay-tree)
 * - Treap (12-treap)
 * 
 * Conceitos abordados:
 * - BST com operações completas
 * - Travessias (in-order, pre-order, post-order, level-order)
 * - Verificação de propriedades
 * - Operações de balanceamento manual
 * - Conversão para lista ordenada
 * 
 * Pré-requisito: Hash tables avançadas (04-hash-table-avancada)
 * 
 * Autor: Estrutura de Dados em C
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// ==================== ESTRUTURAS ====================

typedef struct BSTNode {
    int key;
    struct BSTNode *left;
    struct BSTNode *right;
    struct BSTNode *parent;
} BSTNode;

typedef struct {
    BSTNode *root;
    int size;
} BST;

// Fila para travessia por nível
typedef struct QueueNode {
    BSTNode *data;
    struct QueueNode *next;
} QueueNode;

typedef struct {
    QueueNode *front;
    QueueNode *rear;
} Queue;

// ==================== FUNÇÕES DE FILA ====================

Queue* queue_create() {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void queue_enqueue(Queue *q, BSTNode *node) {
    QueueNode *new_node = (QueueNode *)malloc(sizeof(QueueNode));
    new_node->data = node;
    new_node->next = NULL;
    
    if (q->rear == NULL) {
        q->front = q->rear = new_node;
    } else {
        q->rear->next = new_node;
        q->rear = new_node;
    }
}

BSTNode* queue_dequeue(Queue *q) {
    if (q->front == NULL) return NULL;
    
    QueueNode *temp = q->front;
    BSTNode *data = temp->data;
    q->front = q->front->next;
    
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    free(temp);
    return data;
}

bool queue_is_empty(Queue *q) {
    return q->front == NULL;
}

void queue_free(Queue *q) {
    while (!queue_is_empty(q)) {
        queue_dequeue(q);
    }
    free(q);
}

// ==================== FUNÇÕES BST BÁSICAS ====================

BSTNode* create_node(int key) {
    BSTNode *node = (BSTNode *)malloc(sizeof(BSTNode));
    node->key = key;
    node->left = node->right = node->parent = NULL;
    return node;
}

BST* bst_create() {
    BST *tree = (BST *)malloc(sizeof(BST));
    tree->root = NULL;
    tree->size = 0;
    return tree;
}

BSTNode* bst_insert_helper(BSTNode *node, BSTNode *parent, int key) {
    if (node == NULL) {
        BSTNode *new_node = create_node(key);
        new_node->parent = parent;
        return new_node;
    }
    
    if (key < node->key) {
        node->left = bst_insert_helper(node->left, node, key);
    } else if (key > node->key) {
        node->right = bst_insert_helper(node->right, node, key);
    }
    
    return node;
}

void bst_insert(BST *tree, int key) {
    tree->root = bst_insert_helper(tree->root, NULL, key);
    tree->size++;
}

BSTNode* bst_search(BSTNode *node, int key) {
    if (node == NULL || node->key == key) {
        return node;
    }
    
    if (key < node->key) {
        return bst_search(node->left, key);
    }
    return bst_search(node->right, key);
}

// ==================== TRAVESSIAS ====================

void inorder_traversal(BSTNode *node) {
    if (node != NULL) {
        inorder_traversal(node->left);
        printf("%d ", node->key);
        inorder_traversal(node->right);
    }
}

void preorder_traversal(BSTNode *node) {
    if (node != NULL) {
        printf("%d ", node->key);
        preorder_traversal(node->left);
        preorder_traversal(node->right);
    }
}

void postorder_traversal(BSTNode *node) {
    if (node != NULL) {
        postorder_traversal(node->left);
        postorder_traversal(node->right);
        printf("%d ", node->key);
    }
}

void levelorder_traversal(BSTNode *root) {
    if (root == NULL) return;
    
    Queue *q = queue_create();
    queue_enqueue(q, root);
    
    while (!queue_is_empty(q)) {
        BSTNode *current = queue_dequeue(q);
        printf("%d ", current->key);
        
        if (current->left) queue_enqueue(q, current->left);
        if (current->right) queue_enqueue(q, current->right);
    }
    
    queue_free(q);
}

// ==================== OPERAÇÕES AVANÇADAS ====================

/**
 * Encontrar o nó mínimo na subárvore
 */
BSTNode* find_min(BSTNode *node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

/**
 * Encontrar o nó máximo na subárvore
 */
BSTNode* find_max(BSTNode *node) {
    while (node->right != NULL) {
        node = node->right;
    }
    return node;
}

/**
 * Encontrar o sucessor in-order
 */
BSTNode* successor(BSTNode *node) {
    if (node->right != NULL) {
        return find_min(node->right);
    }
    
    BSTNode *parent = node->parent;
    while (parent != NULL && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

/**
 * Encontrar o predecessor in-order
 */
BSTNode* predecessor(BSTNode *node) {
    if (node->left != NULL) {
        return find_max(node->left);
    }
    
    BSTNode *parent = node->parent;
    while (parent != NULL && node == parent->left) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

/**
 * Transplantar subárvore (helper para deleção)
 */
void transplant(BST *tree, BSTNode *u, BSTNode *v) {
    if (u->parent == NULL) {
        tree->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    
    if (v != NULL) {
        v->parent = u->parent;
    }
}

/**
 * Deletar nó da árvore
 */
void bst_delete(BST *tree, int key) {
    BSTNode *z = bst_search(tree->root, key);
    if (z == NULL) return;
    
    if (z->left == NULL) {
        transplant(tree, z, z->right);
    } else if (z->right == NULL) {
        transplant(tree, z, z->left);
    } else {
        BSTNode *y = find_min(z->right);
        if (y->parent != z) {
            transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
    }
    
    free(z);
    tree->size--;
}

// ==================== PROPRIEDADES DA ÁRVORE ====================

/**
 * Calcular altura da árvore
 */
int tree_height(BSTNode *node) {
    if (node == NULL) return -1;
    
    int left_height = tree_height(node->left);
    int right_height = tree_height(node->right);
    
    return 1 + (left_height > right_height ? left_height : right_height);
}

/**
 * Contar nós na árvore
 */
int count_nodes(BSTNode *node) {
    if (node == NULL) return 0;
    return 1 + count_nodes(node->left) + count_nodes(node->right);
}

/**
 * Contar folhas na árvore
 */
int count_leaves(BSTNode *node) {
    if (node == NULL) return 0;
    if (node->left == NULL && node->right == NULL) return 1;
    return count_leaves(node->left) + count_leaves(node->right);
}

/**
 * Verificar se é uma BST válida
 */
bool is_bst_helper(BSTNode *node, int min, int max) {
    if (node == NULL) return true;
    
    if (node->key <= min || node->key >= max) {
        return false;
    }
    
    return is_bst_helper(node->left, min, node->key) &&
           is_bst_helper(node->right, node->key, max);
}

bool is_valid_bst(BST *tree) {
    return is_bst_helper(tree->root, INT_MIN, INT_MAX);
}

/**
 * Verificar se a árvore está balanceada
 */
int check_balance(BSTNode *node, bool *balanced) {
    if (node == NULL) return -1;
    
    int left_height = check_balance(node->left, balanced);
    int right_height = check_balance(node->right, balanced);
    
    if (abs(left_height - right_height) > 1) {
        *balanced = false;
    }
    
    return 1 + (left_height > right_height ? left_height : right_height);
}

bool is_balanced(BST *tree) {
    bool balanced = true;
    check_balance(tree->root, &balanced);
    return balanced;
}

// ==================== K-ÉSIMO MENOR ELEMENTO ====================

int kth_smallest_helper(BSTNode *node, int *k) {
    if (node == NULL) return -1;
    
    // Procurar na subárvore esquerda
    int left = kth_smallest_helper(node->left, k);
    if (*k == 0) return left;
    
    // Verificar nó atual
    (*k)--;
    if (*k == 0) return node->key;
    
    // Procurar na subárvore direita
    return kth_smallest_helper(node->right, k);
}

int kth_smallest(BST *tree, int k) {
    return kth_smallest_helper(tree->root, &k);
}

// ==================== ANCESTRAL COMUM MAIS BAIXO (LCA) ====================

BSTNode* lowest_common_ancestor(BSTNode *node, int p, int q) {
    if (node == NULL) return NULL;
    
    // Ambos menores - ir para esquerda
    if (p < node->key && q < node->key) {
        return lowest_common_ancestor(node->left, p, q);
    }
    
    // Ambos maiores - ir para direita
    if (p > node->key && q > node->key) {
        return lowest_common_ancestor(node->right, p, q);
    }
    
    // Um de cada lado - este é o LCA
    return node;
}

// ==================== SERIALIZAÇÃO ====================

/**
 * Serializar árvore para array (preorder)
 */
void serialize_helper(BSTNode *node, int *arr, int *idx) {
    if (node == NULL) {
        arr[(*idx)++] = INT_MIN; // Marcador de NULL
        return;
    }
    
    arr[(*idx)++] = node->key;
    serialize_helper(node->left, arr, idx);
    serialize_helper(node->right, arr, idx);
}

int* serialize(BST *tree, int *size) {
    *size = tree->size * 2 + 1;
    int *arr = (int *)malloc((*size) * sizeof(int));
    int idx = 0;
    serialize_helper(tree->root, arr, &idx);
    return arr;
}

// ==================== VISUALIZAÇÃO ====================

void print_tree_helper(BSTNode *node, int level, char prefix) {
    if (node == NULL) return;
    
    for (int i = 0; i < level; i++) printf("    ");
    printf("%c── %d\n", prefix, node->key);
    
    print_tree_helper(node->left, level + 1, 'L');
    print_tree_helper(node->right, level + 1, 'R');
}

void print_tree(BST *tree) {
    if (tree->root == NULL) {
        printf("(árvore vazia)\n");
        return;
    }
    printf("Raiz: %d\n", tree->root->key);
    print_tree_helper(tree->root->left, 0, 'L');
    print_tree_helper(tree->root->right, 0, 'R');
}

// ==================== LIBERAÇÃO DE MEMÓRIA ====================

void free_tree_helper(BSTNode *node) {
    if (node == NULL) return;
    free_tree_helper(node->left);
    free_tree_helper(node->right);
    free(node);
}

void bst_free(BST *tree) {
    free_tree_helper(tree->root);
    free(tree);
}

// ==================== TESTES ====================

void testar_operacoes_basicas() {
    printf("=== OPERAÇÕES BÁSICAS DA BST ===\n\n");
    
    BST *tree = bst_create();
    
    int valores[] = {50, 30, 70, 20, 40, 60, 80, 25, 35};
    int n = sizeof(valores) / sizeof(valores[0]);
    
    printf("Inserindo: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", valores[i]);
        bst_insert(tree, valores[i]);
    }
    printf("\n\n");
    
    printf("Estrutura da árvore:\n");
    print_tree(tree);
    printf("\n");
    
    printf("Travessia In-Order (ordenada): ");
    inorder_traversal(tree->root);
    printf("\n");
    
    printf("Travessia Pre-Order: ");
    preorder_traversal(tree->root);
    printf("\n");
    
    printf("Travessia Post-Order: ");
    postorder_traversal(tree->root);
    printf("\n");
    
    printf("Travessia Level-Order: ");
    levelorder_traversal(tree->root);
    printf("\n\n");
    
    bst_free(tree);
}

void testar_propriedades() {
    printf("=== PROPRIEDADES DA ÁRVORE ===\n\n");
    
    BST *tree = bst_create();
    int valores[] = {50, 30, 70, 20, 40, 60, 80};
    
    for (int i = 0; i < 7; i++) {
        bst_insert(tree, valores[i]);
    }
    
    printf("Árvore: ");
    inorder_traversal(tree->root);
    printf("\n\n");
    
    printf("Altura: %d\n", tree_height(tree->root));
    printf("Número de nós: %d\n", count_nodes(tree->root));
    printf("Número de folhas: %d\n", count_leaves(tree->root));
    printf("É BST válida: %s\n", is_valid_bst(tree) ? "Sim" : "Não");
    printf("Está balanceada: %s\n", is_balanced(tree) ? "Sim" : "Não");
    
    printf("\n");
    
    bst_free(tree);
}

void testar_operacoes_avancadas() {
    printf("=== OPERAÇÕES AVANÇADAS ===\n\n");
    
    BST *tree = bst_create();
    int valores[] = {50, 30, 70, 20, 40, 60, 80, 25};
    
    for (int i = 0; i < 8; i++) {
        bst_insert(tree, valores[i]);
    }
    
    printf("Árvore: ");
    inorder_traversal(tree->root);
    printf("\n\n");
    
    printf("Mínimo: %d\n", find_min(tree->root)->key);
    printf("Máximo: %d\n", find_max(tree->root)->key);
    
    BSTNode *node = bst_search(tree->root, 30);
    if (node) {
        BSTNode *succ = successor(node);
        BSTNode *pred = predecessor(node);
        printf("Nó 30 - Sucessor: %d, Predecessor: %d\n", 
               succ ? succ->key : -1, pred ? pred->key : -1);
    }
    
    printf("\n3º menor elemento: %d\n", kth_smallest(tree, 3));
    printf("5º menor elemento: %d\n", kth_smallest(tree, 5));
    
    BSTNode *lca = lowest_common_ancestor(tree->root, 20, 40);
    printf("LCA de 20 e 40: %d\n", lca ? lca->key : -1);
    
    lca = lowest_common_ancestor(tree->root, 20, 80);
    printf("LCA de 20 e 80: %d\n", lca ? lca->key : -1);
    
    printf("\n");
    
    bst_free(tree);
}

void testar_delecao() {
    printf("=== TESTE DE DELEÇÃO ===\n\n");
    
    BST *tree = bst_create();
    int valores[] = {50, 30, 70, 20, 40, 60, 80};
    
    for (int i = 0; i < 7; i++) {
        bst_insert(tree, valores[i]);
    }
    
    printf("Árvore original: ");
    inorder_traversal(tree->root);
    printf("\n");
    
    printf("Deletando 20 (folha)...\n");
    bst_delete(tree, 20);
    printf("Resultado: ");
    inorder_traversal(tree->root);
    printf("\n");
    
    printf("Deletando 30 (1 filho)...\n");
    bst_delete(tree, 30);
    printf("Resultado: ");
    inorder_traversal(tree->root);
    printf("\n");
    
    printf("Deletando 50 (raiz, 2 filhos)...\n");
    bst_delete(tree, 50);
    printf("Resultado: ");
    inorder_traversal(tree->root);
    printf("\n\n");
    
    bst_free(tree);
}

// ==================== FUNÇÃO PRINCIPAL ====================

int main() {
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║        ÁRVORE BINÁRIA DE BUSCA AVANÇADA                  ║\n");
    printf("║   Fundamento para estruturas mais complexas              ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    testar_operacoes_basicas();
    testar_propriedades();
    testar_operacoes_avancadas();
    testar_delecao();
    
    printf("═══════════════════════════════════════════════════════════\n");
    printf("Esta BST serve como base para:\n");
    printf("- Trie (06): árvore de prefixos para strings\n");
    printf("- Treap (12): BST + Heap para balanceamento probabilístico\n");
    printf("- Splay Tree (13): BST auto-ajustável\n");
    printf("- AVL Tree (14): BST balanceada por altura\n");
    printf("═══════════════════════════════════════════════════════════\n");
    
    return 0;
}
