#include "mainwindow.h"
#include "expensewindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ExpenseWindow DeclareExpenses;
    DeclareExpenses.show();
    return a.exec();
}
