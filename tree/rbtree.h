#ifndef RBTREE_H
#define RBTREE_H

#include "filme.h"


class RBTree {
public:
    RBTree() : root(nullptr) {}
    void insert(const Filme& info);
    bool erase(const Filme& info);
    void clean();
    Filme search(const char* titulo);

private:
    struct Node {
        Filme info;
        enum { RED, BLACK } color;
        Node *left, *right, *parent;
    };

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
    void clean(Node *node);
    Filme search_filme(Node *node, string titulo);
};

#endif // RBTREE_H
