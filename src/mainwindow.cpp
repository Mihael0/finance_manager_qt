#include <mainwindow.h>
#include <ui_mainwindow.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _logIn(new LogInWindow(this)){
    ui->setupUi(this);
    _SetupLogInWindow();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::ShowLogInWindow(void){
    _logIn->show();
}

void MainWindow::on_declareExpenseBtn_clicked(void){
    _SetupExpenseWindow();
    this->hide();
    emit declareExpenseWindowRequested();
}

void MainWindow::showMainWindow(void){
    _logIn->deleteLater();
    this->show();
}

void MainWindow::expenseWindowRequestsBack(void){
    _declareExpense->deleteLater();
    this->show();
}

void MainWindow::on_recurringExpenseBtn_clicked(){
    _SetupRecurringExpenseWindow();
    this->hide();
    emit recurringExpenseWindowRequested();
}

void MainWindow::recurringExpenseWindowRequestsBack(void){
    _recurringExpense->deleteLater();
    this->show();
}

void MainWindow::on_createSummaryBtn_clicked(){
    this->hide();
    emit createSummaryWindowRequested();
}

void MainWindow::createSummaryWindowRequestsBack(void){
    _createSummary->deleteLater();
    this->show();
}
