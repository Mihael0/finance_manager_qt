#include "excel.h"

using namespace libxl;

ExcelResponse Excel::CreateNewExcelBook(QString bookName,QString sheetName){
    _SetFilePath(bookName);

    if(ExcelFileExists(bookName)){
        return FILE_ALREADY_EXISTS;
    }

    _SaveBookInstance(_GetFilePath());
    // We do not check the return of CreateNewSheet, as it is assumed if we have reached here that
    // the _book is empty.
    CreateNewSheet(sheetName);

    return NEW_FILE_CREATED;
}

ExcelResponse Excel::CreateNewSheet(QString sheetName){
    // This function call is required to be able to call _book->sheetCount() and _book->getSheetName()
    _book->loadInfo(_filePath);

    if(_book->sheetCount() == 0){
        // Create a new sheet of the given name.
        _book->addSheet(_ConvertQStringToCharPtr(sheetName));
        _IncrementNumberOfSheets();
        return NEW_SHEET_CREATED;
    }

    for(int i = 0; i <= _book->sheetCount(); i++){
        // Check if a sheet of the given name exsists.
        if(_book->getSheetName(i) == sheetName){
            return SHEET_ALREADY_EXISTS;
        }
    }
    _book->addSheet(_ConvertQStringToCharPtr(sheetName));
    _IncrementNumberOfSheets();

    return NEW_SHEET_CREATED;
}

bool Excel::ExcelFileExists(QString bookName) const{
    if(_book->load(_ConvertQStringToCharPtr(bookName))){
        return true;
    }

    return false;
}
