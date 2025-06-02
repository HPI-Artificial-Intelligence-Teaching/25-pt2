/******************************************************************************
 *
 * An implementation of a binary search tree
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#ifndef __BST_H__
#define __BST_H__

#include "st.h"

// Implements the class for a symbol table based on (un-balanced) binary search trees
template <typename Key, typename Value>
class BST : public ST<Key, Value> {
    // a helper binary tree node data type
    struct Node {
        Key key;
        Value val;
        Node* left;
        Node* right;
        int size;

        // constructor with values
        Node(const Key& k, const Value& v, const int s) : key(k), val(v), size(s), left(nullptr), right(nullptr) {}
    };
    Node* root;  // root of the search tree

    // copys an existing tree pointed to by n
    const Node* deep_copy_tree(const Node* n) const {
        if (n) {
            auto node = new Node(n->key, n->val, n->size);
            node->left = deep_copy_tree(n->left);
            node->right = deep_copy_tree(n->right);
            return (node);
        }
        return (nullptr);
    }

    // frees the tree pointed to by n
    void free_tree(const Node* n) const {
        if (n) {
            free_tree(n->left);
            free_tree(n->right);
            delete n;
        }
        return;
    }

    // returns the size of a tree pointed to by n
    int size(const Node* n) const {
        return (n ? n->size : 0);
    }

    // use recursion to find the correct node
    const Value* get(const Node* n, const Key& key) const {
        if (n == nullptr) return (nullptr);
        if (key < n->key) return (get(n->left, key));
        if (key > n->key) return (get(n->right, key));
        return &(n->val);
    }

    // uses recursion to put a key-value pair into the tree
    Node* put(Node* n, const Key& key, const Value& val) const {
        if (n == nullptr) {
            auto node = new Node(key, val, 1);
            node->left = nullptr;
            node->right = nullptr;
            return (node);
        }
        if (key < n->key)
            n->left = put(n->left, key, val);
        else if (key > n->key)
            n->right = put(n->right, key, val);
        else
            n->val = val;
        n->size = size(n->left) + size(n->right) + 1;
        return (n);
    }

    // finds the minimum of a tree rooted at n
    Node* min(Node* n) const {
        if (n->left == nullptr)
            return (n);
        else
            return (min(n->left));
    }

    // removes the minimum node of a tree rooted at n and returns the new root (but does not free memory!)
    Node* remove_min(Node* n) const {
        if (n->left == nullptr) {
            return (n->right);
        } else {
            n->left = remove_min(n->left);
            n->size = 1 + size(n->left) + size(n->right);
            return (n);
        }
    }

    // removes the node with the a key from a tree rooted at n
    Node* remove(Node* n, const Key& key) const {
        if (n == nullptr) return (nullptr);
        if (key < n->key)
            n->left = remove(n->left, key);
        else if (key > n->key)
            n->right = remove(n->right, key);
        else {
            // one child case: just return the other child (and free the node to be deleted)
            if (n->right == nullptr) {
                Node* t = n->left;
                delete (n);
                return (t);
            }
            if (n->left == nullptr) {
                Node* t = n->right;
                delete (n);
                return (t);
            }

            // two child chase
            Node* t = n;
            n = min(t->right);
            n->right = remove_min(t->right);
            n->left = t->left;
            delete t;
        }
        n->size = 1 + size(n->left) + size(n->right);
        return (n);
    }

   public:
    // default constructor
    BST() : root(nullptr) {}

    // copy constructor
    BST(const BST& bst) { root = deep_copy_tree(bst.root); }

    // move constructor
    BST(BST&& bst) : root(bst.root) { bst.root = nullptr; }

    // copy assignment
    BST& operator=(const BST& bst) {
        // free the existing tree
        free_tree(root);
        // copy the tree
        root = deep_copy_tree(bst.root);
        return (*this);
    }

    // move assignment
    BST& operator=(BST&& bst) {
        // free the existing tree
        free_tree(root);

        root = bst.root;
        bst.root = nullptr;
        return (*this);
    }

    // destructor
    ~BST() { free_tree(root); }

    // put a key-value pair into the table
    void put(const Key& key, const Value& val) { root = put(root, key, val); }

    // gets a value for a given key
    const Value* get(const Key& key) const { return (get(root, key)); }

    // removes a key from the table
    void remove(const Key& key) { root = remove(root, key); }

    // checks if there is a value paired with a key
    bool contains(const Key& key) const { return (get(key) != nullptr); }

    // checks if the BST is empty
    bool is_empty() const { return (size() == 0); }

    // number of nodes stored in the BST
    int size() const { return (size(root)); }
};

#endif