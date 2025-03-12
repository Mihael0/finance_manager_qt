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
    loginwindow.cpp \
    mainwindow.cpp \
    excel.cpp \
    expensewindow.cpp \
    recurringexpensewindow.cpp

HEADERS += \
    createsummarywindow.h \
    loginwindow.h \
    mainwindow.h \
    excel.h \
    expensewindow.h \
    recurringexpensewindow.h
