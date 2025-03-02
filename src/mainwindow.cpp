#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->startOfCurrentMonth->setFrame(false);
    _SetAppTimeToStartOfMonth();
    _InitializeCurrentMonth();
    ui->startOfCurrentMonth->setText(_GetLocalAppTime().toString("dd-MM-yyyy"));
}

void MainWindow::_InitializeCurrentMonth(void){
    if(ui){
        ui->currentMonth->setFrame(false);
        ui->currentMonth->setText(_GetCurrentTime().toString("dd-MM-yyyy"));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_dailyExpenses_returnPressed()
{
    // Excel takes in the inputted float number.
    // And we pass the LocalApptime.
    // We need to have access to the created sheets
    // Maybe like, fetch currentMonth sheet or something?

}

void MainWindow::on_nextDay_clicked()
{
    // Increment the current day by 1.
    _IncrementDayOfLocalAppTime();
    ui->startOfCurrentMonth->setText(_GetLocalAppTime().toString("dd-MM-yyyy"));
}


void MainWindow::on_previousDay_clicked()
{
    // Decrement the current day by 1.
    _DecrementDayOfLocalAppTime();
    ui->startOfCurrentMonth->setText(_GetLocalAppTime().toString("dd-MM-yyyy"));
}

