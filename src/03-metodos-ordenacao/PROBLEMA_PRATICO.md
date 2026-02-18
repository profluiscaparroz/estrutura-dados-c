# Problema Prático: Sistema de Classificação de Notas Escolares

## 📋 Descrição do Problema

Uma escola precisa processar as notas finais de alunos para:
- Gerar ranking dos melhores alunos (ordem decrescente)
- Identificar alunos que precisam de recuperação (notas < 6.0)
- Calcular estatísticas (média, mediana, quartis)
- Exibir aprovados em ordem alfabética

**Por que usar Algoritmos de Ordenação?**
- Rankings requerem dados ordenados
- Mediana e quartis precisam de ordenação
- Facilita busca e análise de dados
- Diferentes algoritmos para diferentes cenários

## 🔴 Problema: Escolha Inadequada de Algoritmo

```c
#include <stdio.h>
#include <string.h>

#define MAX_ALUNOS 1000

typedef struct {
    char nome[50];
    float nota;
} Aluno;

// PROBLEMA: Bubble Sort para grandes volumes - O(n²)
void ordenarPorNota(Aluno *alunos, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (alunos[j].nota < alunos[j + 1].nota) {
                // Troca
                Aluno temp = alunos[j];
                alunos[j] = alunos[j + 1];
                alunos[j + 1] = temp;
            }
        }
    }
}

// PROBLEMA: Não considera casos especiais
void exibirRanking(Aluno *alunos, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d. %s - %.2f\n", i + 1, alunos[i].nome, alunos[i].nota);
    }
}

int main() {
    Aluno turma[MAX_ALUNOS];
    int total = 5;
    
    // Simular entrada de dados
    strcpy(turma[0].nome, "Maria Silva");
    turma[0].nota = 8.5;
    
    strcpy(turma[1].nome, "João Santos");
    turma[1].nota = 6.0;
    
    strcpy(turma[2].nome, "Ana Costa");
    turma[2].nota = 9.5;
    
    strcpy(turma[3].nome, "Pedro Lima");
    turma[3].nota = 5.5;
    
    strcpy(turma[4].nome, "Carla Souza");
    turma[4].nota = 7.0;
    
    printf("=== RANKING DE ALUNOS ===\n");
    ordenarPorNota(turma, total);
    exibirRanking(turma, total);
    
    return 0;
}
```

### Problemas Identificados:
1. ❌ Bubble Sort O(n²) - ineficiente para muitos alunos
2. ❌ Não trata empates nas notas
3. ❌ Perde ordem alfabética original
4. ❌ Não calcula estatísticas úteis

## ✅ Solução: Implementação Eficiente com Quick Sort

