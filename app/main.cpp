#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow SelectMenu;
    SelectMenu.ShowLogInWindow();
    return a.exec();
}
