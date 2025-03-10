include(../defaults.pri)

QT += core gui
QT += widgets

TEMPLATE = lib

TARGET = financemanager
SUBDIRS += ui

FORMS += \
    ui/loginwindow.ui \
    ui/expensewindow.ui \
    ui/mainwindow.ui \

SOURCES += \
    loginwindow.cpp \
    mainwindow.cpp \
    excel.cpp \
    expensewindow.cpp \

HEADERS += \
    loginwindow.h \
    mainwindow.h \
    excel.h \
    expensewindow.h \
