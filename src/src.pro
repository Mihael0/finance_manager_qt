include(../defaults.pri)

QT += core gui
QT += widgets

TEMPLATE = lib

TARGET = financemanager
SUBDIRS += ui

FORMS += \
    ui/createsummarywindow.ui \
    ui/recurringexpensewindow.ui \
    ui/loginwindow.ui \
    ui/expensewindow.ui \
    ui/mainwindow.ui \

SOURCES += \
    createsummarywindow.cpp \
    eventeater.cpp \
    expensemanager.cpp \
    loginwindow.cpp \
    mainwindow.cpp \
    expensewindow.cpp \
    recurringexpensewindow.cpp

HEADERS += \
    createsummarywindow.h \
    eventeater.h \
    expensemanager.h \
    loginwindow.h \
    mainwindow.h \
    expensewindow.h \
    recurringexpensewindow.h
