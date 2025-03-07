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

typedef struct {
    ExcelResponse state;
    const char* libxlState;
} ExcelResponseState;


enum ExcelBookType{
    MONTHLY_EXPENSE,
    MONTHLY_SUMMARY,
    RECURRING_EXPENSE,
    EMPTY_EXCEL,
};

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
    const int _rowOfLastOccupiedRow = 1;
    const int _columnOfLastOccupiedRow = 4;
    const char* error = _GetBookInstance()->errorMessage();

    const char* _GetLibxlErrorMsg(void) const{
        return error;
    }
    /*
     * @return the row of where the LastOccupiedValue is stored
     */
    const int _GetRowOfLastOccupiedRow(void) const{
        return _rowOfLastOccupiedRow;
    }
    /*
     * @return the column of where the LastOcupiedValue is stored.
     */
    const int _GetColumnOfLastOccupiedRow(void) const{
        return _columnOfLastOccupiedRow;
    }
    /*
     * @brief Adds a format to the current book, and sets the borders.
     */
    void _SetFormat(void){
        _format = _GetBookInstance()->addFormat();
        _format->setBorder();
    }
    /*
     * @return the selected format by _SetFormat
     */
    libxl::Format* _GetFormat(void) const{
        return _format;
    }
    /*
     * @brief Combines the two function needed to create/access an excel file. Setting the name, and the path of the file.
     */
    void _ConfigureExcelDirectoryPath(QString bookName){
        _SetBookName(bookName);
        _SetExcelDirectoryPath();
    }
    /*
     * @brief Sets the private variable _bookName with the variable provided. Shoud only be used during the creation of the object.
     */
    void _SetBookName(QString bookName){
        _bookName = bookName;
    }
    /*
     * @return the name of the book provided by the user during the creation of the object.
     */
    QString _GetBookName(void) const{
        return _bookName;
    }
    /*
     * @brief Creates the path where the excel file will be stored. It uses the provided bookName from the user and two hard coded variables.
     */
    void _SetExcelDirectoryPath(void){
        _excelDirectoryPath = _projectDirectoryForExcels + _GetBookName() + _xlsFileExtenstion;
    }
    /*
     * @return the private variable _excelDirectoryPath.
     */
    const QString _GetExcelDirectoryPath(void) const{
        return _excelDirectoryPath;
    }
    /*
     * @details This function is needed due to the constant needed for const char* as an input parameter for many libxl functions.
     * @return the _excelDirectoryPath as a const char pointer.
     */
    const char* _GetExcelDirectoryAsCharPtr(void) const{
        return _excelDirectoryPath.toLocal8Bit().data();
    }
    /*
     * @details Be careful on how you change this pointer, as pointing to the wrong file may result in undefined behaviour.
     * @return Pointer to the _book instance.
     */
    libxl::Book* _GetBookInstance() const{
        return _book;
    }
    /*
     * @brief This function saves the _book into the given path.
     */
    void _SaveExcelFile(void){
        _GetBookInstance()->save(_GetExcelDirectoryAsCharPtr());
    }
    /*
     *
     *
     */
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
    /*
     * @return a pointer to the private variable of _sheet.
     */
    libxl::Sheet* _GetSheetInstance(void){
        return _sheet;
    }
    /*
     *
     *
     */
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
    /*
     *
     *
     */
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
        // Creates the template for MonthlyExpense
        sheet->writeStr(1,0,"Expenses",_GetFormat());
        sheet->writeStr(1,1,"Date",_GetFormat());
        sheet->writeStr(1,2,"Note",_GetFormat());
        sheet->writeStr(1,3,"lastOccupiedRow",_GetFormat());
        // Write the number (row-1) which is the location of the previously written value.
        // The number is (row-1) due to having to add 1 every time we write.
        sheet->writeNum(_GetRowOfLastOccupiedRow(),_GetColumnOfLastOccupiedRow(),1,_GetFormat());
        _SaveExcelFile();

        return NEW_FILE_CREATED;
    }
    /*
     * @brief Creates a new sheet in the given book.
     * @return
     */
    ExcelResponse _CreateNewSheet(QString sheetName){
        if(!_GetBookInstance()){
            return ERROR;
        }
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
};


#endif // EXCEL_H
