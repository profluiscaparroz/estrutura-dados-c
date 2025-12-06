"""Knapsack Greedy"""

def knapsack_greedy(items, capacity):
    # items = [(value, weight), ...]
    items_sorted = sorted(items, key=lambda x: x[0]/x[1], reverse=True)
    
    total_value = 0
    total_weight = 0
    selected = []
    
    for value, weight in items_sorted:
        if total_weight + weight <= capacity:
            selected.append((value, weight))
            total_value += value
            total_weight += weight
    
    return selected, total_value

items = [(60, 10), (100, 20), (120, 30)]
capacity = 50

selected, value = knapsack_greedy(items, capacity)
print("KNAPSACK GREEDY")
print(f"Itens selecionados: {selected}")
print(f"Valor total: {value}")
print(f"Capacidade: {capacity}")
