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
public:
    bool ExcelFileExists(QString filename);
    ExcelResponse CreateNewExcelBook(QString bookName);
    ExcelResponse CreateNewSheet(QString sheetName);

    ~Excel(){
        _book->release();
    }

private:
    // float _DailyExpense;
    libxl::Book* _book = xlCreateBook();
    QDate _currentTime;

    libxl::Book* _GetBookInstance() const{
        return _book;
    }

    const char* _CreateFileDirectory(QString bookName){
        QString dirToStoreExcels = "../data/" + bookName + ".xls";
        QByteArray ba_dirToStoreExcels = dirToStoreExcels.toLocal8Bit();
        const char *c_dirToStoreExcels = ba_dirToStoreExcels.data();

        return c_dirToStoreExcels;
    }
    void _SaveBookInstance(const char* pathToDir){
        _book->save(pathToDir);
    }
    /**
     * Uses the created _book to store a set _DailyExpense.
     */
    void _StoreDailyExpenseInDatabase(float dailyExpense, QDate currentTime, libxl::Book* selectedBook){

    }
};


#endif // EXCEL_H
