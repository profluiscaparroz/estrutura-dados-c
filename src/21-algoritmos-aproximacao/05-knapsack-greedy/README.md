# Knapsack Greedy - Mochila Gulosa

## 📚 Definição

**0/1 Knapsack**: Dados itens com valores e pesos, maximizar valor total respeitando capacidade da mochila.

**Entrada**: n itens (vᵢ, wᵢ), capacidade W  
**Saída**: Subconjunto S que maximiza Σvᵢ tal que Σwᵢ ≤ W

## 🎯 Complexidade

- **Classe**: NP-Difícil
- **Pseudo-polinomial**: DP em O(nW)
- **FPTAS**: (1+ε)-aproximação em O(n³/ε)

## 💡 Algoritmos

### 1. Greedy por Razão Valor/Peso

```
KNAPSACK-GREEDY(items, W):
    Ordena items por vᵢ/wᵢ decrescente
    S = ∅, peso = 0
    
    for item in items:
        if peso + wᵢ ≤ W:
            S = S ∪ {item}
            peso += wᵢ
    
    return S
```

**Fator**: Sem garantia! (Pode ser arbitrariamente ruim)

### 2. Greedy Melhorado

```
KNAPSACK-GREEDY-2(items, W):
    S1 = KNAPSACK-GREEDY(items, W)
    S2 = item de maior valor que cabe
    return max(value(S1), value(S2))
```

**Fator**: 2-aproximação

### 3. FPTAS (Arredondamento + DP)

Arredonda valores → DP rápido → (1+ε)-aproximação

## 💻 Aplicações

1. **Alocação de Recursos**: Orçamento limitado
2. **Portfolio**: Investimentos
3. **Corte de Material**: Maximizar aproveitamento
