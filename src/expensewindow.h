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

public:
    explicit ExpenseWindow(QWidget *parent = nullptr);
    ~ExpenseWindow();

private slots:

    void on_dailyExpenses_returnPressed();

    void on_nextDay_clicked();

    void on_previousDay_clicked();

private:
    Ui::ExpenseWindow *ui;
    const QDateTime _worldClockTime = QDateTime::currentDateTime();
    QDate _localAppTime;

    void _SetLocalAppTime(QDate newLocalAppTime){
        _localAppTime = newLocalAppTime;
    }
    void _InitializeCurrentMonth(void);
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
    QDateTime _GetCurrentTime(void) const{

            return _worldClockTime;
        }

    QDate _GetLocalAppTime(void) const{
        return _localAppTime;
    }

    void _IncrementDayOfLocalAppTime(void){
        _SetLocalAppTime(_GetLocalAppTime().addDays(1));
    }

    void _DecrementDayOfLocalAppTime(void){
        _SetLocalAppTime(_GetLocalAppTime().addDays(-1));
    }
};

#endif // EXPENSEWINDOW_H
