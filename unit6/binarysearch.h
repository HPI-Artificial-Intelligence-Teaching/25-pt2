#ifndef __BINARY_SEARCH_H__
#define __BINARY_SEARCH_H__

#include "st.h"

// Implements the class for a symbol table based on binary search
template <typename Key, typename Value>
class BinarySearchST : public ST<Key, Value> {
    const int initial_capacity = 2;  // initial capacity of the key/values array

    Key* keys;    // array for the keys
    Value* vals;  // array for the values
    int n;        // number of key-value pairs
    int length;   // length of the keys and values array

    // copys the array of keys and values as well as the length
    void deep_copy_keys_and_values(const Key* new_keys, const Value* new_vals, const int new_length) {
        length = new_length;
        keys = new Key[length];
        vals = new Value[length];
        for (auto i = 0; i < length; i++) {
            keys[i] = new_keys[i];
            vals[i] = new_vals[i];
        }
        return;
    }

    // frees the arrays of key value pairs
    void free_arrays() {
        delete[] keys;
        delete[] vals;
        return;
    }

    // resize the underlying arrays
    void resize(const int new_length) {
        // allocate temporary array
        length = new_length;
        auto tmp_keys = new Key[length];
        auto tmp_vals = new Value[length];

        // copy the keys and values
        for (int i = 0; i < n; i++) {
            tmp_keys[i] = keys[i];
            tmp_vals[i] = vals[i];
        }

        // free existing arrays and assign the temporary arrays to the new arrays
        free_arrays();
        keys = tmp_keys;
        vals = tmp_vals;
        
        return;
    }    

   public:
    // default constructor
    BinarySearchST() : n(0), length(initial_capacity) { 
        keys = new Key[length];
        vals = new Value[length];
    }

    // copy constructor
    BinarySearchST(const BinarySearchST& st) : n(st.n) { 
        deep_copy_keys_and_values(st.keys, st.vals, st.length); 
    }

    // move constructor
    BinarySearchST(BinarySearchST&& st) : n(st.n), keys(st.keys), vals(st.vals), length(st.length) {
        st.keys = nullptr;
        st.vals = nullptr;
        st.length = 0;
        st.n = 0;
    }

    // copy assignment
    BinarySearchST& operator=(const BinarySearchST& st) {
        // free the existing arrays
        free_arrays();
        // copy the keys and values
        deep_copy_keys_and_values(st.keys, st.vals, st.length);
        n = st.n;
        return (*this);
    }

    // move assignment
    BinarySearchST& operator=(BinarySearchST&& st) {
        // free the existing list
        free_arrays();

        keys = st.keys;
        vals = st.vals;
        length = st.length;
        n = st.n;
        st.keys = nullptr;
        st.vals = nullptr;
        st.length = 0;
        st.n = 0;
        return (*this);
    }

    // destructor
    ~BinarySearchST() {
        free_arrays();
    }

    // put a key-value pair into the table
    void put(const Key& key, const Value& val) {
        int i = rank(key);

        // key is already in table
        if (i < n && keys[i] == key) {
            vals[i] = val;
            return;
        }

        // insert new key-value pair
        if (n == length) resize(2*length);

        for (int j = n; j > i; j--)  {
            keys[j] = keys[j-1];
            vals[j] = vals[j-1];
        }
        keys[i] = key;
        vals[i] = val;
        n++;
        
        return;
    }

    // gets a value for a given key
    const Value* get(const Key& key) const {
        if (is_empty())
            return (nullptr);

        int i = rank(key);

        if (i < n && keys[i] == key)
            return (&(vals[i]));
        return (nullptr);
    }

    // removes a key from the table
    void remove(const Key& key) {
        // if array is empty, nothing can be removed
        if (is_empty()) return;

        int i = rank(key);
        // do nothing if the key is not contained
        if (i == n || keys[i] != key) 
            return;
        // otherwise copy the values over
        for (int j = i; j < n-1; j++)  {
            keys[j] = keys[j+1];
            vals[j] = vals[j+1];
        }
        n--;

        // resize if 1/4 full
        if (n > 0 && n == length/4) resize(length/2);

        return;
    }

    // returns the number of keys in this symbol table strictly less than key
    int rank(const Key& key) const {
        int lo = 0, hi = n - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (key < keys[mid])
                hi = mid - 1;
            else if (key > keys[mid])
                lo = mid + 1;
            else
                return mid;
        }
        return lo;
    }

    // checks if there is a value paired with a key
    bool contains(const Key& key) const {
        return (get(key) != nullptr);
    }

    // checks if the symbol table is empty
    bool is_empty() const { return (n == 0); }

    // number of key-value pairs in the table
    int size() const { return (n); }
};

#endif