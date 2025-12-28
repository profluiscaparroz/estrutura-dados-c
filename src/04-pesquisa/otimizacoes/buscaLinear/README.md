# Otimizações de Busca Linear

## 📋 Visão Geral

Este diretório contém implementações otimizadas do algoritmo de busca linear, demonstrando técnicas avançadas para melhorar significativamente a performance de buscas sequenciais.

## 📚 Implementações Incluídas

### 1. buscaLinearSentinela.c
Técnica de sentinela para eliminar verificação de limites.

**Conceito**: Adiciona o valor buscado no final do vetor, eliminando necessidade de verificar limites em cada iteração.

**Vantagem:**
- Reduz uma comparação por iteração
- Melhora ~10-15% em performance
- Código mais simples

**Implementação:**
```c
int busca_sentinela(int arr[], int n, int x) {
    int ultimo = arr[n-1];  // Guardar último elemento
    arr[n-1] = x;           // Colocar sentinela
    
    int i = 0;
    while (arr[i] != x) i++;
    
    arr[n-1] = ultimo;      // Restaurar último elemento
    
    // Verificar se encontrou ou era a sentinela
    if (i < n-1 || arr[n-1] == x)
        return i;
    return -1;
}
```

### 2. buscaLinearLoopUnrolling.c
Loop unrolling - desenrolar laço para processar múltiplos elementos por iteração.

**Conceito**: Reduz overhead de controle do loop processando múltiplos elementos simultaneamente.

**Vantagem:**
- Reduz instruções de controle
- Melhora 20-30% em performance
- Melhor uso do pipeline da CPU

**Implementação:**
```c
int busca_unrolled(int arr[], int n, int x) {
    int i;
    // Processar 4 elementos por vez
    for (i = 0; i < n - 3; i += 4) {
        if (arr[i] == x) return i;
        if (arr[i+1] == x) return i+1;
        if (arr[i+2] == x) return i+2;
        if (arr[i+3] == x) return i+3;
    }
    
    // Processar elementos restantes
    for (; i < n; i++) {
        if (arr[i] == x) return i;
    }
    
    return -1;
}
```

**Fator de Unrolling:**
- 2x: Bom para vetores pequenos
- 4x: Ideal para maioria dos casos
- 8x: Para vetores muito grandes

### 3. buscaLinearBuscaParalelaSIMD.c
Paralelização usando instruções SIMD (Single Instruction Multiple Data).

**Conceito**: Usa instruções vetoriais (SSE/AVX) para comparar múltiplos elementos simultaneamente.

**Vantagem:**
- Speedup de 4-8x com AVX2
- Até 16x com AVX-512
- Processa 4-16 elementos por instrução

**Requerimentos:**
- CPU com suporte SSE/AVX
- Compilação com flags apropriadas: `-msse4.2` ou `-mavx2`

**Exemplo com AVX2:**
```c
#include <immintrin.h>

int busca_simd(int arr[], int n, int x) {
    __m256i target = _mm256_set1_epi32(x);
    
    for (int i = 0; i < n; i += 8) {
        __m256i data = _mm256_loadu_si256((__m256i*)&arr[i]);
        __m256i cmp = _mm256_cmpeq_epi32(data, target);
        
        int mask = _mm256_movemask_epi8(cmp);
        if (mask != 0) {
            // Encontrou! Calcular posição exata
            return i + (__builtin_ctz(mask) / 4);
        }
    }
    
    return -1;
}
```

### 4. buscaLinearBuscaParalelaMultithreading.c
Paralelização usando threads para vetores muito grandes.

**Conceito**: Divide o vetor em chunks e processa cada chunk em uma thread separada.

**Vantagem:**
- Speedup próximo ao número de cores
- Ideal para vetores gigantes (n > 1.000.000)
- Aproveita múltiplos núcleos da CPU

**Implementação:**
```c
#include <pthread.h>

typedef struct {
    int *arr;
    int start;
    int end;
    int target;
    int result;
} thread_data_t;

void* busca_thread(void* arg) {
    thread_data_t* data = (thread_data_t*)arg;
    
    for (int i = data->start; i < data->end; i++) {
        if (data->arr[i] == data->target) {
            data->result = i;
            return NULL;
        }
    }
    
    data->result = -1;
    return NULL;
}

int busca_paralela(int arr[], int n, int x, int num_threads) {
    pthread_t threads[num_threads];
    thread_data_t thread_data[num_threads];
    int chunk_size = n / num_threads;
    
    // Criar threads
    for (int i = 0; i < num_threads; i++) {
        thread_data[i].arr = arr;
        thread_data[i].start = i * chunk_size;
        thread_data[i].end = (i == num_threads-1) ? n : (i+1) * chunk_size;
        thread_data[i].target = x;
        
        pthread_create(&threads[i], NULL, busca_thread, &thread_data[i]);
    }
    
    // Aguardar e coletar resultados
    int resultado = -1;
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        if (thread_data[i].result != -1) {
            if (resultado == -1 || thread_data[i].result < resultado) {
                resultado = thread_data[i].result;
            }
        }
    }
    
    return resultado;
}
```

