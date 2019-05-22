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


    QHBoxLayout *tela = new QHBoxLayout(this);
    QVBoxLayout *grid_avl = new QVBoxLayout();
    QVBoxLayout *grid_rb = new QVBoxLayout();

    /*
     *                        ÁRVORE AVL
     */

    QLabel *AVL_label = new QLabel("Árvore AVL", this);
    grid_avl->addWidget(AVL_label);
    AVL_label->setAlignment(Qt::AlignCenter);
    AVL_label->setMaximumHeight(maximum_label_height);
    AVL_label->setFont(labelFont);

    QPushButton *random_AVLTree = new QPushButton("Gerar Aleatoriamente", this);
    random_AVLTree->setFixedWidth(button_size);
    random_AVLTree->setFont(buttonFont);
    //connect(random_AVLTree, &QPushButton::clicked, this, &Window::???);
    grid_avl->addWidget(random_AVLTree);

    QPushButton *insert_at_AVL = new QPushButton("Inserir Filme", this);
    insert_at_AVL->setFixedWidth(button_size);
    insert_at_AVL->setFont(buttonFont);
    //connect(insert_at_AVL, &QPushButton::clicked, this, &Window::???);
    grid_avl->addWidget(insert_at_AVL);

    QPushButton *remove_at_AVL = new QPushButton("Remover Filme", this);
    remove_at_AVL->setFixedWidth(button_size);
    remove_at_AVL->setFont(buttonFont);
    //connect(remove_at_AVL, &QPushButton::clicked, this, &Window::???);
    grid_avl->addWidget(remove_at_AVL);

    QPushButton *search_at_AVL = new QPushButton("Buscar Filme", this);
    search_at_AVL->setFixedWidth(button_size);
    search_at_AVL->setFont(buttonFont);
    //connect(search_at_AVL, &QPushButton::clicked, this, &Window::???);
    grid_avl->addWidget(search_at_AVL);

    QPushButton *AVL_data = new QPushButton("Dados da Árvore", this);
    AVL_data->setFixedWidth(button_size);
    AVL_data->setFont(buttonFont);
    //connect(AVL_data, &QPushButton::clicked, this, &Window::???);
    grid_avl->addWidget(AVL_data);

    /*
     *                        ÁRVORE RED-BLACK
     */

    QLabel *RB_label = new QLabel("Árvore Red-Black", this);
    grid_rb->addWidget(RB_label);
    RB_label->setAlignment(Qt::AlignCenter);
    RB_label->setMaximumHeight(maximum_label_height);
    RB_label->setFont(labelFont);

    QPushButton *random_RBTree = new QPushButton("Gerar Aleatoriamente", this);
    random_RBTree->setFixedWidth(button_size);
    random_RBTree->setFont(buttonFont);
    //connect(random_RBTree, &QPushButton::clicked, this, &Window::???);
    grid_rb->addWidget(random_RBTree);

    QPushButton *insert_at_RB = new QPushButton("Inserir Filme", this);
    insert_at_RB->setFixedWidth(button_size);
    insert_at_RB->setFont(buttonFont);
    //connect(insert_at_RB, &QPushButton::clicked, this, &Window::???);
    grid_rb->addWidget(insert_at_RB);

    QPushButton *remove_at_RB = new QPushButton("Remover Filme", this);
    remove_at_RB->setFixedWidth(button_size);
    remove_at_RB->setFont(buttonFont);
    //connect(remove_at_RB, &QPushButton::clicked, this, &Window::???);
    grid_rb->addWidget(remove_at_RB);

    QPushButton *search_at_RB = new QPushButton("Buscar Filme", this);
    search_at_RB->setFixedWidth(button_size);
    search_at_RB->setFont(buttonFont);
    //connect(search_at_RB, &QPushButton::clicked, this, &Window::???);
    grid_rb->addWidget(search_at_RB);

    QPushButton *RB_data = new QPushButton("Dados da Árvore", this);
    RB_data->setFixedWidth(button_size);
    RB_data->setFont(buttonFont);
    //connect(RB_data, &QPushButton::clicked, this, &Window::???);
    grid_rb->addWidget(RB_data);

    /*
     *                        GERAL
     */

    //QLabel *general_label = new QLabel("Geral", this);
    //???->addWidget(general_label, ?, ?);
    //general_label->setAlignment(Qt::AlignCenter);

    //QPushButton *compare_performance = new QPushButton("Comparar Performance", this);
    //connect(compare_performance, &QPushButton::clicked, this, &Window::???);
    //???->addWidget(compare_performance, ?, ?);

    //QPushButton *compare_insertions = new QPushButton("Comparar Inserções", this);
    //connect(compare_insertions, &QPushButton::clicked, this, &Window::???);
    //???->addWidget(compare_insertions, ?, ?);

    //QPushButton *compare_removals = new QPushButton("Comparar Remoções", this);
    //connect(compare_removals, &QPushButton::clicked, this, &Window::???);
    //???->addWidget(compare_removals, ?, ?);

    //QPushButton *compare_searchs = new QPushButton("Comparar Buscas", this);
    //connect(compare_searchs, &QPushButton::clicked, this, &Window::???);
    //???->addWidget(compare_searchs, ?, ?);

    tela->addSpacing(10);
    tela->addLayout(grid_avl);
    tela->addLayout(grid_rb);
    setLayout(tela);
}
