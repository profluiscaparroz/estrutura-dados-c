"""
Bin Packing - Heurísticas de Aproximação
Next Fit, First Fit, First Fit Decreasing
"""

def next_fit(items, capacity=1.0):
    """Next Fit: O(n), fator 2"""
    bins = [[]]
    for item in items:
        if sum(bins[-1]) + item <= capacity:
            bins[-1].append(item)
        else:
            bins.append([item])
    return bins

def first_fit(items, capacity=1.0):
    """First Fit: O(n²), fator 1.7"""
    bins = []
    for item in items:
        placed = False
        for bin in bins:
            if sum(bin) + item <= capacity:
                bin.append(item)
                placed = True
                break
        if not placed:
            bins.append([item])
    return bins

def first_fit_decreasing(items, capacity=1.0):
    """FFD: O(n log n), fator 1.222"""
    sorted_items = sorted(items, reverse=True)
    return first_fit(sorted_items, capacity)

def main():
    print("╔═══════════════════════════════════════╗")
    print("║  BIN PACKING - Heurísticas (Python)   ║")
    print("╚═══════════════════════════════════════╝\n")
    
    items = [0.7, 0.5, 0.3, 0.4, 0.2, 0.6, 0.1, 0.8]
    capacity = 1.0
    
    print(f"Itens: {items}")
    print(f"Capacidade: {capacity}\n")
    
    nf = next_fit(items, capacity)
    print(f"=== Next Fit: {len(nf)} bins ===")
    for i, bin in enumerate(nf, 1):
        print(f"Bin {i}: {bin} = {sum(bin):.2f}")
    
    ff = first_fit(items, capacity)
    print(f"\n=== First Fit: {len(ff)} bins ===")
    for i, bin in enumerate(ff, 1):
        print(f"Bin {i}: {bin} = {sum(bin):.2f}")
    
    ffd = first_fit_decreasing(items, capacity)
    print(f"\n=== First Fit Decreasing: {len(ffd)} bins ===")
    for i, bin in enumerate(ffd, 1):
        print(f"Bin {i}: {bin} = {sum(bin):.2f}")
    
    print(f"\nResumo:")
    print(f"NF: {len(nf)} bins (fator 2)")
    print(f"FF: {len(ff)} bins (fator 1.7)")
    print(f"FFD: {len(ffd)} bins (fator 1.222)")

if __name__ == "__main__":
    main()
