#ifndef TIMEUTILS_H
#define TIMEUTILS_H
#include "QDateTime"


class TimeUtils{
public:
    // google this?!
    // adjust this.
    static TimeUtils& instance() {
        static TimeUtils instance;  // Guaranteed to be destroyed.
        return instance;
    }

    const QDateTime& GetCurrentTime(void) const;
    void SetAppTimeToStartOfMonth(void);
    QDate GetLocalAppTime(void);
    void IncrementDayOfAppTime(int increment_by);
private:
   // TimeUtils() {}  // Private constructor to prevent instancing
   const QDateTime _WorldClockTime = QDateTime::currentDateTime();
   QDate _LocalAppTime;
   int _increment_amount = 1;
};
#endif // TIMEUTILS_H
