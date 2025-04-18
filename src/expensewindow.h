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

enum class UIState {
    Startup,
    DeclaringExpenses,
    Scrolling,
    EditDelete,
};

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
    void UpdateUIState();
    /*
     * @brief Slot triggered when the Enter is pressed on the keyboard.
     * The slot is responsible for validating and storing the inputted expense and date by the user.
     */
    void on_DailyExpenses_returnPressed();
    /*
     * @brief Slot triggered when the nextDay button is pressed.
     * It increments the current date by one.
     */
    void on_NextDay_clicked();
    /*
     * @brief Slot triggered when the previousDay button is pressed.
     * It decrements the current date by one.
     */
    void on_PreviousDay_clicked();
    /*
     * @brief Slot triggered when the BackBtn is pressed.
     * It sends out a signal that tells the MainWindow that the user
     * is requesting that this window be closed.
     */
    void on_BackBtn_clicked();
    /*
     * @brief Slot triggered by the submitExpense button.
     * It takes all of the inputted expenses and sends them to the server for storage.
     */
    void on_SubmitExpense_clicked();
    /*
     * @brief Slot triggered by the leftExpense button.
     * It moves the currently selected expense one to the left and shows it to the user.
     */
    void on_LeftExpense_clicked();
    /*
     * @brief Slot triggered by the rightExpense button.
     * It moves the currently selected expense one to the right and shows it to the user.
     */
    void on_RightExpense_clicked();
    /*
     * @brief Slot triggered by the maxRight button.
     * It moves the currently selected expense maximum to the right and shows it to the user.
     */
    void on_MaxRight_clicked();
    /*
     * @brief Slot triggered by the maxLight button.
     * It moves the currently selected expense maximum to the left and shows it to the user.
     */
    void on_MaxLeft_clicked();

private:
    Ui::ExpenseWindow *ui;
    EventEater *_keyPressEater = nullptr;
    QCalendarWidget *_calendar = nullptr;
    ExpenseManager *_expenseManager = nullptr;
    AppTime *_appTime = nullptr;
    UIState _currentUIState = UIState::Startup;
    QString _currentErrorText = "";
    bool _showCalendar = false;

    void _ClearDailyExpenses(void);
    void _ClearExpenseNote(void);
    QString _GetExpenseType(void) const;
    QString _GetExpenseNote(void) const;
    QString _GetDailyExpenses(void) const;
    void _SetShowCalendar(bool val){
        _showCalendar = val;
    }
    bool _GetShowCalendar(void) const{
        return _showCalendar;
    }
    void _ProcessUIStateChange(void);
    void _DisplayCurrentErrorText(void);
    void _SetErrorText(QString errorText){
        _currentErrorText = errorText;
    }
    const QString& _GetCurrentErrorText(void) const{
        return _currentErrorText;
    }
    void _UpdateUIBasedOnState(void);

    void _SetUIState(UIState state){
        _currentUIState = state;
    }
    const UIState& _GetCurrentUIState(void) const{
        return _currentUIState;
    }
    void _DisplayExpenseNote(QString noteToSet);
    void _InitializeTypeOfExpenses(void);
    void _SetErrorLabel(const QString& message);
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
    void _DisplayPendingInput(const LastExpenseInfo* restoredUserInput);
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
