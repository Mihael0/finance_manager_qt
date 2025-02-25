#include "excel.h"

using namespace libxl;

void Excel::_CreateNewExcelBook(std::string BookName){
    Book* book = xlCreateBook(); // xlCreateXMLBook() for xlsx
    if(book)
    {
        Sheet* sheet = book->addSheet("Sheet1");
        if(sheet)
        {
            sheet->writeStr(2, 1, "Hello, World !");
            sheet->writeNum(3, 1, 1000);
        }
        std::string dirToStoreExcels = "../data/" + BookName + ".xls";
        book->save(dirToStoreExcels.c_str());
        book->release();
    }
}
