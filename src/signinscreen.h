#ifndef SIGNINSCREEN_H
#define SIGNINSCREEN_H

#include <QDialog>

namespace Ui {
class SignInScreen;
}

typedef struct{
    const QString User1 = "Mihael";
    const QString User2 = "Vanya";
} CREDENTIALS;

class SignInScreen : public QDialog
{
    Q_OBJECT

public:
    explicit SignInScreen(QWidget *parent = nullptr);
    ~SignInScreen();

private slots:
    void on_LogIn_clicked();

private:
    Ui::SignInScreen *ui;
};

#endif // SIGNINSCREEN_H
