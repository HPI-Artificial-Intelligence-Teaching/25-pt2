/******************************************************************************
 *
 * An implementation of a symbol table with sequential search in an unordered linked list
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#ifndef __SSST_H__
#define __SSST_H__

#include "st.h"
#include "queue.h"

// Implements the class for a symbol table based on sequential search in an unordered linked list
template <typename Key, typename Value>
class SequentialSearchST : public ST<Key, Value> {
    // a helper linked list node data type
    struct Node {
        Key key;
        Value val;
        Node* next;

        // constructor with values
        Node(const Key& k, const Value& v, Node* nxt=nullptr) : key(k), val(v), next(nxt) {}
    };
    Node* head;  // head of the linked list of key-value pairs
    int n;       // number of key-value pairs

    // copys an existing linked list pointed to by n into the head
    void deep_copy_list(const Node* x) {
        if (x) {
            head = new Node(x->key, x->val);
            auto* last = head;
            while (x->next) {
                x = x->next;
                last->next = new Node(x->key, x->val);
                last = last->next;
            }
        } else
            head = nullptr;
    }

    // frees the linked list pointed to by head
    void free_list() {
        while (head) {
            auto* tmp = head->next;
            delete head;
            head = tmp;
        }
        return;
    }

    // removes the node with the a key from a list rooted at n
    Node* remove(Node* x, const Key& key) {
        if (x == nullptr) return (nullptr);
        if (x->key == key) {
            n--;
            return (x->next);
        }
        x->next = remove(x->next, key);
        return (x);
    }

   public:
    // default constructor
    SequentialSearchST() : head(nullptr), n(0) {}

    // copy constructor
    SequentialSearchST(const SequentialSearchST& st) : n(st.n) { deep_copy_list(st.root); }

    // move constructor
    SequentialSearchST(SequentialSearchST&& st) : head(st.head), n(st.n) {
        st.root = nullptr;
        st.n = 0;
    }

    // copy assignment
    SequentialSearchST& operator=(const SequentialSearchST& st) {
        // free the existing list
        free_list();
        // copy the list
        deep_copy_list(st.head);
        return (*this);
    }

    // move assignment
    SequentialSearchST& operator=(SequentialSearchST&& st) {
        // free the existing list
        free_list();

        head = st.head;
        n = st.n;
        st.root = nullptr;
        st.n = 0;
        return (*this);
    }

    // destructor
    ~SequentialSearchST() { free_list(); }

    // put a key-value pair into the table
    void put(const Key& key, const Value& val) {
        for (auto* it = head; it != nullptr; it = it->next) {
            if (it->key == key) {
                it->val = val;
                return;
            }
        }

        head = new Node(key, val, head);
        n++;
        return;
    }

    // gets a value for a given key
    const Value* get(const Key& key) const {
        for (auto* it = head; it != nullptr; it = it->next) {
            if (it->key == key)
                return (&(it->val));
        }
        return (nullptr);
    }

    // removes a key from the table
    void remove(const Key& key) { head = remove(head, key); }

    // checks if there is a value paired with a key
    bool contains(const Key& key) const { return (get(key) != nullptr); }

    // checks if the linked list is empty
    bool is_empty() const { return (size() == 0); }

    // number of nodes stored in the linked list
    int size() const { return (n); }

    // returns all keys in the symbol table
    Queue<Key> keys() const {
        Queue<Key> queue;
        for (auto* it = head; it != nullptr; it = it->next) 
            queue.enqueue(it->key);
        return (queue);
    }
};

#endif