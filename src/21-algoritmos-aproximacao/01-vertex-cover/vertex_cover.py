"""
Vertex Cover - Algoritmo de Aproximação 2-Aproximação
via Maximal Matching

Problema: Encontrar conjunto mínimo de vértices que cobre todas as arestas
Algoritmo: Incluir ambos endpoints de cada aresta em um matching maximal
Fator de Aproximação: 2 (garantido)
Complexidade: O(V + E) tempo, O(V) espaço

Autor: Implementação educacional
Data: 2024
"""

from typing import List, Set, Tuple
import random


class Grafo:
    """Classe para representar um grafo não-direcionado"""
    
    def __init__(self, n_vertices: int):
        """
        Inicializa um grafo com n vértices
        
        Args:
            n_vertices: Número de vértices no grafo
        """
        self.n_vertices = n_vertices
        self.arestas = set()  # Conjunto de arestas (u, v) onde u < v
        
    def adicionar_aresta(self, u: int, v: int):
        """Adiciona uma aresta não-direcionada entre u e v"""
        if u > v:
            u, v = v, u  # Garante u < v
        self.arestas.add((u, v))
    
    def remover_aresta(self, u: int, v: int):
        """Remove uma aresta entre u e v"""
        if u > v:
            u, v = v, u
        self.arestas.discard((u, v))
    
    def remover_arestas_incidentes(self, v: int):
        """Remove todas as arestas incidentes ao vértice v"""
        arestas_remover = {(u, w) for (u, w) in self.arestas 
                          if u == v or w == v}
        self.arestas -= arestas_remover
    
    def tem_arestas(self) -> bool:
        """Verifica se ainda existem arestas no grafo"""
        return len(self.arestas) > 0
    
    def obter_aresta(self) -> Tuple[int, int]:
        """Retorna uma aresta arbitrária do grafo"""
        if self.arestas:
            return next(iter(self.arestas))
        return None
    
    def __str__(self) -> str:
        """Representação em string do grafo"""
        return f"Grafo({self.n_vertices} vértices, {len(self.arestas)} arestas)"


def vertex_cover_2approx(grafo: Grafo, verbose: bool = True) -> Set[int]:
    """
    Algoritmo de 2-Aproximação para Vertex Cover via Maximal Matching
    
    Algoritmo:
    1. C = conjunto vazio (vertex cover)
    2. Enquanto houver arestas:
       a) Escolhe aresta (u,v) arbitrária
       b) Adiciona u e v a C
       c) Remove todas arestas incidentes a u ou v
    3. Retorna C
    
    Garantia: |C| ≤ 2 × OPT
    
    Args:
        grafo: Grafo de entrada
        verbose: Se True, imprime passos do algoritmo
    
    Returns:
        Conjunto de vértices no vertex cover
    """
    # Cria cópia do grafo para não modificar o original
    import copy
    g_temp = copy.deepcopy(grafo)
    
    cover = set()
    
    if verbose:
        print("\n=== Executando Algoritmo de 2-Aproximação ===")
    
    iteracao = 1
    while g_temp.tem_arestas():
        # Escolhe uma aresta arbitrária
        u, v = g_temp.obter_aresta()
        
        if verbose:
            print(f"\nIteração {iteracao}:")
            print(f"  Aresta escolhida: ({u}, {v})")
        
        # Adiciona ambos endpoints ao cover
        cover.add(u)
        cover.add(v)
        
        if verbose:
            print(f"  Vértices adicionados ao cover: {u}, {v}")
            print(f"  Tamanho atual do cover: {len(cover)}")
        
        # Remove todas arestas incidentes a u ou v
        g_temp.remover_arestas_incidentes(u)
        g_temp.remover_arestas_incidentes(v)
        
        iteracao += 1
    
    if verbose:
        print("\n=== Algoritmo Concluído ===")
        print(f"Tamanho final do vertex cover: {len(cover)}")
    
    return cover


def verificar_cover(grafo: Grafo, cover: Set[int]) -> bool:
    """
    Verifica se um conjunto de vértices é um vertex cover válido
    
    Args:
        grafo: Grafo original
        cover: Conjunto de vértices proposto como cover
    
    Returns:
        True se o cover é válido, False caso contrário
    """
    for u, v in grafo.arestas:
        if u not in cover and v not in cover:
            print(f"Erro: Aresta ({u}, {v}) não está coberta!")
            return False
    return True


