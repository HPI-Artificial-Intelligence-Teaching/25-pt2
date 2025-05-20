/******************************************************************************
 *
 * An implementation of insertion sort
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#ifndef __INSERTION_H__
#define __INSERTION_H__


// Implements comparison of two array elements 
template <typename Value>
bool less(const Value* a, const int i, const int j) {
    return (a[i] < a[j]);
}

// Implements a swap of element i and j in an array 
template <typename Value>
void swap(Value* a, const int i, const int j) {
    const Value tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
    return;
}

// Checks that an array is sorted
template <typename Value>
bool is_sorted(Value* a, const int n) {
    for (auto i = 1; i < n; i++) {
        if (less(a, i, i - 1)) {
            return false;
        }
    }
    return true;
}

// Implements insertion sort
template <typename Value>
void insertion_sort(Value* a, const int n) {
    for (auto i = 1; i < n; i++) {
        for (auto j = i; j > 0 && less(a, j, j - 1); j--) {
            swap(a, j, j - 1);
        }
    }
    return;
}

// Implements bubble sort
template <typename Value>
void bubble_sort(Value* a, const int n) {
    for (auto i = 0; i < n; i++) {
        for (auto j = n-1; j > i; j--) {
            if (less(a, j, j-1)) {
                swap(a, j, j-1);
            }
        }
    }
    return;
}

// Implements selection sort
template <typename Value>
void selection_sort(Value* a, const int n) {
    for (auto i = 0; i < n; i++) {
        auto min = i;
        for (auto j = i+1; j < n; j++) {
            if (less(a, j, min)) {
                min = j;
            }
        }
        swap(a, i, min);
    }
    return;
}

// Implements shell sort
template <typename Value>
void shell_sort(Value* a, const int n) {

    // 3x+1 increment sequence:  1, 4, 13, 40, 121, 364, 1093, ...
    int h = 1;
    while (h < n/3) {
        h = 3*h + 1;
    }

    while (h >= 1) {
        // h-sort the array
        for (auto i = h; i < n; i++) {
            for (auto j = i; j >= h && less(a, j, j-h); j -= h) {
                swap(a, j, j-h);
            }
        }
        h /= 3;
    }
    return;
}

// Implements merge sort
template <typename Value>
void merge(Value* a, Value* aux, const int lo, const int mid, const int hi) {
    // copy to aux[]
    for (auto k = lo; k <= hi; k++) {
        aux[k] = a[k];
    }

    // merge back to a[]
    auto i = lo, j = mid+1;
    for (auto k = lo; k <= hi; k++) {
        if (i > mid) {
            a[k] = aux[j++];
        } else if (j > hi) {
            a[k] = aux[i++];
        } else if (less(aux, j, i)) {
            a[k] = aux[j++];
        } else {
            a[k] = aux[i++];
        }
    }
    return;
}

// Implements the recursive merge sort
template <typename Value>
void merge_sort(Value* a, Value* aux, const int lo, const int hi) {
    if (hi <= lo) {
        return;
    }
    auto mid = lo + (hi - lo) / 2;
    merge_sort(a, aux, lo, mid);
    merge_sort(a, aux, mid+1, hi);
    merge(a, aux, lo, mid, hi);
    return;
}

// Implements the iterative merge sort
template <typename Value>
void bottom_up_merge_sort(Value* a, const int n) {
    Value* aux = new Value[n];
    for (auto sz = 1; sz < n; sz *= 2) {
        for (auto lo = 0; lo < n-sz; lo += sz+sz) {
            merge(a, aux, lo, lo+sz-1, std::min(lo+sz+sz-1, n-1));
        }
    }
    delete[] aux;
    return;
}

// Implements the partition function of quick sort
template <typename Value>
int partition(Value* a, const int lo, const int hi) {
    auto i = lo, j = hi+1;
    auto v = a[lo];
    while (true) {
        while (less(a, ++i, lo)) {
            if (i == hi) {
                break;
            }
        }
        while (less(a, lo, --j)) {
            if (j == lo) {
                break;
            }
        }
        if (i >= j) {
            break;
        }
        swap(a, i, j);
    }
    swap(a, lo, j);
    return j;
}

// Implements quick sort
template <typename Value>
void quick_sort(Value* a, const int lo, const int hi) {
    if (hi <= lo) {
        return;
    }
    auto j = partition(a, lo, hi);
    quick_sort(a, lo, j-1);
    quick_sort(a, j+1, hi);
    return;
}

// Implements 3-way quick sort
template <typename Value>
void quick_sort_3way(Value* a, const int lo, const int hi) {
    if (hi <= lo) {
        return;
    }
    auto lt = lo, i = lo+1, gt = hi;
    while (i <= gt) {
        if (less(a, i, lt)) {
            swap(a, lt++, i++);
        } else if (less(a, lt, i)) {
            swap(a, i, gt--);
        } else {
            i++;
        }
    }
    quick_sort_3way(a, lo, lt-1);
    quick_sort_3way(a, gt+1, hi);
    return;
}


#endif
