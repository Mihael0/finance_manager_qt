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

private slots:
    void on_LogIn_clicked();

private:
    Ui::LogInWindow *ui;
    bool _authenthicationSuccessful = false;

    void _SetAuthenthicationSuccessful(bool isSuccessful){
        _authenthicationSuccessful = isSuccessful;
    }

    bool _GetAuthehtnicationSuccessful(void){
        return _authenthicationSuccessful;
    }
};

#endif // LOGINWINDOW_H
