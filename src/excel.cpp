#include "excel.h"

using namespace libxl;

ExcelResponse Excel::GetResponseState(void){
    return _responseState;
}

void Excel::StoreDailyExpense(double expense){
    // Check the name of the file
    // Leave a value of the number of filled days
    // We create a function that checks if

    if(!_GetSheetInstance()){
        return;
    }

    double numberOfWrittenExpenses = _GetSheetInstance()->readNum(1,4);
    const char* error = _GetBookInstance()->errorMessage();
    numberOfWrittenExpenses += 3;
    _GetSheetInstance()->writeNum(numberOfWrittenExpenses, 0, expense,_GetFormat());

}

bool Excel::ExcelFileExists(void) const{
    if(_GetBookInstance()->load(_GetExcelDirectoryAsCharPtr())){
        return true;
    }

    return false;
}
