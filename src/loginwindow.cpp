#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "QMessageBox"


typedef struct USRDETAILS{
    QString UserName;
    QString PassWord;
} USERDETAILS;

typedef struct CREDENTIALS{
    const USRDETAILS User1;
    const USRDETAILS User2;
} CREDENTIALS;

CREDENTIALS usrCredentials = {
    .User1 = {"Mihael", "Mihael"},
    .User2 = {"Vanya", "Vanya"}
};

LogInWindow::LogInWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LogInWindow){
    ui->setupUi(this);
}

LogInWindow::~LogInWindow(){
    delete ui;
}

void LogInWindow::on_LogIn_clicked(){
    // TODO: Implement an actual authenthication. For now this is a placeholder.
    // For now check if the username and passwords match one of the two users.
    if((ui->UserName->text() == usrCredentials.User1.UserName ||
        ui->UserName->text() == usrCredentials.User2.UserName) &&
        (ui->PassWord->text() == usrCredentials.User1.PassWord ||
        ui->PassWord->text() == usrCredentials.User2.PassWord)){
        emit authenthicationSucceeded();
    } else{
        QMessageBox::warning(this, "Error", "Authenthication Unsuccessful. Please try again.");
    }

}

