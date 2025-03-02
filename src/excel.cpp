#include "excel.h"

using namespace libxl;

ExcelResponse Excel::CreateNewExcelBook(QString bookName){
    if(ExcelFileExists(bookName)){
        return FILE_ALREADY_EXISTS;
    }

    const char* c_directoryToSToreExcel = _CreateFileDirectory(bookName);
    _SaveBookInstance(c_directoryToSToreExcel);



    return NEW_FILE_CREATED;
}

ExcelResponse CreateNewSheet(QString sheetName){

    // Sheet* sheet = book->addSheet("Sheet1");
    // if(sheet)
    // {
    //     sheet->writeStr(2, 1, "Hello, World !");
    //     sheet->writeNum(3, 1, 1000);
    // }

    return NEW_SHEET_CREATED;
}

bool Excel::ExcelFileExists(QString filename){
    QString filepath = "../data/" + filename + ".xls";
    QByteArray ba_filepath = filepath.toLocal8Bit();
    const char *c_filepath = ba_filepath.data();
    // Check if an excel sheet of the given month exists.
    if(_book->load(c_filepath)){
        // what a time to be alive.
        int a = 5;
    }else{
        int b = 10;
        // what a time to not be alive.
    }

    return false;
}
