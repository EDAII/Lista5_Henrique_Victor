#ifndef AVLTREE_H
#define AVLTREE_H

#include "filme.h"

class AVLTree {
public:
    struct Node {
        Filme info;
        int balance;
        Node *left, *right, *parent;
    };

private:
    Node *root;
    Node* rotateLeft(Node *a);
    Node* rotateRight(Node *a);
    Node* rotateLeftThenRight(Node *n);
    Node* rotateRightThenLeft(Node *n);
    void rebalance(Node *n);
    int height(Node *n);
    void setBalance(Node *n);
    void clean(Node *node);
    Filme search_filme(Node *node, string titulo);

public:
    AVLTree() : root(nullptr) {}
    void insert(const Filme& key);
    void deleteKey(const Filme& key);
    void clean();
    Filme search(const char* titulo);
    Node* get_root() { return root; }
};

#endif // AVLTREE_H
