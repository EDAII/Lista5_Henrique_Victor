#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include "avltree.h"
#include "rbtree.h"
#include "filme.h"

class Window : public QWidget {
public:
    explicit Window(QWidget *parent = nullptr);

private:
    AVLTree avl;
    RBTree rb;

private slots:
    void random_avl();
    void random_rb();
    void insert_avl();
    void insert_rb();
    void remove_avl();
    void remove_rb();
    void search_avl();
    void search_rb();
    void data_avl();
    void data_rb();
    void comp_perf();
    void comp_ins();
    void comp_rmv();
    void comp_search();
};

#endif // WINDOW_H
