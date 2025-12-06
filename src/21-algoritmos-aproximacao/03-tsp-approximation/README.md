# TSP Approximation - Caixeiro Viajante Aproximado

## 📚 Definição

**TSP (Traveling Salesman Problem)**: Encontrar o menor ciclo que visita todas as cidades exatamente uma vez.

**Entrada**: Grafo completo G=(V,E) com pesos d(u,v) nas arestas  
**Saída**: Ciclo hamiltoniano de peso mínimo

## 🎯 Complexidade

- **Classe**: NP-Difícil
- **TSP Geral**: Não aproximável (a menos que P=NP)
- **TSP Métrico**: Admite aproximação (desigualdade triangular)

## 💡 Algoritmos

### 1. MST-based 2-Aproximação

```
TSP-MST(G):
    1. Encontrar MST de G
    2. Fazer DFS na MST
    3. Retornar ordem de visita
```
**Fator**: 2× OPT

### 2. Christofides 1.5-Aproximação

```
CHRISTOFIDES(G):
    1. Encontrar MST de G
    2. Encontrar vértices ímpares em MST
    3. Encontrar matching perfeito mínimo nos vértices ímpares
    4. Combinar MST + matching
    5. Encontrar ciclo Euleriano
    6. Converter em Hamiltoniano via atalhos
```
**Fator**: 1.5× OPT (melhor conhecido)

## 💻 Aplicações

1. **Logística**: Roteamento de entregas
2. **Manufatura**: Sequenciamento de produção  
3. **Biologia**: Sequenciamento de DNA
4. **Redes**: Roteamento de pacotes
