#include "window.h"
#include <QPushButton>
#include <QGridLayout>
#include <QFont>
#include <QEventLoop>
#include <ctime>
#include <QGroupBox>
#include <QFormLayout>
#include <QValidator>
#include <QMessageBox>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

using namespace std;

QLabel *Window::AVL_ins_time = nullptr;
QLabel *Window::AVL_searchs_time = nullptr;
QLabel *Window::AVL_rmv_time = nullptr;
QLabel *Window::RB_ins_time = nullptr;
QLabel *Window::RB_searchs_time = nullptr;
QLabel *Window::RB_rmv_time = nullptr;
QLineEdit *Window::campo_comp = nullptr;

Window::Window(QWidget *parent) : QWidget(parent) {
    avl = AVLTree();
    rb = RBTree();

    int button_size = 300;
    int maximum_label_height = 30;
    QFont buttonFont("Times", 20);
    QFont labelFont("Times", 20, QFont::Bold);

    QVBoxLayout *tela = new QVBoxLayout(this);
    QGridLayout *arvores = new QGridLayout();
    QGridLayout *geral = new QGridLayout();

    campo_quantidade = new QLineEdit();
    campo_quantidade->setValidator(new QIntValidator());
    campo_titulo = new QLineEdit();
    campo_ano = new QLineEdit();
    campo_ano->setValidator(new QIntValidator(1920, 2019));
    campo_bilheteria = new QLineEdit();
    campo_bilheteria->setValidator(new QIntValidator());
    campo_diretor = new QLineEdit();
    campo_pais = new QLineEdit();
    campo_duracao = new QLineEdit();
    campo_duracao->setValidator(new QIntValidator(0, 180));
    alert = new QLabel();

    limpar_todos_campos();

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

    QPushButton *all_movies_AVL = new QPushButton("Lista dos Filmes", this);
    all_movies_AVL->setFixedWidth(button_size);
    all_movies_AVL->setFont(buttonFont);
    connect(all_movies_AVL, &QPushButton::clicked, this, &Window::list_avl);
    arvores->addWidget(all_movies_AVL, 5, 0);

    QPushButton *AVL_data = new QPushButton("Dados da Árvore", this);
    AVL_data->setFixedWidth(button_size);
    AVL_data->setFont(buttonFont);
    connect(AVL_data, &QPushButton::clicked, this, &Window::data_avl);
    arvores->addWidget(AVL_data, 6, 0);

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

    QPushButton *all_movies_RB = new QPushButton("Lista dos Filmes", this);
    all_movies_RB->setFixedWidth(button_size);
    all_movies_RB->setFont(buttonFont);
    connect(all_movies_RB, &QPushButton::clicked, this, &Window::list_rb);
    arvores->addWidget(all_movies_RB, 5, 1);

    QPushButton *RB_data = new QPushButton("Dados da Árvore", this);
    RB_data->setFixedWidth(button_size);
    RB_data->setFont(buttonFont);
    connect(RB_data, &QPushButton::clicked, this, &Window::data_rb);
    arvores->addWidget(RB_data, 6, 1);

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

    QGroupBox *group_arv = new QGroupBox(this);
    QGroupBox *group_geral = new QGroupBox(this);

    group_arv->setLayout(arvores);
    group_geral->setLayout(geral);

    tela->addWidget(group_arv);
    tela->addWidget(group_geral);
    setLayout(tela);
}

void Window::random_tree(int opcao) {
    QFont buttonFont("Times", 20);
    QFont labelFont("Times", 20, QFont::Bold);
    QFont campoFont("Times", 20);
    int button_size = 480;
    int maximum_label_height = 30;

    campo_quantidade->setText("");
    campo_quantidade->setFont(campoFont);

    new_window = new QWidget(nullptr);
    new_window->setFixedSize(500, 300);

    QVBoxLayout *tela = new QVBoxLayout();

    QLabel *label = new QLabel("Insira a quantidade de filmes");
    label->setAlignment(Qt::AlignCenter);
    label->setMaximumHeight(maximum_label_height);
    label->setFont(labelFont);

    QPushButton *button = new QPushButton("Gerar");
    button->setFixedWidth(button_size);
    button->setFont(buttonFont);

    alert = new QLabel("");
    alert->setAlignment(Qt::AlignCenter);
    alert->setMaximumHeight(15);

    progressBar = new QProgressBar();
    progressBar->setFixedHeight(40);

    if(!opcao) { // AVL
        new_window->setWindowTitle("Gerar Árvore AVL Aleatória");
        connect(button, &QPushButton::clicked, this, &Window::gerar_avl_aleat);
    }
    else { // RB
        new_window->setWindowTitle("Gerar Árvore RB Aleatória");
        connect(button, &QPushButton::clicked, this, &Window::gerar_rb_aleat);
    }

    tela->addWidget(label);
    tela->addWidget(campo_quantidade);
    tela->addWidget(button);
    tela->addWidget(progressBar);
    tela->addWidget(alert);
    new_window->setLayout(tela);
    new_window->show();

    QEventLoop loop;
    connect(this, SIGNAL(destroyed()), & loop, SLOT(quit()));
    loop.exec();

    quantidade = 0;
}

void Window::gerar_avl_aleat() {
    srand(time(0));
    get_quantidade();

    if(!quantidade) {
        alert->setText("Numero deve ser maior que 0");
        return;
    }

    alert->setText("");

    progressBar->setMinimum(0);
    progressBar->setMaximum(quantidade);

    avl.clean();

    for(int i = 0; i < quantidade; ++i) {
        avl.insert(Filme(filmes[rand() % quant_filmes],
                   1920 + (rand() % 100),
                   rand() % 4000000001,
                   diretores[rand() % quant_diretores],
                   paises[rand() % quant_paises],
                   rand() % 181));
        progressBar->setValue(i+1);
    }

    campo_quantidade->setText("");
    new_window->close();
}

void Window::gerar_rb_aleat() {
    srand(time(0));
    get_quantidade();

    if(!quantidade) {
        alert->setText("Numero deve ser maior que 0");
        return;
    }

    alert->setText("");

    progressBar->setMinimum(0);
    progressBar->setMaximum(quantidade);

    rb.clean();

    for(int i = 0; i < quantidade; ++i) {
        rb.insert(Filme(filmes[rand() % quant_filmes],
                  1920 + (rand() % 100),
                  rand() % 4000000001,
                  diretores[rand() % quant_diretores],
                  paises[rand() % quant_paises],
                  rand() % 181));
        progressBar->setValue(i+1);
    }

    campo_quantidade->setText("");
    new_window->close();
}

