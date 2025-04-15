#ifndef EXPENSEWINDOW_H
#define EXPENSEWINDOW_H
// QT includes
#include <QWidget>
#include <QCalendarWidget>
#include <QToolButton>
#include <QMessageBox>
// General C++ includes
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

    void on_dailyExpenses_returnPressed();

    void on_nextDay_clicked();

    void on_previousDay_clicked();

    void on_backBtn_clicked();

    void on_submitExpense_clicked();

    void on_leftExpense_clicked();

    void on_rightExpense_clicked();

    void on_maxRight_clicked();

    void on_maxLeft_clicked();

private:
    Ui::ExpenseWindow *ui;
    EventEater *_keyPressEater = nullptr;
    QCalendarWidget *_calendar = nullptr;
    ExpenseManager *_expenseManager = nullptr;
    AppTime *_appTime = nullptr;

    void _DisplayExpenseInfo(const ExpenseInfo* selectedExpense);
    void _StorePendingInput(void);
    void _DisplayPendingInput(const LastExpenseData* restoredUserInput);
    template<typename T>
    void _SetNDisplayLocalAppTime(const T& newLocalAppTime,
                                  typename
                                  std::enable_if<std::is_same<T,QDate>::value
                                    || std::is_same<T,QDateTime>::value
                                    || std::is_same<T,QString>::value>::type* = 0);
};
#endif // EXPENSEWINDOW_H
