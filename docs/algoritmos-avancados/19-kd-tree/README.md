# Aula de Ciência da Computação: KD-Tree (K-Dimensional Tree) – História, Funcionamento e Aplicações

## Introdução

A **KD-Tree** (K-Dimensional Tree) é uma estrutura de dados espacial que organiza pontos em um espaço k-dimensional, permitindo buscas eficientes por vizinhança, range queries e nearest neighbor searches. Foi inventada por Jon Louis Bentley em 1975 e é amplamente utilizada em geometria computacional, visão computacional, machine learning e sistemas de informação geográfica.

---

## 1. História e Motivação

A KD-Tree foi introduzida por Jon Louis Bentley no artigo **"Multidimensional Binary Search Trees Used for Associative Searching"**, publicado na Communications of the ACM em 1975. Bentley buscava uma estrutura eficiente para buscas em espaços multidimensionais, problema comum em banco de dados espaciais e computação gráfica.

Antes da KD-Tree:

* **Busca Linear**: Para encontrar pontos próximos, verificar todos os pontos – O(n) por consulta.
* **Grid-Based Structures**: Dividir espaço em células fixas – ineficiente para distribuições não uniformes.
* **Quadtrees/Octrees**: Boas para 2D/3D, mas não generalizam bem para dimensões arbitrárias.

A KD-Tree generalizou árvores binárias para espaços multidimensionais, alternando dimensões em cada nível da árvore.

---

## 2. Como funciona a KD-Tree?

Uma KD-Tree é uma árvore binária onde:

* Cada nó representa um ponto em k dimensões
* Em cada nível, escolhe-se uma dimensão para dividir o espaço
* Pontos à esquerda têm valor menor naquela dimensão, à direita têm valor maior

### Construção

Para k=2 (plano 2D):
1. Nível 0: dividir por coordenada x
2. Nível 1: dividir por coordenada y
3. Nível 2: dividir por coordenada x novamente
4. E assim por diante, alternando dimensões

### Busca por Nearest Neighbor

1. Descer na árvore como em BST normal
2. Ao chegar em folha, calcular distância
3. Backtrack, verificando se outros ramos podem ter vizinhos mais próximos
4. Usar distância mínima encontrada para podar busca

Complexidade: O(log n) em média, O(n) no pior caso.

---

## 3. Vantagens da KD-Tree

* **Eficiência Espacial**: Busca em espaços multidimensionais em O(log n) médio.
* **Nearest Neighbor**: Encontra vizinho mais próximo rapidamente.
* **Range Queries**: Busca pontos em regiões retangulares.
* **Generalização**: Funciona para qualquer número de dimensões.
* **Construção Simples**: Similar a BST, fácil de implementar.

---

## 4. Desvantagens da KD-Tree

* **Curse of Dimensionality**: Performance degrada em alta dimensionalidade (>20D).
* **Desbalanceamento**: Pode ficar desbalanceada sem construção cuidadosa.
* **Atualizações Caras**: Inserção e remoção dinâmicas são complexas.
* **Não Adaptativa**: Não se adapta bem a distribuições de dados irregulares.

---

## 5. Aplicações Práticas

* **Visão Computacional**: Detecção de pontos-chave, correspondência de features.
* **Machine Learning**: k-NN (k-Nearest Neighbors), clustering.
* **Computação Gráfica**: Ray tracing, detecção de colisão.
* **Robótica**: Planejamento de trajetória, SLAM.
* **GIS**: Consultas espaciais, busca de localização.

---

## Onde a KD-Tree é usada no dia a dia?

1. **Sistemas de Recomendação**: Encontrar usuários/produtos similares em espaço de features.
2. **Processamento de Imagens**: Face recognition, object detection.
3. **Jogos**: Pathfinding, detecção de proximidade.
4. **Mapas e Navegação**: Busca de pontos de interesse próximos.
5. **Astronomia**: Busca de estrelas e galáxias próximas em catálogos.

---

# Implementação da KD-Tree em Python

```python
import math

class Node:
    def __init__(self, point, left=None, right=None):
        self.point = point
        self.left = left
        self.right = right

class KDTree:
    def __init__(self, k=2):
        self.k = k
        self.root = None
    
    def build(self, points, depth=0):
        if not points:
            return None
        
        axis = depth % self.k
        points.sort(key=lambda x: x[axis])
        median = len(points) // 2
        
        return Node(
            point=points[median],
            left=self.build(points[:median], depth + 1),
            right=self.build(points[median + 1:], depth + 1)
        )
    
    def nearest_neighbor(self, point):
        return self._nearest(self.root, point, 0)[0]
    
    def _nearest(self, node, point, depth):
        if node is None:
            return None, float('inf')
        
        axis = depth % self.k
        
        if point[axis] < node.point[axis]:
            near_node = node.left
            far_node = node.right
        else:
            near_node = node.right
            far_node = node.left
        
        best, best_dist = self._nearest(near_node, point, depth + 1)
        
        current_dist = self._distance(point, node.point)
        if current_dist < best_dist:
            best, best_dist = node.point, current_dist
        
        if abs(point[axis] - node.point[axis]) < best_dist:
            far_best, far_dist = self._nearest(far_node, point, depth + 1)
            if far_dist < best_dist:
                best, best_dist = far_best, far_dist
        
        return best, best_dist
    
    def _distance(self, p1, p2):
        return math.sqrt(sum((a - b) ** 2 for a, b in zip(p1, p2)))

# Exemplo de uso
if __name__ == "__main__":
    points = [(2, 3), (5, 4), (9, 6), (4, 7), (8, 1), (7, 2)]
    
    kdtree = KDTree(k=2)
    kdtree.root = kdtree.build(points)
    
    query = (6, 5)
    nearest = kdtree.nearest_neighbor(query)
    print(f"Ponto de consulta: {query}")
    print(f"Vizinho mais próximo: {nearest}")
```

---

# Implementação da KD-Tree em C

```c
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
    
    Node *root = buildKDTree(points, n, 0);
    
    Point query = {{6, 5}};
    Point nearest = nearestNeighbor(root, query);
    
    printf("Ponto de consulta: (%.1f, %.1f)\n", query.coords[0], query.coords[1]);
    printf("Vizinho mais próximo: (%.1f, %.1f)\n", nearest.coords[0], nearest.coords[1]);
    
    freeKDTree(root);
    return 0;
}
```

---

## 7. Conclusão

A KD-Tree representa um avanço fundamental em estruturas de dados espaciais. Desde sua introdução por Bentley em 1975, tornou-se essencial para aplicações que envolvem busca em espaços multidimensionais.

Como Bentley afirmou (1975), "árvores multidimensionais de busca binária fornecem uma estrutura natural e eficiente para buscas associativas em espaços de múltiplas dimensões".

---

## Referências

* Bentley, J. L. (1975). **Multidimensional Binary Search Trees Used for Associative Searching**. *Communications of the ACM*, 18(9), 509-517.

* Friedman, J. H., Bentley, J. L., & Finkel, R. A. (1977). **An Algorithm for Finding Best Matches in Logarithmic Expected Time**. *ACM Transactions on Mathematical Software*, 3(3), 209-226.

* Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009). *Introduction to Algorithms* (3rd ed.). MIT Press.
