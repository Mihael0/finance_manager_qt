#ifndef EXCEL_H
#define EXCEL_H
#include "libxl.h"
#include "string"
#include "QDate"

enum ExcelResponse{
    FILE_ALREADY_EXISTS,
    NEW_FILE_CREATED,
    SHEET_ALREADY_EXISTS,
    NEW_SHEET_CREATED,
    ERROR,
};

class Excel {
    // All public functions that interact with the _book should require a
    // bookName, to be able to set the filePath to the excel file currently
    // being edited.
public:
    bool ExcelFileExists(QString bookName) const;
    ExcelResponse CreateNewExcelBook(QString bookName, QString sheetName);
    ExcelResponse CreateNewSheet(QString sheetName);
    Excel(QString bookName, QString sheetName){
        // Will attempt to create a book by the given name with a sheet of sheetName
        // If the file exists, it will only set the _filePath to point at the file.
        CreateNewExcelBook(bookName, sheetName);
    }
    ~Excel(){
        _book->release();
    }

private:
    // float _DailyExpense;
    libxl::Book* _book = xlCreateBook();
    libxl::Sheet* _sheet;
    QDate _currentTime;
    char* _filePath;
    int _numberOfSheets = 0;

    libxl::Book* _GetBookInstance() const{
        return _book;
    }
    void _SetFilePath(QString bookName){
        QString dirToStoreExcels = "../data/" + bookName + ".xls";
        _filePath = _ConvertQStringToCharPtr(dirToStoreExcels);
    }
    // This function needs to be called if a different file from the originally
    // targeted one from the constructor changes. Otherwise you might be editing
    // the wrong Excel file.
    char* _GetFilePath(void) const{
        return _filePath;
    }
    void _SaveBookInstance(const char* pathToDir){
        _book->save(pathToDir);
    }
    char* _ConvertQStringToCharPtr(QString inputStr) const{
        QByteArray binary_inputStr = inputStr.toLocal8Bit();
        char* char_inputStr = binary_inputStr.data();
        return char_inputStr;
    }
    void _IncrementNumberOfSheets(){
        _numberOfSheets += 1;
    }
    int _GetNumberOfSheets(void){
        return _numberOfSheets;
    }
    // void _StoreDailyExpenseInDatabase(float dailyExpense, QDate currentTime, libxl::Book* selectedBook){

    // }
};


#endif // EXCEL_H
