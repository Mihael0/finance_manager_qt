#include <mainwindow.h>
#include <ui_mainwindow.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_DeclareExpenseBtn_clicked(void)
{
    if(DeclareExpense != nullptr){
        return;
    }
    // Connection for DeclareExpense to know to show itself to the user.
    DeclareExpense = new ExpenseWindow();
    QObject::connect(this,&MainWindow::declareExpenseWindowRequested,DeclareExpense,&ExpenseWindow::showExpenseWindow);
    // Connection to reset DeclareExpense to nullptr
    QObject::connect(DeclareExpense, &ExpenseWindow::closeExpenseWindowRequested,this,&MainWindow::expenseWindowRequestsBack);

    // ExpenseWindowRequestsBack
    this->hide();
    emit declareExpenseWindowRequested();
}

void MainWindow::showMainWindow(void){
    this->show();
}

void MainWindow::expenseWindowRequestsBack(void){
    if(DeclareExpense == nullptr){
        return;
    }

    delete DeclareExpense;
    DeclareExpense = nullptr;
    this->show();
}

void MainWindow::on_RecurringExpenseBtn_clicked()
{
    if(RecurringExpense != nullptr){
        return;
    }
    // Connection for RecurringExpense to know to show itself to the user.
    RecurringExpense = new RecurringExpenseWindow();
    QObject::connect(this,&MainWindow::recurringExpenseWindowRequested,RecurringExpense,&RecurringExpenseWindow::showRecurringExpenseWindow);
    // Connection to reset RecurringExpense to nullptr
    QObject::connect(RecurringExpense, &RecurringExpenseWindow::closeRecurringExpenseWindowRequested,this,&MainWindow::recurringExpenseWindowRequestsBack);

    emit recurringExpenseWindowRequested();
}

void MainWindow::recurringExpenseWindowRequestsBack(void){
    if(RecurringExpense == nullptr){
        return;
    }

    delete RecurringExpense;
    RecurringExpense = nullptr;
    this->show();
}
