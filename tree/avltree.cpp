#include "avltree.h"

void AVLTree::insert(const Filme& info){
    if (root == nullptr) {
        root = new Node {info, 0, nullptr, nullptr, nullptr};
        _size++;
        return;
    }
    Node *n = root, *parent;

    while (true) {
        parent = n;

        bool goLeft = n->info > info;
        n = goLeft ? n->left : n->right;

        if (n == nullptr) {
            goLeft ? parent->left = new Node {info, 0, nullptr, nullptr, parent} :
                     parent->right = new Node {info, 0, nullptr, nullptr, parent};

            rebalance(parent);
            break;
        }
    }
    _size++;
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
            parent->left == n ? parent->left = child : parent->right = child;
            rebalance(parent);
        }
    }
    _size--;
}

AVLTree::Node* AVLTree::rotate_left(Node *a){
    Node *b = a->right;
    b->parent = a->parent;
    a->right = b->left;

    if (a->right != nullptr)
        a->right->parent = a;

    b->left = a;
    a->parent = b;

    if (b->parent != nullptr)
        b->parent->right == a ? b->parent->right = b : b->parent->left = b;

    setBalance(a);
    setBalance(b);
    _rotate_left++;
    return b;
}

AVLTree::Node* AVLTree::rotate_right(Node *a){
    Node *b = a->left;
    b->parent = a->parent;
    a->left = b->right;

    if (a->left != nullptr)
        a->left->parent = a;

    b->right = a;
    a->parent = b;

    if (b->parent != nullptr)
        b->parent->right == a ? b->parent->right = b : b->parent->left = b;

    setBalance(a);
    setBalance(b);
    _rotate_right++;
    return b;
}

AVLTree::Node* AVLTree::rotate_left_right(Node *n){
    n->left = rotate_left(n->left);
    return rotate_right(n);
}

AVLTree::Node* AVLTree::rotate_right_left(Node *n){
    n->right = rotate_right(n->right);
    return rotate_left(n);
}

void AVLTree::rebalance(Node *n){
    setBalance(n);

    if (n->balance == -2)
        n = height(n->left->left) >= height(n->left->right) ? rotate_right(n) : rotate_left_right(n);
    else if (n->balance == 2)
       n = height(n->right->right) >= height(n->right->left) ? rotate_left(n) : rotate_right_left(n);

    if (n->parent != nullptr)
        rebalance(n->parent);
    else
        root = n;
    
    _rebalance++;
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
    while(root != nullptr)
        deleteKey(root->info);

    _rotate_left = 0;
    _rotate_right = 0;
    _rebalance = 0;
    _size = 0;
}

Filme AVLTree::search(const char* titulo) {
    string aux(titulo);
    return search_filme(root, aux);
}

Filme AVLTree::search_filme(Node *node, string titulo) {
    if (node == nullptr)
        return Filme("NULL", -1, 0, "NULL", "NULL", 0);

    if(node->info.get_titulo() == titulo)
        return node->info;

    return titulo < node->info.get_titulo() ? search_filme(node->left, titulo) :
        search_filme(node->right, titulo);
}
