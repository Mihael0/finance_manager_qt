#include "expensewindow.h"
#include "ui_expensewindow.h"
#include "QString"
#include "excel.h"

ExpenseWindow::ExpenseWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ExpenseWindow)
{
    _SetAppTimeToStartOfMonth();

    ui->setupUi(this);
    if(ui){
        ui->currentMonth->setFrame(false);
        ui->startOfCurrentMonth->setFrame(false);
        ui->currentMonth->setText(_GetCurrentTime().toString("dd-MM-yyyy"));
        ui->startOfCurrentMonth->setText(_GetLocalAppTime().toString("dd-MM-yyyy"));
    }

}

ExpenseWindow::~ExpenseWindow(){
    delete ui;
}

// TODO: We have to check if the expense is a valid value.
// TODO: We have to check if the month value has changed.
// if that is the case, then we need to prompt the user if
// they would like to create a new excel file for that given month.
// if they say No, then they are returned to their previous value.
void ExpenseWindow::on_dailyExpenses_returnPressed(){
    QString bookName = _GetCurrentTime().toString("MM-yyyy");
    QString sheetName = "DailyExpenses";
    Excel DailyExpense{bookName, sheetName,MONTHLY_EXPENSE};
    double dailyExpense = ui->dailyExpenses->text().toFloat();
    QString currentDate = _GetLocalAppTime().toString("dd-MM-yyyy");
    DailyExpense.StoreDailyExpense(dailyExpense, currentDate);
}

void ExpenseWindow::on_nextDay_clicked(){
    // Increment the current day by 1.
    _IncrementDayOfLocalAppTime();
    ui->startOfCurrentMonth->setText(_GetLocalAppTime().toString("dd-MM-yyyy"));
}

void ExpenseWindow::on_previousDay_clicked(){
    // Decrement the current day by 1.
    _DecrementDayOfLocalAppTime();
    ui->startOfCurrentMonth->setText(_GetLocalAppTime().toString("dd-MM-yyyy"));
}

void ExpenseWindow::on_back_clicked(){
    this->close();
    emit on_BackBtn_pressed();
}

void ExpenseWindow::on_DailyExpensesBtn_pressed(void){
    this->show();
}

