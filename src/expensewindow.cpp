#include "expensewindow.h"
#include "ui_expensewindow.h"
#include "QMessageBox"
#include "QString"

ExpenseWindow::ExpenseWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ExpenseWindow)
    , _expenseManager(new ExpenseManager){

    // Make sure this function is called as soon as possible.
    _InitializeAppTimeToStartOfMonth();
    ui->setupUi(this);
    if(ui){
        ui->currentMonth->setFrame(false);
        ui->currentMonth->setText(_GetWorldTime().toString("dd-MM-yyyy"));
        ui->dateOfExpense->setText(_GetLocalAppTime().toString("dd-MM-yyyy"));
        ui->howToUseExpenses->setText("<ul>"
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
    delete _expenseManager;
}

void ExpenseWindow::_DisplayExpenseInfo(const ExpenseInfo* selectedExpense){
    ui->dailyExpenses->setText(QString::number(selectedExpense->expenseValue,'f', 2));
    _SetLocalAppTime(selectedExpense->expenseDate);
    ui->dateOfExpense->setText(_GetLocalAppTime().toString("dd-MM-yyyy"));
}

void ExpenseWindow::_StorePendingInput(void){
    QDate rAppTime = _GetLocalAppTime();
    QString rDailyExpenses = ui->dailyExpenses->text();
    _expenseManager->StoreUserInputtedData(rDailyExpenses,rAppTime);
}

void ExpenseWindow::_DisplayPendingInput(const LastExpenseData* restoredUserInput){
    ui->dailyExpenses->setText(restoredUserInput->lastDailyExpense);
    _SetLocalAppTime(restoredUserInput->lastExpenseDate);
}

// TODO: We have to check if the expense is a valid value.
// TODO: We have to check if the month value has changed.
// if that is the case, then we need to prompt the user if
// they would like to create a new excel file for that given month.
// if they say No, then they are returned to their previous value.
void ExpenseWindow::on_dailyExpenses_returnPressed(){
    if(_expenseManager->IsUserScrollingExpenses()){
        QMessageBox::warning(this, "Error", "Cannot submit expense. You are currently scrolling existing expenses. Press the right double arrow to return to inputting new expenses!");
        return;
    }

    bool isFloat = true;
    float expense = ui->dailyExpenses->text().toFloat(&isFloat);

    if(!isFloat){
        QMessageBox::warning(this, "Result", "Invalid Expense! Please submit a decimal number!");
        return;
    }
    // Passing by reference.
    QDate rLocalAppTime = _GetLocalAppTime();
    _expenseManager->SetExpenses(expense,rLocalAppTime);
    ui->dailyExpenses->clear();
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

void ExpenseWindow::showCalendar(){
    _calendar = new QCalendarWidget();
    _calendar->setWindowFlags(Qt::Popup);
    _calendar->move(QCursor::pos());
    _calendar->show();

    connect(_calendar, &QCalendarWidget::clicked, this, [=](const QDate& date){
        ui->dateOfExpense->setText(date.toString("dd-MM-yyyy"));
        _SetLocalAppTime(date);
        _calendar->close();
    });
}

void ExpenseWindow::on_leftExpense_clicked(){
    _expenseManager->MoveExpenseIndexLeft(1);

    if((_expenseManager->GetCurrentStateOfBoundry() == Boundry::Right
        || _expenseManager->GetCurrentStateOfBoundry() == Boundry::LeftRight) // This is in the case of expense size of 1.
        && _expenseManager->GetPreviousStateOfBoundry() == Boundry::HeadOfVector){
        _StorePendingInput();
    }

    const ExpenseInfo* selectedExpense = _expenseManager->GetExpenseAtMovingIndex();
    if(selectedExpense == nullptr){
        QMessageBox::warning(this, "Error", "No Expenses to select");
        return;
    }

    _DisplayExpenseInfo(selectedExpense);
}

void ExpenseWindow::on_rightExpense_clicked(){
    _expenseManager->MoveExpenseIndexRight(1);

    if(_expenseManager->GetCurrentStateOfBoundry() == Boundry::HeadOfVector
        && _expenseManager->GetPreviousStateOfBoundry() != Boundry::HeadOfVector){
        const LastExpenseData* restoredUserInput = _expenseManager->RestoreUserInputtedData();
        _DisplayPendingInput(restoredUserInput);
        return;
    }

    const ExpenseInfo* selectedExpense = _expenseManager->GetExpenseAtMovingIndex();
    if(selectedExpense == nullptr){
        QMessageBox::warning(this, "Error", "No Expenses to select");
        return;
    }

    _DisplayExpenseInfo(selectedExpense);
}

void ExpenseWindow::on_maxRight_clicked(){
    // Restart the Boundry state to HeadOfVector
    _expenseManager->MoveExpenseIndexMaxRight();

    if(_expenseManager->GetCurrentStateOfBoundry() == Boundry::HeadOfVector
        && _expenseManager->GetPreviousStateOfBoundry() != Boundry::HeadOfVector){
        const LastExpenseData* restoredUserInput = _expenseManager->RestoreUserInputtedData();
        _DisplayPendingInput(restoredUserInput);
        return;
    }
}


void ExpenseWindow::on_maxLeft_clicked(){
    // Move the Boundry state to Left
    _expenseManager->MoveExpenseIndexMaxLeft();

    if(_expenseManager->GetPreviousStateOfBoundry() == Boundry::HeadOfVector){
        _StorePendingInput();
    }

    const ExpenseInfo* selectedExpense = _expenseManager->GetExpenseAtMovingIndex();
    if(selectedExpense == nullptr){
        QMessageBox::warning(this, "Error", "No Expenses to select");
        return;
    }

    _DisplayExpenseInfo(selectedExpense);
}

