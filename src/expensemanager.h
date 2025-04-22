#ifndef EXPENSEMANAGER_H
#define EXPENSEMANAGER_H
#include <QString>
#include <QObject>
#include <QDate>

struct ExpenseInfo{
    float expenseValue;
    QDate expenseDate;
    QString expenseType;
    QString expenseNote = ""; // Notes may or may not be empty
};

enum class Boundry{
    Left, // most left saved value (earliest)
    Right, // most right saved vaue by the user. (latest)
    LeftRight, // size of vector is 1 and we are at index 0.
    HeadOfVector, // at a yet unsaved value by the user.
    NoBoundry, // when not at any of the bound conditions.
};

struct LastExpenseInfo{
    QString lastDailyExpense;
    QDate lastExpenseDate;
    QString lastTypeOfExpense;
    QString lastExpenseNote = "";
};

class ExpenseManager: public QObject
{
    Q_OBJECT
signals:
    void UpdateUIStateRequested(void);

public:
    explicit ExpenseManager(QObject* parent = nullptr);
    /*
     * @return expenseValue and expenseDate at the requested index. Returns nullptr if it does not exist.
     */
    const ExpenseInfo* GetExpense(int index) const;
    /*
     * @brief Sets the given arguments into the private _expenses struct. Can be retrieved by calling GetExpenses(index).
     */
    void SetExpenses(const float declaredExpense, const QDate& dateOfExpense, const QString& typeOfExpense, const QString& expenseNote);

    void ReplaceExpense(const float newExpense, const QDate& newDateOfExpense, const QString& newTypeOfExpense, const QString& newExpenseNote);
    /*
     * @brief Moves the _movingIndex "left" by the passed to it.
     */
    void MoveExpenseIndexLeft(int moveby);
    /*
     * @brief Moves the _movingIndex "right" by the passed to it.
     */
    void MoveExpenseIndexRight(int moveby);
    /*
     * @return the state of the boundry.
     */
    Boundry GetCurrentStateOfBoundry(void) const;
    /*
     * @return the state of the previous boundry.
     */
    Boundry GetPreviousStateOfBoundry(void) const;
    /*
     * @return the last inputted value by the user. If none was set, it returns nullptr.
     */
    const LastExpenseInfo* RestoreUserInputtedInfo(void) const;
    /*
     * @detail Please make sure you call the MoveIndex functions to move the index. If IsAtHeadOfVector() is true, it is recommended that
     * you use RestoreUserInputtedInfo() as this function works only within the boundry of the vector.
     * @return the expenseValue and expenseDate at the index controlled by MoveExpenseIndexLeft/Right.
     */
    const ExpenseInfo* GetExpenseAtMovingIndex(void) const;
    /*
     * @detail This function is used to store the last inputted user ExpenseData and ExpenseDate.
     * For this reason the tmpDailyExpense is a QString as it is not checked if it is a correct float value.
     */
    void StoreUserInputtedInfo(const QString& lastDailyExpense, const QDate& lastExpenseDate, const QString& lastTypeOfExpense, const QString& lastExpenseNote);
    /*
     * @detail Moves the moving index to the very right to the head of the vector.
     */
    void MoveExpenseIndexMaxRight(void);
    /*
     * @detail Moves the moving index to the very left to the very first element of the vector, or also known as Left.
     */
    void MoveExpenseIndexMaxLeft(void);

private:
    // all expenses SUBMITTED by the user are stored here.
    // non-submitted expenses are stored in LastExpenseInfo
    std::vector<ExpenseInfo> _expenses;
    // stores the last written value and date that the user had inputted
    // before he started navigating through the expenses.
    // this can be used to restore his context when he is done
    // navigating through his submitted expenses.
    LastExpenseInfo _lastExpenseInfo;
    Boundry _currentBoundryState = Boundry::HeadOfVector;
    Boundry _previousBoundryState = Boundry::HeadOfVector;
    int _movingIndex = -1;

    int _CalculateAnAdjustedIndex(void){
        int adjustedIndex = 0;
        int maxIndexOfExpenses = static_cast<int>(_GetExpenses().size()) - 1;
        // if _movingIndex is 0, that means we want the latest added value.
        if(_movingIndex == 0){
            adjustedIndex = maxIndexOfExpenses;
        } else { // if index is any other value, we have to take the absolute difference.
            adjustedIndex = std::abs(_movingIndex - maxIndexOfExpenses);
        }
        return adjustedIndex;
    }

    /*
     * @return the expenses struct which contains the currently inputted expenses by the user.
     */
    const std::vector<ExpenseInfo>& _GetExpenses(void) const{
        return _expenses;
    }
    /*
     * @detail Sets the boundry to the one corresponding of where the user is currently scrolling through.
     * For more information on what each boundry represents, please look at the declaration of the boundry.
     */
    void _SetStateOfBound(void){
        _previousBoundryState = _currentBoundryState;
        if(_movingIndex == - 1){
            _currentBoundryState = Boundry::HeadOfVector;
            emit UpdateUIStateRequested();
            return;
        }

        int max_index_of_expenseValue = _GetExpenses().size() - 1;
        if(_movingIndex == 0
            && _movingIndex == max_index_of_expenseValue){
            _currentBoundryState = Boundry::LeftRight;
        } else if(_movingIndex == 0){
            _currentBoundryState = Boundry::Right;
        } else if(_movingIndex == max_index_of_expenseValue){
            _currentBoundryState = Boundry::Left;
        } else {
            _currentBoundryState = Boundry::NoBoundry;
        }
        emit UpdateUIStateRequested();
    }
};

#endif // EXPENSEMANAGER_H
