#include "expensemanager.h"

ExpenseManager::ExpenseManager(QObject* parent)
        : QObject(parent){
}

void ExpenseManager::onRequestDeclareExpenses(void){
    emit PublishExpensesRequested(_GetExpenses());
}

const std::vector<ExpenseInfo>* ExpenseManager::GetExpenses(void) const{
    return &_expenses;
}

void ExpenseManager::SetExpenses(const float declaredExpense, const QDate& dateOfExpense, const QString& typeOfExpense, const QString& expenseNote){
    ExpenseInfo expense = {
        declaredExpense,
        dateOfExpense,
        typeOfExpense,
        expenseNote,
    };
    _expenses.push_back(expense);
}

void ExpenseManager::EraseExpenseAtCurrentIndex(void){
    _expenses.erase(_expenses.begin() + _CalculateAnAdjustedIndex());
}

void ExpenseManager::ReplaceExpense(const float newExpense, const QDate& newDateOfExpense, const QString& newTypeOfExpense, const QString& newExpenseNote){
    if (_movingIndex == -1 || _movingIndex >= static_cast<int>(_expenses.size())) {
        // Throw an error or return an error code/enum.
        return;
    }

    ExpenseInfo newExpenseInfo{
        newExpense,
        newDateOfExpense,
        newTypeOfExpense,
        newExpenseNote
    };
    _expenses[_CalculateAnAdjustedIndex()] = newExpenseInfo;
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

void ExpenseManager::StoreUserInputtedInfo(const QString& lastDailyExpense, const QDate& lastExpenseDate, const QString& lastTypeOfExpense, const QString& lastExpenseNote){
    LastExpenseInfo lastExpenseInfo = {
        .lastDailyExpense = lastDailyExpense,
        .lastExpenseDate  = lastExpenseDate,
        .lastTypeOfExpense = lastTypeOfExpense,
        .lastExpenseNote = lastExpenseNote,
    };
    _lastExpenseInfo = lastExpenseInfo;
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
