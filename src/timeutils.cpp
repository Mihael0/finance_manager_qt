#include "timeutils.h"


const QDateTime& TimeUtils::GetCurrentTime(void) const{

    return TimeUtils::_WorldClockTime;
}

void TimeUtils::SetAppTimeToStartOfMonth(void){
    const QDateTime CurrentWorldTime = TimeUtils::GetCurrentTime();
    QDate StartOfMonthTime = CurrentWorldTime.date();
    StartOfMonthTime.setDate(StartOfMonthTime.year(), StartOfMonthTime.month(),1);
    _LocalAppTime = StartOfMonthTime;
}

QDate TimeUtils::GetLocalAppTime(void){
    return _LocalAppTime;
}

void TimeUtils::IncrementDayOfAppTime(int increment_by){
    // check that day is a valid day.
    _increment_amount += increment_by;
    _LocalAppTime.setDate(_LocalAppTime.year(),_LocalAppTime.month(),_increment_amount);
}