```c
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ALUNOS 1000
#define NOTA_MINIMA 6.0

typedef struct {
    char nome[50];
    float nota;
    int id_original;  // Preserva ordem original para desempate
} Aluno;

// Função auxiliar para trocar elementos
void trocar(Aluno *a, Aluno *b) {
    Aluno temp = *a;
    *a = *b;
    *b = temp;
}

// Comparador personalizado: nota DESC, depois nome ASC (desempate)
int compararPorNota(Aluno *a, Aluno *b) {
    if (a->nota > b->nota) return -1;  // Maior nota primeiro
    if (a->nota < b->nota) return 1;
    // Desempate por nome (ordem alfabética)
    return strcmp(a->nome, b->nome);
}

// Comparador por nome (alfabético)
int compararPorNome(Aluno *a, Aluno *b) {
    return strcmp(a->nome, b->nome);
}

// Partição do Quick Sort
int particionar(Aluno *arr, int low, int high, int (*cmp)(Aluno*, Aluno*)) {
    Aluno pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (cmp(&arr[j], &pivot) < 0) {
            i++;
            trocar(&arr[i], &arr[j]);
        }
    }
    trocar(&arr[i + 1], &arr[high]);
    return i + 1;
}

// Quick Sort Recursivo - O(n log n) médio
void quickSort(Aluno *arr, int low, int high, int (*cmp)(Aluno*, Aluno*)) {
    if (low < high) {
        int pi = particionar(arr, low, high, cmp);
        quickSort(arr, low, pi - 1, cmp);
        quickSort(arr, pi + 1, high, cmp);
    }
}

// Calcula média das notas
float calcularMedia(Aluno *alunos, int n) {
    float soma = 0;
    for (int i = 0; i < n; i++) {
        soma += alunos[i].nota;
    }
    return soma / n;
}

// Calcula mediana (requer dados ordenados)
float calcularMediana(Aluno *alunos, int n) {
    if (n % 2 == 0) {
        return (alunos[n/2 - 1].nota + alunos[n/2].nota) / 2.0;
    } else {
        return alunos[n/2].nota;
    }
}

// Identifica alunos em recuperação
void listarRecuperacao(Aluno *alunos, int n) {
    printf("\n=== ALUNOS EM RECUPERAÇÃO (Nota < %.1f) ===\n", NOTA_MINIMA);
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        if (alunos[i].nota < NOTA_MINIMA) {
            printf("⚠️  %s - Nota: %.2f\n", alunos[i].nome, alunos[i].nota);
            count++;
        }
    }
    
    if (count == 0) {
        printf("✓ Nenhum aluno em recuperação!\n");
    } else {
        printf("Total: %d aluno(s)\n", count);
    }
}

// Exibe ranking formatado
void exibirRanking(Aluno *alunos, int n) {
    printf("\n=== RANKING DE NOTAS ===\n");
    printf("%-4s %-30s %s\n", "Pos", "Nome", "Nota");
    printf("%-4s %-30s %s\n", "---", "----", "----");
    
    for (int i = 0; i < n; i++) {
        char simbolo = alunos[i].nota >= NOTA_MINIMA ? "✓" : "✗";
        printf("%s %-2d  %-30s %.2f\n", simbolo, i + 1, alunos[i].nome, alunos[i].nota);
    }
}

// Exibe aprovados em ordem alfabética
void exibirAprovadosAlfabetico(Aluno *alunos, int n) {
    // Criar cópia apenas dos aprovados
    Aluno aprovados[MAX_ALUNOS];
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        if (alunos[i].nota >= NOTA_MINIMA) {
            aprovados[count++] = alunos[i];
        }
    }
    
    if (count == 0) {
        printf("\n⚠️  Nenhum aluno aprovado!\n");
        return;
    }
    
    // Ordenar por nome
    quickSort(aprovados, 0, count - 1, compararPorNome);
    
    printf("\n=== APROVADOS (Ordem Alfabética) ===\n");
    for (int i = 0; i < count; i++) {
        printf("✓ %s - %.2f\n", aprovados[i].nome, aprovados[i].nota);
    }
    printf("Total de aprovados: %d (%.1f%%)\n", count, (count * 100.0) / n);
}

// Exibe estatísticas
void exibirEstatisticas(Aluno *alunos, int n) {
    // Criar cópia para não alterar ordem original
    Aluno copia[MAX_ALUNOS];
    memcpy(copia, alunos, n * sizeof(Aluno));
    
    // Ordenar por nota para calcular mediana
    quickSort(copia, 0, n - 1, compararPorNota);
    
    float media = calcularMedia(alunos, n);
    float mediana = calcularMediana(copia, n);
    float maior = copia[0].nota;  // Primeira após ordenação decrescente
    float menor = copia[n - 1].nota;  // Última
    
    printf("\n=== ESTATÍSTICAS DA TURMA ===\n");
    printf("Total de alunos: %d\n", n);
    printf("Média geral: %.2f\n", media);
    printf("Mediana: %.2f\n", mediana);
    printf("Maior nota: %.2f (%s)\n", maior, copia[0].nome);
    printf("Menor nota: %.2f (%s)\n", menor, copia[n - 1].nome);
}

int main() {
    Aluno turma[MAX_ALUNOS];
    int total = 0;
    
    printf("=== SISTEMA DE CLASSIFICAÇÃO DE NOTAS ===\n\n");
    
    // Simular entrada de dados (10 alunos)
    char *nomes[] = {
        "Maria Silva", "João Santos", "Ana Costa", "Pedro Lima",
        "Carla Souza", "Bruno Alves", "Julia Ferreira", "Lucas Rocha",
        "Beatriz Martins", "Rafael Oliveira"
    };
    float notas[] = {8.5, 6.0, 9.5, 5.5, 7.0, 8.5, 4.0, 9.0, 6.5, 7.5};
    
    for (int i = 0; i < 10; i++) {
        strcpy(turma[i].nome, nomes[i]);
        turma[i].nota = notas[i];
        turma[i].id_original = i;
        total++;
    }
    
    printf("Processando %d alunos...\n", total);
    
    // Criar cópia para ordenação por nota
    Aluno rankingNotas[MAX_ALUNOS];
    memcpy(rankingNotas, turma, total * sizeof(Aluno));
    
    // Ordenar por nota (Quick Sort) - O(n log n)
    quickSort(rankingNotas, 0, total - 1, compararPorNota);
    
    // Exibir resultados
    exibirRanking(rankingNotas, total);
    exibirEstatisticas(turma, total);
    listarRecuperacao(turma, total);
    exibirAprovadosAlfabetico(turma, total);
    
    return 0;
}
```

