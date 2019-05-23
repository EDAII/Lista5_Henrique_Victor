#include <QApplication>
#include "window.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Window tela;
    tela.resize(700, 400);
    tela.setWindowTitle("Estrutura de Dados - Lista 5");
    tela.show();
    return app.exec();
}
