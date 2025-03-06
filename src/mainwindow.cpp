#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "excel.h"

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
// TODO: We have to check if the expense is a valid value.
// TODO: We have to check if the month value has changed.
// if that is the case, then we need to prompt the user if
// they would like to create a new excel file for that given month.
// if they say No, then they are returned to their previous value.
void MainWindow::on_dailyExpenses_returnPressed()
{
    QString bookName = _GetCurrentTime().toString("MM-yyyy");
    QString sheetName = "DailyExpenses";
    Excel DailyExpense{bookName, sheetName,MONTHLY_EXPENSE};
    double dailyExpense = ui->dailyExpenses->text().toFloat();
    DailyExpense.StoreDailyExpense(dailyExpense);

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

