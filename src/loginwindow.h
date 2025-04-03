#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>

namespace Ui {
class LogInWindow;
}

class LogInWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LogInWindow(QWidget *parent = nullptr);
    ~LogInWindow();

signals:
    /*
     * @brief This signal is used to notify the MainWindow that the authenthication has succeeded.
     */
    void authenthicationSucceeded(void);

private slots:
    void on_LogIn_clicked();

private:
    Ui::LogInWindow *ui;
};

#endif // LOGINWINDOW_H