### 5. buscaLinearBaseadaHeuristicaFrequencia.c
Otimização baseada em frequência de acesso.

**Conceito**: Move elementos frequentemente buscados para frente do vetor (Move-to-Front heuristic).

**Vantagem:**
- O(1) para elementos frequentes
- Adapta-se ao padrão de uso
- Auto-organizável

**Estratégias:**
1. **Move-to-Front**: Move elemento encontrado para início
2. **Transpose**: Troca com elemento anterior
3. **Count**: Ordena por frequência de acesso

**Implementação Move-to-Front:**
```c
int busca_mtf(int arr[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x) {
            // Mover para frente
            if (i > 0) {
                int temp = arr[i];
                for (int j = i; j > 0; j--) {
                    arr[j] = arr[j-1];
                }
                arr[0] = temp;
                return 0;
            }
            return i;
        }
    }
    return -1;
}
```

## 🔧 Compilação

### Básica
```bash
gcc -Wall -Wextra -std=c99 -O3 -o linear buscaLinearSentinela.c
```

### Com SIMD
```bash
# SSE4.2
gcc -Wall -Wextra -std=c99 -O3 -msse4.2 -o simd buscaLinearBuscaParalelaSIMD.c

# AVX2 (melhor performance)
gcc -Wall -Wextra -std=c99 -O3 -mavx2 -o simd buscaLinearBuscaParalelaSIMD.c

# AVX-512 (CPUs mais recentes)
gcc -Wall -Wextra -std=c99 -O3 -mavx512f -o simd buscaLinearBuscaParalelaSIMD.c
```

### Com Multithreading
```bash
gcc -Wall -Wextra -std=c99 -O3 -pthread -o parallel buscaLinearBuscaParalelaMultithreading.c
```

## 📊 Comparação de Performance

### Vetor de 1.000.000 elementos

| Técnica | Tempo Relativo | Speedup | Notas |
|---------|----------------|---------|-------|
| **Padrão** | 1.0x | 1.0x | Baseline |
| **Sentinela** | 0.85x | 1.18x | Simples e efetivo |
| **Loop Unrolling 4x** | 0.75x | 1.33x | Bom equilíbrio |
| **SIMD (AVX2)** | 0.15x | 6.67x | Requer hardware |
| **Multithreading (8 cores)** | 0.14x | 7.14x | Para vetores grandes |
| **Heurística (80% hot)** | 0.05x | 20x | Dados com padrão |

## 💡 Escolhendo a Técnica

### Sentinela
✅ **Use quando:**
- Simplicidade é importante
- Vetor não é constante
- Ganho moderado é suficiente

### Loop Unrolling
✅ **Use quando:**
- Quer ganho sem dependências
- Código portável
- Tamanho do vetor é múltiplo do fator de unrolling

### SIMD
✅ **Use quando:**
- Máxima performance é crítica
- Hardware suporta (verificar em runtime)
- Vetor está alinhado na memória

### Multithreading
✅ **Use quando:**
- Vetor é muito grande (n > 1.000.000)
- Múltiplos cores disponíveis
- Overhead de threads compensa

### Heurística
✅ **Use quando:**
- Padrão de acesso não-uniforme
- 80/20 rule: 80% das buscas em 20% dos dados
- Vetor pode ser modificado

## ⚠️ Considerações

### Cache
- Busca linear tem excelente cache locality
- Para vetores pequenos (<1KB), pode ser mais rápida que binária

### Overhead
- Multithreading: overhead de ~1000 ciclos por thread
- SIMD: requer alinhamento e padding

### Portabilidade
- SIMD: CPU-specific, verificar suporte em runtime
- Multithreading: overhead varia por sistema operacional

## 🚀 Técnicas Combinadas

### Híbrida: Sentinela + Loop Unrolling
```c
int busca_hibrida(int arr[], int n, int x) {
    int ultimo = arr[n-1];
    arr[n-1] = x;
    
    int i;
    for (i = 0; i < n - 3; i += 4) {
        if (arr[i] == x) { arr[n-1] = ultimo; return i; }
        if (arr[i+1] == x) { arr[n-1] = ultimo; return i+1; }
        if (arr[i+2] == x) { arr[n-1] = ultimo; return i+2; }
        if (arr[i+3] == x) { arr[n-1] = ultimo; return i+3; }
    }
    
    while (arr[i] != x) i++;
    arr[n-1] = ultimo;
    
    return (i < n-1 || ultimo == x) ? i : -1;
}
```

## 📚 Recursos Adicionais

- [SIMD Tutorial](https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html)
- [Loop Optimization](https://en.wikipedia.org/wiki/Loop_optimization)
- [POSIX Threads](https://en.wikipedia.org/wiki/POSIX_Threads)
- [Self-organizing List](https://en.wikipedia.org/wiki/Self-organizing_list)

---

**Repositório**: https://github.com/profluiscaparroz/estrutura-dados-c
