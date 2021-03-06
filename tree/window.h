#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QProgressBar>
#include "avltree.h"
#include "rbtree.h"
#include "filme.h"
#include "dados.h"
#include <QLineEdit>
#include <QLabel>
#include <QListWidget>

class Window : public QWidget {
public:
    explicit Window(QWidget *parent = nullptr);

private:
    AVLTree avl;
    RBTree rb;
    int quantidade;
    QProgressBar *progressBar;
    QLineEdit *campo_quantidade;
    QLineEdit *campo_titulo;
    QLineEdit *campo_ano;
    QLineEdit *campo_bilheteria;
    QLineEdit *campo_diretor;
    QLineEdit *campo_pais;
    QLineEdit *campo_duracao;
    QLabel *alert;
    QWidget *new_window;
    QListWidget *lista;
    static QLabel *AVL_ins_time;
    static QLabel *AVL_searchs_time;
    static QLabel *AVL_rmv_time;
    static QLabel *RB_ins_time;
    static QLabel *RB_searchs_time;
    static QLabel *RB_rmv_time;
    static QLineEdit *campo_comp;

private slots:
    void random_avl() { random_tree(0); }
    void random_rb() { random_tree(1); }
    void random_tree(int opcao);
    void gerar_avl_aleat();
    void gerar_rb_aleat();
    void insert_avl() { insert(0); }
    void insert_rb() { insert(1); }
    void insert(int opcao);
    void inserir_filme_avl();
    void inserir_filme_rb();
    void remove_avl() { tela_titulo(0); }
    void remove_rb() { tela_titulo(1); }
    void search_avl() { tela_titulo(2); }
    void search_rb() { tela_titulo(3); }
    void remover_filme_avl();
    void remover_filme_rb();
    void buscar_filme_avl();
    void buscar_filme_rb();
    void list_avl() { imprimir_lista(0); }
    void list_rb() { imprimir_lista(1); }
    void imprimir_lista(int opcao);
    void imprimir_avl(AVLTree::Node *f);
    void imprimir_rb(RBTree::Node *f);
    void tela_titulo(int opcao);
    void data_avl();
    void data_rb();
    void comp_perf();
    void start_perf();
    static void *start_perf_AVL(void *t);
    static void *start_perf_RB(void *t);
    void comp_ins();
    void start_ins();
    static void *start_ins_AVL(void *t);
    static void *start_ins_RB(void *t);
    void comp_rmv();
    void start_rmv();
    static void *start_rmv_AVL(void *t);
    static void *start_rmv_RB(void *t);
    void comp_search();
    void start_search();
    static void *start_search_AVL(void *t);
    static void *start_search_RB(void *t);
    void get_quantidade() { quantidade = campo_quantidade->text().toInt(); }
    void limpar_todos_campos();
    void mostrar_filme_encontrado(const Filme& filme);
};

#endif // WINDOW_H
