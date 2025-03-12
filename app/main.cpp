#include "mainwindow.h"
#include "expensewindow.h"
#include "recurringexpensewindow.h"
#include "loginwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LogInWindow LogIn;
    MainWindow SelectMenu;

    // Create all the signal and slot connections between the windows.
    QObject::connect(&LogIn,&LogInWindow::authenthicationSucceeded,&SelectMenu,&MainWindow::showMainWindow);
    // QObject::connect(&SelectMenu,&MainWindow::on_DeclareEpxenseBtn_pressed,&DeclareExpenses,&ExpenseWindow::on_DailyExpensesBtn_pressed);
    // QObject::connect(&DeclareExpenses,&ExpenseWindow::on_BackBtn_pressed,&SelectMenu,&MainWindow::on_DeclareExpenseBackBtn_pressed);

    // Hangs the program until LogIn.exce() returns a result.
    // TODO: remove this hanging, as the user cannot do anything (even close the window) while this is here.
    while(LogIn.exec() != QDialog:: Accepted);
    LogIn.close();

    return a.exec();
}
