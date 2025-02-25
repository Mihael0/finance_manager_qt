#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->currentMonth->setFrame(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_registerExpense_clicked()
{

}

