include(../defaults.pri)

QT += core gui
QT += widgets
QT += core gui network

TEMPLATE = app

SOURCES += main.cpp

LIBS += -L$$DESTDIR -lfinancemanager
