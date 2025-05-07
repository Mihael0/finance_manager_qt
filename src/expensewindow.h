//TODO: Errors are not handled very well. They are a bit all over the place and the decision on how to handle them has been made on the spot,
// rather than making a design decision, there has been a lot of in-place decisions which could (and might have already) result in different
// implementations and mismatch in function returns.
// For example: Centralize it, make it a signleton or something and pass it to the objects.
#ifndef EXPENSEWINDOW_H
#define EXPENSEWINDOW_H
// QT includes
#include <QWidget>
#include <QCalendarWidget>
// Project Includes
#include <eventeater.h>
#include <expensemanager.h>
#include <apptime.h>
#include <QMessageBox>
namespace Ui {
class ExpenseWindow;
}

enum class UIState {
    Startup,
    SubmittingExpenses,
    Scrolling,
    Edit,
    Delete,
    DeclaringExpenses,
};

// This class is a largely One-Way Data Binding design. But, due to the fact that at certain points of operation of the program
// there is a need to show the inputted expenses (by the user) to the user, this entails a Two-Way Data Binding. That is the only
// situation whenever data is exchanged between the ExpenseManager and ExpenseWindow. Combined with the fact that they already
// have two way communication between each other, be it through events (signals and slots), or through composition, creates the Two-Way
// Data Binding design. So, please keep that in mind when interacting with this class.
class ExpenseWindow : public QWidget{
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

    void processDeclaringExpenses(bool isSendingSuccessful);

signals:
    /*
     * @brief This signal is emitted to notify the MainWindow that the ExpenseWindow should be closed.
     */
    void closeExpenseWindowRequested(void);

    void declareExpensesRequested(void);

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

    void on_Calendar_clicked(const QDate& clicked_date);

    void on_EditExpense_clicked();

    void on_DeleteExpense_clicked();

    void on_DeclareExpenses_clicked();

    void on_DeclareExpenses_finished(int usrResponse);

    void on_areExpensesSubmittedSuccessfullyBox_finished(int usrRespone);

private:
    // UI is deleted manually
    Ui::ExpenseWindow *ui;
    // Pointers that use QT's system
    ExpenseManager *_expenseManager = nullptr;
    EventEater *_keyPressEater = nullptr;
    QMessageBox *_submitExpensesConfirmBox = nullptr;
    QMessageBox *_areExpensesSubmittedSuccessfullyBox = nullptr;
    QMessageBox *_areYouSureYouWantToLeaveBox = nullptr;
    // Pointers that use std::unique_ptr
    std::unique_ptr<QCalendarWidget> _calendar;
    std::unique_ptr<AppTime> _appTime;
    // Private member variables
    UIState _currentUIState = UIState::Startup;
    QString _currentErrorText = "";
    bool _showCalendar = true;

    // For now a very basic check. In the future it should be much more extensive.
    // Most likely using an ENUM as a return type.
    // Also check that note is not beyond a certain limit of characters.
    bool _isExpenseValid(void);
    void _DeleteExpense(void){
        _expenseManager->EraseExpenseAtCurrentIndex();
        on_RightExpense_clicked();
        // _SetUIState(UIState::Scrolling);
        // _ProcessUIStateChange();
    }
    void _EditExpense(void){
        if(_isExpenseValid() == false){
            _SetErrorLabel("Invalid Expense! Please submit a decimal number!");
            return;
        }
        _expenseManager->ReplaceExpense(_GetDailyExpenseAsFloat(),_appTime->GetLocalAppTime(), _GetExpenseType(), _GetExpenseNote());
        _SetUIState(UIState::Scrolling);
        _ProcessUIStateChange();
    }

    void _DeclareExpense(void){
        if(_isExpenseValid() == false){
            _SetErrorLabel("Invalid Expense! Please submit a decimal number!");
            return;
        }
        _expenseManager->SetExpenses(_GetDailyExpenseAsFloat(),_appTime->GetLocalAppTime(), _GetExpenseType(), _GetExpenseNote());
        _ClearDailyExpenses();
        _ClearExpenseNote();
    }

    void _SetupCalendar(void){
        if(_calendar == nullptr){
            _calendar = std::make_unique<QCalendarWidget>();
        }
        _calendar->setWindowFlags(Qt::Popup);
        _calendar->move(QCursor::pos());
    }
    /*
     * @brief remove any currently written values from the QLineEdit of the Daily Expense.
     */
    void _ClearDailyExpenses(void);
    /*
     * @brief remove any currently written values from the QLineEdit of the Expense Note.
     */
    void _ClearExpenseNote(void);
    /*
     * @return the expense type taken from the UI
     */
    QString _GetExpenseType(void) const;
    /*
     * @return the expense note taken from the UI
     */
    QString _GetExpenseNote(void) const;
    /*
     * @return the daily expense taken from the UI
     */
    QString _GetDailyExpense(void) const;
    /*
     * @brief Should only be used after isExpenseValid() has been called. Otherwise might lead to strange return behaviour.
     * @return the DailyExpense converted to a float.
     */
    float _GetDailyExpenseAsFloat(void);
    /*
     * @brief Sets if the calendar should be shown or not based on the given boolean value.
     */
    void _SetShowCalendar(bool val){
        _showCalendar = val;
    }
    /*
     * @brief Used to enable/disable the calendar widget.
     * @return if the calendar should be showed or not.
     */
    bool _GetShowCalendar(void) const{
        return _showCalendar;
    }
    /*
     * @brief Gets the current UI state and based on it, changes the states of all the UI elements to match that of the current state.
     */
    void _ProcessUIStateChange(void);
    /*
     * @brief Uses the UI to dislpay whatever the current error is.
     */
    void _DisplayCurrentErrorText(void);
    /*
     * @brief Sets the current Error text based on what is passed to it.
     */
    void _SetErrorText(QString errorText){
        _currentErrorText = errorText;
    }
    /*
     * @return the currentErrorText that is being displayed to the user.
     */
    const QString& _GetCurrentErrorText(void) const{
        return _currentErrorText;
    }
    /*
     * @brief Checks the the current state and acts upon it, based on what the current state is.
     */
    void _UpdateUIBasedOnState(void);
    /*
     * @brief Sets the current state of the UI with whatever state has been passed to the function.
     */
    void _SetUIState(UIState state){
        _currentUIState = state;
    }
    /*
     * @return the current state of the UI.
     */
    const UIState& _GetCurrentUIState(void) const{
        return _currentUIState;
    }
    /*
     * @brief Uses the UI to display the QString passed to the function as an ExpenseNote.
     */
    void _DisplayExpenseNote(QString noteToSet);
    /*
     * @brief Places a number of type of expenses that the user can select when submitting expenses.
     */
    void _InitializeTypeOfExpenses(void);
    /*
     * @brief Takes in a message and then makes sure that the label text is changed to red and outputs that message as an error to the user.
     */
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
