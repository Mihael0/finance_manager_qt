#include "timeutils.h"

QDateTime TimeUtils::GetCurrentTime(void) const{

    return TimeUtils::_worldClockTime;
}

QDate TimeUtils::GetLocalAppTime(void){
    return TimeUtils::_localAppTime;
}

void TimeUtils::IncrementDayOfLocalAppTime(void){
    _SetLocalAppTime(GetLocalAppTime().addDays(1));
}

void TimeUtils::DecrementDayOfLocalAppTime(void){
    _SetLocalAppTime(GetLocalAppTime().addDays(-1));
}
