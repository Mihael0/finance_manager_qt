#ifndef EXCEL_H
#define EXCEL_H
#include "libxl.h"
#include "string"
#include "QDate"

enum ExcelResponse{
    FILE_ALREADY_EXISTS,
    SHEET_ALREADY_EXISTS,
    BOOK_INSTANCE_DOES_NOT_EXIST,
    SHEET_DOES_NOT_EXIST,
    OKAY,
    SHEET_NOT_FOUND,
    CANNOT_LOAD_FILE,
    ERROR_CHECK_LIBXL_RESPONSE,
    ERROR,
};
// NOTE: For now it is not expected to use more than one sheet.
enum SheetInstances{
    FIRST_SHEET,
};

enum ExcelBookType{
    MONTHLY_EXPENSE,
    MONTHLY_SUMMARY,
    RECURRING_EXPENSE,
    EMPTY_EXCEL,
};

class Excel {
public:
    /*
     * @brief Checks if the excel file exists, which is provided by _excelDirectoryPath.
     * @return true or false depending if the file exists or not.
     */
    bool ExcelFileExists(void) const;
    /*
     * @brief Checks if the excel file exists, which is provided by _excelDirectoryPath.
     * @return true or false depending if the file exists or not.
     */
    void StoreDailyExpense(double expense, QString currentDate);
    /*
     * @return the current state of the ExcelResponse.
     */
    ExcelResponse GetResponseState(void);
    Excel(QString bookName, QString sheetName){
        _CreateBookInstance(bookName, sheetName, EMPTY_EXCEL);
    }
    Excel(QString bookName, QString sheetName, ExcelBookType excelType){
        _CreateBookInstance(bookName, sheetName, excelType);
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
    ExcelResponse _responseState = OKAY;
    const int _rowOfLastOccupiedRow = 1;
    const int _columnOfLastOccupiedRow = 4;
    const char* error = _GetBookInstance()->errorMessage();

    /*
     * @brief Sets the value of the _responseState.
     * @detail This function MUST be called at the begining of every base function
     * and if anything goes wrong within those functions, the corresponding ExcelResponse must be set.
     * Base functions are those that interact directly with libxl or only make calls to setters and getters.
     */
    void _SetExcelResponseState(ExcelResponse newState){
        _responseState = newState;
    }
    /*
     * @brief Libxl provides an internal error message.
     * This function returns the state of that message.
     * @return the error message pointer of libxl
     */
    const char* _GetLibxlErrorMsg(void) const{
        return error;
    }
    /*
     * @return the row of where the LastOccupiedValue is stored
     */
    int _GetRowOfLastOccupiedRow(void) const{
        return _rowOfLastOccupiedRow;
    }
    /*
     * @return the column of where the LastOcupiedValue is stored.
     */
    int _GetColumnOfLastOccupiedRow(void) const{
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
     * @brief Uses libxl to assign a _sheet instance.
     * @return true or false depending if the operation was successful or not.
     */
    bool _SetSheetInstance(SheetInstances sheet_number){
        _SetExcelResponseState(OKAY);
        // If the number given is larger than the sheetCount then the sheet does not exist.
        if(_GetBookInstance()->sheetCount() < sheet_number){
            _SetExcelResponseState(SHEET_NOT_FOUND);
            return false;
        }

        _sheet = _GetBookInstance()->getSheet(sheet_number);
        if(!_sheet){
            _SetExcelResponseState(SHEET_DOES_NOT_EXIST);
            return false;
        }

        return true;
    }
    /*
     * @return a pointer to the private variable of _sheet.
     */
    libxl::Sheet* _GetSheetInstance(void){
        return _sheet;
    }
    /*
     * @brief Loads into memory the current excel file that is pointed at by _excelDirectoryPath.
     * If the function returns false, check _GetExcelResponseState().
     * @return true or false depending if the operation was successful or not.
     */
    bool _LoadBookInstance(void){
        _SetExcelResponseState(OKAY);

        if(!_GetBookInstance()->load(_GetExcelDirectoryAsCharPtr())){
            _SetExcelResponseState(CANNOT_LOAD_FILE);
            return false;
        }
        return true;
    }
    /*
     * @brief Interacts with libxl to create the template of MonthlyExpense.
     * If the function returns false, check _GetExcelResponseState().
     * @return true or false depending if the operation was successful or not.
     */
    bool _ApplyMonthlyExpenseTemplate(void){
        _SetExcelResponseState(OKAY);
        // If any of the following functions returns false, operation has failled.
        if (!_GetSheetInstance()->writeStr(1, 0, "Expenses", _GetFormat()) ||
            !_GetSheetInstance()->writeStr(1, 1, "Date", _GetFormat()) ||
            !_GetSheetInstance()->writeStr(1, 2, "Note", _GetFormat()) ||
            !_GetSheetInstance()->writeStr(1, 3, "lastOccupiedRow", _GetFormat()) ||
            // Write the number (row-1) which is the location of the previously written value.
            // The number is (row-1) due to having to add 1 every time we write.
            !_GetSheetInstance()->writeNum(_GetRowOfLastOccupiedRow(), _GetColumnOfLastOccupiedRow(), 1, _GetFormat())) {
            _SetExcelResponseState(ERROR_CHECK_LIBXL_RESPONSE);
            return false;
        }

        return true;
    }
    /*
     * @brief Calls all the needed functions to create an excel of type MonthlyExpense.
     * If the function returns false, check _GetExcelResponseState().
     * @return true or false depending if the operation was successful or not.
     */
    bool _CreateMonthlyExpenseBook(QString sheetName){

        if(!_CreateNewSheet(sheetName)){
            return false;
        }
        //NOTE: Change this function call and implementation if you expect to have more than one sheet
        // For now the expectation is only one sheet will be used. Due to this, it has been decided
        // to not implement multiple sheets as that will decrease performance.
        if(!_SetSheetInstance(FIRST_SHEET)){
            return false;
        }

        _SetFormat();
        if(!_ApplyMonthlyExpenseTemplate()){
            return false;
        }

        _SaveExcelFile();
        return true;
    }
    /*
     * @brief Calls the different functions required to create a new sheet.
     * If the function returns false, check _GetExcelResponseState().
     * @return true or false depending if the operation was successful or not.
     */
    bool _CreateNewSheet(QString sheetName){
        _SetExcelResponseState(OKAY);

        if(!_GetBookInstance()){
            _SetExcelResponseState(BOOK_INSTANCE_DOES_NOT_EXIST);
            return false;
        }

        if(_GetBookInstance()->sheetCount() == 0){
            // Create a new sheet of the given name.
            _GetBookInstance()->addSheet(sheetName.toLocal8Bit().constData());
            return true;
        }
        // If there is more than one sheet.
        for(int i = 0; i <= _GetBookInstance()->sheetCount(); i++){
            // Check if a sheet of the given name exsists.
            if(_GetBookInstance()->getSheetName(i) == sheetName){
                _SetExcelResponseState(SHEET_ALREADY_EXISTS);
                return false;
            }
        }
        // If sheet of the given name is not found, then add it.
        _GetBookInstance()->addSheet(sheetName.toLocal8Bit().constData());

        return true;
    }
    /*
     * @brief Calls the different functions required to create a new excel file or to initialize the object to point to an existing one.
     * If the function returns false, check _GetExcelResponseState().
     * @return true or false depending on if the operation was successful or not.
     */
    bool _CreateBookInstance(QString bookName, QString sheetName, ExcelBookType excelType){
        _ConfigureExcelDirectoryPath(bookName);

        if(ExcelFileExists()){
            if(!_LoadBookInstance()){
                return false;
            }

            _SetFormat();
            if(!_SetSheetInstance(FIRST_SHEET)){
                return false;
            }
            return true;
        }

        switch(excelType){
        case MONTHLY_EXPENSE:
            if(!_CreateMonthlyExpenseBook(sheetName)){
                return false;
            }
        case MONTHLY_SUMMARY:
            break;
        case RECURRING_EXPENSE:
            break;
        // Empty excel
        default:
            break;
        }

        return true;
    }
};
#endif // EXCEL_H
