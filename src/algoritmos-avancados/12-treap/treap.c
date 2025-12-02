/**
 * ============================================================================
 * TREAP - ÁRVORE BINÁRIA COM PRIORIDADES ALEATÓRIAS
 * ============================================================================
 * 
 * Treap é uma combinação de Tree (árvore binária de busca) e Heap.
 * Cada nó tem uma chave (segue propriedade BST) e uma prioridade
 * aleatória (segue propriedade Heap).
 * 
 * Características:
 * - Altura esperada: O(log n) - balanceamento probabilístico
 * - Operações esperadas: O(log n) para busca, inserção e remoção
 * - Mais simples de implementar que AVL ou Red-Black Trees
 * - Sem necessidade de rotações complexas de balanceamento
 * 
 * Aplicações:
 * - Quando simplicidade é preferível à garantia de pior caso
 * - Estruturas de dados persistentes
 * - Árvores implícitas para sequências
 * 
 * Pré-requisito: HyperLogLog (11-hyperloglog)
 * 
 * Autor: Estrutura de Dados em C
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

// ==================== ESTRUTURA DO TREAP ====================

typedef struct TreapNode {
    int key;                    // Chave (propriedade BST)
    int priority;               // Prioridade aleatória (propriedade Heap-max)
    int size;                   // Tamanho da subárvore (para operações de rank)
    struct TreapNode *left;
    struct TreapNode *right;
} TreapNode;

typedef struct {
    TreapNode *root;
} Treap;

// ==================== FUNÇÕES AUXILIARES ====================

/**
 * Criar novo nó
 */
TreapNode* create_node(int key) {
    TreapNode *node = (TreapNode *)malloc(sizeof(TreapNode));
    node->key = key;
    node->priority = rand();  // Prioridade aleatória
    node->size = 1;
    node->left = node->right = NULL;
    return node;
}

/**
 * Obter tamanho da subárvore
 */
int get_size(TreapNode *node) {
    return node ? node->size : 0;
}

/**
 * Atualizar tamanho do nó
 */
void update_size(TreapNode *node) {
    if (node) {
        node->size = 1 + get_size(node->left) + get_size(node->right);
    }
}

// ==================== ROTAÇÕES ====================

/**
 * Rotação à direita
 *       y                x
 *      / \              / \
 *     x   C    =>      A   y
 *    / \                  / \
 *   A   B                B   C
 */
TreapNode* rotate_right(TreapNode *y) {
    TreapNode *x = y->left;
    TreapNode *B = x->right;
    
    x->right = y;
    y->left = B;
    
    update_size(y);
    update_size(x);
    
    return x;
}

/**
 * Rotação à esquerda
 *     x                  y
 *    / \                / \
 *   A   y      =>      x   C
 *      / \            / \
 *     B   C          A   B
 */
TreapNode* rotate_left(TreapNode *x) {
    TreapNode *y = x->right;
    TreapNode *B = y->left;
    
    y->left = x;
    x->right = B;
    
    update_size(x);
    update_size(y);
    
    return y;
}

// ==================== OPERAÇÕES PRINCIPAIS ====================

/**
 * Inserir chave no treap
 */
TreapNode* treap_insert(TreapNode *node, int key) {
    // Caso base: criar novo nó
    if (node == NULL) {
        return create_node(key);
    }
    
    // Inserção BST normal
    if (key < node->key) {
        node->left = treap_insert(node->left, key);
        
        // Manter propriedade heap: se filho tem maior prioridade, rotacionar
        if (node->left->priority > node->priority) {
            node = rotate_right(node);
        }
    } else if (key > node->key) {
        node->right = treap_insert(node->right, key);
        
        if (node->right->priority > node->priority) {
            node = rotate_left(node);
        }
    }
    // Chave duplicada: ignorar (ou poderia atualizar)
    
    update_size(node);
    return node;
}

/**
 * Buscar chave no treap
 */
TreapNode* treap_search(TreapNode *node, int key) {
    if (node == NULL || node->key == key) {
        return node;
    }
    
    if (key < node->key) {
        return treap_search(node->left, key);
    }
    return treap_search(node->right, key);
}

/**
 * Remover chave do treap
 */
TreapNode* treap_delete(TreapNode *node, int key) {
    if (node == NULL) {
        return NULL;
    }
    
    if (key < node->key) {
        node->left = treap_delete(node->left, key);
    } else if (key > node->key) {
        node->right = treap_delete(node->right, key);
    } else {
        // Encontrou o nó para deletar
        
        // Caso 1: folha
        if (node->left == NULL && node->right == NULL) {
            free(node);
            return NULL;
        }
        
        // Caso 2: um filho
        if (node->left == NULL) {
            TreapNode *temp = node->right;
            free(node);
            return temp;
        }
        if (node->right == NULL) {
            TreapNode *temp = node->left;
            free(node);
            return temp;
        }
        
        // Caso 3: dois filhos - rotacionar para baixo até virar folha
        if (node->left->priority > node->right->priority) {
            node = rotate_right(node);
            node->right = treap_delete(node->right, key);
        } else {
            node = rotate_left(node);
            node->left = treap_delete(node->left, key);
        }
    }
    
    update_size(node);
    return node;
}

