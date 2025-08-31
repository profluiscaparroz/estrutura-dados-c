/*
 * ====================================================================
 * IMPLEMENTAÇÃO DE ÁRVORE BINÁRIA DE BUSCA (Binary Search Tree - BST)
 * ====================================================================
 * 
 * Descrição:
 * Uma Árvore Binária de Busca é uma estrutura de dados hierárquica onde
 * cada nó tem no máximo dois filhos (esquerdo e direito), e mantém a
 * propriedade de que todos os valores à esquerda são menores que o nó
 * atual, e todos os valores à direita são maiores.
 * 
 * Complexidade das operações:
 * - Inserção: O(log n) médio, O(n) pior caso
 * - Busca: O(log n) médio, O(n) pior caso  
 * - Remoção: O(log n) médio, O(n) pior caso
 * - Travessia: O(n)
 * 
 * Vantagens:
 * - Busca eficiente
 * - Inserção e remoção dinâmicas
 * - Travessia ordenada (in-order)
 * 
 * Desvantagens:
 * - Pode degenerar em lista ligada (pior caso)
 * - Não balanceada automaticamente
 * 
 * Autor: Estrutura de Dados em C
 * Data: 2024
 * ====================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Estrutura do nó da BST
 * @param data: valor inteiro armazenado no nó
 * @param left: ponteiro para o filho esquerdo
 * @param right: ponteiro para o filho direito
 */
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

/**
 * Cria um novo nó da BST
 * @param data: valor a ser armazenado no nó
 * @return: ponteiro para o novo nó criado
 */
Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Erro: Falha na alocação de memória\n");
        exit(1);
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

/**
 * Insere um novo valor na BST
 * @param root: raiz da árvore
 * @param data: valor a ser inserido
 * @return: ponteiro para a raiz atualizada
 */
Node* insert(Node* root, int data) {
    // Caso base: árvore vazia, criar novo nó
    if (root == NULL) {
        return create_node(data);
    }
    
    // Inserir à esquerda se menor que o nó atual
    if (data < root->data) {
        root->left = insert(root->left, data);
    } 
    // Inserir à direita se maior que o nó atual
    else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    // Se igual, não inserir (evita duplicatas)
    
    return root;
}

/**
 * Busca um valor na BST
 * @param root: raiz da árvore
 * @param data: valor a ser buscado
 * @return: ponteiro para o nó encontrado ou NULL se não encontrado
 */
Node* search(Node* root, int data) {
    // Caso base: árvore vazia ou valor encontrado
    if (root == NULL || root->data == data) {
        return root;
    }
    
    // Buscar à esquerda se menor que o nó atual
    if (data < root->data) {
        return search(root->left, data);
    }
    
    // Buscar à direita se maior que o nó atual
    return search(root->right, data);
}

/**
 * Encontra o nó com valor mínimo na árvore (mais à esquerda)
 * @param root: raiz da árvore ou subárvore
 * @return: ponteiro para o nó com valor mínimo
 */
Node* find_min(Node* root) {
    // Continua indo para a esquerda até encontrar o último nó
    while (root && root->left) {
        root = root->left;
    }
    return root;
}

/**
 * Remove um nó da BST
 * @param root: raiz da árvore
 * @param data: valor a ser removido
 * @return: ponteiro para a raiz atualizada
 */
Node* delete_node(Node* root, int data) {
    if (root == NULL) {
        return root;
    }
    
    // Navegar para encontrar o nó a ser removido
    if (data < root->data) {
        root->left = delete_node(root->left, data);
    } else if (data > root->data) {
        root->right = delete_node(root->right, data);
    } else {
        // Nó encontrado - três casos para remoção:
        
        // Caso 1: Nó sem filho esquerdo (0 ou 1 filho)
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } 
        // Caso 2: Nó sem filho direito (1 filho)
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        
        // Caso 3: Nó com dois filhos
        // Encontrar o sucessor in-order (menor valor da subárvore direita)
        Node* temp = find_min(root->right);
        
        // Copiar o valor do sucessor para este nó
        root->data = temp->data;
        
        // Remover o sucessor da subárvore direita
        root->right = delete_node(root->right, temp->data);
    }
    
    return root;
}

/**
 * Realiza travessia in-order da BST (esquerda, raiz, direita)
 * Resulta em ordem crescente dos valores
 * @param root: raiz da árvore ou subárvore
 */
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);       // Visitar subárvore esquerda
        printf("%d ", root->data); // Processar nó atual
        inorder(root->right);      // Visitar subárvore direita
    }
}

/**
 * Libera toda a memória alocada para a árvore (pós-ordem)
 * @param root: raiz da árvore a ser destruída
 */
void destroy_tree(Node* root) {
    if (root != NULL) {
        destroy_tree(root->left);  // Liberar subárvore esquerda
        destroy_tree(root->right); // Liberar subárvore direita
        free(root);                // Liberar nó atual
    }
}

/**
 * Função principal demonstrando o uso da BST
 * Testa inserção, busca, travessia e remoção
 */
int main() {
    printf("=== DEMONSTRAÇÃO DE ÁRVORE BINÁRIA DE BUSCA ===\n\n");
    
    Node* root = NULL;
    
    // Inserindo valores na BST
    printf("Inserindo valores: 50, 30, 20, 40, 70, 60, 80\n");
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);
    
    // Exibindo travessia in-order (valores em ordem crescente)
    printf("Traversal in-order (valores ordenados): ");
    inorder(root);
    printf("\n\n");
    
    // Testando busca
    printf("=== TESTE DE BUSCA ===\n");
    Node* found = search(root, 40);
    if (found) {
        printf("✓ Elemento %d encontrado na árvore\n", found->data);
    } else {
        printf("✗ Elemento não encontrado\n");
    }
    
    found = search(root, 100);
    if (found) {
        printf("✓ Elemento %d encontrado na árvore\n", found->data);
    } else {
        printf("✗ Elemento 100 não encontrado na árvore\n");
    }
    
    // Testando remoção
    printf("\n=== TESTE DE REMOÇÃO ===\n");
    printf("Removendo elemento 20...\n");
    root = delete_node(root, 20);
    printf("Árvore após remoção: ");
    inorder(root);
    printf("\n");
    
    printf("Removendo elemento 30 (nó com dois filhos)...\n");
    root = delete_node(root, 30);
    printf("Árvore após remoção: ");
    inorder(root);
    printf("\n");
    
    printf("Removendo elemento 50 (raiz)...\n");
    root = delete_node(root, 50);
    printf("Árvore após remoção: ");
    inorder(root);
    printf("\n");
    
    // Limpando memória
    destroy_tree(root);
    printf("\n✓ Memória liberada com sucesso!\n");
    
    return 0;
}