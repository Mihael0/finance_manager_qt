#include "expensewindow.h"
#include "ui_expensewindow.h"
#include "QMessageBox"
#include "QString"

ExpenseWindow::ExpenseWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ExpenseWindow){

    // Make sure this function is called as soon as possible.
    _InitializeAppTimeToStartOfMonth();
    ui->setupUi(this);
    if(ui){
        ui->currentMonth->setFrame(false);
        ui->currentMonth->setText(_GetWorldTime().toString("dd-MM-yyyy"));
        ui->dateOfExpense->setText(_GetLocalAppTime().toString("dd-MM-yyyy"));
        ui->label_10->setText("<ul>"
                             "<li>Input an expense in the Daily Expense box.</li>"
                             "<li>Then press the Next Day button to increase the day.</li>"
                             "<li>Whenever you are done, press the Declare Expenses to store all of your submitted expenses.</li>"
                             "</ul>");
        _keyPressEater = new EventEater(this);
        ui->dateOfExpense->installEventFilter(_keyPressEater);
        QObject::connect(_keyPressEater,&EventEater::showCalendarRequested,this,&ExpenseWindow::showCalendar);
    }
}

ExpenseWindow::~ExpenseWindow(){
    delete ui;
    delete _keyPressEater;
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
    ui->dateOfExpense->setText(_GetLocalAppTime().toString("dd-MM-yyyy"));
}

void ExpenseWindow::on_previousDay_clicked(){
    // Decrement the current day by 1.
    _DecrementDayOfLocalAppTime();
    ui->dateOfExpense->setText(_GetLocalAppTime().toString("dd-MM-yyyy"));
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

void ExpenseWindow::on_previousExpense_clicked(){
    _IncrementExpnsIndex();
    ExpenseInfo selectedExpense = _IndexDeclaredExpenses();
    ui->dateOfExpense->setText(selectedExpense.expenseDate);
    ui->dailyExpenses->setText(QString::number(selectedExpense.expenseValue, 'f', 2));
}

void ExpenseWindow::on_nextExpense_clicked(){
    _DecrementExpnsIndex();
    ExpenseInfo selectedExpense = _IndexDeclaredExpenses();
    ui->dateOfExpense->setText(selectedExpense.expenseDate);
    ui->dailyExpenses->setText(QString::number(selectedExpense.expenseValue, 'f', 2));
}

void ExpenseWindow::showCalendar()
{
    _calendar = new QCalendarWidget();
    _calendar->setWindowFlags(Qt::Popup);
    _calendar->move(QCursor::pos());
    _calendar->show();

    connect(_calendar, &QCalendarWidget::clicked, this, [=](const QDate& date){
        ui->dateOfExpense->setText(date.toString("dd-MM-yyyy"));
        _selectedDate = date;
        _calendar->close();
    });
}
