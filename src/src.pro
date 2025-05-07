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
    apptime.cpp \
    createsummarywindow.cpp \
    eventeater.cpp \
    expensemanager.cpp \
    loginwindow.cpp \
    mainwindow.cpp \
    expensewindow.cpp \
    networkmanager.cpp \
    recurringexpensewindow.cpp

HEADERS += \
    apptime.h \
    createsummarywindow.h \
    eventeater.h \
    expensemanager.h \
    loginwindow.h \
    mainwindow.h \
    expensewindow.h \
    networkmanager.h \
    recurringexpensewindow.h
