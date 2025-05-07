#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <expensewindow.h>
#include <recurringexpensewindow.h>
#include <createsummarywindow.h>
#include <loginwindow.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    /*
     * @brief This slot handles the signal emitted from LogIn window.
     * It shows the MainWindow to the user.
     */
    void showMainWindow(void);
    /*
     * @brief This slot handles the signal emitted whenever a
     * back button is pressed in the ExpenseWindow. It makes
     * sure that the resources allocated to ExpenseWindow are
     * deallocated and shows the MainWindow to the user.
     */
    void expenseWindowRequestsBack(void);
    /*
     * @brief This slot handles the signal emitted whenever a
     * back button is pressed in the RecurringExpenseWindow. It makes
     * sure that the resources allocated to RecurringExpenseWindow are
     * deallocated and shows the MainWindow to the user.
     */
    void recurringExpenseWindowRequestsBack(void);
    /*
     * @brief This slot handles the signal emitted whenever a
     * back button is pressed in the CreateSummaryWindow. It makes
     * sure that the resources allocated to CreateSummaryWindow are
     * deallocated and shows the MainWindow to the user.
     */
    void createSummaryWindowRequestsBack(void);

signals:
    /*
     * @brief This signal is emitted whenever the on_DeclareExpenseBtn_clicked() slot is called.
     * It's purpose is to notify the ExpenseWindow that it must show itself to the user.
     */
    void declareExpenseWindowRequested(void);
    /*
     * @brief This signal is emitted whenever the on_RecurringExpenseBtn_clicked() slot is triggered by the UI.
     */
    void recurringExpenseWindowRequested(void);
    /*
     * @brief This signal is emitted whenever the on_RecurringExpenseBtn_clicked() slot is triggered by the UI.
     */
    void createSummaryWindowRequested(void);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    /*
     * @brief Uses the private class _logIn to show the LogInWindow to the user.
     */
    void ShowLogInWindow(void);

private slots:
    /*
     * @brief Slot connected to the DeclareExpensesBtn. It emits a signal notifying the ExpenseWindow to show up to the user.
     */
    void on_declareExpenseBtn_clicked();
    /*
     * @brief Slot connected to the RecurringExpenseBtn. It emits a signal notifying the RecurringExpenseWindow to show up to the user.
     */
    void on_recurringExpenseBtn_clicked();
    /*
     * @brief Slot connected to the CreateSummaryBtn. It emits a signal notifying the CreateSummaryWindow to show up to the user.
     */
    void on_createSummaryBtn_clicked();

private:
    // Has to be deleted manually
    Ui::MainWindow *ui;
    // All of them inherit from QObject and use QT's integrated memory management.
    ExpenseWindow *_declareExpense = nullptr;
    RecurringExpenseWindow *_recurringExpense = nullptr;
    CreateSummaryWindow *_createSummary = nullptr;
    LogInWindow *_logIn = nullptr;
    // Private member variables
    /*
     * @brief populates LogIn window.
     */
    void _SetupLogInWindow(void){
        QObject::connect(_logIn,&LogInWindow::authenthicationSucceeded,this,&MainWindow::showMainWindow);
        // Tells QT that it should be treated as a Top-level Window.
        // Instead of treating it as a child widget.
        _logIn->setWindowFlags(Qt::Window);
    }
    /*
     * @brief populates the expense window object and makes any nesseccary signal slot connections required for that window to function.
     */
    void _SetupExpenseWindow(void){
        _declareExpense = new ExpenseWindow(this);
        // Tells QT that it should be treated as a Top-level Window.
        // Instead of treating it as a child widget.
        _declareExpense->setWindowFlags(Qt::Window);
        QObject::connect(this,&MainWindow::declareExpenseWindowRequested,_declareExpense,&ExpenseWindow::showExpenseWindow);
        // Connection to reset DeclareExpense to nullptr
        QObject::connect(_declareExpense, &ExpenseWindow::closeExpenseWindowRequested,this,&MainWindow::expenseWindowRequestsBack);
    }
    /*
     * @brief populates the recurring expense window object and makes any nesseccary signal slot connections required for that window to function.
     */
    void _SetupRecurringExpenseWindow(void){
        _recurringExpense = new RecurringExpenseWindow(this);
        // Tells QT that it should be treated as a Top-level Window.
        // Instead of treating it as a child widget.
        _recurringExpense->setWindowFlags(Qt::Window);
        QObject::connect(this,&MainWindow::recurringExpenseWindowRequested,_recurringExpense,&RecurringExpenseWindow::showRecurringExpenseWindow);
        // Connection to reset _recurringExpense to nullptr
        QObject::connect(_recurringExpense, &RecurringExpenseWindow::closeRecurringExpenseWindowRequested,this,&MainWindow::recurringExpenseWindowRequestsBack);
    }
    /*
     * @brief populates the create summary window object and makes any nesseccary signal slot connections required for that window to function.
     */
    void _SetupCreateSummaryWindow(void){
        _createSummary = new CreateSummaryWindow(this);
        // Tells QT that it should be treated as a Top-level Window.
        // Instead of treating it as a child widget.
        _createSummary->setWindowFlags(Qt::Window);
        QObject::connect(this,&MainWindow::createSummaryWindowRequested,_createSummary,&CreateSummaryWindow::showCreateSummaryWindow);
        // Connection to reset _createSummary to nullptr
        QObject::connect(_createSummary, &CreateSummaryWindow::closeCreateSummaryWindowRequested,this,&MainWindow::createSummaryWindowRequestsBack);
    }
};
#endif // MAINWINDOW_H
