/******************************************************************************
 *
 * A symbol table implemented with a separate-chaining hash table.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#ifndef __HASH_ST_H__
#define __HASH_ST_H__

#include "queue.h"
#include "ssst.h"
#include "st.h"

#include<functional>
#include<iostream>

// Implements the class for a symbol table based on separate-chaining hash table
template <typename Key, typename Value>
class SeparateChainingHashST : public ST<Key, Value> {
    int n;                                  // number of key-value pairs
    int m;                                  // hash-table size
    SequentialSearchST<Key, Value>* table;  // array of linked-list symbol tables
    std::hash<Key> key_hash;                // hashing function for the key

    // computes the hash key
    int hash(Key key) const {
        auto h = key_hash(key);
        return h & (m - 1);
    }

    // resize the hash table to have the given number of chains, rehashing all of the keys
    void resize(int chains) {
        SeparateChainingHashST<Key,Value> tmp(chains);
        for(auto i = 0; i < m; i++) {
            for (auto key : table[i].keys())
                tmp.put(key, *table[i].get(key));
        }

        *this = tmp;
    }

   public:
    // default constructor
    SeparateChainingHashST(const int chains = 4) : n(0), m(chains) {
        table = new SequentialSearchST<Key, Value>[m];
    }

    // copy constructor
    SeparateChainingHashST(const SeparateChainingHashST& st) : n(st.n),
                                                               m(st.m) {
        table = new SequentialSearchST<Key, Value>[m];
        for (auto i = 0; i < m; i++) st[i] = st.table[i];
    }

    // move constructor
    SeparateChainingHashST(SeparateChainingHashST&& st) : n(st.n),
                                                          m(st.m),
                                                          table(st.table) {
        st.n = 0;
        st.m = 0;
        st.table = nullptr;
    }

    // copy assignment
    SeparateChainingHashST& operator=(const SeparateChainingHashST& st) {
        // free the existing table
        delete[] table;

        // copy the hash table
        n = st.n;
        m = st.m;
        table = new SequentialSearchST<Key, Value>[m];
        for (auto i = 0; i < m; i++) table[i] = st.table[i];

        return (*this);
    }

    // move assignment
    SeparateChainingHashST& operator=(SeparateChainingHashST&& st) {
        // free the existing table
        delete[] table;

        n = st.n;
        m = st.m;
        table = st.table;

        st.n = 0;
        st.m = 0;
        st.table = nullptr;

        return (*this);
    }

    // destructor
    ~SeparateChainingHashST() { delete[] table; }

    // put a key-value pair into the hash table
    void put(const Key& key, const Value& val) {
        int i = hash(key);

        // double table size if average length of list >= 10
        if (n >= 10*m) resize(2*m);

        if (!table[i].contains(key)) n++;
        table[i].put(key, val);
        return;
    }

    // gets a value for a given key
    const Value* get(const Key& key) const {
        int i = hash(key);
        return (table[i].get(key));
    }

    // removes a key from the table
    void remove(const Key& key) {
        int i = hash(key);
        if (table[i].contains(key)) n--;
        table[i].remove(key);

        // halve table size if average length of list <= 2
        if (m > 4 && n <= 2*m) resize(m/2);

        return;
    }

    // checks if there is a value paired with a key
    bool contains(const Key& key) const { return (get(key) != nullptr); }

    // checks if the linked list is empty
    bool is_empty() const { return (size() == 0); }

    // number of nodes stored in the linked list
    int size() const { return (n); }

    // returns all keys in the symbol table
    Queue<Key> keys() const {
        Queue<Key> queue;
        for (auto i = 0; i < m; i++) {
            for (auto key : table[i].keys())
                queue.enqueue(key);
        }
        return (queue);
    }
};

#endif