"""Set Cover - Greedy O(log n)-aproximação"""

def greedy_set_cover(universe, sets):
    covered = set()
    cover = []
    
    while covered != universe:
        best_set = max(sets, key=lambda s: len(s - covered))
        cover.append(best_set)
        covered |= best_set
    
    return cover

# Exemplo
universe = set(range(1, 11))
sets = [
    {1, 2, 5},
    {2, 3, 4},
    {4, 5, 6},
    {6, 7, 8},
    {8, 9, 10}
]

cover = greedy_set_cover(universe, sets)
print(f"SET COVER - Greedy")
print(f"Cobertura: {len(cover)} conjuntos")
for i, s in enumerate(cover, 1):
    print(f"  Conjunto {i}: {s}")
