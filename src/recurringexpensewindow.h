#ifndef RECURRINGEXPENSEWINDOW_H
#define RECURRINGEXPENSEWINDOW_H

#include <QWidget>

namespace Ui {
class RecurringExpenseWindow;
}

class RecurringExpenseWindow : public QWidget
{
    Q_OBJECT

public slots:
    void showRecurringExpenseWindow(void);

signals:
    /*
     * @brief This signal is emitted to notify the MainWindow that the RecurringExpenseWindow should be closed.
     */
    void closeRecurringExpenseWindowRequested(void);

public:
    explicit RecurringExpenseWindow(QWidget *parent = nullptr);
    ~RecurringExpenseWindow();

private slots:
    void on_backBtn_clicked();

private:
    Ui::RecurringExpenseWindow *ui;
};

#endif // RECURRINGEXPENSEWINDOW_H
