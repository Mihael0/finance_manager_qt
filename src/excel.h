#ifndef EXCEL_H
#define EXCEL_H
#include "libxl.h"
#include "string"



typedef struct {

} FontNames_t;

class Excel {
public:
    // void StoreDailyExpense(float dailyExpense){
        // _DailyExpense = dailyExpense;
    // };

    void _CreateNewExcelBook(std::string BookName);

    // Constructor that allows the user to pick to point at an existing excel book
    // or to create a new one.

private:
    // float _DailyExpense;
    libxl::Book* _book;

    /**
     * Used to configure a given excel book.
     * For now it is static, which means the user cannot adjust
     * the different configurations of the given excel book.
     * If needed can be implemented.
     */
    // void _ConfigureExcelBook(libxl::Book* book){

    // }
    /**
     * Uses the created _book to store a set _DailyExpense.
     */
    void _StoreDailyExpenseInDatabase(void){

    }
};


#endif // EXCEL_H
