#ifndef CREATESUMMARYWINDOW_H
#define CREATESUMMARYWINDOW_H

#include <QWidget>

namespace Ui {
class CreateSummaryWindow;
}

class CreateSummaryWindow : public QWidget
{
    Q_OBJECT

public slots:
    /*
     * @brief This slot is used by the MainWindow to notify the CreateSummaryWindow that it must show up.
     */
    void showCreateSummaryWindow(void);

signals:
    /*
     * @brief This signal is emitted to notify the MainWindow that the CreateSummaryWindow should be closed.
     */
    void closeCreateSummaryWindowRequested(void);

public:
    explicit CreateSummaryWindow(QWidget *parent = nullptr);
    ~CreateSummaryWindow();

private slots:
    void on_backBtn_clicked();

private:
    Ui::CreateSummaryWindow *ui;
};

#endif // CREATESUMMARYWINDOW_H
