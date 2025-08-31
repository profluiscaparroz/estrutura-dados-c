#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int* data;
    int size;
    int capacity;
} MinHeap;

MinHeap* create_heap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (int*)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

int parent(int i) { return (i - 1) / 2; }
int left_child(int i) { return 2 * i + 1; }
int right_child(int i) { return 2 * i + 2; }

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(MinHeap* heap, int i) {
    while (i != 0 && heap->data[parent(i)] > heap->data[i]) {
        swap(&heap->data[i], &heap->data[parent(i)]);
        i = parent(i);
    }
}

void heapify_down(MinHeap* heap, int i) {
    int smallest = i;
    int left = left_child(i);
    int right = right_child(i);
    
    if (left < heap->size && heap->data[left] < heap->data[smallest]) {
        smallest = left;
    }
    
    if (right < heap->size && heap->data[right] < heap->data[smallest]) {
        smallest = right;
    }
    
    if (smallest != i) {
        swap(&heap->data[i], &heap->data[smallest]);
        heapify_down(heap, smallest);
    }
}

void insert(MinHeap* heap, int data) {
    if (heap->size == heap->capacity) {
        printf("Heap overflow\n");
        return;
    }
    
    heap->data[heap->size] = data;
    heapify_up(heap, heap->size);
    heap->size++;
}

int extract_min(MinHeap* heap) {
    if (heap->size <= 0) {
        printf("Heap underflow\n");
        return INT_MAX;
    }
    
    if (heap->size == 1) {
        heap->size--;
        return heap->data[0];
    }
    
    int root = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heapify_down(heap, 0);
    
    return root;
}

int get_min(MinHeap* heap) {
    if (heap->size <= 0) {
        printf("Heap is empty\n");
        return INT_MAX;
    }
    return heap->data[0];
}

void print_heap(MinHeap* heap) {
    printf("Heap: ");
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

void destroy_heap(MinHeap* heap) {
    free(heap->data);
    free(heap);
}

int main() {
    MinHeap* heap = create_heap(10);
    
    insert(heap, 3);
    insert(heap, 2);
    insert(heap, 15);
    insert(heap, 5);
    insert(heap, 4);
    insert(heap, 45);
    
    print_heap(heap);
    
    printf("Mínimo: %d\n", get_min(heap));
    printf("Extraído: %d\n", extract_min(heap));
    print_heap(heap);
    
    destroy_heap(heap);
    return 0;
}