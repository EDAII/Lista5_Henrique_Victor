#include "rbtree.h"

void RBTree::rotate_left(Node *G, Node *P, Node *C) {
    if (G != nullptr)
        G->left == P ? G->left = C : G->right = C;

    P->right = C->left;
    C->left = P;

    C->parent = G;
    P->parent = C;

    if (P->right)
        P->right->parent = P;
}
void RBTree::rotate_right(Node *G, Node *P, Node *C) {
    if (G != nullptr)
        G->left == P ? G->left = C : G->right = C;

    P->left = C->right;
    C->right = P;

    C->parent = G;
    P->parent = C;

    if (P->left)
        P->left->parent = P;
}

void RBTree::insert(const Filme& info) {
    auto node = insert(&root, nullptr, info);
    restore_properties(node);
}

RBTree::Node * RBTree::insert(Node **node, Node *parent, const Filme& info) {
    if (*node == nullptr) {
        *node = new Node { info, Node::RED, nullptr, nullptr, parent };
        return *node;
    }

    if ((*node)->info == info)
        return *node;
    else if (info < (*node)->info)
        return insert(&(*node)->left, *node, info);
    else
        return insert(&(*node)->right, *node, info);
}

void RBTree::restore_properties(Node *node) {
    // Caso 1 - node é a raíz
    if (parent(node) == nullptr)
        node->color = Node::BLACK;

    else if (parent(node)->color == Node::BLACK) // Caso 2 (não é necessário nenhuma operação)
        return;
    else if (uncle(node) and uncle(node)->color == Node::RED) {
        // Caso 3 - pai e tio vermelhos
        parent(node)->color = Node::BLACK;
        uncle(node)->color = Node::BLACK;
        grandparent(node)->color = Node::RED;
        restore_properties(grandparent(node));
    }
    else {
        // Caso 4 - pai vermelho, tio preto
        auto C = node;
        auto P = parent(node);
        auto G = grandparent(node);

        if (C == P->right and P == G->left) {
            rotate_left(G, P, C);
            P = C;
        }
        else if (node == P->left and P == G->right) {
            rotate_right(G, P, C);
            P = C;
        }

        C = P;
        P = G;
        G = parent(P);

        if (C == P->left)
            rotate_right(G, P, C);
        else
            rotate_left(G, P, C);

        if (G == nullptr)
            root = C;

        C->color = Node::BLACK;
        P->color = Node::RED;
    }
}

RBTree::Node * RBTree::find(Node *node, const Filme& info) {
    if (node == nullptr or node->info == info)
        return node;

    return info < node->info ? find(node->left, info) :
        find(node->right, info);
}

RBTree::Node * RBTree::swap_info(Node *N) {
    auto D = N->left;
    while (D->right)
        D = D->right;

    swap(N->info, D->info);
    return D;
}

void RBTree::swap_nodes(Node *N, Node *C) {
    auto P = parent(N);

    if (C)
        C->parent = P;

    if (P == nullptr)
        root = C;
    else if (P->left == N)
        P->left = C;
    else
        P->right = C;
}

bool RBTree::erase(const Filme& info) {
    Node *N = find(root, info);

    if (N == nullptr)
        return false;

    if (N->left and N->right)
        N = swap_info(N);

    erase(N);

    return true;
}

void RBTree::erase(Node *N) {
    auto P = parent(N);
    auto S = sibling(N);
    auto C = N->left ? N->left : N->right;

    swap_nodes(N, C);

    if (N->color == Node::BLACK) {
        if (C and C->color == Node::RED)
            C->color = Node::BLACK;
        else
            rebalancing(P, S, C);
    }

    delete N;
}

void RBTree::rebalancing(Node *P, Node *S, Node *N) {
    if (P == nullptr)
        return;

    if (S and S->color == Node::RED) {
        P->color = Node::RED;
        S->color = Node::BLACK;

        if (N == P->left)
            rotate_left(grandparent(S), P, S);
        else
            rotate_right(grandparent(S), P, S);

        if (parent(S) == nullptr)
            root = S;

        S = P->left == N ? P->right : P->left;
    }

    if (P and P->color == Node::BLACK and S->color == Node::BLACK
    and (S->left == nullptr or S->left->color == Node::BLACK)
    and (S->right == nullptr or S->right->color == Node::BLACK)) {
        S->color = Node::RED;
        return rebalancing(parent(P), sibling(P), P);
    }

    if (P and P->color == Node::RED and S->color == Node::BLACK
    and (S->left == nullptr or S->left->color == Node::BLACK)
    and (S->right == nullptr or S->right->color == Node::BLACK)) {
        S->color = Node::RED;
        P->color = Node::BLACK;
        return;
    }

    if (S and S->color == Node::BLACK) {
        if (P and P->left == N
        and (S->left or S->left->color == Node::RED) and
        (S->right == nullptr or S->right->color == Node::BLACK)) {
            S->color = Node::RED;
            S->left->color = Node::BLACK;
            rotate_right(P, S, S->left);
            S = P->right;
        }
        else if (P and P->right == N
        and (S->left == nullptr or S->left->color == Node::BLACK)
        and (S->right or S->right->color == Node::RED)) {
            S->color = Node::RED;
            S->right->color = Node::BLACK;
            rotate_left(P, S, S->right);
            S = P->left;
        }
    }

    S->color = P->color;
    P->color = Node::BLACK;

    if (N == P->left) {
        S->right->color = Node::BLACK;
        rotate_left(grandparent(P), P, S);
    }
    else {
        S->left->color = Node::BLACK;
        rotate_right(grandparent(P), P, S);
    }

    if (parent(S) == nullptr)
        root = S;
}

void RBTree::clean() {
    clean(root);
}

void RBTree::clean(Node *node) {
    if(node != nullptr) {
        if(node->left != nullptr)
            clean(node->left);

        if(node->right != nullptr)
            clean(node->right);

        delete node;
    }
}

Filme RBTree::search(const char* titulo) {
    string aux(titulo);
    return search_filme(root, aux);
}

Filme RBTree::search_filme(Node *node, string titulo) {
    if (node == nullptr)
        return Filme("NULL", -1, 0, "NULL", "NULL", 0);

    if(node->info.get_titulo() == titulo)
        return node->info;

    return titulo < node->info.get_titulo() ? search_filme(node->left, titulo) :
        search_filme(node->right, titulo);
}
