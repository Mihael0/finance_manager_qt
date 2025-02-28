#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "timeutils.h"

static TimeUtils Time;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->startOfCurrentMonth->setFrame(false);
    InitializeCurrentMonth();
    ui->startOfCurrentMonth->setText(Time.GetLocalAppTime().toString("dd-MM-yyyy"));
}

void MainWindow::InitializeCurrentMonth(void) const{
    ui->currentMonth->setFrame(false);
    ui->currentMonth->setText(Time.GetCurrentTime().toString("dd-MM-yyyy"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_dailyExpenses_returnPressed()
{
    // Excel takes in the inputted float number.

}


void MainWindow::on_nextDay_clicked()
{
    // Increment the current day by 1.
    Time.IncrementDayOfLocalAppTime();
    ui->startOfCurrentMonth->setText(Time.GetLocalAppTime().toString("dd-MM-yyyy"));
}


void MainWindow::on_previousDay_clicked()
{
    // Decrement the current day by 1.
    Time.DecrementDayOfLocalAppTime();
    ui->startOfCurrentMonth->setText(Time.GetLocalAppTime().toString("dd-MM-yyyy"));
}

