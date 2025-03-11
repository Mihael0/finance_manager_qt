#ifndef EXPENSEWINDOW_H
#define EXPENSEWINDOW_H

#include <QWidget>
#include <QDateTime>

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
    void on_DailyExpensesBtn_pressed(void);

signals:
    /*
     * @brief This signals is emitted to notify the MainWindow that the ExpenseWindow has been closed.
     */
    void on_BackBtn_pressed(void);

public:
    explicit ExpenseWindow(QWidget *parent = nullptr);
    ~ExpenseWindow();

private slots:

    void on_dailyExpenses_returnPressed();

    void on_nextDay_clicked();

    void on_previousDay_clicked();

    void on_back_clicked();

private:
    Ui::ExpenseWindow *ui;
    const QDateTime _worldClockTime = QDateTime::currentDateTime();
    QDate _localAppTime;
    /*
     * @brief This function is used to change the value of _localAppTime.
     */
    void _SetLocalAppTime(QDate newLocalAppTime){
        _localAppTime = newLocalAppTime;
    }
    /*
     * Initializes _localAppTime to be the start of the month.
     * Make sure this, or another initialization function of _localAppTime is called
     * before using any of the setters/gettters of _localAppTime.
     * Failing to do so, will lead to undefined behaviour.
     */
    void _SetAppTimeToStartOfMonth(void){
        QDate StartOfMonthTime = _worldClockTime.date();
        StartOfMonthTime.setDate(StartOfMonthTime.year(), StartOfMonthTime.month(),1);
        _SetLocalAppTime(StartOfMonthTime);
    }
    /*
     * @return the current time in the world taken from the QDateTime library. This time is the computer's set time.
     */
    QDateTime _GetCurrentTime(void) const{
        return _worldClockTime;
    }
    /*
     * @return _localAppTime, which is the internal variable used to keep track of the user specified day/month/year.
     */
    QDate _GetLocalAppTime(void) const{
        return _localAppTime;
    }
    /*
     * @brief Increments the LocalAppTime by 1 day. Uses the QDateTime library to handle transition between months.
     */
    void _IncrementDayOfLocalAppTime(void){
        _SetLocalAppTime(_GetLocalAppTime().addDays(1));
    }
    /*
     * @brief Decrements the LocalAppTime by 1 day. Uses the QDateTime library to handle transition between months.
     */
    void _DecrementDayOfLocalAppTime(void){
        _SetLocalAppTime(_GetLocalAppTime().addDays(-1));
    }
};

#endif // EXPENSEWINDOW_H