// ==================== OPERAÇÕES DE SPLIT E MERGE ====================

/**
 * Split: dividir treap em dois baseado em uma chave
 * left_tree: elementos < key
 * right_tree: elementos >= key
 */
void treap_split(TreapNode *node, int key, TreapNode **left, TreapNode **right) {
    if (node == NULL) {
        *left = *right = NULL;
        return;
    }
    
    if (node->key < key) {
        *left = node;
        treap_split(node->right, key, &((*left)->right), right);
        update_size(*left);
    } else {
        *right = node;
        treap_split(node->left, key, left, &((*right)->left));
        update_size(*right);
    }
}

/**
 * Merge: combinar dois treaps (assumindo que todos elementos de left < right)
 */
TreapNode* treap_merge(TreapNode *left, TreapNode *right) {
    if (left == NULL) return right;
    if (right == NULL) return left;
    
    if (left->priority > right->priority) {
        left->right = treap_merge(left->right, right);
        update_size(left);
        return left;
    } else {
        right->left = treap_merge(left, right->left);
        update_size(right);
        return right;
    }
}

// ==================== OPERAÇÕES DE RANK ====================

/**
 * Encontrar k-ésimo menor elemento (1-indexed)
 */
int treap_kth_element(TreapNode *node, int k) {
    if (node == NULL) return -1;
    
    int left_size = get_size(node->left);
    
    if (k <= left_size) {
        return treap_kth_element(node->left, k);
    } else if (k == left_size + 1) {
        return node->key;
    } else {
        return treap_kth_element(node->right, k - left_size - 1);
    }
}

/**
 * Contar elementos menores que key
 */
int treap_count_less(TreapNode *node, int key) {
    if (node == NULL) return 0;
    
    if (key <= node->key) {
        return treap_count_less(node->left, key);
    } else {
        return 1 + get_size(node->left) + treap_count_less(node->right, key);
    }
}

// ==================== TRAVESSIAS ====================

void inorder(TreapNode *node) {
    if (node) {
        inorder(node->left);
        printf("%d ", node->key);
        inorder(node->right);
    }
}

void print_treap_helper(TreapNode *node, int level, char prefix) {
    if (node == NULL) return;
    
    for (int i = 0; i < level; i++) printf("    ");
    printf("%c── %d (p:%d, s:%d)\n", prefix, node->key, node->priority, node->size);
    
    print_treap_helper(node->left, level + 1, 'L');
    print_treap_helper(node->right, level + 1, 'R');
}

void print_treap(TreapNode *root) {
    if (root == NULL) {
        printf("(treap vazio)\n");
        return;
    }
    printf("Raiz: %d (prioridade: %d)\n", root->key, root->priority);
    print_treap_helper(root->left, 0, 'L');
    print_treap_helper(root->right, 0, 'R');
}

// ==================== LIBERAÇÃO DE MEMÓRIA ====================

void treap_free(TreapNode *node) {
    if (node) {
        treap_free(node->left);
        treap_free(node->right);
        free(node);
    }
}

// ==================== CRIAÇÃO DO TREAP ====================

Treap* treap_create() {
    Treap *t = (Treap *)malloc(sizeof(Treap));
    t->root = NULL;
    return t;
}

void treap_insert_wrapper(Treap *t, int key) {
    t->root = treap_insert(t->root, key);
}

void treap_delete_wrapper(Treap *t, int key) {
    t->root = treap_delete(t->root, key);
}

// ==================== VERIFICAÇÃO ====================

/**
 * Verificar propriedade BST
 */
bool verify_bst(TreapNode *node, int min, int max) {
    if (node == NULL) return true;
    
    if (node->key <= min || node->key >= max) return false;
    
    return verify_bst(node->left, min, node->key) &&
           verify_bst(node->right, node->key, max);
}

/**
 * Verificar propriedade heap (max)
 */
bool verify_heap(TreapNode *node) {
    if (node == NULL) return true;
    
    if (node->left && node->left->priority > node->priority) return false;
    if (node->right && node->right->priority > node->priority) return false;
    
    return verify_heap(node->left) && verify_heap(node->right);
}

// ==================== TESTES ====================

void testar_basico() {
    printf("=== TESTE BÁSICO TREAP ===\n\n");
    
    srand(42);
    Treap *t = treap_create();
    
    int valores[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(valores) / sizeof(valores[0]);
    
    printf("Inserindo: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", valores[i]);
        treap_insert_wrapper(t, valores[i]);
    }
    printf("\n\n");
    
    printf("Estrutura do Treap:\n");
    print_treap(t->root);
    printf("\n");
    
    printf("Travessia In-Order (ordenada): ");
    inorder(t->root);
    printf("\n\n");
    
    printf("Verificação:\n");
    printf("  Propriedade BST: %s\n", verify_bst(t->root, -1000000, 1000000) ? "OK" : "FALHA");
    printf("  Propriedade Heap: %s\n", verify_heap(t->root) ? "OK" : "FALHA");
    printf("\n");
    
    treap_free(t->root);
    free(t);
}