void Window::insert(int opcao) {
    new_window = new QWidget(nullptr);
    new_window->setFixedSize(500, 400);
    QFont buttonFont("Times", 20);
    int button_size = 350;
    limpar_todos_campos();

    QFont labelFont("Times", 20, QFont::Bold);
    QFont campoFont("Times", 20);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);

    QLabel *main_label = new QLabel("Insira os dados do filme");
    main_label->setFont(labelFont);
    main_label->setAlignment(Qt::AlignCenter);
    QLabel *label_titulo = new QLabel("Título:");
    label_titulo->setFont(labelFont);
    QLabel *label_ano = new QLabel("Ano:");
    label_ano->setFont(labelFont);
    QLabel *label_bilheteria = new QLabel("Bilheteria:");
    label_bilheteria->setFont(labelFont);
    QLabel *label_diretor = new QLabel("Diretor:");
    label_diretor->setFont(labelFont);
    QLabel *label_pais = new QLabel("País:");
    label_pais->setFont(labelFont);
    QLabel *label_duracao = new QLabel("Duração:");
    label_duracao->setFont(labelFont);

    campo_titulo->setFont(campoFont);
    campo_ano->setFont(campoFont);
    campo_bilheteria->setFont(campoFont);
    campo_diretor->setFont(campoFont);
    campo_pais->setFont(campoFont);
    campo_duracao->setFont(campoFont);

    formLayout->addWidget(main_label);
    formLayout->addRow(label_titulo, campo_titulo);
    formLayout->addRow(label_ano, campo_ano);
    formLayout->addRow(label_bilheteria, campo_bilheteria);
    formLayout->addRow(label_diretor, campo_diretor);
    formLayout->addRow(label_pais, campo_pais);
    formLayout->addRow(label_duracao, campo_duracao);

    QPushButton *button = new QPushButton("Enviar");
    button->setFixedWidth(button_size);
    button->setFont(buttonFont);

    if(!opcao) { // AVL
        new_window->setWindowTitle("Inserir filme na AVL");
        connect(button, &QPushButton::clicked, this, &Window::inserir_filme_avl);
    }
    else { // RB
        new_window->setWindowTitle("Inserir filme na Red-Black");
        connect(button, &QPushButton::clicked, this, &Window::inserir_filme_rb);
    }

    alert = new QLabel("");
    alert->setAlignment(Qt::AlignCenter);
    alert->setMaximumHeight(20);

    formLayout->addWidget(button);
    formLayout->addWidget(alert);

    new_window->setLayout(formLayout);
    new_window->show();

    QEventLoop loop;
    connect(this, SIGNAL(destroyed()), & loop, SLOT(quit()));
    loop.exec();
}

void Window::tela_titulo(int opcao) {
    QFont buttonFont("Times", 20);
    QFont labelFont("Times", 20, QFont::Bold);
    QFont campoFont("Times", 20);
    int button_size = 480;
    int maximum_label_height = 30;

    campo_titulo->setText("");
    campo_titulo->setFont(campoFont);

    new_window = new QWidget(nullptr);
    new_window->setFixedSize(500, 300);

    QVBoxLayout *tela = new QVBoxLayout();

    QLabel *label = new QLabel("Insira o nome do Filme");
    label->setAlignment(Qt::AlignCenter);
    label->setMaximumHeight(maximum_label_height);
    label->setFont(labelFont);

    QPushButton *button = new QPushButton();
    button->setFixedWidth(button_size);
    button->setFont(buttonFont);

    alert = new QLabel("");
    alert->setAlignment(Qt::AlignCenter);
    alert->setMaximumHeight(15);

    if(!opcao) { // Remover na AVL
        new_window->setWindowTitle("Remover Filme na AVL");
        button->setText("Remover");
        connect(button, &QPushButton::clicked, this, &Window::remover_filme_avl);
    }
    else if(opcao == 1) { // Remover na RB
        new_window->setWindowTitle("Remover Filme na Red-Black");
        button->setText("Remover");
        connect(button, &QPushButton::clicked, this, &Window::remover_filme_rb);
    }
    else if(opcao == 2) { // Buscar na AVL
        new_window->setWindowTitle("Buscar Filme na AVL");
        button->setText("Buscar");
        connect(button, &QPushButton::clicked, this, &Window::buscar_filme_avl);
    }
    else { // Buscar na RB
        new_window->setWindowTitle("Buscar Filme na Red-Black");
        button->setText("Buscar");
        connect(button, &QPushButton::clicked, this, &Window::buscar_filme_rb);
    }

    tela->addWidget(label);
    tela->addWidget(campo_titulo);
    tela->addWidget(button);
    tela->addWidget(alert);
    new_window->setLayout(tela);
    new_window->show();

    QEventLoop loop;
    connect(this, SIGNAL(destroyed()), & loop, SLOT(quit()));
    loop.exec();
}

void Window::remover_filme_avl() {
    Filme filme = avl.search(campo_titulo->text().toStdString().c_str());
    if(filme.get_ano() == -1) // Filme não encontrado
        QMessageBox::information(new_window, tr("Aviso"), tr("O filme não foi encontrado"));
    else {
        avl.deleteKey(filme);
        QMessageBox::information(new_window, tr("Aviso"), tr("O filme foi deletado com sucesso"));
        campo_titulo->setText("");
    }
}

void Window::remover_filme_rb() {
    Filme filme = rb.search(campo_titulo->text().toStdString().c_str());
    if(filme.get_ano() == -1) // Filme não encontrado
        QMessageBox::information(new_window, tr("Aviso"), tr("O filme não foi encontrado"));
    else {
        rb.erase(filme);
        QMessageBox::information(new_window, tr("Aviso"), tr("O filme foi deletado com sucesso"));
        campo_titulo->setText("");
    }
}

void Window::buscar_filme_avl() {
    Filme filme = avl.search(campo_titulo->text().toStdString().c_str());
    if(filme.get_ano() == -1) // Filme não encontrado
        QMessageBox::information(new_window, tr("Aviso"), tr("O filme não foi encontrado"));
    else {
        new_window->close();
        mostrar_filme_encontrado(filme);
    }
}

