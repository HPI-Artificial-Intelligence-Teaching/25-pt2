/******************************************************************************
 *
 * Generic min priority queue implementation with a binary heap.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#ifndef __MIN_PQ_H__
#define __MIN_PQ_H__

#include <stdexcept>

using namespace std;

// Implements a generic min priority queue with a binary heap
template <typename T>
class MinPQ {
    T* pq;         // store items at indices 1 to n
    int n;         // number of items on priority queue
    int capacity;  // total capacity of the heap

    // resize the underlying array to have the given capacity
    void resize(int new_capacity) {
        // allocate a new array and copy the given number of keys
        T* tmp = new T[new_capacity];
        for (auto i = 1; i <= n; i++) {
            tmp[i] = pq[i];
        }

        // free the memory of the current priority queue and point to new allocated and filled memory
        delete[] pq;
        pq = tmp;
        capacity = new_capacity;

        return;
    }

    // swims up from index k in the heap
    void swim(int k) {
        while (k > 1 && pq[k / 2] > pq[k]) {
            exch(k / 2, k);
            k = k / 2;
        }
        return;
    }

    // sinks down from index k in the heap
    void sink(int k) {
        while (2 * k <= n) {
            int j = 2 * k;
            if (j < n && pq[j] > pq[j + 1]) j++;
            if (!(pq[k] > pq[j])) break;
            exch(k, j);
            k = j;
        }
        return;
    }

    // swaps the priority entry at level i and j
    void exch(const int i, const int j) {
        T swap = pq[i];
        pq[i] = pq[j];
        pq[j] = swap;
        return;
    }

   public:
    // constructor
    MinPQ(const int _capacity = 1) : capacity(_capacity),
                                     n(0) {
        pq = new T[capacity + 1];
    }

    // copy constructor
    MinPQ(const MinPQ& mq) : capacity(mq.capacity),
                             n(mq.n) {
        pq = new T[capacity + 1];
        for (auto i = 0; i <= capacity; i++) {
            pq[i] = mq.pq[i];
        }
    }

    // move constructor
    MinPQ(MinPQ&& mq) : capacity(mq.capacity),
                        n(mq.n),
                        pq(mq.pq) {
        mq.capacity = 0;
        mq.n = 0;
        mq.pq = nullptr;
    }

    // copy assignment
    MinPQ& operator=(const MinPQ& mq) {
        // free the existing priority queue
        delete[] pq;

        // copy the queue passed in
        capacity = mq.capacity;
        n = mq.n;
        pq = new T[capacity + 1];
        for (auto i = 0; i <= capacity; i++) {
            pq[i] = mq.pq[i];
        }

        return (*this);
    }

    // move assignment
    MinPQ& operator=(MinPQ&& mq) {
        // free the existing priority queue
        delete[] pq;

        // shallow copy of priority queue
        capacity = mq.capacity;
        n = mq.n;
        pq = mq.pq;

        // remove the priority queue passed in
        mq.capacity = 0;
        mq.n = 0;
        mq.pq = nullptr;

        return (*this);
    }

    // destructor
    ~MinPQ() {
        delete[] pq;
    }

    // returns true if this priority queue is empty
    bool is_empty() const {
        return (n == 0);
    }

    // returns the number of keys on this priority queue
    int size() const {
        return (n);
    }

    // returns the minimum of the priority queue
    const T& min() const {
        if (is_empty()) throw logic_error("Priority queue underflow");
        return (pq[1]);
    }

    // adds a new key to this priority queue
    void insert(const T& x) {
        // double size of array if necessary
        if (n == capacity - 1) resize(2 * capacity);

        // add x, and percolate it up to maintain heap invariant
        pq[++n] = x;
        swim(n);

        return;
    }

    // removes and returns a smallest key on this priority queue
    T del_min() {
        if (is_empty()) throw logic_error("Priority queue underflow");
        T min = pq[1];
        exch(1, n--);
        sink(1);
        if ((n > 0) && (n == (capacity - 1) / 4)) resize(capacity / 2);
        return min;
    }
};

#endif
