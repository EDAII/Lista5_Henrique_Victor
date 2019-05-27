#include "avltree.h"

void AVLTree::insert(const Filme& info){
    if (root == nullptr) {
        root = new Node {info, 0, nullptr, nullptr, nullptr};
        return;
    }
    Node *n = root, *parent;

    while (true) {
        parent = n;

        bool goLeft = n->info > info;
        n = goLeft ? n->left : n->right;

        if (n == nullptr) {
            if (goLeft)
                parent->left = new Node {info, 0, nullptr, nullptr, parent};
            else
                parent->right = new Node {info, 0, nullptr, nullptr, parent};

            rebalance(parent);
            break;
        }
    }
}

void AVLTree::deleteKey(const Filme& delKey){
    if (root == nullptr)
        return;

    Node *n = root, *parent = root, *delNode = nullptr, *child = root;

    while (child != nullptr) {
        parent = n;
        n = child;
        child = delKey >= n->info ? n->right : n->left;
        if (delKey == n->info)
            delNode = n;
    }

    if (delNode != nullptr) {
        delNode->info = n->info;

        child = n->left != nullptr ? n->left : n->right;

        if (root->info == delKey)
            root = child;

        else {
            if (parent->left == n)
                parent->left = child;
            else
                parent->right = child;

            rebalance(parent);
        }
    }
}

AVLTree::Node* AVLTree::rotateLeft(Node *a){
    Node *b = a->right;
    b->parent = a->parent;
    a->right = b->left;

    if (a->right != nullptr)
        a->right->parent = a;

    b->left = a;
    a->parent = b;

    if (b->parent != nullptr) {
        if (b->parent->right == a)
            b->parent->right = b;
        else
            b->parent->left = b;
    }

    setBalance(a);
    setBalance(b);
    return b;
}

AVLTree::Node* AVLTree::rotateRight(Node *a){
    Node *b = a->left;
    b->parent = a->parent;
    a->left = b->right;

    if (a->left != nullptr)
        a->left->parent = a;

    b->right = a;
    a->parent = b;

    if (b->parent != nullptr) {
        if (b->parent->right == a)
            b->parent->right = b;
        else
            b->parent->left = b;
    }

    setBalance(a);
    setBalance(b);
    return b;
}

AVLTree::Node* AVLTree::rotateLeftThenRight(Node *n){
    n->left = rotateLeft(n->left);
    return rotateRight(n);
}

AVLTree::Node* AVLTree::rotateRightThenLeft(Node *n){
    n->right = rotateRight(n->right);
    return rotateLeft(n);
}

void AVLTree::rebalance(Node *n){
    setBalance(n);

    if (n->balance == -2) {
        if (height(n->left->left) >= height(n->left->right))
            n = rotateRight(n);
        else
            n = rotateLeftThenRight(n);
    }
    else if (n->balance == 2) {
       if (height(n->right->right) >= height(n->right->left))
            n = rotateLeft(n);
        else
            n = rotateRightThenLeft(n);
    }

    if (n->parent != nullptr)
        rebalance(n->parent);
    else
        root = n;
}

int AVLTree::height(Node *n){
    if (n == nullptr)
        return -1;

    return 1 + max(height(n->left), height(n->right));
}

void AVLTree::setBalance(Node *n){
    n->balance = height(n->right) - height(n->left);
}

void AVLTree::clean() {
    clean(root);
}

Filme AVLTree::search(const char* titulo) {
    string aux(titulo);
    return search_filme(root, aux);
}

void AVLTree::clean(Node *node) {
    while(root != nullptr)
        deleteKey(root->info);
}

Filme AVLTree::search_filme(Node *node, string titulo) {
    if (node == nullptr)
        return Filme("NULL", -1, 0, "NULL", "NULL", 0);

    if(node->info.get_titulo() == titulo)
        return node->info;

    return titulo < node->info.get_titulo() ? search_filme(node->left, titulo) :
        search_filme(node->right, titulo);
}
