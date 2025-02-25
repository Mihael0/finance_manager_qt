#include "excel.h"

using namespace libxl;

void Excel::_CreateNewExcelBook(void){
    Book* book = xlCreateBook(); // xlCreateXMLBook() for xlsx
    if(book)
    {
        Sheet* sheet = book->addSheet("Sheet1");
        if(sheet)
        {
            sheet->writeStr(2, 1, "Hello, World !");
            sheet->writeNum(3, 1, 1000);
        }
        book->save("../data/example.xls");
        book->release();
    }
}
