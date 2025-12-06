# Load Balancing - Balanceamento de Carga

## 📚 Definição

**Load Balancing**: Distribuir n tarefas entre m máquinas para minimizar o makespan (tempo da máquina mais carregada).

**Entrada**: n tarefas com tempos t₁, ..., tₙ, m máquinas  
**Saída**: Atribuição que minimiza max_i(carga_máquina_i)

## 🎯 Complexidade

- **Classe**: NP-Difícil (redução de Partition)
- **Algoritmos**: Greedy, LPT (Longest Processing Time)

## 💡 Algoritmos

### 1. List Scheduling (Greedy)

```
LIST-SCHEDULING(tasks, m):
    loads = [0] * m
    
    for task in tasks:
        i = argmin(loads)  # Máquina menos carregada
        loads[i] += task
    
    return max(loads)
```

**Fator**: 2 - 1/m

### 2. LPT (Longest Processing Time)

```
LPT(tasks, m):
    Ordena tasks em ordem decrescente
    return LIST-SCHEDULING(tasks, m)
```

**Fator**: 4/3 - 1/(3m) (melhor!)

## 💻 Aplicações

1. **Cloud Computing**: Distribuir VMs em servidores
2. **Sistemas Distribuídos**: Balancear requisições
3. **Manufatura**: Scheduling de máquinas
4. **Redes**: Distribuir tráfego