void Window::buscar_filme_rb() {
    Filme filme = rb.search(campo_titulo->text().toStdString().c_str());
    if(filme.get_ano() == -1) // Filme não encontrado
        QMessageBox::information(new_window, tr("Aviso"), tr("O filme não foi encontrado"));
    else {
        new_window->close();
        mostrar_filme_encontrado(filme);
    }
}

void Window::mostrar_filme_encontrado(const Filme& filme) {
    new_window = new QWidget(nullptr);

    QFont labelFont("Times", 20, QFont::Bold);
    int maximum_label_height = 30;

    QGridLayout *layout = new QGridLayout();

    QLabel *label_titulo = new QLabel("Título: ");
    QLabel *label_ano = new QLabel("Ano: ");
    QLabel *label_bilheteria = new QLabel("Bilheteria: ");
    QLabel *label_diretor = new QLabel("Diretor: ");
    QLabel *label_pais = new QLabel("País: ");
    QLabel *label_duracao = new QLabel("Duração: ");

    QLabel *filme_titulo = new QLabel(QString::fromStdString(filme.get_titulo()));
    QLabel *filme_ano = new QLabel(QString::number(filme.get_ano()));

    string bilheteria = to_string(filme.get_bilheteria());

    for(size_t i = bilheteria.size(), j = 0; i > 0; --i, ++j)
        if(!((j+1)%3) && i != 1)
            bilheteria.insert(i-1, ".");

    QLabel *filme_bilheteria = new QLabel("U$ " + QString::fromStdString(bilheteria) + ",00");
    QLabel *filme_diretor = new QLabel(QString::fromStdString(filme.get_diretor()));
    QLabel *filme_pais = new QLabel(QString::fromStdString(filme.get_pais()));
    QLabel *filme_duracao = new QLabel(QString::number(filme.get_duracao()) + " minutos");

    label_titulo->setMaximumHeight(maximum_label_height);
    label_titulo->setFont(labelFont);
    label_ano->setMaximumHeight(maximum_label_height);
    label_ano->setFont(labelFont);
    label_bilheteria->setMaximumHeight(maximum_label_height);
    label_bilheteria->setFont(labelFont);
    label_diretor->setMaximumHeight(maximum_label_height);
    label_diretor->setFont(labelFont);
    label_pais->setMaximumHeight(maximum_label_height);
    label_pais->setFont(labelFont);
    label_duracao->setMaximumHeight(maximum_label_height);
    label_duracao->setFont(labelFont);

    filme_titulo->setMaximumHeight(maximum_label_height);
    filme_titulo->setFont(labelFont);
    filme_ano->setMaximumHeight(maximum_label_height);
    filme_ano->setFont(labelFont);
    filme_bilheteria->setMaximumHeight(maximum_label_height);
    filme_bilheteria->setFont(labelFont);
    filme_diretor->setMaximumHeight(maximum_label_height);
    filme_diretor->setFont(labelFont);
    filme_pais->setMaximumHeight(maximum_label_height);
    filme_pais->setFont(labelFont);
    filme_duracao->setMaximumHeight(maximum_label_height);
    filme_duracao->setFont(labelFont);

    label_titulo->setAlignment(Qt::AlignRight);
    label_ano->setAlignment(Qt::AlignRight);
    label_bilheteria->setAlignment(Qt::AlignRight);
    label_diretor->setAlignment(Qt::AlignRight);
    label_pais->setAlignment(Qt::AlignRight);
    label_duracao->setAlignment(Qt::AlignRight);

    layout->addWidget(label_titulo, 0, 0);
    layout->addWidget(label_ano, 1, 0);
    layout->addWidget(label_bilheteria, 2, 0);
    layout->addWidget(label_diretor, 3, 0);
    layout->addWidget(label_pais, 4, 0);
    layout->addWidget(label_duracao, 5, 0);

    filme_titulo->setAlignment(Qt::AlignLeft);
    filme_ano->setAlignment(Qt::AlignLeft);
    filme_bilheteria->setAlignment(Qt::AlignLeft);
    filme_diretor->setAlignment(Qt::AlignLeft);
    filme_pais->setAlignment(Qt::AlignLeft);
    filme_duracao->setAlignment(Qt::AlignLeft);

    layout->addWidget(filme_titulo, 0, 1);
    layout->addWidget(filme_ano, 1, 1);
    layout->addWidget(filme_bilheteria, 2, 1);
    layout->addWidget(filme_diretor, 3, 1);
    layout->addWidget(filme_pais, 4, 1);
    layout->addWidget(filme_duracao, 5, 1);

    new_window->setWindowTitle("Filme");
    new_window->setLayout(layout);
    new_window->setFixedSize(900, 400);
    new_window->show();

    QEventLoop loop;
    connect(this, SIGNAL(destroyed()), & loop, SLOT(quit()));
    loop.exec();
}

void Window::imprimir_lista(int opcao) {
    QFont font("Times", 15, QFont::Bold);
    new_window = new QWidget(nullptr);
    QVBoxLayout *tela = new QVBoxLayout();

    lista = new QListWidget();
    lista->setFont(font);

    tela->addWidget(lista);
    new_window->setLayout(tela);
    new_window->setFixedSize(650, 330);
    new_window->show();

    if(!opcao) {
        new_window->setWindowTitle("Lista de Filmes na AVL");
        imprimir_avl(avl.get_root());
    }
    else {
        new_window->setWindowTitle("Lista de Filmes na Red-Black");
        imprimir_rb(rb.get_root());
    }

    QEventLoop loop;
    connect(this, SIGNAL(destroyed()), & loop, SLOT(quit()));
    loop.exec();

    lista->clear();
}

void Window::imprimir_avl(AVLTree::Node *f) {
    if(f == nullptr)
        return;

    imprimir_avl(f->left);
    lista->addItem(QString::fromStdString("Título: " + f->info.get_titulo() +
                                          "\nAno: " + to_string(f->info.get_ano()) +
                                          "\nBilheteria: U$" + to_string(f->info.get_bilheteria()) + ",00" +
                                          "\nDiretor: " + f->info.get_diretor() +
                                          "\nPaís: " + f->info.get_pais() +
                                          "\nDuração: " + to_string(f->info.get_duracao()) + " minutos\n"));
    imprimir_avl(f->right);
}

