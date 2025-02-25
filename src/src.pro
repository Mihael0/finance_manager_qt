include(../defaults.pri)

QT += core gui
QT += widgets

TEMPLATE = lib

TARGET = financemanager
SUBDIRS += ui

FORMS += ui/mainwindow.ui
SOURCES += \
    excel.cpp \
    mainwindow.cpp \
    
HEADERS += \
    excel.h \
    mainwindow.h \
