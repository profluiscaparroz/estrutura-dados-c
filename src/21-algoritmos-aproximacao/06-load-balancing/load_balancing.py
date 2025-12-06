"""Load Balancing - List Scheduling e LPT"""

def list_scheduling(tasks, m):
    loads = [0] * m
    assignment = []
    
    for task in tasks:
        min_machine = min(range(m), key=lambda i: loads[i])
        loads[min_machine] += task
        assignment.append(min_machine)
    
    return max(loads), assignment

def lpt(tasks, m):
    sorted_tasks = sorted(tasks, reverse=True)
    return list_scheduling(sorted_tasks, m)

tasks = [7, 5, 4, 4, 3, 3, 2]
m = 3

greedy_makespan, _ = list_scheduling(tasks, m)
lpt_makespan, _ = lpt(tasks, m)

print("LOAD BALANCING")
print(f"Tarefas: {tasks}")
print(f"Máquinas: {m}")
print(f"List Scheduling: makespan = {greedy_makespan}")
print(f"LPT: makespan = {lpt_makespan}")
print("\nLPT é melhor: fator 4/3 vs 2")