void Window::imprimir_rb(RBTree::Node *f) {
    if(f == nullptr)
        return;

    imprimir_rb(f->left);
    lista->addItem(QString::fromStdString("Título: " + f->info.get_titulo() +
                                          "\nAno: " + to_string(f->info.get_ano()) +
                                          "\nBilheteria: U$" + to_string(f->info.get_bilheteria()) + ",00" +
                                          "\nDiretor: " + f->info.get_diretor() +
                                          "\nPaís: " + f->info.get_pais() +
                                          "\nDuração: " + to_string(f->info.get_duracao()) + " minutos\n"));
    imprimir_rb(f->right);
}

void Window::data_avl() {
    new_window = new QWidget(nullptr);

    QFont labelFont("Times", 20, QFont::Bold);
    int maximum_label_height = 30;

    QGridLayout *layout = new QGridLayout();

    QLabel *label_rebalance = new QLabel("Rebalanciamentos: ");
    QLabel *label_rotate_left = new QLabel("Rotações a Esquerda: ");
    QLabel *label_rotate_right = new QLabel("Rotações a Direita: ");
    QLabel *label_size = new QLabel("Tamanho: ");
    
    QLabel *quantidade_rebalance = new QLabel(QString::number(avl._rebalance));
    QLabel *quantidade_rotate_left = new QLabel(QString::number(avl._rotate_left));
    QLabel *quantidade_rotate_right = new QLabel(QString::number(avl._rotate_right));
    QLabel *quantidade_size = new QLabel(QString::number(avl._size));

    label_rebalance->setMaximumHeight(maximum_label_height);
    label_rebalance->setFont(labelFont);
    label_rotate_left->setMaximumHeight(maximum_label_height);
    label_rotate_left->setFont(labelFont);
    label_rotate_right->setMaximumHeight(maximum_label_height);
    label_rotate_right->setFont(labelFont);
    label_size->setMaximumHeight(maximum_label_height);
    label_size->setFont(labelFont);

    quantidade_rebalance->setMaximumHeight(maximum_label_height);
    quantidade_rotate_left->setMaximumHeight(maximum_label_height);
    quantidade_rotate_right->setMaximumHeight(maximum_label_height);
    quantidade_size->setMaximumHeight(maximum_label_height);
    quantidade_rebalance->setFont(labelFont);
    quantidade_rotate_left->setFont(labelFont);
    quantidade_rotate_right->setFont(labelFont);
    quantidade_size->setFont(labelFont);



    label_rebalance->setAlignment(Qt::AlignRight);
    label_rotate_left->setAlignment(Qt::AlignRight);
    label_rotate_right->setAlignment(Qt::AlignRight);
    label_size->setAlignment(Qt::AlignRight);


    layout->addWidget(label_rebalance, 0, 0);
    layout->addWidget(label_rotate_left, 1, 0);
    layout->addWidget(label_rotate_right, 2, 0);
    layout->addWidget(label_size, 3, 0);

    quantidade_rebalance->setAlignment(Qt::AlignLeft);
    quantidade_rotate_left->setAlignment(Qt::AlignLeft);
    quantidade_rotate_right->setAlignment(Qt::AlignLeft);
    quantidade_size->setAlignment(Qt::AlignLeft);

    layout->addWidget(quantidade_rebalance, 0, 1);
    layout->addWidget(quantidade_rotate_left, 1, 1);
    layout->addWidget(quantidade_rotate_right, 2, 1);
    layout->addWidget(quantidade_size, 3, 1);

    new_window->setWindowTitle("Dados da AVL");
    new_window->setLayout(layout);
    new_window->setFixedSize(900, 400);
    new_window->show();

    QEventLoop loop;
    connect(this, SIGNAL(destroyed()), & loop, SLOT(quit()));
    loop.exec();
}

void Window::data_rb() {
    new_window = new QWidget(nullptr);

    QFont labelFont("Times", 20, QFont::Bold);
    int maximum_label_height = 30;

    QGridLayout *layout = new QGridLayout();

    QLabel *label_rebalance = new QLabel("Rebalanciamentos: ");
    QLabel *label_rotate_left = new QLabel("Rotações a Esquerda: ");
    QLabel *label_rotate_right = new QLabel("Rotações a Direita: ");
    QLabel *label_size = new QLabel("Tamanho: ");
    QLabel *label_swap_info = new QLabel("Swaps de Infos: ");
    QLabel *label_swap_node = new QLabel("Swaps de Nodes: ");
    QLabel *label_restore_properties = new QLabel("Propriedades Restauradas: ");
    
    QLabel *quantidade_rebalance = new QLabel(QString::number(rb._rebalance));
    QLabel *quantidade_rotate_left = new QLabel(QString::number(rb._rotate_left));
    QLabel *quantidade_rotate_right = new QLabel(QString::number(rb._rotate_right));
    QLabel *quantidade_size = new QLabel(QString::number(rb._size));
    QLabel *quantidade_swap_info = new QLabel(QString::number(rb._swap_info));
    QLabel *quantidade_swap_node = new QLabel(QString::number(rb._swap_node));
    QLabel *quantidade_restore_properties = new QLabel(QString::number(rb._restore_properties));


    label_rebalance->setMaximumHeight(maximum_label_height);
    label_rebalance->setFont(labelFont);
    label_rotate_left->setMaximumHeight(maximum_label_height);
    label_rotate_left->setFont(labelFont);
    label_rotate_right->setMaximumHeight(maximum_label_height);
    label_rotate_right->setFont(labelFont);
    label_size->setMaximumHeight(maximum_label_height);
    label_size->setFont(labelFont);
    label_swap_info->setMaximumHeight(maximum_label_height);
    label_swap_info->setFont(labelFont);
    label_swap_node->setMaximumHeight(maximum_label_height);
    label_swap_node->setFont(labelFont);
    label_restore_properties->setMaximumHeight(maximum_label_height);
    label_restore_properties->setFont(labelFont);

    quantidade_rebalance->setMaximumHeight(maximum_label_height);
    quantidade_rotate_left->setMaximumHeight(maximum_label_height);
    quantidade_rotate_right->setMaximumHeight(maximum_label_height);
    quantidade_size->setMaximumHeight(maximum_label_height);
    quantidade_swap_info->setMaximumHeight(maximum_label_height);
    quantidade_swap_node->setMaximumHeight(maximum_label_height);
    quantidade_restore_properties->setMaximumHeight(maximum_label_height);

    quantidade_rebalance->setFont(labelFont);
    quantidade_rotate_left->setFont(labelFont);
    quantidade_rotate_right->setFont(labelFont);
    quantidade_size->setFont(labelFont);
    quantidade_swap_info->setFont(labelFont);
    quantidade_swap_node->setFont(labelFont);
    quantidade_restore_properties->setFont(labelFont);

    label_rebalance->setAlignment(Qt::AlignRight);
    label_rotate_left->setAlignment(Qt::AlignRight);
    label_rotate_right->setAlignment(Qt::AlignRight);
    label_size->setAlignment(Qt::AlignRight);
    label_swap_info->setAlignment(Qt::AlignRight);
    label_swap_node->setAlignment(Qt::AlignRight);
    label_restore_properties->setAlignment(Qt::AlignRight);

    layout->addWidget(label_rebalance, 0, 0);
    layout->addWidget(label_rotate_left, 1, 0);
    layout->addWidget(label_rotate_right, 2, 0);
    layout->addWidget(label_size, 3, 0);
    layout->addWidget(label_swap_info, 4, 0);
    layout->addWidget(label_swap_node, 5, 0);
    layout->addWidget(label_restore_properties, 6, 0);

    quantidade_rebalance->setAlignment(Qt::AlignLeft);
    quantidade_rotate_left->setAlignment(Qt::AlignLeft);
    quantidade_rotate_right->setAlignment(Qt::AlignLeft);
    quantidade_size->setAlignment(Qt::AlignLeft);
    quantidade_swap_info->setAlignment(Qt::AlignLeft);
    quantidade_swap_node->setAlignment(Qt::AlignLeft);
    quantidade_restore_properties->setAlignment(Qt::AlignLeft);

    layout->addWidget(quantidade_rebalance, 0, 1);
    layout->addWidget(quantidade_rotate_left, 1, 1);
    layout->addWidget(quantidade_rotate_right, 2, 1);
    layout->addWidget(quantidade_size, 3, 1);
    layout->addWidget(quantidade_swap_info, 4, 1);
    layout->addWidget(quantidade_swap_node, 5, 1);
    layout->addWidget(quantidade_restore_properties, 6, 1);

    new_window->setWindowTitle("Dados da RB");
    new_window->setLayout(layout);
    new_window->setFixedSize(900, 400);
    new_window->show();

    QEventLoop loop;
    connect(this, SIGNAL(destroyed()), & loop, SLOT(quit()));
    loop.exec();
}

