#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "timeutils.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->startOfCurrentMonth->setFrame(false);
    InitializeCurrentMonth();
    TimeUtils::instance().SetAppTimeToStartOfMonth();
    ui->startOfCurrentMonth->setText(TimeUtils::instance().GetLocalAppTime().toString("dd-MM-yyyy"));
}

void MainWindow::InitializeCurrentMonth(void) const{
    ui->currentMonth->setFrame(false);
    ui->currentMonth->setText(TimeUtils::instance().GetCurrentTime().toString("dd-MM-yyyy"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_dailyExpenses_returnPressed()
{

}


void MainWindow::on_nextDay_clicked()
{
    TimeUtils::instance().IncrementDayOfAppTime(1);
    ui->startOfCurrentMonth->setText(TimeUtils::instance().GetLocalAppTime().toString("dd-MM-yyyy"));
}

