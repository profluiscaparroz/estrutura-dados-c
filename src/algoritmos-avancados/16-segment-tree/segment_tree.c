#include <stdio.h>
#include <stdlib.h>

// Estrutura da Segment Tree
typedef struct {
    int *tree;
    int *arr;
    int n;
} SegmentTree;

// Função para criar uma Segment Tree
SegmentTree* createSegmentTree(int arr[], int n) {
    SegmentTree *st = (SegmentTree *)malloc(sizeof(SegmentTree));
    st->n = n;
    st->arr = arr;
    st->tree = (int *)malloc(sizeof(int) * (4 * n));
    return st;
}

// Função auxiliar para construir a árvore
void buildHelper(SegmentTree *st, int node, int start, int end) {
    if (start == end) {
        st->tree[node] = st->arr[start];
    } else {
        int mid = (start + end) / 2;
        int left_child = 2 * node + 1;
        int right_child = 2 * node + 2;
        
        buildHelper(st, left_child, start, mid);
        buildHelper(st, right_child, mid + 1, end);
        
        st->tree[node] = st->tree[left_child] + st->tree[right_child];
    }
}

// Função para construir a Segment Tree
void build(SegmentTree *st) {
    buildHelper(st, 0, 0, st->n - 1);
}

// Função auxiliar para consulta de intervalo
int queryHelper(SegmentTree *st, int node, int start, int end, int L, int R) {
    // Sem sobreposição
    if (R < start || L > end) {
        return 0;
    }
    
    // Sobreposição total
    if (L <= start && end <= R) {
        return st->tree[node];
    }
    
    // Sobreposição parcial
    int mid = (start + end) / 2;
    int left_child = 2 * node + 1;
    int right_child = 2 * node + 2;
    
    int left_sum = queryHelper(st, left_child, start, mid, L, R);
    int right_sum = queryHelper(st, right_child, mid + 1, end, L, R);
    
    return left_sum + right_sum;
}

// Função para consultar soma de intervalo
int rangeQuery(SegmentTree *st, int L, int R) {
    return queryHelper(st, 0, 0, st->n - 1, L, R);
}

// Função auxiliar para atualização de ponto
void updateHelper(SegmentTree *st, int node, int start, int end, int idx, int val) {
    if (start == end) {
        st->arr[idx] = val;
        st->tree[node] = val;
    } else {
        int mid = (start + end) / 2;
        int left_child = 2 * node + 1;
        int right_child = 2 * node + 2;
        
        if (idx <= mid) {
            updateHelper(st, left_child, start, mid, idx, val);
        } else {
            updateHelper(st, right_child, mid + 1, end, idx, val);
        }
        
        st->tree[node] = st->tree[left_child] + st->tree[right_child];
    }
}

// Função para atualizar um elemento
void pointUpdate(SegmentTree *st, int idx, int val) {
    updateHelper(st, 0, 0, st->n - 1, idx, val);
}

// Função para exibir o array
void displayArray(int arr[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
}

// Função para liberar memória
void freeSegmentTree(SegmentTree *st) {
    free(st->tree);
    free(st);
}

// Exemplo de uso
int main() {
    int arr[] = {1, 3, 5, 7, 9, 11};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    SegmentTree *st = createSegmentTree(arr, n);
    build(st);
    
    printf("Array inicial: ");
    displayArray(arr, n);
    
    printf("\n=== Consultas de Intervalo ===\n");
    printf("Soma [1, 3]: %d\n", rangeQuery(st, 1, 3));  // 3 + 5 + 7 = 15
    printf("Soma [0, 5]: %d\n", rangeQuery(st, 0, 5));  // Soma total = 36
    printf("Soma [2, 4]: %d\n", rangeQuery(st, 2, 4));  // 5 + 7 + 9 = 21
    
    printf("\n=== Atualização ===\n");
    printf("Atualizando índice 2 para 10\n");
    pointUpdate(st, 2, 10);
    
    printf("Array atualizado: ");
    displayArray(arr, n);
    
    printf("\n=== Consultas Após Atualização ===\n");
    printf("Soma [1, 3]: %d\n", rangeQuery(st, 1, 3));  // 3 + 10 + 7 = 20
    printf("Soma [0, 5]: %d\n", rangeQuery(st, 0, 5));  // Soma total = 41
    printf("Soma [2, 4]: %d\n", rangeQuery(st, 2, 4));  // 10 + 7 + 9 = 26
    
    freeSegmentTree(st);
    
    return 0;
}
