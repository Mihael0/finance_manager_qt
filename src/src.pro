include(../defaults.pri)

QT += core gui
QT += widgets

TEMPLATE = lib

TARGET = financemanager
SUBDIRS += ui

FORMS += \
    ui/expensewindow.ui \
    ui/mainwindow.ui \
    ui/signinscreen.ui
SOURCES += \
    mainwindow.cpp \
    excel.cpp \
    signinscreen.cpp \
    expensewindow.cpp

HEADERS += \
    mainwindow.h \
    excel.h \
    signinscreen.h \
    expensewindow.h
