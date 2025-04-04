#include "expensewindow.h"
#include "ui_expensewindow.h"
#include "QMessageBox"
#include "QString"

ExpenseWindow::ExpenseWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ExpenseWindow){

    _SetAppTimeToStartOfMonth();
    ui->setupUi(this);
    if(ui){
        ui->currentMonth->setFrame(false);
        ui->startOfCurrentMonth->setFrame(false);
        ui->currentMonth->setText(_GetCurrentTime().toString("dd-MM-yyyy"));
        ui->startOfCurrentMonth->setText(_GetLocalAppTime().toString("dd-MM-yyyy"));
        ui->label_10->setText("<ul>"
                             "<li>Input an expense in the Daily Expense box.</li>"
                             "<li>Then press the Next Day button to increase the day.</li>"
                             "<li>Whenever you are done, press the Declare Expenses to store all of your submitted expenses.</li>"
                             "</ul>");
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
    bool isFloat = true;
    float expense = ui->dailyExpenses->text().toFloat(&isFloat);

    if(!isFloat){
        QMessageBox::warning(this, "Result", "Invalid Expense! Please submit a decimal number!");
        return;
    }
    _SetExpenses(expense,_GetLocalAppTime().toString("dd-MM-yyyy"));


    // QString bookName = _GetCurrentTime().toString("MM-yyyy");
    // QString sheetName = "DailyExpenses";
    // double dailyExpense = ui->dailyExpenses->text().toFloat();
    // QString currentDate = _GetLocalAppTime().toString("dd-MM-yyyy");
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

void ExpenseWindow::on_backBtn_clicked(){
    emit closeExpenseWindowRequested();
}

void ExpenseWindow::showExpenseWindow(void){
    this->show();
}

void ExpenseWindow::on_submitExpense_clicked(){
    on_dailyExpenses_returnPressed();
}

void ExpenseWindow::on_previousExpense_clicked()
{
    // _previousExpenseIndex
}

