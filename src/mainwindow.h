#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_dailyExpenses_returnPressed();

    void on_nextDay_clicked();

    void on_previousDay_clicked();

private:
    Ui::MainWindow *ui;
    const QDateTime _worldClockTime = QDateTime::currentDateTime();
    QDate _localAppTime;

    void _SetLocalAppTime(QDate newLocalAppTime){
        _localAppTime = newLocalAppTime;
    }
    void _InitializeCurrentMonth(void);
    /*
     * Initializes _localAppTime to be the start of the month.
     * Make sure this, or another initialization function of _localAppTime is called
     * before using any of the setters/gettters of _localAppTime.
     * Failing to do so, will lead to undefined behaviour.
     */
    void _SetAppTimeToStartOfMonth(void){
        QDate StartOfMonthTime = _worldClockTime.date();
        StartOfMonthTime.setDate(StartOfMonthTime.year(), StartOfMonthTime.month(),1);
        _SetLocalAppTime(StartOfMonthTime);
    }
    QDateTime _GetCurrentTime(void) const{

        return _worldClockTime;
    }

    QDate _GetLocalAppTime(void) const{
        return _localAppTime;
    }

    void _IncrementDayOfLocalAppTime(void){
        _SetLocalAppTime(_GetLocalAppTime().addDays(1));
    }

    void _DecrementDayOfLocalAppTime(void){
        _SetLocalAppTime(_GetLocalAppTime().addDays(-1));
    }
};
#endif // MAINWINDOW_H
