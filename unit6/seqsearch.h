#ifndef __SEQ_SEARCH_H__
#define __SEQ_SEARCH_H__

#include "st.h"

// Implements the class for a symbol table based on sequential search
template <typename Key, typename Value>
class SeqSearchST : public ST<Key,Value> {
    // a helper linked list data type
    struct Node {
        Key key;
        Value val;
        Node* next;

        // constructor with values
        Node(const Key& k, const Value& v, Node* n) : key(k), val(v), next(n) {}
    };

    int n;       // number of key-value pairs
    Node* head;  // the linked list of key-value pairs

    // removes a key from list pointed to by x and returns the new head
    Node* remove(Node* x, const Key& key) {
        if (x == nullptr) return (nullptr);
        if (x->key == key) {
            n--;
            Node* nxt = x->next;
            delete x;
            return nxt;
        }
        x->next = remove(x->next, key);
        return x;
    }

    // copys an existing list
    const Node* deep_copy_list(const Node* new_head) {
        if (new_head) {
            auto tail = deep_copy_list(new_head->next);
            return (new Node(new_head->key, new_head->val, tail));
        } 
        return (nullptr);
    }

    // frees the list and sets the head to NULL
    void free_list() {

        while (head) {
            Node* tmp = head->next;
            delete head;
            head = tmp;
        }
        return;
    }

   public:
    // default constructor
    SeqSearchST() : n(0), head(nullptr) {}

    // copy constructor
    SeqSearchST(const SeqSearchST& st) : n(st.n) { head = deep_copy_list(st.head); }

    // move constructor
    SeqSearchST(SeqSearchST&& st) : head(st.head), n(st.n) { st.head = nullptr; st.n = 0; }

    // copy assignment
    SeqSearchST& operator=(const SeqSearchST& st) {
        // free the existing list
        free_list();
        // copy the list and list length passed in
        head = deep_copy_list(st.head);
        n = st.n;
        return (*this);
    }

    // move assignment
    SeqSearchST& operator=(SeqSearchST&& st) {
        // free the existing list
        free_list();

        head = st.head;
        n = st.n;
        st.head = nullptr;
        st.n = 0;
        return (*this);
    }

    // destructor
    ~SeqSearchST() {
        free_list();
    }

    // put a key-value pair into the table
    void put(const Key& key, const Value& val) {
        for (Node* x = head; x != nullptr; x = x->next) {
            if (x->key == key) {
                x->val = val;
                return;
            }
        }

        auto new_head = new Node(key, val, head);
        head = new_head;
        return;
    }

    // gets a value for a given key
    const Value* get(const Key& key) const {
        for (Node* x = head; x != nullptr; x = x->next) {
            if (x->key == key) {
                return &(x->val);
            }
        }
        return (nullptr);
    }

    // removes a key from the table
    void remove(const Key& key) {
        head = remove(head, key);
        return;
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