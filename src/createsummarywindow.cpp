#include "createsummarywindow.h"
#include "ui_createsummarywindow.h"

CreateSummaryWindow::CreateSummaryWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CreateSummaryWindow){
    ui->setupUi(this);
}

CreateSummaryWindow::~CreateSummaryWindow(){
    delete ui;
}

void CreateSummaryWindow::showCreateSummaryWindow(void){
    this->show();
}

void CreateSummaryWindow::on_backBtn_clicked()
{
    emit closeCreateSummaryWindowRequested();
}

