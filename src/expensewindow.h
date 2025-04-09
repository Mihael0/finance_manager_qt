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

struct ExpenseInfo{
    float expenseValue;
    QString expenseDate;
};

struct ExpenseData{
    std::vector<ExpenseInfo> dailyExpense;
};

enum class ExpenseDirection{
    Backward,
    Forward,
};

struct TmpExpenseData{
    QString tmpDailyExpense;
    QDate tmpExpenseDate;
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
    ExpenseData GetExpenses(void){
        return _expenses;
    }
private slots:

    void on_dailyExpenses_returnPressed();

    void on_nextDay_clicked();

    void on_previousDay_clicked();

    void on_backBtn_clicked();

    void on_submitExpense_clicked();

    void on_backward_clicked();

    void on_forward_clicked();

    void on_dailyExpenses_editingFinished();

private:
    Ui::ExpenseWindow *ui;
    const QDateTime _worldClockTime = QDateTime::currentDateTime();
    QDate _localAppTime;
    ExpenseData _expenses;
    EventEater *_keyPressEater = nullptr;
    QCalendarWidget *_calendar = nullptr;
    int _expenseIndex = -1;

    void _IncrementExpnsIndex(void){
        // as long as we have not reached the lenght of the the vector. Continue incrementing.
        if(_expenseIndex != static_cast<int>(_GetExpenses().dailyExpense.size() - 1)){
            _expenseIndex++;
        }
    }

    void _DecrementExpnsIndex(void){
        // If we are not at the very front of the vector, decrement
        if(_expenseIndex != 0){
            _expenseIndex--;
        }else{
            // if we have reached the very front and the user has pressed forward
            // then we go beyond the vector, to the next value the user would like to add.
            _expenseIndex = -1;
        }
    }

    bool _isAtHeadOfVector(void){
        // We are at the head of the vector
        if(_expenseIndex == -1){
            return true;
        }

        return false;
    }

    ExpenseInfo* _IndexDeclaredExpenses(void){
        int adjustedIndex = 0;
        int sizeOfDailyExpense = static_cast<int>(_GetExpenses().dailyExpense.size() - 1);
        // User has not filled in any data for us to index.
        if(sizeOfDailyExpense <= 0){
            _expenseIndex = -1;
            return nullptr;
        }

        if(_expenseIndex == 0){
            adjustedIndex = sizeOfDailyExpense;
        } else {
            adjustedIndex = std::abs(_expenseIndex - sizeOfDailyExpense);
        }

        return &_GetExpenses().dailyExpense[adjustedIndex];
    }
    /*
     * @return the expenses struct which contains the currently inputted expenses by the user.
     */
    ExpenseData& _GetExpenses(void){
        return _expenses;
    }
    /*
     * @brief Sets the declaredExpense and increments the iterator for current and previous expense buttons.
     */
    void _SetExpenses(const float declaredExpense, const QString& dateOfExpense){
        _expenses.dailyExpense.push_back({declaredExpense, dateOfExpense});
    }
    /*
     * @brief Sets the value of _localAppTime. This function can accept either QDateTime or QDate arguments.
     * If the argument is QDateTime then it will take only the date from it and assign it.
     */
    template<typename T>
    void _SetLocalAppTime(const T& newlocalAppTime,
                     typename std::enable_if<std::is_same<T,QDate>::value || std::is_same<T,QDateTime>::value || std::is_same<T,QString>::value>::type* = 0){
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
};

#endif // EXPENSEWINDOW_H