void testar_delecao() {
    printf("=== TESTE DE DELEÇÃO ===\n\n");
    
    srand(123);
    Treap *t = treap_create();
    
    for (int i = 1; i <= 7; i++) {
        treap_insert_wrapper(t, i * 10);
    }
    
    printf("Treap inicial: ");
    inorder(t->root);
    printf("\n\n");
    
    printf("Deletando 40...\n");
    treap_delete_wrapper(t, 40);
    printf("Resultado: ");
    inorder(t->root);
    printf("\n");
    
    printf("\nDeletando 10...\n");
    treap_delete_wrapper(t, 10);
    printf("Resultado: ");
    inorder(t->root);
    printf("\n");
    
    printf("\nDeletando 70...\n");
    treap_delete_wrapper(t, 70);
    printf("Resultado: ");
    inorder(t->root);
    printf("\n\n");
    
    treap_free(t->root);
    free(t);
}

void testar_rank() {
    printf("=== TESTE DE RANK/K-ÉSIMO ELEMENTO ===\n\n");
    
    srand(456);
    Treap *t = treap_create();
    
    int valores[] = {5, 2, 8, 1, 4, 6, 9, 3, 7};
    for (int i = 0; i < 9; i++) {
        treap_insert_wrapper(t, valores[i]);
    }
    
    printf("Elementos ordenados: ");
    inorder(t->root);
    printf("\n\n");
    
    printf("K-ésimo menor elemento:\n");
    for (int k = 1; k <= 9; k++) {
        printf("  %dº menor: %d\n", k, treap_kth_element(t->root, k));
    }
    printf("\n");
    
    printf("Contagem de elementos menores:\n");
    printf("  Menores que 5: %d\n", treap_count_less(t->root, 5));
    printf("  Menores que 7: %d\n", treap_count_less(t->root, 7));
    printf("  Menores que 10: %d\n", treap_count_less(t->root, 10));
    printf("\n");
    
    treap_free(t->root);
    free(t);
}

void testar_split_merge() {
    printf("=== TESTE DE SPLIT E MERGE ===\n\n");
    
    srand(789);
    TreapNode *root = NULL;
    
    for (int i = 1; i <= 9; i++) {
        root = treap_insert(root, i * 10);
    }
    
    printf("Treap original: ");
    inorder(root);
    printf("\n\n");
    
    // Split pela chave 50
    TreapNode *left, *right;
    treap_split(root, 50, &left, &right);
    
    printf("Após split(50):\n");
    printf("  Left (< 50): ");
    inorder(left);
    printf("\n");
    printf("  Right (>= 50): ");
    inorder(right);
    printf("\n\n");
    
    // Merge de volta
    TreapNode *merged = treap_merge(left, right);
    
    printf("Após merge: ");
    inorder(merged);
    printf("\n\n");
    
    treap_free(merged);
}

void comparar_balanceamento() {
    printf("=== COMPARAÇÃO DE BALANCEAMENTO ===\n\n");
    
    srand(time(NULL));
    
    // Inserir elementos em ordem (pior caso para BST normal)
    Treap *t = treap_create();
    
    int n = 1000;
    for (int i = 0; i < n; i++) {
        treap_insert_wrapper(t, i);
    }
    
    // Calcular altura
    int altura = 0;
    TreapNode *node = t->root;
    while (node) {
        altura++;
        // Ir para o filho com maior subárvore
        if (get_size(node->left) > get_size(node->right)) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    
    printf("Inserção de %d elementos em ordem:\n", n);
    printf("  BST normal: altura = %d (pior caso)\n", n);
    printf("  Treap: altura aproximada = %d\n", altura);
    printf("  Altura ótima: log2(%d) = %.0f\n", n, log2(n));
    printf("\n");
    
    treap_free(t->root);
    free(t);
}

// ==================== FUNÇÃO PRINCIPAL ====================

int main() {
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║                      TREAP                               ║\n");
    printf("║   Árvore Binária + Heap com balanceamento probabilístico ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    testar_basico();
    testar_delecao();
    testar_rank();
    testar_split_merge();
    comparar_balanceamento();
    
    printf("═══════════════════════════════════════════════════════════\n");
    printf("Propriedades do Treap:\n");
    printf("- Busca/Inserção/Remoção: O(log n) esperado\n");
    printf("- Split/Merge: O(log n) esperado\n");
    printf("- Mais simples que AVL/Red-Black\n");
    printf("- Altura esperada: 2.46 log n\n");
    printf("\n");
    printf("Próximo: Splay Tree (13) - auto-ajuste por acesso\n");
    printf("═══════════════════════════════════════════════════════════\n");
    
    return 0;
}
