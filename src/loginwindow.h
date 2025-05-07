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
    /*
     * @brief triggered whenever the login in button is clicked and if password and username are correct, tells the MainWindow to show itself.
     */
    void on_LogIn_clicked();
    /*
     * @brief toggles if the password is in plain-text or is hidden.
     */
    void on_isShowPasswordToggled_toggled(bool checked);

private:
    Ui::LogInWindow *ui;
};

#endif // LOGINWINDOW_H
