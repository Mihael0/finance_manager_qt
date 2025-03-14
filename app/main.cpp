#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow SelectMenu;

    while(SelectMenu.IsAuthenthicationAccepted() != QDialog:: Accepted);

    return a.exec();
}