void Window::comp_perf() {
    new_window = new QWidget(nullptr);
    QVBoxLayout *tela = new QVBoxLayout(this);
    QGridLayout *barras = new QGridLayout();
    QGridLayout *botao = new QGridLayout();
    QGridLayout *tempos = new QGridLayout();
    int button_size = 300;
    int maximum_label_height = 30;
    QFont buttonFont("Times", 20);
    QFont labelFont("Times", 20, QFont::Bold);

    QLabel *AVL_label = new QLabel("Árvore AVL");
    barras->addWidget(AVL_label, 0, 0);
    AVL_label->setAlignment(Qt::AlignCenter);
    AVL_label->setMaximumHeight(maximum_label_height);
    AVL_label->setFont(labelFont);

    QLabel *RB_label = new QLabel("Árvore Red-Black");
    barras->addWidget(RB_label, 0, 1);
    RB_label->setAlignment(Qt::AlignCenter);
    RB_label->setMaximumHeight(maximum_label_height);
    RB_label->setFont(labelFont);

    QLabel *AVL_ins = new QLabel("50.000 Inserções");
    tempos->addWidget(AVL_ins, 0, 0);
    AVL_ins->setAlignment(Qt::AlignCenter);
    AVL_ins->setMaximumHeight(maximum_label_height);
    AVL_ins->setFont(labelFont);

    AVL_ins_time = new QLabel(" ");
    tempos->addWidget(AVL_ins_time, 1, 0);
    AVL_ins_time->setAlignment(Qt::AlignCenter);
    AVL_ins_time->setMaximumHeight(maximum_label_height);
    AVL_ins_time->setFont(labelFont);

    QLabel *AVL_searchs = new QLabel("1.000.000 Buscas");
    tempos->addWidget(AVL_searchs, 2, 0);
    AVL_searchs->setAlignment(Qt::AlignCenter);
    AVL_searchs->setMaximumHeight(maximum_label_height);
    AVL_searchs->setFont(labelFont);

    AVL_searchs_time = new QLabel(" ");
    tempos->addWidget(AVL_searchs_time, 3, 0);
    AVL_searchs_time->setAlignment(Qt::AlignCenter);
    AVL_searchs_time->setMaximumHeight(maximum_label_height);
    AVL_searchs_time->setFont(labelFont);

    QLabel *AVL_rmv = new QLabel("50.000 Remoções");
    tempos->addWidget(AVL_rmv, 4, 0);
    AVL_rmv->setAlignment(Qt::AlignCenter);
    AVL_rmv->setMaximumHeight(maximum_label_height);
    AVL_rmv->setFont(labelFont);

    AVL_rmv_time = new QLabel(" ");
    tempos->addWidget(AVL_rmv_time, 5, 0);
    AVL_rmv_time->setAlignment(Qt::AlignCenter);
    AVL_rmv_time->setMaximumHeight(maximum_label_height);
    AVL_rmv_time->setFont(labelFont);

    QLabel *RB_ins = new QLabel("50.000 Inserções");
    tempos->addWidget(RB_ins, 0, 1);
    RB_ins->setAlignment(Qt::AlignCenter);
    RB_ins->setMaximumHeight(maximum_label_height);
    RB_ins->setFont(labelFont);

    RB_ins_time = new QLabel(" ");
    tempos->addWidget(RB_ins_time, 1, 1);
    RB_ins_time->setAlignment(Qt::AlignCenter);
    RB_ins_time->setMaximumHeight(maximum_label_height);
    RB_ins_time->setFont(labelFont);

    QLabel *RB_searchs = new QLabel("1.000.000 Buscas");
    tempos->addWidget(RB_searchs, 2, 1);
    RB_searchs->setAlignment(Qt::AlignCenter);
    RB_searchs->setMaximumHeight(maximum_label_height);
    RB_searchs->setFont(labelFont);

    RB_searchs_time = new QLabel(" ");
    tempos->addWidget(RB_searchs_time, 3, 1);
    RB_searchs_time->setAlignment(Qt::AlignCenter);
    RB_searchs_time->setMaximumHeight(maximum_label_height);
    RB_searchs_time->setFont(labelFont);

    QLabel *RB_rmv = new QLabel("50.000 Remoções");
    tempos->addWidget(RB_rmv, 4, 1);
    RB_rmv->setAlignment(Qt::AlignCenter);
    RB_rmv->setMaximumHeight(maximum_label_height);
    RB_rmv->setFont(labelFont);

    RB_rmv_time = new QLabel(" ");
    tempos->addWidget(RB_rmv_time, 5, 1);
    RB_rmv_time->setAlignment(Qt::AlignCenter);
    RB_rmv_time->setMaximumHeight(maximum_label_height);
    RB_rmv_time->setFont(labelFont);

    QPushButton *start = new QPushButton("Start");
    connect(start, &QPushButton::clicked, this, &Window::start_perf);
    botao->addWidget(start, 0, 0);
    start->setFixedWidth(button_size);
    start->setFont(buttonFont);

    tela->addLayout(barras);
    tela->addLayout(botao);
    tela->addLayout(tempos);

    new_window->setLayout(tela);
    new_window->setFixedSize(650, 450);
    new_window->show();

    QEventLoop loop;
    connect(this, SIGNAL(destroyed()), & loop, SLOT(quit()));
    loop.exec();
}

