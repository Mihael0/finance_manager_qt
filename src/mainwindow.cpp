#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "timeutils.h"

// non-POD static.
// Means that there might be a chance that the constructor of this is called before it is declared.
// It is stated here that it might not be a problem https://stackoverflow.com/questions/1538137/c-static-global-non-pod-theory-and-practice
// But it is not certain. For now, I am unsure on how to address this without using a Singleton if this is to be removed.
// Will test it and if the problem does not arise, it will be kept like this. Hopefully not code debt.
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
    // And we pass the LocalApptime.
    // We need to have access to the created sheets
    // Maybe like, fetch currentMonth sheet or something?

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

