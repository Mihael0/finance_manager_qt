#include "recurringexpensewindow.h"
#include "ui_recurringexpensewindow.h"

RecurringExpenseWindow::RecurringExpenseWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RecurringExpenseWindow){
    ui->setupUi(this);
}

RecurringExpenseWindow::~RecurringExpenseWindow()
{
    delete ui;
}

void RecurringExpenseWindow::showRecurringExpenseWindow(void){
    this->show();
}

void RecurringExpenseWindow::on_backBtn_clicked()
{
    emit closeRecurringExpenseWindowRequested();
}

