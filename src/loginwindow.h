#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>

namespace Ui {
class LogInWindow;
}

typedef struct{
    const QString User1 = "Mihael";
    const QString User2 = "Vanya";
} CREDENTIALS;

class LogInWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LogInWindow(QWidget *parent = nullptr);
    ~LogInWindow();
    bool AuthenticationSuccessful(void);

signals:
    void AuthenthicationSuccessful(void);

private slots:
    void on_LogIn_clicked();

private:
    Ui::LogInWindow *ui;
};

#endif // LOGINWINDOW_H
