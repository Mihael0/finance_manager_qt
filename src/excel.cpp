#include "excel.h"

using namespace libxl;

ExcelResponse Excel::GetResponseState(void){
    return _responseState;
}

void Excel::StoreDailyExpense(float expense){
    // Check the name of the file
    // Leave a value of the number of filled days
    // We create a function that checks if

    // if(sheet)
    // {
    //     sheet->writeStr(2, 1, L"Hello, World !");
    //     sheet->writeNum(3, 1, 1000);
    // }
}

bool Excel::ExcelFileExists(void) const{
    if(_GetBookInstance()->load(_GetExcelDirectoryAsCharPtr())){
        return true;
    }

    return false;
}
