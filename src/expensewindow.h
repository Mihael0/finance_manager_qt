#ifndef EXPENSEWINDOW_H
#define EXPENSEWINDOW_H

#include <QWidget>
#include <QDateTime>
#include <type_traits>
#include <QCalendarWidget>
#include <eventeater.h>
#include <QVBoxLayout>
#include <QToolButton>
#include <QMessageBox>
#include <expensemanager.h>

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

private:
    Ui::ExpenseWindow *ui;
    const QDateTime _worldClockTime = QDateTime::currentDateTime();
    QDate _localAppTime;
    EventEater *_keyPressEater = nullptr;
    QCalendarWidget *_calendar = nullptr;
    ExpenseManager *_expenseManager = nullptr;

    /*
     * @brief Sets the value of _localAppTime. This function can accept either QDateTime or QDate arguments.
     * If the argument is QDateTime then it will take only the date from it and assign it.
     */
    template<typename T>
    void _SetLocalAppTime(const T& newlocalAppTime,
                     typename std::enable_if<std::is_same<T,QDate>::value
                    || std::is_same<T,QDateTime>::value
                    || std::is_same<T,QString>::value>::type* = 0){

        if constexpr (std::is_same<T,QDateTime>::value){
            _localAppTime = newlocalAppTime.date();
        } else if constexpr (std::is_same<T,QString>::value) {
            QDate date = QDate::fromString(newlocalAppTime, "dd-MM-yyyy");
            _localAppTime = date;
        }else{
            _localAppTime = newlocalAppTime;
        }
    }
    /*
     * @detail Initializes _localAppTime to be the start of the month.
     * Make sure this, or another initialization function of _localAppTime is called
     * before using any of the setters/gettters of _localAppTime.
     * Failing to do so, will lead to undefined behaviour.
     */
    void _InitializeAppTimeToStartOfMonth(void){
        QDate StartOfMonthTime = _worldClockTime.date();
        StartOfMonthTime.setDate(StartOfMonthTime.year(), StartOfMonthTime.month(),1);
        _SetLocalAppTime(StartOfMonthTime);
        // tmpExpenseData.tmpExpenseDate = _GetLocalAppTime();
    }
    /*
     * @return the current time in the world taken from the QDateTime library. This is the computer's set time.
     */
    QDateTime _GetWorldTime(void) const{
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

    void _DisplayExpenseInfo(const ExpenseInfo* selectedExpense);
    void _StorePendingInput(void);
    void _DisplayPendingInput(const LastExpenseData* restoredUserInput);
};

#endif // EXPENSEWINDOW_H