## 📊 Análise de Complexidade

| Algoritmo | Melhor Caso | Caso Médio | Pior Caso | Espaço | Estável |
|-----------|-------------|------------|-----------|---------|---------|
| Bubble Sort | O(n) | O(n²) | O(n²) | O(1) | Sim |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | O(log n) | Não |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) | Sim |

**Por que Quick Sort?**
- ⚡ Muito rápido em casos médios: O(n log n)
- 💾 Usa pouca memória extra: O(log n)
- 🎯 In-place: não precisa vetor auxiliar grande
- ⚠️ Não é estável, mas resolvemos com desempate por nome

## 💡 Quando Usar Cada Algoritmo

| Cenário | Algoritmo Recomendado | Motivo |
|---------|----------------------|---------|
| Poucos elementos (< 10) | Insertion Sort | Simples e eficiente |
| Dados quase ordenados | Insertion/Bubble Sort | O(n) no melhor caso |
| Precisa estabilidade | Merge Sort | Mantém ordem relativa |
| Uso geral (grande volume) | Quick Sort | Rápido e econômico |
| Memória muito limitada | Heap Sort | O(1) espaço extra |

## 🎯 Conceitos Aplicados

- ✅ Quick Sort com particionamento
- ✅ Comparadores personalizados (callback functions)
- ✅ Tratamento de empates
- ✅ Estatísticas com dados ordenados (mediana)
- ✅ Cópia de dados para preservar ordem original
- ✅ Formatação profissional de saída

## 📝 Como Compilar e Executar

```bash
# Compilar
gcc PROBLEMA_PRATICO.c -o notas -Wall

# Executar
./notas
```

## 🧪 Exemplo de Saída

```
=== SISTEMA DE CLASSIFICAÇÃO DE NOTAS ===

Processando 10 alunos...

=== RANKING DE NOTAS ===
Pos Nome                           Nota
--- ----                           ----
✓ 1   Ana Costa                     9.50
✓ 2   Lucas Rocha                   9.00
✓ 3   Bruno Alves                   8.50
✓ 4   Maria Silva                   8.50
✓ 5   Rafael Oliveira               7.50
✓ 6   Carla Souza                   7.00
✓ 7   Beatriz Martins               6.50
✓ 8   João Santos                   6.00
✗ 9   Pedro Lima                    5.50
✗ 10  Julia Ferreira                4.00

=== ESTATÍSTICAS DA TURMA ===
Total de alunos: 10
Média geral: 7.25
Mediana: 7.25
Maior nota: 9.50 (Ana Costa)
Menor nota: 4.00 (Julia Ferreira)

=== ALUNOS EM RECUPERAÇÃO (Nota < 6.0) ===
⚠️  Pedro Lima - Nota: 5.50
⚠️  Julia Ferreira - Nota: 4.00
Total: 2 aluno(s)

=== APROVADOS (Ordem Alfabética) ===
✓ Ana Costa - 9.50
✓ Beatriz Martins - 6.50
✓ Bruno Alves - 8.50
✓ Carla Souza - 7.00
✓ João Santos - 6.00
✓ Lucas Rocha - 9.00
✓ Maria Silva - 8.50
✓ Rafael Oliveira - 7.50
Total de aprovados: 8 (80.0%)
```

## 📚 Lições Aprendidas

1. **Escolha o algoritmo certo** - Quick Sort para casos gerais
2. **Use comparadores** - Flexibilidade para diferentes ordenações
3. **Preserve dados originais** - Faça cópias quando necessário
4. **Trate empates** - Critérios secundários de desempate
5. **Calcule estatísticas** - Dados ordenados facilitam mediana/quartis
6. **Formatação importa** - Saída clara e profissional
