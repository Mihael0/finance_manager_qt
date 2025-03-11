#include "mainwindow.h"
#include "expensewindow.h"
#include "loginwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Declare all the different windows
    LogInWindow LogIn;
    MainWindow SelectMenu;
    ExpenseWindow DeclareExpenses;
    // Create all the signal and slot connections between the windows.
    QObject::connect(&LogIn,&LogInWindow::AuthenthicationSuccessful,&SelectMenu,&MainWindow::on_Authenthication_successful);
    QObject::connect(&SelectMenu,&MainWindow::on_DeclareEpxenseBtn_clicked,&DeclareExpenses,&ExpenseWindow::on_DailyExpensesBtn_pressed);
    QObject::connect(&DeclareExpenses,&ExpenseWindow::on_BackBtn_pressed,&SelectMenu,&MainWindow::on_BackBtn_pressed);

    // Hangs the program until LogIn.exce() returns a result.
    while(LogIn.exec() != QDialog:: Accepted);
    return a.exec();
}
