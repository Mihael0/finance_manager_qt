include(../defaults.pri)

QT += core gui
QT += widgets
QT += core gui network

TEMPLATE = lib

TARGET = financemanager
SUBDIRS += ui

FORMS += \
    ui/networkmanager.ui \
    ui/createsummarywindow.ui \
    ui/recurringexpensewindow.ui \
    ui/loginwindow.ui \
    ui/expensewindow.ui \
    ui/mainwindow.ui \

SOURCES += \
    createsummarywindow.cpp \
    loginwindow.cpp \
    mainwindow.cpp \
    excel.cpp \
    expensewindow.cpp \
    networkmanager.cpp \
    recurringexpensewindow.cpp

HEADERS += \
    createsummarywindow.h \
    loginwindow.h \
    mainwindow.h \
    excel.h \
    expensewindow.h \
    networkmanager.h \
    recurringexpensewindow.h