void Window::start_perf() {
    pthread_t avl, rb;
    pthread_create(&avl, NULL, &Window::start_perf_AVL, NULL);
    pthread_create(&rb, NULL, &Window::start_perf_RB, NULL);
}

void * Window::start_perf_AVL(void *t) {
    time_t tempo;
    AVLTree avl_perf;

    tempo = clock();
    for(int i = 0; i < 50000; ++i) {
        avl_perf.insert(Filme(filmes[rand() % quant_filmes],
                   1920 + (rand() % 100),
                   rand() % 4000000001,
                   diretores[rand() % quant_diretores],
                   paises[rand() % quant_paises],
                   rand() % 181));
    }
    tempo = clock() - tempo;
    AVL_ins_time->setText(QString::number((float)tempo/CLOCKS_PER_SEC));

    tempo = clock();
    for(int i = 0; i < 1000000; ++i) {
        avl_perf.search(filmes[rand() % quant_filmes]);
        //progressAVL->setValue(i+1);
    }
    tempo = clock() - tempo;
    AVL_searchs_time->setText(QString::number((float)tempo/CLOCKS_PER_SEC));

    tempo = clock();
    avl_perf.clean();
    tempo = clock() - tempo;
    AVL_rmv_time->setText(QString::number((float)tempo/CLOCKS_PER_SEC));

    pthread_exit(NULL);
}

void * Window::start_perf_RB(void *t) {
    time_t tempo;
    RBTree rb_perf;

    tempo = clock();
    for(int i = 0; i < 50000; ++i) {
        rb_perf.insert(Filme(filmes[rand() % quant_filmes],
                   1920 + (rand() % 100),
                   rand() % 4000000001,
                   diretores[rand() % quant_diretores],
                   paises[rand() % quant_paises],
                   rand() % 181));
    }
    tempo = clock() - tempo;
    RB_ins_time->setText(QString::number((float)tempo/CLOCKS_PER_SEC));

    tempo = clock();
    for(int i = 0; i < 1000000; ++i) {
        rb_perf.search(filmes[rand() % quant_filmes]);
    }
    tempo = clock() - tempo;
    RB_searchs_time->setText(QString::number((float)tempo/CLOCKS_PER_SEC));

    tempo = clock();
    rb_perf.clean();
    tempo = clock() - tempo;
    RB_rmv_time->setText(QString::number((float)tempo/CLOCKS_PER_SEC));

    pthread_exit(NULL);
}

void Window::comp_ins() {
    new_window = new QWidget(nullptr);
    QVBoxLayout *tela = new QVBoxLayout(this);
    QGridLayout *campos = new QGridLayout();
    QGridLayout *tempos = new QGridLayout();
    int button_size = 430;
    int maximum_label_height = 30;
    QFont buttonFont("Times", 20);
    QFont labelFont("Times", 20, QFont::Bold);

    QLabel *AVL_label = new QLabel("Insira a quantidade de inserções");
    campos->addWidget(AVL_label, 0, 0);
    AVL_label->setAlignment(Qt::AlignCenter);
    AVL_label->setMaximumHeight(maximum_label_height);
    AVL_label->setFont(labelFont);

    campo_comp = new QLineEdit();
    campos->addWidget(campo_comp, 1, 0);
    campo_comp->setValidator(new QIntValidator());
    campo_comp->setFont(labelFont);

    QPushButton *start = new QPushButton("Start");
    connect(start, &QPushButton::clicked, this, &Window::start_ins);
    campos->addWidget(start, 2, 0);
    start->setFixedWidth(button_size);
    start->setFont(buttonFont);

    QLabel *AVL = new QLabel("AVL");
    tempos->addWidget(AVL, 0, 0);
    AVL->setAlignment(Qt::AlignCenter);
    AVL->setMaximumHeight(maximum_label_height);
    AVL->setFont(labelFont);

    AVL_ins_time = new QLabel(" ");
    tempos->addWidget(AVL_ins_time, 1, 0);
    AVL_ins_time->setAlignment(Qt::AlignCenter);
    AVL_ins_time->setMaximumHeight(maximum_label_height);
    AVL_ins_time->setFont(labelFont);

    QLabel *RB = new QLabel("Red-Black");
    tempos->addWidget(RB, 0, 1);
    RB->setAlignment(Qt::AlignCenter);
    RB->setMaximumHeight(maximum_label_height);
    RB->setFont(labelFont);

    RB_ins_time = new QLabel(" ");
    tempos->addWidget(RB_ins_time, 1, 1);
    RB_ins_time->setAlignment(Qt::AlignCenter);
    RB_ins_time->setMaximumHeight(maximum_label_height);
    RB_ins_time->setFont(labelFont);

    tela->addLayout(campos);
    tela->addLayout(tempos);

    new_window->setLayout(tela);
    new_window->setFixedSize(450, 250);
    new_window->show();

    QEventLoop loop;
    connect(this, SIGNAL(destroyed()), & loop, SLOT(quit()));
    loop.exec();
}

void Window::start_ins() {
    pthread_t avl, rb;
    pthread_create(&avl, NULL, &Window::start_ins_AVL, NULL);
    pthread_create(&rb, NULL, &Window::start_ins_RB, NULL);
}

