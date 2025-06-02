/******************************************************************************
 *
 * A set of helper functions for heaps and Heapsort
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#ifndef __HEAP_H__
#define __HEAP_H__

// Implements comparison of two heap elements (assuming 1-based indexing)
template <typename Value>
bool less(Value* heap, const int i, const int j) {
    return (heap[i - 1] < heap[j - 1]);
}

// Implements a swap of element i and j in an array (assuming 1-based indexing)
template <typename Value>
void swap(Value* heap, const int i, const int j) {
    const Value tmp = heap[i - 1];
    heap[i - 1] = heap[j - 1];
    heap[j - 1] = tmp;
    return;
}

// Implements the swim up function of a heap
template <typename Value>
void swim(Value* heap, int k) {
    while (k > 1 && less(heap, k / 2, k)) {
        swap(heap, k, k / 2);
        k = k / 2;
    }
}

// Implements the sink function of a heap
template <typename Value>
void sink(Value* heap, int k, int n) {
    while (2 * k <= n) {
        int j = 2 * k;
        if (j < n && less(heap, j, j + 1)) j++;
        if (!less(heap, k, j)) break;
        swap(heap, k, j);
        k = j;
    }
}

// Implements Heap Sort
template <typename Value>
void heap_sort(Value* heap, int n) {
    // heapify phase
    for (int k = n / 2; k >= 1; k--)
        sink(heap, k, n);

    // sortdown phase
    int k = n;
    while (k > 1) {
        swap(heap, 1, k--);
        sink(heap, 1, k);
    }

    return;
}

#endif