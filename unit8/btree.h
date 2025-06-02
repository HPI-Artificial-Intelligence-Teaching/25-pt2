#ifndef __BTREE_H__
#define __BTREE_H__

#include "queue.h"

// Implements a binary tree with a recursive struct
template <typename T>
class BTree {
    // stores a node of the binary tree
    struct TreeNode {
        T data;
        TreeNode* left;
        TreeNode* right;
    }* head;

    // recursively copies an existing tree and returns the new pointer to the head
    TreeNode* deep_copy_tree(const TreeNode* node) {
        TreeNode* new_node = nullptr;

        // make a deep copy of the node if it is non-NULL
        if (node) {
            new_node = new TreeNode;
            new_node->data = node->data;
            new_node->left = deep_copy_tree(node->left);
            new_node->right = deep_copy_tree(node->right);
        }

        return new_node;
    }

    // recursively frees the tree nodes
    void free_tree_nodes(const TreeNode* node) {
        if (node) {
            free_tree_nodes(node->left);
            free_tree_nodes(node->right);
            delete node;
        }
        return;
    }

    // recursively inserts a new data item and returns the new head
    TreeNode* insert_node(TreeNode* head, const T& data) {
        // if the head is empty, create a new node and return a pointer to it
        if (head == nullptr) {
            TreeNode* new_head = new TreeNode;
            new_head->data = data;
            new_head->left = nullptr;
            new_head->right = nullptr;
            return new_head;
        }

        // otherwise, decide where to insert based on the data value
        if (data < head->data)
            head->left = insert_node(head->left, data);
        else if (data > head->data)
            head->right = insert_node(head->right, data);

        return head;
    }

    // traverse the tree in order
    void traverse_nodes_in_order(const TreeNode* node, void (*f)(const T&)) {
        if (node) {
            traverse_nodes_in_order(node->left, f);
            f(node->data);
            traverse_nodes_in_order(node->right, f);
        }
        return;
    }

    // traverse the tree pre order
    void traverse_nodes_pre_order(const TreeNode* node, void (*f)(const T&)) {
        if (node) {
            f(node->data);
            traverse_nodes_pre_order(node->left, f);
            traverse_nodes_pre_order(node->right, f);
        }
        return;
    }

    // traverse the tree post order
    void traverse_nodes_post_order(const TreeNode* node, void (*f)(const T&)) {
        if (node) {
            traverse_nodes_post_order(node->left, f);
            traverse_nodes_post_order(node->right, f);
            f(node->data);
        }
        return;
    }

   public:
    // constructor
    BTree() : head(nullptr) {}

    // copy constructor
    BTree(const BTree& s) { head = deep_copy_list(s.head); }

    // move constructor
    BTree(BTree&& s) : head(s.head) { s.head = nullptr; }

    // copy assignment
    BTree& operator=(const BTree& s) {
        // free the existing stack
        free_tree_nodes(head);
        // copy the stack passed in
        head = deep_copy_list(s.head);
        return (*this);
    }

    // move assignment
    BTree& operator=(BTree&& s) {
        // free the existing stack
        free_tree_nodes(head);

        head = s.head;
        s.head = nullptr;
        return (*this);
    }

    // destructor
    ~BTree() {
        free_tree_nodes(head);
    }

    // inserts a new data entry into the tree
    void insert(const T& data) {
        head = insert_node(head, data);
        return;
    }

    // executes a function for every element of the tree (in order)
    void traverse_in_order(void (*f)(const T&)) {
        traverse_nodes_in_order(head, f);
        return;
    }

    // executes a function for every element of the tree (pre order)
    void traverse_pre_order(void (*f)(const T&)) {
        traverse_nodes_pre_order(head, f);
        return;
    }

    // executes a function for every element of the tree (post order)
    void traverse_post_order(void (*f)(const T&)) {
        traverse_nodes_post_order(head, f);
        return;
    }

    // executes a function for every element of the tree (BFS)
    void traverse_bfs_order(void (*f)(const T&)) {
        if (head == nullptr) return;

        Queue<TreeNode*> q;

        q.enqueue(head);
        while (!q.is_empty()) {
            TreeNode* current = q.dequeue();
            f(current->data);
            if (current->left) q.enqueue(current->left);
            if (current->right) q.enqueue(current->right);
        }
        return;
    }
};

#endif