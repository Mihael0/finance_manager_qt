#ifndef APPTIME_H
#define APPTIME_H

#include <QDateTime>
// #include <type_traits>

class AppTime
{
public:
    AppTime();
    /*
     * @brief Sets the value of _localAppTime. This function can accept either QDateTime or QDate arguments.
     * If the argument is QDateTime then it will take only the date from it and assign it.
     */
    template<typename T>
    void SetLocalAppTime(const T& newlocalAppTime,
                          typename
                          std::enable_if<std::is_same<T,QDate>::value
                            || std::is_same<T,QDateTime>::value
                            || std::is_same<T,QString>::value>::type* = 0){
        if constexpr (std::is_same<T,QDateTime>::value){
            _localAppTime = newlocalAppTime.date();
        }else if constexpr (std::is_same<T,QString>::value) {
            QDate date = QDate::fromString(newlocalAppTime, "dd-MM-yyyy");
            _localAppTime = date;
        }else{
            _localAppTime = newlocalAppTime;
        }
    }
    /*
     * @return the local time taken from the QDateTime library. This is the computer's set time.
     */
    QDateTime GetLocalTime(void) const{
        return _localTime;
    }
    /*
     * @return the local time taken from the QDateTime library as a string. This is the computer's set time.
     */
    QString GetLocalTimeAsString(void) const{
        return _localTime.toString("dd-MM-yyyy");
    }
    /*
     * @return _localAppTime, which is the internal variable used to keep track of the user specified day/month/year.
     */
    QDate GetLocalAppTime(void) const{
        return _localAppTime;
    }
    /*
     * @return _localAppTime as a string, which is the internal variable used to keep track of the user specified day/month/year.
     */
    QString GetLocalAppTimeAsString(void) const{
        return _localAppTime.toString("dd-MM-yyyy");
    }
    /*
     * @brief Decrements the LocalAppTime by 1 day. Uses the QDateTime library to handle transition between months.
     */
    void DecrementDayOfLocalAppTime(void){
        SetLocalAppTime(GetLocalAppTime().addDays(-1));
    }
    /*
     * @brief Increments the LocalAppTime by 1 day. Uses the QDateTime library to handle transition between months.
     */
    void IncrementDayOfLocalAppTime(void){
        SetLocalAppTime(GetLocalAppTime().addDays(1));
    }

private:
    const QDateTime _localTime = QDateTime::currentDateTime();
    QDate _localAppTime;

    /*
     * @detail Initializes _localAppTime to be the start of the month.
     * Make sure this, or another initialization function of _localAppTime is called
     * before using any of the setters/gettters of _localAppTime.
     * Failing to do so, will lead to undefined behaviour.
     */
    void _InitializeAppTimeToStartOfMonth(void){
        QDate StartOfMonthTime = _localTime.date();
        StartOfMonthTime.setDate(StartOfMonthTime.year(), StartOfMonthTime.month(),1);
        SetLocalAppTime(StartOfMonthTime);
    }
};

#endif // APPTIME_H
