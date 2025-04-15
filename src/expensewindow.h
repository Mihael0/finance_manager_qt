#ifndef EXPENSEWINDOW_H
#define EXPENSEWINDOW_H
// QT includes
#include <QWidget>
#include <QCalendarWidget>
// Project Includes
#include <eventeater.h>
#include <expensemanager.h>
#include <apptime.h>

namespace Ui {
class ExpenseWindow;
}

class ExpenseWindow : public QWidget
{
    Q_OBJECT

public slots:
    /*
     * @brief This slot is used by the MainWindow to notify the ExpenseWindow that it must show up.
     */
    void showExpenseWindow(void);

    /*
     * @brief This slot is used by the EventEater to notify the ExpenseWindow that it must show a calendar.
     */
    void showCalendar(void);

signals:
    /*
     * @brief This signal is emitted to notify the MainWindow that the ExpenseWindow should be closed.
     */
    void closeExpenseWindowRequested(void);

public:
    explicit ExpenseWindow(QWidget *parent = nullptr);
    ~ExpenseWindow();

private slots:
    /*
     * @brief Slot triggered when the Enter is pressed on the keyboard.
     * The slot is responsible for validating and storing the inputted expense and date by the user.
     */
    void on_dailyExpenses_returnPressed();
    /*
     * @brief Slot triggered when the nextDay button is pressed.
     * It increments the current date by one.
     */
    void on_nextDay_clicked();
    /*
     * @brief Slot triggered when the previousDay button is pressed.
     * It decrements the current date by one.
     */
    void on_previousDay_clicked();
    /*
     * @brief Slot triggered when the BackBtn is pressed.
     * It sends out a signal that tells the MainWindow that the user
     * is requesting that this window be closed.
     */
    void on_backBtn_clicked();
    /*
     * @brief Slot triggered by the submitExpense button.
     * It takes all of the inputted expenses and sends them to the server for storage.
     */
    void on_submitExpense_clicked();
    /*
     * @brief Slot triggered by the leftExpense button.
     * It moves the currently selected expense one to the left and shows it to the user.
     */
    void on_leftExpense_clicked();
    /*
     * @brief Slot triggered by the rightExpense button.
     * It moves the currently selected expense one to the right and shows it to the user.
     */
    void on_rightExpense_clicked();
    /*
     * @brief Slot triggered by the maxRight button.
     * It moves the currently selected expense maximum to the right and shows it to the user.
     */
    void on_maxRight_clicked();
    /*
     * @brief Slot triggered by the maxLight button.
     * It moves the currently selected expense maximum to the left and shows it to the user.
     */
    void on_maxLeft_clicked();

private:
    Ui::ExpenseWindow *ui;
    EventEater *_keyPressEater = nullptr;
    QCalendarWidget *_calendar = nullptr;
    ExpenseManager *_expenseManager = nullptr;
    AppTime *_appTime = nullptr;

    /*
     * @brief Uses the ui to display the currently selected expense value and expense date to the user.
     */
    void _DisplayExpenseInfo(const ExpenseInfo* selectedExpense);
    /*
     * @brief Stores the current date and whatever the user had written in the dailyExpense box
     */
    void _StorePendingInput(void);
    /*
     * @brief Displays the stored date and whatever the use had written in the dailyExpense box.
     */
    void _DisplayPendingInput(const LastExpenseData* restoredUserInput);
    /*
     * @brief Template that can take it multiple arguments that are then used to set the expenseDate
     * and are then displayed to the user.
     */
    template<typename T>
    void _SetNDisplayLocalAppTime(const T& newLocalAppTime,
                                  typename
                                  std::enable_if<std::is_same<T,QDate>::value
                                    || std::is_same<T,QDateTime>::value
                                    || std::is_same<T,QString>::value>::type* = 0);
};
#endif // EXPENSEWINDOW_H
