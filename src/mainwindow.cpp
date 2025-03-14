#include <mainwindow.h>
#include <ui_mainwindow.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _logIn(new LogInWindow())
{
    ui->setupUi(this);
    QObject::connect(_logIn,&LogInWindow::authenthicationSucceeded,this,&MainWindow::showMainWindow);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::IsAuthenthicationAccepted(void){
    if(_logIn){
        _logIn->show();
        return _logIn->exec();
    }
    return QDialog::Rejected;
}

void MainWindow::on_declareExpenseBtn_clicked(void)
{
    if(_declareExpense != nullptr){
        return;
    }
    // Connection for DeclareExpense to know to show itself to the user.
    _declareExpense = new ExpenseWindow();
    QObject::connect(this,&MainWindow::declareExpenseWindowRequested,_declareExpense,&ExpenseWindow::showExpenseWindow);
    // Connection to reset DeclareExpense to nullptr
    QObject::connect(_declareExpense, &ExpenseWindow::closeExpenseWindowRequested,this,&MainWindow::expenseWindowRequestsBack);

    this->hide();
    emit declareExpenseWindowRequested();
}

void MainWindow::showMainWindow(void){
    if(_logIn == nullptr){
        return;
    }
    // This makes sure _logIn gets deleted after the
    // loop executes. Otherwise a race condition might
    // be created.
    _logIn->deleteLater();
    _logIn = nullptr;
    this->show();
}

void MainWindow::expenseWindowRequestsBack(void){
    if(_declareExpense == nullptr){
        return;
    }

    delete _declareExpense;
    _declareExpense = nullptr;
    this->show();
}

void MainWindow::on_recurringExpenseBtn_clicked()
{
    if(_recurringExpense != nullptr){
        return;
    }
    // Connection for _recurringExpense to know to show itself to the user.
    _recurringExpense = new RecurringExpenseWindow();
    QObject::connect(this,&MainWindow::recurringExpenseWindowRequested,_recurringExpense,&RecurringExpenseWindow::showRecurringExpenseWindow);
    // Connection to reset _recurringExpense to nullptr
    QObject::connect(_recurringExpense, &RecurringExpenseWindow::closeRecurringExpenseWindowRequested,this,&MainWindow::recurringExpenseWindowRequestsBack);

    this->hide();
    emit recurringExpenseWindowRequested();
}

void MainWindow::recurringExpenseWindowRequestsBack(void){
    if(_recurringExpense == nullptr){
        return;
    }

    delete _recurringExpense;
    _recurringExpense = nullptr;
    this->show();
}

void MainWindow::on_createSummaryBtn_clicked()
{
    if(_createSummary != nullptr){
        return;
    }
    // Connection for _createSummary to know to show itself to the user.
    _createSummary = new CreateSummaryWindow();
    QObject::connect(this,&MainWindow::createSummaryWindowRequested,_createSummary,&CreateSummaryWindow::showCreateSummaryWindow);
    // Connection to reset _createSummary to nullptr
    QObject::connect(_createSummary, &CreateSummaryWindow::closeCreateSummaryWindowRequested,this,&MainWindow::createSummaryWindowRequestsBack);

    this->hide();
    emit createSummaryWindowRequested();
}

void MainWindow::createSummaryWindowRequestsBack(void){
    if(_createSummary == nullptr){
        return;
    }

    delete _createSummary;
    _createSummary = nullptr;
    this->show();
}
