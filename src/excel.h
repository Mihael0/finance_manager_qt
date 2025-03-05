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
    void StoreDailyExpense(float expense);
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
    libxl::Sheet* _sheet = nullptr;
    QString _bookName = "";
    QString _excelDirectoryPath = "";
    const char* _charFilePath;
    int _numberOfSheets = -1;
    QString _projectDirectoryForExcels = "../data/";
    QString _xlsFileExtenstion = ".xls";
    ExcelResponse _responseState = OPERATION_AS_USUAL;

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
        // Update the char pointer version fo the path.
        // This conversation is done due to many of the libxl functions
        // requiring char pointers as inputs to their parameters.
        _charFilePath = _excelDirectoryPath.toLocal8Bit().constData();
    }

    QString _GetExcelDirectoryPath(void) const{
        return _excelDirectoryPath;
    }

    const char* _GetExcelDirectoryAsCharPtr(void) const{
        return _charFilePath;
    }

    ExcelResponse _CreateNewExcelBook(QString bookName, QString sheetName, ExcelBookType excelType){
        _ConfigureExcelDirectoryPath(bookName);
        _SetResponseState(OPERATION_AS_USUAL);

        if(ExcelFileExists()){
            _SetResponseState(FILE_ALREADY_EXISTS);
            return GetResponseState();
        }

        // switch(excelType){
        // case MONTHLY_EXPENSE:
        //     _SetResponseState(_CreateMonthlyExpenseBook(sheetName));
        //     break;
        // case MONTHLY_SUMMARY:
        //     break;
        // case RECURRING_EXPENSE:
        //     break;
        // // Empty excel
        // default:
        //     break;
        // }

        return GetResponseState();
    }
    // ExcelResponse _CreateNewSheet(QString sheetName){
    //     if(!_GetBookInstance()){
    //         return ERROR;
    //     }
    //     // This function call is required to be able to call _book->sheetCount() and _book->getSheetName()
    //     _GetBookInstance()->loadInfo(_filePath);

    //     if(_GetBookInstance()->sheetCount() == 0){
    //         // Create a new sheet of the given name.
    //         _GetBookInstance()->addSheet(_ConvertQStringToCharPtr(sheetName));
    //         _IncrementNumberOfSheets();
    //         return NEW_SHEET_CREATED;
    //     }

    //     for(int i = 0; i <= _GetBookInstance()->sheetCount(); i++){
    //         // Check if a sheet of the given name exsists.
    //         if(_GetBookInstance()->getSheetName(i) == sheetName){
    //             return SHEET_ALREADY_EXISTS;
    //         }
    //     }
    //     _GetBookInstance()->addSheet(_ConvertQStringToCharPtr(sheetName));
    //     _IncrementNumberOfSheets();

    //     return NEW_SHEET_CREATED;
    // }

    libxl::Book* _GetBookInstance() const{
        return _book;
    }
    // void _SetFilePath(QString bookName){
    //     dirToStoreExcels = "../data/" + bookName + ".xls";
    //     _filePath = dirToStoreExcels.c_str();

    // }
    // // This function saves the _book into the given path.
    // void _SaveExcelFile(void){
    //     _GetBookInstance()->save(_GetFilePath());
    // }
    // void _IncrementNumberOfSheets(){
    //     _numberOfSheets += 1;
    // }
    // int _GetNumberOfSheets(void){
    //     return _numberOfSheets;
    // }
    void _SetResponseState(ExcelResponse response){
        _responseState = response;
    }
    // ExcelResponse _SetSheetInstance(int sheet_number){
    //     // This will begin indexing from 0.
    //     // Indexing starts from 1, unless loadInfo or loadPartially is used.
    //     // As loadInfo and loadPartially can and will be used throughout the class.
    //     // It is difficult to know in what state this function will be called.
    //     // To make it consitent, I have added this call here.
    //     // To gurantee that indexing starts from 0.
    //     // Source: https://www.libxl.com/workbook.html search "Sheet* getSheet(int index) cosnt".
    //     _GetBookInstance()->loadInfo(_filePath);

    //     if(_numberOfSheets < sheet_number){
    //         return SHEET_DOES_NOT_EXIST;
    //     }
    //     _sheet = _GetBookInstance()->getSheet(sheet_number);
    //     return SHEET_FOUND;
    // }
    // libxl::Sheet* _GetSheetInstance(void){
    //     return _sheet;
    // }
    // ExcelResponse _CreateMonthlyExpenseBook(QString sheetName){
    //     if(_CreateNewSheet(sheetName) != NEW_SHEET_CREATED){
    //         return _CreateNewSheet(sheetName);
    //     }
    //     // Set the sheet instance to the first sheet.
    //     if(_SetSheetInstance(0) != SHEET_FOUND){
    //         return _SetSheetInstance(0);
    //     }

    //     libxl::Sheet* sheet = _GetSheetInstance();
    //     if(!sheet){
    //         return ERROR;
    //     }

    //     libxl::Format* format = _GetBookInstance()->addFormat();
    //     format->setBorder();

    //     sheet->writeStr(0,0,"Expenses",format);
    //     sheet->writeStr(0,1,"Date",format);
    //     sheet->writeStr(0,2,"Note",format);
    //     _SaveExcelFile();

    //     return NEW_FILE_CREATED;
    // }

    // void _StoreDailyExpenseInDatabase(float dailyExpense, QDate currentTime, libxl::Book* selectedBook){

    // }
};


#endif // EXCEL_H
