#include "expensemanager.h"

ExpenseManager::ExpenseManager(QObject* parent)
        : QObject(parent){

}

void ExpenseManager::SetExpenses(float declaredExpense, QDate& dateOfExpense, QString& typeOfExpense, QString& expenseNote){
    ExpenseInfo expense = {
        .expenseValue = declaredExpense,
        .expenseDate = dateOfExpense,
        .expenseType = typeOfExpense,
        .expenseNote = expenseNote,
    };
    _expenses.push_back(expense);
}

void ExpenseManager::MoveExpenseIndexLeft(int moveby){
    int maxIndexOfExpenses = static_cast<int>(_GetExpenses().size() - 1);
    int numberOfExpenses = static_cast<int>(_GetExpenses().size());

    if(_movingIndex < maxIndexOfExpenses
        && numberOfExpenses > 0){
        _movingIndex += moveby;
    }
    _SetStateOfBound();
}

void ExpenseManager::MoveExpenseIndexRight(int moveby){
    if(_movingIndex >= 0){
        _movingIndex -= moveby;
    }
    _SetStateOfBound();
}

void ExpenseManager::MoveExpenseIndexMaxRight(void){
    _movingIndex = -1;
    _SetStateOfBound();
}

void ExpenseManager::MoveExpenseIndexMaxLeft(void){
    int maxIndexOfExpenses = _GetExpenses().size() - 1;
    _movingIndex = maxIndexOfExpenses;
    _SetStateOfBound();
}

Boundry ExpenseManager::GetCurrentStateOfBoundry(void) const{
    return _currentBoundryState;
}

Boundry ExpenseManager::GetPreviousStateOfBoundry(void) const{
    return _previousBoundryState;
}

void ExpenseManager::StoreUserInputtedInfo(QString& lastDailyExpense, QDate& lastExpenseDate, QString& lastTypeOfExpense, QString& lastExpenseNote){
    LastExpenseInfo lastExpenseInfo = {
        .lastDailyExpense = lastDailyExpense,
        .lastExpenseDate  = lastExpenseDate,
        .lastTypeOfExpense = lastTypeOfExpense,
        .lastExpenseNote = lastExpenseNote,
    };
    _lastExpenseInfo = lastExpenseInfo;
}

bool ExpenseManager::IsUserScrollingExpenses(void) const{
    return _isUserScrollingExpenses;
}

const ExpenseInfo* ExpenseManager::GetExpenseAtMovingIndex(void) const{
    int adjustedIndex = 0;
    int maxIndexOfExpenses = static_cast<int>(_GetExpenses().size()) - 1;
    // Check to see if the total size of the vector is 0 or if _movingIndex has not been moved.
    if(maxIndexOfExpenses <= -1 || _movingIndex == -1){
        return nullptr;
    }
    // if _movingIndex is 0, that means we want the latest added value.
    if(_movingIndex == 0){
        adjustedIndex = maxIndexOfExpenses;
    } else { // if index is any other value, we have to take the absolute difference.
        adjustedIndex = std::abs(_movingIndex - maxIndexOfExpenses);
    }

    return &_GetExpenses()[adjustedIndex];
}

const LastExpenseInfo* ExpenseManager::RestoreUserInputtedInfo(void) const{
    return &_lastExpenseInfo;
}
