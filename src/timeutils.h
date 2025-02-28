#ifndef TIMEUTILS_H
#define TIMEUTILS_H
#include "QDateTime"

/**
 * Keeps track of all Time related operations in the Application.
 * The class is made with the idea that there is only one static instance of it inside of mainwindow.cpp
 */
class TimeUtils{
public:
    QDateTime GetCurrentTime(void) const;
    QDate GetLocalAppTime(void);
    void IncrementDayOfLocalAppTime(void);
    void DecrementDayOfLocalAppTime(void);
    TimeUtils() {
        _SetAppTimeToStartOfMonth();
    }
private:
   const QDateTime _worldClockTime = QDateTime::currentDateTime();
   QDate _localAppTime;
   int _incrementAmount = 1;

   void _SetLocalAppTime(QDate newLocalAppTime){
       _localAppTime = newLocalAppTime;
   }
   void _SetAppTimeToStartOfMonth(void){
       QDate StartOfMonthTime = _worldClockTime.date();
       StartOfMonthTime.setDate(StartOfMonthTime.year(), StartOfMonthTime.month(),1);
       _localAppTime = StartOfMonthTime;
   }
};
#endif // TIMEUTILS_H
