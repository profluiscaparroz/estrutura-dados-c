"""TSP MST 2-Aproximação"""
import heapq

def prim_mst(dist):
    n = len(dist)
    visited = [False] * n
    parent = [-1] * n
    key = [float('inf')] * n
    key[0] = 0
    
    for _ in range(n):
        u = min((k, i) for i, k in enumerate(key) if not visited[i])[1]
        visited[u] = True
        
        for v in range(n):
            if not visited[v] and dist[u][v] < key[v]:
                key[v] = dist[u][v]
                parent[v] = u
    
    return parent

def dfs_tour(u, adj, visited, tour):
    visited[u] = True
    tour.append(u)
    
    for v in adj.get(u, []):
        if not visited[v]:
            dfs_tour(v, adj, visited, tour)

def tsp_mst_approx(dist):
    n = len(dist)
    parent = prim_mst(dist)
    
    # Construir adjacências da MST
    adj = {}
    for v in range(1, n):
        u = parent[v]
        adj.setdefault(u, []).append(v)
    
    # DFS para tour
    visited = [False] * n
    tour = []
    dfs_tour(0, adj, visited, tour)
    tour.append(0)
    
    # Calcular custo
    cost = sum(dist[tour[i]][tour[i+1]] for i in range(len(tour)-1))
    
    return tour, cost

# Exemplo
dist = [
    [0, 10, 15, 20],
    [10, 0, 35, 25],
    [15, 35, 0, 30],
    [20, 25, 30, 0]
]

tour, cost = tsp_mst_approx(dist)
print("TSP MST 2-Aproximação")
print(f"Tour: {tour}")
print(f"Custo: {cost}")
print("Garantia: ≤ 2× OPT")