def vertex_cover_greedy_grau(grafo: Grafo, verbose: bool = False) -> Set[int]:
    """
    Algoritmo Guloso para Vertex Cover baseado em grau
    
    Sempre escolhe o vértice de maior grau para adicionar ao cover.
    
    NOTA: Este algoritmo NÃO tem fator de aproximação constante!
    Pode dar O(log n)-aproximação no pior caso.
    Mas na prática frequentemente dá soluções boas.
    
    Args:
        grafo: Grafo de entrada
        verbose: Se True, imprime passos
    
    Returns:
        Conjunto de vértices no vertex cover
    """
    import copy
    g_temp = copy.deepcopy(grafo)
    
    cover = set()
    
    if verbose:
        print("\n=== Algoritmo Guloso por Grau ===")
    
    while g_temp.tem_arestas():
        # Calcula grau de cada vértice
        graus = {v: 0 for v in range(grafo.n_vertices)}
        for u, v in g_temp.arestas:
            graus[u] += 1
            graus[v] += 1
        
        # Escolhe vértice de maior grau
        v_max = max(graus, key=graus.get)
        
        if graus[v_max] == 0:
            break
        
        if verbose:
            print(f"Escolhendo vértice {v_max} com grau {graus[v_max]}")
        
        cover.add(v_max)
        g_temp.remover_arestas_incidentes(v_max)
    
    if verbose:
        print(f"Tamanho final: {len(cover)}")
    
    return cover


def exemplo1_path_graph():
    """
    Exemplo 1: Grafo em Linha (Path Graph)
    
         0 --- 1 --- 2 --- 3
    
    Vertex Cover ótimo: {1, 2} (tamanho 2)
    """
    print("\n" + "="*60)
    print("EXEMPLO 1: Grafo em Linha (Path Graph)")
    print("="*60)
    
    g = Grafo(4)
    g.adicionar_aresta(0, 1)
    g.adicionar_aresta(1, 2)
    g.adicionar_aresta(2, 3)
    
    print(f"\n{g}")
    print(f"Arestas: {sorted(g.arestas)}")
    
    # 2-Aproximação
    cover_aprox = vertex_cover_2approx(g, verbose=True)
    print(f"\nVertex Cover (2-aprox): {sorted(cover_aprox)}")
    print(f"Válido: {verificar_cover(g, cover_aprox)}")
    
    # Greedy
    cover_greedy = vertex_cover_greedy_grau(g, verbose=False)
    print(f"\nVertex Cover (greedy): {sorted(cover_greedy)}")
    print(f"Válido: {verificar_cover(g, cover_greedy)}")
    
    print(f"\nAnálise:")
    print(f"- Tamanho 2-aprox: {len(cover_aprox)}")
    print(f"- Tamanho greedy: {len(cover_greedy)}")
    print(f"- Vertex cover ótimo: 2 vértices")
    print(f"- Fator 2-aprox: {len(cover_aprox) / 2:.2f}")
    print(f"- Fator greedy: {len(cover_greedy) / 2:.2f}")


def exemplo2_complete_graph():
    """
    Exemplo 2: Grafo Completo K4
    
         0 --- 1
         |\ /|
         | X |
         |/ \|
         3 --- 2
    
    Vertex Cover ótimo: qualquer 3 vértices (tamanho 3)
    """
    print("\n" + "="*60)
    print("EXEMPLO 2: Grafo Completo K4")
    print("="*60)
    
    g = Grafo(4)
    for i in range(4):
        for j in range(i+1, 4):
            g.adicionar_aresta(i, j)
    
    print(f"\n{g}")
    print(f"Total de arestas: {len(g.arestas)}")
    
    # 2-Aproximação
    cover_aprox = vertex_cover_2approx(g, verbose=True)
    print(f"\nVertex Cover (2-aprox): {sorted(cover_aprox)}")
    
    # Greedy
    cover_greedy = vertex_cover_greedy_grau(g, verbose=False)
    print(f"Vertex Cover (greedy): {sorted(cover_greedy)}")
    
    print(f"\nAnálise:")
    print(f"- Tamanho 2-aprox: {len(cover_aprox)}")
    print(f"- Tamanho greedy: {len(cover_greedy)}")
    print(f"- Vertex cover ótimo: 3 vértices")
    print(f"- Fator 2-aprox: {len(cover_aprox) / 3:.2f}")
    print(f"- Fator greedy: {len(cover_greedy) / 3:.2f}")


