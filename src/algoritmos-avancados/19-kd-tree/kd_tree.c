#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define K 2  // Dimensões (2D neste exemplo)

typedef struct Point {
    double coords[K];
} Point;

typedef struct Node {
    Point point;
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode(Point point) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->point = point;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int comparePoints(const void *a, const void *b, int axis) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    if (p1->coords[axis] < p2->coords[axis]) return -1;
    if (p1->coords[axis] > p2->coords[axis]) return 1;
    return 0;
}

int compareX(const void *a, const void *b) {
    return comparePoints(a, b, 0);
}

int compareY(const void *a, const void *b) {
    return comparePoints(a, b, 1);
}

Node* buildKDTree(Point points[], int n, int depth) {
    if (n <= 0) return NULL;
    
    int axis = depth % K;
    
    if (axis == 0) {
        qsort(points, n, sizeof(Point), compareX);
    } else {
        qsort(points, n, sizeof(Point), compareY);
    }
    
    int median = n / 2;
    Node *node = createNode(points[median]);
    
    node->left = buildKDTree(points, median, depth + 1);
    node->right = buildKDTree(points + median + 1, n - median - 1, depth + 1);
    
    return node;
}

double distance(Point a, Point b) {
    double sum = 0;
    for (int i = 0; i < K; i++) {
        double diff = a.coords[i] - b.coords[i];
        sum += diff * diff;
    }
    return sqrt(sum);
}

void nearestNeighborHelper(Node *node, Point target, int depth, 
                           Point *best, double *bestDist) {
    if (node == NULL) return;
    
    double d = distance(node->point, target);
    if (d < *bestDist) {
        *bestDist = d;
        *best = node->point;
    }
    
    int axis = depth % K;
    double diff = target.coords[axis] - node->point.coords[axis];
    
    Node *near = (diff < 0) ? node->left : node->right;
    Node *far = (diff < 0) ? node->right : node->left;
    
    nearestNeighborHelper(near, target, depth + 1, best, bestDist);
    
    if (fabs(diff) < *bestDist) {
        nearestNeighborHelper(far, target, depth + 1, best, bestDist);
    }
}

Point nearestNeighbor(Node *root, Point target) {
    Point best = root->point;
    double bestDist = DBL_MAX;
    nearestNeighborHelper(root, target, 0, &best, &bestDist);
    return best;
}

void freeKDTree(Node *node) {
    if (node == NULL) return;
    freeKDTree(node->left);
    freeKDTree(node->right);
    free(node);
}

int main() {
    Point points[] = {
        {{2, 3}}, {{5, 4}}, {{9, 6}},
        {{4, 7}}, {{8, 1}}, {{7, 2}}
    };
    int n = sizeof(points) / sizeof(points[0]);
    
    printf("=== KD-Tree 2D ===\n\n");
    printf("Construindo KD-Tree com %d pontos:\n", n);
    for (int i = 0; i < n; i++) {
        printf("  (%.1f, %.1f)\n", points[i].coords[0], points[i].coords[1]);
    }
    
    Node *root = buildKDTree(points, n, 0);
    
    Point query = {{6, 5}};
    Point nearest = nearestNeighbor(root, query);
    
    printf("\nPonto de consulta: (%.1f, %.1f)\n", query.coords[0], query.coords[1]);
    printf("Vizinho mais próximo: (%.1f, %.1f)\n", nearest.coords[0], nearest.coords[1]);
    printf("Distância: %.2f\n", distance(query, nearest));
    
    freeKDTree(root);
    return 0;
}
