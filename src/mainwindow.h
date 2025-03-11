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

public slots:
    void on_Authenthication_successful(void);
    void on_BackBtn_pressed(void);

signals:
    void on_DeclareEpxenseBtn_clicked(void);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();    

private slots:
    void on_DeclareExpenseBtn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
