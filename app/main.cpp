#include "mainwindow.h"
#include "excel.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    Excel Example;
    Example._CreateNewExcelBook();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
