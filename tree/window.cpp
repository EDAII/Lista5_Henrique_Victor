#include "window.h"
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QFont>

Window::Window(QWidget *parent) : QWidget(parent) {
    int button_size = 300;
    int maximum_label_height = 30;
    QFont buttonFont("Times", 20);
    QFont labelFont("Times", 20, QFont::Bold);

    QVBoxLayout *tela = new QVBoxLayout(this);
    QGridLayout *arvores = new QGridLayout();
    QGridLayout *geral = new QGridLayout();

    /*
     *                        ÁRVORE AVL
     */

    QLabel *AVL_label = new QLabel("Árvore AVL", this);
    arvores->addWidget(AVL_label, 0, 0);
    AVL_label->setAlignment(Qt::AlignCenter);
    AVL_label->setMaximumHeight(maximum_label_height);
    AVL_label->setFont(labelFont);

    QPushButton *random_AVLTree = new QPushButton("Gerar Aleatoriamente", this);
    random_AVLTree->setFixedWidth(button_size);
    random_AVLTree->setFont(buttonFont);
    connect(random_AVLTree, &QPushButton::clicked, this, &Window::random_avl);
    arvores->addWidget(random_AVLTree, 1, 0);

    QPushButton *insert_at_AVL = new QPushButton("Inserir Filme", this);
    insert_at_AVL->setFixedWidth(button_size);
    insert_at_AVL->setFont(buttonFont);
    connect(insert_at_AVL, &QPushButton::clicked, this, &Window::insert_avl);
    arvores->addWidget(insert_at_AVL, 2, 0);

    QPushButton *remove_at_AVL = new QPushButton("Remover Filme", this);
    remove_at_AVL->setFixedWidth(button_size);
    remove_at_AVL->setFont(buttonFont);
    connect(remove_at_AVL, &QPushButton::clicked, this, &Window::remove_avl);
    arvores->addWidget(remove_at_AVL, 3, 0);

    QPushButton *search_at_AVL = new QPushButton("Buscar Filme", this);
    search_at_AVL->setFixedWidth(button_size);
    search_at_AVL->setFont(buttonFont);
    connect(search_at_AVL, &QPushButton::clicked, this, &Window::search_avl);
    arvores->addWidget(search_at_AVL, 4, 0);

    QPushButton *AVL_data = new QPushButton("Dados da Árvore", this);
    AVL_data->setFixedWidth(button_size);
    AVL_data->setFont(buttonFont);
    connect(AVL_data, &QPushButton::clicked, this, &Window::data_avl);
    arvores->addWidget(AVL_data, 5, 0);

    /*
     *                        ÁRVORE RED-BLACK
     */

    QLabel *RB_label = new QLabel("Árvore Red-Black", this);
    arvores->addWidget(RB_label, 0, 1);
    RB_label->setAlignment(Qt::AlignCenter);
    RB_label->setMaximumHeight(maximum_label_height);
    RB_label->setFont(labelFont);

    QPushButton *random_RBTree = new QPushButton("Gerar Aleatoriamente", this);
    random_RBTree->setFixedWidth(button_size);
    random_RBTree->setFont(buttonFont);
    connect(random_RBTree, &QPushButton::clicked, this, &Window::random_rb);
    arvores->addWidget(random_RBTree, 1, 1);

    QPushButton *insert_at_RB = new QPushButton("Inserir Filme", this);
    insert_at_RB->setFixedWidth(button_size);
    insert_at_RB->setFont(buttonFont);
    connect(insert_at_RB, &QPushButton::clicked, this, &Window::insert_rb);
    arvores->addWidget(insert_at_RB, 2, 1);

    QPushButton *remove_at_RB = new QPushButton("Remover Filme", this);
    remove_at_RB->setFixedWidth(button_size);
    remove_at_RB->setFont(buttonFont);
    connect(remove_at_RB, &QPushButton::clicked, this, &Window::remove_rb);
    arvores->addWidget(remove_at_RB, 3, 1);

    QPushButton *search_at_RB = new QPushButton("Buscar Filme", this);
    search_at_RB->setFixedWidth(button_size);
    search_at_RB->setFont(buttonFont);
    connect(search_at_RB, &QPushButton::clicked, this, &Window::search_rb);
    arvores->addWidget(search_at_RB, 4, 1);

    QPushButton *RB_data = new QPushButton("Dados da Árvore", this);
    RB_data->setFixedWidth(button_size);
    RB_data->setFont(buttonFont);
    connect(RB_data, &QPushButton::clicked, this, &Window::data_rb);
    arvores->addWidget(RB_data, 5, 1);

    /*
     *                        GERAL
     */

    QLabel *general_label = new QLabel("Geral", this);
    geral->addWidget(general_label, 0, 0);
    general_label->setAlignment(Qt::AlignCenter);
    general_label->setMaximumHeight(maximum_label_height);
    general_label->setFont(labelFont);

    QPushButton *compare_performance = new QPushButton("Comparar Performance", this);
    connect(compare_performance, &QPushButton::clicked, this, &Window::comp_perf);
    geral->addWidget(compare_performance, 1, 0);
    compare_performance->setFixedWidth(button_size);
    compare_performance->setFont(buttonFont);

    QPushButton *compare_insertions = new QPushButton("Comparar Inserções", this);
    connect(compare_insertions, &QPushButton::clicked, this, &Window::comp_ins);
    geral->addWidget(compare_insertions, 2, 0);
    compare_insertions->setFixedWidth(button_size);
    compare_insertions->setFont(buttonFont);

    QPushButton *compare_removals = new QPushButton("Comparar Remoções", this);
    connect(compare_removals, &QPushButton::clicked, this, &Window::comp_rmv);
    geral->addWidget(compare_removals, 3, 0);
    compare_removals->setFixedWidth(button_size);
    compare_removals->setFont(buttonFont);

    QPushButton *compare_searchs = new QPushButton("Comparar Buscas", this);
    connect(compare_searchs, &QPushButton::clicked, this, &Window::comp_search);
    geral->addWidget(compare_searchs, 4, 0);
    compare_searchs->setFixedWidth(button_size);
    compare_searchs->setFont(buttonFont);

    tela->addLayout(arvores);
    tela->addLayout(geral);
    setLayout(tela);
}

void Window::random_avl() {

}

void Window::random_rb() {

}

void Window::insert_avl() {

}

void Window::insert_rb() {

}

void Window::remove_avl() {

}

void Window::remove_rb() {

}

void Window::search_avl() {

}

void Window::search_rb() {

}

void Window::data_avl() {

}

void Window::data_rb() {

}

void Window::comp_perf() {

}

void Window::comp_ins() {

}

void Window::comp_rmv() {

}

void Window::comp_search() {

}
