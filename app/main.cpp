#include "mainwindow.h"
#include "excel.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    Excel Example;
    std::string BookName = "Test";
    Example._CreateNewExcelBook(BookName);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
