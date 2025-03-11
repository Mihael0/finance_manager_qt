#include "mainwindow.h"
#include "expensewindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_DeclareExpenseBtn_clicked(void)
{
    this->hide();
    emit on_DeclareEpxenseBtn_clicked();
}

void MainWindow::on_Authenthication_successful(void){
    this->show();
}

void MainWindow::on_BackBtn_pressed(void){
    this->show();
}
