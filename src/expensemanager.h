#ifndef EXPENSEMANAGER_H
#define EXPENSEMANAGER_H
#include <QString>
#include <QDate>

struct ExpenseInfo{
    float expenseValue;
    QDate expenseDate;
};

enum class Boundry{
    Left, // most left saved value (earliest)
    Right, // most right saved vaue by the user. (latest)
    LeftRight, // size of vector is 1 and we are at index 0.
    HeadOfVector, // at a yet unsaved value by the user.
    NoBoundry, // when not at any of the bound conditions.
};

struct LastExpenseData{
    QString lastDailyExpense;
    QDate lastExpenseDate;
};

class ExpenseManager
{
public:
    ExpenseManager();
    /*
     * @return expenseValue and expenseDate at the requested index. Returns nullptr if it does not exist.
     */
    const ExpenseInfo* GetExpense(int index) const;
    /*
     * @brief Sets the given arguments into the private _expenses struct. Can be retrieved by calling GetExpenses(index).
     */
    void SetExpenses(float declaredExpense, QDate& dateOfExpense);
    void MoveExpenseIndexLeft(int moveby);
    void MoveExpenseIndexRight(int moveby);
    Boundry GetCurrentStateOfBoundry(void) const;
    Boundry GetPreviousStateOfBoundry(void) const;
    Boundry GetStateOfBoundry(void) const;
    /*
     * @return the last inputted value by the user. If none was set, it returns nullptr.
     */
    const LastExpenseData* RestoreUserInputtedData(void) const;
    /*
     * @detail Please make sure you call the MoveIndex functions to move the index. If IsAtHeadOfVector() is true, it is recommended that
     * you use RestoreUserInputtedData() as this function works only within the boundry of the vector.
     * @return the expenseValue and expenseDate at the index controlled by MoveExpenseIndexLeft/Right.
     */
    const ExpenseInfo* GetExpenseAtMovingIndex(void) const;
    /*
     * @detail This function is used to store the last inputted user ExpenseData and ExpenseDate.
     * For this reason the tmpDailyExpense is a QString as it is not checked if it is a correct float value.
     */
    void StoreUserInputtedData(QString& lastDailyExpense, QDate& lastExpenseDate);

    bool IsUserScrollingExpenses(void) const;
    void MoveExpenseIndexMaxRight(void);
    void MoveExpenseIndexMaxLeft(void);

private:
    // all expenses SUBMITTED by the user are stored here.
    // non-submitted expenses are stored in LastExpenseData
    std::vector<ExpenseInfo> _expenses;
    // stores the last written value and date that the user had inputted
    // before he started navigating through the expenses.
    // this can be used to restore his context when he is done
    // navigating through his submitted expenses.
    LastExpenseData _lastExpenseData;
    Boundry _currentBoundryState = Boundry::HeadOfVector;
    Boundry _previousBoundryState = Boundry::HeadOfVector;
    int _movingIndex = -1;
    bool _isUserScrollingExpenses = false;


    void _SetIsUSerScrollingExpenses(bool is){
        _isUserScrollingExpenses = is;
    }
    /*
     * @return the expenses struct which contains the currently inputted expenses by the user.
     */
    const std::vector<ExpenseInfo>& _GetExpenses(void) const{
        return _expenses;
    }

    void _SetStateOfBound(void){
        _previousBoundryState = _currentBoundryState;
        if(_movingIndex == - 1){
            _currentBoundryState = Boundry::HeadOfVector;
            _SetIsUSerScrollingExpenses(false);
            return;
        }

        _SetIsUSerScrollingExpenses(true);
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
    }
};

#endif // EXPENSEMANAGER_H
