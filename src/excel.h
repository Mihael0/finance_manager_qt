#ifndef EXCEL_H
#define EXCEL_H
#include "libxl.h"



typedef struct {

} FontNames_t;

class Excel {
public:
    // void StoreDailyExpense(float dailyExpense){
        // _DailyExpense = dailyExpense;
    // };

    void _CreateNewExcelBook(void);

    // Constructor that allows the user to pick to point at an existing excel book
    // or to create a new one.

private:
    // float _DailyExpense;
    // libxl::Book* _book;

    /**
     * Used to configure a given excel book.
     * For now it is static, which means the user cannot adjust
     * the different configurations of the given excel book.
     * If needed can be implemented.
     */
    // void _ConfigureExcelBook(libxl::Book* book){
    //     libxl::Font* textFont = book->addFont();
    //     textFont->setSize(8);
    //     textFont->setName("Century Gothic");

    //     libxl::Font* titleFont = book->addFont(textFont);
    //     titleFont->setSize(38);
    //     titleFont->setColor(libxl::COLOR_GRAY25);

    //     libxl::Font* font12 = book->addFont(textFont);
    //     font12->setSize(12);

    //     libxl::Font* font10 = book->addFont(textFont);
    //     font10->setSize(10);

    //     libxl::Format* textFormat = book->addFormat();
    //     textFormat->setFont(textFont);
    //     textFormat->setAlignH(libxl::ALIGNH_LEFT);

    //     libxl::Format* titleFormat = book->addFormat();
    //     titleFormat->setFont(titleFont);
    //     titleFormat->setAlignH(libxl::ALIGNH_RIGHT);

    //     libxl::Format* companyFormat = book->addFormat();
    //     companyFormat->setFont(font12);

    //     libxl::Format* dateFormat = book->addFormat(textFormat);
    //     dateFormat->setNumFormat(book->addCustomNumFormat("[$-409]mmmm\\ d\\,\\ yyyy;@"));

    //     libxl::Format* phoneFormat = book->addFormat(textFormat);
    //     phoneFormat->setNumFormat(
    //         book->addCustomNumFormat("[<=9999999]###\\-####;\\(###\\)\\ ###\\-####")
    //         );

    //     libxl::Format* borderFormat = book->addFormat(textFormat);
    //     borderFormat->setBorder();
    //     borderFormat->setBorderColor(libxl::COLOR_GRAY25);
    //     borderFormat->setAlignV(libxl::ALIGNV_CENTER);

    //     libxl::Format* percentFormat = book->addFormat(borderFormat);
    //     percentFormat->setNumFormat(book->addCustomNumFormat("#%_)"));
    //     percentFormat->setAlignH(libxl::ALIGNH_RIGHT);

    //     libxl::Format* textRightFormat = book->addFormat(textFormat);
    //     textRightFormat->setAlignH(libxl::ALIGNH_RIGHT);
    //     textRightFormat->setAlignV(libxl::ALIGNV_CENTER);

    //     libxl::Format* thankFormat = book->addFormat();
    //     thankFormat->setFont(font10);
    //     thankFormat->setAlignH(libxl::ALIGNH_CENTER);

    //     libxl::Format* dollarFormat = book->addFormat(borderFormat);
    //     dollarFormat->setNumFormat(
    //         book->addCustomNumFormat("_($* # ##0.00_);_($* (# ##0.00);_($* -??_);_(@_)")
    //         );
    // }

    /**
     * Uses the created _book to store a set _DailyExpense.
     */
    void _StoreDailyExpenseInDatabase(void){

    }
};


#endif // EXCEL_H