void *Window::start_ins_AVL(void *t) {
    time_t tempo;
    AVLTree avl_perf;

    tempo = clock();
    for(int i = 0; i < campo_comp->text().toInt(); ++i) {
        avl_perf.insert(Filme(filmes[rand() % quant_filmes],
                   1920 + (rand() % 100),
                   rand() % 4000000001,
                   diretores[rand() % quant_diretores],
                   paises[rand() % quant_paises],
                   rand() % 181));
    }
    tempo = clock() - tempo;
    AVL_ins_time->setText(QString::number((float)tempo/CLOCKS_PER_SEC));

    pthread_exit(NULL);
}

void *Window::start_ins_RB(void *t) {
    time_t tempo;
    RBTree rb_perf;

    tempo = clock();
    for(int i = 0; i < campo_comp->text().toInt(); ++i) {
        rb_perf.insert(Filme(filmes[rand() % quant_filmes],
                   1920 + (rand() % 100),
                   rand() % 4000000001,
                   diretores[rand() % quant_diretores],
                   paises[rand() % quant_paises],
                   rand() % 181));
    }
    tempo = clock() - tempo;
    RB_ins_time->setText(QString::number((float)tempo/CLOCKS_PER_SEC));

    pthread_exit(NULL);
}

void Window::comp_rmv() {
    new_window = new QWidget(nullptr);
    QVBoxLayout *tela = new QVBoxLayout(this);
    QGridLayout *campos = new QGridLayout();
    QGridLayout *tempos = new QGridLayout();
    int button_size = 430;
    int maximum_label_height = 30;
    QFont buttonFont("Times", 20);
    QFont labelFont("Times", 20, QFont::Bold);

    QLabel *AVL_label = new QLabel("Insira a quantidade de remoções");
    campos->addWidget(AVL_label, 0, 0);
    AVL_label->setAlignment(Qt::AlignCenter);
    AVL_label->setMaximumHeight(maximum_label_height);
    AVL_label->setFont(labelFont);

    campo_comp = new QLineEdit();
    campos->addWidget(campo_comp, 1, 0);
    campo_comp->setValidator(new QIntValidator());
    campo_comp->setFont(labelFont);

    QPushButton *start = new QPushButton("Start");
    connect(start, &QPushButton::clicked, this, &Window::start_rmv);
    campos->addWidget(start, 2, 0);
    start->setFixedWidth(button_size);
    start->setFont(buttonFont);

    QLabel *AVL = new QLabel("AVL");
    tempos->addWidget(AVL, 0, 0);
    AVL->setAlignment(Qt::AlignCenter);
    AVL->setMaximumHeight(maximum_label_height);
    AVL->setFont(labelFont);

    AVL_ins_time = new QLabel(" ");
    tempos->addWidget(AVL_ins_time, 1, 0);
    AVL_ins_time->setAlignment(Qt::AlignCenter);
    AVL_ins_time->setMaximumHeight(maximum_label_height);
    AVL_ins_time->setFont(labelFont);

    QLabel *RB = new QLabel("Red-Black");
    tempos->addWidget(RB, 0, 1);
    RB->setAlignment(Qt::AlignCenter);
    RB->setMaximumHeight(maximum_label_height);
    RB->setFont(labelFont);

    RB_ins_time = new QLabel(" ");
    tempos->addWidget(RB_ins_time, 1, 1);
    RB_ins_time->setAlignment(Qt::AlignCenter);
    RB_ins_time->setMaximumHeight(maximum_label_height);
    RB_ins_time->setFont(labelFont);

    tela->addLayout(campos);
    tela->addLayout(tempos);

    new_window->setLayout(tela);
    new_window->setFixedSize(450, 250);
    new_window->show();

    QEventLoop loop;
    connect(this, SIGNAL(destroyed()), & loop, SLOT(quit()));
    loop.exec();
}

void Window::start_rmv() {
    pthread_t avl, rb;
    pthread_create(&avl, NULL, &Window::start_rmv_AVL, NULL);
    pthread_create(&rb, NULL, &Window::start_rmv_RB, NULL);
}

void *Window::start_rmv_AVL(void *t) {
    time_t tempo;
    AVLTree avl_perf;

    AVL_ins_time->setText("Inserindo");

    for(int i = 0; i < campo_comp->text().toInt(); ++i) {
        avl_perf.insert(Filme(filmes[rand() % quant_filmes],
                   1920 + (rand() % 100),
                   rand() % 4000000001,
                   diretores[rand() % quant_diretores],
                   paises[rand() % quant_paises],
                   rand() % 181));
    }

    AVL_ins_time->setText("Removendo");

    tempo = clock();
    avl_perf.clean();
    tempo = clock() - tempo;

    AVL_ins_time->setText(QString::number((float)tempo/CLOCKS_PER_SEC));

    pthread_exit(NULL);
}

void *Window::start_rmv_RB(void *t) {
    time_t tempo;
    RBTree rb_perf;

    RB_ins_time->setText("Inserindo");

    for(int i = 0; i < campo_comp->text().toInt(); ++i) {
        rb_perf.insert(Filme(filmes[rand() % quant_filmes],
                   1920 + (rand() % 100),
                   rand() % 4000000001,
                   diretores[rand() % quant_diretores],
                   paises[rand() % quant_paises],
                   rand() % 181));
    }

    RB_ins_time->setText("Removendo");

    tempo = clock();
    rb_perf.clean();
    tempo = clock() - tempo;

    RB_ins_time->setText(QString::number((float)tempo/CLOCKS_PER_SEC));

    pthread_exit(NULL);
}

