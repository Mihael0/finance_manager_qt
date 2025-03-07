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
    SHEET_DOES_NOT_EXIST,
    SHEET_FOUND,
    OPERATION_AS_USUAL,
    SHEET_NOT_FOUND,
    ERROR,
};

enum ExcelBookType{
    MONTHLY_EXPENSE,
    MONTHLY_SUMMARY,
    RECURRING_EXPENSE,
    EMPTY_EXCEL,
};

// Libxl functions often require a char* as an input parameter.
// For that reason, everything relating to the path of the excel file
// will require the transformation from a QString to a QByteArray to eventually
// a char pointer. This sturct helps organize it and make it easier to read.
typedef struct{
    char* charPath;
    QByteArray binaryPath;
} PathParameters_t;

class Excel {
public:
    bool ExcelFileExists(void) const;
    void StoreDailyExpense(double expense, QString currentDate);
    ExcelResponse GetResponseState(void);
    Excel(QString bookName, QString sheetName){
        _CreateNewExcelBook(bookName, sheetName, EMPTY_EXCEL);
    }
    Excel(QString bookName, QString sheetName, ExcelBookType excelType){
        _CreateNewExcelBook(bookName, sheetName, excelType);
    }
    ~Excel(){
        _book->release();
    }

private:
    libxl::Book* _book = xlCreateBook();
    libxl::Sheet* _sheet;
    libxl::Format* _format;
    QString _bookName = "";
    QString _excelDirectoryPath = "";
    QString _projectDirectoryForExcels = "../data/";
    QString _xlsFileExtenstion = ".xls";
    ExcelResponse _responseState = OPERATION_AS_USUAL;
    const int _rowOfNumExp = 1;
    const int _columnOfNumExp = 4;
    const char* error = _GetBookInstance()->errorMessage();

    const int _GetRowOfNumExp(void) const{
        return _rowOfNumExp;
    }

    const int _GetColumnOfNumExp(void) const{
        return _columnOfNumExp;
    }

    libxl::Format* _GetFormat(void) const{
        return _format;
    }

    void _SetFormat(void){
        _format = _GetBookInstance()->addFormat();
        _format->setBorder();

    }
    void _ConfigureExcelDirectoryPath(QString bookName){
        _SetBookName(bookName);
        _SetExcelDirectoryPath();
    }

    void _SetBookName(QString bookName){
        _bookName = bookName;
    }

    QString _GetBookName(void) const{
        return _bookName;
    }

    void _SetExcelDirectoryPath(void){
        _excelDirectoryPath = _projectDirectoryForExcels + _GetBookName() + _xlsFileExtenstion;
    }

    const QString _GetExcelDirectoryPath(void) const{
        return _excelDirectoryPath;
    }

    const char* _GetExcelDirectoryAsCharPtr(void) const{
        return _excelDirectoryPath.toLocal8Bit().data();
    }

    ExcelResponse _CreateNewExcelBook(QString bookName, QString sheetName, ExcelBookType excelType){
        _ConfigureExcelDirectoryPath(bookName);
        _SetResponseState(OPERATION_AS_USUAL);

        if(ExcelFileExists()){
            if(!_GetBookInstance()->load(_GetExcelDirectoryAsCharPtr())){
                _SetResponseState(ERROR);
            }
            _SetSheetInstance(0);
            _SetFormat();
            _SetResponseState(FILE_ALREADY_EXISTS);
            return GetResponseState();
        }

        switch(excelType){
        case MONTHLY_EXPENSE:
            _SetResponseState(_CreateMonthlyExpenseBook(sheetName));
            break;
        case MONTHLY_SUMMARY:
            break;
        case RECURRING_EXPENSE:
            break;
        // Empty excel
        default:
            break;
        }

        return GetResponseState();
    }

    ExcelResponse _CreateMonthlyExpenseBook(QString sheetName){
        if(_CreateNewSheet(sheetName) != NEW_SHEET_CREATED){
            return _CreateNewSheet(sheetName);
        }
        // Set the sheet instance to the first sheet.
        if(_SetSheetInstance(0) != SHEET_FOUND){
            return _SetSheetInstance(0);
        }

        libxl::Sheet* sheet = _GetSheetInstance();
        if(!sheet){
            return SHEET_NOT_FOUND;
        }

        _SetFormat();
        sheet->writeStr(1,0,"Expenses",_GetFormat());
        sheet->writeStr(1,1,"Date",_GetFormat());
        sheet->writeStr(1,2,"Note",_GetFormat());
        sheet->writeStr(1,3,"NumOfWrtExp",_GetFormat());
        // Write the number (row-1) which is the location of the previously written value.
        // The number is (row-1) due to having to add 1 every time we write.
        sheet->writeNum(_GetRowOfNumExp(),_GetColumnOfNumExp(),1,_GetFormat());
        _SaveExcelFile();

        return NEW_FILE_CREATED;
    }

    ExcelResponse _CreateNewSheet(QString sheetName){
        if(!_GetBookInstance()){
            return ERROR;
        }
        // This function call is required to be able to call _book->sheetCount() and _book->getSheetName()
        // _GetBookInstance()->loadInfo(_GetExcelDirectoryAsCharPtr());
        if(_GetBookInstance()->sheetCount() == 0){
            // Create a new sheet of the given name.
            _GetBookInstance()->addSheet(sheetName.toLocal8Bit().constData());
            return NEW_SHEET_CREATED;
        }

        for(int i = 0; i <= _GetBookInstance()->sheetCount(); i++){
            // Check if a sheet of the given name exsists.
            if(_GetBookInstance()->getSheetName(i) == sheetName){
                return SHEET_ALREADY_EXISTS;
            }
        }
        _GetBookInstance()->addSheet(sheetName.toLocal8Bit().constData());

        return NEW_SHEET_CREATED;
    }

    libxl::Book* _GetBookInstance() const{
        return _book;
    }
    // This function saves the _book into the given path.
    void _SaveExcelFile(void){
        _GetBookInstance()->save(_GetExcelDirectoryAsCharPtr());
    }

    void _SetResponseState(ExcelResponse response){
        _responseState = response;
    }

    ExcelResponse _SetSheetInstance(int sheet_number){
        if(_GetBookInstance()->sheetCount() < sheet_number){
            return SHEET_DOES_NOT_EXIST;
        }
        _sheet = _GetBookInstance()->getSheet(sheet_number);
        if(!_sheet){
            return SHEET_NOT_FOUND;
        }
        return SHEET_FOUND;
    }

    libxl::Sheet* _GetSheetInstance(void){
        return _sheet;
    }

    // void _StoreDailyExpenseInDatabase(float dailyExpense, QDate currentTime, libxl::Book* selectedBook){

    // }
};


#endif // EXCEL_H
