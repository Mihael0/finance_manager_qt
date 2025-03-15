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
    void on_declareExpenseBtn_clicked();

    void on_recurringExpenseBtn_clicked();

    void on_createSummaryBtn_clicked();

private:
    Ui::MainWindow *ui;
    ExpenseWindow *_declareExpense = nullptr;
    RecurringExpenseWindow *_recurringExpense = nullptr;
    CreateSummaryWindow *_createSummary = nullptr;
    LogInWindow *_logIn = nullptr;
};
#endif // MAINWINDOW_H