def exemplo3_star_graph():
    """
    Exemplo 3: Grafo Estrela (Star Graph)
    
          1
          |
      2---0---3
          |
          4
    
    Vertex Cover ótimo: {0} (tamanho 1)
    2-Aproximação: todos os vértices (pior caso tight)
    """
    print("\n" + "="*60)
    print("EXEMPLO 3: Grafo Estrela (Star Graph)")
    print("="*60)
    
    g = Grafo(5)
    # Centro é vértice 0
    for i in range(1, 5):
        g.adicionar_aresta(0, i)
    
    print(f"\n{g}")
    print(f"Arestas: {sorted(g.arestas)}")
    
    # 2-Aproximação
    cover_aprox = vertex_cover_2approx(g, verbose=True)
    print(f"\nVertex Cover (2-aprox): {sorted(cover_aprox)}")
    
    # Greedy
    cover_greedy = vertex_cover_greedy_grau(g, verbose=False)
    print(f"Vertex Cover (greedy): {sorted(cover_greedy)}")
    
    print(f"\nAnálise:")
    print(f"- Tamanho 2-aprox: {len(cover_aprox)}")
    print(f"- Tamanho greedy: {len(cover_greedy)}")
    print(f"- Vertex cover ótimo: 1 vértice (centro)")
    print(f"- Fator 2-aprox: {len(cover_aprox) / 1:.2f}")
    print(f"- Fator greedy: {len(cover_greedy) / 1:.2f}")
    print(f"- NOTA: Este é o PIOR CASO para 2-aprox - atinge fator 2!")
    print(f"- Greedy encontra solução ótima neste caso!")


def experimento_grafos_aleatorios(n: int = 20, densidade: float = 0.2, 
                                   num_testes: int = 10):
    """
    Experimento com grafos aleatórios
    
    Args:
        n: Número de vértices
        densidade: Probabilidade de existir aresta entre dois vértices
        num_testes: Número de grafos aleatórios a testar
    """
    print("\n" + "="*60)
    print(f"EXPERIMENTO: {num_testes} Grafos Aleatórios")
    print(f"Parâmetros: n={n}, densidade={densidade}")
    print("="*60)
    
    ratios_aprox = []
    ratios_greedy = []
    
    for i in range(num_testes):
        g = Grafo(n)
        
        # Gera grafo aleatório
        for u in range(n):
            for v in range(u+1, n):
                if random.random() < densidade:
                    g.adicionar_aresta(u, v)
        
        if not g.tem_arestas():
            continue
        
        # Executa algoritmos
        cover_aprox = vertex_cover_2approx(g, verbose=False)
        cover_greedy = vertex_cover_greedy_grau(g, verbose=False)
        
        # Calcula razão (assumindo greedy como referência aproximada)
        ratio_aprox = len(cover_aprox) / len(cover_greedy)
        ratios_aprox.append(len(cover_aprox))
        ratios_greedy.append(len(cover_greedy))
    
    print(f"\nResultados de {len(ratios_aprox)} grafos:")
    print(f"2-Aproximação:")
    print(f"  - Média: {sum(ratios_aprox)/len(ratios_aprox):.2f}")
    print(f"  - Min: {min(ratios_aprox)}, Max: {max(ratios_aprox)}")
    print(f"Greedy:")
    print(f"  - Média: {sum(ratios_greedy)/len(ratios_greedy):.2f}")
    print(f"  - Min: {min(ratios_greedy)}, Max: {max(ratios_greedy)}")
    print(f"Razão média 2-aprox/greedy: {sum(ratios_aprox)/sum(ratios_greedy):.2f}")


def main():
    """Função principal"""
    print("\n" + "╔" + "="*58 + "╗")
    print("║" + " "*8 + "VERTEX COVER - Algoritmo de 2-Aproximação" + " "*8 + "║")
    print("║" + " "*17 + "Via Maximal Matching" + " "*21 + "║")
    print("╚" + "="*58 + "╝")
    
    print("\nEste programa demonstra o algoritmo de 2-aproximação")
    print("para o problema NP-Completo de Vertex Cover.")
    print("\nGarantia: |cover| ≤ 2 × OPT")
    print("Complexidade: O(V + E)")
    
    # Executa exemplos
    exemplo1_path_graph()
    exemplo2_complete_graph()
    exemplo3_star_graph()
    
    # Experimento
    experimento_grafos_aleatorios(n=15, densidade=0.25, num_testes=10)
    
    print("\n" + "="*60)
    print("RESUMO")
    print("="*60)
    print("O algoritmo de 2-aproximação via maximal matching:")
    print("✓ É rápido: O(V + E)")
    print("✓ Tem garantia teórica: nunca pior que 2× ótimo")
    print("✓ É simples de implementar")
    print("✗ Pode dar soluções ruins em grafos estrela")
    print("✗ Não é sempre melhor que heurísticas na prática")
    print("\nLimitação teórica: 2-aproximação é essencialmente ótimo")
    print("(não existe (2-ε)-aprox a menos que P=NP)")


if __name__ == "__main__":
    main()
