#include "signinscreen.h"
#include "ui_signinscreen.h"

SignInScreen::SignInScreen(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SignInScreen)
{
    ui->setupUi(this);
}

SignInScreen::~SignInScreen()
{
    delete ui;
}

void SignInScreen::on_LogIn_clicked()
{   CREDENTIALS Users;

    if(ui->UserName->text()== Users.User1 || ui->UserName->text() == Users.User2){
        int a = 5;
    }
}

