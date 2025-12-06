# Set Cover - Cobertura de Conjuntos

## 📚 Definição

**Set Cover**: Dado um universo U e uma coleção de subconjuntos S₁, S₂, ..., Sₙ de U, encontrar o menor número de subconjuntos cuja união cobre todo U.

**Entrada**: Universo U = {1, 2, ..., m}, conjuntos S₁, ..., Sₙ ⊆ U  
**Saída**: Coleção mínima C ⊆ {S₁, ..., Sₙ} tal que ⋃(S∈C) S = U

## 🎯 Complexidade

- **Classe**: NP-Completo
- **Redução**: De Vertex Cover
- **Fator de Aproximação**: O(log n) via algoritmo guloso

## 💡 Algoritmo Greedy

```
GREEDY-SET-COVER(U, S):
    C = ∅
    U' = U
    
    while U' ≠ ∅:
        Escolha conjunto S ∈ S que maximiza |S ∩ U'|
        C = C ∪ {S}
        U' = U' \ S
    
    return C
```

**Garantia**: |C| ≤ ln(|U|) × OPT

## 💻 Aplicações

1. **Localização de Facilidades**: Minimizar centros de distribuição
2. **Seleção de Features**: Machine learning, minimizar atributos
3. **Cobertura de Rede**: Posicionar antenas/roteadores
4. **Scheduling**: Minimizar turnos de trabalho
