#ifndef EXPENSEWINDOW_H
#define EXPENSEWINDOW_H

#include <QWidget>
#include <QDateTime>

struct ExpenseInfo{
    float expenseValue;
    QString expenseDate;
};

struct ExpenseData{
    std::vector<ExpenseInfo> dailyExpense;
    int nExpenses = 0;
};

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

signals:
    /*
     * @brief This signal is emitted to notify the MainWindow that the ExpenseWindow should be closed.
     */
    void closeExpenseWindowRequested(void);

public:
    explicit ExpenseWindow(QWidget *parent = nullptr);
    ~ExpenseWindow();
    ExpenseData GetExpenses(void){
        return _expenses;
    }

private slots:

    void on_dailyExpenses_returnPressed();

    void on_nextDay_clicked();

    void on_previousDay_clicked();

    void on_backBtn_clicked();

    void on_submitExpense_clicked();

    void on_previousExpense_clicked();

private:
    Ui::ExpenseWindow *ui;
    const QDateTime _worldClockTime = QDateTime::currentDateTime();
    QDate _localAppTime;
    ExpenseData _expenses;
    int _previousExpenseIndex;

    /*
     * @brief Sets the declaredExpense and increments the iterator for the next value.
     */
    void _SetExpenses(const float declaredExpense, const QString& dateOfExpense){
        _expenses.dailyExpense.push_back({declaredExpense, dateOfExpense});
        _expenses.nExpenses++;
    }
    /*
     * @brief This function is used to change the value of _localAppTime.
     */
    void _SetLocalAppTime(QDate newLocalAppTime){
        _localAppTime = newLocalAppTime;
    }
    /*
     * @detail Initializes _localAppTime to be the start of the month.
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
