#ifndef RBTREE_H
#define RBTREE_H

#include "filme.h"

class RBTree {
public:
    struct Node {
        Filme info;
        enum { RED, BLACK } color;
        Node *left, *right, *parent;
    };

    int _rotate_left = 0;
    int _rotate_right = 0;
    int _rebalance = 0;
    int _size = 0;
    int _restore_properties = 0;
    int _swap_info = 0;
    int _swap_node = 0;

private:
    Node *root;

    Node * parent(Node *node) { return node ? node->parent : nullptr; }
    Node * grandparent(Node* node) { return parent(parent(node)); }
    Node * sibling(Node* node) { auto p = parent(node); return p ? (node == p->left ? p->right : p->left) : nullptr; }
    Node * uncle(Node* node) { return sibling(parent(node)); }
    void rotate_left(Node *G, Node *P, Node *C);
    void rotate_right(Node *G, Node *P, Node *C);
    Node * insert(Node **node, Node *parent, const Filme& info);
    void restore_properties(Node *node);
    Node * find(Node *node, const Filme& info);
    Node * swap_info(Node *N);
    void swap_nodes(Node *N, Node *C);
    void erase(Node *N);
    void rebalancing(Node *P, Node *S, Node *N);
    Filme search_filme(Node *node, string titulo);

public:
    RBTree() : root(nullptr) {}
    void insert(const Filme& info);
    bool erase(const Filme& info);
    void clean();
    Filme search(const char* titulo);
    Node* get_root() { return root; }
};

#endif // RBTREE_H
