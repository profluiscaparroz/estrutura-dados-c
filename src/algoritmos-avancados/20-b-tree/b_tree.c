#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define T 3  // Grau mínimo da B-Tree (ordem = 2*T - 1 = 5)

typedef struct BTreeNode {
    int keys[2 * T - 1];
    struct BTreeNode *children[2 * T];
    int n;  // Número atual de chaves
    bool leaf;
} BTreeNode;

typedef struct BTree {
    BTreeNode *root;
} BTree;

BTreeNode* createNode(bool leaf) {
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    node->n = 0;
    node->leaf = leaf;
    for (int i = 0; i < 2 * T; i++) {
        node->children[i] = NULL;
    }
    return node;
}

BTree* createBTree() {
    BTree *tree = (BTree *)malloc(sizeof(BTree));
    tree->root = createNode(true);
    return tree;
}

bool search(BTreeNode *node, int k) {
    int i = 0;
    while (i < node->n && k > node->keys[i]) {
        i++;
    }
    
    if (i < node->n && k == node->keys[i]) {
        return true;
    }
    
    if (node->leaf) {
        return false;
    }
    
    return search(node->children[i], k);
}

void splitChild(BTreeNode *parent, int i) {
    BTreeNode *fullChild = parent->children[i];
    BTreeNode *newChild = createNode(fullChild->leaf);
    
    newChild->n = T - 1;
    
    for (int j = 0; j < T - 1; j++) {
        newChild->keys[j] = fullChild->keys[j + T];
    }
    
    if (!fullChild->leaf) {
        for (int j = 0; j < T; j++) {
            newChild->children[j] = fullChild->children[j + T];
        }
    }
    
    fullChild->n = T - 1;
    
    for (int j = parent->n; j > i; j--) {
        parent->children[j + 1] = parent->children[j];
    }
    parent->children[i + 1] = newChild;
    
    for (int j = parent->n - 1; j >= i; j--) {
        parent->keys[j + 1] = parent->keys[j];
    }
    parent->keys[i] = fullChild->keys[T - 1];
    parent->n++;
}

void insertNonFull(BTreeNode *node, int k) {
    int i = node->n - 1;
    
    if (node->leaf) {
        while (i >= 0 && k < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = k;
        node->n++;
    } else {
        while (i >= 0 && k < node->keys[i]) {
            i--;
        }
        i++;
        
        if (node->children[i]->n == 2 * T - 1) {
            splitChild(node, i);
            if (k > node->keys[i]) {
                i++;
            }
        }
        insertNonFull(node->children[i], k);
    }
}

void insert(BTree *tree, int k) {
    BTreeNode *root = tree->root;
    
    if (root->n == 2 * T - 1) {
        BTreeNode *newRoot = createNode(false);
        newRoot->children[0] = root;
        tree->root = newRoot;
        splitChild(newRoot, 0);
        insertNonFull(newRoot, k);
    } else {
        insertNonFull(root, k);
    }
}

void traverse(BTreeNode *node) {
    int i;
    for (i = 0; i < node->n; i++) {
        if (!node->leaf) {
            traverse(node->children[i]);
        }
        printf("%d ", node->keys[i]);
    }
    if (!node->leaf) {
        traverse(node->children[i]);
    }
}

void freeNode(BTreeNode *node) {
    if (node == NULL) return;
    if (!node->leaf) {
        for (int i = 0; i <= node->n; i++) {
            freeNode(node->children[i]);
        }
    }
    free(node);
}

void freeBTree(BTree *tree) {
    freeNode(tree->root);
    free(tree);
}

int main() {
    BTree *tree = createBTree();
    
    int keys[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int n = sizeof(keys) / sizeof(keys[0]);
    
    printf("=== B-Tree de ordem %d ===\n\n", 2 * T - 1);
    
    printf("Inserindo chaves:\n");
    for (int i = 0; i < n; i++) {
        insert(tree, keys[i]);
        printf("  Inserido: %d\n", keys[i]);
    }
    
    printf("\nPercurso in-order: ");
    traverse(tree->root);
    printf("\n");
    
    printf("\n=== Buscas ===\n");
    printf("Buscar 6: %s\n", search(tree->root, 6) ? "Encontrado" : "Não encontrado");
    printf("Buscar 15: %s\n", search(tree->root, 15) ? "Encontrado" : "Não encontrado");
    printf("Buscar 30: %s\n", search(tree->root, 30) ? "Encontrado" : "Não encontrado");
    
    freeBTree(tree);
    
    return 0;
}
