#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>

namespace Ui {
class LogInWindow;
}

// TODO: Implement an actual authenthication. For now this is a placeholder.
typedef struct CREDENTIALS{
    const QString User1 = "Mihael";
    const QString User2 = "Vanya";
} CREDENTIALS;

class LogInWindow : public QDialog
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