void Window::comp_search() {
    new_window = new QWidget(nullptr);
    QVBoxLayout *tela = new QVBoxLayout(this);
    QGridLayout *campos = new QGridLayout();
    QGridLayout *tempos = new QGridLayout();
    int button_size = 430;
    int maximum_label_height = 30;
    QFont buttonFont("Times", 20);
    QFont labelFont("Times", 20, QFont::Bold);

    QLabel *AVL_label = new QLabel("Insira a quantidade de buscas");
    campos->addWidget(AVL_label, 0, 0);
    AVL_label->setAlignment(Qt::AlignCenter);
    AVL_label->setMaximumHeight(maximum_label_height);
    AVL_label->setFont(labelFont);

    campo_comp = new QLineEdit();
    campos->addWidget(campo_comp, 1, 0);
    campo_comp->setValidator(new QIntValidator());
    campo_comp->setFont(labelFont);

    QPushButton *start = new QPushButton("Start");
    connect(start, &QPushButton::clicked, this, &Window::start_search);
    campos->addWidget(start, 2, 0);
    start->setFixedWidth(button_size);
    start->setFont(buttonFont);

    QLabel *AVL = new QLabel("AVL");
    tempos->addWidget(AVL, 0, 0);
    AVL->setAlignment(Qt::AlignCenter);
    AVL->setMaximumHeight(maximum_label_height);
    AVL->setFont(labelFont);

    AVL_ins_time = new QLabel(" ");
    tempos->addWidget(AVL_ins_time, 1, 0);
    AVL_ins_time->setAlignment(Qt::AlignCenter);
    AVL_ins_time->setMaximumHeight(maximum_label_height);
    AVL_ins_time->setFont(labelFont);

    QLabel *RB = new QLabel("Red-Black");
    tempos->addWidget(RB, 0, 1);
    RB->setAlignment(Qt::AlignCenter);
    RB->setMaximumHeight(maximum_label_height);
    RB->setFont(labelFont);

    RB_ins_time = new QLabel(" ");
    tempos->addWidget(RB_ins_time, 1, 1);
    RB_ins_time->setAlignment(Qt::AlignCenter);
    RB_ins_time->setMaximumHeight(maximum_label_height);
    RB_ins_time->setFont(labelFont);

    tela->addLayout(campos);
    tela->addLayout(tempos);

    new_window->setLayout(tela);
    new_window->setFixedSize(450, 250);
    new_window->show();

    QEventLoop loop;
    connect(this, SIGNAL(destroyed()), & loop, SLOT(quit()));
    loop.exec();
}

void Window::start_search() {
    pthread_t avl, rb;
    pthread_create(&avl, NULL, &Window::start_search_AVL, NULL);
    pthread_create(&rb, NULL, &Window::start_search_RB, NULL);
}

void *Window::start_search_AVL(void *t) {
    time_t tempo;
    AVLTree avl_perf;

    AVL_ins_time->setText("Inserindo");

    for(int i = 0; i < quant_filmes; ++i) {
        avl_perf.insert(Filme(filmes[i],
                   1920 + (rand() % 100),
                   rand() % 4000000001,
                   diretores[rand() % quant_diretores],
                   paises[rand() % quant_paises],
                   rand() % 181));
    }

    AVL_ins_time->setText("Buscando");

    tempo = clock();
    for(int i = 0; i < campo_comp->text().toInt(); ++i)
        avl_perf.search(filmes[rand() % quant_filmes]);
    tempo = clock() - tempo;

    AVL_ins_time->setText(QString::number((float)tempo/CLOCKS_PER_SEC));

    pthread_exit(NULL);
}

void *Window::start_search_RB(void *t) {
    time_t tempo;
    RBTree rb_perf;

    RB_ins_time->setText("Inserindo");

    for(int i = 0; i < quant_filmes; ++i) {
        rb_perf.insert(Filme(filmes[i],
                   1920 + (rand() % 100),
                   rand() % 4000000001,
                   diretores[rand() % quant_diretores],
                   paises[rand() % quant_paises],
                   rand() % 181));
    }

    RB_ins_time->setText("Buscando");

    tempo = clock();
    for(int i = 0; i < campo_comp->text().toInt(); ++i)
        rb_perf.search(filmes[rand() % quant_filmes]);
    tempo = clock() - tempo;

    RB_ins_time->setText(QString::number((float)tempo/CLOCKS_PER_SEC));

    pthread_exit(NULL);
}

void Window::limpar_todos_campos() {
    campo_quantidade->setText("");
    campo_titulo->setText("");
    campo_ano->setText("");
    campo_bilheteria->setText("");
    campo_duracao->setText("");
    campo_diretor->setText("");
    campo_pais->setText("");
    alert->setText("");
}

void Window::inserir_filme_avl() {
    QString aux = campo_titulo->text();
    if(aux == "") {
        alert->setText("Título não pode ser vazio");
        return;
    }
    const char *titulo = aux.toStdString().c_str();

    aux = campo_ano->text();
    if(aux == "") {
        alert->setText("Ano não pode ser vazio");
        return;
    }
    short int ano = aux.toShort();

    aux = campo_bilheteria->text();
    if(aux == "") {
        alert->setText("Bilheteria não pode ser vazio");
        return;
    }
    unsigned int bilheteria = aux.toUInt();

    aux = campo_diretor->text();
    if(aux == "") {
        alert->setText("Diretor não pode ser vazio");
        return;
    }
    const char *diretor = aux.toStdString().c_str();

    aux = campo_pais->text();
    if(aux == "") {
        alert->setText("País não pode ser vazio");
        return;
    }
    const char *pais = aux.toStdString().c_str();

    aux = campo_duracao->text();
    if(aux == "") {
        alert->setText("Duração não pode ser vazio");
        return;
    }
    unsigned char duracao = aux.toShort();

    Filme filme(titulo, ano, bilheteria, diretor, pais, duracao);

    avl.insert(filme);
    campo_quantidade->setText("");
    new_window->close();
}

void Window::inserir_filme_rb() {
    QString aux = campo_titulo->text();
    if(aux == "") {
        alert->setText("Título não pode ser vazio");
        return;
    }
    const char *titulo = aux.toStdString().c_str();

    aux = campo_ano->text();
    if(aux == "") {
        alert->setText("Ano não pode ser vazio");
        return;
    }
    short int ano = aux.toShort();

    aux = campo_bilheteria->text();
    if(aux == "") {
        alert->setText("Bilheteria não pode ser vazio");
        return;
    }
    unsigned int bilheteria = aux.toUInt();

    aux = campo_diretor->text();
    if(aux == "") {
        alert->setText("Diretor não pode ser vazio");
        return;
    }
    const char *diretor = aux.toStdString().c_str();

    aux = campo_pais->text();
    if(aux == "") {
        alert->setText("País não pode ser vazio");
        return;
    }
    const char *pais = aux.toStdString().c_str();

    aux = campo_duracao->text();
    if(aux == "") {
        alert->setText("Duração não pode ser vazio");
        return;
    }
    unsigned char duracao = aux.toShort();

    Filme filme(titulo, ano, bilheteria, diretor, pais, duracao);

    rb.insert(filme);
    campo_quantidade->setText("");
    new_window->close();
}
