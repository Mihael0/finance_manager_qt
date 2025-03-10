#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "QMessageBox"

LogInWindow::LogInWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LogInWindow)
{
    ui->setupUi(this);
}

LogInWindow::~LogInWindow()
{
    delete ui;
}

void LogInWindow::on_LogIn_clicked()
{   CREDENTIALS Users;

    if(ui->UserName->text()== Users.User1 || ui->UserName->text() == Users.User2){
        _SetAuthenthicationSuccessful(true);
        accept();
    } else{
        _SetAuthenthicationSuccessful(false);
        QMessageBox::warning(this, "Error", "Authenthication Unsuccessful. Please try again.");
        reject();
    }

}

bool LogInWindow::AuthenticationSuccessful(void){
    return _GetAuthehtnicationSuccessful();
}

