#include "expensemanager.h"

ExpenseManager::ExpenseManager() {}

void ExpenseManager::SetExpenses(float declaredExpense, QDate& dateOfExpense){
    ExpenseInfo expense = {
        .expenseValue = declaredExpense,
        .expenseDate = dateOfExpense,
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

Boundry ExpenseManager::GetCurrentStateOfBoundry(void) const{
    return _currentBoundryState;
}

Boundry ExpenseManager::GetPreviousStateOfBoundry(void) const{
    return _previousBoundryState;
}

void ExpenseManager::StoreUserInputtedData(QString& lastDailyExpense, QDate& lastExpenseDate){
    LastExpenseData lastExpenseData = {
        .lastDailyExpense = lastDailyExpense,
        .lastExpenseDate  = lastExpenseDate,
    };
    _lastExpenseData = lastExpenseData;
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
    // if _movingIndex is 0, that means we want the most latest added value.
    if(_movingIndex == 0){
        adjustedIndex = maxIndexOfExpenses;
    } else { // if index is any other value, we have to take the absolute difference.
        adjustedIndex = std::abs(_movingIndex - maxIndexOfExpenses);
    }

    return &_GetExpenses()[adjustedIndex];
}

const LastExpenseData* ExpenseManager::RestoreUserInputtedData(void) const{
    return &_lastExpenseData;
}

// void ExpenseManager::MoveLeftNCheckIfUserPendingDataShouldBeStored(void){

// }

// PostMoveAction ExpenseManager::MoveRightNSetMovingState(void){
//     MoveExpenseIndexRight(1);

//     // If we are at the HeadOfVector, and user presses right, we do nothing.
//     if(_expenseManager->GetCurrentStateOfBoundry() == Boundry::HeadOfVector
//         && _expenseManager->GetPreviousStateOfBoundry() == Boundry::HeadOfVector){
//         return PostMoveAction::DoNothing;
//     }

//     if(_expenseManager->GetCurrentStateOfBoundry() == Boundry::HeadOfVector
//         && _expenseManager->GetPreviousStateOfBoundry() != Boundry::HeadOfVector){
//         return PostMoveAction::RestorePendingData;
//     }
// }
