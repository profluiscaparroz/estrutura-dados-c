#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Binary search function that counts operations
int binarySearch(int arr[], int left, int right, int x, int* operations) {
    *operations = 0;  // Initialize operation count
    
    while (left <= right) {
        (*operations)++;  // Count each iteration as an operation
        
        int mid = left + (right - left) / 2;
        
        // Check if x is present at mid
        if (arr[mid] == x) {
            (*operations)++;  // Count this comparison
            return mid;
        }
        
        // If x greater, ignore left half
        if (arr[mid] < x) {
            (*operations)++;  // Count this comparison
            left = mid + 1;
        }
        // If x is smaller, ignore right half
        else {
            right = mid - 1;
        }
    }
    
    // Element was not present in array
    return -1;
}

// Linear search function for comparison
int linearSearch(int arr[], int n, int x, int* operations) {
    *operations = 0;
    
    for (int i = 0; i < n; i++) {
        (*operations)++;
        if (arr[i] == x)
            return i;
    }
    return -1;
}

int main() {
    // Define array sizes for demonstration
    int sizes[] = {10000, 100000, 1000000, 10000000};
    int num_sizes = 4;
    
    printf("Binary Search Performance Analysis\n");
    printf("=================================\n\n");
    
    // Test with different array sizes
    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        printf("Array size: %d\n", n);
        printf("---------------------------------\n");
        
        // Allocate and initialize array
        int* arr = (int*)malloc(n * sizeof(int));
        if (arr == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }
        
        // Fill array with sorted values
        for (int i = 0; i < n; i++) {
            arr[i] = i * 2;  // Even numbers
        }
        
        // Test cases: first element, middle, last, non-existent
        int test_values[] = {0, arr[n/2], arr[n-1], arr[n-1] + 2};
        char* descriptions[] = {"First element", "Middle element", "Last element", "Non-existent"};
        
        for (int t = 0; t < 4; t++) {
            int target = test_values[t];
            int binary_ops = 0, linear_ops = 0;
            
            printf("\nSearching for: %s (value: %d)\n", descriptions[t], target);
            
            // Binary search timing
            clock_t start = clock();
            int binary_result = binarySearch(arr, 0, n - 1, target, &binary_ops);
            clock_t end = clock();
            double binary_time = 1000.0 * (double)(end - start) / CLOCKS_PER_SEC;
            
            // Linear search timing
            start = clock();
            int linear_result = linearSearch(arr, n, target, &linear_ops);
            end = clock();
            double linear_time = 1000.0 * (double)(end - start) / CLOCKS_PER_SEC;
            
            // Print results
            printf("Binary search: %d operations, %.6f ms, %s\n", 
                   binary_ops, binary_time,
                   (binary_result != -1) ? "Found" : "Not found");
                   
            printf("Linear search: %d operations, %.6f ms, %s\n", 
                   linear_ops, linear_time,
                   (linear_result != -1) ? "Found" : "Not found");
                   
            if (binary_ops > 0 && linear_ops > 0) {
                printf("Efficiency ratio: %.2f times fewer operations with binary search\n",
                      (double)linear_ops / binary_ops);
            }
        }
        
        printf("---------------------------------\n\n");
        free(arr);
    }
    
    return 0;
}