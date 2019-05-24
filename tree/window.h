#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QProgressBar>
#include "avltree.h"
#include "rbtree.h"
#include "filme.h"
#include "dados.h"

class Window : public QWidget {
public:
    explicit Window(QWidget *parent = nullptr);

private:
    AVLTree avl;
    RBTree rb;
    int quantidade;
    QProgressBar *progressBar;

private slots:
    void random_avl();
    void random_rb();
    void random_tree(int opcao);
    void gerar_avl_aleat();
    void gerar_rb_aleat();
    void insert_avl();
    void insert_rb();
    void remove_avl();
    void remove_rb();
    void search_avl();
    void search_rb();
    void data_avl();
    void data_rb();
    void print_avl();
    void print_rb();
    void comp_perf();
    void comp_ins();
    void comp_rmv();
    void comp_search();
};

#endif // WINDOW_H
