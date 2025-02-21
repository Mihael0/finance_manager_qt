include(../defaults.pri)

QT += core gui
QT += widgets

TEMPLATE = lib

TARGET = myapp
SUBDIRS += ui

FORMS += ui/mainwindow.ui
SOURCES += \
    mainwindow.cpp \
    
HEADERS += \
    mainwindow.h \
