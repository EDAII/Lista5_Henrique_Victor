TEMPLATE = app
TARGET = tree
INCLUDEPATH += .

QT = core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += window.h \
    avltree.h \
    rbtree.h \
    filme.h \
    dados.h
SOURCES += main.cpp window.cpp \
    avltree.cpp \
    rbtree.cpp \
    filme.cpp \
    dados.cpp
