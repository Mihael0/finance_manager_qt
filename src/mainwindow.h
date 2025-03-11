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
    /*
     * @brief This slot handles the signal emitted from LogIn window.
     * It shows the MainWindow to the user.
     */
    void on_Authenthication_successful(void);
    /*
     * @brief This slot handles the signal emitted from the ExpenseWindow.
     * It shows the MainWindow to the user.
     */
    void on_BackBtn_pressed(void);

signals:
    /*
     * @brief This signal is emitted whenever the on_DeclareExpenseBtn_clicked() slot is called.
     * It's purpose is to notify the ExpenseWindow that it must show itself to the user.
     */
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
