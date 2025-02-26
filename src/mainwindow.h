#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void InitializeCurrentMonth(void) const;
    ~MainWindow();

private slots:

    void on_dailyExpenses_returnPressed();

    void on_nextDay_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
