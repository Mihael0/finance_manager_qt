#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->startOfCurrentMonth->setFrame(false);
    _SetAppTimeToStartOfMonth();
    InitializeCurrentMonth();
    ui->startOfCurrentMonth->setText(MainWindow::GetLocalAppTime().toString("dd-MM-yyyy"));
}

void MainWindow::InitializeCurrentMonth(void) const{
    ui->currentMonth->setFrame(false);
    ui->currentMonth->setText(MainWindow::GetCurrentTime().toString("dd-MM-yyyy"));
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
    MainWindow::IncrementDayOfLocalAppTime();
    ui->startOfCurrentMonth->setText(MainWindow::GetLocalAppTime().toString("dd-MM-yyyy"));
}


void MainWindow::on_previousDay_clicked()
{
    // Decrement the current day by 1.
    MainWindow::DecrementDayOfLocalAppTime();
    ui->startOfCurrentMonth->setText(MainWindow::GetLocalAppTime().toString("dd-MM-yyyy"));
}

QDateTime MainWindow::GetCurrentTime(void) const{

    return MainWindow::_worldClockTime;
}

QDate MainWindow::GetLocalAppTime(void){
    return MainWindow::_localAppTime;
}

void MainWindow::IncrementDayOfLocalAppTime(void){
    _SetLocalAppTime(GetLocalAppTime().addDays(1));
}

void MainWindow::DecrementDayOfLocalAppTime(void){
    _SetLocalAppTime(GetLocalAppTime().addDays(-1));
}

