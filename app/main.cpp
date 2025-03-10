#include "mainwindow.h"
#include "expensewindow.h"
#include "loginwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LogInWindow LogIn;

    // TODO: Add a notification that authenthication was not successful.
    // Hangs the program until LogIn.exce() returns a result.
    while(LogIn.exec() != QDialog:: Accepted);
    if(LogIn.AuthenticationSuccessful() ){
        MainWindow ConfigurationWindow;
        ConfigurationWindow.show();
        return a.exec();
    }

    return 0;
}
