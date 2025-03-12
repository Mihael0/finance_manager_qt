#include "excel.h"

using namespace libxl;

ExcelResponse Excel::GetResponseState(void){
    return _responseState;
}

void Excel::StoreDailyExpense(double expense, QString currentDate){
    if(!_GetBookInstance() ||!_GetSheetInstance()){
        return;
    }

    // Read the number of stored expenses
    double numberOfWrittenExpenses = _GetSheetInstance()->readNum(1,4);
    numberOfWrittenExpenses += 1;
    // Write the given expense
    _GetSheetInstance()->writeNum(numberOfWrittenExpenses, 0, expense);
    // Write the date of the given expense
    const char* c_currentDate = currentDate.toLocal8Bit().data();
    _GetSheetInstance()->writeStr(numberOfWrittenExpenses, 1, c_currentDate);
    // Update the LastOccupiedRow
    _GetSheetInstance()->writeNum(_GetRowOfLastOccupiedRow(),_GetColumnOfLastOccupiedRow(),numberOfWrittenExpenses);

    _SaveExcelFile();

}

bool Excel::ExcelFileExists(void) const{
    if(_GetBookInstance()->load(_GetExcelDirectoryAsCharPtr())){
        return true;
    }

    return false;
}
