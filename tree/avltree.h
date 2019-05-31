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

    int _rotate_left = 0;
    int _rotate_right = 0;
    int _rebalance = 0;
    int _size = 0;

private:
    Node *root;
    Node* rotateLeft(Node *a);
    Node* rotateRight(Node *a);
    Node* rotateLeftThenRight(Node *n);
    Node* rotateRightThenLeft(Node *n);
    void rebalance(Node *n);
    int height(Node *n);
    void setBalance(Node *n);
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
