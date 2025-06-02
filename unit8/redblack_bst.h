/******************************************************************************
 *
 * An implementation of left-leaning red-black trees
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#ifndef __RED_BLACK_BST_H__
#define __RED_BLACK_BST_H__

#include "st.h"

// Implements the class for a symbol table based on (balanced) red-black binary search trees
template <typename Key, typename Value>
class RedBlackBST : public ST<Key, Value> {
    // a helper binary tree node data type
    struct Node {
        Key key;
        Value val;
        Node* left;
        Node* right;
        bool red;
        int size;

        // constructor with values
        Node(const Key& k, const Value& v, const bool _red, const int s) : key(k), val(v), red(_red), size(s), left(nullptr), right(nullptr) {}
    };
    Node* root;  // root of the search tree

    // copys an existing tree pointed to by n
    const Node* deep_copy_tree(const Node* n) const {
        if (n) {
            auto node = new Node(n->key, n->val, n->red, n->size);
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

    // returns whether the link from the parent is red
    bool is_red(const Node* n) const {
        return (n ? n->red : false);
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
            auto node = new Node(key, val, true, 1);
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

        // fix-up any right-leaning links
        if (is_red(n->right) && !is_red(n->left)) n = rotate_left(n);
        if (is_red(n->left) && is_red(n->left->left)) n = rotate_right(n);
        if (is_red(n->left) && is_red(n->right)) flip_colors(n);

        n->size = size(n->left) + size(n->right) + 1;
        return (n);
    }

    // uses recursion to remove a key-value pair from the tree
    Node* remove(Node* n, const Key& key) const {
        if (key < n->key) {
            if (!is_red(n->left) && !is_red(n->left->left))
                n = move_red_left(n);
            n->left = remove(n->left, key);
        } else {
            if (is_red(n->left))
                n = rotate_right(n);
            if ((key == n->key) && (n->right == nullptr)) {
                delete n;
                return (nullptr);
            }
            if (!is_red(n->right) && !is_red(n->right->left))
                n = move_red_right(n);
            if (key == n->key) {
                Node* t = min(n->right);
                n->key = t->key;
                n->val = t->val;
                n->right = remove_min(n->right);
            } else
                n->right = remove(n->right, key);
        }
        return (balance(n));
    }

    // finds the minimum of a tree rooted at n
    Node* min(Node* n) const {
        if (n->left == nullptr)
            return (n);
        else
            return (min(n->left));
    }

    // removes the minimum node of a tree rooted at n and returns the new root
    Node* remove_min(Node* n) const {
        if (n->left == nullptr) {
            delete n;
            return (nullptr);
        } else {
            if (!is_red(n->left) && !is_red(n->left->left))
                n = move_red_left(n);
            n->left = remove_min(n->left);
            return balance(n);
        }
    }

    // make a left-leaning link lean to the right and returns new root
    Node* rotate_right(Node* n) const {
        Node* x = n->left;
        n->left = x->right;
        x->right = n;
        x->red = n->red;
        n->red = true;
        x->size = n->size;
        n->size = size(n->left) + size(n->right) + 1;
        return x;
    }

    // make a right-leaning link lean to the left and returns new root
    Node* rotate_left(Node* n) const {
        Node* x = n->right;
        n->right = x->left;
        x->left = n;
        x->red = n->red;
        n->red = true;
        x->size = n->size;
        n->size = size(n->left) + size(n->right) + 1;
        return x;
    }

    // flip the colors of the link pointing to the node and its two children links
    void flip_colors(Node* n) const {
        n->red = !n->red;
        if (n->left != nullptr) n->left->red = !n->left->red;
        if (n->right != nullptr) n->right->red = !n->right->red;
        return;
    }

    // Assuming that n has a red link pointing into it and both n->left and n->left->left
    // are black, make n->left or one of its child links red.
    Node* move_red_left(Node* n) const {
        flip_colors(n);
        if (is_red(n->right->left)) {
            n->right = rotate_right(n->right);
            n = rotate_left(n);
            flip_colors(n);
        }
        return (n);
    }

    // Assuming that n has a red link pointing into it and both n->right and n->right->left
    // are black, make n->right or one of its child links red.
    Node* move_red_right(Node* n) const {
        flip_colors(n);
        if (is_red(n->left->left)) {
            n = rotate_right(n);
            flip_colors(n);
        }
        return (n);
    }

    // restore red-black tree invariant
    Node* balance(Node* n) const {
        if (is_red(n->right)) n = rotate_left(n);
        if (is_red(n->left) && is_red(n->left->left)) n = rotate_right(n);
        if (is_red(n->left) && is_red(n->right)) flip_colors(n);

        n->size = size(n->left) + size(n->right) + 1;
        return (n);
    }

   public:
    // default constructor
    RedBlackBST() : root(nullptr) {}

    // copy constructor
    RedBlackBST(const RedBlackBST& bst) { root = deep_copy_tree(bst.root); }

    // move constructor
    RedBlackBST(RedBlackBST&& bst) : root(bst.root) { bst.root = nullptr; }

    // copy assignment
    RedBlackBST& operator=(const RedBlackBST& bst) {
        // free the existing tree
        free_tree(root);
        // copy the tree
        root = deep_copy_tree(bst.root);
        return (*this);
    }

    // move assignment
    RedBlackBST& operator=(RedBlackBST&& bst) {
        // free the existing tree
        free_tree(root);

        root = bst.root;
        bst.root = nullptr;
        return (*this);
    }

    // destructor
    ~RedBlackBST() {
        free_tree(root);
    }

    // put a key-value pair into the table
    void put(const Key& key, const Value& val) {
        root = put(root, key, val);
        root->red = false;
        return;
    }

    // gets a value for a given key
    const Value* get(const Key& key) const { return (get(root, key)); }

    // removes a key from the table
    void remove(const Key& key) {
        if (!contains(key)) return;

        // if both children of root have black links, set link into root to red
        if (!is_red(root->left) && !is_red(root->right))
            root->red = true;

        root = remove(root, key);

        // color back the root
        if (!is_empty()) root->red = false;
        return;
    }

    // checks if there is a value paired with a key
    bool contains(const Key& key) const {
        return (get(key) != nullptr);
    }

    // checks if the BST is empty
    bool is_empty() const { return (size() == 0); }

    // number of nodes stored in the BST
    int size() const { return (size(root)); }
};

#endif